---
name: c-block-layout-and-slots
description: "VC7.1 C (RW Xbox) shapes: if-polarity decides block layout after jump threading; stack slots follow first use/lifetime, not declaration order or names; search with tools/ptry.py"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T23:20:00.839Z
---

Learned on the MatFX Xbox renderers (effectPipesXbox.c, 2026-09-30):

- Block layout after jump threading: when a flag set in several branches is tested later (`needSecondPass`, `dualPass`), the image places the *then* block of the later `if` right after the setting branches. Matching took inverting it (`if (!needSecondPass) {single} else {second}`, `if (!dualPass) {...} else {dual}`), and `if (x != UV) {...} else {...}` / `if (!(flags & TEXTURED2))` to get `je`/`js` fallthroughs right.
- Unsigned byte tests: `color.alpha < 0xFF` gives `jae`/`jb`; `!= 0xFF` gives `je`.
- In these C files stack slots ignore declaration order and local names (240 permutations and renames all scored the same); they follow first-use order (swapping two Get calls swapped two slots) and lifetime packing. Arrays only pack into dead space when block-scoped; which scope a 12-byte local lives in (function vs loop) moved it by 4. Search scopes/orders with tools/ptry.py (parallel variants, sorted by ncmp) instead of guessing.
- One load for four stores: `a[0] = a[1] = a[2] = a[3] = x;`; in-place `shinny |= shinny << 8 | ...` rather than a new local.
- A static's unused parameter is dropped from the custom calling convention unless it is passed on to another call.
- tools/xtrace.py decodes cache-macro stores into `TSS stage TYPE = v` / `RS STATE = v` lines for reading big render functions; tools/framemap.py compares frame offsets (push tracking breaks after early-return paths).
- Dead parameter slots (PTank InsSetup, 2026-09-30): which dead param home slot a local reuses follows the order the parameters are first referenced in the source. Two locals swapped between `data`'s and `atomic`'s slots until `atomic` was read after the `right = &data->right` initialisers (PTankPrv/geom assigned as statements, not in declarations). Declaration order, dummy locals and argument order changed nothing.
- Bitfield read-modify-write (`mov al,[slot]; and al,0xf5; or al,5; and al,0xf; ... or al,0x40`) instead of constant byte stores = a field set in both arms of an if/else (`if (n) {..norm = PACKED;} else {norm = NONE;}`), not a default followed by an override.
- cmf with a static callback table (`defaultCB = {..static fns..}`): put the table directly under the last function's `// match:` line (with RW-style static prototypes at the top), so strip and replay take it with that function; anywhere else the header or intermediate commits fail with C2129.

Related: [[xbox-pipeline-shapes]], [[block-local-allocation]].

DMorph callback follow-up (2026-10-01): a CFG-aware ESP map revealed that
the image reused currentBlock +0x24, j +0x14 and target +0x28 across four
attribute passes, while separate draft locals took different slots per pass.
Sharing those locals (plus l, rle, scale and delta pointers) recovered the
entire frame. Keep k/m/maxl scoped inside the passes and initialize j before
k/m: hoisting every counter changed the final-alpha x87 scheduling. Sharing
l fixed the remaining copy calls. Both callback and block helper now match
with VC7.1; see src/rw/plugin/dmorph/xbox/dmorphpipeg.c and questions.md.
