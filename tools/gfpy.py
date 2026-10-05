"""gfpy.py FILE [PORT]: run a READ-ONLY IDAPython snippet on another instance.
Refuses snippets that look like they modify the database."""
import json, re, sys, urllib.request
code = open(sys.argv[1], encoding='utf-8').read()
bad = re.compile(r'\b(set_|patch|rename|del_|add_|create_|apply_|make_|op_|save|undefine|define|put_|idc\.Set|MakeName|SetType|ida_bytes\.put)', re.I)
if bad.search(code):
    sys.exit('refusing: snippet looks like it writes')
port = int(sys.argv[2]) if len(sys.argv) > 2 else 13339
req = urllib.request.Request('http://127.0.0.1:%d/mcp' % port, data=json.dumps(
    {'jsonrpc': '2.0', 'id': 1, 'method': 'tools/call', 'params': {'name': 'py_eval', 'arguments': {'code': code}}}).encode(),
    headers={'Content-Type': 'application/json'})
r = json.loads(urllib.request.urlopen(req, timeout=300).read())
for c in r.get('result', {}).get('content', []):
    t = c.get('text', '')
    try:
        o = json.loads(t)
        print(o.get('stdout', '') or '', o.get('result', '') or '', o.get('stderr', '') or '')
    except Exception:
        print(t)
print(r.get('error', ''))
