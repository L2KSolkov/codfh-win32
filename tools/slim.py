# slim.py UNIT FRAGMENT OUT: the unit's preamble (up to its first match
# comment), its later file-scope declarations (multi-line ones too), then the
# fragment, for fast local_names/trial runs.
import sys
u = open(sys.argv[1], encoding='utf-8').read()
f = open(sys.argv[2], encoding='utf-8').read()
i = u.index('// match:')
decls = []
depth = 0
pending = None
for line in u[i:].split('\n'):
    if pending is not None:
        pending.append(line)
        if line.rstrip().endswith(';'):
            decls.extend(pending)
            pending = None
        elif '{' in line:
            pending = None
    elif (depth == 0 and line and not line[0].isspace() and not line.startswith(('//', '#', '{', '}'))):
        if line.rstrip().endswith(';'):
            decls.append(line)
        elif line.rstrip().endswith(',') or line.rstrip().endswith('('):
            pending = [line]
    depth += line.count('{') - line.count('}')
open(sys.argv[3], 'w', encoding='utf-8', newline='\n').write(u[:i] + '\n'.join(decls) + '\n' + f)
