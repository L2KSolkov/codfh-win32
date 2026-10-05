/*
 * PathNode (the class name it registers with the class factory at
 * 0x30A856, with its MakeNew, sub_A8FC0, and its size, 0x1C): a path's
 * node, a RenderWare Studio attribute handler with no handlers of its own,
 * anchored at its vtable off_3D5F00, which its constructor (sub_A9040) and
 * destructor (sub_A90C0) install.
 */
#ifndef PATHNODE_H
#define PATHNODE_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/linearallocationpolicy.h"

class PathNode : public RWS::CAttributeHandler, public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(PathNode);
    RWS_DECLARE_CLASSID(PathNode);

    PathNode(const RWS::CAttributePacket &attr);
    ~PathNode()
    {
    }

    RwInt32 unk_18;
};
typedef RwChar PathNode_size_check[sizeof(PathNode) == 0x1C ? 1 : -1];

#endif
