"""unkeyedlib.py: the M7 link's unkeyed library data, and where the image may hold it (PLAN M7).

Reads build/m7/link.log of a verbose probe (M7VERBOSE=1): every library member the link
loaded. For each loaded member's initialized data section the probe left unkeyed (named
`$zzzzzzzz`: no row for it), prints the member (library, cdz copy, the installed library's
member name by index), the section's symbols and size, and each image address in the
initialized data sections where its bytes occur with the row there (`=` when the row starts
there). A version difference shows as no address: the image's member lacks the datum."""
import bisect
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LIBEXE = os.path.join(os.environ.get('XDK', r'C:\XDK'), 'xbox', 'bin', 'vc71', 'lib.exe')
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
secs = [(s['name'], s['va'], img.read(s['va'], s['rsize'])) for s in img.sections
        if s['name'] in ('.data', '.rdata', 'XON_RD', '.data1', 'BINKDATA', 'DOLBY')
        or s['name'].endswith(('_RW', '_RD'))]
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
addrs = [r[0] for r in rows]
cdz = os.path.join(ROOT, 'build', 'm7', 'cdz')


def members(lib):
    r = subprocess.run([LIBEXE, '/nologo', '/list', lib], capture_output=True, text=True)
    return [l.strip() for l in r.stdout.splitlines() if l.strip()]


libdir = {}
for f in os.listdir(cdz):
    if f.endswith('.lib'):
        m = members(os.path.join(cdz, f))
        if m:
            libdir[f.lower()] = os.path.dirname(m[0])
loaded = re.findall(r'Loaded (\S+?\.lib)\((m\d+\.obj)\)', open(os.path.join(ROOT, 'build', 'm7', 'link.log'),
                                                          errors='replace').read())
orig_names = {}
for lib, mem in sorted(set(loaded)):
    d = libdir.get(lib.lower())
    if not d:
        continue
    p = os.path.join(d, mem)
    try:
        c = Coff(p)
    except Exception:
        continue
    for i, s in enumerate(c.sections):
        if not s['name'].endswith('$zzzzzzzz') or s['chars'] & 0x1080 or not s['data']:
            continue
        data = bytes(s['data'])
        syms = [v['name'] for v in c.symbols.values() if v['section'] == i + 1 and v['name'] != s['name']]
        if lib.lower() not in orig_names:
            src = os.path.join(os.environ.get('XDK', r'C:\XDK'), 'xbox', 'lib', lib)
            orig_names[lib.lower()] = members(src) if os.path.exists(src) else []
        on = orig_names[lib.lower()]
        idx = int(mem[1:5])
        hits = []
        if data.count(0) != len(data):
            for nm, va, blob in secs:
                k = blob.find(data)
                while k >= 0 and len(hits) < 6:
                    a = va + k
                    j = bisect.bisect_right(addrs, a) - 1
                    hits.append('%s:0x%08X%s%s' % (nm, a, '=' if rows[j][0] == a else '~', rows[j][2][:28]))
                    k = blob.find(data, k + 1)
        print('%s(%s) %s %s %d [%s] %s' % (lib, mem, on[idx] if idx < len(on) else '?', s['name'], len(data),
                                           ','.join(syms[:3]), ' '.join(hits) or '-'))
