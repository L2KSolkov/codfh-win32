"""The eight-byte memset fixes the creator's allocation and register lifetimes."""
exec(open('docs/drafts/rwa_objdef_create_current.py').read())
VS = {}
forms = [
    '        memset(def->unk50, 0, sizeof(rwaLink));',
    '        ((rwaLink *)def->unk50)->next = NULL;\n'
    '        ((rwaLink *)def->unk50)->prev = NULL;',
    '        { rwaLink *links = (rwaLink *)def->unk50;\n'
    '          links->next = NULL;\n'
    '          links->prev = NULL; }',
]
for i, form in enumerate(forms):
    v = d.replace(forms[0], form)
    VS['createclear_%d' % i] = [(s, base + '\n' + v)]
