/*
 * The weapon selection (game/ingamepages.h): the weapon class picked and
 * set, its picture per team, and the weapon classes' selector (the option
 * selector's instance over type_224010_value, with that instance's map
 * code).
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003EAB90
extern const RwReal flt_3EAB90 = 0.01f;
// 0x003EAB94
extern const RwReal flt_3EAB94 = 0.01f;
// 0x003EAB98
extern const RwReal flt_3EAB98 = 16.666666f;
#endif
// End of its data definitions.

using namespace kujuUI;

// match: ??0type_223280@@QAE@HPAUtype_21A5E0@@@Z @ 0x00223280
// match: __ehhandler$??0type_223280@@QAE@HPAUtype_21A5E0@@@Z-0xD1 @ 0x00308BE0
// match: __ehhandler$??0type_223280@@QAE@HPAUtype_21A5E0@@@Z @ 0x00308CB1

type_223280::type_223280(RwInt32 arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0 == 0 ? "weaponselect.layout" : "initialweaponselect.layout", arg_4, &unk_1BC),
      unk_154(this, &type_223280::sub_223890), unk_160(this, &type_223280::sub_223830),
      unk_16C(this, &type_223280::sub_223F50), unk_178(this, &type_223280::vf_040), unk_190(2),
      unk_1C8(0, &unk_154)
{
    sub_204FC0("selectweapon", &unk_160);
    sub_204FC0("weapon", &unk_184);
    sub_204FC0("weaponselect", &unk_1C8);
    sub_204FC0("weaponhint", &unk_1E8);
    if (arg_0 == 0)
        sub_204FC0("WeaponBack", &unk_178);
    for (RwInt32 i = 0; i < 2; i++)
    {
        unk_194[i] = 0;
        for (RwInt32 j = 0; j < 4; j++)
            unk_19C[i][j] = 0;
    }
    unk_1C8.sub_1FCEB0((type_224010_value)0, type_1CB670("Machine Gun", 0));
    unk_1C8.sub_1FCEB0((type_224010_value)1, type_1CB670("Rifle", 0));
    unk_1C8.sub_1FCEB0((type_224010_value)2, type_1CB670("Sniper Rifle", 0));
    unk_1C8.sub_1FCEB0((type_224010_value)3, type_1CB670("Heavy MG", 0));
}

// match: ??_Gtype_223280@@UAEPAXI@Z @ 0x002236B0
// match: ??1type_223280@@UAE@XZ @ 0x002236E0
// match: __ehhandler$??1type_223280@@UAE@XZ-0x90 @ 0x00308CC0
// match: __ehhandler$??1type_223280@@UAE@XZ @ 0x00308D50
type_223280::~type_223280()
{
    sub_223C50();
}

// match: ?vf_008@type_223280@@UAEXXZ @ 0x002237F0
void type_223280::vf_008()
{
    type_21CB10::vf_008();
    RwInt32 var_4 = sub_1C4360();
}

// match: ?vf_014@type_223280@@UAEXM@Z @ 0x00223810
void type_223280::vf_014(RwReal arg_0)
{
    type_21CB10::vf_014(arg_0);
}

// match: ?sub_223830@type_223280@@QAEXXZ @ 0x00223830
void type_223280::sub_223830()
{
    type_224010_value var_4 = unk_1C8.sub_1FD030();

    sub_1C4340(var_4);
    if (unk_130)
        unk_130->sub_21C200(0, 0);
    else
        sub_1C4B10();
}

// match: ?sub_223890@type_223280@@QAEXXZ @ 0x00223890
void type_223280::sub_223890()
{
    sub_223D00(unk_1C8.sub_1FD030());
}

// match: ?givenFocus@type_223280@@UAEXXZ @ 0x002238C0
void type_223280::givenFocus()
{
    sub_20EA40();
    if (!unk_194[0].sub_E87C0())
    {
        if (sub_1C43A0() == 1)
            sub_1C5210();
        sub_223940(sub_1C43A0());
        type_224010_value var_4 = (type_224010_value)sub_1C4360();

        // A compiled-out check (it shifts the registers).
        if (!unk_190)
        {
        }
        sub_223D00(var_4);
        unk_1C8.sub_201EC0(var_4);
    }
    type_21CB10::givenFocus();
}

// match: ?sub_223940@type_223280@@QAE_NH@Z @ 0x00223940
bool type_223280::sub_223940(RwInt32 arg_0)
{
    if (unk_190 != arg_0)
    {
        unk_190 = arg_0;
        return true;
    }
    return false;
}

// The loading: the weapons' libraries of the two sides' teams, then the
// looks "weapon1" to "weapon4" from each.
// match: ?vf_03C@type_223280@@UAEXXZ @ 0x00223970
// match: __ehhandler$?vf_03C@type_223280@@UAEXXZ-0x2E @ 0x00308D60
// match: __ehhandler$?vf_03C@type_223280@@UAEXXZ @ 0x00308D8E
void type_223280::vf_03C()
{
    // The weapons' bitmap libraries by team (0x42D2E8, a static: its literals come out
    // with this function, as the image has them).
    static const RwChar *off_42D2E8[4] = { "w_weaponsGB", "w_weaponsUS", "w_weaponsRU", "w_weaponsDE" };
    type_1E7410 *m_18;
    type_1E3BA0 *ebp_14;
    RwInt32 lv_10;

    sub_223C50();
    lv_10 = sub_1C4480(2);
    if (lv_10 != -1)
        unk_194[0] = sub_1ED040(off_42D2E8[lv_10]);
    lv_10 = sub_1C4480(4);
    if (lv_10 != -1)
        unk_194[1] = sub_1ED040(off_42D2E8[lv_10]);
    if (!unk_194[0].sub_E87C0() && !unk_194[1].sub_E87C0())
    {
        type_1A5EA0 lv_50;
        type_1E3BA0_state *lv_30[6];

        for (RwInt32 i = 0; i < 2; i++)
        {
            for (RwInt32 j = 0; j < 4; j++)
            {
                lv_50 = "weapon";
                lv_50.sub_1C8540(j + 1);
                memset(lv_30, 0, sizeof(lv_30));
                m_18 = unk_194[i]->sub_1ED630(lv_50.c_str());
                lv_30[0] = (type_1E3BA0_state *)m_18;
                sub_1E3C10(lv_30);
                ebp_14 = new type_1E3BA0(lv_30, 0);
                unk_19C[i][j] = ebp_14;
            }
        }
    }
}

// match: ?sub_223C50@type_223280@@QAEXXZ @ 0x00223C50
void type_223280::sub_223C50()
{
    for (RwInt32 var_4 = 0; var_4 < 2; var_4++)
    {
        unk_194[var_4] = 0;
        for (RwInt32 var_8 = 0; var_8 < 4; var_8++)
            delete unk_19C[var_4][var_8];
    }
}

// Its picture and hint for the weapon class arg_0: the look for the class
// and team shown (while the looks are loaded), and the class's text with its
// grenades.
// match: ?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z @ 0x00223D00
// match: __ehhandler$?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z-0x28 @ 0x00308DA0
// match: __ehhandler$?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z @ 0x00308DC8
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_223280::sub_223D00(type_224010_value arg_0)
{
    unk_18C = arg_0;
    if (!unk_194[0].sub_E87C0() && unk_18C >= 0 && unk_18C <= 3)
    {
        RwInt32 v6C = 0;

        if (unk_190 == 4)
            v6C = 1;
        unk_184.sub_1E7510(unk_19C[v6C][unk_18C]);
    }
    type_1CB670 var_68 = sub_1C43C0(unk_190, unk_18C);
    RwInt32 lcl_4C = sub_1AF2C0(arg_0);
    type_1CB670 local_48;

    local_48.sub_202430(lcl_4C);
    type_1CB670 var_2C = sub_1CB7B0("Grenades: %1", local_48.c_str(), 0);

    var_68.sub_1FBB90(*sub_1CB9B0()).sub_1FBB90(*sub_1CB9B0()).sub_1FBB90(var_2C);
    unk_1E8.sub_1F28C0(var_68);
}

// match: ?sub_223F50@type_223280@@QAEXXZ @ 0x00223F50
void type_223280::sub_223F50()
{
    RwInt32 var_4 = 1;

    var_4++;
    var_4 = var_4;
}

// match: ?vf_024@type_223280@@UAEHXZ @ 0x00223F80
RwInt32 type_223280::vf_024()
{
    return in_pause_menu() ? 0x2A : 0x22;
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_223280@@@kujuUI@@QAE@PAUtype_223280@@P82@AEXXZ@Z @ 0x00223FB0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_223280@@@kujuUI@@UAEPAXI@Z @ 0x00224280
// match: ??1?$type_3E7CE8@Utype_223280@@@kujuUI@@UAE@XZ @ 0x00223FF0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

// The selector's instance's map code and deleting destructor.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EAB90@@3MB @ 0x003EAB90
// match: ?flt_3EAB94@@3MB @ 0x003EAB94
// match: ?flt_3EAB98@@3MB @ 0x003EAB98
// match: ??_C@_08IHIHKHMN@Heavy?5MG?$AA@ @ 0x003EAB9C
// match: ??_C@_0N@PNCKKCNC@Sniper?5Rifle?$AA@ @ 0x003EABA8
// match: ??_C@_05NMFDOHOF@Rifle?$AA@ @ 0x003EABB8
// match: ??_C@_0M@EEIFOLGK@Machine?5Gun?$AA@ @ 0x003EABC0
// match: ??_C@_0L@DHEKEDIL@WeaponBack?$AA@ @ 0x003EABCC
// match: ??_C@_0L@DKJBEONL@weaponhint?$AA@ @ 0x003EABD8
// match: ??_C@_0N@HCBEOIIM@weaponselect?$AA@ @ 0x003EABE4
// match: ??_C@_0N@GBNOBPPG@selectweapon?$AA@ @ 0x003EABF4
// match: ??_7type_223280@@6B@ @ 0x003EAC08
// match: ??_C@_0BL@FLJCFIAK@initialweaponselect?4layout?$AA@ @ 0x003EAC58
// match: ??_C@_0BE@MFLLJJE@weaponselect?4layout?$AA@ @ 0x003EAC74
// match: ??_C@_0M@JBEBLHIA@w_weaponsDE?$AA@ @ 0x003EAC88
// match: ??_C@_0M@MDCIHKBD@w_weaponsRU?$AA@ @ 0x003EAC94
// match: ??_C@_0M@JADNMLBA@w_weaponsUS?$AA@ @ 0x003EACA0
// match: ??_C@_0M@NMEGJPBO@w_weaponsGB?$AA@ @ 0x003EACAC
// match: ??_C@_0N@OOFAJEHH@Grenades?3?5?$CF1?$AA@ @ 0x003EACB8
// match: ??_7?$type_3E7CE8@Utype_223280@@@kujuUI@@6B@ @ 0x003EACC8
// match: ??_7?$type_1FCDC0@W4type_224010_value@@@@6B@ @ 0x003EACD8
// match: __ehhandler$??0type_223280@@QAE@HPAUtype_21A5E0@@@Z>1>8 @ 0x00425BEC
// match: __ehhandler$??0type_223280@@QAE@HPAUtype_21A5E0@@@Z>1 @ 0x00425C5C
// match: __ehhandler$??1type_223280@@UAE@XZ>1>8 @ 0x00425C78
// match: __ehhandler$??1type_223280@@UAE@XZ>1 @ 0x00425CC8
// match: __ehhandler$?vf_03C@type_223280@@UAEXXZ>1>8 @ 0x00425CE4
// match: __ehhandler$?vf_03C@type_223280@@UAEXXZ>1 @ 0x00425D0C
// match: __ehhandler$?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z>1>8 @ 0x00425D28
// match: __ehhandler$?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z>1 @ 0x00425D50
// match: __ehhandler$??0?$type_1FCDC0@W4type_224010_value@@@@QAE@PAW4type_224010_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00425D6C
// match: __ehhandler$??0?$type_1FCDC0@W4type_224010_value@@@@QAE@PAW4type_224010_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00425D74
// match: __ehhandler$??1?$type_1FCDC0@W4type_224010_value@@@@UAE@XZ>1>8 @ 0x00425D90
// match: __ehhandler$??1?$type_1FCDC0@W4type_224010_value@@@@UAE@XZ>1 @ 0x00425D98
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_224010_value@@@@QAEXABW4type_224010_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00425DB4
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_224010_value@@@@QAEXABW4type_224010_value@@ABUtype_1CB670@@@Z>1 @ 0x00425DCC
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00425DE8
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@@Z>1 @ 0x00425DF0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00425E0C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00425E24
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00425E34
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00425E48
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00425E64
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00425E6C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00425E88
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00425E98
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00425EA8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00425EBC
// match: ?off_42D2E8@?1??vf_03C@type_223280@@UAEXXZ@4PAPBDA @ 0x0042D2E8

// match: ??_G?$type_1FCDC0@W4type_224010_value@@@@UAEPAXI@Z @ 0x002242B0
// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@@Z @ 0x002242E0
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@@Z @ 0x00224470
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x00308E50
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@@Z @ 0x00308E58
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x002247C0
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00224840
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00224910
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z @ 0x00224980
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x00308E70
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@2@D@Z @ 0x00308E81
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00224A70
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00308E90
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00308E98
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00225000
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00225060
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00308EB0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_224010_value@@Utype_1CB670@@U?$less@W4type_224010_value@@@std@@V?$allocator@U?$pair@$$CBW4type_224010_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00225180

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// The constructor alone builds them, so they are instantiated whole.
template struct type_3E7CE8<type_223280>;

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@W4type_224010_value@@@@QAE@PAW4type_224010_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00224010
// match: __ehhandler$??0?$type_1FCDC0@W4type_224010_value@@@@QAE@PAW4type_224010_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00308DE0
// match: __ehhandler$??0?$type_1FCDC0@W4type_224010_value@@@@QAE@PAW4type_224010_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00308DE8

// match: ??1?$type_1FCDC0@W4type_224010_value@@@@UAE@XZ @ 0x002240A0
// match: __ehhandler$??1?$type_1FCDC0@W4type_224010_value@@@@UAE@XZ-0x8 @ 0x00308E00
// match: __ehhandler$??1?$type_1FCDC0@W4type_224010_value@@@@UAE@XZ @ 0x00308E08

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_224010_value@@@@QAEXABW4type_224010_value@@ABUtype_1CB670@@@Z @ 0x00224100
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_224010_value@@@@QAEXABW4type_224010_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00308E20
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_224010_value@@@@QAEXABW4type_224010_value@@ABUtype_1CB670@@@Z @ 0x00308E38

// Its hook told the value changed: the other instances' copies are folded
// (/OPT:ICF) into this one.
// match: ?sub_2251F0@?$type_1FCDC0@W4type_224010_value@@@@QAEXXZ @ 0x002251F0

