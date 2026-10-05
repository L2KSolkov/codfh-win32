"""rwannot.py FILE SYMBOL=ADDR...: insert `// match: SYMBOL @ 0xADDR` above
each function definition in a RenderWare C source (the definition's name
starts a line; its return type is on the line above)."""
import re
import sys

path = sys.argv[1]
text = open(path, encoding='latin-1', newline='').read()
nl = '\r\n' if '\r\n' in text else '\n'
lines = text.split(nl)
for arg in sys.argv[2:]:
    sym, addr = arg.split('=')
    name = sym[1:]  # the C name: the COFF symbol less its leading underscore
    found = None
    for i, l in enumerate(lines):
        if re.match(r'%s\s*\(' % re.escape(name), l):
            # a definition: '{' comes before any ';' after the name
            rest = nl.join(lines[i:i + 40])
            b, s = rest.find('{'), rest.find(';')
            if b >= 0 and (s < 0 or b < s):
                found = i
    assert found is not None, name
    k = found - 1  # the return type's line
    ann = '// match: %s @ 0x%08X' % (sym, int(addr, 16))
    assert ann not in lines
    lines.insert(k, ann)
open(path, 'w', encoding='latin-1', newline='').write(nl.join(lines))
print('annotated', len(sys.argv) - 2)
