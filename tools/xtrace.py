"""xtrace.py START END: a readable trace of RenderWare Xbox driver code.

Decodes the stores into the render state and texture stage state cache
buffers (the RwXboxSetCachedRenderState / RwXboxSetCachedTextureStageState
macros) as `RS <state> = <value>` and `TSS <stage> <type> = <value>` lines
(names from the XDK's d3d8types.h), drops the macros' dirty-list
bookkeeping, and keeps calls, branches and everything else as plain
disassembly."""
import os
import re
import subprocess
import sys

S = os.path.dirname(os.path.abspath(__file__))
RS_BUF = 0x51F4C0          # _RwXbRenderStateCacheBuffer[D3DRS_MAX]
TSS_BUF = 0x51F760         # _RwXbTextureStageCacheBuffer[D3DTSS_MAX][4]
TSS_DIRTY = 0x51F980       # _RwXbTextureStageCacheDirty (bookkeeping, dropped)
TSS_LIST = 0x51F2C0        # _RwXbTextureStageCacheList
TSS_COUNT = 0x51F960       # _RwXbTextureStageCacheCount[4]
RS_DIRTY = 0x51FBA0        # _RwXbRenderStateCacheDirty
BOOK = ('__RwXbTextureStageCacheCount', '__RwXbTextureStageCacheList',
        '__RwXbRenderStateCacheCount', '__RwXbRenderStateCacheList')
D3D8TYPES = r'C:\XDK\xbox\include\d3d8types.h'


def _enum(prefix):
    names = {}
    for l in open(D3D8TYPES, encoding='latin-1'):
        m = re.match(r'\s*%s_([A-Z0-9_]+)\s*=\s*(\d+)' % prefix, l)
        if m and 'MAX' not in m.group(1) and 'MIN' not in m.group(1):
            names.setdefault(int(m.group(2)), m.group(1))
    return names


TSS = _enum('D3DTSS')
RS = _enum('D3DRS')

lines = subprocess.run([sys.executable, os.path.join(S, 'xdis.py')] + sys.argv[1:3],
                       capture_output=True, text=True).stdout.splitlines()
for l in lines:
    m = re.match(r'\s*([0-9a-f]+)\s+(.*)', l)
    if not m:
        continue
    addr, ins = m.groups()
    if ins.startswith('int3'):
        continue
    if any(b in ins for b in BOOK):
        continue
    d = re.search(r'dword ptr \[(?:e[a-z]x \+ )?(0x5[0-9a-f]{5})\]', ins)
    if d:
        a = int(d.group(1), 16)
        if (RS_DIRTY <= a < RS_DIRTY + 0x400 or TSS_DIRTY <= a < TSS_DIRTY + 0x200
                or TSS_LIST <= a < TSS_LIST + 0x200 or TSS_COUNT <= a < TSS_COUNT + 0x10):
            continue
        w = re.match(r'mov dword ptr \[0x[0-9a-f]+\], (.*)', ins)
        if w and TSS_BUF <= a < TSS_BUF + 0x200:
            t, st = divmod((a - TSS_BUF) // 4, 4)
            print('%s  TSS %d %s = %s' % (addr, st, TSS.get(t, hex(t)), w.group(1)))
            continue
        if w and RS_BUF <= a < RS_BUF + 0x2A0:
            s = (a - RS_BUF) // 4
            print('%s  RS %s = %s' % (addr, RS.get(s, hex(s)), w.group(1)))
            continue
    print('%s  %s' % (addr, ins))
