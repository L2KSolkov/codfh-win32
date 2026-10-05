"""img2masm.py OUT.asm TITLE LO-HI [LO-HI ...]: transcribe image code as a MASM unit, for the
Bink functions the owner allows as assembly ("asm the rest of bink", docs/questions.md).

Each LO-HI run (contiguous unplaced functions, from config/splits.txt) becomes its own
section named after the image section (several sections may share a name: SEGMENT ALIAS).
Every instruction is written as its exact bytes (db), so the encoding is the image's; only
the fields that hold addresses become symbols:

- a relative call/jump out of the run: `call NAME` / `jmp NAME` / `jcc NAME` (rel32);
- an absolute address (a memory displacement or an immediate inside an image section):
  `dd NAME+off`, where NAME is a label of the run (L_xxxxxx) or an external named after its
  address the way match.py resolves (`_sub_XXXXXX`, `_unk_XXXXXX`), or the function's
  config/aliases.txt / config/symbols.txt name;
- a jump table (symbols.txt `jpt_`) or other data inside a function: dwords that point into
  the run become `dd L_xxxxxx`, the rest stay bytes.

Functions are PUBLIC PROCs under their aliases.txt name when one exists at their address,
else their symbols.txt name, each with a `; // match: NAME @ 0xADDR` line."""
import bisect
import os
import re
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def objname(name):
    """The object-file spelling of a symbols.txt name."""
    if name.startswith('_') or name.startswith('?'):
        return name
    return '_' + name


def load():
    syms = {}       # address -> (kind, name)
    for l in open(os.path.join(ROOT, 'config', 'symbols.txt'), encoding='utf-8'):
        p = l.split(None, 4)
        if len(p) == 5 and p[0].startswith('0x'):
            syms.setdefault(int(p[0], 16), (p[1], p[4].strip()))
    aliases = {}    # address -> name
    for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
        p = l.split('#', 1)[0].split()
        if len(p) >= 2 and p[1].startswith('0x'):
            aliases.setdefault(int(p[1], 16), p[0])
    funcs = []      # (start, end, section, name)
    for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x'):
            funcs.append((int(p[0], 16), int(p[1], 16), p[2], p[3]))
    return syms, aliases, sorted(funcs)


def main():
    args = sys.argv[1:]
    addrnames = '--addrnames' in args  # define every function as _sub_XXXXXX (XDK stand-ins)
    args = [a for a in args if a != '--addrnames']
    out_path, title = args[0], args[1]
    runs = [tuple(int(x, 16) for x in a.split('-')) for a in args[2:]]
    syms, aliases, funcs = load()
    img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    starts = [f[0] for f in funcs]

    ident_re = re.compile(r'^[A-Za-z_?@$][\w@?$]*$')

    def fname(a):
        n = fname0(a)
        if n and len(n) > 240:
            # MASM identifiers stop at 247 characters: address the target instead
            return '_sub_%06X' % a
        return n if n and ident_re.match(n) else None

    def fname0(a):
        if a in aliases:
            return aliases[a]
        if a in syms and syms[a][0] == 'function':
            return objname(syms[a][1])
        k = bisect.bisect_left(starts, a)
        if k < len(funcs) and funcs[k][0] == a:
            if funcs[k][3].startswith('chunk_of_'):
                # an IDA tail chunk: no linkable name; address it like match.py does
                return '_loc_%06X' % a
            return objname(funcs[k][3])
        return None

    def in_image(v):
        s = img.section_at(v)
        return s is not None

    def imm_address(v):
        """An immediate is an address when it names something or points at data
        (a .text-range constant such as 0x20000 is a number)."""
        if v < 0x10000 or not in_image(v):
            return False
        if v in syms or v in aliases or fname(v):
            return True
        return not img.section_at(v)['name'].startswith('.text')

    defined = set()
    externs = {}
    body = []
    for n, (lo, hi) in enumerate(runs):
        fs = [f for f in funcs if lo <= f[0] < hi]
        assert fs and fs[0][0] == lo, 'run 0x%X does not start at a function' % lo
        sec = fs[0][2]
        data = img.read(lo, hi - lo)
        # data regions inside the run: jump tables and other named data
        dregions = []
        for a in sorted(syms):
            if lo <= a < hi and syms[a][0] == 'data' and not syms[a][1].startswith('def_') \
                    and not syms[a][1].startswith('loc_'):
                dregions.append(a)
        bounds = sorted(set([f[0] for f in fs] + [f[1] for f in fs] + dregions + [hi]))

        def dend(a):
            k = bisect.bisect_right(bounds, a)
            return bounds[k] if k < len(bounds) else hi
        # pass 1: decode, collect labels
        items = []      # (addr, kind, payload)
        labels = set()
        a = lo
        while a < hi:
            if a in dregions:
                e = dend(a)
                items.append((a, 'data', data[a - lo:e - lo]))
                a = e
                continue
            # code until the next data region / function boundary
            e = dend(a)
            chunk = data[a - lo:e - lo]
            pos = 0
            for i in md.disasm(chunk, a):
                items.append((i.address, 'ins', i))
                pos = i.address + i.size - a
            if pos < len(chunk):  # undecodable tail (fill): bytes
                items.append((a + pos, 'bytes', chunk[pos:]))
            a = e
        for addr, kind, p in items:
            if kind == 'ins' and p.group(capstone.CS_GRP_JUMP) or kind == 'ins' and p.group(capstone.CS_GRP_CALL):
                for op in p.operands:
                    if op.type == capstone.x86.X86_OP_IMM and lo <= op.imm < hi:
                        labels.add(op.imm)
            if kind == 'ins':
                for op in p.operands:
                    v = None
                    if op.type == capstone.x86.X86_OP_MEM and p.disp_size == 4:
                        v = op.mem.disp & 0xFFFFFFFF
                    elif op.type == capstone.x86.X86_OP_IMM and p.imm_size == 4 and not (
                            p.group(capstone.CS_GRP_JUMP) or p.group(capstone.CS_GRP_CALL)):
                        v = op.imm & 0xFFFFFFFF
                    if v is not None and lo <= v < hi:
                        labels.add(v)
            if kind == 'data':
                for k in range(0, len(p) - 3, 4):
                    v = int.from_bytes(p[k:k + 4], 'little')
                    if lo <= v < hi:
                        labels.add(v)
        # pass 2: emit
        fstart = {f[0]: f for f in fs}
        segname = 'seg%d' % n
        body.append('')
        align = 'PARA' if lo % 16 == 0 else ('DWORD' if lo % 4 == 0 else ('WORD' if lo % 2 == 0 else 'BYTE'))
        body.append("%s SEGMENT %s PUBLIC ALIAS('%s') 'CODE'" % (segname, align, sec))
        cur = None

        def ref(v):
            if lo <= v < hi:
                return '$L_%06x' % v
            nm = fname(v)
            if nm is None:
                if v in syms and re.match(r'^(sub|dword|byte|word|off|unk|flt|dbl|qword|asc|stru)_', syms[v][1]):
                    nm = objname(syms[v][1])
                else:
                    nm = '_unk_%06X' % v
            externs.setdefault(nm, 'BYTE')
            return nm

        def emit_bytes(bs):
            for k in range(0, len(bs), 16):
                body.append('        db ' + ', '.join('0%02Xh' % b for b in bs[k:k + 16]))

        def emit_split(start, bs):
            # bytes that hold a label inside them (data the decoder took for code):
            # raw bytes, cut at each label
            cuts = [l - start for l in sorted(labels) if start < l < start + len(bs)]
            k = 0
            for c in cuts + [len(bs)]:
                if c > k:
                    emit_bytes(bs[k:c])
                if c < len(bs):
                    body.append('$L_%06x:' % (start + c))
                k = c
        for addr, kind, p in items:
            if addr in fstart:
                if cur and not addrnames:
                    body.append('%s ENDP' % cur)
                f = fstart[addr]
                cur = ('_sub_%06X' % addr) if addrnames else (fname(addr) or objname(f[3]))
                defined.add(cur)
                body.append('')
                body.append('; // match: %s @ 0x%08X' % (cur, addr))
                body.append(('PUBLIC %s' + chr(10) + '%s:') % (cur, cur) if addrnames else ('%s PROC PUBLIC' % cur))
            if addr in labels:
                body.append('$L_%06x:' % addr)
            if kind == 'bytes':
                emit_split(addr, p)
                continue
            if kind == 'data':
                k = 0
                while k < len(p):
                    if k and addr + k in labels:
                        body.append('$L_%06x:' % (addr + k))
                    if k + 4 <= len(p) and not any(addr + k + j in labels for j in (1, 2, 3)):
                        v = int.from_bytes(p[k:k + 4], 'little')
                        if lo <= v < hi and v in labels:
                            body.append('        dd $L_%06x' % v)
                            k += 4
                            continue
                    body.append('        db 0%02Xh' % p[k])
                    k += 1
                continue
            i = p
            bs = bytes(i.bytes)
            if any(addr < l < addr + len(bs) for l in labels):
                emit_split(addr, bs)
                continue
            text = '%s %s' % (i.mnemonic, i.op_str)
            rel = (i.group(capstone.CS_GRP_JUMP) or i.group(capstone.CS_GRP_CALL)) and \
                i.operands and i.operands[0].type == capstone.x86.X86_OP_IMM
            if rel:
                t = i.operands[0].imm & 0xFFFFFFFF
                if lo <= t < hi:
                    body.append('        db ' + ', '.join('0%02Xh' % b for b in bs) + '   ; ' + text)
                else:
                    nm = ref(t)
                    externs[nm] = 'NEAR'
                    if i.size not in (5, 6):
                        # a short jump to a neighbour placed elsewhere: its bytes (fixed addresses)
                        body.append('        db ' + ', '.join('0%02Xh' % b for b in bs) + '   ; ' + text)
                        continue
                    body.append('        %s %s   ; 0x%X' % (i.mnemonic, nm, t))
                continue
            fields = []
            if i.disp_size == 4:
                for op in i.operands:
                    if op.type == capstone.x86.X86_OP_MEM:
                        v = op.mem.disp & 0xFFFFFFFF
                        if in_image(v) and v >= 0x10000:
                            fields.append((i.disp_offset, v))
            if i.imm_size == 4:
                for op in i.operands:
                    if op.type == capstone.x86.X86_OP_IMM:
                        v = op.imm & 0xFFFFFFFF
                        if imm_address(v):
                            fields.append((i.imm_offset, v))
            if not fields:
                body.append('        db ' + ', '.join('0%02Xh' % b for b in bs) + '   ; ' + text)
                continue
            fields.sort()
            k = 0
            parts = []
            for off, v in fields:
                if off > k:
                    parts.append('        db ' + ', '.join('0%02Xh' % b for b in bs[k:off]))
                parts.append('        dd %s' % ref(v))
                k = off + 4
            if k < len(bs):
                parts.append('        db ' + ', '.join('0%02Xh' % b for b in bs[k:]))
            parts[0] += '   ; ' + text
            body += parts
        if cur and not addrnames:
            body.append('%s ENDP' % cur)
        cur = None
        body.append('%s ENDS' % segname)
    head = ['; codfh-match: %s' % title] + ([
            '; An XDK stand-in repacked from the image (PLAN M3: library code the installed',
            '; libraries do not hold in the image version, extracted byte for byte by',
            '; tools/img2masm.py, never decompiled).'] if addrnames else [
            '; Transcribed from the image (tools/img2masm.py): Bink code the owner allows as',
            '; assembly until it is decompiled (docs/questions.md).']) + [
            '',
            '        .686p',
            '        .model flat',
            '']
    for nm in sorted(externs):
        if nm not in defined:
            head.append('EXTERN %s:%s' % (nm, externs[nm]))
    open(out_path, 'w', encoding='utf-8', newline='\n').write('\n'.join(head + body + ['', '        END', '']))


if __name__ == '__main__':
    main()
