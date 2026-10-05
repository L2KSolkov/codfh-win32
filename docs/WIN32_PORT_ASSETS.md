# Win32 port, appendix B: the disc's data formats (measured)

The formats the Direct3D 9 bridge must translate, measured by `tools/port/scan_assets.py` over the
Xbox data: the disc's `COD.PAK` (1,372 entries) and an extracted copy of it
(`C:\codfh\GameData\Extracted`), which give identical figures. RenderWare chunks are found by walking
each file and resyncing on the 3.x library-id stamp, so streams embedded in game and RenderWare Studio
containers are counted too. (A tree at `D:\FH_Extract` holds PlayStation 2 textures, not this data.)
Plan: [WIN32_PORT.md](WIN32_PORT.md) section 7.

Library ids seen: 0x1803FFFF (RW 3.6.0.3) x738,396, 0x1802FFFF (RW 3.6.0.2) x19,491, 0 (game chunks) x157,214.

## 1. Texture natives (0x15)

Struct layout per `src/rw/driver/xbox/xbtexdic.c` (_rwXbNativeTexture + _rwXbNativeRaster): platform id, filter/addressing, name[32], mask[32], raster format flags, alpha u16, cube u16, width u16, height u16, depth u8, mip levels u8, raster type u8, dxtFormat u8 (an Xbox D3DFORMAT, nonzero = used verbatim), pixel data size u32. When dxtFormat is 0 the D3D format is P8 for PAL4/PAL8 rasters, otherwise `convTable[type == NORMAL][pixfmt >> 8]` (swizzled for TEXTURE rasters, linear for NORMAL ones). Format names verified against `C:\xdk\xbox\include\D3D8Types.h`.

| platform id | texture natives |
|---|---|
| Xbox (rwID_XBOX) | 15695 |

Texture dictionaries: 2969 (texture counts per dictionary: min 0, max 285).

| Xbox D3DFORMAT | name | textures | largest | with mips | cube | pixel bytes | derived from |
|---|---|---|---|---|---|---|---|
| 0x0B | P8 (swz) | 15448 | 512x512 | 1042 | 0 | 232.8 MB | palette 15448 |
| 0x07 | X8R8G8B8 (swz) | 169 | 512x512 | 1 | 0 | 32.1 MB | convTable 888 169 |
| 0x06 | A8R8G8B8 (swz) | 78 | 256x256 | 0 | 0 | 2.1 MB | convTable 8888 78 |

Raster type / format flags (Xbox natives):

| raster type | pixel format | palette | mip flag | automip | depth | count |
|---|---|---|---|---|---|---|
| TEXTURE | 888 | PAL4 | - | - | 8 | 7136 |
| TEXTURE | 888 | PAL8 | - | - | 8 | 4278 |
| TEXTURE | 8888 | PAL8 | - | - | 8 | 2424 |
| TEXTURE | 888 | PAL4 | MIPMAP | - | 8 | 789 |
| TEXTURE | 8888 | PAL4 | - | - | 8 | 568 |
| TEXTURE | 888 | - | - | - | 32 | 168 |
| TEXTURE | 888 | PAL8 | MIPMAP | - | 8 | 133 |
| TEXTURE | 8888 | PAL8 | MIPMAP | - | 8 | 120 |
| TEXTURE | 8888 | - | - | - | 32 | 78 |
| TEXTURE | 888 | - | MIPMAP | - | 32 | 1 |

- Max dimensions: 512x16 (`wood_board_long`); max width 512, max height 512.
- Non-power-of-two: 0 ().
- Cube maps: 0. Palettized: 15448 (PAL8 6955, PAL4 8493). Alpha flag set: 3190.
- Mip level counts: 1: 14652, 5: 3, 6: 51, 7: 220, 8: 388, 9: 373, 10: 8.
- Largest side histogram: 4: 76, 8: 90, 16: 170, 32: 2748, 64: 4699, 128: 5212, 256: 2494, 512: 206.
- Filter modes: 1: 5, 2: 14673, 4: 1017; addressing U/V: 1/1: 15695.
- Stream versions: 36003: 15695.
- Textures with a mask name: 4.

### Standalone / embedded DDS files

154 DDS images (97 entries are plain DDS files, the rest sit inside game archives).

| DDS pixel format | count | largest | with mips | cube |
|---|---|---|---|---|
| DXT5 | 145 | 1024x512 | 0 | 0 |
| DXT1 | 8 | 512x256 | 0 | 0 |
| RGB32A masks FF0000/FF00/FF/FF000000 | 1 | 2x2 | 0 | 0 |

## 2. Geometry (0x0F)

7764 geometries (3366 clumps, 7764 atomics).

| geometries | count |
|---|---|
| native (rpGEOMETRYNATIVE 0x01000000, no generic vertex data on disc) | 7355 |
| generic (RW vertex arrays on disc) | 409 |
| with Xbox vertex-format plugin 0x511 | 7355 |
| without 0x511 | 409 |
| with native data 0x510 (Xbox instanced VB + IB) | 7355 |
| native flag but no 0x510 | 0 |
| skinned (0x116) | 4213 |
|   skin Xbox native | 4064 |
|   skin generic | 149 |
| morph targets > 1 | 0 |
| prelit (flag) | 1793 |
| normals (flag) | 7764 |
| tristrip (flag) | 7764 |
| struct size mismatch (decoder check) | 0 |

UV set counts: 0 sets: 273, 1 sets: 7491.
Morph target counts: 1: 7764.

Max vertices in one geometry: 14660; max triangles: 17757.

### Xbox vertex formats (0x511, RpXboxVtxFmt)

Decoded per `xbvtxfmt.h`: pos:4, norm:4, texCoord:16 (four 4-bit types), prelit:1, bnt:3; component types none/PBYTE/SHORT/NORMSHORT/NORMPACKED3/FLOAT map to D3DVSDT_PBYTE3|SHORT3|NORMSHORT3|NORMPACKED3|FLOAT3 (positions, normals) and D3DVSDT_PBYTE2|SHORT2|NORMSHORT2|NORMPACKED3|FLOAT2 (uvs); prelit = D3DCOLOR; bnt adds two NORMPACKED3 registers (binormal, tangent).

| owner | raw | elements | count | native VB strides seen |
|---|---|---|---|---|
| geometry | 0x00000545 | pos FLOAT, nrm NORMPACKED3, uv0 FLOAT | stride 24 | 5561 | 24: 5561 |
| geometry | 0x01000545 | pos FLOAT, nrm NORMPACKED3, diffuse D3DCOLOR, uv0 FLOAT | stride 28 | 1693 | 28: 1693 |
| world | 0x01000505 | pos FLOAT, diffuse D3DCOLOR, uv0 FLOAT | stride 24 | 870 | - |
| geometry | 0x00000045 | pos FLOAT, nrm NORMPACKED3 | stride 16 | 97 | 16: 97 |
| geometry | 0x01000045 | pos FLOAT, nrm NORMPACKED3, diffuse D3DCOLOR | stride 20 | 4 | 20: 4 |

Vertex element types (formats weighted by objects using them):

| element / Xbox type | objects |
|---|---|
| position D3DVSDT_FLOAT3 | 8225 |
| texcoord D3DVSDT_FLOAT2 | 8124 |
| normal D3DVSDT_NORMPACKED3 | 7355 |
| diffuse D3DVSDT_D3DCOLOR | 2567 |

### Native data (0x510) instanced vertex buffers

| owner | platform | primitive type | count |
|---|---|---|---|
| geometry | Xbox (rwID_XBOX) | TRIANGLESTRIP | 7184 |
| sector | Xbox (rwID_XBOX) | TRIANGLESTRIP | 1976 |
| geometry | Xbox (rwID_XBOX) | TRIANGLELIST | 171 |
| sector | Xbox (rwID_XBOX) | TRIANGLELIST | 44 |

Geometry native VB strides: 16: 97, 20: 4, 24: 5561, 28: 1693.
Native data whose VB size disagrees with stride*numVertices: 0.

Xbox native skins: 4064; max bones 56; maxWeightsUsed {1: 3080, 3: 563, 2: 421}; weights+indices VB strides {3: 3080, 9: 563, 6: 421}.

Generic skins: 149; max bones 33; maxWeights {1: 122, 2: 20, 3: 7}.

## 3. Worlds / BSP

1257 worlds, 10317 atomic (world) sectors, 9042 plane sectors.

| sectors | count |
|---|---|
| total | 10317 |
| with vertices | 4849 |
| empty (0 verts) | 5468 |
| xbox native 0x510 | 2020 |
| no native data | 8297 |

| worlds | count |
|---|---|
| native flag (rpWORLDNATIVE) | 870 |
| with Xbox vertex format 0x511 | 870 |
| all sectors native | 537 |
| mixed | 333 |
| no native sectors | 387 |

Largest world: (37149, 29702, 30, 'LEVELS\\L_2_2_B\\SECTIONS\\s_4.rws').
 (verts, tris, sectors, file)

## 4. Plugins and other Xbox-native chunks

Extension plugin chunks by owner object:

| owner | id | name | count |
|---|---|---|---|
| Atomic | 0x1F | Right To Render | 4253 |
| Atomic | 0x120 | rwID_MATERIALEFFECTSPLUGIN | 137 |
| Frame List | 0x11E | rwID_HANIMPLUGIN | 32245 |
| Frame List | 0x11F | rwID_USERDATAPLUGIN | 8 |
| Material | 0x7A7 | game material plugin (unit_0FB7A0) | 10885 |
| Material | 0x120 | rwID_MATERIALEFFECTSPLUGIN | 285 |
| Material | 0x135 | rwID_UVANIMPLUGIN | 134 |
| ? | 0x50E | rwID_BINMESHPLUGIN | 1 |
| ? | 0x11D | rwID_COLLISPLUGIN | 1 |
| Texture | 0x110 | rwID_SKYMIPMAPVAL | 10494 |
| geometry | 0x50E | rwID_BINMESHPLUGIN | 7764 |
| geometry | 0x510 | rwID_NATIVEDATAPLUGIN (0x510) | 7355 |
| geometry | 0x511 | rwID_VERTEXFMTPLUGIN (Xbox, 0x511) | 7355 |
| geometry | 0x11F | rwID_USERDATAPLUGIN | 5859 |
| geometry | 0x116 | rwID_SKINPLUGIN | 4213 |
| sector | 0x50E | rwID_BINMESHPLUGIN | 10317 |
| sector | 0x11D | rwID_COLLISPLUGIN | 2829 |
| sector | 0x510 | rwID_NATIVEDATAPLUGIN (0x510) | 2020 |
| world | 0x511 | rwID_VERTEXFMTPLUGIN (Xbox, 0x511) | 870 |

All chunk types seen (any depth):

| id | name | count | payload bytes |
|---|---|---|---|
| 0x1 | Struct | 190221 | 617.5 MB |
| 0x2 | String | 86702 | 912.5 KB |
| 0x3 | Extension | 174541 | 267.1 MB |
| 0x6 | Texture | 43351 | 3.2 MB |
| 0x7 | Material | 45096 | 6.1 MB |
| 0x8 | Material List | 9025 | 7.0 MB |
| 0x9 | Atomic Sector | 10317 | 226.4 MB |
| 0xA | Plane Sector | 9042 | 918.9 MB |
| 0xB | World | 1257 | 230.5 MB |
| 0xC | Spline | 1154 | 229.9 KB |
| 0xD | Matrix | 7714 | 482.1 KB |
| 0xE | Frame List | 3366 | 3.6 MB |
| 0xF | Geometry | 7764 | 79.0 MB |
| 0x10 | Clump | 3366 | 83.3 MB |
| 0x14 | Atomic | 7764 | 388.5 KB |
| 0x15 | Texture Native | 15695 | 276.6 MB |
| 0x16 | Texture Dictionary | 2969 | 276.8 MB |
| 0x18 | Image | 8 | 14.3 KB |
| 0x1A | Geometry List | 3366 | 79.1 MB |
| 0x1B | Anim Animation | 61 | 171.6 KB |
| 0x1F | Right To Render | 4253 | 33.2 KB |
| 0x23 | PI Texture Dictionary | 8 | 15.2 KB |
| 0x2B | UV Anim Dict | 91 | 173.8 KB |
| 0x110 | rwID_SKYMIPMAPVAL | 10494 | 41.0 KB |
| 0x116 | rwID_SKINPLUGIN | 4213 | 24.6 MB |
| 0x11D | rwID_COLLISPLUGIN | 2830 | 18.1 MB |
| 0x11E | rwID_HANIMPLUGIN | 32245 | 777.3 KB |
| 0x11F | rwID_USERDATAPLUGIN | 5867 | 287.8 KB |
| 0x120 | rwID_MATERIALEFFECTSPLUGIN | 422 | 3.9 KB |
| 0x135 | rwID_UVANIMPLUGIN | 134 | 6.3 KB |
| 0x1A9 | rwID_2DANIM | 80 | 60.9 KB |
| 0x1B0 | rwID_2DKEYFRAME | 15 | 1.8 KB |
| 0x1B1 | rwID_2DMAESTRO | 3 | 411.2 KB |
| 0x50E | rwID_BINMESHPLUGIN | 18082 | 13.1 MB |
| 0x510 | rwID_NATIVEDATAPLUGIN (0x510) | 9375 | 209.0 MB |
| 0x511 | rwID_VERTEXFMTPLUGIN (Xbox, 0x511) | 8225 | 32.1 KB |
| 0x704 | RWS strfunc_CreateEntity | 18159 | 18.6 MB |
| 0x716 | RWS strfunc_LoadEmbeddedAsset | 1276 | 5.4 MB |
| 0x719 | RWS CustomData (game: level section streaming) | 157214 | 154.2 MB |
| 0x71C | RWS strfunc_PlacementNew | 56 | 26.9 KB |
| 0x7A7 | game material plugin (unit_0FB7A0) | 10885 | 42.5 KB |
| 0x4210 | game clump plugin (unit_0EBF10) | 939 | 0 B |
| 0x4211 | game tagged matrices (clumpdata) | 2718 | 641.6 KB |
| 0x4212 | game chunk 0x4212 | 2718 | 376.9 KB |
| 0x4213 | game chunk 0x4213 | 2718 | 11.8 KB |
| 0x42A0 | game chunk 0x42A0 | 142 | 1.0 MB |
| 0x42A1 | game 'ADST' set (unit_0770C0) | 99 | 1.2 KB |

Decoder notes (unparsed / tolerated): container Material List: bad child header x4

## 5. Files by type (extracted tree)

Extensions marked * are not disc data: the extraction tool added them (texture exports and dumps).

| extension | files | MB |
|---|---|---|
| .rws | 429 | 397.7 |
| .dff | 83 | 189.0 |
| .ads | 270 | 138.1 |
| .png * | 7101 | 74.3 |
| .txt * | 2 | 72.4 |
| .txd | 73 | 46.5 |
| .bin | 73 | 36.8 |
| (none) | 67 | 31.6 |
| .dds | 97 | 15.5 |
| .tga * | 22 | 10.3 |
| .bds | 1 | 7.0 |
| .rel | 1 | 1.2 |
| .layout | 116 | 0.5 |
| .anm | 3 | 0.5 |
| .loc | 42 | 0.3 |
| .met | 38 | 0.2 |
| .csv | 4 | 0.1 |
| .index | 89 | 0.0 |
| .py * | 1 | 0.0 |
| .ini * | 2 | 0.0 |

| folder | files | MB |
|---|---|---|
| LEVELS | 7673 | 765.0 |
| ANIMGRPS | 271 | 138.1 |
| SHELL | 125 | 48.5 |
| (root) | 330 | 33.4 |
| __hashed | 30 | 31.4 |
| WPNBANK | 42 | 5.4 |
| LOC | 43 | 0.3 |

Outside `COD.PAK`, on the disc root: `SB_AWD` and `SB_AGD` (RenderWare Audio wave and group dictionaries),
`AUDIO`, `SHELL\MOVIES` (Bink), `DATA\dsstdfx.bin` (the DSP effects image) and the vertex-shader microcode
files `particle.xvu`, `clones.xvu`, `clonesPL.xvu`. Their audio codecs are not yet inventoried
(WIN32_PORT.md W3.3).
