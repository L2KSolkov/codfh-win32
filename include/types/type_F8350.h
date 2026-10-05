/*
 * type_F8350: a path node. Plain data with no constructor, vtable or methods:
 * sub_F8350 reads all nodes as one buffer (dword_4C011C) from a RenderWare
 * stream and turns the offsets in the node table dword_4C0114 (count
 * dword_4C00F0) into pointers into it, so the type is named after that
 * loader. Nodes vary in size: a list of 32-bit link words starts at +0x1C,
 * or at +0x2C when flag bit 0 is set.
 *
 *   +0x00 unk_00  flags (sub_F8350 and sub_F8010 clear bits 2 and 7)
 *   +0x04 unk_04  kind: nodes of kind 0x11 are registered through sub_F7BA0
 *   +0x08 unk_08  reset to 0 by sub_F8350
 *   +0x0C unk_0C  reset to 0 by sub_F8350
 *   +0x10 unk_10  a point: sub_23B60 passes it to sub_205E0
 *   +0x1C unk_1C  an orientation, on nodes with flag bit 0 (whose links then
 *                 start 0x10 bytes later): AIData::sub_27E30 passes it to the
 *                 owner's vf_0D4, which rotates by it as a quaternion
 */
#ifndef TYPE_F8350_H
#define TYPE_F8350_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rtquat.h"

struct type_F8350
{
    union
    {
        RwUInt32 unk_00;
        RwUInt16 unk_00_w;          // the low flags as a word (the A* costs
                                    // test 0x42 in it, sub_F6750)
        struct
        {
            RwUInt32 unk_00_0 : 1;  // the links start at +0x2C
            RwUInt32 unk_00_1 : 1;
            RwUInt32 unk_00_2 : 1;  // an alarm node taken
                                    // ("SetAlarmPathNodeOccupied")
            RwUInt32 unk_00_3 : 1;
            RwUInt32 unk_00_4 : 1;  // costs half again (sub_F6750); the
                                    // A* filter sub_F6B70 passes it
            RwUInt32 unk_00_5 : 1;
            RwUInt32 unk_00_6 : 1;
            RwUInt32 unk_00_7 : 1;  // a door node's state
                                    // ("SetDoorPathNodeState")
            RwUInt32 unk_00_8 : 1;  // set on a door's linked nodes while
                                    // it is closed
            RwUInt32 unk_00_9 : 1;  // the door-offset kinds (sub_F8FE0)
            RwUInt32 unk_00_10 : 1;
            RwUInt32 unk_00_11 : 1;
            RwUInt32 unk_00_12 : 1; // a node a door's state changes
        };
    };
    RwUInt16 unk_04;
    RwUInt8 unk_06[0x2];
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwV3d unk_10;
    union
    {
        RtQuat unk_1C;
        RwUInt32 unk_1C_links[4];   // the link words, without flag bit 0
    };
    RwUInt32 unk_2C[1];     // the link words after the orientation (flag
                            // bit 0); nodes vary in size

};

#endif
