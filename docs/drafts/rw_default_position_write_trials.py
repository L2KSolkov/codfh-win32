"""Parked default-instance probes. pscore target: __rpXboxDefaultInstance
0x2DED60 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. No candidate matches.
"""
exec(open('docs/drafts/rw_default_position_block_trials.py').read())
VS={}
for k in range(12):
 order=list(range(6));order=order[k%6:]+order[:k%6]
 if k>=6:order.reverse()
 ts=types[:];ts[3]='RwUInt8 **buffer'
 c=chunk.replace('lockedVertexBuffer','(*buffer)')
 h='static __forceinline void PositionWriteTrial('+', '.join(ts[i] for i in order)+') {\n'+c+'}\n'
 ns=names[:];ns[3]='&lockedVertexBuffer'
 call='    PositionWriteTrial('+', '.join(ns[i] for i in order)+');\n'
 VS['dw_%02d'%k]=[(anchor,h+body[:a]+call+body[b:]+anchor)]
