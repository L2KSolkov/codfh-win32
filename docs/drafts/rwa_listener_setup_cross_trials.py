exec(open('docs/drafts/rwa_listener_setup_chain_trials.py').read())
best=VS['lsetc_07_0'][0][1]
VS={}
old='''    listener->right.x = listener->up.y - listener->up.z * 0.0f;
    listener->right.y = listener->up.z * 0.0f - listener->up.x;
    listener->right.z = listener->up.x * 0.0f - listener->up.y * 0.0f;'''
full='''    listener->right.x = listener->up.y * listener->at.z - listener->up.z * listener->at.y;
    listener->right.y = listener->up.z * listener->at.x - listener->up.x * listener->at.z;
    listener->right.z = listener->up.x * listener->at.y - listener->up.y * listener->at.x;'''
for kind in range(4):
    expr=full
    if kind==1:expr=expr.replace('listener->at.z','1.0f').replace('listener->at.x','0.0f').replace('listener->at.y','0.0f')
    if kind==2:expr=expr.replace('listener->at.z','v.y').replace('listener->at.x','v.x').replace('listener->at.y','v.z')
    if kind==3:expr=full.replace('listener->up.', 'v.')
    VS['lsetx_%d'%kind]=[(src,best.replace(old,expr))]
