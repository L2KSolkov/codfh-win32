exec(open('docs/drafts/rwa_cache_header_order_trials.py').read());VS={}
old='    client->header[0] = 0;\n    client->header[1] = 0;\n    client->header[2] = 0;'
forms=['    client->header[2] = client->header[1] = client->header[0] = 0;', '    client->header[0] = 0;\n    client->header[2] = client->header[1] = 0;', '    client->header[1] = client->header[0] = 0;\n    client->header[2] = 0;']
for n,f in enumerate(forms):VS['hcstore_%d'%n]=[(s,s+'\n'+d.replace(old,f))]
