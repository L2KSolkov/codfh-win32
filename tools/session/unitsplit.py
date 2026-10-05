"""unitsplit.py SRC ADDR [--end ADDR] [--move REGEX]...: split a unit at an original object boundary
(PLAN M7; boundaries from objsplit.py).

VC7.1 emits a unit's deferred inline and template functions at its end, so where the image has
them between out-of-line functions the original was several objects. This moves to a new unit,
src/.../unit_ADDR.cpp (beside SRC, same extension):

- every top-level definition whose own match line is for code in [ADDR, END) (reorder.key);
- every other `// match:` line for code in that range, and the EH lines (`__ehhandler$NAME...`)
  of every name moved;
- the top-level items whose code matches a --move REGEX (data, registrations);

and copies SRC's #include lines to the new unit's head. Rows of config/compiled.txt for the
moved names get the new object. END defaults to the end of the unit's code. Fix what does not
compile by hand (cc1.py, fwdfix.py), renumber the $E lines with tools/emap.py --remap."""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import reorder  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TEXT_END = reorder.TEXT_END
LINE = re.compile(r'^//\s*match:\s*(\S+)\s*@\s*0x([0-9A-Fa-f]+)\s*$')


def base_name(n):
    """The function an EH line belongs to: __ehhandler$NAME-0x10 / NAME>1>8 -> NAME."""
    m = re.match(r'(?:__ehhandler\$|__unwindfunclet\$|__catch\$|__tryblocktable\$|__unwindtable\$|__ehfuncinfo\$)(.*?)(?:[-+]0x[0-9A-Fa-f]+|>[0-9>]+|\$\d+)?$', n)
    return m.group(1) if m else None


def main():
    args = sys.argv[1:]
    src = args[0]
    lo = int(args[1], 16)
    hi = TEXT_END
    moves = []
    i = 2
    while i < len(args):
        if args[i] == '--end':
            hi = int(args[i + 1], 16)
            i += 2
        elif args[i] == '--move':
            moves.append(re.compile(args[i + 1]))
            i += 2
        else:
            raise SystemExit('unknown argument ' + args[i])
    raw = open(src, 'rb').read().decode('utf-8', errors='surrogateescape')
    nl = '\r\n' if '\r\n' in raw else '\n'
    t = raw.replace('\r\n', '\n')
    its = reorder.items_kinds(t)
    if its is None:
        raise SystemExit('unsupported structure')
    ext = os.path.splitext(src)[1]
    new_src = os.path.join(os.path.dirname(src), 'unit_%06X%s' % (lo, ext))
    assert not os.path.exists(new_src), new_src
    keep, moved, names = [], [], set()
    loose = []                               # match lines moved on their own
    ns = []                                  # the namespaces the current item is in
    for s, e, kind in its:
        part = t[s:e]
        if kind == 'barrier':
            keep.append(part)
            m = re.search(r'\bnamespace\s+(\w+)', part)
            if m:
                ns.append(m.group(1))
            elif ns:
                ns.pop()
            continue
        k = reorder.key(part)
        code = re.sub(r'//[^\n]*', '', part)
        if k is not None and lo <= k < hi or any(r.search(code) for r in moves):
            # the item's preprocessor lines (and all before them) stay; so do match lines for
            # code outside the range (inlines another object emits)
            plines = part.split('\n')
            if k is not None:
                # only the comment block right above the code goes with a definition
                first_code = next(j for j, l in enumerate(plines)
                                  if l.strip() and not l.lstrip().startswith(('//', '#')))
                cut = first_code
                while cut > 0 and plines[cut - 1].strip() and not plines[cut - 1].startswith('#'):
                    cut -= 1
            else:
                cut = max((j for j, l in enumerate(plines) if l.startswith('#')), default=-1) + 1
            stay = []
            for l in plines[:cut]:
                m = LINE.match(l)
                if m and lo <= int(m.group(2), 16) < hi and int(m.group(2), 16) < TEXT_END \
                        and not base_name(m.group(1)):
                    loose.append(l)
                    names.add(m.group(1))
                else:
                    stay.append(l)
            go = []
            for l in plines[cut:]:
                m = LINE.match(l)
                if m and int(m.group(2), 16) < TEXT_END and not lo <= int(m.group(2), 16) < hi \
                        and not base_name(m.group(1)):
                    stay.append(l)
                else:
                    go.append(l)
            if stay:
                keep.append('\n'.join(stay) + '\n')
            part = '\n'.join(go)
            moved.append((tuple(ns), part))
            names.update(m.group(1) for m in (LINE.match(l) for l in part.split('\n')) if m)
            continue
        # loose match lines for code in the range (inlines, templates, compiler-generated)
        out = []
        for l in part.split('\n'):
            m = LINE.match(l)
            if m and lo <= int(m.group(2), 16) < hi and int(m.group(2), 16) < TEXT_END \
                    and not base_name(m.group(1)) and k is None:
                # with the plain comment lines right above it (what it is)
                j = len(out)
                while j > 0 and out[j - 1].startswith('//') and not LINE.match(out[j - 1]):
                    j -= 1
                loose.extend(out[j:])
                del out[j:]
                loose.append(l)
                names.add(m.group(1))
                continue
            out.append(l)
        keep.append('\n'.join(out))
    # EH lines of moved names, wherever they are
    text_keep = ''.join(keep)
    eh = []
    kept_lines = []
    for l in text_keep.split('\n'):
        m = LINE.match(l)
        if m and base_name(m.group(1)) in names:
            eh.append(l)
            names.add(m.group(1))
            continue
        kept_lines.append(l)
    text_keep = '\n'.join(kept_lines)
    # the moved items, in their namespaces
    moved_text = ''
    cur = ()
    for space, part in moved:
        if space != cur:
            moved_text += ''.join('}\n' for _n in cur) + ''.join('\nnamespace %s\n{\n' % n for n in space)
            cur = space
        moved_text += part
    moved_text += ''.join('}\n' for _n in cur)
    includes = [l for l in t.split('\n') if l.startswith('#include')]
    usings = [l for l in t.split('\n') if l.startswith('using namespace')]
    head = ('// Split from %s at 0x%06X, where the image ends that object (its deferred\n'
            '// functions come before the next out-of-line one; PLAN M7).\n\n' % (os.path.basename(src), lo))
    body = head + '\n'.join(includes) + '\n\n'
    if usings:
        body += '\n'.join(usings) + '\n\n'
    if eh or loose:
        body += '\n'.join(eh + loose) + '\n\n'
    body += moved_text.lstrip('\n')
    open(new_src, 'wb').write(body.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
    open(src, 'wb').write(text_keep.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
    # compiled.txt rows
    old_obj = 'build/' + os.path.relpath(os.path.splitext(src)[0], ROOT).replace(os.sep, '/') + '.obj'
    new_obj = 'build/' + os.path.relpath(os.path.splitext(new_src)[0], ROOT).replace(os.sep, '/') + '.obj'
    cfg = os.path.join(ROOT, 'config', 'compiled.txt')
    lines = open(cfg, encoding='utf-8').read().split('\n')
    n = 0
    for j, l in enumerate(lines):
        q = l.split()
        if len(q) >= 3 and q[1] == old_obj and q[2] in names:
            lines[j] = l.replace(old_obj, new_obj, 1)
            n += 1
    open(cfg, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
    print('%s: %d items, %d loose and %d EH lines moved; %d compiled.txt rows' % (new_src, len(moved), len(loose), len(eh), n))


if __name__ == '__main__':
    main()
