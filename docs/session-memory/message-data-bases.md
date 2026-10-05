---
name: message-data-bases
description: Network messages (game/netmsg.h) have an empty base X_data with inline ctor/copy ctor declared BEFORE the vtable base; it gives the null-checked "p ? p+4 : 0" before vtable stores in copies
metadata:
  type: project
---

Found 2026-09-28 (cNetController's handlers, unit_1A8B20). A handler's copy of a message (`type_X m = *(type_X *)arg_8;`) compiles as follows:
- `cmp arg,0; je; lea/add +4` into a temp (a conversion no code uses);
- then the three vtable stores;
- then the fields copied straight from arg.

This matches `struct X_data { X_data(){} X_data(const X_data &){} }; struct X : X_data, X_vtablebase { fields... };`. The data base is empty with inline constructors and declared first. MSVC still puts the vtable base at +0, the empty base overlaps at +4, and the fields follow in X itself. The compiler inlines the implicit copy constructor for small messages and puts it out of line for larger ones (sub_1AF4F0, sub_1AF600). Those out-of-line copies get standalone `// match: ??0X@@QAE@ABU0@@Z` lines.

Converted so far: type_3E1074, 3E1044, 3E0EB8, 3E0FE4, 3E0FFC, 3E1014. Other messages still have the plain single-base form.

**How to apply:** when a handler or decoder shows that temp-then-vtable pattern, give the message its `_data` base. Never use `(RwUInt8 *)p + 4`, which the audit rejects. Related: [[empty-if-register-shift]].
