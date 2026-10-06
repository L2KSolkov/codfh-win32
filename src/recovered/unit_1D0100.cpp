// The network game's message queue (game/netqueue.h, type_1D0100): its
// lists, its buffers and its message classes' compiler-made members.

#include <string.h>

#include "types/type_DC400.h"
#include "game/netmsg.h"

// The debug print through a pointer (its target is empty in this build).
extern void (*off_42CD14)(const RwChar *arg_0, ...);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_1D0100@@6B@ @ 0x003E4D6C
// match: ??_C@_0FO@DBHPHANI@addPacket?5ran?5out?5of?5ram?5on?5a?5gu@ @ 0x003E4D70
// match: ??_C@_0DE@GJCJLBCM@addPacket?5ran?5out?5of?5ram?0?5packet@ @ 0x003E4DD0
// match: ??_C@_0CL@DMEOIFLI@?2COD?2SHARED?2network?2knet?2cPacket@ @ 0x003E4E04
// match: ??_7type_3E4E30@@6B@ @ 0x003E4E30
// match: ??_7type_3E4E34@@6B@ @ 0x003E4E34
// match: ??_7type_3E4E40@@6B@ @ 0x003E4E40
// match: ??_7type_3E4E4C@@6B@ @ 0x003E4E4C
// match: ??_7type_3E4E58@@6B@ @ 0x003E4E58
// match: ??_C@_0CA@CKGEHHIH@Just?5ran?5out?5of?5ram?5in?5ACK?5que?$CB?$AA@ @ 0x003E4E64
// match: ??_7type_3E4E84@@6B@ @ 0x003E4E84
// match: ??_C@_0EB@GFGLMEKD@Just?5ran?5out?5of?5ram?5in?5receive?5i@ @ 0x003E4E88
// match: ??_C@_0EC@DABJADMP@Just?5ran?5out?5of?5ram?5in?5receive?5u@ @ 0x003E4ED0
// match: __ehhandler$??0type_1D0100@@QAE@XZ>1>8 @ 0x0041F93C
// match: __ehhandler$??0type_1D0100@@QAE@XZ>1 @ 0x0041F95C
// match: __ehhandler$??1type_1D0100@@UAE@XZ>1>8 @ 0x0041F978
// match: __ehhandler$??1type_1D0100@@UAE@XZ>1 @ 0x0041F9B0
// match: __ehhandler$?sub_1D04B0@type_1D0100@@QAEXPAUtype_4F8054@@@Z>1>8 @ 0x0041F9CC
// match: __ehhandler$?sub_1D04B0@type_1D0100@@QAEXPAUtype_4F8054@@@Z>1 @ 0x0041F9DC
// match: __ehhandler$??1?$type_1FA230_list@Utype_1D7CA0@@@@QAE@XZ>1>8 @ 0x0041F9F8
// match: __ehhandler$??1?$type_1FA230_list@Utype_1D7CA0@@@@QAE@XZ>1 @ 0x0041FA00
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E4C@@@@QAE@XZ>1>8 @ 0x0041FA1C
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E4C@@@@QAE@XZ>1 @ 0x0041FA24
// match: __ehhandler$?sub_1D0F60@type_1D0100@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@HABUtype_1CCA10@@H@Z>1>8 @ 0x0041FA40
// match: __ehhandler$?sub_1D0F60@type_1D0100@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@HABUtype_1CCA10@@H@Z>1 @ 0x0041FA58
// match: __ehhandler$?sub_1D2CC0@type_1D0100@@QAEHHPAEI0H@Z>1>8 @ 0x0041FA74
// match: __ehhandler$?sub_1D2CC0@type_1D0100@@QAEHHPAEI0H@Z>1 @ 0x0041FA7C
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E40@@@@QAE@XZ>1>8 @ 0x0041FA98
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E40@@@@QAE@XZ>1 @ 0x0041FAA0
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E58@@@@QAEHABUtype_3E4E58@@@Z>1>8 @ 0x0041FABC
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E58@@@@QAEHABUtype_3E4E58@@@Z>1 @ 0x0041FAC4
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E84@@@@QAE@XZ>1>8 @ 0x0041FAE0
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E84@@@@QAE@XZ>1 @ 0x0041FAE8
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E4C@@@@QAEHABUtype_3E4E4C@@@Z>1>8 @ 0x0041FB04
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E4C@@@@QAEHABUtype_3E4E4C@@@Z>1 @ 0x0041FB0C
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E58@@@@QAE@XZ>1>8 @ 0x0041FB28
// match: __ehhandler$??1?$type_1FA230_list@Utype_3E4E58@@@@QAE@XZ>1 @ 0x0041FB30
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E84@@@@QAEHABUtype_3E4E84@@@Z>1>8 @ 0x0041FB4C
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E84@@@@QAEHABUtype_3E4E84@@@Z>1 @ 0x0041FB54
// match: __ehhandler$??1?$type_1FA230_list@Utype_1D3C80@@@@QAE@XZ>1>8 @ 0x0041FB70
// match: __ehhandler$??1?$type_1FA230_list@Utype_1D3C80@@@@QAE@XZ>1 @ 0x0041FB78
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E40@@@@QAEHABUtype_3E4E40@@@Z>1>8 @ 0x0041FB94
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E40@@@@QAEHABUtype_3E4E40@@@Z>1 @ 0x0041FB9C

// match: ??0type_1D0100@@QAE@XZ @ 0x001D0100
// match: __ehhandler$??0type_1D0100@@QAE@XZ-0x2C @ 0x00303530
// match: __ehhandler$??0type_1D0100@@QAE@XZ @ 0x0030355C

type_1D0100::type_1D0100() : unk_04(sub_1CBC40()), unk_1C(sub_1CBC50()), unk_34(sub_1CBC40()), unk_4C(sub_1CBC70())
{
}

// The deleting destructor, compiler-generated.
// match: ??_Gtype_1D0100@@UAEPAXI@Z @ 0x001D0270

// The implicit constructor of unk_4C4, out of line.
// match: ??0type_1D02A0@@QAE@XZ @ 0x001D02A0

// match: ??1type_1D0100@@UAE@XZ @ 0x001D0390
// match: __ehhandler$??1type_1D0100@@UAE@XZ-0x41 @ 0x00303570
// match: __ehhandler$??1type_1D0100@@UAE@XZ @ 0x003035B1
// Its lists go (their destructors inlined; the type_3E4E40 one has no
// unused local, game/netqueue.h).
type_1D0100::~type_1D0100()
{
}

// match: ?sub_1D04B0@type_1D0100@@QAEXPAUtype_4F8054@@@Z @ 0x001D04B0
// match: __ehhandler$?sub_1D04B0@type_1D0100@@QAEXPAUtype_4F8054@@@Z-0x16 @ 0x003035C0
// match: __ehhandler$?sub_1D04B0@type_1D0100@@QAEXPAUtype_4F8054@@@Z @ 0x003035D6
void type_1D0100::sub_1D04B0(type_4F8054 *arg_0)
{
    RwUInt32 i;

    unk_79C = arg_0;
    unk_794 = 0;
    unk_16C = 1;
    unk_170 = 2;
    unk_174 = 4;
    unk_178 = 1;
    unk_17C = 1;
    unk_164 = (RwUInt8 *)sub_1CBC30()->sub_1F8BF0(0x4C0);
    unk_168 = (RwUInt8 *)sub_1CBC30()->sub_1F8BF0(0x4C0);
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_794)
    {
    }
    for (i = 0; i < 0x10; i++)
    {
        unk_64[i] = new type_1FA230_list<type_1D7CA0>(sub_1CBC60());
        unk_A4[i] = -1;
        unk_E4[i] = new type_1FA230_list<type_1D3C80>(sub_1CBC60());
        unk_124[i] = -1;
        unk_180[i] = (type_3E4E4C **)sub_1CBC30()->sub_1F8BF0(0x190);
        unk_200[i] = (type_3E4E58 **)sub_1CBC30()->sub_1F8BF0(0x190);
        unk_280[i] = (type_3E4E84 **)sub_1CBC30()->sub_1F8BF0(0xC8);
        unk_300[i] = (type_3E4E40 **)sub_1CBC30()->sub_1F8BF0(0x190);
        if (!unk_794)
        {
        }
        unk_440[i] = sub_1CCA10();
    }
    memset(&unk_4C4, 0, sizeof(unk_4C4));
    memset(unk_380, 0, sizeof(unk_380));
    memset(unk_3C0, 0, sizeof(unk_3C0));
    memset(unk_400, 0, sizeof(unk_400));
    if (!unk_794)
    {
    }
    for (i = 0; i < 0x10; i++)
    {
    }
    unk_798 = 1 << zero();
}

// match: ?sub_1D07A0@type_1D0100@@QAEXXZ @ 0x001D07A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1D0100::sub_1D07A0()
{
    RwUInt32 bp_4;
    RwInt32 x8;
    type_1D7CA0 *locc;

    sub_1D0B30(type_1DDE20_mask(type_1DDE20_mask_fill_all));
    unk_04.sub_1FA5B0();
    unk_1C.sub_1FA5B0();
    unk_34.sub_1FA5B0();
    unk_4C.sub_1FA5B0();
    if (!unk_794)
    {
    }
    sub_1CBC30()->sub_1F8C30(unk_164);
    unk_164 = 0;
    sub_1CBC30()->sub_1F8C30(unk_168);
    unk_168 = 0;
    for (bp_4 = 0; bp_4 < 0x10; bp_4++)
    {
        locc = unk_64[bp_4]->first();
        x8 = unk_64[bp_4]->count();
        while (x8--)
        {
            locc->sub_1D7CA0();
            locc = unk_64[bp_4]->sub_1D4100();
        }
        unk_64[bp_4]->release();
        unk_E4[bp_4]->empty();
        unk_E4[bp_4]->release();
        sub_1CBC30()->sub_1F8C30(unk_180[bp_4]);
        unk_180[bp_4] = 0;
        sub_1CBC30()->sub_1F8C30(unk_200[bp_4]);
        unk_200[bp_4] = 0;
        sub_1CBC30()->sub_1F8C30(unk_280[bp_4]);
        unk_280[bp_4] = 0;
        sub_1CBC30()->sub_1F8C30(unk_300[bp_4]);
        unk_300[bp_4] = 0;
        delete unk_64[bp_4];
        unk_64[bp_4] = 0;
        unk_A4[bp_4] = 0;
        delete unk_E4[bp_4];
        unk_E4[bp_4] = 0;
        unk_124[bp_4] = 0;
    }
}

// The pooled lists' out-of-line members this unit instantiates
// (game/netqueue.h). Where several element types compile to the same bytes,
// /OPT:ICF keeps one and config/aliases.txt points the others at it.
// match: ??1?$type_1FA230_list@Utype_1D7CA0@@@@QAE@XZ @ 0x001D0AD0
// match: __ehhandler$??1?$type_1FA230_list@Utype_1D7CA0@@@@QAE@XZ-0x8 @ 0x003035E0
// match: __ehhandler$??1?$type_1FA230_list@Utype_1D7CA0@@@@QAE@XZ @ 0x003035E8
// match: ?sub_1D44B0@?$type_1FA230_list@Utype_1D3C80@@@@QAEXXZ @ 0x001D4440
// match: ?sub_1D44B0@?$type_1FA230_list@Utype_3E4E4C@@@@QAEXXZ @ 0x001D44B0
// match: ??1?$type_1FA230_list@Utype_3E4E4C@@@@QAE@XZ @ 0x001D4010

// match: ?sub_1D0B30@type_1D0100@@QAEXABUtype_1DDE20_mask@@@Z @ 0x001D0B30
// The empty `if (!unk_794)` blocks are compiled-out checks; each moves the
// registers after it on by one load (docs/toolchain.md). Local names state
// their slots; plain var_N names reorder them.
void type_1D0100::sub_1D0B30(const type_1DDE20_mask &arg_0)
{
    RwUInt32 bp_4;
    RwUInt32 x8;
    RwUInt32 locc;
    RwInt32 ebp_10;
    type_3E4E84 *y14;

    sub_1D4530(&unk_04, arg_0);
    sub_1D4530(&unk_1C, arg_0);
    ebp_10 = unk_34.sub_191D80();
    if (ebp_10)
    {
        y14 = unk_34.first();
        while (ebp_10--)
        {
            if (!unk_794)
            {
            }
            type_1DDE20_mask m = y14->unk_10;

            if (!unk_794)
            {
            }
            if (m.overlaps(arg_0))
            {
                if (!unk_794)
                {
                }
                m.unk_00 &= ~arg_0.unk_00;
                if (m.empty())
                {
                    y14 = unk_34.sub_1D4100();
                    continue;
                }
                y14->unk_10 = m;
            }
            y14 = unk_34.sub_1D0E70();
        }
    }
    locc = ((type_1DDE20_mask &)arg_0).sub_1D4900();
    bp_4 = ((type_1DDE20_mask &)arg_0).sub_1D48E0();
    for (x8 = locc; x8 <= bp_4; x8++)
    {
        if (((type_1DDE20_mask &)arg_0).test(x8))
        {
            type_1D7CA0 *e;

            unk_480[x8] = 0;
            unk_440[x8] = sub_1CCA10();
            ebp_10 = unk_64[x8]->count();
            if (ebp_10)
            {
                e = unk_64[x8]->first();
                while (ebp_10--)
                {
                    e->sub_1D7CA0();
                    e = unk_64[x8]->sub_1D4100();
                }
            }
            if (!unk_794)
            {
            }
            unk_A4[x8] = -1;
            if (!unk_794)
            {
            }
            if (!unk_794)
            {
            }
            if (!unk_794)
            {
            }
            unk_E4[x8]->empty();
            if (!unk_794)
            {
            }
            unk_124[x8] = -1;
            unk_380[x8] = 0;
            unk_3C0[x8] = 0;
            unk_400[x8] = 0;
            unk_4C4.unk_50[x8] = 0;
            unk_4C4.unk_210[x8] = 0;
            unk_4C4.unk_110[x8] = 0;
            unk_4C4.unk_1D0[x8] = 0;
            unk_4C4.unk_D0[x8] = 0;
            unk_4C4.unk_250[x8] = 0;
            unk_4C4.unk_150[x8] = 0;
            unk_4C4.unk_290[x8] = 0;
            unk_4C4.unk_190[x8] = 0;
        }
    }
}

// match: ?sub_1D0EC0@type_1D0100@@QAEXXZ @ 0x001D0EC0
void type_1D0100::sub_1D0EC0()
{
    sub_1D4630(&unk_04, unk_180, unk_1C0, 100);
    sub_1D4630(&unk_1C, unk_200, unk_240, 100);
    sub_1D4770(&unk_34, unk_280, unk_2C0, 50);
    sub_1D4630(&unk_4C, unk_300, unk_340, 100);
}
// match: ??$sub_1D4630@Utype_3E4E4C@@@@YAXPAU?$type_1FA230_list@Utype_3E4E4C@@@@QAPAPAUtype_3E4E4C@@PAHH@Z @ 0x001D4630

// addPacket, named by its traces ("addPacket ran out of ram, ..."): queues
// arg_4's arg_8 bits for the peers arg_0 at the time arg_C, as a plain
// message (arg_10 0), a per-peer one (3) or a timed one (1, 4 and the rest,
// each numbered in its own sequence); its handle, 0 when out of memory.
// The compiled-out checks set its registers, and the four that keep three
// locals each (NETQUEUE_CHECK) give the image's twelve slots no instruction
// touches.
// match: ?sub_1D0F60@type_1D0100@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@HABUtype_1CCA10@@H@Z @ 0x001D0F60
// match: __ehhandler$?sub_1D0F60@type_1D0100@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@HABUtype_1CCA10@@H@Z-0x1E @ 0x00303600
// match: __ehhandler$?sub_1D0F60@type_1D0100@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@HABUtype_1CCA10@@H@Z @ 0x0030361E
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1D0100::sub_1D0F60(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8,
                                const type_1CCA10 &arg_C, RwInt32 arg_10)
{
    type_3E4E4C var_128;
    RwUInt32 frm_110;
    type_3E4E58 m_10C;
    type_3E4E40 var6C;
    type_3E4E34 *lv_10;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_794)
    {
    }
    if (((type_1DDE20_mask &)arg_0).empty())
        return 0;
    // Two compiled-out checks (docs/toolchain.md).
    if (!unk_794)
    {
    }
    if (!unk_794)
    {
    }
    if (!arg_10)
        lv_10 = &var_128;
    else if (arg_10 == 3)
        lv_10 = &var6C;
    else
        lv_10 = &m_10C;
    if (!lv_10->vf_004(arg_4->get_unk_00(), arg_8))
    {
        if (CODFH_DEBUG_LOGS)
            off_42CD14("addPacket ran out of ram, packet chucked!! %s : %d\n", "\\COD\\SHARED\\network\\knet\\cPacketEngine.cpp", 450);
        if (arg_10 != 0 && arg_10 != 3)
        {
            if (CODFH_DEBUG_LOGS)
                off_42CD14("addPacket ran out of ram on a guaranteed packet... send less, or increase sizes of buffers!!\n");
        }
        unk_794 = 1;
        return 0;
    }
    NETQUEUE_CHECK(arg_10);
    NETQUEUE_CHECK(arg_10);
    lv_10->unk_14 = arg_8;
    lv_10->unk_0C = arg_C;
    lv_10->unk_08 = arg_0;
    lv_10->unk_0A = ((type_1DDE20_mask &)arg_0).sub_1D48E0();
    lv_10->unk_0B = ((type_1DDE20_mask &)arg_0).sub_1D4900();
    if (!arg_10)
    {
        lv_10->unk_04 = unk_178;
        if (!unk_04.sub_1D3F80(var_128))
        {
            lv_10->vf_008();
            if (CODFH_DEBUG_LOGS)
                off_42CD14("addPacket ran out of ram, packet chucked!! %s : %d\n", "\\COD\\SHARED\\network\\knet\\cPacketEngine.cpp", 489);
            unk_794 = 1;
            return 0;
        }
        unk_178++;
    }
    else if (arg_10 == 3)
    {
        lv_10->unk_04 = unk_17C;
        unk_17C++;
        for (frm_110 = lv_10->unk_0B; frm_110 <= lv_10->unk_0A; frm_110++)
        {
            if (((type_1DDE20_mask &)arg_0).test(frm_110))
            {
                var6C.unk_18[frm_110] = unk_400[frm_110];
                unk_400[frm_110] = lv_10->unk_04;
            }
        }
        if (!unk_4C.sub_1D3F80(var6C))
        {
            lv_10->vf_008();
            if (CODFH_DEBUG_LOGS)
                off_42CD14("addPacket ran out of ram, packet chucked!! %s : %d\n", "\\COD\\SHARED\\network\\knet\\cPacketEngine.cpp", 532);
            unk_794 = 1;
            return 0;
        }
    }
    else
    {
        type_1CCA10 t = arg_C + 0;

        NETQUEUE_CHECK(unk_794);
        if (arg_10 == 1)
        {
            lv_10->unk_04 = unk_16C;
            m_10C.unk_98 = 0;
        }
        else if (arg_10 == 4)
        {
            NETQUEUE_CHECK(unk_794);
            lv_10->unk_04 = unk_174;
            m_10C.unk_98 = 0;
        }
        else
        {
            // Two compiled-out checks (docs/toolchain.md).
            if (!unk_794)
            {
            }
            if (!unk_794)
            {
            }
            lv_10->unk_04 = unk_170;
            m_10C.unk_98 = 1;
        }
        lv_10->unk_0C = t;
        unk_16C += 4;
        unk_174 += 4;
        unk_170 += 4;
        for (frm_110 = lv_10->unk_0B; frm_110 <= lv_10->unk_0A; frm_110++)
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            if (((type_1DDE20_mask &)arg_0).test(frm_110))
            {
                m_10C.unk_18[frm_110] = t;
                if (arg_10 == 4)
                {
                    m_10C.unk_58[frm_110] = unk_3C0[frm_110];
                    unk_3C0[frm_110] = lv_10->unk_04;
                }
                else
                {
                    m_10C.unk_58[frm_110] = unk_380[frm_110];
                    unk_380[frm_110] = lv_10->unk_04;
                }
            }
        }
        if (!unk_1C.sub_1D3F80(m_10C))
        {
            lv_10->vf_008();
            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            unk_794 = 1;
            return 0;
        }
    }
    // A compiled-out check (docs/toolchain.md).
    if (!unk_794)
    {
    }
    return lv_10->unk_04;
}
// match: ?sub_1D0E70@?$type_1FA230_list@Utype_3E4E84@@@@QAEPAUtype_3E4E84@@XZ @ 0x001D0E70
// match: ?sub_1D4100@?$type_1FA230_list@Utype_3E4E84@@@@QAEPAUtype_3E4E84@@XZ @ 0x001D4100
// match: ??$sub_1D4530@Utype_3E4E4C@@@@YAXPAU?$type_1FA230_list@Utype_3E4E4C@@@@ABUtype_1DDE20_mask@@@Z @ 0x001D4530

// match: ?sub_1D17B0@type_1D0100@@QAE?AUtype_1DDE20_mask@@H@Z @ 0x001D17B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Each return copies the mask one load on from the plain copy, as if the copy
// held a compiled-out check; the empty `if (!unk_794)` before each return
// gives that (docs/toolchain.md).
type_1DDE20_mask type_1D0100::sub_1D17B0(RwInt32 arg_0)
{
    type_3E4E58 *bp_4;
    type_1DDE20_mask x8;
    RwInt32 locc;

    locc = unk_1C.sub_191D80();
    if (!locc)
    {
        if (!unk_794)
        {
        }
        return x8;
    }
    bp_4 = unk_1C.last();
    if ((RwUInt32)arg_0 > bp_4->unk_04)
    {
        if (!unk_794)
        {
        }
        return x8;
    }
    bp_4 = unk_1C.first();
    if ((RwUInt32)arg_0 < bp_4->unk_04)
    {
        if (!unk_794)
        {
        }
        return x8;
    }
    while (locc--)
    {
        if (bp_4->unk_04 == (RwUInt32)arg_0)
        {
            if (!unk_794)
            {
            }
            return bp_4->unk_08;
        }
        bp_4 = unk_1C.sub_1D0E70();
    }
    if (!unk_794)
    {
    }
    return x8;
}

// match: ?sub_1D18E0@type_1D0100@@QAE?AUtype_1DDE20_mask@@H@Z @ 0x001D18E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Each return copies the mask one load on from the plain copy, as if the copy
// held a compiled-out check; the empty `if (!unk_794)` before each return
// gives that (docs/toolchain.md).
type_1DDE20_mask type_1D0100::sub_1D18E0(RwInt32 arg_0)
{
    type_3E4E58 *bp_4;
    type_1DDE20_mask x8;
    RwInt32 locc;

    locc = unk_1C.sub_191D80();
    if (!locc)
    {
        if (!unk_794)
        {
        }
        return x8;
    }
    bp_4 = unk_1C.last();
    if ((RwUInt32)arg_0 > bp_4->unk_04)
    {
        if (!unk_794)
        {
        }
        return x8;
    }
    bp_4 = unk_1C.first();
    if ((RwUInt32)arg_0 < bp_4->unk_04)
    {
        if (!unk_794)
        {
        }
        return x8;
    }
    while (locc--)
    {
        if (bp_4->unk_04 == (RwUInt32)arg_0)
        {
            x8 = bp_4->unk_08;
            bp_4->vf_008();
            unk_1C.sub_1D4100();
            if (!unk_794)
            {
            }
            return x8;
        }
        bp_4 = unk_1C.sub_1D0E70();
    }
    if (!unk_794)
    {
    }
    return x8;
}

// match: ?sub_1D1A30@type_1D0100@@QAEPAUtype_3E4E84@@HH@Z @ 0x001D1A30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3E4E84 *type_1D0100::sub_1D1A30(RwInt32 arg_0, RwInt32 arg_4)
{
    type_3E4E84 *bp_4;
    RwInt32 x8;

    x8 = unk_34.sub_191D80();
    if (!x8)
        return 0;
    bp_4 = unk_34.first();
    while (x8--)
    {
        if (bp_4 && bp_4->unk_04 == (RwUInt32)arg_0)
        {
            // Two compiled-out checks (docs/toolchain.md): the registers
            // after them are two loads on.
            if (!unk_794)
            {
            }
            if (!unk_794)
            {
            }
            if (bp_4->unk_10.test(arg_4))
                return bp_4;
        }
        bp_4 = unk_34.sub_1D0E70();
    }
    return 0;
}

// The message classes' compiler-made members and the lists' appends that
// addPacket instantiates.
// match: ??_Gtype_3E4E30@@UAEPAXI@Z @ 0x001D1650
// match: ??0type_3E4E34@@QAE@XZ @ 0x001D1680
// match: ??_Gtype_3E4E34@@UAEPAXI@Z @ 0x001D16D0
// match: ??1type_3E4E34@@UAE@XZ @ 0x001D1700
// match: ??0type_3E4E58@@QAE@XZ @ 0x001D1720
// The packet copy at 0x1D4290 is placed from unit_1D4290.cpp. Its
// packet-only include context preserves the generated array-loop slots.
// match: ??0type_3E4E34@@QAE@ABU0@@Z @ 0x001D43B0
// match: ?sub_1D3F80@?$type_1FA230_list@Utype_3E4E4C@@@@QAEHABUtype_3E4E4C@@@Z @ 0x001D3F80
// match: ?sub_1D3F80@?$type_1FA230_list@Utype_3E4E58@@@@QAEHABUtype_3E4E58@@@Z @ 0x001D4070
// match: ?sub_1D3F80@?$type_1FA230_list@Utype_3E4E40@@@@QAEHABUtype_3E4E40@@@Z @ 0x001D41E0
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E40@@@@QAEHABUtype_3E4E40@@@Z-0x11 @ 0x00303650
// match: __ehhandler$?sub_1D3F80@?$type_1FA230_list@Utype_3E4E40@@@@QAEHABUtype_3E4E40@@@Z @ 0x00303661

// The ack list's append (its handler folded, /OPT:ICF, into the one above)
// and the ack's compiler-made destructor; no matched caller instantiates
// them yet. Its implicit copy selects the const mask's checked overload.
// match: ??0type_3E4E84@@QAE@ABU0@@Z @ 0x001D4320
// match: ??_Gtype_3E4E84@@UAEPAXI@Z @ 0x001D35C0
// match: ??1type_3E4E84@@UAE@XZ @ 0x001D35F0
// match: ?sub_1D3F80@?$type_1FA230_list@Utype_3E4E84@@@@QAEHABUtype_3E4E84@@@Z @ 0x001D4150
template RwInt32 type_1FA230_list<type_3E4E84>::sub_1D3F80(const type_3E4E84 &arg_0);

// match: ?sub_1D1AE0@type_1D0100@@QAEXHH@Z @ 0x001D1AE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1D0100::sub_1D1AE0(RwInt32 arg_0, RwInt32 arg_4)
{
    type_3E4E58 *bp_4;
    RwInt32 x8;

    x8 = unk_1C.sub_191D80();
    if (!x8)
        return;
    bp_4 = unk_1C.last();
    if ((RwUInt32)arg_0 > bp_4->unk_04)
        return;
    bp_4 = unk_1C.first();
    if ((RwUInt32)arg_0 < bp_4->unk_04)
        return;
    while (x8--)
    {
        if (bp_4->unk_04 == (RwUInt32)arg_0)
        {
            // Two compiled-out checks (docs/toolchain.md): the registers
            // after them are two loads on.
            if (!unk_794)
            {
            }
            if (!unk_794)
            {
            }
            if (bp_4->unk_08.test(arg_4))
            {
                bp_4->unk_08.clear(arg_4);
                if (bp_4->unk_08.empty())
                {
                    bp_4->vf_008();
                    unk_1C.sub_1D4100();
                }
                return;
            }
        }
        bp_4 = unk_1C.sub_1D0E70();
    }
}

// match: ?sub_1D1C30@type_1D0100@@QAEXHABUtype_1CCA10@@@Z @ 0x001D1C30
void type_1D0100::sub_1D1C30(RwInt32 arg_0, const type_1CCA10 &arg_4)
{
    RwInt32 bp_4;
    RwInt32 x8;
    RwInt32 locc;
    RwUInt32 ebp_10;
    RwInt32 y14;
    RwInt32 ebp_18;
    type_3E4E58 *frm_1a8[100];

    if (!unk_794)
    {
    }
    bp_4 = 0;
    y14 = 0;
    locc = 0;
    ebp_18 = 0;
    ebp_10 = 0;
    x8 = unk_798.test(arg_0);
    if (unk_340[arg_0])
    {
        RwInt32 loc1ac = unk_340[arg_0];
        RwInt32 lv_1b4;
        type_3E4E40 **var_1b8 = unk_300[arg_0];

        for (lv_1b4 = 0; lv_1b4 < loc1ac - 1; lv_1b4++)
        {
            type_3E4E40 *frm_1c0 = var_1b8[lv_1b4];
            type_3E4E40 *local_1bc = var_1b8[lv_1b4 + 1];

            frm_1c0 = frm_1c0;
            local_1bc = local_1bc;
            if (!unk_794)
            {
            }
            if (!unk_794)
            {
            }
        }
        type_3E4E40 *ebp_1b0 = var_1b8[loc1ac - 1];

        if (arg_4 > ebp_1b0->unk_0C)
            ebp_18 = 1;
    }
    if (!x8 && type_1CCA10(arg_4 - unk_440[arg_0]) < 50 && !ebp_18)
        return;
    if (unk_1C0[arg_0])
    {
        RwInt32 l1c4 = unk_1C0[arg_0];
        RwInt32 frm_1cc;
        type_3E4E4C **u1d0 = unk_180[arg_0];

        for (frm_1cc = 0; frm_1cc < l1c4 - 1; frm_1cc++)
        {
            type_3E4E4C *bp_1d8 = u1d0[frm_1cc];
            type_3E4E4C *lv_1d4 = u1d0[frm_1cc + 1];

            bp_1d8 = bp_1d8;
            lv_1d4 = lv_1d4;
            if (!unk_794)
            {
            }
        }
        // A compiled-out check on a computed value (docs/toolchain.md): the
        // registers after it are one load on.
        if (!(l1c4 & 1))
        {
        }
        type_3E4E4C *ebp_1c8 = u1d0[l1c4 - 1];

        if (arg_4 > ebp_1c8->unk_0C || ebp_18)
            bp_4 = 1;
    }
    if (unk_240[arg_0])
    {
        RwUInt32 x1dc = unk_240[arg_0];
        RwUInt32 fp_1e0;
        type_3E4E58 **ebp_1e4 = unk_200[arg_0];

        for (fp_1e0 = 0; fp_1e0 < x1dc; fp_1e0++)
        {
            type_3E4E58 *bp_1ec = ebp_1e4[fp_1e0];
            RwInt32 frm_1e8 = bp_1ec->unk_18[arg_0].get_unk_00() - arg_4.get_unk_00();

            if (frm_1e8 < 0 || ebp_18)
            {
                frm_1a8[ebp_10] = bp_1ec;
                ebp_10++;
            }
        }
        if (ebp_10 > 0)
        {
            y14 = 1;
            if (unk_1C0[arg_0])
                bp_4 = 1;
        }
    }
    if (unk_2C0[arg_0])
    {
        RwUInt32 w1f0 = unk_2C0[arg_0];
        type_3E4E84 **ebp_1f4 = unk_280[arg_0];

        if (bp_4 || y14 || ebp_18)
            locc = 1;
        else
        {
            for (RwUInt32 lv_1f8 = 0; lv_1f8 < w1f0; lv_1f8++)
            {
                if (ebp_1f4[lv_1f8]->unk_08 < arg_4)
                {
                    locc = 1;
                    break;
                }
            }
        }
    }
    if (!x8 && bp_4 && !y14 && !locc && !ebp_18 && type_1CCA10(arg_4 - unk_440[arg_0]) < 83)
        return;
    if (bp_4 || y14 || locc || ebp_18)
    {
        sub_1D21E0(arg_0, bp_4, unk_180[arg_0], unk_1C0[arg_0], y14, frm_1a8, ebp_10, locc, unk_280[arg_0],
                   unk_2C0[arg_0], ebp_18, unk_300[arg_0], unk_340[arg_0], arg_4);
        unk_440[arg_0] = arg_4;
        if (x8)
            unk_798.clear(arg_0);
    }
}

// Peer arg_0's packet at the time arg_34: its check (when the game uses one),
// then its acks (arg_20, arg_24 of them; each done with dropped, the rest
// due again in 100 ms), the timed messages (arg_14, arg_18; due again in
// 250 ms), the plain ones (arg_8, arg_C; each done with once no peer is
// left) and, when arg_28 is set, the per-peer ones (arg_2C, arg_30) in the
// second buffer; the statistics kept and the lot handed to the game.
// match: ?sub_1D21E0@type_1D0100@@QAEXHHPAPAUtype_3E4E4C@@HHPAPAUtype_3E4E58@@IHPAPAUtype_3E4E84@@HHPAPAUtype_3E4E40@@HABUtype_1CCA10@@@Z @ 0x001D21E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1D0100::sub_1D21E0(RwInt32 arg_0, RwInt32 arg_4, type_3E4E4C **arg_8, RwInt32 arg_C, RwInt32 arg_10,
                             type_3E4E58 **arg_14, RwUInt32 arg_18, RwInt32 arg_1C, type_3E4E84 **arg_20,
                             RwInt32 arg_24, RwInt32 arg_28, type_3E4E40 **arg_2C, RwInt32 arg_30,
                             const type_1CCA10 &arg_34)
{
    RwInt32 var_50;
    RwUInt32 var_4C;
    RwInt32 stk_3C;
    RwInt32 ebp_38;
    RwInt32 q28;
    RwInt32 frm_24;
    RwInt32 var_20;
    RwUInt32 l1C;
    type_1F8560 *m_18;
    RwUInt32 ebp_14;
    RwUInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_794)
    {
    }
    type_1F8560 var_34(unk_164, 0x2400);
    type_1F8560 var_48(unk_168, 0x2400);

    m_18 = &var_48;
    var_4C = (RwUInt32)-1;
    ebp_38 = -1;
    bp_8 = unk_79C->vf_03C();
    l1C = 0;
    bp_4 = 0;
    if (!unk_4C4.unk_50[arg_0])
    {
        unk_4C4.unk_50[arg_0] = 1;
        unk_4C4.unk_90[arg_0] = arg_34;
    }
    stk_3C = 0;
    var_34.sub_1F8520(0);
    var_34.sub_1F8860(0, 6);
    stk_3C++;
    if (bp_8)
    {
        var_4C = var_34.get_unk_08();
        type_1D2CC0_check var_60;

        var_34.sub_1F89D0(var_60.unk_00, 0x48);
        stk_3C += 9;
    }
    q28 = 0;
    for (ebp_14 = 0; ebp_14 < (RwUInt32)arg_24; ebp_14++)
    {
        RwUInt32 var_64;

        if (!ebp_14)
            q28 = arg_20[0]->unk_04;
        var_64 = var_34.get_unk_08() + 0x66;
        if (var_64 > 0x2400)
        {
            arg_24 = ebp_14;
            break;
        }
        var_34.sub_1F8520(1);
        if (!ebp_14)
            var_34.sub_1F88A0(q28);
        else
        {
            RwInt32 var_68;

            var_68 = arg_20[ebp_14]->unk_04 - q28;
            var_34.sub_1F8AB0(var_68);
            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            q28 = arg_20[ebp_14]->unk_04;
        }
        if (arg_34 >= arg_20[ebp_14]->unk_0C)
        {
            unk_34.unk_08 = unk_34.node(arg_20[ebp_14]);
            unk_34.sub_1D4100();
            continue;
        }
        arg_20[ebp_14]->unk_08 = arg_34 + 100;
    }
    var_34.sub_1F8520(0);
    var_C = 0;
    var_50 = 1;
    frm_24 = 0;
    var_20 = 0;
    for (ebp_14 = 0; ebp_14 < arg_18; ebp_14++)
    {
        RwInt32 loc70;
        RwUInt32 var_6C = var_34.get_unk_08() + arg_14[ebp_14]->unk_14 + 0xAF;

        if (var_6C > 0x2400)
            break;
        var_C++;
        var_34.sub_1F8520(1);
        if (var_50)
        {
            RwInt32 var_74;

            var_34.sub_1F88A0(arg_14[ebp_14]->unk_04);
            var_74 = arg_14[ebp_14]->unk_58[arg_0] - arg_14[ebp_14]->unk_04;
            var_34.sub_1F8AB0(var_74);
            var_50 = 0;
            frm_24 = arg_14[ebp_14]->unk_04;
            var_20 = arg_14[ebp_14]->unk_58[arg_0];
        }
        else
        {
            RwInt32 var_78;

            var_78 = arg_14[ebp_14]->unk_04 - frm_24;
            var_34.sub_1F8AB0(var_78);
            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            frm_24 = arg_14[ebp_14]->unk_04;
            var_78 = arg_14[ebp_14]->unk_58[arg_0] - var_20;
            var_34.sub_1F8AB0(var_78);
            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            var_20 = arg_14[ebp_14]->unk_58[arg_0];
        }
        var_34.sub_1F88A0(arg_14[ebp_14]->unk_14 - 1);
        var_34.sub_1F89D0(arg_14[ebp_14]->unk_10, arg_14[ebp_14]->unk_14);
        unk_4C4.unk_110[arg_0] += arg_14[ebp_14]->unk_14;
        loc70 = arg_34.get_unk_00() - arg_14[ebp_14]->unk_18[arg_0].get_unk_00();
        if (loc70 < 0)
            loc70 = 0;
        arg_14[ebp_14]->unk_18[arg_0] = arg_34.get_unk_00() - loc70 + 0xFA;
    }
    var_34.sub_1F8520(0);
    for (ebp_14 = 0; ebp_14 < (RwUInt32)arg_C; ebp_14++)
    {
        RwUInt32 var_7C;

        // A compiled-out check (docs/toolchain.md).
        if (!unk_794)
        {
        }
        var_7C = var_34.get_unk_08() + arg_8[ebp_14]->unk_14 + 0x8A;

        if (var_7C > 0x2400)
        {
            arg_C = ebp_14;
            break;
        }
        var_34.sub_1F8520(1);
        if (!ebp_14)
            var_34.sub_1F88A0(arg_8[0]->unk_04);
        var_34.sub_1F88A0(arg_8[ebp_14]->unk_14 - 1);
        var_34.sub_1F89D0(arg_8[ebp_14]->unk_10, arg_8[ebp_14]->unk_14);
        unk_4C4.unk_D0[arg_0] += arg_8[ebp_14]->unk_14;
        // A compiled-out check (docs/toolchain.md).
        if (!unk_794)
        {
        }
        arg_8[ebp_14]->unk_08.clear(arg_0);
        if (arg_8[ebp_14]->unk_08.empty())
        {
            arg_8[ebp_14]->vf_008();
            unk_04.unk_08 = unk_04.node(arg_8[ebp_14]);
            unk_04.sub_1D4100();
        }
    }
    var_34.sub_1F8520(0);
    if (arg_28)
    {
        var_50 = 1;
        frm_24 = 0;
        var_20 = 0;
        for (ebp_14 = 0; ebp_14 < (RwUInt32)arg_30; ebp_14++)
        {
            RwUInt32 var_80;

            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            var_80 = m_18->get_unk_08() + arg_2C[ebp_14]->unk_14 + 0xAF;

            if (var_80 > 0x2400)
            {
                arg_30 = ebp_14;
                break;
            }
            m_18->sub_1F8520(1);
            if (var_50)
            {
                RwInt32 var_84;

                m_18->sub_1F88A0(arg_2C[ebp_14]->unk_04);
                var_84 = arg_2C[ebp_14]->unk_18[arg_0] - arg_2C[ebp_14]->unk_04;
                m_18->sub_1F8AB0(var_84);
                var_50 = 0;
                frm_24 = arg_2C[ebp_14]->unk_04;
                var_20 = arg_2C[ebp_14]->unk_18[arg_0];
            }
            else
            {
                RwInt32 var_88;

                var_88 = arg_2C[ebp_14]->unk_04 - frm_24;
                m_18->sub_1F8AB0(var_88);
                // A compiled-out check (docs/toolchain.md).
                if (!unk_794)
                {
                }
                frm_24 = arg_2C[ebp_14]->unk_04;
                var_88 = arg_2C[ebp_14]->unk_18[arg_0] - var_20;
                m_18->sub_1F8AB0(var_88);
                // A compiled-out check (docs/toolchain.md).
                if (!unk_794)
                {
                }
                var_20 = arg_2C[ebp_14]->unk_18[arg_0];
            }
            m_18->sub_1F88A0(arg_2C[ebp_14]->unk_14 - 1);
            m_18->sub_1F89D0(arg_2C[ebp_14]->unk_10, arg_2C[ebp_14]->unk_14);
            unk_4C4.unk_150[arg_0] += arg_2C[ebp_14]->unk_14;
            // A compiled-out check (docs/toolchain.md).
            if (!unk_794)
            {
            }
            arg_2C[ebp_14]->unk_08.clear(arg_0);
            if (arg_2C[ebp_14]->unk_08.empty())
            {
                arg_2C[ebp_14]->vf_008();
                unk_4C.unk_08 = unk_4C.node(arg_2C[ebp_14]);
                unk_4C.sub_1D4100();
            }
        }
        m_18->sub_1F8520(0);
        l1C = (var_48.get_unk_08() + 7) >> 3;
    }
    lv_10 = (var_34.get_unk_08() + 7) >> 3;
    if (bp_8)
    {
        var_34.sub_1F8860(0, 7);
        type_1D2CC0_check var_94;

        var_94.sub_73D90(unk_164 + stk_3C, lv_10 - stk_3C);
        var_34.unk_08 = var_4C;
        var_34.sub_1F89D0(var_94.unk_00, 0x48);
    }
    if (unk_79C->vf_040(arg_0))
        unk_79C->vf_020((RwInt32)(unk_164 + stk_3C), lv_10 - stk_3C - bp_4);
    unk_4C4.unk_00[0] += lv_10 + l1C;
    unk_4C4.unk_00[2] += lv_10 + l1C + 0x26;
    unk_4C4.unk_190[arg_0] += 0x130;
    unk_79C->vf_044(arg_0, (RwInt32)unk_164, lv_10, l1C ? (RwInt32)unk_168 : 0, l1C);
}

// Peer arg_0's packet: its check (when the game uses one), then the acks, the
// guaranteed messages (in order or not, each acked), the unreliable ones and
// the extra stream's; the statistics kept. 0 when the packet is dropped.
// match: ?sub_1D2CC0@type_1D0100@@QAEHHPAEI0H@Z @ 0x001D2CC0
// match: __ehhandler$?sub_1D2CC0@type_1D0100@@QAEHHPAEI0H@Z-0xB @ 0x00303630
// match: __ehhandler$?sub_1D2CC0@type_1D0100@@QAEHHPAEI0H@Z @ 0x0030363B
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1D0100::sub_1D2CC0(RwInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8, RwUInt8 *arg_C, RwInt32 arg_10)
{
    RwInt32 local_70;
    RwInt32 var_6C;
    RwInt32 v68;
    RwInt32 frm_64;
    RwUInt32 t60;
    RwInt32 lcl_5C;
    RwInt32 bp_58;
    RwInt32 p54;
    RwInt32 var_50;
    RwInt32 m_4C;
    RwInt32 var44;
    RwInt32 l34;
    RwInt32 var30;
    RwInt32 ebp_1C;
    RwInt32 l18;
    RwInt32 v14;
    RwInt32 lv_10;

    type_1F8560 m_40(arg_4, 0x2400);

    t60 = 0;
    ebp_1C = unk_79C->vf_03C();
    type_1CCA10 local_48 = unk_79C->get_unk_7C();

    l18 = 0;
    // A compiled-out check (docs/toolchain.md).
    if (!unk_794)
    {
    }
    unk_480[arg_0] = local_48;
    unk_4C4.unk_00[1] += arg_8;
    unk_4C4.unk_00[3] += arg_8 + 0x26;
    var30 = m_40.sub_1F8560();
    if (var30)
    {
        unk_4C4.unk_18[3]++;
        return 0;
    }
    lcl_5C = m_40.sub_1F8810(6);
    if (lcl_5C)
    {
        unk_4C4.unk_18[3]++;
        return 0;
    }
    t60++;
    type_1D2CC0_check ebp_2C;
    if (ebp_1C)
    {
        m_40.sub_1F8A40((RwChar *)ebp_2C.unk_00, 0x48);
        t60 += 9;
    }
    if (unk_79C->vf_028(arg_0) == 1)
    {
        local_70 = 1;
        if (ebp_1C)
        {
            type_1D2CC0_check var_7C;

            var_7C.sub_73D90(arg_4 + t60, arg_8 - t60);
            if (arg_8 <= t60 || var_7C != ebp_2C)
                local_70 = 0;
        }
        if (!local_70)
            unk_79C->vf_02C(arg_0, 2);
    }
    if (unk_79C->vf_040(arg_0))
        unk_79C->vf_024(arg_0, (RwInt32)(arg_4 + t60), arg_8 - t60);
    if (ebp_1C)
    {
        type_1D2CC0_check var_88;

        var_88.sub_73D90(arg_4 + t60, arg_8 - t60);
        if (arg_8 <= t60 || var_88 != ebp_2C)
        {
            unk_4C4.unk_18[3]++;
            if (unk_79C->vf_028(arg_0) == 2)
                unk_4C4.unk_18[4]++;
            return 0;
        }
    }
    v14 = 0;
    frm_64 = 0;
    while (m_40.sub_1F8560())
    {
        if (!v14)
            frm_64 = m_40.sub_1F8950();
        else
            frm_64 += m_40.sub_1F8AF0();
        v14++;
        sub_1D1AE0(frm_64, arg_0);
    }
    bp_58 = 0;
    var44 = 0;
    l34 = 0;
    var_6C = 1;
    while (m_40.sub_1F8560())
    {
        type_3E4E84 *stk_8C;
        RwUInt32 fp_90;
        RwInt32 t94;
        RwInt32 w98;


        if (var_6C)
        {
            var_6C = 0;
            var44 = m_40.sub_1F8950();
            l34 = m_40.sub_1F8AF0() + var44;
        }
        else
        {
            var44 += m_40.sub_1F8AF0();
            l34 += m_40.sub_1F8AF0();
        }
        t94 = m_40.sub_1F8950() + 1;
        fp_90 = t94 + m_40.get_unk_08();
        w98 = var44;
        if (!(var44 & 3))
            sub_1D3C80(var44, l34, arg_0, &m_40, t94);
        else
            sub_1D3770(var44, l34, arg_0, &m_40, t94);
        unk_4C4.unk_210[arg_0] += t94;
        stk_8C = sub_1D1A30(w98, arg_0);
        if (!stk_8C)
        {
            type_3E4E84 var_AC;

            var_AC.unk_0C = local_48 + type_1CCA10(0xA6);
            var_AC.unk_08 = local_48;
            NETQUEUE_CHECK(unk_794);
            var_AC.unk_12 = (RwUInt8)arg_0;
            var_AC.unk_13 = (RwUInt8)arg_0;
            NETQUEUE_CHECK(unk_794);
            var_AC.unk_10.unk_00 = 1 << arg_0;
            var_AC.unk_04 = w98;
            if (!unk_34.sub_1D3F80(var_AC))
            {
                if (CODFH_DEBUG_LOGS)
                    off_42CD14("Just ran out of ram in ACK que!");
                unk_794 = 1;
            }
        }
        else
        {
            stk_8C->unk_0C = local_48 + type_1CCA10(0xA6);
            stk_8C->unk_08 = local_48;
        }
        m_40.unk_08 = fp_90;
        bp_58++;
    }
    p54 = 0;
    lv_10 = 0;
    while (m_40.sub_1F8560())
    {
        RwUInt32 oB0;
        RwInt32 xB4;


        if (!p54)
            lv_10 = m_40.sub_1F8950();
        xB4 = m_40.sub_1F8950() + 1;
        oB0 = xB4 + m_40.get_unk_08();
        unk_79C->sub_1CC7D0(lv_10, arg_0, (RwInt32)&m_40, xB4);
        unk_4C4.unk_1D0[arg_0] += xB4;
        m_40.unk_08 = oB0;
        p54++;
    }
    v68 = 0;
    var_50 = 0;
    m_4C = 0;
    if (arg_10)
    {
        type_1F8560 var_C4(arg_C, 0x2400);
        type_1F8560 *var_B8;

        var_B8 = &var_C4;

        var_6C = 1;
        while (var_B8->sub_1F8560())
        {
            RwUInt32 wC8;
            RwInt32 oCC;


            if (var_6C)
            {
                var_6C = 0;
                var_50 = var_B8->sub_1F8950();
                m_4C = var_B8->sub_1F8AF0() + var_50;
            }
            else
            {
                var_50 += var_B8->sub_1F8AF0();
                m_4C += var_B8->sub_1F8AF0();
            }
            oCC = var_B8->sub_1F8950() + 1;
            wC8 = oCC + var_B8->get_unk_08();
            unk_79C->sub_1CC8A0(var_50, m_4C, arg_0, (RwInt32)&var_C4, oCC);
            unk_4C4.unk_250[arg_0] += oCC;
            var_B8->unk_08 = wC8;
            v68++;
        }
    }
    unk_4C4.unk_18[2]++;
    unk_4C4.unk_290[arg_0] += 0x130;
    return 1;
}

// match: ?sub_1D3610@type_1D0100@@QAEXABUtype_1CCA10@@@Z @ 0x001D3610
void type_1D0100::sub_1D3610(const type_1CCA10 &arg_0)
{
    RwUInt32 i;
    RwUInt32 span;

    if (arg_0 >= unk_4C4.unk_14 + 1000)
    {
        if (unk_4C4.unk_10.get_unk_00() == 0)
        {
            unk_4C4.unk_10 = arg_0;
            unk_4C4.unk_14 = unk_4C4.unk_10 + 1;
        }
        span = unk_4C4.unk_14.get_unk_00() - unk_4C4.unk_10.get_unk_00();
        unk_4C4.unk_14 = unk_4C4.unk_14 + 1000;
        unk_4C4.unk_18[0] = unk_4C4.unk_00[2] * 1000 / span;
        unk_4C4.unk_18[1] = unk_4C4.unk_00[3] * 1000 / span;
    }
    sub_1D0EC0();
    for (i = 0; i < 0x10; i++)
        sub_1D1C30(i, arg_0);
    if (unk_794)
        unk_79C->packetEngineHasRunOutOfRam();
}

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Peer arg_8's message number arg_0 (arg_4 its first) of arg_10 bits in the
// stream arg_C: handed on in order (odd numbers through sub_1CC780, even
// through sub_1CC820), then the kept ones that follow it; one arriving early
// is kept (once) until its turn.
// match: ?sub_1D3770@type_1D0100@@QAEXIIHPAUtype_1F8560@@H@Z @ 0x001D3770
void type_1D0100::sub_1D3770(RwUInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    RwInt32 l8;
    type_1D7CA0 *var_4;

    if (unk_A4[arg_8] == -1)
        unk_A4[arg_8] = arg_4;
    if (arg_0 <= (RwUInt32)unk_A4[arg_8])
        return;
    if (arg_4 != (RwUInt32)unk_A4[arg_8])
    {
        RwUInt8 var_418[0x408];
        RwInt32 bp_42C;
        type_1D7CA0 x428;

        bp_42C = unk_64[arg_8]->count();
        var_4 = unk_64[arg_8]->first();
        while (bp_42C--)
        {
            if (var_4->unk_04 == (RwInt32)arg_0)
                return;
            var_4 = unk_64[arg_8]->next();
        }
        arg_C->sub_1F8A40((RwChar *)var_418, arg_10);
        x428.unk_04 = arg_0;
        x428.unk_00 = arg_4;
        x428.unk_08 = 0;
        if (!x428.sub_1D7C30(var_418, arg_10))
        {
            if (CODFH_DEBUG_LOGS)
                off_42CD14("Just ran out of ram in receive in order - guaranteed packed que!");
            unk_794 = 1;
            return;
        }
        l8 = unk_64[arg_8]->add(x428);
        if (!l8)
        {
            x428.sub_1D7CA0();
            if (CODFH_DEBUG_LOGS)
                off_42CD14("Just ran out of ram in receive in order - guaranteed packed que!");
            unk_794 = 1;
            return;
        }
        return;
    }
    if (arg_0 & 1)
        unk_79C->sub_1CC780(arg_0, arg_8, (RwInt32)arg_C, arg_10);
    else
        unk_79C->sub_1CC820(arg_0, arg_8, arg_C, arg_10);
    unk_A4[arg_8] = arg_0;
    while (1)
    {
        RwInt32 var_430;
        RwInt32 bp_438;
        type_1D7CA0 *var_434;

        bp_438 = unk_64[arg_8]->count();
        if (!bp_438)
            return;
        var_434 = unk_64[arg_8]->first();
        var_430 = 0;
        while (bp_438--)
        {
            if (var_434->unk_00 == (RwInt32)arg_0)
            {
                type_1F8560 var_444(var_434->unk_08, var_434->unk_0C + 0x40);

                arg_0 = var_434->unk_04;
                unk_64[arg_8]->sub_1D4100();
                unk_A4[arg_8] = arg_0;
                if (arg_0 & 1)
                    unk_79C->sub_1CC780(arg_0, arg_8, (RwInt32)&var_444, var_434->unk_0C);
                else
                    unk_79C->sub_1CC820(arg_0, arg_8, &var_444, var_434->unk_0C);
                var_434->sub_1D7CA0();
                var_430 = 1;
                break;
            }
            var_434 = unk_64[arg_8]->next();
        }
        if (!var_430)
            return;
    }
}

// Peer arg_8's unordered message number arg_0 (arg_4 the one before it) of
// arg_10 bits in the stream arg_C: handed on (sub_1CC780) unless already
// seen; one arriving before its predecessor is noted (once) so the numbers
// it covers are skipped later (its trace: "receive unordered").
// match: ?sub_1D3C80@type_1D0100@@QAEXIIHPAUtype_1F8560@@H@Z @ 0x001D3C80
void type_1D0100::sub_1D3C80(RwUInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    type_1D3C80 *bp_4;
    RwInt32 var_8 = 0;
    RwInt32 m_C;

    if (unk_124[arg_8] == -1)
        unk_124[arg_8] = arg_4;
    if (arg_0 <= (RwUInt32)unk_124[arg_8])
        var_8 = 1;
    else if (arg_4 != (RwUInt32)unk_124[arg_8])
    {
        type_1D3C80 var_14;
        RwInt32 var_18 = unk_E4[arg_8]->count();

        bp_4 = unk_E4[arg_8]->first();
        while (var_18--)
        {
            if (bp_4->unk_04 == arg_0)
            {
                var_8 = 1;
                break;
            }
            bp_4 = unk_E4[arg_8]->next();
        }
        if (!var_8)
        {
            var_14.unk_04 = arg_0;
            var_14.unk_00 = arg_4;
            RwInt32 var_1C = unk_E4[arg_8]->add(var_14);

            if (!var_1C)
            {
                if (CODFH_DEBUG_LOGS)
                    off_42CD14("Just ran out of ram in receive unordered - guaranteed packed que!");
                unk_794 = 1;
                return;
            }
        }
    }
    else
    {
        unk_124[arg_8] = arg_0;
        while (1)
        {
            RwInt32 var_20;

            m_C = unk_E4[arg_8]->count();
            if (!m_C)
                break;
            bp_4 = unk_E4[arg_8]->first();
            var_20 = 0;
            while (m_C--)
            {
                if (bp_4->unk_00 == arg_0)
                {
                    arg_0 = bp_4->unk_04;
                    unk_E4[arg_8]->sub_1D4100();
                    unk_124[arg_8] = arg_0;
                    var_20 = 1;
                    break;
                }
                bp_4 = unk_E4[arg_8]->next();
            }
            if (!var_20)
                break;
        }
    }
    if (!var_8)
        unk_79C->sub_1CC780(arg_0, arg_8, (RwInt32)arg_C, arg_10);
}

// match: ?sub_1D4770@@YAXPAU?$type_1FA230_list@Utype_3E4E84@@@@QAPAPAUtype_3E4E84@@PAHH@Z @ 0x001D4770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1D4770(type_1FA230_list<type_3E4E84> *arg_0, type_3E4E84 **arg_4[16], RwInt32 *arg_8, RwInt32 arg_C)
{
    RwInt32 stk_40[16];
    RwUInt32 loc44;
    RwUInt32 var_48;
    RwUInt32 loc4c;
    type_3E4E84 *lcl_50;
    RwUInt32 y54;
    RwUInt32 u58;

    var_48 = arg_0->sub_191D80();
    memset(stk_40, 0, sizeof(stk_40));
    if (var_48)
    {
        lcl_50 = arg_0->first();
        for (loc4c = 0; loc4c < var_48; loc4c++)
        {
            if (lcl_50)
            {
                y54 = lcl_50->unk_12;
                u58 = lcl_50->unk_13;
                for (loc44 = u58; loc44 <= y54; loc44++)
                {
                    if (stk_40[loc44] == arg_C)
                        continue;
                    if (lcl_50->unk_10.test(loc44))
                    {
                        arg_4[loc44][stk_40[loc44]] = lcl_50;
                        stk_40[loc44]++;
                    }
                }
            }
            lcl_50 = arg_0->sub_1D0E70();
        }
    }
    for (loc44 = 0; loc44 < 0x10; loc44++)
        arg_8[loc44] = stk_40[loc44];
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_73D90@type_1D2CC0_check@@QAEXPBEI@Z (folded into 0x73D90)
void type_1D2CC0_check::sub_73D90(RwUInt8 const * arg_0, RwUInt32 arg_4)
{
}

// Always 1 (folded by /OPT:ICF into kujuUI's type_3E7C30::processEvent, 0x1F5A00).
RwInt32 type_1D2CC0_check::sub_1F5A00(const type_1D2CC0_check *arg_0)
{
    return 1;
}
