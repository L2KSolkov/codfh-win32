"""dataptrs.py ASM...: in transcribed data (src/xdk/standin_data_*.asm, src/bink/binkdata.asm), every
aligned dword the image holds that is exactly a row's address becomes `dd NAME` (PLAN M7: the
transcription kept such pointers as plain bytes, which the placement link leaves right but the
authentic link cannot relocate: a vtable of DirectSound's, a table of names).

Bytes stay the same (each dword was the row's address), so the placement link is unchanged. A row
the file defines itself is left as bytes (MASM would resolve it within the file), and so is a name
longer than MASM takes. An EXTERN is added for each new name."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from match import resolve_name  # noqa: E402
from coff import Coff  # noqa: E402
rows = {}
addrs = {}
row_obj = {}
_objs = {}


def external(nm):
    """Whether nm's row object defines it as an external (a static resolves only in its object)."""
    o = row_obj.get(nm)
    if o not in _objs:
        try:
            _objs[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            _objs[o] = None
    c = _objs[o]
    if c is None:
        return False
    s = next((x for x in c.symbol_list if x['name'] == nm and x['section'] > 0), None)
    return s is not None and s['class'] == 2
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and '>' not in q[2] and not q[2].startswith('$') and not re.search(r'[-+]0x[0-9A-Fa-f]+$', q[2]):
        rows.setdefault(int(q[0], 16), q[2])
        addrs.setdefault(q[2], set()).add(int(q[0], 16))
        row_obj.setdefault(q[2], q[1])


def resolves_to(nm, val):
    """Whether the placement link (tools/xbelink.py) reads nm as val."""
    r = resolve_name(nm, {})
    if r is not None:
        return r == val
    return addrs.get(nm) == {val}


def parse_db(s):
    out = []
    for x in s.split(','):
        x = x.strip()
        out.append(int(x[:-1], 16) if x.lower().endswith('h') else int(x))
    return out


for p in sys.argv[1:]:
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    defined = set(re.findall(r'^PUBLIC (\S+)$', '\n'.join(L), re.M))
    externs = set(x.split(':')[0] for x in re.findall(r'^EXTERN (\S+)$', '\n'.join(L), re.M))
    out, new_ext, n = [], set(), 0
    i = 0
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if not m:
            out.append(L[i])
            i += 1
            continue
        base = int(m.group(2), 16)
        out.append(L[i])
        i += 1
        # header lines (PUBLIC, label) then the body until the next match line or ENDS
        while i < len(L) and not re.match(r'^\s*(db|dd|dw) ', L[i]) and not L[i].startswith('; // match:') \
                and not re.match(r'^\w+ ENDS$', L[i]):
            out.append(L[i])
            i += 1
        items = []          # ('b', value) or ('l', line) for a kept line
        ok = True
        while i < len(L) and not L[i].startswith('; // match:') and not re.match(r'^\w+ ENDS$', L[i]):
            s = L[i].split(';')[0].strip()
            if s.startswith('db '):
                try:
                    items += [('b', v) for v in parse_db(s[3:])]
                except ValueError:
                    ok = False
                    items.append(('l', L[i]))
            elif s:
                items.append(('l', L[i]))
                if s.startswith('dd '):
                    items += [('pad', 4 - 1)] * 0
            else:
                items.append(('l', L[i]))
            i += 1
        # offsets: kept dd lines count 4 bytes each (one operand), dw 2
        off, k, res = 0, 0, []
        while k < len(items):
            kind, v = items[k]
            if kind == 'l':
                s = v.split(';')[0].strip()
                if s.startswith('dd '):
                    off += 4 * len(s[3:].split(','))
                elif s.startswith('dw '):
                    off += 2 * len(s[3:].split(','))
                res.append(items[k])
                k += 1
                continue
            if (base + off) % 4 == 0 and k + 4 <= len(items) and all(items[k + j][0] == 'b' for j in range(4)):
                val = sum(items[k + j][1] << (8 * j) for j in range(4))
                nm = rows.get(val)
                if nm and nm not in defined and len(nm) < 240 and resolves_to(nm, val) and external(nm):
                    res.append(('d', nm))
                    if nm not in externs:
                        new_ext.add(nm)
                    n += 1
                    k += 4
                    off += 4
                    continue
            res.append(items[k])
            k += 1
            off += 1
        # emit
        run = []

        def flush():
            for j in range(0, len(run), 16):
                out.append('        db ' + ', '.join('0%02Xh' % b for b in run[j:j + 16]))
            run.clear()
        for kind, v in res:
            if kind == 'b':
                run.append(v)
            else:
                flush()
                out.append('        dd ' + v if kind == 'd' else v)
        flush()
    if n:
        k = max(j for j, x in enumerate(out) if x.strip().startswith(('EXTERN ', '.model')))
        for nm in sorted(new_ext, reverse=True):
            out.insert(k + 1, 'EXTERN %s:BYTE' % nm)
        open(p, 'wb').write('\n'.join(out).replace('\n', nl).encode('utf-8'))
    print('%s: %d pointers, %d new EXTERNs' % (os.path.relpath(p, ROOT), n, len(new_ext)))
