"""scope_names.py SOURCE ADDRESS GROUP... [--strict A:B ...] [--apply]

Names locals of the function annotated `// match: NAME @ ADDRESS` in SOURCE
when tools/local_names.py cannot: functions with block-scoped locals, or with
initialisers that pin part of the declaration order.

Each GROUP is the comma-separated slots (hex) of the locals of one scope, in
frame order (nearest ebp first), e.g. `4,8,C,10,1C 30,3C`. Those locals must
be named var_SLOT in SOURCE (or, written SLOT=name, be a fixed name the
function does not declare itself, which only takes part in the ordering) and,
within a scope, declared farthest slot
first (var_7C before var_1C) wherever nothing pins their order: locals
sharing a bucket come out in reverse declaration order, so that is the order
in which ties fall into place (docs/toolchain.md). Every group is walked by
bucket with ties allowed; `--strict A:B` forbids a tie between the adjacent
slots A and B (use it when B is declared after A against that order, e.g. a
local with a constructor declared after the others' initialisers).

How it searches: one probe compile gives each candidate name its bucket.
Each trial then compiles the unit up to and including this one function
with an assembly listing (/FA), which states every local's frame offset
(the function is the last in the listing, so its offsets win), so each
group is checked on its own and only the groups still wrong move on to their
next candidate: the number of compiles is the longest group's search, not the
product of all of them. The winning names are confirmed by compiling SOURCE
and comparing with the image; with --apply they are written into SOURCE.

Block-scoped locals come out after the function-scope ones, a shallower
scope's before a deeper one's, sibling scopes in source order, each scope in
its own bucket order. A pair that seems to break this is usually declared in
the middle of an enclosing block rather than in braces of its own (sub_1C4F0's
second line test), so fix the scopes before searching names."""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_probes import ROOT, compile_unit, flags_for, load_flags  # noqa: E402
from local_names import FORMS, function_block, function_name, name_buckets  # noqa: E402
from match import compare  # noqa: E402
from xbe import Xbe  # noqa: E402

# Candidates tried per group at most (SCOPE_NAMES_LIMIT overrides).
LIMIT = int(os.environ.get('SCOPE_NAMES_LIMIT', '300'))

EQUATE = re.compile(r'^_(\w+?)\$\d* = (-?\d+)', re.M)


def frame_offsets(listing, name):
    """Frame offset of each local of the function NAME (sub_X or a decorated
    name) in a /FA listing: the equates (`_name$123 = -16`) the compiler
    writes just before the function's PROC line, so same-named locals of
    other functions are not mixed in."""
    if not name.startswith('?'):
        name = '?' + name + '@'
    proc = re.search(r'^%s\S* PROC' % re.escape(name), listing, re.M)
    if proc is None:
        return {}
    head = listing[:proc.start()]
    previous = max(head.rfind(' ENDP'), head.rfind(' ENDS'))
    return dict((m.group(1), -int(m.group(2)))
                for m in EQUATE.finditer(head[previous + 1:]))


def rename(block, slots, names):
    for slot, name in zip(slots, names):
        block = re.sub(r'\bvar_%s\b' % slot, name, block)
    return block


def main(argv):
    apply_names = '--apply' in argv
    strict = set()
    args = []
    rest = [a for a in argv[1:] if a != '--apply']
    i = 0
    while i < len(rest):
        if rest[i] == '--strict':
            strict.add(tuple(rest[i + 1].upper().split(':')))
            i += 2
        else:
            args.append(rest[i])
            i += 1
    if len(args) < 3:
        print(__doc__)
        return 2
    source, address = args[0], int(args[1], 16)
    # A slot written SLOT=name is held by a local the function does not
    # declare itself (an inline accessor's `r` takes its place among the
    # function's own locals): it keeps that name and only orders the rest.
    fixed = {}
    groups = []
    for g in args[2:]:
        group = []
        for entry in g.split(','):
            if '=' in entry:
                slot, local = entry.split('=', 1)
                fixed[slot.upper()] = local
                entry = slot
            group.append(entry.upper())
        groups.append(group)
    text = open(source).read()
    found = function_block(text, address)
    if found is None:
        print('no `// match:` annotation for 0x%X in %s' % (address, source))
        return 2
    start, end = found
    name = function_name(text, address)
    block = text[start:end]
    slots = [s for g in groups for s in g]
    missing = [s for s in slots
               if s not in fixed and not re.search(r'\bvar_%s\b' % s, block)]
    if missing:
        print('no local named var_%s in the function' % ', var_'.join(missing))
        return 2
    preamble = text[:start]

    rel = os.path.relpath(source, ROOT).replace(os.sep, '/')
    base_flags = flags_for(rel, load_flags())
    flags = base_flags + ['/I' + os.path.join(ROOT, 'include')]
    out = os.path.join(ROOT, 'build', 'local_names')
    if not os.path.isdir(out):
        os.makedirs(out)
    buckets = name_buckets([f % s for s in slots if s not in fixed for f in FORMS]
                           + list(fixed.values()), base_flags, out)
    if buckets is None:
        print('bucket probe failed to compile')
        return 1

    def fits(group, k, floor):
        """The names local k of GROUP may take after a bucket of FLOOR."""
        tie_ok = k == 0 or (group[k - 1], group[k]) not in strict
        names = [fixed[group[k]]] if group[k] in fixed else [f % group[k] for f in FORMS]
        for name in names:
            if buckets[name] > floor or (buckets[name] == floor and tie_ok):
                yield name

    def walk(group, k, floor, chosen, finishable):
        # Only prefixes that can still be finished are followed: without
        # this a long group spends minutes in dead ends (sub_2B740's 24
        # locals took 50 million calls to reach the first candidate).
        if k == len(group):
            yield chosen
            return
        for name in fits(group, k, floor):
            if finishable(k + 1, buckets[name]):
                for result in walk(group, k + 1, buckets[name], chosen + [name], finishable):
                    yield result

    def finisher(group):
        memo = {}

        def finishable(k, floor):
            if k == len(group):
                return True
            if (k, floor) not in memo:
                memo[k, floor] = any(finishable(k + 1, buckets[name])
                                     for name in fits(group, k, floor))
            return memo[k, floor]
        return finishable

    walks = [walk(g, 0, -1, [], finisher(g)) for g in groups]
    current = [next(w, None) for w in walks]
    if None in current:
        k = current.index(None)
        print('group %s: no names rise with its slots' % ','.join(groups[k]))
        return 1

    trial_src = os.path.join(out, 'scope' + os.path.splitext(source)[1])
    trial_obj = os.path.join(out, 'scope.obj')
    trial_asm = os.path.join(out, 'scope.asm')
    solved = [False] * len(groups)
    for attempt in range(1, LIMIT + 1):
        names = [n for group in current for n in group]
        open(trial_src, 'w').write(preamble + rename(block, slots, names))
        if not compile_unit(trial_src, trial_obj, flags + ['/FA', '/Fa' + trial_asm]):
            print('trial failed to compile')
            return 1
        offsets = frame_offsets(open(trial_asm, errors='replace').read(), name)
        for k, group in enumerate(groups):
            if not solved[k]:
                solved[k] = all(offsets.get(n) == int(s, 16)
                                for s, n in zip(group, current[k]))
        if all(solved):
            break
        for k, w in enumerate(walks):
            if not solved[k]:
                current[k] = next(w, None)
                if current[k] is None:
                    print('group %s: no candidate lands in its slots (%d compiles)'
                          % (','.join(groups[k]), attempt))
                    return 1
    else:
        wrong = [','.join(g) for g, ok in zip(groups, solved) if not ok]
        print('unsolved after %d compiles: %s' % (LIMIT, ' '.join(wrong)))
        return 1

    names = [n for group in current for n in group]
    result = text[:start] + rename(block, slots, names) + text[end:]
    open(trial_src, 'w').write(result)
    if not compile_unit(trial_src, trial_obj, flags):
        print('trial failed to compile')
        return 1
    same, detail = compare(trial_obj, name, address, Xbe(
        os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')))
    print(('match: ' if same else 'slots right, bytes differ: ')
          + ', '.join('%s -> %s' % (s, n) for s, n in zip(slots, names)))
    # Every local is in its slot, so the names are right even when other
    # bytes (compiler temporaries, say) still differ.
    if apply_names:
        open(source, 'w', newline='\n').write(result)
    if not same:
        print(detail)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
