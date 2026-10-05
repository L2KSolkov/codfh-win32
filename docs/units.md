# Translation-unit recovery (M1)

`config/splits.txt` holds placement ranges (one per IDA function and tail chunk); grouping them
into the original translation units is ongoing. Evidence so far:

## Dynamic initializers

`tools/initializers.py` dumps the 404 entries of the `_cinit` table (`0x426D50–0x4273B4`).
392 lie in the grouped block `0x3096E0–0x30DBBE` (the game's), 12 are CRT/XDK.

- 388 construct a `.bss` object, 6 a `.data` object.
- Within a unit, successive initializers construct globals at **descending** `.bss` addresses:
  VC7.1 lays out an object's `.bss` roughly in reverse definition order while initializers run in
  definition order. Splitting at every ascent gives 283 runs.
- The rule is not strict: 66 of the 282 run boundaries overlap the next run's globals (e.g.
  `0x449A50, 0x449A30, 0x4499F0, 0x4499D0 | 0x449A10, 0x4499B0, 0x449950`), so `.bss` order inside
  a unit is not purely reverse. Initializer runs are one boundary signal, not a partition.

## Other signals to combine

- `/GF` literal pool order in `.rdata` (first-object placement of `??_C@` COMDATs).
- `.text$x` order: EH funclets and handler thunks are grouped per object, in object order, and ICF
  folds identical ones across functions (`0x2FF9F0` serves both `sub_78AF0` and `sub_78B40`).
- The 12 assert paths and their `__LINE__` immediates.
- vtable and `__real@` constant placement; RWS and RenderWare file structure.

## Assert paths

The image keeps 12 game `__FILE__` strings, one per translation unit that asserts. For each, the
functions that reference it form one contiguous run, and no run overlaps another. Every run is a
**minimum** extent: only the functions holding an assert reference the path, so the unit's real
boundaries lie at or beyond these, and are found from the other signals.

| Unit | Referencing functions | Minimum extent |
|---|---:|---|
| `Source/GameCore/ai/aidatapathing.cpp` | 1 of 1 | `0x029940–0x029ECE` (the object: `0x028A60–0x031B8F`) |
| `Source/GameCore/ai/astarscheduler.cpp` | 2 of 2 | `0x032F70–0x03318E` |
| `Source/GameCore/pathnodemanager/astarpathfinder.cpp` | 2 of 3 | `0x0F6FC0–0x0F7AFE` |
| `COD/SHARED/fileIO/cFileIn.cpp` | 1 of 1 | `0x1C8B40–0x1C8B94` |
| `COD/SHARED/fileIO/cParsedFile.cpp` | 1 of 1 | `0x1C9980–0x1C9B3F` |
| `COD/SHARED/network/knet/cPacketEngine.cpp` | 1 of 1 | `0x1D0F60–0x1D164E` |
| `COD/SHARED/network/knet/sNetGameEP.cpp` | 31 of 31 | `0x1D5DC0–0x1D7A48` |
| `COD/SHARED/UI/cCaret.cpp` | 3 of 3 | `0x1E0E60–0x1E0EEA` |
| `COD/SHARED/UI/cLayoutPage.cpp` | 1 of 1 | `0x1E8870–0x1E8975` |
| `COD/SHARED/UI/cStaticImage.cpp` | 3 of 3 | `0x1F0190–0x1F021A` |
| `COD/SHARED/UI/cStaticText.cpp` | 3 of 3 | `0x1F05A0–0x1F062A` |
| `COD/SHARED/UI/cTopLayoutPage.cpp` | 1 of 1 | `0x1F4020–0x1F40F2` |

"n of m" is n referencing functions among the m functions inside the extent. The strings sit at
`0x3CE14C–0x3E7B1C` in `.rdata`, in the same order as the code, which fits first-object literal
placement.

## `COD/SHARED/network/knet/sNetGameEP.cpp`

The 31 functions `0x1D5DC0–0x1D7A48` are in the unit, and the unit **ends at `0x1D7A48`**. The
start is **`0x1D5DC0` or `0x1D5D30`**; which one is still open.

- **Definition order.** All 31 functions reference the unit's `__FILE__` string. Across their 57
  assert sites the `__LINE__` immediates rise strictly with address, from 192 at `0x1D5DC0` to 1495
  at `0x1D79B0`, so source order is address order here.
- **Literal run.** The unit's `.rdata` literals are the contiguous run `0x3E5194–0x3E52A3`
  (`"sNetGameEP:: broken packet %s:%d\n"`, the path, then strings used by `sub_1D6920`,
  `sub_1D7010`, `sub_1D7200` and `sub_1D7340`, in function order). The literal before it
  (`0x3E5168`) is used by `sub_1D52E0` (`cXboxLiveNetGame::stateServerTakeUp`); the one after it
  (`0x3E52A4`) by `sub_1D7DD0` (`CSystemLinkQuery::Query`). The unit has no vtable, `.data` or
  `.bss` of its own.
- **End.** The functions after it, `sub_1D7A50–sub_1D7CA0`, are four serialize/deserialize pairs
  reached through vtables at `0x3E4E40–0x3E4E60`. Those vtables sit in `cPacketEngine.cpp`'s
  `.rdata` and are installed by its code (`sub_1D0F60`); the pairs call the bitstream reader and
  writer and reference neither this unit's path nor its literals. They belong to another unit.
- **Start (open).** Just before the unit are `sub_1D5D30`, a formatting print through a 0x800-byte
  `/GS` buffer that hands the result to `dword_4FECF8`, and `sub_1D5DB0`, the one-line setter for
  that callback. `off_42CD14` in `.data` is initialised to `sub_1D5D30`, and this unit's dead
  prints call through it. Neither function has a literal, and their data (`off_42CD14`,
  `dword_4FECF8`) does not place them in this unit or the previous one. The first `__LINE__`
  being 192 leaves room for them in this file but does not require it.
- **Line gap.** `__LINE__` jumps from 1043 (`sub_1D7420`) to 1207 (`sub_1D7560`), with no function
  between them in the image: roughly 160 lines of source that emit no code here (unreferenced
  functions removed by `/OPT:REF`, folded ones, or declarations).
- **Matched (2026-10-01): all 31 functions**, `src/COD/SHARED/network/knet/sNetGameEP.cpp`. Each
  message type (type_DC400.h: `type_1D5DC0`, `type_1D6020`, `type_1D6230`, `type_1D6480`,
  `type_1D6700`, `type_1D6C60`, `type_1D6EB0`, `type_1D7200`, `type_1D7560`, `type_1D7870`, and the
  read-only `type_1D7760`, `type_1D77F0`) has a send (into a stack `type_1F8560_buf<bytes, bits>`,
  game/netmsg.h), a read and a check. The checks are `SNET_CHECK` (a dead `if (0)` print through
  `off_42CD14` with `#line`-pinned `__LINE__`, then `return 0`). What blocked it before: the
  guard's register is VC's register rotation, moved by compiled-out assertions (`SNET_ASSERT`,
  docs/toolchain.md), not a different compiler. Other shapes: `arg_0 = arg_0;`
  opens every check (the self-copy of the game pointer); the host peer is `B0->host()` (a
  `type_4F8054_B0` inline with its own check); `type_1DDE20_mask::single()` (one peer) returns
  through an `if`; the ping's check is `type_1D7560::sub_18F420`, folded by `/OPT:ICF` into
  `sub_18F420` (aliased); its read stores times by implicit conversion (`unk_00 = r->sub_1F8AF0()`).

## `astarscheduler.cpp` starts at `0x32E50` at the latest

`sub_32E50`, `sub_32EB0`, `sub_32F00` and `sub_32F50` set up, flush and complain about the A*
scheduler's two `alfasched` (`dword_438DE8`, `dword_438E38`; "Somebody forgot to unregister in
the AStar Scheduler!"), exactly as `sub_31AD0`, `sub_31B10`, `sub_31B50` and `sub_31B90` do for the
CanShoot scheduler's, and they run straight into `sub_32F70`, the unit's first assert. They are in
`src/Source/GameCore/ai/astarscheduler.cpp`, which is now fully matched: its eleven functions run
from `0x32E50` to `sub_33500` (ending `0x33513`), and `0x33520` starts another `type_3CE6D0` kind
(vtable `off_3CE4B4`), the next unit's. Before them, `0x32210`–`0x32DD0` is the
`type_3CE278` action object (its constructor, methods and "LTA_StartAlertStand"), so the unit
cannot start earlier than `0x32E50` unless that object's methods are in it too, which nothing
suggests.

## First unit (`src/recovered/unit_012000.cpp`), `0x12000–0x15500`

The first object in link order: AI action handlers dispatched through the 36-record table at
`0x427408` (`type_427408`), their helpers, and the AI object's constructor. Its file name and end
boundary are not yet recovered. All 64 of its functions are matched, `sub_12000` included: VC7.1's own
`vector constructor iterator` (35 bytes), which this unit's object emits and places from here (only XDK
code calls it in the image). The entity handle's constructor at 0x22C60 (pCtor) is placed from
unit_0390D0, whose object emits it out of line.

The unit's end is not established. Its literal pool runs on without a break past the constructor
(`sub_16E30`, `sub_17100`, `sub_172F0`, `sub_17AB0` and on to `0x1A2E0`, in first-use order), and
those functions are the AI object's own methods, so the file continues with them in address order.
That is consistent with one unit but does not prove it: consecutive units' pools are contiguous
too. If a boundary turns up, the functions past it move to their own file without changing a byte.

Past the constructor (`0x15500`–`0x21300`), the AI object's methods are matched in address order
(`config/compiled.txt` lists them). These are still binary, for these reasons:

| Function(s) | Why it is still binary |
|---|---|
| (none) | `sub_26A80` and `sub_26000` match with the side test through `and_sides` (an inline's arguments are evaluated right to left) and, in `sub_26000`, the kind read into a named local of each block that tests it; `sub_26A80` writes two of its offsets component by component and passes its last argument as a pointer. `sub_1B540` is disabled by a `goto` past its body, which the compiler still emits (a plain `return` drops it); its four unused locals keep their slots. The 16-aligned frames all match with `/Zi` (`docs/toolchain.md`): the turret centring `sub_1BFB0`, the tank's follow `sub_1ECF0` (RW's `RtQuatConvertToMatrix` macro, now in `rw/rtquat.h`), `sub_198A0`, `sub_19F90`, `sub_1BAA0`, `sub_1BD50` and the range tests `sub_21610`, `sub_21790`, `sub_21910` (SSE square roots through `<xmmintrin.h>`) match with it |

## `src/Source/GameCore/ai/aidatapathing.cpp`, `0x28A60`–`0x31B8F`

The AI's A* path planning and AIData's movement members: one original object (PLAN M7). Its
`.rdata` begins at `0x3CE014` with its own copy of the unreferenced 16.666666 every game object
starts its constants with (then the up axis and 100), and its literals run from `0x3CE028` to
`0x3CE1EC` with no other object's start among them, though `sub_29940`'s debug texts (its
`__FILE__`, `__LINE__` 873 to 919, written with `#line`) sit in the middle. Once three units
(split from unit_012000 at `0x28A60`, then aidatapathing's one function, then `0x29ED0`), merged
2026-10-03. It holds AIData's methods from `sub_28A60`, `sub_29940`, and the classes after them
(`type_3CE1FC`, the free functions from `sub_31AD0`).

## `src/recovered/unit_031B90.cpp`, `0x31B90`–`0x3220F`, and `unit_032210.cpp`, `0x32210`–

Two more objects after aidatapathing's: `unit_031B90`'s `.rdata` begins at `0x3CE200` with its
16.666666, `unit_032210`'s at `0x3CE268` with the up axis and its 16.666666 (`type_3CE278`).

## `src/recovered/unit_033520.cpp`, `0x33520`–`0x34F91`

The two `type_3CE6D0` kinds after `astarscheduler.cpp`: `type_3CE4B4` (kind 0, from `0x33520`)
and `type_3CE4F0` (kind 3, from `0x348D0`), then the cover-point A* search's registration
(`sub_34E20`), release (`sub_34E40`) and completion (`sub_34E60`, which astarscheduler's
`sub_332D0` calls). All of its functions are matched. It ends at `0x34F91`: `sub_34FA0` starts the
Distance Scheduler, whose setup, flushes and warning mirror the ones that open
`astarscheduler.cpp`.

## `src/recovered/unit_034FA0.cpp`, the Distance Scheduler, `0x34FA0`–`0x36723`

The scheduler's setup and shutdown, registrations (`type_35120`, drawn from the pool
"m_freeDistanceParams"), its handle table (`dword_438E90`) and its two callbacks. Its file name is
not in the image. All functions now match. The three remaining callbacks were
recovered with explicit local copies (2026-10-02):

- `sub_35AA0`: 369 bytes including its 32-byte jump table, 10 relocations.
  Three named handle values occupy -0x18/-0x1C/-0x20 before the serial
  getters' inline locals at -0x24/-0x28/-0x2C. Comma expressions keep
  the reads inside the original short-circuit conditions.
- `sub_35FD0` / `sub_362F0`: 674 / 675 bytes, seven relocations each.
  Named payloads, getter values and receiver pointers reproduce the 0x58-byte
  frames, with the four handle values before the three virtual-call receivers.

No compiler option, shared header or inline assembly change was needed.


## `src/recovered/unit_036730.cpp`, `type_3CE5AC`, `0x36730`–`0x390CC`

The kind-1 `type_3CE6D0` object ("AIAction_AttackStand"), after the Distance Scheduler and before
the kind-5 object at `0x390D0`. All match: the 16-aligned frames (the spot search `sub_37490`
with its unwind funclet and handler, the spot check `sub_380F0`, the node search `sub_37270` and
the node checks `sub_38AD0`, `sub_38D80`) with `/Zi`.

## `src/recovered/unit_0390D0.cpp`, `type_3CE5E8`, `0x390D0`–`0x3C1CF`

The kind-5 `type_3CE6D0` object, the fire-and-movement advance ("FireAndMovementFinished",
"FireAndMovementCleared"), between `type_3CE5AC`'s unit and the AIHearing class. Its constructor's
EH handler and funclets (`0x2FF5E0`–`0x2FF620`) are shared with the destructor through `/OPT:ICF`.
All functions now match. The two remaining entries were recovered on 2026-10-02:

- `sub_39AA0`: 1,039 bytes, 23 relocations, plus 22-byte cleanup and 10-byte
  EH handler. The handle-returning `get_unk_574_h()` supplies -0xE0 ahead
  of the later inline locals. Keep the eligibility checks in one condition
  inside a while loop, with the entity advance at the bottom.
- `sub_3A450`: 849 bytes and eight relocations. Named handle copies and
  receiver pointers restore its 0x44-byte frame. The second team branch
  still writes distance to the first team array, as the original does.

No compiler option, shared header or inline assembly change was needed.

## `src/recovered/unit_03C1D0.cpp`, AIHearing, `0x3C1D0`–`0x3CA01`

The AIHearing class ("Somebody forgot to unregister in the AIHearing Class!"): listeners and
lasting sounds, each in a pool and a list, and "AIAction_HearSound". All twelve functions are
matched. `type_3CE6D0`'s own methods follow from `0x3CA10`.

## `src/recovered/unit_03CA10.cpp`, `type_3CE6D0` and the AIManeuverManager, `0x3CA10`–`0x3D407`

`type_3CE6D0`'s own methods, then the AIManeuverManager: its pools, the kind factory and the
handle table `dword_4392A8`. All functions now match.

`sub_3CE20` matches 643 bytes including its 28-byte jump table, with 31
relocations, plus 102-byte cleanup and 10-byte handler pieces. The small
register_maneuver_handle inline keeps the registration call's union-return
temporary in the expansion phase, after the pool-size getter (-0x50 after
-0x4C). Ordinary static inline and by-value arguments are sufficient.

`sub_3D150` matches 388 bytes and six relocations. Named handle copies
at -0x5C/-0x60 put the factory's union return at -0x64. Both functions
use the existing compiler flags and shared headers.

## `src/recovered/unit_03D410.cpp`, `type_3D410`, `0x3D410`–`0x3DF2C`

The context a squad (`type_3DF30`) embeds at `+0x4` (the kinds receive it in their update): its constructor,
periodic updates (the table `dword_427660`; entry 0 is the target scan `sub_3D7D0`), candidate
records and target choice. All its functions are matched.

## `src/recovered/unit_03DF30.cpp`, the squads, `0x3DF30`–`0x3F110`

The squad (`type_3DF30`, 0x2E0 bytes, the pool "m_freeSquadList"): its constructor, setup
(`sub_3DF90`), cleanup (`sub_3E0A0`, a plain method with no unwind frame and so not the
destructor; it ends with an empty `type_3D410` method that /OPT:ICF folded into pDtor), update,
object list (kept in priority order) and entity list; then the squad list `dword_4395F0`: pool
setup, restart and shutdown, the AI update `sub_3ED10` that runs the schedulers and every squad,
and `sub_3EE10`, which puts an entity in a squad. The object list's insertion and removal (`sub_3E2C0`,
`sub_3E3B0`) copy the list links as handles (`type_365A0`) through inline getters and setters on the objects
(`get_unk_14`, `set_unk_14`, `get_unk_18`; the AI data's `get_unk_574_h`).

The squad factory `sub_3EEE0` now matches (194 bytes, 14 relocations),
with its 17-byte cleanup and 10-byte EH handler at 0x2FF6F0/0x2FF701.
An ordinary list getter preserves the head copy at -0x20; declarations
for global placement new/delete preserve the original out-of-line calls
that the transitive XDK `<new>` definitions otherwise inline away.
All functions in the unit are matched.

## `src/recovered/unit_03F120.cpp`, `type_3CE854`, `0x3F120`–`0x3F9EC`

The kind-4 object, derived from kind 3 (`type_3CE4F0`): its constructor, destructor, overrides
and the member driver `sub_3F310` (a switch over the AI object's state, like kind 3's
`sub_34A60`, with each case's locals in a block of its own). All eight functions are matched.

## `src/recovered/unit_03FA10.cpp`, the target scores, `0x3FA10`–`0x40717`

`AIData::sub_3FA10` scores a target for its owner by the owner's kind, through `sub_3FAC0`,
`sub_401B0`, `sub_403F0` or `AIData::sub_404A0`. The Vision Scheduler follows from `0x40720`.
Every function in it matches.

## `src/recovered/unit_040720.cpp`, the Vision Scheduler, `0x40720`–`0x42983`

The Vision Scheduler ("Somebody forgot to unregister in the Vision Scheduler!"): its setup and
shutdowns (like the Distance Scheduler's), its registrations (`type_409A0`, pool
"m_freeVisionParams", handle table `dword_439618`), the looks each schedule runs (`sub_40F00` at
the tracked entity, `sub_40FB0` at every watched entity) and the look itself (`sub_40C60`): range,
turn-taking, line of sight through the collision worlds (`sub_42210` and its callbacks) and the
"TargetSeen" / "TargetLostLOS" / "CanPotentiallySeeTarget" messages. `sub_40A60`, which registers an
object with both schedules, was undefined in the database and was split out. The view-cone test
`sub_415E0` and the line of sight from a node `sub_41B20` (16-aligned frames) match with `/Zi`.
All match.

## `src/recovered/unit_042990.cpp`, the action queue, `0x42990`–`0x42F34`

The action queue ("m_actionPool"): its setup, restart and shutdown, the records' pool, queueing
behind the running action or at the tick's end (`sub_42AF0`), the tick that runs the queued actions
(`sub_42C50`, which sends "Tick") and dropping a sender's actions (`sub_42E00`). All thirteen
functions are matched.

## `src/recovered/unit_042F40.cpp`, `CDebugScript`, `0x42F40`–`0x441A7`

A RenderWare Studio behaviour ("CDebugScript", registered with the class factory at `0x309910`)
whose commands set the message system's debug settings. The unit also holds the inline RWS pieces
it instantiates (`MakeNew`, the linear allocation policy's `operator new`,
`CLinearMemoryManager::Instance`), the base classes' scalar deleting destructors, and the Dinkumware
STL functions it instantiates from the XDK's headers (`std::vector::reserve` and `_Xlen`, and the
`std::string`, `logic_error` and `length_error` functions `_Xlen` brings in), all matched at `/Od`
with their unwind funclets. The RWS headers (`include/rws`) follow the image's older framework:
`CAttributeHandler` has only the destructor and `HandleAttributes`. All functions now match.

`CDebugScript::HandleAttributes` (`sub_43200`) matches 586 bytes including
its 56-byte jump table, with 48 relocations. Command 11 reads into the
named value at -0xC using GetCommandData, then retains the two-load
compiled-out-check effect before the member store. DEBUGSCRIPT_CHECK
documents that the original condition is unknown and is chosen for its
loads. The resulting frame is 0x64; no header or compiler change was needed.

## `src/recovered/unit_0441B0.cpp`, the script commands, `0x441B0`–`0x67253`

The script interpreter's commands ("efuncs"): the table `String1` (`0x4276E0`) names 612 of them,
from `0x443C0` to `0x67200` (the last, "GetWeaponType"). This unit holds the lookup (`sub_441B0`), the debugger's hook
(`sub_44220`), the call's result push (`sub_44350`) and the first commands; each carries its
table name in its comment. Arguments are read through an inline accessor (`SCRIPT_ARG`,
`types/type_44350.h`); each call to the debugger's hook goes through a macro that also expands an
inline function declaring five locals it never uses (`SCRIPT_CHECK`; some call sites reserve six
more, `SCRIPT_CHECK2`), so those slots come in source order with other inline functions' locals
("SnapToCover", "AttachProp"). Some calls to the hook reserve nothing and are written directly
("AttachProp", "AttachPropEx"). Many
commands reserve further slots they never use, beyond their used locals (eleven in most of those
calling `sub_45170`); a nested block of unused locals gives them, placed in the source where the
image's slot order needs it, since block scopes take their slots in source order ("SetEntityScale",
"AttachToMountedWeapon"). The 16-aligned frames all match with `/Zi` (`docs/toolchain.md`): the attach-point getters (`sub_561E0` to `sub_56910`), "AttachToEntity" (`sub_58360`), the distances (`sub_64620` to `sub_648C0`), "SetSplineOffsetXYZIJK" (`sub_65180`), "RotateMyOrientation" (`sub_4D9B0`), "DetachFromEntity" (`sub_58670`), the attach-point task commands (`sub_58F10`, `sub_590F0`, `sub_592E0`), the dive checks (`sub_4D170`, `sub_4DB20`), the MMG and alarm-crank performances (`sub_47A20`, `sub_47C20`), "SetGrenadeThrowPoint" (`sub_49D70`), "SpawnParticleAtPosition" (`sub_4BAA0`), "PlayParticleSystemAtXYZ" (`sub_4AB90`, with the blast request's constructor `sub_4AE70`), the vehicle transitions (`sub_510C0`, `sub_512E0`), `sub_458A0` and "DropGrenadeAtLocationXYZ" (`sub_495F0`). Every function in it matches.

## `src/recovered/unit_067260.cpp`, the handle table, `0x67260`–`0x6769A`

The handle table `dword_439E78` (`types/type_439E78.h`): its reset (`sub_672F0`, and "Restart"
`sub_67340` with its debug print), registration (`sub_673C0`), release (`sub_67520`, which destroys
the object by its kind), lookup (`sub_67620`) and entry fill (`sub_67650`). The constructor
`type_67260::type_67260` (`0x67260`) heads it; its users are all elsewhere, so it may belong to the
script commands' last file instead. `alfahash` follows at `0x676A0` (its pool is named
"alfahash::m_pool"), a separate file.

## `src/recovered/unit_0676A0.cpp`, `alfahash`, `0x676A0`–`0x67B06`

A chained hash table of pointers (`types/alfahash.h`), named from its pool's string
"alfahash::m_pool": constructor, destructor (with its EH handler at `0x2FF880`), set-up, and the
insert, remove, find and walk methods, in address order. Its pool is `type_16C2A0`, whose
constructor and destructor (`sub_16C280`, `sub_16C2A0`) are aliased in `config/aliases.txt`. The
script interpreter's initialisation follows at `0x67B10`.

## `src/recovered/unit_067B10.cpp`, the script VM, `0x67B10`–`0x6B39E`

The interpreter that runs compiled scripts (`types/scriptvm.h`): its set-up (`sub_67B10`, which
fills the opcode table `dword_4491C0` in the source's order, not the table's), image loading
(`sub_67E00`, `sub_67E30`, and the in-place sorts `sub_68190` and `sub_68250`), the run loop
(`sub_68310`) and the opcode handlers from `sub_68450`. The two sorts' record copies are structs of
dwords: padding them with byte arrays gives each a `/GS` cookie the image does not have.
The debugger's reports (`sub_6A970`, a delivery; `sub_6B060`, a line) build their text but never print
it (the print is compiled out): their lookups are named locals, `unk_24` goes through a direct-return
accessor, and the database's `j__atol` is `atoi` (a tail jump into `atol`).

The thread opcode (`sub_6A1A0`) compares its thread's current task with the handle through
`get_unk_04_h()`: a struct returned by value gets a slot among the named locals, not the
temporaries. Its object check is a `SCRIPT_CHECK` (five reserved slots).

## `src/recovered/unit_06B3B0.cpp`, `alfamessman`, `0x6B3B0`–`0x6CA57`

The message manager (`types/alfamessman.h`), named from its pools' strings
("alfamessman::m_messagePool"): its static pools and registration array, set up by `sub_6B3B0`,
and the senders. They hold a kernel critical section (`xbox/xboxkrnl.h`; the import slots are
aliased in `config/aliases.txt`), the messages (`type_42E00`), their delivery through the
registrations (`type_6B960`) and their filters. A class's methods follow at `0x6CA60`.

## `src/recovered/unit_06CA60.cpp`, the Alfa objects' classes, `0x6CA60`–`0x70C96`

The classes of the objects scripts run on (`types/alfaobject.h`), named for their vtables: the base
`type_3D2C88` (the 18 slots `type_67620` describes as a flattened view), the script host
`type_3D2C30` and the entity's script object `type_3D2CD0`, with their constructors, destructors
(the latter's deleting destructor frees nothing: the objects live in pools, so the class has an
empty `operator delete`) and methods. The vtables and the folded empty `type_3D2C30::vf_050` are
aliased in `config/aliases.txt`. `type_3D2C30`'s constructor reserves one slot it never writes
(an unused local). The file goes on with the thread manager `type_3D2DB8` (a state machine of
32-byte states with sorted message handlers, `bsearch`ed) and the task `type_3D2E20` (call records,
threads, parent/callee/child links); `type_67620` and `type_46120` stay flattened views of these for
the script VM and the commands. Their handle links copy through the 4-byte struct
`type_439E78_00`: by-value `operator=` (the argument copied) or a no-local inline's return
(value stored before the destination is loaded), as the bytes require (docs/toolchain.md).
Still binary:

| Function(s) | Why it is still binary |
|---|---|
| `sub_6CCF0` | returns its second argument: the placement `operator new`, emitted where it is used |

The pooled classes' placement `operator new` (`sub_6CCF0`, returning the slot) is defined here as
`type_3D2CD0`'s; /OPT:ICF folds every other class's into it.

## `src/recovered/unit_070CA0.cpp`, `type_3D2E7C`, `0x70CA0`–`0x71359`

The AI object (vtable `off_3D2E7C`, one slot): its constructor, its script's start as a state
machine or a task (telling it "Initialize"), its tasks and thread manager by handle, its entity or
trigger by kind, and "DestroySelf" (`sub_71100`). The object manager (pools, registers) follows at
`0x71360`.

## `src/recovered/unit_071360.cpp`, the Alfa object manager, `0x71360`–`0x71EBF`

The pools the Alfa objects come from (named by the strings its set-up `sub_713E0` passes:
`m_pobjectPool`, `m_aiObjectPool`, `m_stateMachineObjectPool`, `m_taskObjectPool`,
`m_taskTreeDataPool`, `m_inputListPool`, `m_memPools[3]`), their check at restart and shutdown,
allocation and release by kind, scripts' locals from the memory pools, and the 101 global script
registers (`sub_71DB0`, `sub_71E40`). State in `include/types/alfaobjman.h`. The objects are built in their pool slots with class
placement `operator new` (`sub_6CCF0`) whose placement `operator delete` folded into `sub_19A750`;
the four allocators share one unwind funclet and handler (`0x2FF8A0`, `0x2FF8B1`), annotated under
`sub_71870` and aliased for the others. `alfasched` follows at `0x71EC0` (its constructor).

## `src/recovered/unit_071EC0.cpp`, `alfasched`, `0x71EC0`–`0x7280F`

The scheduler (named from its string `alfasched::m_freeList`): registrations
(`alfasched_entry`, 0x1C bytes from `m_freeList`, each with its own kind-5 handle) kept in a list
with head, tail and the entry being run. `sub_72560` runs up to `unk_34` callbacks each `unk_30`
time units, rotating the list; `sub_726E0` filters it through a callback; `unk_40` is told of each
entry freed. The Alfa script tables (`sub_72810`, pools of `alfahash`) follow at `0x72810`.

## `src/recovered/unit_072810.cpp`, the loaded script files, `0x72810`–`0x7335F`

Four `alfahash` tables of loaded file contents by id (`dword_449AD8`, `dword_449AA4` functions,
`dword_449B0C` state machines, `dword_449A70` by word id), the relocation of a loaded file by the
kind byte in its header (`sub_72BA0` to `sub_72F00`), and the resolution of its imports
(`sub_72FC0`), globals registering by their `god_*` type name (`sub_73160`). Also
`CompareFunction` (the database's name), the `qsort` order the script VM sorts its tables with.
The layouts are per-lookup views in `include/types/type_72810.h`; a byte array in a key's struct
gives its lookup a /GS cookie (only `sub_72990`'s has one), which fixes where the arrays are.
`alfatimer` follows at `0x73360`.

## `src/recovered/unit_073360.cpp`, `alfatimer`, `0x73360`–`0x7370F`

The script timers (named from the string `alfatimer::m_freeList`, their pool `dword_449B48`): a
list kept in time order, registered by "RegisterTimer" (`sub_733D0`), dropped per object or per
message, and posted as messages (`sub_6B680`) when the clock `dword_449B40` passes them
(`sub_73650`). State in `include/types/alfatimer.h`. A spawn function follows at `0x73710`.

## `src/recovered/unit_073710.cpp`, the animated background entity, `0x73710`–`0x770BF`

`type_3D32F8` (vtable `off_3D32F8`; "AnimatedBGEntity"), 0x490 bytes, built in entity memory by
`sub_73710` through a class placement `operator new` (`sub_6CCF0`), with its inline constructor
calling the set-up `sub_740B0`. Because its constructor unwinds through `type_3D3548`'s
destructor, this unit is where the image has that destructor and the class's inline virtuals. Its empty three-argument slot (`vf_204`, 0x73D80, "SetUpdateCallBack") also fills slot +0x218 through /OPT:ICF.
The 16-aligned `ebx` frames match with `/Zi`: the set-up `sub_740B0`, the update `vf_04C` (0x751A0,
the mounted weapon at its tag), attaching the player (0x75AF0) and the five-way blend (0x76960).
`type_3D3548`'s destructor is virtual and defined in its class, not expanded: its out-of-line
copy (`sub_73850`), both classes' scalar deleting destructors (their empty class `operator delete`
folded into `sub_19A750`) and `type_3D32F8`'s destructor all match here. Every function in it
matches.

## `src/recovered/unit_0770C0.cpp`, the animation banks, `0x770C0`–`0x78AEF`

The animation banks: a table of banks (`dword_449C94`, 0x44 bytes each) over one heap, set up by
`sub_770F0` ("ANIMATION HEAP SIZE ALLOCATION"), each holding a data set loaded from an
"ANIMGRPS\..." file and built in its part of the heap; the sets' animation chains and event
lists; the animation players' three pools and their handle table (`dword_449CA0`). State in
`include/types/animbank.h`. The pool class's unit follows at `0x78AF0` (its constructor).

The set reader (`sub_77E40`) passes `sub_801C0` and `sub_802D0` one argument more than they
read (the animation's index, the custom size).

## `src/recovered/unit_078AF0.cpp`, `CAnimObjectPool` and the animation player, `0x78AF0`–`0x7CA1F`

The animation players' pools (the class name is in its own warning), three at `byte_44A508`, each
a `type_16C2A0` `m_pool` ("animobjpool::m_pool") of players (`type_7C8D0`, 0x1C0 bytes with their
tracks following) built with a class placement `operator new`; and the animation event callback
`sub_78D10`. Its destructor supersedes probe p03's placement of `0x78B40` (the probe still proves
the EH shape). State in `include/types/animobjpool.h`. The players' class (`type_7C8D0`, vtable
`off_3D3CB4`) follows from `0x78D60`: its tracks (0x2C bytes each, after the player), its ring of
twelve queue records, procedural tracks with their interpolators, root motion (`RtQuat` macros), and
the event callbacks (`dword_44A5A0`) and update hooks (`dword_44A580`).

Aiming the root motion at a point and heading (`sub_79D50`, `RtQuatConvertFromMatrix` and
`RtQuatTransformVectors`, which the database calls RtQuatQueryRotate) and turning to a direction
(`sub_7A0A0`) have 16-aligned frames and match with `/Zi`. The hierarchy set-up `sub_79270`
matches too; it frees through 0x2C37C0, a jump through the memory interface's free slot that the
database calls `__rpCollTreeDestroy` (declared under that name). The update (`sub_7A580`) keeps
its root-motion frame update under an `if (0)` that is still emitted; its header local needs
`type_7CBD0_hdr`'s padding as scalars (a byte array gives it a /GS cookie).

## `src/recovered/unit_07CA20.cpp`, the animation keyframes, `0x7CA20`–

The game's compressed animation keys (quaternions as three shorts in 32768ths with the real part
recovered, positions as half floats) and their interpolation callbacks. State in
`include/types/animkey.h`.

The interpolation schemes register into a 16-entry table (`sub_7FD90`); an animation
(`RtAnimAnimation`, `include/rw/rtanim.h`) is a 0x1C-byte header with a flag byte at +0x10 (set
when `sub_7FE60` allocated it) and its frames 16-aligned after it. `sub_7FEF0`'s size sum only
matches in one association: `((b + 3) & ~3) + (c + (0x2B + ((n * 4 + 3) & ~3)))`.

The interpolators (`type_80300`, 0x150 bytes before their keyframes) come from two pools or the
heap (`sub_80300`, `sub_80550`) and copy their scheme's callbacks (`sub_80740`, `sub_807E0`). The
database had no function at `0x7FFD0` (it started one at `0x80008`, inside it) or at `0x80300`; both
are split out. The game registers one scheme, 0x1142 (`sub_7DE10`): its keys decode through RW's
`RtQuatUnitConvertToMatrix` (`sub_7E230`); `sub_7DEB0` tests `(RwReal)fabs((RwDouble)q)`, not the
float overload of `fabs`, which would copy its argument first. The two key decoders (`sub_7D2F0`, `sub_80910`) keep
their keys in `type_7DCA0_q` locals (a struct holding three shorts), and /GS guards them: the cookie
sits just above the first. Their 35-odd locals were named with `tools/climb_names.py`. `sub_7F3C0`
is RenderWare's RpHAnimHierarchyUpdateMatrices with a root scale; its node stack pointer starts
at the second of its 32 entries.

## `src/recovered/unit_0811C0.cpp`, the asynchronous loading queue, `0x811C0`–

"AsynchLoadingQueue" in its debug strings: a ring of sixteen 0x4C-byte load requests
(`dword_44BAD8`), the loading thread that works through them (`sub_81590`, started through XAPI's
`CreateThread` by `sub_82410`), and the critical sections around both. State in
`include/types/asynchload.h`; the XAPI thread functions in `include/xbox/xapi.h` and RenderWare's
memory interface in `include/rw/bamemory.h`. `sub_813E0` swaps RenderWare's allocation functions
around its wait for the thread. `sub_82130` tests the bank's top bit as `((x & 0x80000000) != 0) == 0`:
the plain `== 0` test compiles without the `neg`/`sbb`/`neg` the image has. The loading thread (`sub_81590`) tests the same bit as
`((x & 0x80000000) != 0) != 0`, ends in `ExitThread` (declared `__declspec(noreturn)`, as winbase.h has
it, so the function needs no `return`), passes two shorts through inline helpers' two-byte
temporaries, and passes an anim bank's set id to `sub_77540` as one 8-byte struct.

## `src/recovered/unit_0824A0.cpp`, the sound banks, `0x824A0`–

Loading the sound banks from their files, and the sound table read at start-up (`sub_82500`).
State in `include/types/soundbank.h`.

Two compiler habits explain the temporaries in this unit (docs/toolchain.md has the details).
The list link's destructor is defined in its class. VC7.1 does not inline it, because it
deletes, but each caller keeps 8 bytes for the expansion it did not make: `sub_83760`,
`sub_85730`, and through `sub_83760` the slot's destructor `sub_863A0`. The operator new that
takes a memory type has a matching placement `operator delete` declared, so every
`new (4) T` copies its result through one more temporary (`sub_825E0`, `sub_85A00`).
`sub_85730` is defined in the class as well. `sub_85090`'s 40 spare bytes come from its two
calls to it, and `sub_835E0`'s 16 from its call to `sub_83760`.
The pause and resume (`sub_85D60`, `sub_860E0`) set `dword_44E89C` and return at once; the rest
of each is dead code after a `return`, which VC7.1 at `/Od` still emits (without the first loop's
initialisation, which nothing reaches). `sub_857B0` calls an empty method of each music player
(`pDtor`, folded by `/OPT:ICF`), not the players' destructor.

## `src/recovered/unit_0863C0.cpp`, the music players, `0x863C0`–

The three music players (`dword_44E8D8`, 0x2025C bytes each): streaming a file through the audio
library, with its request, state and volumes. Its constructor at `0x863C0` starts the file. State
in `include/types/musicplayer.h`.

## `src/recovered/unit_08AB60.cpp`, the CCESS pool manager, `0x8AB60`–

The trackers of the objects that take part ("m_freeTriggerTracker" and
"m_freeSpecialTriggerTracker" pools), and ten slots that each pick one of them now and then
(`dword_4B2178` holds the manager's state, "SetCCESSPoolManagerState"). State in
`include/types/ccess.h`. `sub_8AFF0`, the pick, now matches 392 bytes and
one relocation: the inclusive-range count expression `(count - 1) + 1`
retains the original ECX divisor load. The full unit now matches. Earlier
signedness, cast and inline-helper attempts did not recover this expression.
`type_8F300::sub_8F3E0` (the zone's point test) and `sub_92620` (RenderWare's line-triangle
test) take their dot and cross products through RenderWare's vector macros (`rw/bavector.h`).
Only the macro form gives the image's operand order (docs/toolchain.md). The four-float helpers from
`0x8B920` to `0x8BFA0` (vectors and 4x4 matrices returned by value) each build their result in a
16-aligned local (`__declspec(align(16))` on the local; the matrix type is aligned itself) and
match with `/Zi`, as do the box transform `sub_8C410` and the bone boxes' line and sphere tests
(`sub_8D660`, `sub_8E330`), and the boxes' set-up `sub_8C690` (its box type is 16-aligned too, for
its return temporaries' slots).
The sector zone lists (`sub_8F5C0`) pack four zone indices to a word through a shift and a word
pointer held in block locals, which the image keeps below the struct-return temporaries. The
moving entity's atomic callback (`sub_946B0`) keeps the atomic's orthonormalised matrix and its
inverse on its own aligned frame and points the search context at them.
The entity collision searches all match: the sphere searches `sub_948A0`, `sub_950C0`,
`sub_96EF0` and `sub_985B0` (the context type_93DF0 is declared where its constructor runs,
after the first stores, so its slot needs a later name bucket), their atomic and triangle
callbacks (`sub_943E0`, `sub_946B0`, `sub_929A0`, `sub_930F0`, `sub_93700`, `sub_97790`,
`sub_98200`), the flush and push-outs (`sub_96680`, `sub_974A0`), the sphere-triangle tests
(`sub_95C70`, `sub_959E0`) and the contact sorting (`sub_992B0`). RenderWare's RpIntersection
keeps its data before its type, so the callbacks read `t.sphere` at +0. One reciprocal
(`1.0f / (0, x)` in `sub_929A0` and `sub_93700`) needs a comma expression for its operand order.
The zones' light list (`type_8E670::sub_8E870`) matches too. A triangle's nearest point (`sub_8F960`, 9.6 KB) is two macros, an
edge test inside a projection case, expanded twelve times; two operands need comma expressions.
The world line test (`sub_91F40`) walks RenderWare's line
iterators (`RpSectorLineIt`, `RpCollSectorLineIt` in rw/rpcollis.h; the database swaps two of their
names, config/aliases.txt).

## `src/recovered/unit_09AD40.cpp`, a trigger-spawned entity class, `0x9AD40`–

`type_3D51C0` (its vtable `off_3D51C0`), derived from `type_3D3548`. It is spawned from a
trigger in entity memory (`sub_9AD40`), with a script object and an AI object held by handle,
and a three-word scene. State in `include/types/type_3D51C0.h`. Its constructor is defined in
the class but not expanded: `sub_9AD40` keeps the 8 bytes of a failed inline site for it
(Insight A in docs/toolchain.md). The out-of-line copy matches at `sub_9AE50`. The lists at
+0x3B0 and +0x3BC have inline constructors and destructors and an empty inline base
destructor. The unwind funclets call those destructors out of line (`sub_73A10`, `sub_73A70`,
and pDtor for the base).

The destructors match now that `type_3D3548`'s is virtual and defined in its class, not
expanded (every derived destructor reserves its members' inline-destructor temporaries, the 20
bytes that were missing): `sub_9AFE0` and `type_3D5400`'s and `type_3D5658`'s (`sub_9B860`,
`sub_9C660`), each with its scalar deleting destructor (an empty class `operator delete`, folded
into `sub_19A750`). `vf_234` (`sub_9B0B0`) now matches too: 520 bytes and
13 relocations. Its two script-handle setter values are named locals at -0x1C/-0x20;
the object-handle getter then supplies the struct-return temporary at -0x24, followed
by zero_v3d and the two script getters at -0x28/-0x2C/-0x30. The frame is 0x34.
No header or compiler changes were needed; no function in this unit remains binary.

`type_3D5400` (vtable `off_3D5400`) follows. Its constructor is inline and expanded in
`sub_9B700`.

AddTaskTrigger (`include/types/AddTaskTrigger.h`, the RWS behaviour of kind 0x17) follows from
`0x9DD80`: every function of it matches (its HandleAttributes, `sub_9E0F0`, is a 19-case
attribute switch whose cases come in the source order 11, 5, 7, 6, 8, 2, 10, 3, 13 to 18, 0, 1,
12, 4). AnimatedBGTrigger (`include/types/AnimatedBGTrigger.h`, kind 8)
follows from `0x9F130`, in its own object since M7 (`src/recovered/unit_09F130.cpp`: AddTaskTrigger's
deferred `??_E` thunk at `0x9F120` ends this one): every function of it matches. Its HandleAttributes (`sub_9F5F0`) reads
commands 3 and 4 in a first pass, then the rest; command 28 falls through into 29 (no `break`), and
commands read straight into a field use `GetCommandData`, where those with a value temporary use
`GetAs_RwInt32`.

## `src/recovered/unit_0A02D0.cpp`, CAnimBankInfo, `0xA02D0`–

A RenderWare Studio behaviour holding the animation heap's sizes. The initializer at `0x30A510`
registers it with the class factory as "CAnimBankInfo", together with its MakeNew. It is built
like CDebugScript (unit_042F40): an attribute handler, with an event handler at +0x18.
CAnimPackSelector follows (the single instance at `dword_4B67CC`, which loads the six
animation packs when the system starts). The behaviours around them (the kind-0x17
and kind-8 "triggers" in unit_09AD40) are RWS behaviours of the same shape. They are declared
there on the trigger struct `Trigger` until that struct becomes the RWS class it is.

## `src/recovered/unit_0A0A50.cpp`, CAnimPackSelector, `0xA0A50`–

Split from unit_0A02D0 (PLAN M7): CAnimBankInfo's `??_E` thunk (`0xA0A40`) is deferred, so its
object ends there, and CAnimPackSelector's MakeNew starts the next one. Its `.rdata` (class name,
`flt_3D59B8`, vtables, texts), `dword_4B67CC`, class ID and registration go with it.

## `src/recovered/unit_0A11E0.cpp`, AnimPackTrigger, `0xA11E0`–

A trigger behaviour of kind 0x10 holding six animation packs. It derives from the 0xC0-byte
base `Trigger`, whose constructor (`sub_BBA30`) and destructor (`sub_BBD10`) stay binary
(config/aliases.txt). Its destructor is empty and defined in the class; the image keeps its
out-of-line copy at `sub_A13C0`.

## `src/recovered/unit_0A1690.cpp`, AnimTestTrigger, `0xA1690`–

A soldier spawner for testing animations. It derives from `SoldierTrigger` (unit_0B7AA0).
SoldierTrigger's constant functions (its kind 5,
capacity, key and CCESS slot, `0xA17A0` to `0xA17F0`) sit after this unit's constructor and are
recovered here. The same holds for Trigger's in unit_09AD40. Its HandleAttributes (`sub_A1860`) registers
byte names and performance maps (kind 0xD, `type_198900_perf`).

## `src/recovered/unit_0A1CA0.cpp` and `unit_0A2080.cpp`, HitDeathTestTrigger and SceneTestTrigger

Two more SoldierTrigger test spawners, one for hit deaths and one for scenes, each built like
AnimTestTrigger. Their HandleAttributes (`sub_A1DE0`, `sub_A21D0`) have the same shape as
AnimTestTrigger's; each unit also holds its destructor's adjustor thunk (aliased to its `??_G`).

## The RWS behaviours from `0xA23F0` to `0xCC8A0`, one unit each

CCESSPoolTrigger, ConfinedAreaTrigger, CustomTrigger, DestructableObjectTrigger and its mesh-swap
subclass, DogTrigger, CMountedWeaponBehavior, MountedWeaponTrigger, CNPCWeaponBehavior,
XBOXPadMap, ParticleTrigger, PathNode, CPickupSelector, PickupTrigger,
ProjectileGeneratorTrigger, RenderTrigger, SceneTrigger, SectionInfo, SectionTrigger,
StartingSections, CShellBehaviorClass, CShellLevelBehaviorClass, SimpleMechanicTrigger,
SoldierTrigger, CSoundBankSelector, SoundBankTrigger, SplinePath, StopSoundStreamTrigger,
StreamTrigger, StreamVolume, VehicleEnterExitTrigger, FlakTrigger, VehicleTrigger,
CWeaponBehavior (with CExplosiveBehavior, CTankBehavior, CAntiTankBehavior and CGrenadeBehavior,
one file: their MakeNews share one EH handler and their thunks follow CGrenadeBehavior's
functions), WorldLight, LevelInfo, CPickupBehavior, LevelClumpBankParamTrigger,
StreamClumpTrigger, LevelScriptTrigger, PlaySoundTrigger, GimpTrigger, CGlobalSounds, CPoolSizes,
CMountedWeaponSelector, LadderTrigger, ShrimpTrigger, PulseZoneTrigger,
GimpVehicleTrigger, EndLevelTrigger, FogTrigger and PASTrigger. Each unit is named for its MakeNew and holds the class's
functions in address order, ending with its multiple-inheritance thunk. docs/behaviours.md lists
them.

SplinePath's destructor `sub_BA030` now matches with `/EHa` for its unit.
The source body is empty; asynchronous exception handling preserves the
original EH state 0 and base cleanup. Earlier source-only attempts under
`/EHsc` could not retain that state. All other functions in the unit keep
their exact matches, including its constructor and 16-aligned frames.

## `src/recovered/unit_0CC8A0.cpp`, the entity base type_3D3548, `0xCC8A0`–`0xD48D0`

The base class every game entity derives from (vtable `off_3D3548`): its constructor, reset,
frame and render parts, collision tests and line tests, fading and throbbing, the material
colour callbacks vf_054 uses and a blow at the nearest opposing entity. The RenderWare callbacks
keep their database names (Collision_..., Clump_..., Frame_...).

vf_000 `sub_D34B0` returns 1 on both paths; the frustum test after that is the player's vf_064
test (camera, planes, atomic, sphere), whose dropped set-up still holds its slots.

Every function matches. The 16-aligned frames match with `/Zi`: the model set-up, vf_224
`sub_D1BF0`; the movement and collision, vf_044 `sub_CF520`, whose frame-height easing has an
empty then-branch; the animation events, vf_170 `sub_CE070` (the weapon's event handler,
type_10F710_1A48::vf_030, is its twin); the update vf_03C `sub_CF0E0`; turning the entity,
vf_0D0 to vf_0D8 at `sub_CD9D0`, `sub_CD790` and `sub_CDAC0`; raising a step along its up, vf_210
`sub_D05C0`; and the line and sphere searches over its clump, vf_084 `sub_D16F0` with its atomic
callback `sub_D1990`. The turns' lengths are the float `fabs` of `RwV3dDotProductMacro`, whose
parentheses set the operand loads. The step's move, vf_214 `sub_D0760` (matched 2026-10-01), reads
`type_D05C0` past its first 0x4C bytes (the entity's +0x10C to +0x184, declared there); its
clamps copy the limits through `(RwReal)(RwDouble)` (fld/fstp, not a word copy), and the
animation matrices go back through one pointer local (`var_16C`, slot by first use in the aligned
frame). IDA had not defined it (docs/questions.md); it was placed from symbols.txt.

## `src/recovered/unit_0D48D0.cpp`, the entity handle and jiggle, `0xD48D0`–`0xD5170`

type_D48D0's two methods (setting a handle from an entity and resolving it through the handle
table `dword_4B6A00`) and the entity jiggle (type_D4C80: a random wobble an entity's frame
takes when hit, started by `sub_D4950` and stepped by `sub_D49E0`).

The jiggle's step `sub_D4D00` (a 16-aligned frame) matches with `/Zi`. All match.

## `src/recovered/unit_0D5170.cpp`, the entity manager, `0xD5170`–`0xD6640`

The image's GameEntityManager (named in its warnings): the sixteen entity lists
(type_4B85F8), the nine entity pools (type_4B83A0, the image's GameEntityPool), the handle
table, the dying list, entity memory with priority spawns (`sub_D56D0`) and the per-frame
update of every entity (`sub_D5E20`).

## `src/recovered/unit_0D6640.cpp`, the game loop, `0xD6640`–`0xD99F0`

The game loop (its "GameLoop Init ..." messages): the set-up and the module set-up, the
restart and the shutdown, the main loop and the frame, the pause, the level and section
loading, the section streaming, the level change and the credits, the checkpoint save and
snapshot, and the tick.

The loading screen's drawing (`sub_D9490`) jumps straight to its end (`goto end`): its set-up
is written after the jump, where the compiler drops it but keeps its locals' slots.

## `src/recovered/unit_0D99F0.cpp`, the start-up, `0xD99F0`–`0xD9CF0`

The game's start-up: RenderWare's start (`sub_D99F0`) and stop (`sub_D9BC0`), and the outer
loop that runs the game loop between the front end's screens (`sub_D9C00`).

## `src/recovered/unit_0D9CF0.cpp`, the saves, `0xD9CF0`–`0xDA290`

The memory card (type_D9CF0, a stub on this build) and the save record (type_DA0A0).

## `src/recovered/unit_0DA290.cpp`, the front end, `0xDA290`–`0xDA580`

The front end's world and camera around the shell's screens (`sub_DA290`), and
`sub_DA550` and `sub_DA570`.

## `src/recovered/unit_0DA580.cpp`, the game's font, `0xDA580`–`0xDC400`

type_DA580, a wrapper of an Rt2d font: its creation (the shared brush and the HUD's and the
pad's texture dictionaries), string widths and wrapped heights, plain, wrapped and aligned
text, line breaking over Rt2d's private font layout (include/rw/rt2dfont.h), and the pad
buttons: `$..$` tokens (`sub_DB620`) are looked up (`sub_DBA80`), blanked and drawn as
textured quads in immediate mode (`sub_DBB80`, `sub_DC0D0`), then put back (`sub_DBA10`). The
texture dictionary reader `sub_DC000` ends the unit. The string walking uses the header's
FONT_ inlines and macros, which reproduce the image's slots.

## `src/recovered/unit_0DC400.cpp`, the HUD, `0xDC400`–`0xE8800`

type_DC400, the HUD (dword_4B9190): 151 items of 0x2C0 bytes (quads, images and text,
parented), its fonts, the damage markers, the soldiers' name labels, the radar (`sub_E4030`:
the objectives, along their paths, and the markers), the letterbox, the scoreboard and team
names, the subtitles and the screen flash. It instantiates kujuUI's reference-counted pointer
(type_E8780: the constructors and the null test here, the rest aliased in config/aliases.txt)
and std::vector<RwInt32>'s _Buy and _Xlen.

The frame (`sub_DD180`) and the render (`sub_DF000`) match: the register one step on after an
`if` whose body calls a member is a check compiled out of this build (an empty `if` on a member,
`unk_00`), as elsewhere.

The update (`sub_DD1C0`, with its unwind funclet and handler at `0x300DE0` and `0x300DE8`)
matches. It is a 16-aligned frame, so its slots come in order of first use. Findings:

- Several fields are floats: the items' fade time `unk_2C` and item 80's blink `unk_2B8`, the
  labels' time `unk_20`, the flash's time `unk_1A0AC`, and the vehicle's and turret's headings
  `unk_1A038`/`unk_1A03C`. `unk_1A0C0` is a union, because the script's GetCommandData reads it
  as an int.
- `sub_E08B0` takes a float (the weapon's spread, `sub_11D690`), so its match line is now `...XM@Z`.
- The `fucompp` compares load their right operand first: `0.0f != unk_14` loads the global,
  and `unk_24 != v_14C` loads the local.
- The network player's `unk_2290` (the bomb's time) is read through type_17DBD0_player, and the
  vehicle is a type_3DBC78, whose `+0x920` is `unk_7B0.unk_170`.
- Two compiled-out checks before the vehicle's calls move the registers two steps on.
- The marker loop's `continue` jumps straight to the loop's step.

`sub_E09D0` returns at once; the dead code after its `return` leaves a local above `this` and a switch
temporary below it.

Still binary:

- `sub_E87E0`: std::string's default constructor, out of line for the unit's global strings'
  dynamic initializers (placed with the unit's globals: the HUD texts are `type_4B89B0`, whose
  out-of-line constructor is aliased to it).

The text's out-of-line default constructor (`type_1CB670()`, `sub_E87E0`, after the pointer's members)
is defined here; /OPT:ICF folds every string type's empty one into it.


## `src/recovered/unit_0E87E0.cpp`, the text's default constructor, `0xE87E0`

Split from unit_0DC400 (PLAN M7): the HUD's deferred template functions (`0xE8610`–`0xE87C0`)
end its object, and the text type's (`type_1CB670`) out-of-line empty constructor follows
alone.
## `src/recovered/unit_0E8800.cpp`, the movie player, `0xE8800`–`0xE8F40`

The movie player (include/game/movie.h): the movies' set-up and shutdown, the music's pause
around a movie, the level's opening and closing movies and the credits (in the language's
folder under SHELL\MOVIES\ when the file exists there), the player itself, which stops on
a pad's button, and the shell level behaviour's movie names. Complete.

## `src/recovered/unit_0E8F40.cpp`, the shell manager, `0xE8F40`–`0xEAA60`

type_4B8EF0, the shell manager (dword_4B8EF0; types/type_4B8EF0.h): its constructor and its
base's implicit one (type_E8F90, 54 keys), its destructor, set-up, restart and shutdown (the
HUD it owns, the text manager), its update and render, the loading screen for the game type
and the language's banner, the loading bar, a full-screen raster quad (`sub_EA640`) and the
texture dictionary reader (`sub_EA9C0`). Its dynamic initializer (0x30B500) is placed with the
unit's other globals.

## `src/recovered/unit_0EAA60.cpp`, the text manager, `0xEAA60`–`0xEBF10`

The text manager (game/textmanager.h): console messages (type_EB0A0, from the pool
"textmanager::console") split at a word under 47 characters, queued eight deep and typed out a
character at a time (with `$..$` pad tokens whole and an optional sound) into eight shown
lines that expire by kind; its set-up, restart, shutdown and fonts, the HUD's message items
(`sub_EAB80`) and free text on a camera (`sub_EBAE0`). Complete.

## `src/recovered/unit_0EBF10.cpp`, the clump data plugin, `0xEBF10`–`0xEC6D0`

The game's clump plugin 0x4210 (include/game/clumpdata.h): its registration, constructor,
destructor and copy, the reader of a clump with its tagged matrices, node vectors and ints,
and their accessors, and the placing at a tagged matrix (`sub_EC310`, with `/Zi`). All match.

## `src/recovered/unit_0EC750.cpp`, the performance lookups, `0xEC750`–`0xEE540`

The animation performance tables the scripts and AI look performances up in
(include/game/data.h, types/alfaobject.h): type_ECDA0 (dword_4B92D4, hit and death
performances by the entity's values), type_EC880's value helpers, type_ED340 (dword_4B92FC,
a sorted table searched with partial keys), type_ED850 (dword_4B9300, the scene lookup) and
type_4B9304 (the performance sets: one block of variable-length sets, groups and weighted
choices, drawn at random). Their readers, sorts, compares and frees. Complete.

The hit-and-death lookup's destructor (`type_ECDA0`, `sub_EC6D0`, just before the unit's range) is
defined here: it frees the data, the entries and the data again.

## `src/recovered/unit_0EE540.cpp`, the pad manager, `0xEE540`–`0xEFBC0`

type_4B9308, the pad manager (unk_4B9308, include/game/gameloop.h): four pads of 44 buttons
and a rumble each; its constructor, set-up, update and shutdown over the pad library, button
reads with the stick dead zone and the player's pad, button flags and definitions, and the
rumbles. After it come the mesh particle systems' update and draw (`sub_EF040`, `sub_EFB70`;
game/particles.h). Both match. The draw lights the mesh as a clone, then draws it at the
particles' matrices. The update is a 16-aligned frame. It emits new particles at the definition's
rate: a random offset, velocity and spin, each through `frand_range` with literal bounds, which
take no slots. It ages, moves and spins the live particles, and starts their trails
(`unk_D0`, `unk_F4` read as a float). A product whose left operand is a definition field
(`def->unk_18 * (age - last) * K`) loads the definition pointer first.

## `src/recovered/unit_0EFBC0.cpp`, the decal system, `0xEFBC0`–`0xF06B0`

The decal system (include/game/decals.h): 64 decals in a ring drawn as one RpPTank atomic
(include/rw/rpptank.h, its macros), their set-up, reset, shutdown, update (the texture's
cells and the matrices) and render, and adding one. Complete.


## `src/recovered/unit_0F06B0.cpp`, the particle spawners, `0xF06B0`–`0xF1320`

type_4B9E90, the pool of 128 particle spawners (dword_4B9E90, types/type_4B9E90.h): its
constructor and destructor (with the particle system holder type_F2880's out-of-line
destructor for their unwinding), reset, set-up ("SpawnParticleSpawner"), release, target
(an entity by handle, or an object with a position and direction), the "PT" clump tags,
the emission chance and the attached system's placement; the pool's reset, update,
allocation and the entity's final firing (`sub_F12A0`, "DestroySelf").

The spawner's update `sub_F0C40` (a 16-aligned frame) matches with `/Zi`. All match.

## `src/recovered/unit_0F1320.cpp`, ParticleEditor, `0xF1320`–`0xF25F0`

The RWS behaviour ParticleEditor (types/ParticleEditor.h): its MakeNew, constructor,
destructor, HandleEvents and HandleAttributes (48 commands filling a particle definition,
type_F3130, and naming its three messages), its CSystemCommands matrix reader, the
definition's defaults and the MI thunk (`0xF25E0`, split out of `sub_F23F0`'s range).
RWS::CEventId is 8 bytes (its constructor, 0x12DDB0, clears two words after the record);
a message keeps only the record (CMsgId). Complete.

## `src/recovered/unit_0F25F0.cpp`, the surfaces' particle events, `0xF25F0`–`0xF2880`

The four tables of surface particle events (include/game/surfaceparticles.h: bullet, tank
shell, artillery shell and anti-tank impacts): their reset, free and registration with the
global data loader, and the spawn of a surface's particle system list. The particle
definition moved to types/type_F3130.h; type_F2FF0 (the spawned system) now points at it.
Complete.

## `src/recovered/unit_0F2880.cpp`, the particle systems, `0xF2880`–`0xF4570`

The particle systems (include/game/particles.h, types/type_F2FF0.h): the holder type_F2880's
setter, the definitions file (records hashed by id in an alfahash, found by name as
"<name>.spp"), its texture dictionary and meshes ("<name>.rx1"), the set-up, restart and
shutdown, the two pools a system is built in (placement new) and returned to (its own operator
delete), the live list, the update and the draw (mesh systems first, then sprite systems,
sorted far to near in a tree of 700 nodes), and the system's constructor, destructor, set-up,
update, draw and holder links; the mesh system's set-up (`sub_F3E70`) matches with `/Zi`. All match.

## `src/recovered/unit_0F4570.cpp`, SparkParticle, `0xF4570`–`0xF47F0`

The RWS behaviour SparkParticle (types/SparkParticle.h): its MakeNew, constructor,
destructor, HandleAttributes (command 0 starts the named particle system at the entity's
matrix) and the MI thunk (`0xF47E0`, split out of `sub_F4740`'s range). Its HandleEvents
(`0x15FB30`) and matrix reader (`0xF2360`, ParticleEditor's) are /OPT:ICF folds. Complete.

## `src/recovered/unit_0F47F0.cpp`, the triggered particles, `0xF47F0`–`0xF5F10`

A ParticleTrigger's emitters (types/type_F5740.h): their pools and lists, set-up from the
trigger's settings, children, stop, the schedule of child emissions and the matrices an emitter
and a child's emission start at (the latter a random point in the trigger's sphere, cylinder
or box).

The update (`sub_F4890`, 16-aligned, with EH for its two blasts) matches too: it builds its
blasts' records (type_F4890_blast, a type_67260 with the shake settings after it) on the stack,
so type_67260's padding is dwords (a byte array would bring a /GS cookie the image lacks).
Complete.

## `src/Source/GameCore/pathnodemanager/astarpathfinder.cpp`, the A* path finder, `0xF5F10`–`0xF7BA0`

The unit the assert path names (its outcome logs pass `__FILE__` and `__LINE__`; the source
states the lines with `#line`). It starts right after the triggered particles. The finders
(include/game/astarpathfinder.h): their set-up, restart, shutdown and per-frame step, the
search slots, the search start, the record pool and hash, the open and closed lists, the
expansion over a node's links (with type_3CE1FC's step `sub_F7B00`), the three cost functions,
the heuristic, the two filters and their selectors, and the empty outcome log. The request is
type_169D0. Complete.

## `src/recovered/unit_0F7BA0.cpp`, the path-node manager, `0xF7BA0`–`0xFA9E0`

The path-node graph's manager (include/game/pathnodes.h, types/type_4C00E8.h): the set-up
(with the A* finders'), restart (clearing the nodes' taken and door flags), shutdown, the
graph's clear, release and read (fixing the node and link offsets up and registering the named
nodes), the grid cell of a point, and the occupied alarm nodes' table.

The node search (`sub_F8970`, rings of grid cells nearest first, each cell's nodes through the
request's filter in `sub_F8D30`), the square of cells around a point, the filters' selector by
kind, the cover points' flags and type, and a door node's offsets.

The node filters by kind (height reach through the inline `within_height`, distance, flags,
facing, line of sight through the collision worlds) and the named nodes' registration callback.

Taking an alarm node (`sub_F7BA0`) expands the occupancy entry's constructor, so it is defined
in the class; the table (`dword_4C01A0`) is defined here, which emits its dynamic initializer
and exit function (`0x30B710`, `0x30E5A0`) and the constructor's out-of-line copy. Its owner
branch ends with a compiled-out check (the register one step on). The door-node filter `sub_F9DA0` (a 16-aligned frame) matched 2026-10-01 straight from the
image, with `RtQuatConvertToMatrix`. So did the cover point's corner `sub_FA650` (an `__m128` square root, the link iterator
`type_3CE1FC`, and `var = ((RwReal)fabs(b = (c = f()) - r))` for its fst/fstp pairs). The unit ends with a node's index, the node of an index
and the occupancy entry's constructor (`sub_FA9B0`, out of line for its dynamic initializer).

## `src/recovered/unit_0FA9E0.cpp`, the pickups, `0xFA9E0`–`0xFB7A0`

The pickup entity (types/type_3D94B8.h), derived from `type_3D3548`: its spawns from a
PickupTrigger (the constructor inline) and from settings (the out-of-line constructor, counted
in `dword_4C09A8`), the set-up from the trigger, its overrides (the base's per-frame calls,
landing, the settings-key test, the take-down; `vf_054` and slot 0x74 are /OPT:ICF folds), the
settings table (types/type_4C09B0.h: its constructor for the dynamic initializer, set-up and
restart passes, lookup) and the settings link at +0x3B0 (type_FB6E0).

The set-up from settings (`sub_FADB0`, a 16-aligned frame) matches with `/Zi`; the destructor
(`sub_FAB50`) and scalar deleting destructor (`sub_FAB20`) follow the entity pattern, with a plain
`operator delete` declared beside the placement one. Complete.

## `src/recovered/unit_0FB7A0.cpp`, the RW object extensions, `0xFB7A0`–`0xFC6F0`

The game's extension of RenderWare objects (types/type_3D96F0.h): the plugins that build one in
an atomic's (0x42B0), clump's (0x42B1), frame's (0x42B2), light's (0x42B3, `type_3D96FC`),
material's (0x7A7, `type_3D970C`, streamed) and world's (0x42B5, `type_3D9718`) plugin data,
their getters, registrations, constructors and destructors, the atomic's and clump's accessors,
and the extensions' own methods (set-up, copy, take-down, the node list, the word at +0x08).
IDA had misnamed `sub_24DA70` as `_RpAtomicRegisterPlugin` (the real one is at 0x2D54D0), and
the frame plugin's constructor and destructor as `a3` and `a4`; config/symbols.txt now names
them by address. The derived extensions' constructors inline only with the matching placement
`operator delete` declared.

The set-entity functions (`sub_FB910`, `sub_FBB60`, `sub_FBD80`, `sub_FBF20`) copy the entity's handle
through the handle's by-value setter (`type_3D96F0_14::set_h`) and clear it from a named zero handle in
the `else` block (the zero nearest `ebp`).

## The line test, `0xFC6F0`–`0xFD730` (now in `src/recovered/unit_0FD730.cpp`)

Merged into unit_0FD730 (PLAN M7, 2026-10-03): one object with the player, whose .rdata opens with these functions' constants and puts the aim pass's literals after the player's weapon name tables' texts.

The game's line test `sub_FCAE0`: a segment against the collision worlds of `dword_4E5D30`
(`sub_91F40`) and then their atomics, keeping the nearest hit's point and normal (`sub_FC9F0`,
which also drops hits on surfaces facing away), and the atomic pass's triangle callback
(`sub_FC6F0`, filling a type_FC6F0; its function-scope static `dword_4C1960` keeps the
addresses of its transformed corners), and the sphere pass's triangle callback (`sub_FD700`,
keeping the nearest distance in a type_FD700). `type_91F40` now names its point and normal.

The atomic callback `sub_FC8F0` (a 16-aligned frame, matched with `/Zi`) orthonormalises the
atomic's matrix for the normals. The player's aim pass `sub_FCD90` (an atomic callback over
dword_4C194C, with RenderWare's SSE square roots) matches with `/Zi` too. All match.

## `src/recovered/unit_0FD730.cpp`, the player, `0xFD730`–`0x1154A0`

The player entity type_10F710 (types/type_10F710.h; its set-up's messages call it
"Player::Init()"), derived from `type_3D3548`, 0x2260 bytes: its constructor (with its
unwind funclets and handler) and its small overrides (the AI object at +0x550 and its group
link, the hit points as a fraction at +0x19DC of +0x19E0, the view range, the stance), its
take-down (`vf_230`: the AI, its script object, its weapons' copies, clump, frame and inventory),
building its camera (`sub_FF1A0`, type_3DD948), the player records of `dword_4F4688`, and its
start from its trigger (`sub_FF210`, "Player::SystemStartInit()": the weapons' rounds, the
inventory, its script object and squad; its trigger read as type_712B0_10F710).
Also the hit record (`vf_220`), the stance (`vf_238`), the ally and enemy tests (`vf_248`,
`vf_24C`, `sub_100A50`), the current player's `sub_1014E0`, the weapon change (`sub_100560`) and
the HUD update for its aim (`sub_100880`), weapon selection (`sub_100200`) and its per-frame
update (`vf_038`: the AI, then the weapon's recoil recovering by the stance's settings), and the
aim assist (`sub_100AD0`: slowing the turn over an enemy target, its settings on the player's
trigger).
Also the difficulty's health pick-up multiplier (`sub_104420`), the angle wrap (`sub_104850`),
"ResetCameraZoom" (`sub_104F70`), placing its camera (`vf_244`), `sub_106830`, the stance change
(`sub_104480`), the stealth-kill prompt (`sub_1048E0`) and the aim search's world triangle and
atomic callbacks (`sub_104B30`, `sub_104D00`, on a type_93DF0), leaving the recoil's second
settings (`sub_1062A0`), the inventory kind of a weapon (`sub_1064C0`) and a pick-up's weapon
streaming (`sub_106620`), the pick-up's weapon (`sub_1068A0`), the rounds display (`sub_108B60`)
and the quick select (`sub_108BC0`), "LockPlayerMovement" (`sub_108FF0`) and "SetPlayerState"
(`sub_1090F0`), the forward movement with the bipod stance's animations (`sub_109110`), and the
sideways movement, alone and about a target (`sub_109660`, `sub_1097C0`), the look's pitch and
yaw (`sub_10A330`, `sub_109AE0`), and six movement
states' updates (the on-foot state `sub_10A9D0` with its jump, and `sub_10AD70` to `sub_10B410`:
standing, moving, crouched, a vehicle's seat, a
passenger's, a mounted weapon), two dying states (`sub_10B6F0`, `sub_10B790`) and the spline
state (`sub_10B930`), leaving the forced movement (`sub_10C290`), its footsteps (`sub_10C370`) and
building its model (`sub_10C650`); the crosshair toggle and weapon streaming checks
(`sub_10E880` to `sub_10E930`) and the overrides for its posture, eye matrix and points, weapon
group and attack (`vf_0AC`, `vf_104`, `vf_108`, `vf_110`, `vf_160`, `vf_170`), its flags
(`sub_10F710` to `sub_10F7E0`), its vehicle (`sub_10F810` to `sub_10F8D0`), dismounting
(`sub_10FB70`), its collision ellipsoid (`vf_080`) and the shakes (`sub_110900`, "PlayerShock"
`sub_1109A0`, `sub_110A10`), its weapon's world (`sub_111000`), the checkpoint's copy of its state
(`sub_111040`), its script object (`vf_098`) and sending it along a spline (`vf_234`); the weapon
bob (`sub_111220`), the look spring's step (`sub_112EB0`) and the eased blends (`sub_112F80`,
`sub_112FC0`); leaving a ladder (`sub_114E70`), "PlayerBlewStealth" (`sub_114F50`), an explosion's
shake (`sub_114F90`), its health fraction (`sub_1150A0`) and the room test's collision callbacks
(`sub_115110`, `sub_115130`, `sub_1151B0`) with the room test itself (`sub_115230`), and the
rounds display (`sub_115390`; `sub_EAB80` in unit_0EAA60 takes a third, unused argument, -1 by
default); the step raise on a ladder (`vf_210`), placing it (`vf_0C0`), mounting a ladder
(`sub_114920`) and the vector blend `sub_112F20` (fully parenthesised lines, as a macro expands); climbing a ladder (`sub_114AA0`), the weapon on/off command with the
vehicle's turret (`sub_10E750`), rebuilding the weapon copies (`sub_10D8A0`) and streaming a
weapon's bank (`sub_10DA70`); the weapon's atomics' render callback (`sub_110EC0`; RpAtomic's renderFrame
declared) and the view's bob (`vf_240`); giving it a weapon (`sub_10E9D0`) and a touching entity
(`vf_060`, "BlockingEntity"); a bullet's and an explosion's hit (`vf_064`, `vf_068`; the
bullet's culls the shooter against the camera's frustum planes itself); its movement step
(`vf_040`; the entries at 0x3E25E0 and 0x3E29A0 of two other vtables point at it too); the weapon's sway (`sub_10DBD0`); with `/Zi`, the 16-aligned
levelling of its frame (`sub_FF030`), the crosshair (`sub_100680`) and drawing its clumps
(`sub_110A60`). The
constructor `sub_115470` is type_4C194C's
implicit one, emitted for the global dword_4C194C's dynamic initializer (0x30B770); the unit
defines the global, which emits the initializer and its exit function (0x30E5E0) too.

Entering and leaving a vehicle (`sub_10F900`, `sub_10FBF0`) match: their switch's temporary
first copies the return slot of an inline returning the field directly
(`type_3DBC78::get_unk_1188`). The look spring (`sub_112DA0`) matches through an inlined clamp
whose parameter is assigned in place (`clamp_f`).

The destructor (`sub_FDB30`) and its scalar deleting destructor (`sub_FDB00`) follow the entity
pattern (`~type_10F710() { vf_230(); }`).

Its update (`vf_03C`, `sub_101550`, 16-aligned) matches: its locals take slots in the order of
first use, and its float products keep the image's operand order through `(RwDouble)` casts
(with the named constant `flt_3CE7F4`). Its late step (`vf_04C`, `sub_105B00`) matches too.

Its zoom (`sub_104FF0`), pose (`sub_10C7B0`), lean and recoil (`sub_1116A0`) and collision step
(`vf_044`, `sub_113010`, whose fall damage sends a `type_3DA434` message) match too; the collision
step passes `sub_96EF0` a thirteenth argument, which its definition now takes unused.

Its set-up (`sub_FDC10`) and the pick-up take (`sub_106A60`, which now takes the pick-up as a
`type_3D94B8`) match too.
So do the target search (`sub_108CC0`, over both entity lists), the vehicle seat and exit
states (`sub_10B560`, `sub_10BB30`; the exit transition's times `unk_2154` and `unk_2160` are
floats) and state 12's movement (`sub_113D90`). Every function in the range matches.

The damage message's middle level's id (`type_3DA440::vf_008`, returning 1, `sub_115460`; its vtable
follows the player's) is defined at the end; /OPT:ICF folds the other functions returning 1 into it.

## `src/recovered/unit_1154A0.cpp`, the player's inventory, `0x1154A0`–`0x116310`

type_10F710_21B4 (types/type_10F710.h), the player's inventory: emptying it, the take-down,
the HUD's count of the kind selected (fading with flt_429B40), selecting the next kind and a
kind, using one (a health pack heals, or at full health restarts the music; the grenades and
the like go through the player's `sub_108BC0`), taking a pickup (`sub_1159C0`: health, health
packs by difficulty, rounds scaled by flt_4F2884 through an if/return inline), adding a kind,
whether it has any and the checkpoint's record. Complete; its count accessor is folded
(`/OPT:ICF`) into 0x1E3BF0 and called by that address. Where the unit ends is not proven:
`sub_116310`, which clears the weapons' settings table dword_4C19C0, may open the next one.

## `src/recovered/unit_116310.cpp`, the weapons, `0x116310`–`0x11DB10`

type_10F710_1A48 (types/type_10F710.h), the player's weapon, and its three kinds (type_3DA5A0
the launcher, type_3DA558 the mounted weapon, type_3DA510 the third). Clearing the settings
table dword_4C19C0 (`sub_116310`), the factory (`sub_116490`, pool `new (4)`), set-up and
release, the reload and the magazines, its states and stances (the stance poses from the
model's tagged matrices, `vf_034`), death, the animation callbacks and events (`vf_030`, a
`(RwUInt32)` switch), the recoil, the checkpoint's record (`vf_03C`, `vf_040`) and the
settings' constructor (`sub_11DAB0`, type_4C19C0's, out of line for dword_4C19C0's dynamic
initializer). The base destructor is an in-class virtual inline, so the kinds' compiler-written
destructors reserve its frame but call it (0x116850, aliased with 0x1166D0 for the kinds).

The launcher's firing (`sub_11B040`, 16-aligned) matches: it fills the 0x84-byte record
sub_15F2C0 takes (type_439A48, over the weapon's unk_390) from the settings, some of whose
fields are read there as floats (the `_f` views in type_4C19C0).

The mounted kind's fire (`type_3DA558::vf_018`, `sub_11B9C0`) matches too: its aim blends with
RtSlerp (rw/rtslerp.h), its spread comes from the C library's rand() through `crand`
(game/frand.h), and its light's colour is a 16-aligned four-float (type_140490).

So does the third kind's fire (`type_3DA510::vf_018`, `sub_11C540`: from bone 0x2B73, with a
particle system handed to its projectile; sub_19E9B0 is declared in type_F2FF0.h too, as
particlerender.h needs the D3D headers).

The base fire (`vf_018`, `sub_1176F0`, 16-aligned) matches too: the recoil line (`unk_24_l`) and
its sway, the aimed and unaimed spreads by stance (the `_r` views in type_4C19C0), `fabs_ref`
(game/mathutil.h) and the hand's weapon read through its inline accessors.

The melee strike (`sub_11CF50`) builds the collision context of unit_08AB60 as
type_3D3548::sub_D42D0 does. It ands the sides through `and_sides` (the hit entity's side, its
second argument, computed first) and compares them with the hit entity's through
`get_unk_2C_side` on the left of `==`; its settings' `unk_DC` is copied as a real (`unk_DC_f`).

## `src/recovered/unit_11DB10.cpp`, `unit_11E440.cpp` and `unit_11EE20.cpp`, the projectile generators, `0x11DB10`–`0x1227F0`

type_1227C0 (types/type_1227C0.h), the "PG_" projectile generator (ProjectileGenerator in
its own strings), and its two kinds, each in its own unit: type_11DB10 fires bullets or
projectiles (`0x11DB10`–`0x11E440`, with the base's out-of-line destructor for the
constructor's unwinding), type_11E440 lobs shells on a computed arc (`0x11E440`–`0x11EE20`).
The kinds' compiler-written destructors and their identical `vf_010` are one copy each
(/OPT:ICF), placed in the shells' unit and aliased for the bullets'; the base's inline
virtuals fold into the image's shared empty and constant functions (config/aliases.txt).

The base unit (`0x11EE20`–`0x1227F0`) holds the turret and barrel callbacks, the set-up, the
update (`vf_010`: turret wait, sound replay, bursts, firing stages, targets along a spline),
the aim (first shot and walk, point spread, difficulty-scaled spread), the arc solver
(`sub_1215E0`), the target search, the "PG_" script helpers, the pool (`m_freeGeneratorList`),
the list and the id table (`dword_4CE900`), and the two factories, whose unwinding is one
folded copy. `type_F2880`'s inline constructor is emitted here out of line for the array of
three.

Both factories (`sub_122410`, `sub_1224F0`) now match (213 bytes each,
12 relocations), with their shared 17-byte cleanup and 10-byte EH handler.
Their id getter returns the existing `type_4CE900_00` index/serial record:
its return temporary precedes the list getter's inline local. All functions
in the base unit are matched.

## `src/recovered/unit_1227F0.cpp`, the world render pass, `0x1227F0`–`0x122FB0`

The atomics of the sectors in view (`sub_122D90` walks them with
`RwCameraForAllSectorsInFrustum`, skipping those the PVS hides when asked) are sorted by their
squared distance from the camera into three trees, one per entity render priority
(type_128EB0, game/worldrender.h, a 0x1910-byte object on `sub_122DD0`'s stack reached through
`dword_4CF7C0`), then drawn tree by tree, the second without the depth test. `sub_122820` sets
each atomic's lights first: dark for an unskinned prelit atomic, else the ambient and point
lights of its entity's zone (`type_8E670::sub_8E870`), else the defaults. The sort's
destructor is emitted out of line (`0x122F30`) for `sub_122DD0`'s unwinding.

`type_8F210` (types/vec4.h) is 16-aligned and has no byte array: `sub_122820` keeps one on a
realigned frame without a /GS cookie. `0x2D12E0` is RenderWare's `RpSkinGeometryGetSkin`
(the database's `_RpAtomicGetGeometry`; config/aliases.txt).

## `src/recovered/unit_122FB0.cpp`, the clones, `0x122FB0`–`0x124DC0`

Many copies of a few atomics (game/clones.h). The clump comes from the level stream
(`sub_123440`); each atomic's geometry names its slot in `dword_4CEAE0` with "CloneID" user
data. The clone file (`sub_123280`) is kept whole in `dword_4CEAB0` and read through offsets
from its start: per level section, groups of copies of one clone with the lighting to draw them
with (type_1231F0) and each copy's matrix (type_1243F0). Files from version 0x10001 on can carry
their own vertices and triangle strips, which `sub_124290` puts in vertex buffers and
`sub_1245D0` draws with the vertex shaders "d:\clones.xvu" and "d:\clonesPL.xvu" (D3D, D3DX
and XG calls through the XDK's own headers); otherwise `sub_123FE0` draws each copy through
RenderWare at the copies' frame. The pass (`sub_1234D0`) chooses each group's pass once
(`sub_1239B0`: large clones first, textures whose raster extension flag is set second) and
lights lit groups through the view light and ambient it saves and restores (`sub_123AF0`).

Five RenderWare and CRT functions have names in config/aliases.txt that the database spells
otherwise (the geometry user-data queries, `RpUserDataArrayGetName` folded into
`_rwSListGetBegin`, `malloc`), and the D3D, D3DX and XG functions are aliased by their
decorated names. The Xbox driver's prototypes (rw/rwxbox.h) are the image's calls: neither
RenderWare tree has its headers.

## `src/recovered/unit_124DC0.cpp`, the frame time and the screen fade, `0x124DC0`–`0x125490`

`sub_124DC0` keeps the last ten frame times and reports through the empty debug print whether
their average is under 1/40 or over 1/30 of a second. The fade (game/fade.h): `sub_124EE0`
starts one in or out, `sub_124F70` runs it and calls the function `sub_1252E0` set for its
direction once it ends, and `sub_125060` draws it as a screen-sized triangle fan whose alpha
follows its progress, between saving and restoring the render states it changes (`sub_125320`,
`sub_1253A0`, `sub_125410`).

`sub_125060` divides through RenderWare's `RwCameraGetNearClipPlane`: the macro's parentheses
make VC7.1 load the near plane first (`fdivr`), as the image does.

## `src/recovered/unit_125490.cpp`, the main render, `0x125490`–`0x129200`

The frame (`sub_125F20`, game/render.h): D3D's `ROPZCMPALWAYSREAD` through the XDK's inline
`D3DDevice_SetRenderState` (whose every case the image keeps; config/aliases.txt names the
functions and tables it reaches), the level (`sub_1254D0`: the sky pass over the main worlds,
the level sections' worlds in the passes `sub_129140` begins and ends, the clones, the world
render pass), the effects, RenderWare Studio's entities, the player's own view lit apart
(`sub_126E30`/`sub_127360` put the ambient and four view lights into the world and back), the
motion blur, the fog and far clip fades, the fade and the HUD, with the loading thread
suspended. The passes save and restore the render states they change around the camera update.
`sub_125A50` sets the render settings' defaults (types/RenderTrigger.h holds the settings).

The character shadows: `sub_1279C0` projects a shadow kind's texture ("tankshadow",
"charactershadow") from where a line hits the sections' collision worlds, over the collision
triangles `sub_1283E0` gathers with RenderWare's sector and collision-tree box iterators
(rw/rpcollis.h), into per-kind RwIm3D triangle buffers that `sub_1287F0` draws. The sort tree
of the world render pass (type_128EB0) has its insert and draw here.

Some render settings RenderTrigger stores as ints are read as floats (`dword_4CF4F0`,
`dword_4CF500`, `dword_4CF540`), through casts here, since the trigger's code copies them as
ints. `type_4E5D30`'s middle fields are named (+0x20, +0x24, +0x2C worlds; +0x34 to +0x3C their
flags) with its layout unchanged.


## `src/recovered/unit_129200.cpp`, the Alfa files' resource handler, `0x129200`–`0x129430`

type_3DA848 (types/type_3DA848.h), an RWS::CResourceHandler (rws/cresourcehandler.h: the
image's version has no Update) for "spID_AlfaDataFile" and "spID_AlfaScriptFile": `Load` reads
a data file into a script image (`sub_67E30`) or a script file relocated (kind 3 files'
imports resolved), `UnLoad` releases a kind 3 script file, `IsHandled` names the two types.
Its constructor is out of line for the global instance's (dword_4CF7D4) dynamic initializer,
which stays binary; its vtable is aliased (config/aliases.txt).

## `src/recovered/unit_129430.cpp`, the object holders, `0x129430`–`0x129D60`

The out-of-line methods of the atomic, clump, frame and light holders (types/type_129_base.h):
each holds its object by linking itself (as a type_3D96F0_node) into the object's extension's
holder list (`sub_FC360`, `sub_FC3B0`), hands an entity to it and its parts (the extensions'
setters in unit_0FB7A0), and releases it, destroying it (with RWS::FrameHelper for the frames)
once no holder is left; the clump's release keeps the parts of other entities (its callbacks'
data, type_129940_data). The releases return their results (declared `void` before).

## `src/rws/framework/core/attributehandler/attributehandlerstrfuncs.cpp`, the entity stream functions, `0x129D60`–`0x12A0D0`

RenderWare Studio's chunk handlers that create, update and delete entities from the stream
(rws/strfunc.h's chunk ids), in its anonymous namespace, with the function profiler's handler
(read and ignored) and CAttributeHandler's registration of them. The game calls its hook
`sub_12F0A0` first in the create and delete handlers, will not create a "PathNode"
(`off_429170`), and creates in the handler itself.

## `src/rws/framework/core/attributehandler/cattributehandler.cpp`, the attribute handlers, `0x12A0D0`–`0x12BC90`

The attribute packet's chunk and command iterators and the registry of attribute handlers by
instance id: a `std::map` keyed by RWSGUID (rws/attributehandlermap.h) with no creation-order
list, so Purge and PurgeAll walk the map. Its Dinkumware instantiations follow in the image's
order, with out_of_range's destructor and copy constructor. IsEndChunk and the chunk
iterator's operator-> are folded (/OPT:ICF) into kujuUI's pointer helpers and aliased. The
map's dynamic initializer (0x30B810) and its exit (0x30E610) are placed.

## `src/rws/framework/core/attributehandler/cclassfactory.cpp`, the class factory, `0x12BC90`–`0x12D0A0`

The registry of behaviour classes by name (rws/classfactorymap.h, a function-local static
`std::map` compared with `strcmp`): registration with the linear allocator's rounded size,
MakeNew (which hands the packet to the new handler), and CRegistrar. ClassIsRegistered is not
in the image. The map's _Lrotate, _Rrotate and const_iterator::_Inc are folded with another
map's (0x131770, 0x1E1920, 0x131AD0) and aliased, as is the CRT's `atexit`.

## `src/rws/framework/core/attributehandler/clinearmemorymanager.cpp`, the linear memory manager, `0x12D0A0`–`0x12DC20`

The placement new chunk's handler (sizes the pool from the registered classes' counts),
CreateMemoryPool (inline in rws/clinearmemorymanager.h, emitted here), RequestMemory, and the
pool vector's push_back, insert, _Insert_n, _Buy and _Tidy. Instance, reserve and _Xlen are
the copies in unit_042F40; the pointer `_Uninit_copy` is folded at 0x1B4430 and aliased.

## `src/rws/framework/core/attributehandler/csystemcommands.cpp`, the system commands, `0x12DC20`–`0x12DDB0`

UpdateFrame (the frame's matrix from a CMD_LoadMatrix command; see docs/questions.md on its
name) and the atomic collision properties plugin (rws/atomiccollisionplugin.h): its
constructor, copy, registration and the solid flag's accessors.

## `src/rws/framework/core/eventhandler/ceventhandler.cpp`, the event system, `0x12DDB0`–`0x12EBE0`

RenderWare Studio's event handler without the visualization: CEventId's counts and assignment,
the registry of messages (CRegisteredMsgs, a list headed by a static at 0x4CF82C) and the links
of handlers to them (CLinkedMsg), both from RenderWare free lists, message sending (`_SendMsg`,
with pending unlinks), handler deletion and the RpAtomicToEventHandler plugin. The compiled-out
assertions leave empty `if`s that shift the register rotation (UnRegisterMsg, UnLinkMsg,
LinkMsgToEventHandler). rws/ceventhandler.h keeps the behaviours' names for the id's message
(`p_msgrec`) and a message's id (`CMsgId`).

## `src/rws/framework/core/eventhandler/eventhandlerstrfuncs.cpp`, the test event chunk, `0x12EBE0`–`0x12ECF0`

The stream's test event handler (registers, sends and unregisters a named message) and its
registration.

## `src/rws/framework/core/memoryhandler/memoryhandler.cpp`, the memory handler, `0x12ECF0`–`0x12F1B0`

RenderWare Studio's memory handler as the image's build has it (RWS_DISABLE_MEMORY_CHECKING): the
game's base allocator (the CRT's functions in a critical section, with a busy flag the
asynchronous loader waits for), CMemHandler (rws/cmemhandler.h; its logging blocks leave a copy
of the type in a block of their own), the global operator new and delete and RenderWare's
allocation functions (RWSMalloc is the database's AllocBuffer), plus the game's leak-check stubs
and the entity messages' hook `sub_12F0A0`.

## `src/rws/framework/core/misc/idfromstring.cpp`, `0x12F1B0`–`0x12F200`

GenerateUIntIdFromString, the event registry's name hash.

## `src/rws/framework/core/resourcemanager/cresourcehandler.cpp`, the resource handlers, `0x12F200`–`0x12F8C0`

The handlers' list (a function-local static `std::list`, rws/resourcehandlerlist.h), FindHandler,
OpenAll and CloseAll, and the list's instantiations; its clear is folded at 0x20E1A0 and the
empty Open and Close into pDtor.

## `src/rws/framework/core/resourcemanager/cresourcemanager.cpp`, the resource manager, `0x12F8C0`–`0x130170`

The resource list (CResource, CResourceIterator, rws/cresourcemanager.h), loading through the
handlers (Load sizes the file through the RenderWare file interface), finding, locking and
purging. The game's version has no Update, FindByName or UnLock.

## `src/rws/framework/core/resourcemanager/resourcemanagerstrfunc.cpp`, the asset chunks, `0x130170`–`0x1304B0`

The stream's load, embedded load and unload asset handlers (the game calls its hook first; no
UpdateAsset) and their registration.

## `src/rws/framework/toolkits/rwsplineresource/rwsplineresource.cpp`, `0x1304B0`–`0x130620`

The spline resource handler (an empty asset is a placeholder -1). Its destructor is shared with
the other handlers' (0x130600) and its deleting destructor is the RenderWare handler's
(0x132B00).

## `src/rws/framework/core/streamhandler/streamhandler.cpp`, the stream handler, `0x130620`–`0x131B60`

The chunk handlers' registry (rws/streamhandler.h, a `std::map` by chunk id), the stream's end
test and processing, the version chunk, and the map's instantiations (its _Rrotate and _Dec are
folded with the class factory map's).

## `src/rws/framework/mainloop/logic.cpp`, `0x131B60`–`0x131E80`

The main loop's logic: the running and frozen modes (Frozen is the database's SetFrozenMode) and
the tick messages. No Paused.

## `src/rws/framework/mainloop/mainloop.cpp`, the main loop, `0x131E80`–`0x1323B0`

The game's main loop: its system messages also drive the game loop's level start globals, Reset
restarts the game loop's modules while a level runs, Open makes a sub-raster camera beside the
main one, Poll runs the logic only; DestroyLinearMemoryManager is emitted here.

## `src/rws/framework/mainloop/render.cpp`, `0x1323B0`–`0x132510`

The main loop's render: the two cameras' accessors (the sub-raster camera's are `sub_1323C0` and
`sub_1323E0`: the database names both pairs GetCamera and SetCamera), the render messages and
Poll, which sends them without showing the raster. The empty chunk handler registrations are
folded into sub_19A750.

## `src/rws/framework/startup/attachplugins.cpp` and `registerimageloaders.cpp`, `0x132510`–`0x132690`

The plugin attachment (RenderWare's, RenderWare Studio's and the game's plugins, from a stack
table) and the image loader registration (the Xbox's DDS reader hooked in front of RenderWare's;
the database's j_?DDSTextureRead@...).

## `src/rws/framework/toolkits/debugtools/debugswitches.cpp` and `math/maths.cpp`, `0x132690`–`0x132730`

The debug switches (the database's sub_132690 and sub_1326B0) and DegAngDiff (sub_1326C0).

## `src/rws/framework/toolkits/rwgfxresource/rwgfxresource.cpp`, `0x132730`–`0x132B30`

The RenderWare resource handler: it loads texture dictionaries only, and unloads and recognises
every RenderWare type (the Xbox's MTEffect dictionary too); its scalar deleting destructor is
shared with the other handlers.

## `src/rws/framework/toolkits/time/gftime.cpp`, `0x132B30`–`0x132B50`

Time::GetTime (the database's sub_132B30), GetTickCount's.

## `src/rws/framework/toolkits/world/helpers/`, the world helpers, `0x132B50`–`0x1330B0`, `0x1330B0`–`0x133120`

AtomicHelper's render and collision flags, CameraHelper (the game's near plane is 30, and its
field of view has the HUD's widescreen switch), ClumpHelper (the pre-destroy message and the
clump-wide flag setters), FrameHelper and LightHelper's system commands (the database's
sub_1330B0).

## `src/recovered/unit_1331E0.cpp`, the front end's world and the simple mechanism, `0x1331E0`–`0x1340D0`

`sub_1331E0` makes the front end's empty world, a million units across (its half size is a
constant of the unit's, read from memory). The rest is the simple mechanism (type_3DAC58, the
entity SimpleMechanicTrigger spawns, 0x420 bytes): its spawn (`sub_133230`, whose inline
constructor sets it up with vf_234), the inline overrides its vtable emits, its destructor, its
take-down (vf_230), its path following (vf_03C clamps its place with the `(RwDouble)` compare
the image loads both operands for) and its damage and message handlers.

## `src/recovered/unit_1340D0.cpp`, the soldier, `0x1340D0`–`0x13F9E0`

The soldier (type_3DAFC8, 0x2170 bytes). Head tracking: `sub_1340D0` turns it on or off,
`sub_134160` blends it each frame and runs the procedural track `sub_134320`, which turns the
neck towards the soldier's target point from the head's frame (a quaternion from the axis, to
Euler angles, limited, and back). Its spawn `sub_134B40`; its constructor is defined in the class
but not inlined (its members have destructors), so the spawn's frame keeps room for the
expansion and the out-of-line copy is `sub_134C50`. Its 39 inline overrides follow in
declaration order, then its destructors. The track callback's last parameter is a `bool` (the
callback reads a byte), so the callback type in type_3D3548.h takes one.

Two divisions load their divisor first (vf_17C's `fild; fild; fdivp`, vf_068's `fld; fdivr`):
VC7.1 does that when the divisor is written in parentheses, `a / (b)`.

Every function in the range matches. Idioms first found here:

- `sub_138760` and `vf_134` switch on the weapon kind through a temporary that first takes a
  copy of an uninitialized slot: that slot is the return slot of a direct-return inline getter,
  `switch (unk_3E0.get_unk_04())` (type_15CCE0::get_unk_04), as with
  type_3DBC78::get_unk_1188.
- `vf_170` (the message handler) has twelve bytes of frame that no instruction touches, and the
  case after them starts one register later in the eax/ecx/edx rotation: unreachable statements
  after the 0x76C case's `break`. VC7.1 emits no code for them, but their locals keep slots and
  their register loads still advance the rotation.
- `vf_060` compares with 0 and negates in an inline (`real_abs`, a parameter slot and a result
  temporary), not the C library's `fabs`; the vehicle's `get_unk_113C` keeps its local after
  the `cmp_unk_2C` inline's two.
- The set-up `sub_135430` copies its script object's handle as a struct
  (`get_unk_04_h`, the value loaded before the destination) as type_3D32F8's set-up does, sets
  its second animation's flags through type_7C8D0::set_unk_12 (a word parameter slot), and
  keeps its bone offsets in a 16-aligned type_140490, which realigns the frame.

## `src/recovered/unit_13F9E0.cpp`, math helpers, `0x13F9E0`–`0x141BB0`

Angles, vectors and quaternions after the soldier. `sub_13F9E0` brings an angle into
[-180, 180] with the C++ float `fmod` (whose `fmodf` keeps a float temporary); `sub_13FA50`
normalises a vector and returns its length, its dot product written out rather than through
`RwV3dDotProductMacro` (the macro loads each pair's pointers differently); `sub_13FB00`
normalises a quaternion in double precision.

The rest: a slerp, quaternion products and conversions, a Rodrigues rotation, 4x4 transforms
(type_140490, whose fields are x, y, z and w since the RW vector macros apply to it), line
turns, the barycentric weights `sub_140490` (a bool), look-at matrices, the Euler-angle
matrix `sub_141080`, RenderWare-style vector and point transforms (`sub_141320` to
`sub_141590`, returning their output; `sub_141320` counts its calls in dword_4CFA00) and a
trapezoidal speed profile (`sub_141700`, stepping through `sub_141B10`). Every function in the
range matches.

- `sub_13FFA0` has no `return` although it is declared to return its first argument: eax
  still holds it from the struct copy (C4716, disabled around it).
- A product `m->f * v` or `v * m->f` with a plain local `v` loads `v` first; the image's
  member-first loads are `(m->f) * v`.
- A member passed to the float `sin`/`cos` is copied into a parameter slot; `sub_141080`
  loads each angle straight into the call and rounds through one float temporary, which only
  `(RwReal)(RwDouble)(RwReal)sin((RwDouble)p->x)` reproduces.
- `sub_140490`'s fabs is the C library's (a parameter slot and a call), unlike the soldier's
  inline `real_abs`.
- `_fmod` is aliased to 0x2C7CE4 (libcmt 87fmod.obj, found by tools/lib_scan.py).

## `src/recovered/unit_141BB0.cpp`, the level sections' streaming, `0x141BB0`–`0x143CE0`

The chunk 0x719 (`sub_141BB0` registers `ChunkHandler`, `sub_141BD0` removes it): each chunk
starts with a 0x1C-byte record (type_141C10) whose kind, 1 to 30, picks a handler in
`sub_141C10`; what the handler leaves of the chunk is skipped. The record's key at +0x10 is
built by the key's inline constructor (two `this` temporaries) before the read. Kinds 14, 15
and 30 go to empty handlers that /OPT:ICF folded into the empty debug print `sub_19A750`.
`ChunkHandler` (the database's name) is written as an ordinary function: a file-static one
would mangle the same, but it is dropped whenever no function in the unit calls it.

The handlers: the opaque, alpha, collision and XBSP loaders (one shape; the XBSP's last warning
has no `else` and is logged after every load), the section and global texture dictionaries,
the UV animation dictionary, shared-dictionary worlds, particles and path nodes, the whole-
section load (kind 19, a run of sub-chunks; its first read is part of the loop condition),
the named-object list (`sub_142D70`), six object lists (kinds 20 to 25) and the level
directory, clump bank and animation set; then the texture find callback a BSP read swaps in.
Every function in the range matches.

- RenderWare's `RpWorldStreamRead` and `RwTexDictionaryStreamRead` are called with a second
  argument (the section record's +0x10), so their prototypes take one.
- `sub_142D70`'s names and their length bytes are block-scoped (below the /GS cookie, in
  declaration order: each array, then its byte packed under it); its value goes through
  `type_143DC0::set_unk_2C`, whose `const RwInt32 &` parameter leaves one temporary (the
  inline's local) and no parameter slot. Its constructor (0x143DC0) is aliased.
- The object lists declare their record, object and skip size inside the loop, the record
  after the counter's increment (its key's constructor runs at the declaration); two slot
  layouts occur among the six.
- `sub_143900` keeps a per-level scene-data branch behind `if (0)` (`xor eax, eax; je`).

## `src/recovered/unit_143CE0.cpp`, the spline table and the animated textures, `0x143CE0`–`0x144940`

The spline paths' table (`sub_143CE0` clears it, `sub_143D60` adds one), then the animated
textures (type_143DC0, types/type_143DC0.h): a named animation of up to 16 textures and 32
steps whose materials (type_143D90 entries in a list) get the current step's texture, and
their manager (unk_4E5CC8). The lists and their iterator are modelled as plain structs whose
out-of-line methods keep their addresses as names (the template instantiations at 0x16B810
to 0x16BA10); their destructors, the entries' base's and the base's constructor are aliased
(pDtor, 0x6FCD0). A loop's iterator is declared in the `for` and the element pointer in the
loop body, which puts the iterator nearer `ebp`.

The shared texture dictionary follows (`object`, created by `sub_1446B0`, its textures destroyed
by `sub_1446C0` through `fpCallBack`), and `sub_144740`, RenderWare's
`RwTexDictionaryStreamRead` adapted to read into it (skipping textures it already holds; the
device and native texture reader are RenderWare's static globals, `byte_5200F0` and
`dword_520190`). Every function in the range matches.

## `src/recovered/unit_144940.cpp`, the triggers' bookkeeping, `0x144940`–`0x147080`

A trigger link's setter (type_144940), the set-up and shutdown of the trigger table
(`dword_4CFE30`, 2000 by handle) and its pools (proximity messages, message lists, moved
triggers), the spatial table (unk_4D1DB8) of the triggers that test their surroundings, and the
queue of section loads. `sub_144C00` returns the handle as a full int (its callers store a
word).

The spatial table's cells are 50 by 50 by x and z (`unk_04[x][z]`). While it is sized,
`sub_146360` counts triggers in them; afterwards they hold indices into the cell records
(`type_1461F0`: a list of handle pairs, a changed flag and an in-use flag). `sub_146770` and
`sub_146A00` add and remove a trigger in one cell. `sub_146770` keeps a cell's handles sorted
through a 32-entry `RwInt16` buffer. Its list pointers and loop index are declared in the `for`
and `if` statements, which puts them below the /GS-protected buffer, and `sub_146CD0`'s corner
loop index works the same way. Every function in the range matches (47).

## `src/recovered/unit_147080.cpp`, the vehicles, `0x147080`–`0x155470`

The vehicles' physics bodies (`type_3DBC78_450`, 0x360 bytes, two of them in `type_3DBC78` at
+0x450 and +0x7B0, which `sub_14D2C0` sets up with `sub_147080`) and the vehicle class
`type_3DBC78` (vtable `off_3DBC78`). A body holds 13 contact points, its matrix and, from
+0x2D0, four vertical planes around it. These come from the model's bounding box when the model
has one (`sub_147930`), otherwise from the kind-2 contact points (`sub_147710`). The scripts'
"VehicleSetMaxSpeed" writes the body's top speed `unk_268`, scaled as `sub_147080` scales the
trigger's.

The vehicle's constructor `sub_14C930` fixes its members from its unwinding:
- `type_14D000` at +0x3D4, with no destructor. Its constructor `sub_14D000` is defined in the
  class: it isn't inlined, but the vehicle's constructor still reserves its 13 temporaries.
- The two bodies, each with an empty inline constructor and a destructor folded into pDtor.
- `type_129B10` at +0xB30.
- The guns `type_15B110` at +0xDFC. Their constructor and destructor are in a later unit and
  aliased.
- Two entity handles.
- AIData at +0x11A0, 0x1480 bytes, followed by 0x1C unknown bytes.
- The twelve `type_14D180` records.

The vehicle is 0x2860 bytes. Its factory (`sub_14C820`) reserves the frame of the vehicle's
constructor, defined in the class but not inlined (its out-of-line copy is `sub_14C930`); the
warning reads the trigger's position through a free inline (`trigger_pos`), whose three
expansions trim that reservation to the image's 12 dwords.
`vf_0D8` (0x151CF0) is `fabs(RwV3dDotProduct(arg_0, arg_0))` as written: VC7.1 evaluates the
macro's sum right to left (z first), so no reordering is needed.

## `src/recovered/unit_155470.cpp`, the tank and the flak gun, `0x155470`–`0x15B110`

The tank `type_3DC048` (vtable `off_3DC048`, 0x29B0 bytes) and the flak gun `type_3DC378`
derived from it (vtable `off_3DC378`). The unit also defines the vehicle's bare constructor
`type_3DBC78()` (`sub_1555A0`). It is out of line, since the tank's factory `sub_155470` inlines
the tank's constructor but reserves nothing for the vehicle's. The vehicle's destructor is
defined in its class, because the tank's destructor `sub_155720` reserves its six temporaries.

The tank's destructor `~type_3DC048` is in its class as well: the flak gun's destructor inlines
it. The tank's bare constructor `type_3DC048()` is too, since the flak gun's constructor inlines
it. The key-frame helper `sub_159CB0` reads the UV animation in RenderWare's own layout
(`type_159CB0`, frames at +0x10), not the game's `RtAnimAnimation`. The hatch record's
`unk_10` and `unk_14` are set from the script's raw arguments, so they have integer views.

Resolved below (2026-10-01); historical issue: the flak gun's constructor `sub_15A8C0` (block kept aside, its symbol aliased). Its frame
reserves 16 dwords, the vehicle's bare constructor's expansion, which puts that constructor in
its class. But then the tank's factory `sub_155470` reserves the same 16 dwords, and the image
reserves none there. That is the same kind of question as the vehicle factory's frame
(`sub_14C820`, above).
Tried 2026-10-01: the bare constructor `inline` (declared in the class, defined in unit_155470
after the factory): the flak constructor then matches, but the factory still reserves the 16
dwords; no-code inline calls before the `new` (budget) do not remove it.

## `src/recovered/unit_15B110.cpp`, the vehicles' guns and the decals, `0x15B110`–`0x15C790`

The guns `type_15B110`: four 0xC0-byte `type_15B110_00` records and a -1 after them. Each
record starts with its projectile's model holder (`type_129940`) and holds, at +0x3C, the
`type_67260` settings it hands `sub_15F2C0`. The records' constructor and destructor are defined
in their class; the eh vector iterators take their out-of-line copies (`sub_15B150`,
`sub_15B1C0`).

The decal manager `dword_4D51C0` (`type_4D51C0`) follows: its pool of 50 0x150-byte decals
(`type_15BCC0`), their release (`sub_15BA00`) and allocation (`sub_15C510`, which frees every
fourth unkept decal when full), the builder `sub_15BCC0` and the bilinear UVs `sub_15C610`; and
the debug quads (`sub_15B730`, `dword_4D5170`'s `sub_15BC10`). The decals' colour array is 16-byte
aligned (`type_140490`): the builder's copy source is an aligned local, hence its realigned frame.
The guns' set-up (`sub_15B2A0`) takes each gun's model record through a free inline
(`get_gun_model`), which loads the index before the data.

The next code (0x15C790 on) walks a different pool, 0x80 records of 0x18C bytes at 0x4D53F8,
with their own constructor (0x15C810), so this unit ends there.

## `src/recovered/unit_15C790.cpp`, the NPC weapons' settings, `0x15C790`–`0x15CCE0`

The 128 NPC weapon settings `dword_4D53F8` (types/type_4D53F8.h): their set-up and shutdown
loops (`sub_15C790`, `sub_15C7D0`), the constructor and destructor emitted out of line for the
array's dynamic initializer (0x30BC10, placed) and its destructor thunk `sub_30E860`, each record's clear, readiness and name
registration, lookup by index (`sub_15CB10`) and by name (`sub_15CB40`), and the setters
`CNPCWeaponBehavior` uses. The record embeds a particle holder (`type_F2880`, +0x38) and a
bullets' settings record (`type_67260`, +0x94) that the setters fill. `type_15CCE0` (0x15CCE0)
begins the next unit.

## `src/recovered/unit_15CCE0.cpp`, the soldiers' weapons, `0x15CCE0`–`0x15F1B0`

The soldier's weapon `type_15CCE0` (two in each soldier): its model holder (`type_129940`),
owner handle (`type_D48D0`) and three particle holders; taking up an NPC weapon type
(`sub_15D010`, through the settings' named kind-26 definition and the inline
`definition_model`), putting it away, showing and hiding it, the burst logic (`sub_15D600`,
`sub_15D900`), the shot (`sub_15DE60`: a grenade's arc from the drop settings `dword_4D53E0` to
`dword_4D53F4`, else difficulty-scaled spread), its muzzle and aim, the settings getters and the
weapon-type class tables (`sub_15EFA0`, `sub_15F0A0`, `sub_15EE90`, byte-indexed switches).
Findings: `sqrtf` (math.h's float inline) gives the one-temporary sqrt store; the settings' `unk_7C`
and `unk_164` are written as integers and read as reals (union views); an int-to-bool
conversion (`(bool)x`) sets a byte without the `xor` that `x != 0` emits.

## `src/recovered/unit_15F1B0.cpp`, the projectiles, `0x15F1B0`–`0x166990`

The nine projectile pools `dword_4E19F8` (types/projectile.h: each a kind, a `type_16C2A0`
memory pool and a live list) and their six classes, named for their vtables: the base
`type_3DC7F8` (tracers; kinds 0 and 1), `type_3DC798` (a model; kind 3) and `type_3DC6D8` derived
from it (kind 8), `type_3DC738` (kind 7), `type_3DC858` (kind 4) and the grenade `type_3DC8B8`
(kinds 2, 5, 6). Set-up and shutdown, spawning (`sub_15F2C0`), the tracers' render, the blast
(`sub_1614E0`) and chain reaction, the surface and entity hit effects, and each class's start,
end, gravity and effects. The constant and empty slots are folded by /OPT:ICF (aliases).

Findings: VC7.1 allocates a block's named locals on entering the block and temporaries as met, so
a frame that interleaves named slots and temporaries reflects nested declarations; an in-class
constructor that is never inlined (members with destructors) still reserves its temporaries in the
caller (the factory); `hand_index()` is a direct-return getter beside a result-local one.

The factory `sub_15F590` reserves the temporaries of the kind-4 and grenade constructors,
defined in their classes (their out-of-line copies are `sub_15FCA0` and `sub_15FD30`).
The base step `vf_014` (0x1608F0) compares the sides with the entity's through a
direct-return inline (`get_unk_2C_side`) on the left, and ends with a compiled-out check.
The grenade's step (0x161FC0, 16-aligned) sticks a table-5 grenade to the nearest bone or
frame of what it hits (`unk_13C` to `unk_144`, `unk_160`, `unk_1A0`), bounces the others,
alerts the entities near where it will land and blows up when its fuse is over. The atomics'
callback `sub_1660C0` suppresses soldiers of another side along the line, tests each entity by
its mode and, for a sphere, builds a collision-search context (sub_95030's). Every function in
the range matches.


## `src/recovered/unit_166990.cpp`, the mounted weapon, `0x166990`–`0x16B810`

`type_3DC9B0` (the image's CMountedWeapon entity; all matched) and its settings
`type_4E1B70` (`sub_166990`; 58 functions with it): spawning from a trigger (`sub_1669B0`), set-up (`sub_166FA0`; the
owner is its own trigger, a vehicle's or an animated background's, `unk_498` 0 to 2), its
virtuals (step, aim, render, messages `vf_170`, model keys `vf_058`), mounting and dismounting
for players (`sub_168820`, `sub_168A90`) and NPCs (`sub_168E10`, `sub_169000`), firing
(`sub_169380`: a function-static bullet record, a random spread, recoil, "OutOfAmmo"), the NPC
gunner's aim and fire decision (`sub_16AAE0`), its limits and ammunition from the owning trigger
unless -1, the list lookup by key (`sub_16A340`, entity list 13) and kind 4's pose-key animation
callback (`sub_16B0C0`, as `type_3DBC78`'s `sub_155D30`). Last comes the settings' implicit default
constructor (`0x16B740`, its six names' constructors), which the unit's initializer at
`0x30BC70` runs over `dword_4E1B70[7]`.

Findings: a float conditional whose picked operand goes through the FPU (`fld`/`fstp` into the
temporary) is `(RwReal)(RwDouble)x` on each operand, where plain operands copy with integer moves
(`sub_16B5C0`); an out-parameter matrix fill with no `eax` result is a `void f(RwMatrix *)`, which
callers' `RwMatrix m = f();` could not have produced (`sub_16A030`); `sub_16A990` moved from
`type_3D3548` to this class (its body reads the weapon's limits), and AIData's caller casts.

## `src/recovered/unit_16B810.cpp`, the intrusive lists, `0x16B810`–`0x16BA60`

The lists `type_16B810` (a head, a sentinel's link and a tail), their iterator `type_16B900` and
their nodes' unlink (`type_6FCD0::sub_16BA30`), all out of line in a unit of their own directly
after the mounted weapon's; the animated textures (unit_143CE0) use them. Both destructors are
pDtor (aliases). 11 functions, all matched.

## `src/recovered/unit_16BA60.cpp`, the debug text, `0x16BA60`–`0x16C280`

The debug text (game/debugtext.h): set-up and shutdown with RenderWare's Atari charset
(`RtCharsetCreate` with `foreGround`/`backGround`), a byte buffer of queued strings with their
positions (`sub_16BB00`), and one draw of the queue (`sub_16BBA0`: saves and restores eight render
states, draws each string as Im2D triangle lists built by `sub_16BE20`, a trimmed copy of the
toolkit's `CharsetProcessString` with six vertices a glyph and trivial rejection only). The debug
printf `sub_16C220` (`vsprintf` then `printf("%s%s", buf, "\n")`, /GS) closes the run; it may
be a unit of its own (its only literals are pooled). 6 functions, all matched.

Findings: `climb_names.py` only renames `var_<slot>` locals, so descriptive names must become
slot names before a climb.

## `src/recovered/unit_16C280.cpp`, the free-list pools, `0x16C280`–`0x16C800`

`type_16C2A0` (types/alfasched.h): fixed-size elements in one block, each with a trailing word
that links the free ones and, in a taken element, holds the guard `0x2F2F2F2F` unless flag 2 is
set (flag 1: the block is not its own). Set-up with alignment padding (`sub_16C2C0`), take,
return (by pointer or index), membership, and the shutdown's "Some elements were not freed"
warning. 14 functions, all matched.

Findings: an empty `if` advances VC7.1's register rotation by its condition's register loads,
not by one (`sub_16C710` needs two one-load conditions, `if (!unk_04) {}` and `if (!unk_0C)
{}`; `if (!arg_0)` loads nothing and a call emits code); set-up and shutdown were declared as
returning the pool but never set `eax`, and their flags are `bool` (`movzx`, not `movsx`).

## `src/recovered/unit_16C800.cpp`, the pack file, `0x16C800`–`0x16D220`

The pack file (game/pak.h): the 32-bit FNV-1 string hash `sub_16C800` (used elsewhere), its 64-bit
path hash `sub_16C880` ('/' read as '\', stopping at ';'), the set-up `sub_16C940` that reads
`d:\COD.PAK`'s header and directory into `dword_4E22A8` and points RenderWare's file interface
at its own fopen, fclose, fread, fgets, fseek, feof and fexist (open pack files are the handles
1 to 4; others go to the saved interface), and an open pack file's size (`sub_16D200`). 12
functions, all matched.

Findings: the lookup passes FNV-1's 64-bit basis with its halves swapped (0x84222325CBF29CE4); a
`RwUInt64` local placed straight after a 4-byte one is 8-aligned, leaving a gap only the names
reproduce; fseek's offset is a `long`, declared as `RwFileSeekOffset` in rw/osintf.h.

## `src/recovered/unit_16D220.cpp`, the profiler, `0x16D220`–`0x16D8C0`

The profiler (game/profiler.h): 49 timing sections (`dword_4E23E8`, 0x5C bytes: this frame's and
the last frame's counters, a name and a shown flag), named by `sub_16D3A0` ("Logic", "Render",
... "Clones"; indices 35 to 48 stay unnamed), opened and closed around work by `sub_16D7F0` and
`sub_16D850` (which also run the render timers in `.data` at `dword_42A5B8`), and the frame's own
counters. The shutdown's per-section call is pDtor (alias). 14 functions, all matched.

## `src/recovered/unit_16D8C0.cpp`, the clump utilities, `0x16D8C0`–`0x16E9C0`

The clump utilities (game/clumputil.h), mostly RenderWare iterators with a context on the
caller's stack: render parts shown or hidden by a geometry's string user data or a mask
(`sub_16D8C0`, `sub_16E080`, `sub_16E0C0`), atomics found by name, frames by hierarchy id,
the hierarchy frame (`GetHierarchyFrameRecurse`), the first atomic (`Clump_FindFirstAtomic`,
`Clump_CaptureFirstAtomic`), pruning a clump's frames (`sub_16D9A0`, whose id-based pruning
is compiled out as `if (0)`), bounding spheres, re-parenting atomics onto another clump's
hierarchy, a world's leftover atomics, clumps and lights, textures still referenced,
triangle normals and a file name without its extension. 38 functions, all matched.

Findings: calls that pass a dword to the byte-parameter collision setters (`sub_FB990`,
`sub_FBBE0`) saw an int prototype (declared as int overloads in game/clumputil.h);
RpUserDataArrayGetString is folded with GetInt at 0x2E48A0 (alias); RpGeometry reaches its
mesh header at +0x54 (rw/rpatomic.h), read through RW's first-mesh expression
(`rpMeshHeaderGetFirstMesh`, rw/rpmesh.h).

## `src/recovered/unit_16E9C0.cpp`, the clump banks, `0x16E9C0`–`0x16F2C0`

The clump banks (game/clumpbank.h): `cbank_NN.bin` files of clumps by key, one bank at a time
(`dword_4E51C4`) in a heap of its own (`dword_4E51B8`: base, used, size), with the table of the
keys it made (`dword_4E51D0[64]`, defined here; its initializer at `0x30BCB0` runs the keys'
constructors) so that `sub_16EFD0` unloads them kind by kind (6, 7 with its texture dictionary,
then 3). Loads are synchronous (`sub_16E9E0`, `sub_16EAB0`) or queued on the loading thread
(`sub_16EEC0`). 17 functions, all matched.

Findings: a `this` temporary allocated after a record's constructor temporaries is an inline
method's, not a block local (`type_16EAE0_obj_10::set_unk_0C`).

## `src/recovered/unit_16F2C0.cpp`, the weapon banks, `0x16F2C0`–`0x16FF90`

The weapon banks (game/weaponbank.h): `WPNBANK\0_25` and `26_50\wbank_NN.bin`, the clump banks'
scheme for three slots at once, each with its loaded and requested bank, heap, state (a count
in the high half, a load in progress in the low) and table of eight keys (`dword_4E5528[3][8]`,
defined here; its initializer at `0x30BD00`). 21 functions, all matched.

Findings: constants substituted into /Ob1 inlines stay unfolded when an operation needs them in
a register (`make_bank_state(0, 1)` gives `xor; shl 0x10; add 1`), and a compare keeps its
substituted 0 in a register only when the parameter is narrower than int
(`clear_bank_state(slot, RwInt16 count)`); an inline setter with the value as a substituted
argument computes the store address first (`set_bank_size`, sub_16FF00).

## `src/recovered/unit_16FF90.cpp`, the objectives, `0x16FF90`–`0x171DC0`

The objectives (game/objectives.h): the level script trigger that owns them (`dword_4E5690`, a
type_144940 defined here, "ObjectiveManager initialized twice" when a second registers), fifteen
objective records (`dword_4E56A0`, 0x58 bytes, defined here with their implicit constructor and
destructor, a list linked by byte index from `byte_4E564D`) added, removed and flagged by key,
their five script messages (activate, complete, fail, counter up and down, registered through
sub_6BAE0 with handlers here), nag timers, pulses, targets (a trigger at +0x2C, an entity at
+0x38, a spline path) and fifteen markers (`dword_4E5654`). The records' list for the HUD is a
`std::vector<RwInt32>` (sub_1708E0), whose push_back, insert and _Insert_n instantiations close
the unit. 40 functions, all matched.

Findings: the record's layout moved from type_DC400.h (its +0x2C is a type_144940, which the
initializer constructs, so the HUD reads the target through `unk_2C.unk_08_obj`); the script
command SetObjectiveNagTimer saw an int prototype for sub_170FD0, whose definition takes a float.

## `src/recovered/unit_171DC0.cpp`, the world manager, `0x171DC0`–`0x174950`

The world manager (game/worldmgr.h): the four section slots (`dword_4E5D30`, type_4E5D30, with
its constructor here, which the initializers at `0x30BE00` and `0x30BE30` run) and the global
section (`unk_4E5CD8`, slot `0x7FFF`), each holding opaque, alpha, collision and extra worlds, a
texture dictionary and an arena; the default world, the skybox worlds, shared.txd, the UV
animation dictionary, the four directional lights and the level's light list (through the light
extensions' +0x1C/+0x20 links). It sets up and shuts down the worlds and the clump and weapon
banks' heaps, places clumps, atomics and lights in the world whose section box holds them
(nearest centre wins; a trigger's entity with flag 10 of +0x24 goes to the global section),
registers streamed worlds and dictionaries in slots, unloads a slot under the section lock, and
keeps the entity handle table `dword_4E5D1C`. 60 functions, all matched.

Findings: sub_173100 is an atomic callback (not a clump one); sub_1739C0 copies the lights'
frames' `at` vectors, not their positions; sub_173BE0 works out world-kind flags into a copy it
then drops; the slot flags +0x40 and dictionary +0x30 are now typed; the skybox and dictionary
setters return nothing (their callers' prototypes said otherwise); RpWorldGetFlags expands
through a result local, so it is an inline here; sub_1747D0's buffer is 0x100 bytes.

## `src/recovered/unit_174950.cpp`, the player's camera, `0x174950`–`0x175FC0`

The player's camera entity (types/type_3DD948.h), built by the player's set-up (sub_174A70) in
entity memory: its set-up (the trigger's camera object and scripts, a collision atomic, its
performance player), its modes (follow, head bone, glide to a matrix with "IHaveArrived", spline
path), its shake ("CameraShake") and its render step, which hands the render camera's matrix to
the sway. Also the index-sound table's reset (sub_174950). 18 functions, all matched.

Findings: the script's type_62A60 is the same object; the player trigger reaches +0x468 (its
camera object's and scripts' keys); vf_03C's late locals are block-scoped (their slots follow the
quaternion macro's), and a compiled-out check before its tail shifts the registers; the set-up
tests an inline returning 0 (`xor edx, edx; jne`).

## `src/recovered/unit_175FC0.cpp`, the camera sway, `0x175FC0`–`0x176B30`

The camera sway (types/type_4E5E50.h, unk_4E5E50): the effects table dword_429EB8 (shake, sway,
drift), two noises per effect on the view's pitch and yaw, and the pad rumble with them. 11
functions, all matched. The rumble's scale is multiplied as a double (`(RwDouble)flt_42A038`,
which gives `fild; fmulp` instead of `fimul`).

## `src/recovered/unit_176B30.cpp`, the sway's noise, `0x176B30`–`0x176E50`

The sway's clock and Ken Perlin's noise1 (types/type_4E6F20.h), with his declarations, which
reproduce the frame; and the noise's octave sum (type_176040::sub_176D70). 6 functions, all
matched.

## `src/recovered/unit_176E50.cpp`, the gimp, `0x176E50`–`0x17C3E0`

The gimp (types/type_3DDB98.h; the strings after its vtable name it "GimpEntity"), the entity a
GimpTrigger spawns: a scripted civilian-like figure built on the soldier's model code. Its
set-up, logic and render steps, hit handlers, message handler, weapon hand and clumps are the
soldier's (type_3DAFC8, unit_1340D0) with the gimp's fields, and without the soldier's AI
object, grenade and mounted weapon. It also follows spline paths or a goto point
(sub_179530), flies when sent flying, and loses its head to a head shot. 78 functions, all
matched.

Findings: the soldier's matched sources were the template for nearly every function, several
matching on the first compile; the trigger's command 8 (unk_120) is stored as raw bits and read as
the gimp's health float; vf_068 needed the parenthesised divisor `a / (p->x)` (the name search
fails while any code differs, so diff first); a 4-byte handle stored value-first is a struct
copy (`unk_150_h = unk_384_h`); nested-block locals and named clump locals fixed the rest of the
frames.

## `src/recovered/unit_17C3E0.cpp`, the help messages, `0x17C3E0`–`0x17CA70`

The script's help messages (game/helpmessages.h): up to 32 records (`dword_4E6F38`, constructed
by the initializer at 0x30BEF0) keyed by their text objects, linked from the one shown
(`dword_4E6F28`), shown first or queued last; a killed message fades out over
`dword_4B8F80` after `dword_4B8F84`, and is drawn centred in its box in the HUD's font. 11
functions, all matched. sub_17C500 returns whether it found a slot (functions.h said void).

## `src/recovered/unit_17CA70.cpp`, the shrimps, `0x17CA70`–`0x17D590`

The shrimps (types/type_3DDE70.h, type_17CC40.h): each ShrimpTrigger's type_17CC40 keeps a list
of shrimps from the pool `dword_4E7244` ("Shrimps", 500 of 16 bytes) that swim along its spline
path at its speed (turning back, wrapping or ending by the path's mode) and are drawn as clones
of its model's first atomic, facing along the path, in their own alpha-tested pass; the trigger
adds one by chance (unk_DC out of 100). Its spawn is a bare entity class (off_3DDE70) whose
destructor is implicit (it does not reset the vtable pointer). 18 functions, all matched.

## `src/recovered/unit_17D590.cpp`, the pulse zones, `0x17D590`–`0x17E680`

The pulse zones (types/type_17DB90.h): each PulseZoneTrigger's zone keeps up to 16 entities of
its trigger's side and, every `unk_CC` frames, runs its effect on them `unk_C8` times (0: for
ever). The effects by kind (`dword_42A4B4`): damage (a blow from the zone; the local player's is
also sent to the multiplayer manager, game/netmsg.h), a three-second charge whose next effect is
an explosion (sound, particles, a blast and a view shake), holding players, and none (kind 3);
leaving runs the exit effect by kind (`dword_42A4C4`: only kind 2's, letting the player go). The
manager keeps the zones in a pool (`dword_4E7378`, "m_freePulseZoneList", whose initializer is
0x30BF60), a list (`dword_4E7374`, linked through unk_50) and a handle table (`dword_4E7268`, slot
and serial, so a stale handle finds nothing). 30 functions, all matched.

## `src/recovered/unit_17E680.cpp`, the gimp vehicles, `0x17E680`–`0x183130`

The gimp vehicles (types/type_3DE0E0.h). Type 0 (type_3DE0E0) is a type_3D3548 with the tank's
guns (type_15B110) whose set-up (sub_17EA70) follows the tank's, and whose procedural track
(sub_17F620, turning its track and tilt bones through sub_17FC00) is the tank's too. Its step
(vf_03C) drives it to its goto point or along its spline path (sub_1808D0 steers), standing it on the
ground under the point; its hits (vf_064, placed last) wear its armour before its health. Type 1
(type_3DE350, from sub_180CF0) adds a turret and barrel its track turns, aims them at its target
(sub_181A90, sub_181D20) and fires its guns (vf_254, with the main gun's shot in sub_182990). The
database misses vf_254 (0x181F60) and sub_182990; both were added to `symbols.txt` and `splits.txt`
by hand. Several slots are folded (/OPT:ICF) with the tank's or with empty functions
(config/aliases.txt), and the tank's vf_058 is folded into type 0's. 51 functions, all matched.

## `src/recovered/unit_183130.cpp`, the debug menu, `0x183130`–`0x185C30`

The debug menu (game/debugmenu.h, `unk_4E73A8`): a tree of groups and items on the RenderWare heap,
each item showing a variable by its kind (switches, integers, bytes, floats with their steps, angles
in radians or degrees, colour channels, functions), driven from the pad and drawn with the HUD's font
and its own render states; and the performance display (`dword_4E73F0`) over the profiler's render
timers (`dword_42A598`, whose tail is profiler.h's type_42A5B8): their shares of a frame as text and
as line graphs (Im2D polylines), the highest four, all switched from the menu. 27 functions, all
matched.

## `src/recovered/unit_185C30.cpp`, the waiting screens and message boxes, `0x185C30`–`0x188380`

The front end's message boxes (game/waitscreen.h): two boxes (`dword_4EBE00`) opened by message number
through the openers of `off_42B518`, stepped from the pad (lines, choices with their change and select
callbacks, accept and back) and drawn as Im2D strips with the HUD's font; the pad bindings held while
one is open; and the waiting screens that run their own frames around a caller's draw while the game
saves or looks for the memory card. All 32 functions match. sub_185D50 and sub_186140 return at
once on this build but keep their retry loops, compiled after the return: those test a `const` flag
declared there (its slot set by its name's bucket), after a compiled-out check that moves the
registers one step. sub_186140's name buffer and its scalars are scoped to the block that uses them,
which puts the /GS cookie where the image has it.

## `src/recovered/unit_188380.cpp`, the message box and the messages, `0x188380`–`0x18F3C0`

The message box itself (`type_4EBE00`, game/waitscreen.h): its constructor and reset, its lines and
their choices, sizing (sub_1884B0) and layout (sub_1889C0: the corners about the boxes' centre, the
heading's backdrop and twelve frame pieces as Im2D quads, the 512x448 layout scaled to the screen by
two `const RwReal &` inlines called with `+x`, whose argument copies the image shows); the line draw;
the message strings loader (sub_18A890, a CSV of tags and a column per language, read in two passes
through a table of reader functions and cursors; sub_18AF40 names the memory card's 77 tags in
dword_4F2370); the memory card messages' openers and the slot menu; the not enough free blocks screen
(which can launch the dashboard's memory page); the Xbox Live messages and options; and the in-game
pause menu, its options menu (turn speed, control set, subtitles, invert aim, controller shake, hint
messages, friendly fire block, aim assist; sub_18E380 applies them) and the quit and restart questions.
The 45 functions from 0x18B700 were not functions in IDA and were added by hand to config/symbols.txt
and config/splits.txt (docs/questions.md). Every function matched. The next code, from 0x18F3C0, is
type_3DF8D8's (the in-game text objects).

## `src/recovered/unit_18F3C0.cpp`, the GodAsset objects, `0x18F3C0`–`0x198390`

RenderWare Studio's GodAssets (types/type_3DF8D8.h): the 16-byte base (`type_3DF8D8_base`: its key,
its flags word, three virtuals: read from a stream, release, kind) and its views, and every kind's
class in address order. Each constructor installs its vtable (aliased in config/aliases.txt), each
handler reads its typed references (the kind in the top five bits, through inlines whose constant
arguments are not folded) and registers what they name (sub_198900) with a callback. The kinds: the
variables and their registrations, texture dictionaries, models (clumps, bounds, the model object
that reads its dictionaries and models embedded in the stream into an arena, sub_190B20), UV
animation dictionaries, the soldier, vehicle, weapon and pickup settings, the sounds (basic, random,
sequence, index and streamed music, their lists and the sequence slots of dword_4B1CA0), the
performance sets, the AI points (an entity's, a trigger's or a path node's position and direction,
the node's through RtQuatConvertToMatrix), the mounted weapons' animations, the localised strings
(one reference per language; `#` in the text takes a number), the index-sound table
(dword_4E5E40), and the kinds 0x31 to 0x3B that fill it. 210 functions, all matched. The next
code, from 0x198390, is the GodAsset manager.

## `src/recovered/unit_192BE0.cpp`, the music streams and the GodAsset types after them, `0x192BE0`–

Split from `unit_18F3C0.cpp`. Evidence: the stream name prefix `dword_42B690` ("XBX_", a global, its literal first in the object) and the file-name table, a static of `type_44E8D8_248::vf_00C` (its literals come out with that function, before its "%s%s%s"), sit in the image after the vtables of the classes up to `type_3DFB4C` and of `type_44E8D8_248` itself, whose constructor (0x192B20) stays in the first object; this object starts at `vf_00C` (0x192BE0).

## `src/recovered/unit_198390.cpp`, the GodAsset manager, `0x198390`–`0x19AAB0`

The GodAsset manager (game/godassetmanager.h, named from its own strings): its file statics, each
with its own dynamic initializer (the table of objects by key `dword_4F2728`, a file-info table
`dword_4F26D4`, `m_requestPool`, `m_fileInfoPool`, `GodAssetStringPool` and the six
`m_freeGodAssetPools`); setting it up and shutting it down; a name's key (the quoted, upper-cased
name's odd and even characters FNV-hashed apart, sub_198A20); asking for an object (sub_198900:
answered at once, marked wanted, or made and queued as a request); reading objects from a stream
and answering their requests (sub_198C70, sub_198D30); freeing them back to their pools; the
factory (sub_199010: a 59-kind switch that builds each object in its pool slot with the GodAsset
base's placement pair, `sub_6CCF0` and the empty `sub_19A750`, and counts each kind); and the empty
debug print `sub_19A750` itself (5 bytes in the signed image; config/symbols.txt had the modified
dump's 16). 35 functions, all matched. The next code, from 0x19AAB0, sets the difficulty.

## `src/recovered/unit_19AAB0.cpp`, the save state, `0x19AAB0`–`0x19B0F0`

The game's save state (game/savestate.h, game/data.h's `type_4F28F0`): the difficulty taken from
the state and its twelve multiplier arrays reset (sub_19AAB0); the save record's checksum (its 200
bytes' sum less the checksum's own, 0 for a blank "KNLB" record) and its player block's copy of
the player's state; the state's defaults ("Player", difficulty 1) and its one-time set-up from the
shell's settings (`dword_4F45F8`: language, player, pad, difficulty and profile name, through
free inline setters); and the level, level name, difficulty and language accessors. Two functions
keep unused slots above their inlines' temporaries (declared as unused locals). 11 functions, all
matched. The next code, from 0x19B0F0, sets up the levels' tables.

## `src/recovered/unit_19B0F0.cpp`, the control sets' tables and small helpers, `0x19B0F0`–`0x19BF20`

A run of small helpers with no one subject (game/levels.h, game/clones.h): the five control sets'
button tables' set-up (each row flagged when it drives button 5; the pads' library calls it); the assert trap ("RWASSERT TRAP", then a spin);
the light scales object (`dword_4F30A8`, its constructor) and the scaling of a light list's colours
by it (sub_19B270, whose clamps convert the kept value as from a double); the empty sub_19B650;
the full-screen textured quad (sub_19B6D0: four render states saved, each stage's addressing set
through the Xbox driver's texture stage cache, reconstructed here as `RwXbSetCachedTextureStageState`
in rw/rwxbox.h) and the back buffer drawn over itself with it; a performance-counter stopwatch;
the double camera clear; a debug-print wrapper; a substring replace and two language patches (a
"German" rename and four Italian subtitles given in French); a "$ud$" token test; the connected
controllers' count; and a language's index. 19 functions, all matched. The next code, from
0x19BF20, is the Xbox Live manager (`dword_4F3130`).

## `src/recovered/unit_19BF20.cpp`, the Xbox Live manager, `0x19BF20`–`0x19CB20`

The Xbox Live manager (game/xboxlive.h, `dword_4F3130`, defined here with its implicit destructor):
the UIX engine's sign-in and friends features (uix.h's `ILiveEngine` inlines), the result of each
(a switch over the XONLINE errors), appearing online or offline (the engine's notification
state), signing out, and the pause the sign-out message takes. It implements a six-slot interface
of the engine's (`type_3E0418`, `novtable`; three slots return `E_NOTIMPL` and are folded) and
hands the engine a font renderer over an XFONT (`ITitleFontRenderer`) and an audio plugin that
plays nothing (`ITitleAudioPlugin`). The uix, xonline and XFONT functions it calls are located by
tools/lib_scan.py or by their jump stubs (config/aliases.txt). Including the XDK's headers here
needed game/startup.h's, xbox/xapi.h's and types/soundbank.h's own declarations of XDK functions
guarded. 32 functions, all matched. The next code, from 0x19CB20, is the movie player.

## `src/recovered/unit_19CB20.cpp`, the Xbox platform and the movies' Bink side, `0x19CB20`–`0x19D920`

The Xbox platform (game/platform.h) and the movie object's Bink methods (game/movie.h): the Bink
player (`dword_4F39A8`: a movie opened from d: with its sound tracks at half volume and the
screen's scale to it, and closed after a vertical blank), RenderWare's file system on d:, a file
read ahead, the DDS texture read callback, the gamma ramp, the frame's end (the Live friends
feature started or ended, the back buffer drawn over itself once, the render states kept around
it), the game's entry (the launch data, the save state, the video configuration for the
television, the devices, then the outer loop), and the movie object's open, close, step, draw,
pause, wait and volume. The Bink functions are named by their use (include/bink/bink.h) and placed
by config/aliases.txt. All 28 functions matched; sub_19D290 and sub_19D2D0 set and restore the FPU
control word with the original's inline assembly (allowed since 2026-10-01: docs/PLAN.md). The next code, from 0x19D920, is the pads' library.

## `src/recovered/unit_19D920.cpp`, the pads' library, `0x19D920`–`0x19E500`

The pads' library under the pad manager (game/padlib.h): the four controllers' XInput records
(`dword_4F4638`: this frame's and the last frame's state, the capabilities, the handle, the control
set's bindings and the rumble feedback), their taking out and putting in, the sticks' axes from -1
to 1 with the dead zone, an input's value on being pressed, held or let go, the bindings read into
the manager's pads, the rumble and its run-down, and the queries between actions and inputs.
15 functions matched; sub_19DF40 (the set-up) is not yet: its loop takes its registers one step on
from every shape tried. The next code, from 0x19E500, loads the particles' shaders.

## `src/recovered/unit_19E500.cpp`, the particle renderer, `0x19E500`–`0x1A16D0`

The sprite systems' renderer (game/particlerender.h). It holds the vertex shader ("d:\particle.xvu") and
the four sets of eight spinning matrices, with the random offsets. A system's shader state
(type_19EC70) is filled from its definition, with its colours brightened and scaled. The vertex buffer
gives four corners to each particle. A frame's set-up builds the clip planes, the view matrix and three
projections, the corner constants, the render states and stage 0's blending. The draw pushes the
constants through one buffer, then draws the live quads multisampled.

All 23 functions matched. The frame's set-up needs the XDK's D3DDevice_SetTextureStageState inline,
wrapped in the cache test (RwXbSetTextureStageStateIfChanged, rw/rwxbox.h). Its constants and the
draw's matrices sit on 16-byte slots (type_140490, XGMATRIX). The next code, from 0x1A16D0, is the
save images' holder (a constructor setting "d:\saveimage.xbx").

## `src/recovered/unit_1A16D0.cpp`, the profiles' save files, `0x1A16D0`–`0x1A26F0`

The profiles' saves (game/profiles.h). There are four slots (`dword_4F5DC0`, type_4F5DC0: the index, whether
the slot is in use, the save record and whether it is the chosen one). Each slot is kept as
"DANTE<n>.dat" in a save game named "Profile <n>: <name>" on "u:\". The file has a 0x18-byte header
holding its size and signature, and "saveimage.xbx" is copied in as the save's image. The unit
covers the global that sets the paths up (type_4F6170's constructor), the slots' clearing, the
search for save games, the save and the load, which check the size and the signature, and a slot's
name. It also covers the wide-name conversions, the slots' copy in and out of the launch data, and
the damaged-profile message box.

All 15 functions matched. One of them, `sub_1A2580` (the box's opener, message 0x2D), is missing
from the database. It sat inside `sub_1A24D0`'s range and was added to `symbols.txt` and
`splits.txt` by hand (docs/questions.md). The next code, from 0x1A26F0, loads the Xbox strings
("shell\hud\XboxStrings.csv") and starts the sound.

## `src/recovered/unit_1A26F0.cpp`, the Xbox strings, the start-up's systems and the message decoders, `0x1A26F0`–`0x1A3BE0`

This unit loads the in-game messages' texts from "shell\hud\XboxStrings.csv". It starts the systems
after RenderWare: the log callback, the debug text, the text's language (mapped from the game's),
the multiplayer manager and the service at `dword_5051E8`. It also holds the game loop's one-line
wrappers and the level texture dictionary's reader. The shell (`sub_1A2E40`) runs the front end's
screens with its textures, font and hooks. The rest are the multiplayer manager's message decoders
(game/netmsg.h), from its table at 0x42C850. Each is a function-local static of a message class
named after its vtables, read from the bit stream, plus the three id methods defined here. Four
decoders have destructors, and their exit thunks (`_$E3`, `_$E11`, `_$E13`, `_$E18`) sit in the
grouped initializer region at 0x30EA20–0x30EA50. There is also the players' update decoder
(`sub_1A3550`).

46 functions matched (58 pieces with their EH funclets and exit thunks). The database misses 27 of them (from
0x1A3020), and they were added to `symbols.txt` and `splits.txt` by hand. `sub_1A2A80` (the
network update: the manager's step, then the "NO_NETWORK_CONNECTION" and "NO_SYSTEMLINK_CONNECTION"
warnings) lives in `unit_1A26F0.cpp`; its peers go through
`get_unk_B0_checked()->others_checked()` (type_DC400.h), as in the vote calls. The next code, from
0x1A3BE0, is the multiplayer game modes (their names, "Deathmatch" and so on).

## `src/recovered/unit_1A3BE0.cpp`, the session settings and game type names, `0x1A3BE0`–`0x1A3D50`

The multiplayer session's settings (game/mpgame.h, `unk_4F61F8`) hold the port, 2000 by default, and
whether this machine hosts. The multiplayer manager reads that flag as `dword_4F62FC`. The unit also
has the game types' long and short names ("Deathmatch" and "DM" to "Supremacy" and "SUP", and "Any").
All 3 functions matched.

## `src/recovered/unit_1A3D50.cpp`, the bomb sites, `0x1A3D50`–`0x1A4920`

The search-and-destroy bomb sites (game/bombsites.h, `dword_4F6950`) cover up to five sites, each
at a trigger with its objective key. They handle a site's state as the HUD shows it, the explosion
("ExplodeBomb", a blast and the "MW_OBJ_COMPLETE_<letter>" text), the state changes and the lookups
by point and trigger. They also handle the planted bomb and the declarations the script commands
make.

All 14 functions match. The state change (`sub_1A4200`: "CreateBombAtPos",
"DestroyChildrenAndAllowRecreate", the objective's flags and the defused and planted texts)
reaches the site's objective through a free inline (`site_objective`) from its fourth state on:
each expansion leaves frame bytes, and the frame fits only with them. The next code, from 0x1A4920, is the
capture-the-flag flags (`dword_4F6A7C`).

## `src/recovered/unit_1A4920.cpp`, the capture-the-flag flags, `0x1A4920`–`0x1A5E10`

The capture-the-flag flags (game/flags.h, `dword_4F6A7C`) are two, each with its state, its base
trigger and home, and its flag entity. The unit also keeps whether the homes are swapped. It covers
the reset and set-up (each base's objective and the entity falling at `flt_3E1284`), the lookups
by base and entity, the swap, the rendering time-out that sends a dropped flag home, and putting a
flag upright at a point. The set-up (`sub_1A59D0`) keeps a compiled-out check as an empty `if`,
which the register rotation after it needs.

All 18 functions match. The state change (`sub_1A4B40`, with its texts) reaches its base's
objective through a free inline (`flag_objective`) at all but one site: each expansion leaves
frame bytes that move where the string temporaries' leftovers start, and the frame fits only
with them. The next code, from 0x1A5E10, works on `dword_505188`.

## `src/recovered/unit_1A6140.cpp`, the network players and the manager's parts, `0x1A6140`– (in progress)

The sixteen network players (game/netplayer.h, `unk_4F6B00`) are networked objects of three levels.
The interface gives the object's message. The object is its own update message, at +0x1C. The
player carries the state, and the unit covers its reset, update write and read, and the
application of an update (with its rate kept as a running mean). It also covers what the player
drives and what shows it, its step, the angle wrap and the clamped linear map. The manager's
bomb-site part (`unk_4F8184`, game/bombsites.h) and the bomb site message follow: the sites'
records, their full state written and read, and the lookups by player. So do the string message's
write, the event print, and the id-and-strings type's STL pieces (unit_1A5E10).

The site sync `sub_1A7D80` matches. So do a site's state from a peer (`sub_1A80B0`) and the
message's compiler-made copy constructor it sends on (`sub_1A8400`). The message now has an empty
`type_3E0FCC_data` base declared first. The local player's inline tests `defusing_at` and
`planting_at` give the getter's slot, the posture slot and the bool temporary.

The text decoder `sub_1A8990` now matches (212 bytes, 12 relocations),
along with its exception cleanup and handler. Its buffer is 128 bytes;
the old 132-byte draft added eight bytes through VC7.1's array alignment.
The implicit string conversion and assignment already had the right shape.
Production source supersedes both `blk1a8990*` drafts.

The driven step `sub_1A65B0` now matches (1,977 bytes, 12 relocations).
The facing assignment uses the same const-reference angle conversion as the
following update. Its declined normalization inline retains the unused word
before `this`, allowing the last virtual result to store directly into the
float view of `unk_F0`. Restored the signed-index bit accessors from the
instructions and confirmed the shared height's IDA name, `flt_4F6AF8`.
Production source supersedes the `blk1a65b0*` drafts.

`sub_1A7480` now matches (1,490 bytes,
32 relocations). Its facing assignment constructs an angle from `const RwReal &`,
placing the angle and input temporaries after the returned vectors. The two
inline interpolation calls retain four unused words each, and the angle's
inline normalization retains one more. All nine words come from declined
inline expansions. The normalization copy also matches `sub_1A6E10` (107 bytes,
six relocations) and is aliased to it. Production source supersedes
`docs/drafts/draft_1A7480.cpp`.

## `src/recovered/unit_1A8B20.cpp`, the multiplayer manager, `0x1A8B20`–`0x1AFF40`

The multiplayer manager, cNetController (`unk_4F7EB8`, `type_4F7EB8` in game/gameloop.h). It is the
network game's third listener (`type_4F8054_A8`, game/netlisten.h; its vtable is off_3E13E8, the
listener's own off_3E13F4, whose empty inline slots fold into sub_15FB30 and pDtor). Its layout
holds its parts as members:
- the two score messages at +4 and +0xD0 (game/netscore.h);
- the bomb sites at +0x2CC;
- the flags at +0x384, with the full state part at +0x3D0 (game/netstate.h);
- the +0x490 part with its two strings.

The voice update `sub_1AA380` (`updateVoiceSubSystem`) now matches
(1,962 bytes, 14 relocations). A checked inline returning a mask copy by
value builds its result in `set_voice_peers`' argument slot. This preserves
the register step between the copy's address and destination load while
leaving the shared mask copy constructor unchanged. The old caller-side
mask check is replaced by that check inside the copy helper.
Nothing remains binary in `0x1A8B20` through `0x1AFF40`: the view change `sub_1AB440` matches with
its one call to `sub_1B6DE0` in the original's `__asm` (the countdown passed on the FPU, `fld;
push ecx; fstp [esp]`, a sequence found nowhere else in the image and given by no C++ form).

The kill-cam state change `sub_1ABC00` and respawn `sub_1AED80` now match
(547/865 bytes, 12/22 relocations). Both call `sub_1A6420` through the same
checked network-player accessor. Its compiled-out index check supplies the
register step between the null-checked base conversion and the argument push,
without an extra stack slot. The respawn's position updates use mutable
coordinate references for the two late pointer temporaries. Unit check macros
preserve the remaining retail assertion loads, including the state change's
final assignment. Production source supersedes the `aed*` drafts.

The remote players (+0x1F0) are soldiers with a network part at +0x2170 (game/netsoldier.h). The
local player's +0x2260 part is what a network player drives.

The unit holds the message handlers (the table at 0x42C848: kind, id, decoder, handler), the joins
and leaves, the kill cam, the spawn points, the pickups' sends, the section streaming for a peer, the
respawn message, and the accessors the rest of the game uses. 77 functions matched. The
constructor (`sub_1A8B20`) sets its fields in its initializer list; the vote's texts are
default-constructed out of line (`sub_E87E0`), and the flags' part's empty constructor is folded into
`sub_6FCD0` (config/aliases.txt). The respawn
message (`sub_1AFBB0`) builds its text in a `type_1CB670` local, whose out-of-line default constructor
is `sub_E87E0` (config/aliases.txt).

The messages it copies have an empty data base declared first (`X_data`, game/netmsg.h). That base
gives the null-checked conversion before the vtable stores. Larger messages have out-of-line copy
constructors.

Parked:
- The respawn message's static strings' exit thunks (0x30EA80, 0x30EA90) call the destructor out
  of line and stay binary.
- `sub_1AD750` (matched 2026-10-01): the frame through `show_message()` and `hosting()` (two
  no-code inline expansions after the message texts); the registers through compiled-out checks:
  `var118->unk_0D` before the remote player's fetch (two loads), `hosting()` before the last
  block (back to the image's frame: the inline budget), and `unk_1F0[arg_4]` before the
  visibility test, the hide call and `sub_1A6460` (one load each). The kept player goes to
  `unk_238`, not `unk_1B0` (the relocation check told them apart).
  `sub_1ACBA0` matched the same way, with the peers through
  `get_unk_B0_checked()->others_checked()` passed straight to the send (no named mask local).

The host's start (`sub_1A9A70`) matches. It fills the session's description, waits for the session
to start, then gives the game data the front end's settings. The game data's empty `pDtor` method
is folded into 0x1E41C0 (config/aliases.txt). The four zeroed address words are scalars whose
names (tools/climb_names.py) put them above the /GS cookie.

The grenade handler (`sub_1AE8F0`) matches. It throws a peer's grenade through `sub_15F2C0` with a
static 0x84-byte record (`type_F4890_blast`, type_67260's constructor behind a guard bit). The
record is filled from the weapon: two values chosen by the throw's hand (`unk_498_a`, `unk_4AC_a`)
and the spawned object, read through the `projectile_object` inline. Two compiled-out checks move
the registers two loads on before the message's vectors are read.

The grenade death handler (`sub_1ADD90`) matches. Its remote player takes the blast through its
network part's `pvf_020`, which takes a `type_4AE70 *`: the soldier's override already cast its
argument to one, and the two overrides' match lines changed with it. The victim's name for
"MW_GEN_KILLS_GREN" is a local (the frame is 16-aligned, so it is slotted where first used).
Compiled-out checks are needed at four places.

The join (`sub_1A9CE0`) matches. It waits on the session's join state, feeding the interface's
events, and shows the state's text in `unk_4F7E9C`. That assignment goes straight to
`std::string`'s `assign(str, 0, npos)`, written `static_cast<std::string &>(unk_4F7E9C) =
type_1A5EA0(key, 0)`, whose out-of-line constructor's `this` passes through two slots. The session
getters are `get_unk_14` (with a slot) and `get_unk_310_direct` (the switch's garbage slot), and
the game type's setter `set_game_type` stores through an argument slot. The locals' names come from
tools/local_names.py.

The local respawn (`sub_1ABE30`) matches. Findings:
- The manager's `unk_278` is the local player's `cNetPlayerTrigger` (dword_4F8130), and its
  `unk_28C` is the request's time (`type_1CCA10`).
- The frame is 16-aligned, so the elapsed milliseconds are a named int local, and the point's
  upright fix-up uses three block-scoped pointer locals, not an inline (an inline holding the
  cross-product macros' loops is not expanded).
- The fade test is `fade_done()` (game/fade.h).
- Compiled-out checks are needed at seven places.

## `src/recovered/unit_1AFF40.cpp`, the log, `0x1AFF40`–`0x1B18E0`

The log (`type_4F84B8`, game/startup.h) is three channels of fifty 80-character lines in rings. The
unit holds its constructor, destructor, setters, the add-line (every line also goes to channel 1)
and the accessor `sub_1B18D0`; 6 functions matched. The one log is built at `unk_4F84C0` by a dynamic
initializer (0x30C220, `unk_4F84C0` defined in the unit; its exit is `sub_30EAA0`), both placed.
The drawing (`sub_1B00F0`, 0x1676 bytes of debug display that returns at once) is matched
(docs/questions.md has what it took).

## `src/recovered/unit_1B18E0.cpp`, message methods, `0x1B18E0`–`0x1B4690`

The network messages' own methods (game/netmsg.h):
- A point message's write and read (`type_3E0FB4`).
- The score messages' out-of-line constructors, destructors and ids (`type_3E1E3C`, `type_3E1FC4`).
- The full game state message, which writes and reads every manager part in turn (`type_3E105C`).
- The rules message (`type_3E1074`) and the kick message (`type_3E10BC`).
- The flag part (`type_4F823C`): its reset, network state, step, carriers, the peers' updates
  (`sub_1B1DE0`) and capture the flag's entity step (`sub_1B2670`). `sub_1B1B00` is parked on one
  slot order.
- The network keep-alive thread (`sub_1B2810` to `sub_1B2A80`).
- The score messages' scoring: kills, captures, ranks, the round's total into the game's
  (`sub_1B38E0`), and the player order for the scoreboard (`sub_1B3480`). That function's
  `std::vector<RwUInt32>` pieces are here, a copy of `std::vector<RwInt32>`'s kept apart by name.
- The game data's callbacks (`sub_1B4470` to `sub_1B4520`).

## `src/recovered/unit_1B4470.cpp`, Message handlers, `0x1B4470`–

Split from unit_1B18E0 (PLAN M7): its deferred std::vector<RwUInt32> functions (`0x1B3C30`–`0x1B4430`) end that object. The free message functions `sub_1B4470`–`sub_1B4520` and the handler classes' `vf_000`/`vf_004` follow.

## `src/recovered/unit_1B46B0.cpp`, the game data, `0x1B46B0`–`0x1B6FE0`

The game data (`dword_4FB9E0`, game/data.h, 0x11C bytes):
- Its sixteen records (`type_4FB9E0_74`) and their reset.
- Its two settings blocks (`type_4FB9E0_08`): reset, network write and read. Their empty
  constructor and destructor are folded into `sub_6FCD0` and pDtor.
- Its constructor, destructor and reset ("Clean game flow manager").
- Its settings sent to the network game (`sub_1B60E0`, the session's vf_064). It goes through the
  manager's direct getter, whose unwritten slot the image copies, after a compiled-out check.

## `src/recovered/unit_1B6FE0.cpp`, cNetLevelParams, `0x1B6FE0`–`0x1B79E0`

The RenderWare Studio behaviour `cNetLevelParams` (types/cNetLevelParams.h): per team a count,
two keys and five spawn keys, looked up at the system's start. The multiplayer manager's unk_280
points at it. Its CEventHandler part's deleting destructor thunk (`0x1B79D0`) sits inside
`sub_1B79A0`'s old split range, so it has its own splits.txt and symbols.txt rows. All 12
functions matched.

## `src/recovered/unit_1B7B20.cpp`, the network game's players and pick-up, `0x1B7B20`–`0x1BD6A0`

Three classes. The local player in a network game (`type_17DBD0_player`, game/netmsg.h): a
`type_10F710` with a network part at +0x2260 (a second base, `type_3E24E8`, whose vtable is all
`_purecall`) that the network player driving it calls. The second player (`type_1BABA0`,
game/netplayer.h; the manager's unk_1A8), which a network player shows (its part is
`type_4F6B00_120`); its part's +0x02C is its vf_05C through an adjustor thunk. The network pick-up
(`type_1AE520`, a `type_3D94B8`). `type_10F710`'s constructor and destructor are defined in its
class and not expanded: the players' constructors and destructors reserve their slots and emit them
with the base's vtable and deleting destructor. `type_3D94B8`'s destructor is in its class too (the
pick-up's destructor expands it). The player's sub_10DBD0 is its virtual slot +0x258 (the second
player overrides it). All matched. The local player's vf_068 (0x1B8AA0, matched 2026-10-01) sends the
peers straight from `get_unk_B0_checked()->others_checked()` (two compiled-out `unk_2288` checks
before the kill message's send), as sub_1ACBA0 does; its locals' names state their slots
(`var_10`, `lv_14`, `fp_11C`, ...).

## `src/recovered/unit_1BD340.cpp`, The pick-up spawner (type_1AE520), `0x1BD340`–

Split from unit_1B7B20 (PLAN M7): `type_1BABA0`'s deferred adjustor thunk (`0x1BD330`) ends that object. The pick-up spawner's makers (`sub_1BD340`, `sub_1BD450`), constructors, destructor and `sub_1BD680` follow.

## `src/recovered/unit_1BD930.cpp`, the network pick-ups, `0x1BD930`–`0x1BE0B0`

The network game's pick-ups (`type_4FBB20`, `dword_4FBB20`, game/netmsg.h): 32 slots of network
pick-ups whose ids are their slots, and on the host the triggers that spawned them (respawned at a
level load). Their state goes over the network through the bit stream. Its constructor is out of
line for the global's dynamic initializer. Several functions keep compiled-out checks.

## `src/recovered/unit_1BE0B0.cpp`, cNetPickupTrigger, `0x1BE0B0`–`0x1BE4D0`

The RenderWare Studio behaviour `cNetPickupTrigger` (types/cNetPickupTrigger.h), a PickupTrigger
whose pickups are network pick-ups, taken into the pick-up list by the host at the game's start.
Its CEventHandler part's deleting destructor thunk (`0x1BE4C0`) sat inside `sub_1BE490`'s old split
range, so it has its own splits.txt and symbols.txt rows, as does cNetSoldierTrigger's deleting destructor thunk
(`0x1C0820`, inside `sub_1C07E0`'s old range). The behaviour `cNetSoldierTrigger`
(types/cNetSoldierTrigger.h) spawns remote players. All matched.

## `src/recovered/unit_1BEBB0.cpp`, the remote players and cNetSoldierTrigger, `0x1BEBB0`–`0x1C0830`

The multiplayer manager's remote players (`type_4F7EB8_1F0`, game/netsoldier.h): a soldier
(`type_3DAFC8`) with the network part `type_4F6B00_120` at +0x2170, which takes the remote player's
state and hits. `type_3DAFC8`'s destructor is defined in its class and not expanded (this unit's
destructor reserves its seven slots); its inline `vf_05C` is emitted here, where the part's thunk
(`0x1C06D0`) reaches it through the remote player's identical, folded override. The part's +0x000
(`0x1BF0C0`, reached only through the vtable) was missing from the database: it has its own
splits.txt and symbols.txt rows, as does cNetSoldierTrigger's deleting destructor thunk
(`0x1C0820`, inside `sub_1C07E0`'s old range). The behaviour `cNetSoldierTrigger`
(types/cNetSoldierTrigger.h) spawns remote players. All matched.

## `src/recovered/unit_1C06E0.cpp`, cNetSoldierTrigger, `0x1C06E0`–

Split from unit_1BEBB0 (PLAN M7): the remote player's deferred adjustor thunk (`0x1C06D0`) ends that object. cNetSoldierTrigger's MakeNew, constructor, destructor and `vf_020` follow, with its class name, vtables, class ID and registration.

## `src/recovered/unit_1C0910.cpp`, cNetSpawnPoint and the spawn lists, `0x1C0910`–`0x1C2120`

The RenderWare Studio behaviour `cNetSpawnPoint` (types/cNetSpawnPoint.h), a Trigger that joins
the spawn points' lists at the game's start (`unk_4FBC50`, `type_4FBC50`, game/netmsg.h). There
is one list of every point and one per team (and group) chosen by the game type. Each list
(`type_1C0F60`) picks a point for the players by a rule: in turn, at random, away from enemies,
or by distance. The random pick's divisor is written `unk_08 - 1 + 1`, since only a computed
divisor gives its register. The game-type switch reads the type through a direct-return getter
(`get_unk_08_00`), whose unwritten slot the switch copies first. The CEventHandler part's deleting
destructor thunk (`0x1C2110`) sat inside `sub_1C20F0`'s old range and has its own rows. The distance picks `sub_1C16B0`, `sub_1C1820` and `sub_1C1A40` take their
lengths through `type_1F8560_v::len()` (game/netvec.h): an in-class copy of `sub_1BF590` that
VC7.1 declines to expand, so each caller keeps a never-written slot for its local and calls its
out-of-line copy, which /OPT:ICF folds into `sub_1BF590` (aliased).

## `src/recovered/unit_1C2120.cpp`, cNetStaticCamTrigger, `0x1C2120`–`0x1C2440`

The RenderWare Studio behaviour `cNetStaticCamTrigger` (types/cNetStaticCamTrigger.h). This
Trigger becomes the multiplayer manager's static camera (`unk_234`) at the game's start. Its four
commands are the starting level sections. The CEventHandler part's deleting destructor thunk
(`0x1C2430`) sat inside `sub_1C23E0`'s old range and has its own rows. All matched.

## `src/recovered/unit_1C2440.cpp`, the players' teams, `0x1C2440`–`0x1C2AB0`

The players' teams (`type_4F8288`, `dword_4F8288`, game/netstate.h): sixteen entries of team,
state and a taken flag. Covers the team for a joining player, a team's count, the reset, leaving,
and the table written to and read from the network. The counts test the game's peer mask
through `type_1DDE20_mask::test` after a compiled-out check. The team change (`sub_1C2600`)
queues its console message and ends with a free inline (`set_team`), whose expansion trims the
text branches' leftover slots to the image's. All matched.

## `src/recovered/unit_1C2AB0.cpp`, cNetTriggerViewControl, `0x1C2AB0`–`0x1C2F90`

The RenderWare Studio behaviour `cNetTriggerViewControl` (types/cNetTriggerViewControl.h). Any of
its commands sends the network triggers' visibility settings with
"kujuUpdateTriggerObjectVisibility". The data is `unk_4FD6D4` (`sNetTriggerVisibility`,
game/netvis.h, named for the message's data type string), shared with cNetPickupTrigger and
cNetSpawnPoint. The CEventHandler part's deleting destructor thunk (`0x1C2F80`) sat inside
`sub_1C2F50`'s old range and has its own rows. All matched.

## `src/recovered/unit_1C3120.cpp`, the vote, `0x1C3120`–`0x1C3D20`

The network game's vote (`type_4F8348`, `unk_4F8348`, game/gameloop.h), named by its traces
("VOTE localVoteCall" and so on). Covers the reset and the host's countdown, the votes given, the
end on the host and the result on a client, the last vote kept, and the console messages. Its
texts are `type_1CB670` (game/loc.h, given an empty inline constructor). Several parts start
with a compiled-out check. The count message's buffer sits in an inner block below its two
strings. Not yet matched: `sub_1C32B0` and `sub_1C3520`, the vote calls; the peers mask's shift
is one load early.

## `src/recovered/unit_1C3D20.cpp`, the front end's network interface, `0x1C3D20`–`0x1C5700`

The front end's link to the network game: free functions over this unit's globals. One trace
names it cUIInterface ("cUIInterface::startServer %s"), so `startServer` keeps that name. It
covers:

- the settings copy the front end edits (`unk_4FDBB0`), the level list (`type_505188`, with new
  inline setters), and the lobby's copy of the players' names, teams and scores;
- the screens it opens (`type_1FF250`) and the pending message;
- the vote queries, and the sound, rumble, difficulty, sensitivity and voice options;
- the objective key "winfo_N_W", whose letters are written into the .data string.

The local player and the network game are read through the manager's `unk_1A4` and `unk_19C`
getters. Several functions start one register late; each has a compiled-out check with a
one-load stand-in condition. The objective hint text `sub_1C5350` now matches
(933 bytes, 50 relocations, plus its 88-byte cleanup and 10-byte handler).
It returns `type_1CB670`, uses implicit string conversions for the appends,
reads the team count through its getter, and formats a score in 12 bytes.
Two existing text diagnostics preserve all five character-constructor
expansions. Eight unused inline locals in a separate final-return scope
restore the 0x140 frame without moving the formatted-return temporary.
Their exact discarded source expressions are unknown and documented in
the source. All functions in unit_1C3D20.cpp are matched.

## `src/recovered/unit_1B79E0.cpp`, `unit_1BD6A0.cpp`, `unit_1C0830.cpp`, `unit_1C2F90.cpp`, more message methods

More writes and reads of message classes (`type_3E0F9C`, `type_3E111C`, `type_3E1134`, `type_3E10EC`,
`type_3E0FE4`, `type_3E0FFC`, `type_3E1014`). They use the stream's ranged whole numbers
(`sub_1F8B90`, `sub_1F8B30`). Several reads keep a compiled-out check as an empty `if` before a
field whose registers are one load on. 18 functions matched.

## `src/recovered/unit_1C5700.cpp`, message methods and the id maps, `0x1C5700`–`0x1C60A0`

The maps between the game's and the network's message ids (`sub_1C5800`, `sub_1C5860`). The writes
and reads of eight more message classes. The grenade throw's send (`sub_1C5CA0`), whose message's
implicit constructor is out of line (`0x1C5D40`); its frame's two unused slots are the peers'
mask (`type_4F8054_B0::sub_1A8050`, defined in its class but not inlined) reserved. The sections' wait with
its compiled-out print (`sub_1C58C0`). 25 functions matched. `sub_1C5700` (std::string's `const
char *` constructor) is placed from unit_1FB520, which calls it out of line. The unit also defines kujuUI's focus
stack (`unk_4FDBE4`, its initializer 0x30C3F0 before the id maps'), whose implicit destructor's copy is `sub_1C5740`.

## `src/recovered/unit_1C60A0.cpp`, the voice chat, `0x1C60A0`–`0x1C7EE0`

The voice manager (game/voice.h, `type_3E3860`, 0x3160 bytes) receives the peers' voice data and
this machine's microphone data through two receiver levels. It keeps the latter in a 2500-byte ring
buffer and sends it every 100 milliseconds through its channel (`type_3E3870`, built by the session
module's `sub_1DE280`). The XHV engine's owner (`type_3E3884`, an `ITitleXHV`) creates the engine
and registers talkers with their XUIDs. It sets playback priorities from the mute masks, and sends
each player's headset, speaker and mute status as `type_3E0F54` messages. The XHV C entry points,
processing modes, `XGetDevices` and `IDirectSound_SetEffectData` are aliased to the library code.

35 of 36 functions matched. The send (`sub_1C6700`) takes the elapsed time through `since()`, and
passes the peers' mask through a by-value accessor holding a compiled-out check. Parked:
- `sub_1C7840` (the status update: the second block's test is one register on).

The unit ends at 0x1C7EE0. `sub_1C7EE0` and `sub_1C7F20` (a string append and the assertion
message) belong to the next unit.

Findings:
- The peer mask's `test`, `add` and `clear` are inlines. `add` and `clear` keep two compiled-out
  checks, since their registers are two loads on.
- Tests chained with `&&` whose registers jump between two inlines were written as nested `if`s,
  each with a check.
- The status message's fields are set through inline setters that take `bool`, which leaves the
  byte temporaries.

## `src/recovered/unit_1C7EE0.cpp`, the assertion report, `0x1C7EE0`–`0x1C8110`

The assertion report (`sub_1C7F20`) builds "Assertion failure on line ... In file ... In function ..."
into a /GS buffer and stops in the empty debug hook. With it come a string append (`sub_1C7EE0`) and
two wide-string helpers. Its write pointer sits between the two arrays, declared there. 4 functions
matched.

## `src/recovered/unit_1C8110.cpp`, the null-safe string's editing, `0x1C8110`–`0x1C8A30`

This unit holds `type_1A5EA0`'s insert, erase, append and number append, its constructor from a
`std::string`, and the `std::string` pieces they pull in out of line: `clear`, `substr`,
`erase(iterator, iterator)` and both `append`s. 10 functions matched. Parked:
- `sub_1C8110` and `sub_1C8330`: the image copies each substring into a temporary.
- `sub_1C8540`: frame 0x24 bytes larger.

## `src/recovered/unit_1C8A30.cpp`, the debug print and kujuUI's file input, `0x1C8A30`–`0x1C8DF0`

The debug print (`vsprintf` into `OutputString`, then `OutputDebugStringA`) comes first. A string
key's comparisons follow. Last is `kujuUI::cFileIn` (\COD\SHARED\fileIO\cFileIn.cpp, named by
`readVector`'s assertion), with its open, reads, string read, end test and destructor. These read
through RenderWare's file interface. 12 functions matched.

## `src/recovered/unit_1C8DF0.cpp`, kujuUI's parsed files, `0x1C8DF0`–`0x1CA890`

`kujuUI::cParsedFile` (\COD\SHARED\fileIO\cParsedFile.cpp) is named by `loadBinaryFile`'s assertion.
It holds a string table (`type_1CA4E0`) and a root scope (`type_1C8DF0`). Each scope has child
scopes and values (`type_1C8DF0_104`, of up to eight parts). `kujuUI::cScopeValidator` builds the
children and values from its value definitions (`type_1C9590`, hashed) over fixed pointer arrays and
their iterators. The validator's version is a sum over its tree. 45 functions matched. Among them sits
`type_1A5EA0::sub_1CA470`, a C string's append: its conversion calls the string's constructor out
of line (`sub_1A5EA0`), as VC7.1 does for a function's last such conversion.

Findings:
- The scope reader (`sub_1C9190`) needs its loop variables declared in their `for` statements, which
  gives the block order the frame shows.
- The scope class was first named `cParsedFile`, which was wrong. The assertion's signature showed
  that `cParsedFile` is the 8-byte file object, and the renamed functions were re-committed.

## `src/recovered/unit_1C9B40.cpp`, DDS textures from kujuUI files, `0x1C9B40`–`0x1C9EA0`

`RwXboxDDSTextureRead` reads through RenderWare's file interface. While it runs, the interface is
swapped for functions that read the open kujuUI file (exist, open, read, seek by reading, end, and
a close that returns 1). 8 functions matched.

## `src/recovered/unit_1CA890.cpp`, the localised text, `0x1CA890`–`0x1CBC80`

The manager (`unk_4FEB0C`, `type_1CAC10`, which the rest of the game uses as `sub_1CAF30`,
`sub_1CAD40` and `sub_1CADA0`) holds three tables of wide strings loaded from `LOC\<language>\<file>.loc`.
Each table holds a dictionary sorted by key (`type_1CA8A0`). The unit also has the "%1"/"%2"
formatting, the localised texts as `type_1A5EA0` and derived `type_1CB670` values, and five static
texts with five global ones. 36 functions matched. The two-argument format (`sub_1CB0F0`) keeps its
three flags above the /GS cookie only with the names tools/local_names.py finds (`var_2`, `local_3`,
`var_1`). `sub_1CAF30` now matches (208 bytes, eight relocations): it and
`sub_E3970` return `type_1A5EA0`, and the constructor at `sub_1CB6B0` belongs to
the derived `type_1CB670`. Its base initializes directly in the forwarded
return buffer, with no slicing. A compiled-out language check preserves the
register step after lookup. Existing two-argument `type_1A5EA0` temporary
declarations bind to that compatible constructor entry (config/aliases.txt).
The text constructors and `sub_1CB720` are also matched; the old frame notes
were stale. This unit has no remaining parked function bodies.

## `src/recovered/unit_1CBC80.cpp`, cNetGame, `0x1CBC80`–`0x1CCC00`

The network game (`dword_4F8054`, `type_4F8054`) is named cNetGame by its traces. It is abstract,
with a 34-slot vtable of which 19 slots are pure. It allocates itself and its three parts from a
memory pool (`sub_1CBC30`, game/pool.h): a 0x7A0-byte part with a virtual destructor, the players
(`type_4F8054_B0`, whose compiler-generated constructor sits here) and a 0x6A0-byte part. This unit
holds:
- its reset, take-down (`deinitialise`) and step;
- `createServer`, `joinServer` and the session settings;
- five sends and the two listeners;
- the message dispatch and the session key;
- `setError`, `errorToString` and `packetEngineHasRunOutOfRam` (named by their traces);
- the game clock (`sub_1CCA10`, from the performance counter).

29 functions matched.

## `src/recovered/unit_1CCC00.cpp`, cNetGameSessionManagement, `0x1CCC00`–`0x1D0100`

The network game's players (`type_4F8054_B0`, cNetGame's unk_B0) are named
cNetGameSessionManagement by their traces. The unit holds:
- their reset and emptying;
- the client's join step (`sub_1CCD60`) and the server's (`sub_1CD780`),
  each a state machine that sends a join message and waits for its ack
  with a deadline;
- closing the game, `handlePossibleDisconnections` and kicks
  (`sub_1CD690`, `sub_1CD6E0`, `sendPlayerKicks`);
- the peer records and the per-step bookkeeping (`sub_1CFD50`).

Many functions keep compiled-out checks: a dword-field check is one load, a
mask check is two, and two mask checks move the next register on by one
(docs/toolchain.md). The message handler `sub_1CE650` is matched (2026-10-01): a switch over the sNetGameEP messages in their case order 8/9, 5, 6, 10, 11, 1, 14, 4, 3, 13, 2, 12; each message a block-scoped local named for its slot; 22 `PLAYERS_CHECK`s placed by a first-difference search (scratchpad chk2.py), the mask removals through `discard()`/`clear()` and one add through `admit()` where the image's registers need the inlines' checks; the deadlines are `get_unk_7C() + type_1CCA10(40000)` and `set_unk_44(sub_1CCA10() + 40000)`; it returns a value, so `type_4F8054::vf_048` (and cXboxLiveNetGame's) return the network call's result.

## `src/recovered/unit_1D0100.cpp`, cPacketEngine, `0x1D0100`–`0x1D48B0`

The packet engine (`type_1D0100`, game/netqueue.h; named by its trace path) is cNetGame's unk_AC. It
holds per-peer queues of pooled packet lists (`type_1FA230_list`), their sends and resends, and the
acks. 38 functions matched. The destructor (`sub_1D0390`) matches with the list destructor
specialised for `type_3E4E40` without its unused local (the first list it destroys has no slot for
one).

The message and ack copy constructors `sub_1D43B0`/`sub_1D4320` now match
(138/134 bytes, two relocations each). The mask has distinct mutable and const
copy overloads: the const form retains two compiled-out word checks. This
reproduces the implicit packet copies while preserving mutable copies elsewhere.
The voice-copy helper takes its mutable input by reference to select that form.

`sub_1D4290` now matches in unit_1D4290.cpp: a packet-only instantiation
avoids the unrelated HUD singleton guard that renamed its array locals.
No packet functions remain parked in this range.

The per-peer service `sub_1D1C30` is matched.

`addPacket` (`sub_1D0F60`) is matched with four `NETQUEUE_CHECK`s (its twelve untouched slots).
The packet receive `sub_1D2CC0` is matched. It uses a 9-byte check type (`sub_73D90` fills it,
`sub_1F5A00` compares) and a time sum. The two checks in its ack block are `NETQUEUE_CHECK`s, each keeping
three unused locals: the image's six never-written slots after the ack constructor's temporaries.
The packet builder `sub_1D21E0` is matched: its cursor moves go through the list's `node` inline, and
ten compiled-out checks set its registers. The receives in order (`sub_1D3770`) and unordered
(`sub_1D3C80`, whose per-peer lists hold 8-byte `type_1D3C80` entries) are matched. The ack list's append
(`sub_1D4150`) and the ack's destructors (`sub_1D35C0`, `sub_1D35F0`) are instantiated explicitly.

## `src/recovered/unit_1D48B0.cpp`, peer-mask helpers, `0x1D48B0`–`0x1D4AB0`

The peer mask's (`type_1DDE20_mask`) out-of-line helpers:
- the every-peer constructor;
- its highest and lowest peers;
- the peers as text ("Empty", or "1, 3" in the static buffer at 0x4FEC78);
- how many peers it holds.

## `src/recovered/unit_1D4AB0.cpp`, cTimeKeeper, `0x1D4AB0`–`0x1D5190`

The network game's third part, named by its trace ("KNET: cTimeKeeper() - ..."): formerly
`type_1D4AB0`. It pings the peers four at a time every 600 milliseconds and keeps each peer's last
eight pings (`cTimeKeeper_0C`: sent, answered, round trip). From them it keeps each peer's
latency and clock offset. Its ping packet is `type_1D7560`, whose send and read are in
sNetGameEP.cpp. All matched: the step `sub_1D4CA0` (names by block search; the peer-mask
intersection `operator&` carries a compiled-out check; times read through `ms()`, the latency's
time built by `type_1CCA10(d / c)`) and the ping message `sub_1D5010` (the round trip is
`sub_1CCA10().since(...)`).

## `src/recovered/unit_1D5190.cpp`, cXboxLiveNetGame, `0x1D5190`–`0x1D5D30`

cNetGame's Xbox side (types/cXboxLiveNetGame.h), named by its trace
("cXboxLiveNetGame::stateServerTakeUp ..."): formerly `type_1D5190`. It covers the host's session
over Xbox Live or the system link, the join with the server's address and keys (the 0x74-byte
`cXboxLiveNetGame_114`), the peers' user ids, the session's settings and the link's watch, all
through the network system (`sub_1D8810`, game/voice.h). The base class's pure virtuals got their
widths from its overrides; the trivial ones are inline and folded (/OPT:ICF). The empty state steps
share `sub_15FB30`. Several steps start with a compiled-out check. Also here is
`type_4F8054::sub_1D5BB0`. All matched.

## `src/recovered/unit_1D5D30.cpp`, the network debug print, `0x1D5D30`–`0x1D5DC0`

The network layer's debug print (to the debugger, the game's empty print and a hook) and the hook's
setter. All matched.

## `src/recovered/unit_1D7A50.cpp`, the packet engine's messages, `0x1D7A50`–`0x1D7CE0`

The data halves (vf_004 and vf_008) of three packet-engine messages, and a queued packet's
(`type_1D7CA0`) read and release. They keep leading compiled-out checks. 8 functions matched.

## `src/recovered/unit_1D7CE0.cpp`, cXboxLive's file, from `0x1D7CE0`

One source file by its literals: the run from `0x3E52A4` holds `CSystemLinkQuery::Query`'s trace and then
the `cXboxLive::` traces (createSession, joinServer, disconnectPlayer and the connection handshakes). The
network system is cXboxLive (types/cXboxLive.h, formerly `type_1D8810`); its constructor is `sub_1D83C0`.

First, the system link host search `CSystemLinkQuery` (game/systemlink.h, at cXboxLive +0x18C4): its
constructor and destructor, `Query` (a 0x60-byte probe with an `XNetRandom` nonce and five
`XONLINE_ATTRIBUTE`s, broadcast through the network system's socket), the poll that ends it after half a
second (`XONLINETASK_S_SUCCESS`), and the answers it keeps (25 hosts of 0x9A bytes). Then the block list's
XUID comparison `sub_1D8370`, which compares only the 64-bit user ids.

cXboxLive itself (types/cXboxLive.h, 0x41A8 bytes): its constructor (members' constructors, zeroed blocks,
16 players and an empty name in the session settings, "SystemLinkHost"), destructor, the instance getter
`sub_1D8810` (a function-local static at `0x4FED00`, exit thunk `0x30EC00`) and `sub_1D8880`, which
starts the Xbox online library. The members' constructors and destructors are aliased until they match;
the sockets' destructor is empty and folded into `sub_1E41C0`. Then the session's reset (`sub_1D8900`), the
send to one peer (`sub_1D8B40`, whose peer test holds a compiled-out check in a comma expression through
cXboxLive's `check()` inline) and createSession (`sub_1D8C00`), the system link createSession (`sub_1D8E10`),
the session searches over Xbox Live (`sub_1D8EE0`) and the system link (`sub_1D9100`), their stop and poll
(`sub_1D9090`, `sub_1D91E0`) and `sub_1D9230`, the found sessions copied out for the game (`sub_1D9270`,
0x74-byte `type_1D9270_session`s; the Live search at +0x878 keeps its sessions like the query's hosts) and
the host's sockets (`sub_1D9610`), joinServer (`sub_1D9700`), the peer at an address (`sub_1D9970`) and the
receive poll (`sub_1D9A10`, which hands peers' packets to the packet engine's receive), peerConnectToNewPlayer
(`sub_1D9C30`) and disconnectPlayer (`sub_1D9DD0`); the session key's text (`sub_1DA070`, function statics
at `0x42CD18` and `0x502EEC`), the IP address conversions (`sub_1DA0C0`, `sub_1DA110`), the session's end
(`sub_1DA170`), a lost peer (`sub_1DA1D0`), the lost connection (`sub_1DA230`) and the handshake messages
(`sub_1DA270`, `sub_1DA350`, `sub_1DA430`: 0xFF, a type and a value, and this machine's XUID), the connection
attempts' timeouts and resends (`sub_1DA4D0`, its mask bit cleared through the free inline `mask_remove`) and
the block list's add (`sub_1DA680`) and the host's handling of a join request (`sub_1DA6D0`: the player limit
from the session description, the network game's `type_4F8054_18`), and a peer's handling of the host's
accept and reject (`sub_1DAA60`, `sub_1DABA0`), another peer's request, accept and reject (`sub_1DACB0`,
`sub_1DAF00`, `sub_1DB060`) and the handshake dispatcher (`sub_1DB180`, a switch on the message type), the
host's answer to a system link probe (`sub_1DB250`), the session's slots and settings setters (`sub_1DB750` to
`sub_1DB920`), its state setters, the logon user (`sub_1DB990`), `sub_1DBA40` and its step (`sub_1DBA80`: the
logon, session and search tasks), the player getter (`sub_1DBD40`), a peer's user id (`sub_1DBD60`), the block
list (a 16-entry ring: `sub_1DBE00`, `sub_1DBE30`, `sub_1DBED0`, `sub_1DBF20`) and the socket's constructor
(`sub_1DBF50`). Then the socket, cXboxSocket (game/systemlink.h, named by its traces): `create` (VDP or UDP,
the system link one broadcasting on port 1001), its close, `receiveMessage` (a VDP packet's game and voice
messages), `broadcast`, `sendMessage`, `incomingMessageWaiting` (the XDK's FD_SET), the last error's text (the
table at `0x42CD30`) and the close after unrecoverable errors. Then the Xbox Live session, CSession
(types/cXboxLive.h): the XDK's MatchSim generates it, and the sample SimpleConnect's match.cpp holds the same
class, so its functions follow the sample's (with nine attributes, and a sixth state for a failed create), down
to its QoS queue's out-of-line members (`0x1DD190` to `0x1DD2E0`), and the sample's CQuickmatchQuery, the Xbox
Live search (eight integer arguments; five integer result attributes and the host's name, the table at
`0x3E6680`), with its results' out-of-line `Remove`. 121 functions matched.

## `src/recovered/unit_1DBF50.cpp`, cXboxSocket (the game's UDP socket) and the Xbox Live matchmaking queries, `0x1DBF50`–

Split from `unit_1D7CE0.cpp` (cXboxLive). Evidence: the Winsock error-string table `unk_42CD30` (0x42CD30) is a global whose string literals the compiler emits before any function's, and the image has them after cXboxLive's last strings and before cXboxSocket::create's (0x3E5EFC), so this object starts with cXboxSocket at 0x1DBF50 and defines the table. `X_MATCH_NULL_INTEGER` (internal linkage) moved with the query code that uses it.

## `src/recovered/unit_1DDBE0.cpp`, the network session, from `0x1DDBE0`

Its vtables follow cXboxLive's file's data (`0x3E66B0` on). The network game's message listener
(`type_3E3860_10`, game/voice.h: it passes the messages on to the voice channel and sends the channel's)
and the network session (`type_4F8058`, game/netmsg.h, dword_4F8058: the peer listener). The session sends a
message to peers through the stream `unk_502EF0` (its id first; three delivery kinds), hands a message that
came in to its handler from the table `unk_42C848` (kind 0 reads it and takes the result, kind 1 takes the
stream; compiled-out checks of the function pointers), and keeps the networked objects (a pooled list of
`type_3E1388` pointers) whose updates it sends when due. The listener bases' own methods are empty
(`0x1DE440`, and `0xF7B90` for the peer listener). Then the voice channel (`type_3E3870`, game/voice.h): the
voice manager's packets to and from the peers, 24 incoming and 5 outgoing, each on free and waiting lists;
the incoming ones queued per sender in number order and played when next or too old, the outgoing ones sent
every 100 milliseconds and relayed through the peer the routing table (`unk_42CE38`) gives. Its methods need
compiled-out checks throughout (its inline `check()`), and its time differences come back through inlines
returning a time (`type_1CCA10::since`, `zero`). Last, its state for a debug display (`sub_1DF990`). 39
functions matched.

## `src/recovered/unit_1DFBB0.cpp`, kujuUI, from `0x1DFBB0`

The start of kujuUI (\COD\SHARED\UI\, game/kujuui.h), its data from `0x3E6CE0` (after the voice channel's):
the quad helpers (an `RwIm2DVertex` from a position, depth, texture coordinates and a packed RGBA colour,
`RwIm2DVertexSetIntRGBA` over its bytes; a quad's two triangles; a vertex's screen x and y) and the pad's
event mapper (`type_3E6CEC`: a target per button, pressed when released on the button last pressed on it,
with the front end's sound 3). The event types are kujuUI's own, named by cCaret's trace
(`kujuUI::cStateChange`, `kujuUI::eEventWasHandled`); the whole library is in namespace `kujuUI`, as
its parsed files already were. Then the border widget (`type_3E6D0C`, its type named "border"): a frame of
quads 3 in from its rectangle and, when not plain, a darker panel with a caption bar; its measures are named
constants of their own (two 3.0s and two 1.0s at separate addresses), and its creator (`type_3E6D3C`) reads
its rectangle from the parsed file's value. 25 functions matched.

## `src/recovered/unit_1E0670.cpp`, kujuUI's button, from `0x1E0670`

The button (`type_3E6D70`, its type named "button", up to `0x1E0D93`; cCaret's file follows): a selectable
widget (`type_3E76B4`: the widget plus two interfaces, over a look of its own, out of line at `0x1EFDA0`) that
runs its action when released after being pressed on it, with hooks for the focus coming and going, its
look's state following them. Its creator finds the action and hooks by id through two template lookups
instantiated here (`sub_1E0CB0`, `type_1ED670::sub_1E0D50`), warning (compiled out) when the source is
missing. 18 functions matched.

## `src/recovered/unit_1E09A0.cpp`, kujuUI's button creator (type_3E6DA0), `0x1E09A0`–

Split from unit_1E0670 (PLAN M7): the button's deferred adjustor thunk (`0x1E0990`) ends that object. The button's creator (`type_3E6DA0`, the "button" type) follows, with the two template lookups it instantiates (`sub_1E0CB0`, `type_1ED670::sub_1E0D50`).

## `src/recovered/unit_1E0DA0.cpp`, kujuUI's caret, `0x1E0DA0`–`0x1E0F73`

`\COD\SHARED\UI\cCaret.cpp`: `kujuUI::cCaret`, a selectable widget that blinks every half second. Its traces
name the class and three widget slots (`processEvent`, `givenFocus`, `lostFocus`, renamed through the
hierarchy); their reports are written with `#line`, `__FILE__`, `__LINE__` and `__FUNCSIG__`, the lines 55,
63 and 80. The STL map code after it (`0x1E0F80` on) is a template instantiated elsewhere. 9 functions
matched.

## `src/recovered/unit_1E0F80.cpp`, kujuUI's name map, `0x1E0F80`–`0x1E2155`

A small class of its own (`type_1E0F80`, game/kujuui.h) over `std::map<type_1C8A60, type_1ED670_object *>`:
find by name, insert (1 when new), clear and size, then the map's instantiations in the XDK's Dinkumware
code (`insert`, `find`, `clear`, `erase` twice, `_Insert`, `_Erase`, `_Tidy`, `_Init`, `_Lbound`, `_Rrotate`,
`_Buynode` twice; `_Lrotate` and the iterators' `_Inc` and `_Dec` fold with the class factory's and stream
handler's). The key's out-of-line members in unit_1C8A30 are its `operator=`, `operator==` and `operator<`
(std::less calls the last). 19 functions matched.

## `src/recovered/unit_1E2160.cpp`, kujuUI's combobox, from `0x1E2160`

First a font's glyph helpers (half a texel; a texel rectangle's texture rectangle, its divisions written
before the half-texel calls, which the compiler then evaluates first; the glyph, 0x16 bytes, from its file
entry, copied under another code, empty), then the combobox (`type_3E6F74`, its type named "combobox"): a
selectable widget stepping a value (`type_1E34A0`) up and down by the pad's buttons for its orientation (the
tables `unk_3E6F3C` and `unk_3E6F4C`) or by the pad's button repeat (`unk_504210`), showing it between a
prefix and suffix (`type_1CB670` strings) in a text, with an optional caption. Its step's repeat branch is
a conditional expression whose operands end in 0 (the image keeps that 0 in a temporary). The creator's
`vf_008` (`sub_1E2C40`) keeps its caption text as a `type_1CB670` (out-of-line default constructor,
`sub_E87E0`); its orientations are `a ? 0 : b ? 2 : 1` (the image's `setne; inc`), and its registry lookup
for the value is one more `sub_1E0D50` instance aliased to the folded copy. 26 functions matched.

## `src/recovered/unit_1E2BC0.cpp`, kujuUI's combobox creator (type_3E6FA4), `0x1E2BC0`–

Split from unit_1E2160 (PLAN M7): the combobox's deferred adjustor thunk (`0x1E2BB0`) ends that object. The combobox's creator (`type_3E6FA4`, the "combobox" type) follows with the eleven value definitions it reads (`unk_50331C`–`unk_5034D4`, built by its dynamic initializers `0x30C9F0` on).

## `src/recovered/unit_1E3430.cpp`, kujuUI's widget values, from `0x1E3430`

The value hook (`type_1E34A0`, off_3E7098: a registry object of kind 1 over off_3E70B0) with its out-of-line
constructor and destructor and the widget it is shown in, a value part's integer (`sub_1E3480`), 29 getters
of the value definitions widgets read (static `type_1C9590`s whose dynamic initializers are elsewhere, so
they are declared extern) and the two validators over them, built together on first use (`sub_1E3640`). 36
functions matched.

## `src/recovered/unit_1E37A0.cpp`, kujuUI's looks and drawing, from `0x1E37A0`

A selectable widget's look (`type_1E37A0`): a quad (`type_1EEAD0`, which the border's `unk_20` also is,
set over a rectangle rather than holding a caption) rebuilt when the state, rectangle or look changes from
the state's texture rectangle moved by its texture's offsets; the look's six states (`type_1E3BA0`) and
the filling of missing ones from the others; the validator of a look's values; the pad (`type_1E3DB0`,
moved from the front end's header into kujuUI) and the buttons its controls make (the table
`unk_42CE80`); and the render state the widgets draw with (`type_1E4130`: raster and filter set only when
they change, a full-screen quad for fades, depth 20). The pad's constructor is folded into RWS's
`CAttributeDataChunkIterator` constructor (0x12A1B0). Several frames needed slot-stating names
(`climb_names.py`); `sub_1E37E0`'s declarations are written highest slot first. 23 functions matched.

The look's empty destructor (`pDtor`, 0x1E41C0) is defined here; /OPT:ICF folds the other empty
functions into it.

## `src/recovered/unit_1E4250.cpp`, kujuUI's editbox, from `0x1E4250`

The editbox (`type_3E7228`, its type named "editbox"): a text field (`type_3E7BCC`, 0x1F4D00, not yet matched)
that opens the on-screen keyboard (`type_1F5D70`) on its text, takes the keyboard's text when entered and
tells its text source (`type_1F28C0`, a registry object of kind 3), and listens to that source (the
interface `type_3E7258` at +0xF0). Its two actions are a template over the owner (`type_3E7264<T>`,
calling the owner's methods through pointers to members; the members are defined outside the class, so they
stay out of line), whose base's pure destructor has its body at the end of this unit (`sub_1E5260`). The
registry's objects have a pure virtual destructor in slot 1, which the actions' vtable shows. `vf_014` has a
compiled-out check after its focus call (one register load). 27 functions matched.

## `src/recovered/unit_1E4D30.cpp`, kujuUI's edit box creator (type_3E7284), `0x1E4D30`–

Split from unit_1E4250 (PLAN M7): the edit box's deferred template and thunk functions (`0x1E4C50`–`0x1E4D20`) end that object. Its creator (`type_3E7284`) follows with the seven value definitions it reads (`unk_503E9C`–`unk_503FA4`) and their initializers.

## `src/recovered/unit_1E5280.cpp`, kujuUI's fonts, from `0x1E5280`

The font (`type_1E5A60`, game/kujufont.h, which now holds the font types the HUD's header had): a
reference-counted object (`type_3E7314`) with its glyphs, texture pages (`type_1E5830`, whose destructor
is defined in its class and so reserves its expansion in the font's destructor) and the list of fonts loaded;
the loader (`sub_1E5A80`, reading the font file into two scratch arrays, a template whose members are named
for what they do), the glyph search, the layout of a string into four text pages (`sub_1E6690`, colour codes
1 to 8) and its line measure (`sub_1E69D0`; a character's code goes through an inline with a local, and the
advance's getter is called on the search's result), and the font sets (`type_1E6350`: six fonts, the missing
ones filled from the others). The font's constructor (`sub_1E5280`) takes its last glyph through an inline
(`last_glyph`): with the address taken directly, the name's declined string constructor keeps 32 more bytes
of frame reserved. The characters every font copies (0x42CF80, `unk_42CF80`) are declared in
game/kujufont.h. 35 functions matched.

## `src/recovered/unit_1E62C0.cpp`, kujuUI's font lookups, `0x1E62C0`–

Split from unit_1E5280 (PLAN M7): the font's deferred page-list templates (`0x1E61A0`–`0x1E62B0`) end that object. The font-set lookups (`sub_1E62C0` on, `type_1E6350`), the "fontset" scope validator and its six value definitions with their initializers, and the text measures (`sub_1E6690`, `sub_1E69D0`, with the `skip_blanks` inline) follow.

## `src/recovered/unit_1E6B50.cpp`, kujuUI's images, from `0x1E6B50`

A 32-bit image (`type_1E6B50`, game/kujufont.h: width, height, pixels) read from a .tga (`sub_1E6CD0`: types 2
and 3 at 32, 24 or 8 bits, the header's reads and-ed into one flag, flipped unless the descriptor is set),
flipped top to bottom and halved (each pixel the mean of four by channel), and a global's getter
(`sub_1E72B0`). The .tga reader leaks its file on an unknown type, as the image does. 10 functions matched.

## `src/recovered/unit_1E72C0.cpp`, kujuUI's image library's pieces, from `0x1E72C0`

The library's images by name (`type_1E72C0`, over a map template `type_1EFCF0<T>` whose destructor and
insertion are folded into 0x1E0FA0 and 0x1EFCF0), which it owns and deletes, and an image (`type_1E7410`:
its name cut to 0x2B characters, its texture rectangle and its library). The library itself (0x1ECCE0 on,
"Enumerating images in ...") comes later. 5 functions matched.

## `src/recovered/unit_1E76A0.cpp`, kujuUI's integer value, from `0x1E76A0`

The integer value a combobox steps (`type_1E76A0`, a value hook: least, greatest, small and large steps,
wrapping unless told not to, a text at the least, prefix and suffix, and a hook told of changes; `std::min`
and `std::max` clamp it). Its display (`sub_1E7A80`) appends the number through `add_text`. 9 functions matched.

## `src/recovered/unit_1E7C40.cpp`, kujuUI's focus stack, from `0x1E7C40`

The focus stack (`type_1E7CF0`, dword_50420C): up to four widgets that take the pad from the others; the top
one gets the events and the focus, the others are drawn below a shade. Its array is the font loader's
scratch-array template (`type_1E61A0<T, N>`, game/kujufont.h, now holding all its members and an iterator);
the members this unit instantiates first (at, erase, find, end, empty, the iterator's step back and compare)
are matched here, the rest are folded into other units' copies. 24 functions matched.

## `src/recovered/unit_1E8350.cpp`, kujuUI's layout page, from `0x1E8350`

`cLayoutPage` (named by its traces, `\COD\SHARED\UI\cLayoutPage.cpp`): a container widget (`type_3E7584`, not yet
matched) whose widgets the pad's buttons move the focus between along links kept in a `std::set<type_1F8040>`
(widget, the widget a button leads to, the button), with the focused widget, the one to start on or return
to, and the held button repeating with the pad's button repeat. `focusAvailableWidget` keeps its two
traced checks (lines 207 and 209) through `#line`. The set's seventeen instances follow the page's
functions. 34 functions matched.

## `src/recovered/unit_1E9F60.cpp`, kujuUI's list box, from `0x1E9F60`

The list box (`type_3E7490`): rows (`type_3E74C0`, the next unit) in a `std::vector`, a page of them shown under
a look, a selection moved by the pad (up, down and a page either way, repeating with the on-screen keyboard's
timer, its direction kept in the keyboard's `unk_08`) and columns (`type_1ECA30`) moved by the pad's other
buttons. The vector's instances follow (explicitly instantiated, so `insert` and `_Insert_n` are compiled
for the insertion). The layout, insertion and removal take row n through `row_at` (a free inline returning
`iterator(begin() + n)`: the image's one more iterator copy), and the layout's end iterator is an explicit
`iterator(end())` copy for the same reason. 42 functions matched.

## `src/recovered/unit_1EBE50.cpp`, kujuUI's list box rows, creator and columns, from `0x1EBE50`

A list box's row (`type_3E74C0`, abstract: slot 1 fills its texts) with a look and a text per column in two
of kujuUI's arrays; the list box's creator ("listbox": a row height from its value or its font's line height,
the rows that fit) and its columns (`type_1ECA30`, a registry object of kind 2: widths fitted to the list box,
alignments). The array template gains `clear` and `back` (their instances for these rows are this unit's).
27 functions matched.

## `src/recovered/unit_1EC490.cpp`, kujuUI's list box creator (type_3E74C8), `0x1EC490`–

Split from unit_1EBE50 (PLAN M7): the list box's deferred page-list templates (to `0x1EC470`) end that object; its creator (`type_3E74C8`) follows.

## `src/recovered/unit_1ECBD0.cpp`, kujuUI's image library, from `0x1ECBD0`

The image library (`type_1ECCE0`, off_3E7504, counted): a texture loaded from its name's `.dds` (images over
0x40000 pixels are halved first; the `.tga` read is compiled out) and its images by name, read from its
`.index` file's "image" entries; the libraries loaded form a list (dword_504224) searched by name, and the
library-by-name function returns a counted pointer to one, loading it when needed. The counted pointer's
destructor and release are placed here (`type_E8780<type_1ECCE0>`). The looks' old `type_1ED650` was this
library. All 12 functions matched; the constructor (`sub_1ECBD0`) reads the texture's raster through `get_unk_00`.
`sub_1E72B0` now returns the libraries' directory (a string, not a number).

## `src/recovered/unit_1ED730.cpp`, kujuUI's container widget, from `0x1ED730`

The container widget (`type_3E7584`, off_3E7584; the layout page's base): its children in a
`std::vector<type_3E7D08 *>`, which it passes its slots 2, 3, 5 and 6 on to and whose rectangles it bounds
about the screen's centre line; children added last or first, room made, and their first and end given.
Its vtable has 13 slots: slot 13 (`vf_034`) is the layout page's own. The vector's instances follow (explicit
instantiation). 19 functions matched.

## `src/recovered/unit_1EE870.cpp`, kujuUI's root widget and the pad's button changes, from `0x1EE870`

A widget with nothing of its own (`type_3E75B8`, the game's interface's root: it takes every event and
draws nothing); the pad's buttons held (`type_1EE900`), a button's bit, and the events their changes make
into the pad's queue (`type_1E7560`); the selectable widget's interface's destructor and its move to a point.
`cStateChange` gains inline constructors (the queue's array builds through the empty one). 9 functions
matched, with the buttons' clearing constructor (`sub_1EE9E0`, which /OPT:ICF shares with two lookups'
constructors; their aliases stay).

## `src/recovered/unit_1EEAD0.cpp`, kujuUI's quad, from `0x1EEAD0`

The quad (`type_1EEAD0`: six Im2D vertices, two triangles): built at the origin, put off screen, drawn,
moved to a point (every vertex by the difference), set from a rectangle and texture rectangle, and coloured
(the colour's red and blue swapped into the vertices' ARGB). 6 functions matched.

## `src/recovered/unit_1EECE0.cpp`, kujuUI's textures, from `0x1EECE0`

An RwImage over a 32-bit image's pixels (`type_1EECE0`; its stride through an inline setter, whose depth
argument the compiler substitutes unfolded), a raster made from one or a texture read through the DDS
loader (`type_1EEEE0`, destroyed accordingly), and the loaders from a `.tga` and a `.bin`. `rw/baimage.h`
gains RwImage, its macros, RwImageCreate, RwImageDestroy and RwRasterSetFromImage. 8 functions matched.

## `src/recovered/unit_1EF040.cpp`, kujuUI's plain raster and the pad's button repeat, from `0x1EF040`

A 4 by 4 texture raster made on first use, and the pad's held-button repeat (`type_1EF160`, `unk_504210`,
formerly taken for the on-screen keyboard): the time held, run, stopped and started, stepped by the time
passed (firing every 0.25 s) and the steps held past the first 0.5 s. 7 functions matched.

## `src/recovered/unit_1EF1E0.cpp`, kujuUI's looks' libraries, from `0x1EF1E0`

The image libraries' validator (`type_1EF260`, a scope validator with the "images" definition and the looks'
validator as a child; one, made on first use and deleted), and the looks' libraries (`type_1EF3A0`): the image
libraries in use, in one of kujuUI's arrays of counted pointers (the array gains `take`, and its `clear` now
destroys each item), and the looks built from their scopes into a `std::list` (each state's image found in
any library) and named in a name map (whose insertion, `sub_1EFCF0`, is placed here). The array's, its
iterator's and the list's instances follow. 26 functions matched.

## `src/recovered/unit_1EFDA0.cpp`, kujuUI's selectable widget, from `0x1EFDA0`

The selectable widget (`type_3E76B4`: a widget with a look over its rectangle, hidden or not, abstract: its
destructor is pure): built, destroyed, drawn unless hidden, its look's state set and given, and its
interfaces' slots (the look set, the rectangle given and set, hidden given and set), and its rectangle; then
the registry object's pure destructor's body (`type_3E70B0`). 12 functions matched; its first argument is a
look typed as a string (docs/questions.md).

## `src/recovered/unit_1F00E0.cpp`, kujuUI's static image, from `0x1F00E0`

The static image (`cStaticImage`, named by its traces, `\COD\SHARED\UI\cStaticImage.cpp`): a selectable
widget that takes no focus and no events (its handlers only report being called), its deleting destructor's
adjustor thunk, and its creator ("image": a look over its rectangle, hooked into the registry). 12
functions matched.

## `src/recovered/unit_1F0230.cpp`, kujuUI's static image creator (type_3E7830), `0x1F0230`–

Split from unit_1F00E0 (PLAN M7): cStaticImage's deferred adjustor thunk (`0x1F0220`) ends that object; its creator (`type_3E7830`) follows.

## `src/recovered/unit_1F0410.cpp`, kujuUI's static text, from `0x1F0410`

The static text (`cStaticText`, named by its traces, `\COD\SHARED\UI\cStaticText.cpp`): a widget showing a
text (`type_1F1420`), told its state and text as a text source, optionally bound to a text; it takes no focus
and no events. Its own slots 12 to 15 reach the text's rectangle and hidden flag through the text's
interface (virtual calls on the member through a base reference). 16 functions matched.

## `src/recovered/unit_1F07C0.cpp`, kujuUI's text button, from `0x1F07C0`

The text button (`type_3E79B4`: a button with a text over it that is its own text source, bound to a text
object or showing a localised default), its adjustor thunks, and its creator ("textbutton", which hooks the
registry's interfaces of the widget already in `*arg_14` before storing the new one: the image does the
same). The creator's kind value is `a ? 0 : (b ? 2 : 1)` (setne and inc). 15 functions matched.

## `src/recovered/unit_1F0AE0.cpp`, kujuUI's text button creator (type_3E79E4), `0x1F0AE0`–

Split from unit_1F07C0 (PLAN M7): the text button's deferred adjustor thunks (`0x1F0AC0`, `0x1F0AD0`) end that object; its creator (`type_3E79E4`) follows.

## `src/recovered/unit_1F1040.cpp`, kujuUI's static text's creator, from `0x1F1040`

The static text's creator ("text"): a text over its rectangle in its font, bound to a text object (the
source) or else given its localised text (a named `type_1A5EA0` under /GS). 6 functions matched.

## `src/recovered/unit_1F1420.cpp`, kujuUI's text, from `0x1F1420`

The text (`type_1F1420`: a string in a font set's font over a rectangle, laid out into four texture pages,
pulsing between its state's colour and state 0's when highlighted, cut to fit with the ellipsis unless shown
whole), the font's measures (a text's width and height, wrapping, and how many characters fit: its switch
stops at NUL and newline, which makes a jump table), `std::string`'s `operator+(const string &, const char *)`,
the text object a widget shows and edits (`type_1F28C0`), and the text source's destructor. The ellipsis
getter (`sub_1CBBB0`) now returns a reference. 27 functions matched: the constructors (`sub_1F1420`,
`sub_1F2790`) match with their texts `type_1CB670` (whose default constructor is out of line, `sub_E87E0`),
their setters assigning through the base; `sub_1F1420`'s last argument is an integer. The layout (`sub_1F15C0`)
reads the pulse's second colour through the font set's `get_colour` inline (the image's unfolded `[0]`) and the
rectangle through its `width()`/`height()` inlines, whose `this` slots place the getter call after the cut
text's temporary.

## `src/recovered/unit_1F26B0.cpp`, kujuUI's text measure and type_1F28C0, `0x1F26B0`–

Split from unit_1F1420 (PLAN M7): the deferred std::string operator+ (`0x1F25F0`) ends the text's object. The font's text measure (`type_1E5A60::sub_1F26B0`) and `type_1F28C0` follow.

## `src/recovered/unit_1F2920.cpp`, kujuUI's widget factory and top layout page, from `0x1F2920`

The widget factory (`type_1F2A00`, one, made on first use: the creators by name, the layout files' validator
built from theirs, and the layout file's own values) and the top layout page (`cTopLayoutPage`, named by
its traces, `\COD\SHARED\UI\cTopLayoutPage.cpp`, declared in the new `game/kujuilayout.h`): loaded from its
file in steps (the file, its image libraries, its looks and font sets, then its widgets), with a title over
a border, its links resolved by widget name, and a load error that reports itself (`throwLoadError`). The
font sets' `std::list` and the validators' array (`type_1E61A0<cScopeValidator, 8>`) instances follow.
37 functions matched. The widget builder (`sub_1F3510`) reads the factory's values through inline getters
(`get_unk_A60` and the rest, each with its own `this` slot) and fetches the factory for its widget call through
`widget_factory()`, an inline that puts it in a temporary before the arguments; its title text is a named
`type_1A5EA0` (the function's /GS cookie) and the untitled case passes a `type_1CB670()` temporary (out-of-line
default constructor, `sub_E87E0`).

## `src/recovered/unit_1F4D00.cpp`, kujuUI's text field, from `0x1F4D00`

The text field (`type_3E7BCC`: a selectable widget with a text and a caret, its caret placed after the text's
first characters, its state following whether it may be entered): built, destroyed, its slots, its text set
and cut, and its adjustor thunk. The caret's rectangle is read through the rectangle's inline `height()` and
`width()`. The key handler (`sub_1F52C0`) takes the key as unsigned; its delete case tests the text through the
field's `text_length()` inline (a direct `size()` there reserves two more slots before the inline string
copy). 17 functions matched.

## `src/recovered/unit_1F5870.cpp`, kujuUI's on-screen keyboard's key, from `0x1F5870`

The keyboard's key (`type_3E7C30`: a text button that is also an action, doing nothing, run when the key is
given no action of its own; it takes every event) and its three adjustor thunks. The action's slots 2 and 3
are renamed `pvf_008` and `pvf_00C` (the key has the widget's `vf_008` and `vf_00C` too). 7 functions matched.

## `src/recovered/unit_1F5A50.cpp`, kujuUI's text page, from `0x1F5A50`

The text page (`type_1F5A50`, game/kujufont.h): a growing array of Im2D vertices (six a quad, the room doubled
as needed), placed by moving every vertex by the change, drawn as a triangle list and emptied. Its layout is
now typed (vertices, count, room, position); the border's frame, declared as a separate "quad list"
(`type_1F5A90`), is the same class and now uses it. 8 functions matched.

## `src/recovered/unit_1F5D70.cpp`, kujuUI's on-screen keyboard, from `0x1F5D70`

The on-screen keyboard (`type_1F5D70`, now a container widget): a text field over a 5 by 11 grid of keys built
from the layout table at `0x42D140` (codes above 11 are characters, the others the keys "Done" to ">"; a code
repeated along a row makes one wide key), its layouts switched by shift, caps lock and the accent, symbol and
alphabet keys, the pad moving the focus and typing, and a key typed on the pad finding its key and layout. The
original's switch picking a special key's action lets "Space" fall through into the default (no action).
Two inlines stand in for addressless code: the key code at a row and column (read flat within the layout) and
the first rectangle centred on the screen's centre line. Its actions are two template instances: the editbox's
two-method action and a one-method one (`type_3E7CE8`). 33 functions matched.

## `src/recovered/unit_1F76E0.cpp`, kujuUI's widget, from `0x1F76E0`

The widget base (`type_3E7D08`): its constructor, destructor, focus and slot 7 (passed to the parent); the
interface's root widget (`dword_504390`, set with the time) and its frame (`sub_1F77D0`: the time passed, the
root updated and drawn with a draw state, the log drawn, the camera cleared and shown around it when asked);
and the widget factory's building of a widget from a scope by its type's creator, with its compiled-out
failure traces. The creators' slot 2 still declares the looks and font sets as integers (seven matched
overrides use that signature), so the factory casts them. 10 functions matched.

## `src/recovered/unit_1F7A20.cpp`, kujuUI's widget creators and scope readers, from `0x1F7A20`

The widget creators' base (`type_3E7D94`: its constructor, destructor and validator, closed by "end"), the
factory's readers of a scope's values (a widget's rectangle, from "position" or from a corner and a size in its
look's texture's pixels; its look and font set by name; whether it is plain; its hooks into the registry, whose
kinds 4 and 5 are declared only as far as their setter), the compiled-out check they trace through
(`sub_1F7A60`), the layout page's link (constructors and order) and the looks' state names with the index
lookup. The readers keep the creators' integer and string types for the looks and font sets and cast where they
use them; the scope validator's second argument is now typed as the closing keyword it is. 23 functions matched.

## `src/recovered/unit_1F81E0.cpp`, the network's bit stream, from `0x1F81E0`

The bit stream (`type_1F8560`, game/netmsg.h): the bits a value needs (a nibble table), and the stream's bits,
floats, signed values, ranged floats and integers, message numbers (in nibbles, their count first) and bytes
(through a second, padded stream over them: a new inline constructor). The methods carry compiled-out checks
(`BITSTREAM_CHECK`) whose conditions are chosen for the register loads they account for; `sub_1F8520` and
`sub_1F8560` move one bit, not a dword. The two word helpers they call (`sub_1F81E0`, `sub_1F8300`: a bit field
in two big-endian words, 64-bit shifts and masks) swap the words' bytes with hand-written inline assembly
(`ror bx, 8` through `ebx`), so they stay binary under the plan; their C, which matched with the assembly in
macros, is not kept in the tree. 19 functions matched.

## `src/recovered/unit_1F8BF0.cpp`, the memory pools, from `0x1F8BF0`

The memory pools (game/pool.h, restructured): the counting pool (`type_1F8BF0`, abstract), the heap pool
(`type_3E7E0C`: new and delete; one function-local static made on first use, with its exit thunk `_$E2`) and
the block pool (`type_1F8E00`, 0x20 bytes: a heap run in a block taken from its parent pool, through its second
base `type_3E7E30` and that base's inline allocation, freeing and reset; the five global pools are block pools).
Compiled-out count checks (`POOL_CHECK`) account for the registers. 20 functions matched, with the unwind
pieces of three.

## `src/recovered/unit_1F90E0.cpp`, the block pools' heaps, from `0x1F90E0`

Doug Lea's malloc 2.7.0 (game/dlmalloc.h): identified by its state's layout (fast bins at +4, top at +0x2C, the
bins at +0x34, the binmap at +0x434, the statistics to +0x470), its size classes and bin macros and the shape of
each function; built without mmap, with a 128K trim threshold, an 8-byte page and the fast-chunk bit's 2.7.0
sense. The state in use is a global the pools switch (`dword_5043A8`), and MORECORE carves the state's own
block (two fields appended at +0x474). Written with the library's macros and local names, which give its frame
layouts: malloc, sYSMALLOc, free, sYSTRIm, malloc_consolidate and malloc_init_state, and the state's getter,
setter and initialisation over a block. 10 functions matched.

## `src/recovered/unit_1FA6E0.cpp`, the network player's motion curves, from `0x1FA6E0`

The network player's motion between two updates (`type_1FAE60`, game/netplayer.h): a cubic set from a Bezier
segment (`type_1FA6E0`: its coefficients, point and derivative), a straight segment held at its ends
(`type_1FB3C0`, whose point is an inline kept out of line), and the fit that picks one (straight when the
velocity along the way would not cover the distance) with the position and velocity at a time. The vector
type (`type_1F8560_v`, game/netvec.h) gains its arithmetic as inlines; the evaluators keep their intermediate
vectors in named locals. Compiled-out checks (`CURVE_CHECK`, one kept local) account for three register shifts
and an unused slot. 9 functions matched.

## `src/recovered/unit_1FB520.cpp`, the game browser's rows, from `0x1FB520`

The game browser's row (`type_1FB520`, game/browser.h: a list box row over a session), its name, the browser's
sort mode and two string helpers of `type_1A5EA0` (a number and a text appended, out of line and shared).
The rows' texts (`sub_1FB7B0`) build them in `type_1CB670` texts (default-constructed out of line,
`sub_E87E0`). The rows' order (`sub_1FB5A0`) compares the names as two named `type_1A5EA0`s whose inline constructors
call std::string's `const char *` constructor out of line; that COMDAT is placed from here at 0x1C5700.
11 functions matched.

## `src/recovered/unit_1FBBF0.cpp`, the in-game menus' manager, from `0x1FBBF0`

`InGameMenuManager` (game/ingamemenu.h; named by its traces): the one instance, the menu shown and hidden, its
passing of kujuUI's events, updates and drawing to the pad's widget stack, and the menus' loop over the camera
(the game kept stepping, the pad's events queued and handled, the front end's message box shown or closed as
the pad leaves or returns, the frame drawn and the menu changed when the front end asks). Its menus
(`type_1FBDA0_menu`) are declared only as far as used. The pad's buttons, the event queue and the pad gain
their missing members; `sub_20A540` now returns the widget it gives. 11 functions matched, with the unwind
pieces of two.

## `src/recovered/unit_1FA180.cpp`, the pooled list, from `0x1FA180`

The pooled list (`type_1FA230`, game/poollist.h) that the packet engine's queues use: its nodes
(`type_1FA180_node`, whose constructor folds into 0x1EFD70), insertion, removal, the cursor and the
emptying. 15 functions matched.

## `src/recovered/unit_0A2080.cpp`, from `0x0A2080`

SceneTestTrigger, a soldier spawner for testing scenes: its MakeNew, constructor and destructor. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A2080–0x0A21C6`; 4 functions matched.

## `src/recovered/unit_0A23F0.cpp`, from `0x0A23F0`

CCESSPoolTrigger, the CCESS pool manager: its MakeNew, constructor and destructor. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A23F0–0x0A2C10`; 8 functions matched.

## `src/recovered/unit_0A2C20.cpp`, from `0x0A2C20`

ConfinedAreaTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A2C20–0x0A2DC0`; 7 functions matched.

## `src/recovered/unit_0A2DD0.cpp`, from `0x0A2DD0`

CustomTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A2DD0–0x0A3500`; 9 functions matched.

## `src/recovered/unit_0A3510.cpp`, from `0x0A3510`

DestructableObjectTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A3510–0x0A3A30`; 6 functions matched.

## `src/recovered/unit_0A3A40.cpp`, from `0x0A3A40`

MeshSwapDestructableObjectTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A3A40–0x0A3E70`; 9 functions matched.

## `src/recovered/unit_0A3E80.cpp`, from `0x0A3E80`

DogTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A3E80–0x0A4948`; 8 functions matched.

## `src/recovered/unit_0A4950.cpp`, from `0x0A4950`

CMountedWeaponBehavior: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A4950–0x0A5350`; 6 functions matched.

## `src/recovered/unit_0A5360.cpp`, from `0x0A5360`

MountedWeaponTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A5360–0x0A58A0`; 8 functions matched.

## `src/recovered/unit_0A58B0.cpp`, from `0x0A58B0`

CNPCWeaponBehavior: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A58B0–0x0A6C40`; 7 functions matched.

## `src/recovered/unit_0A6C50.cpp`, from `0x0A6C50`

XBOXPadMap: its MakeNew, constructor and destructor. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A6C50–0x0A6D7C`; 4 functions matched.

## `src/recovered/unit_0A6D80.cpp`, from `0x0A6D80`

ParticleTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A6D80–0x0A8FB0`; 11 functions matched.

## `src/recovered/unit_0A8FC0.cpp`, from `0x0A8FC0`

PathNode: its MakeNew, constructor and destructor. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A8FC0–0x0A90DC`; 4 functions matched.

## `src/recovered/unit_0A90E0.cpp`, from `0x0A90E0`

CPickupSelector: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A90E0–0x0A93A0`; 7 functions matched.

## `src/recovered/unit_0A93B0.cpp`, from `0x0A93B0`

PickupTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0A93B0–0x0A9970`; 10 functions matched.

## `src/recovered/unit_0AD1B0.cpp`, from `0x0AD1B0`

ProjectileGeneratorTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0AD1B0–0x0AF148`; 7 functions matched.

## `src/recovered/unit_0AF150.cpp`, from `0x0AF150`

RenderTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0AF150–0x0AF92D`; 6 functions matched.

## `src/recovered/unit_0AF9C0.cpp`, from `0x0AF9C0`

SceneTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0AF9C0–0x0AFBB0`; 6 functions matched.

## `src/recovered/unit_0AFBC0.cpp`, from `0x0AFBC0`

SectionInfo: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0AFBC0–0x0B0178`; 10 functions matched.

## `src/recovered/unit_0B0180.cpp`, from `0x0B0180`

SectionTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B0180–0x0B0408`; 6 functions matched.

## `src/recovered/unit_0B0410.cpp`, from `0x0B0410`

StartingSections: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B0410–0x0B07C8`; 7 functions matched.

## `src/recovered/unit_0B07D0.cpp`, from `0x0B07D0`

CShellBehaviorClass: its MakeNew, constructor, destructor and HandleAttributes (242 commands, which
set the HUD's and the front end's settings and the difficulty and damage multipliers). Its original
file name is not in the image, so it is named for its start address.

Placed range `0x0B07D0–0x0B6EA8`; 6 functions matched.

## `src/recovered/unit_0B6EB0.cpp`, from `0x0B6EB0`

CShellLevelBehaviorClass: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B6EB0–0x0B7328`; 6 functions matched.

## `src/recovered/unit_0B7330.cpp`, from `0x0B7330`

SimpleMechanicTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B7330–0x0B7A98`; 9 functions matched.

## `src/recovered/unit_0B7AA0.cpp`, from `0x0B7AA0`

SoldierTrigger, the soldier spawner: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B7AA0–0x0B9108`; 11 functions matched.

## `src/recovered/unit_0B9110.cpp`, from `0x0B9110`

CSoundBankSelector: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B9110–0x0B99B8`; 9 functions matched.

## `src/recovered/unit_0B99C0.cpp`, from `0x0B99C0`

SoundBankTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B99C0–0x0B9E98`; 7 functions matched.

## `src/recovered/unit_0B9EA0.cpp`, from `0x0B9EA0`

SplinePath: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0B9EA0–0x0BA9DA`; all 10 functions matched.
The empty destructor `sub_BA030` requires this unit's `/EHa` setting:
73 bytes / six relocations, plus its 8-byte unwind and 10-byte handler.
All 15 previously annotated pieces also match with that setting.

## `src/recovered/unit_0BA9E0.cpp`, from `0x0BA9E0`

StopSoundStreamTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BA9E0–0x0BAC48`; 8 functions matched.

## `src/recovered/unit_0BAC50.cpp`, from `0x0BAC50`

StreamTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BAC50–0x0BB378`; 9 functions matched.

## `src/recovered/unit_0BB380.cpp`, from `0x0BB380`

StreamVolume: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BB380–0x0BB9A8`; 8 functions matched.

## `src/recovered/unit_0BB9B0.cpp`, from `0x0BB9B0`

Trigger, the base trigger behaviour: its MakeNew, constructor, destructor and handlers, and the helpers the derived triggers share. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BB9B0–0x0BEAA8`; 40 functions matched.

## `src/recovered/unit_0BEAB0.cpp`, from `0x0BEAB0`

VehicleEnterExitTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BEAB0–0x0BF648`; 12 functions matched.

## `src/recovered/unit_0BF650.cpp`, from `0x0BF650`

FlakTrigger: its MakeNew, constructor, destructor and handlers, and VehicleTrigger's flag accessors the image places after its constructor. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BF650–0x0BF958`; 11 functions matched.

## `src/recovered/unit_0BF960.cpp`, from `0x0BF960`

VehicleTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0BF960–0x0C10A8`; 11 functions matched.

## `src/recovered/unit_0C10B0.cpp`, from `0x0C10B0`

CWeaponBehavior and the four explosive behaviours derived from it: their MakeNews, constructors, destructors and handlers. The original file name is not in the image, so it is named for its start address.

Placed range `0x0C10B0–0x0C5378`; 33 functions matched.

## `src/recovered/unit_0C5380.cpp`, from `0x0C5380`

WorldLight: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C5380–0x0C5A58`; 9 functions matched.

## `src/recovered/unit_0C5A60.cpp`, from `0x0C5A60`

LevelInfo: its MakeNew, constructor, destructor and handler. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C5A60–0x0C5D68`; 7 functions matched.

## `src/recovered/unit_0C5D70.cpp`, from `0x0C5D70`

CPickupBehavior: its MakeNew, constructor, destructor and handler. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C5D70–0x0C60D8`; 6 functions matched.

## `src/recovered/unit_0C60E0.cpp`, from `0x0C60E0`

LevelClumpBankParamTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C60E0–0x0C6498`; 7 functions matched.

## `src/recovered/unit_0C64A0.cpp`, from `0x0C64A0`

StreamClumpTrigger: its MakeNew, constructor, destructor and handler. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C64A0–0x0C66B8`; 7 functions matched.

## `src/recovered/unit_0C66C0.cpp`, from `0x0C66C0`

LevelScriptTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C66C0–0x0C6A78`; 7 functions matched.

## `src/recovered/unit_0C6A80.cpp`, from `0x0C6A80`

PlaySoundTrigger: its MakeNew, constructor, destructor and handler. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C6A80–0x0C6DE8`; 7 functions matched.

## `src/recovered/unit_0C6DF0.cpp`, from `0x0C6DF0`

GimpTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C6DF0–0x0C7CD8`; 12 functions matched.

## `src/recovered/unit_0C7CE0.cpp`, from `0x0C7CE0`

CGlobalSounds: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0C7CE0–0x0CA2B8`; 7 functions matched.

## `src/recovered/unit_0CA2C0.cpp`, from `0x0CA2C0`

CPoolSizes: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CA2C0–0x0CA788`; 7 functions matched.

## `src/recovered/unit_0CA790.cpp`, from `0x0CA790`

CMountedWeaponSelector: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CA790–0x0CAA88`; 7 functions matched.

## `src/recovered/unit_0CAA90.cpp`, from `0x0CAA90`

LadderTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CAA90–0x0CAE18`; 9 functions matched.

## `src/recovered/unit_0CAE20.cpp`, from `0x0CAE20`

ShrimpTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CAE20–0x0CB428`; 11 functions matched.

## `src/recovered/unit_0CB430.cpp`, from `0x0CB430`

PulseZoneTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CB430–0x0CB9C8`; 9 functions matched.

## `src/recovered/unit_0CB9D0.cpp`, from `0x0CB9D0`

GimpVehicleTrigger: its MakeNew, constructor, destructor and handlers. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CB9D0–0x0CC088`; 7 functions matched.

## `src/recovered/unit_0CC090.cpp`, from `0x0CC090`

EndLevelTrigger: its MakeNew, constructor, destructor and methods. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CC090–0x0CC368`; 11 functions matched.

## `src/recovered/unit_0CC370.cpp`, from `0x0CC370`

FogTrigger: its MakeNew, constructor, destructor and handler. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CC370–0x0CC648`; 8 functions matched.

## `src/recovered/unit_0CC650.cpp`, from `0x0CC650`

PASTrigger: its MakeNew, constructor, destructor and handler. Its original file name is not in the image, so it is named for its start address.

Placed range `0x0CC650–0x0CC898`; 9 functions matched.

## `src/recovered/unit_11E440.cpp`, from `0x11E440`

The projectile generators' shell kind (type_11E440, types/type_1227C0.h). The original file name is not in the image, so it is named for its start address.

Placed range `0x11E440–0x11EE18`; 9 functions matched.

## `src/recovered/unit_11EE20.cpp`, from `0x11EE20`

The projectile generators' base (type_1227C0, types/type_1227C0.h), their pool and id table, and the "PG_" helpers they share. The original file name is not in the image, so it is named for its start address.

Placed range `0x11EE20–0x1227E4`; 51 functions matched, including both factories and their shared exception cleanup.

## `src/recovered/unit_1A5E10.cpp`, from `0x1A5E10`

An id with two strings (types/type_505188.h), and the library's string members it needs out of line.

Placed range `0x1A5E10–0x1A6134`; 9 functions matched.

## `src/recovered/unit_1BD6A0.cpp`, from `0x1BD6A0`

Network messages' own methods (game/netmsg.h).

Placed range `0x1BD6A0–0x1BD92F`; 6 functions matched.

## `src/recovered/unit_1C0830.cpp`, from `0x1C0830`

Network messages' own methods (game/netmsg.h).

Placed range `0x1C0830–0x1C0901`; 4 functions matched.

## `src/recovered/unit_1C2F90.cpp`, from `0x1C2F90`

Network messages' own methods (game/netmsg.h).

Placed range `0x1C2F90–0x1C311D`; 6 functions matched.

## `src/recovered/unit_1E7490.cpp`, from `0x1E7490`

kujuUI's look given to a widget by name, and the pad's event queue (game/kujuui.h).

Placed range `0x1E7490–0x1E7692`; 9 functions matched.

## `src/recovered/unit_1FC320.cpp`, from `0x1FC320`

The front end's options page (game/options.h): its selectors' template (six instances), the page's destruction and its settings read and written. The page's constructor (sub_1FC320) default-constructs its texts as `type_1CB670` (out of line, sub_E87E0) and adds its last label through the page's `get_unk_198()` inline (a direct member access leaves 8 more bytes of frame).

Placed range `0x1FC320–0x1FF1B8`; 57 functions matched.

## `src/recovered/unit_1FF250.cpp`, from `0x1FF250`

The in-game screens (game/ingamescreens.h): the pause menu, the controls' legend and the screens over the game, built for the game type, shown, hidden and run a frame at a time. The legend's update (sub_1FFE80) builds its text in a std::string through the library's out-of-line default constructor (sub_E87E0); its service getter (get_unk_1120) and the legend's draw (show_legend) are free inlines with no address, placed by slot order and frame size.

Placed range `0x1FF250–0x20095B`; 16 functions matched.

## `src/recovered/unit_200960.cpp`, from `0x200960`

The shell on a camera (game/frontend.h): its in-game menus' manager pointed at the opening menu once the menus are loaded, run, and put away with its items.

Placed range `0x200960–0x200B8A`; 6 functions matched.

## `src/recovered/unit_200B90.cpp`, from `0x1FF1C0`

The host's game options (game/hostoptions.h): the options read from the front end's settings copy and written back, the checks the pages' widgets make, and the selectors' members and map code this unit holds. The settings' read (sub_201890) reads the settings copy through inline accessors (game/uiglue.h), which spend the inline budget its text's destructor chain would otherwise leave unused slots with (docs/questions.md). The constructor (sub_200B90) keeps each minutes text in a block of its own inside its loops. The time limit's update (sub_2016A0) passes its values as literals (the temporaries take their slots in order of use).

Placed range `0x1FF1C0–0x203D7B`; 72 functions matched (the key selector's pick by value, `sub_201E10`, comes from its explicit instantiation). The time limit's remove and pick (sub_202350, sub_2023E0) are emitted here through its update.

## `src/recovered/unit_203D80.cpp`, from `0x203D80`

The shell's hooks (game/frontend.h): the front end's sound player, and the front end's sounds played on the listener or at the player.

Placed range `0x203D80–0x203FFD`; 3 functions matched.

## `src/recovered/unit_204020.cpp`, from `0x204020`

The in-game menus (game/ingamemenu.h): the fourteen menus built and deleted, queued to load and loaded a step at a time, and the menu arg_0. The menus (unk_5044F0) and the load queue (unk_50452C) are kujuUI's arrays of fourteen (game/kujufont.h); their constructors run from the compiler's initialisers (0x30DAD0, 0x30DAE0), placed with the arrays' definitions in the unit.

The arrays' constructor (`sub_2049B0`, which only those initialisers call) is placed from here through an explicit instantiation.

Placed range `0x204020–0x2049C7`; 18 functions matched.

## `src/recovered/unit_2049D0.cpp`, from `0x2049D0`

The Live login pages (game/livemenu.h): the player's name and friends list shown over each, and the network warning shown while the Xbox Live connection is down (one instance, shared by the pages that ask for it). The player's status text (`sub_205070`) builds its text in a `type_1CB670` local (default-constructed out of line, `sub_E87E0`) from the sign-in statuses' table (`dword_42D278`).

Placed range `0x2049D0–0x2053BC`; all 20 functions matched.

## `src/recovered/unit_2053C0.cpp`, from `0x2053C0`

The create session page (game/livemenu.h): its actions over the host's options and the advanced options' page, the options' defaults for the game type and the check on the session's name. The texts' fill (sub_205880) passes the name it falls back to (the signed-in user's) to a compiled-out debug print (`debug_text`, types/type_505188.h), whose expansion its frame shows.

Placed range `0x2053C0–0x20618C`; 21 functions matched.

## `src/recovered/unit_206190.cpp`, from `0x206190`

The create session menu (in-game menu 0, game/livemenu.h): the create session page over "CreateSession.layout", starting the game as the host and going back to the menu it came from.

Placed range `0x206190–0x2062AE`; 5 functions matched.

## `src/recovered/unit_2062B0.cpp`, from `0x2062B0`

The find session page (in-game menu 1, game/livemenu.h): its search settings reset, the search started with them, and the minimum players kept below the players picked. The settings' reset (sub_206850) keeps its level key above the /GS cookie with the names `lv_54` and `lv_10`, and the actions' constructor (sub_206B50) is emitted by an explicit instantiation.

Placed range `0x2062B0–0x206BDC`; all 10 functions matched.

## `src/recovered/unit_206D10.cpp`, from `0x206D10`

The instant action page (in-game menu 2, game/livemenu.h): a game of the type picked found at once (the in-game menu 3 then), or back to the Live menu.

Placed range `0x206D10–0x20713C`; 12 functions matched.

## `src/recovered/unit_207160.cpp`, from `0x207140`

The instant action's results (in-game menu 3, game/livemenu.h): the search started with the game type picked, the sessions found scored and sorted, the one shown stepped on, and the pages shown while searching, after a failed join and when nothing is found.

Placed range `0x207140–0x2097DE`; all 38 functions matched (the results list's _Incsize, sub_209500, among them).

## `src/recovered/unit_2097E0.cpp`, from `0x2097E0`

The system link's create session menu (in-game menu 8, game/livemenu.h): the create session page over "XboxSysLinkCreateSession.layout", starting the game as the host over the system link and going back to the menu it came from.

Placed range `0x2097E0–0x2098E9`; 5 functions matched.

## `src/recovered/unit_2098F0.cpp`, from `0x2098F0`

The system link's menu (in-game menu 10, game/livemenu.h): finding a session, creating one, the options, or back.

Placed range `0x2098F0–0x209BEC`; 9 functions matched.

## `src/recovered/unit_209BF0.cpp`, from `0x209BF0`

The system link's session list (in-game menu 9, game/livemenu.h): the session list page over "XboxSysLinkSessionList.layout".

Placed range `0x209BF0–0x209CFB`; 6 functions matched.

## `src/recovered/unit_209D00.cpp`, from `0x209D00`

In-game menu 11's sign-in page and the Live options (game/livemenu.h): the options' actions, their text of the appearing status, and the one options page (sub_20A540).

Placed range `0x209D00–0x20A66C`; all 19 functions matched.

## `src/recovered/unit_20A670.cpp`, from `0x20A670`

In-game menu 12's sign-in page (game/livemenu.h): waits for the network system's state and opens the next menu.

Placed range `0x20A670–0x20A7AF`; 4 functions matched.

## `src/recovered/unit_20A7B0.cpp`, from `0x20A7B0`

The message menu (in-game menu 4, game/livemenu.h): a text and an "OK" that closes it and calls the caller's callback.

Placed range `0x20A7B0–0x20AA0C`; 7 functions matched.

## `src/recovered/unit_20AA10.cpp`, from `0x20AA10`

The multiplayer menu (in-game menu 13, game/livemenu.h): back to the dashboard, playing on Xbox Live or over the system link, and the join failure page.

Placed range `0x20AA10–0x20B56C`; all 17 functions matched.

## `src/recovered/unit_20B570.cpp`, from `0x20B570`

The in-game options (in-game menu 5, game/livemenu.h): the front end's options page (game/options.h) under "Options.layout", with "Back" and "Accept", following the voice chat's speakers.

Placed range `0x20B570–0x20B9CC`; 11 functions matched.

## `src/recovered/unit_20B9D0.cpp`, from `0x20B9D0`

The Xbox Live menu (in-game menu 6, game/livemenu.h): instant action, finding or creating a session, the Live options, the options, back, and the join failure page.

Placed range `0x20B9D0–0x20C2EC`; all 13 functions matched.

## `src/recovered/unit_20C2F0.cpp`, from `0x20C2F0`

The Xbox Live session list (in-game menu 7, game/livemenu.h): the session list page over "SessionList.layout".

Placed range `0x20C2F0–0x20C46B`; 8 functions matched.

## `src/recovered/unit_20C470.cpp`, from `0x20C470`

The session list page (game/livemenu.h), the base of the in-game menus 7 and 9: searching for sessions, listing them sorted in its columns, and joining the one selected.

Placed range `0x20C470–0x20E84B`; all 40 functions matched (the update, `sub_20D4C0`, among them). The sessions' fill (`sub_20D8D0`) reads the network game's results (0x74-byte `type_1FB520_session` entries) through slot 0x78. The rows' index for a session (`sub_20DC80`) takes its name by value and tests it with the strings' inline `operator<`. The search's start (`sub_20CB70`) builds its filter in a `type_4F8054_4C` local.

The sort's label (`sub_20E060`) keeps its four column names in a local array whose elements unwind through the null-safe string's implicit destructor (sub_43900), and its formatted text is a named local; the names `lv_10`, `lv_A4` and `lv_30` give the frame. The rows' list's _Incsize (`sub_20E420`) matches as emitted.

## `src/recovered/unit_20E850.cpp`, from `0x20E850`

The Live menus' base (game/livemenu.h): built over a layout with its objects by name and the "LiveMenu" action, loaded to the end on demand.

Placed range `0x20E850–0x20EB2C`; 10 functions matched.

## `src/recovered/unit_20EB30.cpp`, from `0x20EB30`

The searching pages' dots (game/livemenu.h): a text with zero to three dots cycling four times a second as the time `flt_505180` advances; each dot is appended through a free inline with a reference parameter. The score limit's constructor after it (`sub_20EC00`) passes its value's texts as `type_1CB670` temporaries (default-constructed out of line, `sub_E87E0`); its deleting destructor (`sub_20EDD0`) comes with it.

Placed range `0x20EB30–0x20EDFA`; all 3 functions matched.

## `src/recovered/unit_20EE00.cpp`, from `0x20EE00`

The respawn selector (game/hostoptions.h, a member of the host options): its destruction, and its option selector's instance over type_20EFD0_value with that instance's map code. The selector's constructor (sub_20EE00) builds its labels through type_1CB670's localised-text constructor from a key (sub_1CB6B0; config/aliases.txt) and unwinds them through sub_43900.

Placed range `0x20EE00–0x210178`; all 17 functions matched.

## `src/recovered/unit_210180.cpp`, from `0x210180`

The game type selector (game/hostoptions.h, a member of the host options): its destruction, and its option selector's instance over type_210430_value with that instance's map code and the selectors' shared slot 2 (0x2106A0). The selector's constructor (sub_210180) builds its labels through the localised text's out-of-line constructor from a key (folded into sub_1CB6B0; config/aliases.txt).

Placed range `0x210180–0x211678`; all 18 functions matched.

## `src/recovered/unit_211680.cpp`, from `0x211680`

The level selector (game/hostoptions.h, a member of the host options): its destruction, and its option selector's instance over the level key with that instance's map code, the key pair's destructor and the selectors' shared slot 3 (0x211AE0). The selector's constructor (sub_211680) builds its labels through the localised text's out-of-line constructor from a key (folded into sub_1CB6B0; config/aliases.txt); its keys convert implicitly from the levels (a key temporary made before the label), each level index checked twice (LEVELS_CHECK), and "Any" is the level at 0x505188 (`unk_505188`).

Placed range `0x211680–0x212A80`; all 18 functions matched.

## `src/recovered/unit_212A80.cpp`, from `0x212A80`

The respawn order selector's option selector instance over type_212C70_value (game/hostoptions.h; the rest of its code sits with the host options' unit): its constructor, its value added, and its map's insertion; and the server name text (type_213610). The respawn order selector's constructor (sub_212A80) builds its labels through the localised text's out-of-line constructor from a key (folded into sub_1CB6B0; config/aliases.txt); with it its deleting destructor (0x212C40) is emitted.

Placed range `0x212A80–0x21367C`; all 13 functions matched.

## `src/recovered/unit_213680.cpp`, from `0x213680`

The players selector (game/hostoptions.h, a member of the host options): its destruction, and its option selector's instance over type_2138C0_value with that instance's map code; and a text's number appended (sub_214A70). The selector's constructor (sub_213680) builds its labels through the localised text's out-of-line constructor from a key (folded into sub_1CB6B0; config/aliases.txt).

Placed range `0x213680–0x214A8C`; all 18 functions matched.

## `src/recovered/unit_214A90.cpp`, from `0x214A90`

The yes-or-no rules' selectors' option selector instance over type_214C30_value (game/hostoptions.h; the rest of its code sits with the host options' unit): its constructor, its value added, and its map's insertion. The yes-or-no selector's constructor (sub_214A90, picking its value argument by address) builds its labels through the localised text's out-of-line constructor from a key (folded into sub_1CB6B0; config/aliases.txt); with it its deleting destructor (0x214C00, over the compiler's destructor at 0x201370) is emitted.

Placed range `0x214A90–0x215595`; all 10 functions matched.

## `src/recovered/unit_215740.cpp`, from `0x2155A0`

The cancel warnings (game/ingamepages.h): the one page showing a warning over the game with its text and "Cancel", and the warnings' calls to show, hide and retext it.

Placed range `0x2155A0–0x215B3C`; 17 functions matched.

## `src/recovered/unit_215B40.cpp`, from `0x215B40`

The game type vote (game/ingamepages.h): a vote page and its question (slot 22, sub_215BD0), built in two `type_1CB670` texts whose default constructor is out of line (`sub_E87E0`).

Placed range `0x215B40–0x215BCC`; 5 functions matched.

## `src/recovered/unit_215D40.cpp`, from `0x215D40`

The next map vote (game/ingamepages.h): a vote page and its question (slot 22, sub_215DC0), built in two `type_1CB670` texts whose default constructor is out of line (`sub_E87E0`).

Placed range `0x215D40–0x215DBC`; 4 functions matched.

## `src/recovered/unit_215F30.cpp`, from `0x215F30`

The kick vote (game/ingamepages.h): a vote page and its question (slot 22, sub_215FB0), built in two `type_1CB670` texts whose default constructor is out of line (`sub_E87E0`).

Placed range `0x215F30–0x215FAC`; 4 functions matched.

## `src/recovered/unit_216130.cpp`, from `0x216130`

The votes' base (game/ingamepages.h): a page over the pause menu with the question and "yes" and "no". Its showing (slot 2, sub_2162D0) sets the question from slot 22.

Placed range `0x216130–0x216435`; all 11 functions matched.

## `src/recovered/unit_216440.cpp`, from `0x216440`

The debug menu (game/ingamepages.h): killing the player, resetting the round and adding to its time, then back to the game.

Placed range `0x216440–0x21675C`; 9 functions matched.

## `src/recovered/unit_216760.cpp`, from `0x216760`

The defect asked (game/ingamepages.h): "yes" and "no" answered to the pause menu.

Placed range `0x216760–0x21698C`; 8 functions matched.

## `src/recovered/unit_216990.cpp`, from `0x216990`

The end of round host settings (game/ingamepages.h): the host options pages' base over "EndRoundHostSettings.layout", going back to the widget it was opened from.

Placed range `0x216990–0x216AA3`; 5 functions matched.

## `src/recovered/unit_216C10.cpp`, from `0x216AB0`

The error screens (game/ingamepages.h): a message and "continue". Setting the message (sub_216C10) unwinds its text through the library's out-of-line string destructor (sub_43900): the null-safe string's implicit destructor, which the unwind funclet calls, is folded into it (config/aliases.txt).

Placed range `0x216AB0–0x216D1C`; all 7 functions matched.

## `src/recovered/unit_216D20.cpp`, from `0x216D20`

The game settings (game/ingamepages.h): the front end's options page over the pause menu, written back on "Accept", and the player's kill.

Placed range `0x216D20–0x2171EC`; 10 functions matched.

## `src/recovered/unit_217670.cpp`, from `0x2171F0`

The two-prompt dialog (game/ingamepages.h): a title, a prompt and two options (and "Back") running the caller's actions, one instance shown and hidden over the pad's widget stack.

Placed range `0x2171F0–0x2179DC`; 18 functions matched.

## `src/recovered/unit_2179E0.cpp`, from `0x2179E0`

The host's options (game/ingamepages.h): the game settings and a player's kick, from the pause menu.

Placed range `0x2179E0–0x217CCC`; 12 functions matched.

## `src/recovered/unit_217CD0.cpp`, from `0x217CD0`

The online settings (game/ingamepages.h): the host options pages' base over "OnlineSettings.layout" with "SaveNow", which writes and sends the options and leaves the pause menu.

Placed range `0x217CD0–0x217F3C`; 8 functions matched.

## `src/recovered/unit_217F40.cpp`, from `0x217F40`

The initial team selection (game/ingamepages.h): the team selection's base with "auto", which lets the game pick the team.

Placed range `0x217F40–0x2181DC`; 8 functions matched.

## `src/recovered/unit_2181E0.cpp`, from `0x2181E0`

The kick page (game/ingamepages.h): the other players listed by name, the one picked kicked after a confirmation. The selection's handler (its columns' slot 4, sub_2186C0) names the player in the confirmation and pushes it. The rows' list's _Incsize (sub_218AB0) matches: its unwinding reaches std::string's out-of-line destructor (sub_43900) as ours does.

Placed range `0x2181E0–0x218DCB`; all 21 functions matched.

## `src/recovered/unit_218DD0.cpp`, from `0x218DD0`

The in-game controls' legend (game/ingamepages.h): two texts over the pause menu.

Placed range `0x218DD0–0x218F3F`; 4 functions matched.

## `src/recovered/unit_218F40.cpp`, from `0x218F40`

A sign-in page with no layout of its own (game/ingamepages.h): the service started last asked for step 6, and back while its state is not 6.

Placed range `0x218F40–0x219009`; 5 functions matched.

## `src/recovered/unit_219010.cpp`, from `0x219010`

The in-game Live options (game/ingamepages.h): the friends and players lists, appearing offline and signing out, with their status texts. "SignOut"'s run (sub_219560) asks through `type_1CB670` texts (one default-constructed out of line, `sub_E87E0`), its slots named as a scoreboard's "quit" prompt's.

Placed range `0x219010–0x219C1C`; all 18 functions matched.

## `src/recovered/unit_219C20.cpp`, from `0x219C20`

A sign-in page with no layout of its own (game/ingamepages.h): the service started last asked for step 7, its Live feature ended when left, and back while its state is not 7.

Placed range `0x219C20–0x219D09`; 6 functions matched.

## `src/recovered/unit_219D10.cpp`, from `0x219D10`

The next round asked (game/ingamepages.h): "yes" and "no" answering the pause menu.

Placed range `0x219D10–0x219F5C`; 9 functions matched.

## `src/recovered/unit_219F60.cpp`, from `0x219F60`

The host options pages' base (game/ingamepages.h): the host's options over an in-game page, saved, and their advanced page opened, cancelled and closed.

Placed range `0x219F60–0x21A5DC`; all 15 functions matched.

## `src/recovered/unit_21A5E0.cpp`, from `0x21A5E0`

The pause menu (game/ingamepages.h): its entries' pages, the one shown and moving between them, its entries' actions and the vote's texts. The update (sub_21BA50) builds "Xbox Live Options" in a buffer declared in an inner block (so the /GS cookie sits below the function's scalars). The loading (`vf_03C`, sub_21BD60) is not matched yet: a draft with the level read through an inline holding the two `LEVELS_CHECK`s (the image's two-register shift) matches every instruction, but its frame is one slot (4 bytes) smaller than the image's, the slot missing among the unused ones between its two name reads (docs/questions.md). Its string helper `sub_21CA90` (`sub_1C85D0`'s result returned) is matched.

Placed range `0x21A5E0–0x21CB0C`; 46 functions matched, including the pause-menu loader and its cleanup/EH pieces.

## `src/recovered/unit_21CB10.cpp`, from `0x21CB10`

The in-game pages' base (game/ingamepages.h): a Live menus' page over a layout with "Back" and "Options" into the pause menu, and whether it is shown.

Placed range `0x21CB10–0x21CE55`; 13 functions matched.

## `src/recovered/unit_21CE60.cpp`, from `0x21CE60`

A row of the kick list (game/ingamepages.h): a player's index and name (copied from a by-value text), and its texts (slot 1, sub_21CF90).

Placed range `0x21CE60–0x21D0CA`; all 7 functions matched.

## `src/recovered/unit_21D0D0.cpp`, from `0x21D0D0`

The quit asked (game/ingamepages.h): "yes" and "no" answered to the pause menu, or to the page's parent without one. Its showing (slot 2, sub_21D270) sets its question.

Placed range `0x21D0D0–0x21D46C`; all 9 functions matched.

## `src/recovered/unit_21D470.cpp`, from `0x21D470`

A scoreboard's players (game/ingamepages.h): their rows, ordered by their two counts, and the columns holding them. The rows' texts (sub_21D5A0) build the counts in `type_1CB670` locals (default-constructed out of line, `sub_E87E0`) through the `add_number` inline. The rows' list's _Incsize (sub_21DCF0) matches: its unwinding reaches std::string's out-of-line destructor (sub_43900) as ours does.

Placed range `0x21D470–0x21DFDD`; all 23 functions matched.

## `src/recovered/unit_21DFE0.cpp`, from `0x21DFE0`

A scoreboard's options (game/ingamepages.h): the host's settings, level and countdown, a client's quit and wait, and continuing. The countdown's text (sub_21E3E0) appends through the shared `add_text` inline (types/type_505188.h), and "quit" (sub_21E880) keeps its four texts in named locals (names from local_names).

Placed range `0x21DFE0–0x21EB2C`; all 24 functions matched.

## `src/recovered/unit_21EB30.cpp`, from `0x21EB30`

The scoreboards' base (game/ingamepages.h): its flags loaded and dropped, the side shown swapped by the pad and the texts refreshed as the players change. Its constructor (`sub_21EB30`) matches with the flags' default constructor closure (`sub_21EFC0`, `??_F`, from the array of flag libraries). Its text builder (sub_21F1C0) matches: the ranking's locals in an inner block (only the local player's index above the /GS cookie), the team texts' block holding its buffer and score, and four compiled-out text diagnostics after the team texts (the inline budget that sets the frame). Showing (sub_21FB60) now matches
(1,909 bytes, 88 relocations), with its 156-byte cleanup and 10-byte EH handler.
The team-count accessor is free, preserving the three result slots without
receiver-expansion leftovers; the branch retains seven no-code text diagnostics
and two unused inline locals. The HUD and scoreboard agree on type_1CB670 as
the return type of sub_1C5350, whose body is now matched in unit_1C3D20.cpp.

Placed range `0x21EB30–0x22079C`; showing and its unwind pieces are now matched; nothing remains binary inside it.

## `src/recovered/unit_2207A0.cpp`, from `0x2207A0`

A scoreboard (game/ingamepages.h): the scoreboards' base with its options page shown, updated, drawn and given the pad's events first, and "continue" leaving the front end's screens.

Placed range `0x2207A0–0x220C3C`; 14 functions matched.

## `src/recovered/unit_220C40.cpp`, from `0x220C40`

The team selection's base (game/ingamepages.h): the two teams to join, their flags shown as each is focused, and the flags' looks loaded from their libraries.

Placed range `0x220C40–0x22158C`; 16 functions matched.

## `src/recovered/unit_221590.cpp`, from `0x221590`

A "use now" question (game/ingamepages.h): "yes" and "no" answering the pause menu.

Placed range `0x221590–0x22177C`; 6 functions matched.

## `src/recovered/unit_221780.cpp`, from `0x221780`

A vote's confirmation (game/ingamepages.h): "ok" carries the vote out and "cancel" takes the confirmation off the pad's widget stack. Its question (sub_221A80) keeps the kick case's name in a nested block and passes the formatted buffer to a compiled-out debug print (`debug_text`), whose expansion the frame shows.

Placed range `0x221780–0x2220DC`; 14 functions matched.

## `src/recovered/unit_2220E0.cpp`, from `0x2220E0`

The vote over the game type (game/ingamepages.h): the type picked and "confirm" calling the vote.

Placed range `0x2220E0–0x22234C`; 7 functions matched.

## `src/recovered/unit_222350.cpp`, from `0x222350`

The vote over the level (game/ingamepages.h): the level picked and "confirm" calling the vote.

Placed range `0x222350–0x2225DC`; 8 functions matched.

## `src/recovered/unit_2225E0.cpp`, from `0x2225E0`

The votes' choice (game/ingamepages.h): a player, the map or the game type to vote on.

Placed range `0x2225E0–0x22295C`; 13 functions matched.

## `src/recovered/unit_222960.cpp`, from `0x222960`

The vote on a player (game/ingamepages.h): the other players listed by name, the one picked voted on after a confirmation. The columns' selection handler (sub_222F60) is the kick page's, over this page's members.

Placed range `0x222960–0x22327B`; all 15 functions matched.

## `src/recovered/unit_223280.cpp`, from `0x223280`

The weapon selection (game/ingamepages.h): the weapon class picked and set, its picture per team, and the weapon classes' selector (the option selector's instance over type_224010_value, with that instance's map code).

Placed range `0x223280–0x225215`; all 32 functions matched. The picture (`sub_223D00`) builds its hint in `type_1CB670` locals; its class (`unk_18C`) is an integer.

## `src/recovered/unit_225220.cpp`, from `0x225220`

The Live engine's font renderer (game/uixfont.h): UIX's text drawn with three kujuUI fonts, and the fonts' wide-string layout it uses.

Placed range `0x225220–0x2261C0`; 16 functions matched.

## `src/recovered/unit_2261C0.cpp`, from `0x2261C0`

The late service (game/liveservice.h): the Live engine's host, which starts the engine with the UI and audio plugins, runs it each frame, starts its features, follows the mute list and joins the sessions friends invite to; the players list's items are kept in a std::vector, whose instances follow.

Placed range `0x2261C0–0x228D61`; 43 functions matched.

## `src/recovered/unit_228D70.cpp`, from `0x228D70`

The UI plugin the late service hands the Live engine (game/uixfont.h): its objects (textboxes, listboxes and backgrounds) drawn with the Live engine's font renderer and the skin's images.

Placed range `0x228D70–0x22ADF3`; 43 functions matched.

## `src/recovered/unit_22AE00.cpp`, from `0x22AE00`

The UIX audio plugin and players list items the late service hands the Live engine (game/uixfont.h).

Placed range `0x22AE00–0x22B1AA`; 12 functions matched (the voice chat's status tests `sub_22B040` and `sub_22B0C0` through the free inline `peer_in`).

## `src/rw/tool/dict/rtdict.c`, RenderWare's dictionary toolkit, `0x22B1B0`–`0x22B5C7`

RenderWare 3.7.2's own `rtdict.c`, unchanged but for the `// match:` lines, built with RenderWare's flags
(docs/toolchain.md). All 12 of its functions in the image match; the rest of the file was dropped by the
linker. The database's names for 0x22B410 and 0x22B450 are off by one function: they are
`RtDictDestroy` and `RtDictSchemaCreateDict`.

## `src/rw/plugin/uvanim/`, RenderWare's UV animation plugin, `0x22B5D0`–`0x22CB5A`

`rpuvanim.c`, `stdkey.c`, `param.c` and `linear.c` from RenderWare 3.7.2, unchanged but for the
`// match:` lines: 35 functions match. The image keeps `RpMaterialUVAnimAddAnimTime` (0x22BCB0) beside
`SetCurrentTime`, and the param keyframes' empty `MulRecip` (0x22C6E0) stands for the empty `Add` too.
Still binary (the 3.6 code differs from 3.7.2): `RpMaterialUVAnimApplyUpdate`, `UVAnimCopy`,
`UVAnimWrite`, `CreateDummyAnim` and `RpUVAnimParamKeyFrameDataInitFromMatrix`.

## `src/rw/`, the RenderWare library from its own sources (M6)

The RenderWare library code in the image (the core, world, plugins and toolkits) partly compiles byte for
byte from the 3.7.2 sources with the in-project RenderWare's flags (docs/toolchain.md). Each source is a
unit under `src/rw/<its RWSDK path>`, unchanged but for `// match:` lines on the functions that match (the
rest are 3.6 differences, left binary, or were dropped by the linker); internal headers sit beside them
and the generated ones in `include/rw/sdk`. The core's `balibtyp.h` carries the image's `RwGlobals`
layout, like `rwplcore.h`. Matrices and frames are 16-byte aligned (`RWALIGN`, `rwMATRIXALIGNMENT` and
`rwFRAMEALIGNMENT` in `rwplcore.h` and `os/win/ostypes.h`: the image's matrix, frame and light free lists
pass 0x10), and `tool/2d/gstate.h`'s `Rt2dGlobalVars` has the image's extra word after `colorCache`. Calls the image makes to /OPT:ICF-folded copies are aliased. Other platforms'
driver and pipe sources are not used, even where a function's bytes agree. The RtFS toolkit
(`tool/fsyst/`, with the Xbox file system written from the Godfather debug build) is VC7.0 and fully matched.

Collision follow-up (2026-10-01): `RpCollSectorLineItInit` (0x2C2B20, 680 bytes) and
`GeometryForAllTriIntsecLine` (0x2C07F0, 2316 bytes) now match after the shared interval
macro computes each endpoint inside its sign branch, always evaluating inf before sup.

Placed so far, 712 functions (per source): plugin/matfx/rpmatfx.c (42), src/batextur.c (26), plugin/uvanim/rpuvanim.c (21), src/baframe.c (20), src/baimage.c (19), plugin/pvs/rppvs.c (17), plugin/hanim/rphanim.c (16), tool/2d/gstate.c (16), driver/common/palquant.c (15), world/bageomet.c (15), plugin/skin2/rpskin.c (14), src/plcore/bamemory.c (14), plugin/morph/rpmorph.c (13), plugin/ptank/ptank.c (13), world/bameshop.c (13), plugin/prtstd/emitter.c (12), plugin/prtstd/rpprtstd.c (12), plugin/spline/rpspline.c (12), tool/2d/font.c (12), tool/anim/rtanim.c (12), tool/dict/rtdict.c (12), plugin/collis/colldata.c (11), plugin/matfx/multiTex.c (11), plugin/matfx/multiTexEffect.c (11), plugin/prtstd/standard.c (11), src/plcore/balist.c (11), tool/2d/path.c (11), world/bamesh.c (11), plugin/prtstd/prop.c (10), src/baraster.c (10), src/plcore/baplcore.c (10), plugin/userdata/rpusrdat.c (9), world/balight.c (9), world/bamateri.c (9), plugin/mipkl/rpmipkl.c (8), src/plcore/batkreg.c (8), src/plcore/rwstring.c (8), tool/2d/brush.c (8), plugin/anisot/rpanisot.c (7), plugin/dmorph/dmphgeom.c (7), world/babinwor.c (7), plugin/dmorph/dmphintp.c (6), plugin/hanim/stdkey.c (6), plugin/uvanim/linear.c (6), src/pipe/p2/p2heap.c (6), src/plcore/babinary.c (6), src/plcore/batkbin.c (6), tool/charse/rtcharse.c (6), plugin/collis/collquery.c (5), plugin/collis/ctdata.c (5), plugin/prtstd/eclass.c (5), plugin/prtstd/pclass.c (5), plugin/prtstd/pptank.c (5), plugin/random/rprandom.c (5), src/plcore/baerr.c (5), src/plcore/baresour.c (5), world/bamatlst.c (5), world/basector.c (5), plugin/collis/ctquery.c (4), plugin/pvs/rppvsaux.c (4), plugin/uvanim/param.c (4), plugin/uvanim/stdkey.c (4), src/basync.c (4), tool/2d/tri.c (4), tool/slerp/rtslerp.c (4), plugin/lodatm/rplodatm.c (3), src/babbox.c (3), src/babintex.c (3), src/baimras.c (3), src/baresamp.c (3), src/pipe/p2/p2resort.c (3), src/plcore/bastream.c (3), tool/2d/object.c (3), tool/2danim/anim.c (3), tool/2danim/maestro.c (3), src/babinfrm.c (2), src/pipe/p2/p2altmdl.c (2), src/plcore/bacolor.c (2), src/plcore/rwgrp.c (2), tool/2danim/message.c (2), tool/pitexd/rtpitexd.c (2), tool/quat/rtquat.c (2), os/win/osintf.c (1), plugin/dmorph/rpdmorph.c (1), src/babincam.c (1), src/batypehf.c (1), src/plcore/resmem.c (1), tool/2d/2dstr.c (1), tool/2d/scene.c (1), tool/2d/shape.c (1), tool/2d/stroke.c (1), tool/2danim/bucket.c (1), tool/2danim/button.c (1), tool/2danim/cel.c (1), tool/2danim/props.c (1), tool/2danim/strlabel.c (1), tool/intsec/rtintsec.c (1).

## `src/recovered/unit_0A9980.cpp`, from `0x0A9980`

PlayerTrigger (types/PlayerTrigger.h): its MakeNew, constructor, destructor, key, HandleEvents, the
weapons' restore, the difficulty's scaling, the weapon helpers, the settings copied into the player entity,
the death animations' registration, the free function sub_AA3F0 that clears their flag, and its
HandleAttributes (`sub_AA400`, 116 commands; command 5 reads a weapons block, command 18 the camera's
view angles from the video mode).

Placed range `0x0A9980–0x0AD1B0`; 16 functions matched.


## `src/recovered/unit_1BE4D0.cpp`, from `0x1BE4D0`

cNetPlayerTrigger (types/cNetPlayerTrigger.h), the network game's player trigger over PlayerTrigger: its
MakeNew, constructor (dword_4F8130), compiler-written destructor, the local player's respawn with the weapons
chosen, the network player's set-up (dword_4F8060), its move to a matrix, the player's lookup and its
HandleEvents.

Placed range `0x1BE4D0–0x1BEBA8`; 10 functions matched.

## RenderWare Audio (`src/rwa/`), 0x23B750–0x252000

No source, headers or symbols exist for RenderWare Audio; it is decompiled from the image alone
(`src/rwa/rwa.h` holds the shared types, named by offset). The library is x87 code built with
`/O2 /Ob1 /G6 /Gy` (no `/arch:SSE`; `/Ob2` inlines calls the image keeps). Its functions are padded
with `nop` rather than `int3`, so each placed function's `config/splits.txt` range ends at its code
(`tools/addfn.py --trim`), and functions IDA missed (reached only through tables) are added by hand
with `tools/addfn.py`. A field the image copies with `fld`/`fstp` is `volatile` (VC7.1 copies a
plain float with integer moves).

### `src/rwa/rwavirtualvoiceobj.c`, the virtual voice object, `0x23B750`–`0x23BFE0`

The library's PS2 header (`docs/reference/rwacore_ps2.h`, Criterion's 2001 `rwacore.h`, kept as
naming evidence: its sections name the source files, and its public types and prototypes the
functions) shows this is the virtual voice object: `RwaVirtualVoiceRegister` (0x23BF60) registers
the definition with the virtual voice interface, and the parameter handlers are its inputs and
outputs. Its definition set-up `sub_23BD10` sets the state alignment through rwaint.h's
`rwaLog2`/`rwaPow2` macros (each use calls `sub_242150`, which returns `RwUInt8`). The handlers are reached only through the parameter
table at 0x42E1C8 (24-byte entries: parameter UUID, 0, 0, type UUID, 1, handler); twelve of them
were missing from the database. The database's `RwaStreamCreate` and `RwaListenerUnregister` names
here (also at 0x24DF20 and 0x24EC60, the same code in other objects) are kept until evidence names
them. 38 matched.

### `src/rwa/rwawave.c`, waves and wave dictionaries, `0x23BFE0`–

The wave state set-up, the dictionary file load's helpers (header conversion, chunked stream read,
offset fix-ups), the dictionary list (`RwaWaveDictFindByIndex`, `RwaWaveDictGetCount`,
`RwaWaveDictContainsWave`, `RwaWaveDictUsingAllWaveDef`, `RwaWaveDictFindWaveByIndex`,
`RwaWaveDictAddWave`, `RwaWaveDictGetWorking`, `RwaWaveDictRemoveAllWave`) and its open and close.
The Xbox `RwaWaveDict` follows the PS2 header's layout (unique id, the wave list's `RwaLLNode`, then
the Xbox flags and type bytes and the dictionary list link at 0x1C). One translation unit: a caller
here keeps a value in `edx` across a call to a function of this file. `RwaWaveDictDestroy` (0x23CAA0) releases an unused wave twice when no dictionary is loaded,
as the image does. Dictionary file load 23C490 now matches (624 bytes / 22
relocations). Save the three node fields in a RwaLLNode local, keep params at
function scope, and store the computed dictionary address to state before
assigning the local pointer. All 29 annotations in this unit match.

### `src/rwa/unit_23CC10.c`, the listener object, `0x23CC10`–

Not in the PS2 header (the output interface there has listener position, velocity, up and at
parameters). Its creation (the database's `RwaListenerCreate`) and unregistration, and the
parameter handlers of the table at 0x42E488 (position, velocity, orientation, up, at, right and
three scalars, each setter marking a dirty bit at +0x70); four handlers were missing from the
database. Its definition set-up `sub_23D450` and registration `sub_23D690` (missing from the
database; added with `tools/addfn.py`) are matched. Initializer 23CC70 and the up/at
setters 23D2A0/23D320 now also match (208/96/96 bytes). Their cross product uses
the exact nested parentheses of the original RW bavector.h macro. The initializer
returns the listener pointer; the creation callback registration reflects this.
Spatialization 23CD40 now also matches (1,040 bytes / 49 relocations). Its
typed listener-state view begins at object +0x28 and preserves existing direct
member access through a union. Declare at between rolloff and velocityScale;
use the original RW Sub/Dot macro parentheses and qualified initial x reads.
Original qualifiers are unknown. All 24 annotations match.

### `src/rwa/rwaobjdef.c`, object definitions, `0x23D710`–

`RwaObjDefAssignID` (the text ID set before the UUID), `RwaObjDefGetDefaultCreationParams`, the
instance pool set-up (`sub_23D7C0`: a free list or a pool sized `maxInstances`, aligned to
`1 << (flags >> 28)`) and allocation, the child-definition searches (by interface, by UUID) and
their callbacks. The Xbox `RwaObjDef` (rwaint.h) is laid out differently from the PS2 header's.
Instance-memory release `sub_23D8B0` now matches (144 bytes / four relocations,
including 10 NOP bytes). A separate unused state-offset output local lets the
compiler reuse the input argument home without retaining an extra flags pointer.
The allocation pointer is recovered before choosing free-list, pool, heap or
custom release. No qualifiers or compiler flags changed.

Creation group 23DAA0/23DB30/23DE20/23DF00/23DFB0 is now matched: 848 bytes
total. The creator clears its eight-byte list with memset. Parameter defaults
use a 16-bit index and branch-local table pointers. The definition initializer
clears the packed stateSize/stateAlign fields separately, then sets alignment
with the existing macro, preserving the final OR. The shared type exposes the
packed +0x40 word through a union; its flags view is retained for other code.
Repro: rwa_objdef_create_current.py. SetupParams 23DD00 now also matches
(288 bytes / five relocations): allocation and supplied-table paths form
an if/else and share the final return. Repro: rwa_objdef_setup_return_trials.py.
Search 23D970 and destroy 23DB90 now also match (176/208 bytes). Search keeps
the root separately and qualifies two argument-home reads; the original qualifier
is unknown. Destroy uses the first interface link before setting its head pointer
and repeats the instances clear inside all three allocator branches. All tracked
functions in this unit are placed.

### `src/rwa/rwaobj.c`, object instances, `0x23EF00`–`0x23F770`

Named after `_rwaObjFindFixed` and `_rwaObjCloseModule`. An instance (`rwaInstance`, 0x28 bytes,
the PS2 header's `RwaObj`) holds its definition, a link in the instance list (0x506A28), its
sub-object list and link, flags, a state pointer and its parent. Its state, an optional extra word
(flag 2, the handle count) and the parameter tables (flag 1: an `rwaInput` per input and a list per
output, connections from a free list at 0x506A34) follow it in one allocation sized by
`sub_23F300`. The module creates the top-level object (0x506A58) in a static buffer.
`DSPHandle_Stop` (the database's name) destroys an instance. The execute walks `sub_23F0D0`
and `sub_23F140` now match 112 bytes each, including 11 NOP bytes, with no relocations.
Their callback/status values are object pointers (RwaObjExecuteFunc in the reference
header and all installed callbacks). A qualified incoming pointer copied to a normal
local preserves the two parameter-home reloads; the original qualifier is unknown.
All 20 annotations in this unit match. Core wrappers now correctly pass FALSE as
the execute flag, with sub_23F2F0 declared as the no-argument top-level getter.

### `src/rwa/rwaobject.c`, object handles, `0x23F770`–`0x23FAD0`

The PS2 header's `rwaobject` group: handles (`RwaObjHandle`, 0x18 bytes: instance, interface,
link, flags, reference count) from a free list, their creation and release (the database's
`DSPResource_Release`) and the parameter accessors through the interface's set and get tables.

Getter dispatcher `sub_23F8E0` now matches (2026-10-01; 48 bytes including padding):
widen the parameter number to RwUInt32 before the call. Setter dispatcher
`Behavior_DispatchCallback` (23F8B0) now also matches: 48 bytes including two
NOP bytes, no relocations. Load handle->obj into a local before selecting
the setter; keep the widened parameter and named data value before the call.

### `src/rwa/unit_23FAD0.c`, the stream object, `0x23FAD0`–`0x240980`

A 0xDA0-byte instance that plays a stream file: its source (a name or a UUID), player (+0xEC) and
play queue (+0x154). A worker thread runs the playing streams under a semaphore (the xapilib
`WaitForSingleObject`/`ReleaseSemaphore` calls need `_Name@N` aliases). `hSemaphore` and `hObject`
are plain globals, since the set-up takes their addresses; the other module data is static. The
parameter handlers wrap the locked operations. Unlink callback `sub_23FC00`
now matches (96 bytes / seven relocations). A named count and explicit qualified
count/input accesses preserve the load and decrement order before the wait.
Original qualifiers are unknown and documented in source.
The position query `sub_23FEE0` now matches (2026-10-01; 240 bytes including
padding). A local out pointer copied from the query parameter selects the
original integer-to-float temporary stack slot.

### `src/rwa/rwauuid.c`, UUIDs and unique IDs, `0x240980`–`0x240C50`

The PS2 header's rwauuid.h: `RwaUUIDCompare` (an inlined `memcmp`), the UUID and vector byte
swaps, the free list of copied UUIDs and the `RwaUniqueID` UUID and name setters and releases.
The case-insensitive compare `sub_240B90` folds its two operands with different tests (the
second one also folds characters up to 'A'), as the image does.

### `src/rwa/rwastreamsourceobj.c`, the stream source object, `0x240C50`–`0x2416D0`

Named after the database's `RwaStreamSourceInterfaceRegister` and
`__rwaStreamSourceCreationParamsInit`. A 0x208-byte instance whose stream node state (+0x5C)
reads a stream file's regions into a play queue. Its execute callback, the queue fill and
completion callbacks, position requests, parameter handlers, definition set-up and registration
are here. The node's flags and region index are `volatile`; the image reloads them. Not yet
matched: the creation callback `sub_241230`.

### `src/rwa/unit_2416D0.c`, threads and semaphores, `0x2416D0`–`0x2417C0`

Semaphore creation and try-wait, the library's threads (`_RwaThreadCreate`, the entry that releases
the semaphore its function returns, the start with priority) and an `_InterlockedExchange` store.
xapilib's `CreateSemaphoreA`, `CreateThread` and `SetThreadPriority` are called directly.

### `src/rwa/unit_2417C0.c`, interface registrations, `0x2417C0`–`0x2418E0`

The listener, voice 3D and virtual voice interface definitions (static, 0x28 bytes each), registered
with their parameter tables and unregistered at close.

### `src/rwa/rwaparam.c`, parameter types, `0x2418E0`–`0x241F90`

The PS2 header's rwaparam.h. Range values come from five free lists keyed by value size. Types are
kept in the symbol table at 0x516C50, created as plain, pointer, reference or derived types, and
destroyed recursively. The built-in table at 0x42EFC0 holds 15 types.

### `src/rwa/unit_241F90.c` and `src/rwa/rwamemory.c`, helpers and memory, `0x241F90`–`0x2422B0`

A gain to hundredths of a decibel (`2000 * log10`), a 32 by 32 bit multiply into two 31-bit
halves, a value's lowest set bit (the alignment macros' `sub_242150`), and allocation through the
RenderWare engine's memory interface (0x520214) with aligned blocks and C library defaults.

Byte-swapping copy 241FD0 now matches (128 bytes). Its 16-bit path uses a word
shift; its 32-bit expression uses direct source reads on the left and a saved
value on the right. Vector length 242050 now also matches (128 bytes / two
relocations) with the original fully parenthesized RW Dot macro and the existing
table square root. All five numeric helpers match.

### `src/rwa/unit_2422B0.c` and `src/rwa/unit_242910.c`, waves and wave definitions, `0x2422B0`–`0x243160`

The PS2 header's rwawave.h types with Xbox layouts. A wave (0x5C bytes) holds its definition, its
source and device formats (0x1C bytes each, with extra format data), data, flags and state. A
wave definition (0x6C bytes) holds its callbacks, supported formats, data size, an instance free
list and a link in its object definition's list (`rwaObjDef.waveDefs`, 0x20). The unit covers
wave creation, set-up and destruction, format matching and conversion sizes, the codec table
(0x42F7A0) and definition creation, destruction and lookup by UUID. The busy query
`sub_242570` now matches (32 bytes including 15 bytes of NOP padding, no relocations):
RwaWaveDefUploadBusyFunc takes no arguments, as the reference header declares. The
shared busy callback type now agrees. Upload `sub_242810` also matches (256 bytes,
11 relocations): a separate uploadOffset local is assigned by both conversion branches
before the common callback call. All 34 annotations in this unit now match. The old
rwa_wave_draft.c is superseded by production source.

Two objects (PLAN M7): the waves (`unit_2422B0.c`, `0x2422B0`–`0x242910`, their pool at
0x506FD4) and the wave definitions (`unit_242910.c`, from `0x242910`, their pool at 0x507004).
In one unit VC7.0 emits the wave functions that call the format comparison `sub_2429D0`, defined
later, and their callers at the unit's end (it defers a function that calls one defined further
down); the image has them in place, so the comparison was another object's.

### `src/rwa/rwallist.c` and `src/rwa/unit_243670.c`, lists and free lists, `0x243490`–`0x243AE0`

`RwaLLNode` lists (after the database's `_rwaLListModuleOpen`), and the free lists: 0x24-byte
`RwaFreeList`s of bitmapped blocks, all linked at 0x507030, the free lists themselves coming
from one at 0x507060. Free `sub_2437A0` now matches: 224 bytes, one relocation,
including 11 NOP bytes. A named bitmap pointer reused for clearing and summing
recovers all three address encodings. Allocation `sub_243670` also matches:
304 bytes / one relocation, including 13 NOP bytes. A separate remaining-entry
counter preserves the allocation hint; the named bitmap pointer, alignment
inline, and shared entry-found check recover the register and branch layout.
All seven annotations match.

### `src/rwa/unit_243AE0.c`, object interfaces, `0x243AE0`–`0x244220`

Interface definitions (0x28 bytes: unique ID, input and output parameter IDs, flags, an
unregister callback and a link in the list at 0x5070B0), their creation, parameter IDs,
destruction and lookup by UUID, and the interface instances an object definition hands out. Each
instance holds its definition, accessor tables built by matching parameter UUIDs, a reference
count and a link in the definition's parameter-table list. Definition creator
`sub_243E20` now matches (128 bytes including seven NOP bytes, seven relocations).
An inline that returns the allocated/existing definition after setting its flags
preserves the original branch layout around shared initialization. Compatibility
`sub_243BC0` (272 bytes / two relocations) and instance create `sub_243FF0`
(560 bytes / four relocations) now match too. The instance uses the same allocation
inline shape; separate per-pass counters plus qualified table-pointer reads preserve
the remaining address encodings. Original qualifiers are unknown and documented in
source. All 12 annotations match; the old interface drafts are superseded.

Two objects (PLAN M7): the listener's interface registration (`unit_243AE0.c`,
`0x243AE0`–`0x243B40`) and the interface definitions (`unit_243B40.c`, from `0x243B40`, with
their pool at 0x50708C and list at 0x5070B0). In one unit VC7.0 emits the listener functions,
which call the definitions' functions defined further down, at the unit's end.

### RW Audio pools, symbol tables, memory waves and timer, `0x244220`–`0x2449C0`

- `src/rwa/unit_244220.c`: pools of variably sized chunks. These are the instance pools that
  rwaobjdef.c creates.
- `src/rwa/rwasymboltable.c`: the PS2 header's symbol table of parameter types.
  Add `244650` and remove `244690` now match (64 bytes each); both return
  the table pointer, as the reference header declares.
- `src/rwa/unit_244790.c`: the memory wave definition (data in a block at the wave's +0x4C) and an
  interface definition's registration. The database missed five of these functions; they were
  added with `tools/addfn.py`.
- `src/rwa/rwatimer.c`: the time stamp counter's frequency (733333333), the timer start and the
  elapsed-ticks wrapper. The `rdtsc` readers stay binary.

### `src/rwa/unit_2449C0.c`, the stream cache, `0x2449C0`–`0x245240`

The database's `_rwaRwStreamCacheOpenModule`. One worker reads queued requests through a
one-sector (0x800-byte) cache, or straight into aligned destinations, under three semaphores.
Clients open, read and seek stream files through it. The globals whose addresses escape are plain
globals; the image re-reads them across stores. The database missed 0x245240 (an interface
registration; it and its unregistration, `sub_245290`, are src/rwa/unit_245240.c, matched 2026-10-01). The completion handler `sub_244B40` and cache-copy helper `sub_244AF0` now match
(2026-10-01; 720 bytes including padding). Both handler exits share an unlock label;
this selects EAX for the final semaphore handle. Header callback 244FA0 now
matches (192 bytes / four relocations); duplicate failure cleanup in both
failure branches so the compiler merges the original register sequence.
Dispatcher 245060 (96 / two) and helper 2449C0 (32 / zero) now match too.
Open 2450C0 remains parked.

### `src/rwa/unit_2452A0.c`, the stream container, `0x2452A0`–`0x246FD0`

The object a stream plays through (`rwaStreamPlayer`, the stream object's +0xEC, and
`rwaStreamContainer`, which adds its node set, command and reported states): the output node, the
decoders and converters built between each track's format and the output's (`rwaConversion` steps,
searched recursively through the converter definitions), its play state from theirs, and the
command that changes its rate, mode and per-channel values. The database names
`_rwaStreamContainerCommandInitialize`. The file statics take their arguments in registers; the
compiler picks the registers from the body, and the argument order of a caller's call (for
`sub_245690`, `sub_245CC0`, `sub_245F10`) sets the order the caller loads them in. Matched: 46. The state machine
`sub_246AD0` (2026-10-01) keeps a `failed` flag that its breaks set and its end tests (the
compiler threads those jumps straight into the failure block, whose missing-source entry is a
label before the state store), while its default case has its own copy and `return`. The track
loops index `tracks[i]` (the audit rejects byte-offset casts). Not yet (bodies in the unit,
unannotated): the graph build `sub_246500`, the converter chains `sub_246240`, the source's
decoder `sub_2457A0` and value set `sub_246ED0` (register
assignment).

Entry initialization `sub_246D70` now matches (2026-10-01; 256 bytes,
no relocations). A typed per-entry inline preserves the four groups of
channel/track/kind/value stores and the original register allocation.

Two objects (PLAN M7): the container (`unit_2452A0.c`, to `0x246D50`) and its command set-up
(`unit_246D50.c`, `0x246D50`–`0x246FD0`, with the entries helper initEntry). In one unit VC7.0
emits the five container functions calling the later-defined command functions at the end.

### `src/rwa/unit_246FD0.c`, stream nodes, `0x246FD0`–`0x247430`

What every node of a stream container shares (`rwaStreamNodeState`, its object's +0x28: the node
interface, play mode and status, the creation callback), the node interface's accessor calls and
the play queue's ring (`rwaQueue`: head, count, size, items). The database names
`_RwaStreamNodeCreationComplete`, `_RwaStreamNodeGetParams`, `RwaObjIntGetParamUInt32` and
`__rwaStreamSourceCreationParamsInit`. Not yet: the accessor calls `sub_247220` and `sub_247260`
(the image loads the accessor's parameter before the value; every form tried loads the value
first).

Node set/get dispatchers `sub_247220`/`sub_247260` now match (2026-10-01;
48 bytes each including padding). Return the callback result as RwBool and
cache its 16-bit parameter number in a RwUInt32 local.

### `src/rwa/unit_247430.c`, the stream source reader, `0x247430`–`0x249490`

A stream source's node state (`rwaDecoderState`, the object's +0x5C) reading its stream file
through the stream cache: the cache callback's open and header state machine, the marker lookups,
the two rings of chunks (`regions` played, `entries` look-ahead; their indexes and the read
requests are `volatile`), and the stream node and stream source interface registrations (database
names). Matched: 16. Still parked (draft: `docs/drafts/rwa_source_draft.c`):
the look-ahead copy `sub_247660`, wrap count `sub_247F20`, seek `sub_247FE0`,
read `sub_248520`, cache callback `sub_248810` and setup `sub_249160`.

Source pump `sub_248410` and its static request helper `sub_2475D0` now match
(2026-10-01; 416 bytes total). A qualified read preserves the second load of
the look-ahead index at 0x2484AC. The helper is emitted with its original
EAX argument convention alongside the caller.

Chunk acquire `sub_247C50` now matches (2026-10-01; 432 bytes including padding).
The look-ahead path comes first, failure branches release and return directly,
and volatile-qualified region flag reads preserve the observed access order.

Chunk release `sub_247E00` now matches (2026-10-01; 288 bytes including padding).
Both exits share a semaphore-release label, selecting the original register and
unsigned-division instruction order.

Track-position helper `sub_248360` now matches (2026-10-01; 80 bytes). Ordinary
high/low result locals reuse the original parameter slots and select the
original final LEA encoding.

### `src/rwa/unit_249490.c`, wave format conversion, `0x249490`–`0x24CC40`

The converters (`rwaConverter`, 51 at 0x42FDF0: two wave format descriptions, flag 1 for a rate
change, and the conversion), the converter description for a format, the size of a conversion
through a chain of converters, and the sample converters. Matched: 14, including the IMA ADPCM
mono block decoder `sub_24C560`, mono block encoder `sub_24C620`, and stereo block decoder
`sub_24C700` (2026-10-01; 736 bytes including padding). The two static dispatchers
`sub_24C840`/`sub_24C880` match only alongside the unplaced conversion caller `sub_24C8C0`;
all three remain parked in `docs/drafts/rwa_24C8C0_draft.c`. Not yet: the chain search
`sub_2494F0` (recursive, with the last five chains cached at 0x507A28; register assignment) and the
x87 sample converters from `sub_249920` (draft: scratchpad rwa_convert_draft.c).

IMA sample decoder `sub_24BDE0` now matches (2026-10-01; 128 bytes,
two relocations). Updating the predictor through its pointer and checking
`*index` after the index write preserve the original register allocation.

### `src/rwa/unit_24CC50.c`, the stream splitter, `0x24CC50`–`0x24D4C0`

A stream node (state 0x88, `rwaSplitterState`) that reads items of interleaved tracks from its
source and hands each track a track item into the same data; an item goes back once every track
has played it (mask per item). Its update returns its argument and was folded by /OPT:ICF into
RtFS's `TkFSManagerGetValue` (alias `_rwaSplitterUpdate`). Then the definition's set-up and
registration and `RwaStreamRendererInterfaceRegister`. IDA missed six functions here (added
with tools/addfn.py): the definition's unregistration 0x24CC40, the four parameter handlers
0x24CF70–0x24CFD0 and the interface's unregistration 0x24D4B0. Matched: 17, including constructor `sub_24CFF0` (448 bytes, six relocations).
Its typed allocation inline evaluates the size before allocator fields; caching the
callback-array pointer and qualifying the tracks-pointer read reproduce the remaining
address calculations. Not yet (draft: `docs/drafts/rwa_splitter_draft.c`): the status
machine `sub_24CC80` (case 7 mode-test threading) and track read `sub_24CD50`
(the failure tail clears EAX after the pops instead of before them).

### `src/rwa/unit_24D4C0.c`, the read request ring, `0x24D4C0`–`0x24D670`

The stream source reader's cache (unit_247430.c) queues its file reads in a ring of
`rwaReadRequest`s under a semaphore. Matched: 5.

### `src/rwa/unit_24D9F0.c`, the stream description clears, `0x24D9F0`–`0x24DA70`

A marker's, a track's and a stream description's clears. The fix-up before them
(`sub_24D670`: a stream file's description gets its pointers back, packed data after it) is a
near miss: the image computes some element pointers before reading their fields and allocates
its loop counters in other slots (draft: scratchpad rwa_fixup_draft.c). Matched: 3.

### `src/rwa/xbox/unit_24DA70.c`, the Xbox streamed wave definition, `0x24DA70`–`0x24DF20`

From 0x24DA70 to 0x252000 RW Audio is padded with `int3`: this Xbox layer is built with VC7.1
(`src/rwa/xbox/*` in config/flags.txt), the rest with VC7.0. The streamed wave definition keeps
its waves' data in the streamed waves' memory (144-byte units of the allocation bitmap at
0x51DE60, or the application's allocator when it set one) and loads them straight from the file.
All 18 annotated functions match. The creator `sub_24DBA0` is 182 bytes / 12 relocations;
its static allocation helper `sub_24DAD0` is 58 bytes / three relocations. A qualified
read of the incoming wave pointer preserves its early ESI save, and qualified length
reads preserve the reload after the unk48 store. The original qualifier spellings are
unknown; these are local representations of the observed accesses. VC7.1 flags and
shared types are unchanged. Production source supersedes rwa_nv_followup.c.

### `src/rwa/xbox/unit_24DF20.c`, the Xbox output object, `0x24DF20`–`0x24EC60`

The DirectSound device behind the output definition at 0x507CE8 (VC7.1). Create makes the
DirectSound object, downloads the effects image (`d:\data\dsstdfx.bin` unless the parameters
name one), converts the parameters' mix bin gains to levels and sets the 3D defaults; each update
applies what the listener's state (flags at +0x48) and the I3DL2 settings changed, switches the
headphones on for speaker mode 3, and calls `DirectSoundDoWork`. Then its parameter handlers (the
int3-separated functions 0x24E270–0x24E3D0 IDA missed), its definition's set-up and registration
(0x24EB50, also missed by IDA, added with tools/addfn.py) and the registration lists'
unregistration.

The Xbox layer's string literals are in `.data`: the flags spell out /O2 without /GF. The output
flags (+0x68) are `volatile` (each test re-reads them, each change is a load, op, store); the
I3DL2 settings are copied field by field into the `IDirectSound_SetI3DL2Listener` argument, and the
update's speaker mode switch keeps its jump table only with (dead) per-mode speaker configuration
stores. Its float getter (`rwaXboxOutputGetUnk04`) was folded by /OPT:ICF into 0x24F1C0 (alias).
Matched: 36. Not yet: the destroy `sub_24E710`, whose frame keeps three dead zero stores after
the listener is cleared (draft: scratchpad rwa_out_710_draft.c).

### `src/rwa/xbox/unit_24EC60.c`, the Xbox voice object, `0x24EC60`–`0x250AC0`

The voice definition at 0x507D80 (VC7.1): a DirectSound buffer playing a wave straight from the
streamed waves' memory (the output's), or (flags 0x68000) a buffer other voices mix into. Its
state (0x16C after the instance) keeps the 3D parameters as a `DS3DBUFFER`, the I3DL2 settings,
volume, pan, frequency, the play position and the mix bins; setters mark what changed and the
update applies it. Then the int3-separated parameter handlers (0x24F890–0x24FDF0, IDA-missed) and
the definition's set-up and registration. The creation's slot sharing needs block-scoped locals
(the search, the zero vector and the mix bins share one slot); the update's 3D gains take a
`rwa3DSource` (position, velocity, min and max distance).
Matched: 102. The update `sub_250340` now matches 1,134 bytes and 29
relocations. A local getter pointer preserves the unknown-write boundary while
compiling to the original direct call. Qualified listener/gain reads, vector
operand order, a named position result, and I3DL2 assignment order recover the
remaining instructions. The original declaration forms remain unknown and are
identified as such in the source; no shared header or compiler flag changed.
Not yet (draft: docs/drafts/rwa_voice_draft.c): the wave set `sub_24F410`
(the image keeps the wave in `esi` and the 3D flag in `edi`), with its statics
`sub_24EDC0` and `sub_24F350` (both match alongside the draft caller).

### `src/rwa/xbox/unit_250AC0.c`, the Xbox output interface, `0x250AC0`–`0x250B20`

The interface the output definition registers (0x24EB50): seven set and seven get parameters.
Matched: 2.

### `src/rwa/xbox/unit_250B20.c`, the Xbox WMA stream source, `0x250B20`–`0x252000`

The WMA stream source definition at 0x507E18 (VC7.1): a stream node whose state (0x2A0) holds a
WMA decoder (`WmaCreateDecoderEx`; its calls go through the XMediaObject vtable), a ring of
decoded packets (`rwaWmaPacket`), the queue items that play them, and a stream description
(info, one track, one marker, the PCM format). One WMA thread, opened by the first source
(`sub_251630`, count at 0x507EB8) and stopped by the last (`sub_250B30`), keeps the listed
sources' rings filled, seeks and loops them. Then the handlers, the definition's set-up and
registration, and the voice interface (0x251FA0) the voice definition registers.
Matched: 26. The play position `sub_250D90` now matches 100 bytes and four
relocations: use a unit switch, whose SUB dispatch also restores the ECX state
pointer. Not yet (draft: docs/drafts/rwa_wma_draft.c): the default parameters
`sub_250C10` (an `add esp` scheduled before the stores), the WMA thread `sub_251210` (aligned frame: the image's
slots put `next` below the seek results, and keeps the loop's new position in `ebx`), and the
create `sub_2516E0` (fail-path tail merging and slot order).

The rest of RW Audio from 0x24C230 (to 0x24DA70) is still to do; the Xbox layer
(0x24DA70–0x252000) is done apart from the near misses above.

### `src/rwa/rwabase.c`, the core, `0x23E1C0`–

`RwaCoreUpdateStart`/`RwaCoreUpdateFinish` (header names) and the module table's helpers: the
RenderWare engine start-up and shut-down used when no graphics engine is running, and the module
open/close callbacks.
Engine startup `sub_23E1C0`, static `sub_23E240` and `RwaCoreOpen` now match
(2026-10-01; 304 bytes including padding). The module loop increments i before
testing the user callback's result, so rollback includes that opened module.
Allocation cursor callback `sub_23E680` also matches (16 bytes): it returns
the previous cursor before advancing it; the old void draft was incorrect.

### `src/rwa/unit_23E610.c`, the clock and the allocation cursor, `0x23E610`–`0x23E690`

Split from `rwabase.c` (PLAN M7): `RwaCoreUpdateStart` calls the clock `sub_23E610`, and VC7.0
emits a function calling one defined further down at the unit's end (it holds it back to inline
the callee; a recursion cycle, as in RenderWare's multiTexEffect.c, prevents that). The image has
`RwaCoreUpdateStart` and `RwaCoreUpdate` in place, so the clock was another object's.

### `src/rwa/rwavoicemanager.c`, the voice manager, `0x23E690`–

The virtual voices' free and active lists, the voice binding shut-down (`DSPResourceMgr_Shutdown`),
priorities from the listener distance (with the library's table square root) and the stop/start
transitions (`SoundStopper_Transition`). Its globals are file statics: only that lets the compiler
move their loads past stores through a voice pointer, as the image does.

Priority 23E980 and helpers 23E8E0/23EE70/SoundStopper_Transition now match
(592/160/80/64 bytes). The original RW Sub/Dot macros, shared unity-volume
path, head-first insertion case and one final flags update recover their
register lifetimes. Integer bit copies and a pointer comparison inline retain
the existing shared fields. All six unit annotations pass; creator 23E690
and update 23EBD0 remain unplaced.


### `src/rwa/unit_2FD5D0.c`, allocation bitmaps, `0x2FD5D0`–`0x2FDB00`

Linked apart from the rest of RW Audio, after the XDK's voice codec members: a bitmap of
allocation units (`RwaAllocBitmap`, 0x18 bytes in rwaint.h) whose runs are handed out as handles
that pack the first unit and, above `shift` bits, the length. The streamed waves' buffer memory
(0x51DE60: 144-byte units, set up by `sub_24DBA0`) is carved from one. Matched: the destroy, the
range set/clear, the free count, the two handle helpers and the free. The create `sub_2FD5D0` and
the allocation `sub_2FD880` (its bit loop is unrolled by hand, eight steps in a `bit += 8` loop:
the compiler never unrolls) differ only in register assignment (docs/questions.md). The rest of
the range, from `sub_2FDB00`, is another module.

### `src/rwa/unit_2FDB00.c`, the stream voice, `0x2FDB00`–`0x2FEC60`

A stream node (definition 0x512658, state `rwaStreamVoiceState`, 0x298 bytes in rwaint.h) that
uploads its queue items into the entries of a streamed wave (`sub_24DA70`) and plays it looping
through an Xbox voice embedded in its state (+0x34, created through `RwaStreamCreate_2` with the
allocation callback `sub_2FDB10`, linked as its sub-object), following the voice's position to
return played items and report the position; its rate, channel level and position parameters,
the definition's set-up and registration, and two handlers over the voices it mutes (file statics
0x5126B4/0x5126B8: the image loads the list's fields before its stores). The database missed the
handlers at 0x2FE210-0x2FE270 and 0x2FE800 (tools/addfn.py). Matched 2026-10-01: 23 of 24. Shapes:
the register-argument static `sub_2FDF80` takes (obj, play, rewind) (the callers load the last
argument first); the create's format and I3DL2 settings are block locals sharing stack; the voice
definition lookup is its own statement before the callback data's stores (data, func, state).
Not yet: the update `sub_2FE290` (register assignment; body in the unit, unannotated).

## Bink (`src/bink/`)

RAD's Bink 1.6 player, decompressor and colour converters, in the `BINK*` sections and a `.text`
run (`popmal.obj`, `radmem.obj`: `pushmalloc`, `popmalloc`, `radmalloc`, `radfree`). Names come
from RAD's `binkxbox.lib` (1.5s, `docs/reference/Bink`); the image's layouts are BINK2.H's (1.6c).
`src/bink/bink.h` holds RAD's public types, `src/bink/binkint.h` the cross-unit declarations, the
radcb structures and the Xbox calls. The library's names for the database's `sub_` functions and
the Bink data are in `config/aliases.txt`, each with its evidence.

### `src/bink/radcb.c`, background callbacks, `0x344160`–`0x344990`

RAD's `radcb.obj`: handler threads (`RAD_callback_thread`, the database's `StartAddress`) that
call their registered callbacks in priority order, and the suspend, resume, free and unregister
calls the player uses for its IO and sound callbacks. A callback's node lives in the caller's
control buffer. Unused library functions (`RADCB_registered_count`, the single-handler suspends,
`RADCB_unregister_callback`, `RADCB_callback_size`) are not in the image.

### `src/bink/binkfile.c` and `src/bink/memory.c`

RAD's default file IO (`binkfile.obj`, `0x349BA0`–`0x34A2B0`: the BINKIO callbacks reading 16K
blocks into the IO buffer, with simulated data rates) and `radmalloc`/`radfree` (`0x258C90`,
`0x258D00`, 32-byte aligned blocks through the user's allocator when set).

### `src/bink/binkds.cpp`, DirectSound output, `0x345540`–`0x346170`

RAD's `binkds.obj` (C++): a sound track's looping DirectSound buffer, the BINKSND callbacks and
`BinkOpenDirectSound`. DirectSound is called through dsound.h's C++ inline wrappers (in
`binkint.h`; the library member carries their COMDAT copies). Found: writing `CH(bs)->` instead of
a channel local, a redundant `moved = 0` in `start_streaming`'s restart branch, the dB conversion
written out with an `F32` temporary. `Open` (`0x345E40`) is a `__declspec(naked)` transcription
for now (docs/questions.md); it calls `set_rate_volume_and_pan` and `DS_clear` through the
aliases `_binkds_set_rate_volume_and_pan` and `_binkds_DS_clear` so the C callers keep VC's
register convention for them.

### `src/bink/popmal.c`, pushed allocations, `0x258B20`–`0x258C90`

`pushmalloc` records (pointer variable, size) pairs and `popmalloc` makes one 32-byte aligned
block for them all and fills the pointers in; `popmalloctotal` is the total.
All three are now C. The cache-line padding calculation masks each index
before subtracting; this restores pushmalloc's ESI/EDI allocation with the
existing VC7.1 flags (213 bytes / 17 relocations). Matched: 3.

### `src/bink/fft.c`, the audio FFT, `0x258D30`–`0x25D910`

Bink's audio transform is Takuya Ooura's General Purpose FFT package (`fftsg.c`, the 1996-2001
version with `cftrec1`/`cftrec2`/`cftexp1`/`cftexp2`, freely usable per its notice) in single
precision: only `rdft` and `ddct` are public (`__stdcall`). The 2001 code differs from the
well-known 2006 release in small ways the image shows: `makewt` stores `+sin` for the 3j
twiddles, `cftf162` reads `wk3i = w[7]` (and `cftf082` its twiddle at `w[4]`/`w[5]`), the
4-point butterflies store `a[0], a[1], a[4], a[5], a[2]...`, and `atan(1.0)` is the float
constant 0.785398f. `cftx020` and `cftfx42` are inlined (/O2 auto-inlining). Matched: 30.

### `src/bink/wintimer.c`, the millisecond timer, `0x344990`–`0x344AB0`

`RADTimerRead`: the performance counter in milliseconds, kept in step with `GetTickCount`. A
`__declspec(naked)` transcription for now (C draft: scratchpad wintimer_draft.c): VC7.1 (and
VC7.0, tested against the library member) reassociates `(time - lasttime) - (rad - lastrad)`,
which RAD's code keeps as two differences. Its statics are named `_wintimer_*` (aliases).
Matched: 1.

### The colour converters, `src/bink/rgb*.asm` and `yuy2*.asm`

RAD's hand-written MMX converters, one MASM unit per library member, in the `BINK32`, `BINK32A`,
`BINK16`, `BINK4444`, `BINK5551`, `BINKYUY2`, `BINK16MX`, `BINK16X2`, `BINK16M`, `BINK32MX`,
`BINK32X2` and `BINK32M` sections (each after yuv.obj's C++ code there): 23 entry points, the same
instruction sequences as the library's members (drafted with `tools/asmgen.py`). They work on
yuv.obj's blit state `S` and tables and yuv32.obj's `pmem*` constants (aliased);
`rgb32m`/`rgb32mx2` define their own `pmemd0111`. The library's separate `YUY2M`, `YUY2MX2`,
`YUY2X2`, `16MX2` and `32MX2` sections are merged into `BINKYUY2`, `BINK16MX` and `BINK32MX` in
the image.

### Bink's MASM transcriptions, `src/bink/*_asm.asm`

The rest of Bink's code that is not matched in C, transcribed from the image by
`tools/img2masm.py` (owner: "asm the rest of bink", 2026-10-01; docs/questions.md): exact
bytes, with only the address fields as symbols (`_sub_`/`_unk_` names resolve by address).
Each file holds one library member's leftovers, one section per contiguous run:

- `binkread_asm.asm`: binkread.obj's statics only the naked binkread.c transcriptions call
  (`bpopmalloc` `0x341480`, `dosilence` `0x3414E0`, `GotoFrame` `0x341860`, `high1secrate`
  `0x341990`); 4 functions.
- `binkacd.c`: binkacd.obj, the audio decompressor (all seven functions restored in C), `0x344AB0`–`0x345540`; 7 functions
  (the C draft's near misses are in questions.md).
- `yuv.cpp`: the masked generic blitter (`0x34B150`, 2484 bytes / 144 relocations),
  fourteen helpers/wrappers and the per-format edge routines are restored in C++.
- `yuv_asm.asm`: only setup (`0x34A840`), the normal generic blitter (`0x34ACD0`),
  and init (`0x34BB90`) remain.
- `dct_asm.asm`: dct.obj's inverse DCTs, `0x34C400`–`0x34CEC0`; 5 functions.
- `bitplane.c`: ReadBPLossless (`0x34CEC0`, 2308 bytes / 10 relocations) and ReadBPLossyWithMotion (`0x34DCB0`, 813 bytes / one relocation), restored in C.
- `bitplane_asm.asm`: only readlossy (`0x34D7D0`) remains pending C restoration.

### `src/bink/expand.c` and `src/bink/expand_asm.asm`, the plane decoder, `0x346170`–`0x349BA0`

ExpandPlane (`0x347B40`) is restored in C: 7876 bytes / 118 relocations,
including 68 bytes of jump tables. Its original inline copy primitives
remain. Only simpmergesort and CheckReadHuff4PairBundle remain in MASM.

RAD's `expand.obj`: the bundle readers, the bundle sizes and the plane and frame expanders.
`StartReadHuff8Bundle` and `ExpandBundleSizes@8` match in C (`getbunsize` is inlined, as in the
library member). The other 13 functions are a MASM transcription of the image
(`tools/img2masm.py`; the owner's "asm the rest of bink", 2026-10-01): every instruction is
written as its bytes and only the address fields are symbols, so the transcription cannot
encode differently. The image's Bink is newer than the library here: `simpmergesort` takes
the merge decisions as an argument (the library's `mergesort` reads them) and `ReadHuffTable`
peeks the bits and consumes the count the merge returns. Names come from the library member
(its order and shapes; `config/aliases.txt`). The C draft of `ReadHuffTable` came within one
register swap (in the session notes; questions.md).

### `binkread.obj` (`0x341480`–`0x344160`)

Committed as binkread.c (C and naked transcriptions) and binkread_asm.asm (the four statics
only the transcriptions call). The notes below are from the C drafting.

All 30 functions are drafted; 24 match. They must be committed together: VC7.1 inlines a
static helper only when it has one caller, so leaving the near misses out changes the matched
functions (`inittimer` folds into `BinkCopyToBufferRect`). Near misses: `BinkOpen` (base/index
register order in the sound-track loop, the 8-bit conversion test), `BinkSetSoundOnOff` (the
failure branch placed after the epilogue), `BinkWait` (the operand order of
`t - big_sound_skip_adj - start`), `BinkDoFrame` (stack slots of an inlined `mult64anddiv`'s
operands). Found so far: `BinkSetSoundSystem` is inlined into `BinkOpen` only as a static
function; `BinkClose` passes its handler selections through locals; extra zero stores change the
zero-register allocation.


### Xbox default render callback follow-up (2026-10-01)

`src/rw/world/pipe/p2/xbox/xbpipe.c`: `_rxXbDefaultRenderCallback` at 0x2E02A0
matches all 1240 bytes and 116 relocations. The texture-stage force operation
uses the documented typed inline variant in `src/rw/driver/xbox/xbcache.h`;
the existing macro is retained for its other callers.


## Resolved: Xbox atomic morph update (2026-10-01)

`rwXBInstanceDataMorphUpdate` (0x2E2080) now matches 612 bytes and 13
relocations; its caller `_rxXBAtomicDefaultReinstanceCallback` (0x2E2380)
matches 82 bytes and 2 relocations alongside it. The current-header baseline
had 30 normalized diff lines. A `const RwV3d *verts = morphTarget->verts`
local in the single-target branch fixes that branch (10 lines remaining).
A `const RwRGBA *color = geometry->preLitLum` local immediately before
prelight instancing fixes both the prelight call and subsequent texture-loop
format load. Typed call wrappers, count/stride/destination locals and texture
format expression variants did not improve the result. Both functions are
placed together so the static helper's compiler register convention is kept.


## Resolved: Xbox skin render callback (2026-10-01)

`_rpSkinXboxRenderCallback` (0x2D4220) matches 125 bytes and four relocations.
A block-local `const RpMaterial *material = mesh->material` immediately
before `_rpSkinXboxPlainMaterialSetUp` fixes the atomic argument's delayed
load into eax and the following draw-call register allocation. A typed
inline setup wrapper also matches, but the source-pointer local is simpler.
The source uses `rpSkinXboxRenderCallback`, retaining the binary symbol's
single leading underscore and the existing pipeline callback reference.


## Resolved: world stream reader (2026-10-01)

`RpWorldStreamRead` (0x2DAB30) matches 1423 bytes and 52 relocations.
A block-local `void *readBuffer = &w34000` before the old-header memset,
used as the subsequent RwStreamRead destination, makes the compiler hoist
the common size push before the version branch and allocate the original
header-buffer slot. A local readSize initialized before the memset also
matches, but the buffer-pointer version is used. Narrow typed wrappers
around either or both reads retain the baseline's 107 normalized diff
lines; no wrapper was added.


## Resolved: Flatten2d (2026-10-01)

`Flatten2d` (0x2530C0) matches 1130 bytes and 12 relocations. The second
SubPathLineto2d expansion uses the documented `SubPathLineto2dInline`
variant of the existing macro. Typed path/point arguments plus a
`const RwV2d *normal` local for the previous node's normal reproduce the
miter dot product's load and multiply order. The first expansion retains
the macro: changing both calls or the shared macro changes other registers.
A pointer-argument dot-product forceinline also matches; the local normal
pointer avoids that extra helper. Ordinary __inline does not force expansion
and fails to match. The unit's existing annotations and source audit pass.


## Resolved: Xbox skin matrix update (2026-10-01)

`_rpSkinXboxMatrixUpdate` (0x2D2230) matches 701 bytes and 16 relocations;
`D3DMATRIXFromRwMatrix` (0x2D21C0) matches 100 bytes without relocations
when compiled beside it. Starting from the 100-line follow-up draft:

- Cache the atomic frame before initialization/inversion: 90 lines.
- Cache the first branch's per-bone frame before its matrix call: 72 lines.
- Initialize the third branch's loop counter before matrix initialization:
  66 lines; index shaderConstants[i * 3] in all three branches: 14 lines.
- Give the first bone loop a separate local counter: exact byte match.
  This puts the matrix-array and second-loop counter into the original
  stack slots. Remaining score artifacts are relocation addends/padding.

Removed the now-unused stepped constants locals; exact comparison still
passes. The full unit's existing matched functions are checked as well.


### Voice update copy-check revalidation (2026-10-01)

The proposed two-check copy-constructor fix for sub_1AA380 does not match
with the current headers. Its unchanged body remains six normalized lines
off; two checks yield 25. See questions.md and the standalone
`docs/drafts/voice_copy_followup_trials.py` overlay tests. No shared header
was changed and no previously matched caller was disturbed.


## Resolved: RWA ADPCM converter and dispatchers (2026-10-01)

`sub_24C8C0` (0x24C8C0) now matches 896 bytes including padding and 11
relocations; `sub_24C840` and `sub_24C880` match 64 bytes each including
padding and two relocations each. All three compile together in unit_249490.

The baseline had 178 normalized differing lines. A shared result-return
label fixes result allocation and the prologue (107 lines). Declare the
source pointer before the destination in both split and merge loops and
advance the merge source before its destination (38 lines). Finally,
advance the destination parameter once before memset and pass that pointer
to the decoder: exact match. A volatile result was rejected because it
introduced reads absent from the original; production uses ordinary storage.

## Resolved: Xbox skin vertex-format shader (2026-10-01)

`_rpSkinXboxGetVertexFormatShader` at 0x2D4440 now matches in
`src/rw/plugin/skin2/xbox/skinxboxformat.c`: 688 bytes, 42 relocations
(including 63 bytes of jump-table/padding data). Packed flag caching and
the widened weight local retain the earlier near-match improvements.
A typed forceinline containing the final format store, shader creation,
and handle return keeps the insertion index unscaled in ESI, matching
the three original scaled addresses. All six helper argument orders
matched those instructions; including the count increment also worked.
The helper is explicitly a local reconstruction, not a recovered symbol.

The skin texture-register table at 0x418FD4 is named unk_418FD4 here to
avoid resolving its local reference name to the distinct world table at
0x41939C. The existing create/destroy functions remain byte-identical.

## Resolved: MatrixOrthoNormalize (2026-10-01)

`MatrixOrthoNormalize` at 0x2A48C0 now matches in
`src/rw/src/plcore/bamatrix.c`: 1,468 bytes, four relocations.
The 21-line baseline had cross-product operand-load differences and
first-axis normalization store scheduling differences. Local variants of
the existing vector macros preserve explicit reads: first cross product
reads a.y and b.x/y/z; first scale reads a.x; second cross product reads
a.z/a.x in the y expression and a.x in the z expression. These qualifiers
encode observed loads, not a claim about original volatile declarations.
The arithmetic and original reciprocal-square-root macro are unchanged.
Whole-unit byte comparisons pass, including the public wrapper.

Typed combined basis helpers alone retained 21 lines. Component-read
trials reduced this to 17, then four, then exact by restricting the second
cross-product reads to the individual expressions. No new assembly.

## Resolved: compressed-normal Xbox tangent/binormal conversion (2026-10-01)

`_rpXboxVtxFmtInstBNTComp` at 0x2DE0F0 now matches in
`src/rw/world/pipe/p2/xbox/xbvtxfmt.c`: 1,459 bytes, 13 relocations.
Starting from the 12-line follow-up, accumulate tangent squares in
separate statements: y squared, then x squared, then z squared. This
fixes the remaining loads and SSE sum registers. Keep the component copy
and explicit y read in the scale established by the previous trials.
Whole-unit comparisons retain all existing matches.

The same square-accumulation shape improves ordinary-normal 2DDB50
from 14 to four normalized lines; its final cross-product load/multiply
order still differs. New best is `rw_xbvtxfmt_bnt_sum_followup.c`.
512 individual-read probes did not resolve that last difference.
Reproduce the ordinary-normal work with `rw_bnt_sum_steps_trials.py`
and `rw_bnt_sum_reads_trials.py`.

## Resolved: flak vehicle constructor (2026-10-01)

`type_3DC378::type_3DC378(type_712B0 *)` at 0x15A8C0 now matches
134 bytes / 11 relocations, plus its 32-byte unwind funclet and 10-byte
handler at 0x301D00/0x301D20. The bare vehicle constructor definition is
inline in unit_155470.cpp. Three reference-returning trigger-coordinate
accessors in the tank factory warning preserve its 293-byte match while
allowing the flak constructor's larger frame. All existing unit matches
remain exact. No diagnostic no-op calls are retained.

The old attempt only tested inline-budget calls before new. Three calls
after new or later in the factory remove the excess frame; real coordinate
accessors provide those expansions without changing emitted instructions.
Returning coordinates by value changes code; const-reference returns match.

## Resolved: ordinary Xbox tangent/binormal conversion (2026-10-01)

`_rpXboxVtxFmtInstBNT` at 0x2DDB50 now matches in
`src/rw/world/pipe/p2/xbox/xbvtxfmt.c`: 1,425 bytes, 10 relocations.
A two-vector-pointer inline for the final cross-product z component,
with explicit normal x/y reads, fixes both multiply operand orders.
Keep the earlier y/x/z square accumulation and the x/y macro expressions.
The qualifiers record instruction order, not original volatile types.
All 27 annotated functions in the unit retain exact matches. No new assembly.

The earlier four-line draft and final-product probes are superseded.
Full-vector scheduling trials were worse (best 41 normalized lines).
Of the smaller pointer/read trials, `zp_ab_1_12` matches exactly; both
pointer argument orders work. Scalar-argument helpers alone had failed.
Reproduction: `rw_bnt_pointer_read_trials.py` with pscore, against the
pre-placement source at cc3f31efa; target `__rpXboxVtxFmtInstBNT`, 0x2DDB50.

### Delta-morph unsigned texture count (2026-10-01; improved, parked)

2F28D0 improves from 900 to 898 normalized diff lines. The original
clamps numTexCoordSets to four using JBE at 0x2F2A8E; the old signed
RwInt32 local emitted JLE. Declare numTexCoordSets as RwUInt32, which
also agrees with its unsigned iteration later in the function. Changing
numVertices to unsigned has no effect, so preserve its existing type.
The new best draft is `dmorph_instance_unsigned_followup.c`; the first
byte mismatch remains +0x1B and substantial register/stack work remains.
XboxDMorphAddBlock still verifies exactly beside it: 109 bytes, no relocs.

Before the type correction, 128 individual target-flag/RLE-read qualifier
combinations did not improve 900. Keep those probes as negative evidence,
not production qualifiers. Reproduction: `dmorph_initial_qualified_trials.py`
and `dmorph_count_type_trials.py` (tc_1 gives the new best). No production
or placement changes; the callback remains binary.

### Delta-morph values/current address distance (2026-10-01; improved, parked)

2F28D0 improves from 898 to 894 normalized lines. Explicitly compute the
32-bit unsigned address difference between atomic values and current
values once, then compare through current-address + difference while
advancing current. The image similarly subtracts these addresses at
0x2F293E. This brings the initial values load into original EAX (896).
Initializing current before the target pointer further improves to 894.
Keep unsigned address arithmetic for the Xbox's 32-bit address space;
signed and pointer forms were diagnostic alternatives only.

The guard/count variants remain worse. New best:
`dmorph_instance_distance_followup.c`. First byte still differs at +0x1B;
large register/stack differences remain, so no production placement.
The companion XboxDMorphAddBlock verifies exact: 109 bytes, zero relocs.
Reproduction: `dmorph_value_distance_trials.py` and
`dmorph_distance_guard_trials.py`; winner vg_0_2_0. Earlier unsigned-count
draft is superseded but retained to reproduce its trials.

## `src/recovered/unit_30EA80.cpp`, retired shutdown reconstruction

This file is retained as a history note. The callbacks at `sub_30EA80` and
`sub_30EA90` are now generated naturally in `unit_1A8B20.cpp` as `_$E19` and
`_$E18`. Correcting the Axis/Allies local statics to `type_1A5EA0` reproduces
their ordinary destructor calls (15 bytes, two relocations each). The
registrations at 0x1AFC5D/0x1AFC1C establish the exact object bindings.

### RW stream skip matched (VC7.1, 2026-10-01)

`RwStreamSkip` at 0x2A7210 now matches all 292 bytes, 13 relocations,
and 18 bytes of jump tables with the existing VC7.1 flags. The missing
source structure was in the file branch: Godfather debug `_RwStreamSkip`
at 0xBB6760 has a `RwStream *retVal`, assigns it in both seek outcomes,
then returns it once. Restoring that structure fixes the memory branch's
LEA base/index byte at +0x87; changing the addition itself was unnecessary.
Production `bastream.c` supersedes the stream-skip experiments.


### RW skin atomic node matched (VC7.1, 2026-10-01)

`XBoxSkinAtomicAllInOneNode` at 0x2D46F0 now matches all 986 bytes and
36 relocations. Godfather debug 0x11568D0 supplies three source details:

- Advance the shader-constant pointer through the viewport and matrix
  constants instead of spelling each array offset independently.
- Traverse bone batches with `firstBatch + currentBatch` indexing.
  These two changes together fix the remap SIB byte at +0x306; either
  change by itself retains the mismatch.
- Pass `(RxXboxResEntryHeader *)(resEntry + 1)` directly to the render
  callback. This fixes the EDI header reload before the ESI mesh reload.
  The reference's actual callback argument is visible at 0x1156F09.

The existing VC7.1 flags are unchanged. Production `skinplatform.c`
supersedes `rw_skinplatform_draft.c` and all skin-node probe candidates.


### RW default instancer matched (VC7.1, 2026-10-01)

`_rpXboxDefaultInstance` at 0x2DED60 now matches all 669 bytes and
18 relocations. Godfather debug 0xB7B540's frame identifies `size` at
-0x20 as signed `int`; the old draft incorrectly used RwUInt32. Store
both position paths' results in an RwInt32 size local, then advance the
buffer after the branch. This restores the separate packed/unpacked
exits, their format-pointer reloads and the downstream alignment.

The signed local without the common pointer advance still differs;
the common advance with an unsigned local also differs. Both changes
are required. Scoped signed attribute locals also match, confirming
that signedness and use determine the missing source structure.
No compiler flags or shared declarations changed. Production
`xbvtxfmt.c` supersedes the default-instancer drafts and probes.

### Delta-morph reference structure (2026-10-01; improved, unmatched)

New best: docs/drafts/dmorph_instance_reference_followup.c, 495 normalized
diff lines (previously 894), first byte +0x33. Signed position size plus its
common advance, reference Lock calls, and the texture-count conditional
restore most of the original instruction scheduling. The indexed counting
loop now naturally produces the game's pointer-distance/countdown code.
Remaining: global stack-slot placement and prelight-copy scheduling; see
questions.md. XboxDMorphAddBlock still matches 109 bytes beside the caller.
Both functions remain binary. Compiler and production sources are unchanged.

### Xbox delta-morph complete (2026-10-01)

src/rw/plugin/dmorph/xbox/dmorphpipeg.c now has all eight functions matched.
The final helper at 2F2860 is 109 bytes, no relocations; callback 2F28D0 is
5,740 bytes, 93 relocations, including 160 jump-table bytes. Both compile
with the existing VC7.1 settings. Shared deformation-pass locals restore
stack-slot lifetimes; k/m/maxl stay within their attribute passes, and l is
shared. The exact match supersedes all dmorph_instance_* drafts. See the
matched delta-morph entry in questions.md for the stack-map evidence.

### Packet copy include context (2026-10-02)

`src/recovered/unit_1D4290.cpp` places the implicit type_3E4E58 copy at
0x1D4290 (144 bytes, two relocations). It includes only game/netqueue.h
and explicitly instantiates the existing list append. The append's own
133-byte body also matches; its placement remains in unit_1D0100.cpp.
The class definitions and default constructor are unchanged.

The broad HUD include in unit_1D0100 parses the function-local singleton
guard $S1 in CLinearMemoryManager::Instance. VC7.1 then numbers the copy's
array locals $S2/$S3/$S4 instead of $S1/$S2/$S3, changing their stack order.
The isolated instantiation reproduces the required compiler context without
changing the shared RWS header. See docs/toolchain.md for the controlled
small-header, full-header and declaration-only overlay comparisons.


### RWA wave setter, destructor and listener follow-up (2026-10-02; parked)

No production function or placement changed in this batch. All probes use
the existing per-unit compiler flags: VC7.1 for the Xbox layer and VC7.0
for the core listener. Run each script with tools/session/pscore.py, its
underscored C symbol, hexadecimal address, and the production unit below.

* **24F410 / unit_24EC60:** current-header baseline was 247 normalized
  diff lines. Shared changed/created control flow (skip format setup when
  neither is true) and a named flags value around the initial wave clear
  reduce that to 115. The first 13 instructions match. The wave and is3D
  values still choose the wrong registers; the null-wave path, descriptor
  store scheduling and play-region argument evaluation also differ. A
  non-null outer if puts the stop path at the end but scores 121 and merges
  format-call tails differently. Pointer/local declaration variants,
  qualified wave reads, explicit pointer/offset temporaries, nested scopes,
  and format/play-region inlines do not resolve the remaining differences.
  Helpers 24EDC0 and 24F350 match 116 bytes / five relocations and 33 bytes /
  zero relocations, but remain coupled to the unplaced caller.
  Best bundle: rwa_voice_wave_followup.c. Reproduction: rwa_voice_wave_*
  trials (shape variant vws_12, plus the alternative vws_13).

* **24E710 / unit_24DF20:** the volatile integer-array probe remains two
  normalized lines away: its first zero store is scheduled before the
  setter call's stack cleanup. A forceinline store helper instead drops
  that first store entirely; exact object disassembly confirms this is a
  missing store, not a match. Local function-pointer calls, chained/comma
  forms, pointer-element types, scope changes and several inline pointer
  shapes do not fix it. sub_24DF00 traverses the NV wave definitions; it
  is not a parameter-UUID getter, so the discarded parameter-call theory
  is unsupported. Reproduction: rwa_output_destroy_*_trials.py.

* **23D2A0 / 23D320 / unit_23CC10:** current VC7.0 baselines differ by
  14 / 16 normalized lines. Reversing scalar product operands alone has
  no effect. Qualified individual reads reduce these to eight / six,
  with remaining x87 operand-order, pop/load and dirty-flag scheduling differences.
  Pointer-based whole-cross inlines, component inlines, and named scalar
  product temporaries remain unmatched. Best probes: lisr_01 for 23D2A0,
  lisr_11 for 23D320. No qualifiers have been applied to shared types.

* **23CC70 / unit_23CC10:** the old draft conflicts with the unit's
  placeholder callback declaration. The scratch build gives it its
  pointer return and casts it to the definition callback, as other units
  do. VC7.0 reproduces the initial temporary zero-vector copies. Chained
  assignments for the zero/one orientation values, and literal 0.0f in
  the cross product instead of the external flt_3CD84C object, reduce 57
  normalized lines to 18; the first 35 instructions match. Remaining
  work is x87 common-term use and scheduling after the up-vector copy.
  Full cross-product expressions retain the same mismatch. Best variant:
  lsetc_07_0; lsetc_10_0 and lsetc_20_0 have the same score/prefix.
  Best listener bodies: rwa_listener_current_followup.c. Reproduction:
  rwa_listener_*_trials.py; choose the matching symbol/address for each.

Scores are iteration aids and include padding effects. None of these
drafts passes the exact byte/relocation check; only production annotations
are evidence of placement.

### RWA WMA defaults follow-up (2026-10-02)

sub_250C10 in xbox/unit_250B20.c now matches 97 bytes / one relocation. Move
unk04=1 directly after unk00=0 and leave fileType=1 after the zero stores.
This restores the zero/one register lifetimes and call cleanup. The existing
RwaStreamNodeGetParams declaration now agrees with its pointer return.
All 27 annotations match; no header or compiler flags changed.

### RWA debug-reference batch resolved (2026-10-02)

Ten more functions were committed and pushed through cmf.py. All unit checks,
the source audit and the placement gate pass: 18,151 pieces / 3,486,335 bytes,
SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387, byte-identical. RWA remaining:
16 (14 main, two tail); RW remains zero. These results supersede older parked
entries for the addresses below.

- 247660: 1,520 bytes / 13 relocations. Debug _RwaStreamSourceReinterleave
  (rwad.dll 0x100B6FE1) recovers the pointer return, buffer direction, UInt16
  counters and UInt8 channel. The wide case copies two separate eight-byte pairs.
- 249160: 624/17. Debug __rwaStreamSourceCreate (0x100B29DA) recovers initialization
  order. A qualified unk174 reset preserves the final buffer-size load position;
  the original declaration is unknown. A typed union in rwaStreamSourceParams
  retains the existing values[15] layout. All 22 unit annotations match.
- 246ED0: 176/0. Initialize trackStart/kindStart/kindEnd before trackEnd;
  preserve the bit-31 mask ternary. The incoming UInt32 transports float bits.
  Debug _rwaStreamContainerCommandSetStreamGain is 0x100C04BA; all 50 unit
  annotations now match and are placed.
- 24CC80: 160/7. A separate incoming argument and typed obj local fixes the
  remaining register choice. Keep the case 4-6 else-if and case 7 independent
  conditions. Debug _RwaStreamFanOutStartExecute is 0x10067D61.
- 249D00: 496/2. Typed per-branch input/output arrays, separate indices and
  direct used reads recover channel duplication/averaging.
- 249EF0: 880/30. The helper 249C90 takes (from, srcSize, to), not the old
  declaration's order. This corrects argument-home reuse. Keep byte channels,
  separate previous/next arrays, scalar source index and the debug expression order.
- 24A260 and 24A740: 1,024/29 and 320/5. Per-destination loop index scopes fix
  the depth helper. The caller matches with the resampler definition in the same
  translation unit, with ordinary scalar locals and no new qualifiers.
- 24B260: 464/0. Debug GCN ADPCM decode (0x100B007E) uses flat coefficients,
  signed sample staging and an ordinary parity branch; byte-swap parentheses matter.
- 24BC50: 224/2. Debug VAG decode (0x100B13BB) separates persistent histories
  from per-block sample locals and decodes both nibbles explicitly.

All 25 wave-conversion unit annotations pass after these changes. Code and the
supporting rwaint.h changes were pushed only through cmf.py; compiler flags unchanged.

### RWA path, bitmap and format setup resolved (2026-10-02)

2494F0 now matches 688 bytes / 17 relocations. The debug DLL's
_RwaWaveConvFindPath (0x100AABAD) preserves a separate cache counter reused
for copying, a per-iteration validity flag, and increments/decrements the
recursive depth parameter. The Xbox version omits the debug DLL's unused
cache-step clearing loop. All 26 wave-conversion annotations pass.

2FD880 now matches 576 bytes / one relocation. _rwaAllocBitmapAlloc
(0x100BB929) uses direct bits[i] reads and an ordinary bit++ loop, naturally
unrolled by the compiler. Clamp run=count before breaking the outer loop;
use a failure-first final guard. All eight bitmap annotations are placed.

24D670 now matches 896 bytes / 23 relocations. _rwaStreamFormatCreateFromPack
(0x10069E30) shares UUID/name locals across header and marker loops. Cue loops
have separate inner indices and ID locals. Use direct format-field indexing
and final track-ID reads. All four stream-description annotations are placed.

All three were committed and pushed with cmf.py, with no header or compiler
changes. Audit: 723 files, zero problems. Full gate: 18,154 pieces / 3,488,495
bytes, SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387, byte-identical.
Remaining RWA: 13 (12 main, one tail). RW: zero.

### RWA encoding, renderer and Xbox wave batch resolved (2026-10-02)

Seven more functions are placed and pushed through cmf.py. Full gate: 18,161
pieces / 3,494,497 bytes, original SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387,
byte-identical. Audit: 723 files, zero problems. RWA remaining: six, all main.

- 24AB90 / 24BEF0: GCN ADPCM encoder and caller, 1,744/30 and 832/9. Debug
  _RwaWaveConvGCNADPCMEncode (0x100AF723) recovers signed histories, staged
  residuals and the 32767.0f residual scale. Keep the asymmetric parentheses
  around the first prediction product. Caller retains the existing byte swap.
  All 28 conversion annotations pass; VAG encoder group remains unplaced.
- 2FE290: renderer update, 1,264/23. A separate remaining counter walks played
  entries; preserve the source assignment order and positive silence branch.
  The old explicit obj fallback for current on underrun was an inference that
  changed register allocation. Leaving current unassigned on that path produces
  the exact Xbox bytes, including reuse of the argument's stack home. Later
  rwad.dll FinishExecute (0x10072BAC) clamps the count and assigns a valid entry.
  The source records this release behavior. All 27 unit annotations pass.
- 251210: Xbox WMA worker, 1,046/19. Keep next as the loop iterator and advance
  it after recovering obj/state. Initialize packetState, size, ok, looped,
  loopedAt and newPosition in that order; newPosition last restores EBX.
  All 28 WMA annotations pass. No qualifiers or helper changes were required.
- 24F410: Xbox wave setup, 967/24. Cache format before buffer work; initialize
  created before is3D. Preserve descriptor field order and a named play offset
  before the final fresh format pointer. The static mix helper 24ECC0 takes
  (state, is3D); its existing caller was adjusted and retains identical bytes.
  Dependent helpers 24EDC0 (116/5) and 24F350 (33/0) are placed with it.
  All 105 unit annotations pass; no new qualifiers or shared types.

Only 23E690, 24B510, 24BB00, 24C230, 24E710 and 2516E0 remain. VAG wrapper
24BB00 and caller 24C230 are exact in scratch but await their block encoder.
