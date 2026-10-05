exec(open('docs/drafts/rwa_iface_instance_join_trials.py').read());b=VS['ijoin_6'][0][1];VS={}
a=b.index('    if (allocFunc)',b.index('// match: _sub_243FF0'));z=b.index('    objInterface->setters',a)
part=b[a:z]
# Move the fallback allocation behind the common return with an explicit join.
for n in range(4):
 u=b
 first=part[:part.index('    else')]
 alt=part[part.index('    else'):]
 alt=alt[alt.index('{')+1:alt.rfind('}')]
 common=first.replace('    if (allocFunc)','    if (!allocFunc) goto allocate;\n') if False else first
 body=first[first.index('{')+1:first.rfind('}')]
 u=u[:a]+'    if (!allocFunc) goto allocate;\n'+body+'initialize:\n'+u[z:]
 pos=u.index('  fail:',a)
 u=u[:pos]+'allocate:\n'+alt+'    goto initialize;\n\n'+u[pos:]
 if n&1:u=u.replace('    if (!allocFunc) goto allocate;', '    if (allocFunc) goto supplied;\n    goto allocate;\nsupplied:')
 if n&2:u=u.replace('            goto fail;', '            return NULL;')
 VS['ilayout_%d'%n]=[(s,u)]
