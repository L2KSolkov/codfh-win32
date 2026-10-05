---
name: unwind-inline-copies
description: "Unwind funclet calls a different address than the body's base-dtor call = inline base dtor (body expands it, funclet calls its COMDAT copy); plus the parked STL-reserve cases"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T03:42:06.831Z
---

Found 2026-09-28 (kujuUI, unit_1E72C0): a link DIFF in `__ehhandler$X-0xN` saying the funclet's call
resolves to A but the image encodes B, where the dtor body calls A. The direct base's destructor is
inline (empty, in class): the body expands it into a call of the base's own base/member dtor (A,
0x1E0FA0), while the unwind funclet calls the inline dtor's out-of-line COMDAT (B, 0x20E940, which
just calls A). Model it as `Derived : Mid<T>` with `~Mid() {}` in class over `Base<T>` whose dtor is
out of line; alias Mid's dtor to B and Base's to A.

Also parked (docs/questions.md): sub_1E5280 (font ctor) and sub_1E7A80 reserve 32/16 bytes more
than the image around type_1A5EA0/type_1CB670 string pieces; likely an xstring difference (same
root as [[string-ctor-out-of-line]]). Don't sink more time into them without new evidence.

**How to apply:** check [[inline-reserve-and-placement-delete]] first; if the extra frame is only
around std::string expansions, park.
