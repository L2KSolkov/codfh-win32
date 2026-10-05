/*
 * RwBBoxInitialize and RwBBoxAddPoint, copied from RenderWare 3.7.2
 * RWSDK/src/plcore/babbox.h (the prototypes only). The game calls the
 * image's _RwBBoxInitialize (0x2B3160) and _RwBBoxAddPoint (0x2B31A0), as
 * the vehicle's set-up (type_3DBC78::sub_14D2C0) does.
 */
#ifndef RW_BABBOX_H
#define RW_BABBOX_H

#include "rw/batypes.h"

#ifdef    __cplusplus
extern "C"
{
#endif

extern RwBBox *RwBBoxInitialize(RwBBox *boundBox, const RwV3d *vertex);
extern RwBBox *RwBBoxAddPoint(RwBBox *boundBox, const RwV3d *vertex);
/* The GodAsset models bound their vertices with it (sub_18FC80). */
extern RwBBox *RwBBoxCalculate(RwBBox *boundBox, const RwV3d *verts, RwInt32 numVerts);

#ifdef    __cplusplus
}
#endif

#endif
