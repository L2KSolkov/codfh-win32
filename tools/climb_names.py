"""climb_names.py SOURCE ADDRESS SLOTS [--apply]

Names the locals var_SLOT (SLOTS: comma-separated hex, nearest ebp first) of
the function annotated `// match: NAME @ ADDRESS` in SOURCE from the frame
offsets a /FA listing states, for flat functions local_names.py cannot
solve (its bucket ranks can be wrong when many names tie). Slot by slot, it
tries every name form and keeps the one that lands just after the previous
local, with the declarations written highest slot first (docs/toolchain.md).
A local the function never uses has no offset in the listing: leave it out
of SLOTS. With --apply the names are written into SOURCE."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys, os, re
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from scope_names import frame_offsets
from local_names import FORMS, function_name
src, addr, slots = sys.argv[1], int(sys.argv[2], 16), sys.argv[3].split(',')
apply_ = '--apply' in sys.argv
extra = ['m_%s', 'p%s', 'r%s', 's%s', 't%s', 'x%s', 'y%s', 'z%s', 'q%s', 'w%s', 'o%s', 'u%s']
forms = FORMS + extra
text = open(src, encoding='utf-8').read()
name = function_name(text, addr)
m = re.search(r'^// match: \S+ @ 0x0*%X\n' % addr, text, re.M)
nxt = re.compile(r'\n// match: (?!__ehhandler)')
e = nxt.search(text, m.end()); e = len(text) if e is None else e.start() + 1
head, blk0, tail = text[:m.start()], text[m.start():e], text[e:]
rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
flags = flags_for(rel, load_flags()) + ['/I' + os.path.join(ROOT, 'include')]
out = os.path.join(ROOT, 'build', 'local_names'); os.makedirs(out, exist_ok=True)
tsrc = os.path.join(out, 'oclimb' + os.path.splitext(src)[1]); obj = os.path.join(out, 'oclimb.obj'); asm = os.path.join(out, 'oclimb.asm')
def build(names):
    blk = blk0
    for s, n in zip(slots, names):
        blk = re.sub(r'\bvar_%s\b' % s, n, blk)
    a = blk.index('{\n') + 2; z = blk.index('\n\n', a)
    lines = blk[a:z].split('\n')
    def sl(l):
        mm = re.search(r'\b(\w+)(\[[^\]]*\])?;', l)
        if mm and mm.group(1) in names: return int(slots[names.index(mm.group(1))], 16)
        return None
    dec = sorted([l for l in lines if sl(l) is not None], key=lambda l: -sl(l))
    rest = [l for l in lines if sl(l) is None]
    return blk[:a] + '\n'.join(rest + dec) + blk[z:]
def offsets(names):
    blk = build(names)
    # Close any namespace the kept head leaves open (the rest of the file
    # is dropped).
    opened = len(re.findall(r'^namespace \w+\s*\{', head, re.M))
    open(tsrc, 'w', encoding='utf-8').write(head + blk + '\n}\n' * opened)
    if not compile_unit(tsrc, obj, flags + ['/FA', '/Fa' + asm]): return None
    return frame_offsets(open(asm, errors='replace').read(), name)
names = ['var_%s' % s for s in slots]
ranked = sorted(slots, key=lambda s: int(s, 16))
compiles = 0
for k, s in enumerate(slots):
    best = None
    for f in forms:
        trial = list(names); trial[k] = f % s
        if trial[k] in trial[:k] or trial[k] in names[k + 1:]: continue
        o = offsets(trial); compiles += 1
        if o is None or trial[k] not in o: continue
        if not all(o.get(trial[j], -1) < o.get(trial[j + 1], -1) for j in range(k)): continue
        if k and not o[trial[k - 1]] < o[trial[k]]: continue
        # rank: how many other locals sit between the previous name and this one
        prev = o[trial[k - 1]] if k else 0
        gap = sum(1 for n, v in o.items() if prev < v < o[trial[k]])
        if best is None or gap < best[0]:
            best = (gap, trial)
            if gap == 0: break
    if best is None:
        print('stuck at slot', s, 'after', compiles, 'compiles'); sys.exit(1)
    names = best[1]
o = offsets(names)
print('final', all(o.get(n) == int(s, 16) for n, s in zip(names, slots) if n in o))
print(' '.join('%s=%s' % (s, n) for s, n in zip(slots, names)), '(%d compiles)' % compiles)
if apply_:
    blk = build(names)
    note = ('// Local names state their slots; plain var_N names reorder them '
            '(docs/toolchain.md).\n')
    line = blk.index('\n') + 1
    # after the function's EH pieces' annotations, which must follow its own
    while blk.startswith('// match: __ehhandler', line):
        line = blk.index('\n', line) + 1
    if any(not n.startswith('var_') for n in names) and not blk[line:].startswith(note):
        blk = blk[:line] + note + blk[line:]
    open(src, 'w', encoding='utf-8', newline='\n').write(head + blk + tail)
