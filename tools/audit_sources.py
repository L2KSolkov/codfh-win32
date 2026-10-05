"""audit_sources.py

Checks the source conventions in docs/PLAN.md that byte comparison cannot see.
tools/match.py proves a function's bytes; this proves the source is the kind
the plan allows. Exit status 1 on any violation.

Scope: src/ (every .c/.cpp) and our headers in include/ (everything except
include/rw/, which holds RenderWare's own headers copied verbatim, and
src/rw/, RenderWare's own sources as the game built them).

1. No hand-transcribed assembly. `__declspec(naked)` is always rejected.
   Inline `__asm`/`_asm` is rejected except the one allowed idiom, the
   disabled debug print's guard: `__asm xor R, R` with R one of eax/ecx/edx,
   immediately followed by `__asm jz LABEL`. Bink (src/bink/) is exempt:
   RAD's code has inline assembly of its own (radmath's mult64anddiv, an
   __inline __asm function the library members binkread.obj and others
   carry and inline), so its sources keep it. Bink may also hold a
   `__declspec(naked)` transcription of a function its C does not yet
   match, by the owner's decision; each one is listed in docs/questions.md.
2. No image address written as a number. A hexadecimal literal whose value
   lies inside a section of the original image is an address the compiler
   should have relocated; declare the target and reference it by name. A
   genuine constant that happens to fall in that range (a flag value, a mask)
   is allowed only on a line whose comment says `not an address`.
3. No raw offsets. A cast to a byte pointer followed by arithmetic or an
   index (`(char *)p + 0x1C`, `((RwUInt8 *)p)[0x1C]`) stands in for a field.
4. No duplicated structs. A struct, class or union is defined only in a
   header, and each name is defined exactly once.
5. RenderWare types. The bare scalar types `int`, `unsigned`, `signed`,
   `short`, `long`, `char`, `float` and `double` are rejected; use RwInt32,
   RwUInt8, RwReal, RwChar and the rest from include/rw/ostypes.h. Bink's
   sources use RAD's own (U8 ... F32, defined by typedef in
   src/bink/bink.h) and `char` for its text, as RAD's API does.
6. No `auto` storage class: `auto v = d;` compiles in C++98 and means
   `int v = d;`."""
import glob
import hashlib
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ORIGINAL = os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')
CACHE = os.path.join(ROOT, 'build', 'audit_cache.json')

GUARD_XOR = re.compile(r'^\s*__asm\s+xor\s+(eax|ecx|edx)\s*,\s*\1\s*$')
GUARD_JZ = re.compile(r'^\s*__asm\s+(jz|je)\s+\w+\s*$')
ASM = re.compile(r'(?<![\w])(__asm|_asm|asm)(?![\w])')
NAKED = re.compile(r'__declspec\s*\(\s*naked\s*\)')
HEX = re.compile(r'(?<![\w.])0[xX]([0-9A-Fa-f]+)(?![\w.])')
RAW_OFFSET = re.compile(
    r'\(\s*(?:const\s+)?(?:char|RwChar|RwInt8|RwUInt8|unsigned\s+char|signed\s+char|void)\s*\*\s*\)'
    r'\s*\(?\s*[\w>.-]+\s*\)?\s*(?:\+|\[)')
DEFINITION = re.compile(r'\b(struct|class|union)\s+(\w+)\s*(?::[^{;()]*)?\{')
BARE_TYPE = re.compile(r'\b(int|unsigned|signed|short|long|char|float|double)\b')
AUTO = re.compile(r'(?<![\w:.>])auto\s+\w+\s*=')


def strip(text):
    """Blank out comments, string and character literals, keeping line
    structure so reported line numbers stay right."""
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            out.append(' ' * (j - i))
            i = j
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            out.append(''.join('\n' if ch == '\n' else ' ' for ch in text[i:j]))
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            j = min(j + 1, n)
            out.append(c + ' ' * (j - i - 2) + c)
            i = j
        else:
            out.append(c)
            i += 1
    return ''.join(out)


def files():
    found = []
    for pattern in ('src/**/*.cpp', 'src/**/*.c', 'include/**/*.h'):
        for path in glob.glob(os.path.join(ROOT, pattern), recursive=True):
            rel = os.path.relpath(path, ROOT).replace(os.sep, '/')
            if rel.startswith('include/rw/') or rel.startswith('src/rw/'):
                continue
            found.append((rel, path))
    return sorted(found)


def audit_file(rel, path, sections):
    """(problems, [(kind, name, line)] type definitions) of one file."""
    problems = []
    defs = []
    raw = open(path, errors='replace').read()
    raw_lines = raw.split('\n')
    code = strip(raw)
    lines = code.split('\n')
    is_header = rel.endswith('.h')
    is_bink = rel.startswith('src/bink/')
    allowed_asm = set()
    inside = False
    for k, raw_line in enumerate(raw_lines):
        if '// begin original __asm' in raw_line:
            inside = True
        elif '// end original __asm' in raw_line:
            inside = False
        elif inside:
            allowed_asm.add(k)
    for k, line in enumerate(lines):
        if GUARD_XOR.match(line):
            nxt = k + 1
            while nxt < len(lines) and not lines[nxt].strip():
                nxt += 1
            if nxt < len(lines) and GUARD_JZ.match(lines[nxt]):
                allowed_asm.update((k, nxt))
    for k, line in enumerate(lines):
        where = '%s:%d' % (rel, k + 1)
        if NAKED.search(line) and not is_bink:
            problems.append('%s: __declspec(naked)' % where)
        if ASM.search(line) and k not in allowed_asm and not is_bink:
            problems.append('%s: inline assembly outside the debug-guard idiom' % where)
        if line.lstrip().startswith('#line'):
            continue
        constant_ok = 'not an address' in raw_lines[k]
        for m in HEX.finditer(line if not constant_ok else ''):
            value = int(m.group(1), 16)
            for lo, hi, name in sections:
                if lo <= value < hi:
                    problems.append('%s: 0x%X is an address in %s; reference the target by name'
                                    % (where, value, name))
                    break
        if RAW_OFFSET.search(line):
            problems.append('%s: raw offset through a byte-pointer cast; declare the member'
                            % where)
        if AUTO.search(line):
            problems.append('%s: `auto` declares an int in C++98' % where)
        for m in BARE_TYPE.finditer(line):
            if is_bink and (m.group(1) == 'char' or line.lstrip().startswith('typedef')):
                continue
            problems.append('%s: bare `%s`; use the RenderWare typedef' % (where, m.group(1)))
    for m in DEFINITION.finditer(code):
        defs.append((m.group(1), m.group(2), code.count('\n', 0, m.start()) + 1))
    if not is_header:
        problems += ['%s:%d: %s %s defined in a source file; define it in its header' % (rel, n, k, d)
                     for k, d, n in defs]
    return problems, defs


def main():
    image = Xbe(ORIGINAL)
    sections = [(s['va'], s['va'] + s['vsize'], s['name']) for s in image.sections]
    problems = []
    definitions = {}
    # per-file results, reused while a file and this script are unchanged
    salt = hashlib.sha1(open(os.path.abspath(__file__), 'rb').read()).hexdigest()
    try:
        cache = json.load(open(CACHE))
    except (OSError, ValueError):
        cache = {}
    if cache.get('salt') != salt:
        cache = {'salt': salt}
    found = files()
    for rel, path in found:
        key = hashlib.sha1(open(path, 'rb').read()).hexdigest()
        hit = cache.get(rel)
        if not hit or hit[0] != key:
            hit = cache[rel] = [key] + list(audit_file(rel, path, sections))
        problems += hit[1]
        for kind, name, line_no in hit[2]:
            where = '%s:%d' % (rel, line_no)
            if name in definitions:
                problems.append('%s: %s %s already defined at %s' % (where, kind, name, definitions[name]))
            else:
                definitions[name] = where
    try:
        json.dump(cache, open(CACHE, 'w'))
    except OSError:
        pass
    for p in problems:
        print('AUDIT ' + p)
    print('audit: %d files, %d problems' % (len(found), len(problems)))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
