---
name: xdk-placement
description: M3 done mechanically: tools/xdkplace.py places installed XDK lib members (4,050 funcs) via build/xdk + config/xdk_members.txt; xdksplit fixes ranges
metadata:
  type: project
---
2026-10-01: M3 placement — `python tools/xdkplace.py [LIB...]` then `python tools/xdksplit.py`, then xbelink/build. Members extracted to build/xdk by tools/xdk_members.py (build step "xdk members"). Aliases auto-added from image encodings ("(M3)" evidence). Post-check resolves via placed pieces (twins!). Pitfalls fixed: duplicate member names (#N), labels inside asm members, `$L` symbols, SECREL relocs, merged lib sections (XDK_MERGES in match.py), IDA splitting a function (xdksplit grows ranges). Remaining XDK = members in other versions (stay binary, M7 stand-ins). Related: [[bink-library]].
