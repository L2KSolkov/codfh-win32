// RenderWare Studio's memory handler (the game framework's
// framework/core/memoryhandler/memoryhandler.cpp) as the image's build has
// it (RWS_DISABLE_MEMORY_CHECKING): the base allocator, CMemHandler, the
// global operator new and delete and the RenderWare allocation functions.
// The game's base allocator serialises the CRT's allocation functions with a
// critical section and raises a flag while inside them (the asynchronous
// loader waits for it), and it adds the leak checks and the hook below.
// operator new[], delete[] and the typed delete are identical to the plain
// ones (folded, /OPT:ICF); BaseMemClose and GetRawHeaderSize are empty
// (folded, config/aliases.txt).

#ifdef CODFH_WIN32
#include <malloc.h>
#endif
#include <stdlib.h>

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "xbox/xboxkrnl.h"
#include "rws/memoryhandler.h"
#include "rws/cmemhandler.h"
#include "game/data.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004CF86C
struct _RTL_CRITICAL_SECTION unk_4CF86C;
// 0x004CF888
RwInt32 dword_4CF888;
// 0x004CF88C
bool byte_4CF88C;
// 0x004CF88D
bool byte_4CF88D;
// End of its data definitions.


void BaseMemClose(void);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?GetRef@CMemHandler@@SAAAV1@XZ>1>8 @ 0x0041D83C
// match: __ehhandler$?GetRef@CMemHandler@@SAAAV1@XZ>1 @ 0x0041D844

// match: ?BaseMemInit@@YAXXZ @ 0x0012ECF0
// sp-match: ?BaseMemInit@@YAXXZ @ 0x000E0C40

void BaseMemInit(void)
{
   if (!byte_4CF88D)
   {
      RtlInitializeCriticalSection(&unk_4CF86C);
      dword_4CF888 = 0;
      byte_4CF88D = true;
   }
}

// match: ?BaseMemAlloc@@YAPAXII@Z @ 0x0012ED20
// sp-match: ?BaseMemAlloc@@YAPAXII@Z @ 0x000E0C70
void *BaseMemAlloc(size_t size, RwUInt32 userTypeNum)
{
   dword_4CF888 = 1;
   RtlEnterCriticalSection(&unk_4CF86C);

#ifdef CODFH_WIN32
   // (Win32: 16-byte aligned blocks, as the Xbox's heap gives them; RenderWare's SSE matrix
   // and vector code loads them aligned)
   void *pMem = _aligned_malloc(size ? size : 1, 16);
#else
   void *pMem = malloc(size);
#endif

   RtlLeaveCriticalSection(&unk_4CF86C);
   dword_4CF888 = 0;

   return (pMem);
}

// match: ?BaseMemFree@@YAXPAX@Z @ 0x0012ED70
// sp-match: ?BaseMemFree@@YAXPAX@Z @ 0x000E0CB0
void BaseMemFree(void *pMem)
{
   dword_4CF888 = 1;
   RtlEnterCriticalSection(&unk_4CF86C);

#ifdef CODFH_WIN32
   _aligned_free(pMem);
#else
   free(pMem);
#endif

   RtlLeaveCriticalSection(&unk_4CF86C);
   dword_4CF888 = 0;
}

// match: ?BaseMemReAlloc@@YAPAXPAXII@Z @ 0x0012EDB0
// sp-match: ?BaseMemReAlloc@@YAPAXPAXII@Z @ 0x000E0CF0
void *BaseMemReAlloc(void *pMem, size_t size, RwUInt32 userTypeNum)
{
   dword_4CF888 = 1;
   RtlEnterCriticalSection(&unk_4CF86C);

#ifdef CODFH_WIN32
   void *pNewMem = _aligned_realloc(pMem, size, 16);
#else
   void *pNewMem = realloc(pMem, size);
#endif

   RtlLeaveCriticalSection(&unk_4CF86C);
   dword_4CF888 = 0;

   return (pNewMem);
}

// match: ?BaseMemCalloc@@YAPAXIII@Z @ 0x0012EE00
// sp-match: ?BaseMemCalloc@@YAPAXIII@Z @ 0x000E0D40
void *BaseMemCalloc(size_t num, size_t size, RwUInt32 userTypeNum)
{
   dword_4CF888 = 1;
   RtlEnterCriticalSection(&unk_4CF86C);

#ifdef CODFH_WIN32
   void *pMem = _aligned_recalloc(0, num ? num : 1, size ? size : 1, 16);
#else
   void *pMem = calloc(num, size);
#endif

   RtlLeaveCriticalSection(&unk_4CF86C);
   dword_4CF888 = 0;

   return (pMem);
}

// match: ??0CMemHandler@@AAE@XZ @ 0x0012EE50
// sp-match: ??0CMemHandler@@AAE@XZ @ 0x000E0D90
CMemHandler::CMemHandler(void) :
      m_doingMsg(false)
{
   BaseMemInit();
}

// match: ??1CMemHandler@@QAE@XZ @ 0x0012EE70
CMemHandler::~CMemHandler(void)
{
   BaseMemClose();
}

// The leak check for a region (the game's; its checks are compiled out).
#ifdef CODFH_SP
// Single player folds this empty check into another `return false` (SP
// 0xD5A00) and keeps the calls to it, so it is only declared here.
bool sub_12EE80(RwInt32 arg_0);
#else
// match: ?sub_12EE80@@YA_NH@Z @ 0x0012EE80
bool sub_12EE80(RwInt32 arg_0)
{
   bool leaked = false;

   return (leaked);
}
#endif

// The singleton (GetRef, inline in rws/cmemhandler.h, emitted here with its
// function-local static and the guard's unwind funclet).
// GetRef registers the local singleton's compiler-generated exit.
// match: ?memHandler@?1??GetRef@CMemHandler@@SAAAV1@XZ@$AV1@A @ 0x0030E680
// match: ?GetRef@CMemHandler@@SAAAV1@XZ @ 0x0012EE90
// match: __ehhandler$?GetRef@CMemHandler@@SAAAV1@XZ-0xE @ 0x003016F0
// match: __ehhandler$?GetRef@CMemHandler@@SAAAV1@XZ @ 0x003016FE
// sp-match: ?GetRef@CMemHandler@@SAAAV1@XZ @ 0x000E0E70
// sp-match: ?memHandler@?1??GetRef@CMemHandler@@SAAAV1@XZ@$AV1@A @ 0x0021EA30

// match: ?GetExtraSize@CMemHandler@@AAEIXZ @ 0x0012EF00
// sp-match: ?GetExtraSize@CMemHandler@@AAEIXZ @ 0x000E0EB0
RwUInt32 CMemHandler::GetExtraSize(void)
{
   RwUInt32 extraHeader = GetAlignedHeaderSize(),
         extraTrailer = 0;

   return(extraHeader + extraTrailer);
}

// The header the logging adds (none in this build). Folded (/OPT:ICF) into
// sub_19B650, which returns 0 the same way (config/aliases.txt).
RwUInt32 CMemHandler::GetRawHeaderSize(void)
{
   RwUInt32 headerSize = 0;

   return(headerSize);
}

// match: ?GetAlignedHeaderSize@CMemHandler@@CAIXZ @ 0x0012EF30
// sp-match: ?GetAlignedHeaderSize@CMemHandler@@CAIXZ @ 0x000E0E60
RwUInt32 CMemHandler::GetAlignedHeaderSize(void)
{
   RwUInt32 headerSize = GetRawHeaderSize();

   headerSize = (headerSize + (RWS_MEMORY_ALIGNMENT - 1)) & ~(RWS_MEMORY_ALIGNMENT - 1);

   return(headerSize);
}

// match: ?Alloc@CMemHandler@@SAPAXIW4mem_type@1@II@Z @ 0x0012EF50
// sp-match: ?Alloc@CMemHandler@@SAPAXIW4mem_type@1@II@Z @ 0x000E0EC0
void *CMemHandler::Alloc(size_t userSize, mem_type type, RwUInt32 hint, const RwUInt32 userTypeNum)
{
   void *pAllocMem,
         *pUserMem;

   // What is left of the Studio sources' logging block: a copy of the type
   // in a block of its own (ReAlloc and Calloc have one too).
   {
      mem_type allocType = type;
   }

   pAllocMem = BaseMemAlloc(userSize + GetRef().GetExtraSize(), userTypeNum);

   pUserMem = pAllocMem;

   return(pUserMem);
}

// match: ?ReAlloc@CMemHandler@@SAPAXPAXIW4mem_type@1@II@Z @ 0x0012EF90
// sp-match: ?ReAlloc@CMemHandler@@SAPAXPAXIW4mem_type@1@II@Z @ 0x000E0EE0
void *CMemHandler::ReAlloc(void *pUserMem, size_t userSize, mem_type type, RwUInt32 hint, RwUInt32 userTypeNum)
{
   void *pAllocMem,
         *pNewUser = 0,
         *pNewAlloc;

   if (userSize)
   {
      pAllocMem = pUserMem;

      mem_type allocType = type;

      pNewAlloc = BaseMemReAlloc(pAllocMem, userSize + GetRef().GetExtraSize(), userTypeNum);

      pNewUser = pNewAlloc;
   }
   else
   {
      pAllocMem = pUserMem;

      pNewUser = BaseMemReAlloc(pAllocMem, userSize, userTypeNum);
   }

   return(pNewUser);
}

// match: ?Calloc@CMemHandler@@SAPAXIIW4mem_type@1@II@Z @ 0x0012F000
// sp-match: ?Calloc@CMemHandler@@SAPAXIIW4mem_type@1@II@Z @ 0x000E0DA0
void *CMemHandler::Calloc(size_t num, size_t size, mem_type type, RwUInt32 hint, RwUInt32 userTypeNum)
{
   void *pAllocMem,
         *pUserMem;
   size_t allocSize;

   allocSize = size;

   {
      mem_type allocType = type;
   }

   pAllocMem = BaseMemCalloc(num, allocSize, userTypeNum);

   pUserMem = pAllocMem;

   return(pUserMem);
}

// match: ?Free@CMemHandler@@SAXPAX@Z @ 0x0012F040
// sp-match: ?Free@CMemHandler@@SAXPAX@Z @ 0x000E0DC0
void CMemHandler::Free(void *pUserMem)
{
   void *pAllocMem;

   pAllocMem = pUserMem;

   BaseMemFree(pAllocMem);
}

// Reports the leaks of region arg_0 (the game's).
// match: ?sub_12F060@@YAXH@Z @ 0x0012F060
// sp-match: ?sub_12F060@@YAXH@Z @ 0x000E0DD0
void sub_12F060(RwInt32 arg_0)
{
   sub_12EE80(arg_0);
}

// Whether region arg_0 leaked (the game's; always false in this build).
// match: ?sub_12F080@@YA_NH@Z @ 0x0012F080
// sp-match: ?sub_12F080@@YA_NH@Z @ 0x000D5A00
bool sub_12F080(RwInt32 arg_0)
{
   return false;
}

// Clears the hook's flag (the game loop's restart).
// match: ?sub_12F090@@YAXXZ @ 0x0012F090
// sp-match: ?sub_12F090@@YAXXZ @ 0x000E0DE0
void sub_12F090()
{
   byte_4CF88C = false;
}

// The game's hook in RenderWare Studio's entity messages: sets the flag
// while dword_4B8710 is set.
// match: ?sub_12F0A0@@YAXXZ @ 0x0012F0A0
// sp-match: ?sub_12F0A0@@YAXXZ @ 0x000E0DF0
void sub_12F0A0()
{
   if (dword_4B8710)
   {
      byte_4CF88C = true;
   }
}

// match: ??2@YAPAXI@Z @ 0x0012F0C0
// sp-match: ??2@YAPAXI@Z @ 0x000E0F30
void *operator new(size_t size)
{
   return(CMemHandler::Alloc(size, CMemHandler::MHMT_STD, rwMEMHINTDUR_GLOBAL, RWS::RWS_MEMORY_TYPE_STD));
}

// match: ??2@YAPAXII@Z @ 0x0012F0E0
// sp-match: ??2@YAPAXII@Z @ 0x000E0F50
void *operator new(size_t size, RwUInt32 userTypeNum)
{
   return(CMemHandler::Alloc(size, CMemHandler::MHMT_RWS, rwMEMHINTDUR_GLOBAL, userTypeNum));
}

// The database's AllocBuffer.
// match: ?RWSMalloc@@YAPAXII@Z @ 0x0012F100
// sp-match: ?RWSMalloc@@YAPAXII@Z @ 0x000E0F70
void *RWSMalloc(size_t size, RwUInt32 hint)
{
   void *pMem = CMemHandler::Alloc(size, CMemHandler::MHMT_RW, rwMEMHINTDUR_GLOBAL, RWS::RWS_MEMORY_TYPE_RW);

   return(pMem);
}

// match: ??3@YAXPAX@Z @ 0x0012F130
// sp-match: ??3@YAXPAX@Z @ 0x000E0E10
void operator delete(void *pMem)
{
   if (pMem)
   {
      CMemHandler::Free(pMem);
   }
}

// match: ?RWSReAlloc@@YAPAXPAXII@Z @ 0x0012F150
// sp-match: ?RWSReAlloc@@YAPAXPAXII@Z @ 0x000E0F90
void *RWSReAlloc(void *pMem, size_t newSize, RwUInt32 hint)
{
   return(CMemHandler::ReAlloc(pMem, newSize, CMemHandler::MHMT_RW, rwMEMHINTDUR_GLOBAL, RWS::RWS_MEMORY_TYPE_RW));
}

// match: ?RWSCalloc@@YAPAXIII@Z @ 0x0012F170
// sp-match: ?RWSCalloc@@YAPAXIII@Z @ 0x000E0E40
void *RWSCalloc(size_t num, size_t size, RwUInt32 hint)
{
   return(CMemHandler::Calloc(num, size, CMemHandler::MHMT_RW, rwMEMHINTDUR_GLOBAL, RWS::RWS_MEMORY_TYPE_RW));
}

// match: ?RWSFree@@YAXPAX@Z @ 0x0012F190
void RWSFree(void *pMem)
{
   CMemHandler::Free(pMem);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?BaseMemClose@@YAXXZ (folded into 0x19A750)
void BaseMemClose()
{
}

// The typed delete RenderWare Studio defines with RWS_DISABLE_MEMORY_CHECKING
// (the match of operator new's typed form; the XDK's stand-ins and the
// weapon copies' factory unwind through it).
// ??3@YAXPAXI@Z (folded into 0x12F130)
// (single player keeps it apart: its plain delete tail-jumps, SP 0xE0E10)
// sp-match: ??3@YAXPAXI@Z @ 0x000E0E30
void operator delete(void *pMem, RwUInt32 type)
{
   if (pMem)
   {
      CMemHandler::Free(pMem);
   }
}

// ??_U@YAPAXI@Z (folded into 0x12F0C0)
void *operator new[](size_t size)
{
   return(CMemHandler::Alloc(size, CMemHandler::MHMT_STD, rwMEMHINTDUR_GLOBAL, RWS::RWS_MEMORY_TYPE_STD));
}

// ??_V@YAXPAX@Z (folded into 0x12F130)
void operator delete[](void *pMem)
{
   if (pMem)
   {
      CMemHandler::Free(pMem);
   }
}
