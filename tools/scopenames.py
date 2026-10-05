"""scopenames.py ADDR SLOT... : search names for the function-scope locals of
the function annotated `// match: sub_ADDR`, leaving block-scoped locals alone.
Each SLOT (hex, e.g. 4 8 C 10 1C 20) is a function-scope local currently named
var_SLOT. Tries combinations of forms by a rank probe, then confirms each by
compiling the unit and comparing with tools/match.py."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import itertools, os, re, subprocess, sys
sys.path.insert(0, _os_repo.path.join(_REPO, r"tools"))
from build_probes import compile_unit, flags_for, load_flags
from coff import Coff
import match
from xbe import Xbe

ROOT = _REPO
SRC = os.path.join(ROOT, "src", "recovered", "unit_012000.cpp")
FORMS = ['var_%s', 'local_%s', 'v%s', 'l%s', 'var%s', 'lv_%s', 'loc%s',
         'ebp_%s', 'stk_%s', 'slot_%s', 'bp_%s', 'fp_%s', 'lcl_%s', 'frm_%s']
D = os.path.dirname(os.path.abspath(__file__))
addr = int(sys.argv[1], 16)
slots = sys.argv[2:]
flags = flags_for("src/recovered/unit_012000.cpp", load_flags()) + ['/I' + os.path.join(ROOT, 'include')]

text = open(SRC).read()
m = re.search(r"// match: sub_%X @ 0x[0-9A-F]+\n" % addr, text)
start = m.start()
n = re.search(r"\n// match: ", text[m.end():])
end = m.end() + n.start() + 1 if n else len(text)
block = text[start:end]
symbol = None
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))

def trial(names):
    b = block
    for s in slots:
        b = re.sub(r"\bvar_%s\b" % s, names[s], b)
    t = text[:start] + b + text[end:]
    path = os.path.join(D, "trial_unit.cpp")
    open(path, "w").write(t)
    obj = os.path.join(D, "trial_unit.obj")
    if not compile_unit(path, obj, flags):
        return False
    c = Coff(obj)
    global symbol
    if symbol is None:
        for s in c.symbols if hasattr(c, 'symbols') else []:
            pass
    sym = re.search(r"\?sub_%X@[\x21-\x7e]*" % addr, open(obj, 'rb').read().decode('latin-1'))
    ok, msg = match.compare(obj, sym.group(0), addr, image, {})
    return ok, msg

# rank probe: a function with one int local per candidate name
cands = [f % s for s in slots for f in FORMS]
probe = "void rank_probe() {\n" + "".join("    int %s;\n" % c for c in cands) + \
    "".join("    %s = %d;\n" % (c, i) for i, c in enumerate(cands)) + "}\n"
ppath = os.path.join(D, "rank_probe.cpp"); pobj = ppath[:-4] + ".obj"
open(ppath, "w").write(probe)
assert compile_unit(ppath, pobj, flags)
c = Coff(pobj)
b = c.function_bytes(c.find_function("?rank_probe@@YAXXZ"))
if isinstance(b, tuple): b = b[0]
code = bytes(b)
rank = {}
for i, cname in enumerate(cands):
    # mov dword ptr [ebp-X], imm32 : c7 45 XX imm or c7 85 XXXXXXXX imm
    imm = i.to_bytes(4, 'little')
    k = code.find(b"\xc7\x45")
    pos = 0
    while True:
        j = code.find(imm, pos)
        if j < 0: break
        if code[j-3:j-1] == b"\xc7\x45":
            rank[cname] = -int.from_bytes(code[j-1:j], 'little', signed=True); break
        if code[j-6:j-4] == b"\xc7\x85":
            rank[cname] = -int.from_bytes(code[j-4:j], 'little', signed=True); break
        pos = j + 1
# want: higher slot (larger N) -> larger offset below ebp -> rank increasing with slot
order = sorted(slots, key=lambda s: int(s, 16))
tried = 0
def walk(k, prev, chosen):
    global tried
    if k == len(order):
        yield dict(chosen); return
    s = order[k]
    for f in FORMS:
        nm = f % s
        if nm not in rank: continue
        if prev is None or rank[nm] > prev:
            chosen[s] = nm
            yield from walk(k + 1, rank[nm], chosen)
            del chosen[s]
ORIG = None
def score(names):
    global ORIG
    r = trial(names)
    if not r:
        return -1
    ok, msg = r
    if ok:
        return 1 << 30
    obj = os.path.join(D, "trial_unit.obj")
    c = Coff(obj)
    sym = re.search(r"\?sub_%X@[\x21-\x7e]*" % addr, open(obj, 'rb').read().decode('latin-1')).group(0)
    b = c.function_bytes(c.find_function(sym))
    if isinstance(b, tuple): b = b[0]
    if ORIG is None:
        ORIG = image.read(addr, len(b) + 64)
    return sum(1 for x, y in zip(b, ORIG) if x == y)

cur = dict((s, 'var_%s' % s) for s in slots)
print("initial trial:", trial(cur))
best = score(cur)
improved = True
while improved and best < (1 << 30):
    improved = False
    for s in order:
        for f in FORMS:
            nm = f % s
            if nm == cur[s]:
                continue
            t = dict(cur); t[s] = nm
            sc = score(t)
            if sc > best:
                best, cur, improved = sc, t, True
                print("better", hex(best) if best < (1 << 30) else "MATCH", cur)
                if best >= (1 << 30):
                    break
        if best >= (1 << 30):
            break
print("final", "MATCH" if best >= (1 << 30) else hex(best), cur)
