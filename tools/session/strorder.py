"""strorder.py OBJ UNIT: an object's string literals and __real@ constants in its section order
against the image (config/compiled.txt rows of UNIT): the descents (PLAN M7: a global's
initializer literals come before every function's, so a descent can mark an object boundary)."""
import struct,sys
p=sys.argv[1]; unit=sys.argv[2]
d=open(p,'rb').read()
_,n,_,sp,ns,_,_=struct.unpack_from('<HHIIIHH',d,0)
st=sp+ns*18; i=0; secs={}
while i<ns:
    o=sp+i*18; raw=d[o:o+8]; v,sec,t,c,na=struct.unpack_from('<IhHBB',d,o+8)
    nm=(d[st+struct.unpack_from('<I',raw,4)[0]:d.index(b'\0',st+struct.unpack_from('<I',raw,4)[0])] if raw[:4]==b'\0'*4 else raw.rstrip(b'\0')).decode('latin-1')
    if (nm.startswith('??_C@') or nm.startswith('__real@')) and sec>0: secs.setdefault(sec,nm)
    i+=1+na
img={}
for l in open('config/compiled.txt',encoding='utf-8'):
    q=l.split()
    if len(q)>=3 and q[1].endswith(unit+'.obj'): img[q[2]]=int(q[0],16)
seq=[img[secs[s]] for s in sorted(secs) if secs[s] in img]
for k,(a,b) in enumerate(zip(seq,seq[1:])):
    if b<a: print("descent at", k, hex(a), "->", hex(b))
inv=sum(1 for a,b in zip(seq,seq[1:]) if b<a)
print(len(seq),'literals,',inv,'descents')
