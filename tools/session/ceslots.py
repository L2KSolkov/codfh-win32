import os, re, subprocess, sys
S=os.path.dirname(os.path.abspath(__file__))
obj = sys.argv[1] if len(sys.argv) > 1 else 'build/src/recovered/unit_1CCC00.obj'
img=subprocess.run([sys.executable,'tools/xdis.py','0x1CE650','0x1CF716'],capture_output=True,text=True).stdout
ours=subprocess.run([sys.executable,S+'/objdis.py',obj,'?sub_1CE650@type_4F8054_B0@@QAEHHHHPAUtype_1F8560@@H@Z'],capture_output=True,text=True).stdout
def slots(t):
    s=[]
    for m in re.finditer(r'\[ebp - (0x[0-9a-f]+)\]',t):
        v=int(m.group(1),16)
        if v not in s: s.append(v)
    return s
a=slots(img); b=slots(ours)
for i in range(max(len(a),len(b))):
    x = hex(a[i]) if i < len(a) else '-'; y = hex(b[i]) if i < len(b) else '-'
    print(i, x, y, '' if x == y else '<<')
