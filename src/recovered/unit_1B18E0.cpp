// The network messages' own methods (game/netmsg.h): a point message's
// write and read, the scores' constructors and ids, and the full game
// state and rules messages.

#include <xtl.h>

#include "game/netmsg.h"
#include "game/data.h"
#include "game/bombsites.h"
#include "game/flags.h"
#include "game/mpgame.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/functions.h"
#include "game/debugtext.h"
#include "game/netplayer.h"
#include "game/parsedfile.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E1E18
extern const RwReal flt_3E1E18 = 16.666666f;
// 0x003E1E1C
extern const RwReal flt_3E1E1C = 0.01f;
// 0x003E1E20
extern const RwReal flt_3E1E20 = 0.01f;
// 0x003E1E24
extern const RwReal flt_3E1E24 = 0.01f;
// 0x003E1E28
extern const RwReal flt_3E1E28 = 0.01f;
// 0x003E1E2C
extern const RwReal flt_3E1E2C = 16.666666f;
// 0x003E1E30
extern const RwReal flt_3E1E30 = 16.666666f;
// 0x003E1E34
extern const RwReal flt_3E1E34 = 0.01f;
// 0x003E1E38
extern const RwReal flt_3E1E38 = 0.01f;
// 0x0042CAB8
RwReal flt_42CAB8 = 1.0f;
// 0x0042CABC
RwInt32 dword_42CABC = 1;
// 0x004FB9C8
RwInt32 dword_4FB9C8;
// 0x004FB9CC
DWORD dword_4FB9CC;
// 0x004FB9D0
RwInt32 dword_4FB9D0;
// 0x004FB9D4
RwInt32 dword_4FB9D4;
// 0x004FBAA8
#ifndef CODFH_PLAIN
RwInt32 dword_4FBAA8;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E1E18@@3MB @ 0x003E1E18
// match: ?flt_3E1E1C@@3MB @ 0x003E1E1C
// match: ?flt_3E1E20@@3MB @ 0x003E1E20
// match: ?flt_3E1E24@@3MB @ 0x003E1E24
// match: ?flt_3E1E28@@3MB @ 0x003E1E28
// match: ?flt_3E1E2C@@3MB @ 0x003E1E2C
// match: ?flt_3E1E30@@3MB @ 0x003E1E30
// match: ?flt_3E1E34@@3MB @ 0x003E1E34
// match: ?flt_3E1E38@@3MB @ 0x003E1E38
// match: ??_7type_3E1E3C@@6B@ @ 0x003E1E3C
// match: ??_7type_3E1E48@@6B@ @ 0x003E1E48
// match: ??_C@_0DB@PKGFHPCJ@SCORE?3?5?$CFd?5points?5for?5returning?5O@ @ 0x003E1E54
// match: ??_C@_0DI@FMACGHHI@SCORE?3?5?$CFd?5points?5for?5returning?5e@ @ 0x003E1E88
// match: ??_C@_0DB@NFDPGJMM@SCORE?3?5?$CFd?5points?5for?5picking?5up?5@ @ 0x003E1EC0
// match: ??_C@_0DD@HPCLPKMM@SCORE?3?5?$CFd?5points?5for?5getting?5fla@ @ 0x003E1EF4
// match: ??_C@_0CK@ICLCDHBL@SCORE?3?5?$CFd?5points?5for?5destroying?5@ @ 0x003E1F28
// match: ??_C@_0CG@HIOFDHLB@SCORE?3?5?$CFd?5points?5for?5defusing?5a?5@ @ 0x003E1F54
// match: ??_C@_0CG@ODPIJBO@SCORE?3?5?$CFd?5points?5for?5planting?5a?5@ @ 0x003E1F7C
// match: ??_C@_0BO@MNLCKAKB@?$CISERVER?$CJ?5Round?5score?5updated?6?$AA@ @ 0x003E1FA4
// match: ??_7type_3E1FC4@@6B@ @ 0x003E1FC4
// match: ??_7type_3E1FD0@@6B@ @ 0x003E1FD0
// match: ??_C@_0BN@KLBADHHD@?$CISERVER?$CJ?5Game?5score?5updated?6?$AA@ @ 0x003E1FDC
// match: __ehhandler$?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z>1>8 @ 0x0041EDFC
// match: __ehhandler$?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z>1>16>16 @ 0x0041EE1C
// match: __ehhandler$?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z>1>16>36 @ 0x0041EE2C
// match: __ehhandler$?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z>1>16 @ 0x0041EE3C
// match: __ehhandler$?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z>1 @ 0x0041EE64
// match: ?flt_42CAB8@@3MA @ 0x0042CAB8
// match: ?dword_42CABC@@3HA @ 0x0042CABC

// match: ?vf_000@type_3E0FB4@@UAEXPAUtype_1F8560@@@Z @ 0x001B18E0

void type_3E0FB4::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F87B0(unk_04, 8);
    arg_0->sub_1F8860(unk_08, 8);
    arg_0->sub_1F85F0(unk_0C.x);
    arg_0->sub_1F85F0(unk_0C.y);
    arg_0->sub_1F85F0(unk_0C.z);
    if (unk_18 == -1)
        arg_0->sub_1F8860(16, 8);
    else
        arg_0->sub_1F8860(unk_18, 8);
    arg_0->sub_1F8860(unk_1C, 8);
    arg_0->sub_1F8520(unk_20);
}

// match: ?vf_004@type_3E0FB4@@UAEXPAUtype_1F8560@@@Z @ 0x001B1990
void type_3E0FB4::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8750(8);
    unk_08 = arg_0->sub_1F8810(8);
    unk_0C.x = arg_0->sub_1F85A0();
    unk_0C.y = arg_0->sub_1F85A0();
    unk_0C.z = arg_0->sub_1F85A0();
    unk_18 = arg_0->sub_1F8810(8);
    if (unk_18 == 16)
        unk_18 = -1;
    unk_1C = arg_0->sub_1F8810(8);
    unk_20 = arg_0->sub_1F8560();
}

// match: ?sub_1B1A30@type_4F823C@@QAEXXZ @ 0x001B1A30
void type_4F823C::sub_1B1A30()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_00[var_4].unk_00 = 0;
        unk_00[var_4].unk_04 = 0;
        unk_00[var_4].unk_08 = 0;
        unk_00[var_4].unk_0C.x = 0;
        unk_00[var_4].unk_0C.y = 0;
        unk_00[var_4].unk_0C.z = 0;
        unk_00[var_4].unk_18 = 0;
        unk_00[var_4].unk_1C = 0;
        unk_00[var_4].unk_20 = 0;
    }
}

// Flag arg_0's new state arg_4 (at arg_8, by nobody when arg_10 is set, a
// capture when arg_C is): when hosting it is sent to the host (peer 0);
// otherwise, when it changes, it is kept (updates counted, the scores told)
// and sent to the other peers.
// match: ?sub_1B1B00@type_4F823C@@QAEXHHPAURwV3d@@HH@Z @ 0x001B1B00
void type_4F823C::sub_1B1B00(RwInt32 arg_0, RwInt32 arg_4, RwV3d *arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwV3d slot_C;

    if (arg_8)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00[0].unk_00)
        {
        }
        slot_C = *arg_8;
    }
    else
        slot_C.x = slot_C.y = slot_C.z = 0;
    if (unk_4F61F8.unk_104)
    {
        type_3E0FB4 l34;

        l34.unk_04 = arg_0;
        l34.unk_08 = arg_4;
        l34.unk_0C = slot_C;
        l34.unk_18 = unk_4F7EB8.sub_1AEC70();
        l34.unk_1C = 0;
        l34.unk_20 = arg_C;
        type_1DDE20_mask r10;

        r10.put(0);
        type_4F8058::get()->sub_1DDE20(&l34, r10);
    }
    else if (arg_4 != unk_00[arg_0].unk_00)
    {
        type_4F823C_flag z7C = unk_00[arg_0];

        unk_00[arg_0].unk_00 = arg_4;
        if (arg_10)
            unk_00[arg_0].unk_08 = -1;
        else
            unk_00[arg_0].unk_08 = unk_4F7EB8.sub_1AEC70();
        unk_00[arg_0].unk_18 = unk_48;
        unk_00[arg_0].unk_1C = 0;
        unk_00[arg_0].unk_0C = slot_C;
        unk_00[arg_0].unk_20 = 30.0f;
        type_3E0FB4 m_58;

        m_58.unk_04 = arg_0;
        m_58.unk_08 = arg_4;
        m_58.unk_0C = slot_C;
        if (arg_10)
            m_58.unk_18 = -1;
        else
            m_58.unk_18 = unk_4F7EB8.sub_1AEC70();
        m_58.unk_1C = ++unk_00[arg_0].unk_04;
        m_58.unk_20 = arg_C;
        unk_4F7EB8.unk_04.sub_1B3030(arg_0, &z7C, &unk_00[arg_0]);
        if (arg_C)
            unk_4F7EB8.unk_04.sub_1B2FD0(dword_4F6A7C.sub_1A5950(arg_0));
        type_4F8058::get()->sub_1DDE20(&m_58, type_4F8054::get()->get_unk_B0()->sub_1A8050());
    }
}

// Flag arg_0's new state as a peer sends it: when not hosting the newer
// update is kept and shown (and the local player's unk_229C cleared when an
// enemy takes its team's flag); when hosting a change is kept (updates
// counted, a 30 second timer), sent on to the other peers, shown and scored.
// match: ?sub_1B1DE0@type_4F823C@@QAEXPAUtype_3E0FB4@@@Z @ 0x001B1DE0
void type_4F823C::sub_1B1DE0(type_3E0FB4 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    if (unk_4F61F8.unk_104)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00[0].unk_00)
        {
        }
        if ((RwUInt32)arg_0->unk_1C > (RwUInt32)unk_00[arg_0->unk_04].unk_04)
        {
            unk_00[arg_0->unk_04].unk_00 = arg_0->unk_08;
            unk_00[arg_0->unk_04].unk_04 = arg_0->unk_1C;
            unk_00[arg_0->unk_04].unk_08 = arg_0->unk_18;
            unk_00[arg_0->unk_04].unk_0C = arg_0->unk_0C;
            unk_00[arg_0->unk_04].unk_1C = 0;
            if (arg_0->unk_18 != unk_4F7EB8.sub_1AEC70())
            {
                dword_4F6A7C.sub_1A4B40(arg_0->unk_04, arg_0->unk_08, arg_0->unk_18, &arg_0->unk_0C, 0);
                if (type_4F805C::get() && type_4F805C::get()->sub_1B8420() != dword_4F6A7C.sub_1A5950(arg_0->unk_04) &&
                    arg_0->unk_08 == 1 && type_4F805C::get()->has_unk_229C())
                    type_4F805C::get()->unk_229C = 0;
            }
        }
    }
    else if (arg_0->unk_08 != unk_00[arg_0->unk_04].unk_00)
    {
        type_4F823C_flag frm_24 = unk_00[arg_0->unk_04];

        unk_00[arg_0->unk_04].unk_00 = arg_0->unk_08;
        unk_00[arg_0->unk_04].unk_08 = arg_0->unk_18;
        unk_00[arg_0->unk_04].unk_18 = unk_48;
        unk_00[arg_0->unk_04].unk_0C = arg_0->unk_0C;
        unk_00[arg_0->unk_04].unk_1C = 0;
        unk_00[arg_0->unk_04].unk_20 = 30.0f;
        type_3E0FB4 w48(*arg_0);

        w48.unk_1C = ++unk_00[arg_0->unk_04].unk_04;
        type_4F8058::get()->sub_1DDE20(&w48, type_4F8054::get()->get_unk_B0()->sub_1A8050());
        dword_4F6A7C.sub_1A4B40(arg_0->unk_04, arg_0->unk_08, arg_0->unk_18, &arg_0->unk_0C, 0);
        unk_4F7EB8.unk_04.sub_1B3030(arg_0->unk_04, &frm_24, &unk_00[arg_0->unk_04]);
        if (arg_0->unk_20)
            unk_4F7EB8.unk_04.sub_1B2FD0(dword_4F6A7C.sub_1A5950(arg_0->unk_04));
    }
}


// match: ?sub_1B21A0@type_4F823C@@QAEXPAUtype_1F8560@@@Z @ 0x001B21A0
void type_4F823C::sub_1B21A0(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        arg_0->sub_1F8860(unk_00[var_4].unk_04, 8);
        arg_0->sub_1F8860(unk_00[var_4].unk_00, 8);
        if (unk_00[var_4].unk_08 == -1)
            arg_0->sub_1F8860(16, 8);
        else
            arg_0->sub_1F8860(unk_00[var_4].unk_08, 8);
        arg_0->sub_1F85F0(unk_00[var_4].unk_0C.x);
        arg_0->sub_1F85F0(unk_00[var_4].unk_0C.y);
        arg_0->sub_1F85F0(unk_00[var_4].unk_0C.z);
        arg_0->sub_1F8520(unk_00[var_4].unk_1C);
    }
}

// match: ?sub_1B2290@type_4F823C@@QAEXPAUtype_1F8560@@@Z @ 0x001B2290
void type_4F823C::sub_1B2290(type_1F8560 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwV3d loc1C;
    RwInt32 p20;
    RwInt32 ebp_10;
    RwInt32 locC;
    RwUInt32 x8;
    RwInt32 bp_4;

    for (p20 = 0; p20 < 2; p20++)
    {
        x8 = arg_0->sub_1F8810(8);
        ebp_10 = arg_0->sub_1F8810(8);
        locC = arg_0->sub_1F8810(8);
        if (locC == 16)
            locC = -1;
        loc1C.x = arg_0->sub_1F85A0();
        loc1C.y = arg_0->sub_1F85A0();
        loc1C.z = arg_0->sub_1F85A0();
        bp_4 = arg_0->sub_1F8560();
        if ((RwUInt32)unk_00[p20].unk_04 < x8)
        {
            unk_00[p20].unk_04 = x8;
            unk_00[p20].unk_00 = ebp_10;
            unk_00[p20].unk_08 = locC;
            unk_00[p20].unk_0C = loc1C;
            unk_00[p20].unk_1C = bp_4;
            dword_4F6A7C.sub_1A4B40(p20, ebp_10, locC, &loc1C, 0);
        }
    }
}

// Its step by arg_0 frames: the round's timer counted down in seconds for
// each dropped flag (state 2), which goes home when it runs out; only on
// a client.
// match: ?sub_1B23B0@type_4F823C@@QAEXM@Z @ 0x001B23B0
void type_4F823C::sub_1B23B0(RwReal arg_0)
{
    RwReal l4;
    RwInt32 var_8;

    l4 = arg_0 / 60.0f;
    if (!unk_4F61F8.unk_104)
    {
        for (var_8 = 0; var_8 < 2; var_8++)
        {
            if (unk_00[var_8].unk_00 == 2 && unk_00[var_8].unk_20 > 0.0f)
            {
                unk_00[var_8].unk_20 = unk_00[var_8].unk_20 - l4;
                if (unk_00[var_8].unk_20 <= 0.0f)
                {
                    RwV3d *var_C = 0;

                    dword_4F6A7C.sub_1A4A20(var_8, 0, -1, var_C, 0);
                }
            }
        }
    }
}

// match: ?sub_1B2480@type_4F823C@@QAEHH@Z @ 0x001B2480
RwInt32 type_4F823C::sub_1B2480(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (unk_00[var_4].unk_00 == 1 && unk_00[var_4].unk_08 == arg_0)
            return 1;
    }
    return 0;
}

// Drops the flag player arg_0 carries where the player is (capture the
// flag, on a client).
// match: ?sub_1B24E0@type_4F823C@@QAEXH@Z @ 0x001B24E0
void type_4F823C::sub_1B24E0(RwInt32 arg_0)
{
    RwInt32 var_4;

    if (dword_4FB9E0.get_unk_08() != 4)
        return;
    if (unk_4F61F8.unk_104)
        return;
    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (unk_00[var_4].unk_08 == arg_0 && unk_00[var_4].unk_00 == 1)
        {
            type_3E0FB4 var_28;
            type_3D3548 *var_2C = unk_4F7EB8.sub_1AECA0(arg_0, 0);

            var_28.unk_04 = var_4;
            var_28.unk_08 = 2;
            var_28.unk_0C = *(RwV3d *)var_2C->vf_0C4();
            var_28.unk_18 = arg_0;
            var_28.unk_1C = unk_00[var_4].unk_04;
            var_28.unk_20 = 0;
            sub_1B1DE0(&var_28);
        }
    }
}

// match: ?sub_1B25E0@type_4F823C@@QAEPAUtype_3D3548@@PAU2@@Z @ 0x001B25E0
type_3D3548 *type_4F823C::sub_1B25E0(type_3D3548 *arg_0)
{
    RwInt32 var_4 = unk_4F7EB8.sub_1AF1B0(arg_0);

    return sub_1B2610(var_4);
}

// match: ?sub_1B2610@type_4F823C@@QAEPAUtype_3D3548@@H@Z @ 0x001B2610
type_3D3548 *type_4F823C::sub_1B2610(RwInt32 arg_0)
{
    if (unk_00[0].unk_00 == 1 && unk_00[0].unk_08 == arg_0)
        return dword_4F6A7C.sub_1A5D70(0);
    if (unk_00[1].unk_00 == 1 && unk_00[1].unk_08 == arg_0)
        return dword_4F6A7C.sub_1A5D70(1);
    return 0;
}

// match: ?sub_1B2670@type_4F823C@@QAEXXZ @ 0x001B2670
void type_4F823C::sub_1B2670()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 bp_4;
    RwUInt8 var_14[12];

    if (dword_4FB9E0.get_unk_08() != 4)
        return;
    for (bp_4 = 0; bp_4 < 2; bp_4++)
    {
        // Block-scoped: they sit below the /GS arrays (docs/toolchain.md).
        type_ED340 *frm_24;
        RwInt16 t20;
        RwInt32 l1C;
        type_3D32F8 *m_18;

        m_18 = (type_3D32F8 *)dword_4F6A7C.sub_1A5D70(bp_4);
        if (m_18)
        {
            if (m_18 == sub_1B2610(unk_4F7EB8.sub_1AEC70()))
                m_18->vf_1A4(1);
            else
                m_18->vf_1A4(0);
        }
        for (l1C = 0; l1C < 6; l1C++)
        {
            var_14[l1C] = 0;
            var_14[l1C + 6] = 1;
        }
        var_14[0] = 0;
        var_14[2] = 2;
        var_14[1] = 0xAB;
        frm_24 = dword_4B92FC;
        t20 = frm_24->sub_ED340(m_18, var_14, 0, 0);
        if (t20 != -1 && m_18 && m_18->vf_090())
        {
            ((type_3D2CD0 *)m_18->vf_090())->sub_6D380(t20, 0, 0, 0, 0, 0, 0, 0);
            m_18->vf_090()->set_unk_144(1);
        }
        if (m_18 && unk_00[bp_4].unk_00 != 1)
        {
            m_18->unk_478 = 0;
            m_18->set_unk_480(flt_42CAB8);
            m_18->sub_76960();
        }
    }
}

void sub_1B2950(RwInt32 arg_0);
DWORD sub_1B2990(LPTHREAD_START_ROUTINE arg_0);
DWORD WINAPI sub_1B28C0(LPVOID arg_0);
// Starts the keep-alive thread.
// match: ?sub_1B2810@@YAXXZ @ 0x001B2810
void sub_1B2810()
{
    dword_4FB9D0 = -1;
    dword_4FB9C8 = -1;
    dword_4FB9D4 = 1;
    dword_4FB9CC = sub_1B2990(sub_1B28C0);
    sub_19A750((RwInt32)sub_1B2950);
}

DWORD sub_1B29B0(DWORD arg_0);
// Stops it.
// match: ?sub_1B2860@@YAXXZ @ 0x001B2860
void sub_1B2860()
{
    sub_19A750();
    sub_1B29B0(dword_4FB9CC);
    dword_4FB9D4 = 0;
}

void sub_1B29D0(RwUInt32 arg_0);
// A wait while it stops.
// match: ?sub_1B2890@@YAXXZ @ 0x001B2890
void sub_1B2890()
{
    sub_19A750((RwInt32)dword_4FB9CC);
    sub_1B29D0(1);
    sub_19A750((RwInt32)dword_4FB9CC);
}

// The thread: while it runs, the session is ticked, then it sleeps.
// match: ?sub_1B28C0@@YGKPAX@Z @ 0x001B28C0
DWORD WINAPI sub_1B28C0(LPVOID arg_0)
{
    // Read and unused.
    type_4F8054 *var_4 = dword_4F8054;

    while (dword_4FB9D4 == 1)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!var_4->unk_04)
        {
        }
        unk_4F7EB8.sub_1AF750(sub_1CCA10(), 0, 1);
        sub_19A750(dword_4FB9C8);
        sub_19A750(0x28);
        sub_19A750(dword_4FB9C8);
        dword_42CABC = 1;
        sub_1B29D0(0);
    }
    dword_4FB9D4 = 2;
    ExitThread(1);
}

// match: ?sub_1B2950@@YAXH@Z @ 0x001B2950
void sub_1B2950(RwInt32 arg_0)
{
    sub_19A750((RwInt32)dword_4FB9CC);
    sub_1B29D0(1);
    sub_19A750((RwInt32)dword_4FB9CC);
    sub_19A750(arg_0);
}

DWORD sub_1B29F0(LPTHREAD_START_ROUTINE arg_0);
// match: ?sub_1B2990@@YAKP6GKPAX@Z@Z @ 0x001B2990
DWORD sub_1B2990(LPTHREAD_START_ROUTINE arg_0)
{
    return sub_1B29F0(arg_0);
}

DWORD sub_1B2A30(DWORD arg_0);
// match: ?sub_1B29B0@@YAKK@Z @ 0x001B29B0
DWORD sub_1B29B0(DWORD arg_0)
{
    return sub_1B2A30(arg_0);
}

void sub_1B2A80(DWORD arg_0);
// match: ?sub_1B29D0@@YAXI@Z @ 0x001B29D0
void sub_1B29D0(RwUInt32 arg_0)
{
    sub_1B2A80(arg_0);
}

// match: ?sub_1B29F0@@YAKP6GKPAX@Z@Z @ 0x001B29F0
DWORD sub_1B29F0(LPTHREAD_START_ROUTINE arg_0)
{
    HANDLE var_4;
    DWORD local_8;

    var_4 = CreateThread(0, 0, arg_0, 0, 0, &local_8);
    SetThreadPriority(var_4, -2);
    ResumeThread(var_4);
    return local_8;
}

// "XBOXDestroyThread", as the loading thread's.
// match: ?sub_1B2A30@@YAKK@Z @ 0x001B2A30
DWORD sub_1B2A30(DWORD arg_0)
{
    sub_16C220("XBOXDestroyThread:: Waiting for loading thread to exit...");
    dword_4FB9D4 = 0;
    while (dword_4FB9D4 != 2)
    {
        sub_1B2890();
    }
    dword_4FB9D4 = 0;
    sub_16C220("XBOXDestroyThread:: Done waiting for loading thread to exit.  Loading thread destroyed...");
    return arg_0;
}

// The HUD's message line refresh (sub_1C4C30).
void sub_1C4C30(bool arg_0);

// The network's keep-alive thread (the multiplayer manager's session told
// each tick): its state (dword_4FB9D4: 1 while it runs, 2 once it has
// stopped, 0 to stop it), its id and two unused values. The helpers are a
// copy of the loading thread's (unit_0811C0), its strings too.
extern RwInt32 dword_4FB9C8;
extern DWORD dword_4FB9CC;
extern RwInt32 dword_4FB9D0;
extern RwInt32 dword_4FB9D4;
// Set by each tick of the keep-alive thread.
extern RwInt32 dword_42CABC;
DWORD sub_1B2990(LPTHREAD_START_ROUTINE arg_0);
DWORD sub_1B29B0(DWORD arg_0);
void sub_1B29D0(RwUInt32 arg_0);
DWORD sub_1B29F0(LPTHREAD_START_ROUTINE arg_0);
DWORD sub_1B2A30(DWORD arg_0);
void sub_1B2A80(DWORD arg_0);
void sub_1B2890();
DWORD WINAPI sub_1B28C0(LPVOID arg_0);
void sub_1B2950(RwInt32 arg_0);

// match: ?sub_1B2A80@@YAXK@Z @ 0x001B2A80
void sub_1B2A80(DWORD arg_0)
{
    Sleep(arg_0);
}

// match: ??0type_3E1E3C@@QAE@XZ @ 0x001B2A90
type_3E1E3C::type_3E1E3C()
{
    sub_1B3820();
}

// match: ??1type_3E1E3C@@QAE@XZ @ 0x001B2AD0
type_3E1E3C::~type_3E1E3C()
{
}

// match: ?sub_1B2AF0@type_3E1E3C@@QAEHIH@Z @ 0x001B2AF0
RwInt32 type_3E1E3C::sub_1B2AF0(RwUInt32 arg_0, RwInt32 arg_4)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask locC;
    RwInt32 ebp_10 = 0;
    RwInt32 x8;
    RwUInt32 bp_4;
    RwInt32 y14;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_04[0])
    {
    }
    if (!unk_04[0])
    {
    }
    x8 = unk_04[arg_0];

    locC = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        y14 = dword_4F8288.sub_1C2A90(bp_4);
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_04[0])
        {
        }
        if (locC.test(bp_4) && bp_4 != arg_0 && y14 == arg_4)
        {
            if (x8 < unk_04[bp_4] || x8 == unk_04[bp_4] && bp_4 > arg_0)
                ebp_10++;
        }
    }
    return ebp_10;
}

// match: ?sub_1B2BC0@type_3E1E3C@@QAEHH@Z @ 0x001B2BC0
RwInt32 type_3E1E3C::sub_1B2BC0(RwInt32 arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask x8;
    RwUInt32 bp_4;

    if (arg_0 == -1)
        return 0;
    x8 = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_04[0])
        {
        }
        if (x8.test(bp_4) && bp_4 != arg_0)
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_04[0])
            {
            }
            if (!unk_4F6B00[bp_4].get_unk_130())
                return 0;
        }
    }
    return 1;
}

// match: ?sub_1B2C60@type_3E1E3C@@QAEHH@Z @ 0x001B2C60
RwInt32 type_3E1E3C::sub_1B2C60(RwInt32 arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask x8;
    RwUInt32 bp_4;

    x8 = type_4F8054::get()->get_unk_B0()->get_unk_0C();
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_04[0])
        {
        }
        if (x8.test(bp_4))
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_04[0])
            {
            }
            if (!unk_4F6B00[bp_4].get_unk_130() && dword_4F8288.sub_1C2A90(bp_4) == arg_0)
                return 0;
        }
    }
    return 1;
}

// Player arg_0's death at player arg_4's hand: a death for arg_0, and for
// arg_4 a point and a kill, or a point lost for a suicide or (unless arg_8
// is set) for killing a team mate; 2 more points for killing a flag
// carrier. Only on a client; the scores are sent on.
// match: ?sub_1B2D00@type_3E1E3C@@QAEXHH_N@Z @ 0x001B2D00
void type_3E1E3C::sub_1B2D00(RwInt32 arg_0, RwInt32 arg_4, bool arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (unk_4F61F8.unk_104)
        return;
    if (arg_0 == -1 || arg_4 == -1)
        return;
    bp_4 = dword_4F8288.sub_1C2A90(arg_4);
    bp_8 = dword_4F8288.sub_1C2A90(arg_0);
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_04[0])
    {
    }
    unk_4F6B00[arg_0].unk_130 = 1;
    if (dword_4FB9E0.get_unk_08() == 1)
    {
        bool w9 = true;

        if (dword_4FB9E0.get_unk_0C())
        {
            if (sub_1B2BC0(arg_4))
            {
                dword_4FB9E0.sub_1B6550(1);
                if (arg_0 == arg_4)
                    w9 = false;
            }
            else
                w9 = false;
        }
        if (w9)
        {
            if (arg_0 != arg_4)
            {
                unk_04[arg_4]++;
                unk_44[arg_4]++;
                unk_84[arg_0]++;
            }
            else
            {
                unk_04[arg_4]--;
                unk_84[arg_0]++;
            }
        }
    }
    else
    {
        RwInt32 lv_10;
        bool loc11;

        loc11 = false;
        lv_10 = bp_4 != 2;
        if (dword_4FB9E0.get_unk_0C())
        {
            if (sub_1B2C60(bp_8))
            {
                if (bp_8 == 2)
                    dword_4FB9E0.sub_1B6550(4);
                else
                    dword_4FB9E0.sub_1B6550(2);
                if (dword_4FB9E0.get_unk_08() == 2 || dword_4FB9E0.get_unk_08() == 8)
                    loc11 = true;
            }
        }
        else if (dword_4FB9E0.get_unk_08() == 2)
            loc11 = true;
        if (bp_4 != bp_8)
        {
            unk_04[arg_4]++;
            unk_44[arg_4]++;
            unk_84[arg_0]++;
            if (unk_4F7EB8.unk_384.sub_1B2480(arg_0))
                unk_04[arg_4] += 2;
            if (loc11)
                unk_C4[lv_10]++;
        }
        else
        {
            if (arg_0 == arg_4 || !arg_8)
                unk_04[arg_4]--;
            unk_84[arg_0]++;
        }
    }
    sub_1B3400();
}

// A capture by team arg_0 (2 or 4) counted when not hosting.
// match: ?sub_1B2FD0@type_3E1E3C@@QAEXH@Z @ 0x001B2FD0
void type_3E1E3C::sub_1B2FD0(RwInt32 arg_0)
{
    if (unk_4F61F8.unk_104)
        return;
    if (arg_0 == 2)
        unk_C4[1]++;
    if (arg_0 == 4)
        unk_C4[0]++;
    sub_1B3400();
}

// The points for flag arg_0's change from arg_4 to arg_8 to the player
// who made it: 5 for taking it from the enemy base, 3 for picking it up,
// 5 for returning the enemy's flag home and 3 for returning one's own.
// match: ?sub_1B3030@type_3E1E3C@@QAEXHPAUtype_4F823C_flag@@0@Z @ 0x001B3030
void type_3E1E3C::sub_1B3030(RwInt32 arg_0, type_4F823C_flag *arg_4, type_4F823C_flag *arg_8)
{
    RwInt32 var_4;

    if (arg_8->unk_08 == -1)
        return;
    var_4 = dword_4F8288.sub_1C2A90(arg_8->unk_08);
    if (var_4 != dword_4F6A7C.sub_1A5950(arg_0))
    {
        if (arg_4->unk_00 == 0 && arg_8->unk_00 == 1)
        {
            unk_04[arg_8->unk_08] += 5;
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("SCORE: %d points for getting flag from enemy base\n", 5);
        }
        else if (arg_4->unk_00 == 2 && arg_8->unk_00 == 1)
        {
            unk_04[arg_8->unk_08] += 3;
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("SCORE: %d points for picking up flag off ground\n", 3);
        }
        else if (arg_4->unk_00 == 1 && arg_8->unk_00 == 0)
        {
            unk_04[arg_8->unk_08] += 5;
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("SCORE: %d points for returning enemy flag to home base\n", 5);
        }
    }
    else if (arg_4->unk_00 == 1 && arg_8->unk_00 == 0)
    {
        unk_04[arg_8->unk_08] += 3;
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("SCORE: %d points for returning OWN flag to base\n", 3);
    }
    sub_1B3400();
}

// The points for bomb site arg_0's change from arg_4 to arg_8: 5 for
// planting, 3 for defusing, 5 to the planter for destroying the target.
// match: ?sub_1B3190@type_3E1E3C@@QAEXHPAUtype_4F8184_site@@0@Z @ 0x001B3190
void type_3E1E3C::sub_1B3190(RwInt32 arg_0, type_4F8184_site *arg_4, type_4F8184_site *arg_8)
{
    if (arg_4->unk_00 == 2 && arg_8->unk_00 == 3)
    {
        unk_04[arg_8->unk_0C] += 5;
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("SCORE: %d points for planting a bomb\n", 5);
    }
    else if (arg_4->unk_00 == 4 && arg_8->unk_00 == 0)
    {
        unk_04[arg_8->unk_0C] += 3;
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("SCORE: %d points for defusing a bomb\n", 3);
    }
    else if (arg_4->unk_00 == 3 && arg_8->unk_00 == 5)
    {
        unk_04[arg_8->unk_14] += 5;
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("SCORE: %d points for destroying a target\n", 5);
    }
    sub_1B3400();
}

// match: ?sub_1B3270@type_3E1E3C@@QAEXH@Z @ 0x001B3270
void type_3E1E3C::sub_1B3270(RwInt32 arg_0)
{
    if (dword_4FB9E0.get_unk_C8())
        return;
    if (unk_4F61F8.unk_104)
        return;
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04[0])
    {
    }
    unk_04[arg_0] = 0;
    unk_44[arg_0] = 0;
    unk_84[arg_0] = 0;
    unk_4F7EB8.unk_D0.sub_1B3890(arg_0);
    sub_1B3400();
}

// match: ?vf_004@type_3E1E3C@@UAEXPAUtype_1F8560@@@Z @ 0x001B32E0
void type_3E1E3C::vf_004(type_1F8560 *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        unk_04[var_4] = arg_0->sub_1F8750(8);
        unk_44[var_4] = arg_0->sub_1F8750(8);
    }
    unk_C4[0] = arg_0->sub_1F8750(8);
    unk_C4[1] = arg_0->sub_1F8750(8);
}

// match: ?sub_1B3360@type_3E1E3C@@QAEHH@Z @ 0x001B3360
RwInt32 type_3E1E3C::sub_1B3360(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04[0])
    {
    }
    return unk_04[arg_0];
}

// match: ?sub_1B3380@type_3E1E3C@@QAEHH@Z @ 0x001B3380
RwInt32 type_3E1E3C::sub_1B3380(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04[0])
    {
    }
    return unk_44[arg_0];
}

// match: ?sub_1B33A0@type_3E1E3C@@QAEHH@Z @ 0x001B33A0
RwInt32 type_3E1E3C::sub_1B33A0(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04[0])
    {
    }
    return unk_84[arg_0];
}

// match: ?sub_1B33C0@type_3E1E3C@@QAEHH@Z @ 0x001B33C0
RwInt32 type_3E1E3C::sub_1B33C0(RwInt32 arg_0)
{
    if (arg_0 == 2)
        return unk_C4[0];
    if (arg_0 == 4)
        return unk_C4[1];
    return 0;
}

// match: ?sub_1B3400@type_3E1E3C@@QAEXXZ @ 0x001B3400
void type_3E1E3C::sub_1B3400()
{
    sub_1C4C30(1);
    if (unk_4F61F8.unk_104)
        return;
    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04[0])
    {
    }
    if (!unk_04[0])
    {
    }
    type_4F8058::get()->sub_1DDDB0((type_3DA44C *)this, type_4F8054::get()->get_unk_B0()->sub_1A8050());
    sub_1A8A70(&unk_4F7EB8, "(SERVER) Round score updated\n");
    dword_4FB9E0.sub_1B6130();
}

// The players in order, best first: by score, then by kills (a bubble sort
// of their numbers into arg_0).
// match: ?sub_1B3480@type_3E1E3C@@QAEXAAV?$vector@IV?$allocator@I@std@@@std@@@Z @ 0x001B3480
void type_3E1E3C::sub_1B3480(std::vector<RwUInt32> &arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    arg_0.resize(16);
    for (bp_4 = 0; bp_4 < 16; bp_4++)
        arg_0[bp_4] = bp_4;
    for (bp_4 = 0; bp_4 < 15; bp_4++)
    {
        for (bp_8 = 0; bp_8 < 15; bp_8++)
        {
            if (unk_04[arg_0[bp_8]] < unk_04[arg_0[bp_8 + 1]] ||
                unk_04[arg_0[bp_8]] <= unk_04[arg_0[bp_8 + 1]] && unk_44[arg_0[bp_8]] < unk_44[arg_0[bp_8 + 1]])
            {
                slot_C = arg_0[bp_8];
                arg_0[bp_8] = arg_0[bp_8 + 1];
                arg_0[bp_8 + 1] = slot_C;
            }
        }
    }
}

// match: ??0type_3E1FC4@@QAE@XZ @ 0x001B37C0
type_3E1FC4::type_3E1FC4()
{
    sub_1B3820();
}

// match: ??1type_3E1FC4@@QAE@XZ @ 0x001B3800
type_3E1FC4::~type_3E1FC4()
{
}

// Clears the scores (type_3E1E3C's is the same code, /OPT:ICF).
// match: ?sub_1B3820@type_3E1FC4@@QAEXXZ @ 0x001B3820
void type_3E1FC4::sub_1B3820()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        unk_04[var_4] = 0;
        unk_44[var_4] = 0;
        unk_84[var_4] = 0;
    }
    unk_C4[0] = 0;
    unk_C4[1] = 0;
}

// match: ?sub_1B3890@type_3E1FC4@@QAEXH@Z @ 0x001B3890
void type_3E1FC4::sub_1B3890(RwInt32 arg_0)
{
    if (unk_4F61F8.unk_104)
        return;
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04[0])
    {
    }
    unk_04[arg_0] = 0;
    unk_44[arg_0] = 0;
    unk_84[arg_0] = 0;
    sub_1B3BA0();
}

// match: ?sub_1B38E0@type_3E1FC4@@QAEXXZ @ 0x001B38E0
void type_3E1FC4::sub_1B38E0()
{
    // The locals' names state their slots (docs/toolchain.md).
    bool bp_D;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    if (unk_4F61F8.unk_104)
        return;
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        unk_04[bp_4] += unk_4F7EB8.unk_04.sub_1B3360(bp_4);
        unk_44[bp_4] += unk_4F7EB8.unk_04.sub_1B3380(bp_4);
        unk_84[bp_4] += unk_4F7EB8.unk_04.sub_1B33A0(bp_4);
    }
    if (dword_4FB9E0.get_unk_08() == 1)
    {
        unk_C4[0] = 0;
        unk_C4[1] = 0;
    }
    if (dword_4FB9E0.get_unk_08() == 4 || dword_4FB9E0.get_unk_08() == 2)
    {
        bp_8 = unk_4F7EB8.unk_04.sub_1B33C0(2);
        slot_C = unk_4F7EB8.unk_04.sub_1B33C0(4);
        if (bp_8 > slot_C)
            unk_C4[0]++;
        if (slot_C > bp_8)
            unk_C4[1]++;
    }
    if (dword_4FB9E0.get_unk_08() == 8)
    {
        bp_D = false;
        if (dword_4FB9E0.get_unk_E8())
            bp_D = true;
        else if (dword_4FB9E0.get_unk_0C() && dword_4FB9E0.get_unk_EC() &&
                 dword_4FB9E0.get_unk_F0() == dword_4FB9E0.get_team_count())
            bp_D = true;
        if (bp_D)
        {
            if (dword_4FB9E0.get_unk_10C())
                unk_C4[1]++;
            else
                unk_C4[0]++;
        }
        else
        {
            if (dword_4FB9E0.get_unk_10C())
                unk_C4[0]++;
            else
                unk_C4[1]++;
        }
    }
    sub_1B3BA0();
}

// Written with the full game state (type_3E1E3C's is the same code,
// /OPT:ICF).
// match: ?vf_000@type_3E1FC4@@UAEXPAUtype_1F8560@@@Z @ 0x001B3B20
void type_3E1FC4::vf_000(type_1F8560 *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        arg_0->sub_1F87B0(unk_04[var_4], 8);
        arg_0->sub_1F87B0(unk_44[var_4], 8);
    }
    arg_0->sub_1F87B0(unk_C4[0], 8);
    arg_0->sub_1F87B0(unk_C4[1], 8);
}

// match: ?sub_1B3BA0@type_3E1FC4@@QAEXXZ @ 0x001B3BA0
void type_3E1FC4::sub_1B3BA0()
{
    if (unk_4F61F8.unk_104)
        return;
    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04[0])
    {
    }
    if (!unk_04[0])
    {
    }
    type_4F8058::get()->sub_1DDDB0((type_3DA44C *)this, type_4F8054::get()->get_unk_B0()->sub_1A8050());
    sub_1A8A70(&unk_4F7EB8, "(SERVER) Game score updated\n");
}

// match: ?vf_008@type_3E1E48@@UAEHXZ @ 0x001B3C10
RwInt32 type_3E1E48::vf_008()
{
    return 13;
}

// match: ?vf_008@type_3E1FD0@@UAEHXZ @ 0x001B3C20
RwInt32 type_3E1FD0::vf_008()
{
    return 27;
}

void sub_1C4A10();

extern RwUInt8 byte_4FDAA8;
void sub_1C5220();


// The std::vector<RwUInt32> pieces sub_1B3480 pulls in, out of line here.
// match: ?resize@?$vector@IV?$allocator@I@std@@@std@@QAEXII@Z @ 0x001B3C30
// match: ?erase@?$vector@IV?$allocator@I@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001B3D30
// match: ?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z @ 0x001B3DC0
// match: __ehhandler$?_Insert_n@?$vector@IV?$allocator@I@std@@@std@@IAEXViterator@12@IABI@Z @ 0x00302C20
// match: ??$_Uninit_copy@II@std@@YAPAIPAI00AAV?$allocator@I@0@U_Scalar_ptr_iterator_tag@0@@Z @ 0x001B4430

// The callbacks the game data hands out (its sub_1B5BF0, sub_1B6200,
// sub_1B6310, sub_1B52D0 and others): the front end's overlay check
// (sub_1C4A10), the data's and the flags' resets and a bit of dword_4B86F8;
// and four that call one of the data's methods. Only the widths are known.
void sub_1C4A10();
void sub_1C5220();
extern RwUInt8 byte_4FDAA8;









// The message's compiler-made copy constructor, out of line (sub_1B1DE0
// copies the message it sends on through it).
// match: ??0type_3E0FB4@@QAE@ABU0@@Z @ 0x001B2100

// The turn the flags not carried are given (1.0; its only reader).
extern RwReal flt_42CAB8;


// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_4F823C@@QAE@XZ (folded into 0x6FCD0)
type_4F823C::type_4F823C()
{
    
}

// ??4type_3E1FC4@@QAEAAU0@ABU0@@Z (folded into 0x1AE340)
struct type_3E1FC4 & type_3E1FC4::operator=(struct type_3E1FC4 const & arg_0)
{
    RwUInt32 bp_4;
    RwUInt32 x8;
    RwUInt32 locc;
    RwUInt32 ebp_10;

    for (bp_4 = 0; bp_4 < 0x10; bp_4++)
        unk_04[bp_4] = arg_0.unk_04[bp_4];
    for (x8 = 0; x8 < 0x10; x8++)
        unk_44[x8] = arg_0.unk_44[x8];
    for (locc = 0; locc < 0x10; locc++)
        unk_84[locc] = arg_0.unk_84[locc];
    for (ebp_10 = 0; ebp_10 < 2; ebp_10++)
        unk_C4[ebp_10] = arg_0.unk_C4[ebp_10];
    return *this;
}

// ?vf_000@type_3E1E3C@@UAEXPAUtype_1F8560@@@Z (folded into 0x1B3B20)
void type_3E1E3C::vf_000(struct type_1F8560 *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        arg_0->sub_1F87B0(unk_04[var_4], 8);
        arg_0->sub_1F87B0(unk_44[var_4], 8);
    }
    arg_0->sub_1F87B0(unk_C4[0], 8);
    arg_0->sub_1F87B0(unk_C4[1], 8);
}

// ?vf_004@type_3E1FC4@@UAEXPAUtype_1F8560@@@Z (folded into 0x1B32E0)
void type_3E1FC4::vf_004(struct type_1F8560 *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        unk_04[var_4] = arg_0->sub_1F8750(8);
        unk_44[var_4] = arg_0->sub_1F8750(8);
    }
    unk_C4[0] = arg_0->sub_1F8750(8);
    unk_C4[1] = arg_0->sub_1F8750(8);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1B3380@type_3E1FC4@@QAEHH@Z (folded into 0x1B3380)
RwInt32 type_3E1FC4::sub_1B3380(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_04[0])
    {
    }
    return unk_44[arg_0];
}

// ?sub_1B3820@type_3E1E3C@@QAEXXZ (folded into 0x1B3820)
void type_3E1E3C::sub_1B3820()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        unk_04[var_4] = 0;
        unk_44[var_4] = 0;
        unk_84[var_4] = 0;
    }
    unk_C4[0] = 0;
    unk_C4[1] = 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXH@Z (folded into 0x19A750)
void sub_19A750(RwInt32 arg_0)
{
}
