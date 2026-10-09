/*
 * XBOXPadMap (the class name it registers with the class factory at
 * 0x30A7F6, with its MakeNew, sub_A6C50, and its size, 0x1C): a RenderWare
 * Studio attribute handler with no handlers of its own, anchored at its
 * vtable off_3D5EA4, which its constructor (sub_A6CD0) and destructor
 * (sub_A6D60) install.
 */
#ifndef XBOXPADMAP_H
#define XBOXPADMAP_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/linearallocationpolicy.h"

class XBOXPadMap : public RWS::CAttributeHandler, public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(XBOXPadMap);
    RWS_DECLARE_CLASSID(XBOXPadMap);

    XBOXPadMap(const RWS::CAttributePacket &attr);
    ~XBOXPadMap()
    {
    }

#ifdef CODFH_SP
    // Single player maps the pads' bindings from its attributes (SP 0x81E10; its vtable 0x2E257C has
    // HandleAttributes in slot 1) through three helpers of its own (SP 0x81D20, 0x81D60, 0x81DC0).
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    RwInt32 sp_sub_81D20(const RwChar *arg_0);
    void sp_sub_81D60(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, const RwChar *arg_C);
    void sp_sub_81DC0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
#endif

    RwInt32 unk_18;
};

typedef RwChar XBOXPadMap_size_check[sizeof(XBOXPadMap) == 0x1C ? 1 : -1];

#endif
