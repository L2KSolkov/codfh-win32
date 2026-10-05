/*
 * The in-game options (in-game menu 5, game/livemenu.h): the front end's
 * options page (game/options.h) under "Options.layout", with "Back" and
 * "Accept", following the voice chat's speakers.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E8F50
extern const RwReal flt_3E8F50 = 0.01f;
// 0x003E8F54
extern const RwReal flt_3E8F54 = 0.01f;
// 0x003E8F58
extern const RwReal flt_3E8F58 = 16.666666f;
// 0x0042D2A8
RwInt32 dword_42D2A8 = -1;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8F50@@3MB @ 0x003E8F50
// match: ?flt_3E8F54@@3MB @ 0x003E8F54
// match: ?flt_3E8F58@@3MB @ 0x003E8F58
// match: ??_C@_06MDEHPNLG@Accept?$AA@ @ 0x003E8F5C
// match: ??_C@_0BC@EODIGGC@VoiceChatSpeakers?$AA@ @ 0x003E8F64
// match: ??_C@_09MPPKNLCA@vibration?$AA@ @ 0x003E8F78
// match: ??_C@_08BJJAFCGA@Controls?$AA@ @ 0x003E8F84
// match: ??_C@_05ONLACEHD@YAxis?$AA@ @ 0x003E8F90
// match: ??_C@_04EKEMLFA@Turn?$AA@ @ 0x003E8F98
// match: ??_C@_05MAHMNMLO@Sound?$AA@ @ 0x003E8FA0
// match: ??_C@_0M@ININPOCK@Sensitivity?$AA@ @ 0x003E8FA8
// match: ??_C@_06IDJCEMPA@Volume?$AA@ @ 0x003E8FB4
// match: ??_7type_20B570@@6B@ @ 0x003E8FC0
// match: ??_C@_0P@LLAGOHLD@Options?4layout?$AA@ @ 0x003E9004
// match: ??_7?$type_3E7CE8@Utype_20B570@@@kujuUI@@6B@ @ 0x003E9014
// match: __ehhandler$??0type_20B570@@QAE@XZ>1>8 @ 0x004231C4
// match: __ehhandler$??0type_20B570@@QAE@XZ>1 @ 0x004231E4
// match: __ehhandler$??1type_20B570@@UAE@XZ>1>8 @ 0x00423200
// match: __ehhandler$??1type_20B570@@UAE@XZ>1 @ 0x00423218
// match: ?dword_42D2A8@@3HA @ 0x0042D2A8

// match: ??0type_20B570@@QAE@XZ @ 0x0020B570
// match: __ehhandler$??0type_20B570@@QAE@XZ-0x32 @ 0x003062A0
// match: __ehhandler$??0type_20B570@@QAE@XZ @ 0x003062D2

type_20B570::type_20B570()
    : type_2049D0("Options.layout", 0, true), type_1FC320(0, 0, 0, 0), unk_340(this, &type_20B570::sub_20B8A0),
      unk_350(this, &type_20B570::sub_20B8F0)
{
    sub_204FC0("Volume", &this->type_1FC320::unk_00);
    sub_204FC0("Sensitivity", &this->type_1FC320::unk_7C);
    sub_204FC0("Sound", &this->type_1FC320::unk_F8);
    sub_204FC0("Turn", &this->type_1FC320::unk_118);
    sub_204FC0("YAxis", &this->type_1FC320::unk_138);
    sub_204FC0("Controls", &this->type_1FC320::unk_158);
    sub_204FC0("vibration", &this->type_1FC320::unk_178);
    sub_204FC0("VoiceChatSpeakers", &this->type_1FC320::unk_198);
    sub_204FC0("Back", &unk_340);
    sub_204FC0("Accept", &unk_350);
}

// match: ??_Gtype_20B570@@UAEPAXI@Z @ 0x0020B720
// match: ??1type_20B570@@UAE@XZ @ 0x0020B750
// match: __ehhandler$??1type_20B570@@UAE@XZ-0x3F @ 0x003062E0
// match: __ehhandler$??1type_20B570@@UAE@XZ @ 0x0030631F
type_20B570::~type_20B570()
{
}

// match: ?vf_03C@type_20B570@@UAEXXZ @ 0x0020B7F0
void type_20B570::vf_03C()
{
    type_2049D0::vf_03C();
    sub_1FCC80();
    unk_360 = (type_1FD490_value)sub_1C51A0();
    type_1FC320::unk_198.sub_201EC0(unk_360);
}

// match: ?vf_014@type_20B570@@UAEXM@Z @ 0x0020B840
void type_20B570::vf_014(RwReal arg_0)
{
    type_2049D0::vf_014(arg_0);
    RwInt32 var_4 = sub_1C51A0();
    if (var_4 != unk_360)
    {
        unk_360 = (type_1FD490_value)var_4;
        type_1FC320::unk_198.sub_201EC0(unk_360);
    }
}

// match: ?sub_20B8A0@type_20B570@@QAEXXZ @ 0x0020B8A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_20B570::sub_20B8A0()
{
    RwInt32 var_8 = dword_42D2A8 ? 10 : 6;
    type_1FBDA0_menu *l4 = sub_2046C0(var_8);

    sub_1FC310()->sub_1FBDA0(l4);
}

// match: ?sub_20B8F0@type_20B570@@QAEXXZ @ 0x0020B8F0
void type_20B570::sub_20B8F0()
{
    sub_1FCD10();
    sub_1C5220();
    sub_20B8A0();
}

// match: ?sub_20B920@@YAXH@Z @ 0x0020B920
void sub_20B920(RwInt32 arg_0)
{
    dword_42D2A8 = arg_0;
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_20B570@@@kujuUI@@QAE@PAUtype_20B570@@P82@AEXXZ@Z @ 0x0020B930
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_20B570@@@kujuUI@@UAEPAXI@Z @ 0x0020B9A0
// match: ??1?$type_3E7CE8@Utype_20B570@@@kujuUI@@UAE@XZ @ 0x0020B980
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
