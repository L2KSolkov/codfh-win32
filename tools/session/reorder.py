"""reorder.py SOURCE...: put a unit's function definitions in image address order (PLAN M7).

/Gy places functions in definition order, so for the authentic link a unit's out-of-line
definitions must come in the order of their addresses. The file is cut into top-level items (a
declaration or definition with the comments and blank lines before it); every item that defines
a function and carries a `// match: NAME @ 0xADDR` line for code is a definition, keyed by its
first such address. The definitions are put back into the slots definitions occupied, sorted by
address; everything else stays where it is. A namespace's own lines (`namespace N {`, its `}`)
are barriers: definitions are sorted within each stretch between them. A #line directive at
file scope goes with the item after it. Units with #if blocks at file scope are skipped
(reported).

    reorder.py --check SOURCE...   only report which would change"""
import os
import re
import sys

TEXT_END = 0x2F0000
MATCH = re.compile(r'^//\s*match:\s*(\S+)\s*@\s*0x([0-9A-Fa-f]+)', re.M)


def items_kinds(text):
    """[(start, end, 'item' or 'barrier')] covering text; None when the structure is unsupported."""
    out = []
    depth = 0
    i = 0
    n = len(text)
    start = 0
    paren = 0
    namespaces = 0
    line_start = True

    def line_end(k):
        e = text.find('\n', k)
        return n if e < 0 else e + 1

    while i < n:
        c = text[i]
        if line_start and c == '#':
            # preprocessor line (with continuations)
            j = text.find('\n', i)
            while j > 0 and text[j - 1] == '\\':
                j = text.find('\n', j + 1)
            j = n if j < 0 else j + 1
            if re.match(r'#\s*(if|ifdef|ifndef|else|elif|endif)\b', text[i:j]) and depth == 0:
                return None
            i = j
            continue
        if text.startswith('//', i):
            i = line_end(i)
            line_start = True
            continue
        if text.startswith('/*', i):
            j = text.find('*/', i + 2)
            i = n if j < 0 else j + 2
            continue
        if c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            i = j + 1
            line_start = False
            continue
        line_start = c == '\n' or (line_start and c in ' \t')
        if c == '(':
            paren += 1
        elif c == ')':
            paren -= 1
        elif c == '{':
            if depth == 0 and re.search(r'\bnamespace\b[^;{}]*$', text[start:i]) \
                    and text[i + 1:line_end(i)].strip() == '':
                # `namespace N {` alone on its line: a barrier; its body is items at depth 0
                e = line_end(i)
                out.append((start, e, 'barrier'))
                start = i = e
                namespaces += 1
                line_start = True
                continue
            depth += 1
        elif c == '}' and depth == 0:
            pending = text[start:i]
            if not namespaces or re.sub(r'//[^\n]*', '', pending).strip():
                return None
            if pending.strip():
                # comment lines before the namespace's brace: an item of their own
                out.append((start, i, 'item'))
                start = i
            e = line_end(i)
            out.append((start, e, 'barrier'))
            start = i = e
            namespaces -= 1
            line_start = True
            continue
        elif c == '}':
            depth -= 1
            if depth == 0:
                # a definition ends here unless a ';' follows (class, initializer)
                k = i + 1
                while k < n and text[k] in ' \t':
                    k += 1
                if k < n and text[k] == ';':
                    i = k
                else:
                    e = line_end(i)
                    out.append((start, e, 'item'))
                    start = i = e
                    line_start = True
                    continue
        if c == ';' and depth == 0 and paren == 0:
            e = line_end(i)
            out.append((start, e, 'item'))
            start = i = e
            line_start = True
            continue
        i += 1
    if start < n:
        out.append((start, n, 'item'))
    return out


def items(text):
    """[(start, end)] top-level items (namespace lines included); None when unsupported."""
    its = items_kinds(text)
    return None if its is None else [(s, e) for s, e, _k in its]


def key(item):
    """The item's first code match address when it defines a function, else None."""
    body = item
    code = re.sub(r'//[^\n]*', '', body)
    if '{' not in code or not re.search(r'\)\s*(const\s*)?(:[^{;]*)?\{', code):
        return None
    if re.match(r'\s*(struct|class|union|enum|namespace)\b', code) and not re.search(r'::', code.split('{')[0]):
        return None
    # the comment block right above the code (bodiless match lines for inlines may come first,
    # separated by a blank line)
    lead = body[:len(body) - len(body.lstrip())]
    lines = body.split('\n')
    first_code = next(k for k, l in enumerate(lines) if l.strip() and not l.lstrip().startswith(('//', '#')))
    k = first_code
    while k > 0 and lines[k - 1].strip():
        k -= 1
    block = '\n'.join(lines[k:first_code])
    del lead
    for name, addr in MATCH.findall(block) or MATCH.findall(body):
        a = int(addr, 16)
        if a < TEXT_END and not name.startswith(('__ehhandler$', '$L', '__unwindfunclet$')):
            return a
    return None


def reorder(text):
    its = items_kinds(text)
    if its is None:
        return None, 'unsupported structure'
    parts = [text[s:e] for s, e, _k in its]
    keys = [None if k == 'barrier' else key(p) for p, (_s, _e, k) in zip(parts, its)]
    new = list(parts)
    moved = 0
    seg = []
    for j in range(len(its) + 1):
        if j == len(its) or its[j][2] == 'barrier':
            # one stretch between namespace lines: its definitions sorted into its slots
            slots = [i for i in seg if keys[i] is not None]
            defs = sorted((keys[i], i) for i in slots)
            for slot, (_k, i) in zip(slots, defs):
                new[slot] = parts[i]
            moved += sum(1 for slot, (_k, i) in zip(slots, defs) if slot != i)
            seg = []
        else:
            seg.append(j)
    return ''.join(new), moved


def main():
    check = '--check' in sys.argv
    for p in [a for a in sys.argv[1:] if not a.startswith('--')]:
        raw = open(p, 'rb').read().decode('utf-8', errors='surrogateescape')
        nl = '\r\n' if '\r\n' in raw else '\n'
        t = raw.replace('\r\n', '\n')
        new, moved = reorder(t)
        if new is None:
            print('%s: skipped (%s)' % (p, moved))
            continue
        assert sorted(new.splitlines()) == sorted(t.splitlines()), p
        if new != t:
            print('%s: %d definitions moved' % (p, moved))
            if not check:
                open(p, 'wb').write(new.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
        else:
            print('%s: in order' % p)


if __name__ == '__main__':
    main()
