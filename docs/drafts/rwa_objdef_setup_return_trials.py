"""23DD00: share the success return across allocation and supplied-table paths."""
from pathlib import Path
s = Path('src/rwa/rwaobjdef.c').read_text()
a = s.index('// match: __rwaObjDefSetupParams')
b = s.index('\n}\n', a) + 3
body = s[a:b]
VS = {'setupreturn_exact': [(s, s)]}
start = body.index('    else\n    {\n')
loop_start = start + len('    else\n    {\n')
loop_end = body.index('\n    }\n    return def;', loop_start)
loops = ''.join(line[4:] if line.startswith('    ') else line
                for line in body[loop_start:loop_end].splitlines(True))
alloc = body[:start]
close = alloc.rfind('    }\n')
early = alloc[:close] + '        return def;\n    }\n\n' + loops + '\n    return def;\n}\n'
VS['setupreturn_early_exit'] = [(body, early)]
