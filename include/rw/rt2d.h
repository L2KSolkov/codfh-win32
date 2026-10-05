/*
 * The Rt2d calls the game's font (type_DA580) makes, copied from RenderWare
 * 3.7.2 RWSDK/include/null/rt2d.h (the prototypes, Rt2dBBox, the opaque font,
 * and the brush with its shade parameters from RWSDK/tool/2d/rt2d.h) and batxdict.h (RwTexDictionaryDestroy). Several are named
 * without the C underscore in the database, and 0x255220 as
 * Rt2dFontTexDictionaryGet (config/aliases.txt).
 */
#ifndef RW_RT2D_H
#define RW_RT2D_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

typedef struct RwCamera RwCamera;

typedef struct Rt2dFont Rt2dFont;
typedef struct Rt2dBrush Rt2dBrush;
typedef struct RwTexDictionary RwTexDictionary;
typedef struct RwTexture RwTexture;
typedef struct RpMaterial RpMaterial;

/* The brush (private in RW; the font reads its colorCache's alpha, +0x63). */
typedef struct rt2dShadeParameters rt2dShadeParameters;
struct rt2dShadeParameters
{
    RwRGBAReal          col;    /* col */
    RwV2d               uv;     /* uv */
};

struct Rt2dBrush
{
    rt2dShadeParameters top;
    rt2dShadeParameters dtop;
    rt2dShadeParameters bottom;
    rt2dShadeParameters dbottom;
    RwRGBA              colorCache;
    RwInt32             flag;
    RwTexture          *texture;
    RpMaterial         *material;
    RwReal              halfwidth;
    RwInt32             refCount;
};

typedef struct Rt2dBBox Rt2dBBox;
struct Rt2dBBox
{
    RwReal x;
    RwReal y;
    RwReal w;
    RwReal h;
};

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern Rt2dBrush *Rt2dBrushCreate(void);
extern RwBool Rt2dBrushDestroy(Rt2dBrush *brush);
extern Rt2dBrush *Rt2dBrushSetRGBA(Rt2dBrush *brush, RwRGBA *col0, RwRGBA *col1, RwRGBA *col2,
                                   RwRGBA *col3);
extern Rt2dFont *Rt2dFontRead(const RwChar *name);
extern RwBool Rt2dFontDestroy(Rt2dFont *font);
extern RwReal Rt2dFontGetHeight(Rt2dFont *font);
extern RwReal Rt2dFontGetStringWidth(Rt2dFont *font, const RwChar *string, RwReal height);
extern RwBool Rt2dFontIsUnicode(Rt2dFont *font);
extern Rt2dFont *Rt2dFontShow(Rt2dFont *font, const RwChar *string, RwReal height, RwV2d *anchor,
                              Rt2dBrush *brush);
extern RwTexDictionary *Rt2dFontTexDictionarySet(RwTexDictionary *texDict);
extern RwBool Rt2dCTMPush(void);
extern RwBool Rt2dCTMPop(void);
extern RwBool Rt2dCTMSetIdentity(void);
extern RwBool Rt2dCTMScale(RwReal x, RwReal y);
extern RwBool Rt2dDeviceGetStep(RwV2d *xstep, RwV2d *ystep, RwV2d *origin);
extern RwBool Rt2dDeviceGetMetric(RwReal *x, RwReal *y, RwReal *w, RwReal *h);
extern RwBool Rt2dDeviceSetCamera(RwCamera *cam);
extern RwBool Rt2dDeviceSetFlat(RwReal r);
extern const RwChar *Rt2dFontSetPath(const RwChar *path);
extern RwBool RwTexDictionaryDestroy(RwTexDictionary *dict);
/* A Rt2d maestro (opaque; RenderWare Studio's resource handler destroys
 * them). */
typedef struct Rt2dMaestro Rt2dMaestro;
extern RwBool Rt2dMaestroDestroy(Rt2dMaestro *maestro);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
