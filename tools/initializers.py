"""initializers.py

Dumps the 404 C++ dynamic initializers from the live IDA database and checks
the property M1 relies on: the linker lays them out in object order, and each
constructs globals of its own translation unit, so the globals they touch
should rise through .data/.bss in the same order.

Writes build/initializers.json and prints the monotonicity report."""
import json
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CLIENT = os.environ.get('CODFH_IDA_CLIENT', r'C:\codfh\tools\ida_client.py')


def dump():
    raw = os.path.join(ROOT, 'build', 'ida_initializers.json')
    script = os.path.join(ROOT, 'tools', 'ida_dump_initializers.py')
    subprocess.check_call([sys.executable, CLIENT, '--binary', 'Game_XboxMultiplayer.xbe',
                           '--tool', 'py_exec_file', '--args', json.dumps({'file_path': script}),
                           '--output', raw], cwd=os.path.dirname(os.path.dirname(CLIENT)))
    return json.loads(json.load(open(raw, encoding='utf-8'))['stdout'])


def main():
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    entries = dump()
    json.dump(entries, open(os.path.join(ROOT, 'build', 'initializers.json'), 'w'), indent=1)
    data_section = [s for s in image.sections if s['name'] == '.data'][0]
    previous = None
    descents = 0
    first_globals = []
    for e in entries:
        globals_ = [d for d in e['data']
                    if data_section['va'] <= d < data_section['va'] + data_section['vsize']]
        if not globals_:
            continue
        g = min(globals_)
        first_globals.append((e['init'], g))
        if previous is not None and g < previous:
            descents += 1
        previous = g
    print('initializers %d, touching .data/.bss %d, descents in global order %d'
          % (len(entries), len(first_globals), descents))
    game = [(i, g) for i, g in first_globals]
    print('first: init 0x%08X -> global 0x%08X' % game[0])
    print('last:  init 0x%08X -> global 0x%08X' % game[-1])
    calls = [c for e in entries for c in e['calls']]
    in_game = sum(1 for c in calls if 0x12000 <= c < 0x22F4B6)
    print('calls from initializers: %d, into game code %d' % (len(calls), in_game))


if __name__ == '__main__':
    main()
