"""23DF00: separate bitfield clears retain the original OR with EAX=0."""
exec(open('docs/drafts/rwa_objdef_create_current.py').read())
VS = {'initbits_exact': [(s, base + '\n' + d)]}
v = d.replace('    def->unk40.stateSize = 0;\n    def->unk40.stateAlign = 0;',
              '    def->flags = 0;')
VS['initbits_word_clear'] = [(s, base + '\n' + v)]
