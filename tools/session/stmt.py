import os
A = os.environ['AANCH']
forms = os.environ['AFORMS'].split('|')
VS = {'st%d' % k: [(A, f)] for k, f in enumerate(forms)}
