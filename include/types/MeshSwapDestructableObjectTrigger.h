/*
 * MeshSwapDestructableObjectTrigger (the class name it registers with the
 * class factory at 0x30A709, with its MakeNew, sub_A3A40, and its size,
 * 0x120): a destructable object (DestructableObjectTrigger) of kind 0x16
 * that swaps meshes, anchored at its vtables off_3D5D7C and off_3D5D74
 * (+0x18), which its constructor (sub_A3AC0) and destructor (sub_A3BB0)
 * install.
 */
#ifndef MESHSWAPDESTRUCTABLEOBJECTTRIGGER_H
#define MESHSWAPDESTRUCTABLEOBJECTTRIGGER_H

#include "rw/ostypes.h"
#include "types/DestructableObjectTrigger.h"

class MeshSwapDestructableObjectTrigger : public DestructableObjectTrigger
{
public:
    RWS_MAKENEWCLASS(MeshSwapDestructableObjectTrigger);
    RWS_DECLARE_CLASSID(MeshSwapDestructableObjectTrigger);

    MeshSwapDestructableObjectTrigger(const RWS::CAttributePacket &attr);
    ~MeshSwapDestructableObjectTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x16).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 0x16;
    }
    // Its child: a type_3D5400 spawned for it (sub_9B700), when its first
    // mesh's name is known.
    virtual type_3D3548 *vf_020();

    type_3DF8D8_04 unk_100;     // its meshes' names (commands 0 and 1): of
    type_3DF8D8_04 unk_108;     // the kind 3, or 0x30 with unk_110 set
    RwInt32 unk_110;            // command 2
    RwInt32 unk_114;            // command 3
    RwUInt8 unk_118[0x8];
};
typedef RwChar MeshSwapDestructableObjectTrigger_size_check[sizeof(MeshSwapDestructableObjectTrigger) == 0x120 ? 1 : -1];

#endif
