---
name: fast-build-tools
description: Use tools/cmf.py (incremental ibuild.py, no redundant final build) instead of cm.py; ~30 s per commit instead of ~100 s; the user asked not to edit cm.py
metadata:
  type: feedback
---

2026-09-29, at the user's request ("make this a different script, dont edit cm.py"):
- The tools/ibuild.py is tools/build.py's gate with incremental compiles. A unit is recompiled only when its source, flags, a header from its /showIncludes list, or its object changed. Every function is still matched on each run. It prints the same `== PASS`. No-change runs take 10 s instead of 35 s.
- `cmf.py` is cm.py (same arguments, CMUNIT) using ibuild.py. It skips the final rebuild when the tree is byte-identical to the one the first build passed. A commit takes ~30 s. Use it instead of cm.py. cm.py and the repo's tools stay untouched.
- 2026-09-30 (user request): the workflow tools now live in tools/ (cmf, cm, ibuild, fdiff, ncmp, rawcmp, vtry, xdis, xfn, gf/gfpy/gfd, xdkalias, bsolve, sdiff, vva, srep, ...; listed in docs/toolchain.md). Their work files (blog.txt, fdiff.obj, vtry_*.c, the inc overlay) are in build/tooltmp/. Run them from the repo root: `CMUNIT=rw/... python tools/cmf.py ADDR...`, gate on build/tooltmp/blog.txt. New reusable scripts go into tools/ too.
- Name searches: bsolve's "buckets [0, 0, …]" is real (most short names share bucket 0). Within a bucket, the local declared last lands nearest ebp. So declare the names farthest slot first. That solved sub_20DC80 in one compile. pnames.py (the parallel brute force) compiles the whole unit and is slow on big units; use it only for 2-3 names.
- A byte temp below the locals after a statement with a string temporary = the if condition saved across the temporary's destruction. Write the condition inline, not as a named bool.

**Why:** the user repeatedly asked for faster tooling and multithreaded searches.
**How to apply:** commit with `CMUNIT=unit_X python tools/cmf.py -m "msg" ADDR...`. Related: [[cm-one-at-a-time]], [[local-names-first]].
- `applyb.py SRC ADDR "S=name ..."` takes bsolve's output. It renames lv_S and rewrites those function-scope declarations farthest slot first. bsolve + applyb solved sub_20D8D0's 12 slots in one compile. Draft locals as lv_<slot> so this works directly.
- 2026-09-29 (user: "use faster scripts", "or use bprobe"): never run tools/local_names.py (minutes). Run bsolve, then pass its *picked names* to applyb; don't keep var_N names. `$S/fastnames.py` probes a tiny ranks() function holding just the locals (bool/int) in ~0.3 s per compile to confirm a layout. `tools/bprobe2.py` is bsolve in 80-name batches.
- Script VM: a gap of 0x14 unused bytes above the temporaries next to a `sub_44220(e)` call = `SCRIPT_CHECK(e)` (type_44350.h). A handle compared via `get_unk_04_h()` (struct returned by value) gets its slot among the named locals (sub_6A1A0).
- Use `tools/bprobe4.py SLOTS` for name solving. It pads every probe batch until all 16 buckets show, so bucket numbers agree across batches (bsolve/bprobe2 batches can disagree and misplace a few slots). It takes about 2 s for 30 slots; then run applyb. Large struct locals start on 8-byte boundaries, so size iterator/struct stand-ins to fit (sub_91F40).
- cmf -m fails with 'nothing added to commit' when only the unit changed (no header/config prereqs): rerun cmf WITHOUT -m; replay makes the match commit.
- Git Bash rewrites args like /O2 into paths when calling python: set MSYS_NO_PATHCONV=1 for compiler-flag arguments.

2026-09-30 (user asked why not cmf.py): cmf.py also commits RenderWare C units — CMUNIT=rw/driver/xbox/xbconvrt (it picks .c when that file exists; the header commit stages src/rw and include/rw/sdk). Use it for RW matches instead of rwci.sh; rwci.sh only for non-match edits (imports, renames, docs).
