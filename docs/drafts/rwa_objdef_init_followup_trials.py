"""Initializer's missing OR survives the usual field-zero and mask forms."""
exec(open('docs/drafts/rwa_objdef_create_current.py').read())
VS = {}
for n in range(6):
    v = d.replace('    def->unk40.stateSize = 0;\n    def->unk40.stateAlign = 0;',
                  '    def->flags = 0;')
    if n == 1:
        v = v.replace('    def->flags = 0;',
                      '    memset(&def->flags, 0, sizeof(def->flags));')
    if n == 2:
        v = v.replace('    def->flags = 0;',
                      '    *(volatile RwUInt32 *)&def->flags = 0;')
    if n == 3:
        v = v.replace('    rwaObjDefSetStateAlignment(def, 1);',
                      '    def->flags = (def->flags & 0x0FFFFFFF) | (rwaLog2(1) << 28);')
    if n == 4:
        v = v.replace('    rwaObjDefSetStateAlignment(def, 1);',
                      '    *(volatile RwUInt32 *)&def->flags |= rwaLog2(1) << 28;')
    if n == 5:
        v = v.replace('    def->flags = 0;\n    def->instances = NULL;\n'
                      '    rwaObjDefSetStateAlignment(def, 1);',
                      '    { RwUInt32 *flags = &def->flags;\n'
                      '      *flags = 0;\n      def->instances = NULL;\n'
                      '      *flags |= rwaLog2(1) << 28; }')
    VS['createinit_%d' % n] = [(s, base + '\n' + v)]
