exec(open('docs/drafts/rwa_stream_unlink_trials.py').read());VS={}
for n in range(12):
 u=s;v=d;helper=''
 if n==0:v=v.replace('sub_23FC00(rwaStream *stream)','sub_23FC00(rwaStream *obj)').replace('    dword_506B38--;','    rwaStream *stream = obj;\n    dword_506B38--;')
 if n==1:v=v.replace('    dword_506B38--;','    RwInt32 count = dword_506B38;\n    dword_506B38 = count - 1;')
 if n==2:u=u.replace('static RwInt32 dword_506B38','RwInt32 dword_506B38')
 if n==3:u=u.replace('static RwInt32 dword_506B38','static volatile RwInt32 dword_506B38')
 if n==4:u=u.replace('void *hSemaphore;','void * volatile hSemaphore;')
 if n in [5,6]:
  helper='static __forceinline void LockStream('+('void **handle' if n==5 else 'void *handle')+') { WaitForSingleObject('+('*handle' if n==5 else 'handle')+', rwaINFINITE); }\n'
  v=v.replace('WaitForSingleObject(hSemaphore, rwaINFINITE);','LockStream('+('&hSemaphore' if n==5 else 'hSemaphore')+');')
 if n in [7,8]:v=v.replace('    dword_506B38--;', '    '+('RwInt32 *count = &dword_506B38; --*count;' if n==7 else '--dword_506B38;'))
 if n>=9:
  helper='static __forceinline void Decrement('+('RwInt32 *count' if n==9 else 'void')+') { '+('--*count;' if n==9 else '--dword_506B38;')+' }\n'
  v=v.replace('dword_506B38--;','Decrement('+('&dword_506B38' if n==9 else '')+');')
 VS['us_%d'%n]=[(s,u+'\n'+h+helper+v)]
