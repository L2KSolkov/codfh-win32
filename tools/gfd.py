"""gfd.py ADDR [N] [PORT]: plain disassembly listing from a Godfather instance."""
import json, subprocess, sys, os
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

addr = sys.argv[1]; n = int(sys.argv[2]) if len(sys.argv) > 2 else 80
port = sys.argv[3] if len(sys.argv) > 3 else '13340'
out = subprocess.run([sys.executable, os.path.join(S, 'gf.py'), 'disasm',
                      json.dumps({'addr': addr, 'max_instructions': n}), port], capture_output=True, text=True).stdout
d = json.loads(out)
for l in d['asm']['lines']:
    print('%s  %s%s' % (l['addr'], l['instruction'], ('   ; ' + l['comment']) if l.get('comment') else ''))
