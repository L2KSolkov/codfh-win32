/*
 * CMemHandler, copied from RenderWare Studio's game framework
 * (framework/core/memoryhandler/memoryhandler.cpp, which defines it in the
 * source), as the image's build has it: RWS_DISABLE_MEMORY_CHECKING, with no
 * logging, leak checks or metrics, so the handler only adds its (empty)
 * header's aligned size to each allocation. Its one data member is the
 * report flag (the singleton, 0x4CF88E, is one byte). The image's memory
 * types start at 1 (operator new passes 1 for the standard allocations,
 * RWSMalloc 3 for RenderWare's).
 * Only memoryhandler.cpp includes this.
 */
#ifndef RWS_CMEMHANDLER_H
#define RWS_CMEMHANDLER_H

#include <stddef.h>

#include "rw/ostypes.h"

class CMemHandler
{
public:
   enum mem_type
   {
      MHMT_STD = 1,
      MHMT_RWS,
      MHMT_RW,
      MHMT_TOTAL
   };

   static CMemHandler &GetRef(void)
   {
      static CMemHandler memHandler;

      return(memHandler);
   }

   ~CMemHandler(void);

   static void *Alloc(size_t userSize, mem_type type, RwUInt32 hint, const RwUInt32 userTypeNum);
   static void *ReAlloc(void *pUserMem, size_t userSize, mem_type type, RwUInt32 hint, RwUInt32 userTypeNum);
   static void *Calloc(size_t num, size_t size, mem_type type, RwUInt32 hint, RwUInt32 userTypeNum);
   static void Free(void *pUserMem);

private:
   CMemHandler(void);
   CMemHandler(const CMemHandler &rhs);
   CMemHandler& operator =(const CMemHandler &rhs);

   RwUInt32 GetExtraSize(void);
   static RwUInt32 GetAlignedHeaderSize(void);
   static RwUInt32 GetRawHeaderSize(void);

   bool m_doingMsg;
};

#endif
