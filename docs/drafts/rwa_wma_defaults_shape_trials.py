from pathlib import Path
import re

draft = Path('docs/drafts/rwa_wma_draft.c').read_text()
body = draft[:draft.index('/* The play position')]
anchor = "/* The play queue's read:"
proto = 'extern void RwaStreamNodeGetParams(rwaDecoder *obj, rwaStreamNodeParams *params);'
VS = {}
def add(name, b, extra=[]):
    VS['wmad_' + name] = [(anchor, b + anchor), (proto, proto.replace('void ', 'rwaDecoder *'))] + extra
add('base', body)
call = '    RwaStreamNodeGetParams((rwaDecoder *)obj, (rwaStreamNodeParams *)params);'
stores = body[body.index('    params->unk00'):body.index('\n    return obj;')]
zero = stores[:stores.index('    params->unk04')]
tail = stores[stores.index('    params->unk04'):]
for name, text in [('all', stores), ('zero', zero), ('tail', tail)]:
    for ret in [False, True]:
        helper = 'static __inline ' + ('void *' if ret else 'void') + '\ndefaults_' + name + '(rwaWmaParams *params, rwaWmaSource *obj)\n{\n' + text + ('    return obj;\n' if ret else '') + '}\n\n'
        b = body.replace(text, ('    return ' if ret else '    ') + 'defaults_' + name + '(params, obj);\n')
        if ret:
            if name != 'tail' and name != 'all':
                continue
            b = b.replace('\n    return obj;', '')
        add(name + '_helper' + str(int(ret)), helper + b)
add('void_pointer', body.replace('rwaWmaParams *params)', 'rwaWmaParams *arg)\n').replace('{\n    RwaStreamNodeGetParams', '{\n    rwaWmaParams *params = arg;\n    RwaStreamNodeGetParams'))
add('out_volatile', body.replace('rwaWmaParams *params)', 'rwaWmaParams *arg)').replace('{\n    RwaStreamNodeGetParams', '{\n    volatile rwaWmaParams *params = arg;\n    RwaStreamNodeGetParams'))
add('chain_ones', body.replace('    params->unk04 = 1;\n    params->fileType = 1;', '    params->fileType = params->unk04 = 1;'))
add('chain_int_zeros', body.replace(zero, '    params->yieldRate = params->unk48 = params->unk50 = params->unk54 = params->unk4C = params->unk28 = params->unk20 = params->unk1C = params->unk24 = params->unk38 = params->unk34 = params->unk00 = 0;\n    params->file = NULL;\n'))
for slot in ['before_call', 'after_call', 'before_ones']:
    b = body.replace('{\n', '{\n    RwUInt32 one;\n', 1)
    target = call if slot.endswith('call') else '    params->unk04 = 1;'
    if slot == 'after_call': b = b.replace(call, call+'\n    one = 1;')
    else: b = b.replace(target, '    one = 1;\n'+target)
    b = b.replace('params->unk04 = 1;', 'params->unk04 = one;').replace('params->fileType = 1;', 'params->fileType = one;')
    add('local_' + slot, b)
for split in [1, 6, 13]:
    lines = stores.splitlines(True)
    b = body.replace(stores, '    {\n' + ''.join(lines[:split]) + '    }\n    {\n' + ''.join(lines[split:]) + '    }\n')
    add('blocks_' + str(split), b)
