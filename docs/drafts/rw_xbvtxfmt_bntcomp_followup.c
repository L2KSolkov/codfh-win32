/* SUPERSEDED: 2DE0F0 now matches in production xbvtxfmt.c. */
/* PARKED: 2DE0F0 improves from 53 to 12 normalized diff lines.
 * Insert before _rpXboxVtxFmtUnInstV3d with current xbvtxfmt.c headers.
 * Initial tangent length-squared load/sum ordering remains different.
 * Explicit scale read records observed code generation, not original
 * volatile type evidence. See questions.md and rw_bntcomp_* probes. */
#define CompScaleTrial(o, a, s)                                \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) * ( (s)));                               \
    (o)->y = ((((const volatile RwV3d *)(a))->y) * ( (s)));                               \
    (o)->z = (((a)->z) * ( (s)));                               \
}                                                               \
MACRO_STOP
#define SMALL_FLOAT 9.999999960041972e-13
// match: __rpXboxVtxFmtInstBNTComp @ 0x002DE0F0
RwUInt32
_rpXboxVtxFmtInstBNTComp(RwUInt8 *mem,
                     const RwV3d *pos,
                     const RpVertexNormal *normal,
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
        RwV3d unpacked;
        RwV3d *currentTangent = tangent + n;
        RwV3d   *currentBinormal = binormal + n;

        { RwV3d dotValues;
dotValues.y = currentTangent->y;
dotValues.x = currentTangent->x;
dotValues.z = currentTangent->z;
 { RwReal length2 = RwV3dDotProductMacro(&dotValues, &dotValues); rwInvSqrtMacro(&unused, length2); CompScaleTrial(currentTangent, currentTangent, unused); } }

        unpacked.x = ((RwReal)normal[n].x) * (1.0f / 128.0f);
        unpacked.y = ((RwReal)normal[n].y) * (1.0f / 128.0f);
        unpacked.z = ((RwReal)normal[n].z) * (1.0f / 128.0f);
        RwV3dCrossProduct(currentBinormal, currentTangent, &unpacked);

        { RwReal length2 = RwV3dDotProductMacro(currentBinormal, currentBinormal); rwInvSqrtMacro(&unused, length2); currentBinormal->x = unused * currentBinormal->x; currentBinormal->y = unused * currentBinormal->y; currentBinormal->z = unused * currentBinormal->z; }
    }

    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem, tangent, numVerts, stride);
    _rpXboxVtxFmtInstV3d(rpNORMALIZEDPACKED, mem + 4, binormal, numVerts, stride);

    RwFree(binormal);
    RwFree(tangent);

    return 8;
}

