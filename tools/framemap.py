"""framemap.py OBJ SYM ADDR: compare stack frame layouts of our compiled
function and the image's.

Walks both instruction streams (which must already line up, as ncmp shows),
tracks the push depth, turns every [esp + X] operand into a frame offset
(from esp right after the prologue's `sub esp, N`), and prints each pair of
differing offsets once: `ours -> image`, with the first instruction using it."""
import re
import sys

sys.path.insert(0, __import__('os').path.dirname(__import__('os').path.abspath(__file__)))
import ncmp  # noqa: E402


def frame_offsets(lines):
    depth = 0
    started = False
    out = []
    for ins in lines:
        m = re.match(r'sub esp, (0x[0-9a-f]+|\d+)$', ins)
        if m and not started:
            started = True
            depth = 0
            out.append(None)
            continue
        offs = [int(x, 16) - depth for x in re.findall(r'\[esp \+ (0x[0-9a-f]+)\]', ins)]
        if re.search(r'\[esp\]', ins):
            offs.append(-depth)
        out.append(offs or None)
        if ins.startswith('push '):
            depth += 4
        elif ins.startswith('pop '):
            depth -= 4
        else:
            m = re.match(r'add esp, (0x[0-9a-f]+|\d+)$', ins)
            if m:
                depth -= int(m.group(1), 0)
            m = re.match(r'sub esp, (0x[0-9a-f]+|\d+)$', ins)
            if m:
                depth += int(m.group(1), 0)
    return out


def main():
    obj, sym, addr = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
    ours, img = ncmp.listings(obj, sym, addr)
    fo, fi = frame_offsets(ours), frame_offsets(img)
    seen = {}
    for a, b, la, lb in zip(fo, fi, ours, img):
        if a and b and a != b:
            for x, y in zip(a, b):
                if x != y and (x, y) not in seen:
                    seen[(x, y)] = la
    for (x, y), l in sorted(seen.items()):
        print('ours 0x%02x -> image 0x%02x   %s' % (x, y, l))


if __name__ == '__main__':
    main()
