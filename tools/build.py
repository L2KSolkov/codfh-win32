"""build.py

The per-commit gate: compiles every probe (and, as they appear, every source
unit), matches each annotated function, then runs the placement linker. Exit
status 0 means every compiled function matches and the rebuilt image is
byte-identical to the original."""
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOLS = os.path.join(ROOT, 'tools')


def step(label, script):
    print('== %s' % label)
    return subprocess.call([sys.executable, os.path.join(TOOLS, script)])


def main():
    failures = 0
    failures += step('source audit', 'audit_sources.py') != 0
    failures += step('probes: compile and match', 'build_probes.py') != 0
    failures += step('sources: compile and match', 'build_sources.py') != 0
    print('== xdk members: extract and match')
    failures += subprocess.call([sys.executable, os.path.join(TOOLS, 'xdk_members.py'), '--check']) != 0
    failures += step('placement link', 'xbelink.py') != 0
    print('== %s' % ('PASS' if not failures else 'FAIL'))
    return 1 if failures else 0


if __name__ == '__main__':
    sys.exit(main())
