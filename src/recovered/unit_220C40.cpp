/*
 * The team selection's base (game/ingamepages.h): the two teams to join,
 * their flags shown as each is focused, and the flags' looks loaded from
 * their libraries.
 */
#include <string.h>
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EA770
extern const RwReal flt_3EA770 = 0.01f;
// 0x003EA774
extern const RwReal flt_3EA774 = 0.01f;
// 0x003EA778
extern const RwReal flt_3EA778 = 16.666666f;
// 0x0042D2D4
const RwChar *off_42D2D4[4] = { "w_flagsGB", "w_flagsUS", "w_flagsRU", "w_flagsDE" };
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA770@@3MB @ 0x003EA770
// match: ?flt_3EA774@@3MB @ 0x003EA774
// match: ?flt_3EA778@@3MB @ 0x003EA778
// match: ??_C@_0L@GIDDOABI@team2focus?$AA@ @ 0x003EA77C
// match: ??_C@_0L@FJNLPKIF@team1focus?$AA@ @ 0x003EA788
// match: ??_7type_220C40@@6B@ @ 0x003EA798
// match: ??_C@_07LHPBNBHM@w_blank?$AA@ @ 0x003EA7E8
// match: ??_7?$type_3E7CE8@Utype_220C40@@@kujuUI@@6B@ @ 0x003EA7F0
// match: __ehhandler$??0type_220C40@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425754
// match: __ehhandler$??0type_220C40@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00425794
// match: __ehhandler$??1type_220C40@@UAE@XZ>1>8 @ 0x004257B0
// match: __ehhandler$??1type_220C40@@UAE@XZ>1 @ 0x004257F0
// match: __ehhandler$?vf_03C@type_220C40@@UAEXXZ>1>8 @ 0x0042580C
// match: __ehhandler$?vf_03C@type_220C40@@UAEXXZ>1 @ 0x0042582C
// match: ?off_42D2D4@@3PAPBDA @ 0x0042D2D4
// match: ?dword_42D2E4@?1??vf_03C@type_220C40@@UAEXXZ@4PBDB @ 0x0042D2E4

// match: ??0type_220C40@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00220C40
// match: __ehhandler$??0type_220C40@@QAE@PBDPAUtype_21A5E0@@@Z-0x74 @ 0x003086B0
// match: __ehhandler$??0type_220C40@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00308724

type_220C40::type_220C40(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, &unk_1B0), unk_154(this, &type_220C40::sub_220FE0),
      unk_160(this, &type_220C40::sub_221050), unk_16C(1), unk_170(1), unk_174(1),
      unk_178(this, &type_220C40::sub_2210C0), unk_184(this, &type_220C40::sub_2210E0)
{
    sub_204FC0("team1", &unk_154);
    sub_204FC0("team2", &unk_160);
    sub_204FC0("flag", &unk_190);
    sub_204FC0("team1focus", &unk_178);
    sub_204FC0("team2focus", &unk_184);
    unk_1B0.sub_1EFCF0("team1", &unk_1BC[0]);
    unk_1B0.sub_1EFCF0("team2", &unk_1BC[1]);
    for (RwInt32 var_10 = 0; var_10 < 3; var_10++)
    {
        unk_198[var_10] = 0;
        unk_1A4[var_10] = 0;
    }
}

// match: ??_Gtype_220C40@@UAEPAXI@Z @ 0x00220E70
// match: ??1type_220C40@@UAE@XZ @ 0x00220EA0
// match: __ehhandler$??1type_220C40@@UAE@XZ-0x74 @ 0x00308730
// match: __ehhandler$??1type_220C40@@UAE@XZ @ 0x003087A4
type_220C40::~type_220C40()
{
    sub_221430();
}

// match: ?vf_008@type_220C40@@UAEXXZ @ 0x00220F90
void type_220C40::vf_008()
{
    type_21CB10::vf_008();
    RwInt32 var_4 = 0;

    if (sub_1C43A0() == 4)
        var_4 = 1;
    sub_1E8B50(unk_1BC[var_4]);
}

// match: ?sub_220FE0@type_220C40@@QAEXXZ @ 0x00220FE0
void type_220C40::sub_220FE0()
{
    if (unk_130)
    {
        if (sub_221100(2))
            unk_130->sub_21C200(3, 2);
        else
            unk_130->sub_21C200(0, 0);
    }
    else
    {
        sub_221100(2);
        sub_1C4380(2);
        sub_1C4B10();
    }
}

// match: ?sub_221050@type_220C40@@QAEXXZ @ 0x00221050
void type_220C40::sub_221050()
{
    if (unk_130)
    {
        if (sub_221100(4))
            unk_130->sub_21C200(3, 2);
        else
            unk_130->sub_21C200(0, 0);
    }
    else
    {
        sub_221100(4);
        sub_1C4380(4);
        sub_1C4B10();
    }
}

// match: ?sub_2210C0@type_220C40@@QAEXXZ @ 0x002210C0
void type_220C40::sub_2210C0()
{
    sub_221140(2);
}

// match: ?sub_2210E0@type_220C40@@QAEXXZ @ 0x002210E0
void type_220C40::sub_2210E0()
{
    sub_221140(4);
}

// match: ?sub_221100@type_220C40@@QAE_NH@Z @ 0x00221100
bool type_220C40::sub_221100(RwInt32 arg_0)
{
    if (unk_170 != arg_0)
    {
        unk_174 = unk_170;
        unk_170 = arg_0;
        return true;
    }
    return false;
}

// match: ?sub_221140@type_220C40@@QAE_NH@Z @ 0x00221140
bool type_220C40::sub_221140(RwInt32 arg_0)
{
    if (!unk_198[0].sub_E87C0() && unk_16C != arg_0)
    {
        unk_16C = arg_0;
        switch (unk_16C)
        {
        case 2:
            unk_190.sub_1E7510(unk_1A4[0]);
            break;
        case 4:
            unk_190.sub_1E7510(unk_1A4[1]);
            break;
        default:
            unk_190.sub_1E7510(unk_1A4[2]);
            break;
        }
        return true;
    }
    return false;
}

// match: ?vf_03C@type_220C40@@UAEXXZ @ 0x002211F0
// match: __ehhandler$?vf_03C@type_220C40@@UAEXXZ-0x23 @ 0x003087B0
// match: __ehhandler$?vf_03C@type_220C40@@UAEXXZ @ 0x003087D3
void type_220C40::vf_03C()
{
    // The flags' library for none (a static: the image has "w_blank" after the
    // constructor's vtable, with this function, and its pointer after the team table).
    static const RwChar *dword_42D2E4 = "w_blank";
    sub_221430();
    RwInt32 var_10 = sub_1C4480(2);

    if (var_10 != -1)
        unk_198[0] = sub_1ED040(off_42D2D4[var_10]);
    var_10 = sub_1C4480(4);
    if (var_10 != -1)
        unk_198[1] = sub_1ED040(off_42D2D4[var_10]);
    unk_198[2] = sub_1ED040(dword_42D2E4);
    if (!unk_198[0].sub_E87C0() && !unk_198[1].sub_E87C0() && !unk_198[2].sub_E87C0())
    {
        type_1E3BA0 *var_14;
        type_1E7410 *var_18;
        type_1E3BA0_state *var_30[6];

        for (RwInt32 var_34 = 0; var_34 < 3; var_34++)
        {
            memset(var_30, 0, sizeof(var_30));
            var_18 = unk_198[var_34]->sub_1ED630("normal");
            var_30[0] = (type_1E3BA0_state *)var_18;
            sub_1E3C10(var_30);
            var_14 = new type_1E3BA0(var_30, 0);
            unk_1A4[var_34] = var_14;
        }
    }
}

// match: ?sub_221430@type_220C40@@QAEXXZ @ 0x00221430
void type_220C40::sub_221430()
{
    for (RwInt32 var_4 = 0; var_4 < 3; var_4++)
    {
        unk_198[var_4] = 0;
        delete unk_1A4[var_4];
        unk_1A4[var_4] = 0;
    }
}

// match: ?vf_024@type_220C40@@UAEHXZ @ 0x002214D0
RwInt32 type_220C40::vf_024()
{
    return in_pause_menu() ? 0x1A : 0x12;
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_220C40@@@kujuUI@@QAE@PAUtype_220C40@@P82@AEXXZ@Z @ 0x00221500
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_220C40@@@kujuUI@@UAEPAXI@Z @ 0x00221560
// match: ??1?$type_3E7CE8@Utype_220C40@@@kujuUI@@UAE@XZ @ 0x00221540
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
