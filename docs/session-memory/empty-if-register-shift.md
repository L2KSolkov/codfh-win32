---
name: empty-if-register-shift
description: "Registers one step off after a statement = a compiled-out assert inside an empty `if` (no code, but shifts VC7.1's register rotation)"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T22:58:28.105Z
---

When everything after some statement uses the next register in the eax/ecx/edx rotation
(ours `mov eax` where the image has `mov ecx`, and so on to the end), add the source's
empty `if (cond) { }` there. Under /Od an `if` with an empty body and no else emits no code
but still advances the register rotation. Expression statements (`(void)0;`, `x;`) don't.

**Why:** RenderWare Studio's RWS_ASSERT/RWS_TRACE compile out inside `if (x<0) {...}`;
found in the event handler (UnRegisterMsg, UnLinkMsg, LinkMsgToEventHandler, 2026-09-26).

Refinement (2026-09-27, the free-list pool sub_16C5A0/sub_16C710): the shift equals the register
loads the condition would make, not one per `if`. `if (!unk_08) {}` (loads `this`) shifts one;
`if (!arg_0) {}` (compares memory directly) shifts none; a call in the condition emits code. Pick
conditions whose load count mod 3 gives the image's register.

Refinement (2026-09-28, the voice chat unit_1C60A0):
- Inline member functions can hold the checks. type_1DDE20_mask's add, clear and assign keep two
  checks each, which also matched sub_1A8050.
- A rotation between two tests in one `&&` chain needs nested ifs, with a check between them.
- With an else as the function's last code, write `{ A; return; }` in the nested if and put the else
  code after it.
- Scratchpad seqchecks.py walks the statements and inserts 1 or 2 checks, following fulldiff's
  first hunk. It ignores relocation-only hunks and strips CRs.

Refinement (2026-09-28, unit_1CCC00 and unit_1D48B0): count loads mod 3. `if (!dwordField) {}` is 1 load (this, then a cmp on memory). `if (!mask.unk_00) {}` on a word is 2 loads (this, then movzx). `if (!p->x) {}` is 3 loads, which is a no-op. For "+1", use TWO word checks (4 loads). Loop-body tests, and tests at a `je` block start, that come out one register early needed exactly that (sub_1D4990, sub_1CD780, sub_1CFD50). A getter feeding clear() on a local mask can carry the checks itself: joiner() has 2 dword checks, self() has 1. Checks inside test()/clear() break other units, and a checked test() copy adds a `this` temp.

Refinement (2026-09-28, sub_19DF40 and sub_1A84C0):
- When every operand around is in memory (globals, locals), a compiled-out check on a computed value takes a register: `if (!(local & 1)) {}` is +1. A plain `if (!local) {}` or a check on a global is +0.
- A shift starting in the middle of an `a && b` test: split it into nested ifs with checks between them (sub_1A84C0: +2 before the float part).

Refinement (2026-09-28, the packet engine sub_1D2CC0 and sub_1D21E0):
- Never-written frame slots right after an inline's temporaries (and before the next inline's) can be a compiled-out check that kept unused locals. The receive's two ack-block checks reserve 3 each: NETQUEUE_CHECK in game/netqueue.h, like SCRIPT_CHECK in types/type_44350.h. Test it by adding an inline with N unused locals where the gap's temporaries were created.
- A loop-body jump that is short in ours but near in the image (lens.py in the scratchpad compares instruction offsets) can be a `continue` in an if branch in place of an else.

Refinement (2026-09-29, type_DC400::sub_DD1C0): before two vcalls through a local (`p->vf()` passed on), the image had +2 on the first call and the second followed on from there. Two `if (unk_00) {}` before the first call only (one load each) matched both calls. Adding one before each call over-shifts the second. The shift carries forward into all later statements.

**How to apply:** look in the framework source for an assert or trace wrapped in an `if`
at the point where the rotation diverges, and keep it as an empty `if` with a comment.
With an else, see [[int-expression-shapes]] (empty then = `je body; jmp end`).
