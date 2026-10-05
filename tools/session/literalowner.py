"""literalowner.py [--apply]: compiled.txt rows of shared COMDAT literals (??_C@ strings, __real@
constants) named after another object than the one whose copy the link keeps (PLAN M7: a
same-named COMDAT is the first object's, in link order; build/m7/link.rsp's object order, then the
libraries' members in their order there).

Prints ADDR, the row's object and the first object (of ours) defining the literal; --apply gives
the row that object."""
import collections
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv


def defined(path):
    d = open(path, 'rb').read()
    _, n, _, sp, ns, _, _ = struct.unpack_from('<HHIIIHH', d, 0)
    st = sp + ns * 18
    out = set()
    i = 0
    while i < ns:
        o = sp + i * 18
        raw = d[o:o + 8]
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, o + 8)
        if sec > 0 and c == 2:
            if raw[:4] == b'\0\0\0\0':
                so = struct.unpack_from('<I', raw, 4)[0]
                nm = d[st + so:d.index(b'\0', st + so)].decode('latin-1')
            else:
                nm = raw.rstrip(b'\0').decode('latin-1')
            if nm.startswith('??_C@') or nm.startswith('__real@'):
                out.add(nm)
        i += 1 + na
    return out


# link order: the probe's objects, then each of our libraries' members (rsp files of build/m7/lib)
order = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.rsp')):
    l = l.strip().strip('"')
    if l.lower().endswith('.obj'):
        order.append(os.path.relpath(l, ROOT).replace(os.sep, '/'))
    elif l.lower().endswith('.lib'):
        rsp = os.path.splitext(l)[0] + '.rsp'
        if os.path.exists(rsp):
            for m in open(rsp):
                order.append(os.path.relpath(m.strip().strip('"'), ROOT).replace(os.sep, '/'))
# (M7ORDER links numbered copies, build/m7/cdz/obj/NNNN.obj; objects.txt names each)
cdz = {}
cp = os.path.join(ROOT, 'build', 'm7', 'cdz', 'objects.txt')
if os.path.exists(cp):
    for l in open(cp):
        k, v = l.split()
        cdz['build/m7/cdz/obj/' + k] = v
order = [cdz.get(o, o) for o in order]
order = [o if not o.startswith('build/m7/obj/') else o[len('build/m7/obj/'):] for o in order]
first = {}
for o in order:
    p = os.path.join(ROOT, o)
    if not os.path.exists(p) or not o.startswith('build/src/'):
        continue
    for nm in defined(p):
        first.setdefault(nm, o)
path = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(path, encoding='utf-8').read().split('\n')
moves = 0
for i, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and (q[2].startswith('??_C@') or q[2].startswith('__real@')):
        f = first.get(q[2])
        if f and f != q[1] and q[1].startswith('build/src/'):
            print('%s %s -> %s' % (q[0], os.path.basename(q[1]), os.path.basename(f)))
            moves += 1
            if apply:
                lines[i] = ' '.join([q[0], f] + q[2:])
print(moves, 'rows')
if apply:
    open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
