// XBOXPadMap: its MakeNew, constructor and destructor. Its original file name
// is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/XBOXPadMap.h"
#ifdef CODFH_SP
#include "rw/badevice.h"
#include "game/levels.h"
#include "game/gameloop.h"   // dword_429498, the input events (unit_0EE540)
#endif

RWS_IMPLEMENT_CLASSID(XBOXPadMap);
RWS_REGISTERCLASS(XBOXPadMap);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@MIDJDNIO@XBOXPadMap?$AA@ @ 0x003D5E98
// match: ??_7XBOXPadMap@@6B@ @ 0x003D5EA4
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BD40
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BD48
// match: .CRT$XCU+0 @ 0x00426F24
// match: ?pXBOXPadMapClassID@XBOXPadMap@@2PBDB @ 0x00429168

// match: _$E2 @ 0x0030A7E0
// match: _$E3 @ 0x0030E070

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A6C50
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFFD0
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFFDF
// sp-match: ?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00082390
RWS_DEFINE_MAKENEW(XBOXPadMap)

// match: ??0XBOXPadMap@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A6CD0
// sp-match: ??0XBOXPadMap@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00081CF0
XBOXPadMap::XBOXPadMap(const RWS::CAttributePacket &attr)
{
    unk_18 = 0;
}

// match: ??_GXBOXPadMap@@UAEPAXI@Z @ 0x000A6D40
// sp-match: ??_GXBOXPadMap@@UAEPAXI@Z @ 0x00081E00

// match: ??1XBOXPadMap@@UAE@XZ @ 0x000A6D60
// sp-match: ??1XBOXPadMap@@UAE@XZ @ 0x00081D10
// (Defined in the class, in XBOXPadMap.h.)

#ifdef CODFH_SP
RwInt32 sp_sub_12D360(type_42B740 *arg_0, RwInt32 arg_4, RwInt32 arg_8);

// The binding named arg_0's index, -1 when there is none: the input events' names (dword_429498,
// SP .data 0x3219D8; the names from SP 0x3219E0) up to the 40th.
// sp-match: ?sp_sub_81D20@XBOXPadMap@@QAEHPBD@Z @ 0x00081D20
RwInt32 XBOXPadMap::sp_sub_81D20(const RwChar *arg_0)
{
    for (RwInt32 i = 0; i < 40; i++)
    {
        if (rwstrcmp(dword_429498[i].unk_08, arg_0) == 0)
        {
            return i;
        }
    }
    return -1;
}
#endif

#ifdef CODFH_SP
// Binds arg_8 (40: none) to the input arg_0 of pad map arg_4; only the map's
// first entry is looked at.
// sp-match: ?sp_sub_81D60@XBOXPadMap@@QAEXHHHPBD@Z @ 0x00081D60
void XBOXPadMap::sp_sub_81D60(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, const RwChar *arg_C)
{
    if (arg_8 != -1)
    {
        type_42B740 *p = sub_19B1E0(arg_4);
        RwInt32 done = 0;
        for (; p->unk_00 != -1 && !done; p++)
        {
            if (p->unk_00 == arg_0)
            {
                if (arg_8 == 0x28)
                {
                    sp_sub_12D360(p, -1, 1);
                }
                else
                {
                    sp_sub_12D360(p, arg_8, 1);
                }
            }
            done = 1;
        }
    }
}
#endif

#ifdef CODFH_SP
// Sets the input arg_0's setting in pad map arg_4.
// sp-match: ?sp_sub_81DC0@XBOXPadMap@@QAEXHHH@Z @ 0x00081DC0
void XBOXPadMap::sp_sub_81DC0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    for (type_42B740 *p = sub_19B1E0(arg_4); p->unk_00 != -1; p++)
    {
        if (p->unk_00 == arg_0)
        {
            p->unk_1C = arg_8;
        }
    }
}
#endif

#ifdef CODFH_SP
// Command 0: the pad map; 1 to 4: settings 0x10 to 0x13; 5 to 24: the
// bindings 0 to 0x13, by name.
// sp-match: ?HandleAttributes@XBOXPadMap@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00081E10
void XBOXPadMap::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(XBOXPadMap));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_18 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            sp_sub_81D60(0, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 6:
            sp_sub_81D60(1, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 7:
            sp_sub_81D60(2, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 8:
            sp_sub_81D60(3, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 9:
            sp_sub_81D60(4, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 10:
            sp_sub_81D60(5, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 11:
            sp_sub_81D60(6, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 12:
            sp_sub_81D60(7, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 13:
            sp_sub_81D60(8, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 14:
            sp_sub_81D60(9, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 15:
            sp_sub_81D60(0xa, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 16:
            sp_sub_81D60(0xb, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 17:
            sp_sub_81D60(0xc, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 18:
            sp_sub_81D60(0xd, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 19:
            sp_sub_81D60(0xe, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 20:
            sp_sub_81D60(0xf, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 21:
            sp_sub_81D60(0x10, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 22:
            sp_sub_81D60(0x11, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 23:
            sp_sub_81D60(0x12, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 24:
            sp_sub_81D60(0x13, unk_18, sp_sub_81D20(attrIt->GetAs_RwChar_ptr()), attrIt->GetAs_RwChar_ptr());
            break;
        case 1:
            sp_sub_81DC0(0x10, unk_18, attrIt->GetAs_RwInt32());
            break;
        case 2:
            sp_sub_81DC0(0x11, unk_18, attrIt->GetAs_RwInt32());
            break;
        case 3:
            sp_sub_81DC0(0x12, unk_18, attrIt->GetAs_RwInt32());
            break;
        case 4:
            sp_sub_81DC0(0x13, unk_18, attrIt->GetAs_RwInt32());
            break;
        }
        ++attrIt;
    }
}
#endif
