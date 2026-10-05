"""shiftcount.py: per image section, how many times the M7 probe's map offset (map address minus
image address) changes from one placed row to the next (PLAN M7: each change is a layout
difference to explain), and how many rows the map lacks. SC_SHOW=SECTION[,SECTION] lists the
rows where those sections' offset changes."""
import collections
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
secs = sorted((s['va'], s['va'] + s['vsize'], s['name']) for s in img.sections)
# the linked objects (build/m7/cdz/objects.txt: NNNN.obj -> its source, a repacked member's
# build/m7/standin/members.txt): a row's own object's symbol first, the name's first otherwise
num_of = {}
_ot = os.path.join(ROOT, 'build', 'm7', 'cdz', 'objects.txt')
if os.path.exists(_ot):
    pre = 'build/m7/obj/'
    for l in open(_ot):
        q = l.split()
        if len(q) == 2:
            src = q[1][len(pre):] if q[1].startswith(pre) else q[1]
            num_of[src] = q[0]
_mt = os.path.join(ROOT, 'build', 'm7', 'standin', 'members.txt')
if os.path.exists(_mt):
    for l in open(_mt):
        q = l.split()
        if len(q) == 3 and q[2] in num_of:
            num_of.setdefault(q[1], num_of[q[2]])
mp = {}
mp_obj = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    q = l.split()
    if len(q) >= 3 and re.match(r'00[0-9a-f]{2}:[0-9a-f]{8}$', q[0]) and re.match(r'[0-9a-f]{8}$', q[2]):
        mp.setdefault(q[1], int(q[2], 16))
        mp_obj.setdefault((q[1], q[-1]), int(q[2], 16))
# (a row whose order-file name differs, a static the probe packaged under a name of its own:
# that name, build/m7/ordernames.txt)
oname = {}
_on = os.path.join(ROOT, 'build', 'm7', 'ordernames.txt')
if os.path.exists(_on):
    for l in open(_on):
        q = l.split()
        if len(q) == 2:
            oname[int(q[0], 16)] = q[1]
# (an EH handler the probe folded into another copy, build/m7/ehfolds.txt: the kept copy's name)
ehkeep = {}
_ef = os.path.join(ROOT, 'build', 'm7', 'ehfolds.txt')
if os.path.exists(_ef):
    for l in open(_ef):
        q = l.split()
        if len(q) == 3:
            ehkeep[q[1]] = q[2]
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
shifts, missing, total = collections.Counter(), collections.Counter(), collections.Counter()
last = {}
show = set(os.environ.get('SC_SHOW', '').split(','))
for a, o, n in rows:
    sec = next((s[2] for s in secs if s[0] <= a < s[1]), '?')
    total[sec] += 1
    on = oname.get(a)
    if on and on != n and on.startswith(('_cdz_', 'cdz_')):
        n = on if on.startswith('_') else '_' + on
    num = num_of.get(o)
    if n in ehkeep and (n, num) not in mp_obj:
        n = ehkeep[n]
    m = None
    if num:
        m = mp_obj.get((n, num)) or (None if n.startswith('_') else mp_obj.get(('_' + n, num)))
    if m is None:
        m = mp.get(n) or (None if n.startswith('_') else mp.get('_' + n))
    if m is None:
        missing[sec] += 1
        continue
    off = m - a
    if sec in last and last[sec] != off:
        shifts[sec] += 1
        if sec in show:
            print('0x%08X %+6d -> %+6d  %s %s' % (a, last[sec], off, os.path.basename(o), n))
    last[sec] = off
for s in [x[2] for x in secs]:
    if total[s]:
        print('%-10s %6d rows %5d shifts %5d missing' % (s, total[s], shifts[s], missing[s]))
