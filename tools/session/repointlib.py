"""repointlib.py LIB [--apply]: rows of the installed XDK library LIB onto its xdklib/ copy
(PLAN M7: the image's library table says which version it linked; d3d8 and dsound are
1.0.5849.1, the base 5849 copies in xdklib/, not the installed QFE's).

For each installed member with rows (build/xdk/LIB/MEMBER), the same member of xdklib/LIB.lib
is extracted (build/xdk/xdklib_LIB/MEMBER); a row whose symbol the xdklib copy defines with the
same section bytes, size and relocation targets moves to the xdklib object (config/compiled.txt)
and the member joins config/xdk_members.txt. Rows that differ stay and are listed. Prints the
plan; --apply edits."""
import os
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LIBEXE = os.path.join(os.environ.get('XDK', r'C:\XDK'), 'xbox', 'bin', 'vc71', 'lib.exe')
lib = sys.argv[1]
apply = '--apply' in sys.argv
src_lib = os.path.join(ROOT, 'xdklib', lib + '.lib')
inst_dir = 'build/xdk/%s/' % lib
alt_dir = 'build/xdk/xdklib_%s/' % lib
members = {}
for l in open(os.path.join(ROOT, 'config', 'xdk_members.txt'), encoding='utf-8'):
    q = l.split(None, 2)
    if len(q) == 3 and q[0].startswith(inst_dir):
        members[q[0]] = q[2].strip()
have_alt = set(l.split(None, 2)[0] for l in open(os.path.join(ROOT, 'config', 'xdk_members.txt'), encoding='utf-8')
               if l.startswith(alt_dir))
rows = [l.rstrip('\n') for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')]


def sig(c, name):
    y = next((y for y in c.symbol_list if y['name'] == name and y['section'] > 0), None)
    if y is None:
        return None
    s = c.sections[y['section'] - 1]
    byi = dict((z['index'], z) for z in c.symbol_list)
    rel = tuple(sorted((va, t, byi[si]['name'] if byi[si]['class'] == 2 or byi[si]['section'] <= 0 else
                        ('static', byi[si]['value'])) for va, si, t in s['relocs']))
    return (bytes(s['data']), y['value'], s['name'], rel)


moved, kept, new_members = {}, [], {}
for obj, mem in sorted(members.items()):
    alt = alt_dir + os.path.basename(obj)
    altp = os.path.join(ROOT, alt)
    if not os.path.exists(altp):
        os.makedirs(os.path.dirname(altp), exist_ok=True)
        r = subprocess.run([LIBEXE, '-nologo', '-EXTRACT:' + mem, '-OUT:' + altp, src_lib], capture_output=True, text=True)
        if r.returncode or not os.path.exists(altp):
            print('no member %s in %s' % (mem, src_lib))
            continue
    try:
        ci, ca = Coff(os.path.join(ROOT, obj)), Coff(altp)
    except Exception as e:
        print('unreadable', obj, e)
        continue
    for i, l in enumerate(rows):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and q[1] == obj:
            a, b = sig(ci, q[2]), sig(ca, q[2])
            if a is not None and a == b:
                moved[i] = '%s %s %s' % (q[0], alt, q[2])
                if alt not in have_alt:
                    new_members[alt] = mem
            else:
                kept.append((q[0], os.path.basename(obj), q[2]))
print('%d rows move to %s, %d stay' % (len(moved), alt_dir, len(kept)))
for a, o, n in kept[:40]:
    print('  stays', a, o, n[:70])
if apply:
    for i, l in moved.items():
        rows[i] = l
    open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(rows) + '\n')
    with open(os.path.join(ROOT, 'config', 'xdk_members.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for alt, mem in sorted(new_members.items()):
            f.write('%s xdklib/%s.lib %s\n' % (alt, lib, mem))
    print('applied; %d members added' % len(new_members))
