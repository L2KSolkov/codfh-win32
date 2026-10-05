"""cutpiece.py PIECE_ADDR AT_ADDR OBJ NAME: cut an installed member's datum out of a data stand-in
piece (PLAN M7).

The piece at PIECE_ADDR (src/xdk/standin_*.asm) holds, from AT_ADDR, the member OBJ's datum NAME
(its bytes checked against the image, relocation fields aside): the piece keeps what comes before
(under its name), the datum becomes OBJ's row at AT_ADDR, and what follows it becomes a piece of
its own (_unk_ADDR) with a row; config/splits.txt gets the extents."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

def write(path, text):
    """Writes PATH (bytes), retrying while another process (an indexer) holds it."""
    import time
    for k in range(50):
        try:
            open(path, 'wb').write(text)
            return
        except OSError:
            time.sleep(0.2)
    raise SystemExit('cannot write ' + path)


ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
pa, at, obj, name = int(sys.argv[1], 16), int(sys.argv[2], 16), sys.argv[3], sys.argv[4]
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
c = Coff(os.path.join(ROOT, obj))
x = next(s for s in c.symbol_list if s['section'] > 0 and s['name'] == name)
sec = c.sections[x['section'] - 1]
later = sorted(y['value'] for y in c.symbol_list if y['section'] == x['section'] and y['value'] > x['value'])
d = bytes(sec['data'][x['value']:(later[0] if later else len(sec['data']))])
ra = set()
for va, si, t in sec['relocs']:
    ra.update(range(va - x['value'], va - x['value'] + 4))
im = img.read(at, len(d))
assert all(d[j] == im[j] for j in range(len(d)) if j not in ra), 'the datum is not the image there'
end = at + len(d)

# the piece's lines as items of known size
lines = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read().split('\n')
row = next(l for l in lines if l.startswith('0x%08X ' % pa))
pname = row.split()[2]
asm = None
for f in os.listdir(os.path.join(ROOT, 'src', 'xdk')):
    if f.startswith('standin_') and f.endswith('.asm'):
        t = open(os.path.join(ROOT, 'src', 'xdk', f), 'rb').read().decode('utf-8')
        if ('; // match: %s @ 0x%08X' % (pname, pa)) in t.replace('\r\n', '\n'):
            asm = os.path.join(ROOT, 'src', 'xdk', f)
            break
raw = open(asm, 'rb').read().decode('utf-8')
nl = '\r\n' if '\r\n' in raw else '\n'
L = raw.replace('\r\n', '\n').split('\n')
i0 = L.index('; // match: %s @ 0x%08X' % (pname, pa))
j = i0 + 1
while not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
    j += 1
body = L[i0 + 1:j]
items = []      # (size, text, kind): a byte, a relocated dword, a 5-byte call/jmp, a $L label
for ln in body:
    s = ln.split(';', 1)[0].strip()
    m = re.match(r'^db\s+(.*)$', s)
    if m:
        # (a whole db line, its comment kept, unless the cut splits it)
        vals = [v.strip() for v in m.group(1).split(',')]
        items.append((len(vals), (vals, ln), 'dbl'))
        continue
    m = re.match(r'^dd\s+(.*)$', s)
    if m:
        for v in m.group(1).split(','):
            items.append((4, v.strip(), 'd'))
        continue
    # (a code stand-in's piece: img2masm writes a relocated call or jmp as the instruction, a
    # rel32 one, and a jump target as a $L_ADDR label)
    if re.match(r'^(call|jmp)\s+\S', s):
        items.append((5, ln, 'line'))
        continue
    m = re.match(r'^\$L_([0-9a-fA-F]+):$', s)
    if m:
        items.append((0, ln.strip(), 'label'))
        continue
    # (a code stand-in's piece, data disassembled as code: its label is `NAME:`)
    assert not s or s.startswith('PUBLIC ') or re.match(r'^\S+ LABEL BYTE$', s) or re.match(r'^\S+:$', s), \
        'unexpected line: ' + ln
pos, before, after = pa, [], []
start_labels = []   # (labels in the cut, with their offsets: their references go to the datum's symbol)
for sz, v, kind in items:
    if kind == 'label':
        assert int(v[3:-1], 16) == pos, 'label %s at 0x%X' % (v, pos)
        if pos < at:
            before.append((sz, v, kind))
        elif pos >= end:
            after.append((sz, v, kind))
        else:
            start_labels.append((v[:-1], pos - at))
        continue
    if pos + sz <= at:
        before.append((sz, v, kind))
    elif pos >= end:
        after.append((sz, v, kind))
    elif kind == 'dbl':
        for k_, b_ in enumerate(v[0]):
            if pos + k_ < at:
                before.append((1, b_, 'b'))
            elif pos + k_ >= end:
                after.append((1, b_, 'b'))
    else:
        assert pos >= at and pos + sz <= end, 'a relocated item straddles the cut'
    pos += sz


def emit(items_):
    out, run = [], []
    for sz, v, kind in items_:
        if kind == 'b':
            run.append(v)
            if len(run) == 16:
                out.append('        db ' + ', '.join(run))
                run = []
            continue
        if run:
            out.append('        db ' + ', '.join(run))
            run = []
        if kind == 'd':
            out.append('        dd ' + v)
        elif kind == 'dbl':
            out.append(v[1])
        else:
            out.append(v)
    if run:
        out.append('        db ' + ', '.join(run))
    return out


aname = '_unk_%X' % end
# (a label already in the file: a cut done before, half written; never a second definition)
assert not after or ('\nPUBLIC %s\n' % aname) not in raw.replace('\r\n', '\n'), aname + ' exists already'

# (a cut at the piece's start removes its label: the stand-ins' references to it, a table's
# pointer to the datum, go to the member's symbol, which must be external)
olds = ([] if before else [pname]) + [lb for lb, o in start_labels]
repl = dict([(pname, name)] + [(lb, name if not o else '%s+%d' % (name, o)) for lb, o in start_labels])
_old_pat = re.compile(r'(?<![\w?@$])(%s)(?![\w?@$])' % '|'.join(re.escape(o) for o in olds)) if olds else None


def _refs(text):
    return _old_pat is not None and _old_pat.search(text) is not None


new = []
if before:
    new += ['; // match: %s @ 0x%08X' % (pname, pa), 'PUBLIC %s' % pname, '%s LABEL BYTE' % pname] + emit(before)
if after:
    new += ['; // match: %s @ 0x%08X' % (aname, end), 'PUBLIC %s' % aname, '%s LABEL BYTE' % aname] + emit(after)

redirect = []
if olds:
    for f in os.listdir(os.path.join(ROOT, 'src', 'xdk')):
        fp = os.path.join(ROOT, 'src', 'xdk', f)
        if not (f.startswith('standin_') and f.endswith('.asm')):
            continue
        t = raw if fp == asm else open(fp, 'rb').read().decode('utf-8')
        body_ = '\n'.join(L[:i0] + new + L[j:]) if fp == asm else t
        if _refs('\n'.join(l for l in body_.split('\n') if not l.startswith(('EXTERN ', 'PUBLIC ', '; // match:')))):
            redirect.append(fp)
    assert not redirect or x['class'] == 2, '%s is referenced and %s is file-local' % (olds, name)


def _redirect(lines_):
    lines_ = [l for l in lines_ if not any(l.startswith('EXTERN %s:' % o) for o in olds)]
    lines_ = [_old_pat.sub(lambda m_: repl[m_.group(1)], l) if not l.startswith('PUBLIC ') else l for l in lines_]
    if not any(l.startswith('EXTERN %s:' % name) or l == 'PUBLIC %s' % name for l in lines_):
        k = max((i for i, l in enumerate(lines_) if l.startswith('EXTERN ')), default=None)
        if k is None:
            k = next(i for i, l in enumerate(lines_) if l.strip().startswith('.model'))
        lines_.insert(k + 1, 'EXTERN %s:BYTE' % name)
    return lines_


L[i0:j] = new
# (the remainder's label referenced in the file before, as an external: now defined here)
if after:
    L = [l for l in L if not l.startswith('EXTERN %s:' % aname)]
if asm in redirect:
    L = _redirect(L)
for fp in redirect:
    if fp != asm:
        t = open(fp, 'rb').read().decode('utf-8')
        nl_ = '\r\n' if '\r\n' in t else '\n'
        write(fp, '\n'.join(_redirect(t.replace('\r\n', '\n').split('\n'))).replace('\n', nl_).encode('utf-8'))
write(asm,'\n'.join(L).replace('\n', nl).encode('utf-8'))
out = []
for l in lines:
    if l == row:
        if before:
            out.append(l)
        out.append('0x%08X %s %s' % (at, obj, name))
        if after:
            out.append('0x%08X %s %s' % (end, row.split()[1], aname))
        continue
    out.append(l)
write(os.path.join(ROOT, 'config', 'compiled.txt'), '\n'.join(out).encode('utf-8'))
sp = os.path.join(ROOT, 'config', 'splits.txt')
S = open(sp, encoding='utf-8').read().split('\n')
for k, l in enumerate(S):
    q = l.split(None, 3)
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) <= pa < int(q[1], 16):
        a0, e0, sname = int(q[0], 16), int(q[1], 16), q[2]
        rest = q[3] if len(q) > 3 else '-'
        parts = []
        if at > a0:
            parts.append('0x%08X 0x%08X %-10s %s' % (a0, at, sname, rest))
        parts.append('0x%08X 0x%08X %-10s %s' % (at, end, sname, name.lstrip('_')))
        if e0 > end:
            parts.append('0x%08X 0x%08X %-10s %s' % (end, e0, sname, '-'))
        S[k:k + 1] = parts
        break
write(sp, '\n'.join(S).encode('utf-8'))
print('cut', name, 'out of', pname, 'at 0x%X-0x%X' % (at, end))
