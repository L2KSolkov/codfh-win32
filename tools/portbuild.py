"""portbuild.py [--only GLOB]... [--link] [--jobs N]: the Win32 port's build (docs/WIN32_PORT.md): every source
under src/ (bar the Xbox-only trees src/xbe and src/xdk) compiled for Win32 x86
with MSVC 14.51 and Windows SDK 10.0.26100, against the port's bridge headers (port/include, ahead
of everything; they stand in for the XDK's xtl.h, d3d8.h, dsound.h and the rest, which are not on
the include path). Each unit keeps its include paths and defines from config/flags.txt (the first
matching rule, as the matching build reads it); the Xbox/VC7.1-only switches are dropped and the
port's own are added: CODFH_WIN32 and CODFH_PLAIN, x87 code (/arch:IA32, as the game sets the FPU
itself), VC7.1-era language rules (/permissive, /Zc:forScope-, /Zc:wchar_t-...).

Objects go to build/port/obj; build/port/compile.log has every unit's compiler output and
build/port/errors.md a summary: units that fail, error codes by count, and the headers and
identifiers the errors name most. Linking comes with W0's entry point.

Bink (W6) is the Xbox library as the tree has it: its C, and its image transcriptions (.asm,
assembled with ml.exe: the code is 32-bit x86 with symbolic relocations, so it runs as is).
"""
import collections
import concurrent.futures
import fnmatch
import glob
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
OUT = os.path.join(ROOT, 'build', 'port')
OBJ = os.path.join(OUT, 'obj')

VS = os.environ.get('CODFH_VS', r'C:\Program Files\Microsoft Visual Studio\18\Enterprise')
MSVC_VER = os.environ.get('CODFH_MSVC', '14.51.36231')
SDK = os.environ.get('CODFH_WINSDK', r'C:\Program Files (x86)\Windows Kits\10')
SDK_VER = os.environ.get('CODFH_WINSDK_VER', '10.0.26100.0')
MSVC = os.path.join(VS, 'VC', 'Tools', 'MSVC', MSVC_VER)
CL = os.path.join(MSVC, 'bin', 'Hostx64', 'x86', 'cl.exe')

SYSTEM_INCLUDES = [
    os.path.join(MSVC, 'include'),
    os.path.join(SDK, 'Include', SDK_VER, 'ucrt'),
    os.path.join(SDK, 'Include', SDK_VER, 'um'),
    os.path.join(SDK, 'Include', SDK_VER, 'shared'),
]
SYSTEM_LIBS = [
    os.path.join(MSVC, 'lib', 'x86'),
    os.path.join(SDK, 'Lib', SDK_VER, 'ucrt', 'x86'),
    os.path.join(SDK, 'Lib', SDK_VER, 'um', 'x86'),
]

# The port's own switches.
PORT_FLAGS = [
    '/c', '/nologo', '/O2', '/Oy-', '/Zi', '/FS', '/MT', '/W1', '/GR-', '/arch:IA32',
    # the sources are written for VC7.1's language rules
    '/permissive', '/Zc:forScope-', '/Zc:wchar_t-', '/Zc:threadSafeInit-', '/Zc:sizedDealloc-',
    '/Zc:strictStrings-', '/Zc:inline-', '/Zc:externConstexpr-',
    '/DCODFH_WIN32', '/DCODFH_PLAIN', '/D_WIN32', '/DWIN32', '/D_X86_',
    # C string functions return char * in C++ too (no const-correct overloads), as in VC7.1
    '/D_CONST_RETURN=',
    # calls to undeclared functions reported (the sources' own C has some, as on the Xbox)
    '/w14013',
    '/D_CRT_SECURE_NO_WARNINGS', '/D_CRT_NONSTDC_NO_DEPRECATE', '/D_WINSOCK_DEPRECATED_NO_WARNINGS',
]
# Switches from config/flags.txt that MSVC 14.51 or the port does not take.
DROP = re.compile(r'^/(compiler:.*|G[5-7B]|Gs\d*|QIfist|arch:.*|O[12bdgistxy].*|GF-?|Gy-?|GS-?|'
                  r'EH.*|GR-?|MT.*|MD.*|W\d|Zi|nologo|c)$')

SKIP_DIRS = ('src/xbe/', 'src/xdk/')
ASM_DIRS = ('src/bink/',)


def load_rules():
    rules = []
    for line in open(os.path.join('config', 'flags.txt'), encoding='utf-8'):
        line = line.strip()
        if not line or line.startswith('#'):
            continue
        pat, flags = line.split(':', 1)
        rules.append((pat.strip(), flags.split()))
    return rules


def unit_flags(src, rules):
    """The first matching rule's flags, Xbox/VC7.1-only switches dropped; exception handling kept."""
    for pat, flags in rules:
        if fnmatch.fnmatch(src, pat):
            break
    else:
        flags = []
    eh = [f for f in flags if f.startswith('/EH')] or ['/EHsc']
    kept = [f for f in flags if not DROP.match(f)]
    return eh + kept


def compile_unit(job):
    src, obj, flags = job
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    if src.endswith('.asm'):
        ml = os.path.join(os.path.dirname(CL), 'ml.exe')
        cmd = [ml, '/c', '/nologo', '/coff', '/Zi', '/I' + os.path.dirname(src), '/Fo' + obj, src]
        r = subprocess.run(cmd, capture_output=True, text=True, errors='replace')
        out = r.stdout + r.stderr
        # (ml's errors read "error A2xxx"; reported as the compiler's for the summary)
        return src, r.returncode, out.replace(': error A', ': error C')
    lang = '/TC' if src.endswith('.c') else '/TP'
    cmd = ([CL] + PORT_FLAGS + flags + [lang, '/Iport/include', '/Iinclude']
           + ['/Fo' + obj, '/Fd' + os.path.join(OBJ, 'port.pdb'), src])
    env = dict(os.environ)
    env['INCLUDE'] = ';'.join(SYSTEM_INCLUDES)
    env['LIB'] = ';'.join(SYSTEM_LIBS)
    env['PATH'] = os.path.dirname(CL) + os.pathsep + os.path.join(MSVC, 'bin', 'Hostx64', 'x64') + \
        os.pathsep + env['PATH']
    r = subprocess.run(cmd, capture_output=True, text=True, errors='replace', env=env)
    return src, r.returncode, r.stdout + r.stderr


def main():
    args = sys.argv[1:]
    only = [args[i + 1] for i, a in enumerate(args) if a == '--only']
    jobs_n = int(args[args.index('--jobs') + 1]) if '--jobs' in args else (os.cpu_count() or 4)
    if not os.path.exists(CL):
        sys.exit('no compiler at %s (set CODFH_VS / CODFH_MSVC)' % CL)
    rules = load_rules()
    srcs = sorted(s.replace(os.sep, '/') for s in
                  glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.cpp', recursive=True))
    # the port layer's own sources (port/src: the entry point, xpal, the bridges)
    srcs += sorted(s.replace(os.sep, '/') for s in
                   glob.glob('port/src/**/*.c', recursive=True) + glob.glob('port/src/**/*.cpp', recursive=True))
    srcs += sorted(s.replace(os.sep, '/') for d in ASM_DIRS for s in glob.glob(d + '*.asm'))
    srcs = [s for s in srcs if not s.startswith(SKIP_DIRS)]
    # (an .asm beside a .c of the same name gets its own object)
    def obj_of(s):
        base = os.path.splitext(s)[0] + ('_asm' if s.endswith('.asm') and not s.endswith('_asm.asm') else '')
        return os.path.join(OBJ, base + '.obj')
    every = [obj_of(s) for s in srcs]
    if only:
        srcs = [s for s in srcs if any(fnmatch.fnmatch(s, p) for p in only)]
    jobs = [(s, obj_of(s), unit_flags(s, rules)) for s in srcs]
    os.makedirs(OBJ, exist_ok=True)
    with concurrent.futures.ThreadPoolExecutor(jobs_n) as pool:
        results = list(pool.map(compile_unit, jobs))

    log = []
    failed = []
    codes = collections.Counter()
    code_text = {}
    headers = collections.Counter()
    idents = collections.Counter()
    per_unit = {}
    for src, rc, out in results:
        log.append('==== %s (exit %d)\n%s' % (src, rc, out))
        errs = [l for l in out.splitlines() if re.search(r'\b(error|fatal error) C\d+', l)]
        per_unit[src] = len(errs)
        if rc:
            failed.append(src)
        for l in errs:
            m = re.search(r'(?:fatal )?error (C\d+): (.*)', l)
            if not m:
                continue
            codes[m.group(1)] += 1
            code_text.setdefault(m.group(1), m.group(2)[:110])
            h = re.search(r"Cannot open include file: '([^']+)'", l)
            if h:
                headers[h.group(1)] += 1
            for i in re.findall(r"'([A-Za-z_][A-Za-z0-9_:]*)'", m.group(2)):
                idents[i] += 1
    open(os.path.join(OUT, 'compile.log'), 'w', encoding='utf-8').write('\n'.join(log))

    md = ['# Port build: compile summary', '',
          '`python tools/portbuild.py`: %d units, %d compile, %d fail.' % (
              len(results), len(results) - len(failed), len(failed)), '']
    md += ['## Error codes', '', '| code | count | first message |', '|---|---|---|']
    md += ['| %s | %d | %s |' % (c, n, code_text[c].replace('|', '\\|')) for c, n in codes.most_common(40)]
    md += ['', '## Missing include files', '', '| header | units |', '|---|---|']
    md += ['| %s | %d |' % (h, n) for h, n in headers.most_common()]
    md += ['', '## Identifiers named in errors (top 150)', '', '| identifier | errors |', '|---|---|']
    md += ['| `%s` | %d |' % (i, n) for i, n in idents.most_common(150)]
    md += ['', '## Failing units by error count', '', '| unit | errors |', '|---|---|']
    md += ['| %s | %d |' % (s, per_unit[s]) for s in sorted(failed, key=lambda s: -per_unit[s])]
    open(os.path.join(OUT, 'errors.md'), 'w', encoding='utf-8').write('\n'.join(md) + '\n')
    print('%d units: %d compile, %d fail (build/port/errors.md, build/port/compile.log)' % (
        len(results), len(results) - len(failed), len(failed)))
    # (--link: link after a partial compile, with the other units' objects as they are)
    if not failed and (not only or '--link' in args):
        link(every)


LIBS = ['kernel32.lib', 'user32.lib', 'gdi32.lib', 'winmm.lib', 'd3d11.lib', 'dxgi.lib', 'd3dcompiler.lib', 'xaudio2.lib', 'ws2_32.lib',
        'ntdll.lib', 'ole32.lib', 'shell32.lib', 'bcrypt.lib', 'iphlpapi.lib', 'dbghelp.lib', 'mfplat.lib', 'mfreadwrite.lib', 'mfuuid.lib', 'advapi32.lib']


def link(objs):
    """Links build/port/codfh.exe; build/port/link.log has link.exe's output and build/port/link.md
    the unresolved symbols, each with the objects that reference it."""
    exe = os.path.join(OUT, 'codfh.exe')
    rsp = os.path.join(OUT, 'link.rsp')
    open(rsp, 'w').write(''.join('"%s"\n' % os.path.abspath(o) for o in objs))
    env = dict(os.environ)
    env['LIB'] = ';'.join(SYSTEM_LIBS)
    cmd = [os.path.join(os.path.dirname(CL), 'link.exe'), '/nologo', '/MACHINE:X86', '/SUBSYSTEM:WINDOWS',
           '/DEBUG', '/INCREMENTAL:NO', '/OPT:REF', '/LARGEADDRESSAWARE', '/MAP:' + os.path.join(OUT, 'codfh.map'),
           '/PDB:' + os.path.join(OUT, 'codfh.pdb'), '/OUT:' + exe, '@' + rsp] + LIBS
    r = subprocess.run(cmd, capture_output=True, text=True, errors='replace', env=env)
    log = r.stdout + r.stderr
    open(os.path.join(OUT, 'link.log'), 'w', encoding='utf-8').write(' '.join(cmd) + '\n' + log)
    unresolved = collections.defaultdict(set)
    for l in log.splitlines():
        m = re.match(r'(\S+?)\.obj : error LNK2019: unresolved external symbol (\S+) referenced in function', l)
        m = m or re.match(r'(\S+?)\.obj : error LNK2001: unresolved external symbol (\S+)', l)
        if m:
            unresolved[m.group(2)].add(m.group(1))
    others = [l for l in log.splitlines() if ' error ' in l and 'LNK2019' not in l and 'LNK2001' not in l
              and 'LNK1120' not in l]
    md = ['# Port build: link', '', '`python tools/portbuild.py`: exit %d, %d unresolved symbols.' % (
        r.returncode, len(unresolved)), '']
    if others:
        md += ['## Other errors', ''] + ['    ' + l for l in others[:100]] + ['']
    md += ['## Unresolved symbols', '', '| symbol | referenced from |', '|---|---|']
    md += ['| `%s` | %s |' % (s, ', '.join(sorted(unresolved[s])[:6]) + (' +%d' % (len(unresolved[s]) - 6)
                                                                    if len(unresolved[s]) > 6 else ''))
           for s in sorted(unresolved)]
    open(os.path.join(OUT, 'link.md'), 'w', encoding='utf-8').write('\n'.join(md) + '\n')
    print('link exit %d: %d unresolved symbols, %d other errors (build/port/link.md)' % (
        r.returncode, len(unresolved), len(others)))


if __name__ == '__main__':
    main()
