"""fwdfix.py SRC...: declare what a reordered unit uses before its definition (PLAN M7).

After reorder.py puts definitions in address order, a function or datum the unit defines further
down can be used above its definition. This compiles the unit (cc1's way), takes the names the
errors report (C2065, C3861, C2365, C2040, C2371, C2373), and puts a declaration copied from the
unit's own definition just above the first top-level item that uses the name: a function's
signature (default arguments dropped), or `extern` and the datum's declarator without its
initializer. Repeats until the unit compiles or nothing changes. With --from OTHER, names
this unit does not define are declared from OTHER's definitions or declarations (after
unitsplit.py: the unit it was split from)."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_probes import flags_for, load_flags  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402
import reorder  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ERR = re.compile(r"error (C2065|C3861|C2365|C2040|C2371|C2373)\s*:\s*'(\w+)'")
rules = load_flags()


def errors(src):
    rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'fwdfix.obj')
    out = []
    ok = compile_with_deps(os.path.abspath(src), obj, flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')], out) is not None
    text = '\n'.join(out)
    names = []
    for m in ERR.finditer(text):
        if m.group(2) not in names:
            names.append(m.group(2))
    return ok, names, [l for l in text.splitlines() if 'error' in l]


def strip_comments(s):
    return re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', s, flags=re.S))


def declaration(item, name):
    """The declaration of name that item defines, or None."""
    code = strip_comments(item).strip()
    m = re.search(r'(?<![\w:])' + re.escape(name) + r'\s*\(', code)
    if m and '{' in code[m.end():] and '{' not in code[:m.start()] and ';' not in code[:m.start()]:
        head = code[:code.index('{', m.end())].rstrip()
        if head.endswith(')') or re.search(r'\)\s*const$', head):
            if '::' in head[:m.start()].split()[-1:][0] if head[:m.start()].split() else False:
                return None
            head = re.sub(r'\s*=\s*[^,()]+(?=[,)])', '', head)      # default arguments
            return ' '.join(head.split()) + ';'
    # data: the statement (between top-level semicolons) that names it
    stmts, depth, cur = [], 0, ''
    for ch in code:
        depth += ch == '{'
        depth -= ch == '}'
        if ch == ';' and depth == 0:
            stmts.append(cur)
            cur = ''
        else:
            cur += ch
    stmts.append(cur)
    code = next((s.strip() for s in stmts if re.search(r'(?<![\w:])' + re.escape(name) + r'\b', s.split('=')[0])), '')
    if '{' in code.split('=')[0]:
        return None                     # a function body, not a declaration
    if re.search(r'(?<![\w:])' + re.escape(name) + r'\s*\(', code.split('=')[0]):
        # a prototype: copied as it is
        return ' '.join(code.split()) + ';'
    m = re.search(r'(?<![\w:])' + re.escape(name) + r'\b', code)
    if m and not re.search(r'\(', code[:m.start()]):
        decl = code[:m.end()]
        rest = code[m.end():]
        dims = re.match(r'(\s*\[[^\]]*\])*', rest).group(0)
        decl = ' '.join((decl + dims).split())
        if decl.startswith('static '):
            return None
        if not decl.startswith('extern '):
            decl = 'extern ' + decl
        return decl + ';'
    return None


def fix(src):
    for _round in range(20):
        ok, names, errs = errors(src)
        if ok:
            print('%s: ok' % src)
            return True
        raw = open(src, 'rb').read().decode('utf-8', errors='surrogateescape')
        nl = '\r\n' if '\r\n' in raw else '\n'
        t = raw.replace('\r\n', '\n')
        its = reorder.items(t)
        if its is None:
            its = []
        parts = [t[s:e] for s, e in its] or [t]
        changed = False
        for name in names:
            defn = None
            for i, p in enumerate(parts):
                d = declaration(p, name)
                if d and re.search(r'\{', strip_comments(p)) or (d and '=' in strip_comments(p)):
                    defn = (i, d)
                    break
            if defn is None:
                for i, p in enumerate(parts):
                    d = declaration(p, name)
                    if d:
                        defn = (i, d)
                        break
            if defn is None:
                # a declaration from another unit (--from: the unit this one was split from)
                for other in OTHERS:
                    ot = open(other, encoding='utf-8', errors='surrogateescape').read().replace('\r\n', '\n')
                    for s, e in reorder.items(ot) or []:
                        d = declaration(ot[s:e], name)
                        if d and re.match(r'(static\s+)?inline\b', d) and '{' in strip_comments(ot[s:e]):
                            # an inline helper (no address of its own): its whole definition,
                            # so the calls still expand
                            d = ot[s:e].strip('\n')
                        elif d:
                            d = re.sub(r'^static\s+', '', d) if '(' in d else d
                        if d:
                            defn = (len(parts), d)
                            break
                    if defn:
                        break
            if defn is None:
                print('%s: no definition of %s here' % (src, name))
                continue
            di, decl = defn
            use = next((i for i, p in enumerate(parts) if i != di and
                        re.search(r'(?<![\w:])' + re.escape(name) + r'\b', strip_comments(p))), None)
            if use is None or use > di:
                print('%s: %s is not used before its definition' % (src, name))
                continue
            p = parts[use]
            pp = [m.end() for m in re.finditer(r'^#[^\n]*\n', p, re.M)]
            if pp:
                # after the item's preprocessor lines (the first item holds the includes)
                k = pp[-1]
                parts[use] = p[:k] + '\n' + decl + '\n' + p[k:]
            else:
                k = len(p) - len(p.lstrip('\n'))
                parts[use] = p[:k] + decl + '\n' + p[k:]
            changed = True
        if not changed:
            print('%s: stuck' % src)
            for e in errs[:6]:
                print('   ', e.strip()[:200])
            return False
        t = ''.join(parts)
        open(src, 'wb').write(t.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
    return False


OTHERS = []
args = sys.argv[1:]
while '--from' in args:
    k = args.index('--from')
    OTHERS.append(args[k + 1])
    del args[k:k + 2]
ok = [fix(s) for s in args]
if not all(ok):
    sys.exit(1)       # stuck: splitunit.py stops here
