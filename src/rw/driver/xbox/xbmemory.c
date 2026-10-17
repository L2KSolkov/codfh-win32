/*
 * codfh-match: RenderWare 3.6's Xbox driver memory (driver/xbox/xbmemory.c):
 * the physical memory manager (blocks from XPhysicalAlloc handed out with a
 * header before each allocation) and the dynamic vertex buffers. Written from
 * the image; the structure, names and types are those of the Godfather debug
 * build's copy of the same file (RenderWare 3.7), without its debug counters.
 */

#include <xtl.h>

#include "batypes.h"
#include "balibtyp.h"
#include "bamemory.h"
#include "badebug.h"

#include "xbmemory.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/driver/xbox/xbmemory.c#1 $";

/* A block of physical memory, free or created. */
typedef struct _rwXboxMemoryBlockEntry _rwXboxMemoryBlockEntry;
struct _rwXboxMemoryBlockEntry
{
    RwUInt32                    address;
    RwUInt32                    size;
    _rwXboxMemoryBlockEntry    *next;
    _rwXboxMemoryBlockEntry    *prev;
};

/* The header before each allocation. */
typedef struct XbBlockHeader XbBlockHeader;
struct XbBlockHeader
{
    RwUInt32                    unaligned;
    RwUInt32                    size;
};

/* A dynamic vertex buffer. */
typedef struct XbAllocatedVB XbAllocatedVB;
struct XbAllocatedVB
{
    D3DVertexBuffer            *vertexBuffer;
    RwUInt32                    size;
    XbAllocatedVB              *next;
    XbAllocatedVB              *prev;
};

/* The size of the blocks created. */
static RwUInt32 Granularity = 256 * 1024;

static RwInt32 FreeBlockFreeListEntriesPerBlock = 256;
static RwUInt32 FreeBlockFreeListNumBlocksToPrealloc = 1;
static RwInt32 CreatedBlockFreeListEntriesPerBlock = 128;
static RwUInt32 CreatedBlockFreeListNumBlocksToPrealloc = 1;
static RwInt32 VertexBufferHeaderFreeListEntriesPerBlock = 341;
static RwUInt32 VertexBufferHeaderFreeListNumBlocksToPrealloc = 1;
static RwInt32 AllocatedVertexBufferFreeListEntriesPerBlock = 256;
static RwUInt32 AllocatedVertexBufferFreeListNumBlocksToPrealloc = 1;

static RwFreeList VertexBufferHeaderFreeList;
static RwFreeList AllocatedVertexBufferFreeList;
static RwFreeList CreatedBlockFreeList;
static RwFreeList FreeBlockFreeList;

_rwXboxMemoryBlockEntry *_rwXboxMemoryBlockFreelist = NULL;
_rwXboxMemoryBlockEntry *_rwXboxMemoryBlocklist = NULL;

static XbAllocatedVB *AllocatedVertexBuffers = NULL;
static D3DVertexBuffer *CurrentVertexBuffer = NULL;

static RwUInt32 XbDynamicVertexBufferDiscardMemory(RwUInt32 size, RwBool releaseBusyVB);
static void XbDynamicVertexBufferClose(void);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x004166A0
// match: ??_C@_0CC@BABPDLDD@Failed?5to?5create?5a?5vertex?5buffer@ @ 0x004166E8
// match: _Granularity @ 0x004355F4
// match: _FreeBlockFreeListEntriesPerBlock @ 0x004355F8
// match: _FreeBlockFreeListNumBlocksToPrealloc @ 0x004355FC
// match: _CreatedBlockFreeListEntriesPerBlock @ 0x00435600
// match: _CreatedBlockFreeListNumBlocksToPrealloc @ 0x00435604
// match: _VertexBufferHeaderFreeListEntriesPerBlock @ 0x00435608
// match: _VertexBufferHeaderFreeListNumBlocksToPrealloc @ 0x0043560C
// match: _AllocatedVertexBufferFreeListEntriesPerBlock @ 0x00435610
// match: _AllocatedVertexBufferFreeListNumBlocksToPrealloc @ 0x00435614

// match: __rwXbMemoryManagerOpen @ 0x002AD980
// sp-match: __rwXbMemoryManagerOpen @ 0x001CB140

RwBool
_rwXbMemoryManagerOpen(void)
{
    RwFreeListCreateAndPreallocateSpace(sizeof(_rwXboxMemoryBlockEntry),
                                        FreeBlockFreeListEntriesPerBlock, 4,
                                        FreeBlockFreeListNumBlocksToPrealloc,
                                        &FreeBlockFreeList,
                                        rwID_DRIVERMODULE | rwMEMHINTDUR_GLOBAL);

    RwFreeListCreateAndPreallocateSpace(sizeof(_rwXboxMemoryBlockEntry),
                                        CreatedBlockFreeListEntriesPerBlock, 4,
                                        CreatedBlockFreeListNumBlocksToPrealloc,
                                        &CreatedBlockFreeList,
                                        rwID_DRIVERMODULE | rwMEMHINTDUR_GLOBAL);

    RwFreeListCreateAndPreallocateSpace(sizeof(D3DVertexBuffer),
                                        VertexBufferHeaderFreeListEntriesPerBlock, 4,
                                        VertexBufferHeaderFreeListNumBlocksToPrealloc,
                                        &VertexBufferHeaderFreeList,
                                        rwID_DRIVERMODULE | rwMEMHINTDUR_GLOBAL);

    RwFreeListCreateAndPreallocateSpace(sizeof(XbAllocatedVB),
                                        AllocatedVertexBufferFreeListEntriesPerBlock, 4,
                                        AllocatedVertexBufferFreeListNumBlocksToPrealloc,
                                        &AllocatedVertexBufferFreeList,
                                        rwID_DRIVERMODULE | rwMEMHINTDUR_GLOBAL);

    return TRUE;
}

// match: __rwXbMemoryPhysicalFree @ 0x002ADA10
// sp-match: __rwXbMemoryPhysicalFree @ 0x001CB1D0
void
_rwXbMemoryPhysicalFree(void *memIn)
{
    RwUInt32                    mem = (RwUInt32)memIn;
    _rwXboxMemoryBlockEntry    *freelist;
    XbBlockHeader              *block;
    RwUInt32                    address;
    RwUInt32                    size;
    RwUInt32                    addressEnd;
    RwBool                      addEnd = FALSE;

    block = ((XbBlockHeader *)(mem | 0x80000000)) - 1;

    address = block->unaligned;
    size = block->size;
    addressEnd = size + address;

    /* Is there a free block just before or after this one? */
    for (freelist = _rwXboxMemoryBlockFreelist; freelist != NULL; freelist = freelist->next)
    {
        if (freelist->size + freelist->address == address)
        {
            addEnd = TRUE;
            break;
        }

        if (addressEnd == freelist->address)
        {
            addEnd = FALSE;
            break;
        }
    }

    if (freelist != NULL)
    {
        RwUInt32        newAdress = address;
        RwUInt32        newSize = size;
        RwBool          canCompactMore;

        do
        {
            _rwXboxMemoryBlockEntry *blocklist;

            if (addEnd)
            {
                freelist->size += newSize;
            }
            else
            {
                freelist->address = newAdress;
                freelist->size += newSize;
            }

            /* The biggest free block goes first */
            if (_rwXboxMemoryBlockFreelist != freelist &&
                _rwXboxMemoryBlockFreelist->size < freelist->size)
            {
                if (freelist->prev != NULL)
                {
                    freelist->prev->next = freelist->next;
                }

                if (freelist->next != NULL)
                {
                    freelist->next->prev = freelist->prev;
                }

                freelist->next = _rwXboxMemoryBlockFreelist;
                freelist->prev = NULL;
                _rwXboxMemoryBlockFreelist->prev = freelist;
                _rwXboxMemoryBlockFreelist = freelist;
            }

            canCompactMore = FALSE;

            /* Give back whole created blocks the free block covers */
            do
            {
                blocklist = _rwXboxMemoryBlocklist;
                while (blocklist != NULL &&
                       (blocklist->size > freelist->size ||
                        (blocklist->address != freelist->address &&
                         blocklist->size + blocklist->address != freelist->size + freelist->address)))
                {
                    blocklist = blocklist->next;
                }

                if (blocklist == NULL)
                {
                    break;
                }

                if (blocklist->address == freelist->address && blocklist->size == freelist->size)
                {
                    if (freelist->prev != NULL)
                    {
                        freelist->prev->next = freelist->next;
                    }

                    if (freelist->next != NULL)
                    {
                        freelist->next->prev = freelist->prev;
                    }

                    if (_rwXboxMemoryBlockFreelist == freelist)
                    {
                        _rwXboxMemoryBlockFreelist = freelist->next;
                    }

                    RwFreeListFree(&FreeBlockFreeList, freelist);
                    freelist = NULL;
                }
                else if (blocklist->address == freelist->address && blocklist->size < freelist->size)
                {
                    freelist->address += blocklist->size;
                    freelist->size -= blocklist->size;
                }
                else if (blocklist->size + blocklist->address == freelist->size + freelist->address)
                {
                    freelist->size -= blocklist->size;
                }

                XPhysicalFree((LPVOID)(blocklist->address | 0x80000000));

                if (blocklist->prev != NULL)
                {
                    blocklist->prev->next = blocklist->next;
                }

                if (blocklist->next != NULL)
                {
                    blocklist->next->prev = blocklist->prev;
                }

                if (_rwXboxMemoryBlocklist == blocklist)
                {
                    _rwXboxMemoryBlocklist = blocklist->next;
                }

                RwFreeListFree(&CreatedBlockFreeList, blocklist);
            }
            while (freelist != NULL);

            /* Can the free block join another one? */
            if (freelist != NULL)
            {
                _rwXboxMemoryBlockEntry *oldFreelist;

                newAdress = freelist->address;
                newSize = freelist->size;
                addressEnd = newSize + newAdress;

                oldFreelist = freelist;

                for (freelist = _rwXboxMemoryBlockFreelist; freelist != NULL; freelist = freelist->next)
                {
                    if (freelist->size + freelist->address == newAdress)
                    {
                        canCompactMore = TRUE;
                        addEnd = TRUE;
                        break;
                    }

                    if (addressEnd == freelist->address)
                    {
                        canCompactMore = TRUE;
                        addEnd = FALSE;
                        break;
                    }
                }

                if (canCompactMore)
                {
                    if (oldFreelist->prev != NULL)
                    {
                        oldFreelist->prev->next = oldFreelist->next;
                    }

                    if (oldFreelist->next != NULL)
                    {
                        oldFreelist->next->prev = oldFreelist->prev;
                    }

                    if (_rwXboxMemoryBlockFreelist == oldFreelist)
                    {
                        _rwXboxMemoryBlockFreelist = oldFreelist->next;
                    }

                    RwFreeListFree(&FreeBlockFreeList, oldFreelist);
                }
            }
        }
        while (canCompactMore);
    }
    else
    {
        freelist = (_rwXboxMemoryBlockEntry *)RwFreeListAlloc(&FreeBlockFreeList,
                                                              rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

        freelist->address = address;
        freelist->size = size;

        if (_rwXboxMemoryBlockFreelist != NULL && _rwXboxMemoryBlockFreelist->size >= size)
        {
            freelist->next = _rwXboxMemoryBlockFreelist->next;
            freelist->prev = _rwXboxMemoryBlockFreelist;
            _rwXboxMemoryBlockFreelist->next = freelist;

            if (freelist->next != NULL)
            {
                freelist->next->prev = freelist;
            }
        }
        else
        {
            freelist->next = _rwXboxMemoryBlockFreelist;
            freelist->prev = NULL;

            if (_rwXboxMemoryBlockFreelist != NULL)
            {
                _rwXboxMemoryBlockFreelist->prev = freelist;
            }

            _rwXboxMemoryBlockFreelist = freelist;
        }
    }
}

// match: _RwXbReleaseVertexBuffer @ 0x002ADCA0
// sp-match: _RwXbReleaseVertexBuffer @ 0x001CB460
void
RwXbReleaseVertexBuffer(D3DVertexBuffer *vertexBuffer)
{
    if (vertexBuffer->Common & D3DCOMMON_D3DCREATED)
    {
        D3DResource_Release((D3DResource *)vertexBuffer);
    }
    else
    {
        if (vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK)
        {
            D3DDevice_SetStreamSource(0, NULL, 0);

            if (vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK)
            {
                D3DDevice_SetStreamSource(1, NULL, 0);
            }
        }

        D3DResource_BlockUntilNotBusy((D3DResource *)vertexBuffer);
        _rwXbMemoryPhysicalFree((void *)vertexBuffer->Data);
        RwFreeListFree(&VertexBufferHeaderFreeList, vertexBuffer);
    }
}

// match: _XbDynamicVertexBufferClose @ 0x002ADD00
// sp-match: _XbDynamicVertexBufferClose @ 0x001CB4C0
static void
XbDynamicVertexBufferClose(void)
{
    while (AllocatedVertexBuffers != NULL)
    {
        XbAllocatedVB  *next = AllocatedVertexBuffers->next;

        RwXbReleaseVertexBuffer(AllocatedVertexBuffers->vertexBuffer);
        RwFreeListFree(&AllocatedVertexBufferFreeList, AllocatedVertexBuffers);

        AllocatedVertexBuffers = next;
    }

    RwFreeListDestroy(&AllocatedVertexBufferFreeList);

    CurrentVertexBuffer = NULL;
}

/* Releases idle dynamic vertex buffers (all, if releaseBusyVB) until size
   bytes are released. */
// match: _XbDynamicVertexBufferDiscardMemory @ 0x002ADDB0
// sp-match: _XbDynamicVertexBufferDiscardMemory @ 0x001CB570
static RwUInt32
XbDynamicVertexBufferDiscardMemory(RwUInt32 size, RwBool releaseBusyVB)
{
    RwUInt32        releasedMemory = 0;

    if (AllocatedVertexBuffers)
    {
        XbAllocatedVB  *currentVb = AllocatedVertexBuffers;
        XbAllocatedVB  *next;

        do
        {
            D3DVertexBuffer *vertexBuffer;

            next = currentVb->next;
            vertexBuffer = currentVb->vertexBuffer;

            if (!(vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK) &&
                (!vertexBuffer->Lock || !D3DDevice_IsFencePending(vertexBuffer->Lock)))
            {
                if (CurrentVertexBuffer == vertexBuffer)
                {
                    CurrentVertexBuffer = NULL;
                }

                RwXbReleaseVertexBuffer(vertexBuffer);

                if (currentVb->next)
                {
                    currentVb->next->prev = currentVb->prev;
                }

                if (currentVb->prev)
                {
                    currentVb->prev->next = currentVb->next;
                }

                if (AllocatedVertexBuffers == currentVb)
                {
                    AllocatedVertexBuffers = currentVb->next;
                }

                releasedMemory += currentVb->size;

                RwFreeListFree(&AllocatedVertexBufferFreeList, currentVb);

                if (releasedMemory >= size)
                {
                    return releasedMemory;
                }
            }

            currentVb = next;
        }
        while (next);

        if (releaseBusyVB)
        {
            currentVb = AllocatedVertexBuffers;

            while (currentVb)
            {
                next = currentVb->next;

                if (CurrentVertexBuffer == currentVb->vertexBuffer)
                {
                    CurrentVertexBuffer = NULL;
                }

                RwXbReleaseVertexBuffer(currentVb->vertexBuffer);

                if (currentVb->next)
                {
                    currentVb->next->prev = currentVb->prev;
                }

                if (currentVb->prev)
                {
                    currentVb->prev->next = currentVb->next;
                }

                if (AllocatedVertexBuffers == currentVb)
                {
                    AllocatedVertexBuffers = currentVb->next;
                }

                releasedMemory += currentVb->size;

                RwFreeListFree(&AllocatedVertexBufferFreeList, currentVb);

                if (releasedMemory >= size)
                {
                    return releasedMemory;
                }

                currentVb = next;
            }
        }
    }

    return releasedMemory;
}

// match: _XbDynamicVertexBufferAdd @ 0x002ADEE0
// sp-match: _XbDynamicVertexBufferAdd @ 0x001CB6A0
static void
XbDynamicVertexBufferAdd(D3DVertexBuffer *vertexBuffer, RwUInt32 size)
{
    XbAllocatedVB  *currentVb;
    XbAllocatedVB  *lastVb;

    currentVb = (XbAllocatedVB *)RwFreeListAlloc(&AllocatedVertexBufferFreeList,
                                                 rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

    currentVb->vertexBuffer = vertexBuffer;
    currentVb->size = size;

    /* Append */
    lastVb = AllocatedVertexBuffers;
    while (lastVb != NULL && lastVb->next != NULL)
    {
        lastVb = lastVb->next;
    }

    currentVb->next = NULL;
    currentVb->prev = lastVb;

    if (lastVb != NULL)
    {
        lastVb->next = currentVb;
    }

    if (AllocatedVertexBuffers == NULL)
    {
        AllocatedVertexBuffers = currentVb;
    }
}

// match: _RwXboxSetCurrentStream @ 0x002ADF40
// sp-match: _RwXboxSetCurrentStream @ 0x001CB700
void
RwXboxSetCurrentStream(RwUInt32 stride)
{
    D3DDevice_SetStreamSource(0, CurrentVertexBuffer, stride);
}

// match: _RwXboxGetCurrentVertexBuffer @ 0x002ADF60
// sp-match: _RwXboxGetCurrentVertexBuffer @ 0x001CB720
D3DVertexBuffer *
RwXboxGetCurrentVertexBuffer(void)
{
    return CurrentVertexBuffer;
}

// match: __rwXbMemoryManagerClose @ 0x002ADF70
// sp-match: __rwXbMemoryManagerClose @ 0x001CB730
void
_rwXbMemoryManagerClose(void)
{
    XbDynamicVertexBufferClose();

    while (_rwXboxMemoryBlockFreelist)
    {
        _rwXboxMemoryBlockEntry *nextFreelist = _rwXboxMemoryBlockFreelist->next;

        RwFreeListFree(&FreeBlockFreeList, _rwXboxMemoryBlockFreelist);

        _rwXboxMemoryBlockFreelist = nextFreelist;
    }

    while (_rwXboxMemoryBlocklist)
    {
        _rwXboxMemoryBlockEntry *nextblocklist = _rwXboxMemoryBlocklist->next;

        if (_rwXboxMemoryBlocklist->address)
        {
            XPhysicalFree((LPVOID)(_rwXboxMemoryBlocklist->address | 0x80000000));
        }

        RwFreeListFree(&CreatedBlockFreeList, _rwXboxMemoryBlocklist);

        _rwXboxMemoryBlocklist = nextblocklist;
    }

    RwFreeListDestroy(&CreatedBlockFreeList);
    RwFreeListDestroy(&FreeBlockFreeList);
    RwFreeListDestroy(&VertexBufferHeaderFreeList);
}

// match: __rwXbMemoryPhysicalAlloc @ 0x002AE000
// sp-match: __rwXbMemoryPhysicalAlloc @ 0x001CB7C0
void *
_rwXbMemoryPhysicalAlloc(RwUInt32 size, RwUInt32 alignment)
{
    _rwXboxMemoryBlockEntry *freelist;
    RwUInt32        alignmentMask;
    RwUInt32        aligned;
    XbBlockHeader  *block;

    alignmentMask = alignment - 1;

    XbDynamicVertexBufferDiscardMemory(size, FALSE);

    /* The first free block it fits in */
    for (freelist = _rwXboxMemoryBlockFreelist; freelist; freelist = freelist->next)
    {
        if (freelist->size > size)
        {
            aligned = (alignmentMask + freelist->address + sizeof(XbBlockHeader)) & ~alignmentMask;

            if (freelist->size + freelist->address >= size + aligned)
            {
                break;
            }
        }
    }

    if (!freelist)
    {
        _rwXboxMemoryBlockEntry *blocklist;
        RwBool          purgeDone = FALSE;
        RwBool          failIfNull = FALSE;

        /* Create a new block */
        freelist = (_rwXboxMemoryBlockEntry *)RwFreeListAlloc(&FreeBlockFreeList,
                                                              rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

        freelist->size = Granularity;

        while (1)
        {
            if (freelist->size < size + alignmentMask + sizeof(XbBlockHeader))
            {
                freelist->size = (size + alignmentMask + sizeof(XbBlockHeader) + 4095) & ~4095;
                failIfNull = TRUE;
            }

            freelist->address = (RwUInt32)XPhysicalAlloc(freelist->size, MAXULONG_PTR, 0,
                                                         PAGE_READWRITE | PAGE_WRITECOMBINE) &
                                0x7FFFFFFF;
            if (freelist->address)
            {
                break;
            }

            if (!purgeDone)
            {
                XbDynamicVertexBufferDiscardMemory(freelist->size, TRUE);
                RwFreeListPurgeAllFreeLists();
                purgeDone = TRUE;
            }
            else
            {
                if (failIfNull)
                {
                    break;
                }

                freelist->size >>= 1;
            }
        }

        if (!freelist->address)
        {
            RwFreeListFree(&FreeBlockFreeList, freelist);
            return NULL;
        }

        freelist->next = _rwXboxMemoryBlockFreelist;
        freelist->prev = NULL;

        if (_rwXboxMemoryBlockFreelist)
        {
            _rwXboxMemoryBlockFreelist->prev = freelist;
        }

        _rwXboxMemoryBlockFreelist = freelist;

        blocklist = (_rwXboxMemoryBlockEntry *)RwFreeListAlloc(&CreatedBlockFreeList,
                                                               rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

        blocklist->address = freelist->address;
        blocklist->size = freelist->size;
        blocklist->next = _rwXboxMemoryBlocklist;
        blocklist->prev = NULL;

        if (_rwXboxMemoryBlocklist)
        {
            _rwXboxMemoryBlocklist->prev = blocklist;
        }

        _rwXboxMemoryBlocklist = blocklist;

        aligned = (alignmentMask + freelist->address + sizeof(XbBlockHeader)) & ~alignmentMask;
    }

    block = (XbBlockHeader *)((aligned - sizeof(XbBlockHeader)) | 0x80000000);

    if (aligned - sizeof(XbBlockHeader) - freelist->address > 256)
    {
        _rwXboxMemoryBlockEntry *newfreelist;
        _rwXboxMemoryBlockEntry *lastfreelist;

        /* Keep the space before the header free */
        newfreelist = (_rwXboxMemoryBlockEntry *)RwFreeListAlloc(&FreeBlockFreeList,
                                                                 rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

        newfreelist->address = freelist->address;
        newfreelist->size = aligned - sizeof(XbBlockHeader) - freelist->address;

        lastfreelist = freelist;
        while (lastfreelist->next && lastfreelist->next->size > newfreelist->size)
        {
            lastfreelist = lastfreelist->next;
        }

        newfreelist->next = lastfreelist->next;

        if (newfreelist->next)
        {
            newfreelist->next->prev = newfreelist;
        }

        newfreelist->prev = lastfreelist;
        lastfreelist->next = newfreelist;

        block->unaligned = aligned - sizeof(XbBlockHeader);
        block->size = size + sizeof(XbBlockHeader);
    }
    else
    {
        block->unaligned = freelist->address;
        block->size = size + aligned - freelist->address;
    }

    if (freelist->size + freelist->address > size + aligned)
    {
        freelist->size = freelist->size + freelist->address - (size + aligned);
        freelist->address = size + aligned;

        if (_rwXboxMemoryBlockFreelist != freelist &&
            _rwXboxMemoryBlockFreelist->size < freelist->size)
        {
            if (freelist->prev)
            {
                freelist->prev->next = freelist->next;
            }

            if (freelist->next)
            {
                freelist->next->prev = freelist->prev;
            }

            freelist->next = _rwXboxMemoryBlockFreelist;
            freelist->prev = NULL;
            _rwXboxMemoryBlockFreelist->prev = freelist;
            _rwXboxMemoryBlockFreelist = freelist;
        }
    }
    else
    {
        freelist->size = 0;

        if (freelist->prev)
        {
            freelist->prev->next = freelist->next;
        }

        if (freelist->next)
        {
            freelist->next->prev = freelist->prev;
        }

        if (_rwXboxMemoryBlockFreelist == freelist)
        {
            _rwXboxMemoryBlockFreelist = freelist->next;
        }

        RwFreeListFree(&FreeBlockFreeList, freelist);
    }

    return (void *)aligned;
}

// match: _RwXbCreateVertexBuffer @ 0x002AE2B0
// sp-match: _RwXbCreateVertexBuffer @ 0x001CBA70
D3DVertexBuffer *
RwXbCreateVertexBuffer(RwUInt32 size)
{
    D3DVertexBuffer *vertexBuffer;
    void           *mem;

    vertexBuffer = (D3DVertexBuffer *)RwFreeListAlloc(&VertexBufferHeaderFreeList,
                                                      rwID_DRIVERMODULE | rwMEMHINTDUR_EVENT);

    mem = _rwXbMemoryPhysicalAlloc((size + 31) & ~31, 1);

    vertexBuffer->Data = (DWORD)mem;
    vertexBuffer->Lock = 0;
    vertexBuffer->Common = 1 | D3DCOMMON_TYPE_VERTEXBUFFER;

    if (mem == NULL)
    {
        RwFreeListFree(&VertexBufferHeaderFreeList, vertexBuffer);

        RWERROR((E_RW_DEVICEERROR, RWSTRING("Failed to create a vertex buffer.")));
        return NULL;
    }

    return vertexBuffer;
}

// match: _RwXboxLockDynamicVertexBuffer @ 0x002AE330
// sp-match: _RwXboxLockDynamicVertexBuffer @ 0x001CBAF0
RwUInt8 *
RwXboxLockDynamicVertexBuffer(RwInt32 size)
{
    RwInt32         currentDist;
    D3DVertexBuffer *vertexBuffer;
    XbAllocatedVB  *next;
    XbAllocatedVB  *currentVb;
    XbAllocatedVB  *minDistVb;
    RwInt32         minDist;
    RwUInt8        *bufferMem;

    CurrentVertexBuffer = NULL;

    minDistVb = NULL;
    minDist = 0x7FFFFFFF;

    /* The idle buffer closest in size (but no more than twice the size) */
    for (currentVb = AllocatedVertexBuffers; currentVb != NULL; currentVb = next)
    {
        next = currentVb->next;
        vertexBuffer = currentVb->vertexBuffer;

        if (!(vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK) &&
            (vertexBuffer->Lock == 0 || !D3DDevice_IsFencePending(vertexBuffer->Lock)))
        {
            currentDist = currentVb->size - size;

            if (currentDist < 0 || currentDist >= size || currentDist >= minDist)
            {
                if (vertexBuffer->Common & D3DCOMMON_D3DCREATED)
                {
                    D3DResource_Release((D3DResource *)vertexBuffer);
                }
                else
                {
                    if (vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK)
                    {
                        D3DDevice_SetStreamSource(0, NULL, 0);

                        if (vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK)
                        {
                            D3DDevice_SetStreamSource(1, NULL, 0);
                        }
                    }

                    D3DResource_BlockUntilNotBusy((D3DResource *)vertexBuffer);
                    _rwXbMemoryPhysicalFree((void *)vertexBuffer->Data);
                    RwFreeListFree(&VertexBufferHeaderFreeList, vertexBuffer);
                }

                if (currentVb->next != NULL)
                {
                    currentVb->next->prev = currentVb->prev;
                }

                if (currentVb->prev != NULL)
                {
                    currentVb->prev->next = currentVb->next;
                }

                if (AllocatedVertexBuffers == currentVb)
                {
                    AllocatedVertexBuffers = currentVb->next;
                }

                RwFreeListFree(&AllocatedVertexBufferFreeList, currentVb);
            }
            else
            {
                if (minDistVb != NULL)
                {
                    RwXbReleaseVertexBuffer(minDistVb->vertexBuffer);

                    if (minDistVb->next != NULL)
                    {
                        minDistVb->next->prev = minDistVb->prev;
                    }

                    if (minDistVb->prev != NULL)
                    {
                        minDistVb->prev->next = minDistVb->next;
                    }

                    if (AllocatedVertexBuffers == minDistVb)
                    {
                        AllocatedVertexBuffers = minDistVb->next;
                    }

                    RwFreeListFree(&AllocatedVertexBufferFreeList, minDistVb);
                }

                minDistVb = currentVb;
                minDist = currentDist;

                if (currentDist <= 32)
                {
                    break;
                }
            }
        }
    }

    if (minDistVb == NULL)
    {
        do
        {
            CurrentVertexBuffer = RwXbCreateVertexBuffer(size);
        }
        while (CurrentVertexBuffer == NULL &&
               XbDynamicVertexBufferDiscardMemory(size, TRUE) > 0);

        if (CurrentVertexBuffer == NULL)
        {
            return NULL;
        }

        XbDynamicVertexBufferAdd(CurrentVertexBuffer, size);
    }
    else
    {
        CurrentVertexBuffer = minDistVb->vertexBuffer;
    }

    D3DVertexBuffer_Lock(CurrentVertexBuffer, 0, size, &bufferMem, 0);

    return bufferMem;
}

// match: _RwXbVertexBufferLockDiscard @ 0x002AE520
// sp-match: _RwXbVertexBufferLockDiscard @ 0x001CBCE0
RwUInt8 *
RwXbVertexBufferLockDiscard(D3DVertexBuffer *vertexBuffer, RwUInt32 size)
{
    D3DVertexBuffer *vertexBufferNew;
    RwUInt8        *bufferMem;

    vertexBufferNew = RwXbCreateVertexBuffer(size);
    if (vertexBufferNew != NULL)
    {
        D3DVertexBuffer vertexBufferBackUp;

        D3DVertexBuffer_Lock(vertexBufferNew, 0, size, &bufferMem, 0);

        if (vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK)
        {
            D3DDevice_SetStreamSource(0, NULL, 0);

            if (vertexBuffer->Common & D3DCOMMON_INTREFCOUNT_MASK)
            {
                D3DDevice_SetStreamSource(1, NULL, 0);
            }
        }

        /* Swap the headers: the new memory under the old header */
        vertexBufferBackUp = *vertexBuffer;
        *vertexBuffer = *vertexBufferNew;
        *vertexBufferNew = vertexBufferBackUp;

        XbDynamicVertexBufferAdd(vertexBufferNew, size);
    }
    else
    {
        D3DVertexBuffer_Lock(vertexBuffer, 0, size, &bufferMem, 0);
    }

    return bufferMem;
}

#ifdef CODFH_WIN32
/* The port's crash report (CODFH_WIN32 crash report, port/src/crashinfo.cpp, not in the image):
 * the driver's physical memory, its blocks created and their bytes, the free entries and their
 * bytes, the dynamic vertex buffers and their bytes, into out[0..5]; walked capped (the caller
 * guards the reads). */
void
_rwXbMemoryStats(RwUInt32 *out)
{
    const _rwXboxMemoryBlockEntry *e;
    const XbAllocatedVB *vb;
    RwInt32 guard;

    out[0] = out[1] = out[2] = out[3] = out[4] = out[5] = 0;
    for (e = _rwXboxMemoryBlocklist, guard = 0; e && guard < 100000; e = e->next, guard++)
        out[0]++, out[1] += e->size;
    for (e = _rwXboxMemoryBlockFreelist, guard = 0; e && guard < 100000; e = e->next, guard++)
        out[2]++, out[3] += e->size;
    for (vb = AllocatedVertexBuffers, guard = 0; vb && guard < 100000; vb = vb->next, guard++)
        out[4]++, out[5] += vb->size;
}
#endif
