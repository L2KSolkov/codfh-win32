"""addfn.py [--trim] ADDR...: hand-add functions IDA missed to config/symbols.txt and
config/splits.txt (the IDA database itself is never touched).

Each ADDR starts a new function `sub_ADDR` inside an existing split range: the
range is cut there, and a symbols.txt row is added with the size up to the
next function start, less any trailing nop/int3 padding.

--trim ADDR...: only end the given functions' split ranges at their code
(for libraries padded with nop, whose padding stays an unplaced gap), and set
their symbols.txt sizes to match.

A function's code end is found by decoding from its start: the end is the
first instruction boundary after which only padding bytes (0x90 or 0xCC)
remain before the next range."""
import os
import re
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ncmp  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYM = os.path.join(ROOT, 'config', 'symbols.txt')
SPL = os.path.join(ROOT, 'config', 'splits.txt')
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def read(path):
    t = open(path, encoding='utf-8', newline='').read()
    return t, ('\r\n' if '\r\n' in t else '\n')


def code_bytes(start, end):
    x = ncmp._img()
    s = [s for s in x.sections if s['name'] == '.text'][0]
    o = s['raw'] + start - s['va']
    return x.data[o:o + end - start]


def code_end(start, end):
    """Last instruction boundary such that the rest up to end is padding."""
    data = code_bytes(start, end)
    bounds = [0]
    for i in MD.disasm(data, start):
        bounds.append(i.address + i.size - start)
    for b in bounds:
        if all(c in (0x90, 0xCC) for c in data[b:]) and b > 0:
            # the padding run must not be decoded code: prefer the earliest
            # boundary where the remaining bytes are all padding
            return start + b
    return end


def split_rows(t):
    return [l for l in t.splitlines(True)]


def main():
    args = sys.argv[1:]
    trim = args and args[0] == '--trim'
    if trim:
        args = args[1:]
    addrs = sorted(int(a, 16) for a in args)
    st, snl = read(SPL)
    rows = split_rows(st)
    yt, ynl = read(SYM)
    yrows = split_rows(yt)
    for a in addrs:
        idx = None
        for k, l in enumerate(rows):
            m = re.match(r'0x([0-9A-F]+) 0x([0-9A-F]+) (\.text\s+)(\S+)', l)
            if m and int(m.group(1), 16) <= a < int(m.group(2), 16):
                idx = k
                lo, hi, sec, name = int(m.group(1), 16), int(m.group(2), 16), m.group(3), m.group(4)
                break
        assert idx is not None, hex(a)
        if trim:
            assert lo == a, 'not a range start: %x' % a
            nxt = None
            for l in rows[idx + 1:]:
                m = re.match(r'0x([0-9A-F]+) ', l)
                if m:
                    nxt = int(m.group(1), 16)
                    break
            e = code_end(a, nxt if nxt else hi)
            rows[idx] = '0x%08X 0x%08X %s%s%s' % (lo, e, sec, name, snl)
            for k, l in enumerate(yrows):
                m2 = re.match(r'(0x%08X function )0x[0-9A-F]+\s+(\.text.*)$' % a, l, re.S)
                if m2:
                    yrows[k] = m2.group(1) + '%-9s' % ('0x%X' % (e - a)) + m2.group(2)
            print('trim %x-%x' % (a, e))
            continue
        assert lo < a, 'already a range start: %x' % a
        e_prev = code_end(lo, a)
        new = 'sub_%X' % a
        rows[idx] = '0x%08X 0x%08X %s%s%s' % (lo, a, sec, name, snl)
        rows.insert(idx + 1, '0x%08X 0x%08X %s%s%s' % (a, hi, sec, new, snl))
        size = code_end(a, hi) - a
        # symbols: insert in address order, fix the previous function's size
        ins = len(yrows)
        for k, l in enumerate(yrows):
            m = re.match(r'0x([0-9A-F]+) (function|data)', l)
            if m and int(m.group(1), 16) > a:
                ins = k
                break
        for k in range(ins - 1, -1, -1):
            m = re.match(r'0x([0-9A-F]+) function 0x([0-9A-F]+)', yrows[k])
            if m:
                ps = int(m.group(1), 16)
                if ps == lo and ps + int(m.group(2), 16) > a:
                    m2 = re.match(r'(0x[0-9A-F]+ function )0x[0-9A-F]+\s+(\.text.*)$', yrows[k], re.S)
                    yrows[k] = m2.group(1) + '%-9s' % ('0x%X' % (e_prev - lo)) + m2.group(2)
                break
        yrows.insert(ins, '0x%08X function %-9s.text      %s%s' % (a, '0x%X' % size, new, ynl))
        print('add %x size %x (split %x-%x)' % (a, size, a, hi))
    open(SPL, 'w', encoding='utf-8', newline='').write(''.join(rows))
    open(SYM, 'w', encoding='utf-8', newline='').write(''.join(yrows))


if __name__ == '__main__':
    main()
