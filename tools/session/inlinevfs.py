"""inlinevfs.py SRC HEADER CLASS NAME...: make CLASS's members NAME... inline in its class, in the given
order (--anchor NAME: put them where NAME, a new virtual, is declared, so its slot holds;
PLAN M7 layout: an out-of-line constructor's vtable emits the class's inline virtual
functions after it and before ??_G, in their declaration order, where the image has them).

Each `RET CLASS::NAME(ARGS)\\n{ ... }` definition in SRC moves (its match line stays) into
HEADER's `struct CLASS`, replacing NAME's declaration; the moved bodies go, in the given order,
where the first of those declarations was. Only overrides may be reordered this way (a new
virtual's declaration order sets its vtable slot): check the build."""
import re
import sys


def rd(p):
    raw = open(p, 'rb').read().decode('utf-8')
    return raw.replace('\r\n', '\n'), ('\r\n' if '\r\n' in raw else '\n')


def wr(p, t, nl):
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))


args = sys.argv[1:]
anchor = None
if '--anchor' in args:
    i = args.index('--anchor')
    anchor = args[i + 1]
    del args[i:i + 2]
src, header, cls = args[:3]
names = args[3:]
s, snl = rd(src)
h, hnl = rd(header)
bodies = {}
for n in names:
    m = re.search(r'^([^\n]*?)\b%s::%s\(([^\n]*)\)(\s*const)?\n\{\n(.*?)\n\}\n' % (re.escape(cls), re.escape(n)), s, re.M | re.S)
    if not m:
        raise SystemExit('no definition of %s::%s' % (cls, n))
    ret, args, const, body = m.group(1).strip(), m.group(2), m.group(3) or '', m.group(4)
    bodies[n] = (ret, args, const, body)
    s = s[:m.start()] + s[m.end():]
a = re.search(r'^(?:struct|class) %s\b[^;{]*\n\{\n' % re.escape(cls), h, re.M)
if not a:
    raise SystemExit('no struct %s in %s' % (cls, header))
end = h.index('\n};\n', a.end())
body_h = h[a.end():end]
first = None
for n in names:
    m = re.search(r'^( *)virtual [^\n;]*\b%s\([^\n;]*\)[^\n;]*;\n' % re.escape(n), body_h, re.M)
    if not m:
        raise SystemExit('no declaration of %s in %s' % (n, cls))
    pos = m.start()
    body_h = body_h[:m.start()] + body_h[m.end():]
    if anchor is not None:
        if n == anchor:
            first = pos
        elif first is not None and pos < first:
            first -= m.end() - m.start()
    elif first is None or pos < first:
        first = pos
text = '    // Inline: the constructor\'s vtable emits them after it, before ??_G (the image\'s order).\n'
for n in names:
    ret, args, const, body = bodies[n]
    ret = ret if ret.startswith('virtual') else 'virtual ' + ret
    text += '    %s %s(%s)%s\n    {\n' % (ret, n, args, const)
    text += '\n'.join(('    ' + l if l else l) for l in body.split('\n')) + '\n    }\n'
body_h = body_h[:first] + text + body_h[first:]
h = h[:a.end()] + body_h + h[end:]
wr(src, s, snl)
wr(header, h, hnl)
print('ok')
