/*
 * codfh-match: RenderWare 3.6's Xbox world pipeline instancing and default
 * rendering (world/pipe/p2/xbox/xbpipe.c), rebuilt from the image; names from
 * the Godfather PDB's copy of the same file.
 */

#include <xtl.h>
#include <stdlib.h>
#include <string.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "bageomet.h"

#include "xbmemory.h"

#include "xbpipe.h"

// match: _XBMeshGetNumVerticesMinIndex @ 0x002DF670
void
XBMeshGetNumVerticesMinIndex(const RwUInt16 *indices, RwUInt32 numIndices,
                             RwInt32 *numVertices, RwUInt32 *min)
{
    if (numIndices)
    {
        RwUInt32    minVert = 0xFFFFFFFF;
        RwUInt32    maxVert = 0;

        do
        {
            const RwUInt32 index = *indices;

            minVert = (minVert >= index) ? index : minVert;
            maxVert = (maxVert <= index) ? index : maxVert;

            indices++;
        }
        while (--numIndices);

        *numVertices = maxVert - minVert + 1;
        *min = minVert;
    }
    else
    {
        *numVertices = 0;
        *min = 0;
    }
}

// match: __rwXBResourceEntryInstanceDataDestroy @ 0x002DF6C0
void
_rwXBResourceEntryInstanceDataDestroy(RwResEntry *repEntry)
{
    RxXboxResEntryHeader    *resEntryHeader = (RxXboxResEntryHeader *)(repEntry + 1);

    if (resEntryHeader->vertexBuffer)
    {
        RwXbReleaseVertexBuffer((D3DVertexBuffer *)resEntryHeader->vertexBuffer);
        resEntryHeader->vertexBuffer = NULL;
    }
}

/* qsort order for triangles: by their sorted vertex indices. */
// match: _SortTriangles @ 0x002DF6E0
static int
SortTriangles(const void *pA, const void *pB)
{
    const RwUInt16  *triA = (const RwUInt16 *)pA;
    const RwUInt16  *triB = (const RwUInt16 *)pB;
    RwUInt32        sortedIndexA[3];
    RwUInt32        sortedIndexB[3];
    RwUInt32        temp;

    sortedIndexA[0] = triA[0];
    sortedIndexA[1] = triA[1];
    sortedIndexA[2] = triA[2];

    if (sortedIndexA[0] > sortedIndexA[1])
    {
        temp = sortedIndexA[0];
        sortedIndexA[0] = sortedIndexA[1];
        sortedIndexA[1] = temp;
    }

    if (sortedIndexA[1] > sortedIndexA[2])
    {
        temp = sortedIndexA[1];
        sortedIndexA[1] = sortedIndexA[2];
        sortedIndexA[2] = temp;

        if (sortedIndexA[0] > sortedIndexA[1])
        {
            temp = sortedIndexA[0];
            sortedIndexA[0] = sortedIndexA[1];
            sortedIndexA[1] = temp;
        }
    }

    sortedIndexB[0] = triB[0];
    sortedIndexB[1] = triB[1];
    sortedIndexB[2] = triB[2];

    if (sortedIndexB[0] > sortedIndexB[1])
    {
        temp = sortedIndexB[0];
        sortedIndexB[0] = sortedIndexB[1];
        sortedIndexB[1] = temp;
    }

    if (sortedIndexB[1] > sortedIndexB[2])
    {
        temp = sortedIndexB[1];
        sortedIndexB[1] = sortedIndexB[2];
        sortedIndexB[2] = temp;

        if (sortedIndexB[0] > sortedIndexB[1])
        {
            temp = sortedIndexB[0];
            sortedIndexB[0] = sortedIndexB[1];
            sortedIndexB[1] = temp;
        }
    }

    if (sortedIndexA[0] == sortedIndexB[0])
    {
        if (sortedIndexA[1] == sortedIndexB[1])
        {
            return sortedIndexA[2] - sortedIndexB[2];
        }

        return sortedIndexA[1] - sortedIndexB[1];
    }

    return sortedIndexA[0] - sortedIndexB[0];
}
