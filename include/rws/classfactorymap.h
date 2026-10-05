/*
 * The class factory's registry, copied from RenderWare Studio's game
 * framework (framework/core/attributehandler/cclassfactory.cpp, where it is
 * private to that file). Only cclassfactory.cpp includes this: its types are
 * in an anonymous namespace, so the image's template instantiations carry
 * that file's namespace hash.
 */
#ifndef RWS_CLASSFACTORYMAP_H
#define RWS_CLASSFACTORYMAP_H

#include <map>
#ifdef CODFH_WIN32
// (std::binary_function: VC7.1's <map> brings in <functional>, the port's library does not)
#include <functional>
#endif
#include <string.h>

#include "rw/ostypes.h"
#include "rws/cclassfactory.h"

namespace
{
   // Predicate for the map of class names.
   struct cstrless : std::binary_function<const RwChar*, const RwChar*, bool>
   {
      bool operator() (const RwChar* x, const RwChar* y) const
      {
         return strcmp(x, y) < 0;
      }
   };

   // What the factory knows of a registered class.
   struct SClassInfo
   {
      RWS::CClassFactory::MakeNewPtr MakeNewFunc;
      size_t size;
   };

   typedef std::map<const RwChar*, SClassInfo*, cstrless> NameToPtrMap;
}

#endif
