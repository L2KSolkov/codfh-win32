/*
 * codfh-match: RenderWare 3.6's Xbox world sector all-in-one node
 * (world/pipe/p2/xbox/nodeXBoxWorldSectorAllInOne.c).
 */
#ifndef NODEXBOXWORLDSECTORALLINONE_H
#define NODEXBOXWORLDSECTORALLINONE_H

extern void _rwXbWorldSectorDefaultLightingCallback(void *object);
extern RwBool _rxXBWorldSectorDefaultInstanceCallback(void *object,
                                                      RxXboxResEntryHeader *instancedHeader,
                                                      RwBool reinstance);
extern RwBool _rxXBWorldSectorAllInOnePipelineInit(RxPipelineNode *node);
extern RxNodeDefinition *RxNodeDefinitionGetXboxWorldSectorAllInOne(void);

#endif /* NODEXBOXWORLDSECTORALLINONE_H */
