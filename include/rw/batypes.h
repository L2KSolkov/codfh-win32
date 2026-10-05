/*
 * TRUE/FALSE, RwRGBAReal, RwV2d, RwV3d, RwSphere, RwLine, RwRGBA, RwPlane, RwFrustumPlane, RwBBox, RwLLLink, RwLinkList and their accessors
 * (from RWSDK/src/plcore/balist.h), RWFORCEENUMSIZEINT and the MACRO_START/MACRO_STOP
 * wrappers, copied from RenderWare 3.7.2
 * RWSDK/src/plcore/batypes.h. The image links RenderWare 3.6; a vector of three RwReal is the same
 * in both, and the game reads these as three floats (fld at +0, +4, +8).
 */
#ifndef RW_BATYPES_H
#define RW_BATYPES_H

#include <stddef.h>
#include "rw/ostypes.h"

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE !FALSE

#ifndef MACRO_START
#define MACRO_START do
#endif /* MACRO_START */

#ifndef MACRO_STOP
#define MACRO_STOP while(0)
#endif /* MACRO_STOP */

typedef struct RwRGBAReal RwRGBAReal;
struct RwRGBAReal
{
    RwReal red;
    RwReal green;
    RwReal blue;
    RwReal alpha;
};

typedef struct RwV3d RwV3d;
struct RwV3d
{
    RwReal x;   /**< X value */
    RwReal y;   /**< Y value */
    RwReal z;   /**< Z value */
};

typedef struct RwSphere RwSphere;
struct RwSphere
{
    RwV3d center;   /**< Sphere center */
    RwReal radius;  /**< Sphere radius */
};

typedef struct RwV2d RwV2d;
struct RwV2d
{
    RwReal x;   /**< X value*/
    RwReal y;   /**< Y value */
};

typedef struct RwLine RwLine;
struct RwLine
{
    RwV3d start;    /**< Line start */
    RwV3d end;      /**< Line end */
};

typedef struct RwRGBA RwRGBA;
struct RwRGBA
{
    RwUInt8 red;    /**< red component */
    RwUInt8 green;  /**< green component */
    RwUInt8 blue;   /**< blue component */
    RwUInt8 alpha;  /**< alpha component */
};

/* RwPlane and RwFrustumPlane (RWSDK/src/babbox.h and bacamera.h). */
typedef struct RwPlane RwPlane;
struct RwPlane
{
    RwV3d normal;       /**< Normal to the plane */
    RwReal distance;    /**< Distance to plane from origin in normal direction*/
};

typedef struct RwFrustumPlane RwFrustumPlane;
struct RwFrustumPlane
{
    RwPlane plane;
    RwUInt8 closestX;
    RwUInt8 closestY;
    RwUInt8 closestZ;
    RwUInt8 pad;
};

typedef struct RwBBox RwBBox;
struct RwBBox
{
    /* Must be in this order */
    RwV3d sup;   /**< Supremum vertex. */
    RwV3d inf;   /**< Infimum vertex. */
};

typedef struct RwLLLink RwLLLink;
struct RwLLLink
{
    RwLLLink *next;
    RwLLLink *prev;
};

typedef struct RwLinkList RwLinkList;
struct RwLinkList
{
    RwLLLink link;
};

#define rwLinkListGetFirstLLLink(list) ((list)->link.next)
#define rwLinkListGetTerminator(list)  (&((list)->link))
#define rwLLLinkGetData(linkvar, type, entry)                           \
    ((type *)(((RwUInt8 *)(linkvar)) - offsetof(type, entry)))

#define RWFORCEENUMSIZEINT ((RwInt32)((~((RwUInt32)0))>>1))

/* A plugin's data in its object, from RWSDK/src/plcore/batype.h (the game's
 * clump data plugin, sub_EC6C0, reaches its data with it). */
#define RWPLUGINOFFSET(_type, _base, _offset) ((_type *)((RwUInt8 *)(_base) + (_offset)))

/* A rectangle (RWSDK rwplcore.h): the sub-raster camera's
 * (RWS::CameraHelper::CreateSubRasterCamera). */
typedef struct RwRect RwRect;
struct RwRect
{
    RwInt32 x;
    RwInt32 y;
    RwInt32 w;
    RwInt32 h;
};

/* rwPI (RWSDK rwplcore.h). */
#define rwPI ((RwReal)(3.1415926535f))

/* From RWSDK/src/plcore/bacolor.h: a real colour quantised to bytes. */
#define RwInt32FromRealMacro(x) ((RwInt32)(x))
#define RwRGBAFromRwRGBARealMacro(o, i)                                  MACRO_START                                                              {                                                                            RwInt32 quantize;                                                                                                                                 quantize = RwInt32FromRealMacro(((i)->red * (RwReal)255.0) + (RwReal)0.5);       (o)->red = (RwUInt8)quantize;                                            quantize = RwInt32FromRealMacro(((i)->green * (RwReal)255.0) + (RwReal)0.5);     (o)->green = (RwUInt8)quantize;                                          quantize = RwInt32FromRealMacro(((i)->blue * (RwReal)255.0) + (RwReal)0.5);      (o)->blue = (RwUInt8)quantize;                                           quantize = RwInt32FromRealMacro(((i)->alpha * (RwReal)255.0) + (RwReal)0.5);     (o)->alpha = (RwUInt8)quantize;                                      }                                                                        MACRO_STOP

#endif
