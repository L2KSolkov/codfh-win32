---
name: asm-byte-swap-stays-binary
description: Owner rule 2026-10-01 — no __asm unless the original function had it; such regions go between "// begin original __asm" / "// end original __asm" (audit allows)
metadata:
  type: feedback
---

Owner (2026-10-01): "for the remaining items, no __asm unless the function originally had it." (Earlier: "asm the rest of bink" — Bink only.) So:
- Functions whose original code used inline asm (ror byte swaps sub_1F81E0/1F8300, FPU control word sub_19D290/2D0, RWA rdtsc sub_244930/940, RenderWare's own Xbox asm helpers) are written with that asm between `// begin original __asm (evidence)` and `// end original __asm` lines; tools/audit_sources.py accepts only those regions (plus the debug guard and src/bink).
- Never transcribe other functions (RWA, RW, game near misses stay C work). PLAN.md Amendments records the rule.

**Why:** owner's explicit rule; transcribing compiler output is not decompilation.
**How to apply:** look for evidence the original had asm (instructions no compiler emits: rdtsc, ror bx, fstcw, cvttss2si helper, ebx use at /Od) before using a region.
