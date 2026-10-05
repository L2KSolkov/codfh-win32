"""cfwd.py SRC...: put a C unit's data definitions where their names are declared (PLAN M5/M6).

The m5defs block first moves below the unit's file-scope declarations (just before its first
function's `// match:` line), since C units define local types and constants above their code.
Then every function the block names gets a declaration above it: the unit's own declaration of
it (moved up when it comes later), else a prototype copied from its definition (in SRC or any
other src/rwa, src/rw C source); placeholder declarations `extern void NAME(void);` go. Data the
block names that the unit declares only further down gets that extern above it too."""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ALL = {f: open(f, encoding='utf-8', errors='replace').read()
       for f in glob.glob(os.path.join(ROOT, 'src', 'rwa', '**', '*.c'), recursive=True) +
       glob.glob(os.path.join(ROOT, 'src', 'rw', '**', '*.c'), recursive=True)}


def prototype(name, own):
    pat = re.compile(r'^((?:static\s+)?(?:const\s+)?[A-Za-z_][\w \t]*[\w\*][ \t]*\**)\s*\n?\s*\b%s\s*(\([^;{]*?\))\s*\n\{'
                     % re.escape(name), re.M)
    for t in [own] + list(ALL.values()):
        m = pat.search(t)
        if m:
            ret = ' '.join(m.group(1).replace('static', '').split())
            params = ' '.join(m.group(2).split())
            return ('%s%s%s;' if ret.endswith('*') else '%s %s%s;') % (ret, name, params)
    return None


for src in sys.argv[1:]:
    text = open(src, encoding='utf-8').read()
    if m5defs.BEGIN not in text:
        continue
    pre = '// What its data definitions name.\n'
    if pre in text:
        # an earlier run's declarations: dropped and re-derived (typedefs stay in place)
        a0 = text.index(pre)
        b0 = text.index(m5defs.BEGIN, a0)
        kept = [l for l in text[a0 + len(pre):b0].split('\n') if l.startswith('typedef')]
        text = text[:a0] + ''.join(l + '\n' for l in kept) + text[b0:]
    i = text.index(m5defs.BEGIN)
    j = text.index(m5defs.END, i) + len(m5defs.END)
    block = text[i:j]
    # declarations inside the block are re-derived (earlier runs' and the generators' own)
    block = re.sub(r'^(?!typedef\b)(?:extern\s+[^=\n]*;|[A-Za-z_][\w \t\*]*\b\w+\s*\([^;=\n]*\)\s*;)\n', '', block, flags=re.M)
    text = text[:i] + text[j:]
    # below the file-scope declarations: before the first function's match line
    f = re.search(r'^// match: \S+ @ 0x0*([0-9A-F]+)\n(?!// match)', text, re.M)
    pos = f.start() if f else len(text)
    while pos > 0 and text[pos - 1] == '\n' and text[pos - 2:pos] == '\n\n':
        pos -= 1
    before, after = text[:pos], text[pos:]
    defined = set(re.findall(r'^[^/\n][^=\n]*?\b(\w+)\s*(?:\[[^\]]*\])*\s*=', block, re.M))
    added = []
    # identifiers in initializer value positions: functions unless taken by address or data-named
    values = re.findall(r'[{,=]\s*(?:\(\s*void\s*\*\s*\)\s*)?(&?)\s*([A-Za-z_]\w*)\s*(?=[,}])', block)
    funcs = {n for amp, n in values if not amp and not re.match(r'(unk|dword|off|flt|stru|word|byte)_[0-9A-F]+$', n)}
    for name in sorted(funcs):
        placeholder = 'extern void %s(void);\n' % name
        block = block.replace(placeholder, '')
        before = before.replace(placeholder, '')
        if name in defined or re.search(r'^[^/\n]*\b%s\s*\([^;]*\)\s*;' % re.escape(name), before, re.M):
            continue
        own = re.search(r'^[^/\n]*\b%s\s*\([^;{]*\)\s*;' % re.escape(name), after, re.M)
        # a function this unit defines needs its own prototype (a different declaration would
        # clash); one from elsewhere is only an address here
        defines = re.search(r'^\S[^\n;]*\b%s\s*\([^;]*\)\s*\n\{' % re.escape(name), after, re.M) or \
            re.search(r'^%s\s*\(' % re.escape(name), after, re.M)
        p = own.group(0) if own else prototype(name, before + after) if defines else None
        added.append(p or 'extern void %s(void);' % name)
    for name in sorted(set(re.findall(r'\b((?:unk|dword|off|flt|stru|word|byte)_[0-9A-F]+)\b', block)) - defined):
        if re.search(r'^[^/\n]*\b%s\b[^;\n]*;' % name, before, re.M):
            continue
        d = re.search(r'^extern\s+[^;\n]*\b%s\b[^;\n]*;' % name, after, re.M)
        decl = d.group(0) if d else 'extern RwUInt8 %s[];' % name
        if decl not in added:
            added.append(decl)
    # types the definitions use that the unit declares only further down: their typedefs move up
    for t in sorted(set(re.findall(r'^([A-Za-z_]\w*)\s+\**\s*\w+\s*(?:\[[^\]]*\])*\s*=', block, re.M))):
        if re.search(r'\btypedef\b[^;]*\b%s\s*;|\bstruct\s+%s\s*\{' % (t, t), before):
            continue
        d = re.search(r'^typedef\b[^;{]*\b%s\b[^;{]*;\n|^typedef\s+[^;{]*\(\s*\*\s*%s\s*\)\s*\([^;]*\);\n' % (t, t), after, re.M)
        if d:
            after = after[:d.start()] + after[d.end():]
            added.insert(0, d.group(0).rstrip('\n'))
    if added:
        # above the block (m5defs keeps only its `// 0x` items)
        block = '// What its data definitions name.\n' + '\n'.join(added) + '\n' + block
    new = before.rstrip('\n') + '\n\n' + block + '\n' + after.lstrip('\n')
    open(src, 'w', encoding='utf-8', newline='\n').write(new)
    print('%s: %d declarations' % (os.path.relpath(src, ROOT), len(added)))
