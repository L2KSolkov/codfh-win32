"""23DE20: a 16-bit index and branch-local tables recover the entire helper."""
exec(open('docs/drafts/rwa_objdef_create_current.py').read())
a = d.index('// match: _sub_23DE20')
b = d.index('// match: _sub_23DF00', a)
body = d[a:b]
VS = {}
for n in range(4):
    v = body
    if n & 1:
        v = v.replace('    RwUInt16        i;', '    RwUInt32        i;')
    if n & 2:
        v = v.replace('            rwaParamTables *tables = (rwaParamTables *)def->interfaces;\n', '')
        v = v.replace('    if (io == 1)',
                      '    rwaParamTables *tables = (rwaParamTables *)def->interfaces;\n\n'
                      '    if (io == 1)', 1)
    VS['defaults_recovery_%d' % n] = [(s, base + '\n' + d[:a] + v + d[b:])]
