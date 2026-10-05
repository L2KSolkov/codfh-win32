import os
src = open(os.environ['ASRC'], encoding='utf-8').read()
anchor = os.environ['AANCH']
assert src.count(anchor) >= 1
cands = os.environ['ACANDS'].split('|')
VS = {}
for k, c in enumerate(cands):
    ind = anchor[:len(anchor) - len(anchor.lstrip())]
    VS['an%d' % k] = [(anchor, ind + c + '\n' + anchor)]
