"""standindrop.py NAMES_FILE: take the named pieces out of the XDK stand-in sources (src/xdk/standin_*.asm)
once their rows name a library member's function (tools/session/standinmatch.py; PLAN M7).

A piece runs from its `; // match: NAME @` line to the next piece's or its segment's end. A segment
left empty goes, and so does an EXTERN nothing else in the file uses."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
empty_only = sys.argv[1] == '--empty'
# NAMES_FILE lines: OLD [NEW] (NEW: the name the piece's row now has)
newname = {}
if not empty_only:
    for l in open(sys.argv[1], encoding='utf-8'):
        q = l.split()
        if q:
            newname[q[0]] = q[1] if len(q) > 1 else None
names = set(newname)
total = 0
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out, skip, n = [], False, 0
    label_new = {}      # a $L_ label at a removed piece's start -> the piece's new name
    cur, at_start = None, False
    for l in L:
        m = re.match(r'^; // match: (\S+) @ ', l)
        if m:
            skip = m.group(1) in names
            n += skip
            cur, at_start = m.group(1), True
        elif re.match(r'^\w+ ENDS$', l):
            skip = False
        elif skip:
            lm = re.match(r'^(\$L_\w+):$', l)
            if lm:
                if at_start and newname.get(cur):
                    label_new[lm.group(1)] = newname[cur]
                else:
                    print('%s: label %s inside %s' % (os.path.basename(p), lm.group(1), cur))
            elif l.strip() and not l.startswith('PUBLIC ') and not (cur and l.startswith(cur + ':')):
                at_start = False
        if not skip:
            out.append(l)
    if label_new:
        text = '\n'.join(out)
        for lab, nn in label_new.items():
            text = re.sub(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(lab), lambda _m: nn, text)
        out = text.split('\n')
        k = max(i for i, x in enumerate(out) if x.startswith(('EXTERN ', '.model')))
        for nn in sorted(set(label_new.values())):
            out.insert(k + 1, 'EXTERN %s:NEAR' % nn)
    if not n and not empty_only:
        continue
    # empty segments
    res = []
    for l in out:
        if re.match(r'^(\w+) ENDS$', l):
            k = len(res)
            while k and res[k - 1] == '':
                k -= 1
            if k and re.match(r'^%s SEGMENT ' % l.split()[0], res[k - 1]):
                del res[k - 1:]
                if res and res[-1] == '':
                    res.pop()
                continue
        res.append(l)
    body = '\n'.join(x for x in res if not x.startswith('EXTERN '))
    res = [x for x in res if not x.startswith('EXTERN ') or
           re.search(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(x.split()[1].split(':')[0]), body)]
    open(p, 'wb').write('\n'.join(res).replace('\n', nl).encode('utf-8'))
    total += n
    print('%s: %d pieces' % (os.path.relpath(p, ROOT), n))
print(total, 'pieces')
