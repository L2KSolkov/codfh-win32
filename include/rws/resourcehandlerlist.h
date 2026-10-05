/*
 * The resource handlers' list, copied from RenderWare Studio's game
 * framework (framework/core/resourcemanager/cresourcehandler.cpp, where it is
 * private to that file). Only cresourcehandler.cpp includes this: the type is
 * in an anonymous namespace.
 */
#ifndef RWS_RESOURCEHANDLERLIST_H
#define RWS_RESOURCEHANDLERLIST_H

#include <list>

#include "rws/cresourcehandler.h"

namespace RWS
{
   namespace
   {
      typedef std::list<CResourceHandler*> CResourceHandlerList;
   }
}

#endif
