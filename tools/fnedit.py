"""fnedit.py FILE ADDR 'old=>new' ...: exact replacements inside one function's
block (from its match line to the next non-EH match line). A literal \\n in an
argument is a newline; an 're:a=>b' argument renames the word a to b."""
import sys, re
p, addr = sys.argv[1], int(sys.argv[2], 16)
t = open(p, encoding='utf-8').read()
m = re.search(r'^// match: \S+ @ 0x0*%X\n' % addr, t, re.M)
e = re.compile(r'\n// match: (?!__ehhandler)').search(t, m.end())
e = e.start() + 1 if e else len(t)
b = t[m.start():e]
for arg in sys.argv[3:]:
    o, n = arg.split('=>', 1)
    o = o.replace('\\n', '\n')
    n = n.replace('\\n', '\n')
    if o.startswith('re:'):
        b = re.sub(r'\b%s\b' % o[3:], n, b)
    else:
        assert o in b, ('missing', o)
        b = b.replace(o, n)
open(p, 'w', encoding='utf-8', newline='\n').write(t[:m.start()] + b + t[e:])
