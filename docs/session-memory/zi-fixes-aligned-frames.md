---
name: zi-fixes-aligned-frames
description: "/Zi makes CL 13.10.3077 emit the image's 8-byte realigned (ebx) prologue; unblocks the 16-aligned-frame functions"
metadata:
  node_type: memory
  type: project
  originSessionId: ce8a3a7f-545d-4b1e-be24-7d4c060a02bb
  modified: 2026-09-26T18:08:59.456Z
---

Found 2026-09-26 (scratch tests only, main tree untouched at the user's request): adding `/Zi` to the
src/* flags makes the XDK compiler (13.10.3077, byte-identical to the XDK 5849 download's vc71 CL)
emit `53 8b dc 83 ec 08 83 e4 f0` for functions with a 16-aligned local, exactly like the image.
Without it the compiler emits `push ecx` (4 bytes), which is why docs/toolchain.md listed about 253
functions as blocked. /Z7 does the same. sub_FC8F0 matched byte for byte with /Zi on the first try.
Recompiling all 119 units with /Zi kept every existing match (3317 ok; the only 2 diffs were
unfinished unit_1154A0 work, and they fail the same way without /Zi).

**Why:** the image was evidently built with debug info on. It doesn't change other codegen.
**Applied 2026-09-26** (user approved): config/flags.txt src/* has /Zi, build_probes.compile_unit adds a per-object /Fd; build PASS with 3376 OK.
**How to apply:** retry the aligned-frame functions (sub_110A60, sub_FF030,
sub_100680, vf_03C 0x101550, sub_19F90, ...). Test harness: scratchpad xtrial.py / xall.py.

Slot order in these ebx frames (found 2026-09-26, type_3D32F8::sub_76960 and others): locals are
not ordered by name; each takes its slot where it is first used, interleaved with the compiler's
temporaries, so the slot solver does not apply. When two floats sit reversed (y above x), they are
one RwV2d/RwV3d. `this` is always at -4.
