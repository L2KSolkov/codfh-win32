"""aliasbodies.py [--apply]: bodies for the folded trivial functions the real link needs (PLAN M7).

/OPT:ICF folded many trivial members into one body (config/aliases.txt maps their names to it), so
the placement link never needed their definitions; the real link does. For an alias the m7 probe
lists as unresolved (build/m7/unresolved.txt) whose target is one of the shared trivial bodies,
the member's declaration is found in the headers and an out-of-line definition with that body
is appended to the unit holding most of the class's placed members (out of line: an inline body
could be expanded into matched callers). Prints the plan and what it could not do."""
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
TRIVIAL = {0x1E41C0: '', 0x15FB30: '', 0x19A750: '', 0x1E4CB0: 'return 0;', 0x32260: 'return 0;', 0x1E4AA0: 'return 0;',
           0x6FCD0: 'return this;', 0x1F5A00: 'return 1;', 0x9E000: 'return 4;'}
NAMES = {0x1E41C0: 'the empty body', 0x15FB30: 'the empty body', 0x19A750: 'the empty debug print', 0x1E4CB0: '`return 0`', 0x32260: '`return 0`',
         0x1E4AA0: '`return false`', 0x6FCD0: '`return this`', 0x1F5A00: '`return 1`', 0x9E000: '`return 4`'}
unres = set(l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')) if l.strip())
aliases = {}
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and not l.startswith('#') and q[1].startswith('0x'):
        aliases[q[0]] = int(q[1], 16)
members = collections.defaultdict(collections.Counter)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/'):
        m = re.match(r'^\?\?[0-9_A-Z]?\$?(\w+)@@|^\?\w+@(\w+)@@|^\?\?_[7GE](\w+)@@', q[2])
        if m:
            members[m.group(1) or m.group(2) or m.group(3)][q[1]] += 1
members_objs = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[1].startswith('build/src/'):
        members_objs.add(q[1])
headers = {}
for top in ('include', 'src'):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if f.endswith(('.h', '.hpp')):
                headers[os.path.join(dp, f)] = open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()


def demangle(n):
    """(class, member) for ?member@Class@@... and ??1Class@@ (destructors); None for others."""
    m = re.match(r'^\?\?1(\w+)@@', n)
    if m:
        return m.group(1), '~' + m.group(1)
    m = re.match(r'^\?\?3(\w+)@@S', n)
    if m:
        return m.group(1), 'operator delete'
    m = re.match(r'^\?(\w+)@(\w+)@@[QUAE]', n)
    if m:
        return m.group(2), m.group(1)
    return None


def class_body(cls):
    for p, t in headers.items():
        m = re.search(r'^(?:struct|class)\s+%s\b[^;{]*\{' % re.escape(cls), t, re.M)
        if m:
            depth, k = 0, m.end() - 1
            while k < len(t):
                if t[k] == '{':
                    depth += 1
                elif t[k] == '}':
                    depth -= 1
                    if depth == 0:
                        return p, t[m.end():k]
                k += 1
    return None, None


srcs = {}
for top in ('include', 'src'):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if f.endswith(('.h', '.hpp', '.c', '.cpp')):
                srcs[os.path.join(dp, f)] = open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()
# the first object (in the probe's link log) that reads each unresolved name
readers = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.log'), errors='replace'):
    m = re.match(r'^(\S+\.obj) : error LNK20\d\d: unresolved external symbol .*\((\S+)\)', l)
    if m and m.group(2) not in readers:
        hit = [o for o in members_objs if o.endswith('/' + m.group(1))]
        if hit:
            readers[m.group(2)] = hit[0]
plan, skipped = [], []
for n in sorted(unres):
    if n not in aliases or aliases[n] not in TRIVIAL:
        continue
    dm = demangle(n)
    fm = re.match(r'^\?(\w+)@@Y', n)
    if not dm and fm:
        # a free function: its declaration anywhere in the sources, defined in its first reader
        fn = fm.group(1)
        forms = set()
        for p, t in srcs.items():
            for d0 in re.findall(r'^\s*(?:extern\s+)?([A-Za-z_][^;{}()\n]*?\b%s\s*\([^;{}()\n]*\))\s*;' % re.escape(fn), t, re.M):
                forms.add(' '.join(d0.split()))
        owner = readers.get(n)
        if len(forms) != 1 or not owner:
            skipped.append((n, '%d free declarations' % len(forms)))
            continue
        decl = re.sub(r'\s*=\s*[^,)]+', '', list(forms)[0])
        plan.append((owner, n, decl, aliases[n]))
        continue
    if not dm:
        skipped.append((n, 'not a plain member'))
        continue
    cls, mem = dm
    hp, body = class_body(cls)
    if body is None:
        skipped.append((n, 'class not found'))
        continue
    decls = re.findall(r'^\s*(?!//)((?:virtual\s+)?[^;{}()\n]*?\b%s\s*\([^;{}()\n]*\)\s*(?:const)?)\s*;' % re.escape(mem), body, re.M)
    if len(decls) != 1:
        skipped.append((n, '%d declarations' % len(decls)))
        continue
    decl = ' '.join(decls[0].split())
    decl = re.sub(r'^(virtual|static)\s+', '', decl)
    decl = re.sub(r'\s*=\s*[^,)]+', '', decl)          # default arguments
    decl = re.sub(r'\b%s\s*\(' % re.escape(mem), '%s::%s(' % (cls, mem), decl, count=1)
    owner = members[cls].most_common(1)[0][0] if members[cls] else None
    if not owner:
        skipped.append((n, 'no unit'))
        continue
    plan.append((owner, n, decl, aliases[n]))
by = collections.defaultdict(list)
for o, n, d, a in plan:
    by[o].append((n, d, a))
print(len(plan), 'definitions in', len(by), 'units;', len(skipped), 'skipped')
for s in skipped[:int(os.environ.get("NSKIP", "25"))]:
    print('  skip', s)
if not apply:
    for o, n, d, a in plan[:15]:
        print(o.split('/')[-1], '|', d, '|', TRIVIAL[a])
    sys.exit(0)
for o, items in by.items():
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if not src:
        continue
    t = open(src, encoding='utf-8').read().rstrip('\n') + '\n'
    t += ('\n// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for\n'
          '// the authentic link (PLAN M7); the placement link takes the shared bodies.\n')
    for n, d, a in items:
        t += '\n// %s (folded into %s at 0x%X)\n%s\n{\n%s}\n' % (n, NAMES[a], a, d, ('    ' + TRIVIAL[a] + '\n') if TRIVIAL[a] else '')
    open(src, 'w', encoding='utf-8', newline='\n').write(t)
print('applied')
