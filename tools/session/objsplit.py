"""objsplit.py [OBJ...]: where a unit's original objects end, from its deferred functions (PLAN M7).

VC7.1 emits the inline and template functions it did not inline (and the ones only an initializer
names) after every out-of-line definition, at the end of the object. A unit whose deferred
functions sit between its out-of-line ones in the image was several original objects: each
ends after a run of deferred functions that an out-of-line one follows. Deferred here means in
the compiled object's tail, after its last out-of-line definition (a definition with a body after
its `// match:` line in the unit's source).

    objsplit.py           every unit that the image splits, with its object count
    objsplit.py OBJ...    the unit's functions in image order, the boundaries marked"""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import objorder  # noqa: E402

ROOT = objorder.ROOT


def defined_names(obj):
    """Names the unit's source defines out of line."""
    base = os.path.join(ROOT, obj[len('build/'):-len('.obj')])
    for ext in ('.cpp', '.c'):
        if os.path.exists(base + ext):
            text = open(base + ext, encoding='utf-8', errors='replace').read()
            break
    else:
        return set()
    out = set()
    lines = text.split('\n')
    for k, l in enumerate(lines):
        m = re.match(r'//\s*match:\s*(\S+)\s*@', l)
        if not m:
            continue
        j = k + 1
        while j < len(lines) and lines[j].startswith('//'):
            j += 1
        if j < len(lines) and lines[j].strip() and not lines[j].startswith('#'):
            out.add(m.group(1))
    return out


def selections(path):
    """Section number -> COMDAT selection (1 no duplicates: an ordinary function; 2 any: inline,
    template or compiler-generated)."""
    d = open(path, 'rb').read()
    _m, _ns, _t, symptr, nsyms, _o, _c = struct.unpack_from('<HHIIIHH', d, 0)
    out = {}
    i = 0
    while i < nsyms:
        _name, _v, sec, _ty, sclass, naux = struct.unpack_from('<8sIhHBB', d, symptr + i * 18)
        if sclass == 3 and naux == 1 and sec > 0 and sec not in out:
            aux = d[symptr + (i + 1) * 18: symptr + (i + 2) * 18]
            out[sec] = aux[14]
        i += 1 + naux
    return out


def analyse(obj):
    seq = objorder.order(obj)
    if not seq:
        return None
    from coff import Coff
    c = Coff(os.path.join(ROOT, obj))
    sel = selections(os.path.join(ROOT, obj))
    secof = dict((s['name'], s['section']) for s in c.symbol_list if s['section'] > 0 and s['class'] in (2, 3))
    plain = [i for i, (_a, n) in enumerate(seq) if sel.get(secof.get(n)) == 1]
    last = max(plain, default=-1)
    deferred = set(n for i, (_a, n) in enumerate(seq) if i > last and sel.get(secof.get(n)) != 1)
    image = sorted(seq)
    marks = []
    for i in range(len(image) - 1):
        if image[i][1] in deferred and image[i + 1][1] not in deferred:
            marks.append(i)
    return image, deferred, marks


if len(sys.argv) > 1:
    for obj in sys.argv[1:]:
        image, deferred, marks = analyse(obj)
        print('%s: %d objects' % (obj, len(marks) + 1))
        for i, (a, n) in enumerate(image):
            print('  %s 0x%06X %s' % ('d' if n in deferred else ' ', a, n[:100]))
            if i in marks:
                print('  ---- object ends')
else:
    total = 0
    rows = []
    for obj in objorder.rows:
        if not obj.startswith('build/src/') or not os.path.exists(os.path.join(ROOT, obj)):
            continue
        r = analyse(obj)
        if r and r[2]:
            rows.append((len(r[2]) + 1, obj))
            total += len(r[2])
    rows.sort(reverse=True)
    for k, obj in rows:
        print('%3d objects  %s' % (k, obj))
    print('%d units to split, %d new objects' % (len(rows), total))
