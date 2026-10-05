# Plan: finding speedrun-relevant bugs by analysing the game code

A plan for reading this repository's recovered source to find bugs a speedrun could use
(movement speed, clips, sequence breaks, skips, load and checkpoint tricks). **The work is
analysis of the code itself:** no running the game, no emulator, no disc data, no other
executables. Every finding is a statement about what the code does, backed by the code.

## 1. Scope

- **The code analysed** is this repository's source: the game (`src/recovered`, `src/COD`,
  `src/Source`) and the RenderWare Studio framework (`src/rws`), with RenderWare and RenderWare
  Audio read only where game code calls into them.
- **This is the multiplayer executable's code.** Its own levels are the multiplayer maps, and it
  launches `d:\default.xbe` for the campaign. The engine and most game systems (player movement,
  collision, triggers, section streaming, the level-script system, checkpoints, weapons, AI,
  vehicles) are this code; findings are stated as properties of this code, with a note where
  a finding depends on multiplayer-only paths.
- **Not in scope:** testing in the game or an emulator, level data, timing on hardware. Where a
  finding's usefulness depends on things only testing can settle (level geometry, script
  contents, frame windows), the finding says so and lists exactly what would need checking.
- **Cheats and the debug menu** are analysed as code (what they change and how they are
  reached), flagged as not run material.

## 2. Where to look (measured 2026-10-05)

| Area | Where it is | What makes it interesting |
|---|---|---|
| Frame time | the `deltaTime` global: 77 uses in 31 files | Each use is either integrated (`x += v * dt`) or per-frame; per-frame logic behaves differently at other frame rates |
| Collision | 18 files calling RenderWare collision (`RpCollisionWorldForAll...`, `RtIntersection...`) | How movement is tested against geometry |
| Triggers | 114 files; types include `PlayerTrigger`, `EndLevelTrigger`, `LevelScriptTrigger`, `LadderTrigger`, `ConfinedAreaTrigger`, `MountedWeaponTrigger`, `PickupTrigger`, `GimpVehicleTrigger`, `DestructableObjectTrigger`, `AnimPackTrigger`, `CustomTrigger` | What each tests, when, and against what; moved triggers (`"*Trigger (%d) being moved to:..."`) |
| Level-script API | `Efunc*` functions and the script calls `AddObjective`, `ModifyObjectiveCounter`, `ClearObjectiveFlags`, `EnableEndLevelTrigger`, `GetCheckPointRegister`, `GetGlobalRegister_AsGodName`, `IsLevelSectionLoaded`, `AddTaskTrigger`, `GetNumberOfObjectsInTrigger`, `IsNamedEntityInTrigger` | The primitives level scripts use to gate progress; their checks define what scripts can rely on |
| Section streaming | `AsynchLoadingQueue`, section banks (`"Adding load of section %d to AsynchQueue..."`, `"Aborting load of section %d"`, `"Canceling queued load of section %d"`, `"no section bank available to load Collision BSP for section %d"`) | Per-section collision; aborted and cancelled loads |
| Player carry-over | `"PlayerTrigger: using player attribs from previous level or from memCard"`, `Player::Init` | What passes from level to level or from a save |
| Checkpoints and saves | 7 files (`SerializeManager`, `XCreateSaveGame`, the checkpoint register) | What a reload restores and what it does not |
| Movement states | ladders (`"getting off the ladder because player is on ground."`), mounted weapons (`AttachToMountedWeapon`, `DetachFromMountedWeapon`), crouch/prone, vehicles | State transitions |
| Debug and cheats | `"MAIN DEBUG MENU"`, `"Debug Switches"`, `"Cheats"`, `"Game Speed"`, `"Cheatflags Address %x"`, `ePE_RUNSPEEDCHEAT`, `"Unlimited Ammo"`, `"Level change to %d"` (`unit_183130`) | How they are reached, and what they reveal about the mechanics they change |

## 3. Analysis tooling (Phase 0, 1-2 weeks)

All of these read the source and the compiled objects only:

1. **Call graph and cross-references** (`tools/speedrun/xref.py`): from our objects' relocations
   and the sources, who calls what, who reads and writes each global and each struct member
   (`unk_XX` fields included). This is the backbone for "what else touches this state?".
2. **State-variable index** (`tools/speedrun/stateidx.py`): for each player, trigger, objective,
   section and checkpoint variable, every read and write site with the condition guarding it.
3. **Pattern scanners** (`tools/speedrun/scan_*.py`), one per bug class in section 4: they emit
   candidate lists with file, function and the matching code.
4. **Update-order map** (`tools/speedrun/frameorder.py`): the per-frame update sequence (input,
   player, triggers, AI, physics, streaming, scripts) traced from the main loop, so ordering
   bugs (state read before or after it is updated within a frame) can be seen.
5. **Findings log template** (section 6).

## 4. Bug classes: patterns to find and how to analyse them

Each class lists the code to find, what to establish from it, and what would make it useful.

### 4.1 Movement speed

- **Find:** where stick and button input become a velocity; every speed multiplier (stance,
  sprint, aiming, carrying, damage), their caps, and the code that clears or keeps velocity on
  state changes.
- **Establish:**
  - Diagonal input normalised or not (forward + strafe giving more than the forward speed).
  - Multipliers that stack, or that stay applied after their state ends (leaving a ladder or a
    mounted weapon mid-transition).
  - Velocity kept across mount/dismount, landing and ladder exits.
  - External impulses (explosions, grenades, vehicles, AI pushes): their direction, magnitude
    and caps, and whether they add vertical velocity.
- **Useful if:** a reachable input or state combination yields more speed than intended; the
  write-up gives the formula and the conditions.

### 4.2 Frame-rate and timing dependence

- **Find:** all 77 `deltaTime` uses; timers in the alfa timer/scheduler; script waits.
- **Establish:**
  - which integrations are per-frame vs time-based;
  - whether `dt` is clamped, so a long frame cannot let movement skip collision or timers jump;
  - which timers run during pauses, cutscenes and loading;
  - how PAL/NTSC and 480i/480p video modes (`XGetVideoFlags`) change any of it.
- **Useful if:** a mechanic's result depends on frame time in a direction a runner can exploit
  (faster at lower frame rates, skippable at a hitch).

### 4.3 Collision clips and out-of-bounds

- **Find:** the player's collision query (segment vs end-point tests), step-up and slope limits,
  stance capsule sizes, the stand-up check from crouch/prone, attach/detach positions for mounted
  weapons, vehicles and ladders, and how section collision worlds are loaded and unloaded.
- **Establish:**
  - Whether a fast enough move can pass through a thin wall: the speed from 4.1 times the
    largest `dt` against the test used.
  - Whether standing up into geometry is checked.
  - Whether detaching places the player at a locator without a collision check.
  - What happens to collision when the player is in a section whose collision BSP is not
    loaded, or whose load was aborted or cancelled (`AbortUnneededSections`).
- **Useful if:** a code path moves or places the player without the usual collision test.

### 4.4 Trigger and sequence breaks

- **Find:** each trigger type's test (point in volume, line crossing, capsule overlap), when it
  runs (every frame or less often), and its effect; every script-API function that gates
  progress.
- **Establish:**
  - Whether a trigger can be passed between two frames' tests.
  - Whether end-of-level and progression triggers check prerequisites themselves or only rely
    on the script enabling them.
  - How moved and re-oriented triggers behave in the frames around a move.
  - Whether counters can be double-incremented (entering twice, one kill counted twice) or
    satisfied by `>=` where `==` was intended.
  - Whether flags are cleared on reload.
  - Whether a script wait can be satisfied early.
- **Useful if:** progress can be reached in an order or way the gates do not stop. Which levels
  have such a layout is a level-data question, recorded as such.

### 4.5 Loading, streaming and level transitions

- **Find:** how sections are chosen for loading by position (`StartingSections`, the queue), the
  abort/cancel paths, and the level-end save and next-level read of player attributes.
- **Establish:**
  - What happens when the player outruns the load queue or doubles back.
  - What is carried between levels (health, ammo, weapons, items picked up out of order).
  - What decides load length.
- **Useful if:** a carry-over or streaming behaviour skips work or gives an advantage later.

### 4.6 Checkpoints, saves and reloads

- **Find:** everything a checkpoint saves and restores (`GetCheckPointRegister`, the serialize
  manager), the die / restart-checkpoint / restart-level paths (`"at restart//shutdown"`), and
  saves loaded from the memory unit.
- **Establish:** state the game depends on that a reload does not restore, or restores
  inconsistently:
  - triggers left fired or re-armed;
  - objective progress kept while the position rewinds ("save warps");
  - duplicated inventory.
- **Useful if:** a reload changes progress in the runner's favour.

### 4.7 Cutscenes, movies and skips

- **Find:** skip handling (`" to skip"`), movie playback and its end (Bink calls), and the script
  state after a skip.
- **Establish:** what a skip skips besides the picture (timers, script steps, spawns), and
  whether skip timing matters.

### 4.8 Combat and AI gates

- **Find:** damage and invulnerability windows, fall damage, difficulty scaling; AI conditions
  scripts wait on; spawning from triggers and its failure paths (`"A spawn could not be created
  due to lack of entity memory"`, `"Cannot create soldier entity from trigger loc"`).
- **Establish:** whether a gating spawn can fail (entity memory exhausted) and what the script
  does then; invulnerability windows usable for movement through danger.

### 4.9 Memory-safety bugs

- **Find:** array indexing from counters, input or level data without bounds checks; entity
  deletion and later use; uninitialised locals and members; counter overflow and underflow.
- **Establish:** reachability from player actions (pickups, inventory changes, triggers) and the
  state each one can corrupt.

### 4.10 Debug menu and cheats (analysed, not run material)

- **Find:** the debug menu code (`unit_183130`, `DebugMenu.layout`), the cheat flags
  (`ePE_RUNSPEEDCHEAT`, unlimited ammo, game speed), and every check of them.
- **Establish:** how each is reached in this build (input codes, unlocks, compiled-out paths),
  and what each changes. The run-speed cheat, for one, shows exactly where player speed is
  computed, which feeds 4.1.

## 5. Phases

| Phase | Work | Duration |
|---|---|---|
| 0 | Analysis tooling (section 3) | 1-2 weeks |
| 1 | Scanners over all classes; ranked candidate lists | 2 weeks |
| 2 | Deep reads by subsystem, in order of likely payoff: player movement and collision, triggers and the script API, section streaming, checkpoints, level transitions, cutscenes, combat and AI, memory safety | 6-10 weeks |
| 3 | Write-ups (section 6) | alongside 2 |

**Ranking:** the potential effect (time a runner could save if the level layout allows it), times
how directly the code permits it. Each finding also gets the precision a runner would need, as
far as the code shows it: a frame window, an exact angle or position tolerance, or none.

## 6. Recording findings

`docs/speedrun/findings.md`, one entry per candidate, kept even when the analysis rules it out:

- **ID, class, status** (candidate / established from code / ruled out).
- **Code:** functions, files, addresses; the relevant lines quoted.
- **Mechanism:** what the code does, step by step, and why it allows the behaviour.
- **Conditions:** the states, inputs and timing the code requires.
- **Open questions:** what only the level data or testing could settle (geometry, script
  contents, frame windows on hardware), stated precisely so someone can check them later.
- **Confidence:** how directly the code shows it (fully determined by the code read / depends on
  unread callers / depends on data).

`docs/speedrun/systems/<subsystem>.md`: per-subsystem notes (update order, state variables,
formulas), the reference the findings build on.

Names found during the analysis go into the naming registry (docs/NAMING_PLAN.md) with their
evidence; the analysis changes no code.
