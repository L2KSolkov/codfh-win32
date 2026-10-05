"""img2data.py OUT.asm TITLE LO-HI [LO-HI ...]: transcribe image data as a MASM stand-in unit
(PLAN M3: library data the installed libraries do not hold in the image version, repacked byte
for byte, never decompiled).

Each LO-HI range becomes its own segment named after its image section, with a PUBLIC label
`_unk_XXXXXX` at its start (the name match.py resolves to that address) and the bytes as `db`
rows. Pointers inside the data stay bytes: the stand-in only holds its addresses where the
image does (PLAN M7 relinks them from the library objects' own relocations)."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    out_path, title = sys.argv[1], sys.argv[2]
    runs = [tuple(int(x, 16) for x in a.split('-')) for a in sys.argv[3:]]
    img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    body = ['; codfh-match: %s' % title,
            '; An XDK stand-in repacked from the image (PLAN M3: library data the installed',
            '; libraries do not hold in the image version, extracted byte for byte by',
            '; tools/img2data.py, never decompiled).',
            '',
            '        .686p',
            '        .model flat']
    for n, (lo, hi) in enumerate(runs):
        sec = img.section_at(lo)['name']
        data = img.read(lo, hi - lo)
        name = '_unk_%06X' % lo
        body += ['',
                 # (.rdata pieces read-only, so the link merges them into .rdata)
                 "dseg%d SEGMENT BYTE PUBLIC %sALIAS('%s') 'DATA'" % (n, 'READONLY ' if sec == '.rdata' else '', sec),
                 '; // match: %s @ 0x%08X' % (name, lo),
                 'PUBLIC %s' % name,
                 '%s LABEL BYTE' % name]
        for k in range(0, len(data), 16):
            body.append('        db ' + ', '.join('0%02Xh' % b for b in data[k:k + 16]))
        body.append('dseg%d ENDS' % n)
    body += ['', '        END', '']
    open(out_path, 'w', encoding='utf-8', newline='\n').write('\n'.join(body))


if __name__ == '__main__':
    main()
