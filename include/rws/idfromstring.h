/*
 * GenerateUIntIdFromString, copied from RenderWare Studio's game framework
 * (framework/core/misc/idfromstring.h): the hash the event handler keeps of
 * each message's name and format.
 */
#ifndef RWS_IDFROMSTRING_H
#define RWS_IDFROMSTRING_H

#include "rw/ostypes.h"

namespace RWS
{
   RwUInt32 GenerateUIntIdFromString(const RwChar *cptr);
}

#endif
