/***************************************************************************
 *                                                                         *
 * Module  : balibtyp.h                                                    *
 *                                                                         *
 * Purpose : Macros/types only accessable from the library                 *
 *           This should be included directly after batypes.h in all       *
 *           modules which are part of the library (as opposed to the      *
 *           device.                                                       *
 *                                                                         *
 **************************************************************************/

#ifndef RWLIBTYP_H
#define RWLIBTYP_H

/****************************************************************************
 Includes
 */

#include "badebug.h"
#include "batkreg.h"
#include "badevice.h"
#include "bamemory.h"
#include "rwstring.h"
#include "drvmodel.h"

/****************************************************************************
 Macros
 */

/* RWPUBLIC */
/* Finding MSBs */

#define RWBYTEFINDMSB(a) \
   (_rwMsbBit[(a)]-1)

#define RWWORDFINDMSB(a) \
   (((a)&0xff00)?RWBYTEFINDMSB((a)>>8)+8: RWBYTEFINDMSB(a))

#define RWLONGFINDMSB(a) \
   (((a)&0xffff0000UL)?RWWORDFINDMSB((a)>>16)+16: RWWORDFINDMSB(a))

/****************************************************************************
 Defines
 */

/* macros used to access plugin data in objects */
#define RWPLUGINOFFSET(_type, _base, _offset)                   \
   ((_type *)((RwUInt8 *)(_base) + (_offset)))

#define RWPLUGINOFFSETCONST(_type, _base, _offset)              \
   ((const _type *)((const RwUInt8 *)(_base) + (_offset)))

/* macro used to access global data structure (the root type is RwGlobals) */
#define RWSRCGLOBAL(variable) \
   (((RwGlobals *)RwEngineInstance)->variable)

#define RWASSERTISTYPE(_f, _t) \
   RWASSERT((((const RwObject *)(_f))->type)==(_t))

/****************************************************************************
 Global Types
 */

enum RwEngineStatus
{
    rwENGINESTATUSIDLE = 0,                     /* This needs to be zero */
    rwENGINESTATUSINITED = 1,
    rwENGINESTATUSOPENED = 2,
    rwENGINESTATUSSTARTED = 3,
    rwENGINESTATUSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwEngineStatus RwEngineStatus;

/* codfh-match: RenderWare 3.6's file function table (RenderWare Studio's
 * framework sets rwfexist ... rwftell through RwOsGetFileInterface) */
typedef RwBool (*rwFnFexist)(const RwChar *name);
typedef void *(*rwFnFopen)(const RwChar *name, const RwChar *access);
typedef int (*rwFnFclose)(void *fptr);
typedef size_t (*rwFnFread)(void *addr, size_t size, size_t count, void *fptr);
typedef size_t (*rwFnFwrite)(const void *addr, size_t size, size_t count, void *fptr);
typedef RwChar *(*rwFnFgets)(RwChar *buffer, int maxLen, void *fptr);
typedef int (*rwFnFputs)(const RwChar *buffer, void *fptr);
typedef int (*rwFnFeof)(void *fptr);
typedef int (*rwFnFseek)(void *fptr, long offset, int origin);
typedef int (*rwFnFflush)(void *fptr);
typedef int (*rwFnFtell)(void *fptr);

typedef struct RwFileFunctions RwFileFunctions;
struct RwFileFunctions
{
    rwFnFexist  rwfexist;
    rwFnFopen   rwfopen;
    rwFnFclose  rwfclose;
    rwFnFread   rwfread;
    rwFnFwrite  rwfwrite;
    rwFnFgets   rwfgets;
    rwFnFputs   rwfputs;
    rwFnFeof    rwfeof;
    rwFnFseek   rwfseek;
    rwFnFflush  rwfflush;
    rwFnFtell   rwftell;
};

extern RwFileFunctions *RwOsGetFileInterface(void);

typedef struct RwGlobals RwGlobals;

#if (!defined(DOXYGEN))
struct RwGlobals
{
#ifdef RWDEBUG
        RwDebugHandler      debugFunction;          /* debug string handler */
        RwInt32             debugStackDepth;        /* current depth of function stack */
        RwBool              debugTrace;             /* is function tracing enabled */
//@{ 20050511 DDonSS : RWMESSAGE 출력여부 결정용
        RwBool				debugMessage;

//@} DDonSS
//@{ 20050513 DDonSS : Threadsafe 테스트용
        RwUInt32			debugMainThreadId;		// 메인 Thread의 Id
//@} DDonSS

#endif

		/* codfh-match: the drop's "Jaewon 20050603" debugLogFunc field is not in
		 * the image's RwGlobals (curCamera is its first word, at 0x5200E0). */

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
        /* codfh-match: RenderWare 3.6's file functions, which 3.7.2 dropped:
         * RwOsGetFileInterface (0x2AB6C0) returns 0x5201A4, and the game
         * and RenderWare Studio call through rwfopen, rwfclose, ... */
        RwFileFunctions     fileFuncs;
		
        /* The string functions */
        RwStringFunctions   stringFuncs;

        /* The memory allocation functions */
        RwMemoryFunctions   memoryFuncs;
#ifdef RWDEBUG
        RwBool              freeListExtraDebug;
#endif /* RWDEBUG */

        /* virtual memory alloc/free functions */
        RwMemoryAllocFn         memoryAlloc;
        RwMemoryFreeFn          memoryFree;

        RwMetrics           *metrics;

        /* Current engine status */
        RwEngineStatus      engineStatus;

        /* Resource arena init size. */
        RwUInt32            resArenaInitSize;


//@{ 2005414 DDonSS : Threadsafe
#if defined WIN32
#if ( defined USE_EXTERNAL_LOCK_FUNCTION ) || ( defined USE_EXTERNAL_LOCK_FUNCTION_WITH_FILEINFO )
		CsLockFunc			CsInitLock;
		CsLockFunc			CsLock;
		CsLockFunc			CsUnlock;
		CsLockFunc			CsDelLock;
#endif // ( defined USE_EXTERNAL_LOCK_FUNCTION ) || ( defined USE_EXTERNAL_LOCK_FUNCTION_WITH_FILEINFO )

#if defined USE_THREADSAFE_FRAME
		// Critical Section for dirtyFrameList
		CRITICAL_SECTION	csFrame;
#endif // defined USE_THREADSAFE_FRAME

#if defined USE_THREADSAFE_RESARENA
		// Critical Section for Resource Arena
		CRITICAL_SECTION	csResArena;
#endif // defined USE_THREADSAFE_RESARENA

#if defined USE_THREADSAFE_ATOMIC
		// Critical Section for Atomic Sync & remove
		CRITICAL_SECTION	csAtomic;
#endif // defined USE_THREADSAFE_ATOMIC

#if defined USE_THREADSAFE_GEOMETRY
		// Critical Section for global geometry access
		CRITICAL_SECTION	csGeometry;
#endif // defined USE_THREADSAFE_GEOMETRY


#else // defined WIN32

#if defined USE_THREADSAFE_FRAME
		void*				csFrame;
#endif // defined USE_THREADSAFE_FRAME

#if defined USE_THREADSAFE_RESARENA
		void*				csResArena;
#endif // defined USE_THREADSAFE_RESARENA

#endif // defined WIN32
//@} DDonSS

};

typedef struct RwModuleInfo RwModuleInfo;
struct RwModuleInfo
{
        RwInt32     globalsOffset;
        RwInt32     numInstances;
};
#endif /* (!defined(DOXYGEN)) */



/****************************************************************************
 Program wide globals
 */

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

#ifdef RWGLOBALSIZE
extern RwUInt32     ourGlobals[RWGLOBALSIZE / sizeof(RwUInt32)];
#define RwEngineInstance ourGlobals
#else /* RWGLOBALSIZE */

#ifdef _RWDLL
__declspec(dllimport) extern void         *RwEngineInstance;
#else
extern void         *RwEngineInstance;
#endif

#endif /* RWGLOBALSIZE */

#if defined(_RWDLL)
__declspec(dllimport) extern RwInt8 _rwMsbBit[];
#else /* defined(_RWDLL) */
extern RwInt8 _rwMsbBit[];
#endif /* defined(_RWDLL) */

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

/****************************************************************************
 Function prototypes
 */

#endif /* RWLIBTYP_H */
