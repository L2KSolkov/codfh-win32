/*
 * codfh-match: RenderWare 3.6's Xbox world lights
 * (world/pipe/p2/xbox/xblights.c).
 */
#ifndef XBLIGHTS_H
#define XBLIGHTS_H

extern RwBool _rwXBLightsGlobalEnable(RwUInt32 *numLights, RwUInt32 flags, RwBool hasNormals);
extern RwBool _rxXBLightLocalEnable(RpLight *light, RwUInt32 *numLights);
extern void RwXboxLightsEnable(RwInt32 numLights, RwBool enable);

#endif /* XBLIGHTS_H */
