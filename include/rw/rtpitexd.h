/*
 * RtPITexDictionaryStreamRead, copied from RenderWare 3.7.2
 * RWSDK/tool/pitexd/rtpitexd.h (the prototype): reads a platform-independent
 * texture dictionary (the GodAsset texture dictionary kind, sub_18F9E0).
 */
#ifndef RW_RTPITEXD_H
#define RW_RTPITEXD_H

#include "rw/bastream.h"
#include "rw/batextur.h"

#ifdef    __cplusplus
extern "C"
{
#endif

extern RwTexDictionary *RtPITexDictionaryStreamRead(RwStream *stream);

#ifdef    __cplusplus
}
#endif

#endif
