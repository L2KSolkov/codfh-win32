---
name: xbox-pipeline-shapes
description: "RW 3.6 Xbox pipelines (world/skin/ptank/matfx): register-convention statics, static globals for no-alias caching, cmf config staging, Godfather debug as template, RW's own asm allowed"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T22:30:27.237Z
---

Learned matching RenderWare 3.6's Xbox pipeline files (2026-09-30):

- User rule (2026-09-30): "If a Renderware function originally used __asm, that is acceptable. Do not invent __asm that did not exist in Renderware." Evidence of RW asm = Godfather debug PDB (asm labels like `instv3dcopybegin`, a lone `cvttss2si` inline function). rwplcore.h now has the Xbox `RwFastRealToUInt32Inline` (`__asm cvttss2si eax, x`); the V3d/V2d instancers carry RW's MMX movntq `__asm` copy.
- Statics called with the compiler's own register convention (eax/esi/edi args): the caller only matches when the static is compiled beside it.
- To get the register convention at all, the static must modify its parameter (e.g. `shaderConstantPtr++` instead of a local copy) — MSVC then passes it in a register.
- A global written only in one file and read around loads of other floats: make it `static` — the image caches it in xmm registers (no-alias), ours reloads if it's extern.
- Nested call in an argument (`f(g(x)->pos, ...)`, `AddFragment(lpipe, NULL, NodeDefGet(), NULL)`): the image evaluates g first; a local for the call result fixes it.
- Operand order of `a*x + b*y` that the compiler won't flip from source: try scaling the parameter in place (`scale *= 255.0f`) instead of a new local (InstV3dMorph).
- Signedness of struct fields matters for loop compares (SkinPlatformData ints).
- Godfather release (13339) and debug (13340) builds are 3.7 but very close to 3.6 Xbox code; decompile them for structure and names.
- cmf.py: CMUNIT is relative to src/ (e.g. rw/plugin/matfx/xbox/effectPipesXbox); it stages config lists only in the header commit of a new unit; for an existing unit commit symbols/aliases/headers yourself first.
- ICF-folded trivial callbacks (return object) alias to `__rwerror` 0x2D9180 or CollisionDataConstructor 0x2FC4B0; generic `_rxXboxAllInOneSetRenderCallBack` is ICF-folded into the skin one (0x2D4B10).
