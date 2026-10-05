---
name: inline-reserve-and-placement-delete
description: "Unexplained extra temporaries/frame bytes: a callee defined in-class but not inlined (reserves its expansion's slots); a declared matching placement delete (extra new-result copy)"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T17:12:05.235Z
---

VC7.1 habits found on 2026-09-25 (unit_0824A0; see docs/toolchain.md, "Inline functions that are not inlined, and placement delete"):
1. An in-class function or destructor that `delete`s is not inlined at /Ob1. It is emitted as a COMDAT and called, but every caller's frame still reserves the expansion's temporaries (8 bytes per failed site; they nest). A frame a few bytes too large next to such a call is the symptom. The fix is to define the callee in the class body. Don't invent unused locals.
2. If `new (x) T` copies its result through one more temporary than expected, declare the matching placement `operator delete(void *, same extra args)`.
3. A derived class's constructor (base has a user-declared destructor) is NOT inlined into `new (x) Derived` unless that matching placement delete is declared. With it, write `p = new (p) T;` with no extra named local (the delete adds the copy temp). Found 2026-09-26 in unit_0FB7A0 (light/world extensions).
4. Found 2026-09-28 in unit_1A6140. An in-class constructor that has nothing to do with delete can also fail to inline. type_1A7AA0's ctor (empty body, base ctor with a default ref arg) is called out of line at 0x1A7AA0. Yet the caller (sub_1A6140) reserved exactly its expansion's slots (its default-arg temp plus three `this` temps = 16 bytes = "four unused slots").

5. Found 2026-09-28, string temporaries with an in-class ctor that is not inlined (type_1A5EA0(const char *)). An explicit `f(T(x))` stores the ctor's eax result through two extra temporaries. The implicit conversion `f(x)` (param `const T &`) passes `lea temp` directly, which is what the image does. So when the image passes `lea temp`, make the conversion implicit, if necessary by changing the callee's param type (sub_1C84F0 takes `const type_1A5EA0 &`).
6. An implicit conversion in an assignment (`t = std_string_expr`, with T having an in-class ctor from std::string) calls the base class's copy ctor out of line. As a function argument, the same conversion is inlined. The out-of-line piece is the library's own function (sub_1C85F0 = std::string's copy ctor, not type_1A5EA0's).

7. Found 2026-09-28: type_4F8054_B0::sub_1A8050 (the peers' mask) is defined in its class but not inlined. Every caller reserves its two slots. The old `unused_slot()` pairs and get_2's "unused locals" were stand-ins for this; both are removed and get_2 is gone. Suspect any remaining `unused_slot()` stand-in of being a callee's reservation.

8. Found 2026-09-28: a BASE class's ctor/dtor defined in class but not inlined (type_10F710: 10 and 6 slots) makes every derived ctor/dtor reserve them. Moving them in-class also moves the base's vtable, ??_G and dtor COMDATs to the units that construct it (move their match lines there). A base dtor that IS expanded (type_3D94B8's) is also just in-class.

**Method:** if the image's frame has N extra unused slots, look at the out-of-line callees (same unit or header). Compare each callee's own frame, its temporaries excluding its `this` slot, with N. Then move the matching one into its class body.

**Why:** these explained four "unmatchable" functions at once (plus fake-local stand-ins I had wrongly added), and later the network player's constructor.

**How to apply:** use them on any parked function with "frame N bytes larger / unused slots" (the manager's destructor, sub_1ACBA0, sub_1AD750, sub_1A4200, type_505188, sub_1A8990, type_1CB670, sub_1CB720, ~type_1D0100, sub_1D0F60). Related: [[local-names-first]], [[cm-replay-limits]].
