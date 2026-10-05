"""aliasdefs.py [--apply] [UNIT...]: definitions for the ICF-folded functions the real link needs (PLAN M7).

/OPT:ICF folded many functions into one body; config/aliases.txt maps their names to it, so the
placement link never needed their definitions, but the real link does (build/m7/unresolved.txt).
For each unresolved alias: its signature from the undecorated name (dbghelp), its body the folded
target's own source body (same code, so the same text with the target's parameter names), its
unit the one holding most of its class's placed members (else its first reader in the probe's
link log). Class templates and function templates are left out. With --apply each owner unit
gets the definitions appended and is compiled alone; definitions the compiler rejects are taken
out again (a unit that still fails gets none). UNIT limits the owners (basename, no extension)."""
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
_dbghelp = ctypes.windll.dbghelp
_dbghelp.UnDecorateSymbolName.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]
_und = {}


def undname(n):
    if n not in _und:
        b = ctypes.create_string_buffer(4096)
        _dbghelp.UnDecorateSymbolName(n.encode(), b, 4096, 0)
        _und[n] = b.value.decode(errors='replace').strip()
    return _und[n]


def split_params(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '<(':
            depth += 1
        elif ch in '>)':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


RWT = [(r'\bunsigned long\b', 'ULONG'), (r'\blong\b', 'HRESULT'), (r'\bunsigned int\b', 'RwUInt32'),
       (r'\bunsigned short\b', 'RwUInt16'), (r'\bunsigned char\b', 'RwUInt8'), (r'\bsigned char\b', 'RwInt8'),
       (r'\bint\b', 'RwInt32'), (r'\bshort\b', 'RwInt16'), (r'\bfloat\b', 'RwReal'), (r'\bchar\b', 'RwChar')]
SIG = re.compile(r'^(?:(?:public|protected|private): )?(?:virtual |static )?(.*?)\b(__thiscall|__cdecl|__stdcall|__fastcall) '
                 r'(.*?)\((.*)\)\s*(const)?$')


def parse_sig(n):
    """(return type, convention, qualified name, [param types], const) or None."""
    u = undname(n)
    m = SIG.match(u)
    if not m:
        return None
    ret, conv, qual, params, const = m.groups()
    params = [] if params.strip() in ('void', '') else split_params(params)
    return ret.strip(), conv, qual, params, bool(const)


aliases = {}
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and not l.startswith('#') and q[1].startswith('0x'):
        aliases[q[0]] = int(q[1], 16)
unres = set(l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')) if l.strip())
rows, by_class = {}, collections.defaultdict(collections.Counter)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/'):
        rows.setdefault(int(q[0], 16), (q[1], q[2]))
        if q[2].startswith('?') and int(q[0], 16) < 0x3C0000:
            s = parse_sig(q[2])
            if s and '::' in s[2]:
                by_class[s[2].rsplit('::', 1)[0]][q[1]] += 1
readers, overloads = {}, set()
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.log'), errors='replace'):
    m = re.match(r'^(\S+\.obj) : error LNK20\d\d: unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))', l)
    if m and (m.group(2) or m.group(3)) not in readers:
        readers[m.group(2) or m.group(3)] = m.group(1)
# address-named functions folded into a function placed under another qualified name: aliases
# config/aliases.txt does not list (a declaration with only another signature is not one)
for n in unres:
    m = re.match(r'^\?(?:sub|nullsub)_([0-9A-F]+)@', n)
    if not m or n in aliases:
        continue
    a = int(m.group(1), 16)
    if a not in rows:
        continue
    s = parse_sig(n)
    placed = [parse_sig(r[1]) for r in [rows[a]]]
    # a placed function with a real name (RWS::...GetIsSolid) is the one the reader means: its
    # declaration is the thing to fix, not a second definition
    if s and placed[0] and placed[0][2] != s[2] and re.search(r'(?:sub|vf|nullsub|pvf)_[0-9A-F]+$', placed[0][2]):
        aliases[n] = a
    elif '--overloads' in sys.argv and s and placed[0] and placed[0][2] == s[2] and placed[0][3] != s[3]:
        # the same name with other parameters: a distinct function folded into this one when the
        # body ignores its parameters (an empty or constant body); an overload with that body
        aliases[n] = a
        overloads.add(n)
objs = set(o for o, n in rows.values())


def source_of(obj):
    base = os.path.join(ROOT, obj[len('build/'):-len('.obj')])
    return next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)


_texts = {}


def text_of(p):
    if p not in _texts:
        _texts[p] = open(p, encoding='utf-8', errors='replace').read()
    return _texts[p]


_headers = None


def inline_def(cls, member):
    """(param names, body) of MEMBER defined inline in CLS's body in a header."""
    global _headers
    if _headers is None:
        _headers = []
        for dp, _dn, fs in os.walk(os.path.join(ROOT, 'include')):
            for f in fs:
                if f.endswith('.h'):
                    _headers.append(text_of(os.path.join(dp, f)))
    for t in _headers:
        cm = re.search(r'^\s*(?:struct|class)\s+%s\b[^;{]*\{' % re.escape(cls), t, re.M)
        if not cm:
            continue
        depth, k = 0, cm.end() - 1
        while k < len(t):
            depth += {'{': 1, '}': -1}.get(t[k], 0)
            if depth == 0:
                break
            k += 1
        body = t[cm.end():k]
        mm = re.search(r'\b%s\s*\(([^()]*)\)\s*(?:const)?\s*\{' % re.escape(member), body)
        if not mm:
            return None
        names = []
        for p in ([] if mm.group(1).strip() in ('', 'void') else split_params(mm.group(1))):
            nm = re.search(r'(\w+)\s*$', re.sub(r'\s*=.*$', '', p))
            names.append(nm.group(1) if nm else '')
        depth, s = 0, mm.end() - 1
        e = s
        while e < len(body):
            depth += {'{': 1, '}': -1}.get(body[e], 0)
            if depth == 0:
                break
            e += 1
        return names, body[s:e + 1]
    return None


def target_def(a):
    """(param names, body text) of the function placed at A, from its unit's source."""
    if a not in rows:
        return None
    obj, name = rows[a]
    src = source_of(obj)
    if not src:
        return None
    t = text_of(src)
    i = t.find('// match: %s @ 0x%08X\n' % (name, a))
    if i < 0:
        return None
    j = i
    while True:                     # past the match and comment lines
        k = t.find('\n', j) + 1
        if not t[k:].startswith('//') and t[k:k + 1] != '\n':
            j = k
            break
        j = k
    s = parse_sig(name)
    if not s:
        return None
    member = s[2].rsplit('::', 1)[-1]
    head_end = t.find('{', j)
    head = t[j:head_end]
    if head.lstrip().startswith('template') or member not in head or ';' in head:
        # a match line stacked with others: the definition head by its qualified name
        cls = s[2].rsplit('::', 1)[0].split('::')[-1] if '::' in s[2] else None
        pat = (r'\b%s::%s\s*\(' % (re.escape(cls), re.escape(member))) if cls else (r'^[^\n;(]*\b%s\s*\(' % re.escape(member))
        m = re.compile(r'^(?!template)[^\n;{}]*%s[^;{]*\)\s*(?:const)?\s*\n?\{' % pat, re.M).search(t)
        if not m and cls:
            return inline_def(cls, member)
        if not m:
            return None
        j = m.start()
        head_end = t.find('{', m.start() + len(m.group(0)) - 1)
        head = t[j:head_end]
    po = head.find('(', head.find(member))
    depth, k = 0, po
    while k < len(head):
        depth += {'(': 1, ')': -1}.get(head[k], 0)
        if depth == 0:
            break
        k += 1
    plist = head[po + 1:k].strip()
    # a constructor's member initializers (between the parameters and the body) are part of it
    init = ' '.join(head[k + 1:].split())
    init = init if init.startswith(':') else ''
    names = []
    for p in ([] if plist in ('', 'void') else split_params(plist)):
        if p == '...':
            names.append('...')
            continue
        p = re.sub(r'\s*=.*$', '', p)
        m = re.search(r'(\w+)\s*(\[[^\]]*\])?$', p)
        if not m or '(' in p:
            return None
        names.append(m.group(1))
    depth, k = 0, head_end
    while k < len(t):
        depth += {'{': 1, '}': -1}.get(t[k], 0)
        if depth == 0:
            break
        k += 1
    return names, (init + '\n' if init else '') + t[head_end:k + 1]


plan, skipped = collections.defaultdict(list), collections.Counter()
for n in sorted(unres):
    if n not in aliases:
        continue
    s = parse_sig(n)
    if not s:
        skipped['no signature'] += 1
        continue
    ret, conv, qual, params, const = s
    if '<' in qual or '`' in qual:
        skipped['template'] += 1
        continue
    td = target_def(aliases[n])
    if not td:
        skipped['target body not found'] += 1
        continue
    names, body = td
    # a different return type (another view of the same pointer, or a pointer where the target
    # returns an int): the target's returns cast to it, no code
    tsig = parse_sig(rows[aliases[n]][1]) if aliases[n] in rows else None
    if ret and ret != 'void' and tsig and tsig[0] != ret:
        rtyp = ret
        for a_, b_ in RWT:
            rtyp = re.sub(a_, b_, rtyp)
        rtyp = re.sub(r'\b(struct|class|enum) ', '', rtyp)
        body = re.sub(r'\breturn\s+([^;]+);', lambda m: 'return (%s)(%s);' % (rtyp, m.group(1).strip()), body)
    if not ret:                     # a constructor or destructor folded into `return this`
        body = re.sub(r'\breturn\s+this\s*;', '', body)
    reads = any(re.search(r'\b%s\b' % re.escape(x), body) for x in names if x != '...')
    if n in overloads:
        if reads or len(body) > 200:
            skipped['overload body reads its parameters'] += 1
            continue
        names = ['arg_%X' % (4 * i) for i in range(len(params))]
    elif not reads and (len(names) != len(params) or '...' in names):
        # a body that ignores its parameters (the empty debug print an operator delete was
        # folded into): the alias's own parameters, unnamed alike
        names = ['arg_%X' % (4 * i) for i in range(len(params))]
    if len(names) != len(params) or any('(' in p for p in params):
        skipped['parameters differ'] += 1
        continue
    cls = qual.rsplit('::', 1)[0] if '::' in qual else None
    owner = by_class[cls].most_common(1)[0][0] if cls and by_class[cls] else None
    if not owner and n in readers:
        owner = next((o for o in objs if o.endswith('/' + readers[n])), None)
    if not owner:
        skipped['no unit'] += 1
        continue
    if only and os.path.basename(owner)[:-4] not in only:
        continue
    keep_conv = conv if conv in ('__stdcall', '__fastcall') and not cls else ''
    decl = '%s%s%s(%s)%s' % (ret + ' ' if ret else '', keep_conv + ' ' if keep_conv else '', qual,
                             ', '.join('%s %s' % (p, nm) for p, nm in zip(params, names)), ' const' if const else '')
    for a_, b_ in RWT:              # the audit's RenderWare scalar types
        decl = re.sub(a_, b_, decl)
    plan[owner].append((n, decl, body, aliases[n]))
print(sum(len(v) for v in plan.values()), 'definitions in', len(plan), 'units; skipped', dict(skipped))
if not apply:
    for o, items in list(plan.items())[:8]:
        for n, d, b, a in items[:2]:
            print(os.path.basename(o), '|', d, '|', ' '.join(b.split())[:60])
    sys.exit(0)
rules = load_flags()
tmp = os.path.join(ROOT, 'build', 'tooltmp', 'aliasdefs.obj')
os.makedirs(os.path.dirname(tmp), exist_ok=True)
HEAD = ('\n// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the\n'
        '// authentic link (PLAN M7) with that body; the placement link takes the folded one.\n')
done = 0
for o, items in sorted(plan.items()):
    src = source_of(o)
    raw = open(src, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    base = raw.rstrip('\r\n') + nl
    rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
    flags = flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')]
    live = list(items)
    for attempt in range(6):
        if not live:
            break
        text, spans = base + HEAD.replace('\n', nl), []
        for n, d, b, a in live:
            start = text.count('\n') + 2
            block = '%s// %s (folded into 0x%X)%s%s%s%s%s' % (nl, n, a, nl, d, nl, b.replace('\r\n', '\n').replace('\n', nl), nl)
            text += block
            spans.append((start, text.count('\n') + 1))
        open(src, 'wb').write(text.encode('utf-8'))
        out = []
        if compile_with_deps(src, tmp, flags, out) is not None:
            break
        bad = set()
        for line in '\n'.join(out).splitlines():
            m = re.match(r'^(.*)\((\d+)\) : (?:fatal )?error', line)
            if m and os.path.normcase(os.path.abspath(m.group(1))) == os.path.normcase(src):
                ln = int(m.group(2))
                hit = set(i for i, (s0, s1) in enumerate(spans) if s0 <= ln <= s1)
                if os.environ.get('ALIASDEBUG') and hit - bad:
                    print('    drop %s: %s' % (live[min(hit)][0], line.split(' : ', 1)[-1][:150]))
                bad |= hit
        if not bad:
            live = []
            break
        live = [x for i, x in enumerate(live) if i not in bad]
    else:
        live = []
    if not live:
        open(src, 'wb').write(raw.encode('utf-8'))
        print('  none for', os.path.basename(src))
        continue
    done += len(live)
    print('  %-28s %d of %d' % (os.path.basename(src), len(live), len(items)))
print('applied', done)
