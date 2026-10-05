/*
 * codfh-match: RenderWare 3.6's Xbox skin plugin internals
 * (plugin/skin2/xbox/); names from the Godfather PDB. The skin's platform
 * data and pipeline array live in null/skinnull.h's _XBOX branch.
 */
#ifndef SKINXBOX_H
#define SKINXBOX_H

#include "xbpipe.h"

/* The skin's vertex format: component types per element. */
#pragma pack(push, 1)
typedef struct _rpSkinXboxVtxFmtTag _rpSkinXboxVtxFmt;
struct _rpSkinXboxVtxFmtTag
{
    RwUInt8             pos : 4;
    RwUInt8             norm : 4;
    RwUInt16            texCoord;       /* four 4-bit types */
    RwUInt8             prelit : 1;
    RwUInt8             numWeights : 6;
    RwUInt8             bnt : 1;
};
#pragma pack(pop)

extern DWORD _rpSkinXboxGetVertexFormatShader(const _rpSkinXboxVtxFmt *desc);

/* A skin vertex shader's key. */
typedef struct _rpSkinXboxShaderDesc _rpSkinXboxShaderDesc;
struct _rpSkinXboxShaderDesc
{
    RwUInt8     numWeights;
    RwUInt8     numDirect;
    RwUInt8     numPoint;
    RwUInt8     matfx : 4;
    RwUInt8     bnt : 3;
    RwUInt8     prelit : 1;
};

typedef void (*_rxXboxSkinAllInOneRenderCallBack)(RxXboxResEntryHeader *resEntryHeader,
                                                  RxXboxInstanceData *mesh,
                                                  RpAtomic *atomic,
                                                  RwUInt32 flags,
                                                  RwUInt32 maxWeightsUsed,
                                                  RwUInt32 dirLightCount,
                                                  RwUInt32 pointLightCount);

extern RwBool _rpSkinXboxInitShaders(void);
extern void _rpSkinXboxDestroyShaders(void);
extern void _rpSkinXboxPurgeShaderCache(void);
extern void _rpSkinXboxSetShader(DWORD formatIndex, const DWORD *shader);
extern const DWORD *_rpSkinXboxGetShader(const _rpSkinXboxShaderDesc *desc);
extern RxPipeline *_rpSkinXboxCreateAtomicPipeline(void);
extern void _rpSkinXboxVertexFormatCreate(void);
extern void _rpSkinXboxVertexFormatDestroy(void);

extern RxNodeDefinition *RxNodeDefinitionGetXboxSkinAtomicAllInOne(void);
extern void _rxXboxSkinAllInOneSetRenderCallBack(RxPipelineNode *node,
                                                 _rxXboxSkinAllInOneRenderCallBack callback);

/* skinxboxrender.c: the per-atomic vertex shader constants and the cached
 * matrices. */
extern RwV4d _rpSkinXboxPerAtomicConstants[];
extern D3DMATRIX _rpSkinXboxCachedWorldMatrix;
extern D3DMATRIX _rpSkinXboxCachedViewMatrix;

extern void _rpSkinXboxComputeProjViewWorld(D3DMATRIX *worldMatrix, D3DMATRIX *viewMatrix,
                                            D3DMATRIX *projViewWorldMatrix,
                                            const RpAtomic *atomic,
                                            const D3DVECTOR4 *viewportScale);
extern RwV4d *_rpSkinXboxEnumerateLights(RwV4d *shaderConstants, RwInt32 *dirLightCount,
                                         RwInt32 *pointLightCount, RpAtomic *atomic);
extern void _rpSkinXboxMatrixUpdate(RwV4d *shaderConstants, RpAtomic *atomic, RpSkin *skin);
extern void _rpSkinXboxSetMaterialColor(const RpMaterial *material, RwUInt32 modulate);

/* skinxboxinstance.c */
extern RwBool _rpSkinXboxInstanceCallback(void *object, RxXboxResEntryHeader *instancedHeader,
                                          RwBool reinstance);
extern RwBool _rpSkinXboxReInstanceCallback(void *object, RxXboxResEntryHeader *instancedHeader);

extern RwInt32 _rpSkinXboxPlainMaterialSetUp(const RpAtomic *atomic,
                                             const RxXboxInstanceData *mesh,
                                             const RpMaterial *material,
                                             RwUInt32 pass);
extern RxPipeline *_rpSkinXboxCreatePlainPipe(void);
extern void _rpSkinXboxDestroyPlainPipe(void);

extern void _rpSkinXboxTo192Constants(void);
extern void _rpSkinXboxTo96Constants(void);

#endif /* SKINXBOX_H */
