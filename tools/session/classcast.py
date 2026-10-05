"""classcast.py [--apply] [UNIT...]: calls of a member through the wrong class view (PLAN M7).

Some readers call a member through a class view of their own (type_67620, the script VM's
flattened view of the Alfa objects) while the function is placed as a member of the real class
(type_3D2CD0::sub_6D380): the reader's call names a symbol nothing defines. tools/session/sigdiff.py
lists them; for each (member, reader class, defining class) and each reader unit, the calls
`EXPR->m(` / `EXPR.m(` / `m(` (inside the reader class's own members) become
`((D *)EXPR)->m(` (`((D *)&EXPR)->m(`, `((D *)this)->m(`): a pointer cast, no code. The unit
then compiles alone; arguments the compiler cannot convert to the real parameter types
(C2664) get the parameter's type as a cast, and the defining class's header is included when
the unit lacks it. Units that still fail are restored. The full build decides whether the
callers still match."""
import collections
import ctypes
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import flags_for, load_flags  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
only = set(a for a in sys.argv[1:] if not a.startswith('--'))
d = ctypes.windll.dbghelp
d.UnDecorateSymbolName.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]


def und(n):
    b = ctypes.create_string_buffer(4096)
    d.UnDecorateSymbolName(n.encode(), b, 4096, 0)
    return b.value.decode(errors='replace')


rows = collections.defaultdict(list)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[int(q[0], 16)].append(q[2])
readers = collections.defaultdict(set)
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.log'), errors='replace'):
    m = re.match(r'^(\S+)\.obj : error LNK20\d\d: unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))', l)
    if m:
        readers[m.group(2) or m.group(3)].add(m.group(1))
QUAL = re.compile(r'(?:([\w:]+)::)?(\w+)\(')
fixes = collections.defaultdict(list)       # unit -> [(member, reader class, defining class)]
rets = {}                                   # (unit, member) -> the reader's return type
for n in (l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt'))):
    m = re.match(r'^\?((?:sub|nullsub)_([0-9A-F]+))@(\w+)@@', n)
    if not m:
        continue
    a = int(m.group(2), 16)
    mu = QUAL.search(und(n))
    for r in rows.get(a, []):
        md = QUAL.search(und(r))
        if mu and md and md.group(1) and mu.group(1) != md.group(1) and mu.group(2) == md.group(2):
            for u in readers[n]:
                if not only or u in only:
                    rm = re.match(r'^(?:(?:public|protected|private): )?(?:virtual |static )?(.*?)\s*__thiscall', und(n))
                    rets[(u, mu.group(2))] = rm.group(1) if rm else ''
                    fixes[u].append((mu.group(2), mu.group(1), md.group(1)))
            break
print(sum(len(v) for v in fixes.values()), 'member uses in', len(fixes), 'units')
for u, f in sorted(fixes.items()):
    print(' ', u, ', '.join('%s %s->%s' % x for x in f)[:150])
if not apply:
    sys.exit(0)

headers = {}
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'include')):
    for f in fs:
        if f.endswith('.h'):
            t = open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()
            for m in re.finditer(r'^(?:struct|class)\s+(\w+)\b[^;{]*\{', t, re.M):
                headers.setdefault(m.group(1), os.path.relpath(os.path.join(dp, f), os.path.join(ROOT, 'include')).replace(os.sep, '/'))


def primary_start(line, end):
    """Start index of the postfix expression ending at END (exclusive) in LINE."""
    i = end
    while i > 0:
        c = line[i - 1]
        if c in ')]':
            close = {')': '(', ']': '['}[c]
            depth, j = 0, i - 1
            while j >= 0:
                if line[j] == c:
                    depth += 1
                elif line[j] == close:
                    depth -= 1
                    if depth == 0:
                        break
                j -= 1
            i = j
            continue
        if c.isalnum() or c == '_':
            i -= 1
            continue
        if line[max(0, i - 2):i] == '->':
            i -= 2
            continue
        if c == '.' or line[max(0, i - 2):i] == '::':
            i -= 1 if c == '.' else 2
            continue
        break
    return i


def rewrite(text, member, rcls, dcls):
    out = []
    for line in text.split('\n'):
        code, sep, com = line.partition('//')
        if re.match(r'^(?!\s*return\b)\s*(?:virtual\s+)?[\w:\*&<> ]+\b%s\s*\([^;{]*\)\s*(?:const)?\s*;' % member, code):
            out.append(line)        # a declaration
            continue
        k = 0
        while True:
            m = re.compile(r'(->|\.)?\b%s\s*\(' % member).search(code, k)
            if not m:
                break
            if m.group(1):
                s = primary_start(code, m.start())
                expr = code[s:m.start()]
                if not expr or expr.startswith('((%s *)' % dcls):
                    k = m.end()
                    continue
                new = '((%s *)%s%s)->%s(' % (dcls, '&' if m.group(1) == '.' else '', expr, member)
                code = code[:s] + new + code[m.end():]
                k = s + len(new)
            else:
                before = code[:m.start()].rstrip()
                if before.endswith('::') or re.search(r'\b(?:void|RwInt32|RwUInt32|bool|RwReal|\w+\s*\*)\s*$', before):
                    k = m.end()
                    continue
                # through the reader's class first: an implicit this converts to it (a base may adjust)
                new = '((%s *)(%s *)this)->%s(' % (dcls, rcls, member)
                code = code[:m.start()] + new + code[m.end():]
                k = m.start() + len(new)
        out.append(code + sep + com)
    return '\n'.join(out)


rules = load_flags()
tmp = os.path.join(ROOT, 'build', 'tooltmp', 'classcast.obj')
os.makedirs(os.path.dirname(tmp), exist_ok=True)
for u, items in sorted(fixes.items()):
    src = next((p for p in (os.path.join(ROOT, 'src', 'recovered', u + '.cpp'),) if os.path.exists(p)), None)
    if not src:
        print('  no source for', u)
        continue
    raw = open(src, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    text = raw.replace('\r\n', '\n')
    for member, rcls, dcls in items:
        text = rewrite(text, member, rcls, dcls)
        h = headers.get(dcls.split('::')[-1])
        if h and '#include "%s"' % h not in text:
            incs = list(re.finditer(r'^#include [^\n]*\n', text, re.M))
            text = text[:incs[-1].end()] + '#include "%s"\n' % h + text[incs[-1].end():]
    rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
    flags = flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')]
    ok = False
    for attempt in range(8):
        open(src, 'wb').write(text.replace('\n', nl).encode('utf-8'))
        out = []
        if compile_with_deps(src, tmp, flags, out) is not None:
            ok = True
            break
        lines = text.split('\n')
        changed = False
        for e in '\n'.join(out).splitlines():
            # the result used as the reader's view returned it: a cast to that type
            m = re.match(r'^(.*)\((\d+)\) : error (C2109|C2440|C2446|C2227|C2100|C2678|C2679)', e)
            if m and os.path.normcase(os.path.abspath(m.group(1))) == os.path.normcase(src):
                ln = int(m.group(2)) - 1
                line = lines[ln]
                for mem, _r, dcls in items:
                    rt = rets.get((u, mem), '')
                    rt = re.sub(r'\b(struct|class|enum) ', '', rt)
                    rt = re.sub(r'\bunsigned int\b', 'RwUInt32', re.sub(r'\bint\b', 'RwInt32', rt))
                    cm = re.search(r'\(\(%s \*\)' % re.escape(dcls), line)
                    cc = re.search(r'\)->%s\(' % mem, line)
                    if not cm or not cc or not rt or rt == 'void' or line[:cm.start()].endswith('((%s)' % rt):
                        continue
                    i, depth = cc.end() - 1, 0
                    while i < len(line):
                        depth += {'(': 1, ')': -1}.get(line[i], 0)
                        if depth == 0:
                            break
                        i += 1
                    lines[ln] = line[:cm.start()] + '((%s)' % rt + line[cm.start():i + 1] + ')' + line[i + 1:]
                    changed = True
                    break
                continue
            m = re.match(r'^(.*)\((\d+)\) : error C2664:.*cannot convert parameter (\d+) from \'[^\']*\' to \'([^\']*)\'', e)
            if not m or os.path.normcase(os.path.abspath(m.group(1))) != os.path.normcase(src):
                continue
            ln, pn, typ = int(m.group(2)) - 1, int(m.group(3)), m.group(4)
            typ = re.sub(r'\b(struct|class|enum) ', '', typ)
            line = lines[ln]
            # the member call on this line and its PN-th argument
            for mem, _r, dcls in items:
                cm = re.search(r'\)->%s\(' % mem, line)
                if not cm:
                    continue
                i, depth, args, start = cm.end(), 0, [], cm.end()
                while i < len(line):
                    c = line[i]
                    if c in '([':
                        depth += 1
                    elif c in ')]':
                        if depth == 0:
                            args.append((start, i))
                            break
                        depth -= 1
                    elif c == ',' and depth == 0:
                        args.append((start, i))
                        start = i + 1
                    i += 1
                if pn <= len(args):
                    s, e2 = args[pn - 1]
                    arg = line[s:e2].strip()
                    lead = line[s:e2][:len(line[s:e2]) - len(line[s:e2].lstrip())]
                    line = line[:s] + lead + '(%s)%s' % (typ, arg if re.match(r'^[\w\.\->\[\]]+$', arg) else '(%s)' % arg) + line[e2:]
                    lines[ln] = line
                    changed = True
                break
        if not changed:
            break
        text = '\n'.join(lines)
    if not ok:
        open(src, 'wb').write(raw.encode('utf-8'))
        print('  restored', u)
        for e in '\n'.join(out).splitlines():
            if 'error' in e:
                print('     ', e.strip()[:200])
                break
    else:
        print('  done', u)
