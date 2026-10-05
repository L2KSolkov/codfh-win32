"""dataalign.py [--write]: the 16-byte alignment fill in the image's .data (PLAN M7).

The image's .data has zero gaps of under 16 bytes before some 16-aligned rows (libcmt: exsup's
__NLG_Destination, throw's, the math functions' names): the original link met an empty
16-aligned .data section of a MASM object there (memset's), in its object order. The M7 probe
lays .data out by address (.data$ADDR), so those empty sections no longer fall in place.
Read from the probe's map (build/m7/game.map): a keyed .data group at a 16-aligned address
that lies closer to the previous group than in the image gets an empty PARA-aligned section
named `.data$KEY` (KEY: its address minus one) in src/xbe/dataalign.asm, sorting just before
it. The keys accumulate (the file's own are kept); rerun the probe after --write."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ASM = os.path.join(ROOT, 'src', 'xbe', 'dataalign.asm')
groups = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), encoding='utf-8', errors='replace'):
    m = re.match(r'\s*([0-9a-f]{4}):([0-9a-f]{8}) ([0-9a-f]{8})H \.data\$([0-9A-F]{8})\s', l)
    if m:
        groups.append((int(m.group(4), 16), int(m.group(2), 16), m.group(1)))
have = set()
if os.path.exists(ASM):
    have = set(int(x, 16) + 1 for x in re.findall(r"ALIAS\('\.data\$([0-9A-F]{8})'\)", open(ASM).read()))
new = set()
for (k0, o0, s0), (k1, o1, s1) in zip(groups, groups[1:]):
    if s0 == s1 and k1 % 16 == 0 and (o1 - o0) < (k1 - k0) and k1 not in have:
        new.add(k1)
for k in sorted(new):
    print('0x%08X' % k)
print(len(new), 'new,', len(have), 'kept')
if '--write' in sys.argv:
    # (and .data's first row, 0x427400: the gap after the .XAPI$ tables before it)
    keys = sorted(have | new | {0x427400})
    out = ['; codfh-match: the 16-byte alignment fill in .data (PLAN M7, tools/session/dataalign.py)',
           '; Empty PARA-aligned sections, each sorting just before the 16-aligned row the image pads',
           '; to: the empty 16-aligned .data of a MASM library object the original link met there.',
           '',
           '        .686p', '']
    for k in keys:
        out += ["da%08X SEGMENT PARA PUBLIC USE32 ALIAS('.data$%08X') 'DATA'" % (k, k - 1),
                'da%08X ENDS' % k]
    out += ['', '        END', '']
    open(ASM, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
