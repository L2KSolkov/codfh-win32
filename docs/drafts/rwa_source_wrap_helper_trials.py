exec(open('docs/drafts/rwa_source_wrap_shape_trials.py').read());v=VS['wraps_5'][0][1];VS={}
old='''            count = size % unit;
            sub_2420D0(size % unit, 0xFFFFFFFF / unit, &high, &count);
            if (++count > result)'''
for n in range(8):
 h='static __forceinline RwUInt32 wrapCount('+('RwUInt32 unit, RwUInt32 size' if n&1 else 'RwUInt32 size, RwUInt32 unit')+') { RwUInt32 high; RwUInt32 count = size % unit; sub_2420D0(size % unit, 0xFFFFFFFF / unit, &high, &count); return '+('++count' if n&2 else 'count')+'; }\n'
 u=v.replace('// match: _sub_247F20',h+'// match: _sub_247F20').replace(old,'            count = wrapCount('+('unit, size' if n&1 else 'size, unit')+');\n            if ('+('count' if n&2 else '++count')+' > result)')
 if n&4:u=u.replace('return ++count;', 'return count + 1;')
 VS['wraph_%d'%n]=[(s,u)]
