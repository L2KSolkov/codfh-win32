"""fwddecl.py SRC...: declare the functions a unit's data definitions name before they are declared
(PLAN M5).

Function pointer tables sit in the m5defs block after the includes, above the functions they
name. For each `sub_X` in the block with no declaration before it, the declaration is copied from
the function's definition (in this unit or any other source) and put just above the block."""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ALL = None


def definition(name, own):
    global ALL
    pat = re.compile(r'^((?:static )?[A-Za-z_][\w \*:]*?\b%s\([^;{)]*\))\s*\n\{' % name, re.M)
    m = pat.search(own)
    if m:
        return m.group(1)
    if ALL is None:
        ALL = [open(f, encoding='utf-8', errors='replace').read()
               for f in glob.glob(os.path.join(ROOT, 'src', '**', '*.c*'), recursive=True)]
    for t in ALL:
        m = pat.search(t)
        if m:
            return m.group(1)
    return None


for src in sys.argv[1:]:
    text = open(src, encoding='utf-8').read()
    i = text.index(m5defs.BEGIN)
    j = text.index(m5defs.END, i)
    before, block = text[:i], text[i:j]
    incs = ''
    for inc in re.findall(r'^#include "(.*)"', before, re.M):
        p = os.path.join(ROOT, 'include', inc)
        if os.path.exists(p):
            incs += open(p, encoding='utf-8', errors='replace').read()
    need = []
    for n in sorted(set(re.findall(r'\b(sub_[0-9A-F]+)\b', block)), key=lambda n: int(n[4:], 16)):
        if re.search(r'\b%s\s*\(' % n, before + incs):
            continue
        d = definition(n, text)
        if d is None:
            print('%s: no definition of %s' % (src, n))
            continue
        need.append(d.replace('static ', '') + ';')
    if need:
        pre = '// The functions its tables name (defined below or in other units).\n' + '\n'.join(need) + '\n\n'
        text = before + pre + text[i:]
        open(src, 'w', encoding='utf-8', newline='\n').write(text)
        print('%s: %d declarations' % (src, len(need)))
