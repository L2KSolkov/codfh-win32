"""Historical DMorph reference draft and key ablations, superseded by production.

Use the pre-placement source at b7167fc7a to reproduce these trials.

python tools/session/pscore.py docs/drafts/dmorph_reference_trials.py \
    _XboxDmorphAtomicInstanceCallback 0x2F28D0 \
    src/rw/plugin/dmorph/xbox/dmorphpipeg.c -j 4

The best source is the reference variant. Scores include jump-table artifacts;
tools/match.py remains authoritative. No production file is modified.
"""
from pathlib import Path
import re

src = Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text()
anchor = re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*', src)[0]
draft = Path('docs/drafts/dmorph_instance_reference_followup.c').read_text()
body = draft[draft.index('typedef struct _BlockInfo'):]
inc = ('#include "xbpipe.h"', '#include "xbpipe.h"\n#include "xbvtxfmt.h"')


def variant(text):
    return [(anchor, text + anchor), inc]


VS = {'dm_reference': variant(body)}
conditional = ('        numTexCoordSets = ((flags & rxGEOMETRY_TEXTURED) || '
               '(flags & rpGEOMETRYTEXTURED2)) ? geometry->numTexCoordSets : 0;')
assert conditional in body
separate = '''        if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2))
        {
            numTexCoordSets = geometry->numTexCoordSets;
        }
        else
        {
            numTexCoordSets = 0;
        }'''
VS['dm_separate_texture_count'] = variant(body.replace(conditional, separate))
signed = '            RwInt32             size;'
assert body.count(signed) == 1
VS['dm_unsigned_position_size'] = variant(body.replace(signed, signed.replace('RwInt32', 'RwUInt32')))

locks = re.compile(r'D3DVertexBuffer_Lock\(([^;]+), 0, vbSize, &(lockedVertexBuffer(?:Static)?), 0\);')
direct, n = locks.subn(lambda m: m[2] + ' = D3DVertexBuffer_Lock2(' + m[1] + ', 0);', body)
assert n == 4, n
VS['dm_direct_locks'] = variant(direct)

without_shift = body.replace('                                            RwInt32 shift;\n', '')
shift = re.compile(r'shift = \(RwInt32\)\(([^;]+)\);\n +color\[k\]\.(red|green|blue|alpha) \+= \(RwUInt8\)shift;')
without_shift, n = shift.subn(lambda m: 'color[k].' + m[2] + ' += (RwUInt8)(' + m[1] + ');', without_shift)
assert n == 4, n
VS['dm_direct_color_cast'] = variant(without_shift)
