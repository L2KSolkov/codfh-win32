---
name: implicit-conversion-temp
description: A temporary passed by `lea` (no ctor-return slots) = implicit conversion (`s = "text"`), not an explicit type_1A5EA0("text") temp
metadata:
  type: project
---

Found 2026-09-29 (weapon selection's loading, 0x223970): the image built a type_1A5EA0 temporary with sub_1A5EA0 and passed it to the out-of-line assign by `lea` of the temporary, with no slots for the constructor's return value. Writing `lv = type_1A5EA0("weapon");` (or static_cast to std::string, or assign()) gives two extra return-value slots; `lv = "weapon";` (implicit conversion through the converting constructor, then the implicit operator=) matched.

**Why:** an explicit temporary's address comes from the constructor's return (eax spilled to slots); an implicit conversion's temporary is addressed directly.
**How to apply:** when a text temporary is pushed via `lea` right after its constructor call, try the implicit-conversion spelling. See also [[block-local-allocation]] (a /GS array declared in an inner block keeps function scalars above it).
