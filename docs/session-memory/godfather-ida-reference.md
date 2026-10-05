---
name: godfather-ida-reference
description: "Godfather IDA instances with PDB: 13339 release, 13340 DEBUG (original RW Xbox loops/cases); names, types, locals; read-only via tools/gf.py/gfpy.py TOOL JSON PORT"
metadata:
  node_type: memory
  type: reference
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T17:32:11.134Z
---

User pointed out (2026-09-30) a second IDA instance: ears_godfather_r.xbe (The Godfather, Xbox, with MAP+PDB). Its MCP server is at http://127.0.0.1:13339/mcp (13337 = our game, 13338 = game_framework_d3d_noopt.exe, a PC d3d build without optimisation). 13340 = ears_godfather_d.xbe, the DEBUG build: decompiles show the original loops, helper calls (j___rwXbRenderStateInit not inlined) and case structure. Check it FIRST when an RW Xbox function won't match (e.g. _rwXbCacheInit: a copy loop the optimiser turned into memset/memcpy, and Count[i] = 0 inside the stage loop).

- The ida-pro-mcp tools in this session only reach 13337; call others by JSON-RPC (`tools/call`).
- Scratchpad helpers: gf.py TOOL JSON [PORT] (read-only tool whitelist) and gfpy.py SNIPPET [PORT] (py_eval, refuses writing-looking code).
- Never modify these databases either (see [[no-ida-edits]]).
- The Godfather RW is also optimised, but the PDB gives real function/local names (`zero`, `one`), struct layouts (`_rwXbStateCache`, `RwXboxRasterExtension`, `_rxXboxDriverGlobals`, `RwXboxDeviceConfig`) and global C names (`RwXbStateCache`, `RwXbTextureCache` have no leading underscore).
- Print a type: ida_typeinf.tinfo_t().get_named_type(None, name) then ._print(name, PRTYPE_MULTI|PRTYPE_TYPE|PRTYPE_DEF); list types with type_query {"queries":{"filter":"*rwXb*"}}.

Related: [[xbox-driver-from-asm]].

How to use the debug build (13340) well:
- Hex-Rays reorders cases/conditions; read the DEBUG ASM instead (scratchpad gf_cases.py / gf_range.py style py_eval over idautils.FuncItems): unoptimised layout = source order. `test; jnz ELSE-ish` with the then-block first means the source condition is negated (`if (!(format & mask))`).
- The debug frame's named locals and block structure carry over; `[ebp+type]`-like slots typed as an enum are switch temporaries, not locals.
- Godfather is RW 3.7 ("3.7-040719"): it adds error checks our 3.6 image lacks; keep only what the image shows. XDK unlock calls are empty inlines (invisible).
- A small `switch` with a missing value (0/4/5) explains a `je / jle 3 / jle 5` compare tree on a widened int.

- The DEBUG instance (13340) has real local names and every local, even ones the decompile hides: `gf.py stack_frame {"addrs":"0x..."} 13340`. A reload after a call (e.g. `x->a[strlen(x->a)-1]`) = a separate `len` local there. Its decompile can flip if/else polarity; trust the debug block order.
- VC7.0 /Ob2 emits a function that calls a later-defined inline candidate after that callee (rtfsxxbx: FOpen after FileExists); keep the source order.
