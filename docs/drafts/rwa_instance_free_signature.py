exec(open('docs/drafts/rwa_instance_free_access.py').read())
u=VS['instfreeaccess_4'][0][1]
u=u.replace('rwaInstance *input, void (*release)(void *, void *), void *data)', 'rwaInstance *input, void *callback, void *data)').replace('    rwaInstance *obj = input;', '    void (*release)(void *, void *) = (void (*)(void *, void *))callback;\n    rwaInstance *obj = input;')
VS={'instfreesig':[(s,u)]}
