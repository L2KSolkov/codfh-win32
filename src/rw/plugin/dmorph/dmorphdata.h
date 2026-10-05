/*
 * codfh-match: RenderWare 3.6's Xbox delta morph platform data
 * (plugin/dmorph/xbox); the Godfather PDB's DMorphPlatformDataTag.
 */
#ifndef DMORPHDATA_H
#define DMORPHDATA_H

typedef struct DMorphPlatformDataTag DMorphPlatformData;
struct DMorphPlatformDataTag
{
    void       *vertexBuffer;
    RwUInt32    stride;
    RwUInt32    geometryFlags;
};

#endif /* DMORPHDATA_H */
