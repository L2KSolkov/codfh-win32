/*
 * RenderWare's immediate mode as the game's font draws a pad button
 * (sub_DC0D0), copied from RenderWare 3.7.2: the render states and their
 * values, RwPrimitiveType (rwplcore.h), the leading fields of RwDevice
 * (RWSDK/src/plcore/badevice.h) and RwGlobals (balibtyp.h) with the
 * RWSRCGLOBAL, RwRenderStateSet/Get, RwIm2DRenderPrimitive and
 * RwIm2DGetNear/FarScreenZ macros, and the D3D8 RwIm2DVertex and its setters
 * and getters
 * (driver/d3d8/drvmodel.h).
 *
 * The game was built with RWGLOBALSIZE: RwEngineInstance is the static
 * ourGlobals array (RenderWare's badevice.c, at 0x5200E0), read directly
 * (zBufferNear at 0x5200F8, fpRenderStateSet at 0x520100, the string
 * functions from 0x5201D0, the memory functions from 0x520214). RwGlobals
 * is declared up to memoryFree (RenderWare 3.6's layout: the file functions
 * 3.7.2 dropped sit after dirtyFrameList), with RenderWare's string and
 * memory macros (rwstrcmp, RwMalloc, RwFreeListAlloc, ...).
 */
#ifndef RW_BADEVICE_H
#define RW_BADEVICE_H

#include <stdarg.h>
#include <stddef.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamemory.h"
#include "rw/osintf.h"

enum RwRenderState
{
    rwRENDERSTATENARENDERSTATE = 0,
    rwRENDERSTATETEXTURERASTER,
    rwRENDERSTATETEXTUREADDRESS,
    rwRENDERSTATETEXTUREADDRESSU,
    rwRENDERSTATETEXTUREADDRESSV,
    rwRENDERSTATETEXTUREPERSPECTIVE,
    rwRENDERSTATEZTESTENABLE,
    rwRENDERSTATESHADEMODE,
    rwRENDERSTATEZWRITEENABLE,
    rwRENDERSTATETEXTUREFILTER,
    rwRENDERSTATESRCBLEND,
    rwRENDERSTATEDESTBLEND,
    rwRENDERSTATEVERTEXALPHAENABLE,
    rwRENDERSTATEBORDERCOLOR,
    rwRENDERSTATEFOGENABLE,
    rwRENDERSTATEFOGCOLOR,
    rwRENDERSTATEFOGTYPE,
    rwRENDERSTATEFOGDENSITY,
    rwRENDERSTATECULLMODE = 20,
    rwRENDERSTATESTENCILENABLE,
    rwRENDERSTATESTENCILFAIL,
    rwRENDERSTATESTENCILZFAIL,
    rwRENDERSTATESTENCILPASS,
    rwRENDERSTATESTENCILFUNCTION,
    rwRENDERSTATESTENCILFUNCTIONREF,
    rwRENDERSTATESTENCILFUNCTIONMASK,
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK,
    rwRENDERSTATEALPHATESTFUNCTION,
    rwRENDERSTATEALPHATESTFUNCTIONREF,
    rwRENDERSTATEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwRenderState RwRenderState;

/* The values the font sets. */
#define rwFILTERNEAREST         1
#define rwFILTERLINEAR          2
#define rwTEXTUREADDRESSCLAMP   3
#define rwBLENDONE              2
#define rwBLENDSRCALPHA         5
#define rwBLENDINVSRCALPHA      6
#define rwCULLMODECULLNONE      1
#define rwCULLMODECULLBACK      2
#define rwSHADEMODEGOURAUD      2
#define rwALPHATESTFUNCTIONGREATER 5
#define rwALPHATESTFUNCTIONALWAYS 8

enum RwPrimitiveType
{
    rwPRIMTYPENAPRIMTYPE = 0,
    rwPRIMTYPELINELIST = 1,
    rwPRIMTYPEPOLYLINE = 2,
    rwPRIMTYPETRILIST = 3,
    rwPRIMTYPETRISTRIP = 4,
    rwPRIMTYPETRIFAN = 5,
    rwPRIMTYPEPOINTLIST = 6,
    rwPRIMITIVETYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwPrimitiveType RwPrimitiveType;

typedef struct RwD3D8Vertex RwD3D8Vertex;
struct RwD3D8Vertex
{
    RwReal      x;              /**< Screen X */
    RwReal      y;              /**< Screen Y */
    RwReal      z;              /**< Screen Z */
    RwReal      rhw;            /**< Reciprocal of homogeneous W */

    RwUInt32    emissiveColor;  /**< Vertex color */

    RwReal      u;              /**< Texture coordinate U */
    RwReal      v;              /**< Texture coordinate V */
};
typedef RwD3D8Vertex    RwIm2DVertex;

#define RwIm2DVertexSetRecipCameraZ(vert, recipz)   ((vert)->rhw = recipz)
#define RwIm2DVertexSetScreenX(vert, scrnx)         ((vert)->x = (scrnx))
#define RwIm2DVertexSetScreenY(vert, scrny)         ((vert)->y = (scrny))
#define RwIm2DVertexSetScreenZ(vert, scrnz)         ((vert)->z = (scrnz))
#define RwIm2DVertexSetU(vert, texU, recipz)        ((vert)->u = (texU))
#define RwIm2DVertexSetV(vert, texV, recipz)        ((vert)->v = (texV))
#define RwIm2DVertexGetRed(vert)    \
    (((vert)->emissiveColor >> 16) & 0xFF)
#define RwIm2DVertexGetGreen(vert)  \
    (((vert)->emissiveColor >> 8) & 0xFF)
#define RwIm2DVertexGetBlue(vert)   \
    ((vert)->emissiveColor & 0xFF)
#define RwIm2DVertexGetAlpha(vert)  \
    (((vert)->emissiveColor >> 24) & 0xFF)
#define RwIm2DVertexSetIntRGBA(vert, red, green, blue, alpha)   \
    ((vert)->emissiveColor =                                    \
     ((((RwUInt32)(alpha)) << 24) |                             \
      (((RwUInt32)(red)) << 16) |                               \
      (((RwUInt32)(green)) << 8) |                              \
      (((RwUInt32)(blue)))))

typedef RwBool (*RwRenderStateSetFunction)(RwRenderState nState, void *pParam);
typedef RwBool (*RwRenderStateGetFunction)(RwRenderState nState, void *pParam);
typedef RwBool (*RwIm2DRenderLineFunction)(RwIm2DVertex *vertices, RwInt32 numVertices,
                                           RwInt32 vert1, RwInt32 vert2);
typedef RwBool (*RwIm2DRenderTriangleFunction)(RwIm2DVertex *vertices, RwInt32 numVertices,
                                               RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
typedef RwBool (*RwIm2DRenderPrimitiveFunction)(RwPrimitiveType primType,
                                                RwIm2DVertex *vertices, RwInt32 numVertices);

typedef RwBool (*RwIm2DRenderIndexedPrimitiveFunction)(RwPrimitiveType primType, RwIm2DVertex *vertices,
                                                       RwInt32 numVertices, RwUInt16 *indices,
                                                       RwInt32 numIndices);

typedef RwBool (*RwIm3DRenderLineFunction)(RwInt32 vert1, RwInt32 vert2);
typedef RwBool (*RwIm3DRenderTriangleFunction)(RwInt32 vert1, RwInt32 vert2, RwInt32 vert3);
typedef RwBool (*RwIm3DRenderPrimitiveFunction)(RwPrimitiveType primType);
typedef RwBool (*RwIm3DRenderIndexedPrimitiveFunction)(RwPrimitiveType primtype, RwUInt16 *indices,
                                                       RwInt32 numIndices);

typedef struct RwDevice RwDevice;
struct RwDevice
{
    RwReal                                  gammaCorrection; /* Gamma correction  */
    void                                   *fpSystem;  /* System handler */
    RwReal                                  zBufferNear; /* Near Z buffer value */
    RwReal                                  zBufferFar; /* Far Z buffer value */

    /* Immediate mode functions */
    RwRenderStateSetFunction                fpRenderStateSet; /* Internal Use */
    RwRenderStateGetFunction                fpRenderStateGet; /* Internal Use */

    /* Render functions */
    RwIm2DRenderLineFunction                fpIm2DRenderLine; /* Internal Use */
    RwIm2DRenderTriangleFunction            fpIm2DRenderTriangle; /* Internal Use */
    RwIm2DRenderPrimitiveFunction           fpIm2DRenderPrimitive; /* Internal Use */
    RwIm2DRenderIndexedPrimitiveFunction    fpIm2DRenderIndexedPrimitive; /* Internal Use */

    RwIm3DRenderLineFunction                fpIm3DRenderLine; /* Internal Use */
    RwIm3DRenderTriangleFunction            fpIm3DRenderTriangle; /* Internal Use */
    RwIm3DRenderPrimitiveFunction           fpIm3DRenderPrimitive; /* Internal Use */
    RwIm3DRenderIndexedPrimitiveFunction    fpIm3DRenderIndexedPrimitive; /* Internal Use */
};

/* The standard functions (rwplcore.h): the device's native texture reader. */
typedef RwBool (*RwStandardFunc)(void *pOut, void *pInOut, RwInt32 nI);
#define rwSTANDARDNATIVETEXTUREREAD     26  /* Read native texture from the stream */
#define rwSTANDARDNUMOFSTANDARD         29

/* RwStringFunctions (rwstring.h). */
typedef int (*vecSprintfFunc)(RwChar *buffer, const RwChar *format, ...);
typedef int (*vecVsprintfFunc)(RwChar *buffer, const RwChar *format, va_list argptr);
typedef RwChar *(*vecStrcpyFunc)(RwChar *dest, const RwChar *srce);
typedef RwChar *(*vecStrncpyFunc)(RwChar *dest, const RwChar *srce, size_t size);
typedef RwChar *(*vecStrcatFunc)(RwChar *dest, const RwChar *srce);
typedef RwChar *(*vecStrncatFunc)(RwChar *dest, const RwChar *srce, size_t size);
typedef RwChar *(*vecStrrchrFunc)(const RwChar *string, int findThis);
typedef RwChar *(*vecStrchrFunc)(const RwChar *string, int findThis);
typedef RwChar *(*vecStrstrFunc)(const RwChar *string, const RwChar *findThis);
typedef int (*vecStrcmpFunc)(const RwChar *string1, const RwChar *string2);
typedef int (*vecStrncmpFunc)(const RwChar *string1, const RwChar *string2, size_t max_size);
typedef int (*vecStricmpFunc)(const RwChar *string1, const RwChar *string2);
typedef size_t (*vecStrlenFunc)(const RwChar *string);
typedef RwChar *(*vecStruprFunc)(RwChar *string);
typedef RwChar *(*vecStrlwrFunc)(RwChar *string);
typedef RwChar *(*vecStrtokFunc)(RwChar *string, const RwChar *delimit);
typedef int (*vecSscanfFunc)(const RwChar *buffer, const RwChar *format, ...);

typedef struct RwStringFunctions RwStringFunctions;
struct RwStringFunctions
{
    vecSprintfFunc vecSprintf;
    vecVsprintfFunc vecVsprintf;
    vecStrcpyFunc vecStrcpy;
    vecStrncpyFunc vecStrncpy;
    vecStrcatFunc vecStrcat;
    vecStrncatFunc vecStrncat;
    vecStrrchrFunc vecStrrchr;
    vecStrchrFunc vecStrchr;
    vecStrstrFunc vecStrstr;
    vecStrcmpFunc vecStrcmp;
    vecStrncmpFunc vecStrncmp;
    vecStricmpFunc vecStricmp;
    vecStrlenFunc vecStrlen;
    vecStruprFunc vecStrupr;
    vecStrlwrFunc vecStrlwr;
    vecStrtokFunc vecStrtok;
    vecSscanfFunc vecSscanf;
};

/* The free lists' allocator and releaser (bamemory.h). */
typedef void *(*RwMemoryAllocFn)(RwFreeList *fl, RwUInt32 hint);
typedef RwFreeList *(*RwMemoryFreeFn)(RwFreeList *fl, void *pData);

/* RwGlobals up to memoryFree (a release build: no debug fields). */
typedef struct RwGlobals RwGlobals;
struct RwGlobals
{
    /* Current entities */
    void                *curCamera;             /* Current camera */
    void                *curWorld;              /* Current World */

    /* Checking counters */
    RwUInt16            renderFrame;            /* Camera display count */
    RwUInt16            lightFrame;             /* Used to ensure each light is applied only once. */
    RwUInt16            pad[2];                 /* Longword align it again */

    /* For the currently accessed device */
    RwDevice            dOpenDevice;

    /* Standard renderers and functions */
    RwStandardFunc      stdFunc[rwSTANDARDNUMOFSTANDARD];

    /* All of the frames which have been updated */
    RwLinkList          dirtyFrameList;

    /* RenderWare 3.6's file functions (RwOsGetFileInterface's block) */
    RwFileFunctions     fileFuncs;

    /* The string functions */
    RwStringFunctions   stringFuncs;

    /* The memory allocation functions */
    RwMemoryFunctions   memoryFuncs;

    /* virtual memory alloc/free functions */
    RwMemoryAllocFn     memoryAlloc;
    RwMemoryFreeFn      memoryFree;
};

// ourGlobals (RWGLOBALSIZE); see above.
#ifdef    __cplusplus
extern "C" RwUInt32 ourGlobals[];
#else
extern RwUInt32 ourGlobals[];
#endif
#define RwEngineInstance ourGlobals

#define RWSRCGLOBAL(variable) \
   (((RwGlobals *)RwEngineInstance)->variable)

/* RenderWare's string macros (rwstring.h) */
#define rwstrcpy(_dst, _src)    RWSRCGLOBAL(stringFuncs).vecStrcpy(_dst, _src)
#define rwstrcat(_dst, _src)    RWSRCGLOBAL(stringFuncs).vecStrcat(_dst, _src)
#define rwstrcmp(_s1, _s2)      RWSRCGLOBAL(stringFuncs).vecStrcmp(_s1, _s2)
#define rwstrlen(_str)          RWSRCGLOBAL(stringFuncs).vecStrlen(_str)

/* RenderWare's memory macros (rwplcore.h) */
#define RwMalloc(_s, _h)        ((RWSRCGLOBAL(memoryFuncs).rwmalloc)((_s), (_h)))
#define RwFree(_p)              ((RWSRCGLOBAL(memoryFuncs).rwfree)((_p)))
#define RwCalloc(_n, _s, _h)    ((RWSRCGLOBAL(memoryFuncs).rwcalloc)((_n), (_s), (_h)))
#define RwRealloc(_p, _s, _h)   ((RWSRCGLOBAL(memoryFuncs).rwrealloc)((_p), (_s), (_h)))
#define RwFreeListAlloc(_f, _h) ((RWSRCGLOBAL(memoryAlloc))((_f), (_h)))
#define RwFreeListFree(_f, _p)  ((RWSRCGLOBAL(memoryFree))((_f), (_p)))

#define RwRenderStateGet(_state, _value) \
        RWSRCGLOBAL(dOpenDevice).fpRenderStateGet(_state, _value)
#define RwRenderStateSet(_state, _value) \
        RWSRCGLOBAL(dOpenDevice).fpRenderStateSet(_state, _value)
#define RwIm2DRenderPrimitive(_primType, _vertices, _numVertices) \
        RWSRCGLOBAL(dOpenDevice).fpIm2DRenderPrimitive(_primType, _vertices, _numVertices)
#define RwIm2DRenderIndexedPrimitive(_primType, _vertices, _numVertices, _indices, _numIndices) \
        RWSRCGLOBAL(dOpenDevice).fpIm2DRenderIndexedPrimitive(_primType, _vertices, _numVertices, \
                                                              _indices, _numIndices)
#define RwIm2DGetNearScreenZ() \
        (RWSRCGLOBAL(dOpenDevice).zBufferNear)
#define RwIm2DGetFarScreenZ() \
        (RWSRCGLOBAL(dOpenDevice).zBufferFar)
#define RwCameraGetCurrentCamera() \
        ((RwCamera *)RWSRCGLOBAL(curCamera))

#endif
