/*
 * The attribute handlers' map by instance id, copied from RenderWare
 * Studio's game framework (framework/core/attributehandler/
 * cattributehandler.cpp, where it is private to that file). Only
 * cattributehandler.cpp includes this: the predicate is in an anonymous
 * namespace, so the image's template instantiations carry that file's
 * namespace hash (?A0x737baa82).
 */
#ifndef RWS_ATTRIBUTEHANDLERMAP_H
#define RWS_ATTRIBUTEHANDLERMAP_H

#include <map>

#include "rws/rwsguid.h"
#include "rws/cattributehandler.h"

namespace RWS
{
   namespace
   {
      // Predicate for attribute handler map. Allows RWSGUID type to be used
      // as the key.
      struct RWSGUIDless : std::binary_function<const RWSGUID, const RWSGUID, bool>
      {
         bool operator() (const RWSGUID x, const RWSGUID y) const
         {
            return (x) < (y);
         }
      };

      typedef std::map< RWSGUID , RWS::CAttributeHandler*, RWSGUIDless > Id2AttributeHandler_Map;
   }
}

#endif
