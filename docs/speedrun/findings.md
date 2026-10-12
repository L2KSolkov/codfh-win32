# Speedrun findings from the code

Bugs and quirks in *Call of Duty: Finest Hour* (Xbox, single player) that a speedrun could use,
found by reading the recovered source (2026-10-11). **None of it has been tested in the game
yet.** Each entry gives the code, how it works, what a runner needs, and what to test. Line
numbers are in `src/recovered/` unless another path is given; `sp_` files are
`src/sp/units/`.

Confidence labels:

- **code**: the code read shows the whole mechanism.
- **data**: the mechanism is in the code, but whether it pays off depends on level data
  (geometry, script contents, per-level attributes).
- **test**: depends on timing or hardware behaviour that only testing settles.

Units are centimetres (100 per metre). Frame time is in 60 Hz ticks: `deltaTime` is 1.0 at
NTSC 60, 1.2 at PAL 50, 2.0 at 30 fps, capped at 5.0 (`unit_0D95A0.cpp:107-139`).

---

## Ranked shortlist

| # | Finding | Kind | Likely value | Confidence |
|---|---|---|---|---|
| 1 | [Pause-menu Restart skips intros in ~12 levels](#c9-per-level-results-from-the-level-data) | restart skip | every listed level | data |
| 2 | [Diagonal movement is 1.41x](#m1-diagonal-movement-is-not-normalised) | movement | every level | code + test (pad range) |
| 3 | [Creep step-up over high edges](#k1-creep-step-up-walls-with-a-low-edge-give-way) | collision | route shortcuts | code + data |
| 4 | ["Clear the area" counts positions, not deaths](#t2-clear-the-area-means-no-enemy-position-inside-the-volume) | objectives | per objective | code + data |
| 5 | [Checkpoints can be set out of order](#c3-checkpoints-can-be-set-out-of-order) | sequence break | data | code + data |
| 6 | [Dying refills health and the default loadout](#c2-dying-gives-back-full-health-and-the-default-loadout) | resource | moderate | code |
| 7 | [Turning saving off saves ≥1 s per level](#c4-saving-off-saves-at-least-1-s-per-level-transition) | load time | ~20 s+ per full run | code |
| 8 | [Unlock-all-levels code and the cheat unlock rule](#x1-cheats-and-unlocks-category-rules) | categories | rules | code + test |
| 9 | [Tank blind spots](#a-tanks) | combat | per tank fight | code |
| 10 | [Ladders: grab mid-air, no fall damage, faster at low fps](#m3-ladders) | movement | data | code |
| 11 | [Untested placement on dismount and vehicle exit](#k3-placement-with-no-collision-test) | clip | data | code + data |
| 12 | [Section collision missing until loaded](#k4-collision-exists-only-for-loaded-sections) | OOB / fall-through | data | code + test |
| 13 | [Item button cancels a reload](#a-weapons) | weapons | every fight | code + test |
| 14 | [Face shooters, strafe through fire; stay < 650 from grenadiers](#a-damage-and-survival) | combat | every fight | code |
| 15 | [Corpse-slot spawns vanish; eviction skips death messages](#a-spawning-and-kill-gates) | wave skips | data | code + test |
| 16 | [Vehicles ignore walls below speed 2](#v1-below-speed-2-the-vehicle-ignores-world-walls) | clip (driving) | big where a wall hides a shortcut | code + data + test |
| 17 | [L_3_1_C rockets respawn every 1 s](#p2-respawning-pickups) | resources | fights and tanks | code + data |
| 18 | [L_2_2 MG nest dies to one far barrel shot](#d4-destructibles-that-open-things) | skip | one fight | data |
| 19 | [L_1_1_B kill-on-ground zones: 0.1 s death warps](#o8-pulse-zones-fast-death-warps-and-mines) | death warp | with C1/C3 | code + data |
| 20 | [Crawl under triggers (they test eye height)](#t-triggers-scripts-and-objectives) | trigger avoid | data | code |
| 21 | [Wall-collapse and door panels go non-solid](#d2-animated-geometry-that-does-turn-its-collision-off) | clip | L_1_3 | code + data |
| 22 | [Walk-through glass and AI-only walls](#d5-collision-surfaces-from-the-levels-data) | routing | per level | data |

---

## M. Movement

### M1. Diagonal movement is not normalised

- **Code:** `sub_19DA80`/`sub_19DB10` (`unit_19D920.cpp:150-180`) read each stick axis on its
  own. The dead zone is square (0.32, not rescaled), and anything above 0.95 snaps to 1.0.
  Forward speed is `unk_C0.z = axis * fwd` (`type_10F710::sub_109110`, `unit_0FD730.cpp:5309`),
  strafe is `unk_C0.x = axis * strafe` (`sub_109660`, 5455). Nothing takes the vector's length.
- **Effect:** speed = √((F·fy)² + (S·sx)²), with F and S the per-stance speeds
  (`unk_164[stance]`, `unk_1E4[stance]`, per level). If the pad reads ≥ 0.95 on both axes at
  the diagonal, that is √(F²+S²): **1.414x** when F = S. At (0.8, 0.8) it is about 1.13x; at a
  round gate's (0.707, 0.707), nothing.
- **Real numbers:** L_1_1's PlayerTrigger gives standing forward 12.87 and strafe 10 per tick.
  That is 386 u/s forward against **489 u/s diagonal (1.27x)**, if the pad reaches the corner
  (see the per-level table, when filled in).
- **Use:** hold forward plus strafe, with the view turned about 38-45° to compensate.
- **Test:** log `sThumbLX/LY` at a full diagonal on a real pad. Time one straight distance
  forward-only, then diagonally.

### M2. Aiming at an enemy uses a different strafe speed (the aim ray reaches 350 through walls)

- **Code:** in `vf_03C` (2483-2530) the aim pass casts 2000 units (`unk_334`) along the camera.
  If it hits world geometry, the line is **extended 350 past the hit**
  (`end = v_D8*350 + v_C0`, 2519). `sub_100AD0` (2154-2196) then sets `unk_454 = 1` and an
  interpolated strafe speed `unk_480`. In `sub_10A9D0` (6062-6066), while `unk_454` is set,
  strafing uses `unk_480` in place of `unk_1E4[stance]`, and turning uses `unk_37C` (12) in
  place of `unk_1B4` (2).
- **Defaults** (`unit_0A9980.cpp:184-187`): standing 12 at 0 units down to 9 at 2000;
  crouched 4 to 2; prone 2 to 1. The levels' own strafe speeds decide whether this is faster.
- **Conditions:** the aim pass must be on for the level (`flt_4B8F2C`, `unit_0B07D0.cpp:956`).
  The target must be a live enemy, which can be up to 350 units behind a wall.
- **Test:** time strafing with the crosshair on an enemy (including one behind a thin wall)
  against strafing with it off.

### M3. Ladders

- **Grabbed from anywhere, in any state:** `LadderTrigger::vf_028` (`unit_0CAA90.cpp:92-145`)
  counts the player as inside without any facing test when nearer the top than the bottom.
  The grab (`sub_114920`, `unit_0FD730.cpp:9992-10040`, from `unit_144940.cpp:522`) only
  stores the state (`sub_1090F0(0xD)`). It does not check for falling, jumping or anything
  else, and needs no button.
- **No fall damage:** while on a ladder, the fall height resets every frame
  (`unk_510 = -1000000.0f`, 9634-9640), and so does the fall timer `unk_518`. **Falling into
  the top half of a ladder volume cancels any fall.** At the bottom the player drops off and
  falls again from there.
- **Faster at low frame rates:** the climb is a spring (`sub_112DA0`, 9390) that runs
  `int(t20)` whole steps plus a blended part step, at most 10 units per step. Simulated with
  the real constants (`scratchpad/agent_move/ladder.py`): **≈227 u/s at 60 fps, ≈271 at PAL
  50, 300 at ≤30 fps.**
- **Climb direction bug:** "looking down" is `atan2(at.y, at.x)*57.3 < -15` (10032, 10075),
  which is not pitch. Facing −x or ±z, the slightest downward look reverses the climb and
  makes bottom grabs fail. It saves no time, but explains lost inputs.
- **Test:** walk off a > 3 m ledge straight into a ladder's top. Time one ladder at 60 fps and
  at 30 fps.

### M4. Scripted spline walks: Action ends them

- **Code:** `sub_10B930` (6450-6497). The walk advances about 1 unit per frame (60 u/s on NTSC,
  50 on PAL, no frame-time scaling). Pressing Action (`ePE_ACTION`, event 15) sets state 0
  at once (6481). It starts only from PlayerTrigger attribute 115 (`unit_0A9980.cpp:956`).
- **Use:** wherever a level walks the player along a spline, press Action. **Data:** which
  levels set attribute 115.

### M5. When hit, forward is blocked but strafing is not

- `sub_109110` (5354): while `unk_19F0 > 0`, forward stick gives 0 speed. Backward and strafe
  still work. Set on bullet hits (only when the shooter is on screen) and every damaging blast.
- **Bug:** in `PlayerTrigger::HandleAttributes` (`unit_0A9980.cpp:384-388`), case 7 has no
  `break`, so the bullet-invulnerability time also becomes the forward-block time.
- **Use:** when hit, turn 90° and strafe.

### M6. Slow motion and shell shock: the player is not slowed, but timers are

- "TimeScale" (`unit_0441B0.cpp:2416-2440`) fixes `deltaTime` at 0.2 per **drawn frame**.
  Explosions within half their radius and "PlayerShock" (`sub_1109A0`, 8574) scale real time
  by 0.2.
- The player's step is floored at 0.5, so at 60 fps the player moves at full real speed.
  Meanwhile AI, script timers, animations and grenades run at a fifth.
- Scripted slow-mo is counted in frames: 1 s of it lasts 5 s at 60, 6 s on PAL, 10 s at
  30 fps. **Keep the frame rate high during scripted slow-mo, and prefer 60 Hz.**
- Shell shock also makes bullet invulnerability (`unk_19EC`) and the forward block last 5x
  longer. It is a loss whenever you are waiting on a timed script.

### M7. Jumping

- The default jump strength `unk_1D8` is 0.75 (`unit_0A9980.cpp:136`), below gravity's first
  step, so by default a jump never leaves the ground. That matches the retail game.
- If a level sets attribute 62, the height depends on that frame's step: up to about 2-4x
  higher when jumping on the frame after a dropped frame (best when step H = J/10).
- Jumping off a ladder ignores both the stance check and the cooldown.
- **Data:** attribute 62 per level.

### M8. Frame rate in general

- NTSC 60's whole-millisecond tick jitter (16/17/17 ms) plus the 0.5 floor gives about 1.3%
  more movement per second than PAL 50 (**test**).
- Ladders favour low fps (M3); slow-mo favours high fps (M6).
- Below 30 fps the fall timer runs about twice as fast (K5).

**Ruled out:**

- There is no momentum: horizontal velocity is rebuilt every frame and none carries over from
  vehicles, mounts, ladders or landing.
- There is no sprint, no weight penalty and no low-health slowdown.
- Explosions and bullets do not push the player.
- `ePE_RUNSPEEDCHEAT` is read only by the debug menu.
- A load hitch gives at most a 2.5x step, split in two for collision.

---

## K. Collision and clips

How it works: the player moves each frame, then runs one ground search with two spheres of
radius rx = 0.8 × `unk_4C`. `unk_4C` comes from the PlayerTrigger (`unit_0A9980.cpp:1288`,
default 90); the levels' data sets **55**, so **rx = 44**. Then one line is cast between the old and new frame positions, at
**eye height** (see T) (`type_10F710::vf_044`, `unit_0FD730.cpp:9503-9738`; spheres and floor
probe in `sub_96680`, `unit_0929A0.cpp:1730-1880`). The move is split into two halves only
when dt > 2 or the first line test hits. There is no sweep of the body.

### K1. Creep step-up: walls with a low edge give way

- **Mechanism:** the height comes only from the floor snap, so the vertical part of each
  sphere push-out is thrown away the next frame. Against an edge below the bottom sphere's
  centre, the push points mostly up, and only its small horizontal part resists. If the
  forward move per half-step is larger than that, the centre creeps over the edge, the floor
  probe finds the top, and the snap lifts the player onto it.
- **Thresholds** (rx 44, standing; forward move needed per half-step):

  | Edge height | 42 | 48 | 54 | 60 | 66 | 72 | 78 |
  |---|---|---|---|---|---|---|---|
  | Move needed | 0.7 | 2.8 | 5.8 | 9.9 | 15.1 | 21.9 | 31.4 |

  The top of the edge must also be no higher than the centre (feet + bp_8). The nominal step
  is 38. Prone shifts the table down by 19.
- **Frame-rate dependence:** the move per half-step grows with dt, so **lower frame rates
  climb higher edges**. Diagonal speed (M1) helps too.
- **Use:** walk onto crates, sandbags and low walls well above the normal step, with no jump.
- **Test:** run at full (diagonal) speed into boxes of rising height, then crouched, then at
  30 fps.

### K2. Steep slopes and gaps

- Any up-facing surface up to **69.4°** (|n.y| ≥ 0.352, `flt_4290EC`) is walkable ground, with
  no sliding or slowdown.
- The four floor-probe points are fixed world offsets, not rotated with the player: `{0,0,0}`,
  `{0,0,-20}`, `{±14.14,0,14.14}`. The player can therefore overhang ledges by up to 20 units
  toward −z and does not fall into gaps narrower than about 34 (z) or 28 (x).
- **Use:** run straight up steep rubble or embankments.

### K3. Placement with no collision test

Each of these moves the player with `vf_0C0` while the move-and-collide flags are off. When
normal movement resumes, the frame-gap reset (`unit_0FD730.cpp:9863`,
`if (bp_8 - unk_424 > 2)`) takes the new spot as the last position, so the line test never
sees the jump.

- **Mounted-gun dismount** (`sub_168A90` → `sub_16A030`, `unit_166990.cpp:856-870,
  1357-1393`): the player lands at the gun's mount frame + offset + **120 up**, including its
  facing. There is no facing requirement to mount, just contact plus a clear line of sight
  (`sp_sub_C2DF0`, `unit_0FD730.cpp:7516-7537`). **Use:** touch a gun from the outside of a
  bunker slit or window, mount, dismount, and land inside. Whether that works depends on each
  gun's collision (**data**).
- **Vehicle exit** (`sub_10FBF0`, 8113-8143): 150 up in the **vehicle's** local frame. On a
  tilted vehicle that points sideways, into a wall or onto an overhang. Exits happen only in
  VehicleEnterExitTrigger volumes, through scripts (**data**).
- **Exit/enter transition** (state 14, `sub_10BB30`, 6640-6657): no collision at all while it
  blends to the script's point.
- **Ladders** (`sub_114AA0`): no line test, spheres only (≤ 10 units per step, so a clip is
  unlikely).
- **Script teleports:** "SetMyPosition", "TeleportToNamedObject", "SnapToCover".

### K4. Collision exists only for loaded sections

- Every collision query loops the section banks `dword_4E5D30[0..3]`. A section's collision
  goes live only when its load completes (`sub_D8230`, `unit_0D7F20.cpp:186-206`), and
  **nothing pauses or stops the player meanwhile**.
- **Entering a section trigger** (`sub_145060`, `unit_144940.cpp:360-477`) does three things:
  - destroys one bank at once;
  - queues the new section;
  - cancels queued loads not on its list; a load in progress is destroyed when it finishes
    (`unit_0811C0.cpp:411-415`).
- With nothing loaded under you there is no floor and no walls: you fall. Death then comes
  from the fall timer (K5) or fall damage.
- **Use:** an out-of-bounds or fall-through route by outrunning a load, or by crossing two
  section triggers back and forth to cancel one.
- **Risk:** if no bank is free the loader dereferences NULL (`unit_141BB0.cpp:259`), so
  skipping section triggers can crash.
- An aborted load still reads the whole file first, so back-and-forth costs a full load each
  time.
- **Test:** this needs per-level section-trigger layouts; the port's trigger overlay shows
  them.

### K5. The fall timer runs double below 30 fps

- `unk_518 += clamp(dt*0.5, 0.5, 4)` sits **inside** the half-step loop (9641-9645), so it
  counts twice whenever the move is split (dt > 2, or the first line test hits). The fall death
  (`flt_429B38` = 120) comes at about 2 s instead of 4 s.
- The pre-move test's correction is computed and then thrown away (9562-9589), so it only
  forces the split.
- **Use:** a faster death warp from a long fall (see C1). It is a hazard otherwise.

### K6. The line test can miss a thin wall

- `sub_91F40` (`unit_08E670.cpp:691-820`) takes the **first** crossing triangle per tree leaf,
  not the nearest. For the player, a hit facing away is dropped (`if (var_4 > 0.0f) return;`).
  If the far face of a thin wall comes first in its leaf, the wall is missed, and only the
  spheres stop you.
- A clean clip needs one half-step move larger than rx + half the wall's thickness, which is
  not reachable by running (rx 44, a few units per step). Low value unless a level shrinks rx (script
  "SetMyWidthHeight").

### K7. Standing up is only partly checked

- Prone → stand tests one sphere (radius 0.75 × `unk_4C`) at +65. Crouch → stand tests one
  at +85 (`sub_104480`, 3313-3344).
- The test reads the lagging visual position, not the physics position.
- `type_93DF0 lD8` in `sub_115230` leaves its `unk_74` filter uninitialised, so the surfaces it
  skips depend on stack garbage.
- **Use:** stand up under thin slabs while crawling forward, so the snap lifts you on top
  (**data/test**).

**Ruled out:**

- Knockback (there is none).
- Falling through floors from speed (capped at −60 per frame).
- Being carried by moving objects.
- A free first landing (the spawn drop uses it up).

---

## T. Triggers, scripts and objectives

How triggers test: one point per frame, a strict point-in-volume test, no sweep
(`sub_D5E20` → `sub_144C80`, `unit_144940.cpp:220`).

- **The point is the eye, not the feet.** It is the player's frame position,
  `unk_434.y = unk_1A00 + unk_420 - unk_524` (`unit_0FD730.cpp:9931`), i.e. feet plus the
  stance eye height. That is 120 standing, 65 crouched, 25 prone (per the PlayerTrigger data).
  The game's own "IsTargetWithinDefendArea" subtracts it to get the feet back
  (`unit_0441B0.cpp:15407`).
  - **Use:** going prone lowers the test point by 95 and crouching by 55, so a trigger whose
    bottom is 25-120 above the floor can be **crawled under**.
- **The point trails the body:** it follows the physics position through a spring, about 62
  units behind at a forward run and 79 on the diagonal (see O1).
- **The use button** sends block 6 of **every** trigger you are in (`sub_145970`).

### T1. How levels end

- **EndLevelTrigger with Action:** once a script has enabled it (`EnableEndLevelTrigger` →
  `EndLevelTrigger::sub_CC2A0`, `unit_0CC090.cpp:96`), pressing Action inside it ends the
  level at once (`unit_0FD730.cpp:3958-3976`: `if (v_9C->unk_C4) … sub_D8CC0(next)`). It
  checks no objectives.
- **Script call:** otherwise a level ends when its script calls `QuitAndLoadNextLevel`
  (`sub_D8CC0`), again with no objective check.
- **Objectives:** `ModifyObjectiveCounter` (`sp_sub_10D160`, `unit_16FF90.cpp:456`) completes
  on `<= 0`, so overshooting completes. Objective flags only drive the HUD and compass;
  nothing in the C++ reads them to gate progress, and only scripts do.

### T2. "Clear the area" means "no enemy position inside the volume"

- `GetNumberOfObjectsInTrigger` (`unit_0441B0.cpp:8924`) counts entities of a list **by
  position only**. Alive or dead does not matter, and it includes entities flagged for
  deletion (unlike `GetNumberOfActiveObjects`).
- L_1_1_B's pillbox objectives poll `GetNumberOfObjectsInTrigger(9, area) <= 0` every 0.5 s,
  and L_1_1 has the same pattern.
- **Use:** enemies that are *outside* the box complete the objective without dying:
  - blown out by an explosion;
  - standing above or below it;
  - not spawned yet when the poll starts.
- **Test:** activate a pillbox before its occupants spawn, or grenade them out of the volume.

### T3. Script position checks use the local frame

- `IsNamedEntityInTrigger` and `GetNumberOfObjectsInTrigger` read the entity frame's **local**
  matrix (`vf_0C4`, `unit_0CC8A0.cpp:465`) as a world position.
- The SP build re-parents an entity's frame to what it stands on (`unit_0929A0.cpp:1128`), and
  `AttachToEntity` also parents.
- So an enemy riding something can drop out of an "area clear" count, and a player-in-trigger
  check can come out false (**data**).

### T4. Wrong enter/leave events after a trigger moves

- `sub_144C80` (`unit_144940.cpp:220-280`) merges the old and new grid-cell lists with the bit
  counters crossed. That is harmless only while both lists start at bit 1.
- Removals leave holes in place (`sub_146A00`, 1221), and doors that move their trigger
  (`SetMyTriggerPosition`; the DoorAnimBGObj2WayClass doors in L_1_1_B and L_3_1) create them.
- After that, crossing a grid-cell boundary can give **spurious enters** of a trigger you are
  not in, missed enters, or spurious leaves. A simulation got 4,841 wrong out of 20,000 cases
  with holes, and 0 without.
- A moved trigger also re-caches every entity from an **uninitialised** stack point
  (`lcl_18`, 740/757).
- **Use:** a remote trigger fire (**test**; the port's trigger overlay can log events).

### T5. Other trigger notes

- **Facing tests:** "facing" and "toward" tests are OR'd, not AND'd (796-806).
- **Proximity re-enable:** `SetTriggerProximityChecks(1)` gives an immediate enter to a player
  already standing inside, so pre-positioning works.
- **Wait wake-ups:** a directed message wakes every task on that object waiting for that kind,
  ignoring filters, and `RegisterTimer` replaces the object's earlier timer of the same kind
  (`unit_06B3B0.cpp:516`, `unit_0441B0` `sub_733D0`). A short timer can therefore cut a long
  wait short on objects that run two timed threads (**data**).
- **Thin triggers:** a point test can be crossed between frames. L_1_1's thinnest
  SectionTriggers are 50 cm, which needs > 15 m/s at 30 fps. Skipping one leaves its section
  unrequested (see K4).

---

## C. Checkpoints, deaths, saves and loading

**Background:**

- **Reboots:** in single player, every level change reboots `default.xbe`
  (`sub_D6EB0`, `unit_0D6640.cpp:650-689`).
- **What a death or restart keeps:** only the checkpoint register `dword_4B8780`, the restart
  count, the starting sections, the default clump bank and the restart animation groups.
- **What is rebuilt:** all 101 script registers, all entities, all trigger scripts and moved
  triggers, and the player.

### C1. An opened level exit stays open after a death or restart

- `EndLevelTrigger::unk_C4` (the enable) is set only by `sub_CC2A0`. `HandleEvents` just
  forwards to `Trigger`, and the restart code re-enables proximity checks but **never clears
  `unk_C4`**. Pressing Action in an enabled exit ends the level (T1).
- **Use:** open the exit, then die or Restart. If the respawn (checkpoint or level start) is
  nearer the exit than where you died, walk straight out without redoing what opened it.
- **Unless:** the level's start script disables the exit again (**data**).
- **Retail data: dead.** EndLevelTriggers exist only in L_2_2, L_2_2_B and L_3_5. Their script
  enables them only on an `EnableEndLevelTriggers` message, and nothing sends a non-zero one.
  So `unk_C4` is never set in retail. (L_2_2_B's exit also has a plain enter block, so walking
  into it ends that level; see C9.)

### C2. Dying gives back full health and the default loadout

- The inventory is never recorded at a checkpoint. After any restart the player trigger's own
  weapons and ammo come back ("Restoring Original Weapons", `sub_AC900`,
  `unit_0A9980.cpp:1054-1100, 1180-1185`), and health is full (`unit_0FD730.cpp:1101-1117`).
  The health that is saved (`sub_111040`) is the level-end carry-over record, not a checkpoint.
- **Use:** dying refills an empty or low loadout. In levels that carry gear over, it throws
  the carried gear away.

### C3. Checkpoints can be set out of order

- `SetCheckPointRegister` (`sub_4B910`, `unit_0441B0.cpp:6285-6294`) stores its argument with
  no ordering or validity check.
- On a death the scripts rebuild state from that value alone, so a checkpoint trigger reached
  early by a sequence break gives everything the scripts tie to it.
- A lower checkpoint reached later overwrites a higher one.
- The pause-menu Restart (`sub_18F190`) always goes back to the level start (it clears the
  register).

### C4. Saving off saves at least 1 s per level transition

- `sub_186140` (`unit_185C30.cpp:480-510`) busy-waits 1000 ms after the save write at every
  level end, unless `dword_4F5A30` (saving disabled) is set.
- **How to set it:** cold boot with fewer than 30 free blocks on the hard disk. The first
  Start shows the "not enough blocks" message, whose first button sets the flag
  (`unit_18AF40.cpp:1533`). The flag survives the reboots, and carry-over still works.
- **Saving:** 1 s plus the write, times about 19 level transitions.
- **Rules question:** whether a nearly full hard disk is allowed.

### C5. A restart is faster when you die near the checkpoint

- `sub_D8660` (`unit_0D7F20.cpp:321-484`) keeps sections that are already loaded and in the
  starting list. It loads each missing one synchronously, up to 4.
- A restart never re-reads `LEVEL.DFF` or `LEVEL.RWS`, and the 2.5 s fade-in does not block
  input.

### C6. Hazard: dying during the 2 s end-of-level fade

- `sub_D8CC0` has already set the next level and bit 0x80. A death (`unit_116310.cpp:1196`) or
  a script `RenderFadeIn` replaces or cancels the fade's callback (`sub_1252E0` guards only one
  case).
- The result is a restart with the **next** level's index: the next level's sections are
  loaded into this level, and the exit can no longer fire.
- **Avoid it.** Gameplay keeps running and the player is not invulnerable during that fade.

### C7. Carry-over between levels

- `unit_0A9980.cpp:495-519` carries gear only within a chapter, from a lower level to a level
  flagged to carry. The pairs:

  | From | To |
  |---|---|
  | 1 | 2, 3 |
  | 4 | 5, 6 |
  | 7 | 8, 9 |
  | 11 | 13 |
  | 14 | 15, 16 |
  | 17 | 18, 19 |
  | 24 | 25, 26 |
  | 27 | 28, 29 |
  | 30 | 31, 32 |
  | 33 | 34, 35 |
  | 36 | 37, 38 |

- **What carries:** 2 weapons, clip plus reserve ammo (reserve capped at the maximum), the 13
  item counts, grenades (the larger of carried and default) and health.
- **What cancels it:** holding weapon 0x20 or no weapon gives the defaults
  (`sub_D9240`, `unit_0D7F20.cpp:800-830`).
- **Replays:** the record updates only when the next level is also your furthest. On a
  profile with more progress, replayed levels get the old record's gear.

### C8. Movies, fades, pause

- **Bink movies:** A or Start on any pad skips from the first frame (`sub_E8BA0`,
  `unit_0E8800.cpp:279-335`). Restarts do not replay the intro.
- **In-engine cutscenes:** none of the 614 script commands is a skip.
- **Fixed fades:** level end 2.0 s, death 2.0 s, quit 1.0 s. All are game time and freeze while
  paused.
- **Pause:** no real-time gain; streaming continues while paused. There is no in-game timer
  (`dword_4B8724` is summed but never shown).

**Ruled out:**

- Mid-level saves (`RequestSaveGame` is an empty function).
- Item duplication across restarts.
- Script registers or trigger states surviving a restart (except C1).
- Extra carry-over through level select or a saved game.

---

### C9. Per-level results from the level data

These come from all 19 levels' scripts, decoded and traced (the tables are in the session
scratchpad, `agent_data/tables`).

**Pause-menu Restart skips intros.**

- **Why it happens:** Restart (`sub_18F190`) clears the checkpoint register but still runs
  `sub_D6A50`, which increments the restart count. Scripts that test
  `GetNumberOfRestarts() > 0` then skip their intro scenes.
- **Levels:** L_1_1 (and both boat sections), L_1_2, L_1_3_A, L_1_5 (10 scenes), L_2_1_B,
  L_2_2 (9 scenes), L_2_2_B, L_3_1, L_3_3, L_3_5, L_3_5_B, L_3_5_C.
- **Use:** start the level, pause, Restart.

**Checkpoints you can walk into, then die to fast-forward (C3).**

- **L_1_2:** trigger B9352FA5 at the ladder, [-7899,-327,-1183], half-size [400,300,150]. It is
  armed from the level's start with no gate, and stores the player's HP. The restart
  auto-completes objectives 1-3 and teleports both buddies. It is about 329 m from the end.
- **L_2_1:** volume 01141BB0 [-11063,974,-1503]. The restart skips the whole Kareem section.
- **L_3_1:** volume B5BA6C96 [5356,-1212,-4320]. It stores the M12 tank's HP, and is about 57 m
  from the manhole end.
- **L_3_1_B:** volume 368507F4 [415,-1567,-18132]. **The restart counts 4 of the 5 charges as
  planted** without checking.
- **L_3_1_C:** volume A9CD5185 [-1711,84,-24183].
- **L_3_5:** volume E5B88D5B, storing the HP of ally 988C0065.
- **L_3_5_B:** volume D641371A, storing the tank's HP.
- **L_1_5_B:** on the tank exit at the control tower. The restart **arms the end at once and
  skips the 9-Junker mech-yard gate**.
- **Watch out:** where the register stores an ally's HP, a dead ally gives 0, and the checkpoint
  doesn't count.

**Level ends worth routing.**

- **L_2_2_B:** walk into its EndLevelTrigger volume [25652,3239,103356]. There is no objective
  gate, and it is about 65 m from the start in a straight line.
- **L_3_5_B:** reach the tank-arena volume 03AC734D [40580,986,-18904], then wait about 5 s. No
  kills are needed.
- **L_3_1_B:** its 5 objectives are polled every 5 s, and **failed counts as done**. Entering
  70B2EAA3 fails "protect buddies", which satisfies that check.
- **L_3_1_C:** the end needs 09CDD096 [-1870,-50,-32099] plus the 2 cathedral panzers. Your
  position at the end doesn't matter.
- **L_1_3_B:** use door B1B6A2E7. No script gates it.
- **L_3_5_C:** sphere 16D52126 [47503,4416,-58447], r421, probably starts the ending once tower
  soldier 151811F8 dies (**test**).
- **L_2_1:** plant C4 at F9515736 and the level ends at once. Its flags are remembered only
  after the end script starts; a comm-post bomb done earlier softlocks the level.
- **L_1_2:** objectives 1→3 must arrive **in order**. An early one is lost, which is a softlock
  risk.

**Positional "clear" gates (T2), confirmed.**

- **L_2_1:** the Guard Post A nests and the Fortress box F3A82556.
- **L_1_1_B:** the pillboxes (side objectives only).
- **L_2_1_B:** entering F7F607ED clears Guard Post D.

**Run-away kills (S6).**

- **What happens:** the handler does `SetHitPoints(-1)` once you are far enough away.
- **Where:** L_2_1 (4 soldiers at 30-50 m), L_3_1 (28 at 50-80 m), L_3_1_C (38 at 25-75 m, some
  of them squadmates).

**Unavoidable waits.**

- **L_1_2_B:** a defend loop of 10 × 60.1 s ≈ 601 s on the critical path.
- **L_3_3:** a fixed ≈120 s timer at the end.

**Corrections to earlier entries.**

- **Speeds:** all 19 levels share one PlayerTrigger: forward 12.87 / 7.02 / 3.9, strafe 10 / 6 /
  3, radius 55, eye 120 / 65 / 25.
- **M1:** the diagonal is **1.27×**.
- **M7:** jump is **12.0** in every level, not the 0.75 default. A real jump exists if a button
  maps to `ePE_JUMP` (**test**).
- **M4:** attribute 115 is never set, so the spline-walk skip is moot.
- **M6:** no level uses TimeScale. PlayerShock is used in L_1_1 (3-6 s "stay in cover"),
  L_1_5 (up to 5 s) and L_1_5_B (3 s per hard tank collision).
- **D3:** L_1_2_B's player scenes 1106/314 set camera mode 1, and nothing in that level sets it
  back. If they play, you may have **no bullet damage for the rest of the level** (**test**).

---

## A. Combat and AI

### A. Tanks

(`AIData` aim code in `unit_0154C0.cpp`, tank in `unit_155470.cpp`.)

- **Turret freezes up close** (`sub_1BAA0`, 2171-2197):
  - Within **400 units** of the main-gun muzzle, the "facing" value is forced to 1, so the
    turret stops turning and fires wherever it points.
  - Between 400 and 800, an `abs()` turns "directly behind" into "aligned", so a target within
    about 10-15° of the rear axis also freezes it.
  - **Use:** walk up from behind or the side and grenade it without dodging.
  - Scripted vehicles (`type_3DE350`, `unit_17E680.cpp:1311-1334`) have the same bug at
    200/400, and fire with no line-of-sight test.
- **Main gun aims at your feet** (`sub_1BEF0`, 2246-2257): the aim point drops to the ground
  under you, and the gun needs a clear line to it. **Waist-high cover in front of you blocks
  it**, and the coaxial MG follows the same barrel into the wall.
- **Hull MG ("RIFC"):** aimed straight at you with no pitch check or line test, within about
  ±30° of the hull's front (2443-2445, `sub_1BD50`). **The sides and rear of the hull are safe
  from it.** Both MGs fire only at targets on foot.
- **Pitch dead zone:** the gun pitch is clamped to +33.8° / −18°, and the main gun fires only
  within about 5° of the target slope. Hugging the tank is safe from the main gun.
  - Bug: the depression limit reads the **player's** vehicle mode (`sub_1745A0(0)`), so while
    the player is in a tank's hatch or chase view, enemy tanks can only depress 7°
    (`unit_155470.cpp:734-744`).
- **Fresh tanks can't fire at first:** the clip starts at 0 and refills only after a full
  reload time (`unit_15B110.cpp:79-139`). Rush tanks as they spawn.
- **No lead or arc compensation:** shells aim at your current position. Strafe at range.

### A. Damage to the player

- **Hit invulnerability needs the shooter on screen:** the bullet-invulnerability timer
  (`unk_19EC`) is set only when the shooter is inside the camera frustum
  (`unit_0FD730.cpp:8316-8349`). **Keep MG nests and tanks on screen while crossing their fire**;
  with your back turned every bullet lands.
- **Every blast you survive gives bullet immunity:** a blast always sets that timer, with no
  frustum check (8534).
- **Blast cover:** within half a shell's radius cover is ignored. Beyond that, the blast needs
  line of sight to your body or head (`unit_0CC8A0.cpp:2841-2910`).
- **No bullet damage while the script camera mode is 1** (8273).
- **Riding in a vehicle:** the riding states clear the player's hit flag each frame (states
  5, 6, 12: `unit_0FD730.cpp:6212, 6341`). A passenger, or a buttoned-up driver, takes **no
  bullet or blast damage**; only the vehicle does. Hatch mode is the exception (`vf_1E4`).
  Vehicles regain `unk_2634` health per step (`unit_14C820.cpp:1551-1556`).
- **Mounted guns give no protection** (state 7 keeps the hit flag), but the player has
  **unlimited ammo** on them: ammo only drops when an AI mounted it (`unk_4F0`,
  `unit_166990.cpp:1130-1139`).
- **MG nests can hurt vehicles:** a player-manned kind-2 gun does a fifth damage to vehicles
  (`unit_14C820.cpp:851-857`).
- **Driving kills on touch:** a soldier you touch while driving dies instantly, enemies and
  allies alike. You need speed ≥ 1, or to be turning in place (`unk_113C`)
  (`unit_134B40.cpp:3580-3680`).

### A. Buddies and escorts

- **No catch-up teleport in the engine:** a buddy who falls behind is never teleported. Every
  teleport is a script command ("TeleportToNamedObject", "SetMyPosition", …). A missing path
  only raises "AStar_PathNotFound" to the script.
- **Arrival is loose:**
  - Path nodes count as reached within 64 units, or on any overshoot within 200
    (`aidatapathing.cpp:893`).
  - Path end counts within the script's radius, with no height check, before intermediate
    nodes. A buddy who cuts a corner skips the rest.
  - A direct goto counts within 125 units, or on **any** overshoot (`unit_0154C0.cpp:1351`).
- **Spline escorts are driven by the player:**
  - "FollowEntityOnSpline_ArrivedAtDestination" fires when the **followed entity (normally
    the player)** reaches the spline's end (`sub_213B0`, 3941). The buddy's own position
    doesn't matter.
  - The leash is ignored when the player is 200 or more units above or below the spline.
  - The anchor only moves forward.
- **Body-blocking:** the player is never stored as a blocking entity
  (`sub_309E0`, `aidatapathing.cpp:2576`), so the AI's own stall timer never runs on you.
  Standing in front of a buddy sends him "BlockingEntity"; what he does then is up to the
  script.
- **"Go go go"** (Action on a friendly within 300, `sub_1048E0`): it pulls the group up to
  5 path nodes or ~500 units toward where you look. It works only where the script set AI flag
  26 and the buddy has no order.
- **Vehicles following you** (`sub_1A630`): they keep full throttle only while you are more
  than 1.2 × their follow distance ahead. Get closer and they brake.

### A. Numbers from the levels' data

These were read from the disc's attribute packets; all 19 retail levels share them.

- **Player:** full health 1000; bullet invulnerability 10 frames; forward block when hit
  20 frames; fall damage from 3 m, lethal from 10 m.
- **Difficulty** (easy / normal / hard, from `global.dff`, commands 194-205,
  `unit_0B07D0.cpp:2052-2160`):

  | What | Easy | Normal | Hard |
  |---|---|---|---|
  | Bullet damage to you | 0.75 | 1 | 1.25 |
  | Blast damage to you | 0.8 | 1 | 1.25 |
  | Your damage | 1.25 | 1 | 0.8 |
  | Enemy spread | 1.15 | 1 | 0.8 |
  | Enemy grenade chance | 0.9 | 1 | 1.25 |
  | Medkit and health pickups | 1.5 | 1 | 0.8 |

### A. Damage and survival

- **Facing the shooters caps bullet damage.** Combined with the on-screen invulnerability
  rule above, facing them limits you to one hit per 10 frames (6 per second). Off-screen
  shooters' hits stack.
  - But on-screen hits also block forward movement for 20 frames, so under steady fire
    straight forward never moves; **diagonal or strafe movement does** (M5).
- **Flat bullet damage:** `damage × difficulty / 1000` per bullet, with no distance falloff
  and no hit-location factor (`unit_0FD730.cpp:8276`).
- **Total invulnerability:** with "DisablePlayerDamage" (`unk_19FC`), or while a script holds
  the camera in mode 1 (head-bone camera, "SetCameraMode"). **Data:** which scripts do that
  while leaving the player in control.
- **Stance shrinks blast radii:** crouched you only take damage inside `unk_08`, prone only
  inside `unk_0C` (`vf_068`, 8380-8547). The hit volume's half-height is 75 standing, 45
  crouched, 25 prone.
- **Close blasts cost time:** a blast within half its radius slows the game to 0.2× for 60
  game frames (`sub_D98D0(0.2f, 60)`), about **4-5 s of real time lost**, and each new blast
  restarts it. Avoid getting caught near grenades on time-critical stretches.
- **Fall damage:** `(h − 300) / 700` of full health, the same on every difficulty, and **not
  stopped by DisablePlayerDamage or camera mode 1**. A 6.5 m fall costs half your health.
- **Final level only:** once QuitLevel's 1 s fade starts (bit 0x40, `sub_D8C20`), you can't
  die (`unit_0FD730.cpp:2468`). The normal next-level path (`sub_D8CC0`, bit 0x80) has no such
  guard (see C6).
- **Healing:** a medkit gives 50% × the difficulty factor (`unit_1154A0.cpp:159-190`). You
  carry 6 / 4 / 2 of them. There is no regeneration and no respawn invulnerability.

### A. Enemy perception and fire

- **Vision:** a cone, a range and a line-of-sight test. **Stance, noise and speed don't change
  whether you are seen**; stance only moves the point they look at (`unit_040720.cpp`).
- **Vision is rationed:** at most 3 looks at tracked targets and 1 soldier's full scan per
  frame, and targets beyond 20 m are checked every other look (`sub_408F0`, 204-213). With 15
  soldiers, first notice takes **15-30 frames**.
- **Hearing:** soldiers hear only while idle-ish (AI action 0, 4 or 0x1A,
  `unit_0154C0.cpp:665`), so engaged soldiers are deaf.
- **Aim:** no lead, and a fixed spread angle that ignores your speed, stance, range and cover
  (`unit_15CCE0.cpp:674-804`). Bullets are projectiles. **Strafing at range beats riflemen.**
  - Recoil lifts their aim up to 75 units over a burst, so long MG bursts tend to pass over a
    prone player.
- **Grenades:** thrown only at **700-3000 units**, with a 120-frame cooldown
  (`unit_134B40.cpp:1005-1107`). **Staying within about 650 units of a thrower turns them
  off.**
- **Losing them:**
  - Break line of sight and move more than 300 units: they keep attacking your last-seen
    spot only within 300 (`unit_0154C0.cpp:1243`).
  - Targets are dropped after 45 s unseen (`unit_012000.cpp:1234`).
  - One squad member spotting you alerts the squad.
- **Vehicle seats:** in a seat that isn't the driving posture, soldiers can't target you at all
  (`include/sp/sp_target.h:20-31`).

### A. Spawning and kill gates

- **Background:**
  - The SP soldier pool is 15 slots; animation pool 2 holds 16 objects, shared with the
    player.
  - A failed spawn is silent and never retried.
  - Death is a flag (`unk_28` 0x200) that the scripts set: damage only sends "HitByBullet".
- **S1. Priority spawns into a corpse's slot vanish.**
  - The mechanism:
    1. Eviction (`sub_D56D0`, `unit_0D5170.cpp:460-492`) picks a queued corpse.
    2. `sub_D5AD0` (536-554) deletes it **without unlinking it** from the deletion queue
       `dword_4B8204`.
    3. The free list is last-in first-out, so the new soldier is built in the same memory, and
       its constructor zeroes the queue's next pointer.
    4. On the next queue walk the new soldier is deleted, and every corpse behind it is
       orphaned. Orphaned corpses hold their slots for the rest of the level, even across
       restarts.
  - **Effect:** a reinforcement can disappear without ever sending a death message. That can
    remove a wave, or softlock a gate waiting on death messages.
  - **Conditions:** a full pool, a corpse still in its deletion delay, and a priority
    trigger.
  - **Test:** watch the queue and pool 6's free count over the port's live link.
- **S2. Eviction ("sacrificial lambs"):** silently deletes the farthest expendable enemy of
  the same trigger kind, with no death message (`sub_D56D0`, 427-493). Gates that count active
  entities clear; gates that count kill messages may hang.
- **S3. Corpses on screen hold back spawns:** a corpse in view lives up to 240 extra frames
  (`sub_D5D20`, 652-657). When animation pool 2 is full, non-priority spawns fail, so **looking
  at corpses can delay waves, and looking away lets them in**.
- **S4. Gimp special spawns unbalance two CCESS slots:** each one leaves slot 2 one higher for
  good and pushes slot 0 one lower (`sub_8B4C0` against `sub_8B6B0`, `unit_08AB60.cpp:560-648`).
  Gimp waves dry up early while slot 0 over-spawns.
- **S5. CCESS caps count corpses until deleted,** and the respawn delay restarts before the
  cap check (`sub_8AEB0`, 285-298). Time your kills against the wave timer.
- **S6. "HitByBulletAssassination":** enemies whose trigger has bit 20 get this event once the
  player is farther than `unk_54` (default 0, so on the first 64-frame check) (`sub_D5E20`,
  708-725). If the scripts treat it as a death, **running past them counts as killing them**
  (**data**).

### A. Weapons

- **W1. The item button cancels a reload** (`unit_0FD730.cpp:3108-3123`: `unk_13 = 1; unk_12 = 0;`
  runs before the inventory check).
  - After the "ammo in" animation event, the clip is already full and you can fire at once.
  - Before it, you get no ammo.
  - It is free with no grenade selected, or with a medkit at full health.
  - Probably 0.2-1 s per reload. **Test first.**
- **W2. Scoped bolt rifles (13, 17, 18) skip the fire-animation gate while fully zoomed**
  (`unit_116310.cpp:881-897`), so only the fire timer limits them.
- **W3. A melee during a draw or holster ends the switch early** (`unit_0FD730.cpp:2946-2950`).
  It only helps if the melee is shorter than the switch.
- **W4. A gun picked up into an empty second slot *sets* your current gun's clip**
  (`unit_0FD730.cpp:5060-5072`).
  - The current gun's clip becomes min(pickup amount, its magazine).
  - The new gun keeps its own full magazine, and the rest goes into its reserve **past its
    maximum** (`unk_418 += v_144`, no cap).
  - L_1_1 example: the MP40 pickup (324 rounds) taken while holding the Mosin gives MP40 32 +
    **319 reserve** (cap 160). See P4.
- **Pitfalls:**
  - An automatic ammo pickup during a reload restarts the reload from empty
    (`unit_1154A0.cpp:510-513`).
  - Reloading while holstering can leave the new gun locked until another animation ends.
- **Not frame-dependent:** fire rate runs on game time, there is no grenade cooking, and melee
  damage is flat.

**Ruled out:**

- Hit-location or distance factors on damage to the player.
- Regeneration.
- The god flag `byte_4F28F8`: it is only ever cleared.
- Enemies leading their shots.
- Ammo or grenade duplication.
- Double kill messages.

### A. A level whose data doesn't match the code (L_3_4)

L_3_4's PlayerTrigger packet is one attribute short from command 11 on, so every later value
lands in the wrong field: player height 15, fall damage safe to 10 m and lethal above it. Its
shell packet stops early, so every difficulty factor stays 1.0. It is the cut level that will
not load properly (no GodData), so it is not run material.

---

## V. Driving (player vehicles)

Physics is in `unit_147080.cpp` unless noted. Speeds are cm per 60 Hz tick (×0.6 = m/s), and
dt is capped at 3 inside the vehicle step (477). The per-vehicle values were read from every
level's VehicleTrigger data.

### V1. Below speed 2 the vehicle ignores world walls

- **Code:** the hull-sphere wall test is the vehicle's only world-wall test, and it runs only
  above speed 2 (1115):

  ```
  if ((unk_2A0 || arg_0->unk_28_23) && frm_24 > 2.0f && !unk_108)
  ```

  `frm_24` is horizontal speed + spin × 0.318.
- **Wheel probe:** it casts from 100 above each wheel to 300 below, takes any surface it crosses
  as ground, and lifts that wheel up to 55·dt per step (1273-1284).
- **Effect:** at speed ≤ 2 (no steering) the vehicle **drives through any wall** if the floor
  continues behind it, and climbs ledges up to about 1 m. Props and other vehicles still
  collide.
  - Speeding up once a hull sphere's centre is past the wall's face pushes it the rest of the
    way through.
- **Holding speed under 2:** the stick dead zone is 0.32 and not rescaled
  (`unit_19D920.cpp:73`).
  - **L_1_3_A / L_1_3_B** (the mode-3 tank): about 1.58 at the minimum stick on NTSC, so it
    works with the stick held at 0.32-0.33.
  - **Other vehicles** sit above 2 at the minimum stick: tap the throttle (one frame on,
    several off) or creep uphill.
  - **PAL:** nothing works with a held stick.
- **Confidence:** code + data + test. **Test:** a speed readout plus a slow creep into a tall
  wall in L_1_3_A on NTSC.

### V2. Over ground with no collision the vehicle hovers, with no gravity and no speed cap

- **Code:** `sub_14C520` (1915-1935) probes the ground at the front and rear centres. If either
  finds nothing, `unk_27C = 1` and the vertical speed is zeroed (500).
  - AI vehicles, and vehicles you only ride in, then freeze: `if (unk_27C && !unk_2A0) return;`.
  - When you drive, throttle still applies (523) and gravity is skipped (596).
  - With no wheel touching there is no drag, no friction and **no top-speed cap**
    (601, 683).
- **Effect:**
  - With one end over a hole, the vehicle bridges it at a constant height.
  - With both ends over nothing, it gains F/m per tick² with no limit (about +40 cm/tick per
    second for L_1_3_A). That is enough to push through walls in one step.
  - Surfaces flagged 0x40000 count as nothing for the player's vehicle (1323).
- **Conditions:** a collision hole, or a section not loaded under the vehicle (K4).

### V3. Speeds and turning

- **Top speed:** set by force/mass, (F/m − 0.2)/0.03, capped at mph × 0.7493 and only while on
  the ground.

  | Vehicle | Top speed (cm/tick) | Limited by |
  |---|---|---|
  | L_1_3_A / L_1_3_B mode-3 tank | 15.6 (9.3 m/s) | force/mass |
  | L_2_1_B jeep | 16.7 | force/mass |
  | L_1_3_B mode-2 tank | 10.5 | mph cap |
  | L_1_5, L_1_5_B, L_3_3 tanks | 11.2 | mph cap |

- **Reverse** is exactly as fast as forward.
- **Slopes:** gravity along the slope is ±0.55·sinθ per tick. L_1_3_A drops to 11.9 at 10°
  uphill and stalls at about 25°.
- **Frame rate:** NTSC and PAL speeds are the same. Below 20 fps the dt cap slows vehicles in
  real time.
- **Tanks turn at a fixed rate** that doesn't depend on speed: L_1_3_A 34.7°/s, L_1_5 38°/s,
  L_3_3 52°/s. So **pivoting in place costs nothing extra**. The player gets 0.52 turn torque
  where AI gets 0.7 (`dword_429D04`).
- **Jeeps** turn with speed (torque × min(|v|, 15)), and not at all when stopped. Sideways grip
  is 0.7 per tick², so the turn radius is v²/0.7.
- **No diagonal-style stacking:** throttle and steering are separate inputs.

### V4. Tank gun, damage, misc.

- **The player's tank gun has no reload check:** `vf_2A8(0, 0, 1)` skips `vf_2A4`
  (`unit_116310.cpp:2212`, `unit_155470.cpp:1264`). Only the weapon interval limits it: **one
  shot per 2.68 s** (weapon 29/35 command 5). Damage 150 (300 in L_3_3), blast 250, radius
  likely 700.
- **Vehicle damage:**
  - Bullets hurt only for kinds 3, 4 and 6.
  - Explosions skip the per-side armour multipliers and have no falloff or cover.
  - Health regenerates **per frame** (1.0 for most player tanks; NTSC regenerates 20% faster
    per second than PAL).
  - There is no fall damage for vehicles.
- **Explosions and recoil never push your vehicle:** they move only a cosmetic follower body
  (`unit_14C820.cpp:1006`, `unit_155470.cpp:1483`).
- **Corner tunnelling:** wall pushes are averaged per triangle, so in a simulation a hull can
  push into corners. Only the fast L_3_4 tank did it, which isn't run material.
- **Scripted spline vehicles can't be sped up:** there is no input path into them
  (`unit_17E680.cpp:642-800`).

---

## O. Frame order and timing

### O0. One frame, in order

`sub_D7880` (`unit_0D6640.cpp:1048-1149`) runs these steps:

1. Frame time.
2. Pad poll. A press is an edge between two polls, and nothing is buffered.
3. Pause menu.
4. Pause toggle.
5. HUD.
6. RWS tick.
7. **Script timers, then the script queue.** Scripts run here, before anything moves.
8. CCESS spawns.
9. **Entity lists 0-15 in order.** Vehicles, objects, pickups, soldiers, gimps and mounted guns
   come first; the **player is list 14** and the camera list 15. Each entity runs, in turn:
   input, move, collide + spring, Action/mount checks, trigger test.
10. Projectiles.
11. Pulse zones.
12. AI schedulers.
13. Objectives.
14. Fades.
15. Render.

**Consequences:**

- Enemies and scripts always use the player's position from the previous frame.
- Trigger events reach scripts the frame after they happen.
- The Action/exit check uses the previous frame's trigger membership.

### O1. The trailing trigger point

The test point springs after the body (k 0.075, damping 0.6, at most 50 per step).

| | Steady lag | Settles after stopping |
|---|---|---|
| 60 Hz, forward / diagonal | 62 / 79 u (about 10 frames) | 26 frames |
| 30 fps, forward / diagonal | 56 / 71 u | |
| Crouched / prone (60 Hz) | 34 / 19 u | |

- **It never ends up inside walls:** the corner cut-in is at most about 21 u, under rx 44.
- **Poke:** run into a volume and reverse at once (there is no momentum). The body gets about
  35-44 u in, but the test point never enters, so **no enter or leave events fire**.
  - Use: scraping kill zones and ConfinedArea edges.
- **Leaving is late:** an area notices you leaving about 0.15 s and 60-80 u late.

### O2. Falls

- **Terminal speed:** 60 u per frame, so 3600 u/s at 60 Hz and 1800 at 30 fps. Acceleration is
  the same at every frame rate.
- **Long drops are faster at 60 Hz:** a 2000 u drop takes 0.95 s at 60 Hz and 1.30 s at 30 fps.
- **The trigger and camera point lags a lot on landing:** about 300 u behind after a 6.5 m fall.
  Control comes back when the body lands, so **move straight away rather than waiting for the
  camera to settle**.
- **Thin triggers can be skipped while falling:** horizontal triggers thinner than about 25 u
  (60 Hz) or 50 u (30 fps).

### O3. A ladder grab snaps the body back to the trailing point

The climb starts from the frame position (`sub_114AA0` → `vf_0C0`, `unit_0FD730.cpp:9957,
10085`).

- **On foot:** grabbing a ladder while running pulls the body back 60-80 u.
- **While falling:** the grab happens when the *lagging* point enters the ladder volume, and the
  body is teleported up to it. That makes the M3 fall-cancel more forgiving, but fall damage is
  still taken if the body touched ground first.

### O4. Action stops working after you leave an open exit

- **Code:**
  - The exit's Action slot 0 is set only at `unit_0FD730.cpp:3965`.
  - It is cleared only at 3982, and only while you are inside some *other* trigger.
  - The game has only those two writers, plus the player's own initialisation.
- **Effect:** after you walk out of an open exit without pressing Action, every Action press
  returns slot 0 until you stand in another trigger. That means **no mounting, no vehicles, no
  weapon pickups and no action items**.
- **Avoid it:** don't cut through an open exit (C1) before a gun or vehicle.

### O5. Script waits and the VM

- **No instruction budget:** a task runs until it blocks (`unit_067B10.cpp:429`).
- **Waits run on game time:** "RegisterTimer" counts ticks from the clock at registration, so
  each wait overshoots by about half a frame. Waits follow slow-mo, freeze in pause, and fall
  behind real time below 12 fps. PAL and NTSC take the same real time.
- **Full pools crash rather than drop:** messages 1000, actions 1000, timers 200.

### O6. Pause and input

- **Resume with A:** SP unpauses on the same frame the menu accepts, and gameplay then reads the
  same pad poll (`unit_0D6640.cpp:1207-1231`). With controller sets 2 and 3 (A = Action),
  resuming with A also gives an Action press on the first frame.
- **Lost presses:** presses during pause, the about 4 frames after a restart, and synchronous
  loads are lost.

### O7. Slow-mo is replaced, not stacked; it also stretches fades

- **Replaced:** blasts and PlayerShock overwrite the remaining slow-mo time
  (`sub_D98D0`, `unit_0D95A0.cpp:189-209`). A blast during long scripted slow-mo **shortens**
  it, to about 5 s real.
- **Fades stretch:** fades run on game time, so a close blast during the 2 s exit or death fade
  makes it **about 6 s**.

### O8. Pulse zones: fast death warps and mines

- **Pulse timing:**
  - Zones pulse at their interval plus up to a frame, and the countdown restarts at each pulse
    (`unit_17D590.cpp:128-143`).
  - So damage zones hurt about 15-20% less per second at 30 fps.
  - The phase is global, so walking in just after a pulse gives a whole interval free.
- **Kind 2 "hold" zones kill on ground contact:** `if (m_6C && unk_520) vf_178(0)`
  (`unit_0FD730.cpp:9628`). That ignores DisablePlayerDamage.
  - **L_1_1_B has six**, 0.1 s interval, players only. Examples: centre (−20141, 820, 2903) box
    6000×1700×3122; (−31084, 548, −1305) 9002×3002×3122; (−26252, 1425, 1506) 8000×1700×3122.
  - Death comes about 0.1 s after the test point enters, which makes these a **near-instant death
    warp** for C1/C2 where one borders the route.
- **L_1_5_B:** a 2000-damage zone hitting everyone every 0.1 s, at (57589, 4824, −47270), box
  400×1000×5600.
- **Kind 1 mines:**
  - They arm when something is inside at a pulse, and go off after 3 s **only if something is
    still inside**. Keep moving.
  - L_3_5_C's big one (3200×2400×2400, anyone, every 0.75 s) also gives 4 s of slow-mo to a
    player within 15 m.

### O9. Triggers keep firing after you die

The dead state (`sub_10B790`, `unit_0FD730.cpp:6404-6446`) leaves the trigger-test flag on.
Gravity, collision and the spring keep running through the death animation and the fade.

- **Effect:** the body slides another 60-80 u after a running death, and keeps falling after a
  fall death. Checkpoint and section triggers there still fire.
- **Use:** dying just short of a checkpoint trigger may still count for the respawn (C3), if
  its script doesn't check you are alive.

### O10. Other timing notes

- **Pause-menu Restart during the exit fade** keeps the next level's index and bit 0x80, the
  same broken state as C6. Avoid it.
- **Enemy vision checks are budgeted per frame,** so at 30 fps enemies take about twice as long
  to notice you (`unit_071EC0.cpp:302-345`).
- **"HitByBulletAssassination"** checks every 64 frames: about 1 s at 60 Hz, 2.1 s at 30 fps.

---

## D. Doors, destructibles and surfaces

### D1. Doors are solid at every pose, and can't be used to clip

- **Live collision:** door collision is a separate clump that follows the animation bones
  every frame (`unit_0CC8A0.cpp:2323`, `unit_16D8C0.cpp:400`), and the door scripts never
  switch it off.
- **No clipping:** pushes resolve against world triangles last, and the line test catches wall
  crossings, so a door can't push you through a wall. It only flips you to its other side when
  it pins you against the wall it swings to.
- **Wrong-side opening:** you can open a door from up to about 150 units away, through its wall
  plane, with no line of sight.
  - Facing tests are OR'd (T5), so with a "facing" plus "toward" pair (L_1_1_B), you can open it
    **with your back to it** from the side the trigger's axis points away from.
  - Test: L_1_1_B door 9F1E7BC3 at (−11421.7, 1936.2, 300.3), standing on the −x side facing
    −x.
- **Presses during a swing are ignored,** so there is no double-trigger.

### D2. Animated geometry that does turn its collision off

- **L_1_3_A's one-shot door** (1A5DE243): about 1/6 s after its opening animation, the script's
  `SetCollision(0)` makes the panel **permanently non-solid**.
- **`I03K1A_WALLCOLLAPSE`** (L_1_3 animation packs): animation event 1600 turns the object's
  collision **off 0.70 s** into a 3.53 s collapse. **Walk through at 0.7 s.**
- **Soldier door kicks** (event 1500, `F06A1A_KICKDOOR`) hit the nearest door within 300 units.
  Kicking an open door confuses its state: drawn open, scripted as closed.

### D3. Explosions reach destructibles through walls

- **Reach:** the blast search (`sub_9A960`/`sub_9A860`, `unit_0929A0.cpp:3374-3472`) tests
  bounding spheres only, never triangles.
- **No cover:** destructibles skip the cover test (`vf_070` with `arg_4 = 0`,
  `unit_0CC8A0.cpp:2857`).
- **No falloff:** damage is flat (`unit_09B700.cpp:269`).
- **So** a grenade damages an object **through walls**, out to its radius plus the object's
  whole bounding sphere.
- **Scripted and particle explosions ignore cover for everyone, including you.**
  "CreateExplosionZone" passes no source object, so `vf_070` returns 1 at once. Barrel scripts
  use radius 1000 with 200 damage (L_1_5, L_2_2) or 300 with 200 (L_3_5_B). A barrel kills
  soldiers behind cover within 10 m.

### D4. Destructibles that open things

- **Walk-through rubble:** with "remain hittable" 0, a destroyed object loses all collision
  (`unit_09B700.cpp:218-219`), so its destroyed mesh is walk- and shoot-through.
  - **L_1_5:** seven explosion-only objects, HP 50-100.
  - **L_1_5_B:** one has **HP 1 and takes any bullet**, at (19462, −80, −41391).
  - **L_1_3_A:** six with HP 10.
  - **L_3_1:** several more.
  - Which of these block a route is still to test.
- **L_2_2 MG nest:** five barrel-type objects share one hard-wired script. Shooting **any one**
  of them blows up, assassinates the gunner at (8203, −3845, 62052), and permanently destroys the
  MG trigger. Four of the five are about 30 m from the nest (≈ 28.4k-30.7k, 2.07k, 84.5k-85.2k).
  **One bullet clears the nest from far away** (copy-paste bug).
- **L_1_5 barrels** go off on *any* explosion hit, whatever their health, so they can chain.
- **L_1_1 sapper rubble** at (−3900, 2103, −4971) has HP 10 and is explosion-only. A player
  grenade destroys it before the sapper scene, but the buddies still wait for the scene's
  "WallRubbleDestroyed". Whether you can go through ahead of them depends on the destroyed mesh,
  which still collides here.
- **L_3_1 "Bldg1_Wall"** at (4347, −219, 7036), HP 100: once its GameEvent fires, a grenade
  of 100 or more completes it with no line of sight needed, instead of the scripted shot.

### D5. Collision surfaces from the levels' data

The masks: the player's body and probes skip 0x10000; mount, pickup and use sight lines skip
0x410000; bullets and grenades 0x180000; AI sight 0x420000; the player's vehicle 0x40000.

- **Walk-through-looking-solid (0x4FFFFF):**
  - `glass` (L_3_5, L_3_5_B)
  - `window_03`, `window_05`, the cathedral clockface and crosses (L_3_1_C)
  - `3_5_windowframe_01`
  - `acable` (L_3_1_B)
  - graffiti and bullet-hole decals
  - Where glass is the only thing in a reachable window, **walk through it**.
- **Blocks bullets, not you:**
  - `wood_pallet` (L_1_5_B)
  - `bulletonly_col` (L_3_5, L_3_5_B)
  - `step_bulletonly` (L_2_1, L_2_1_B)
  - `coll_brickart`, `coll_stairsart` (L_3_1, L_3_1_B, L_3_1_C)
  - `__nochars` (L_1_3_A, L_1_3_B)
  - These are a free bullet shield you can stand inside. AI usually sees through them.
- **Blocks AI, not you:**
  - `slope_collision` (L_1_1)
  - `soldier_only` (L_1_1_B)
  - `npconly` (L_1_2, L_1_2_B)
  - `soldier_collision` (L_2_1, L_2_1_B)
  - `coll_enemy_nopass` (L_3_1, L_3_1_C)
  - These give paths enemies can't follow (they break leashes), and are a hazard for escorts.
- **Mount and pickup sight lines see through 0x400000:**
  - player-only invisible walls (`playeronly_col` and friends)
  - shoot-through meshes
  - window frames
  - `metal_grate_catwalk` (L_1_5)
  - fences
  - **Use:** mount a gun across a grate or player-only wall and dismount inside (K3, +120 up),
    or grab health through bars.
- **Driving goes through some player-only walls:** `playeronly_col`, `shoot_throug_col`
  0x4E/0xCE, `vehicleoff`, bushes.

---

## P. Pickups and inventory

### P1. Collection rules

- **Health:** health packs and stored medkits (75-77) are taken on contact, from any angle, if
  the sight line is clear.
- **Everything else:** must also be **in front of the camera** (the nearest to screen centre
  wins) (`unit_0FD730.cpp:7579-7634`). **Turn toward ammo boxes**; walking backwards over them
  takes nothing.
- **Through walls:** the sight line skips 0x10000 and 0x400000 surfaces, so you can collect
  through shoot-through meshes, and possibly through a thin floor within about 15 units.
- **Buttons:**
  - Weapons you don't carry, and teddy bears, need Action.
  - **Holding Action as you run onto a weapon** takes it on contact.
  - Action goes to the lowest slot first. The order is exit, vehicle, mounted gun, use icon,
    bear, weapon, so you can't take a weapon next to a mounted gun or inside a use-icon trigger.
- **Streaming:** the first touch of a weapon whose bank isn't loaded only starts the stream.

### P2. Respawning pickups

- **Rule:** a pickup respawns after its delay, counted in game time, only if you are within 50 m
  when the timer ends. Otherwise the timer restarts from 0 (`unit_0A93B0.cpp:139-193`).
- **These respawn forever in single player:**

  | Level | Pickup | Respawn | Notes |
  |---|---|---|---|
  | **L_3_1_C** | Panzerschreck ammo ×10 | **1 s** | at (−6608, 789, −38290): effectively unlimited rockets |
  | L_3_3 | Panzerschreck ammo ×6 (three spots) | 5 s | |
  | L_2_1_B | Teller mines ×3 (three spots) | 5 s | |
  | L_1_2_B | stored medkits | 20 s and 30 s | at (−21320, 848, 34147) and (−22723, 1110, 29919) |
  | L_1_2_B | DP ammo ×500 | 30 s | |
  | L_3_5 / L_3_5_B | Panzerschreck (the weapon) | 45 s / 60 s | |

### P3. Medkits are instant

- **The heal:** it lands on the press frame, with no animation (`unit_1154A0.cpp:159-194`).
- **When it works:** the Health button isn't blocked by aiming, reloading or switching, and it
  doesn't cancel a reload.
- **Hazard:** an ally in view within 325 units and under 40% health takes the press, and your
  medkit (`unit_0FD730.cpp:3073-3105`).
- **Carry-over:** medkits carried over aren't capped by the new difficulty.

### P4. Ammo tricks

- **Over-max reserve:** the empty-slot pickup gives a reserve past the maximum (W4).
- **Hidden reserve:** swapping a gun away keeps its reserve on the weapon object, and ammo
  pickups for a gun you don't carry still fill that reserve (`unit_1154A0.cpp:496-504`). Taking
  the gun later gives it all back.
- **Swap mid-reload:** the dropped gun's reload flag stays set, so it comes back with its clip
  filled at the end of its draw animation, with no reload played (`unit_116310.cpp:1712-1769`).
- **Per-round reloads:** rounds already loaded are kept when you cancel with W1.
- **Weapon pickups:** they give the raw amount, without the difficulty factor that ammo boxes
  get.

### P5. Planting and use are instant in single player

- **No plant state:** SP has no plant or defuse state (`unit_0FD730.cpp:2583-2590`). Every use
  is a message sent on the Action press frame; any delay after it is the level script's.
- **One press fires everything you are inside:** it sends every trigger's use block, even while
  driving (6244), and that same press can also exit the vehicle.
- **L_1_1 rifle objective:** the "pick up the rifle" script listens for "PickedUpWeapon", which
  any weapon taken while unarmed sends. Taking the placed Mosin at (−1035, 1955, −4786) or the
  MP40 at (−2684, 2021, −3872) **may skip the BDR run and the rifle wait**.
  - Related latent bug: that pickup path writes through `unk_1A48[-1]`, so the rifle's reserve
    then depends on leftover memory.

---

## R. Randomness

- **One shared generator:** almost everything, gameplay and cosmetic, uses RenderWare's
  `RpRandom`, seeded with a constant `0x9a319039` (`src/rw/plugin/random/rprandom.c:184`).
  Sounds, animation picks and muzzle effects use the C `rand()`, never seeded in SP.
- **Reset every level:** each level change reboots the game, so both generators restart at each
  level.
- **Not reset by deaths and restarts:** a death or checkpoint restart re-seeds nothing.
- **No input-sequence manipulation:**
  - Frame time comes from the real-time clock.
  - Particles draw 9-13 numbers each, at a frame-rate-dependent count.
  - Every bullet anyone fires draws 2, and camera shake draws 4 per frame.
  - So results drift within a few frames even with identical inputs.
- **Re-rolling works:** a death or checkpoint restart gives fresh rolls for random script waits
  (L_1_1 alone has 169 random-range calls, e.g. 6-15 s waits), CCESS delays, cover choices and
  grenade rolls.
- **Possible repeats:** values drawn during loading, before the first real frame (soldier sizes,
  a level's opening timers), may repeat on every fresh level start (**test**).
- **Grenades, from the code:**
  - **Throw chance:** `RpRandom()%10000+1 > base × difficulty × l20` means no throw.
    - `l20` is 1.3 with one of the thrower's allies within 700 of you, 2.0 with more, and 0.6
      lower if a member of any other side is there.
  - **Aim:** grenades land **50-110% of the way to your last-seen spot, mostly short**.
  - **Use:** keep moving, and stay within 700 of the thrower (A).
- **Projectile generators** (artillery, scripted MG fire) roll a hit chance per shot
  (`unit_11DB10.cpp:228`), and ambient blast triggers pick random positions inside their volume.

---

## H. Crash and softlock hazards a route must avoid

These are memory-safety bugs that the retail levels don't reach in normal play, but that a
sequence break might. None gives a useful corruption; they only crash or hang.

- **CCESS tracker pool (100):** `ToggleCCESSPoolCreation(1)` takes a tracker with no NULL check
  (`unit_08AB60.cpp:408-413`). L_1_1 has 237 pool triggers, L_3_5_B 167 and L_3_1 148. Scripts
  add and remove them by area, so **a route that skips the "remove" senders but reaches later
  "add" senders can exceed 100 and crash.**
- **More than 32 triggers in one grid cell** overflows a stack buffer and trips the /GS
  cookie, which ends the game (`unit_144940.cpp:1121`). The busiest cell is 31 (L_3_5_C, cell
  29,25), so two triggers moved into it would crash.
- **Section bank exhaustion:** NULL dereference when no bank is free (`unit_141BB0.cpp:259`; K4).
- **Dropped weapons evict other small entities:** pool 0 has 25 slots, and once it is full, each
  dropped weapon (swaps, soldier deaths) silently deletes the farthest pool-0 entity
  (`unit_0D5170.cpp:384-390`). That may include level pickups (**test**).
- **S1 is more common than it looks:** eviction *prefers* corpses already queued for deletion
  (+10000 score), so every priority spawn into a full pool with a fresh corpse around corrupts
  the deletion queue.
- **Unreachable with the retail data:**
  - the AddObjective overflow (the most objectives is 14, in L_3_3);
  - the objective handlers' entry-15 read;
  - the trigger handle table (at most 1033);
  - the subtitle buffer.

---

## X. Cheats, unlocks and the debug menu (for category rules)

### X1. Cheats and unlocks (category rules)

- **Seven cheats, one at a time:** each cheats-screen "On" button sets a single bit and the
  "Off" button clears all (`sp_fend.cpp:1127-1210`). The flags are saved with the profile.

  | Bit | Name | What the code does |
  |---|---|---|
  | 0 | BigHeads | soldiers' heads scaled ×2 (`unit_134B40.cpp:1540`), a bigger headshot target |
  | 1 | RicochetPlayer | the player's bullets bounce up to twice (`unit_15F1B0.cpp:648-656`) |
  | 2 | HeadShotKills | headshots do 1000 damage, other hits 0 (`unit_134B40.cpp:3362`) |
  | 3 | RicochetAll | every shooter's bullets bounce |
  | 4 | ShrinkingSoldiers | soldier scale = hp/max·0.67 + 0.33 |
  | 5 | OneShotKills | every non-friendly bullet does 1000 damage, **so enemies one-shot your escorts too** |
  | 6 | BigNSmall | random soldier scale 0.3-1.2 |

- **Who they affect:** all of them act on soldiers only, never on the player's damage. Using
  them blocks no saves or progress.
- **How cheats unlock:** finishing level 38 (`sub_D8C60`, `unit_0D7F20.cpp:553-586`); only
  that level's difficulty counts.

  | Difficulty when finishing level 38 | Cheats unlocked |
  |---|---|
  | 0 | 1-4 |
  | 1 | 1-6 |
  | 2 | all 7 |

  So **playing level 38 alone, from level select, on the hardest difficulty unlocks all
  seven**.
- **Other unlocks:** level 12 sets extras bit 0x1000 and level 18 sets 0x2000.
- **The "all cheats" and making-of codes can never be entered:** they need inputs 19-22
  (d-pad directions), which the code recorder never stores (`sp_fendbase.cpp:587-645`,
  `default: continue;`).

### X2. Unlock every level for one visit

- **Code:** `checkUnlockSPLvlsMBS` (`sp_fend.cpp:1596-1606`). At level select, the last four
  presses must be {11, 17, 17, 25}, i.e. **Start, Back, Back, X**. The hold check
  (`sp_sub_ADAE0(...,true)`) must also see input 0x21 held on the **next** controller port
  (`unit_0EE540.cpp:408`, `get_unk_B48()+1`), probably d-pad Up on pad 2.
- **Effect:** the shown furthest level becomes 38 for this visit only; nothing is saved.
- Combined with X1, a fresh profile can open level 38.
- **Test:** which button on which pad is the hold.

### X3. Unreachable in retail

- The debug menu: its open flag is only ever set to 0 (`unit_183130.cpp:127, 517`).
- Unlimited Ammo (`dword_4C19AC`), Game Speed (`flt_429298`), `ePE_RUNSPEEDCHEAT` and the debug
  switches: written only by the debug menu, or read by nothing.

---

## Suggested test order

1. **C9:** pause-menu Restart at level start in the listed levels; the checkpoint-volume deaths.
2. **W1:** the item-button reload cancel.
3. **M1:** read the pad's diagonal, then time a straight run with and without strafe.
4. **K1:** step-up heights at full diagonal speed and at 30 fps.
5. **T2:** grenade enemies out of "clear the area" volumes, or start the poll before they
   spawn.
6. **C4:** time one level transition with saving disabled.
7. **X2:** find the button and pad for the hold.
8. **K3 and M3:** mounted-gun dismount spots, vehicle exits, ladder-top fall cancels.
9. **K4 and T4:** section-trigger and door-trigger tricks, with the port's trigger overlay
   logging events.
10. **V1:** creep the L_1_3_A tank into a wall at under speed 2 (NTSC).
11. **P2, D4, O8:** L_3_1_C rocket spot; L_2_2 far barrel; L_1_1_B kill floors.
12. **D2:** L_1_3 wall collapse at 0.7 s, and the L_1_3_A door panel after it opens.
13. **O4:** walk out of an open exit, then try a mounted gun (expect it to fail).

The port's debug tools already help with this: the trigger overlay, `-checkpoint <n>` to start
at a checkpoint, the mount and vehicle buttons, and the script log.
