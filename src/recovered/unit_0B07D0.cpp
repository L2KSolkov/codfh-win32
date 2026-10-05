// CShellBehaviorClass: its MakeNew, constructor, destructor and
// HandleAttributes. Its original file name is not in the image, so it is
// named for its start address.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/helpmessages.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "game/objectives.h"
#include "game/savestate.h"
#include "game/textmanager.h"
#include "game/waitscreen.h"
#include "types/CShellBehaviorClass.h"
#include "types/EndLevelTrigger.h"
#include "types/type_3DAFC8.h"
#include "types/type_72810.h"
#include "types/type_DC400.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D644C
extern const RwReal flt_3D644C = 16.666666f;
// 0x003D6450
extern const RwReal flt_3D6450 = 0.01f;
// 0x003D6454
extern const RwReal flt_3D6454 = 1.0f;
// 0x004B8F0C
#ifndef CODFH_PLAIN
RwReal flt_4B8F0C;
#endif
// 0x004B8F10
#ifndef CODFH_PLAIN
RwReal flt_4B8F10;
#endif
// 0x004B8F20
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F20;
#endif
// 0x004B8F24
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F24;
#endif
// 0x004B8F2C
#ifndef CODFH_PLAIN
RwReal flt_4B8F2C;
#endif
// 0x004B8F3C
#ifndef CODFH_PLAIN
RwInt32 dword_4B8F3C;
#endif
// 0x004B8F40
#ifndef CODFH_PLAIN
RwInt32 dword_4B8F40;
#endif
// 0x004B8F44
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F44;
#endif
// 0x004B8F48
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F48;
#endif
// 0x004B8F4C
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F4C;
#endif
// 0x004B8F50
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F50;
#endif
// 0x004B8F54
#ifndef CODFH_PLAIN
RwV2d dword_4B8F54;
#endif
// 0x004B8F5C
#ifndef CODFH_PLAIN
RwInt32 dword_4B8F5C;
#endif
// 0x004B8F60
#ifndef CODFH_PLAIN
RwInt32 dword_4B8F60;
#endif
// 0x004B8F64
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F64;
#endif
// 0x004B8F68
#ifndef CODFH_PLAIN
RwV2d dword_4B8F68;
#endif
// 0x004B8F70
#ifndef CODFH_PLAIN
RwV3d dword_4B8F70;
#endif
// 0x004B8F7C
#ifndef CODFH_PLAIN
RwReal flt_4B8F7C;
#endif
// 0x004B8F80
#ifndef CODFH_PLAIN
RwReal dword_4B8F80;
#endif
// 0x004B8F84
#ifndef CODFH_PLAIN
RwReal dword_4B8F84;
#endif
// 0x004B8F88
#ifndef CODFH_PLAIN
RwV2d dword_4B8F88;
#endif
// 0x004B8F90
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8F90;
#endif
// 0x004B8F98
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F98;
#endif
// 0x004B8F9C
#ifndef CODFH_PLAIN
RwRGBA dword_4B8F9C;
#endif
// 0x004B8FA0
#ifndef CODFH_PLAIN
RwReal dword_4B8FA0;
#endif
// 0x004B8FA4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FA4;
#endif
// 0x004B8FAC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FAC;
#endif
// 0x004B8FB4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FB4;
#endif
// 0x004B8FBC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FBC;
#endif
// 0x004B8FC4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FC4;
#endif
// 0x004B8FCC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FCC;
#endif
// 0x004B8FD4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FD4;
#endif
// 0x004B8FDC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FDC;
#endif
// 0x004B8FE4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FE4;
#endif
// 0x004B8FEC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FEC;
#endif
// 0x004B8FF4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FF4;
#endif
// 0x004B8FFC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B8FFC;
#endif
// 0x004B9004
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9004;
#endif
// 0x004B900C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B900C;
#endif
// 0x004B9014
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9014;
#endif
// 0x004B901C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B901C;
#endif
// 0x004B9024
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9024;
#endif
// 0x004B902C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B902C;
#endif
// 0x004B9034
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9034;
#endif
// 0x004B903C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B903C;
#endif
// 0x004B9044
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9044;
#endif
// 0x004B904C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B904C;
#endif
// 0x004B9054
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9054;
#endif
// 0x004B905C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B905C;
#endif
// 0x004B9064
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9064;
#endif
// 0x004B906C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B906C;
#endif
// 0x004B9074
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9074;
#endif
// 0x004B907C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B907C;
#endif
// 0x004B9084
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9084;
#endif
// 0x004B908C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B908C;
#endif
// 0x004B9094
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9094;
#endif
// 0x004B909C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B909C;
#endif
// 0x004B90A4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90A4;
#endif
// 0x004B90AC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90AC;
#endif
// 0x004B90B4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90B4;
#endif
// 0x004B90BC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90BC;
#endif
// 0x004B90C4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90C4;
#endif
// 0x004B90CC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90CC;
#endif
// 0x004B90D4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90D4;
#endif
// 0x004B90DC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90DC;
#endif
// 0x004B90E4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90E4;
#endif
// 0x004B90EC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90EC;
#endif
// 0x004B90F4
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90F4;
#endif
// 0x004B90FC
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B90FC;
#endif
// 0x004B9104
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9104;
#endif
// 0x004B910C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B910C;
#endif
// 0x004B9114
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9114;
#endif
// 0x004B911C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B911C;
#endif
// 0x004B9124
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9124;
#endif
// 0x004B912C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B912C;
#endif
// 0x004B9134
#ifndef CODFH_PLAIN
type_3DF8D8_04_data unk_4B9134;
#endif
// 0x004B913C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B913C;
#endif
// 0x004B9144
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B9144;
#endif
// 0x004B914C
#ifndef CODFH_PLAIN
type_3DF8D8_04_data dword_4B914C;
#endif
// 0x004B9154
#ifndef CODFH_PLAIN
RwReal dword_4B9154;
#endif
// 0x004B9158
#ifndef CODFH_PLAIN
RwReal dword_4B9158;
#endif
// 0x004B915C
#ifndef CODFH_PLAIN
RwReal flt_4B915C;
#endif
// 0x004B9160
#ifndef CODFH_PLAIN
RwReal flt_4B9160;
#endif
// 0x004B9164
#ifndef CODFH_PLAIN
RwReal flt_4B9164;
#endif
// 0x004B9168
#ifndef CODFH_PLAIN
RwReal flt_4B9168;
#endif
// 0x004B916C
#ifndef CODFH_PLAIN
RwInt32 dword_4B916C;
#endif
// 0x004B9170
#ifndef CODFH_PLAIN
RwInt32 dword_4B9170;
#endif
// 0x004B9174
#ifndef CODFH_PLAIN
RwV2d dword_4B9174;
#endif
// 0x004B917C
#ifndef CODFH_PLAIN
RwRGBAReal unk_4B917C;
#endif
// End of its data definitions.



RWS_IMPLEMENT_CLASSID(CShellBehaviorClass);
RWS_REGISTERCLASS(CShellBehaviorClass);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BE@IILIBEN@CShellBehaviorClass?$AA@ @ 0x003D6438
// match: ?flt_3D644C@@3MB @ 0x003D644C
// match: ?flt_3D6450@@3MB @ 0x003D6450
// match: ?flt_3D6454@@3MB @ 0x003D6454
// match: ??_7CShellBehaviorClass@@6BCEventHandler@RWS@@@ @ 0x003D6458
// match: ??_7CShellBehaviorClass@@6BCAttributeHandler@RWS@@@ @ 0x003D6460
// match: __real@3b808081 @ 0x003D6468
// match: __real@43f00000 @ 0x003D646C
// match: __real@44200000 @ 0x003D6470
// match: __ehhandler$?MakeNew@CShellBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C044
// match: __ehhandler$?MakeNew@CShellBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C04C
// match: __ehhandler$??1CShellBehaviorClass@@UAE@XZ>1>8 @ 0x0041C068
// match: __ehhandler$??1CShellBehaviorClass@@UAE@XZ>1 @ 0x0041C070
// match: .CRT$XCU+0 @ 0x00426F54
// match: ?pCShellBehaviorClassClassID@CShellBehaviorClass@@2PBDB @ 0x004291A4

// match: _$E2 @ 0x0030AA20
// match: _$E3 @ 0x0030E130

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CShellBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B07D0
// match: __ehhandler$?MakeNew@CShellBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300250
// match: __ehhandler$?MakeNew@CShellBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030025F
RWS_DEFINE_MAKENEW(CShellBehaviorClass)

// match: ??0CShellBehaviorClass@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B0850
CShellBehaviorClass::CShellBehaviorClass(const RWS::CAttributePacket &attr)
{
}

// match: ??_GCShellBehaviorClass@@UAEPAXI@Z @ 0x000B08E0

// match: ??1CShellBehaviorClass@@UAE@XZ @ 0x000B0900
// match: __ehhandler$??1CShellBehaviorClass@@UAE@XZ-0x8 @ 0x00300270
// match: __ehhandler$??1CShellBehaviorClass@@UAE@XZ @ 0x00300278
// (Defined in the class, in CShellBehaviorClass.h.)

// match: ??_ECShellBehaviorClass@@WBI@AEPAXI@Z @ 0x000B6EA0

// match: ?HandleAttributes@CShellBehaviorClass@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B0980
void CShellBehaviorClass::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 loc50;
    RwInt32 x4C;
    RwV3d w48;
    const RwChar *ebp_3C;
    RwUInt32 lcl_38;
    RwRGBA r34;
    RwV2d lv_30;
    RwReal q28;
    RwReal frm_24;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwRGBAReal lv_10;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator loc20(attr, RWS_CLASSID_OF(CShellBehaviorClass));

    while (!loc20.IsFinished())
    {
        switch (loc20->GetCommandId())
        {
            case 0:
                if (dword_4B9190)
                {
                    ebp_3C = loc20->GetAs_RwChar_ptr();
                    dword_4B9190->sub_E52B0(ebp_3C);
                }
                break;
            case 1:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[3].unk_00.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[3].unk_00.y = (RwUInt32)Height * w48.y;
                    dword_4B9190->sub_E7050(0x4, dword_4B9190->unk_14[3].unk_00.x, dword_4B9190->unk_14[3].unk_00.y);
                }
                break;
            case 2:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[3].unk_08.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[3].unk_08.y = (RwUInt32)Height * w48.y;
                }
                break;
            case 3:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x5, &lv_30);
                break;
            case 4:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x6, &lv_30);
                break;
            case 5:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x6, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 6:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->sub_E7200(0x6, r34.red, r34.green, r34.blue, r34.alpha);
                break;
            case 7:
                loc20->GetCommandData(dword_4B9190->unk_E0[6].unk_1E8);
                break;
            case 9:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x8, &lv_30);
                break;
            case 10:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x8, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 11:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x9, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 12:
            {
                RwReal lv_54;

                loc20->GetCommandData(lv_54);
                dword_4B9158 = lv_54;
                break;
            }
            case 13:
            {
                RwReal slot_58;

                loc20->GetCommandData(slot_58);
                flt_4B915C = slot_58 * 60.0f;
                break;
            }
            case 14:
            {
                RwReal y5C;

                loc20->GetCommandData(y5C);
                flt_4B9160 = y5C * 60.0f;
                break;
            }
            case 15:
            {
                RwReal stk_60;

                loc20->GetCommandData(stk_60);
                flt_4B9164 = stk_60 * stk_60;
                break;
            }
            case 16:
            {
                RwReal var_64;

                loc20->GetCommandData(var_64);
                flt_4B9168 = var_64 * var_64;
                break;
            }
            case 207:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x94, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 208:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x95, &lv_30);
                break;
            case 209:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x96, &lv_30);
                break;
            case 210:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x96, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 211:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->sub_E7200(0x96, r34.red, r34.green, r34.blue, r34.alpha);
                break;
            case 212:
                loc20->GetCommandData(dword_4B9190->unk_E0[150].unk_1E8);
                break;
            case 213:
                loc20->GetCommandData(q28);
                if (dword_4B9190)
                    dword_4B9190->sub_E5F60(0x94, q28);
                break;
            case 215:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x42, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 216:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x43, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 217:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x44, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 219:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x45, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 220:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x46, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 221:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x47, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 222:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x48, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 223:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x4A, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 224:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x4B, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x4C, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 225:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x4D, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 226:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x4F, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 227:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x50, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x51, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 229:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x52, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 230:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x53, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 228:
                loc20->GetCommandData(frm_24);
                if (dword_4B9190)
                    dword_4B9190->unk_5C = frm_24;
                break;
            case 231:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_60[0] = r34;
                    dword_4B9190->unk_60[1] = r34;
                }
                break;
            case 232:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->unk_60[2] = r34;
                break;
            case 233:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->unk_60[3] = r34;
                break;
            case 234:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->unk_60[4] = r34;
                break;
            case 235:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_74 = r34;
                    dword_4B9190->unk_78 = r34;
                }
                break;
            case 240:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x58, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 241:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x59, (RwUInt32)Width * w48.x * flt_3D6454, (RwUInt32)Height * w48.y);
                }
                break;
            case 218:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x54, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 236:
                loc20->GetCommandData(frm_24);
                if (dword_4B9190)
                    dword_4B9190->sub_E7050(0x56, 0, (RwUInt32)Height * frm_24);
                break;
            case 238:
                loc20->GetCommandData(frm_24);
                if (dword_4B9190)
                    dword_4B9190->sub_E7050(0x57, 0, (RwUInt32)Height * frm_24);
                break;
            case 237:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->sub_E75D0(0x56, r34);
                break;
            case 239:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->sub_E75D0(0x57, r34);
                break;
            case 17:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x1D, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 18:
                loc20->GetCommandData(frm_24);
                lv_30.x = lv_30.y = frm_24;
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E74D0(0x1F, &lv_30);
                    dword_4B9190->sub_E74D0(0x1E, &lv_30);
                }
                break;
            case 19:
                loc20->GetCommandData(frm_24);
                lv_30.x = lv_30.y = frm_24;
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E74D0(0x20, &lv_30);
                    dword_4B9190->sub_E74D0(0x21, &lv_30);
                    dword_4B9190->sub_E74D0(0x31, &lv_30);
                    dword_4B9190->sub_E74D0(0x32, &lv_30);
                    dword_4B9190->sub_E74D0(0x33, &lv_30);
                    dword_4B9190->sub_E74D0(0x34, &lv_30);
                    dword_4B9190->sub_E74D0(0x35, &lv_30);
                    dword_4B9190->sub_E74D0(0x36, &lv_30);
                    dword_4B9190->sub_E74D0(0x37, &lv_30);
                    dword_4B9190->sub_E74D0(0x38, &lv_30);
                    dword_4B9190->sub_E74D0(0x39, &lv_30);
                    dword_4B9190->sub_E74D0(0x3A, &lv_30);
                    dword_4B9190->sub_E74D0(0x3B, &lv_30);
                    dword_4B9190->sub_E74D0(0x3C, &lv_30);
                    dword_4B9190->sub_E74D0(0x3D, &lv_30);
                    dword_4B9190->sub_E74D0(0x3E, &lv_30);
                    dword_4B9190->sub_E74D0(0x3F, &lv_30);
                    dword_4B9190->sub_E74D0(0x40, &lv_30);
                }
                break;
            case 20:
                loc20->GetCommandData(frm_24);
                lv_30.x = lv_30.y = frm_24;
                if (dword_4B9190)
                {
                    for (RwInt32 q68 = 0; q68 < 15; q68++)
                    {
                        dword_4B9190->sub_E74D0(q68 + 0x22, &lv_30);
                    }
                }
                break;
            case 21:
                loc20->GetCommandData(ebp_14);
                if (dword_4B9190)
                    dword_4B9190->sub_E3DB0(&dword_4B9190->unk_E0[31], ebp_14);
                break;
            case 22:
                loc20->GetCommandData(ebp_14);
                if (dword_4B9190)
                    dword_4B9190->sub_E3DB0(&dword_4B9190->unk_E0[30], ebp_14);
                break;
            case 23:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_54 = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_58 = (RwUInt32)Height * w48.y;
                    dword_4B9190->sub_E7050(0x5A, dword_4B9190->unk_54, dword_4B9190->unk_58);
                    dword_4B9190->sub_E7050(0x8A, dword_4B9190->unk_54, dword_4B9190->unk_58);
                }
                break;
            case 24:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E74D0(0x5B, &lv_30);
                    dword_4B9190->sub_E74D0(0x5E, &lv_30);
                    dword_4B9190->sub_E74D0(0x5C, &lv_30);
                    dword_4B9190->sub_E74D0(0x5D, &lv_30);
                }
                break;
            case 29:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x5F, &lv_30);
                break;
            case 30:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x60, &lv_30);
                break;
            case 26:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F20 = r34;
                break;
            case 27:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F24 = r34;
                break;
            case 28:
                loc20->GetCommandData(flt_4B8F2C);
                flt_4B8F2C = flt_4B8F2C * 100.0f;
                break;
            case 31:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[0].unk_00.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[0].unk_00.y = (RwUInt32)Height * w48.y;
                    dword_4B9190->sub_E7050(0xE, dword_4B9190->unk_14[0].unk_00.x, dword_4B9190->unk_14[0].unk_00.y);
                }
                break;
            case 32:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[0].unk_08.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[0].unk_08.y = (RwUInt32)Height * w48.y;
                }
                break;
            case 33:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x13, &lv_30);
                break;
            case 34:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[1].unk_00.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[1].unk_00.y = (RwUInt32)Height * w48.y;
                    dword_4B9190->sub_E7050(0xF, dword_4B9190->unk_14[1].unk_00.x, dword_4B9190->unk_14[1].unk_00.y);
                }
                break;
            case 35:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[1].unk_08.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[1].unk_08.y = (RwUInt32)Height * w48.y;
                }
                break;
            case 36:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x11, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 37:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[2].unk_00.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[2].unk_00.y = (RwUInt32)Height * w48.y;
                    dword_4B9190->sub_E7050(0x10, dword_4B9190->unk_14[2].unk_00.x, dword_4B9190->unk_14[2].unk_00.y);
                }
                break;
            case 38:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->unk_14[2].unk_08.x = (RwUInt32)Width * w48.x;
                    dword_4B9190->unk_14[2].unk_08.y = (RwUInt32)Height * w48.y;
                }
                break;
            case 39:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x12, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 40:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x14, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 41:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x1C, &lv_30);
                break;
            case 42:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x15, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x16, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x17, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x19, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x1A, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7050(0x18, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 43:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E74D0(0x15, &lv_30);
                    dword_4B9190->sub_E74D0(0x16, &lv_30);
                    dword_4B9190->sub_E74D0(0x17, &lv_30);
                    dword_4B9190->sub_E74D0(0x19, &lv_30);
                    dword_4B9190->sub_E74D0(0x1A, &lv_30);
                    dword_4B9190->sub_E74D0(0x18, &lv_30);
                }
                break;
            case 44:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x1B, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 45:
                m_18 = 0;
                loc20->GetCommandData(m_18);
                break;
            case 46:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0xA, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 47:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0xB, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 48:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0xC, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 49:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0xD, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 50:
                if (dword_4B9190)
                    loc20->GetCommandData(dword_4B9190->unk_1A14C);
                break;
            case 51:
                if (dword_4B9190)
                    loc20->GetCommandData(dword_4B9190->unk_1A154);
                break;
            case 52:
                if (dword_4B9190)
                {
                    loc20->GetCommandData(dword_4B9190->unk_E0[11].unk_1E8);
                    loc20->GetCommandData(dword_4B9190->unk_E0[13].unk_1E8);
                    loc20->GetCommandData(dword_4B9190->unk_E0[12].unk_1E8);
                }
                break;
            case 53:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x7A, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 54:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E74D0(0x7C, &lv_30);
                    dword_4B9190->sub_E74D0(0x7D, &lv_30);
                    dword_4B9190->sub_E74D0(0x7E, &lv_30);
                    dword_4B9190->sub_E74D0(0x7F, &lv_30);
                    dword_4B9190->sub_E74D0(0x7B, &lv_30);
                    dword_4B9190->sub_E74D0(0x80, &lv_30);
                    dword_4B9190->sub_E74D0(0x82, &lv_30);
                    dword_4B9190->sub_E74D0(0x83, &lv_30);
                    dword_4B9190->sub_E74D0(0x84, &lv_30);
                    dword_4B9190->sub_E74D0(0x85, &lv_30);
                    dword_4B9190->sub_E74D0(0x86, &lv_30);
                    dword_4B9190->sub_E74D0(0x87, &lv_30);
                }
                break;
            case 55:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x81, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 56:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x62, &lv_30);
                break;
            case 57:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x62, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 58:
                loc20->GetCommandData(q28);
                if (dword_4B9190)
                    dword_4B9190->sub_E5F60(0x62, q28);
                break;
            case 59:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x63, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 60:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x64, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 61:
                loc20->GetCommandData(dword_4B9190->unk_E0[100].unk_1E8);
                break;
            case 62:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x65, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 63:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x65, &lv_30);
                break;
            case 64:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x66, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 65:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x67, &lv_30);
                break;
            case 66:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x69, &lv_30);
                break;
            case 67:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x69, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 68:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                unk_4B8F34 = r34;
                if (dword_4B9190)
                    dword_4B9190->sub_E7270(0x69, &unk_4B8F34, &unk_4B8F34, &unk_4B8F38, &unk_4B8F38);
                break;
            case 69:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                unk_4B8F38 = r34;
                if (dword_4B9190)
                    dword_4B9190->sub_E7270(0x69, &unk_4B8F34, &unk_4B8F34, &unk_4B8F38, &unk_4B8F38);
                break;
            case 70:
                loc20->GetCommandData(dword_4B9190->unk_E0[105].unk_1E8);
                break;
            case 71:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x68, &lv_30);
                break;
            case 72:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x68, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 73:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->sub_E7270(0x68, &r34, &r34, &r34, &r34);
                break;
            case 74:
                loc20->GetCommandData(dword_4B9190->unk_E0[104].unk_1E8);
                break;
            case 75:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x90, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 76:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x92, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7140(0x92, w48.z);
                }
                break;
            case 77:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x92, &lv_30);
                break;
            case 78:
                loc20->GetCommandData(q28);
                if (dword_4B9190)
                    dword_4B9190->sub_E5F60(0x92, q28);
                break;
            case 79:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x91, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                }
                break;
            case 80:
                loc20->GetCommandData(lv_30);
                if (dword_4B9190)
                    dword_4B9190->sub_E74D0(0x93, &lv_30);
                break;
            case 81:
                loc20->GetCommandData(w48);
                if (dword_4B9190)
                {
                    dword_4B9190->sub_E7050(0x93, (RwUInt32)Width * w48.x, (RwUInt32)Height * w48.y);
                    dword_4B9190->sub_E7140(0x93, w48.z);
                }
                break;
            case 82:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                if (dword_4B9190)
                    dword_4B9190->sub_E7200(0x93, r34.red, r34.green, r34.blue, r34.alpha);
                break;
            case 83:
                loc20->GetCommandData(dword_4B9190->unk_E0[147].unk_1E8);
                break;
            case 84:
                loc20->GetCommandData(w48);
                unk_4B8EF4.x = (RwUInt32)Width * w48.x / 640.0f;
                unk_4B8EF4.y = (RwUInt32)Height * w48.y / 480.0f;
                break;
            case 85:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                unk_4B8EFC = r34;
                break;
            case 86:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                unk_4B8F00 = r34;
                break;
            case 87:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                unk_4B8F04 = r34;
                break;
            case 88:
                loc20->GetCommandData(flt_4B8F08);
                break;
            case 89:
                loc20->GetCommandData(w48);
                dword_4B8F54.x = w48.x;
                dword_4B8F54.y = w48.y;
                break;
            case 90:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F44 = r34;
                break;
            case 91:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F48 = r34;
                break;
            case 92:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F50 = r34;
                break;
            case 93:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F4C = r34;
                break;
            case 95:
                loc20->GetCommandData(x4C);
                dword_4B8F5C = x4C;
                break;
            case 94:
                loc20->GetCommandData(loc50);
                dword_4B8F60 = loc50;
                break;
            case 96:
                if (dword_4B9190)
                {
                    loc20->GetCommandData(lcl_38);
                    r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                    r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                    r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                    r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                    do
                    {
                        dword_4B9190->unk_1A0B0 = ((RwReal)r34.red) * ((RwReal)(1.0 / 255.0));
                        dword_4B9190->unk_1A0B4 = ((RwReal)r34.green) * ((RwReal)(1.0 / 255.0));
                        dword_4B9190->unk_1A0B8 = ((RwReal)r34.blue) * ((RwReal)(1.0 / 255.0));
                        dword_4B9190->unk_1A0BC = ((RwReal)r34.alpha) * ((RwReal)(1.0 / 255.0));
                    }
                    while (0);
                }
                break;
            case 97:
                if (dword_4B9190)
                    loc20->GetCommandData(dword_4B9190->unk_1A0C0);
                break;
            case 102:
                if (dword_4B9190)
                    loc20->GetCommandData(dword_4B9190->unk_1A0C8);
                break;
            case 98:
                if (dword_4B9190)
                    loc20->GetCommandData(dword_4B9190->unk_1A0CC);
                break;
            case 99:
                if (dword_4B9190)
                    loc20->GetCommandData(dword_4B9190->unk_1A0D0);
                break;
            case 100:
                loc20->GetCommandData(dword_4B9154);
                dword_4B9154 = dword_4B9154 * 1000.0f;
                break;
            case 101:
                if (dword_4B9190)
                {
                    for (RwInt32 m_6C = 0; m_6C < 5; m_6C++)
                    {
                        loc20->GetCommandData(dword_4B9190->unk_E0[m_6C + 0x8B].unk_1E8);
                    }
                }
                break;
            case 103:
                if (dword_4B9190)
                {
                    loc20->GetCommandData(lv_30);
                    for (RwInt32 s70 = 0; s70 < 5; s70++)
                    {
                        dword_4B9190->sub_E74D0(s70 + 0x8B, &lv_30);
                    }
                }
                break;
            case 104:
                loc20->GetCommandData(flt_4B8F0C);
                flt_4B8F0C = flt_4B8F0C * 1000.0f;
                break;
            case 105:
                loc20->GetCommandData(flt_4B8F10);
                flt_4B8F10 = flt_4B8F10 * 1000.0f;
                break;
            case 106:
                loc20->GetCommandData(dword_4B8F3C);
                break;
            case 107:
                loc20->GetCommandData(dword_4B8F40);
                break;
            case 108:
                if (dword_4B9190)
                {
                    RwRGBA fp_78;
                    RwUInt32 frm_74;

                    loc20->GetCommandData(frm_74);
                    fp_78.alpha = (RwUInt8)((frm_74 & 0xFF000000) >> 24);
                    fp_78.red = (RwUInt8)((frm_74 & 0xFF0000) >> 16);
                    fp_78.green = (RwUInt8)((frm_74 & 0xFF00) >> 8);
                    fp_78.blue = (RwUInt8)(frm_74 & 0xFF);
                    dword_4B8F64 = fp_78;
                }
                break;
            case 109:
                loc20->GetCommandData(dword_4B8F68);
                break;
            case 110:
                loc20->GetCommandData(dword_4B8F70);
                break;
            case 111:
                loc20->GetCommandData(flt_4B8F7C);
                flt_4B8F7C = flt_4B8F7C * 60.0f;
                break;
            case 112:
                loc20->GetCommandData(dword_4B8F80);
                dword_4B8F80 = dword_4B8F80 * 60.0f;
                break;
            case 113:
                loc20->GetCommandData(dword_4B8F84);
                dword_4B8F84 = dword_4B8F84 * 60.0f;
                break;
            case 114:
                loc20->GetCommandData(dword_4B8F88);
                break;
            case 115:
                loc20->GetCommandData(unk_4B8F90);
                break;
            case 116:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F98 = r34;
                break;
            case 117:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4B8F9C = r34;
                break;
            case 118:
                loc20->GetCommandData(dword_4B8FA0);
                break;
            case 119:
                loc20->GetCommandData(unk_4B8FA4);
                if (unk_4B8FA4.unk_00 && unk_4B8FA4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FA4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 120:
                loc20->GetCommandData(unk_4B8FAC);
                if (unk_4B8FAC.unk_00 && unk_4B8FAC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FAC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 121:
                loc20->GetCommandData(unk_4B8FB4);
                if (unk_4B8FB4.unk_00 && unk_4B8FB4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FB4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 122:
                loc20->GetCommandData(unk_4B8FBC);
                if (unk_4B8FBC.unk_00 && unk_4B8FBC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FBC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 123:
                loc20->GetCommandData(unk_4B8FC4);
                if (unk_4B8FC4.unk_00 && unk_4B8FC4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FC4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 124:
                loc20->GetCommandData(unk_4B8FCC);
                if (unk_4B8FCC.unk_00 && unk_4B8FCC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FCC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 125:
                loc20->GetCommandData(unk_4B8FD4);
                if (unk_4B8FD4.unk_00 && unk_4B8FD4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FD4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 126:
                loc20->GetCommandData(unk_4B8FDC);
                if (unk_4B8FDC.unk_00 && unk_4B8FDC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FDC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 127:
                loc20->GetCommandData(unk_4B8FE4);
                if (unk_4B8FE4.unk_00 && unk_4B8FE4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FE4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 128:
                loc20->GetCommandData(unk_4B8FEC);
                if (unk_4B8FEC.unk_00 && unk_4B8FEC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FEC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 129:
                loc20->GetCommandData(unk_4B8FF4);
                if (unk_4B8FF4.unk_00 && unk_4B8FF4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FF4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 130:
                loc20->GetCommandData(unk_4B8FFC);
                if (unk_4B8FFC.unk_00 && unk_4B8FFC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B8FFC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 131:
                loc20->GetCommandData(unk_4B9004);
                if (unk_4B9004.unk_00 && unk_4B9004.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9004, 0x32, 0, 0, 0, 0);
                }
                break;
            case 132:
                loc20->GetCommandData(unk_4B900C);
                if (unk_4B900C.unk_00 && unk_4B900C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B900C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 133:
                loc20->GetCommandData(unk_4B9014);
                if (unk_4B9014.unk_00 && unk_4B9014.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9014, 0x32, 0, 0, 0, 0);
                }
                break;
            case 134:
                loc20->GetCommandData(unk_4B901C);
                if (unk_4B901C.unk_00 && unk_4B901C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B901C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 135:
                loc20->GetCommandData(unk_4B9024);
                if (unk_4B9024.unk_00 && unk_4B9024.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9024, 0x32, 0, 0, 0, 0);
                }
                break;
            case 136:
                loc20->GetCommandData(unk_4B902C);
                if (unk_4B902C.unk_00 && unk_4B902C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B902C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 137:
                loc20->GetCommandData(unk_4B9034);
                if (unk_4B9034.unk_00 && unk_4B9034.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9034, 0x32, 0, 0, 0, 0);
                }
                break;
            case 138:
                loc20->GetCommandData(unk_4B903C);
                if (unk_4B903C.unk_00 && unk_4B903C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B903C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 139:
                loc20->GetCommandData(unk_4B9044);
                if (unk_4B9044.unk_00 && unk_4B9044.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9044, 0x32, 0, 0, 0, 0);
                }
                break;
            case 140:
                loc20->GetCommandData(unk_4B904C);
                if (unk_4B904C.unk_00 && unk_4B904C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B904C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 141:
                loc20->GetCommandData(unk_4B9054);
                if (unk_4B9054.unk_00 && unk_4B9054.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9054, 0x32, 0, 0, 0, 0);
                }
                break;
            case 142:
                loc20->GetCommandData(unk_4B905C);
                if (unk_4B905C.unk_00 && unk_4B905C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B905C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 143:
                loc20->GetCommandData(unk_4B9064);
                if (unk_4B9064.unk_00 && unk_4B9064.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9064, 0x32, 0, 0, 0, 0);
                }
                break;
            case 144:
                loc20->GetCommandData(unk_4B906C);
                if (unk_4B906C.unk_00 && unk_4B906C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B906C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 145:
                loc20->GetCommandData(unk_4B9074);
                if (unk_4B9074.unk_00 && unk_4B9074.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9074, 0x32, 0, 0, 0, 0);
                }
                break;
            case 146:
                loc20->GetCommandData(unk_4B907C);
                if (unk_4B907C.unk_00 && unk_4B907C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B907C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 147:
                loc20->GetCommandData(unk_4B9084);
                if (unk_4B9084.unk_00 && unk_4B9084.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9084, 0x32, 0, 0, 0, 0);
                }
                break;
            case 148:
                loc20->GetCommandData(unk_4B908C);
                if (unk_4B908C.unk_00 && unk_4B908C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B908C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 149:
                loc20->GetCommandData(unk_4B9094);
                if (unk_4B9094.unk_00 && unk_4B9094.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9094, 0x32, 0, 0, 0, 0);
                }
                break;
            case 150:
                loc20->GetCommandData(unk_4B909C);
                if (unk_4B909C.unk_00 && unk_4B909C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B909C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 151:
                loc20->GetCommandData(unk_4B90A4);
                if (unk_4B90A4.unk_00 && unk_4B90A4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90A4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 152:
                loc20->GetCommandData(unk_4B90AC);
                if (unk_4B90AC.unk_00 && unk_4B90AC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90AC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 153:
                loc20->GetCommandData(unk_4B90B4);
                if (unk_4B90B4.unk_00 && unk_4B90B4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90B4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 154:
                loc20->GetCommandData(unk_4B90BC);
                if (unk_4B90BC.unk_00 && unk_4B90BC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90BC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 155:
                loc20->GetCommandData(unk_4B90C4);
                if (unk_4B90C4.unk_00 && unk_4B90C4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90C4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 156:
                loc20->GetCommandData(unk_4B90CC);
                if (unk_4B90CC.unk_00 && unk_4B90CC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90CC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 157:
                loc20->GetCommandData(unk_4B90D4);
                if (unk_4B90D4.unk_00 && unk_4B90D4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90D4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 158:
                loc20->GetCommandData(unk_4B90DC);
                if (unk_4B90DC.unk_00 && unk_4B90DC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90DC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 159:
                loc20->GetCommandData(unk_4B90E4);
                if (unk_4B90E4.unk_00 && unk_4B90E4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90E4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 160:
                loc20->GetCommandData(unk_4B90EC);
                if (unk_4B90EC.unk_00 && unk_4B90EC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90EC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 162:
                loc20->GetCommandData(unk_4B90FC);
                if (unk_4B90FC.unk_00 && unk_4B90FC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90FC, 0x32, 0, 0, 0, 0);
                }
                break;
            case 163:
                loc20->GetCommandData(unk_4B9104);
                if (unk_4B9104.unk_00 && unk_4B9104.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9104, 0x32, 0, 0, 0, 0);
                }
                break;
            case 164:
                loc20->GetCommandData(unk_4B910C);
                if (unk_4B910C.unk_00 && unk_4B910C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B910C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 165:
                loc20->GetCommandData(unk_4B9114);
                if (unk_4B9114.unk_00 && unk_4B9114.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9114, 0x32, 0, 0, 0, 0);
                }
                break;
            case 166:
                loc20->GetCommandData(unk_4B911C);
                if (unk_4B911C.unk_00 && unk_4B911C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B911C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 167:
                loc20->GetCommandData(unk_4B9124);
                if (unk_4B9124.unk_00 && unk_4B9124.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9124, 0x32, 0, 0, 0, 0);
                }
                break;
            case 161:
                loc20->GetCommandData(unk_4B90F4);
                if (unk_4B90F4.unk_00 && unk_4B90F4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B90F4, 0x32, 0, 0, 0, 0);
                }
                break;
            case 168:
                loc20->GetCommandData(unk_4B912C);
                if (unk_4B912C.unk_00 && unk_4B912C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B912C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 169:
                loc20->GetCommandData(unk_4B9134);
                if (unk_4B9134.unk_00 && unk_4B9134.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_4B9134, 0x32, 0, 0, 0, 0);
                }
                break;
            case 170:
                loc20->GetCommandData(dword_4B913C);
                if (dword_4B913C.unk_00 && dword_4B913C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&dword_4B913C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 171:
                loc20->GetCommandData(dword_4B9144);
                if (dword_4B9144.unk_00 && dword_4B9144.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&dword_4B9144, 0x32, 0, 0, 0, 0);
                }
                break;
            case 172:
                loc20->GetCommandData(dword_4B914C);
                if (dword_4B914C.unk_00 && dword_4B914C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&dword_4B914C, 0x32, 0, 0, 0, 0);
                }
                break;
            case 173:
                loc20->GetCommandData(dword_4B916C);
                break;
            case 174:
                loc20->GetCommandData(dword_4B9170);
                break;
            case 175:
                loc20->GetCommandData(dword_4B9174);
                dword_4B9174.x /= 100.0f;
                dword_4B9174.x *= (RwReal)(RwUInt32)Width / (RwUInt32)Height;
                dword_4B9174.y /= 100.0f;
                break;
            case 176:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                do
                {
                    lv_10.red = ((RwReal)r34.red) * ((RwReal)(1.0 / 255.0));
                    lv_10.green = ((RwReal)r34.green) * ((RwReal)(1.0 / 255.0));
                    lv_10.blue = ((RwReal)r34.blue) * ((RwReal)(1.0 / 255.0));
                    lv_10.alpha = ((RwReal)r34.alpha) * ((RwReal)(1.0 / 255.0));
                }
                while (0);
                unk_4B917C = lv_10;
                // (No break: it goes on into command 177.)
            case 177:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4EBD20 = r34;
                break;
            case 178:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4EBDE8 = r34;
                break;
            case 179:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4EBD24 = r34;
                break;
            case 180:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4EBD14 = r34;
                break;
            case 181:
                loc20->GetCommandData(lcl_38);
                r34.alpha = (RwUInt8)((lcl_38 & 0xFF000000) >> 24);
                r34.red = (RwUInt8)((lcl_38 & 0xFF0000) >> 16);
                r34.green = (RwUInt8)((lcl_38 & 0xFF00) >> 8);
                r34.blue = (RwUInt8)(lcl_38 & 0xFF);
                dword_4EBD10 = r34;
                break;
            case 182:
            {
                RwV2d r80;

                loc20->GetCommandData(r80);
                r80.x = (RwUInt32)Width * 0.5f * r80.x;
                r80.y = (RwUInt32)Height * 0.5f * r80.y;
                dword_4EBCF8 = r80;
                break;
            }
            case 183:
            {
                RwV2d t88;

                loc20->GetCommandData(t88);
                t88.x = (RwUInt32)Width * 0.5f * t88.x;
                t88.y = (RwUInt32)Height * 0.5f * t88.y;
                dword_4EBD08 = t88;
                break;
            }
            case 184:
                set_part_multiplier(0, loc20->GetAs_RwReal());
                break;
            case 185:
                set_part_multiplier(1, loc20->GetAs_RwReal());
                break;
            case 186:
                set_part_multiplier(2, loc20->GetAs_RwReal());
                break;
            case 187:
                set_part_multiplier(3, loc20->GetAs_RwReal());
                break;
            case 188:
                set_part_multiplier(4, loc20->GetAs_RwReal());
                break;
            case 189:
                set_part_multiplier(6, loc20->GetAs_RwReal());
                break;
            case 190:
                set_part_multiplier(5, loc20->GetAs_RwReal());
                break;
            case 191:
                set_part_multiplier(7, loc20->GetAs_RwReal());
                break;
            case 192:
                set_part_multiplier(8, loc20->GetAs_RwReal());
                break;
            case 194:
            {
                RwV3d frm_94;

                loc20->GetCommandData(frm_94);
                set_multiplier(flt_4F286C, 0, frm_94.x);
                set_multiplier(flt_4F286C, 1, frm_94.y);
                set_multiplier(flt_4F286C, 2, frm_94.z);
                break;
            }
            case 195:
            {
                RwV3d pA0;

                loc20->GetCommandData(pA0);
                set_multiplier(flt_4F28E4, 0, pA0.x);
                set_multiplier(flt_4F28E4, 1, pA0.y);
                set_multiplier(flt_4F28E4, 2, pA0.z);
                break;
            }
            case 196:
            {
                RwV3d local_AC;

                loc20->GetCommandData(local_AC);
                set_multiplier(flt_4F28A8, 0, local_AC.x);
                set_multiplier(flt_4F28A8, 1, local_AC.y);
                set_multiplier(flt_4F28A8, 2, local_AC.z);
                break;
            }
            case 197:
            {
                RwV3d local_B8;

                loc20->GetCommandData(local_B8);
                set_multiplier(flt_4F2878, 0, local_B8.x);
                set_multiplier(flt_4F2878, 1, local_B8.y);
                set_multiplier(flt_4F2878, 2, local_B8.z);
                break;
            }
            case 198:
            {
                RwV3d local_C4;

                loc20->GetCommandData(local_C4);
                set_multiplier(flt_4F2860, 0, local_C4.x);
                set_multiplier(flt_4F2860, 1, local_C4.y);
                set_multiplier(flt_4F2860, 2, local_C4.z);
                break;
            }
            case 200:
            {
                RwV3d fp_D0;

                loc20->GetCommandData(fp_D0);
                set_multiplier(flt_4F2890, 0, fp_D0.x);
                set_multiplier(flt_4F2890, 1, fp_D0.y);
                set_multiplier(flt_4F2890, 2, fp_D0.z);
                break;
            }
            case 201:
            {
                RwV3d frm_DC;

                loc20->GetCommandData(frm_DC);
                set_multiplier(flt_4F28B4, 0, frm_DC.x);
                set_multiplier(flt_4F28B4, 1, frm_DC.y);
                set_multiplier(flt_4F28B4, 2, frm_DC.z);
                break;
            }
            case 202:
            {
                RwV3d var_E8;

                loc20->GetCommandData(var_E8);
                set_multiplier(flt_4F28D8, 0, var_E8.x);
                set_multiplier(flt_4F28D8, 1, var_E8.y);
                set_multiplier(flt_4F28D8, 2, var_E8.z);
                break;
            }
            case 203:
            {
                RwV3d local_F4;

                loc20->GetCommandData(local_F4);
                set_multiplier(flt_4F28C0, 0, local_F4.x);
                set_multiplier(flt_4F28C0, 1, local_F4.y);
                set_multiplier(flt_4F28C0, 2, local_F4.z);
                break;
            }
            case 204:
            {
                RwV3d l100;

                loc20->GetCommandData(l100);
                set_multiplier(flt_4F28CC, 0, l100.x);
                set_multiplier(flt_4F28CC, 1, l100.y);
                set_multiplier(flt_4F28CC, 2, l100.z);
                break;
            }
            case 205:
            {
                RwV3d o10C;

                loc20->GetCommandData(o10C);
                set_multiplier(flt_4F2884, 0, o10C.x);
                set_multiplier(flt_4F2884, 1, o10C.y);
                set_multiplier(flt_4F2884, 2, o10C.z);
                break;
            }
        }
        ++loc20;
    }
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@CShellBehaviorClass@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void CShellBehaviorClass::HandleEvents(RWS::CMsg &pMsg)
{
}
