// ParticleEditor: its MakeNew, constructor, destructor, handlers and
// defaults (types/ParticleEditor.h). Its original file name is not in the
// image, so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/batextur.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/csystemcommands.h"
#include "game/decals.h"
#include "game/functions.h"
#include "types/ParticleEditor.h"



// Sends the message Id with no data when handlers are linked to it, like
// RWS::SendMsg but reading the id's record through its accessor each time:
// an inline with no address, named for what it does. Evidence: sub_F1720
// loads the record into a temporary of its own for each test and for the
// message.
inline void send_msg(RWS::CEventId &Id)
{
    if (Id.get_p_msgrec() && Id.get_p_msgrec()->Erm.p_next)
    {
        RWS::CMsg Msg(Id.get_p_msgrec());
        RWS::_SendMsg(Msg);
    }
}

RWS_IMPLEMENT_CLASSID(ParticleEditor);
RWS_REGISTERCLASS(ParticleEditor);
// Its data definitions (PLAN M5), after the class id (VC7.1 emits data definitions
// last-defined first, and the image has the constants before the class name).
// 0x003D91C0
extern const RwReal flt_3D91C0 = 16.666666f;
// 0x003D91C4
extern const RwReal flt_3D91C4 = 16.666666f;
// End of its data definitions.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D91C0@@3MB @ 0x003D91C0
// match: ?flt_3D91C4@@3MB @ 0x003D91C4
// match: ??_C@_0P@NCDNGMJM@ParticleEditor?$AA@ @ 0x003D91C8
// match: ??_7ParticleEditor@@6BCEventHandler@RWS@@@ @ 0x003D91D8
// match: ??_7ParticleEditor@@6BCAttributeHandler@RWS@@@ @ 0x003D91E0
// match: __ehhandler$?MakeNew@ParticleEditor@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041CF7C
// match: __ehhandler$?MakeNew@ParticleEditor@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041CF84
// match: __ehhandler$??0ParticleEditor@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041CFA0
// match: __ehhandler$??0ParticleEditor@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041CFC8
// match: __ehhandler$??1ParticleEditor@@UAE@XZ>1>8 @ 0x0041CFE4
// match: __ehhandler$??1ParticleEditor@@UAE@XZ>1 @ 0x0041D00C
// match: .CRT$XCU+0 @ 0x0042705C
// match: ?pParticleEditorClassID@ParticleEditor@@2PBDB @ 0x004296D0

// match: _$E2 @ 0x0030B590
// match: _$E3 @ 0x0030E4F0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@ParticleEditor@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000F1320
// match: __ehhandler$?MakeNew@ParticleEditor@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300F90
// match: __ehhandler$?MakeNew@ParticleEditor@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300F9F
// sp-match: ?MakeNew@ParticleEditor@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B8F50
RWS_DEFINE_MAKENEW(ParticleEditor)

// match: ??0ParticleEditor@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000F13A0
// match: __ehhandler$??0ParticleEditor@@QAE@ABVCAttributePacket@RWS@@@Z-0x3D @ 0x00300FB0
// match: __ehhandler$??0ParticleEditor@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300FED
// sp-match: ??0ParticleEditor@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B8820
ParticleEditor::ParticleEditor(const RWS::CAttributePacket &attr)
{
    unk_24 = RwMatrixCreate();
    if (unk_24)
    {
        RwMatrixSetIdentity(unk_24);
    }
    sub_F23F0(&unk_28);
}

// match: ??_GParticleEditor@@UAEPAXI@Z @ 0x000F15B0
// sp-match: ??_GParticleEditor@@UAEPAXI@Z @ 0x000B8940

// match: ??1ParticleEditor@@UAE@XZ @ 0x000F15D0
// match: __ehhandler$??1ParticleEditor@@UAE@XZ-0x59 @ 0x00301000
// match: __ehhandler$??1ParticleEditor@@UAE@XZ @ 0x00301059
// sp-match: ??1ParticleEditor@@UAE@XZ @ 0x000B8530
ParticleEditor::~ParticleEditor()
{
    if (unk_24)
    {
        RwMatrixDestroy(unk_24);
        unk_24 = 0;
    }
    UnLinkMsg(unk_240);
    RWS::CEventHandler::UnRegisterMsg(unk_240);
    UnLinkMsg(unk_248);
    RWS::CEventHandler::UnRegisterMsg(unk_248);
    UnLinkMsg(unk_250);
    RWS::CEventHandler::UnRegisterMsg(unk_250);
}

// match: ?HandleEvents@ParticleEditor@@UAEXAAVCMsg@RWS@@@Z @ 0x000F1720
// sp-match: ?HandleEvents@ParticleEditor@@UAEXAAVCMsg@RWS@@@Z @ 0x000B8630
void ParticleEditor::HandleEvents(RWS::CMsg &pMsg)
{
    RwChar var_24[32];

    if (pMsg.Id.p_msgrec == unk_240.get_p_msgrec())
    {
        unk_134 = unk_28;
        sub_F3370(&unk_134);
        sub_16E950(var_24, unk_134.unk_84);
        unk_134.unk_04 = RwTexDictionaryFindNamedTexture(dict, var_24);
        sub_F3130(&unk_134, unk_24, 0, 1, 0, 0);
    }
    if (pMsg.Id.p_msgrec == unk_250.get_p_msgrec())
    {
        send_msg(unk_240);
    }
    if (pMsg.Id.p_msgrec == unk_248.get_p_msgrec())
    {
        sub_F2A00(1);
    }
}

// match: ?HandleAttributes@ParticleEditor@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000F1860
// sp-match: ?HandleAttributes@ParticleEditor@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B8950
void ParticleEditor::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    sub_F2360(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(ParticleEditor));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            UnLinkMsg(unk_240);
            RWS::CEventHandler::UnRegisterMsg(unk_240);
            RWS::CEventHandler::RegisterMsg(unk_240, attrIt->GetAs_RwChar_ptr(), 0);
            LinkMsg(unk_240, 0, 0x8000);
            break;
        case 1:
            UnLinkMsg(unk_250);
            RWS::CEventHandler::UnRegisterMsg(unk_250);
            RWS::CEventHandler::RegisterMsg(unk_250, attrIt->GetAs_RwChar_ptr(), 0);
            LinkMsg(unk_250, 0, 0x8000);
            break;
        case 2:
            UnLinkMsg(unk_248);
            RWS::CEventHandler::UnRegisterMsg(unk_248);
            RWS::CEventHandler::RegisterMsg(unk_248, attrIt->GetAs_RwChar_ptr(), 0);
            LinkMsg(unk_248, 0, 0x8000);
            break;
        case 4:
            unk_28.unk_CC = attrIt->GetAs_RwReal();
            break;
        case 5:
            unk_28.unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 6:
            unk_28.unk_0C = attrIt->GetAs_RwReal();
            break;
        case 7:
            unk_28.unk_10 = attrIt->GetAs_RwReal();
            break;
        case 8:
            unk_28.unk_14 = attrIt->GetAs_RwReal();
            break;
        case 9:
            unk_28.unk_18 = attrIt->GetAs_RwReal();
            break;
        case 10:
            unk_28.unk_1C = attrIt->GetAs_RwReal();
            break;
        case 11:
            unk_28.unk_20 = attrIt->GetAs_RwReal();
            break;
        case 12:
            unk_28.unk_24 = attrIt->GetAs_RwReal();
            break;
        case 13:
            unk_28.unk_28 = attrIt->GetAs_RwReal();
            break;
        case 14:
            unk_28.unk_F8 = attrIt->GetAs_RwReal();
            break;
        case 15:
            unk_28.unk_FC = attrIt->GetAs_RwReal();
            break;
        case 16:
            unk_28.unk_100 = attrIt->GetAs_RwReal();
            break;
        case 17:
            unk_28.unk_104 = attrIt->GetAs_RwReal();
            break;
        case 25:
            unk_28.unk_2C = attrIt->GetAs_RwReal();
            break;
        case 26:
            unk_28.unk_30 = attrIt->GetAs_RwReal();
            break;
        case 27:
            unk_28.unk_34 = attrIt->GetAs_RwReal();
            break;
        case 28:
            unk_28.unk_38 = attrIt->GetAs_RwReal();
            break;
        case 29:
            unk_28.unk_3C = attrIt->GetAs_RwReal();
            break;
        case 30:
            unk_28.unk_40 = attrIt->GetAs_RwReal();
            break;
        case 31:
            unk_28.unk_44 = attrIt->GetAs_RwReal();
            break;
        case 32:
            unk_28.unk_48 = attrIt->GetAs_RwReal();
            break;
        case 33:
            unk_28.unk_4C = attrIt->GetAs_RwReal();
            break;
        case 34:
            unk_28.unk_50 = attrIt->GetAs_RwReal();
            break;
        case 35:
            unk_28.unk_54 = attrIt->GetAs_RwReal();
            break;
        case 37:
            unk_28.unk_58 = attrIt->GetAs_RwUInt32();
            break;
        case 38:
            unk_28.unk_108 = attrIt->GetAs_RwUInt32();
            break;
        case 39:
            unk_28.unk_5C = attrIt->GetAs_RwUInt32();
            break;
        case 40:
            unk_28.unk_60 = attrIt->GetAs_RwReal();
            break;
        case 41:
            unk_28.unk_64 = attrIt->GetAs_RwReal();
            break;
        case 42:
            unk_28.unk_68 = attrIt->GetAs_RwReal();
            break;
        case 43:
            unk_28.unk_6C = attrIt->GetAs_RwReal();
            break;
        case 44:
            unk_28.unk_70 = attrIt->GetAs_RwReal();
            break;
        case 45:
            unk_28.unk_74 = attrIt->GetAs_RwReal();
            break;
        case 46:
            unk_28.unk_78 = attrIt->GetAs_RwReal();
            break;
        case 47:
            unk_28.unk_7C = attrIt->GetAs_RwReal();
            break;
        case 18:
            unk_28.unk_80 = attrIt->GetAs_RwInt32();
            break;
        case 19:
            if (const RwChar *p19 = attrIt->GetAs_RwChar_ptr())
            {
                strcpy(unk_28.unk_84, p19);
            }
            break;
        case 20:
            if (const RwChar *p20 = attrIt->GetAs_RwChar_ptr())
            {
                strcpy(unk_28.unk_AC, p20);
            }
            break;
        case 21:
            unk_28.unk_A8 = attrIt->GetAs_RwInt32();
            break;
        case 36:
            unk_28.unk_A4 = attrIt->GetAs_RwInt32();
            break;
        case 22:
            if (const RwChar *p22 = attrIt->GetAs_RwChar_ptr())
            {
                strcpy(unk_28.unk_D0, p22);
            }
            break;
        case 23:
            unk_28.unk_F0 = attrIt->GetAs_RwInt32();
            break;
        case 24:
            unk_28.unk_F4 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_F2360@ParticleEditor@@QAEXABVCAttributePacket@RWS@@@Z @ 0x000F2360
// sp-match: ?sub_F2360@ParticleEditor@@QAEXABVCAttributePacket@RWS@@@Z @ 0x000BA6A0
void ParticleEditor::sub_F2360(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS::CSystemCommands::pCSystemCommandsClassID);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case RWS::CSystemCommands::CMD_LoadMatrix:
        {
            const RwMatrix *pMatrix = (const RwMatrix *)attrIt->GetAs_RwChar_ptr();

            *unk_24 = *pMatrix;
            RwMatrixOptimize(unk_24, 0);
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?sub_F23F0@ParticleEditor@@QAEXPAUtype_F3130@@@Z @ 0x000F23F0
// sp-match: ?sub_F23F0@ParticleEditor@@QAEXPAUtype_F3130@@@Z @ 0x000B8710
void ParticleEditor::sub_F23F0(type_F3130 *arg_0)
{
    arg_0->unk_00 = 6;
    arg_0->unk_80 = 0;
    arg_0->unk_08 = 300;
    arg_0->unk_20 = 10.0f;
    arg_0->unk_0C = 10.0f;
    arg_0->unk_10 = 10.0f;
    arg_0->unk_14 = 10.0f;
    arg_0->unk_18 = 2.0f;
    arg_0->unk_1C = 0.0f;
    arg_0->unk_24 = 4.0f;
    arg_0->unk_28 = 0.0f;
    arg_0->unk_2C = 30.0f;
    arg_0->unk_30 = 0.0f;
    arg_0->unk_40 = 0.0f;
    arg_0->unk_44 = 1.0f;
    arg_0->unk_48 = 0.0f;
    arg_0->unk_4C = 0.35f;
    arg_0->unk_50 = 0.0f;
    arg_0->unk_54 = 0.35f;
    arg_0->unk_34 = 0.0f;
    arg_0->unk_38 = -20.0f;
    arg_0->unk_3C = 0.0f;
    arg_0->unk_58 = 0xFFFF0000;
    arg_0->unk_108 = 0xFF00FF00;
    arg_0->unk_5C = 0xFF0000FF;
    arg_0->unk_60 = 25.0f;
    arg_0->unk_64 = 25.0f;
    arg_0->unk_68 = 0.0f;
    arg_0->unk_6C = 0.0f;
    arg_0->unk_70 = 25.0f;
    arg_0->unk_74 = 25.0f;
    arg_0->unk_78 = 0.0f;
    arg_0->unk_7C = 0.0f;
    arg_0->unk_84[0] = 0;
    arg_0->unk_A8 = 0;
    arg_0->unk_A4 = 1;
    arg_0->unk_AC[0] = 0;
    arg_0->unk_CC = 1.0f;
    arg_0->unk_D0[0] = 0;
    arg_0->unk_F0 = 0;
    arg_0->unk_F4 = 0;
    arg_0->unk_F8 = 0;
    arg_0->unk_FC = 0;
    arg_0->unk_100 = 0;
    arg_0->unk_104 = 0;
}

// match: ??_EParticleEditor@@WBI@AEPAXI@Z @ 0x000F25E0
// sp-match: ??_EParticleEditor@@WBI@AEPAXI@Z @ 0x000B8810
