/*
 * codfh-match: RenderWare 3.6's Xbox PTank platform files
 * (plugin/ptank/xbox/ptankxbox.c and ptankxboxopt.c), rebuilt from the
 * image; RenderWare's 3.7.2 tree has only the D3D8/D3D9/OpenGL versions,
 * which the names follow.
 */
#ifndef PTANKXBOX_H
#define PTANKXBOX_H

/* The optimized (point sprite) path: platFlags 1. The application puts its
 * vertex description in the PTank data's userData; the image reads the
 * stride (16 = position and colour, else position only) and a flag that
 * selects the constant colour. */
#define rpPTANKXBOXFLAGSOPTIMIZED   1

typedef struct rpPTankXboxOptData rpPTankXboxOptData;
struct rpPTankXboxOptData
{
    RwUInt32    stride;
    RwUInt32    reserved;
    RwBool      constantColor;
};

extern RwBool _rpPTankXboxOptCreate(RpAtomic *atomic, RpPTankData *ptankGlobal,
                                    RwInt32 maxPCount, RwUInt32 dataFlags,
                                    RwUInt32 platFlags);
extern RwBool _rpPTankXboxOptInstance(RpAtomic *atomic, RpPTankData *ptankGlobal,
                                      RwInt32 actPCount, RwUInt32 instFlags);
extern RwBool _rpPTankXboxOptRenderCallBack(RpAtomic *atomic, RpPTankData *ptankGlobal,
                                            RwInt32 actPCount);

#endif /* PTANKXBOX_H */
