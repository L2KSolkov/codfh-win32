# Latent bugs

Bugs that the byte-identical (placement/M7) build never shows but a **non-matching build** does:
the plain build (`tools/plainbuild.py`), the research builds on top of it, and the Win32 port
(docs/WIN32_PORT.md). Found 2026-10-05 while running the plain build in xemu (xbdm crash triage),
first on the multiplayer maps, then with single-player levels loaded into the multiplayer
executable (the research patch's `/levels` page).

Three kinds:

- **A. Plain-build bugs**: our source declares something differently from the image (size,
  alignment, identity). The placement link hides it because every name is pinned to its image
  address; a normal link gives each declaration its own storage. These are *our* bugs and must be
  fixed for any non-matching build, under `#ifdef CODFH_PLAIN` (and `CODFH_WIN32` for the port).
- **B. Original-game bugs**: unguarded assumptions in the game's own code (null pointers, empty
  pools, indexes out of range, infinite loops). The shipped game never reaches them in normal
  play; anything that changes the content or the timing (the port, mods, the research tools)
  can.
- **C. Multiplayer-executable limits**: things the multiplayer executable leaves out or sizes
  for multiplayer only. Not bugs, but they decide what single-player content can run on it.

Addresses are image addresses (the matching build's); research fixes live in the research patch
under `#ifdef CODFH_DRAW_TRIGGERS` and are not in the repository.

## A. Plain-build bugs

| What | Where | Symptom | Status |
|---|---|---|---|
| Fields of a bigger object declared as separate globals (aliases), e.g. `dword_4F8180` is `unk_4F7EB8.unk_2C8` | 171 names, `tools/session/overlapvars.py --aliases` | the alias keeps its own zeroed storage: NULL dereferences in the multiplayer menus | fixed: references under `CODFH_PLAIN`, bound after `#pragma init_seg(lib)` (`da52532c3`, `0fd5d04f9`) |
| Buffers the image lets overrun into the next variable (`unk_4498D4`, the script VM's argument stack) | `alfaobject.h`, `unit_06CA60` | writes past the declared size land in unrelated variables | fixed (`43e909fbc`): declared at the real size under `CODFH_PLAIN` |
| SSE matrices needing 16-byte alignment | `unit_122FB0`, `unit_19E500` | `movaps` faults; VC7.1 ignores `__declspec(align)` in `.bss` | fixed (`43e909fbc`): an initializer moves them to `.data` |
| Fixed-size `memset`s over a block of several image variables (`dword_4B8780`, 0x48 bytes) | `unit_0D7F20` | clears unrelated variables in a normal link | fixed (`43e909fbc`): one clear per variable |
| **`byte_44E490` declared as one byte; the image has a 0x100-byte buffer (0x44E490-0x44E590)** | `unit_0824A0.cpp`, `include/types/soundbank.h`; written by `strcpy` in `unit_192BE0.cpp:254` (a sound's subtitle line) | a subtitle overwrote the pointers after it (`dword_44C0A8`, RenderWare Audio's object): crash in `sub_23BFE0` on the next `LoadSoundBankSynchronously`. Multiplayer maps never play subtitled sounds | fixed in the working tree (uncommitted): `RwUInt8 &byte_44E490` bound to a 0x100-byte buffer under `CODFH_PLAIN` |

**The open class: scalars that are really buffers.** `byte_44E490` was a one-byte declaration with
an unused gap after it. M5's gap-fill arrays are sized to the next variable (so they are safe);
plain scalars followed by a gap are not. An audit should list every global whose declared size is
smaller than the distance to the next image variable and that is used by address (`&name`,
`strcpy`, `memcpy`, `sprintf` targets, array indexing through a cast), and size each from its
uses. Until then, expect more of these when new content (strings, counts) exercises them.

## B. Original-game bugs (unguarded assumptions)

| Function (unit) | Assumption | Trigger seen | Consequence | Research fix |
|---|---|---|---|---|
| `sub_D56D0` @0xD56D0 (`unit_0D5170`) | the "no sacrificial lambs" warning reads the last candidate's trigger `l34->unk_90..98` | entity memory full and nothing to evict | NULL read, crash | skip the warning when `l34` is NULL |
| `sub_8B180` @0x8B180 (`unit_08AB60`) | the 100-entry tracker pool `dword_4B2188` never runs dry (its sibling pool is checked) | "ToggleCCESSPoolCreation" on a single-player level | NULL write | return 0 when the pool is empty |
| script commands' `SCRIPT_CHECK` (`unit_0441B0`, 939 uses) | the checks are asserts: in release they only call the debugger hook `sub_44220` and carry on | any command whose object/player lookup fails, e.g. "LockPlayerMovement" with no local player | NULL dereferences in the command | under the research define a failed check returns with a 0 result (helpers return; three value-returning functions keep the original) |
| `sub_1BD450` @0x1BD450 (`unit_1BD340`) | a dropped weapon's pickup settings name a model this map loaded | dropping a weapon the map never had (multiplayer swap) | `sub_FB760` clones NULL: crash | borrow the weapon's handheld model, else no pickup |
| `type_3DC048::vf_03C` (`unit_155470`, tank) | there is always a local player | a tank updating while the player is between respawns | NULL read of `unk_4D0` (two places) | no player is no driver |
| `type_3DC9B0::vf_054` @0x167970 (`unit_166990`, mounted gun) | there is always a local player | a mounted gun drawn while the player is between respawns | NULL read of `unk_1B28` | **not fixed** |
| `type_DC400::sub_E5480` (`unit_0DC400`, HUD) | a local player exists while a subtitle shows; the team-icon index `sub_1AF2F0()` is 0-3 | subtitle during respawn; a CTF HUD with no rules object (`unk_4F7EB8.unk_280`, index -1) | NULL read; `unk_98[-1]` read as a texture, `0xFFFFFFFF->raster` | null-player check; out-of-range icon = none; untextured draw for a NULL texture |
| `sub_80910` @0x80910 (`unit_07CA20`, animation step) | the animation has frames and a sane duration | a gimp's animation the executable never loaded: 0 frames, duration ~2.7e-44 | `while (t > duration) t -= duration;` never ends: hang | skip such animations |
| `type_10F710::sub_10DA70` + `sub_10E930` (`unit_0FD730`, weapon streaming) | only the two held weapons' bank slots are in use | streaming a weapon while a grenade (not a held weapon) is in hand | the in-hand model is freed while drawn: crash in `RpGeometryDestroy` | the research give picks a slot no in-use model comes from |
| `type_10F710_1A48::sub_1170B0` (`unit_116310`, draw weapon) | the weapon copy has a model | a single-player level's starting weapon whose bank was never streamed | NULL clump through `sub_173180`, `vf_034` | skip drawing a weapon with no model |
| `type_3DA5A0::vf_018` (`unit_116310`, grenade throw) | the settings name a throw animation (`unk_2C`) | grenades on the multiplayer maps (`unk_2C` 0 or the hash of "") | the throw waits for an animation event that never comes: grenade held for good | throw at once (events 1900 then 1) when the projectile object is loaded |
| `cNetPlayerTrigger` / spawn lists (`unit_1BE4D0`, `unit_1C0910`) | the level has a `cNetPlayerTrigger` and `cNetSpawnPoint`s | a single-player level in the multiplayer executable | NULL `unk_4F7EB8.unk_278`; `RpRandom() % 0` | first `PlayerTrigger` made a `cNetPlayerTrigger`; static stand-in spawn points |

Pattern: **the single-player code assumes a local player always exists** (105 reads of
`sub_1745A0(0)` in 36 files). The multiplayer flow deletes the player between death and respawn,
so every single-player entity, HUD element or script that runs then can hit a NULL player. The
cases above are the ones seen; a general guard (pausing entity updates and drawing while there is
no local player on a single-player level) is the alternative to fixing them one by one.

## C. Multiplayer-executable limits

| Limit | Where | Effect on single-player content | Research workaround |
|---|---|---|---|
| Level names: only `L_NULL`, `MP_1`..`MP_10` | `sub_19B060` (`unit_19AAB0`) | single-player levels cannot be chosen | `/levels` overrides the folder in `sub_D7F40` (`unit_0D7F20`) |
| Starting sections: the level's `StartingSections` asks for a list that is all zero; the single-player game fills it through `sub_1727E0` | `unit_0B0410`, `unit_0D7F20` `sub_D8660`, gate `dword_4B870C` in `sub_D7570` | the game waits for a first section for ever (black screen) | load section 1 into slot 0 |
| Entity pools (`dword_3D7130`): no pool a soldier (0x2170) may use (sizes under 0x21D0 are kept to pools 0-5); 0 slots of 0x790 and 0x29D0. `default.xbe`'s table: 0x790 x30, 0x2170 x15, 0x29D0 x10 | `unit_0D5170` `sub_D5320`, `sub_D56D0` | soldiers and vehicles cannot spawn | single-player counts; soldiers allowed into the 0x2240 pool |
| Root motion compiled out: `type_7C8D0::sub_7A580` never computes the step (`if (0)` block, absent from the binary) | `unit_078D60` | soldiers play the run cycle in place (AI, paths and collision all working) | the block enabled for single-player levels |
| Level objects come from a linear memory pool sized by the level stream | `RWS_NEW`, `LinearAllocationPolicy` | an object the stream did not declare (or a bigger class) gets NULL or overruns the pool | allocate such objects from the heap; never link them to messages |
| Grenade throw animations and pickup models are per map | weapon settings, pickup settings | given weapons/grenades from other levels lack them | see B |
