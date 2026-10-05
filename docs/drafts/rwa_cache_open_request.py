exec(open('docs/drafts/rwa_cache_open_current.py').read())
VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('        case 2:\n', '        case 2:\n        { rwaCacheRequest *request = &client->request;\n').replace('client->request.', 'request->').replace('            break;', '            break;\n        }')
 if n&2:u=u.replace('            client->request.state = 1;\n','').replace('            request->state = 1;\n','').replace('            client->mode = 1;', '            '+('request->state' if n&1 else 'client->request.state')+' = client->mode = 1;')
 if n&4:u=u.replace('            client->data = data;', '').replace('            client->callback = callback;', '            client->callback = callback;\n            client->data = data;')
 VS['cacheopenrequest_%d'%n]=[(s,s+'\n'+u)]
