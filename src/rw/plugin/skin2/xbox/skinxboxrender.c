/*
 * codfh-match: RenderWare 3.6's Xbox skin rendering, rebuilt from the
 * image; the file name is the image's RCS id string's, names and shapes the
 * Godfather PDB's copy. The generated vertex shaders are cached by key,
 * the least recently used one replaced when the cache is full.
 */

#include <xtl.h>
#include <xgraphics.h>
#include <string.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"

#include "skinxbox.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00509BE0
RwChar TextArray[2048];
// 0x0050B000
D3DMATRIX _rpSkinXboxCachedWorldMatrix;
// 0x0050B040
D3DMATRIX _rpSkinXboxCachedViewMatrix;
// 0x0050B080
SkinGlobals _rpSkinGlobals;
// End of its data definitions.


/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/skin2/xbox/skinxboxrender.c#3 $";

/* The precompiled vertex shader fragments the generator splices around its code (.data;
 * each a header word, 0x2078 | count << 16, and count instructions; named by address). */
static DWORD dword_436748[13] =
{
    0x00032078, 0x00000000, 0x00A0001B, 0x5436A86C,
    0x21500FF8, 0x00000000, 0x0800001B, 0x083613FD,
    0x50510FF8, 0x00000000, 0x0040001A, 0x55FEA86C,
    0x2E500FF9,
};

static DWORD dword_43677C[5] =
{
    0x00012078, 0x00000000, 0x0020A01B, 0x0C36106C,
    0x2FB00FF9,
};

static DWORD dword_436790[5] =
{
    0x00012078, 0x00000000, 0x0060A81B, 0x0836106C,
    0x3FB00FF9,
};

static DWORD dword_4367A4[5] =
{
    0x00012078, 0x00000000, 0x00200A1B, 0x0836106C,
    0x2070F849,
};

static DWORD dword_4367B8[41] =
{
    0x000A2078, 0x00000000, 0x00200A1B, 0x0836106C,
    0x2070F848, 0x00000000, 0x00B7401B, 0x5436186C,
    0x28100FF8, 0x00000000, 0x00B7601B, 0x5436186C,
    0x24100FF8, 0x00000000, 0x00B7801B, 0x5436186C,
    0x22100FF8, 0x00000000, 0x00A0001B, 0x1436286C,
    0x21100FF8, 0x00000000, 0x0800001B, 0x083613FC,
    0x50110FF8, 0x00000000, 0x0040001A, 0x15FE286C,
    0x2E100FF8, 0x00000000, 0x00B7201B, 0x0C36286C,
    0x28900FF8, 0x00000000, 0x00B7001B, 0x0C36286C,
    0x24900FF8, 0x00000000, 0x00600A15, 0x94361054,
    0x2070C851,
};

static DWORD dword_43685C[13] =
{
    0x00032078, 0x00000000, 0x00D7A01B, 0x5436186C,
    0x20708850, 0x00000000, 0x00D7C01B, 0x5436186C,
    0x20704850, 0x00000000, 0x00200A1B, 0x0836106C,
    0x2070F849,
};

static DWORD dword_436890[49] =
{
    0x000C2078, 0x00000000, 0x00D7A01B, 0x5436186C,
    0x20708858, 0x00000000, 0x00D7C01B, 0x5436186C,
    0x20704858, 0x00000000, 0x00200A1B, 0x0836106C,
    0x2070F848, 0x00000000, 0x00B7401B, 0x5436186C,
    0x28100FF8, 0x00000000, 0x00B7601B, 0x5436186C,
    0x24100FF8, 0x00000000, 0x00B7801B, 0x5436186C,
    0x22100FF8, 0x00000000, 0x00A0001B, 0x1436286C,
    0x21100FF8, 0x00000000, 0x0800001B, 0x083613FC,
    0x50110FF8, 0x00000000, 0x0040001A, 0x15FE286C,
    0x2E100FF8, 0x00000000, 0x00B7201B, 0x0C36286C,
    0x28900FF8, 0x00000000, 0x00B7001B, 0x0C36286C,
    0x24900FF8, 0x00000000, 0x00600A15, 0x94361054,
    0x2070C851,
};

static DWORD dword_436954[5] =
{
    0x00012078, 0x00000000, 0x00200C1B, 0x0836106C,
    0x2070F849,
};

static DWORD dword_436968[9] =
{
    0x00022078, 0x00000000, 0x00D7AA1B, 0x0836186C,
    0x20708848, 0x00000000, 0x00D7CA1B, 0x0836186C,
    0x20704849,
};

static DWORD dword_43698C[9] =
{
    0x00022078, 0x00000000, 0x00D7AC1B, 0x0836186C,
    0x20708848, 0x00000000, 0x00D7CC1B, 0x0836186C,
    0x20704849,
};

static DWORD dword_4369B0[29] =
{
    0x00072078, 0x00000000, 0x00C0201B, 0x3436186C,
    0x20708800, 0x00000000, 0x00C0801B, 0x3436186C,
    0x20701800, 0x00000000, 0x00C0401B, 0x3436186C,
    0x20704800, 0x00000000, 0x00C0601B, 0x3436186C,
    0x20702800, 0x00000000, 0x062000FF, 0xC43613FF,
    0x10188828, 0x00000000, 0x0057E01B, 0x0C37686C,
    0x2070F818, 0x00000000, 0x0080001B, 0xC400286C,
    0x3070E801,
};

static DWORD dword_436A28[25] =
{
    0x00062078, 0x00000000, 0x00C0201B, 0x3436186C,
    0x20708800, 0x00000000, 0x00C0801B, 0x3436186C,
    0x20701800, 0x00000000, 0x00C0401B, 0x3436186C,
    0x20704800, 0x00000000, 0x00C0601B, 0x3436186C,
    0x20702800, 0x00000000, 0x062000FF, 0xC43613FF,
    0x10188828, 0x00000000, 0x0080001B, 0xC400286C,
    0x3070E801,
};

/* A cached skin vertex shader. */
typedef struct _rpSkinXboxShaderItemDesc _rpSkinXboxShaderItemDesc;
struct _rpSkinXboxShaderItemDesc
{
    _rpSkinXboxShaderDesc   desc;
    RwUInt32                renderFrame;
    const DWORD            *byteCode;
};

#define rpSKINXBOXSHADERCACHESIZE 256

static RwInt32 lastFormatIndex;
static const DWORD *lastShader;
static _rpSkinXboxShaderItemDesc VertexShaderCache[rpSKINXBOXSHADERCACHESIZE];

static _rpSkinXboxShaderItemDesc *LastVertexShaderDesc = VertexShaderCache;

static RwBool shadersInited;

static RwV4d _rpSkinXboxAmbientLight;
static RwInt32 NumShadersInCache;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00418568
// match: _elements @ 0x004185BC
// match: _dword_436748 @ 0x00436748
// match: _dword_43677C @ 0x0043677C
// match: _dword_436790 @ 0x00436790
// match: _dword_4367A4 @ 0x004367A4
// match: _dword_4367B8 @ 0x004367B8
// match: _dword_43685C @ 0x0043685C
// match: _dword_436890 @ 0x00436890
// match: _dword_436954 @ 0x00436954
// match: _dword_436968 @ 0x00436968
// match: _dword_43698C @ 0x0043698C
// match: _dword_4369B0 @ 0x004369B0
// match: _dword_436A28 @ 0x00436A28
// match: _off_4185C0 @ 0x004185C0
// match: _off_4185D0 @ 0x004185D0
// match: _off_4185D8 @ 0x004185D8
// match: ??_C@_04NPFAEOEN@xyzw?$AA@ @ 0x004185F4
// match: ??_C@_03POMAGKDD@xyz?$AA@ @ 0x004185FC
// match: ??_C@_02KEKBNNLK@xy?$AA@ @ 0x00418600
// match: ??_C@_01FJMABOPO@x?$AA@ @ 0x00418604
// match: __real@3f13cd3a @ 0x00418608
// match: ??_C@_0BA@OKHIGGMB@mov?5oT1?4xy?0?5v5?6?$AA@ @ 0x0041860C
// match: ??_C@_0BB@MFLIAMLP@mov?5oT0?4xy?0?5v?$CFd?6?$AA@ @ 0x0041861C
// match: ??_C@_0BK@GKCEFOJM@dp3?5oT3?4z?0?5c?$FL1?5?$CL?593?$FN?0?5r5?6?$AA@ @ 0x00418630
// match: ??_C@_0BK@IFONJFHL@dp3?5oT3?4y?0?5c?$FL1?5?$CL?593?$FN?0?5r2?6?$AA@ @ 0x0041864C
// match: ??_C@_0BK@GODCFPCI@dp3?5oT3?4x?0?5c?$FL1?5?$CL?593?$FN?0?5r4?6?$AA@ @ 0x00418668
// match: ??_C@_0BK@NCNFLMFP@dp3?5oT2?4z?0?5c?$FL0?5?$CL?593?$FN?0?5r5?6?$AA@ @ 0x00418684
// match: ??_C@_0BK@DNBMHHLI@dp3?5oT2?4y?0?5c?$FL0?5?$CL?593?$FN?0?5r2?6?$AA@ @ 0x004186A0
// match: ??_C@_0BK@NGMDLNOL@dp3?5oT2?4x?0?5c?$FL0?5?$CL?593?$FN?0?5r4?6?$AA@ @ 0x004186BC
// match: ??_C@_0CN@MMGEGAHI@mad?5oD0?4xyz?0?5r1?0?5c?$FL0?5?$CL?5?990?$FN?4z?0?5c@ @ 0x004186D8
// match: ??_C@_0CN@ICONGLNB@mad?5oD1?4xyz?0?5r1?0?5c?$FL0?5?$CL?5?990?$FN?4z?0?5c@ @ 0x00418708
// match: ??_C@_0CN@KFJBHENE@mad?5oT2?4xyz?0?5r1?0?5c?$FL0?5?$CL?5?990?$FN?4z?0?5c@ @ 0x00418738
// match: ??_C@_0BG@FPOFGKJN@mul?5r1?4xyz?0?5r1?0?5r7?4w?6?$AA@ @ 0x00418768
// match: ??_C@_0BC@IALCEOKI@dp3?5r1?4z?0?5r7?0?5r5?6?$AA@ @ 0x00418780
// match: ??_C@_0BC@BMBPDOCM@dp3?5r1?4y?0?5r7?0?5r2?6?$AA@ @ 0x00418794
// match: ??_C@_0BC@NJBMJNFO@dp3?5r1?4x?0?5r7?0?5r4?6?$AA@ @ 0x004187A8
// match: ??_C@_0BO@IOJLNEAB@max?5r7?4w?0?5r7?4w?0?5c?$FL0?5?$CL?5?990?$FN?4w?6?$AA@ @ 0x004187BC
// match: ??_C@_0CM@PGOIODID@mad?5r7?4w?0?5r7?4w?0?5c?$FL0?5?$CL?5?990?$FN?4x?0?5c?$FL@ @ 0x004187DC
// match: ??_C@_0BA@JCJFOBPK@rcp?5r7?4w?0?5r7?4w?6?$AA@ @ 0x00418808
// match: ??_C@_0BG@ILMLKEBP@mul?5r7?4xyz?0?5r7?0?5r7?4w?6?$AA@ @ 0x00418818
// match: ??_C@_0BA@ELPIJPMD@rsq?5r7?4w?0?5r7?4w?6?$AA@ @ 0x00418830
// match: ??_C@_0BC@OIEHAIBM@dp3?5r7?4w?0?5r7?0?5r7?6?$AA@ @ 0x00418840
// match: ??_C@_0CG@HLCIJJMF@add?5r7?4xyz?0?5?9?5c?$FL1?5?$CL?5?990?$FN?4xyz?0?5r3@ @ 0x00418854
// match: ??_C@_0CN@NGACFADJ@mad?5oD0?4xyz?0?5r1?0?5c?$FL0?5?$CL?5?990?$FN?4w?0?5c@ @ 0x0041887C
// match: ??_C@_0CN@JIILFLJA@mad?5oD1?4xyz?0?5r1?0?5c?$FL0?5?$CL?5?990?$FN?4w?0?5c@ @ 0x004188AC
// match: ??_C@_0CN@LPPHEEJF@mad?5oT2?4xyz?0?5r1?0?5c?$FL0?5?$CL?5?990?$FN?4w?0?5c@ @ 0x004188DC
// match: ??_C@_0BG@NAKFJPDN@mul?5r1?4xyz?0?5r1?0?5r1?4w?6?$AA@ @ 0x0041890C
// match: ??_C@_0BA@CMANKACA@rsq?5r1?4w?0?5r1?4w?6?$AA@ @ 0x00418924
// match: ??_C@_0BC@CPPPJOEJ@dp3?5r1?4w?0?5r1?0?5r1?6?$AA@ @ 0x00418934
// match: ??_C@_0BK@LGMCOOCJ@dp3?5r1?4z?0?5c?$FL0?5?$CL?5?990?$FN?0?5r5?6?$AA@ @ 0x00418948
// match: ??_C@_0BK@BANLHOAF@dp3?5r1?4y?0?5c?$FL0?5?$CL?5?990?$FN?0?5r2?6?$AA@ @ 0x00418964
// match: ??_C@_0BK@MDLEICOP@dp3?5r1?4x?0?5c?$FL0?5?$CL?5?990?$FN?0?5r4?6?$AA@ @ 0x00418980
// match: ??_C@_0BP@GHBJGCGF@mad?5r2?0?5r4?4yzxw?0?5r5?4zxyw?0?5?9r2?6?$AA@ @ 0x0041899C
// match: ??_C@_0BK@EMDDKMFB@mul?5r2?0?5r4?4zxyw?0?5r5?4yzxw?6?$AA@ @ 0x004189BC
// match: ??_C@_0N@BKEAPMLL@mov?5oD0?0?5v4?6?$AA@ @ 0x004189D8
// match: ??_C@_0BD@EIDJKLFM@dp3?5r4?4z?0?5v9?0?5r10?6?$AA@ @ 0x004189E8
// match: ??_C@_0BC@NJBABHHJ@dp3?5r4?4y?0?5v9?0?5r9?6?$AA@ @ 0x004189FC
// match: ??_C@_0BC@BJFMKCIO@dp3?5r4?4x?0?5v9?0?5r8?6?$AA@ @ 0x00418A10
// match: ??_C@_0BM@BFNKIIEA@dp3?5r4?4z?0?5v9?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418A24
// match: ??_C@_0BM@GOMEAKKD@dp3?5r4?4y?0?5v9?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418A40
// match: ??_C@_0BM@PBBOIJDN@dp3?5r4?4x?0?5v9?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418A5C
// match: ??_C@_0BJ@OFLKNILC@mul?5r6?4?$CFs?0?5r6?4?$CFs?0?5r8?4?$CFs?6?$AA@ @ 0x00418A78
// match: ??_C@_0CD@PIFLPMPH@add?5r8?4?$CFs?0?5?9c?$FL?$CFd?5?$CL?5?990?$FN?4?$CFs?0?5r8?4?$CF@ @ 0x00418A94
// match: ??_C@_0CJ@OAGHDFMH@max?5r6?4?$CFs?0?5c?$FL?$CFd?5?$CL?51?5?$CL?5?990?$FN?4wwww?0@ @ 0x00418AB8
// match: ??_C@_0CC@GMKNCDEH@max?5r8?4?$CFs?0?5c?$FL?$CFd?5?$CL?5?990?$FN?4?$CFs?0?5r1?4?$CFs@ @ 0x00418AE4
// match: ??_C@_0BD@IGDCCFPH@dp3?5r6?4?$CFc?0?5r5?0?5r7?6?$AA@ @ 0x00418B08
// match: ??_C@_0BC@HEJMEKL@rsq?5r1?4?$CFc?0?5r1?4?$CFc?6?$AA@ @ 0x00418B1C
// match: ??_C@_0BD@HEGAJOBO@dp3?5r1?4?$CFc?0?5r7?0?5r7?6?$AA@ @ 0x00418B30
// match: ??_C@_0CH@FPOGLOPA@add?5r7?4xyz?0?5?9?5c?$FL?$CFd?5?$CL?5?990?$FN?4xyz?0?5r@ @ 0x00418B44
// match: ??_C@_0DG@MJHAHFIF@mad?5r11?4xyz?0?5c?$FL?$CFd?5?$CL?51?5?$CL?5?990?$FN?4xyz@ @ 0x00418B6C
// match: ??_C@_0BN@DHNHBOBO@max?5r6?4?$CFs?0?5c?$FL?990?$FN?4w?0?5?9r6?4?$CFs?6?$AA@ @ 0x00418BA4
// match: ??_C@_0BM@EAJIFKBA@dp3?5r6?4?$CFc?0?5c?$FL?$CFd?5?$CL?5?990?$FN?0?5r5?6?$AA@ @ 0x00418BC4
// match: ??_C@_0CD@GOOFFNGF@mad?5r3?4xyz?0?5v1?4?$CFc?0?5r2?4xyz?0?5r3?4xy@ @ 0x00418BE0
// match: ??_C@_0BL@FJPGLDCL@mul?5r3?4xyz?0?5v1?4?$CFc?0?5r2?4xyz?6?$AA@ @ 0x00418C04
// match: ??_C@_0BM@EBGFAFMB@dp4?5r2?4z?0?5v0?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418C20
// match: ??_C@_0BM@DKHLIHCC@dp4?5r2?4y?0?5v0?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418C3C
// match: ??_C@_0BM@KFKBAELM@dp4?5r2?4x?0?5v0?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418C58
// match: ??_C@_0BD@EEPGFGOC@dp3?5r5?4z?0?5v3?0?5r10?6?$AA@ @ 0x00418C74
// match: ??_C@_0BC@KAPGJBLC@dp3?5r5?4y?0?5v3?0?5r9?6?$AA@ @ 0x00418C88
// match: ??_C@_0BC@GALKCEEF@dp3?5r5?4x?0?5v3?0?5r8?6?$AA@ @ 0x00418C9C
// match: ??_C@_0BD@BCCJGGPM@dp4?5r3?4z?0?5v0?0?5r10?6?$AA@ @ 0x00418CB0
// match: ??_C@_0BC@MMACKMIH@dp4?5r3?4y?0?5v0?0?5r9?6?$AA@ @ 0x00418CC4
// match: ??_C@_0BC@MEOBJHA@dp4?5r3?4x?0?5v0?0?5r8?6?$AA@ @ 0x00418CD8
// match: ??_C@_0BO@GCBNFPCB@mul?5r10?0?5v1?4?$CFc?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418CEC
// match: ??_C@_0BN@PNNKMCIJ@mul?5r9?0?5v1?4?$CFc?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418D0C
// match: ??_C@_0BN@HMPPKHKO@mul?5r8?0?5v1?4?$CFc?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418D2C
// match: ??_C@_0CD@EJGANEAF@mad?5r10?0?5v1?4?$CFc?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?0?5r1@ @ 0x00418D4C
// match: ??_C@_0CB@KBBKLNEN@mad?5r9?0?5v1?4?$CFc?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?0?5r9?6@ @ 0x00418D70
// match: ??_C@_0CB@KBGNCKGH@mad?5r8?0?5v1?4?$CFc?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?0?5r8?6@ @ 0x00418D94
// match: ??_C@_0BB@PNMADBML@mov?5a0?4x?0?5v2?4?$CFc?6?$AA@ @ 0x00418DB8
// match: ??_C@_0BM@LMIFLNMN@dp3?5r5?4z?0?5v3?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418DCC
// match: ??_C@_0BM@MHJLDPCO@dp3?5r5?4y?0?5v3?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418DE8
// match: ??_C@_0BM@FIEBLMLA@dp3?5r5?4x?0?5v3?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418E04
// match: ??_C@_0BM@NKBGOPBF@dp4?5r3?4z?0?5v0?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418E20
// match: ??_C@_0BM@KBAIGNPG@dp4?5r3?4y?0?5v0?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418E3C
// match: ??_C@_0BM@DONCOOGI@dp4?5r3?4x?0?5v0?0?5c?$FLa0?4x?5?$CL?5?$CFd?$FN?6?$AA@ @ 0x00418E58
// match: ??_C@_0BA@JCEGDFAJ@mov?5a0?4x?0?5v2?4x?6?$AA@ @ 0x00418E74
// match: ??_C@_08NLHOJCGN@xvs?41?41?6?$AA@ @ 0x00418E84
// match: _LastVertexShaderDesc @ 0x00436A8C

// match: __rpSkinXboxPurgeShaderCache @ 0x002D1840
// sp-match: __rpSkinXboxPurgeShaderCache @ 0x001EC190

void
_rpSkinXboxPurgeShaderCache(void)
{
    lastShader = (const DWORD *)-1;
    lastFormatIndex = -1;
}

// match: __rpSkinXboxInitShaders @ 0x002D1850
// sp-match: __rpSkinXboxInitShaders @ 0x001EC1A0
RwBool
_rpSkinXboxInitShaders(void)
{
    if (!shadersInited)
    {
        shadersInited = TRUE;

        _rpSkinXboxVertexFormatCreate();

        _rpSkinXboxPurgeShaderCache();

        memset(VertexShaderCache, 0, sizeof(VertexShaderCache));
    }

    return TRUE;
}

// match: __rpSkinXboxSetShader @ 0x002D1890
// sp-match: __rpSkinXboxSetShader @ 0x001EC1E0
void
_rpSkinXboxSetShader(DWORD formatIndex, const DWORD *shader)
{
    if ((RwInt32)formatIndex != lastFormatIndex || shader != lastShader)
    {
        lastFormatIndex = formatIndex;
        lastShader = shader;

        D3DDevice_LoadVertexShaderProgram(shader, 12);
        D3DDevice_SelectVertexShader(formatIndex, 12);
    }
}

// match: __rpSkinXboxComputeProjViewWorld @ 0x002D18D0
// sp-match: __rpSkinXboxComputeProjViewWorld @ 0x001EC220
void
_rpSkinXboxComputeProjViewWorld(D3DMATRIX *worldMatrix, D3DMATRIX *viewMatrix,
                                D3DMATRIX *projViewWorldMatrix,
                                const RpAtomic *atomic,
                                const D3DVECTOR4 *viewportScale)
{
    const RwCamera  *camera;
    const RwMatrix  *ltm;
    D3DMATRIX       projMatrix;
    D3DMATRIX       worldMatrixTransposed;
    RwMatrix        invCameraMatrix;
    D3DMATRIX       viewWorldMatrix;
    RwReal          xScale;
    RwReal          yScale;

    camera = (const RwCamera *)RWSRCGLOBAL(curCamera);

    /* Projection matrix, scaled to the viewport */
    xScale = camera->recipViewWindow.x * viewportScale->x;
    yScale = camera->recipViewWindow.y * viewportScale->y;

    projMatrix.m[0][0] = xScale;
    projMatrix.m[0][1] = 0.0f;
    projMatrix.m[0][2] = camera->viewOffset.x * xScale;
    projMatrix.m[0][3] = -camera->viewOffset.x * xScale;

    projMatrix.m[1][0] = 0.0f;
    projMatrix.m[1][1] = yScale;
    projMatrix.m[1][2] = camera->viewOffset.y * yScale;
    projMatrix.m[1][3] = -camera->viewOffset.y * yScale;

    if (camera->projectionType == rwPARALLEL)
    {
        projMatrix.m[2][0] = 0.0f;
        projMatrix.m[2][1] = 0.0f;
        projMatrix.m[2][2] = viewportScale->z / (camera->farPlane - camera->nearPlane);
        projMatrix.m[2][3] = -camera->nearPlane * projMatrix.m[2][2];

        projMatrix.m[3][0] = 0.0f;
        projMatrix.m[3][1] = 0.0f;
        projMatrix.m[3][2] = 0.0f;
        projMatrix.m[3][3] = 1.0f;
    }
    else
    {
        projMatrix.m[2][0] = 0.0f;
        projMatrix.m[2][1] = 0.0f;
        projMatrix.m[2][2] = viewportScale->z * camera->farPlane /
                             (camera->farPlane - camera->nearPlane);
        projMatrix.m[2][3] = -camera->nearPlane * projMatrix.m[2][2];

        projMatrix.m[3][0] = 0.0f;
        projMatrix.m[3][1] = 0.0f;
        projMatrix.m[3][2] = 1.0f;
        projMatrix.m[3][3] = 0.0f;
    }

    /* View matrix (the camera matrix inverted, transposed) */
    RwMatrixInvert(&invCameraMatrix, RwFrameGetLTM(RwCameraGetFrame(camera)));

    viewMatrix->m[0][0] = -invCameraMatrix.right.x;
    viewMatrix->m[0][1] = -invCameraMatrix.up.x;
    viewMatrix->m[0][2] = -invCameraMatrix.at.x;
    viewMatrix->m[0][3] = -invCameraMatrix.pos.x;

    viewMatrix->m[1][0] = invCameraMatrix.right.y;
    viewMatrix->m[1][1] = invCameraMatrix.up.y;
    viewMatrix->m[1][2] = invCameraMatrix.at.y;
    viewMatrix->m[1][3] = invCameraMatrix.pos.y;

    viewMatrix->m[2][0] = invCameraMatrix.right.z;
    viewMatrix->m[2][1] = invCameraMatrix.up.z;
    viewMatrix->m[2][2] = invCameraMatrix.at.z;
    viewMatrix->m[2][3] = invCameraMatrix.pos.z;

    viewMatrix->m[3][0] = 0.0f;
    viewMatrix->m[3][1] = 0.0f;
    viewMatrix->m[3][2] = 0.0f;
    viewMatrix->m[3][3] = 1.0f;

    /* World matrix */
    ltm = RwFrameGetLTM(RpAtomicGetFrame(atomic));

    worldMatrixTransposed.m[0][0] = ltm->right.x;
    worldMatrixTransposed.m[0][1] = ltm->up.x;
    worldMatrixTransposed.m[0][2] = ltm->at.x;
    worldMatrixTransposed.m[0][3] = ltm->pos.x;

    worldMatrixTransposed.m[1][0] = ltm->right.y;
    worldMatrixTransposed.m[1][1] = ltm->up.y;
    worldMatrixTransposed.m[1][2] = ltm->at.y;
    worldMatrixTransposed.m[1][3] = ltm->pos.y;

    worldMatrixTransposed.m[2][0] = ltm->right.z;
    worldMatrixTransposed.m[2][1] = ltm->up.z;
    worldMatrixTransposed.m[2][2] = ltm->at.z;
    worldMatrixTransposed.m[2][3] = ltm->pos.z;

    worldMatrixTransposed.m[3][0] = 0.0f;
    worldMatrixTransposed.m[3][1] = 0.0f;
    worldMatrixTransposed.m[3][2] = 0.0f;
    worldMatrixTransposed.m[3][3] = 1.0f;

    if ((rwMatrixGetFlags(ltm) & rwMATRIXTYPEMASK) != rwMATRIXTYPEORTHONORMAL)
    {
        RwMatrix    orthoNormalMatrix;

        RwMatrixOrthoNormalize(&orthoNormalMatrix, ltm);

        worldMatrix->m[0][0] = orthoNormalMatrix.right.x;
        worldMatrix->m[0][1] = orthoNormalMatrix.up.x;
        worldMatrix->m[0][2] = orthoNormalMatrix.at.x;
        worldMatrix->m[0][3] = orthoNormalMatrix.pos.x;

        worldMatrix->m[1][0] = orthoNormalMatrix.right.y;
        worldMatrix->m[1][1] = orthoNormalMatrix.up.y;
        worldMatrix->m[1][2] = orthoNormalMatrix.at.y;
        worldMatrix->m[1][3] = orthoNormalMatrix.pos.y;

        worldMatrix->m[2][0] = orthoNormalMatrix.right.z;
        worldMatrix->m[2][1] = orthoNormalMatrix.up.z;
        worldMatrix->m[2][2] = orthoNormalMatrix.at.z;
        worldMatrix->m[2][3] = orthoNormalMatrix.pos.z;
    }
    else
    {
        worldMatrix->m[0][0] = ltm->right.x;
        worldMatrix->m[0][1] = ltm->up.x;
        worldMatrix->m[0][2] = ltm->at.x;
        worldMatrix->m[0][3] = ltm->pos.x;

        worldMatrix->m[1][0] = ltm->right.y;
        worldMatrix->m[1][1] = ltm->up.y;
        worldMatrix->m[1][2] = ltm->at.y;
        worldMatrix->m[1][3] = ltm->pos.y;

        worldMatrix->m[2][0] = ltm->right.z;
        worldMatrix->m[2][1] = ltm->up.z;
        worldMatrix->m[2][2] = ltm->at.z;
        worldMatrix->m[2][3] = ltm->pos.z;
    }

    worldMatrix->m[3][0] = 0.0f;
    worldMatrix->m[3][1] = 0.0f;
    worldMatrix->m[3][2] = 0.0f;
    worldMatrix->m[3][3] = 1.0f;

    D3DXMatrixMultiply(&viewWorldMatrix, viewMatrix, &worldMatrixTransposed);
    D3DXMatrixMultiply(projViewWorldMatrix, &projMatrix, &viewWorldMatrix);
}

// match: _FindLights @ 0x002D1D30
// sp-match: _FindLights @ 0x001EC680
static RwV4d *
FindLights(RwV4d *shaderConstantPtr,
           RwInt32 *dirLightCount,
           RwInt32 *pointLightCount,
           const RpAtomic *atomic)
{
    RwMatrix        inverseAtomicLTM;
    RwMatrix        nonscaledInverseAtomicLTM;
    RwBool          notOrthonormal;
    RwBool          orthoNormalized;
    RwInt32         numPointLights;
    RwReal          *radiusBlock;
    const RpWorld   *world;
    RwLLLink        *cur, *end;

    RwMatrixInvert(&inverseAtomicLTM, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

    notOrthonormal = (rwMatrixGetFlags(&inverseAtomicLTM) & rwMATRIXTYPEMASK) !=
                     rwMATRIXTYPEORTHONORMAL;
    orthoNormalized = FALSE;

    _rpSkinXboxAmbientLight.x = 0.0f;
    _rpSkinXboxAmbientLight.y = 0.0f;
    _rpSkinXboxAmbientLight.z = 0.0f;

    shaderConstantPtr++;

    world = (const RpWorld *)RWSRCGLOBAL(curWorld);

    cur = rwLinkListGetFirstLLLink(&world->directionalLightList);
    end = rwLinkListGetTerminator(&world->directionalLightList);
    if (cur != end)
    {
        do
        {
            RpLight *light = rwLLLinkGetData(cur, RpLight, inWorld);

            if (light && rwObjectTestFlags(light, rpLIGHTLIGHTATOMICS))
            {
                switch (RpLightGetType(light))
                {
                    case rpLIGHTDIRECTIONAL:
                    {
                        const RwV3d *at = RwMatrixGetAt(RwFrameGetLTM(RpLightGetFrame(light)));

                        if (notOrthonormal)
                        {
                            if (!orthoNormalized)
                            {
                                orthoNormalized = TRUE;
                                RwMatrixOrthoNormalize(&nonscaledInverseAtomicLTM,
                                                       &inverseAtomicLTM);
                            }

                            RwV3dTransformVector((RwV3d *)shaderConstantPtr, at,
                                                 &nonscaledInverseAtomicLTM);
                        }
                        else
                        {
                            RwV3dTransformVector((RwV3d *)shaderConstantPtr, at, &inverseAtomicLTM);
                        }

                        shaderConstantPtr->w = 0.0f;
                        shaderConstantPtr++;

                        shaderConstantPtr->x = light->color.red;
                        shaderConstantPtr->y = light->color.green;
                        shaderConstantPtr->z = light->color.blue;
                        shaderConstantPtr->w = 1.0f;
                        shaderConstantPtr++;

                        (*dirLightCount)++;

                        break;
                    }

                    case rpLIGHTAMBIENT:
                    {
                        _rpSkinXboxAmbientLight.x += light->color.red;
                        _rpSkinXboxAmbientLight.y += light->color.green;
                        _rpSkinXboxAmbientLight.z += light->color.blue;

                        break;
                    }
                }
            }

            cur = rwLLLinkGetNext(cur);
        }
        while (cur != end);

        if (!(1.0f > _rpSkinXboxAmbientLight.x))
        {
            _rpSkinXboxAmbientLight.x = 1.0f;
        }

        if (!(1.0f > _rpSkinXboxAmbientLight.y))
        {
            _rpSkinXboxAmbientLight.y = 1.0f;
        }

        if (!(1.0f > _rpSkinXboxAmbientLight.z))
        {
            _rpSkinXboxAmbientLight.z = 1.0f;
        }
    }

    if (RpGeometryGetFlags(RpAtomicGetGeometry(atomic)) & rpGEOMETRYPRELIT)
    {
        _rpSkinXboxAmbientLight.w = 0.0f;
    }
    else
    {
        _rpSkinXboxAmbientLight.w = 1.0f;
    }

    RWSRCGLOBAL(lightFrame)++;

    numPointLights = 0;

    for (cur = rwLinkListGetFirstLLLink(&atomic->llWorldSectorsInAtomic);
         cur != rwLinkListGetTerminator(&atomic->llWorldSectorsInAtomic);
         cur = rwLLLinkGetNext(cur))
    {
        RpTie       *tpTie = rwLLLinkGetData(cur, RpTie, lWorldSectorInAtomic);
        RwLLLink    *curLight, *endLight;

        curLight = rwLinkListGetFirstLLLink(&tpTie->worldSector->lightsInWorldSector);
        endLight = rwLinkListGetTerminator(&tpTie->worldSector->lightsInWorldSector);
        while (curLight != endLight)
        {
            RpLightTie  *lightTie = rwLLLinkGetData(curLight, RpLightTie, lightInWorldSector);
            RpLight     *light = lightTie->light;

            if (light && (light->lightFrame != RWSRCGLOBAL(lightFrame)) &&
                (rwObjectTestFlags(light, rpLIGHTLIGHTATOMICS)))
            {
                const RwV3d     *pos;
                const RwSphere  *sphere;
                RwV3d           distanceVector;
                RwReal          distanceSquare;
                RwReal          distanceCollision;

                light->lightFrame = RWSRCGLOBAL(lightFrame);

                pos = &(RwFrameGetLTM(RpLightGetFrame(light))->pos);
                sphere = RpAtomicGetWorldBoundingSphere((RpAtomic *)atomic);

                RwV3dSub(&distanceVector, &sphere->center, pos);

                distanceSquare = RwV3dDotProduct(&distanceVector, &distanceVector);

                distanceCollision = sphere->radius + RpLightGetRadius(light);

                if (distanceSquare < distanceCollision * distanceCollision)
                {
                    if (RpLightGetType(light) == rpLIGHTPOINT)
                    {
                        if ((numPointLights % 4) == 0)
                        {
                            radiusBlock = (RwReal *)shaderConstantPtr;
                            shaderConstantPtr++;
                        }

                        numPointLights++;

                        pos = &(RwFrameGetLTM(RpLightGetFrame(light))->pos);
                        RwV3dTransformPoint((RwV3d *)shaderConstantPtr, pos, &inverseAtomicLTM);
                        shaderConstantPtr->w = 0.0f;
                        shaderConstantPtr++;

                        shaderConstantPtr->x = light->color.red;
                        shaderConstantPtr->y = light->color.green;
                        shaderConstantPtr->z = light->color.blue;
                        shaderConstantPtr->w = 1.0f;
                        shaderConstantPtr++;

                        if (notOrthonormal)
                        {
                            RwV3d   radiusLocal;

                            radiusLocal.x = 0.57735026f;
                            radiusLocal.y = 0.57735026f;
                            radiusLocal.z = 0.57735026f;

                            RwV3dTransformVector(&radiusLocal, &radiusLocal, &inverseAtomicLTM);

                            *radiusBlock++ = RwV3dLength(&radiusLocal) / RpLightGetRadius(light);
                        }
                        else
                        {
                            *radiusBlock++ = 1.0f / RpLightGetRadius(light);
                        }


                        (*pointLightCount)++;
                    }
                }
            }

            curLight = rwLLLinkGetNext(curLight);
        }
    }

    return shaderConstantPtr;
}

// match: __rpSkinXboxEnumerateLights @ 0x002D2130
// sp-match: __rpSkinXboxEnumerateLights @ 0x001ECA80
RwV4d *
_rpSkinXboxEnumerateLights(RwV4d *shaderConstantPtr,
                           RwInt32 *dirLightCount,
                           RwInt32 *pointLightCount,
                           RpAtomic *atomic)
{
    RwUInt32    flags;

    *dirLightCount = 0;
    *pointLightCount = 0;

    flags = RpGeometryGetFlags(RpAtomicGetGeometry(atomic));

    if (flags & rxGEOMETRY_LIGHT)
    {
        shaderConstantPtr->x = 0.0f;
        shaderConstantPtr->y = 0.0f;
        shaderConstantPtr->z = 0.0f;
        shaderConstantPtr->w = 1.0f;

        if (RWSRCGLOBAL(curWorld))
        {
            return FindLights(shaderConstantPtr, dirLightCount, pointLightCount, atomic);
        }
    }
    else
    {
        if (flags & rxGEOMETRY_PRELIT)
        {
            shaderConstantPtr->x = 0.0f;
            shaderConstantPtr->y = 0.0f;
            shaderConstantPtr->z = 0.0f;
            shaderConstantPtr->w = 0.0f;
        }
        else
        {
            shaderConstantPtr->x = 1.0f;
            shaderConstantPtr->y = 1.0f;
            shaderConstantPtr->z = 1.0f;
            shaderConstantPtr->w = 1.0f;
        }
    }

    return shaderConstantPtr + 1;
}

// match: _D3DMATRIXFromRwMatrix @ 0x002D21C0
// sp-match: _D3DMATRIXFromRwMatrix @ 0x001ECB10
static void
D3DMATRIXFromRwMatrix(D3DMATRIX *d, const RwMatrix *m)
{
    RwReal  *dst = (RwReal *)d;

    *dst++ = m->right.x;
    *dst++ = m->up.x;
    *dst++ = m->at.x;
    *dst++ = m->pos.x;

    *dst++ = m->right.y;
    *dst++ = m->up.y;
    *dst++ = m->at.y;
    *dst++ = m->pos.y;

    *dst++ = m->right.z;
    *dst++ = m->up.z;
    *dst++ = m->at.z;
    *dst = m->pos.z;
}

// match: __rpSkinXboxMatrixUpdate @ 0x002D2230
// sp-match: __rpSkinXboxMatrixUpdate @ 0x001ECB80
void
_rpSkinXboxMatrixUpdate(RwV4d *shaderConstants, RpAtomic *atomic, RpSkin *skin)
{
    RpHAnimHierarchy    *hierarchy = RPSKINATOMICGETDATA(atomic)->hierarchy;
    RwMatrix            result;
    RwInt32             i;

    if (hierarchy)
    {
        const RwMatrix  *matrixArray = hierarchy->pMatrixArray;
        const RwMatrix  *skinToBone = RpSkinGetSkinToBoneMatrices(skin);

        if (hierarchy->flags & rpHANIMHIERARCHYNOMATRICES)
        {
            RpHAnimNodeInfo *frameInfo = hierarchy->pNodeInfo;
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;

            RwFrame *frame = RpAtomicGetFrame(atomic);
            rwMatrixInitialize(&inverseLtm, 0);
            rwMatrixInitialize(&tempMatrix, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(frame));

            {
                RwInt32 localIndex;
    for (localIndex = 0; localIndex < skin->platformData.numBonesUsed; localIndex++)
                {
                    RwInt32 bone = skin->platformData.matrixIndexMap[localIndex];

                    { RwFrame *boneFrame = frameInfo[bone].pFrame;
                    RwMatrixMultiply(&tempMatrix, &skinToBone[bone], RwFrameGetLTM(boneFrame)); }
                    RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                    D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[localIndex * 3], &result);

                }
            }
        }
        else if (hierarchy->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES)
        {

            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&result, &skinToBone[bone], &matrixArray[bone]);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);

            }
        }
        else
        {
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;

            RwFrame *frame = RpAtomicGetFrame(atomic);

            i = 0;
            rwMatrixInitialize(&inverseLtm, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(frame));

            for (; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&tempMatrix, &skinToBone[bone], &matrixArray[bone]);
                RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);

            }
        }
    }
    else
    {
        RwReal  *dst = (RwReal *)shaderConstants;

        for (i = 0; i < skin->platformData.numBonesUsed; i++)
        {
            *dst++ = 1.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;

            *dst++ = 0.0f;
            *dst++ = 1.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;

            *dst++ = 0.0f;
            *dst++ = 0.0f;
            *dst++ = 1.0f;
            *dst++ = 0.0f;
        }
    }
}

// match: __rpSkinXboxSetMaterialColor @ 0x002D24F0
// sp-match: __rpSkinXboxSetMaterialColor @ 0x001ECE40
void
_rpSkinXboxSetMaterialColor(const RpMaterial *material, RwUInt32 modulate)
{
    DWORD   *pPush;
    RwReal  ambient;
    const RwSurfaceProperties *surfProps = &material->surfaceProps;

    /* The ambient colour: vertex shader constant -91. */
    pPush = D3DDevice_BeginState(7);

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT_LOAD, 1);
    *pPush++ = 5;
    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT, 4);

    ambient = surfProps->ambient;
    if (ambient != 1.0f)
    {
        ((RwReal *)pPush)[0] = _rpSkinXboxAmbientLight.x * ambient;
        ((RwReal *)pPush)[1] = _rpSkinXboxAmbientLight.y * ambient;
        ((RwReal *)pPush)[2] = _rpSkinXboxAmbientLight.z * ambient;
    }
    else
    {
        ((RwReal *)pPush)[0] = _rpSkinXboxAmbientLight.x;
        ((RwReal *)pPush)[1] = _rpSkinXboxAmbientLight.y;
        ((RwReal *)pPush)[2] = _rpSkinXboxAmbientLight.z;
    }

    ((RwReal *)pPush)[3] = _rpSkinXboxAmbientLight.w;

    D3DDevice_EndState(pPush + 4);

    /* The material colour: vertex shader constant 95. */
    pPush = D3DDevice_BeginState(7);

    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT_LOAD, 1);
    *pPush++ = 0xBF;
    *pPush++ = D3DPUSH_ENCODE(D3DPUSH_SET_TRANSFORM_CONSTANT, 4);

    if (modulate && *(const RwUInt32 *)&material->color != 0xFFFFFFFF)
    {
        const RwReal    scale = material->surfaceProps.diffuse * (1.0f / 255.0f);

        ((RwReal *)pPush)[0] = (RwReal)material->color.red * scale;
        ((RwReal *)pPush)[1] = (RwReal)material->color.green * scale;
        ((RwReal *)pPush)[2] = (RwReal)material->color.blue * scale;
        ((RwReal *)pPush)[3] = (RwReal)material->color.alpha * (1.0f / 255.0f);
    }
    else
    {
        ((RwReal *)pPush)[0] = material->surfaceProps.diffuse;
        ((RwReal *)pPush)[1] = material->surfaceProps.diffuse;
        ((RwReal *)pPush)[2] = material->surfaceProps.diffuse;
        ((RwReal *)pPush)[3] = 1.0f;
    }

    D3DDevice_EndState(pPush + 4);
}

// match: __rpSkinXboxCreateAtomicPipeline @ 0x002D2660
// sp-match: __rpSkinXboxCreateAtomicPipeline @ 0x001ECFB0
RxPipeline *
_rpSkinXboxCreateAtomicPipeline(void)
{
    RxPipeline  *pipe;

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        lpipe = RxPipelineLock(pipe);
        if (NULL != lpipe)
        {
            RxNodeDefinition    *instanceNode = RxNodeDefinitionGetXboxSkinAtomicAllInOne();

            lpipe = RxLockedPipeAddFragment(lpipe, NULL, instanceNode, NULL);

            RxLockedPipeUnlock(lpipe);

            return pipe;
        }

        RxPipelineDestroy(pipe);
    }

    return NULL;
}

/* The skin vertex shader generator's text buffer, its component letters and
 * write masks, and the precompiled fragments it splices around the
 * generated code (named by address: the image has no names for them). */
extern RwChar TextArray[];
static const RwChar elements[4] = { 'x', 'y', 'z', 'w' };
static const RwChar *const off_4185C0[4] = { "x", "xy", "xyz", "xyzw" };
static const DWORD *const off_4185D0[2] = { dword_43677C, dword_436790 };
static const DWORD *const off_4185D8[7] =
{
    dword_4367A4, dword_4367B8, dword_43685C, dword_436890, dword_436954, dword_436968,
    dword_43698C,
};

#define rpSKINXBOXASSEMBLEFLAGS                                         \
    (SASM_SKIPVALIDATION | SASM_DONOTOPTIMIZE | SASM_SKIPPREPROCESSOR | \
     SASM_DISABLE_GLOBAL_OPTIMIZATIONS)

// match: __rpSkinXboxGenerateShader @ 0x002D26B0
// sp-match: __rpSkinXboxGenerateShader @ 0x001ED000
static const DWORD *
_rpSkinXboxGenerateShader(const _rpSkinXboxShaderDesc *desc)
{
    RwChar          *text;
    RwBool          lit = FALSE;
    RwBool          bntLit = FALSE;
    XGBuffer        *transformBuffer = NULL;
    XGBuffer        *directBuffer = NULL;
    XGBuffer        *pointBuffer = NULL;
    RwInt32         baseConstant;
    RwUInt32        i;
    RwInt32         constant;
    const DWORD     *shaders[7];
    RwUInt32        numShaders;
    RwUInt32        numInstructions;
    DWORD           *newShader;

    if (desc->numDirect || desc->numPoint ||
        desc->matfx == 1 || desc->matfx == 2 || desc->matfx == 3 || desc->matfx == 7)
    {
        lit = TRUE;

        if (desc->bnt)
        {
            bntLit = TRUE;
        }
    }

    baseConstant = (desc->numPoint + desc->numDirect) * 2 - 90;
    if (desc->numPoint)
    {
        baseConstant += (desc->numPoint + 3) / 4;
    }

    /* The transform */
    text = TextArray;
    text += rwsprintf(text, "xvs.1.1\n");

    if (desc->numWeights == 1)
    {
        text += rwsprintf(text, "mov a0.x, v2.x\n");
        text += rwsprintf(text, "dp4 r3.x, v0, c[a0.x + %d]\n", baseConstant);
        text += rwsprintf(text, "dp4 r3.y, v0, c[a0.x + %d]\n", baseConstant + 1);
        text += rwsprintf(text, "dp4 r3.z, v0, c[a0.x + %d]\n", baseConstant + 2);

        if (lit)
        {
            text += rwsprintf(text, "dp3 r5.x, v3, c[a0.x + %d]\n", baseConstant);
            text += rwsprintf(text, "dp3 r5.y, v3, c[a0.x + %d]\n", baseConstant + 1);
            text += rwsprintf(text, "dp3 r5.z, v3, c[a0.x + %d]\n", baseConstant + 2);
        }
    }
    else if (lit)
    {
        for (i = 0; i < desc->numWeights; i++)
        {
            text += rwsprintf(text, "mov a0.x, v2.%c\n", elements[i]);

            if (i)
            {
                text += rwsprintf(text, "mad r8, v1.%c, c[a0.x + %d], r8\n", elements[i], baseConstant);
                text += rwsprintf(text, "mad r9, v1.%c, c[a0.x + %d], r9\n", elements[i], baseConstant + 1);
                text += rwsprintf(text, "mad r10, v1.%c, c[a0.x + %d], r10\n", elements[i], baseConstant + 2);
            }
            else
            {
                text += rwsprintf(text, "mul r8, v1.%c, c[a0.x + %d]\n", elements[i], baseConstant);
                text += rwsprintf(text, "mul r9, v1.%c, c[a0.x + %d]\n", elements[i], baseConstant + 1);
                text += rwsprintf(text, "mul r10, v1.%c, c[a0.x + %d]\n", elements[i], baseConstant + 2);
            }
        }

        text += rwsprintf(text, "dp4 r3.x, v0, r8\n");
        text += rwsprintf(text, "dp4 r3.y, v0, r9\n");
        text += rwsprintf(text, "dp4 r3.z, v0, r10\n");
        text += rwsprintf(text, "dp3 r5.x, v3, r8\n");
        text += rwsprintf(text, "dp3 r5.y, v3, r9\n");
        text += rwsprintf(text, "dp3 r5.z, v3, r10\n");
    }
    else
    {
        for (i = 0; i < desc->numWeights; i++)
        {
            text += rwsprintf(text, "mov a0.x, v2.%c\n", elements[i]);
            text += rwsprintf(text, "dp4 r2.x, v0, c[a0.x + %d]\n", baseConstant);
            text += rwsprintf(text, "dp4 r2.y, v0, c[a0.x + %d]\n", baseConstant + 1);
            text += rwsprintf(text, "dp4 r2.z, v0, c[a0.x + %d]\n", baseConstant + 2);

            if (!i)
            {
                text += rwsprintf(text, "mul r3.xyz, v1.%c, r2.xyz\n", elements[i]);
            }
            else
            {
                text += rwsprintf(text, "mad r3.xyz, v1.%c, r2.xyz, r3.xyz\n", elements[i]);
            }
        }
    }

    if (FAILED(XGAssembleShader(NULL, TextArray, text - TextArray, rpSKINXBOXASSEMBLEFLAGS,
                                NULL, &transformBuffer, NULL, NULL, NULL, NULL, NULL)))
    {
        return NULL;
    }

    if (!bntLit)
    {
        /* Directional lights */
        if (desc->numDirect)
        {
            RwUInt32    i;

            text = TextArray;
            text += rwsprintf(text, "xvs.1.1\n");

            for (i = 0; i < desc->numDirect; i += 4)
            {
                RwUInt32    j;
                RwUInt32    count = 4;

                if (desc->numDirect - i < count)
                {
                    count = desc->numDirect - i;
                }

                for (j = 0; j < count; j++)
                {
                    text += rwsprintf(text, "dp3 r6.%c, c[%d + -90], r5\n",
                                      elements[j], (i + j) * 2);
                }

                text += rwsprintf(text, "max r6.%s, c[-90].w, -r6.%s\n",
                                  off_4185C0[count - 1], off_4185C0[count - 1]);

                for (j = 0; j < count; j++)
                {
                    text += rwsprintf(text, "mad r11.xyz, c[%d + 1 + -90].xyz, r6.%c%c%c, r11.xyz\n",
                                      (i + j) * 2, elements[j], elements[j], elements[j]);
                }

            }

            if (FAILED(XGAssembleShader(NULL, TextArray, text - TextArray, rpSKINXBOXASSEMBLEFLAGS,
                                        NULL, &directBuffer, NULL, NULL, NULL, NULL, NULL)))
            {
                return NULL;
            }
        }

        /* Point lights */
        if (desc->numPoint)
        {
            RwUInt32    i;

            text = TextArray;
            text += rwsprintf(text, "xvs.1.1\n");

            constant = desc->numDirect * 2;
            for (i = 0; i < desc->numPoint; i += 4)
            {
                const RwChar    *mask;
                RwUInt32        j;
                RwUInt32        count = 4;

                if (desc->numPoint - i < count)
                {
                    count = desc->numPoint - i;
                }

                for (j = 0; j < count; j++)
                {
                    text += rwsprintf(text, "add r7.xyz, - c[%d + -90].xyz, r3.xyz\n",
                                      constant + 1 + j * 2);
                    text += rwsprintf(text, "dp3 r1.%c, r7, r7\n", elements[j]);
                    text += rwsprintf(text, "rsq r1.%c, r1.%c\n", elements[j], elements[j]);
                    text += rwsprintf(text, "dp3 r6.%c, r5, r7\n", elements[j]);
                }

                mask = off_4185C0[count - 1];
                text += rwsprintf(text, "max r8.%s, c[%d + -90].%s, r1.%s\n",
                                  mask, constant, mask, mask);
                text += rwsprintf(text, "max r6.%s, c[%d + 1 + -90].wwww, -r6.%s\n",
                                  mask, constant, mask);
                text += rwsprintf(text, "add r8.%s, -c[%d + -90].%s, r8.%s\n",
                                  mask, constant, mask, mask);
                text += rwsprintf(text, "mul r6.%s, r6.%s, r8.%s\n", mask, mask, mask);

                for (j = 0; j < count; j++)
                {
                    text += rwsprintf(text, "mad r11.xyz, c[%d + 1 + -90].xyz, r6.%c%c%c, r11.xyz\n",
                                      constant + 1 + j * 2, elements[j], elements[j], elements[j]);
                }

                constant += count * 2 + 1;
            }

            if (FAILED(XGAssembleShader(NULL, TextArray, text - TextArray, rpSKINXBOXASSEMBLEFLAGS,
                                        NULL, &pointBuffer, NULL, NULL, NULL, NULL, NULL)))
            {
                return NULL;
            }
        }
    }
    else
    {
        /* Bump mapped lighting */
        text = TextArray;
        text += rwsprintf(text, "xvs.1.1\n");

        if (desc->numWeights == 1)
        {
            text += rwsprintf(text, "dp3 r4.x, v9, c[a0.x + %d]\n", baseConstant);
            text += rwsprintf(text, "dp3 r4.y, v9, c[a0.x + %d]\n", baseConstant + 1);
            text += rwsprintf(text, "dp3 r4.z, v9, c[a0.x + %d]\n", baseConstant + 2);
        }
        else
        {
            text += rwsprintf(text, "dp3 r4.x, v9, r8\n");
            text += rwsprintf(text, "dp3 r4.y, v9, r9\n");
            text += rwsprintf(text, "dp3 r4.z, v9, r10\n");
        }

        if (desc->prelit)
        {
            text += rwsprintf(text, "mov oD0, v4\n");
        }

        text += rwsprintf(text, "mul r2, r4.zxyw, r5.yzxw\n");
        text += rwsprintf(text, "mad r2, r4.yzxw, r5.zxyw, -r2\n");

        if (desc->numDirect)
        {
            text += rwsprintf(text, "dp3 r1.x, c[0 + -90], r4\n");
            text += rwsprintf(text, "dp3 r1.y, c[0 + -90], r2\n");
            text += rwsprintf(text, "dp3 r1.z, c[0 + -90], r5\n");
            text += rwsprintf(text, "dp3 r1.w, r1, r1\n");
            text += rwsprintf(text, "rsq r1.w, r1.w\n");
            text += rwsprintf(text, "mul r1.xyz, r1, r1.w\n");

            if (desc->matfx != 2 && desc->matfx != 3)
            {
                text += rwsprintf(text, "mad oT2.xyz, r1, c[0 + -90].w, c[0 + -90].w\n");
            }
            else if (desc->prelit)
            {
                text += rwsprintf(text, "mad oD1.xyz, r1, c[0 + -90].w, c[0 + -90].w\n");
            }
            else
            {
                text += rwsprintf(text, "mad oD0.xyz, r1, c[0 + -90].w, c[0 + -90].w\n");
            }
        }
        else if (desc->numPoint)
        {
            text += rwsprintf(text, "add r7.xyz, - c[1 + -90].xyz, r3.xyz\n");
            text += rwsprintf(text, "dp3 r7.w, r7, r7\n");
            text += rwsprintf(text, "rsq r7.w, r7.w\n");
            text += rwsprintf(text, "mul r7.xyz, r7, r7.w\n");
            text += rwsprintf(text, "rcp r7.w, r7.w\n");
            text += rwsprintf(text, "mad r7.w, r7.w, c[0 + -90].x, c[0 + -90].y\n");
            text += rwsprintf(text, "max r7.w, r7.w, c[0 + -90].w\n");
            text += rwsprintf(text, "dp3 r1.x, r7, r4\n");
            text += rwsprintf(text, "dp3 r1.y, r7, r2\n");
            text += rwsprintf(text, "dp3 r1.z, r7, r5\n");
            text += rwsprintf(text, "dp3 r1.w, r1, r1\n");
            text += rwsprintf(text, "rsq r1.w, r1.w\n");
            text += rwsprintf(text, "mul r1.xyz, r1, r1.w\n");
            text += rwsprintf(text, "mul r1.xyz, r1, r7.w\n");

            if (desc->matfx != 2 && desc->matfx != 3)
            {
                text += rwsprintf(text, "mad oT2.xyz, r1, c[0 + -90].z, c[0 + -90].z\n");
            }
            else if (desc->prelit)
            {
                text += rwsprintf(text, "mad oD1.xyz, r1, c[0 + -90].z, c[0 + -90].z\n");
            }
            else
            {
                text += rwsprintf(text, "mad oD0.xyz, r1, c[0 + -90].z, c[0 + -90].z\n");
            }
        }

        if (desc->matfx == 2 || desc->matfx == 3)
        {
            text += rwsprintf(text, "dp3 oT2.x, c[0 + 93], r4\n");
            text += rwsprintf(text, "dp3 oT2.y, c[0 + 93], r2\n");
            text += rwsprintf(text, "dp3 oT2.z, c[0 + 93], r5\n");
            text += rwsprintf(text, "dp3 oT3.x, c[1 + 93], r4\n");
            text += rwsprintf(text, "dp3 oT3.y, c[1 + 93], r2\n");
            text += rwsprintf(text, "dp3 oT3.z, c[1 + 93], r5\n");
        }

        text += rwsprintf(text, "mov oT0.xy, v%d\n", desc->bnt + 4);
        text += rwsprintf(text, "mov oT1.xy, v5\n");

        if (FAILED(XGAssembleShader(NULL, TextArray, text - TextArray, rpSKINXBOXASSEMBLEFLAGS,
                                    NULL, &directBuffer, NULL, NULL, NULL, NULL, NULL)))
        {
            return NULL;
        }
    }

    /* Splice the pieces */
    shaders[0] = (const DWORD *)XGBuffer_GetBufferPointer(transformBuffer);
    *(DWORD *)shaders[0] += 0xFFFE0000;
    numInstructions = ((const RwUInt8 *)shaders[0])[2];
    numShaders = 1;

    if (lit)
    {
        shaders[1] = dword_436748;
        numInstructions += ((const RwUInt8 *)dword_436748)[2];
        numShaders = 2;
    }

    shaders[numShaders] = off_4185D0[desc->prelit];
    numInstructions += ((const RwUInt8 *)shaders[numShaders])[2];
    numShaders++;

    if (desc->numDirect)
    {
        shaders[numShaders] = (const DWORD *)XGBuffer_GetBufferPointer(directBuffer);
        *(DWORD *)shaders[numShaders] += 0xFFFE0000;
        numInstructions += ((const RwUInt8 *)shaders[numShaders])[2];
        numShaders++;
    }

    if (desc->numPoint)
    {
        shaders[numShaders] = (const DWORD *)XGBuffer_GetBufferPointer(pointBuffer);
        *(DWORD *)shaders[numShaders] += 0xFFFE0000;
        numInstructions += ((const RwUInt8 *)shaders[numShaders])[2];
        numShaders++;
    }

    if (!bntLit)
    {
        if (desc->matfx < 7)
        {
            shaders[numShaders] = off_4185D8[desc->matfx];
            numInstructions += ((const RwUInt8 *)shaders[numShaders])[2];
            numShaders++;
        }

        shaders[numShaders] = dword_4369B0;
        numInstructions += ((const RwUInt8 *)dword_4369B0)[2];
        numShaders++;
    }
    else
    {
        shaders[numShaders] = dword_436A28;
        numInstructions += ((const RwUInt8 *)dword_436A28)[2];
        numShaders++;
    }

    newShader = (DWORD *)RwMalloc((numInstructions + 4) * 16,
                                  rwID_SKINPLUGIN | rwMEMHINTDUR_EVENT);

    XGSpliceVertexShaders(newShader, NULL, NULL, shaders, numShaders, TRUE);

    if (pointBuffer)
    {
        XGBuffer_Release(pointBuffer);
    }

    if (directBuffer)
    {
        XGBuffer_Release(directBuffer);
    }

    if (transformBuffer)
    {
        XGBuffer_Release(transformBuffer);
    }

    return newShader;
}

// match: _BinaryFindVertexShader @ 0x002D3110
// sp-match: _BinaryFindVertexShader @ 0x001EDA60
static RwInt32
BinaryFindVertexShader(const _rpSkinXboxShaderDesc *value,
                       const _rpSkinXboxShaderItemDesc *buffer,
                       RwInt32 numElems)
{
    RwInt32     lowerValue = 0;
    RwInt32     higherValue;
    RwInt32     midleValue;

    if (numElems > 0)
    {
        higherValue = numElems - 1;

        do
        {
            if (numElems <= 1)
            {
                if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[lowerValue].desc)
                {
                    return lowerValue;
                }

                if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[lowerValue].desc)
                {
                    return -(lowerValue + 1);
                }

                return -(lowerValue + 2);
            }

            midleValue = lowerValue + numElems / 2 - (1 - (numElems & 1));

            if (*(const RwUInt32 *)value == *(const RwUInt32 *)&buffer[midleValue].desc)
            {
                return midleValue;
            }

            if (*(const RwUInt32 *)value < *(const RwUInt32 *)&buffer[midleValue].desc)
            {
                higherValue = midleValue - 1;
            }
            else
            {
                lowerValue = midleValue + 1;
            }

            numElems = higherValue - lowerValue + 1;
        }
        while (numElems > 0);
    }

    return -(lowerValue + 1);
}

// match: __rpSkinXboxGetShader @ 0x002D3180
// sp-match: __rpSkinXboxGetShader @ 0x001EDAD0
const DWORD *
_rpSkinXboxGetShader(const _rpSkinXboxShaderDesc *desc)
{
    RwInt32         index;
    const DWORD     *byteCode;

    if (*(const RwUInt32 *)&LastVertexShaderDesc->desc == *(const RwUInt32 *)desc)
    {
        LastVertexShaderDesc->renderFrame = RWSRCGLOBAL(renderFrame);

        return LastVertexShaderDesc->byteCode;
    }

    index = BinaryFindVertexShader(desc, VertexShaderCache, NumShadersInCache);
    if (index >= 0)
    {
        LastVertexShaderDesc = &VertexShaderCache[index];
        LastVertexShaderDesc->renderFrame = RWSRCGLOBAL(renderFrame);

        return LastVertexShaderDesc->byteCode;
    }

    byteCode = _rpSkinXboxGenerateShader(desc);

    if (NumShadersInCache >= rpSKINXBOXSHADERCACHESIZE)
    {
        _rpSkinXboxShaderItemDesc   *oldest = VertexShaderCache;
        RwInt32                     i;

        for (i = 1; i < NumShadersInCache; i++)
        {
            if (VertexShaderCache[i].renderFrame < oldest->renderFrame)
            {
                oldest = &VertexShaderCache[i];
            }
        }

        oldest->desc = *desc;
        oldest->renderFrame = RWSRCGLOBAL(renderFrame);

        if (oldest->byteCode)
        {
            RwFree((void *)oldest->byteCode);
        }

        oldest->byteCode = byteCode;

        LastVertexShaderDesc = oldest;
    }
    else
    {
        index = -(index + 1);

        if (index < NumShadersInCache)
        {
            memmove(&VertexShaderCache[index + 1], &VertexShaderCache[index],
                    (NumShadersInCache - index) * sizeof(_rpSkinXboxShaderItemDesc));
        }

        LastVertexShaderDesc = &VertexShaderCache[index];
        LastVertexShaderDesc->desc = *desc;
        LastVertexShaderDesc->byteCode = byteCode;
        LastVertexShaderDesc->renderFrame = RWSRCGLOBAL(renderFrame);
        NumShadersInCache++;
    }

    return byteCode;
}

// match: _RpXboxSkinVertexShaderCachePurge @ 0x002D32A0
// sp-match: _RpXboxSkinVertexShaderCachePurge @ 0x001EDBF0
void
RpXboxSkinVertexShaderCachePurge(void)
{
    RwInt32 i;

    for (i = 0; i < NumShadersInCache; i++)
    {
        if (VertexShaderCache[i].byteCode)
        {
            RwFree((void *)VertexShaderCache[i].byteCode);
            VertexShaderCache[i].byteCode = NULL;
        }
    }

    NumShadersInCache = 0;

    LastVertexShaderDesc = VertexShaderCache;

    LastVertexShaderDesc->desc.numWeights = 0;
    LastVertexShaderDesc->desc.numDirect = 0;
    LastVertexShaderDesc->desc.numPoint = 0;
    LastVertexShaderDesc->desc.matfx = 0;
    LastVertexShaderDesc->desc.bnt = 0;
    LastVertexShaderDesc->desc.prelit = 0;
}

// match: __rpSkinXboxDestroyShaders @ 0x002D3310
// sp-match: __rpSkinXboxDestroyShaders @ 0x001EDC60
void
_rpSkinXboxDestroyShaders(void)
{
    if (shadersInited)
    {
        shadersInited = FALSE;

        _rpSkinXboxVertexFormatDestroy();

        _rpSkinXboxPurgeShaderCache();
    }

    RpXboxSkinVertexShaderCachePurge();
}
