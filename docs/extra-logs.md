# Extra logs (CODFH_EXTRA_LOGS)

The GameCube build (`main.dol`, built Apr 2003 with the Dolphin SDK) keeps debug prints that both
Xbox builds compiled out. `tools/portbuild.py` defines `CODFH_EXTRA_LOGS` for the port by default
(`--no-extra-logs` leaves it out); the prints go through the debug print `sub_19A750`, which the
port writes to `codfh.log`. The Xbox builds never define it.

Each print was placed by its call site in the DOL (PowerPC disassembly of the code that loads the
string's address), matched to the same function in `src/recovered`:

| Text | DOL site | Port site |
|---|---|---|
| `Done reading type %d time=%.2f` | 0x8006AAE8 (loading thread) | `sub_813E0`, unit_0811C0: after each request |
| `Creating GodAsset: UV Anim (%x,%x)` | 0x800C3B48 | GodAsset reader, unit_18F3C0 |
| `GodAsset exists: UV Anim / texture dictionary / DFF geometry / DFF collide (%x,%x)` | 0x800C3BD4, 0x800C3D30, 0x800C3E80, 0x800C3FAC | the same reader's skip branches |
| `PLATFORM INDEPENDENT texture: %s`, then the `platform independent texture` assert | 0x800C2968 (callback), 0x800C2AAC | `type_3DF8F0::vf_000`, unit_18F3C0 |
| `Asset still loading!` | 0x800C6260 | `type_3DFD40::vf_00C`, unit_192BE0 |
| `CFreeList::GetFreeElem() m_maxElements=%d m_freeCount=%d`, `GetFreeElem %d/%d` (freelist.cpp:323) | 0x80135C58 | `type_16C2A0::sub_16C5A0`, unit_16C280 |
| `%s: Anim goes back!!!` (SAnimInterpolatorAddAnimTime) | 0x80063238 | `sub_80910`, unit_07CA20 |
| `%s: Anim goes back!!!` (SkelKeyFrameUncompress) | 0x80068A6C | `sub_7D2F0`, unit_07CA20 |

The prints only report; behaviour is unchanged (the GameCube's anim interpolator also restarts the
track from key 0 there, and its asserts stop the game: neither is copied).

Not ported:
- `*** Switching to <main/loading/audio> thread from <...> thread` (nine strings), `illegal memory
  type`, `function assumes pointer is non-null, please check in caller`: no code references them.
- `LOOP DETECTED` / `FOUND A LOOP` (asynchqueue.cpp:1558): a GameCube watchdog thread, resumed when
  a frame counter passes 1800, not in the Xbox code.
- The particle renderer's `Wrong number of particles` / `estimated=%d, rendered=%d`: the GameCube
  fills particle vertices on the CPU and counts them; the Xbox draws them in a vertex shader.
- GameCube platform code (Native/Gcn, DVD, memory card, AX audio, ProDG, STLport, Dolphin SDK).
