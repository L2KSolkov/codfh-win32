# Naming plan: every symbol named from evidence

A plan for replacing the database's placeholder names (`sub_1C5220`, `type_3E66D4`, `unk_1C`,
`dword_4B8744`, `vf_00C`, `var_10`) with real names throughout the recovered sources, with every
name backed by recorded evidence, and with the byte-identical builds (the placement-link gate
and the M7 retail SHA-1) unaffected.

## 1. Rules (the owner's, 2026-10-05)

1. **A name found in the text is used verbatim.** When the image, a library, or a source tree
   spells the name (`m_messageArgsLargePool`, `GameEntityManager::Restart`,
   `cXboxLiveNetGame::stateServerTakeUp`), that exact spelling is the name, prefixes and case
   included.
2. **Otherwise the name is chosen after verifying it with evidence** (section 4) and the evidence
   is recorded with the name.
3. **Every function gets a name.** No `sub_`, `vf_` or `pvf_` remains.
4. **RenderWare Studio classes keep RenderWare Studio's naming scheme** (the `RWS` namespace,
   `C`-prefixed classes, RW Studio's own member and method naming, as in
   `C:\rwstudio\Studio\console\game_framework\source`).
5. **Everything else uses Hungarian notation** for variables (members, globals, statics,
   parameters, locals), with the conventions in section 3.
6. **RenderWare (`src/rw`) and RenderWare Audio (`src/rwa`) are not touched** (the owner,
   2026-10-05): no renames in their sources or headers, including their address-named data and
   their unnamed RW Audio functions. Game code keeps calling and referencing them by their
   current names.
7. **Every function has a description comment** saying what it does (section 4.2), in every
   in-scope file, including functions whose names were already known.
8. **Game classes built on RW Studio bases (behaviours) are game code:** Hungarian variables,
   `C`-prefixed names (`CMountedWeaponBehavior`).
9. **Nothing changes bytes.** Every renaming batch passes the gate (`tools/ibuild.py`,
   `== PASS`), the M7 check (`m7retail.py`, `== IDENTICAL`) and `tools/session/labelcheck.py`.

## 2. Scope (measured 2026-10-05)

Placed rows outside the XDK (config/compiled.txt), by area and kind:

| Area | Placeholder functions (`sub_`) | `vf_` virtuals | Members of `type_` classes | Address-named data | Already named |
|---|---|---|---|---|---|
| game (`src/recovered`) | 5,967 | 1,448 | 3,249 | 1,086 | 2,214 |
| COD / Source | 142 | - | 4 | 14 | 1 |
| RW Studio (`src/rws`) | 7 | - | - | 3 | 416 |
| Bink (`src/bink`) | - | - | - | 15 | 373 |

Not in scope (rule 6): RenderWare (10 `sub_`, 21 address-named data, 1,906 named) and RenderWare
Audio (726 `sub_`, 337 address-named data, 62 named).

In the headers and sources:

- 1,007 placeholder types (`type_XXXXXX`);
- 1,145 distinct placeholder member names (`unk_XX`, 11,334 uses);
- 93,125 uses of slot-named locals and parameters (`var_N`, `lv_N`, `bp_N`, `arg_N`...).

Textual evidence in the image's data (5,700 strings):

- 20 member names (`m_actionPool`, `m_messageArgsSmallPool`, `m_taskTreeDataPool`...);
- 99 `Class::member` mentions across 48 classes (`GameEntityManager`, `SoldierEntity`,
  `CSystemLinkQuery`, `AsynchLoadingQueue`, `cNetGame`, `kujuUI`...);
- 1,618 identifier-like strings (attribute, message, event, behaviour and asset names).

## 3. Conventions

### 3.1 Which scheme applies

| Code | Types and functions | Variables |
|---|---|---|
| Game (`src/recovered`, `src/COD`, `src/Source`), behaviours on RW Studio bases included | Evidence spelling; otherwise section 3.2 | Hungarian (3.3) |
| RW Studio framework (`src/rws`, the `RWS` namespace) | RW Studio's scheme | RW Studio's scheme |
| Bink (`src/bink`) | RAD's names from `binkxbox.lib` (already in place) | Original names where the library has them; Hungarian for the few without |
| RenderWare (`src/rw`), RenderWare Audio (`src/rwa`) | Not touched | Not touched |

### 3.2 Types and functions (game code)

- **Types we name ourselves (no evidenced name):** `C` + PascalCase for classes, behaviours
  included (`CSquadList`, `CMountedWeaponBehavior`); PascalCase for plain data structs. Evidenced
  names keep their own spelling whatever their style (`cNetGame`, `kujuUI`, `alfasched`,
  `GameEntityManager`).
- **Functions:** PascalCase verb phrases (`GetHealth`, `UpdateSquads`, `IsAlive`); virtuals take
  the name of the base-class slot they override; constructors and destructors stay as they are.
- **Enums:** `E` + PascalCase; values `UPPER_CASE` with a common prefix.

### 3.3 Hungarian notation (variables)

| Prefix | Meaning | Prefix | Meaning |
|---|---|---|---|
| `g_` | global | `m_` | class/struct member |
| `s_` | file or function static | (none) | local or parameter |
| `p` | pointer (`pp` pointer to pointer) | `a` | array |
| `n` / `i` | signed int count / index | `u` / `ui` | unsigned int |
| `dw` | 32-bit flags/DWORD | `w` | 16-bit | 
| `by` | byte | `c` / `ch` | char |
| `b` | bool (`RwBool`, `bool`) | `f` | float (`RwReal`) |
| `d` | double | `sz` / `wsz` | NUL-terminated string / wide |
| `h` | handle | `pfn` | function pointer |
| `v` | vector (`RwV3d`) | `mat` | matrix (`RwMatrix`) |
| `e` | enum | `ll` / `ull` | 64-bit |

Examples: `m_pSquadList`, `g_nActivePlayers`, `s_fLastTime`, `pEntity`, `iSlot`, `szAlias`,
`m_aWeapons`. A name the evidence spells otherwise is used as spelled (rule 1), even when it is
not Hungarian (`m_actionPool`).

## 4. Evidence

### 4.1 Sources, strongest first

| Level | Source | Examples |
|---|---|---|
| **E1, text in the image** | Assert/debug strings, `Class::Method` messages, member names passed to pools and lists, `__FILE__` paths, RWS class/attribute/message registration strings, event names | `"GameEntityManager::Restart - ..."` names the function holding it; `"m_taskTreeDataPool"` names the pool member it initialises |
| **E2, a library or source tree** | RW Studio sources (`C:\rwstudio`), XDK headers and libraries, `binkxbox.lib`; the RenderWare and RW Audio headers for the types and functions game code passes to them | A game member typed `RpClump *` and passed to `RpClumpRender` is a clump; a member set from an RW Audio object creation holds that object |
| **E3, structure** | A virtual overriding a named base-class slot; a constructor's class name given to its vtable, destructor and methods; an accessor of a named member; a callback registered under a named event; a parameter passed straight to a named parameter | A behaviour's `HandleAttributes` override; `GetMessageArgsLargePool` returning `m_messageArgsLargePool` |
| **E4, verified behaviour** | The function's code, callers and data uses, read and checked (including in xemu for runtime behaviour when needed) | A function that returns the count of a list's live entries is `GetActiveCount` |

A name never rests on a guess: E4 names say what the code demonstrably does, and nothing beyond
it. When behaviour is unclear the name stays general (`UpdateState`, not `UpdateAiCombatState`)
until more evidence arrives.

### 4.2 Recording

Every renamed item keeps the existing PLAN.md comment form (original database name, address
or offset, type, evidence):

```
// sub_1D52E0 @ 0x1D52E0 - E1: "cXboxLiveNetGame::stateServerTakeUp" (string 0x3E5068)
// Takes over as server when the host leaves: elects this peer if it has the lowest player
// index, re-registers the session key and tells the remaining peers the new host's address.
int cXboxLiveNetGame::stateServerTakeUp()

RwInt32 m_nFreeCount;   // unk_14 (+0x14, RwInt32) - E3: count GetFreeCount (0x3EF20) returns
```

(The description above illustrates the form; each real one states what that function's code
does.)

**Function descriptions (required for every function).** The comment block above each function
holds, after the name/evidence line, a plain description of what the function does: its effect,
the inputs it reads, what it returns, and notable side effects (state changes, messages sent,
resources created or freed). Rules:

- It describes what the code demonstrably does (the same standard as E4 names): no intent or
  history beyond the evidence.
- Short functions get one sentence (`// Returns the squad's member count.`); longer ones a few
  lines, with the steps in order.
- Functions with no address of their own (inlines, folded copies) get one too.
- An existing description (many units already have them) is kept when it is accurate, and
  corrected when the naming pass shows otherwise.
- The comment lives in the source file above the definition, where `cm.py` and the audit expect
  the function's comment block; renaming tools keep it attached to its function.

A machine-readable registry, `config/names.txt`, holds one line per renamed symbol:
address or `type+offset`, old name, new name, evidence level and citation. The tools in
section 5 read it, the audit checks it against the sources, and the IDA database stays
untouched (names are never written back to it).

## 5. Tooling (built first)

1. **`tools/names/harvest.py`, the E1 index.** For every function, the strings it references
   (from the compiled objects' relocations to `??_C@`/`$SG` literals and the image's
   cross-references), the pool/list names passed with each global or member, and the
   `Class::member` strings; output: proposals with their citations.
2. **`tools/names/libmatch.py`, the E2 index.** RW Studio source names for the COD/Source and
   `src/rws` functions that match them, and the RenderWare/RW Audio API each game function and
   member is used with (evidence for the game's names; RW and RWA themselves stay as they are).
3. **`tools/names/propagate.py`, E3.** Virtual slots named from their base classes, class names
   from constructors to vtables, destructors and methods, accessor names from their members.
4. **`tools/names/rename.py`, the renaming engine.** Renames a symbol (function, type, member,
   global, local) in `src/` and `include/`, and refreshes everything keyed by the old
   decorated name: `config/compiled.txt` rows and `// match:` lines (the decorated names are read
   back from the recompiled objects), `config/aliases.txt`, `config/objaliases.txt`, the M7
   configs (`m7rows`, `m7drop`, `m7alt`, `m7disown`, `m7static`, `m7tls`, `m7bssrw`), and
   `config/names.txt`. It then runs the gate, `labelcheck.py` and the M7 check, and reverts
   the batch on any failure. Names read back from objects keep the configs' anonymous-namespace
   hashes (`?A0x...`, the hashes of the C:\codfh-match checkout): VC7.1 hashes the source's
   absolute path into them, so in another checkout (C:\codfh-rename) `rename.py` maps them back
   through `tools/anonfix.py`'s mapping before writing, and `cm.py`/`cmf.py` rows written there
   get the same treatment.
5. **`tools/names/localnames.py`, Hungarian locals at `/Od`.** VC7.1 at `/Od` lays out locals by
   name (docs/toolchain.md, "Local names decide stack slots": a fixed ranking over a 16-bucket
   hash). So a Hungarian name is chosen per slot from the meaningful base name plus allowed
   variants (`pEntity`, `pEntity2`, `pEnt`, `pTarget`...), and each variant is ranked with the
   probe `tools/local_names.py` already uses, until the whole frame keeps its layout. (Bink, the
   one optimised library in scope, does not depend on local names.)
6. **`tools/names/audit.py`.** Fails on any remaining `sub_`/`vf_`/`type_`/`unk_`/`var_` in the
   in-scope code (everything but `src/rw` and `src/rwa`), on any change under `src/rw`,
   `src/rwa` or their headers, on Hungarian prefixes that contradict the declared type (`pCount` for an int),
   on renamed items without an evidence comment or registry line, and on any function definition
   without a description comment above it.

### What renaming can and cannot change (checked by the gate)

- **Function, type and member names** do not change code or data bytes (no RTTI, `/GR-`), but
  they change decorated names, which the rows, configs and the M7 order file key on: hence the
  refresh step in `rename.py`, and the probe re-run with a refreshed `build/m7/seed.map` after
  each batch.
- **Names that are bytes:** the type descriptors of thrown exception classes (`??_R0?AV...`)
  and any name inside a string literal. Those names are E1 evidence by definition and are not
  changed.
- **Static and global names** can change an object's `.bss`/`.data` order by symbol hash; the
  placement link pins variables by row and the M7 link by address, so this is caught, not lost.
- **Local names at `/Od`** change stack slots: handled by step 5 and confirmed by the gate.

## 6. Process

### Phase 0: groundwork (2-3 weeks)

- The section 5 tools, tried on one unit end to end.
- `docs/PLAN.md`'s source conventions amended to these rules. They replace the slot-stating
  local names and the database-names-by-default rule.
- `config/names.txt` seeded with every name already evidenced in the sources (the existing
  evidence comments).

### Phase 1: textual evidence, everywhere (2-3 weeks)

- **E1 harvest** applied across the game: functions holding `Class::Method` strings, pools and
  lists named by their strings, RWS registration names.
- **E2 matching:** the COD/Source and `src/rws` functions from RW Studio sources where they
  match; game members and functions named from the RenderWare/RW Audio calls they make or feed.

### Phase 2: structure (3-4 weeks)

- **Class names** for the 1,007 placeholder types from E1/E3 (constructor strings, base classes,
  owning managers).
- **The 1,448 `vf_` slots** from their base classes (RW Studio's `CEventHandler`,
  `CAttributeHandler` and friends; the game's own base classes once named).
- **Accessors and their members** named together.

### Phase 3: behaviour, subsystem by subsystem (3-5 months)

E4 naming of the remaining functions, members and globals, one subsystem at a time, so each
batch reads as a whole and names stay consistent:

1. core (memory, containers, timers, `alfa*` scheduling and messaging);
2. entities and assets;
3. AI (squads, tasks, maneuvers, hearing);
4. weapons and projectiles;
5. players and input;
6. networking (`cNet*`, `cXbox*`);
7. UI (`kujuUI`, menus, in-game pages);
8. audio glue, level and section management.

Each subsystem batch:
1. Read the units; draft names with evidence, and a description for every function.
2. Apply with `rename.py` (descriptions are comments: they never change bytes).
3. Run the gate, `labelcheck.py` and the M7 check.
4. Commit.

The batches are small enough to review: one or a few units each.

### Phase 4: variables (alongside Phase 3, per unit)

Members, globals and statics get Hungarian names (and parameters and locals in the same
unit) once the unit's types and functions are named. At `/Od` the local-name tool keeps every
frame layout; the gate confirms.

## 7. Verification and done criteria

- Every batch: gate `== PASS`, M7 `== IDENTICAL`, `labelcheck.py` clean, `audit.py` clean for the
  units touched.
- Done: `audit.py` reports no placeholder names in the game, RW Studio, COD/Source and Bink
  code, no change under `src/rw` or `src/rwa`, every renamed item has an evidence comment and a
  registry line, and every function in scope has a description comment.

## 8. Decisions (the owner, 2026-10-05)

1. Behaviours (game classes on RW Studio bases) use Hungarian notation; RW Studio's scheme stays
   for the `RWS` framework itself.
2. Class names we coin take the `C` prefix (`CMountedWeaponBehavior`); evidenced names keep their
   own spelling.
3. Every function carries a description comment (4.2).
4. RenderWare and RenderWare Audio are not touched.
