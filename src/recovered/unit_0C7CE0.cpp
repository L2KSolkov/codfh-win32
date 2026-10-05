// CGlobalSounds: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/data.h"
#include "types/CGlobalSounds.h"
#include "types/musicplayer.h"
#include "types/soundbank.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6CC8
extern const RwReal flt_3D6CC8 = 16.666666f;
// 0x0044D490
RwReal flt_44D490;
// 0x0044D494
RwReal flt_44D494;
// 0x0044D498
RwReal flt_44D498;
// 0x0044D4CC
RwInt32 dword_44D4CC;
// 0x0044D4D4
RwInt32 dword_44D4D4;
// 0x0044D4D8
RwInt32 dword_44D4D8;
// 0x0044E720
#ifndef CODFH_PLAIN
RwInt32 dword_44E720[8];
#endif
// 0x0044E814
RwReal flt_44E814;
// 0x0044E818
RwReal flt_44E818;
// 0x0044E81C
RwReal flt_44E81C;
// 0x0044E838
RwInt32 dword_44E838;
// 0x0044E83C
RwInt32 dword_44E83C;
// 0x0044E840
RwInt32 dword_44E840;
// 0x0044E844
RwInt32 dword_44E844;
// 0x0044E848
RwInt32 dword_44E848;
// 0x0044E84C
RwInt32 dword_44E84C;
// 0x0044E850
RwInt32 dword_44E850;
// 0x0044E854
RwInt32 dword_44E854;
// 0x0044E858
RwInt32 dword_44E858;
// 0x0044E85C
RwInt32 dword_44E85C;
// 0x0044E860
RwInt32 dword_44E860;
// 0x0044E864
RwInt32 dword_44E864;
// 0x0044E868
RwInt32 dword_44E868;
// 0x0044E86C
RwInt32 dword_44E86C;
// 0x0044E874
RwInt32 dword_44E874;
// 0x004B1C68
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B1C68;
#endif
// 0x004B1C70
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B1C70;
#endif
// 0x004B1F2C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B1F2C;
#endif
// 0x004B1F34
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B1F34;
#endif
// End of its data definitions.

// match: _$E2 @ 0x0030AF30
// match: _$E3 @ 0x0030E2E0

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@GOMAJMCL@CGlobalSounds?$AA@ @ 0x003D6CB8
// match: ?flt_3D6CC8@@3MB @ 0x003D6CC8
// match: ??_7CGlobalSounds@@6BCEventHandler@RWS@@@ @ 0x003D6CCC
// match: ??_7CGlobalSounds@@6BCAttributeHandler@RWS@@@ @ 0x003D6CD4
// match: __ehhandler$?MakeNew@CGlobalSounds@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C878
// match: __ehhandler$?MakeNew@CGlobalSounds@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C880
// match: __ehhandler$??0CGlobalSounds@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C89C
// match: __ehhandler$??0CGlobalSounds@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C8AC
// match: __ehhandler$??1CGlobalSounds@@UAE@XZ>1>8 @ 0x0041C8C8
// match: __ehhandler$??1CGlobalSounds@@UAE@XZ>1 @ 0x0041C8D8
// match: .CRT$XCU+0 @ 0x00426FC0
// match: ?pCGlobalSoundsClassID@CGlobalSounds@@2PBDB @ 0x00429210

RWS_IMPLEMENT_CLASSID(CGlobalSounds);
RWS_REGISTERCLASS(CGlobalSounds);
// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CGlobalSounds@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C7CE0
// match: __ehhandler$?MakeNew@CGlobalSounds@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300900
// match: __ehhandler$?MakeNew@CGlobalSounds@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030090F
RWS_DEFINE_MAKENEW(CGlobalSounds)

// match: ??0CGlobalSounds@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C7D60
// match: __ehhandler$??0CGlobalSounds@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x00300920
// match: __ehhandler$??0CGlobalSounds@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300933
CGlobalSounds::CGlobalSounds(const RWS::CAttributePacket &attr)
{
    LinkMsg(iMsgSparkStartSystem, 0, 0x8000);
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GCGlobalSounds@@UAEPAXI@Z @ 0x000C7E80

// match: ??1CGlobalSounds@@UAE@XZ @ 0x000C7EA0
// match: __ehhandler$??1CGlobalSounds@@UAE@XZ-0x2F @ 0x00300940
// match: __ehhandler$??1CGlobalSounds@@UAE@XZ @ 0x0030096F
CGlobalSounds::~CGlobalSounds()
{
    UnLinkMsg(iMsgSparkStartSystem);
    UnLinkMsg(RWS::iMsgStartSystem);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// match: ?HandleAttributes@CGlobalSounds@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C7F60
void CGlobalSounds::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CGlobalSounds));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B30 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 1:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C60[0] = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 2:
            if (attrIt->GetAs_RwChar_ptr())
            {
                *(type_3DF8D8_04 *)&dword_4B1C68 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 3:
            if (attrIt->GetAs_RwChar_ptr())
            {
                *(type_3DF8D8_04 *)&dword_4B1C70 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 4:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C08 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 5:
            flt_44E808 = attrIt->GetAs_RwReal();
            break;
        case 6:
            flt_44E5E8 = attrIt->GetAs_RwReal();
            break;
        case 18:
            flt_44D4D0 = attrIt->GetAs_RwReal();
            break;
        case 19:
            flt_44D4BC = attrIt->GetAs_RwReal();
            break;
        case 7:
            flt_44D4A0 = attrIt->GetAs_RwReal();
            break;
        case 8:
            flt_44E824 = attrIt->GetAs_RwReal();
            break;
        case 9:
            flt_44D488 = attrIt->GetAs_RwReal();
            break;
        case 10:
            flt_44E810 = attrIt->GetAs_RwReal();
            break;
        case 11:
            flt_44E80C = attrIt->GetAs_RwReal();
            break;
        case 12:
            flt_44E800 = attrIt->GetAs_RwReal();
            break;
        case 13:
            flt_44E828 = attrIt->GetAs_RwReal();
            break;
        case 164:
            flt_428E28 = attrIt->GetAs_RwReal() * 60.0f;
            flt_4AEFF4 = flt_428E28;
            break;
        case 26:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C98 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 27:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B48 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 28:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C88 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 29:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C00 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 54:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C50 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 55:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C78 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 56:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1E88 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 37:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AEFEC = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 38:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C40 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 39:
            dword_44D4D4 = attrIt->GetAs_RwInt32();
            break;
        case 40:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F3C = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 41:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF010 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 42:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F4C = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 43:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B58 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 44:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C90 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 45:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 51:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B38 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 52:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1E90 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 53:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF030 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 57:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C80 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 58:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 59:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF018 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 60:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF000 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 61:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B40 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 62:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF020 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 63:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B28 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 64:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AEFF8 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 65:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B10 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 30:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1E80 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 36:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C48 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 31:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B50 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 32:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C38 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 33:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1B20 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 34:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F1C = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 35:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF008 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 46:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F44 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 47:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C10 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 48:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4AF028 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 49:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1C58 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 50:
            if (attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1A18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 66:
            dword_44E600[0].unk_00[0] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 67:
            dword_44E600[0].unk_00[1] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 68:
            dword_44E600[0].unk_00[2] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 69:
            dword_44E600[0].unk_00[3] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 70:
            dword_44E600[0].unk_00[4] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 71:
            dword_44E600[0].unk_00[5] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 72:
            dword_44E600[0].unk_00[6] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 73:
            dword_44E600[0].unk_00[7] = attrIt->GetAs_RwInt32();
            dword_44E600[1].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 74:
            dword_44E600[2].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 75:
            dword_44E600[2].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 76:
            dword_44E600[2].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 77:
            dword_44E600[2].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 78:
            dword_44E600[2].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 79:
            dword_44E600[2].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 80:
            dword_44E600[2].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 81:
            dword_44E600[2].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 82:
            dword_44E600[3].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 83:
            dword_44E600[3].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 84:
            dword_44E600[3].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 85:
            dword_44E600[3].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 86:
            dword_44E600[3].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 87:
            dword_44E600[3].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 88:
            dword_44E600[3].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 89:
            dword_44E600[3].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 90:
            dword_44E600[4].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 91:
            dword_44E600[4].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 92:
            dword_44E600[4].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 93:
            dword_44E600[4].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 94:
            dword_44E600[4].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 95:
            dword_44E600[4].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 96:
            dword_44E600[4].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 97:
            dword_44E600[4].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 98:
            dword_44E600[9].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 99:
            dword_44E600[9].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 100:
            dword_44E600[9].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 101:
            dword_44E600[9].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 102:
            dword_44E600[9].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 103:
            dword_44E600[9].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 104:
            dword_44E600[9].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 105:
            dword_44E600[9].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 106:
            dword_44E600[5].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 107:
            dword_44E600[5].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 108:
            dword_44E600[5].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 109:
            dword_44E600[5].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 110:
            dword_44E600[5].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 111:
            dword_44E600[5].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 112:
            dword_44E600[5].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 113:
            dword_44E600[5].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 114:
            dword_44E600[7].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 115:
            dword_44E600[7].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 116:
            dword_44E600[7].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 117:
            dword_44E600[7].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 118:
            dword_44E600[7].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 119:
            dword_44E600[7].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 120:
            dword_44E600[7].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 121:
            dword_44E600[7].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 122:
            dword_44E600[8].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 123:
            dword_44E600[8].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 124:
            dword_44E600[8].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 125:
            dword_44E600[8].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 126:
            dword_44E600[8].unk_00[4] = attrIt->GetAs_RwInt32();
            break;
        case 127:
            dword_44E600[8].unk_00[5] = attrIt->GetAs_RwInt32();
            break;
        case 128:
            dword_44E600[8].unk_00[6] = attrIt->GetAs_RwInt32();
            break;
        case 129:
            dword_44E600[8].unk_00[7] = attrIt->GetAs_RwInt32();
            break;
        case 130:
            dword_44D4D8 = attrIt->GetAs_RwInt32();
            break;
        case 131:
            dword_44D4CC = attrIt->GetAs_RwInt32();
            break;
        case 14:
            flt_44C0A4 = 1.0f / attrIt->GetAs_RwInt32();
            break;
        case 15:
            flt_44D4B0 = 1.0f / attrIt->GetAs_RwInt32();
            break;
        case 16:
            flt_44C0A0 = 1.0f / attrIt->GetAs_RwInt32();
            break;
        case 17:
            flt_44D4B8 = 1.0f / attrIt->GetAs_RwInt32();
            break;
        case 132:
            attrIt->GetCommandData(dword_44E838);
            break;
        case 133:
            attrIt->GetCommandData(dword_44E83C);
            break;
        case 134:
            attrIt->GetCommandData(dword_44E840);
            break;
        case 135:
            attrIt->GetCommandData(dword_44E844);
            break;
        case 136:
            attrIt->GetCommandData(dword_44E848);
            break;
        case 137:
            attrIt->GetCommandData(dword_44E84C);
            break;
        case 138:
            attrIt->GetCommandData(dword_44E850);
            break;
        case 139:
            attrIt->GetCommandData(dword_44E854);
            break;
        case 140:
            attrIt->GetCommandData(dword_44E858);
            break;
        case 141:
            attrIt->GetCommandData(dword_44E85C);
            break;
        case 142:
            attrIt->GetCommandData(dword_44E5F0[0]);
            break;
        case 143:
            attrIt->GetCommandData(dword_44E5F0[1]);
            break;
        case 144:
            attrIt->GetCommandData(dword_44E5F0[2]);
            break;
        case 145:
            attrIt->GetCommandData(dword_44E860);
            break;
        case 146:
            attrIt->GetCommandData(dword_44E864);
            break;
        case 147:
            attrIt->GetCommandData(dword_44E868);
            break;
        case 148:
            attrIt->GetCommandData(dword_44E86C);
            break;
        case 149:
            attrIt->GetCommandData(dword_44E870);
            break;
        case 150:
            attrIt->GetCommandData(dword_44E874);
            break;
        case 155:
            if (*(const RwInt32 *)attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F24[0].unk_00 = *(const RwUInt32 *)attrIt->GetAs_RwChar_ptr();
                dword_4B1F24[0].unk_04 = ((const RwUInt32 *)attrIt->GetAs_RwChar_ptr())[1];
            }
            break;
        case 156:
            if (*(const RwInt32 *)attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F2C.unk_00 = *(const RwUInt32 *)attrIt->GetAs_RwChar_ptr();
                dword_4B1F2C.unk_04 = ((const RwUInt32 *)attrIt->GetAs_RwChar_ptr())[1];
            }
            break;
        case 157:
            if (*(const RwInt32 *)attrIt->GetAs_RwChar_ptr())
            {
                dword_4B1F34.unk_00 = *(const RwUInt32 *)attrIt->GetAs_RwChar_ptr();
                dword_4B1F34.unk_04 = ((const RwUInt32 *)attrIt->GetAs_RwChar_ptr())[1];
            }
            break;
        case 158:
            flt_44D490 = attrIt->GetAs_RwReal();
            flt_44D490 = flt_44D490 / 1000.0f * 60.0f;
            break;
        case 159:
            flt_44D494 = attrIt->GetAs_RwReal();
            flt_44D494 = flt_44D494 / 1000.0f * 60.0f;
            break;
        case 160:
            flt_44D498 = attrIt->GetAs_RwReal();
            flt_44D498 = flt_44D498 / 1000.0f * 60.0f;
            break;
        case 161:
            flt_44E814 = attrIt->GetAs_RwReal() / 100.0f;
            break;
        case 162:
            flt_44E818 = attrIt->GetAs_RwReal() / 100.0f;
            break;
        case 163:
            flt_44E81C = attrIt->GetAs_RwReal() / 100.0f;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@CGlobalSounds@@UAEXAAVCMsg@RWS@@@Z @ 0x000CA250
void CGlobalSounds::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
    }
    else if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec)
    {
        sub_83B20();
        UnLinkMsg(iMsgSparkStartSystem);
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        sub_83B20();
    }
}

// match: ??_ECGlobalSounds@@WBI@AEPAXI@Z @ 0x000CA2B0
