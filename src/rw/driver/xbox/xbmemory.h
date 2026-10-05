/*
 * codfh-match: RenderWare 3.6's Xbox driver memory (driver/xbox/xbmemory.c),
 * written from the image.
 */
#ifndef XBMEMORY_H
#define XBMEMORY_H

extern RwBool _rwXbMemoryManagerOpen(void);
extern void _rwXbMemoryManagerClose(void);
extern void *_rwXbMemoryPhysicalAlloc(RwUInt32 size, RwUInt32 alignment);
extern void _rwXbMemoryPhysicalFree(void *address);

extern D3DVertexBuffer *RwXbCreateVertexBuffer(RwUInt32 size);
extern void RwXbReleaseVertexBuffer(D3DVertexBuffer *vertexBuffer);
extern RwUInt8 *RwXbVertexBufferLockDiscard(D3DVertexBuffer *vertexBuffer, RwUInt32 size);
extern RwUInt8 *RwXboxLockDynamicVertexBuffer(RwInt32 size);
extern void RwXboxSetCurrentStream(RwUInt32 stride);
extern D3DVertexBuffer *RwXboxGetCurrentVertexBuffer(void);

#endif /* XBMEMORY_H */
