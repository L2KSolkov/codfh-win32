"""unconst.py NAME...: make globals the image keeps in .data non-const (PLAN M5).

A const global with a constant initializer compiles into .rdata; one the image holds in .data was
not const. For each NAME, every declaration in include/ and src/ loses its top-level const: a
leading `const` of a non-pointer type (`const RwInt32 x[11]` -> `RwInt32 x[11]`), or the `*const`
of a pointer (`const RwChar *const x[11]` -> `const RwChar *x[11]`)."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
files = glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True) + \
    glob.glob(os.path.join(ROOT, 'src', '**', '*.c*'), recursive=True)
for name in sys.argv[1:]:
    pat = re.compile(r'^((?:extern )?)(const )?([\w:]+(?: ?\*+ ?(?:const )?)?)\s*\b(%s)\b' % re.escape(name), re.M)
    for f in files:
        t = open(f, encoding='utf-8', errors='replace').read()
        if name not in t:
            continue

        def fix(m):
            typ = m.group(3)
            if '*' in typ:
                # a pointer: its own const goes, the pointee's stays
                return m.group(1) + (m.group(2) or '') + re.sub(r'\*\s*const\s*', '*', typ).rstrip() + \
                    ('' if typ.rstrip().endswith('*') or 'const' in typ else ' ') + m.group(4)
            return m.group(1) + typ + ' ' + m.group(4)
        n = pat.sub(fix, t)
        n = re.sub(r'\*\s+(%s)\b' % re.escape(name), r'*\1', n)
        if n != t:
            open(f, 'w', encoding='utf-8', newline='\n').write(n)
            print(os.path.relpath(f, ROOT), name)
