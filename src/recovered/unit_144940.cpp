// The triggers' bookkeeping: the handle table, the pools and the spatial
// table, and the queue of section loads.

#include "rw/ostypes.h"
#include "types/type_4D1DB8.h"
#include "types/type_44350.h"
#include "types/type_129_base.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "types/type_3D3548.h"
#include "types/type_92430.h"
#include "rw/baframe.h"
#include "types/type_10F710.h"
#include "types/AddTaskTrigger.h"
#include "types/PulseZoneTrigger.h"
#include "types/EndLevelTrigger.h"
#include "types/PASTrigger.h"
#include "types/CustomTrigger.h"
#include <string.h>
#include "types/SectionTrigger.h"
#include "types/SectionInfo.h"
#include "types/VehicleEnterExitTrigger.h"
#include "types/SoundBankTrigger.h"
#include "types/ConfinedAreaTrigger.h"
#include "types/PlaySoundTrigger.h"
#include "types/StreamClumpTrigger.h"
#include "types/LadderTrigger.h"
#include "types/FogTrigger.h"
#include "types/type_4E5D30.h"
#include "types/asynchload.h"
#include "types/type_4B85F8.h"
#include "rw/baengine.h"
#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigdraw.cpp: the trigger view's activity)
void TrigDrawTriggerEvent(void *pTrigger, RwInt32 nKind, const RwChar *pszName);
#endif
#if !defined(CODFH_SP) || CODFH_SP_PART != 2 // single player compiles the rest in another file (src/sp/units/sp_unit_144940_2.cpp)

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DB9E4
extern const RwReal flt_3DB9E4 = 16.666666f;
// 0x00429D00
RwInt32 dword_429D00 = -1;
// 0x004CFE30
type_4CFE30 *dword_4CFE30[2000];
// 0x004D1D70
RwInt32 dword_4D1D70;
// 0x004D1D74
RwInt32 dword_4D1D74;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4D1D78;
type_16C2A0 dword_4D318C;
type_4D1DB8 unk_4D1DB8;
type_16C2A0 dword_4D1D98;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DB9E4@@3MB @ 0x003DB9E4
// match: ??_C@_0BE@KMGKCMIO@sm_MovedTriggerPool?$AA@ @ 0x003DB9E8
// match: ??_C@_0BD@CAGKEJKI@sm_messageListPool?$AA@ @ 0x003DB9FC
// match: ??_C@_0BI@DGFGPBO@sm_proximityMessagePool?$AA@ @ 0x003DBA10
// match: ??_C@_0DH@IEBENLCE@The?5sm_proximityMessagePool?5was?5@ @ 0x003DBA28
// match: ??_C@_0DC@CJOHEAME@The?5moved?5trigger?5pool?5was?5not?5e@ @ 0x003DBA60
// match: ??_C@_0DI@DMGEJHOO@The?5trigger?5messagelist?5pool?5was@ @ 0x003DBA94
// match: ??_C@_0CO@JOFBBHBD@Some?5trigger?5was?5not?5deleted?5dur@ @ 0x003DBACC
// match: ??_C@_0CN@BIBLIDNL@Adding?5load?5of?5section?5?$CFd?5to?5Asy@ @ 0x003DBAFC
// match: ??_C@_0CF@OGFBPMNH@Section?5being?5removed?5while?5load@ @ 0x003DBB2C
// match: ??_C@_0CD@NBPNNPMH@Section?5to?5load?5was?5loaded?5twice@ @ 0x003DBB54
// match: ??_C@_0CC@KLDIFIAK@Unloading?5more?5than?5one?5section?$CB@ @ 0x003DBB78
// match: ??_C@_0GD@FFONEEJF@Cannot?5unload?5section?5ID?5?$CFd?5in?5b@ @ 0x003DBBA0
// match: ??_C@_0BD@OOBHJELL@m_freeTriggerLists?$AA@ @ 0x003DBC04
// match: .CRT$XCU+0 @ 0x00427114
// match: .CRT$XCU+4 @ 0x00427118
// match: .CRT$XCU+8 @ 0x0042711C
// match: .CRT$XCU+12 @ 0x00427120
// match: ?dword_429D00@@3HA @ 0x00429D00

// match: _$E2 @ 0x0030BB80
// match: _$E3 @ 0x0030E820
// match: _$E5 @ 0x0030BBA0
// match: _$E6 @ 0x0030E830
// match: _$E8 @ 0x0030BBC0
// match: _$E9 @ 0x0030E840
// match: _$E11 @ 0x0030BBE0
// match: _$E12 @ 0x0030E850
// match: ?sub_144940@type_144940@@QAEXPAVTrigger@@@Z @ 0x00144940
// sp-match: ?sub_144940@type_144940@@QAEXPAVTrigger@@@Z @ 0x000EFFD0
// sp-match: _$E2 @ 0x0021DB80
// sp-match: _$E5 @ 0x0021DBA0
// sp-match: _$E8 @ 0x0021DBC0
// sp-match: _$E11 @ 0x0021DBE0
// sp-match: _$E3 @ 0x0021EBF0
// sp-match: _$E6 @ 0x0021EC00
// sp-match: _$E9 @ 0x0021EC10
// sp-match: _$E12 @ 0x0021EC20

void type_144940::sub_144940(Trigger *arg_0)
{
    Trigger *var_4;

    var_4 = unk_08;
    if (var_4)
    {
        if (var_4 == arg_0)
            return;
        var_4->sub_BD200(this);
    }
    if (arg_0)
        arg_0->sub_BD1A0(this);
    unk_08 = arg_0;
}

// match: sub_144990 @ 0x00144990
// sp-match: sub_144990 @ 0x000F0000
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_144990()
{
    RwInt32 var_4;
    type_145830 *local_8;

    dword_4D1D74 = 0;
    dword_4D1D70 = 1;
    dword_429D00 = -1;
    for (var_4 = 0; var_4 < 2000; var_4++)
        dword_4CFE30[var_4] = 0;
    dword_4D318C.sub_16C2C0(400, 0x1C, "sm_proximityMessagePool", 4, 0);
    dword_4D1D78.sub_16C2C0(400, 0x20, "sm_messageListPool", 4, 0);
    dword_4D1D98.sub_16C2C0(0x40, 0x10, "sm_MovedTriggerPool", 4, 0);
    for (var_4 = 0; var_4 < 0x40; var_4++)
    {
        local_8 = (type_145830 *)dword_4D1D98.sub_16C6A0(var_4);
        local_8->unk_00 = -1;
    }
}

// match: sub_144A70 @ 0x00144A70
// sp-match: sub_144A70 @ 0x000F0B70
void sub_144A70()
{
    if (dword_4D1D70)
    {
        sub_144AD0();
        if (dword_4D1D74)
        {
            unk_4D1DB8.sub_145F50();
            dword_4D1D74 = 0;
        }
        dword_4D1D78.sub_16C4D0(1);
        dword_4D318C.sub_16C4D0(1);
        dword_4D1D98.sub_16C4D0(1);
        dword_4D1D70 = 0;
    }
}

// match: sub_144AD0 @ 0x00144AD0
// Warns of what shutdown finds left.
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles out the warnings: an empty body, defined in unit_067B10 (SP 0x5A260)
void sub_144AD0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2000; var_4++)
    {
        if (dword_4CFE30[var_4])
            sub_19A750("Some trigger was not deleted during shutdown!");
    }
    if (dword_4D1D78.in_use())
        sub_19A750("The trigger messagelist pool was not empty at shutdown!");
    if (dword_4D1D98.in_use())
        sub_19A750("The moved trigger pool was not empty at shutdown!");
    if (dword_4D318C.in_use())
        sub_19A750("The sm_proximityMessagePool was not empty at shutdown!");
}
#endif

// match: sub_144B80 @ 0x00144B80
// sp-match: sub_144B80 @ 0x000F0BD0
// Builds the spatial table from the triggers that test their surroundings.
void sub_144B80()
{
    RwInt32 var_4;

    unk_4D1DB8.sub_145EB0(dword_429D00 + 1, dword_4CFE30);
    for (var_4 = 0; var_4 <= dword_429D00; var_4++)
    {
        if (sub_1458B0((Trigger *)dword_4CFE30[var_4]))
            unk_4D1DB8.sub_1464E0((Trigger *)dword_4CFE30[var_4]);
    }
    dword_4D1D74 = 1;
}

// match: ?sub_144C00@@YAHPAVTrigger@@@Z @ 0x00144C00
// sp-match: ?sub_144C00@@YAHPAVTrigger@@@Z @ 0x000F0C30
// Gives the trigger arg_0 the next handle (and a place in the spatial table
// once it is built).
RwInt32 sub_144C00(Trigger *arg_0)
{
    dword_429D00++;
    dword_4CFE30[dword_429D00] = (type_4CFE30 *)arg_0;
    if (dword_4D1D74 && sub_1458B0(arg_0))
        unk_4D1DB8.sub_1464E0(arg_0);
    return dword_429D00;
}

// match: ?sub_144C50@@YAXPAVTrigger@@@Z @ 0x00144C50
// sp-match: ?sub_144C50@@YAXPAVTrigger@@@Z @ 0x000F0090
void sub_144C50(Trigger *arg_0)
{
    dword_4CFE30[arg_0->unk_3C] = 0;
    unk_4D1DB8.sub_146640(arg_0);
}

// match: ?sub_144C80@@YAXPAUtype_3D3548@@PAHH@Z @ 0x00144C80
// sp-match: ?sub_144C80@@YAXPAUtype_3D3548@@PAHH@Z @ 0x000F0C70
// Updates the entity arg_0's trigger volume: the cells of the triggers
// around its frame now (sub_145B40) are walked against the ones it was in
// (*arg_4: their mask and list), and it enters (sub_145060) or leaves
// (sub_145640) each trigger whose bit changed; the new state goes back in
// *arg_4. arg_8 is unused.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_144C80(type_3D3548 *arg_0, RwInt32 *arg_4, RwInt32 arg_8)
{
    RwInt32 var_30;
    RwInt32 bp_2C;
    RwInt32 local_28;
    RwMatrix *local_24;
    type_144E80 *local_20;
    RwInt32 var_1C;
    type_145B40 var18;
    RwInt32 l10;
    RwInt32 local_C;
    type_144E80 *lv_8;
    RwFrame *var_4;

    var_4 = arg_0->get_unk_340();
    local_24 = RwFrameGetLTM(var_4);
    sub_145B40(local_24, &var18, arg_0->unk_2C_4);
    local_20 = var18.unk_04;
    l10 = var18.unk_00;
    bp_2C = 1;
    local_C = 1;
    var_30 = arg_4[0];
    lv_8 = (type_144E80 *)arg_4[1];
    local_28 = sub_144E80(&local_20, &bp_2C, -1);
    var_1C = sub_144E80(&lv_8, &local_C, -1);
    while (1)
    {
        if (var_1C == -1 && local_28 == -1)
            break;
        if (var_1C == -1 || (var_1C > local_28 && local_28 != -1))
        {
            if (local_C & l10)
                sub_145060(arg_0, (Trigger *)dword_4CFE30[local_28]);
            local_28 = sub_144E80(&local_20, &local_C, (RwInt16)local_28);
            continue;
        }
        if (local_28 == -1 || (local_28 > var_1C && var_1C != -1))
        {
            if (bp_2C & var_30)
                sub_145640(arg_0, (Trigger *)dword_4CFE30[var_1C]);
            var_1C = sub_144E80(&lv_8, &bp_2C, (RwInt16)var_1C);
            continue;
        }
        if ((bp_2C & var_30) && !(local_C & l10))
            sub_145640(arg_0, (Trigger *)dword_4CFE30[local_28]);
        if (!(bp_2C & var_30) && (local_C & l10))
            sub_145060(arg_0, (Trigger *)dword_4CFE30[local_28]);
        var_1C = sub_144E80(&lv_8, &bp_2C, (RwInt16)var_1C);
        local_28 = sub_144E80(&local_20, &local_C, (RwInt16)local_28);
    }
    arg_4[0] = l10;
    arg_4[1] = (RwInt32)var18.unk_04;
    // Six slots below the temporaries that no code uses (as sub_D7040's).
    unused_slot();
    unused_slot();
    unused_slot();
    unused_slot();
    unused_slot();
    unused_slot();
}

// match: ?sub_144E80@@YAFPAPAUtype_144E80@@PAHF@Z @ 0x00144E80
// sp-match: ?sub_144E80@@YAFPAPAUtype_144E80@@PAHF@Z @ 0x000F00B0
// The next trigger after arg_8 in the cell list *arg_0 (whose ranges run
// from unk_00 to unk_02), moving *arg_0 on to its range and the bit *arg_4
// along; -1 at the end.
RwInt16 sub_144E80(type_144E80 **arg_0, RwInt32 *arg_4, RwInt16 arg_8)
{
    type_144E80 *var_4;

    for (var_4 = *arg_0; var_4; var_4 = var_4->unk_04)
    {
        if (var_4->unk_00 > arg_8)
        {
            *arg_0 = var_4;
            return var_4->unk_00;
        }
        if (arg_8 != var_4->unk_02 || arg_8 == -1)
            *arg_4 <<= 1;
        if (var_4->unk_02 > arg_8)
        {
            *arg_0 = var_4;
            return var_4->unk_02;
        }
        *arg_4 <<= 1;
    }
    *arg_0 = 0;
    return -1;
}

// match: ?sub_144F20@@YAHPAURwV3d@@PAVTrigger@@@Z @ 0x00144F20
// sp-match: ?sub_144F20@@YAHPAURwV3d@@PAVTrigger@@@Z @ 0x000F0110
// Whether the point arg_0 lies in the trigger arg_4's volume, by its shape:
// a sphere (0), a cylinder (1) or a box (2); 0 for a trigger switched off.
RwInt32 sub_144F20(RwV3d *arg_0, Trigger *arg_4)
{
    if (arg_4 && arg_4->unk_24_0)
    {
        switch (arg_4->get_unk_46())
        {
        case 0:
            return sub_9ACE0(arg_0, (RwV3d *)&arg_4->unk_90, arg_4->get_unk_48());
        case 1:
            return sub_92900(arg_0, &arg_4->unk_60_m, arg_4->get_unk_48(), arg_4->get_unk_4C());
        case 2:
            return sub_9ABE0(arg_0, &arg_4->unk_60_m, arg_4->get_unk_48(), arg_4->get_unk_4C(),
                             arg_4->get_unk_50());
        }
    }
    return 0;
}

// match: ?sub_145000@@YAHPAURwMatrixTag@@PAVTrigger@@@Z @ 0x00145000
// sp-match: ?sub_145000@@YAHPAURwMatrixTag@@PAVTrigger@@@Z @ 0x000F01C0
// The trigger's facing test (vf_028) when it has one (flag 7), else 1.
RwInt32 sub_145000(RwMatrix *arg_0, Trigger *arg_4)
{
    if (!arg_4->unk_24_7)
        return 1;
    return arg_4->vf_028(arg_0);
}

// match: ?sub_145030@@YAHPAURwMatrixTag@@PAVTrigger@@@Z @ 0x00145030
// sp-match: ?sub_145030@@YAHPAURwMatrixTag@@PAVTrigger@@@Z @ 0x000F01E0
// Likewise for its direction test (vf_02C, flag 12).
RwInt32 sub_145030(RwMatrix *arg_0, Trigger *arg_4)
{
    if (!arg_4->unk_24_12)
        return 1;
    return arg_4->vf_02C(arg_0);
}

// match: ?sub_145060@@YAXPAUtype_3D3548@@PAVTrigger@@@Z @ 0x00145060
// sp-match: ?sub_145060@@YAXPAUtype_3D3548@@PAVTrigger@@@Z @ 0x000F0200
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The entity arg_0 enters the trigger arg_4: the trigger's messages, then
// what its kind does. A section trigger a player enters queues its section
// to load (unless it is loaded or loading), unloading the one slot that
// holds none of the sections to keep; the other kinds act for players (or
// for anyone).
void sub_145060(type_3D3548 *arg_0, Trigger *arg_4)
{
    type_10F710 *var_30;
    type_4E5D30 *var_2C;
    RwUInt16 var_28;
    RwInt32 ebp_24;
    type_4E5D30 *var_20;
    RwInt32 l1C;
    SectionTrigger *m_18;
    RwInt32 ebp_14;
    RwUInt16 lv_10;
    RwUInt16 var_C;
    RwInt32 bp_8;
    type_4E5D30 *bp_4;

#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawTriggerEvent(arg_4, 0, NULL);
#endif
    arg_4->sub_BD560(arg_0);
    switch (arg_4->vf_008())
    {
    case 4:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
        {
            m_18 = (SectionTrigger *)arg_4;
            bp_4 = 0;
            var_C = -1;
            lv_10 = 0xFFFF;
            ebp_14 = 0;
            if (SectionInfo::sub_B0140() && m_18->unk_D0)
            {
                if (sub_174640((RwUInt16)m_18->unk_CC))
                {
                    ebp_14 = 1;
                }
                else
                {
                    l1C = 1;
                    ebp_24 = m_18->unk_D0 - 1;
                    var_20 = &dword_4E5D30[ebp_24];
                    if (var_20->get_unk_00() || var_20->get_unk_04())
                    {
                        var_28 = var_20->unk_08;
                        if (var_28 == m_18->unk_C0 || var_28 == m_18->unk_C4 || var_28 == m_18->unk_C8)
                        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                            sub_19A750("Cannot unload section ID %d in bank slot %d because it is specified as one of "
                                       "the sections to keep",
                                       var_28, var_20->get_unk_0A());
#endif
                            l1C = 0;
                        }
                        if (l1C)
                        {
                            if (var_20->get_unk_04() && var_28 == m_18->unk_CC)
                            {
                                ebp_14 = 1;
                            }
                            else
                            {
                                bp_4 = var_20;
                                var_C = var_20->unk_0A;
                                lv_10 = var_28;
                            }
                        }
                        else
                        {
                            ebp_14 = 1;
                        }
                    }
                }
            }
            else
            {
                for (bp_8 = 0; bp_8 < 4; bp_8++)
                {
                    var_2C = &dword_4E5D30[bp_8];
                    if (var_2C->get_unk_08() != m_18->unk_C0 && var_2C->get_unk_08() != m_18->unk_C4
                        && var_2C->get_unk_08() != m_18->unk_C8 && var_2C->get_unk_08() != m_18->unk_CC)
                    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        if (bp_4)
                            sub_19A750("Unloading more than one section!\n");
#endif
                        bp_4 = var_2C;
                        var_C = (RwInt16)bp_8;
                        lv_10 = var_2C->unk_08;
                    }
                    if (var_2C->get_unk_08() == m_18->unk_CC)
                    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                        if (ebp_14)
                            sub_19A750("Section to load was loaded twice \n");
#endif
                        ebp_14 = 1;
                    }
                }
            }
            if (bp_4)
            {
                if (lv_10 != 0xFFFF && !sub_82020(0, lv_10))
                {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                    if (bp_4->get_unk_04())
                        sub_19A750("Section being removed while loading\n");
#endif
                    sub_174030(var_C, 0);
                    bp_4->set_unk_08((RwUInt16)m_18->unk_CC);
                    if (SectionInfo::sub_B0140() && m_18->unk_D0)
                        bp_4->unk_04 = 1;
                }
                sub_82070(m_18->unk_C0, m_18->unk_C4, m_18->unk_C8, m_18->unk_CC);
            }
            if (!ebp_14 && !sub_81FB0(0, "", m_18->unk_CC))
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("Adding load of section %d to AsynchQueue...\n", m_18->unk_CC);
#endif
                sub_81EB0(0, "", m_18->unk_CC);
            }
        }
        break;
    case 23:
        ((AddTaskTrigger *)arg_4)->sub_9EED0(arg_0);
        break;
    case 26:
        ((VehicleEnterExitTrigger *)arg_4)->sub_BF590(arg_0);
        break;
    case 10:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((SoundBankTrigger *)arg_4)->sub_B9D80();
        break;
    case 9:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
        {
            var_30 = (type_10F710 *)arg_0;
            var_30->unk_1A1C = ((ConfinedAreaTrigger *)arg_4)->get_unk_C0();
        }
        break;
    case 13:
        if (((PlaySoundTrigger *)arg_4)->unk_C0)
            ((type_145060_30 *)arg_4)->vf_030();
        else if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((type_145060_30 *)arg_4)->vf_030();
        break;
    case 12:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((type_145060_30 *)arg_4)->vf_030();
        break;
    case 28:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((StreamClumpTrigger *)arg_4)->sub_C6650();
        break;
    case 14:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((type_145060_30 *)arg_4)->vf_030();
        break;
    case 15:
        ((type_145060_30 *)arg_4)->vf_030();
        break;
    case 16:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((type_145060_30 *)arg_4)->vf_030();
        break;
    case 32:
        ((LadderTrigger *)arg_4)->sub_CAC30(arg_0);
        break;
    case 34:
        ((PulseZoneTrigger *)arg_4)->sub_CB960((RwInt32)arg_0);
        break;
    case 36:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((EndLevelTrigger *)arg_4)->sub_CC250((RwInt32)arg_0);
        break;
#ifdef CODFH_SP // single player numbers FogTrigger 37 and PASTrigger 38 (their vf_008, SP 0x124460, 0x1244A0)
    case 37:
#else
    case 38:
#endif
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((FogTrigger *)arg_4)->sub_CC5D0((RwInt32)arg_0);
        break;
#ifdef CODFH_SP
    case 38:
#else
    case 39:
#endif
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((PASTrigger *)arg_4)->sub_CC850((RwInt32)arg_0);
        break;
    }
}

// match: ?sub_145640@@YAXPAUtype_3D3548@@PAVTrigger@@@Z @ 0x00145640
// sp-match: ?sub_145640@@YAXPAUtype_3D3548@@PAVTrigger@@@Z @ 0x000F06F0
// The entity arg_0 leaves the trigger arg_4: the trigger's messages, then
// what its kind does (a player leaves a confined area, and the end-level
// and PAS triggers see a player go).
void sub_145640(type_3D3548 *arg_0, Trigger *arg_4)
{
    type_10F710 *var_4;

#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawTriggerEvent(arg_4, 1, NULL);
#endif
    arg_4->sub_BD780(arg_0);
    switch (arg_4->vf_008())
    {
    case 23:
        ((AddTaskTrigger *)arg_4)->sub_9EFD0(arg_0);
        break;
#ifdef CODFH_SP // two distinct empty members, called separately (SP 0xF0731, 0xF073C)
    case 26:
        ((VehicleEnterExitTrigger *)arg_4)->sp_leave(arg_0);
        break;
    case 32:
        ((LadderTrigger *)arg_4)->sp_leave(arg_0);
        break;
#else
    case 26:
        arg_4->sub_15FB30(arg_0);
        break;
    case 32:
        arg_4->sub_15FB30(arg_0);
        break;
#endif
    case 34:
        ((PulseZoneTrigger *)arg_4)->sub_CB990((RwInt32)arg_0);
        break;
    case 9:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
        {
            var_4 = (type_10F710 *)arg_0;
            var_4->unk_1A1C = 0;
        }
        break;
    case 36:
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((EndLevelTrigger *)arg_4)->sub_CC280((RwInt32)arg_0);
        break;
#ifdef CODFH_SP // single player numbers PASTrigger 38 (its vf_008, SP 0x1244A0; SP 0xF0782)
    case 38:
#else
    case 39:
#endif
        if ((arg_0->unk_2C & 0x3FFFFF0) == 0x10)
            ((PASTrigger *)arg_4)->sub_CC870((RwInt32)arg_0);
        break;
    }
}

// match: sub_145770 @ 0x00145770
// sp-match: sub_145770 @ 0x000F07E0
void *sub_145770()
{
    return dword_4D1D78.sub_16C5A0(0);
}

// match: sub_145790 @ 0x00145790
// sp-match: sub_145790 @ 0x000F07F0
void sub_145790(void *arg_0)
{
    dword_4D1D78.sub_16C710(arg_0);
}

// match: ?sub_1457B0@@YAXPAUTrigger_30@@@Z @ 0x001457B0
// sp-match: ?sub_1457B0@@YAXPAUTrigger_30@@@Z @ 0x000F0800
void sub_1457B0(Trigger_30 *arg_0)
{
    dword_4D318C.sub_16C710(arg_0);
}

// match: ?sub_1457D0@@YAPAUTrigger_30@@XZ @ 0x001457D0
// sp-match: ?sub_1457D0@@YAPAUTrigger_30@@XZ @ 0x000F0810
Trigger_30 *sub_1457D0()
{
    Trigger_30 *var_4;

    var_4 = (Trigger_30 *)dword_4D318C.sub_16C5A0(0);
    var_4->unk_00[2] = 0;
    var_4->unk_00[3] = 0;
    var_4->unk_00[4] = 0;
    var_4->unk_00[6] = 0;
    var_4->unk_00[5] = 0;
    var_4->unk_00[0] = 0;
    var_4->unk_00[1] = 0;
    return var_4;
}

// match: ?sub_145830@@YAPAUtype_145830@@XZ @ 0x00145830
// sp-match: ?sub_145830@@YAPAUtype_145830@@XZ @ 0x000F0840
type_145830 *sub_145830()
{
    type_145830 *var_4;

    var_4 = (type_145830 *)dword_4D1D98.sub_16C5A0(0);
    if (var_4)
    {
        memset(var_4, 0, sizeof(type_145830));
        var_4->unk_00 = -1;
    }
    return var_4;
}

// match: ?sub_145870@@YAXPAUtype_145830@@@Z @ 0x00145870
// sp-match: ?sub_145870@@YAXPAUtype_145830@@@Z @ 0x000F0870
void sub_145870(type_145830 *arg_0)
{
    if (arg_0)
    {
        memset(arg_0, 0, sizeof(type_145830));
        arg_0->unk_00 = -1;
        dword_4D1D98.sub_16C710(arg_0);
    }
}

// match: ?sub_1458B0@@YAHPAVTrigger@@@Z @ 0x001458B0
// sp-match: ?sub_1458B0@@YAHPAVTrigger@@@Z @ 0x000F08A0
// Whether the trigger arg_0 goes in the spatial table: the kinds that test
// their surroundings, or any trigger with blocks.
RwInt32 sub_1458B0(Trigger *arg_0)
{
    switch (arg_0->vf_008())
    {
    case 4:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 23:
    case 28:
    case 32:
    case 34:
    case 36:
        return 1;
    default:
        if (arg_0->unk_30
            && (arg_0->unk_30->unk_00[6] || arg_0->unk_30->unk_00[0] || arg_0->unk_30->unk_00[1]
                || arg_0->unk_30->unk_00[4] || arg_0->unk_30->unk_00[2] || arg_0->unk_30->unk_00[3]))
            return 1;
        return 0;
    }
}

// match: ?sub_145970@@YAXPAUtype_3D3548@@PAUtype_145B40@@@Z @ 0x00145970
// sp-match: ?sub_145970@@YAXPAUtype_3D3548@@PAUtype_145B40@@@Z @ 0x000F0930
// Sends block 6 of each trigger whose bit is set in the cells arg_4 to the
// entity arg_0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_145970(type_3D3548 *arg_0, type_145B40 *arg_4)
{
    RwInt32 var_4;
    type_144E80 *local_8;

    var_4 = 1;
    for (local_8 = arg_4->unk_04; local_8; local_8 = local_8->unk_04)
    {
        if (local_8->unk_00 != -1 && (var_4 & arg_4->unk_00))
            ((Trigger *)dword_4CFE30[local_8->unk_00])->sub_BD8A0(arg_0);
        var_4 <<= 1;
        if (local_8->unk_02 != -1 && (var_4 & arg_4->unk_00))
            ((Trigger *)dword_4CFE30[local_8->unk_02])->sub_BD8A0(arg_0);
        var_4 <<= 1;
    }
}

// match: ?sub_145A10@@YAXPAVTrigger@@@Z @ 0x00145A10
// sp-match: ?sub_145A10@@YAXPAVTrigger@@@Z @ 0x000F09A0
void sub_145A10(Trigger *arg_0)
{
    if (dword_4D1D74 && !unk_4D1DB8.sub_146E80(arg_0))
        unk_4D1DB8.sub_1464E0(arg_0);
}

// match: ?sub_145A40@@YAXPAVTrigger@@@Z @ 0x00145A40
// sp-match: ?sub_145A40@@YAXPAVTrigger@@@Z @ 0x000F0E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_145A40(Trigger *arg_0)
{
    RwInt32 var_4;
    type_3D3548 *loc8;
    RwFrame *local_C;
    RwV3d lcl_18;
    RwMatrix *fp_1C;

    if (dword_4D1D74)
    {
        unk_4D1DB8.sub_146F10();
        unk_4D1DB8.sub_146640(arg_0);
        if (sub_1458B0(arg_0))
            unk_4D1DB8.sub_1464E0(arg_0);
        for (var_4 = 0; var_4 < 0x10; var_4++)
        {
            for (loc8 = dword_4B85F8[var_4].unk_08; loc8; loc8 = loc8->unk_10)
            {
                if (loc8->unk_28_6)
                {
                    local_C = loc8->get_unk_340();
                    fp_1C = RwFrameGetLTM(local_C);
                    if (unk_4D1DB8.sub_146F50(&lcl_18))
                        sub_145B40(fp_1C, (type_145B40 *)&loc8->unk_248, loc8->unk_2C_4);
                }
            }
        }
    }
}

// match: ?sub_145B40@@YAXPAURwMatrixTag@@PAUtype_145B40@@E@Z @ 0x00145B40
// sp-match: ?sub_145B40@@YAXPAURwMatrixTag@@PAUtype_145B40@@E@Z @ 0x000F09D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The triggers around the matrix arg_0's position (the spatial table's
// cell list into arg_4->unk_04) and the mask of those whose volume holds it
// (arg_4->unk_00, a bit per range end); for a player (arg_8) a trigger with
// facing tests also needs the camera to pass one.
void sub_145B40(RwMatrix *arg_0, type_145B40 *arg_4, RwUInt8 arg_8)
{
    RwMatrix *var_20;
    RwCamera *l1C;
    RwMatrix *m_18;
    RwCamera *ebp_14;
    type_144E80 *lv_10;
    RwV3d *var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    var_C = &arg_0->pos;
    arg_4->unk_04 = unk_4D1DB8.sub_1466B0(var_C);
    bp_4 = 1;
    bp_8 = 0;
    for (lv_10 = arg_4->unk_04; lv_10; lv_10 = lv_10->unk_04)
    {
        if (lv_10->unk_00 != -1 && ((Trigger *)dword_4CFE30[lv_10->unk_00])->get_unk_24_3()
            && sub_144F20(var_C, (Trigger *)dword_4CFE30[lv_10->unk_00]))
        {
            if (arg_8 && (((Trigger *)dword_4CFE30[lv_10->unk_00])->unk_24_7
                          || ((Trigger *)dword_4CFE30[lv_10->unk_00])->unk_24_12))
            {
                ebp_14 = (RwCamera *)dword_4E5C74;
                m_18 = RwFrameGetMatrix(RwCameraGetFrame(ebp_14));
                if (((Trigger *)dword_4CFE30[lv_10->unk_00])->unk_24_7
                    && sub_145000(m_18, (Trigger *)dword_4CFE30[lv_10->unk_00]))
                    bp_8 |= bp_4;
                if (((Trigger *)dword_4CFE30[lv_10->unk_00])->unk_24_12
                    && sub_145030(m_18, (Trigger *)dword_4CFE30[lv_10->unk_00]))
                    bp_8 |= bp_4;
            }
            else
            {
                bp_8 |= bp_4;
            }
        }
        bp_4 <<= 1;
        if (lv_10->unk_02 != -1 && ((Trigger *)dword_4CFE30[lv_10->unk_02])->get_unk_24_3()
            && sub_144F20(var_C, (Trigger *)dword_4CFE30[lv_10->unk_02]))
        {
            if (arg_8 && (((Trigger *)dword_4CFE30[lv_10->unk_02])->unk_24_7
                          || ((Trigger *)dword_4CFE30[lv_10->unk_02])->unk_24_12))
            {
                l1C = (RwCamera *)dword_4E5C74;
                var_20 = RwFrameGetMatrix(RwCameraGetFrame(l1C));
                if (((Trigger *)dword_4CFE30[lv_10->unk_02])->unk_24_7
                    && sub_145000(var_20, (Trigger *)dword_4CFE30[lv_10->unk_02]))
                    bp_8 |= bp_4;
                if (((Trigger *)dword_4CFE30[lv_10->unk_02])->unk_24_12
                    && sub_145030(var_20, (Trigger *)dword_4CFE30[lv_10->unk_02]))
                    bp_8 |= bp_4;
            }
            else
            {
                bp_8 |= bp_4;
            }
        }
        bp_4 <<= 1;
    }
    arg_4->unk_00 = bp_8;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART != 1 // single player: sp_unit_144940_2.cpp, the second file
// match: ?sub_145E20@@YAHPBX0@Z @ 0x00145E20
// sp-match: ?sub_145E20@@YAHPBX0@Z @ 0x000F0EC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 __cdecl sub_145E20(const void *arg_0, const void *arg_4)
{
    const RwInt16 *var_4;
    const RwInt16 *local_8;

    local_8 = (const RwInt16 *)arg_0;
    var_4 = (const RwInt16 *)arg_4;
    if (*local_8 < *var_4)
        return -1;
    if (*local_8 > *var_4)
        return 1;
    return 0;
}

// match: ??0type_4D1DB8@@QAE@XZ @ 0x00145E70
// sp-match: ??0type_4D1DB8@@QAE@XZ @ 0x000F0EF0
type_4D1DB8::type_4D1DB8()
{
}

// match: ??1type_4D1DB8@@QAE@XZ @ 0x00145E90
// sp-match: ??1type_4D1DB8@@QAE@XZ @ 0x000F0F10
type_4D1DB8::~type_4D1DB8()
{
}

// match: ?sub_145EB0@type_4D1DB8@@QAEXHPAPAUtype_4CFE30@@@Z @ 0x00145EB0
// sp-match: ?sub_145EB0@type_4D1DB8@@QAEXHPAPAUtype_4CFE30@@@Z @ 0x000F1D80
// Builds the table from the arg_0 triggers of arg_4: those that go in it
// (sub_1458B0) are placed, then the cells are finished and the handles'
// cells cleared.
void type_4D1DB8::sub_145EB0(RwInt32 arg_0, type_4CFE30 **arg_4)
{
    RwInt32 var_4;

    sub_145FB0(arg_0, arg_4);
    sub_146190();
    for (var_4 = 0; var_4 < arg_0; var_4++)
    {
        if (sub_1458B0((Trigger *)arg_4[var_4]))
            sub_146360(arg_4[var_4]);
    }
    sub_1461F0();
    memset(unk_04, -1, sizeof(unk_04));
    unk_00 = 0;
}

// match: ?sub_145F50@type_4D1DB8@@QAEXXZ @ 0x00145F50
// sp-match: ?sub_145F50@type_4D1DB8@@QAEXXZ @ 0x000F0F20
void type_4D1DB8::sub_145F50()
{
    if (unk_13AC > 0)
        unk_13B4.sub_16C4D0(0);
    if (unk_13B0)
    {
        operator delete(unk_13B0);
        unk_13B0 = 0;
    }
}

// match: ?sub_145FB0@type_4D1DB8@@QAEXHPAPAUtype_4CFE30@@@Z @ 0x00145FB0
// sp-match: ?sub_145FB0@type_4D1DB8@@QAEXHPAPAUtype_4CFE30@@@Z @ 0x000F1A00
// The extent of the arg_0 triggers of arg_4 that go in the table, and the
// cells' size (a fiftieth of it); with none, all of space (but z from
// 1e37).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D1DB8::sub_145FB0(RwInt32 arg_0, type_4CFE30 **arg_4)
{
    RwInt32 var_4;
    type_146B70 local_14;

    if (!arg_0)
    {
        unk_1390 = 1e37f;
        unk_138C = -1e37f;
        unk_1398 = 1e37f;
        unk_1394 = 1e37f;
        unk_139C = (unk_1390 - unk_138C) / 50.0f;
        unk_13A0 = (unk_1398 - unk_1394) / 50.0f;
        return;
    }
    unk_1390 = -1e37f;
    unk_138C = 1e37f;
    unk_1398 = -1e37f;
    unk_1394 = 1e37f;
    for (var_4 = 0; var_4 < arg_0; var_4++)
    {
        if (sub_1458B0((Trigger *)arg_4[var_4]))
        {
            sub_146B70(arg_4[var_4], &local_14);
            if (local_14.unk_00 < unk_138C)
                unk_138C = local_14.unk_00;
            if (local_14.unk_04 > unk_1390)
                unk_1390 = local_14.unk_04;
            if (local_14.unk_08 < unk_1394)
                unk_1394 = local_14.unk_08;
            if (local_14.unk_0C > unk_1398)
                unk_1398 = local_14.unk_0C;
        }
    }
    unk_139C = (unk_1390 - unk_138C) / 50.0f;
    unk_13A0 = (unk_1398 - unk_1394) / 50.0f;
}

// match: ?sub_146190@type_4D1DB8@@QAEXXZ @ 0x00146190
// sp-match: ?sub_146190@type_4D1DB8@@QAEXXZ @ 0x000F0F60
void type_4D1DB8::sub_146190()
{
    unk_13A4 = 0;
    unk_13A8 = 0;
    unk_13AC = 0;
    unk_13B0 = 0;
    memset(unk_04, 0, sizeof(unk_04));
}

// match: ?sub_1461F0@type_4D1DB8@@QAEXXZ @ 0x001461F0
// sp-match: ?sub_1461F0@type_4D1DB8@@QAEXXZ @ 0x000F0F90
// Sizes the table from the counts sub_146360 left in the cells: a record
// per occupied cell (and 50 spare), a list element per two triggers in each
// (and 100 spare); then empties the cells.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D1DB8::sub_1461F0()
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 varC;

    for (var_4 = 0; var_4 < 50; var_4++)
    {
        for (v8 = 0; v8 < 50; v8++)
        {
            if (unk_04[v8][var_4] > 0)
            {
                unk_13A8++;
                unk_13AC += (unk_04[v8][var_4] + 1) / 2;
            }
        }
    }
    unk_13AC += 100;
    unk_13B4.sub_16C2C0(unk_13AC, 8, "m_freeTriggerLists", 4, 0);
    unk_13A8 += 50;
    unk_13B0 = (type_1461F0 *)RWSMalloc(unk_13A8 * 8, 0x34250); // not an address: an allocation tag
    for (varC = 0; varC < unk_13A8; varC++)
    {
        unk_13B0[varC].unk_00 = 0;
        unk_13B0[varC].unk_05 = 0;
    }
    memset(unk_04, -1, sizeof(unk_04));
}

// match: ?sub_146360@type_4D1DB8@@QAEXPAUtype_4CFE30@@@Z @ 0x00146360
// sp-match: ?sub_146360@type_4D1DB8@@QAEXPAUtype_4CFE30@@@Z @ 0x000F1B50
// Counts the trigger arg_0 in each cell its extent covers.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D1DB8::sub_146360(type_4CFE30 *arg_0)
{
    RwInt32 var_4;
    RwInt32 loc8;
    RwInt32 local_C;
    RwInt32 var10;
    type_146B70 l20;
    RwInt32 fp_24;
    RwInt32 fp_28;

    unk_13A4++;
    sub_146B70(arg_0, &l20);
    local_C = (RwInt32)((l20.unk_00 - unk_138C) / unk_139C);
    var10 = (RwInt32)((l20.unk_04 - unk_138C) / unk_139C);
    loc8 = (RwInt32)((l20.unk_08 - unk_1394) / unk_13A0);
    var_4 = (RwInt32)((l20.unk_0C - unk_1394) / unk_13A0);
    if (local_C < 0)
        local_C = 0;
    else if (local_C >= 50)
        local_C = 49;
    if (var10 < 0)
        var10 = 0;
    else if (var10 >= 50)
        var10 = 49;
    if (loc8 < 0)
        loc8 = 0;
    else if (loc8 >= 50)
        loc8 = 49;
    if (var_4 < 0)
        var_4 = 0;
    else if (var_4 >= 50)
        var_4 = 49;
    for (fp_24 = loc8; fp_24 <= var_4; fp_24++)
    {
        for (fp_28 = local_C; fp_28 <= var10; fp_28++)
            unk_04[fp_28][fp_24]++;
    }
}

// match: ?sub_1464E0@type_4D1DB8@@QAEXPAVTrigger@@@Z @ 0x001464E0
// sp-match: ?sub_1464E0@type_4D1DB8@@QAEXPAVTrigger@@@Z @ 0x000F1C60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D1DB8::sub_1464E0(Trigger *arg_0)
{
    RwInt32 var_4;
    RwInt32 loc8;
    RwInt32 local_C;
    RwInt32 var10;
    type_146B70 l20;
    RwInt32 fp_24;
    RwInt32 fp_28;

    unk_00++;
    sub_146B70((type_4CFE30 *)arg_0, &l20);
    local_C = (RwInt32)((l20.unk_00 - unk_138C) / unk_139C);
    var10 = (RwInt32)((l20.unk_04 - unk_138C) / unk_139C);
    loc8 = (RwInt32)((l20.unk_08 - unk_1394) / unk_13A0);
    var_4 = (RwInt32)((l20.unk_0C - unk_1394) / unk_13A0);
    if (local_C < 0)
        local_C = 0;
    else if (local_C >= 50)
        local_C = 49;
    if (var10 < 0)
        var10 = 0;
    else if (var10 >= 50)
        var10 = 49;
    if (loc8 < 0)
        loc8 = 0;
    else if (loc8 >= 50)
        loc8 = 49;
    if (var_4 < 0)
        var_4 = 0;
    else if (var_4 >= 50)
        var_4 = 49;
    for (fp_24 = loc8; fp_24 <= var_4; fp_24++)
    {
        for (fp_28 = local_C; fp_28 <= var10; fp_28++)
            sub_146770(fp_28, fp_24, arg_0);
    }
}

// match: ?sub_146640@type_4D1DB8@@QAEXPAVTrigger@@@Z @ 0x00146640
// sp-match: ?sub_146640@type_4D1DB8@@QAEXPAVTrigger@@@Z @ 0x000F17A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D1DB8::sub_146640(Trigger *arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    unk_00--;
    for (var_4 = 0; var_4 < 50; var_4++)
    {
        for (local_8 = 0; local_8 < 50; local_8++)
            sub_146A00(local_8, var_4, arg_0);
    }
}

// match: ?sub_1466B0@type_4D1DB8@@QAEPAUtype_144E80@@PAURwV3d@@@Z @ 0x001466B0
// sp-match: ?sub_1466B0@type_4D1DB8@@QAEPAUtype_144E80@@PAURwV3d@@@Z @ 0x000F1130
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_144E80 *type_4D1DB8::sub_1466B0(RwV3d *arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    var_4 = (RwInt32)((arg_0->x - unk_138C) / unk_139C);
    local_8 = (RwInt32)((arg_0->z - unk_1394) / unk_13A0);
    if (var_4 < 0)
        var_4 = 0;
    if (var_4 >= 50)
        var_4 = 49;
    if (local_8 < 0)
        local_8 = 0;
    if (local_8 >= 50)
        local_8 = 49;
    if (unk_04[var_4][local_8] != -1)
        return unk_13B0[unk_04[var_4][local_8]].unk_00;
    return 0;
}

// match: ?sub_146770@type_4D1DB8@@QAEXHHPAVTrigger@@@Z @ 0x00146770
// sp-match: ?sub_146770@type_4D1DB8@@QAEXHHPAVTrigger@@@Z @ 0x000F17D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Adds the trigger arg_8 to the cell (arg_0, arg_4) (a record for it if it
// has none), keeping the cell's handles in order.
void type_4D1DB8::sub_146770(RwInt32 arg_0, RwInt32 arg_4, Trigger *arg_8)
{
    RwInt16 var_58[32];
    RwInt32 local_10;
    RwInt32 var_C;
    type_144E80 *bp_8;
    type_144E80 *bp_4;

    local_10 = unk_04[arg_0][arg_4];
    if (local_10 == -1)
    {
        unk_04[arg_0][arg_4] = sub_147020();
        local_10 = unk_04[arg_0][arg_4];
    }
    for (type_144E80 *var_60 = 0, *var_5C = unk_13B0[local_10].unk_00; var_5C; var_5C = var_5C->unk_04)
    {
        if (var_5C->unk_00 == -1)
        {
            var_5C->unk_00 = arg_8->unk_3C;
            break;
        }
        else if (var_5C->unk_02 == -1)
        {
            var_5C->unk_02 = arg_8->unk_3C;
            break;
        }
        else
        {
            var_60 = var_5C;
        }
    }
    if (!var_5C)
    {
        type_144E80 *var_64 = (type_144E80 *)unk_13B4.sub_16C5A0(0);
        var_64->unk_00 = arg_8->unk_3C;
        var_64->unk_02 = -1;
        var_64->unk_04 = 0;
        if (var_60)
            var_60->unk_04 = var_64;
        else
            unk_13B0[local_10].unk_00 = var_64;
    }
    var_C = 0;
    for (var_5C = unk_13B0[local_10].unk_00; var_5C; var_5C = var_5C->unk_04)
    {
        if (var_5C->unk_00 != -1)
        {
            var_58[var_C] = var_5C->unk_00;
            var_C++;
        }
        if (var_5C->unk_02 != -1)
        {
            var_58[var_C] = var_5C->unk_02;
            var_C++;
        }
    }
    if (var_C > 1)
        qsort(var_58, var_C, 2, sub_145E20);
    bp_8 = 0;
    var_5C = unk_13B0[local_10].unk_00;
    for (RwInt32 var_68 = 0; var_68 < var_C; var_68++)
    {
        var_5C->unk_00 = var_58[var_68];
        var_68++;
        if (var_68 < var_C)
            var_5C->unk_02 = var_58[var_68];
        else
            var_5C->unk_02 = -1;
        bp_8 = var_5C;
        var_5C = var_5C->unk_04;
    }
    if (var_5C && bp_8)
        bp_8->unk_04 = 0;
    while (var_5C)
    {
        bp_4 = var_5C->unk_04;
        unk_13B4.sub_16C710(var_5C);
        var_5C = bp_4;
    }
    unk_13B0[local_10].unk_04 = 1;
}

// match: ?sub_146A00@type_4D1DB8@@QAEXHHPAVTrigger@@@Z @ 0x00146A00
// sp-match: ?sub_146A00@type_4D1DB8@@QAEXHHPAVTrigger@@@Z @ 0x000F11B0
// Takes the trigger arg_8 out of the cell (arg_0, arg_4), freeing the
// emptied list elements at its end (and the cell's record once none is
// left).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D1DB8::sub_146A00(RwInt32 arg_0, RwInt32 arg_4, Trigger *arg_8)
{
    RwInt32 var_4;
    type_144E80 *v8;
    RwInt32 stk_C;
    type_144E80 *var_10;

    var_4 = unk_04[arg_0][arg_4];
    if (var_4 == -1)
        return;
    for (v8 = unk_13B0[var_4].unk_00; v8; v8 = v8->unk_04)
    {
        if (v8->unk_00 == arg_8->unk_3C)
        {
            v8->unk_00 = -1;
            break;
        }
        else if (v8->unk_02 == arg_8->unk_3C)
        {
            v8->unk_02 = -1;
            break;
        }
    }
    stk_C = 1;
    while (stk_C)
    {
        stk_C = 0;
        var_10 = 0;
        for (v8 = unk_13B0[var_4].unk_00; v8; v8 = v8->unk_04)
        {
            if (!v8->unk_04 && v8->unk_00 == -1 && v8->unk_02 == -1)
            {
                unk_13B4.sub_16C710(v8);
                if (var_10)
                {
                    var_10->unk_04 = 0;
                    stk_C = 1;
                }
                else
                {
                    unk_13B0[var_4].unk_00 = 0;
                    unk_13B0[var_4].unk_05 = 0;
                    unk_04[arg_0][arg_4] = -1;
                }
                break;
            }
            var_10 = v8;
        }
    }
}

// match: ?sub_146B70@type_4D1DB8@@QAEXPAUtype_4CFE30@@PAUtype_146B70@@@Z @ 0x00146B70
// sp-match: ?sub_146B70@type_4D1DB8@@QAEXPAUtype_4CFE30@@PAUtype_146B70@@@Z @ 0x000F19A0
void type_4D1DB8::sub_146B70(type_4CFE30 *arg_0, type_146B70 *arg_4)
{
    switch (((Trigger *)arg_0)->get_unk_46())
    {
    case 0:
        sub_146C30(&((Trigger *)arg_0)->unk_60_m, ((Trigger *)arg_0)->get_unk_48(), arg_4);
        break;
    case 1:
        sub_146C90(&((Trigger *)arg_0)->unk_60_m, ((Trigger *)arg_0)->get_unk_48(),
                   ((Trigger *)arg_0)->get_unk_4C(), arg_4);
        break;
    case 2:
        sub_146CD0(&((Trigger *)arg_0)->unk_60_m, ((Trigger *)arg_0)->get_unk_48(),
                   ((Trigger *)arg_0)->get_unk_4C(), ((Trigger *)arg_0)->get_unk_50(), arg_4);
        break;
    }
}

// match: ?sub_146C30@type_4D1DB8@@QAEXPAURwMatrixTag@@MPAUtype_146B70@@@Z @ 0x00146C30
// sp-match: ?sub_146C30@type_4D1DB8@@QAEXPAURwMatrixTag@@MPAUtype_146B70@@@Z @ 0x000F1290
// A sphere's extent: the radius arg_4 either side of the matrix arg_0's
// position.
void type_4D1DB8::sub_146C30(RwMatrix *arg_0, RwReal arg_4, type_146B70 *arg_8)
{
    RwV3d *var_4;

    var_4 = &arg_0->pos;
    arg_8->unk_00 = var_4->x - arg_4;
    arg_8->unk_04 = arg_4 + var_4->x;
    arg_8->unk_08 = var_4->z - arg_4;
    arg_8->unk_0C = arg_4 + var_4->z;
}

// match: ?sub_146C90@type_4D1DB8@@QAEXPAURwMatrixTag@@MMPAUtype_146B70@@@Z @ 0x00146C90
// sp-match: ?sub_146C90@type_4D1DB8@@QAEXPAURwMatrixTag@@MMPAUtype_146B70@@@Z @ 0x000F1970
// A cylinder's extent: a box its diameter wide and arg_8 high.
void type_4D1DB8::sub_146C90(RwMatrix *arg_0, RwReal arg_4, RwReal arg_8, type_146B70 *arg_C)
{
    sub_146CD0(arg_0, arg_4 * 2, arg_8, arg_4 * 2, arg_C);
}

// match: ?sub_146CD0@type_4D1DB8@@QAEXPAURwMatrixTag@@MMMPAUtype_146B70@@@Z @ 0x00146CD0
// sp-match: ?sub_146CD0@type_4D1DB8@@QAEXPAURwMatrixTag@@MMMPAUtype_146B70@@@Z @ 0x000F12D0
// A box's extent: its eight corners (arg_4, arg_8, arg_C either side of the
// centre) through the matrix arg_0, and their least and greatest x and z.
void type_4D1DB8::sub_146CD0(RwMatrix *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C,
                             type_146B70 *arg_10)
{
    RwV3d var_60[8];

    var_60[0].x = arg_4;
    var_60[0].y = arg_8;
    var_60[0].z = arg_C;
    var_60[1].x = -arg_4;
    var_60[1].y = -arg_8;
    var_60[1].z = -arg_C;
    var_60[2].x = -arg_4;
    var_60[2].y = arg_8;
    var_60[2].z = arg_C;
    var_60[3].x = arg_4;
    var_60[3].y = -arg_8;
    var_60[3].z = -arg_C;
    var_60[4].x = arg_4;
    var_60[4].y = -arg_8;
    var_60[4].z = arg_C;
    var_60[5].x = -arg_4;
    var_60[5].y = arg_8;
    var_60[5].z = -arg_C;
    var_60[6].x = arg_4;
    var_60[6].y = arg_8;
    var_60[6].z = -arg_C;
    var_60[7].x = -arg_4;
    var_60[7].y = -arg_8;
    var_60[7].z = arg_C;
    sub_141590(var_60, var_60, 8, arg_0);
    arg_10->unk_00 = 1.0e37f;
    arg_10->unk_04 = -1.0e37f;
    arg_10->unk_08 = 1.0e37f;
    arg_10->unk_0C = -1.0e37f;
    for (RwInt32 var_64 = 0; var_64 < 8; var_64++)
    {
        if (var_60[var_64].x < arg_10->unk_00)
            arg_10->unk_00 = var_60[var_64].x;
        if (var_60[var_64].x > arg_10->unk_04)
            arg_10->unk_04 = var_60[var_64].x;
        if (var_60[var_64].z < arg_10->unk_08)
            arg_10->unk_08 = var_60[var_64].z;
        if (var_60[var_64].z > arg_10->unk_0C)
            arg_10->unk_0C = var_60[var_64].z;
    }
}

// match: ?sub_146E80@type_4D1DB8@@QAEHPAVTrigger@@@Z @ 0x00146E80
// sp-match: ?sub_146E80@type_4D1DB8@@QAEHPAVTrigger@@@Z @ 0x000F1650
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4D1DB8::sub_146E80(Trigger *arg_0)
{
    RwInt32 var_4;
    type_144E80 *local_8;

    for (var_4 = 0; var_4 < unk_13A8; var_4++)
    {
        for (local_8 = unk_13B0[var_4].unk_00; local_8; local_8 = local_8->unk_04)
        {
            if (local_8->unk_00 == arg_0->unk_3C || local_8->unk_02 == arg_0->unk_3C)
                return 1;
        }
    }
    return 0;
}

// match: ?sub_146F10@type_4D1DB8@@QAEXXZ @ 0x00146F10
// sp-match: ?sub_146F10@type_4D1DB8@@QAEXXZ @ 0x000F16B0
void type_4D1DB8::sub_146F10()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < unk_13A8; var_4++)
        unk_13B0[var_4].unk_04 = 0;
}

// match: ?sub_146F50@type_4D1DB8@@QAEHPAURwV3d@@@Z @ 0x00146F50
// sp-match: ?sub_146F50@type_4D1DB8@@QAEHPAURwV3d@@@Z @ 0x000F16E0
// Whether the cell of the point arg_0 changed since sub_146F10 (a point
// outside any cell counts as changed).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4D1DB8::sub_146F50(RwV3d *arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    var_4 = (RwInt32)((arg_0->x - unk_138C) / unk_139C);
    local_8 = (RwInt32)((arg_0->z - unk_1394) / unk_13A0);
    if (var_4 < 0)
        var_4 = 0;
    if (var_4 >= 50)
        var_4 = 49;
    if (local_8 < 0)
        local_8 = 0;
    if (local_8 >= 50)
        local_8 = 49;
    if (unk_04[var_4][local_8] != -1)
        return unk_13B0[unk_04[var_4][local_8]].unk_04;
    return 1;
}

// match: ?sub_147020@type_4D1DB8@@QAEHXZ @ 0x00147020
// sp-match: ?sub_147020@type_4D1DB8@@QAEHXZ @ 0x000F1770
// Takes the first free cell record (marking it used); -1 when none is.
RwInt32 type_4D1DB8::sub_147020()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < unk_13A8; var_4++)
    {
        if (!unk_13B0[var_4].unk_05)
        {
            unk_13B0[var_4].unk_05 = 1;
            return var_4;
        }
    }
    return -1;
}

#ifdef CODFH_SP
// ?sp_leave@LadderTrigger@@QAEXPAUtype_3D3548@@@Z (single player only, folded into SP 0xD60D0):
// defined here, in single player's second file, away from its caller sub_145640.
void LadderTrigger::sp_leave(type_3D3548 *arg_0)
{
}
#endif
#endif
