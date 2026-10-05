"""SplinePath destructor compiler probes. pscore target
??1SplinePath@@UAE@XZ 0xBA030 src/recovered/unit_0B9EA0.cpp.
No match; scratch inline functions are diagnostic only.
"""
from pathlib import Path
s=Path('src/recovered/unit_0B9EA0.cpp').read_text();h=Path('include/types/SplinePath.h').read_text()
old='    ~SplinePath()\n    {\n    }'
assert old in h
forms={'base':old,'throwempty':'    ~SplinePath() throw() {}','throwint':'    ~SplinePath() throw(RwInt32) {}','tryempty':'    ~SplinePath() try {} catch (...) {}','tryrethrow':'    ~SplinePath() try {} catch (...) { throw; }','assumetrue':'    ~SplinePath() { __assume(1); }','assumethis':'    ~SplinePath() { __assume(this != 0); }','sizeofcall':'    ~SplinePath() { sizeof(sub_143D60(this)); }','trybody':'    ~SplinePath() { try {} catch (...) { throw; } }'}
VS={}
for n,f in forms.items():
 # Declaration required for the unevaluated expression probe.
 hh=h.replace('struct SplinePath :','struct SplinePath; RwUInt32 sub_143D60(SplinePath *);\nstruct SplinePath :',1).replace(old,f)
 VS['sp_'+n]=[('#include "types/SplinePath.h"',hh)]
