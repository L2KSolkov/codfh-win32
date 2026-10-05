"""libdatascan.py: library members that are not in config/xdk_members.txt but whose plain data
sections the image holds inside XDK data stand-in pieces (PLAN M7).

The original link pulls a member for a reference and keeps its plain data sections whatever
/OPT:REF drops of its code (xvoice's nnet_dual and melcep_Int: no code in the image, their
tables in it). For every member of the installed and 5849 libraries not yet extracted, each
plain .data/.rdata/named data section of at least 32 bytes (with 16 bytes or more that are not
zero or relocated) is searched for in the stand-in pieces; prints the members whose sections
are found there, with where."""
import glob
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from lib import Library  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
known = set()
for l in open(os.path.join(ROOT, 'config', 'xdk_members.txt'), encoding='utf-8'):
    q = l.split(None, 2)
    if len(q) == 3:
        known.add((os.path.basename(q[1]).lower(), q[2].strip().lower()))
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'))
              if len(q) >= 3 and q[0].startswith('0x'))
pieces = []
for k, (a, o, n) in enumerate(rows):
    if o.startswith('build/src/xdk/standin_data') and k + 1 < len(rows):
        try:
            pieces.append((a, rows[k + 1][0], n, img.read(a, rows[k + 1][0] - a)))
        except Exception:
            pass
libs = glob.glob(r'C:\XDK\xbox\lib\*.lib') + glob.glob(os.path.join(ROOT, 'xdklib', '*.lib'))
for lp in libs:
    try:
        L = Library(lp)
    except Exception:
        continue
    lib = os.path.basename(lp).lower()
    for m, d in L.members:
        if (lib, m.lower()) in known or not m.lower().endswith('.obj'):
            continue
        try:
            c = Coff(m, data=d)
        except Exception:
            continue
        found = []
        for s in c.sections:
            if s['chars'] & 0x20 or s['chars'] & 0x1000 or not (s['chars'] & 0x40) or s['name'].startswith('.debug') \
                    or len(s['data']) < 32:
                continue
            data = bytes(s['data'])
            ra = set()
            for va, si, t in s['relocs']:
                ra.update(range(va, va + 4))
            if sum(1 for j in range(len(data)) if j not in ra and data[j]) < 16:
                continue
            k0 = next((k for k in range(len(data) - 8) if not any(j in ra for j in range(k, k + 8)) and any(data[k:k + 8])), None)
            if k0 is None:
                continue
            for a, e, n, b in pieces:
                j = b.find(data[k0:k0 + 8])
                while j >= 0:
                    st = j - k0
                    if st >= 0 and st + len(data) <= len(b) and all(data[q] == b[st + q] for q in range(len(data)) if q not in ra):
                        found.append('%s %d at 0x%X (%s)' % (s['name'], len(data), a + st, n))
                        break
                    j = b.find(data[k0:k0 + 8], j + 1)
        if found:
            print(lib, m, '; '.join(found))
