/*
 * RwStreamFindChunk (RenderWare 3.7.2 RWSDK/src/plcore/babinary.h) and
 * RwTexDictionaryStreamRead (RWSDK/src/babintex.h), as the game's texture
 * dictionary reader (sub_DC000) calls them. The image's
 * RwTexDictionaryStreamRead reads only its stream, but the game passes a
 * second argument, 0, so its prototype took one more (named for its value
 * only).
 */
#ifndef RW_BABINTEX_H
#define RW_BABINTEX_H

#include "rw/ostypes.h"
#include "rw/bastream.h"

typedef struct RwTexDictionary RwTexDictionary;

/* The world's stream chunk (rwID_WORLD, rwVENDORID_CORE's 0x0B): the
 * level sections' loaders (unit_141BB0) find it. */
#define rwID_WORLD 0x0B
#define rwID_TEXDICTIONARY 0x16
/* The PI texture dictionary's chunk id, MAKECHUNKID(rwVENDORID_CORE, 0x23). */
#define rwID_PITEXDICTIONARY 0x23
/* The UV animation dictionary's chunk id (rwID_UVANIMDICT, 0x2B). */
#define rwID_UVANIMDICT 0x2B

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwBool RwStreamFindChunk(RwStream *stream, RwUInt32 type,
                                RwUInt32 *lengthOut, RwUInt32 *versionOut);
extern RwTexDictionary *RwTexDictionaryStreamRead(RwStream *stream, void *unused);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
