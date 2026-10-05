/* PARKED 2026-10-01: delta-morph instance callback follow-up.
 * Insert before _rpDMorphPipelinesCreate in dmorph/xbox/dmorphpipeg.c;
 * the unit also needs xbvtxfmt.h. Derived from dmorph_instance_draft.c.
 * Separate counters in position, prelight and texcoord deformation loops
 * reduce the current-header normalized diff from 1312 to 1261 lines.
 * First differing instruction remains 6; this is still far from a match.
 * XboxDMorphAddBlock must remain beside the caller for its register ABI.
 * Full 255-subset loop-scope search found no better score. Initial-loop
 * cached inputs and typed extension accessors did not resolve the prologue.
 */
typedef struct _BlockInfo _BlockInfo;
struct _BlockInfo
{
    RwUInt32    firstVertex;
    RwUInt32    numVertex;
};

// match: _XboxDMorphAddBlock @ 0x002F2860
static RwUInt32
XboxDMorphAddBlock(RwUInt32 numBlocks, _BlockInfo *blocks,
                   RwUInt32 firstVertex, RwUInt32 numVertex)
{
    RwUInt32    lastVertexBlockToAdd;
    RwUInt32    n;

    lastVertexBlockToAdd = firstVertex + numVertex;

    for (n = 0; n < numBlocks; n++)
    {
        if (firstVertex >= blocks[n].firstVertex)
        {
            RwUInt32    lastVertexBlock;

            lastVertexBlock = blocks[n].firstVertex + blocks[n].numVertex;

            if (firstVertex < lastVertexBlock)
            {
                if (lastVertexBlockToAdd > lastVertexBlock)
                {
                    blocks[n].numVertex += lastVertexBlockToAdd - lastVertexBlock;
                }
                break;
            }
            else if (firstVertex == lastVertexBlock)
            {
                blocks[n].numVertex += numVertex;
                break;
            }
        }
        else if (lastVertexBlockToAdd == blocks[n].firstVertex)
        {
            blocks[n].firstVertex = firstVertex;
            blocks[n].numVertex += numVertex;
            break;
        }
    }

    if (n >= numBlocks)
    {
        blocks[numBlocks].firstVertex = firstVertex;
        blocks[numBlocks].numVertex = numVertex;
        numBlocks++;
    }

    return numBlocks;
}

// match: _XboxDmorphAtomicInstanceCallback @ 0x002F28D0
RwBool
XboxDmorphAtomicInstanceCallback(void *object,
                                 RxXboxResEntryHeader *instancedHeader,
                                 RwBool reinstance)
{
    RpAtomic                *atomic = (RpAtomic *)object;
    RpGeometry              *geometry = RpAtomicGetGeometry(atomic);
    RpGeometryFlag          flags = (RpGeometryFlag)RpGeometryGetFlags(geometry);
    rpDMorphAtomicData      *atomicData = RPDMORPHATOMICGETDATA(atomic);
    rpDMorphGeometryData    *geometryData = *RPDMORPHGEOMETRYGETDATA(RpAtomicGetGeometry(atomic));
    RwUInt32                dmorphLockedSinceLastInst;
    RwUInt32                dmorphFlags;
    RwUInt32                numBlocks;
    RwUInt32                i;

    dmorphLockedSinceLastInst = 0;
    dmorphFlags = 0;
    numBlocks = 0;

    if (geometryData && atomicData->values)
    {
        for (i = 0; i < geometryData->numDMorphTargets; i++)
        {
            const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets[i];

            dmorphFlags |= dMorphTarget->flags;

            if (atomicData->values[i] != geometryData->currValues[i])
            {
                const rpDMorphRLE   *rle = &dMorphTarget->rle;
                RwUInt32            j;

                for (j = 0; j < rle->numCodeElements; j++)
                {
                    if ((rle->code[j] & 0x7F) && (rle->code[j] & 0x80))
                    {
                        numBlocks++;
                    }
                }

                if (dMorphTarget->flags & rpGEOMETRYPOSITIONS)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKVERTICES;
                }
                if (dMorphTarget->flags & rpGEOMETRYNORMALS)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKNORMALS;
                }
                if (dMorphTarget->flags & rpGEOMETRYPRELIT)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKPRELIGHT;
                }
                if (dMorphTarget->flags & rpGEOMETRYTEXTURED)
                {
                    dmorphLockedSinceLastInst |= rpGEOMETRYLOCKTEXCOORDS1;
                }
            }
        }
    }

    if (dmorphLockedSinceLastInst || !reinstance || geometry->lockedSinceLastInst)
    {
        RpXboxVtxFmt        *fmt;
        RwUInt8             *lockedVertexBuffer = NULL;
        RwUInt8             *lockedVertexBufferStatic = NULL;
        RwUInt8             *dstVertices = NULL;
        RwUInt8             *dstNormals = NULL;
        RwUInt8             *dstPreLightColors = NULL;
        RwUInt8             *dstTexCoords = NULL;
        RwUInt8             *currentVertexBuffer;
        RwUInt8             *currentVertexBufferStatic;
        RwV3d               *positions;
        RwV3d               *normals;
        RwRGBA              *color;
        RwInt32             numTexCoordSets;
        RwTexCoords         **texCoordSets;
        RwUInt32            lockedSinceLastInst;
        RwInt32             numVertices;
        RwUInt32            flagsStatic;

        fmt = RpXboxGeometryGetVtxFmt(geometry);

        positions = geometry->morphTarget->verts;

        if (flags & rxGEOMETRY_NORMALS)
        {
            normals = geometry->morphTarget->normals;
        }
        else
        {
            normals = NULL;
        }

        if (flags & rxGEOMETRY_PRELIT)
        {
            color = RpGeometryGetPreLightColors(geometry);
        }
        else
        {
            color = NULL;
        }

        if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2))
        {
            numTexCoordSets = geometry->numTexCoordSets;
        }
        else
        {
            numTexCoordSets = 0;
        }

        if ((flags & rxGEOMETRY_TEXTURED) || (flags & rpGEOMETRYTEXTURED2))
        {
            texCoordSets = geometry->texCoords;
        }
        else
        {
            texCoordSets = NULL;
        }

        if (reinstance)
        {
            lockedSinceLastInst = geometry->lockedSinceLastInst;
        }
        else
        {
            lockedSinceLastInst = rpGEOMETRYLOCKALL;
        }

        numVertices = instancedHeader->numVertices;

        if (numTexCoordSets > 4)
        {
            numTexCoordSets = 4;
        }

        if (*((RwUInt32 *)fmt) == 0)
        {
            RpXboxVtxFmtInit(fmt, flags, numTexCoordSets);
        }

        if (instancedHeader->vertexBuffer == NULL)
        {
            DWORD               vertexFormatDecl[256];
            DWORD               shader;
            RxXboxInstanceData  *mesh;

            if (dmorphFlags)
            {
                geometryData->platformData.geometryFlags = (flags & ~dmorphFlags) & rpGEOMETRYFLAGSMASK;
            }
            else
            {
                dmorphFlags = flags;
                geometryData->platformData.geometryFlags = 0;
            }

            vertexFormatDecl[0] = D3DVSD_STREAM(0);
            i = 1;
            instancedHeader->stride = 0;

            if (dmorphFlags & rxGEOMETRY_POSITIONS)
            {
                switch (fmt->pos)
                {
                    case rpPACKEDBYTE:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_PBYTE3);
                        instancedHeader->stride += 3;
                        break;

                    case rpSHORT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_SHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDSHORTS:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMSHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDPACKED:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMPACKED3);
                        instancedHeader->stride += 4;
                        break;

                    case rpFLOAT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3);
                        instancedHeader->stride += 12;
                        break;
                }
            }

            if (dmorphFlags & rxGEOMETRY_NORMALS)
            {
                switch (fmt->norm)
                {
                    case rpPACKEDBYTE:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_PBYTE3);
                        instancedHeader->stride += 3;
                        break;

                    case rpSHORT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_SHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDSHORTS:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMSHORT3);
                        instancedHeader->stride += 6;
                        break;

                    case rpNORMALIZEDPACKED:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMPACKED3);
                        instancedHeader->stride += 4;
                        break;

                    case rpFLOAT:
                        vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3);
                        instancedHeader->stride += 12;
                        break;
                }
            }

            if (dmorphFlags & rxGEOMETRY_PRELIT)
            {
                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR);
                instancedHeader->stride += 4;
            }

            if (dmorphFlags & rxGEOMETRY_TEXTURED)
            {
                RpXboxCompType type = (RpXboxCompType)(fmt->texCoord & 0xF);

                if (type != rpCOMPTYPENONE)
                {
                    switch (type)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_PBYTE2);
                            instancedHeader->stride += 2;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_SHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMSHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMPACKED3);
                            instancedHeader->stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2);
                            instancedHeader->stride += 8;
                            break;
                    }
                }
            }

            if (dmorphFlags & rpGEOMETRYTEXTURED2)
            {
                RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> 4) & 0xF);

                if (type != rpCOMPTYPENONE)
                {
                    switch (type)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_PBYTE2);
                            instancedHeader->stride += 2;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_SHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMSHORT2);
                            instancedHeader->stride += 4;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMPACKED3);
                            instancedHeader->stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT2);
                            instancedHeader->stride += 8;
                            break;
                    }
                }
            }

            geometryData->platformData.stride = 0;

            if (geometryData->platformData.geometryFlags)
            {
                vertexFormatDecl[i++] = D3DVSD_STREAM(1);

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_POSITIONS)
                {
                    switch (fmt->pos)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_PBYTE3);
                            geometryData->platformData.stride += 3;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_SHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMSHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_NORMPACKED3);
                            geometryData->platformData.stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3);
                            geometryData->platformData.stride += 12;
                            break;
                    }
                }

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_NORMALS)
                {
                    switch (fmt->norm)
                    {
                        case rpPACKEDBYTE:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_PBYTE3);
                            geometryData->platformData.stride += 3;
                            break;

                        case rpSHORT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_SHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDSHORTS:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMSHORT3);
                            geometryData->platformData.stride += 6;
                            break;

                        case rpNORMALIZEDPACKED:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_NORMPACKED3);
                            geometryData->platformData.stride += 4;
                            break;

                        case rpFLOAT:
                            vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3);
                            geometryData->platformData.stride += 12;
                            break;
                    }
                }

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_PRELIT)
                {
                    vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR);
                    geometryData->platformData.stride += 4;
                }

                if (geometryData->platformData.geometryFlags & rxGEOMETRY_TEXTURED)
                {
                    RpXboxCompType type = (RpXboxCompType)(fmt->texCoord & 0xF);

                    if (type != rpCOMPTYPENONE)
                    {
                        switch (type)
                        {
                            case rpPACKEDBYTE:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_PBYTE2);
                                geometryData->platformData.stride += 2;
                                break;

                            case rpSHORT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_SHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDSHORTS:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMSHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDPACKED:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_NORMPACKED3);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpFLOAT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2);
                                geometryData->platformData.stride += 8;
                                break;
                        }
                    }
                }

                if (geometryData->platformData.geometryFlags & rpGEOMETRYTEXTURED2)
                {
                    RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> 4) & 0xF);

                    if (type != rpCOMPTYPENONE)
                    {
                        switch (type)
                        {
                            case rpPACKEDBYTE:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_PBYTE2);
                                geometryData->platformData.stride += 2;
                                break;

                            case rpSHORT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_SHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDSHORTS:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMSHORT2);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpNORMALIZEDPACKED:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_NORMPACKED3);
                                geometryData->platformData.stride += 4;
                                break;

                            case rpFLOAT:
                                vertexFormatDecl[i++] = D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT2);
                                geometryData->platformData.stride += 8;
                                break;
                        }
                    }
                }
            }

            vertexFormatDecl[i++] = D3DVSD_END();

            if (D3D_OK != D3DDevice_CreateVertexShader(vertexFormatDecl, NULL, &shader, 0))
            {
                return FALSE;
            }

            for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
            {
                mesh->vertexShader = shader;
            }

            instancedHeader->vertexBuffer = RwXbCreateVertexBuffer(instancedHeader->stride * numVertices);
            if (instancedHeader->vertexBuffer == NULL)
            {
                return FALSE;
            }

            lockedVertexBuffer = D3DVertexBuffer_Lock2((D3DVertexBuffer *)instancedHeader->vertexBuffer, 0);

            if (geometryData->platformData.vertexBuffer)
            {
                RwXbReleaseVertexBuffer((D3DVertexBuffer *)geometryData->platformData.vertexBuffer);
                geometryData->platformData.vertexBuffer = NULL;
            }

            if (geometryData->platformData.stride)
            {
                geometryData->platformData.vertexBuffer =
                    RwXbCreateVertexBuffer(geometryData->platformData.stride * numVertices);
                if (geometryData->platformData.vertexBuffer == NULL)
                {
                    return FALSE;
                }

                lockedVertexBufferStatic =
                    D3DVertexBuffer_Lock2((D3DVertexBuffer *)geometryData->platformData.vertexBuffer, 0);
            }
            else
            {
                geometryData->platformData.vertexBuffer = NULL;
            }
        }
        else
        {
            D3DVertexBuffer     *pBuffer = (D3DVertexBuffer *)instancedHeader->vertexBuffer;
            RwUInt32            lockFlagsStatic;
            RwUInt32            vbSize;

            lockFlagsStatic = 0;
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_POSITIONS)
            {
                lockFlagsStatic = rpGEOMETRYLOCKVERTICES;
            }
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_NORMALS)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKNORMALS;
            }
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_PRELIT)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKPRELIGHT;
            }
            if (geometryData->platformData.geometryFlags & rxGEOMETRY_TEXTURED)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKTEXCOORDS1;
            }
            if (geometryData->platformData.geometryFlags & rpGEOMETRYTEXTURED2)
            {
                lockFlagsStatic |= rpGEOMETRYLOCKTEXCOORDS2;
            }

            vbSize = instancedHeader->stride * numVertices;

            if (pBuffer->Lock && D3DDevice_IsFencePending(pBuffer->Lock))
            {
                lockedVertexBuffer = RwXbVertexBufferLockDiscard(pBuffer, vbSize);
                reinstance = FALSE;
                lockedSinceLastInst |= (~lockFlagsStatic & rpGEOMETRYLOCKALL);
            }
            else
            {
                lockedVertexBuffer = D3DVertexBuffer_Lock2(pBuffer, 0);
            }

            if (lockedSinceLastInst & lockFlagsStatic)
            {
                lockedVertexBufferStatic =
                    D3DVertexBuffer_Lock2((D3DVertexBuffer *)geometryData->platformData.vertexBuffer, 0);
            }
        }

        flagsStatic = geometryData->platformData.geometryFlags;
        lockedSinceLastInst &= ~dmorphLockedSinceLastInst;

        currentVertexBuffer = lockedVertexBuffer;
        currentVertexBufferStatic = lockedVertexBufferStatic;

        if (positions)
        {
            if (flagsStatic & rxGEOMETRY_POSITIONS)
            {
                dstVertices = currentVertexBufferStatic;
                if (lockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos,
                                                                     currentVertexBufferStatic,
                                                                     positions, numVertices,
                                                                     geometryData->platformData.stride);
                }
                else
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
                }
            }
            else
            {
                dstVertices = currentVertexBuffer;
                if (lockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
                {
                    currentVertexBuffer += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos,
                                                               currentVertexBuffer,
                                                               positions, numVertices,
                                                               instancedHeader->stride);
                }
                else
                {
                    currentVertexBuffer += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);
                }
            }
        }

        if (normals)
        {
            if (flagsStatic & rxGEOMETRY_NORMALS)
            {
                dstNormals = currentVertexBufferStatic;
                if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm,
                                                                     currentVertexBufferStatic,
                                                                     normals, numVertices,
                                                                     geometryData->platformData.stride);
                }
                else
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
                }
            }
            else
            {
                dstNormals = currentVertexBuffer;
                if (lockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
                {
                    currentVertexBuffer += _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm,
                                                               currentVertexBuffer,
                                                               normals, numVertices,
                                                               instancedHeader->stride);
                }
                else
                {
                    currentVertexBuffer += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->norm, 3);
                }
            }
        }

        if (color)
        {
            if (flagsStatic & rxGEOMETRY_PRELIT)
            {
                dstPreLightColors = currentVertexBufferStatic;
                if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
                {
                    instancedHeader->vertexAlpha =
                        _rpXboxVtxFmtInstColor(currentVertexBufferStatic, color, numVertices,
                                               geometryData->platformData.stride);
                }
                currentVertexBufferStatic += sizeof(RwRGBA);
            }
            else
            {
                dstPreLightColors = currentVertexBuffer;
                if (lockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
                {
                    instancedHeader->vertexAlpha =
                        _rpXboxVtxFmtInstColor(currentVertexBuffer, color, numVertices,
                                               instancedHeader->stride);
                }
                currentVertexBuffer += sizeof(RwRGBA);
            }
        }

        if (flagsStatic & (rxGEOMETRY_TEXTURED | rpGEOMETRYTEXTURED2))
        {
            dstTexCoords = currentVertexBufferStatic;
            for (i = 0; i < (RwUInt32)numTexCoordSets; i++)
            {
                RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

                if (lockedSinceLastInst & (rpGEOMETRYLOCKTEXCOORDS1 << i))
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtInstV2d(type, currentVertexBufferStatic,
                                                                     texCoordSets[i], numVertices,
                                                                     geometryData->platformData.stride);
                }
                else
                {
                    currentVertexBufferStatic += _rpXboxVtxFmtGetSize(type, 2);
                }
            }
        }
        else
        {
            dstTexCoords = currentVertexBuffer;
            for (i = 0; i < (RwUInt32)numTexCoordSets; i++)
            {
                RpXboxCompType type = (RpXboxCompType)((fmt->texCoord >> (4 * i)) & 0xF);

                if (lockedSinceLastInst & (rpGEOMETRYLOCKTEXCOORDS1 << i))
                {
                    currentVertexBuffer += _rpXboxVtxFmtInstV2d(type, currentVertexBuffer,
                                                               texCoordSets[i], numVertices,
                                                               instancedHeader->stride);
                }
                else
                {
                    currentVertexBuffer += _rpXboxVtxFmtGetSize(type, 2);
                }
            }
        }

        if (dmorphLockedSinceLastInst)
        {
            _BlockInfo  *blocks;

            blocks = (_BlockInfo *)RwMalloc(sizeof(_BlockInfo) * numBlocks, 0);

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKVERTICES)
            {
                RwUInt32    currentBlock = 0;

                { RwUInt32 localIndex;
for (localIndex = 0; localIndex < geometryData->numDMorphTargets; localIndex++)
                {
                    if (atomicData->values[localIndex] != geometryData->currValues[localIndex])
                    {
                        const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets[localIndex];

                        if (dMorphTarget->flags & rpGEOMETRYPOSITIONS)
                        {
                            const RwReal        scale = atomicData->values[localIndex] - geometryData->currValues[localIndex];
                            const rpDMorphRLE   *rle = &dMorphTarget->rle;
                            const RwV3d         *deltaVertices = dMorphTarget->vertices;
                            RwUInt32            j;
                            RwUInt32            k;

                            k = 0;
                            for (j = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        RwUInt32    l;

                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            positions[k].x += deltaVertices->x * scale;
                                            positions[k].y += deltaVertices->y * scale;
                                            positions[k].z += deltaVertices->z * scale;
                                            k++;
                                            deltaVertices++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }
}

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;
                    RwUInt32        l;

                    for (l = 0; l < currentBlock; l++)
                    {
                        _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos,
                                             &dstVertices[stride * blocks[l].firstVertex],
                                             &positions[blocks[l].firstVertex],
                                             blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos, dstVertices, positions,
                                         numVertices, instancedHeader->stride);
                }
            }

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKNORMALS)
            {
                RwUInt32    currentBlock = 0;

                for (i = 0; i < geometryData->numDMorphTargets; i++)
                {
                    if (atomicData->values[i] != geometryData->currValues[i])
                    {
                        const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets[i];

                        if (dMorphTarget->flags & rpGEOMETRYNORMALS)
                        {
                            const RwReal        scale = atomicData->values[i] - geometryData->currValues[i];
                            const rpDMorphRLE   *rle = &dMorphTarget->rle;
                            const RwV3d         *deltaNormals = dMorphTarget->normals;
                            RwUInt32            j;
                            RwUInt32            k;

                            k = 0;
                            for (j = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        RwUInt32    l;

                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            normals[k].x += deltaNormals->x * scale;
                                            normals[k].y += deltaNormals->y * scale;
                                            normals[k].z += deltaNormals->z * scale;
                                            k++;
                                            deltaNormals++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;
                    RwUInt32        l;

                    for (l = 0; l < currentBlock; l++)
                    {
                        _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm,
                                             &dstNormals[stride * blocks[l].firstVertex],
                                             &normals[blocks[l].firstVertex],
                                             blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    _rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->norm, dstNormals, normals,
                                         numVertices, instancedHeader->stride);
                }
            }

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKPRELIGHT)
            {
                RwUInt32    currentBlock = 0;

                { RwUInt32 localIndex;
for (localIndex = 0; localIndex < geometryData->numDMorphTargets; localIndex++)
                {
                    if (atomicData->values[localIndex] != geometryData->currValues[localIndex])
                    {
                        const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets[localIndex];

                        if (dMorphTarget->flags & rpGEOMETRYPRELIT)
                        {
                            const rpDMorphRLE   *rle = &dMorphTarget->rle;
                            const RwRGBA        *deltaPreLightColors = dMorphTarget->preLightColors;
                            RwUInt32            j;
                            RwUInt32            k;
                            RwUInt32            m;

                            k = 0;
                            m = 0;
                            for (j = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        RwUInt32    l;

                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            const RwReal lastValue = geometryData->currValues[localIndex];
                                            const RwReal thisValue = atomicData->values[localIndex];

                                            color[k].red += (RwUInt8)(deltaPreLightColors[m].red * thisValue -
                                                                      deltaPreLightColors[m].red * lastValue);
                                            color[k].green += (RwUInt8)(deltaPreLightColors[m].green * thisValue -
                                                                        deltaPreLightColors[m].green * lastValue);
                                            color[k].blue += (RwUInt8)(deltaPreLightColors[m].blue * thisValue -
                                                                       deltaPreLightColors[m].blue * lastValue);
                                            color[k].alpha += (RwUInt8)(deltaPreLightColors[m].alpha * thisValue -
                                                                        deltaPreLightColors[m].alpha * lastValue);
                                            k++;
                                            m++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }
}

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;
                    RwUInt32        l;

                    for (l = 0; l < currentBlock; l++)
                    {
                        instancedHeader->vertexAlpha |=
                            _rpXboxVtxFmtInstColor(&dstPreLightColors[stride * blocks[l].firstVertex],
                                                   &color[blocks[l].firstVertex],
                                                   blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    instancedHeader->vertexAlpha =
                        _rpXboxVtxFmtInstColor(dstPreLightColors, color, numVertices,
                                               instancedHeader->stride);
                }
            }

            if (dmorphLockedSinceLastInst & rpGEOMETRYLOCKTEXCOORDS1)
            {
                RwUInt32    currentBlock = 0;

                { RwUInt32 localIndex;
for (localIndex = 0; localIndex < geometryData->numDMorphTargets; localIndex++)
                {
                    if (atomicData->values[localIndex] != geometryData->currValues[localIndex])
                    {
                        const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets[localIndex];

                        if (dMorphTarget->flags & rpGEOMETRYTEXTURED)
                        {
                            const RwReal        scale = atomicData->values[localIndex] - geometryData->currValues[localIndex];
                            const rpDMorphRLE   *rle = &dMorphTarget->rle;
                            const RwTexCoords   *deltaTexCoords = dMorphTarget->texCoords;
                            RwUInt32            j;
                            RwUInt32            k;
                            RwUInt32            m;

                            k = 0;
                            m = 0;
                            for (j = 0; j < rle->numCodeElements; j++)
                            {
                                RwUInt32    maxl = rle->code[j] & 0x7F;

                                if (maxl)
                                {
                                    if (rle->code[j] & 0x80)
                                    {
                                        RwUInt32    l;

                                        if (reinstance)
                                        {
                                            currentBlock = XboxDMorphAddBlock(currentBlock, blocks, k, maxl);
                                        }

                                        for (l = 0; l < maxl; l++)
                                        {
                                            texCoordSets[0][k].u += deltaTexCoords[m].u * scale;
                                            texCoordSets[0][k].v += deltaTexCoords[m].v * scale;
                                            k++;
                                            m++;
                                        }
                                    }
                                    else
                                    {
                                        k += maxl;
                                    }
                                }
                            }
                        }
                    }
                }
}

                if (reinstance)
                {
                    const RwUInt32  stride = instancedHeader->stride;
                    RwUInt32        l;

                    for (l = 0; l < currentBlock; l++)
                    {
                        _rpXboxVtxFmtInstV2d((RpXboxCompType)(fmt->texCoord & 0xF),
                                             &dstTexCoords[stride * blocks[l].firstVertex],
                                             &texCoordSets[0][blocks[l].firstVertex],
                                             blocks[l].numVertex, stride);
                    }
                }
                else
                {
                    _rpXboxVtxFmtInstV2d((RpXboxCompType)(fmt->texCoord & 0xF), dstTexCoords,
                                         texCoordSets[0], numVertices, instancedHeader->stride);
                }
            }

            for (i = 0; i < geometryData->numDMorphTargets; i++)
            {
                geometryData->currValues[i] = atomicData->values[i];
            }

            RwFree(blocks);
        }

        D3DVertexBuffer_Unlock((D3DVertexBuffer *)instancedHeader->vertexBuffer);
        if (lockedVertexBufferStatic)
        {
            D3DVertexBuffer_Unlock((D3DVertexBuffer *)geometryData->platformData.vertexBuffer);
        }
    }

    return TRUE;
}

