"""anonfix.py: anonymous-namespace hashes for checkouts in other directories.

VC7.1 names an anonymous namespace `?A0x` + a hash of the source file's absolute path, so the
same unit compiled in another checkout (C:\\codfh-rename beside C:\\codfh-match) gets other
decorated names for its anonymous-namespace symbols. The configs (config/compiled.txt,
aliases.txt, splits.txt, symbols.txt) and a copied build/m7/seed.map spell the hashes of the
checkout they were made in. `translate(text)` rewrites those hashes to this checkout's, found
by looking up each such compiled.txt row in its compiled object; in the original checkout the
map is empty and every line comes back unchanged. `lines(path)` reads a file translated.

Coff lookups (tools/coff.py) already accept a hash difference; this module serves the tools
that put names into a link (the M7 probe's order file, /INCLUDE and /ALTERNATENAME lines) or
compare them as text."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_ANON = re.compile(r'\?A0x[0-9a-f]{8}')
_map = None


def _build():
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from coff import Coff  # noqa: E402
    m = {}
    objs = {}
    for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
        q = l.split()
        if len(q) < 3 or not q[0].startswith('0x') or '?A0x' not in q[2]:
            continue
        path = os.path.join(ROOT, q[1])
        if not os.path.exists(path):
            continue
        if path not in objs:
            try:
                objs[path] = Coff(path)
            except Exception:
                objs[path] = None
        c = objs[path]
        if c is None:
            continue
        sym = c.find_function(q[2])
        if sym is None or '?A0x' not in sym['name']:
            continue
        for old, new in zip(_ANON.findall(q[2]), _ANON.findall(sym['name'])):
            if old != new:
                m.setdefault(old, new)
    return m


def mapping():
    """old hash -> this checkout's hash (empty where they agree)."""
    global _map
    if _map is None:
        _map = _build()
    return _map


def translate(text):
    m = mapping()
    if not m or '?A0x' not in text:
        return text
    return _ANON.sub(lambda x: m.get(x.group(), x.group()), text)


def lines(path, encoding='utf-8', errors=None):
    """The lines of PATH with their anonymous-namespace hashes translated."""
    with open(path, encoding=encoding, errors=errors) as f:
        return [translate(l) for l in f]


if __name__ == '__main__':
    for k, v in sorted(mapping().items()):
        print(k, '->', v)
    print(len(mapping()), 'hashes differ in this checkout')
