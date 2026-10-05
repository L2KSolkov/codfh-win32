"""overlapvars.py [--aliases [--json OUT]]: game variables declared bigger than the room the image
gives them (PLAN M7, and any link other than the placement one).

The placement link pins each recovered variable at its image address, so two declarations of
one object (an int at a struct's first field, a placeholder at a global's address) both work
there; any other link gives each its own storage. A variable whose declared extent (the
compiler's: to the next symbol in its object's section, or the section's end) runs past the
next variable's image address overlaps that variable in the image: one of the two is a second
declaration of the other's storage. Prints those, game objects only.

Noisy (2026-10-04): the declared extent is the gap to the next symbol in the object's
section, which alignment padding and a declaration order other than the image's inflate;
confirm each hit against the variable's type before acting on it.

--aliases (2026-10-05, for plain builds: tools/plainbuild.py binds them under CODFH_PLAIN):
every variable T whose image address lies inside another variable S, by S's exact sizeof
(a probe includes S's unit and initializes a char (*)[sizeof(S)] with 1; the error message
prints the size). T is then a second name for S's bytes at T - S, which a plain link must
bind to S's storage to keep the image's layout. Rules:
- S's range ends at the first symbol that is certainly storage of its own: a function-local
  static or guard, a string literal, or a variable of the other kind (.data against .bss).
- T goes to its innermost container (gap-fill arrays from the M5 data rules span many
  variables; the object inside them is the real container), followed outward while that
  container is itself an alias, to real storage. A T past that storage's end is a variable
  of its own (a gap-fill array inside a struct can run past the struct's end).
- T is never bound when it is constructed (a $E dynamic initializer in its object refers to
  it), or cannot be named elsewhere (anonymous namespace, function statics): listed as kept.
--json writes the aliases as [{name, symbol, addr, outer, outer_symbol, outer_obj,
outer_addr, offset}]."""
import bisect
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ALIASES = '--aliases' in sys.argv
GAME_SKIP = ('build/src/rw/', 'build/src/rwa/', 'build/src/xdk/', 'build/src/bink/', 'build/src/xbe/')
place = {}           # (object, name) -> image address
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) >= 0x426D40:
        place[(q[1], q[2])] = int(q[0], 16)
p = os.path.join(ROOT, 'build', 'm7', 'bssmap.txt')
bss_ext, bss_static = {}, {}
for l in open(p):
    q = l.split()
    if len(q) == 3 and q[0].startswith('0x'):
        if q[1] == '-':
            bss_ext.setdefault(q[2], int(q[0], 16))
        else:
            bss_static[(q[1], q[2])] = int(q[0], 16)
all_addrs = sorted(set(place.values()) | set(bss_ext.values()) | set(bss_static.values()))
names_at = {}
for (o, n), a in place.items():
    names_at.setdefault(a, n)
for n, a in bss_ext.items():
    names_at.setdefault(a, n)
for (o, n), a in bss_static.items():
    names_at.setdefault(a, n)
all_names_at = {}
for (o, n), a in place.items():
    all_names_at.setdefault(a, []).append(n)
for n, a in bss_ext.items():
    all_names_at.setdefault(a, []).append(n)
for (o, n), a in bss_static.items():
    all_names_at.setdefault(a, []).append(n)
objs = sorted(set(o for o, n in place if o.startswith('build/src/')))
for r, ds, fs in os.walk(os.path.join(ROOT, 'build', 'src')):
    for f in fs:
        if f.endswith('.obj'):
            objs.append(os.path.relpath(os.path.join(r, f), ROOT).replace(os.sep, '/'))
objs = sorted(set(objs))
found = 0
cands = []           # (object, symbol, address, extent, inner addresses)
constructed = set()  # image addresses a $E dynamic initializer refers to
for o in objs:
    if ALIASES and o.startswith(GAME_SKIP):
        continue
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    if ALIASES:
        # (the variables each $E initializer refers to: constructed, never aliased)
        e_secs = set(y['section'] for y in c.symbol_list
                     if y['section'] > 0 and re.match(r'^_?\$E\d', y['name']))
        for sn in e_secs:
            for vaddr, si, rtype in c.sections[sn - 1]['relocs']:
                y = c.symbols.get(si)
                if not y:
                    continue
                a = place.get((o, y['name']))
                if a is None:
                    a = bss_static.get((o, y['name'])) if y['class'] == 3 else bss_ext.get(y['name'])
                if a is not None:
                    constructed.add(a)
    by_sec = {}
    for y in c.symbol_list:
        if y['class'] in (2, 3) and y['section'] > 0:
            s = c.sections[y['section'] - 1]
            if not (s['chars'] & 0x20) and (s['chars'] & 0xC0) and y['name'] != s['name'] \
                    and not y['name'].startswith(('$', '??_C@', '__real@', '??_R', '_$E')):
                by_sec.setdefault(y['section'], []).append(y)
    for sn, ys in by_sec.items():
        s = c.sections[sn - 1]
        size = s.get('size') or len(s['data'] or b'')
        ys.sort(key=lambda y: y['value'])
        for k, y in enumerate(ys):
            end = ys[k + 1]['value'] if k + 1 < len(ys) else size
            ext = end - y['value']
            a = place.get((o, y['name']))
            if a is None:
                a = bss_static.get((o, y['name'])) if y['class'] == 3 else bss_ext.get(y['name'])
            if a is None or ext <= 0:
                continue
            i = bisect.bisect_right(all_addrs, a)
            if ALIASES:
                inner = []
                while i < len(all_addrs) and all_addrs[i] < a + ext:
                    inner.append(all_addrs[i])
                    i += 1
                if inner and not y['name'].startswith('??_7'):
                    cands.append((o, y['name'], a, ext, inner))
                continue
            if i < len(all_addrs) and all_addrs[i] < a + ext:
                # (only past alignment padding: the next variable starts before the declared end
                # by at least four bytes, or at an unaligned point)
                if a + ext - all_addrs[i] >= 4:
                    print('0x%08X %-48s %s: declared 0x%X, next 0x%08X %s' % (
                        a, y['name'][:48], o.split('/')[-1], ext, all_addrs[i], names_at.get(all_addrs[i], '')[:48]))
                    found += 1
if not ALIASES:
    print('%d variables run into the next' % found)
    sys.exit(0)

from build_probes import XDK, flags_for, load_flags, split_compiler  # noqa: E402


def expression(symbol):
    """The C++ expression naming a mangled global (None when not a plain named global)."""
    m = re.match(r'^\?([A-Za-z_][A-Za-z0-9_]*)@((?:[A-Za-z_][A-Za-z0-9_]*@)*)@[23]', symbol)
    if not m:
        return None
    scopes = [s for s in m.group(2).split('@') if s]
    return '::'.join(list(reversed(scopes)) + [m.group(1)])


# exact sizes, one probe per defining unit
rules = load_flags()
sizes, unsized = {}, []
by_obj = {}
for o, sym, a, ext, inner in cands:
    by_obj.setdefault(o, []).append(sym)
tmp = os.path.join(ROOT, 'build', 'overlapvars')
os.makedirs(tmp, exist_ok=True)
for o, syms in sorted(by_obj.items()):
    rel = o[len('build/'):-len('.obj')]
    src = next((rel + e for e in ('.cpp', '.c') if os.path.exists(os.path.join(ROOT, rel + e))), None)
    if src is None or src.endswith('.c'):
        unsized += [(o, sym, 'C unit or no source') for sym in syms]
        continue
    line_of = {}     # probe line -> symbol
    lines = ['#include "%s"' % os.path.join(ROOT, src).replace('\\', '/')]
    for sym in syms:
        e = expression(sym)
        if e is None:
            unsized.append((o, sym, 'name not parsed'))
            continue
        line_of[len(lines) + 1] = sym
        lines.append('char (*overlap_size_%d)[sizeof(%s)] = 1;' % (len(lines), e))
    probe = os.path.join(tmp, 'probe.cpp')
    open(probe, 'w').write('\n'.join(lines) + '\n')
    cl, flags = split_compiler(flags_for(src, rules) + ['/I' + os.path.join(ROOT, 'include')])
    flags = [f for f in flags if f != '/Zi']
    env = dict(os.environ)
    env['PATH'] = os.path.dirname(cl) + os.pathsep + env.get('PATH', '')
    env['INCLUDE'] = os.path.join(XDK, 'xbox', 'include')
    out = subprocess.run([cl] + flags + ['/Fo' + os.path.join(tmp, 'probe.obj'), probe],
                         env=env, capture_output=True, text=True).stdout
    for k, n in re.findall(r"\.cpp\((\d+)\) : error C2440: 'initializing' : cannot convert from 'int' "
                           r"to 'char \(\*\)\[(\d+)\]'", out):
        if int(k) in line_of:
            sizes[(o, line_of[int(k)])] = int(n)
    for sym in syms:
        if (o, sym) not in sizes and expression(sym) is not None:
            unsized.append((o, sym, 'no size from the probe'))

in_bss = set(bss_ext.values()) | set(bss_static.values())
LOCAL = re.compile(r'@\?[^@]*@?\?\?|^\?\$S|^\$S|\?\?_C@')


def separate(t, a):
    """Whether the variable at t is certainly storage of its own (ends the range from a)."""
    if (t in in_bss) != (a in in_bss):
        return True
    return any(LOCAL.search(n) for n in all_names_at[t])


container = {}       # inner address -> (object, symbol, address) of its innermost container
for o, sym, a, ext, inner in cands:
    n = sizes.get((o, sym))
    if n is None:
        continue
    for t in inner:
        if t >= a + n or separate(t, a):
            break
        if t not in container or a > container[t][2]:
            container[t] = (o, sym, a)
rows, kept = [], []
for t in sorted(container):
    names = all_names_at[t]
    why = None
    if t in constructed:
        why = 'constructed'
    elif all(expression(n) is None or '?A0x' in n for n in names):
        why = 'cannot be named elsewhere'
    if why:
        kept.append((t, names[0], why))
        continue
    o, sym, a = container[t]
    # (follow outward to real storage: a container that is itself an alias has none)
    while a in container and a not in constructed:
        o, sym, a = container[a]
    if t >= a + sizes[(o, sym)]:
        # (a gap-fill array inside a struct runs past the struct's end: t lies past the real
        # storage, so it is a variable of its own)
        kept.append((t, names[0], 'past %s' % expression(sym)))
        continue
    for n in names:
        if expression(n) is None or '?A0x' in n:
            continue
        rows.append({'name': expression(n), 'symbol': n, 'addr': t, 'outer': expression(sym),
                     'outer_symbol': sym, 'outer_obj': o, 'outer_addr': a, 'offset': t - a})
for r in rows:
    print('0x%08X %-40s = %s + 0x%X' % (r['addr'], r['name'][:40], r['outer'], r['offset']))
print('%d aliases' % len(rows))
print('%d kept as their own storage:' % len(kept))
for t, n, why in kept:
    print('  0x%08X %s: %s' % (t, n[:60], why))
print('%d containers not sized:' % len(unsized))
for o, sym, why in unsized:
    print('  %s %s: %s' % (o.split('/')[-1], sym, why))
if '--json' in sys.argv:
    json.dump(rows, open(sys.argv[sys.argv.index('--json') + 1], 'w'), indent=1)
