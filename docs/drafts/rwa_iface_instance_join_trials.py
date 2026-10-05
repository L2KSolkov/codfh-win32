exec(open('docs/drafts/rwa_iface_instance_trials.py').read());base=VS['ii_3'][0][1];VS={}
for n in range(8):
 u=base
 a=u.index('// match: _sub_243FF0');pre=u[:a];u=u[a:]
 if n&1:u=u.replace('        return NULL;', '        goto fail;')
 if n&2:
  u=u.replace('    objInterface->link.prev = head;\n    objInterface->link.next = head->next;', '    objInterface->link.next = head->next;\n    objInterface->link.prev = head;')
 if n&4:
  u=u.replace('    n = ((rwaParamTables *)objDef->interfaces)->noInputs;\n    count = def->noInputs;', '    count = def->noInputs;\n    n = ((rwaParamTables *)objDef->interfaces)->noInputs;')
 VS['ijoin_%d'%n]=[(s,pre+u)]
