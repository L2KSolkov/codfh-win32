/*
 * RtDict (RenderWare 3.7.2 RWSDK/include/xbox/rtdict.h): the dictionary
 * schemas, as far as the game uses them. The level sections' XBSP loader
 * (unit_141BB0) makes the UV animation schema's current dictionary the one
 * the database calls `schema` (0x4E5CC0) before it reads the world.
 */
#ifndef RW_RTDICT_H
#define RW_RTDICT_H

#include "rw/ostypes.h"
#include "rw/bastream.h"

typedef struct RtDict RtDict;
typedef struct RtDictSchema RtDictSchema;

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RtDictSchema *RtDictSchemaSetCurrentDict(RtDictSchema *schema, RtDict *dict);
typedef void *RtDictEntryType;
typedef RtDictEntryType RtDictEntryCallBack(RtDictEntryType entry, void *data);
extern RtDict *RtDictSchemaStreamReadDict(RtDictSchema *schema, RwStream *stream);
extern const RtDict *RtDictForAllEntries(const RtDict *dict, RtDictEntryCallBack *callBack, void *data);
extern RtDict *RtDictDestroy(RtDict *dict);
/* The database names it RtDictDestroy (0x22B450; config/aliases.txt). */
extern RtDict *RtDictSchemaCreateDict(RtDictSchema *schema);
extern RtDictEntryType RtDictAddEntry(RtDict *dict, RtDictEntryType entry);
extern RtDictEntryType RtDictFindNamedEntry(RtDict *dict, const RwChar *name);
/* The UV animation plugin's dictionary schema (rpuvanim.h's
 * RpUVAnimGetDictSchema() is &_rpUVAnimDictSchema). */
extern RtDictSchema _rpUVAnimDictSchema;

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
