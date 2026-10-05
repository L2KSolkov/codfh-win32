/*
 * type_545C0: an animated background entity (flag unk_2C_8 of the entity),
 * named after the first command reading it, "SetAnimatedBGEntityType"
 * (sub_545C0); its vtable is not identified. Only the field that command
 * sets is known.
 */
#ifndef TYPE_545C0_H
#define TYPE_545C0_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"

struct type_3DC9B0;
struct type_10F710;

struct type_545C0 : type_3D3548
{
    // +0x234: its mounted weapon
    // ("AnimatedBGEntityMountedWeaponGetAttachedPlayer"); +0x238 and +0x23C
    // attach a player to it and detach it
    // ("AnimatedBGEntityAttachPlayerToMountedWeapon").
    virtual type_3DC9B0 *vf_234();
    virtual void vf_238(type_10F710 *arg_0);
    virtual void vf_23C();

    RwUInt8 unk_3A8[0x2C];
    RwInt32 unk_3D4;        // its type ("SetAnimatedBGEntityType"; 1 for an
                            // alarm, "GetClosestAlarmObject")

    // An inline accessor for unk_3D4, with no address and so no database
    // name; named for its field. Evidence: "GetClosestAlarmObject" compares
    // it through a compiler temporary.
    RwInt32 get_unk_3D4()
    {
        return unk_3D4;
    }
};

#endif
