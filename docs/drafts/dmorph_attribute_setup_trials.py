"""Delta-morph buffer setup probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Unmatched.
"""
exec(open('docs/drafts/dmorph_buffer_init_trials.py').read())
VS={}
for mask in range(16):
 t=body
 if mask&1:
  a=t.index('        if ((flags & rxGEOMETRY_TEXTURED)');b=t.index('        if (reinstance)',a)
  t=t[:a]+'''        if (flags & (rxGEOMETRY_TEXTURED | rpGEOMETRYTEXTURED2))
        {
            numTexCoordSets = geometry->numTexCoordSets;
            texCoordSets = geometry->texCoords;
        }
        else
        {
            numTexCoordSets = 0;
            texCoordSets = NULL;
        }

'''+t[b:]
 for bit,cond,n,expr in [(2,'flags & rxGEOMETRY_NORMALS','normals','geometry->morphTarget->normals'),(4,'flags & rxGEOMETRY_PRELIT','color','RpGeometryGetPreLightColors(geometry)'),(8,'reinstance','lockedSinceLastInst','geometry->lockedSinceLastInst')]:
  if mask&bit:
   a=t.index('        if ('+cond+')');b=t.index('\n        }',t.index('        else',a))+10
   t=t[:a]+'        '+n+' = ('+cond+') ? '+expr+' : '+('rpGEOMETRYLOCKALL' if bit==8 else 'NULL')+';'+t[b:]
 VS['ba_%02d'%mask]=[(anchor,t+anchor),inc]
