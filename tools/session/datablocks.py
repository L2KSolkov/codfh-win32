"""datablocks.py: merge the "Its data (PLAN M5)" blocks dataplace.py writes into one sorted block per file."""
import glob
import re
import subprocess

HEAD = 'Its data (PLAN M5): literals, constants and tables where the image has them.'
files = subprocess.run(['git', 'grep', '-l', HEAD, '--', 'src'], capture_output=True, text=True).stdout.split()
changed = 0
for f in files:
    raw = open(f, 'rb').read()
    try:
        text, enc = raw.decode('utf-8'), 'utf-8'
    except UnicodeDecodeError:
        text, enc = raw.decode('cp1252'), 'cp1252'
    eol = '\r\n' if '\r\n' in text else '\n'
    lines = text.split(eol)
    prefix = '; ' if f.endswith('.asm') else ''
    hdr = prefix + '// ' + HEAD
    idx = [i for i, l in enumerate(lines) if l == hdr]
    if not idx:
        continue
    first = idx[0]
    # the region from the first header: header lines and match lines, blank lines between them
    j = first
    matches = []
    while j < len(lines):
        l = lines[j]
        if l == hdr or l.strip() == '':
            j += 1
            continue
        m = re.match(r'^%s// match: (\S+) @ (0x[0-9A-Fa-f]+)$' % re.escape(prefix), l)
        if m:
            matches.append((int(m.group(2), 16), l))
            j += 1
            continue
        break
    # keep only lines before the next non-data match (the region ends at a blank line followed by
    # a non-block line); a data block is followed by the first function's match line, which the
    # loop above would have swallowed as a match line: keep only addresses in data sections
    data = [(a, l) for a, l in matches if a >= 0x3CD300]
    rest = [l for a, l in matches if a < 0x3CD300]
    new = [hdr] + [l for a, l in sorted(set(data))] + [''] + rest
    lines[first:j] = new + ([''] if rest else [])
    open(f, 'w', encoding=enc, newline='').write(eol.join(lines))
    changed += 1
print('files', changed)
