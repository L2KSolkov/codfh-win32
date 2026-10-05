/*
 * codfh-match: RenderWare 3.6's Xbox Im3D nodes
 * (src/pipe/p2/xbox/nodeXBoxSubmitNoLight.c), after d3d8's
 * nodeD3D8SubmitNoLight.h.
 */

#ifndef NODEXBOXSUBMITNOLIGHT_H
#define NODEXBOXSUBMITNOLIGHT_H

#include "p2core.h"

/****************************************************************************
 global prototypes
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RxNodeDefinition *RxNodeDefinitionGetXboxImmInstance(void);
extern RxNodeDefinition *RxNodeDefinitionGetXboxSubmitNoLight(void);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif /* NODEXBOXSUBMITNOLIGHT_H */
