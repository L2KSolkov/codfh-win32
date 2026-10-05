"""protofix.py [--apply] [NAME...]: free functions declared with another prototype than their definition's (PLAN M7).

A reader that declares `void sub_18F8B0(RwInt32, RwInt32, RwInt32)` while the function is defined
as `RwInt32 sub_18F8B0(type_3DF8D8 *, RwInt32, void *)` references a symbol nothing defines.
For each such free function (same name; tools/session/sigdiff.py), every declaration of it in
include/ and in the reader units is replaced by the definition's prototype (the struct types it
names forward-declared before it), and the readers compile alone: arguments the compiler cannot
convert (C2664) get the parameter's type as a cast, uses of the result it cannot convert (C2440)
get the old return type as a cast. A function whose readers still fail is put back. The full
build decides whether the callers still match."""
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
_d = ctypes.windll.dbghelp
_d.UnDecorateSymbolName.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]


def und(n):
    b = ctypes.create_string_buffer(4096)
    _d.UnDecorateSymbolName(n.encode(), b, 4096, 0)
    return b.value.decode(errors='replace')


rows = collections.defaultdict(list)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[int(q[0], 16)].append((q[1], q[2]))
readers = collections.defaultdict(set)
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.log'), errors='replace'):
    m = re.match(r'^(\S+)\.obj : error LNK20\d\d: unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))', l)
    if m:
        readers[m.group(2) or m.group(3)].add(m.group(1))


def source_of(obj):
    base = os.path.join(ROOT, obj[len('build/'):-len('.obj')])
    return next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)


def definition_prototype(obj, name, fname):
    """The definition's head as a prototype: 'RET fname(PARAMS);'."""
    src = source_of(obj)
    if not src:
        return None
    t = open(src, encoding='utf-8', errors='replace').read()
    i = t.find('// match: %s @ ' % name)
    if i < 0:
        i = t.find('// match: %s @ ' % fname)
    if i < 0:
        return None
    m = re.compile(r'^((?:[\w\*&:<> ]+?\s+\**)?%s\s*\(([^;{]*?)\))\s*\n?\{' % re.escape(fname), re.M).search(t, i)
    if not m or t[i:m.start()].count('\n// match:') > 8:
        return None
    head = ' '.join(m.group(1).split())
    head = re.sub(r'\s*=\s*[^,)]+', '', head)
    return head + ';'


def _params(u):
    m = re.search(r'\((.*)\)\s*(?:const)?$', u)
    s = m.group(1) if m else ''
    out, depth, cur = [], 0, ''
    for ch in s:
        depth += ch in '(<'
        depth -= ch in ')>'
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip() and cur.strip() != 'void':
        out.append(cur.strip())
    return out


WORD = {'int', 'unsigned int', 'long', 'unsigned long', 'enum'}


def _kind(t):
    t = t.replace('const ', '').strip()
    if t.endswith('*') or t.endswith('&') or '(__cdecl*)' in t or '(__stdcall*)' in t:
        return 'word'                # a pointer passes as a 4-byte word
    if t in WORD or t.startswith('enum '):
        return 'word'
    return t


def abi_same(ur, ud):
    """The reader's and the definition's parameters pass the same way (pointers as pointers,
    4-byte integers as such): a cast changes no code. Narrower types, bool and float do."""
    pr, pd = _params(ur), _params(ud)
    return len(pr) == len(pd) and all(_kind(a) == _kind(b) for a, b in zip(pr, pd))


def overloaded(fname):
    """Overloads defined for it (aliasdefs.py --overloads): distinct functions, not a prototype."""
    for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if f.endswith('.cpp') and re.search(r'^// \?%s@@\S* \(folded into' % fname,
                                                 open(os.path.join(dp, f), encoding='utf-8', errors='replace').read(), re.M):
                return True
    return False


todo, skipped = [], []
for n in (l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt'))):
    m = re.match(r'^\?((?:sub|nullsub)_([0-9A-F]+))@@Y', n)
    if not m or (only and m.group(1) not in only):
        continue
    for obj, r in rows.get(int(m.group(2), 16), []):
        if re.match(r'^\?%s@@Y' % m.group(1), r) and r != n:
            proto = definition_prototype(obj, r, m.group(1))
            if proto and abi_same(und(n), und(r)) and not overloaded(m.group(1)):
                todo.append((m.group(1), proto, sorted(readers[n]), obj))
            elif proto:
                skipped.append((m.group(1), und(n)[:80], und(r)[:80]))
            break
print(len(todo), 'functions')
for s in skipped:
    print('  skip %-12s %s  vs  %s' % s)
for f, p, rd, o in todo[:60]:
    print('  %-12s %-70s %s' % (f, p[:70], ','.join(rd)[:60]))
if not apply:
    sys.exit(0)

rules = load_flags()
tmp = os.path.join(ROOT, 'build', 'tooltmp', 'protofix.obj')
os.makedirs(os.path.dirname(tmp), exist_ok=True)


def files_declaring(fname):
    out = []
    for top in ('include', 'src'):
        for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
            if 'sdk' in dp.split(os.sep):
                continue
            for f in fs:
                if f.endswith(('.h', '.cpp')):
                    p = os.path.join(dp, f)
                    t = open(p, encoding='utf-8', errors='replace').read()
                    if re.search(r'^(?:extern\s+(?:"C"\s+)?)?[A-Za-z_][^;\n(]*?\b%s\s*\([^;{]*\)\s*;' % fname, t, re.M):
                        out.append(p)
    return out


def unit_source(u):
    src = os.path.join(ROOT, 'src', 'recovered', u + '.cpp')
    if os.path.exists(src):
        return src
    for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
        if u + '.cpp' in fs:
            return os.path.join(dp, u + '.cpp')
    return src


def compile_unit(u):
    src = unit_source(u)
    if not os.path.exists(src):
        return True, []
    rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
    out = []
    ok = compile_with_deps(src, tmp, flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')], out) is not None
    return ok, '\n'.join(out).splitlines()


def call_args(line, start):
    """[(s, e)] argument spans of the call whose '(' is at START."""
    i, depth, args, s = start + 1, 0, [], start + 1
    while i < len(line):
        c = line[i]
        if c in '([':
            depth += 1
        elif c in ')]':
            if depth == 0:
                args.append((s, i))
                return args, i
            depth -= 1
        elif c == ',' and depth == 0:
            args.append((s, i))
            s = i + 1
        i += 1
    return args, None


for fname, proto, rd, obj in todo:
    files = files_declaring(fname)
    saved = dict((p, open(p, 'rb').read()) for p in files)
    for p in files:
        raw = saved[p].decode('utf-8', errors='surrogateescape')
        nl = '\r\n' if '\r\n' in raw else '\n'
        t = raw.replace('\r\n', '\n')
        if p == source_of(obj):
            continue
        fwd = sorted(set(re.findall(r'\b((?:type|Rw|Rp|Rt)\w*)\s*\*', proto)) - {'RwInt32', 'RwUInt32', 'RwReal', 'RwChar', 'RwUInt8', 'RwInt16', 'RwUInt16', 'RwBool'})

        def repl(m):
            lead = m.group(1) or ''
            pre = ''.join('struct %s;\n' % x for x in fwd if not re.search(r'\b(?:struct|class|typedef)\s[^;]*\b%s\b' % x, t))
            return pre + lead + proto
        t = re.sub(r'^((?:extern\s+(?:"C"\s+)?)?)[A-Za-z_][^;\n(]*?\b%s\s*\([^;{]*\)\s*;' % fname, repl, t, flags=re.M)
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
    oldret = None
    good = True
    for u in rd:
        src = unit_source(u)
        for attempt in range(10):
            ok, errs = compile_unit(u)
            if ok:
                break
            if not os.path.exists(src):
                break
            if src not in saved:
                saved[src] = open(src, 'rb').read()
            raw = open(src, 'rb').read().decode('utf-8', errors='surrogateescape')
            nl = '\r\n' if '\r\n' in raw else '\n'
            lines = raw.replace('\r\n', '\n').split('\n')
            changed = False
            for e in errs:
                m = re.match(r'^(.*)\((\d+)\) : error (C2664|C2440|C2446|C2440): (.*)$', e)
                if not m or (os.path.normcase(os.path.abspath(m.group(1))) != os.path.normcase(src)
                              and os.path.basename(m.group(1)).lower() != os.path.basename(src).lower()):
                    continue
                ln = int(m.group(2)) - 1
                if ln >= len(lines):
                    continue
                line = lines[ln]
                cm = re.search(r'\b%s\s*\(' % fname, line)
                if not cm:
                    # a call continued onto this line: join it onto its first line (layout only)
                    for j in range(ln - 1, max(ln - 5, -1), -1):
                        if re.search(r'\b%s\s*\(' % fname, lines[j]):
                            lines[j] = lines[j].rstrip() + ' ' + ' '.join(x.strip() for x in lines[j + 1:ln + 1])
                            del lines[j + 1:ln + 1]
                            changed = True
                            break
                    if changed:
                        break
                    continue
                if m.group(3) == 'C2664':
                    pm = re.search(r"cannot convert parameter (\d+) from '[^']*' to '([^']*)'", m.group(4))
                    if not pm:
                        continue
                    # the call the message names (the function itself, or one it is passed to)
                    callee = re.match(r"'([^']*)'", m.group(4))
                    callee = callee.group(1).split('::')[-1] if callee else fname
                    cc = re.search(r'\b%s\s*\(' % re.escape(callee), line)
                    if not cc:
                        continue
                    args, _e = call_args(line, cc.end() - 1)
                    k = int(pm.group(1))
                    if k > len(args):
                        continue
                    s, e2 = args[k - 1]
                    arg = line[s:e2].strip()
                    typ = re.sub(r'\b(struct|class|enum) ', '', pm.group(2))
                    typ = re.sub(r'\s*\*\s*', ' *', typ).replace('* *', '**').strip()
                    lead = line[s:e2][:len(line[s:e2]) - len(line[s:e2].lstrip())]
                    lines[ln] = line[:s] + lead + '(%s)%s' % (typ, arg if re.match(r'^[\w\.\->\[\]]+$', arg) else '(%s)' % arg) + line[e2:]
                    changed = True
                else:
                    tm = re.search(r"cannot convert from '[^']*' to '([^']*)'", m.group(4))
                    if not tm:
                        continue
                    args, close = call_args(line, cm.end() - 1)
                    if close is None:
                        continue
                    typ = re.sub(r'\b(struct|class|enum) ', '', tm.group(1))
                    lines[ln] = line[:cm.start()] + '(%s)%s' % (typ, line[cm.start():close + 1]) + line[close + 1:]
                    changed = True
            if not changed:
                break
            open(src, 'wb').write('\n'.join(lines).replace('\n', nl).encode('utf-8', errors='surrogateescape'))
        if not ok:
            good = False
            print('  %s: %s fails: %s' % (fname, u, next((e.strip()[:160] for e in errs if 'error' in e), '')))
            break
    if not good:
        for p, b in saved.items():
            open(p, 'wb').write(b)
        print('  put back', fname)
    else:
        print('  done', fname, len(files), 'files')
