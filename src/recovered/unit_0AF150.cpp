// RenderTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/RenderTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6358
extern const RwReal flt_3D6358 = 16.666666f;
// 0x004CF46C
RwInt32 dword_4CF46C;
// 0x004CF4F4
RwInt32 dword_4CF4F4;
// 0x004CF764
RwInt32 dword_4CF764;
// 0x004CF768
RwRGBA stru_4CF768;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(RenderTrigger);
RWS_REGISTERCLASS(RenderTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@GIJOIKHK@RenderTrigger?$AA@ @ 0x003D6348
// match: ?flt_3D6358@@3MB @ 0x003D6358
// match: ??_7RenderTrigger@@6B@ @ 0x003D635C
// match: __ehhandler$?MakeNew@RenderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BF48
// match: __ehhandler$?MakeNew@RenderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BF50
// match: .CRT$XCU+0 @ 0x00426F40
// match: ?pRenderTriggerClassID@RenderTrigger@@2PBDB @ 0x00429184

// match: _$E2 @ 0x0030A930
// match: _$E3 @ 0x0030E0E0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@RenderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000AF150
// match: __ehhandler$?MakeNew@RenderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300170
// match: __ehhandler$?MakeNew@RenderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030017F
// sp-match: ?MakeNew@RenderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00087C20
RWS_DEFINE_MAKENEW(RenderTrigger)

// match: ??0RenderTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000AF1D0
// sp-match: ??0RenderTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000876A0
RenderTrigger::RenderTrigger(const RWS::CAttributePacket &attr)
{
}

// match: ??_GRenderTrigger@@UAEPAXI@Z @ 0x000AF230
// sp-match: ??_GRenderTrigger@@UAEPAXI@Z @ 0x00087770

// match: ??1RenderTrigger@@UAE@XZ @ 0x000AF250
// sp-match: ??1RenderTrigger@@UAE@XZ @ 0x000876C0
// (Defined in the class, in RenderTrigger.h.)

// match: ?sub_AF270@RenderTrigger@@QAEHH@Z @ 0x000AF270
// sp-match: ?sub_AF270@RenderTrigger@@QAEHH@Z @ 0x000876D0
RwInt32 RenderTrigger::sub_AF270(RwInt32 arg_0)
{
    RwInt32 var_4;

    switch (arg_0)
    {
    default:
        var_4 = 1;
        break;
    case 1:
        var_4 = 2;
        break;
    case 2:
        var_4 = 3;
        break;
    case 3:
        var_4 = 4;
        break;
    case 4:
        var_4 = 5;
        break;
    case 5:
        var_4 = 6;
        break;
    case 6:
        var_4 = 7;
        break;
    case 7:
        var_4 = 8;
        break;
    case 8:
        var_4 = 9;
        break;
    case 9:
        var_4 = 10;
        break;
    case 10:
        var_4 = 11;
        break;
    }
    return var_4;
}

// match: ?HandleAttributes@RenderTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000AF330
// sp-match: ?HandleAttributes@RenderTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00087780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void RenderTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(RenderTrigger));
    while (!attrIt.IsFinished())
    {
        RwUInt32 var_14;
        RwUInt32 lv_10;
        RwInt32 var_C;

        switch (attrIt->GetCommandId())
        {
        case 0:
            dword_4CF518 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 1:
            dword_4CF5B8 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 2:
            dword_4CF760 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 3:
            dword_4CF4FC = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 4:
            switch (attrIt->GetAs_RwInt32())
            {
            case 0:
                dword_4CF778 = 1;
                break;
            case 1:
                dword_4CF778 = 2;
                break;
            case 2:
                dword_4CF778 = 3;
                break;
            }
            break;
        case 5:
            dword_4CF4DC = sub_AF270(attrIt->GetAs_RwInt32());
            break;
        case 6:
            dword_4CF780 = sub_AF270(attrIt->GetAs_RwInt32());
            break;
        case 7:
            dword_4CF460 = attrIt->GetAs_RwInt32();
            break;
        case 8:
            dword_4CF784 = attrIt->GetAs_RwInt32();
            break;
        case 9:
            dword_4CF45C = attrIt->GetAs_RwInt32();
            break;
        case 10:
            var_C = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            switch (var_C)
            {
            default:
                dword_4CF504 = 2;
                break;
            case 1:
                dword_4CF504 = 1;
                break;
            }
            break;
        case 12:
            dword_4CF50C = attrIt->GetAs_RwInt32();
            sub_126770();
            break;
        case 13:
            dword_4CF754 = attrIt->GetAs_RwInt32();
            sub_1268D0();
            break;
        case 15:
            switch (attrIt->GetAs_RwInt32())
            {
            case 0:
                dword_4CF450 = 0;
                break;
            case 1:
                dword_4CF450 = 1;
                break;
            case 2:
                dword_4CF450 = 2;
                break;
            case 3:
                dword_4CF450 = 3;
                break;
            }
            break;
        case 16:
            dword_4CF474 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 17:
            dword_4CF454 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 18:
            dword_4CF4F0 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 19:
            lv_10 = *(const RwUInt32 *)attrIt->GetAs_RwChar_ptr();
            stru_4CF790.alpha = (RwUInt8)((lv_10 & 0xFF000000) >> 24);
            stru_4CF790.red = (RwUInt8)((lv_10 & 0xFF0000) >> 16);
            stru_4CF790.green = (RwUInt8)((lv_10 & 0xFF00) >> 8);
            stru_4CF790.blue = (RwUInt8)(lv_10 & 0xFF);
            break;
        case 20:
            if (attrIt->GetAs_RwInt32())
            {
                dword_4CF5BC |= 1;
            }
            else
            {
                dword_4CF5BC &= ~1;
            }
            break;
        case 21:
            if (attrIt->GetAs_RwInt32())
            {
                dword_4CF5BC |= 2;
            }
            else
            {
                dword_4CF5BC &= ~2;
            }
            break;
        case 22:
            if (attrIt->GetAs_RwInt32())
            {
                dword_4CF5BC |= 4;
            }
            else
            {
                dword_4CF5BC &= ~4;
            }
            break;
        case 23:
#ifdef CODFH_SP // shape: SP 0x87AB9 copies the field of view as a float (fld/fst/fstp)
            *(RwReal *)&dword_4CF468 = *(const RwReal *)attrIt->GetAs_RwChar_ptr();
            *(RwReal *)&dword_4CF540 = *(RwReal *)&dword_4CF468;
#else
            dword_4CF468 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            dword_4CF540 = dword_4CF468;
#endif
            break;
        case 24:
            flt_4CF458 = *(const RwReal *)attrIt->GetAs_RwChar_ptr();
            farClip = flt_4CF458;
            break;
        case 25:
            dword_4CF500 = attrIt->GetAs_RwInt32();
            break;
        case 26:
            var_14 = *(const RwUInt32 *)attrIt->GetAs_RwChar_ptr();
            stru_4CF768.alpha = (RwUInt8)((var_14 & 0xFF000000) >> 24);
            stru_4CF768.red = (RwUInt8)((var_14 & 0xFF0000) >> 16);
            stru_4CF768.green = (RwUInt8)((var_14 & 0xFF00) >> 8);
            stru_4CF768.blue = (RwUInt8)(var_14 & 0xFF);
            break;
        case 27:
            dword_4CF4F4 = attrIt->GetAs_RwInt32();
            break;
        case 30:
            dword_4CF764 = attrIt->GetAs_RwInt32();
            break;
        case 31:
            dword_4CF46C = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// Functions /OPT:ICF folded into another body, defined here for the authentic link (PLAN M7)
// with that body; the placement link takes the folded one.

// ?vf_008@RenderTrigger@@UAEHXZ (folded into 0x195D00)
RwInt32 RenderTrigger::vf_008()
{
    return 2;
}
