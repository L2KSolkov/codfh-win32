/*
 * Win32 port bridge (docs/WIN32_PORT.md W2): the Xbox Direct3D constants the sources use, with
 * their Xbox values. The values are the Xbox's, not Direct3D 9's: the disc's texture
 * dictionaries and native geometry store Xbox formats and vertex element types, and the driver's
 * state tables are indexed by Xbox render-state and texture-stage-state numbers. The bridge
 * (port/d3d9bridge) translates them to Direct3D 9 where it hands them on; only it sees d3d9.h.
 *
 * The list is the names the sources use; the values were read from a probe compiled against the
 * XDK (5849), so each one is the number the Xbox build compiled.
 */
#ifndef PORT_D3D8VALUES_H
#define PORT_D3D8VALUES_H

/* D3DRS_* */
#define D3DRS_ZFUNC                              0x39
#define D3DRS_ALPHAFUNC                          0x3A
#define D3DRS_ALPHABLENDENABLE                   0x3B
#define D3DRS_ALPHATESTENABLE                    0x3C
#define D3DRS_ALPHAREF                           0x3D
#define D3DRS_SRCBLEND                           0x3E
#define D3DRS_DESTBLEND                          0x3F
#define D3DRS_ZWRITEENABLE                       0x40
#define D3DRS_DITHERENABLE                       0x41
#define D3DRS_SHADEMODE                          0x42
#define D3DRS_COLORWRITEENABLE                   0x43
#define D3DRS_STENCILZFAIL                       0x44
#define D3DRS_STENCILPASS                        0x45
#define D3DRS_STENCILFUNC                        0x46
#define D3DRS_STENCILREF                         0x47
#define D3DRS_STENCILMASK                        0x48
#define D3DRS_STENCILWRITEMASK                   0x49
#define D3DRS_BLENDOP                            0x4A
#define D3DRS_BLENDCOLOR                         0x4B
#define D3DRS_SWATHWIDTH                         0x4C
#define D3DRS_POLYGONOFFSETZSLOPESCALE           0x4D
#define D3DRS_POLYGONOFFSETZOFFSET               0x4E
#define D3DRS_POINTOFFSETENABLE                  0x4F
#define D3DRS_WIREFRAMEOFFSETENABLE              0x50
#define D3DRS_SOLIDOFFSETENABLE                  0x51
#define D3DRS_FOGENABLE                          0x5C
#define D3DRS_FOGTABLEMODE                       0x5D
#define D3DRS_FOGSTART                           0x5E
#define D3DRS_FOGEND                             0x5F
#define D3DRS_FOGDENSITY                         0x60
#define D3DRS_RANGEFOGENABLE                     0x61
#define D3DRS_WRAP0                              0x62
#define D3DRS_WRAP1                              0x63
#define D3DRS_WRAP2                              0x64
#define D3DRS_WRAP3                              0x65
#define D3DRS_LIGHTING                           0x66
#define D3DRS_SPECULARENABLE                     0x67
#define D3DRS_LOCALVIEWER                        0x68
#define D3DRS_COLORVERTEX                        0x69
#define D3DRS_BACKSPECULARMATERIALSOURCE         0x6A
#define D3DRS_BACKDIFFUSEMATERIALSOURCE          0x6B
#define D3DRS_BACKAMBIENTMATERIALSOURCE          0x6C
#define D3DRS_BACKEMISSIVEMATERIALSOURCE         0x6D
#define D3DRS_SPECULARMATERIALSOURCE             0x6E
#define D3DRS_DIFFUSEMATERIALSOURCE              0x6F
#define D3DRS_AMBIENTMATERIALSOURCE              0x70
#define D3DRS_EMISSIVEMATERIALSOURCE             0x71
#define D3DRS_BACKAMBIENT                        0x72
#define D3DRS_AMBIENT                            0x73
#define D3DRS_POINTSIZE                          0x74
#define D3DRS_POINTSIZE_MIN                      0x75
#define D3DRS_POINTSPRITEENABLE                  0x76
#define D3DRS_POINTSCALEENABLE                   0x77
#define D3DRS_POINTSCALE_A                       0x78
#define D3DRS_POINTSCALE_B                       0x79
#define D3DRS_POINTSCALE_C                       0x7A
#define D3DRS_POINTSIZE_MAX                      0x7B
#define D3DRS_PATCHEDGESTYLE                     0x7C
#define D3DRS_PATCHSEGMENTS                      0x7D
#define D3DRS_SWAPFILTER                         0x7E
#define D3DRS_PRESENTATIONINTERVAL               0x7F
#define D3DRS_PSTEXTUREMODES                     0x88
#define D3DRS_VERTEXBLEND                        0x89
#define D3DRS_FOGCOLOR                           0x8A
#define D3DRS_FILLMODE                           0x8B
#define D3DRS_BACKFILLMODE                       0x8C
#define D3DRS_TWOSIDEDLIGHTING                   0x8D
#define D3DRS_NORMALIZENORMALS                   0x8E
#define D3DRS_ZENABLE                            0x8F
#define D3DRS_STENCILENABLE                      0x90
#define D3DRS_STENCILFAIL                        0x91
#define D3DRS_FRONTFACE                          0x92
#define D3DRS_CULLMODE                           0x93
#define D3DRS_TEXTUREFACTOR                      0x94
#define D3DRS_ZBIAS                              0x95
#define D3DRS_LOGICOP                            0x96
#define D3DRS_EDGEANTIALIAS                      0x97
#define D3DRS_MULTISAMPLEANTIALIAS               0x98
#define D3DRS_MULTISAMPLEMASK                    0x99
#define D3DRS_MULTISAMPLEMODE                    0x9A
#define D3DRS_MULTISAMPLERENDERTARGETMODE        0x9B
#define D3DRS_SHADOWFUNC                         0x9C
#define D3DRS_LINEWIDTH                          0x9D
#define D3DRS_DXT1NOISEENABLE                    0x9F
#define D3DRS_YUVENABLE                          0xA0
#define D3DRS_OCCLUSIONCULLENABLE                0xA1
#define D3DRS_STENCILCULLENABLE                  0xA2
#define D3DRS_ROPZCMPALWAYSREAD                  0xA3
#define D3DRS_ROPZREAD                           0xA4
#define D3DRS_DONOTCULLUNCOMPRESSED              0xA5
#define D3DRS_MAX                                0xA6

/* D3DTSS_* */
#define D3DTSS_ADDRESSU                          0
#define D3DTSS_ADDRESSV                          1
#define D3DTSS_ADDRESSW                          2
#define D3DTSS_MAGFILTER                         3
#define D3DTSS_MINFILTER                         4
#define D3DTSS_MIPFILTER                         5
#define D3DTSS_MIPMAPLODBIAS                     6
#define D3DTSS_MAXMIPLEVEL                       7
#define D3DTSS_MAXANISOTROPY                     8
#define D3DTSS_COLORKEYOP                        9
#define D3DTSS_COLORSIGN                         0xA
#define D3DTSS_ALPHAKILL                         0xB
#define D3DTSS_COLOROP                           0xC
#define D3DTSS_COLORARG0                         0xD
#define D3DTSS_COLORARG1                         0xE
#define D3DTSS_COLORARG2                         0xF
#define D3DTSS_ALPHAOP                           0x10
#define D3DTSS_ALPHAARG0                         0x11
#define D3DTSS_ALPHAARG1                         0x12
#define D3DTSS_ALPHAARG2                         0x13
#define D3DTSS_RESULTARG                         0x14
#define D3DTSS_TEXTURETRANSFORMFLAGS             0x15
#define D3DTSS_BUMPENVMAT00                      0x16
#define D3DTSS_BUMPENVMAT01                      0x17
#define D3DTSS_BUMPENVMAT11                      0x18
#define D3DTSS_BUMPENVMAT10                      0x19
#define D3DTSS_BUMPENVLSCALE                     0x1A
#define D3DTSS_BUMPENVLOFFSET                    0x1B
#define D3DTSS_TEXCOORDINDEX                     0x1C
#define D3DTSS_BORDERCOLOR                       0x1D
#define D3DTSS_COLORKEYCOLOR                     0x1E
#define D3DTSS_MAX                               0x20
#define D3DTSS_TCI_CAMERASPACENORMAL             0x10000
#define D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR   0x30000

/* D3DTS_* */
#define D3DTS_VIEW                               0
#define D3DTS_PROJECTION                         1
#define D3DTS_TEXTURE0                           2
#define D3DTS_TEXTURE1                           3
#define D3DTS_TEXTURE2                           4
#define D3DTS_TEXTURE3                           5
#define D3DTS_WORLD                              6

/* D3DTA_* */
#define D3DTA_DIFFUSE                            0
#define D3DTA_CURRENT                            1
#define D3DTA_TEXTURE                            2
#define D3DTA_TFACTOR                            3
#define D3DTA_ALPHAREPLICATE                     0x20

/* D3DTOP_* */
#define D3DTOP_DISABLE                           1
#define D3DTOP_SELECTARG1                        2
#define D3DTOP_SELECTARG2                        3
#define D3DTOP_MODULATE                          4
#define D3DTOP_MODULATE2X                        5
#define D3DTOP_BLENDTEXTUREALPHA                 0xE
#define D3DTOP_MULTIPLYADD                       0x17

/* D3DTTFF_* */
#define D3DTTFF_DISABLE                          0
#define D3DTTFF_COUNT2                           2
#define D3DTTFF_COUNT3                           3

/* D3DTALPHAKILL_* */
#define D3DTALPHAKILL_DISABLE                    0

/* D3DTEXF_* */
#define D3DTEXF_NONE                             0
#define D3DTEXF_POINT                            1
#define D3DTEXF_LINEAR                           2
#define D3DTEXF_ANISOTROPIC                      3
#define D3DTEXF_QUINCUNX                         4
#define D3DTEXF_GAUSSIANCUBIC                    5

/* D3DTADDRESS_* */
#define D3DTADDRESS_WRAP                         1
#define D3DTADDRESS_MIRROR                       2
#define D3DTADDRESS_CLAMP                        3
#define D3DTADDRESS_BORDER                       4

/* D3DBLEND_* */
#define D3DBLEND_ZERO                            0
#define D3DBLEND_ONE                             1
#define D3DBLEND_SRCCOLOR                        0x300
#define D3DBLEND_INVSRCCOLOR                     0x301
#define D3DBLEND_SRCALPHA                        0x302
#define D3DBLEND_INVSRCALPHA                     0x303
#define D3DBLEND_DESTALPHA                       0x304
#define D3DBLEND_INVDESTALPHA                    0x305
#define D3DBLEND_DESTCOLOR                       0x306
#define D3DBLEND_INVDESTCOLOR                    0x307
#define D3DBLEND_SRCALPHASAT                     0x308

/* D3DCMP_* */
#define D3DCMP_NEVER                             0x200
#define D3DCMP_LESS                              0x201
#define D3DCMP_EQUAL                             0x202
#define D3DCMP_LESSEQUAL                         0x203
#define D3DCMP_GREATER                           0x204
#define D3DCMP_NOTEQUAL                          0x205
#define D3DCMP_GREATEREQUAL                      0x206
#define D3DCMP_ALWAYS                            0x207

/* D3DSTENCILOP_* */
#define D3DSTENCILOP_ZERO                        0
#define D3DSTENCILOP_INVERT                      0x150A
#define D3DSTENCILOP_KEEP                        0x1E00
#define D3DSTENCILOP_REPLACE                     0x1E01
#define D3DSTENCILOP_INCRSAT                     0x1E02
#define D3DSTENCILOP_DECRSAT                     0x1E03
#define D3DSTENCILOP_INCR                        0x8507
#define D3DSTENCILOP_DECR                        0x8508

/* D3DCULL_* */
#define D3DCULL_NONE                             0
#define D3DCULL_CW                               0x900
#define D3DCULL_CCW                              0x901

/* D3DSHADE_* */
#define D3DSHADE_FLAT                            0x1D00
#define D3DSHADE_GOURAUD                         0x1D01

/* D3DFOG_* */
#define D3DFOG_EXP                               1
#define D3DFOG_EXP2                              2
#define D3DFOG_LINEAR                            3

/* D3DMCS_* */
#define D3DMCS_MATERIAL                          0
#define D3DMCS_COLOR1                            1

/* D3DCOLORWRITEENABLE_* */
#define D3DCOLORWRITEENABLE_ALL                  0x1010101

/* D3DLIGHT_* */
#define D3DLIGHT_POINT                           1
#define D3DLIGHT_SPOT                            2
#define D3DLIGHT_DIRECTIONAL                     3

/* D3DPT_* */
#define D3DPT_POINTLIST                          1
#define D3DPT_LINELIST                           2
#define D3DPT_LINESTRIP                          4
#define D3DPT_TRIANGLELIST                       5
#define D3DPT_TRIANGLESTRIP                      6
#define D3DPT_TRIANGLEFAN                        7
#define D3DPT_QUADLIST                           8

/* D3DFVF_* */
#define D3DFVF_XYZ                               2
#define D3DFVF_XYZRHW                            4
#define D3DFVF_DIFFUSE                           0x40
#define D3DFVF_TEX1                              0x100

/* D3DVSDT_* */
#define D3DVSDT_PBYTE1                           0x14
#define D3DVSDT_SHORT1                           0x15
#define D3DVSDT_NORMPACKED3                      0x16
#define D3DVSDT_NORMSHORT2                       0x21
#define D3DVSDT_FLOAT2                           0x22
#define D3DVSDT_PBYTE2                           0x24
#define D3DVSDT_SHORT2                           0x25
#define D3DVSDT_NORMSHORT3                       0x31
#define D3DVSDT_FLOAT3                           0x32
#define D3DVSDT_PBYTE3                           0x34
#define D3DVSDT_SHORT3                           0x35
#define D3DVSDT_D3DCOLOR                         0x40
#define D3DVSDT_FLOAT4                           0x42
#define D3DVSDT_PBYTE4                           0x44
#define D3DVSDT_SHORT4                           0x45

/* D3DVSDE_* */
#define D3DVSDE_POSITION                         0
#define D3DVSDE_BLENDWEIGHT                      1
#define D3DVSDE_NORMAL                           2
#define D3DVSDE_DIFFUSE                          3
#define D3DVSDE_TEXCOORD0                        9
#define D3DVSDE_TEXCOORD1                        0xA
#define D3DVSDE_TEXCOORD2                        0xB
#define D3DVSDE_TEXCOORD3                        0xC

/* D3DFMT_* */
#define D3DFMT_L8                                0
#define D3DFMT_A1R5G5B5                          2
#define D3DFMT_X1R5G5B5                          3
#define D3DFMT_A4R4G4B4                          4
#define D3DFMT_R5G6B5                            5
#define D3DFMT_A8R8G8B8                          6
#define D3DFMT_X8R8G8B8                          7
#define D3DFMT_P8                                0xB
#define D3DFMT_DXT1                              0xC
#define D3DFMT_DXT2                              0xE
#define D3DFMT_DXT4                              0xF
#define D3DFMT_LIN_A1R5G5B5                      0x10
#define D3DFMT_LIN_R5G6B5                        0x11
#define D3DFMT_LIN_A8R8G8B8                      0x12
#define D3DFMT_LIN_L8                            0x13
#define D3DFMT_LIN_X1R5G5B5                      0x1C
#define D3DFMT_LIN_A4R4G4B4                      0x1D
#define D3DFMT_LIN_X8R8G8B8                      0x1E
#define D3DFMT_D24S8                             0x2A
#define D3DFMT_F24S8                             0x2B
#define D3DFMT_LIN_D24S8                         0x2E
#define D3DFMT_LIN_F24S8                         0x2F
#define D3DFMT_LIN_D16                           0x30

/* D3DMULTISAMPLE_* */
#define D3DMULTISAMPLE_NONE                      0x11
#define D3DMULTISAMPLE_2_SAMPLES_MULTISAMPLE_LINEAR 0x1021
#define D3DMULTISAMPLE_4_SAMPLES_MULTISAMPLE_LINEAR 0x1022
#define D3DMULTISAMPLE_2_SAMPLES_MULTISAMPLE_QUINCUNX 0x1121
#define D3DMULTISAMPLE_4_SAMPLES_MULTISAMPLE_GAUSSIAN 0x1222
#define D3DMULTISAMPLE_9_SAMPLES_MULTISAMPLE_GAUSSIAN 0x1233
#define D3DMULTISAMPLE_2_SAMPLES_SUPERSAMPLE_VERTICAL_LINEAR 0x2012
#define D3DMULTISAMPLE_2_SAMPLES_SUPERSAMPLE_HORIZONTAL_LINEAR 0x2021
#define D3DMULTISAMPLE_4_SAMPLES_SUPERSAMPLE_LINEAR 0x2022
#define D3DMULTISAMPLE_4_SAMPLES_SUPERSAMPLE_GAUSSIAN 0x2222
#define D3DMULTISAMPLE_9_SAMPLES_SUPERSAMPLE_GAUSSIAN 0x2233

/* D3DMULTISAMPLEMODE_* */
#define D3DMULTISAMPLEMODE_1X                    0
#define D3DMULTISAMPLEMODE_2X                    1
#define D3DMULTISAMPLEMODE_4X                    2

/* D3DPRESENTFLAG_* */
#define D3DPRESENTFLAG_WIDESCREEN                0x10
#define D3DPRESENTFLAG_INTERLACED                0x20
#define D3DPRESENTFLAG_PROGRESSIVE               0x40
#define D3DPRESENTFLAG_FIELD                     0x80
#define D3DPRESENTFLAG_10X11PIXELASPECTRATIO     0x100

/* D3DPRESENT_* */
#define D3DPRESENT_INTERVAL_ONE                  1
#define D3DPRESENT_INTERVAL_IMMEDIATE            0x80000000

/* D3DSWAPEFFECT_* */
#define D3DSWAPEFFECT_DISCARD                    1

/* D3DDEVTYPE_* */
#define D3DDEVTYPE_HAL                           1

/* D3DCREATE_* */
#define D3DCREATE_HARDWARE_VERTEXPROCESSING      0x40

/* D3DBACKBUFFER_* */
#define D3DBACKBUFFER_TYPE_MONO                  0

/* D3DCLEAR_* */
#define D3DCLEAR_ZBUFFER                         1
#define D3DCLEAR_STENCIL                         2
#define D3DCLEAR_TARGET                          0xF0

/* D3DLOCK_* */
#define D3DLOCK_NOOVERWRITE                      0x20
#define D3DLOCK_TILED                            0x40
#define D3DLOCK_READONLY                         0x80

/* D3DPOOL_* */
#define D3DPOOL_DEFAULT                          0

/* D3DCUBEMAP_* */
#define D3DCUBEMAP_FACE_POSITIVE_X               0
#define D3DCUBEMAP_FACE_NEGATIVE_X               1
#define D3DCUBEMAP_FACE_POSITIVE_Y               2
#define D3DCUBEMAP_FACE_NEGATIVE_Y               3
#define D3DCUBEMAP_FACE_POSITIVE_Z               4
#define D3DCUBEMAP_FACE_NEGATIVE_Z               5

/* D3DPALETTE_* */
#define D3DPALETTE_256                           0
#define D3DPALETTE_32                            3
#define D3DPALETTE_ALIGNMENT                     0x40

/* D3DTEXTURE_* */
#define D3DTEXTURE_ALIGNMENT                     0x80

/* D3DCOMMON_* */
#define D3DCOMMON_TYPE_VERTEXBUFFER              0
#define D3DCOMMON_INTREFCOUNT_MASK               0x780000
#define D3DCOMMON_D3DCREATED                     0x1000000

/* D3DSCM_* */
#define D3DSCM_96CONSTANTS                       0
#define D3DSCM_192CONSTANTS                      1
#define D3DSCM_NORESERVEDCONSTANTS               0x10

/* D3DPUSH_* */
#define D3DPUSH_SET_TRANSFORM_CONSTANT           0xB80
#define D3DPUSH_SET_BEGIN_END                    0x17FC
#define D3DPUSH_INLINE_ARRAY                     0x1818
#define D3DPUSH_SET_TRANSFORM_CONSTANT_LOAD      0x1EA4
#define D3DPUSH_NOINCREMENT_FLAG                 0x40000000

#define D3DTSS_MAXSTAGES 4

#endif
