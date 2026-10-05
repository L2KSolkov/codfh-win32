/*
 * codfh-match: RenderWare 3.6's Xbox atomic all-in-one node
 * (world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c).
 */
#ifndef NODEXBOXATOMICALLINONE_H
#define NODEXBOXATOMICALLINONE_H

extern void _rwXbAtomicDefaultLightingCallback(void *object);
extern RwBool _rxXBAtomicDefaultInstanceCallback(void *object,
                                                 RxXboxResEntryHeader *instancedHeader,
                                                 RwBool reinstance);
extern RwBool _rxXBAtomicDefaultReinstanceCallback(void *object,
                                                   RxXboxResEntryHeader *instancedHeader);
extern RwBool _rxXBAtomicAllInOnePipelineInit(RxPipelineNode *node);
extern RxNodeDefinition *RxNodeDefinitionGetXboxAtomicAllInOne(void);

#endif /* NODEXBOXATOMICALLINONE_H */
