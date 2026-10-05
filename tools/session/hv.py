"""hv.py FILE OLD NEW SRC SYM ADDR: apply a header edit, build SRC, print odiff count, revert."""
import os, sys, subprocess, shutil
f, old, new, src, sym, addr = sys.argv[1:7]
t = open(f, encoding='utf-8').read()
assert old in t, 'old missing'
shutil.copy(f, f + '.hvbak')
open(f, 'w', encoding='utf-8').write(t.replace(old, new, 1))
try:
    r = subprocess.run([sys.executable, "tools/build_sources.py", src], capture_output=True, text=True)
    if "compile error" in r.stdout: print("COMPILE ERROR"); sys.exit()
    obj = 'build/' + src.rsplit('.', 1)[0] + '.obj'
    out = subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'odiff.py'), obj, sym, addr], capture_output=True, text=True).stdout
    print(sum(1 for l in out.split('\n') if l.startswith(' -') or l.startswith(' +')))
    if len(sys.argv) > 7: print(out)
finally:
    shutil.move(f + '.hvbak', f)
