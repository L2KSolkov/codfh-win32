/* SUPERSEDED: matched production implementation in xbvtxfmt.c. */
/* PARKED: 2DDB50, four normalized diff lines remain.
 * Explicit y/x/z square accumulation fixes SSE sum ordering; final
 * cross-product load/multiply order remains different. */
#define CrossLoadTrial(o, a, b)                         \
MACRO_START                                                     \
{                                                               \
    (o)->x =                                                    \
        (( (((a)->y) * ( (b)->z))) -                            \
         ( (((a)->z) * ( (b)->y))));                            \
    (o)->y =                                                    \
        (( (((a)->z) * ( (b)->x))) -                            \
         ( (((a)->x) * ( (b)->z))));                            \
    (o)->z =                                                    \
        (( (((a)->x) * ( (b)->y))) -                            \
         ( (((a)->y) * ( (b)->x))));                            \
}                                                               \
MACRO_STOP
#define SMALL_FLOAT 1e-12f
// match: __rpXboxVtxFmtInstBNT @ 0x002DDB50
RwUInt32
_rpXboxVtxFmtInstBNT(RwUInt8 *mem,
                     const RwV3d *pos,
                     const RwV3d *normal,
                     const RwTexCoords *texCoord,
                     RxXboxResEntryHeader *instancedHeader,
                     RwInt32 numVerts,
                     RwUInt32 stride)
{
    RwV3d               *tangent, *binormal;
    RxXboxInstanceData  *mesh;
    RwInt32             n;
    RwReal              unused;

    tangent = (RwV3d *)RwMalloc(sizeof(RwV3d) * instancedHeader->numVertices,
                                rwMEMHINTDUR_FUNCTION | rwID_WORLDPIPEMODULE);
    memset(tangent, 0, sizeof(RwV3d) * instancedHeader->numVertices);

    binormal = (RwV3d *)RwMalloc(sizeof(RwV3d) * instancedHeader->numVertices,
                                 rwMEMHINTDUR_FUNCTION | rwID_WORLDPIPEMODULE);

    for (mesh = instancedHeader->begin; mesh != instancedHeader->end; mesh++)
    {
        const RwUInt16  *indexBuffer = mesh->indexBuffer;
        RwInt32         numIndices = mesh->numIndices;

        if (instancedHeader->primType == D3DPT_TRIANGLESTRIP)
        {
            numIndices -= 2;
        }

        n = 0;
        while (n < numIndices)
        {
            RwUInt32            i1, i2, i3;
            const RwV3d         *vert1, *vert2, *vert3;
            const RwTexCoords   *uv1, *uv2, *uv3;
            RwV3d               *tang1, *tang2, *tang3;
            RwV3d               edge01, edge02, cp;

            if (instancedHeader->primType == D3DPT_TRIANGLELIST)
            {
                i1 = indexBuffer[n + 0];
                i2 = indexBuffer[n + 1];
                i3 = indexBuffer[n + 2];

                n += 3;
            }
            else
            {
                if (n & 0x01)
                {
                    i1 = indexBuffer[n + 2];
                    i2 = indexBuffer[n + 1];
                    i3 = indexBuffer[n + 0];
                }
                else
                {
                    i1 = indexBuffer[n + 0];
                    i2 = indexBuffer[n + 1];
                    i3 = indexBuffer[n + 2];
                }

                ++n;

                if (i1 == i2 || i1 == i3 || i2 == i3)
                {
                    continue;
                }
            }

            vert1 = pos + i1;
            vert2 = pos + i2;
            vert3 = pos + i3;

            uv1 = texCoord + i1;
            uv2 = texCoord + i2;
            uv3 = texCoord + i3;

            tang1 = tangent + i1;
            tang2 = tangent + i2;
            tang3 = tangent + i3;

            /* x, s, t */
            edge01.x = vert2->x - vert1->x;
            edge01.y = uv2->u - uv1->u;
            edge01.z = uv2->v - uv1->v;

            edge02.x = vert3->x - vert1->x;
            edge02.y = uv3->u - uv1->u;
            edge02.z = uv3->v - uv1->v;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->x -= cp.y * invcpx;
                tang2->x -= cp.y * invcpx;
                tang3->x -= cp.y * invcpx;
            }

            /* y, s, t */
            edge01.x = vert2->y - vert1->y;
            edge02.x = vert3->y - vert1->y;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->y -= cp.y * invcpx;
                tang2->y -= cp.y * invcpx;
                tang3->y -= cp.y * invcpx;
            }

            /* z, s, t */
            edge01.x = vert2->z - vert1->z;
            edge02.x = vert3->z - vert1->z;

            RwV3dCrossProduct(&cp, &edge01, &edge02);
            if ((RwReal)fabs(cp.x) > SMALL_FLOAT)
            {
                const RwReal    invcpx = 1.0f / cp.x;

                tang1->z -= cp.y * invcpx;
                tang2->z -= cp.y * invcpx;
                tang3->z -= cp.y * invcpx;
            }
        }
    }

    /* Normalize the tangents and build the binormals */
    for (n = 0; n < instancedHeader->numVertices; n++)
    {
        const RwV3d *currentNormal = normal + n;
        RwV3d *currentTangent = tangent + n;
        RwV3d   *currentBinormal = binormal + n;

        _rwV3dNormalizeMacro(unused, currentTangent, currentTangent);

        CrossLoadTrial(currentBinormal, currentTangent, currentNormal);

        {
            RwReal length2 = currentBinormal->y * currentBinormal->y;
length2 += currentBinormal->x * currentBinormal->x;
length2 += currentBinormal->z * currentBinormal->z;

            rwInvSqrtMacro(&unused, length2);
            currentBinormal->x = unused * currentBinormal->x;
            currentBinormal->y = unused * currentBinormal->y;
            currentBinormal->z = unused * currentBinormal->z;
        }
    }

    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem, tangent, numVerts, stride);
    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem + 4, binormal, numVerts, stride);

    RwFree(binormal);
    RwFree(tangent);

    return 8;
}

