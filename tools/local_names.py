"""local_names.py SOURCE ADDRESS [--apply]

VC7.1 at /Od lays out a function's locals by their names, not by the order
they are used (docs/toolchain.md), so the right names are found rather than
written. For the function annotated `// match: sub_X @ ADDRESS` in SOURCE,
every local named for a frame slot (var_N, local_N, vN, lN, varN, lv_N, locN,
ebp_N, stk_N, slot_N, bp_N, fp_N, lcl_N, frm_N)
takes one of those forms, and the first working combination is printed.
SOURCE is not modified unless --apply is given, which writes the chosen names
into it (with a comment when they are not all var_N) and, when the bucket
stage found them, the declaration order they need.

How the layout works, measured: the compiler walks its symbol table's hash
buckets in a fixed order, and locals sharing a bucket come out in reverse
declaration order. So each name has a bucket, and locals take slots from
ebp-4 down in bucket order.

Stages, cheapest first:
1. Rank pick. One probe compile ranks every candidate name; the first
   combination, in FORMS order, whose ranks rise with the slots is confirmed
   by compiling the function (the next 300 rising combinations too).
2. Bucket pick. Two probe compiles (candidates declared forwards and
   backwards) give each name its bucket. With the locals declared from the
   highest slot down, any combination whose buckets never decrease with the
   slots works; the first such combinations are confirmed.
3. Climb: change one local's form at a time, keeping any change that makes
   more of the function's bytes match.
4. Every combination, only when there are few."""
import itertools
import os
import re
import struct
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_probes import ROOT, compile_unit, flags_for, load_flags  # noqa: E402
from coff import Coff  # noqa: E402
from match import compare  # noqa: E402
from xbe import Xbe  # noqa: E402

FORMS = ['var_%s', 'local_%s', 'v%s', 'l%s', 'var%s', 'lv_%s', 'loc%s',
         'ebp_%s', 'stk_%s', 'slot_%s', 'bp_%s', 'fp_%s', 'lcl_%s', 'frm_%s']
SLOT = r'\b(?:local_|slot_|ebp_|stk_|var_|lcl_|frm_|lv_|bp_|fp_|loc|var|v|l)([0-9A-F]+)\b'
NOTE = ('// Local names state their slots; plain var_N names reorder them '
        '(docs/toolchain.md).\n')


def name_offsets(names, flags, out):
    """Frame offset of each name when all are int locals of one function,
    declared in the given order."""
    src = os.path.join(out, 'ranks.cpp')
    obj = os.path.join(out, 'ranks.obj')
    body = ['extern "C" int g(int);', 'void ranks()', '{']
    body += ['    int %s;' % n for n in names]
    body += ['    %s = g(%d);' % (n, i) for i, n in enumerate(names)]
    body += ['}', '']
    open(src, 'w').write('\n'.join(body))
    if not compile_unit(src, obj, flags):
        return None
    coff = Coff(obj)
    code, _ = coff.function_bytes(coff.find_function('ranks'))
    offsets = []
    i = 0
    while i < len(code) - 2:
        # mov [ebp-disp8], eax / mov [ebp-disp32], eax right after each call
        if code[i] == 0x89 and code[i + 1] == 0x45:
            offsets.append(-struct.unpack_from('<b', code, i + 2)[0])
            i += 3
        elif code[i] == 0x89 and code[i + 1] == 0x85:
            offsets.append(-struct.unpack_from('<i', code, i + 2)[0])
            i += 6
        else:
            i += 1
    if len(offsets) != len(names):
        return None
    return dict(zip(names, offsets))


def name_buckets(names, flags, out):
    """Bucket index of each name. Declared forwards, names come out in bucket
    order with each bucket's names in reverse declaration order; declared
    backwards, only the order inside each bucket flips. So a run of names
    whose backwards order falls is one bucket."""
    forwards = name_offsets(names, flags, out)
    backwards = name_offsets(names[::-1], flags, out)
    if forwards is None or backwards is None:
        return None
    buckets, bucket, previous = {}, -1, None
    for name in sorted(names, key=lambda n: forwards[n]):
        if previous is None or backwards[name] > backwards[previous]:
            bucket += 1
        buckets[name] = bucket
        previous = name
    return buckets


def function_block(text, address):
    """(start, end) of the function annotated `// match: NAME @ ADDRESS` in
    TEXT (NAME is sub_X, or a decorated name such as a constructor's): from
    its marker to the next function's. The comment lines right
    after the marker (the `// match:` lines of its EH funclets and handler
    thunk, `// symbol:` lines) belong to it, so they do not end it."""
    marker = re.search(r'^// match: (\S+) @ 0x0*%X\n' % address, text, re.M)
    if marker is None:
        return None
    body = marker.end()
    while text.startswith('//', body):
        body = text.index('\n', body) + 1
    following = text.find('\n// match: ', body)
    return marker.start(), (following + 1 if following >= 0 else len(text))


def function_name(text, address):
    """The name the `// match:` annotation gives the function at ADDRESS."""
    marker = re.search(r'^// match: (\S+) @ 0x0*%X\n' % address, text, re.M)
    return marker.group(1) if marker else 'sub_%X' % address


def descending_declarations(template):
    """The template with its slot-named declarations in descending slot
    order, or None if they are not one contiguous block."""
    lines = template.split('\n')
    # `return var_8;` has the same shape as a declaration
    decl = re.compile(r'^\s+(?!return\b)\w[\w ]*?\**\s*@@([0-9A-F]+)@@;\s*$')
    idx = [i for i, line in enumerate(lines) if decl.match(line)]
    if not idx or idx != list(range(idx[0], idx[-1] + 1)):
        return None
    block = sorted((lines[i] for i in idx),
                   key=lambda line: -int(decl.match(line).group(1), 16))
    return '\n'.join(lines[:idx[0]] + block + lines[idx[-1] + 1:])


def main(argv):
    apply_names = '--apply' in argv
    argv = [a for a in argv if a != '--apply']
    if len(argv) != 3:
        print(__doc__)
        return 2
    source, address = argv[1], int(argv[2], 16)
    text = open(source).read()
    found = function_block(text, address)
    if found is None:
        print('no `// match: sub_%X` in %s' % (address, source))
        return 2
    start, end = found
    symbol = function_name(text, address)
    body = text[start:end]
    slots = sorted(set(re.findall(SLOT, body)), key=lambda s: int(s, 16))
    template = re.sub(SLOT, lambda m: '@@%s@@' % m.group(1), body)
    rel = os.path.relpath(source, ROOT).replace(os.sep, '/')
    flags = flags_for(rel, load_flags()) + ['/I' + os.path.join(ROOT, 'include')]
    out = os.path.join(ROOT, 'build', 'local_names')
    if not os.path.isdir(out):
        os.makedirs(out)
    trial_src = os.path.join(out, 'trial' + os.path.splitext(source)[1])
    trial_obj = os.path.join(out, 'trial.obj')
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    candidates = [f % s for s in slots for f in FORMS]

    def fill(names, tmpl):
        return re.sub(r'@@([0-9A-F]+)@@', lambda m: names[m.group(1)], tmpl)

    def build(names, tmpl):
        # The compiler (or a virus scan) can still hold the last trial for a
        # moment after it finishes.
        for attempt in range(20):
            try:
                open(trial_src, 'w').write(text[:start] + fill(names, tmpl) + text[end:])
                break
            except PermissionError:
                if attempt == 19:
                    raise
                time.sleep(0.25)
        if not compile_unit(trial_src, trial_obj, flags):
            raise SystemExit(1)

    def matches(names, tmpl):
        build(names, tmpl)
        return compare(trial_obj, symbol, address, image)[0]

    def closeness(names, tmpl):
        build(names, tmpl)
        obj = Coff(trial_obj)
        code, relocs = obj.function_bytes(obj.find_function(symbol))
        original = image.read(address, len(code))
        masked = set()
        for offset, _target, _rtype in relocs:
            masked.update(range(offset, offset + 4))
        same = sum(1 for i in range(len(code)) if i in masked or code[i] == original[i])
        return same, len(code)

    def report(names, tmpl):
        print('match: ' + ', '.join('%s -> %s' % (s, names[s]) for s in slots))
        if apply_names:
            trial = fill(names, tmpl)
            if any(names[s] != 'var_%s' % s for s in slots) and NOTE not in trial:
                # the note goes on the line before the function's signature
                signature = re.search(r'^\w[^\n]*\bsub_%X\(' % address, trial, re.M)
                if signature:
                    trial = trial[:signature.start()] + NOTE + trial[signature.start():]
            open(source, 'w', newline='\n').write(text[:start] + trial + text[end:])
        return 0

    def walk(key, allow_equal):
        """Combinations, in FORMS order, whose keys rise with the slots
        (strictly, or never falling): a depth-first walk that prunes early,
        so the full product is never enumerated."""
        def step(k, floor, chosen):
            if k == len(slots):
                yield dict(zip(slots, chosen))
                return
            for form in FORMS:
                name = form % slots[k]
                ok = key[name] >= floor if allow_equal else key[name] > floor
                if ok:
                    for found in step(k + 1, key[name], chosen + [name]):
                        yield found
        return step(0, -1, [])

    # 1. Rank pick, with the declarations as written.
    ranks = name_offsets(candidates, flags, out)
    if ranks is not None:
        for tried, names in enumerate(walk(ranks, False)):
            if tried == 300:
                break
            if matches(names, template):
                return report(names, template)

    # 2. Bucket pick, with the declarations from the highest slot down.
    descending = descending_declarations(template)
    buckets = name_buckets(candidates, flags, out)
    if descending is not None and buckets is not None:
        for tried, names in enumerate(walk(buckets, True)):
            if tried == 300:
                break
            if matches(names, descending):
                return report(names, descending)

    # 3. Climb.
    tmpl = descending or template
    names = dict((s, FORMS[0] % s) for s in slots)
    best, size = closeness(names, tmpl)
    budget = 800
    improved = True
    while improved and best < size and budget > 0:
        improved = False
        for s in slots:
            for form in FORMS:
                if budget <= 0 or best == size:
                    break
                trial = dict(names)
                trial[s] = form % s
                if trial == names:
                    continue
                budget -= 1
                got, _ = closeness(trial, tmpl)
                if got > best:
                    names, best, improved = trial, got, True
    if best == size and matches(names, tmpl):
        return report(names, tmpl)

    # 4. Every combination, only when there are few.
    total = len(FORMS) ** len(slots)
    if total > 2500:
        print('no name combination found, and %d combinations are too many to try: '
              'the difference is probably not the names' % total)
        return 1
    for combo in itertools.product(FORMS, repeat=len(slots)):
        names = dict((s, f % s) for s, f in zip(slots, combo))
        if matches(names, template):
            return report(names, template)
    print('no combination of %s matched' % ', '.join(FORMS))
    return 1


if __name__ == '__main__':
    sys.exit(main(sys.argv))
