---
name: library-local-names
description: "Recognised third-party C code (dlmalloc 2.7.0 at 0x1F90E0): write it with the library's own macros and local names; the frame layouts then match with no slot solving"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T07:27:47.920Z
---

When a region is a known library, write it in the library's own style. unit_1F90E0 is Doug Lea's malloc 2.7.0, identified by its malloc_state layout, largebin_index ladder and fastchunk-bit sense. Using the library's real macros and local names (av, nb, victim, bck, fwd, remainder_size and the rest) made 8 of 10 functions byte-identical on the first trial. Local layout follows name hashes, so the original names give the original slots.

**Why:** On 2026-09-29 this saved all the bucket solving. It also exposed the version's quirks, such as the binmap path unlinking inline and 2.7.0's `sYSMALLOc` lacking 2.7.1's checks.

**How to apply:** Once a library is recognised, recall its exact version's source and keep its macro spellings. Wrap byte-pointer casts in parentheses, `((RwChar *)(p)) + s` as dlmalloc does, or the audit's raw-offset rule fires. Run `tools/audit_sources.py` before cm.
