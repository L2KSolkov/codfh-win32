/*
 * Rt2d's private font layout, which the game's font (type_DA580::sub_DB3E0)
 * reads directly: Rt2dFont, rt2dCharRect and the FontCharGetCode macro,
 * copied from RenderWare 3.7.2 RWSDK/tool/2d/font.h, with _rwSListGetArray
 * from RWSDK/src/plcore/balist.h. The image links 3.6; the offsets it reads
 * match this layout (intergap +0xC, aCharIndex +0x24, uCharOffset +0x124,
 * uCharIndexCount +0x128, uCharIndex +0x12C, charMap +0x134, and the 32-byte
 * rect with its width first).
 */
#ifndef RW_RT2DFONT_H
#define RW_RT2DFONT_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rt2d.h"

#define rtFONTMAXPAGES          4
#define rtFONTACHARINDEXSIZE    128

typedef struct RwSList RwSList;
typedef struct RwTexture RwTexture;
typedef struct Rt2dPath Rt2dPath;

typedef Rt2dFont   *(*Rt2dFontShowCallBack)
    (Rt2dFont * font, const RwChar * string,
     RwReal height, RwV2d * anchor, Rt2dBrush * brush);

typedef struct rt2dCharRect rt2dCharRect;
struct rt2dCharRect
{
    RwReal              width;
    RwTexture          *tex;
    RwV2d               uv[2];
    Rt2dPath           *path;
    RwInt8              charpage;
};

struct Rt2dFont
{
    RwBool              isOutline;
    RwReal              height, baseline;
    RwReal              intergap;

    RwUInt32            flag;

    RwTexture          *textures[rtFONTMAXPAGES];

    RwInt16             aCharIndex[rtFONTACHARINDEXSIZE];

    RwInt32             uCharOffset;
    RwInt32             uCharIndexCount;
    RwInt16            *uCharIndex;

    RwInt32             charCount;
    RwSList            *charMap;

    Rt2dFontShowCallBack fontshowCB;

    Rt2dFont           *nextBatch;
    void               *strCache;
};

#define FontCharGetCode(_code, _c, _font) \
MACRO_START \
    if ((_c) >= rtFONTACHARINDEXSIZE) \
    { \
        (_code) = (_c) - (_font)->uCharOffset; \
        if (((_code) >= 0) && ((_code) < (_font)->uCharIndexCount)) \
        { \
            (_code) = (RwInt32) (_font)->uCharIndex[(_code)]; \
        } \
        else \
        { \
            (_code) = -1; \
        } \
    } \
    else \
    { \
        (_code) = (RwInt32) (_font)->aCharIndex[(_c)]; \
    } \
MACRO_STOP

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern void        *_rwSListGetArray(RwSList *sList);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define rwSListGetArray(sList) \
       _rwSListGetArray(sList)

#endif
