"""Release pointer lifetime: baseline 6, clear pointer 2, shared pointer exact."""
from pathlib import Path

production = Path('src/rwa/unit_243670.c').read_text()
start = production.index('// match: _sub_2437A0')
end = production.index('// match: _sub_243880', start)
base = production[:start] + production[end:]
draft = Path('docs/drafts/rwa_freelist_draft.c').read_text()
draft = draft[draft.index('// match: _sub_2437A0'):]
pointer = draft.replace('            rwaLink    *first;',
                        '            rwaLink    *first;\n            RwUInt8 *heap;')
pointer = pointer.replace('            block->bitmap[byte]',
                          '            heap = block->bitmap;\n            heap[byte]')
shared = pointer.replace('used += block->bitmap[i];', 'used += heap[i];')
VS = {name: [(production, base + '\n' + body)] for name, body in
      [('flrelease_base', draft), ('flrelease_clear', pointer),
       ('flrelease_shared', shared)]}
