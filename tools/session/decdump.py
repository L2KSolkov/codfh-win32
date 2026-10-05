"""decdump.py LO HI OUT: decompile every symbols.txt function in [LO, HI) from the
main IDA (port 13337, read-only decompile) into OUT."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import json
import sys
import urllib.request

lo, hi, out = int(sys.argv[1], 16), int(sys.argv[2], 16), sys.argv[3]
rows = []
for l in open(_os_repo.path.join(_REPO, r'config\symbols.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function':
        a = int(p[0], 16)
        if lo <= a < hi:
            rows.append((a, int(p[2], 16), p[4]))


def call(tool, args):
    req = urllib.request.Request('http://127.0.0.1:13337/mcp', data=json.dumps(
        {'jsonrpc': '2.0', 'id': 1, 'method': 'tools/call', 'params': {'name': tool, 'arguments': args}}).encode(),
        headers={'Content-Type': 'application/json'})
    r = json.loads(urllib.request.urlopen(req, timeout=120).read())
    return ''.join(c.get('text', '') for c in r['result']['content'])


with open(out, 'w', encoding='utf-8') as f:
    for a, n, name in rows:
        t = call('decompile', {'addr': hex(a), 'include_addresses': False})
        try:
            code = json.loads(t).get('code') or t
        except Exception:
            code = t
        f.write('==== 0x%08X 0x%08X %s\n%s\n' % (a, a + n, name, code))
print(len(rows))
