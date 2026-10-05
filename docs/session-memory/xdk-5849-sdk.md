---
name: xdk-5849-sdk
description: "XDK 5849 (Dec 2003) setup at C:\\Users\\Jordan\\Downloads\\2003-12 - 5849 - RecoveryISO+EXE, SDK (stripped)\\XBOX.SDK.5849.December-COMPLEX\\cpx-5849\\XDKSetup5849 — its libs may match the image better than C:\\xdk's; copy matching ones into the worktree"
metadata:
  node_type: memory
  type: reference
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-10-01T10:59:06.905Z
---

The user pointed (2026-10-01) to an XDK 5849 setup:
`C:\Users\Jordan\Downloads\2003-12 - 5849 - RecoveryISO+EXE, SDK (stripped)\XBOX.SDK.5849.December-COMPLEX\cpx-5849\XDKSetup5849`

Some Xbox libraries there may match the image better than the ones under C:\xdk. When one matches more, copy it into the worktree (the libraries the XDK placement uses, e.g. xdklib/ / build/xdk extraction — see [[xdk-placement]]) and use it.

**How to apply:** when an XDK piece fails to place or matches poorly with the C:\xdk lib, compare against this SDK's lib of the same name first.

Done 2026-10-01: copied 5849 d3d8, dsound, uix, xvoice, xonlines, xgraphics, xnets into xdklib/ (untracked). Tools take a library name with a slash as a worktree path (lib_scan.lib_path); `python tools/xdkplace.py xdklib/<lib>` placed 29 more functions. Same VC7.1 compiler as C:\XDK; no vc70 in 5849. See docs/libraries.md "The XDK 5849 libraries".
