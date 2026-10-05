exec(open('docs/drafts/rwa_voice_priority_current.py').read())
base=VS['vmcurrent_7'][0][1];VS={}
for n in range(16):
 u=base
 if n&1:
  a=u.index('            if (!(distance <');b=u.index('\n        }\n        else',a)
  v=u[a:b];calc=v[v.index('                RwReal  beyond'):v.index('\n            }\n            else')]
  u=u[:a]+'            if (distance < rwaReal(minDistanceBits))\n            {\n                volume = 1.0f;\n            }\n            else\n            {\n'+calc+'\n            }'+u[b:]
 if n&2:u=u.replace('RwReal      prevPriority;', 'RwUInt32 prevPriorityBits;').replace('prevPriority = (rwaLink *)prev == &dword_5069C0 ? -1.0f : rwaReal(prev->unk80);', 'prevPriorityBits = (rwaLink *)prev == &dword_5069C0 ? 0xBF800000 : prev->unk80;').replace('priority < prevPriority', 'priority < rwaReal(prevPriorityBits)')
 if n&4:
  a=u.index('// match: _sub_23E980');b=u.index('// match: _sub_23EE70');v=u[a:b]
  v=v.replace('    rwaReal(sound->unk80) = 0.0f;', '    RwUInt8 one = 1;\n    rwaReal(sound->unk80) = 0.0f;',1).replace('sound->flags & 1', 'sound->flags & one').replace('sound->flags |= 1', 'sound->flags |= one')
  u=(u[:a]+v+u[b:]).replace('if (_exp & 1)', 'if (_exp & one)')
 if n&8:u=u.replace('distance = dx * dx + dy * dy + dz * dz;', 'distance = dy * dy + dx * dx + dz * dz;')
 VS['vmshape_%d'%n]=[(s,u)]
