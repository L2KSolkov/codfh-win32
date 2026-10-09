/*
 * The game settings (game/ingamepages.h): the front end's options page
 * over the pause menu, written back on "Accept", and the player's kill.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9928
extern const RwReal flt_3E9928 = 0.01f;
// 0x003E992C
extern const RwReal flt_3E992C = 0.01f;
// 0x003E9930
extern const RwReal flt_3E9930 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9928@@3MB @ 0x003E9928
// match: ?flt_3E992C@@3MB @ 0x003E992C
// match: ?flt_3E9930@@3MB @ 0x003E9930
// match: ??_7type_216D20@@6B@ @ 0x003E9938
// match: ??_7?$type_3E7CE8@Utype_216D20@@@kujuUI@@6B@ @ 0x003E9988
// match: __ehhandler$??0type_216D20@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x004244CC
// match: __ehhandler$??0type_216D20@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x004244FC
// match: __ehhandler$??1type_216D20@@UAE@XZ>1>8 @ 0x00424518
// match: __ehhandler$??1type_216D20@@UAE@XZ>1 @ 0x00424540

// match: ??0type_216D20@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00216D20
// match: __ehhandler$??0type_216D20@@QAE@PBDPAUtype_21A5E0@@@Z-0x4E @ 0x003072A0
// match: __ehhandler$??0type_216D20@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x003072EE

type_216D20::type_216D20(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), type_1FC320(&unk_330, &unk_330, &unk_330, &unk_340),
      unk_310(this, &type_216D20::sub_2170F0), unk_320(this, &type_216D20::sub_217120),
      unk_330(this, &type_216D20::sub_1E41C0), unk_340(this, &type_216D20::sub_39440)
{
    sub_204FC0("Volume", &this->type_1FC320::unk_00);
    sub_204FC0("Sensitivity", &this->type_1FC320::unk_7C);
    sub_204FC0("Sound", &this->type_1FC320::unk_F8);
    sub_204FC0("Turn", &this->type_1FC320::unk_118);
    sub_204FC0("YAxis", &this->type_1FC320::unk_138);
    sub_204FC0("Controls", &this->type_1FC320::unk_158);
    sub_204FC0("vibration", &this->type_1FC320::unk_178);
    sub_204FC0("VoiceChatSpeakers", &this->type_1FC320::unk_198);
    sub_204FC0("Accept", &unk_310);
    sub_204FC0("kill", &unk_320);
}

// match: ??_Gtype_216D20@@UAEPAXI@Z @ 0x00216F50
// match: ??1type_216D20@@UAE@XZ @ 0x00216F80
// match: __ehhandler$??1type_216D20@@UAE@XZ-0x5B @ 0x00307300
// match: __ehhandler$??1type_216D20@@UAE@XZ @ 0x0030735B
type_216D20::~type_216D20()
{
}

// match: ?vf_008@type_216D20@@UAEXXZ @ 0x00217040
void type_216D20::vf_008()
{
    type_21CB10::vf_008();
    sub_1FCC80();
    unk_350 = (type_1FD490_value)sub_1C51A0();
    type_1FC320::unk_198.sub_201EC0(unk_350);
}

// match: ?vf_014@type_216D20@@UAEXM@Z @ 0x00217090
void type_216D20::vf_014(RwReal arg_0)
{
    type_20E850::vf_014(arg_0);
    RwInt32 var_4 = sub_1C51A0();
    if (var_4 != unk_350)
    {
        unk_350 = (type_1FD490_value)var_4;
        type_1FC320::unk_198.sub_201EC0(unk_350);
    }
}

// match: ?sub_2170F0@type_216D20@@QAEXXZ @ 0x002170F0
void type_216D20::sub_2170F0()
{
    sub_1FCD10();
    unk_130->sub_21C200(0, 0);
}

// match: ?sub_217120@type_216D20@@QAEXXZ @ 0x00217120
void type_216D20::sub_217120()
{
    sub_1C44F0();
    unk_130->sub_21C200(0, 0);
    unk_130->sub_21C360();
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_216D20@@@kujuUI@@QAE@PAUtype_216D20@@P82@AEXXZ@Z @ 0x00217150
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_216D20@@@kujuUI@@UAEPAXI@Z @ 0x002171C0
// match: ??1?$type_3E7CE8@Utype_216D20@@@kujuUI@@UAE@XZ @ 0x002171A0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_024@type_216D20@@UAEHXZ (folded into 0x222540)
RwInt32 type_216D20::vf_024()
{
        return 0x3A;
    }

// Functions /OPT:ICF folded into the shared empty body (pDtor, 0x1E41C0) and
// into its caller (0x39440); defined for the authentic link (PLAN M7).

void type_216D20::sub_1E41C0()
{
}

void type_216D20::sub_39440()
{
    sub_1E41C0();
}
