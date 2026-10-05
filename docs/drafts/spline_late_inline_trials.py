"""SplinePath destructor compiler probes. pscore target
??1SplinePath@@UAE@XZ 0xBA030 src/recovered/unit_0B9EA0.cpp.
No match; scratch inline functions are diagnostic only.
"""
exec(open('docs/drafts/spline_empty_eh_trials.py').read())
VS={}
for n in range(4):
 decl='inline void SplineCleanupTrial();\n'
 definition='inline void SplineCleanupTrial() {}\n'
 hh=h.replace(old,'    ~SplinePath() { SplineCleanupTrial(); }')
 if n&1:definition='__forceinline void SplineCleanupTrial() {}\n';decl='__forceinline void SplineCleanupTrial();\n'
 if n&2:
  hh=hh.replace('SplineCleanupTrial();','SplineCleanupTrial(this);')
  decl=decl.replace('();','(SplinePath *);');definition=definition.replace('()','(SplinePath *)')
  decl='struct SplinePath;\n'+decl
 VS['sl_%d'%n]=[('#include "types/SplinePath.h"',decl+hh+'\n'+definition)]
