from pathlib import Path
s=Path('src/rwa/unit_24CC50.c').read_text();d=Path('docs/drafts/rwa_splitter_draft.c').read_text().split('/* A track')[0].replace('static rwaSplitter *','rwaSplitter *');VS={}
one='                if (mode == 1)\n                {\n                    obj->state.node.status = 3;\n                }'
for n in range(8):
 u=d
 a=u.index('            case 7:');head=u[:a];tail=u[a:]
 if n&1:head=head.replace(one,'                goto check_one;');tail=tail.replace(one,'check_one:\n'+one,1)
 if n&2:tail=tail.replace('                    obj->state.node.status = 4;', '                    obj->state.node.status = 4;\n                    goto check_one;') if n&1 else tail
 if n&4:
  head=head.replace('                    obj->state.node.status = 4;','                    goto status_four;')
  tail=tail.replace('            case 8:', 'status_four:\n                obj->state.node.status = 4;\n                break;\n            case 8:')
 VS['splitforward_%d'%n]=[(s,s+'\n'+head+tail)]
