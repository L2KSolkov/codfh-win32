#!/usr/bin/env python3
"""
scan_assets.py - inventory of the Xbox game data (Call of Duty: Finest Hour) for a
PC Direct3D 9 port of the RenderWare 3.6 Xbox renderer (docs/WIN32_PORT_ASSETS.md,
docs/WIN32_PORT.md section 7).

Walks every file of an extracted copy of COD.PAK, finds RenderWare binary stream chunks (also ones
embedded in game / RenderWare Studio containers, by scanning for the 3.6
library-id stamp), recurses into containers and decodes:
  * Texture Native (0x15) structs as read by src/rw/driver/xbox/xbtexdic.c
  * Geometry (0x0F) structs, plus the Xbox vertex format plugin (0x511,
    src/rw/world/pipe/p2/xbox/xbvtxfmt.c), native data (0x510, native.c),
    and the skin plugin (0x116, generic or Xbox native skinxboxinstance.c)
  * World (0x0B), Atomic Sector (0x09), Plane Sector (0x0A)
  * standalone / embedded DDS files and a census of non-RW files.

Usage: python tools/port/scan_assets.py EXTRACTED_DIR [out.md]
Read-only on the data. Sections 1-4 of docs/WIN32_PORT_ASSETS.md come from its output.
"""
import collections
import json
import os
import re
import struct
import sys

if len(sys.argv) < 2:
    sys.exit(__doc__)
ROOT = sys.argv[1]
OUT = sys.argv[2] if len(sys.argv) > 2 else 'disc_formats.md'

# ---------------------------------------------------------------- chunk ids
CORE = {
    0x01: 'Struct', 0x02: 'String', 0x03: 'Extension', 0x05: 'Camera',
    0x06: 'Texture', 0x07: 'Material', 0x08: 'Material List',
    0x09: 'Atomic Sector', 0x0A: 'Plane Sector', 0x0B: 'World',
    0x0C: 'Spline', 0x0D: 'Matrix', 0x0E: 'Frame List', 0x0F: 'Geometry',
    0x10: 'Clump', 0x12: 'Light', 0x13: 'Unicode String', 0x14: 'Atomic',
    0x15: 'Texture Native', 0x16: 'Texture Dictionary',
    0x17: 'Anim Database', 0x18: 'Image', 0x19: 'Skin Animation',
    0x1A: 'Geometry List', 0x1B: 'Anim Animation', 0x1C: 'Team',
    0x1D: 'Crowd', 0x1E: 'DMorph Animation', 0x1F: 'Right To Render',
    0x20: 'MT Effect Native', 0x21: 'MT Effect Dict',
    0x22: 'Team Dictionary', 0x23: 'PI Texture Dictionary', 0x24: 'TOC',
    0x25: 'PRT Std Global Data', 0x26: 'AltPipe', 0x27: 'PipeDS',
    0x28: 'Patch Mesh', 0x29: 'Chunk Group Start', 0x2A: 'Chunk Group End',
    0x2B: 'UV Anim Dict', 0x2C: 'Coll Tree', 0x2D: 'Environment',
}
TK = {0x01: "METRICSPLUGIN", 0x02: "SPLINEPLUGIN", 0x03: "STEREOPLUGIN", 0x04: "VRMLPLUGIN",
      0x05: "MORPHPLUGIN", 0x06: "PVSPLUGIN", 0x07: "MEMLEAKPLUGIN", 0x08: "ANIMPLUGIN",
      0x09: "GLOSSPLUGIN", 0x0a: "LOGOPLUGIN", 0x0b: "MEMINFOPLUGIN", 0x0c: "RANDOMPLUGIN",
      0x0d: "PNGIMAGEPLUGIN", 0x0e: "BONEPLUGIN", 0x0f: "VRMLANIMPLUGIN", 0x10: "SKYMIPMAPVAL",
      0x11: "MRMPLUGIN", 0x12: "LODATMPLUGIN", 0x13: "MEPLUGIN", 0x14: "LTMAPPLUGIN",
      0x15: "REFINEPLUGIN", 0x16: "SKINPLUGIN", 0x17: "LABELPLUGIN", 0x18: "PARTICLESPLUGIN",
      0x19: "GEOMTXPLUGIN", 0x1a: "SYNTHCOREPLUGIN", 0x1b: "STQPPPLUGIN", 0x1c: "PARTPPPLUGIN",
      0x1d: "COLLISPLUGIN", 0x1e: "HANIMPLUGIN", 0x1f: "USERDATAPLUGIN", 0x20: "MATERIALEFFECTSPLUGIN",
      0x22: "DMORPHPLUGIN", 0x23: "PATCHPLUGIN", 0x24: "TEAMPLUGIN", 0x25: "CROWDPPPLUGIN",
      0x26: "MIPSPLITPLUGIN", 0x27: "ANISOTPLUGIN", 0x29: "GCNMATPLUGIN", 0x2a: "GPVSPLUGIN",
      0x2b: "XBOXMATPLUGIN", 0x2c: "MULTITEXPLUGIN", 0x2d: "CHAINPLUGIN", 0x2e: "TOONPLUGIN",
      0x2f: "PTANKPLUGIN", 0x30: "PRTSTDPLUGIN", 0x31: "PDSPLUGIN", 0x32: "PRTADVPLUGIN",
      0x33: "NORMMAPPLUGIN", 0x34: "ADCPLUGIN", 0x35: "UVANIMPLUGIN", 0x36: "ENVIRONMENTPLUGIN",
      0x37: "IDPLUGIN", 0x80: "CHARSEPLUGIN", 0x81: "NOHSWORLDPLUGIN", 0x82: "IMPUTILPLUGIN",
      0x83: "SLERPPLUGIN", 0x84: "OPTIMPLUGIN", 0x85: "TLWORLDPLUGIN", 0x86: "DATABASEPLUGIN",
      0x87: "RAYTRACEPLUGIN", 0x88: "RAYPLUGIN", 0x89: "LIBRARYPLUGIN", 0x90: "2DPLUGIN",
      0x91: "TILERENDPLUGIN", 0x92: "JPEGIMAGEPLUGIN", 0x93: "TGAIMAGEPLUGIN", 0x94: "GIFIMAGEPLUGIN",
      0x95: "QUATPLUGIN", 0x96: "SPLINEPVSPLUGIN", 0x97: "MIPMAPPLUGIN", 0x98: "MIPMAPKPLUGIN",
      0x99: "2DFONT", 0x9a: "INTSECPLUGIN", 0x9b: "TIFFIMAGEPLUGIN", 0x9c: "PICKPLUGIN",
      0x9d: "BMPIMAGEPLUGIN", 0x9e: "RASIMAGEPLUGIN", 0x9f: "SKINFXPLUGIN", 0xa0: "VCATPLUGIN",
      0xa1: "2DPATH", 0xa2: "2DBRUSH", 0xa3: "2DOBJECT", 0xa4: "2DSHAPE", 0xa5: "2DSCENE",
      0xa6: "2DPICKREGION", 0xa7: "2DOBJECTSTRING", 0xa8: "2DANIMPLUGIN", 0xa9: "2DANIM",
      0xb0: "2DKEYFRAME", 0xb1: "2DMAESTRO", 0xb2: "BARYCENTRIC", 0xb3: "PITEXDICTIONARYTK",
      0xb4: "TOCTOOLKIT", 0xb5: "TPLTOOLKIT", 0xb6: "ALTPIPETOOLKIT", 0xb7: "ANIMTOOLKIT",
      0xb8: "SKINSPLITTOOKIT", 0xb9: "CMPKEYTOOLKIT", 0xba: "GEOMCONDPLUGIN", 0xbb: "WINGPLUGIN",
      0xbc: "GENCPIPETOOLKIT", 0xbd: "LTMAPCNVTOOLKIT", 0xbe: "FILESYSTEMPLUGIN", 0xbf: "DICTTOOLKIT",
      0xc0: "UVANIMLINEAR", 0xc1: "UVANIMPARAM"}
WORLDV = {0x0E: 'BINMESHPLUGIN', 0x10: 'NATIVEDATAPLUGIN (0x510)',
          0x11: 'VERTEXFMTPLUGIN (Xbox, 0x511)'}
STRFUNC = ['Reset', 'Reserved1', 'Reserved2', 'SetDirectorsCameraMatrix', 'CreateEntity',
           'UpdateEntityAttributes', 'SetFrozenMode', 'SetRunningMode', 'EnableDirectorsCamera',
           'DisableDirectorsCamera', 'TextComment', 'StartSystem', 'StopSystem', 'DeleteEntity',
           'DeleteAllEntities', 'UnLoadAsset', 'Shutdown', 'CloseConnection', 'SendTestEvent',
           'Reserved3', 'Reserved3b', 'LoadAsset', 'LoadEmbeddedAsset', 'Reserved4',
           'GetEntityMatrix', 'CustomData', 'FunctionProfiler', 'ResetEntity', 'PlacementNew',
           'Initialize', 'UpdateAsset', 'DynamicSequence']
GAME = {0x4210: 'game clump plugin (unit_0EBF10)', 0x4211: 'game tagged matrices (clumpdata)',
        0x4212: 'game chunk 0x4212', 0x4213: 'game chunk 0x4213',
        0x42A0: 'game chunk 0x42A0', 0x42A1: "game 'ADST' set (unit_0770C0)",
        0x42B0: 'game atomic plugin', 0x42B1: 'game clump plugin', 0x42B2: 'game frame plugin',
        0x42B3: 'game light plugin', 0x42B5: 'game world plugin',
        0x7A7: 'game material plugin (unit_0FB7A0)', 0x7FE: 'RWS 0x7FE', 0x7FF: 'RWS 0x7FF',
        0x719: 'RWS CustomData (game: level section streaming)'}


def chunk_name(t):
    if t in GAME:
        return GAME[t]
    v, i = t >> 8, t & 0xFF
    if v == 0 and i in CORE:
        return CORE[i]
    if v == 1 and i in TK:
        return 'rwID_' + TK[i]
    if v == 5 and i in WORLDV:
        return 'rwID_' + WORLDV[i]
    if v == 7 and i < len(STRFUNC):
        return 'RWS strfunc_' + STRFUNC[i]
    if v == 8:
        return 'RW Audio 0x%X' % t
    return '0x%X' % t


CONTAINERS = {0x03, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0E, 0x0F, 0x10,
              0x12, 0x14, 0x15, 0x16, 0x1A, 0x2B, 0x510}
# opaque payloads we never signature-scan (raw data of known meaning)
KNOWN_OPAQUE = {0x01, 0x02, 0x13, 0x50E, 0x511, 0x116, 0x11E, 0x11F, 0x110, 0x11D, 0x120,
                0x135, 0x2C, 0x1B, 0x12C, 0x12B, 0x105, 0x122, 0x1A1, 0x1A2, 0x1A3, 0x1A4,
                0x1A5, 0x1A9, 0x1B0, 0x1B1, 0x1B4}

# ------------------------------------------------------------- Xbox formats
XB_D3DFMT = {
    0x00: 'L8 (swz)', 0x01: 'AL8 (swz)', 0x02: 'A1R5G5B5 (swz)', 0x03: 'X1R5G5B5 (swz)',
    0x04: 'A4R4G4B4 (swz)', 0x05: 'R5G6B5 (swz)', 0x06: 'A8R8G8B8 (swz)', 0x07: 'X8R8G8B8 (swz)',
    0x0B: 'P8 (swz)', 0x0C: 'DXT1', 0x0E: 'DXT2/DXT3', 0x0F: 'DXT4/DXT5',
    0x10: 'LIN_A1R5G5B5', 0x11: 'LIN_R5G6B5', 0x12: 'LIN_A8R8G8B8', 0x13: 'LIN_L8',
    0x16: 'LIN_R8B8', 0x17: 'LIN_G8B8/V8U8', 0x19: 'A8 (swz)', 0x1A: 'A8L8 (swz)',
    0x1B: 'LIN_AL8', 0x1C: 'LIN_X1R5G5B5', 0x1D: 'LIN_A4R4G4B4', 0x1E: 'LIN_X8R8G8B8',
    0x1F: 'LIN_A8', 0x20: 'LIN_A8L8', 0x24: 'YUY2', 0x25: 'UYVY', 0x27: 'R6G5B5/L6V5U5 (swz)',
    0x28: 'G8B8/V8U8 (swz)', 0x29: 'R8B8 (swz)', 0x2A: 'D24S8', 0x2B: 'F24S8', 0x2C: 'D16',
    0x2D: 'F16', 0x2E: 'LIN_D24S8', 0x2F: 'LIN_F24S8', 0x30: 'LIN_D16', 0x31: 'LIN_F16',
    0x32: 'L16 (swz)', 0x33: 'V16U16 (swz)', 0x35: 'LIN_L16', 0x36: 'LIN_V16U16',
    0x37: 'LIN_R6G5B5', 0x38: 'R5G5B5A1 (swz)', 0x39: 'R4G4B4A4 (swz)', 0x3A: 'A8B8G8R8 (swz)',
    0x3B: 'B8G8R8A8 (swz)', 0x3C: 'R8G8B8A8 (swz)', 0x3D: 'LIN_R5G5B5A1',
    0x3E: 'LIN_R4G4B4A4', 0x3F: 'LIN_A8B8G8R8', 0x40: 'LIN_B8G8R8A8', 0x41: 'LIN_R8G8B8A8',
}
# xbtexdic.c convTable[type == rwRASTERTYPENORMAL][pixel format >> 8]
CONV = [[None, 0x02, 0x05, 0x04, 0x00, 0x06, 0x07, None, None, None, 0x03],
        [None, 0x10, 0x11, 0x1D, 0x13, 0x12, 0x1E, None, None, None, 0x1C]]
RASFMT = {0x000: 'DEFAULT', 0x100: '1555', 0x200: '565', 0x300: '4444', 0x400: 'LUM8',
          0x500: '8888', 0x600: '888', 0x700: '16', 0x800: '24', 0x900: '32', 0xA00: '555'}
RASTYPE = {0: 'NORMAL', 1: 'ZBUFFER', 2: 'CAMERA', 4: 'TEXTURE', 5: 'CAMERATEXTURE'}
PLATFORM = {1: 'D3D7?', 2: 'OpenGL', 3: 'Mac', 4: 'PS2 (old)', 5: 'Xbox (rwID_XBOX)',
            6: 'GameCube', 7: 'SoftRas', 8: 'D3D8', 9: 'D3D9', 0x00325350: "PS2 'PS2\\0'"}
COMP = {0: 'none', 1: 'PBYTE', 2: 'SHORT', 3: 'NORMSHORT', 4: 'NORMPACKED3', 5: 'FLOAT'}
COMPSIZE = {0: 0, 1: 1, 2: 2, 3: 2, 4: 4, 5: 4}
XB_PRIM = {1: 'POINTLIST', 2: 'LINELIST', 3: 'LINELOOP', 4: 'LINESTRIP', 5: 'TRIANGLELIST',
           6: 'TRIANGLESTRIP', 7: 'TRIANGLEFAN', 8: 'QUADLIST', 9: 'QUADSTRIP', 10: 'POLYGON'}


def vsdt3(c):
    return {1: 'D3DVSDT_PBYTE3', 2: 'D3DVSDT_SHORT3', 3: 'D3DVSDT_NORMSHORT3',
            4: 'D3DVSDT_NORMPACKED3', 5: 'D3DVSDT_FLOAT3'}.get(c, '?%d' % c)


def vsdt2(c):
    return {1: 'D3DVSDT_PBYTE2', 2: 'D3DVSDT_SHORT2', 3: 'D3DVSDT_NORMSHORT2',
            4: 'D3DVSDT_NORMPACKED3', 5: 'D3DVSDT_FLOAT2'}.get(c, '?%d' % c)


def decode_vtxfmt(v):
    """RpXboxVtxFmt (xbvtxfmt.h), streamed as one little-endian int32."""
    pos = v & 0xF
    norm = (v >> 4) & 0xF
    tex = (v >> 8) & 0xFFFF
    prelit = (v >> 24) & 1
    bnt = (v >> 25) & 7
    texs = []
    for i in range(4):
        t = (tex >> (4 * i)) & 0xF
        if t == 0:
            break
        texs.append(t)
    stride = 0
    for c in (pos, norm):
        if c:
            stride += 4 if c == 4 else 3 * COMPSIZE.get(c, 0)
    if prelit:
        stride += 4
    if bnt:
        stride += 8
    for t in texs:
        stride += 4 if t == 4 else 2 * COMPSIZE.get(t, 0)
    return dict(pos=pos, norm=norm, tex=texs, prelit=prelit, bnt=bnt, stride=stride,
                reserved=(v >> 28) & 0xF)


def fmt_desc(d):
    parts = ['pos ' + COMP.get(d['pos'], '?')]
    if d['norm']:
        parts.append('nrm ' + COMP.get(d['norm'], '?'))
    if d['prelit']:
        parts.append('diffuse D3DCOLOR')
    for i, t in enumerate(d['tex']):
        parts.append('uv%d %s' % (i, COMP.get(t, '?')))
    if d['bnt']:
        parts.append('binormal+tangent NORMPACKED3 (from uv%d)' % (d['bnt'] - 1))
    return ', '.join(parts) + ' | stride %d' % d['stride']


# ------------------------------------------------------------ library ids
def lib_version(l):
    if l & 0xFFFF0000:
        return (((l >> 14) & 0x3FF00) + 0x30000) | ((l >> 16) & 0x3F)
    return l


def lib_ok(l):
    if l & 0xFFFF0000:
        v = lib_version(l)
        return 0x31000 <= v <= 0x37FFF
    return False   # pre-3.1 stamps: none on this disc


SIG = re.compile(rb'\xff\xff[\x00-\x3f][\x04-\x1c]')   # build 0xFFFF, version 3.1..3.7

# ----------------------------------------------------------------- state
S = dict(
    chunk_types=collections.Counter(), chunk_bytes=collections.Counter(),
    libids=collections.Counter(), ext_plugins=collections.Counter(),
    textures=[], geometries=[], worlds=[], sectors=collections.Counter(),
    sector_native=collections.Counter(), sector_vtx=collections.Counter(),
    plane_sectors=0, dds=[], anomalies=collections.Counter(), files=[],
    nativedata=collections.Counter(), clumps=0, atomics=0, texdicts=0,
    texdict_sizes=[],
)


def note(kind):
    S['anomalies'][kind] += 1


class Ctx:
    def __init__(self, entry):
        self.entry = entry
        self.rw_bytes = 0
        self.dds = 0
        self.top_types = collections.Counter()
        self.sectors = 0


# -------------------------------------------------------------- decoders
def parse_texnative(b, pos, end, ver, ctx):
    if end - pos < 4:
        note('texnative struct too short')
        return
    pid = struct.unpack_from('<I', b, pos)[0]
    t = dict(entry=ctx.entry, platform=pid, version=ver)
    if pid != 5 or end - pos < 72 + 16:
        S['textures'].append(t)
        return
    fa = struct.unpack_from('<I', b, pos + 4)[0]
    name = b[pos + 8:pos + 40].split(b'\0')[0].decode('latin1')
    mask = b[pos + 40:pos + 72].split(b'\0')[0].decode('latin1')
    q = pos + 72
    if ver < 0x34001:
        fmt, alpha, w, h, depth, mips, typ, dxt = struct.unpack_from('<iIHHBBBB', b, q)
        cube, size = 0, None
        q += 16
    else:
        fmt, alpha, cube, w, h, depth, mips, typ, dxt, size = struct.unpack_from('<iHHHHBBBBI', b, q)
        q += 20
    if dxt:
        d3d = dxt
    elif fmt & 0x6000:
        d3d = 0x0B
    else:
        d3d = CONV[1 if typ == 0 else 0][(fmt & 0xF00) >> 8] if ((fmt & 0xF00) >> 8) < 11 else None
    # rwRASTERFORMATPAL8 = 0x2000, rwRASTERFORMATPAL4 = 0x4000 (32-entry palette)
    pal = 'PAL8' if fmt & 0x2000 else ('PAL4' if fmt & 0x4000 else '')
    if pal:
        q += 4 * (256 if pal == 'PAL8' else 32)
    t.update(filter=fa & 0xFF, addrU=(fa >> 8) & 0xF, addrV=(fa >> 12) & 0xF, name=name,
             mask=mask, rasfmt=fmt, alpha=alpha, cube=cube, w=w, h=h, depth=depth, mips=mips,
             type=typ, dxt=dxt, d3d=d3d, pal=pal, size=size,
             automip=bool(fmt & 0x1000), mipflag=bool(fmt & 0x8000))
    if size is not None and q + size > end:
        note('texnative pixel size exceeds struct')
    S['textures'].append(t)


def parse_geometry_struct(b, pos, end, ver):
    if end - pos < 16:
        return None
    flags, ntri, nvert, nmorph = struct.unpack_from('<IiiI', b, pos)
    q = pos + 16
    if ver < 0x34001:
        q += 12
    ntex = (flags >> 16) & 0xFF
    if ntex == 0:
        ntex = 2 if flags & 0x80 else (1 if flags & 0x04 else 0)
    native = bool(flags & 0x01000000)
    g = dict(flags=flags, tris=ntri, verts=nvert, morphs=nmorph, ntex=ntex, native=native,
             prelit=bool(flags & 0x08), normals=bool(flags & 0x10), tristrip=bool(flags & 1),
             light=bool(flags & 0x20), modmat=bool(flags & 0x40), plugins=[], vtxfmt=None,
             nd=None, skin=None, morph_has_verts=0, morph_has_normals=0)
    if not native:
        if flags & 0x08:
            q += 4 * nvert
        q += 8 * nvert * ntex
        q += 8 * ntri
    for m in range(nmorph):
        if q + 24 > end:
            break
        hv, hn = struct.unpack_from('<ii', b, q + 16)
        q += 24
        if hv:
            g['morph_has_verts'] += 1
            q += 12 * nvert
        if hn:
            g['morph_has_normals'] += 1
            q += 12 * nvert
    if q != end:
        g['struct_mismatch'] = (q - pos, end - pos)
    return g


def parse_nativedata(b, pos, end, owner_kind, ctx):
    if end - pos < 8:
        note('native data struct short')
        return None
    pid, size = struct.unpack_from('<II', b, pos)
    nd = dict(platform=pid, size=size)
    if pid == 5 and end - pos >= 8 + 32:
        serial, nmesh, prim, nv, stride = struct.unpack_from('<HHIii', b, pos + 8)
        nd.update(meshes=nmesh, prim=prim, nverts=nv, stride=stride)
        vb = pos + 4 + size
        if vb + stride * nv != end:
            nd['vb_mismatch'] = (vb + stride * nv - pos, end - pos)
    S['nativedata'][(owner_kind, pid, XB_PRIM.get(nd.get('prim'), nd.get('prim')))] += 1
    return nd


def parse_skin(b, pos, end, geom):
    # Xbox native: Struct chunk {rwID_XBOX, numBones, SkinPlatformData(0x810)}, VB, matrices, split
    if end - pos >= 12:
        t, s, l = struct.unpack_from('<III', b, pos)
        if t == 1 and lib_ok(l) and s <= end - pos - 12 and end - pos >= 12 + 8:
            pid, nb = struct.unpack_from('<Ii', b, pos + 12)
            if pid == 5 and s >= 8 + 0x810:
                nbu, maxw, _vb, stride = struct.unpack_from('<iiIi', b, pos + 12 + 8 + 0x800)
                return dict(kind='xbox-native', bones=nb, bonesUsed=nbu, maxWeights=maxw,
                            vbStride=stride)
            return dict(kind='native?', platform=pid)
    if end - pos >= 4:
        nb, nused, maxw, _ = struct.unpack_from('<BBBB', b, pos)
        return dict(kind='generic', bones=nb, bonesUsed=nused, maxWeights=maxw)
    return dict(kind='empty')


# ------------------------------------------------------------- walker
def header_at(b, pos, end):
    if pos + 12 > end:
        return None
    t, s, l = struct.unpack_from('<III', b, pos)
    if s > end - pos - 12:
        return None
    if lib_ok(l) or (0x700 <= t <= 0x7FF and l == 0):
        return t, s, l
    return None


def walk_children(b, pos, end, parent, obj, ctx, depth):
    """Children of a container; returns the list of (type, start, end, ver)."""
    kids = []
    while pos + 12 <= end:
        h = header_at(b, pos, end)
        if h is None:
            note('container %s: bad child header' % chunk_name(parent))
            break
        t, s, l = h
        kids.append(t)
        chunk(b, pos, t, s, l, parent, obj, ctx, depth + 1)
        pos += 12 + s
    if 0 < end - pos < 12:
        note('container %s: trailing bytes' % chunk_name(parent))
    return kids


def chunk(b, pos, t, s, l, parent, obj, ctx, depth):
    ver = lib_version(l)
    S['chunk_types'][t] += 1
    S['chunk_bytes'][t] += s
    S['libids'][l] += 1
    p, end = pos + 12, pos + 12 + s
    if depth > 40:
        note('depth limit')
        return
    if parent == 0x03:
        S['ext_plugins'][(obj.get('kind') if obj else None, t)] += 1
        if obj is not None and 'rec' in obj:
            obj['rec'].setdefault('plugins', []).append(t)
    if t == 0x01:   # Struct: meaning depends on parent
        if parent == 0x15:
            parse_texnative(b, p, end, ver, ctx)
        elif parent == 0x0F and obj is not None:
            g = parse_geometry_struct(b, p, end, ver)
            if g:
                g['entry'] = ctx.entry
                S['geometries'].append(g)
                obj['rec'] = g
        elif parent == 0x0B and obj is not None and end - p >= 40:
            rootws, ox, oy, oz, ntri, nvert, nplane, nsect, colsz, wfmt = \
                struct.unpack_from('<ifffiiiiiI', b, p)
            w = dict(entry=ctx.entry, tris=ntri, verts=nvert, planes=nplane, sectors=nsect,
                     format=wfmt, native=bool(wfmt & 0x01000000), vtxfmt=None, version=ver,
                     sec_native=0, sec_plain=0, sec_count=0)
            S['worlds'].append(w)
            obj['rec'] = w
            obj['world'] = w
        elif parent == 0x09 and obj is not None and end - p >= 44:
            mlb, ntri, nvert = struct.unpack_from('<iii', b, p)
            obj['rec'] = dict(tris=ntri, verts=nvert, native=False)
        elif parent == 0x510 and obj is not None:
            nd = parse_nativedata(b, p, end, obj.get('owner_kind'), ctx)
            if obj.get('owner') is not None:
                obj['owner']['nd'] = nd
        return
    if t == 0x511 and parent == 0x03 and obj is not None and 'rec' in obj and s >= 4:
        v = struct.unpack_from('<I', b, p)[0]
        obj['rec']['vtxfmt'] = v
        return
    if t == 0x116 and parent == 0x03 and obj is not None and 'rec' in obj:
        obj['rec']['skin'] = parse_skin(b, p, end, obj['rec'])
        return
    if t in CONTAINERS:
        if t == 0x0F:
            sub = dict(kind='geometry')
        elif t == 0x0B:
            sub = dict(kind='world')
        elif t == 0x09:
            sub = dict(kind='sector', world=(obj or {}).get('world'))
        elif t == 0x0A:
            S['plane_sectors'] += 1
            sub = dict(kind='plane', world=(obj or {}).get('world'))
        elif t == 0x03:
            sub = obj        # extension belongs to its owner
        elif t == 0x510:
            sub = dict(kind='nd', owner=(obj or {}).get('rec'),
                       owner_kind=(obj or {}).get('kind'))
        elif t == 0x15:
            sub = dict(kind='texnative')
        else:
            sub = dict(kind=chunk_name(t), world=(obj or {}).get('world'))
        if t == 0x10:
            S['clumps'] += 1
        if t == 0x14:
            S['atomics'] += 1
        if t == 0x16:
            S['texdicts'] += 1
            if s >= 12 + 4:
                S['texdict_sizes'].append(struct.unpack_from('<H', b, p + 12)[0])
        if t == 0x510 and parent != 0x03:
            note('0x510 outside an extension')
        walk_children(b, p, end, t, sub, ctx, depth)
        if t == 0x09:
            rec = sub.get('rec') or {}
            w = sub.get('world')
            nd = rec.get('nd')
            S['sectors']['total'] += 1
            ctx.sectors += 1
            S['sectors']['empty (0 verts)' if rec.get('verts', 0) == 0 else 'with vertices'] += 1
            S['sector_native'][('xbox native 0x510' if nd and nd.get('platform') == 5 else
                                'native other' if nd else 'no native data')] += 1
            if 'vtxfmt' in rec and rec['vtxfmt'] is not None:
                S['sector_vtx']['sector has own 0x511'] += 1
            if w is not None:
                w['sec_count'] += 1
                if nd:
                    w['sec_native'] += 1
                else:
                    w['sec_plain'] += 1
        return
    # opaque payload: game/RWS containers may embed RW streams
    if t not in KNOWN_OPAQUE and s >= 24:
        scan_region(b, p, end, ctx, depth + 1, inner=True)


DDS_RE = re.compile(rb'DDS \x7c\x00\x00\x00')


def parse_dds(b, pos, ctx, where):
    if pos + 128 > len(b):
        return
    flags, h, w, pitch, depth, mips = struct.unpack_from('<IIIIII', b, pos + 8)
    pfflags, fourcc, bits = struct.unpack_from('<I4sI', b, pos + 80)
    masks = struct.unpack_from('<IIII', b, pos + 92)
    caps2 = struct.unpack_from('<I', b, pos + 112)[0]
    if pfflags & 4:
        f = fourcc.decode('latin1', 'replace')
    elif pfflags & 0x20:
        f = 'P8'
    elif pfflags & 0x40:
        f = 'RGB%d%s masks %s' % (bits, 'A' if pfflags & 1 else '',
                                  '/'.join('%X' % m for m in (masks if pfflags & 1 else masks[:3])))
    elif pfflags & 0x20000:
        f = 'L%d' % bits
    else:
        f = 'pf 0x%X' % pfflags
    S['dds'].append(dict(entry=ctx.entry, w=w, h=h, mips=max(mips, 1), fmt=f,
                         cube=bool(caps2 & 0x200), volume=bool(caps2 & 0x200000), where=where))
    ctx.dds += 1


def known_type(t):
    return not chunk_name(t).startswith('0x')


def plausible(b, pos, end, h):
    """Extra checks for a header found by resyncing on the library-id stamp."""
    t, s, l = h
    if not known_type(t) or (l & 0xFFFF) != 0xFFFF and not (0x700 <= t <= 0x7FF and l == 0):
        return False
    if t in CONTAINERS and s >= 12:
        return header_at(b, pos + 12, pos + 12 + s) is not None
    return True


def scan_region(b, start, end, ctx, depth, inner=False):
    pos = start
    gaps = []
    while pos + 12 <= end:
        h = header_at(b, pos, end)
        if h is not None and h[0] == 0x4210 and pos + 16 <= end:
            # game clump wrapper (unit_0EBF10 sub_EBF40): header + int32, then the Clump,
            # 0x4211/0x4212/0x4213 follow as siblings; its size field does not bound them
            S['chunk_types'][0x4210] += 1
            ctx.top_types[0x4210] += 1 if depth == 0 else 0
            pos += 16
            continue
        if h is not None and plausible(b, pos, end, h):
            t, s, l = h
            ctx.top_types[t] += 1 if depth == 0 else 0
            ctx.rw_bytes += 12 + s if depth == 0 else 0
            chunk(b, pos, t, s, l, None, None, ctx, depth)
            pos += 12 + s
            continue
        # resync: next 3.x library-id stamp
        m = SIG.search(b, pos + 9, end)
        nxt = None
        while m:
            cand = m.start() - 8
            hc = header_at(b, cand, end) if cand >= pos else None
            if hc and plausible(b, cand, end, hc):
                nxt = cand
                break
            m = SIG.search(b, m.start() + 1, end)
        gend = nxt if nxt is not None else end
        gaps.append((pos, gend))
        if nxt is None:
            break
        pos = nxt
    for g0, g1 in gaps:
        for m in DDS_RE.finditer(b, g0, g1):
            parse_dds(b, m.start(), ctx, 'file start' if m.start() == 0 else 'embedded')


# ------------------------------------------------------------- non-RW census
def classify(b):
    m = b[:4]
    if m == b'DDS ':
        return 'DDS texture'
    if m[:3] == b'BIK':
        return 'Bink video (BIK%s)' % m[3:4].decode('latin1')
    if m == b'\x89PNG':
        return 'PNG image'
    if m == b'RIFF':
        return 'RIFF (%s)' % b[8:12].decode('latin1', 'replace')
    if m in (b'XPR0', b'XPR1', b'XPR2'):
        return 'Xbox packed resource (%s)' % m.decode()
    if m == b'WBND':
        return 'XACT wave bank'
    if m == b'SNR1':
        return "'SNR1' sound data"
    if m == b'METR':
        return "'METRICS1' font metrics text"
    if m == b'NSBF':
        return "'NSBF' bitmap font"
    if m == b'lang':
        return 'language table text'
    if b[:2] in (b'\xff\xfe', b'\xfe\xff'):
        return 'UTF-16 text'
    if len(b) >= 12:
        t, s, l = struct.unpack_from('<III', b, 0)
        if s <= len(b) - 12 and (lib_ok(l) or (0x700 <= t <= 0x7FF and l == 0)):
            return 'RW stream starting with %s' % chunk_name(t)
        if t == len(b) and s == 1 and len(b) >= 16:
            return 'length-prefixed string record (size, 1, ascii id, utf16)'
        if 0 < t < 0x1000 and s < 0x10000 and b[8:16].isascii() is False:
            pass
    if len(b) >= 18 and b[1] in (0, 1) and b[2] in (1, 2, 3, 9, 10, 11) and b[16] in (8, 16, 24, 32):
        w, h = struct.unpack_from('<HH', b, 12)
        if w and h and (b[2] >= 9 or 18 + b[0] + w * h * b[16] // 8 <= len(b)):
            return 'TGA image (type %d, %d bpp)' % (b[2], b[16])
    if len(b) >= 16 and struct.unpack_from('<I', b, 0)[0] < 64 and b'.dds\0' in b[:4096]:
        return 'DDS archive (count + names + DDS files)'
    if all(32 <= c < 127 or c in (9, 10, 13) for c in b[:256]):
        return 'plain text'
    return 'unknown (first dword 0x%08X)' % struct.unpack_from('<I', b.ljust(4, b'\0'), 0)[0]


# ------------------------------------------------------------------- main
def main():
    """Walk the extracted tree (ROOT); every file is scanned for RW chunks."""
    paths = []
    for dp, dn, fn in os.walk(ROOT):
        dn.sort()
        for x in sorted(fn):
            paths.append(os.path.relpath(os.path.join(dp, x), ROOT))
    for i, rel in enumerate(paths):
        with open(os.path.join(ROOT, rel), 'rb') as fh:
            b = fh.read()
        ctx = Ctx(i)
        cls = classify(b)
        scan_region(b, 0, len(b), ctx, 0)
        S['files'].append(dict(entry=i, size=len(b), cls=cls, rw_bytes=ctx.rw_bytes,
                               dds=ctx.dds, sectors=ctx.sectors, top=sorted(ctx.top_types), name=rel,
                               kind=kind_of(rel),
                               tga=struct.unpack_from('<HH', b, 12) if cls.startswith('TGA') else None))
    report(len(paths))


def kind_of(name):
    """Asset kind: top directory (LEVELS/*/<sub> for levels) + extension."""
    parts = name.replace('/', os.sep).split(os.sep)
    ext = os.path.splitext(parts[-1])[1].lower() or '(none)'
    if parts[0] == '__hashed':
        return '__hashed (no name)'
    top = parts[0].upper() if len(parts) > 1 else '(root)'
    if top == 'LEVELS' and len(parts) > 3:
        top = 'LEVELS/*/' + parts[2].upper()
    elif top == 'LEVELS':
        top = 'LEVELS/*'
    elif top in ('ANIMGRPS', 'SB_AGD', 'SB_AWD'):
        top += '/*'
    return '%s/ %s' % (top, ext) if top != '(root)' else '(root) ' + ext


def human(n):
    for u in ('B', 'KB', 'MB', 'GB'):
        if n < 1024:
            return '%.1f %s' % (n, u) if u != 'B' else '%d B' % n
        n /= 1024
    return '%.1f TB' % n


def table(rows, head):
    out = ['| ' + ' | '.join(head) + ' |', '|' + '---|' * len(head)]
    for r in rows:
        out.append('| ' + ' | '.join(str(x) for x in r) + ' |')
    return '\n'.join(out)


def report(n):
    L = []
    A = L.append
    A('# Game data formats - inventory for a PC Direct3D 9 port\n')
    A('Generated by `scan_disc.py` from the extracted tree `%s` (%d files). RenderWare chunks '
      'are found by walking each file and resyncing on the 3.x library-id stamp, so RW streams '
      'embedded in game / RenderWare Studio containers are counted too. Payload byte totals '
      'include nested chunks.\n' % (ROOT, n))
    plat = collections.Counter()
    for t in S['textures']:
        plat[PLATFORM.get(t['platform'], '0x%X' % t['platform'])] += 1
    if len(plat) > 1:
        A('> **Warning: mixed platforms in this tree.** Texture natives by platform: ' +
          ', '.join('%s %d' % kv for kv in plat.most_common()) + '. The Xbox tables below '
          'count only platform 5 (rwID_XBOX) data; see section 5 for which files carry '
          'which platform.\n')
    A('Library ids seen: ' + ', '.join('0x%08X (RW %X) x%d' % (l, lib_version(l), c)
                                        for l, c in S['libids'].most_common(6)) + '\n')

    # ---------------- textures
    tex = S['textures']
    xb = [t for t in tex if t['platform'] == 5 and 'w' in t]
    A('## 1. Texture natives (0x15)\n')
    A('Struct layout per `src/rw/driver/xbox/xbtexdic.c` (_rwXbNativeTexture + '
      '_rwXbNativeRaster): platform id, filter/addressing, name[32], mask[32], raster format '
      'flags, alpha u16, cube u16, width u16, height u16, depth u8, mip levels u8, raster type '
      'u8, dxtFormat u8 (an Xbox D3DFORMAT, nonzero = used verbatim), pixel data size u32. '
      'When dxtFormat is 0 the D3D format is P8 for PAL4/PAL8 rasters, otherwise '
      '`convTable[type == NORMAL][pixfmt >> 8]` (swizzled for TEXTURE rasters, linear for '
      'NORMAL ones). Format names verified against `C:\\xdk\\xbox\\include\\D3D8Types.h`.\n')
    pc = collections.Counter(t['platform'] for t in tex)
    A(table([(PLATFORM.get(p, '0x%X' % p), c) for p, c in pc.most_common()],
            ['platform id', 'texture natives']))
    A('\nTexture dictionaries: %d (texture counts per dictionary: min %s, max %s).\n' % (
        S['texdicts'], min(S['texdict_sizes'], default='-'), max(S['texdict_sizes'], default='-')))
    by = collections.defaultdict(list)
    for t in xb:
        by[t['d3d']].append(t)
    rows = []
    for k, lst in sorted(by.items(), key=lambda kv: -len(kv[1])):
        mw = max(lst, key=lambda t: t['w'] * t['h'])
        src = collections.Counter('dxtFormat' if t['dxt'] else ('palette' if t['pal'] else
                                  'convTable ' + RASFMT.get(t['rasfmt'] & 0xF00, '?')) for t in lst)
        rows.append(('0x%02X' % k if k is not None else 'unmapped',
                     XB_D3DFMT.get(k, '?') if k is not None else '-', len(lst),
                     '%dx%d' % (mw['w'], mw['h']),
                     sum(1 for t in lst if t['mips'] > 1),
                     sum(1 for t in lst if t['cube']),
                     human(sum(t['size'] or 0 for t in lst)),
                     ', '.join('%s %d' % kv for kv in src.most_common())))
    A(table(rows, ['Xbox D3DFORMAT', 'name', 'textures', 'largest', 'with mips', 'cube',
                   'pixel bytes', 'derived from']))
    A('')
    A('Raster type / format flags (Xbox natives):\n')
    rt = collections.Counter((RASTYPE.get(t['type'], t['type']),
                              RASFMT.get(t['rasfmt'] & 0xF00, '?'), t['pal'] or '-',
                              'MIPMAP' if t['mipflag'] else '-', 'AUTOMIPMAP' if t['automip'] else '-',
                              t['depth']) for t in xb)
    A(table([k + (c,) for k, c in rt.most_common()],
            ['raster type', 'pixel format', 'palette', 'mip flag', 'automip', 'depth', 'count']))
    if xb:
        A('')
        mx = max(xb, key=lambda t: max(t['w'], t['h']))
        A('- Max dimensions: %dx%d (`%s`); max width %d, max height %d.' % (
            mx['w'], mx['h'], mx['name'], max(t['w'] for t in xb), max(t['h'] for t in xb)))
        np2 = [t for t in xb if (t['w'] & (t['w'] - 1)) or (t['h'] & (t['h'] - 1))]
        A('- Non-power-of-two: %d (%s).' % (len(np2), ', '.join(
            '%s %dx%d %s' % (t['name'], t['w'], t['h'], XB_D3DFMT.get(t['d3d'], '?')) for t in np2[:8])))
        A('- Cube maps: %d. Palettized: %d (PAL8 %d, PAL4 %d). Alpha flag set: %d.' % (
            sum(1 for t in xb if t['cube']), sum(1 for t in xb if t['pal']),
            sum(1 for t in xb if t['pal'] == 'PAL8'), sum(1 for t in xb if t['pal'] == 'PAL4'),
            sum(1 for t in xb if t['alpha'])))
        mc = collections.Counter(t['mips'] for t in xb)
        A('- Mip level counts: ' + ', '.join('%d: %d' % kv for kv in sorted(mc.items())) + '.')
        sc = collections.Counter(max(t['w'], t['h']) for t in xb)
        A('- Largest side histogram: ' + ', '.join('%d: %d' % kv for kv in sorted(sc.items())) + '.')
        A('- Filter modes: ' + ', '.join('%d: %d' % kv for kv in sorted(
            collections.Counter(t['filter'] for t in xb).items())) + '; addressing U/V: ' + ', '.join(
            '%d/%d: %d' % (k[0], k[1], c) for k, c in sorted(
                collections.Counter((t['addrU'], t['addrV']) for t in xb).items())) + '.')
        A('- Stream versions: ' + ', '.join('%X: %d' % kv for kv in sorted(
            collections.Counter(t['version'] for t in xb).items())) + '.')
        A('- Textures with a mask name: %d.' % sum(1 for t in xb if t['mask']))
    A('')

    # DDS
    A('### Standalone / embedded DDS files\n')
    dd = S['dds']
    A('%d DDS images (%d entries are plain DDS files, the rest sit inside game archives).\n' % (
        len(dd), sum(1 for d in dd if d['where'] == 'file start')))
    dc = collections.defaultdict(list)
    for d in dd:
        dc[d['fmt']].append(d)
    A(table([(k, len(v), '%dx%d' % max(((d['w'], d['h']) for d in v), key=lambda x: x[0] * x[1]),
              sum(1 for d in v if d['mips'] > 1), sum(1 for d in v if d['cube']))
             for k, v in sorted(dc.items(), key=lambda kv: -len(kv[1]))],
            ['DDS pixel format', 'count', 'largest', 'with mips', 'cube']))
    A('')

    # ---------------- geometry
    G = S['geometries']
    A('## 2. Geometry (0x0F)\n')
    A('%d geometries (%d clumps, %d atomics).\n' % (len(G), S['clumps'], S['atomics']))
    rows = [
        ('native (rpGEOMETRYNATIVE 0x01000000, no generic vertex data on disc)', sum(g['native'] for g in G)),
        ('generic (RW vertex arrays on disc)', sum(not g['native'] for g in G)),
        ('with Xbox vertex-format plugin 0x511', sum(g['vtxfmt'] is not None for g in G)),
        ('without 0x511', sum(g['vtxfmt'] is None for g in G)),
        ('with native data 0x510 (Xbox instanced VB + IB)', sum(g['nd'] is not None for g in G)),
        ('native flag but no 0x510', sum(g['native'] and g['nd'] is None for g in G)),
        ('skinned (0x116)', sum(g['skin'] is not None for g in G)),
        ('  skin Xbox native', sum(1 for g in G if g['skin'] and g['skin']['kind'] == 'xbox-native')),
        ('  skin generic', sum(1 for g in G if g['skin'] and g['skin']['kind'] == 'generic')),
        ('morph targets > 1', sum(g['morphs'] > 1 for g in G)),
        ('prelit (flag)', sum(g['prelit'] for g in G)),
        ('normals (flag)', sum(g['normals'] for g in G)),
        ('tristrip (flag)', sum(g['tristrip'] for g in G)),
        ('struct size mismatch (decoder check)', sum('struct_mismatch' in g for g in G)),
    ]
    A(table(rows, ['geometries', 'count']))
    A('')
    A('UV set counts: ' + ', '.join('%d sets: %d' % kv for kv in sorted(
        collections.Counter(g['ntex'] for g in G).items())) + '.')
    A('Morph target counts: ' + ', '.join('%d: %d' % kv for kv in sorted(
        collections.Counter(g['morphs'] for g in G).items())) + '.\n')
    A('Max vertices in one geometry: %d; max triangles: %d.\n' % (
        max((g['verts'] for g in G), default=0), max((g['tris'] for g in G), default=0)))

    A('### Xbox vertex formats (0x511, RpXboxVtxFmt)\n')
    A('Decoded per `xbvtxfmt.h`: pos:4, norm:4, texCoord:16 (four 4-bit types), prelit:1, '
      'bnt:3; component types none/PBYTE/SHORT/NORMSHORT/NORMPACKED3/FLOAT map to '
      'D3DVSDT_PBYTE3|SHORT3|NORMSHORT3|NORMPACKED3|FLOAT3 (positions, normals) and '
      'D3DVSDT_PBYTE2|SHORT2|NORMSHORT2|NORMPACKED3|FLOAT2 (uvs); prelit = D3DCOLOR; bnt adds '
      'two NORMPACKED3 registers (binormal, tangent).\n')
    vf = collections.Counter()
    vfs = collections.defaultdict(collections.Counter)
    for g in G:
        if g['vtxfmt'] is not None:
            vf[('geometry', g['vtxfmt'])] += 1
            if g['nd'] and 'stride' in g['nd']:
                vfs[('geometry', g['vtxfmt'])][g['nd']['stride']] += 1
    for w in S['worlds']:
        if w['vtxfmt'] is not None:
            vf[('world', w['vtxfmt'])] += 1
    rows = []
    for (owner, v), c in vf.most_common():
        d = decode_vtxfmt(v)
        st = vfs.get((owner, v))
        rows.append((owner, '0x%08X' % v, fmt_desc(d), c,
                     ', '.join('%d: %d' % kv for kv in st.items()) if st else '-'))
    A(table(rows, ['owner', 'raw', 'elements', 'count', 'native VB strides seen']))
    A('')
    el = collections.Counter()
    for (owner, v), c in vf.items():
        d = decode_vtxfmt(v)
        if d['pos']:
            el['position ' + vsdt3(d['pos'])] += c
        if d['norm']:
            el['normal ' + vsdt3(d['norm'])] += c
        if d['prelit']:
            el['diffuse D3DVSDT_D3DCOLOR'] += c
        for t in d['tex']:
            el['texcoord ' + vsdt2(t)] += c
        if d['bnt']:
            el['binormal+tangent D3DVSDT_NORMPACKED3'] += c
    A('Vertex element types (formats weighted by objects using them):\n')
    A(table(el.most_common(), ['element / Xbox type', 'objects']))
    A('')
    A('### Native data (0x510) instanced vertex buffers\n')
    A(table([(k[0], PLATFORM.get(k[1], k[1]), k[2], c) for k, c in S['nativedata'].most_common()],
            ['owner', 'platform', 'primitive type', 'count']))
    strides = collections.Counter()
    for g in G:
        if g['nd'] and 'stride' in g['nd']:
            strides[g['nd']['stride']] += 1
    A('\nGeometry native VB strides: ' + ', '.join('%d: %d' % kv for kv in sorted(strides.items())) + '.')
    A('Native data whose VB size disagrees with stride*numVertices: %d.\n' % sum(
        1 for g in G if g['nd'] and 'vb_mismatch' in g['nd']))
    sk = [g['skin'] for g in G if g['skin'] and g['skin']['kind'] == 'xbox-native']
    if sk:
        A('Xbox native skins: %d; max bones %d; maxWeightsUsed %s; weights+indices VB strides %s.\n' % (
            len(sk), max(s['bones'] for s in sk),
            dict(collections.Counter(s['maxWeights'] for s in sk)),
            dict(collections.Counter(s['vbStride'] for s in sk))))
    skg = [g['skin'] for g in G if g['skin'] and g['skin']['kind'] == 'generic']
    if skg:
        A('Generic skins: %d; max bones %d; maxWeights %s.\n' % (
            len(skg), max(s['bones'] for s in skg),
            dict(collections.Counter(s['maxWeights'] for s in skg))))

    # ---------------- worlds
    W = S['worlds']
    A('## 3. Worlds / BSP\n')
    A('%d worlds, %d atomic (world) sectors, %d plane sectors.\n' % (
        len(W), S['sectors']['total'], S['plane_sectors']))
    A(table([(k, v) for k, v in S['sectors'].items()] +
            [(k, v) for k, v in S['sector_native'].items()] +
            [(k, v) for k, v in S['sector_vtx'].items()], ['sectors', 'count']))
    A('')
    A(table([('native flag (rpWORLDNATIVE)', sum(w['native'] for w in W)),
             ('with Xbox vertex format 0x511', sum(w['vtxfmt'] is not None for w in W)),
             ('all sectors native', sum(1 for w in W if w['sec_count'] and w['sec_plain'] == 0)),
             ('mixed', sum(1 for w in W if w['sec_native'] and w['sec_plain'])),
             ('no native sectors', sum(1 for w in W if w['sec_native'] == 0))],
            ['worlds', 'count']))
    A('')
    A('Largest world: %s.\n' % (max(((w['verts'], w['tris'], w['sectors'], S['files'][w['entry']]['name']) for w in W),
                                     default=None),) + ' (verts, tris, sectors, file)\n')

    # ---------------- other xbox / plugins
    A('## 4. Plugins and other Xbox-native chunks\n')
    A('Extension plugin chunks by owner object:\n')
    A(table([(o or '?', '0x%X' % t, chunk_name(t), c) for (o, t), c in
             sorted(S['ext_plugins'].items(), key=lambda kv: (str(kv[0][0]), -kv[1]))],
            ['owner', 'id', 'name', 'count']))
    A('')
    A('All chunk types seen (any depth):\n')
    A(table([('0x%X' % t, chunk_name(t), c, human(S['chunk_bytes'][t]))
             for t, c in sorted(S['chunk_types'].items())], ['id', 'name', 'count', 'payload bytes']))
    A('')
    if S['anomalies']:
        A('Decoder notes (unparsed / tolerated): ' + '; '.join(
            '%s x%d' % kv for kv in S['anomalies'].most_common(15)) + '\n')

    # ---------------- files
    A('## 5. Pack entry census\n')
    fc = collections.defaultdict(list)
    for fl in S['files']:
        fc[fl['cls']].append(fl)
    A(table([(k, len(v), human(sum(x['size'] for x in v)),
              human(sum(x['rw_bytes'] for x in v)), sum(x['dds'] for x in v))
             for k, v in sorted(fc.items(), key=lambda kv: -sum(x['size'] for x in kv[1]))],
            ['class (by leading bytes)', 'entries', 'bytes', 'RW top-level chunk bytes', 'DDS inside']))
    A('')
    A('Entries containing RenderWare chunks anywhere: %d of %d.\n' % (
        sum(1 for fl in S['files'] if fl['top']), n))
    open(OUT, 'w', encoding='utf-8').write('\n'.join(L) + '\n')
    json.dump(dict(textures=xb, geometries=G, worlds=W, dds=dd),
              open(OUT.rsplit('.', 1)[0] + '.json', 'w'), default=str)
    print('wrote', OUT)


if __name__ == '__main__':
    main()
