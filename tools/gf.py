"""gf.py TOOL [JSON-ARGS] [PORT]: call a read-only IDA MCP tool on another
instance (default 13339, ears_godfather_r.xbe) and print its text."""
import json
import sys
import urllib.request

READONLY = {'server_health', 'lookup_funcs', 'decompile', 'disasm', 'list_funcs', 'xrefs_to',
            'find', 'find_regex', 'search_text', 'get_bytes', 'get_int', 'get_string',
            'list_globals', 'read_struct', 'search_structs', 'type_inspect', 'type_query',
            'func_profile', 'basic_blocks', 'callees', 'func_query', 'entity_query',
            'stack_frame', 'imports', 'get_global_value', 'xref_query', 'insn_query'}
tool = sys.argv[1]
if tool not in READONLY:
    sys.exit('refusing non-read-only tool %s' % tool)
args = json.loads(sys.argv[2]) if len(sys.argv) > 2 else {}
port = int(sys.argv[3]) if len(sys.argv) > 3 else 13339
req = urllib.request.Request('http://127.0.0.1:%d/mcp' % port, data=json.dumps(
    {'jsonrpc': '2.0', 'id': 1, 'method': 'tools/call', 'params': {'name': tool, 'arguments': args}}).encode(),
    headers={'Content-Type': 'application/json'})
r = json.loads(urllib.request.urlopen(req, timeout=120).read())
for c in r.get('result', {}).get('content', []):
    t = c.get('text', '')
    try:
        o = json.loads(t)
        if isinstance(o, dict) and 'code' in o:
            print(o['code'])
            continue
        if isinstance(o, list) and o and isinstance(o[0], dict) and 'code' in o[0]:
            for x in o:
                print(x.get('code') or x)
            continue
    except Exception:
        pass
    print(t)
if 'error' in r:
    print(r['error'])
