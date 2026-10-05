/*
 * codfh-match: RenderWare 3.6's Xbox world pipeline instancing types
 * (world/pipe/p2/xbox/xbpipe.c); the Godfather PDB's layouts and names.
 */
#ifndef XBPIPE_H
#define XBPIPE_H

/* One instanced mesh. */
typedef struct RxXboxInstanceData RxXboxInstanceData;
struct RxXboxInstanceData
{
    RwUInt32            minVert;
    RwInt32             numVertices;
    RwInt32             numIndices;
    RwUInt16           *indexBuffer;
    RpMaterial         *material;
    DWORD               vertexShader;
};

/* The header following an instanced object's RwResEntry. */
typedef struct RxXboxResEntryHeader RxXboxResEntryHeader;
struct RxXboxResEntryHeader
{
    RwInt32             size;
    RwUInt16            serialNumber;
    RwUInt16            numMeshes;
    RwUInt32            primType;
    RwInt32             numVertices;
    RwInt32             stride;
    void               *vertexBuffer;
    RwBool              vertexAlpha;
    RxXboxInstanceData *begin;
    RxXboxInstanceData *end;
};

typedef RwBool (*RxXboxAllInOneInstanceCallBack)(void *object,
                                                RxXboxResEntryHeader *resEntryHeader,
                                                RwBool reinstance);

typedef RwBool (*_rxXboxAllInOneReinstanceCallBack)(void *object,
                                                  RxXboxResEntryHeader *resEntryHeader);

typedef void (*RxXboxAllInOneLightingCallBack)(void *object);

typedef void (*RxXboxAllInOneRenderCallBack)(RxXboxResEntryHeader *resEntryHeader,
                                             void *object, RwUInt8 type, RwUInt32 flags);

/* An all-in-one node's private data. */
typedef struct _rxXboxInstanceNodeData _rxXboxInstanceNodeData;
struct _rxXboxInstanceNodeData
{
    RxXboxAllInOneInstanceCallBack      instanceCallback;
    _rxXboxAllInOneReinstanceCallBack   reinstanceCallback;
    RxXboxAllInOneLightingCallBack      lightingCallback;
    RxXboxAllInOneRenderCallBack        renderCallback;
};

extern const D3DPRIMITIVETYPE RwXboxPrimConvTable[7];

extern void XBMeshGetNumVerticesMinIndex(const RwUInt16 *indices, RwUInt32 numIndices,
                                         RwInt32 *numVertices, RwUInt32 *min);
extern void _rwXBResourceEntryInstanceDataDestroy(RwResEntry *repEntry);
extern RwResEntry *_rxXBInstance(void *object, void *owner, RwResEntry **resEntryPointer,
                                 RpMeshHeader *meshHeader, RwInt32 numVertices,
                                 RxXboxAllInOneInstanceCallBack instanceCallback,
                                 RwBool allocateNative);
extern void _rxXbDefaultRenderCallback(RxXboxResEntryHeader *resEntryHeader, void *object,
                                       RwUInt8 type, RwUInt32 flags);
extern void _rxXbDefaultRenderFFPObjectSetUp(RxXboxResEntryHeader *instancedHeader,
                                             void *object, RwUInt8 type, RwUInt32 flags);
extern void _rxXbDefaultRenderFFPMeshSetUp(RxXboxInstanceData *mesh);
extern void _rxXbDefaultRenderFFPMeshCombinerSetUp(RxXboxInstanceData *mesh, RwUInt32 flags);
extern void _rxXbDefaultRenderFFPMeshCombinerTearDown(void);
extern void _rxXbDefaultRenderFFPMesh(RxXboxResEntryHeader *instancedHeader,
                                      RxXboxInstanceData *mesh, RwUInt32 flags);
extern void _rxXboxAllInOneSetInstanceCallBack(RxPipelineNode *node,
                                               RxXboxAllInOneInstanceCallBack callback);
extern RxXboxAllInOneInstanceCallBack _rxXboxAllInOneGetInstanceCallBack(RxPipelineNode *node);
extern void _rxXboxAllInOneSetRenderCallBack(RxPipelineNode *node,
                                             RxXboxAllInOneRenderCallBack callback);

#endif /* XBPIPE_H */
