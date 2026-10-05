exec(open('docs/drafts/rwa_streamcache_open_trials.py').read())
base=VS['so_0'][0][1]
VS={}
for n in range(3):
 u=base.replace('static __forceinline void ClientInit(', 'static __forceinline rwaCacheClient *ClientInit(').replace(init+'}',init+'    return client;\n}')
 u=u.replace('            ClientInit(client, holder, callback, data);\n','')
 if n==0:u=u.replace('_RtFSManagerFOpen(name, 0x11, sub_244B40, client);','_RtFSManagerFOpen(name, 0x11, sub_244B40, ClientInit(client, holder, callback, data));')
 if n==1:u=u.replace('_RtFSManagerFOpen(name, 0x11, sub_244B40, client);','{ rwaCacheClient *initialized = ClientInit(client, holder, callback, data);\n            _RtFSManagerFOpen(name, 0x11, sub_244B40, initialized); }')
 if n==2:u=u.replace('_RtFSManagerFOpen(name, 0x11, sub_244B40, client);','client = ClientInit(client, holder, callback, data);\n            _RtFSManagerFOpen(name, 0x11, sub_244B40, client);')
 VS['so_ret%d'%n]=[(s,u)]
