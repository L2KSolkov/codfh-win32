"""Reproduce 2026-10-01 MatrixOrthoNormalize/RwStreamSkip source trials.

Run from the repository root:
  python tools/session/pscore.py docs/drafts/rw_matrix_stream_trials.py _MatrixOrthoNormalize 0x2A48C0 src/rw/src/plcore/bamatrix.c
For RwStreamSkip set environment variable RW_TRIAL=stream and substitute
_RwStreamSkip 0x2A7210 src/rw/src/plcore/bastream.c.

These are candidate substitutions, not matched source. Best candidates retain
the original mismatch. Byte comparison is authoritative; pscore also counts
padding and jump-table disassembly and is only a ranking aid.
"""
import os
from itertools import permutations
from pathlib import Path

VS = {'baseline': []}
if os.environ.get('RW_TRIAL') == 'stream':
    s = Path('src/rw/src/plcore/bastream.c').read_text()
    start = s.index('RwStreamSkip(RwStream *stream, RwUInt32 offset)')
    end = s.index('\n}\n', start) + 3
    body = s[start:end]
    for i, expr in enumerate([
        'offset + smpMem->position',
        '(RwUInt32)((RwInt32)smpMem->position + (RwInt32)offset)',
        'smpMem->position - (0U - offset)',
        'offset - (0U - smpMem->position)',
    ]):
        VS['stream_expr%d' % i] = [(body, body.replace('smpMem->position + offset', expr))]
    for i, expr in enumerate(['offset += smpMem->position',
                              'offset = smpMem->position + offset',
                              'offset = offset + smpMem->position']):
        b = body.replace('if (smpMem->position + offset > smpMem->nSize)',
                         'if ((%s) > smpMem->nSize)' % expr)
        b = b.replace('smpMem->position += offset;\n                stream->position += offset;',
                      'stream->position += offset - smpMem->position;\n                smpMem->position = offset;')
        VS['stream_param%d' % i] = [(body, b)]
else:
    calls = [('RwV3dCrossProductMacro(vpW, vpU, vpV);', 'vpW', 'vpU', 'vpV'),
             ('RwV3dCrossProductMacro(vpV, vpW, vpU);', 'vpV', 'vpW', 'vpU')]
    for ci, (old, o, a, b) in enumerate(calls):
        for mode in ['swap', 'cast']:
            for mask in range(64):
                expr = []
                for i, (j, k) in enumerate([('y', 'z'), ('z', 'x'), ('x', 'y')]):
                    terms = []
                    for n, (u, v) in enumerate([(j, k), (k, j)]):
                        aa, bb = '%s->%s' % (a, u), '%s->%s' % (b, v)
                        chosen = mask & (1 << (i * 2 + n))
                        term = '(%s * %s)' % ((bb, aa) if chosen and mode == 'swap' else (aa, bb))
                        terms.append('(RwReal)' + term if chosen and mode == 'cast' else term)
                    expr.append('%s->%s = %s - %s;' % (o, 'xyz'[i], *terms))
                VS['matrix_%d_%s_%02d' % (ci, mode, mask)] = [(old, '{ ' + ' '.join(expr) + ' }')]
    old = '_rwV3dNormalizeMacro(recip, vpW, vpW);'
    for order in permutations('xyz'):
        for mode in range(4):
            init = 'RwReal length2 = RwV3dDotProductMacro(vpW, vpW); rwInvSqrtMacro(&recip, length2); '
            if mode == 0:
                scale = ' '.join('vpW->%s *= recip;' % c for c in order)
            elif mode == 1:
                scale = ' '.join('vpW->%s = recip * vpW->%s;' % (c, c) for c in order)
            elif mode == 2:
                scale = 'RwV3d scaled; ' + ' '.join('scaled.%s = vpW->%s * recip;' % (c, c) for c in order) + ' *vpW = scaled;'
            else:
                scale = 'RwV3d copy = *vpW; ' + ' '.join('vpW->%s = copy.%s * recip;' % (c, c) for c in order)
            VS['matrix_norm_' + ''.join(order) + str(mode)] = [(old, '{ ' + init + '{ ' + scale + ' } }')]
    for order in permutations(['right', 'up', 'at', 'pos']):
        VS['matrix_decl_' + '_'.join(order)] = [('RwV3d               right, up, at, pos;', 'RwV3d ' + ', '.join(order) + ';')]
    for order in permutations(['vpU', 'vpV', 'vpW']):
        VS['matrix_ptr_' + '_'.join(order)] = [('RwV3d              *vpU, *vpV, *vpW;', 'RwV3d *' + ', *'.join(order) + ';')]
