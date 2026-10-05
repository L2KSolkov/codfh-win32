// Split from unit_1D7CE0.cpp at 0x1D8370, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include <string.h>
#include "game/systemlink.h"
#include "types/cXboxLive.h"
#include "game/gameloop.h"
#include "types/cXboxLiveNetGame.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E52E4
extern const RwReal flt_3E52E4 = 0.01f;
// 0x003E52E8
extern const RwReal flt_3E52E8 = 0.01f;
// 0x003E52EC
extern const RwReal flt_3E52EC = 16.666666f;

// match: ?flt_3E52E4@@3MB @ 0x003E52E4
// match: ?flt_3E52E8@@3MB @ 0x003E52E8
// match: ?flt_3E52EC@@3MB @ 0x003E52EC


// match: _$E3 @ 0x0030EC00
// match: ??_C@_0P@IOIDDMKJ@SystemLinkHost?$AA@ @ 0x003E52F0
// match: ??_C@_0O@NPFKCNOE@Unknown?5Error?$AA@ @ 0x003E5EEC
// match: ??_C@_11LOCGONAA@?$AA?$AA@ @ 0x003E5300
// match: ??_C@_08PCBJDKE@failure?6?$AA@ @ 0x003E5304
// match: ??_C@_08IEFGGJPF@success?6?$AA@ @ 0x003E5310
// match: ??_C@_0CA@KKOBNEMH@Starting?5Xbox?5online?5library?4?4?4?$AA@ @ 0x003E531C
// match: ??_C@_0DD@DIIENAAJ@Trying?5to?5send?5message?5to?5non?9co@ @ 0x003E533C
// match: ??_C@_15MAOEGKJF@?$AA?$CF?$AAS?$AA?$AA@ @ 0x003E5370
// match: ??_C@_0FE@CJMIJJCM@cXboxLive?3?3createSession?$CI?$CJ?5?9?5ERR@ @ 0x003E5378
// match: ??_C@_0DN@PAJDCLCG@cXboxLive?3?3createSession?$CI?$CJ?5?9?5Cre@ @ 0x003E53CC
// match: ??_C@_02KPKOKMHB@?$CFS?$AA@ @ 0x003E540C
// match: ??_C@_0DE@LIOLEHLK@cXboxLive?3?3joinServer?$CI?$CJ?5?3?5send?5j@ @ 0x003E5410
// match: ??_C@_0FA@KFAPLILL@cXboxLive?3?3joinServer?$CI?$CJ?5?3?5failed@ @ 0x003E5448
// match: ??_C@_0DK@KFLCKMLD@cXboxLive?3?3joinServer?$CI?$CJ?5?3?5failed@ @ 0x003E5498
// match: ??_C@_0DD@JFNONLJO@cXboxLive?3?3joinServer?$CI?$CJ?5?3?5failed@ @ 0x003E54D4
// match: ??_C@_0CJ@JFJNHMK@cXboxLive?3?3joinServer?$CI?$CJ?5?3?5not?5lo@ @ 0x003E5508
// match: ??_C@_0DK@JJGNONOI@cXboxLive?3?3peerConnectToNewPlaye@ @ 0x003E5534
// match: ??_C@_0CK@FHAMFEIO@Attempting?5connection?5to?5player?5@ @ 0x003E5570
// match: ??_C@_0P@OGJLBNEC@?$CFd?4?$CFd?4?$CFd?4?$CFd?3?$CFd?$AA@ @ 0x003E559C
// match: ??_C@_0EF@FICLHPNE@cXboxLive?3?3disconnectPlayer?5?9?5co@ @ 0x003E55B0
// match: ??_C@_0CA@LGFMLEHP@cXboxLive?3?3disconnectPlayer?5?$CFd?6?$AA@ @ 0x003E55F8
// match: ??_C@_0BJ@DIALEAIE@Player?5?$CFd?5has?5been?5lost?6?$AA@ @ 0x003E5618
// match: ??_C@_0EO@INABDKLD@cXboxLive?3?5No?5response?5to?5connec@ @ 0x003E5638
// match: ??_C@_0DG@OMHILAKC@cXboxLive?3?5Connection?5attempt?5to@ @ 0x003E5688
// match: ??_C@_0BM@NIMGFDNB@Blocking?5player?5XUID?5?$CFI64u?6?$AA@ @ 0x003E56C0
// match: ??_C@_0DL@GPEEALBA@Non?9host?5peer?5received?5peer?9to?9h@ @ 0x003E56DC
// match: ??_C@_0DE@ICPICBPE@Ran?5out?5of?5slots?5?9?9?9?9?5connection@ @ 0x003E5718
// match: ??_C@_0BL@FKPLHIOO@KNET?3?5accepting?5player?5?$CFd?6?$AA@ @ 0x003E574C
// match: ??_C@_0DE@HHPJLBLC@Connection?5rejected?5?9?5player?5blo@ @ 0x003E5768
// match: ??_C@_0ED@FLFAHNIB@Peer?5received?5host?9to?9peer?5accep@ @ 0x003E57A0
// match: ??_C@_0FF@HEJHLLFI@Peer?5received?5host?9to?9peer?5accep@ @ 0x003E57E8
// match: ??_C@_0EB@OFIDNJKL@Peer?5host?9to?9peer?5accept?5with?5in@ @ 0x003E5840
// match: ??_C@_0DC@FLBBEBNC@Peer?5got?5accept?5from?5host?0?5conne@ @ 0x003E5884
// match: ??_C@_0DG@DDLMONFP@Host?5peer?5received?5host?9to?9peer?5@ @ 0x003E58B8
// match: ??_C@_0ED@EGAEOPJG@Peer?5received?5host?9to?9peer?5rejec@ @ 0x003E58F0
// match: ??_C@_0FF@GGPPEGNG@Peer?5received?5host?9to?9peer?5rejec@ @ 0x003E5938
// match: ??_C@_0EF@JDPMIFDG@Peer?5got?5host?9to?9peer?5reject?5wit@ @ 0x003E5990
// match: ??_C@_0CO@LEEFMDAF@Peer?5got?5reject?5from?5host?0?5conne@ @ 0x003E59D8
// match: ??_C@_0DG@GJJHGDBG@Host?5peer?5received?5host?9to?9peer?5@ @ 0x003E5A08
// match: ??_C@_0GD@JKPFGGLK@Peer?5received?5peer?9to?9peer?5conne@ @ 0x003E5A40
// match: ??_C@_0HH@EKOIBBPM@Peer?5received?5peer?9to?9peer?5conne@ @ 0x003E5AA8
// match: ??_C@_0DH@NLGJOHGJ@Host?5peer?5received?5peer?9to?9peer?5@ @ 0x003E5B20
// match: ??_C@_0EL@PBBELNIE@Peer?5received?5peer?9to?9peer?5accep@ @ 0x003E5B58
// match: ??_C@_0EL@PHNDHAOO@Peer?5received?5peer?9to?9peer?5accep@ @ 0x003E5BA8
// match: ??_C@_0GC@HIONHECO@Peer?5received?5peer?9to?9peer?5accep@ @ 0x003E5BF8
// match: ??_C@_0FG@NFKDHPGL@Peer?5received?5peer?9to?9peer?5accep@ @ 0x003E5C60
// match: ??_C@_0DC@KADCDAIE@Peer?5got?5accept?5from?5peer?0?5conne@ @ 0x003E5CB8
// match: ??_C@_0DG@CGMPFDCL@Host?5peer?5received?5peer?9to?9peer?5@ @ 0x003E5CEC
// match: ??_C@_0EL@PAFCPLHB@Peer?5received?5peer?9to?9peer?5rejec@ @ 0x003E5D28
// match: ??_C@_0EL@PGJFDGBL@Peer?5received?5peer?9to?9peer?5rejec@ @ 0x003E5D78
// match: ??_C@_0GC@DBAPJENL@Peer?5received?5peer?9to?9peer?5rejec@ @ 0x003E5DC8
// match: ??_C@_0FB@PEOMHGGA@Peer?5received?5peer?9to?9peer?5rejec@ @ 0x003E5E30
// match: ??_C@_0CO@FFCGCJNL@Peer?5got?5reject?5from?5peer?0?5conne@ @ 0x003E5E84
// match: ??_C@_0DG@HMOENNGC@Host?5peer?5received?5peer?9to?9peer?5@ @ 0x003E5EB4

extern void (*off_42CD14)(const RwChar *arg_0, ...);

// match: __ehhandler$??0cXboxLive@@QAE@XZ>1>8 @ 0x0041FBB8
// match: __ehhandler$??0cXboxLive@@QAE@XZ>1 @ 0x0041FBE0
// match: __ehhandler$??1cXboxLive@@QAE@XZ>1>8 @ 0x0041FBFC
// match: __ehhandler$??1cXboxLive@@QAE@XZ>1 @ 0x0041FC1C
// match: __ehhandler$?sub_1D8810@@YAPAUcXboxLive@@XZ>1>8 @ 0x0041FC38
// match: __ehhandler$?sub_1D8810@@YAPAUcXboxLive@@XZ>1 @ 0x0041FC40

// match: ?sub_1D8370@type_1D8370@@QBE_NPBU_XUID@@@Z @ 0x001D8370
bool type_1D8370::sub_1D8370(const XUID *arg_0) const
{
    return qwUserID == arg_0->qwUserID;
}
// The network system's constructor: its settings start with 16 players, no
// values and no name, and the system link host is called "SystemLinkHost".
// match: ??0cXboxLive@@QAE@XZ @ 0x001D83C0
// match: __ehhandler$??0cXboxLive@@QAE@XZ-0x46 @ 0x00303670
// match: __ehhandler$??0cXboxLive@@QAE@XZ @ 0x003036B6
cXboxLive::cXboxLive() : unk_770(0), unk_774(0), unk_2918(0), unk_291C(0), unk_2920(0), unk_2924(0),
                         unk_2928(0), unk_3DAC(0), unk_3DB0(0), unk_4038(0), unk_403C(0), unk_40C8(0xA1EEA1EE)
{
    memset(unk_000, 0, sizeof(unk_000));
    memset(&unk_700, 0, sizeof(unk_700));
    memset(unk_3DB4, 0, sizeof(unk_3DB4));
    memset(unk_3EB4, 0, sizeof(unk_3EB4));
    memset(unk_3F74, 0, sizeof(unk_3F74));
    memset(&unk_4040, 0, sizeof(unk_4040));
    memset(unk_4048, 0, sizeof(unk_4048));
    memset(unk_4088, 0, sizeof(unk_4088));
    unk_778.PrivateFilled = 0;
    unk_778.PrivateOpen = 0;
    unk_778.PublicFilled = 0;
    unk_778.PublicOpen = 16;
    unk_778.sub_1DCF90(0);
    unk_778.sub_1DCF40(0);
    unk_778.sub_1DCFE0(0);
    unk_778.sub_1DD030(16);
    unk_778.sub_1DD0E0(0);
    unk_778.sub_1DD0B0(0);
    unk_778.sub_1DD130(0);
    unk_778.SetName(L"");
    strncpy(unk_40CC, "SystemLinkHost", sizeof(unk_40CC));
    unk_40CC[15] = 0;
}
// match: ??1cXboxLive@@QAE@XZ @ 0x001D8780
// match: __ehhandler$??1cXboxLive@@QAE@XZ-0x38 @ 0x003036C0
// match: __ehhandler$??1cXboxLive@@QAE@XZ @ 0x003036F8
cXboxLive::~cXboxLive()
{
}
// The network system (unk_4FED00, built on first use).
// match: ?sub_1D8810@@YAPAUcXboxLive@@XZ @ 0x001D8810
// match: __ehhandler$?sub_1D8810@@YAPAUcXboxLive@@XZ-0xE @ 0x00303710
// match: __ehhandler$?sub_1D8810@@YAPAUcXboxLive@@XZ @ 0x0030371E
cXboxLive *sub_1D8810()
{
    static cXboxLive unk_4FED00;

    return &unk_4FED00;
}
// match: ?sub_1D8880@cXboxLive@@QAEHXZ @ 0x001D8880
BOOL cXboxLive::sub_1D8880()
{
    HRESULT var_4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (0)
        off_42CD14("Starting Xbox online library...");
    var_4 = XOnlineStartup(NULL);
    if (var_4 == S_OK)
    {
        unk_3DAC |= 8;
        if (0)
            off_42CD14("success\n");
    }
    else if (0)
        off_42CD14("failure\n");
    return var_4 == S_OK;
}
// match: ?sub_1D8900@cXboxLive@@QAEXXZ @ 0x001D8900
void cXboxLive::sub_1D8900()
{
    if (unk_291C)
    {
        unk_778.Delete();
        unk_291C = 3;
    }
    if (unk_2920 == 1)
        sub_1D9090();
    if (unk_3DAC & 4 && !unk_291C)
        XNetUnregisterKey(&unk_4040);
    unk_3DAC &= ~0x20;
    memset(&unk_4040, 0, sizeof(unk_4040));
    unk_3DAC &= ~4;
    unk_3DAC &= ~0x10;
    unk_41A4.unk_00 = 0;
    unk_292C.unk_00 = 0;
    unk_2932.unk_00 = 0;
    unk_4034.unk_00 = 0;
    if (unk_3DAC & 1)
    {
        unk_292E.unk_00 = 0;
        unk_2930.unk_00 = 0;
        unk_3DAC &= ~1;
    }
    memset(unk_3DB4, 0, sizeof(unk_3DB4));
    memset(unk_3EB4, 0, sizeof(unk_3EB4));
    memset(unk_3F74, 0, sizeof(unk_3F74));
    unk_4038 = 0;
    unk_403C = 0;
    memset(unk_4048, 0, sizeof(unk_4048));
    memset(unk_4088, 0, sizeof(unk_4088));
    unk_40DC.sub_1DBF20();
    memset(&unk_41A6.unk_00, 0, sizeof(unk_41A6.unk_00));
    memset(&unk_41A6.unk_24, 0, sizeof(unk_41A6.unk_24));
    memset(&unk_41A6.unk_2C, 0, sizeof(unk_41A6.unk_2C));
    unk_778.PrivateFilled = 0;
    unk_778.PrivateOpen = 0;
    unk_778.PublicFilled = 0;
    unk_778.PublicOpen = 16;
}
// Sends to peer arg_0 when it is connected: on failure the socket is
// reopened (sub_1DA230) or the peer dropped (sub_1DA1D0).
// match: ?sub_1D8B40@cXboxLive@@QAEXHHHHH@Z @ 0x001D8B40
void cXboxLive::sub_1D8B40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_292C.unk_00)
    {
    }
    if (unk_292C.test(arg_0) || (check(), unk_2932.test(arg_0)))
    {
        if (!unk_2934.sendMessage((const void *)arg_4, arg_8, arg_C, arg_10, &unk_3DB4[arg_0]))
        {
            if (!unk_2934.is_open())
                sub_1DA230();
            else
                sub_1DA1D0(arg_0);
        }
    }
    else if (0)
        off_42CD14("Trying to send message to non-connected player %d\n", arg_0);
}
// match: ?sub_1D8C00@cXboxLive@@QAEHXZ @ 0x001D8C00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1D8C00()
{
    ULONGLONG var_38;
    ULONGLONG var30;
    WCHAR var_28[16];
    HRESULT l4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_292C.unk_00)
    {
    }
    unk_778.sub_1DD080(unk_40C8);
    unk_3DAC &= ~0x20;
    if (unk_778.PublicOpen)
    {
        unk_778.PublicFilled++;
        unk_778.PublicOpen--;
        var30 = unk_778.sub_1DD110();
        unk_778.sub_1DD130(var30 + 1);
        // The host (peer 0) takes a public slot: the peer and the mask are
        // kept in locals of their own, with a compiled-out check before the
        // bit is set (docs/toolchain.md).
        {
            RwInt32 t3C = 0;
            type_1DDE20_mask *y40 = &unk_292E;

            if (!y40->unk_00)
            {
            }
            y40->unk_00 |= 1 << t3C;
        }
    }
    else if (unk_778.PrivateOpen)
    {
        unk_778.PrivateFilled++;
        unk_778.PrivateOpen--;
        var_38 = unk_778.sub_1DD110();
        unk_778.sub_1DD130(var_38 + 1);
        // The same for a private slot, with two checks.
        {
            RwInt32 var_44 = 0;
            type_1DDE20_mask *v48 = &unk_2930;

            if (!v48->unk_00)
            {
            }
            if (!v48->unk_00)
            {
            }
            v48->unk_00 |= 1 << var_44;
        }
    }
    else
    {
        if (0)
            off_42CD14("cXboxLive::createSession() - ERROR: attempting session creation with no open slots\n");
        unk_291C = 0;
        return 0;
    }
    swprintf(var_28, L"%S", sub_1DBD40()->szGamertag);
    unk_778.SetName(var_28);
    l4 = unk_778.Create();
    if (l4 == S_OK)
        unk_291C = 1;
    else
        unk_291C = 0;
    return l4 == S_OK;
}
// createSession over the system link: this machine's address (waited for), a
// new session key registered; 1 when it was created.
// match: ?sub_1D8E10@cXboxLive@@QAEHXZ @ 0x001D8E10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1D8E10()
{
    INT var_8;
    DWORD l4;

    unk_778.sub_1DD080(unk_40C8);
    unk_3DAC |= 0x20;
    do
    {
        l4 = XNetGetTitleXnAddr(&unk_41A6.unk_00);
        unk_291C = 1;
    } while (l4 == XNET_GET_XNADDR_PENDING);
    if (l4 == XNET_GET_XNADDR_NONE)
        return 0;
    var_8 = XNetCreateKey(&unk_41A6.unk_24, &unk_41A6.unk_2C);
    var_8 = XNetRegisterKey(&unk_41A6.unk_24, &unk_41A6.unk_2C);
    unk_291C = 2;
    if (0)
        off_42CD14("cXboxLive::createSession() - Created system-link session ok\n");
    return 1;
}
// match: ?sub_1D8EE0@cXboxLive@@QAEHPAUtype_4F8054_4C@@HH@Z @ 0x001D8EE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1D8EE0(struct type_4F8054_4C *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    ULONGLONG lv_10 = MAXLONGLONG;
    ULONGLONG var30 = MAXLONGLONG;
    ULONGLONG local_40 = MAXLONGLONG;
    ULONGLONG lcl_28 = MAXLONGLONG;
    ULONGLONG loc20 = MAXLONGLONG;
    ULONGLONG l18 = MAXLONGLONG;
    ULONGLONG var_38 = MAXLONGLONG;
    HRESULT bp_4;

    unk_3DAC &= ~0x20;
    if (arg_0->unk_00[0] != -1)
        lv_10 = (RwUInt32)arg_0->unk_00[0];
    if (arg_0->unk_10 != -1)
        var30 = (RwUInt32)arg_0->unk_10;
    if (arg_0->unk_00[2] != -1)
        local_40 = (RwUInt32)arg_0->unk_00[2];
    if (arg_0->unk_00[3] != -1)
        lcl_28 = (RwUInt32)arg_0->unk_00[3];
    if (arg_0->unk_00[1] != -1)
        loc20 = (RwUInt32)arg_0->unk_00[1];
    if (arg_0->unk_18 != -1)
        l18 = (RwUInt32)arg_0->unk_18;
    if (arg_0->unk_14 != -1)
        var_38 = (RwUInt32)arg_0->unk_14;
    bp_4 = unk_878.Query(lv_10, var30, local_40, loc20, unk_40C8, l18, var_38, lcl_28);
    if (bp_4 == S_OK)
    {
        unk_2920 = 1;
        unk_2924 = arg_4;
        unk_2928 = arg_8;
    }
    return bp_4 == S_OK;
}
// match: ?sub_1D9090@cXboxLive@@QAEHXZ @ 0x001D9090
RwInt32 cXboxLive::sub_1D9090()
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_292C.unk_00)
    {
    }
    if (is_system_link())
        unk_18C4.sub_1D7D60();
    else
        unk_878.Cancel();
    unk_2924 = 0;
    unk_2928 = 0;
    unk_2920 = 0;
    return 1;
}
// match: ?sub_1D9100@cXboxLive@@QAEHPAUtype_4F8054_4C@@HH@Z @ 0x001D9100
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1D9100(struct type_4F8054_4C *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    ULONGLONG lv_10 = (RwUInt32)arg_0->unk_00[0];
    ULONGLONG loc20 = (RwUInt32)arg_0->unk_10;
    ULONGLONG var_28 = (RwUInt32)arg_0->unk_00[2];
    ULONGLONG l18 = (RwUInt32)arg_0->unk_00[1];
    HRESULT bp_4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_292C.unk_00)
    {
    }
    unk_3DAC |= 0x20;
    bp_4 = unk_18C4.Query(&unk_3370, lv_10, loc20, var_28, l18, unk_40C8);
    if (bp_4 == S_OK)
    {
        unk_2920 = 1;
        unk_2924 = arg_4;
        unk_2928 = arg_8;
    }
    return bp_4 == S_OK;
}
// Whether the search goes on: over the system link or while the voice runs,
// until it has finished (unk_2920 2).
// match: ?sub_1D91E0@cXboxLive@@QAEHXZ @ 0x001D91E0
RwInt32 cXboxLive::sub_1D91E0()
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (is_system_link() || voice_running())
        return unk_2920 == 2;
    return 1;
}
// match: ?sub_1D9230@cXboxLive@@QAEHXZ @ 0x001D9230
RwInt32 cXboxLive::sub_1D9230()
{
    if (!unk_2918)
        return 0;
    if (unk_700.xuid.dwUserFlags & 0x10000)
        return 1;
    return 0;
}
// match: ?sub_1D9270@cXboxLive@@QAEPAUtype_1D9270_session@@PAI@Z @ 0x001D9270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1D9270_session *cXboxLive::sub_1D9270(RwUInt32 *arg_0)
{
    type_1D9270_session *var_8 = 0;
    type_1D8140_host *var_10;
    RwUInt32 local_C;
    RwUInt32 bp_4;

    if (!unk_2920)
    {
        *arg_0 = 0;
        return var_8;
    }
    // A compiled-out check (docs/toolchain.md).
    if (!unk_292C.unk_00)
    {
    }
    var_8 = (type_1D9270_session *)unk_2924;
    bp_4 = (RwUInt32)unk_2928 / sizeof(type_1D9270_session);
    if (is_system_link())
    {
        *arg_0 = unk_18C4.get_unk_F0C();
        if (*arg_0 > bp_4)
            *arg_0 = bp_4;
        for (local_C = 0; local_C < *arg_0; local_C++)
        {
            var_10 = &unk_18C4.unk_000[local_C];
            var_8[local_C].unk_00 = sizeof(type_1D9270_session);
            var_8[local_C].unk_29 = var_10->unk_92 + var_10->unk_8E;
            var_8[local_C].unk_28 = (RwUInt8)var_10->unk_10;
            var_8[local_C].unk_2A = var_10->unk_92 + var_10->unk_8A + var_10->unk_86 + var_10->unk_8E;
            sprintf(var_8[local_C].unk_10, "%S", var_10->unk_28);
            var_8[local_C].unk_34 = 1;
            var_8[local_C].unk_2B = (RwUInt8)var_10->unk_00;
            var_8[local_C].unk_2C = (RwUInt8)var_10->unk_08;
            var_8[local_C].unk_38 = var_10->unk_62;
            var_8[local_C].unk_5C = var_10->unk_4A;
            var_8[local_C].unk_64 = var_10->unk_52;
        }
    }
    else
    {
        *arg_0 = unk_878.Results.Size();
        if (*arg_0 > bp_4)
            *arg_0 = bp_4;
        for (local_C = 0; local_C < *arg_0; local_C++)
        {
            var_10 = &unk_878.Results.v[local_C];
            var_8[local_C].unk_00 = sizeof(type_1D9270_session);
            var_8[local_C].unk_29 = var_10->unk_92 + var_10->unk_8E;
            var_8[local_C].unk_28 = (RwUInt8)var_10->unk_10;
            var_8[local_C].unk_2A = var_10->unk_92 + var_10->unk_8A + var_10->unk_86 + var_10->unk_8E;
            sprintf(var_8[local_C].unk_10, "%S", var_10->unk_28);
            var_8[local_C].unk_34 = 1;
            var_8[local_C].unk_34 = 1;
            var_8[local_C].unk_2B = (RwUInt8)var_10->unk_00;
            var_8[local_C].unk_2C = (RwUInt8)var_10->unk_08;
            var_8[local_C].unk_38 = var_10->unk_62;
            var_8[local_C].unk_5C = var_10->unk_4A;
            var_8[local_C].unk_64 = var_10->unk_52;
        }
    }
    return var_8;
}
// The host's sockets (the second only over the system link, arg_0 clear):
// this machine becomes peer 0 with its user id; 0 when a socket failed.
// match: ?sub_1D9610@cXboxLive@@QAEH_N@Z @ 0x001D9610
RwInt32 cXboxLive::sub_1D9610(bool arg_0)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (!unk_2934.is_open() && !unk_2934.create(1))
        return 0;
    if (!arg_0 && !unk_3370.is_open() && !unk_3370.create(2))
        return 0;
    unk_3DAC |= 1;
    {
        RwInt32 bp_4 = 0;
        type_1DDE20_mask *y8 = &unk_292C;

        y8->unk_00 |= 1 << bp_4;
    }
    memcpy(&unk_3EB4[0], &unk_700.xuid, sizeof(XUID));
    unk_3DB0->get_unk_B0()->sub_1CFB80();
    return 1;
}
// match: ?sub_1D9700@cXboxLive@@QAEHPAUXNADDR@@PAUXNKID@@PAUXNKEY@@ABUtype_1CCA10@@H@Z @ 0x001D9700
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1D9700(XNADDR *arg_0, XNKID *arg_4, XNKEY *arg_8, const type_1CCA10 &arg_C, RwInt32 arg_10)
{
    bool var_19 = false;
    sockaddr_in l18;
    INT l4;

    if (is_system_link() || voice_running())
    {
        if (0)
            off_42CD14("cXboxLive::joinServer() : not logged in\n");
    }
    if (!unk_2934.is_open() && !unk_2934.create(1))
    {
        if (0)
            off_42CD14("cXboxLive::joinServer() : failed to create socket\n");
        return 0;
    }
    l4 = XNetRegisterKey(arg_4, arg_8);
    if (l4 != 0)
    {
        unk_2934.sub_1DC130();
        if (0)
            off_42CD14("cXboxLive::joinServer() : failed to register session key\n");
        return 0;
    }
    l4 = XNetXnAddrToInAddr(arg_0, arg_4, &l18.sin_addr);
    if (l4 != 0)
    {
        XNetUnregisterKey(arg_4);
        unk_2934.sub_1DC130();
        if (0)
            off_42CD14("cXboxLive::joinServer() : failed to convert network address to console context\n");
        return 0;
    }
    l18.sin_family = AF_INET;
    l18.sin_port = htons(1000);
    if (!sub_1DA270(&l18, 1, arg_10))
    {
        XNetUnregisterKey(arg_4);
        unk_2934.sub_1DC130();
        if (0)
            off_42CD14("cXboxLive::joinServer() : send join message failed\n");
        return 0;
    }
    unk_4040 = *arg_4;
    unk_3DAC |= 4;
    if (arg_10)
        unk_3DAC |= 0x10;
    unk_3DAC &= ~1;
    unk_3DAC |= 2;
    {
        RwInt32 var_20 = 0;
        type_1DDE20_mask *var_24 = &unk_2932;

        if (!var_24->unk_00)
        {
        }
        var_24->unk_00 |= 1 << var_20;
    }
    unk_4088[0] = arg_C;
    unk_4048[0] = arg_C;
    unk_3DB4[0] = l18;
    unk_4038 = 1;
    return 1;
}
// match: ?sub_1D9970@cXboxLive@@QAEIPBUsockaddr_in@@@Z @ 0x001D9970
RwUInt32 cXboxLive::sub_1D9970(const sockaddr_in *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        if ((unk_292C.test(var_4) || (check(), unk_2932.test(var_4))) &&
            unk_3DB4[var_4].sin_addr.s_addr == arg_0->sin_addr.s_addr && unk_3DB4[var_4].sin_port == arg_0->sin_port)
            break;
    }
    return var_4;
}
// match: ?sub_1D9A10@cXboxLive@@QAEXXZ @ 0x001D9A10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1D9A10()
{
    RwUInt32 var_81C = 16;
    RwUInt8 local_1020[0x800];
    RwInt32 local_820;
    RwUInt8 loc818[0x800];
    sockaddr_in l18;
    RwInt32 l4;

    if (unk_3370.is_open())
    {
        if (unk_3370.receiveMessage(local_1020, 0x800, 0, 0, &local_820, &l4, &l18))
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_3DAC)
            {
            }
            sub_1DB250(local_1020, local_820, &l18);
        }
        else if (!unk_3370.is_open())
            sub_1DA230();
    }
    if (unk_2934.is_open())
    {
        while (unk_2934.incomingMessageWaiting())
        {
            if (unk_2934.receiveMessage(local_1020, 0x800, loc818, 0x800, &local_820, &l4, &l18))
            {
                if (local_1020[0] == 0xFF)
                    sub_1DB180(local_1020, local_820, &l18);
                else
                {
                    var_81C = sub_1D9970(&l18);
                    if (var_81C < 16)
                        unk_3DB0->get_unk_AC()->sub_1D2CC0(var_81C, local_1020, local_820, l4 ? loc818 : 0, l4);
                }
            }
            else
            {
                if (!unk_2934.is_open())
                    sub_1DA230();
                break;
            }
        }
        if (!unk_2934.is_open())
            sub_1DA230();
    }
}
// match: ?sub_1D9C30@cXboxLive@@QAEHHPAUtype_1D9C30_peer@@ABUtype_1CCA10@@@Z @ 0x001D9C30
RwInt32 cXboxLive::sub_1D9C30(RwInt32 arg_0, type_1D9C30_peer *arg_4, const type_1CCA10 &arg_8)
{
    RwChar var_98[0x80];
    RwUInt8 var_15;
    sockaddr_in var_14;

    var_15 = unk_3DB0->get_unk_B0()->sub_1CFF90();
    sprintf(var_98, "%d.%d.%d.%d:%d", arg_4->unk_18[0], arg_4->unk_18[1], arg_4->unk_18[2], arg_4->unk_18[3],
            arg_4->unk_20);
    if (0)
        off_42CD14("Attempting connection to player %s at %s\n", arg_4->unk_00, var_98);
    var_14.sin_family = AF_INET;
    var_14.sin_port = htons(1000);
    var_14.sin_addr.S_un.S_un_b.s_b1 = arg_4->unk_18[3];
    var_14.sin_addr.S_un.S_un_b.s_b2 = arg_4->unk_18[2];
    var_14.sin_addr.S_un.S_un_b.s_b3 = arg_4->unk_18[1];
    var_14.sin_addr.S_un.S_un_b.s_b4 = arg_4->unk_18[0];
    if (!sub_1DA270(&var_14, 0, 0))
    {
        if (0)
            off_42CD14("cXboxLive::peerConnectToNewPlayer() - connection failed!\n");
        return 0;
    }
    unk_2932.include(arg_0);
    unk_4088[arg_0] = arg_8;
    unk_4048[arg_0] = arg_8;
    unk_3DB4[arg_0] = var_14;
    return 1;
}
// match: ?sub_1D9DD0@cXboxLive@@QAEXH@Z @ 0x001D9DD0
void cXboxLive::sub_1D9DD0(RwInt32 arg_0)
{
    ULONGLONG var_8;
    ULONGLONG var_10;

    if (0)
        off_42CD14("cXboxLive::disconnectPlayer %d\n", arg_0);
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (!unk_292C.test(arg_0))
    {
        if (0)
            off_42CD14("cXboxLive::disconnectPlayer - connection has already gone, bailing!\n");
        memset(&unk_3DB4[arg_0], 0, sizeof(unk_3DB4[arg_0]));
    }
    else
    {
        unk_292C.clear(arg_0);
        memset(&unk_3DB4[arg_0], 0, sizeof(unk_3DB4[arg_0]));
        memcpy(&unk_3F74[arg_0], &unk_3EB4[arg_0], sizeof(XUID));
        unk_4034.add(arg_0);
        if (unk_3DAC & 1)
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_292C.unk_00)
            {
            }
            if (unk_292E.test(arg_0))
            {
                unk_778.PublicFilled--;
                unk_778.PublicOpen++;
                var_8 = unk_778.sub_1DD110();
                unk_778.sub_1DD130(var_8 - 1);
                unk_292E.clear(arg_0);
            }
            else
            {
                unk_778.PrivateFilled--;
                unk_778.PrivateOpen++;
                var_10 = unk_778.sub_1DD110();
                unk_778.sub_1DD130(var_10 - 1);
                unk_2930.clear(arg_0);
            }
        }
    }
    unk_2932.clear(arg_0);
    memset(&unk_3EB4[arg_0], 0, sizeof(XUID));
    unk_41A4.clear(arg_0);
}
// match: ?sub_1DA070@cXboxLive@@QAEPBDXZ @ 0x001DA070
const RwChar *cXboxLive::sub_1DA070()
{
    static RwChar unk_42CD18[] = "2357111317192329";
    static RwInt32 dword_502EEC;
    INT var_4;

    if (!dword_502EEC)
    {
        var_4 = XNetRandom((BYTE *)unk_42CD18, 16);
        if (!var_4)
        {
            unk_42CD18[16] = 0;
            dword_502EEC = 1;
        }
    }
    return unk_42CD18;
}
// match: ?unk_42CD18@?1??sub_1DA070@cXboxLive@@QAEPBDXZ@4PADA @ 0x0042CD18
// match: ?sub_1DA0C0@cXboxLive@@QAEHPBEPAUXNADDR@@@Z @ 0x001DA0C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1DA0C0(const RwUInt8 *arg_0, XNADDR *arg_4)
{
    IN_ADDR var_8;
    INT l4;

    var_8.S_un.S_un_b.s_b1 = arg_0[3];
    var_8.S_un.S_un_b.s_b2 = arg_0[2];
    var_8.S_un.S_un_b.s_b3 = arg_0[1];
    var_8.S_un.S_un_b.s_b4 = arg_0[0];
    l4 = XNetInAddrToXnAddr(var_8, arg_4, NULL);
    return l4 == 0;
}
// match: ?sub_1DA110@cXboxLive@@QAEHPBUXNADDR@@PAE@Z @ 0x001DA110
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxLive::sub_1DA110(const XNADDR *arg_0, RwUInt8 *arg_4)
{
    IN_ADDR var_8;
    INT l4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    l4 = XNetXnAddrToInAddr(arg_0, &((cXboxLiveNetGame *)unk_3DB0)->unk_F8, &var_8);
    if (l4 == 0)
    {
        arg_4[3] = var_8.S_un.S_un_b.s_b1;
        arg_4[2] = var_8.S_un.S_un_b.s_b2;
        arg_4[1] = var_8.S_un.S_un_b.s_b3;
        arg_4[0] = var_8.S_un.S_un_b.s_b4;
        return 1;
    }
    return 0;
}
// match: ?sub_1DA170@cXboxLive@@QAEXXZ @ 0x001DA170
void cXboxLive::sub_1DA170()
{
    if (unk_778.Exists())
        unk_778.Update();
}
// match: ?sub_1DA1D0@cXboxLive@@QAEXI@Z @ 0x001DA1D0
void cXboxLive::sub_1DA1D0(RwUInt32 arg_0)
{
    if (arg_0 < 16)
    {
        if (0)
            off_42CD14("Player %d has been lost\n", arg_0);
        unk_3DB0->get_unk_B0()->sub_1CFC20(arg_0);
        sub_1D9DD0(arg_0);
    }
}
// match: ?sub_1DA230@cXboxLive@@QAEXXZ @ 0x001DA230
void cXboxLive::sub_1DA230()
{
    sub_1D8900();
    memset(&unk_700, 0, sizeof(unk_700));
    unk_3DB0->setError(7, 10);
}
// match: ?sub_1DA270@cXboxLive@@QAEHPBUsockaddr_in@@HH@Z @ 0x001DA270
RwInt32 cXboxLive::sub_1DA270(const sockaddr_in *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwUInt8 var_14[15];

    if (arg_4)
    {
        var_14[0] = 0xFF;
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        var_14[1] = (RwInt32)(arg_8 != 0);
        var_14[2] = 0x10;
        memcpy(&var_14[3], &unk_700, sizeof(XUID));
    }
    else
    {
        var_14[0] = 0xFF;
        var_14[1] = 4;
        var_14[2] = unk_3DB0->get_unk_B0()->sub_1CFF90();
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        memcpy(&var_14[3], &unk_700, sizeof(XUID));
    }
    if (unk_2934.sendMessage(var_14, 15, 0, 0, arg_0))
        return 1;
    if (!unk_2934.is_open())
        sub_1DA230();
    return 0;
}
// match: ?sub_1DA350@cXboxLive@@QAEHPBUsockaddr_in@@H@Z @ 0x001DA350
RwInt32 cXboxLive::sub_1DA350(const sockaddr_in *arg_0, RwInt32 arg_4)
{
    RwUInt8 var_14[15];

    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (unk_3DAC & 1)
    {
        var_14[0] = 0xFF;
        var_14[1] = 2;
        var_14[2] = arg_4;
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        memcpy(&var_14[3], &unk_700, sizeof(XUID));
    }
    else
    {
        var_14[0] = 0xFF;
        var_14[1] = 5;
        var_14[2] = unk_3DB0->get_unk_B0()->sub_1CFF90();
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        memcpy(&var_14[3], &unk_700, sizeof(XUID));
    }
    if (unk_2934.sendMessage(var_14, 15, 0, 0, arg_0))
        return 1;
    if (!unk_2934.is_open())
        sub_1DA230();
    return 0;
}
// match: ?sub_1DA430@cXboxLive@@QAEHPBUsockaddr_in@@H@Z @ 0x001DA430
RwInt32 cXboxLive::sub_1DA430(const sockaddr_in *arg_0, RwInt32 arg_4)
{
    RwUInt8 var_4[3];

    if (unk_3DAC & 1)
    {
        var_4[0] = 0xFF;
        var_4[1] = 3;
        var_4[2] = arg_4;
    }
    else
    {
        var_4[0] = 0xFF;
        var_4[1] = 6;
        var_4[2] = unk_3DB0->get_unk_B0()->sub_1CFF90();
    }
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (unk_2934.sendMessage(var_4, 3, 0, 0, arg_0))
        return 1;
    if (!unk_2934.is_open())
        sub_1DA230();
    return 0;
}
// match: ?sub_1DA4D0@cXboxLive@@QAEXABUtype_1CCA10@@@Z @ 0x001DA4D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DA4D0(const type_1CCA10 &arg_0)
{
    type_1CCA10 var_8;
    RwUInt32 l4;

    for (l4 = 0; l4 < 16; l4++)
    {
        if (unk_2932.test(l4))
        {
            var_8 = arg_0 - unk_4088[l4];
            if (var_8 > 10000)
            {
                if (0)
                    off_42CD14("cXboxLive: Connection attempt to player %d timed out\n", l4);
                if (l4 == 0)
                {
                    mask_remove(&unk_2932, 0);
                    unk_4038 = 3;
                    unk_403C = 3;
                }
                else
                    sub_1DA1D0(l4);
            }
            else
            {
                var_8 = arg_0 - unk_4048[l4];
                if (var_8 > 750)
                {
                    if (0)
                        off_42CD14("cXboxLive: No response to connection attempt to player %d, resending request\n",
                                   l4);
                    sub_1DA270(&unk_3DB4[l4], l4 == 0, l4 == 0 ? unk_3DAC & 0x10 : 0);
                    unk_4048[l4] = arg_0;
                }
            }
        }
    }
}
// match: ?sub_1DA680@cXboxLive@@QAEXU_XUID@@@Z @ 0x001DA680
void cXboxLive::sub_1DA680(XUID arg_0)
{
    XUID var_C = arg_0;

    unk_40DC.sub_1DBE30(&var_C);
    if (0)
        off_42CD14("Blocking player XUID %I64u\n", arg_0.qwUserID);
}
// match: ?sub_1DA6D0@cXboxLive@@QAEXPBEHPBUsockaddr_in@@@Z @ 0x001DA6D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DA6D0(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8)
{
    ULONGLONG var_28;
    ULONGLONG var_20;
    XUID m_18;
    RwUInt32 var_C;
    RwUInt8 bp_8[4];
    RwUInt32 bp_4;

    if (unk_3DAC & 1)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        var_C = sub_1D9970(arg_8);
        if (var_C < 16)
        {
            if (!sub_1DA350(arg_8, var_C))
                sub_1DA1D0(var_C);
        }
        else
        {
            memcpy(&m_18, arg_0 + 3, sizeof(XUID));
            if (unk_40DC.sub_1DBED0(&m_18))
            {
                if (0)
                    off_42CD14("Connection rejected - player blocked (XUID: %I64u)\n", m_18.qwUserID);
                sub_1DA430(arg_8, 2);
            }
            else if ((RwUInt32)unk_292C.sub_1D4A60() < unk_3DB0->get_desc()->unk_2B &&
                     (arg_0[1] == 1 && unk_778.PrivateOpen || unk_778.PublicOpen))
            {
                for (bp_4 = 1; bp_4 < 16; bp_4++)
                {
                    if (!unk_292C.test(bp_4))
                    {
                        if (0)
                            off_42CD14("KNET: accepting player %d\n", bp_4);
                        unk_292C.add(bp_4);
                        unk_3DB4[bp_4] = *arg_8;
                        if (arg_0[1] == 1 && unk_778.PrivateOpen)
                        {
                            unk_778.PrivateFilled++;
                            unk_778.PrivateOpen--;
                            var_20 = unk_778.sub_1DD110();
                            unk_778.sub_1DD130(var_20 + 1);
                            unk_2930.add(bp_4);
                        }
                        else
                        {
                            unk_778.PublicFilled++;
                            unk_778.PublicOpen--;
                            var_28 = unk_778.sub_1DD110();
                            unk_778.sub_1DD130(var_28 + 1);
                            unk_292E.include(bp_4);
                        }
                        bp_8[3] = arg_8->sin_addr.S_un.S_un_b.s_b1;
                        bp_8[2] = arg_8->sin_addr.S_un.S_un_b.s_b2;
                        bp_8[1] = arg_8->sin_addr.S_un.S_un_b.s_b3;
                        bp_8[0] = arg_8->sin_addr.S_un.S_un_b.s_b4;
                        memcpy(&unk_3EB4[bp_4], arg_0 + 3, sizeof(XUID));
                        unk_3DB0->get_unk_B0()->sub_1CFAC0(bp_4, bp_8, arg_8->sin_port);
                        if (!sub_1DA350(arg_8, bp_4))
                            sub_1DA1D0(bp_4);
                        return;
                    }
                }
            }
            else
            {
                if (0)
                    off_42CD14("Ran out of slots ---- connection Attempt rejected!\n");
                sub_1DA430(arg_8, 1);
            }
        }
    }
    else if (0)
        off_42CD14("Non-host peer received peer-to-host request, ignoring it.\n");
}
// match: ?sub_1DAA60@cXboxLive@@QAEXPBEHPBUsockaddr_in@@@Z @ 0x001DAA60
void cXboxLive::sub_1DAA60(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8)
{
    RwUInt32 var_4;

    if (unk_3DAC & 1)
    {
        if (0)
            off_42CD14("Host peer received host-to-peer accept, ignoring it.\n");
    }
    else
    {
        var_4 = sub_1D9970(arg_8);
        if (var_4 == 0)
        {
            if (unk_4038 == 1)
            {
                var_4 = arg_0[2];
                if (var_4 < 16)
                {
                    if (0)
                        off_42CD14("Peer got accept from host, connection successful\n");
                    {
                        RwInt32 bp_8 = 0;
                        type_1DDE20_mask *rC = &unk_2932;

                        if (!rC->unk_00)
                        {
                        }
                        rC->unk_00 &= ~(1 << bp_8);
                    }
                    {
                        RwInt32 u10 = 0;
                        type_1DDE20_mask *u14 = &unk_292C;

                        u14->unk_00 |= 1 << u10;
                    }
                    memcpy(&unk_3EB4[0], arg_0 + 3, sizeof(XUID));
                    unk_4038 = 2;
                }
                else if (0)
                    off_42CD14("Peer host-to-peer accept with invalid player index, ignoring it\n");
            }
            else if (0)
                off_42CD14("Peer received host-to-peer accept from host, but peer already in game, ignoring it.\n");
        }
        else if (0)
            off_42CD14("Peer received host-to-peer accept not from the host, ignoring it.\n");
    }
}
// match: ?sub_1DABA0@cXboxLive@@QAEXPBEHPBUsockaddr_in@@@Z @ 0x001DABA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DABA0(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8)
{
    RwInt32 var_8;
    RwUInt32 l4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (unk_3DAC & 1)
    {
        if (0)
            off_42CD14("Host peer received host-to-peer reject, ignoring it.\n");
    }
    else
    {
        l4 = sub_1D9970(arg_8);
        if (l4 == 0)
        {
            if (unk_4038 == 1)
            {
                var_8 = arg_0[2];
                if (arg_0[2] < 4)
                {
                    if (0)
                        off_42CD14("Peer got reject from host, connection failed\n");
                    {
                        RwInt32 var_C = 0;
                        type_1DDE20_mask *var_10 = &unk_2932;

                        if (!var_10->unk_00)
                        {
                        }
                        var_10->unk_00 &= ~(1 << var_C);
                    }
                    unk_4038 = 3;
                    unk_403C = var_8;
                }
                else if (0)
                    off_42CD14("Peer got host-to-peer reject with invalid reason code - ignoring it\n");
            }
            else if (0)
                off_42CD14("Peer received host-to-peer reject from host, but peer already in game, ignoring it.\n");
        }
        else if (0)
            off_42CD14("Peer received host-to-peer reject not from the host, ignoring it.\n");
    }
}
// match: ?sub_1DACB0@cXboxLive@@QAEXPBEHPBUsockaddr_in@@@Z @ 0x001DACB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DACB0(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    if (unk_3DAC & 1)
    {
        if (0)
            off_42CD14("Host peer received peer-to-peer request, ignoring it.\n");
    }
    else
    {
        l4 = arg_0[2];
        var_8 = sub_1D9970(arg_8);
        if (var_8 < 16)
        {
            if (l4 == var_8)
            {
                if (!sub_1DA350(arg_8, unk_3DB0->get_unk_B0()->sub_1CFF90()))
                    sub_1DA1D0(var_8);
            }
            else if (0)
                off_42CD14("Peer received peer-to-peer connection request from player already in game, but with "
                           "different index, ignoring request\n");
        }
        else if ((RwUInt32)unk_292C.sub_1D4A60() < unk_3DB0->get_desc()->unk_2B)
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_292C.unk_00)
            {
            }
            if (unk_292C.test(l4))
            {
                if (0)
                    off_42CD14("Peer received peer-to-peer connection request for a player index already in use, "
                               "ignoring request\n");
            }
            else
            {
                if (0)
                    off_42CD14("KNET: accepting player %d\n", l4);
                // A compiled-out check (docs/toolchain.md).
                if (!unk_3DAC)
                {
                }
                if (unk_41A4.test(l4))
                {
                    unk_41A4.clear(l4);
                    unk_3DB0->get_unk_B0()->sub_1CFFF0(l4, 1);
                }
                unk_292C.add(l4);
                unk_3DB4[l4] = *arg_8;
                memcpy(&unk_3EB4[l4], arg_0 + 3, sizeof(XUID));
                if (!sub_1DA350(arg_8, unk_3DB0->get_unk_B0()->sub_1CFF90()))
                    sub_1DA1D0(l4);
                return;
            }
        }
        else
        {
            if (0)
                off_42CD14("Ran out of slots ---- connection Attempt rejected!\n");
            sub_1DA430(arg_8, 1);
        }
    }
}
// match: ?sub_1DAF00@cXboxLive@@QAEXPBEHPBUsockaddr_in@@@Z @ 0x001DAF00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DAF00(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    if (unk_3DAC & 1)
    {
        if (0)
            off_42CD14("Host peer received peer-to-peer accept, ignoring it.\n");
    }
    else
    {
        l4 = arg_0[2];
        if (l4 < 16)
        {
            var_8 = sub_1D9970(arg_8);
            if (var_8 < 16)
            {
                if (var_8 == l4)
                {
                    if (unk_2932.test(var_8))
                    {
                        unk_2932.clear(var_8);
                        unk_292C.add(var_8);
                        memcpy(&unk_3EB4[var_8], arg_0 + 3, sizeof(XUID));
                        if (0)
                            off_42CD14("Peer got accept from peer, connection successful\n");
                    }
                    else if (0)
                        off_42CD14("Peer received peer-to-peer accept from peer, but peer already accepted, "
                                   "ignoring it.\n");
                }
                else if (0)
                    off_42CD14("Peer received peer-to-peer accept with player index that doesn't match the "
                               "address, ignoring it.\n");
            }
            else if (0)
                off_42CD14("Peer received peer-to-peer accept from unrecognised address, ignoring it.\n");
        }
        else if (0)
            off_42CD14("Peer received peer-to-peer accept with invalid player index, ignoring it.\n");
    }
}
// match: ?sub_1DB060@cXboxLive@@QAEXPBEHPBUsockaddr_in@@@Z @ 0x001DB060
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DB060(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (unk_3DAC & 1)
    {
        if (0)
            off_42CD14("Host peer received peer-to-peer reject, ignoring it.\n");
    }
    else
    {
        l4 = arg_0[2];
        if (l4 < 16)
        {
            var_8 = sub_1D9970(arg_8);
            if (var_8 < 16)
            {
                if (var_8 == l4)
                {
                    // A compiled-out check (docs/toolchain.md).
                    if (!unk_3DAC)
                    {
                    }
                    if (unk_2932.test(var_8))
                    {
                        unk_2932.clear(var_8);
                        if (0)
                            off_42CD14("Peer got reject from peer, connection failed\n");
                        sub_1DA1D0(var_8);
                    }
                    else if (0)
                        off_42CD14("Peer received peer-to-peer reject from peer, but peer not pending, ignoring it.\n");
                }
                else if (0)
                    off_42CD14("Peer received peer-to-peer reject with player index that doesn't match the "
                               "address, ignoring it.\n");
            }
            else if (0)
                off_42CD14("Peer received peer-to-peer reject from unrecognised address, ignoring it.\n");
        }
        else if (0)
            off_42CD14("Peer received peer-to-peer reject with invalid player index, ignoring it.\n");
    }
}
// A handshake message (0xFF first) from arg_8, by its type.
// match: ?sub_1DB180@cXboxLive@@QAEXPAEHPAUsockaddr_in@@@Z @ 0x001DB180
void cXboxLive::sub_1DB180(RwUInt8 *arg_0, RwInt32 arg_4, sockaddr_in *arg_8)
{
    switch (arg_0[1])
    {
    case 0:
    case 1:
        sub_1DA6D0(arg_0, arg_4, arg_8);
        break;
    case 2:
        sub_1DAA60(arg_0, arg_4, arg_8);
        break;
    case 3:
        sub_1DABA0(arg_0, arg_4, arg_8);
        break;
    case 4:
        sub_1DACB0(arg_0, arg_4, arg_8);
        break;
    case 5:
        sub_1DAF00(arg_0, arg_4, arg_8);
        break;
    case 6:
        sub_1DB060(arg_0, arg_4, arg_8);
        break;
    }
}
// A system link datagram from arg_8: a probe the host answers when its five
// attributes match the session's (0xFFFFFFFF matches anything; the third
// wants the session's at most), or an answer to this machine's query.
// match: ?sub_1DB250@cXboxLive@@QAEXPAEHPAUsockaddr_in@@@Z @ 0x001DB250
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DB250(RwUInt8 *arg_0, RwInt32 arg_4, sockaddr_in *arg_8)
{
    RwInt32 var_D4;
    type_1D8140_reply var_D0;
    bool local_C;
    bool var_B;
    bool vA;
    bool w9;
    type_1D7DD0_probe *bp_8;
    bool var_1;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    if (unk_3DAC & 1 && arg_0[1] == 0xFF)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        bp_8 = (type_1D7DD0_probe *)arg_0;
        // A compiled-out check (docs/toolchain.md).
        if (!unk_292C.unk_00)
        {
        }
        var_1 = bp_8->unk_10[0].info.integer.qwValue == 0xFFFFFFFF ||
                bp_8->unk_10[0].info.integer.qwValue == unk_778.sub_1DCF20();
        w9 = bp_8->unk_10[1].info.integer.qwValue == 0xFFFFFFFF ||
                bp_8->unk_10[1].info.integer.qwValue == unk_778.sub_1DCFC0();
        vA = bp_8->unk_10[2].info.integer.qwValue == 0xFFFFFFFF ||
                bp_8->unk_10[2].info.integer.qwValue >= unk_778.sub_1DD010();
        local_C = bp_8->unk_10[3].info.integer.qwValue == 0xFFFFFFFF ||
                bp_8->unk_10[3].info.integer.qwValue == unk_778.sub_1DCF70();
        var_B = bp_8->unk_10[4].info.integer.qwValue == 0xFFFFFFFF ||
                bp_8->unk_10[4].info.integer.qwValue == unk_778.sub_1DD060();
        if (var_1 && w9 && vA && local_C && var_B)
        {
            var_D0.unk_00[0] = 0xFF;
            var_D0.unk_00[1] = 0xFE;
            var_D0.unk_0A = unk_41A6.unk_24;
            var_D0.unk_12 = unk_41A6.unk_2C;
            var_D0.unk_22 = unk_41A6.unk_00;
            for (var_D4 = 0; var_D4 < 8; var_D4++)
                var_D0.unk_02[var_D4] = bp_8->unk_02[var_D4];
            var_D0.unk_48[0].dwAttributeID = 0;
            var_D0.unk_48[1].dwAttributeID = 0;
            var_D0.unk_48[2].dwAttributeID = 0;
            var_D0.unk_48[3].dwAttributeID = 0;
            var_D0.unk_48[4].dwAttributeID = 0;
            var_D0.unk_48[0].info.integer.qwValue = unk_778.sub_1DCF20();
            var_D0.unk_48[1].info.integer.qwValue = unk_778.sub_1DCFC0();
            var_D0.unk_48[2].info.integer.qwValue = unk_778.sub_1DD010();
            var_D0.unk_48[3].info.integer.qwValue = unk_778.sub_1DCF70();
            var_D0.unk_48[4].info.integer.qwValue = unk_778.sub_1DD060();
            swprintf(var_D0.unk_98, L"%S", unk_40CC);
            var_D0.unk_B8 = unk_4F7EB8.sub_1ACA70();
            unk_3370.broadcast((const RwChar *)&var_D0, sizeof(var_D0));
        }
    }
    else if (arg_0[1] == 0xFE)
        unk_18C4.sub_1D80F0(arg_0, arg_4, (RwInt32)arg_8);
}
// The session's public (arg_0) and private (arg_4) slots; a running session
// is told.
// match: ?sub_1DB750@cXboxLive@@QAEXHH@Z @ 0x001DB750
void cXboxLive::sub_1DB750(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_778.PublicOpen = arg_0 - unk_778.PublicFilled;
    unk_778.PrivateOpen = arg_4 - unk_778.PrivateFilled;
    unk_778.sub_1DD030((RwUInt32)(arg_0 + arg_4));
    if (unk_291C)
        unk_778.Update();
}
// The session's settings (the map and options), one attribute each; a
// running session is told.
// match: ?sub_1DB7C0@cXboxLive@@QAEXH@Z @ 0x001DB7C0
void cXboxLive::sub_1DB7C0(RwInt32 arg_0)
{
    unk_778.sub_1DCF40((RwUInt32)arg_0);
    if (unk_291C)
        unk_778.Update();
}
// match: ?sub_1DB800@cXboxLive@@QAEXH@Z @ 0x001DB800
void cXboxLive::sub_1DB800(RwInt32 arg_0)
{
    unk_778.sub_1DCFE0((RwUInt32)arg_0);
    if (unk_291C)
        unk_778.Update();
}
// match: ?sub_1DB840@cXboxLive@@QAEXH@Z @ 0x001DB840
void cXboxLive::sub_1DB840(RwInt32 arg_0)
{
    unk_778.sub_1DD0E0((RwUInt32)arg_0);
    if (unk_291C)
        unk_778.Update();
}
// match: ?sub_1DB880@cXboxLive@@QAEXH@Z @ 0x001DB880
void cXboxLive::sub_1DB880(RwInt32 arg_0)
{
    unk_778.sub_1DD0B0((RwUInt32)arg_0);
    if (unk_291C)
        unk_778.Update();
}
// match: ?sub_1DB8C0@cXboxLive@@QAEXH@Z @ 0x001DB8C0
void cXboxLive::sub_1DB8C0(RwInt32 arg_0)
{
    unk_778.sub_1DCF90((RwUInt32)arg_0);
    if (unk_291C)
        unk_778.Update();
}
// match: ?sub_1DB900@cXboxLive@@QAEXH@Z @ 0x001DB900
void cXboxLive::sub_1DB900(RwInt32 arg_0)
{
    unk_40C8 = arg_0;
}
// The system link host's name.
// match: ?sub_1DB920@cXboxLive@@QAEXPBD@Z @ 0x001DB920
void cXboxLive::sub_1DB920(const RwChar *arg_0)
{
    strncpy(unk_40CC, arg_0, sizeof(unk_40CC));
    unk_40CC[15] = 0;
}
// match: ?sub_1DB950@cXboxLive@@QAEXXZ @ 0x001DB950
void cXboxLive::sub_1DB950()
{
    unk_2918 = 0;
}
// match: ?sub_1DB970@cXboxLive@@QAEXXZ @ 0x001DB970
void cXboxLive::sub_1DB970()
{
    unk_2918 = 1;
}
// match: ?sub_1DB990@cXboxLive@@QAEXXZ @ 0x001DB990
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DB990()
{
    RwInt32 var_8;
    XONLINE_USER *l4;

    unk_2918 = 4;
    l4 = XOnlineGetLogonUsers();
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        if (l4[var_8].szGamertag[0])
        {
            memcpy(&unk_700, &l4[var_8], sizeof(XONLINE_USER));
            break;
        }
    }
}
// match: ?sub_1DBA00@cXboxLive@@QAEXXZ @ 0x001DBA00
void cXboxLive::sub_1DBA00()
{
    unk_2918 = 2;
}
// match: ?sub_1DBA20@cXboxLive@@QAEXXZ @ 0x001DBA20
void cXboxLive::sub_1DBA20()
{
    unk_2918 = 3;
}
// Marks peer arg_0 (as the players who left are, unk_41A4).
// match: ?sub_1DBA40@cXboxLive@@QAEXHH@Z @ 0x001DBA40
void cXboxLive::sub_1DBA40(RwInt32 arg_0, RwInt32 arg_4)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    unk_41A4.add(arg_0);
}
// match: ?sub_1DBA80@cXboxLive@@QAEXABUtype_1CCA10@@@Z @ 0x001DBA80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cXboxLive::sub_1DBA80(const type_1CCA10 &arg_0)
{
    RwInt32 var_C;
    HRESULT bp_8;
    XONLINE_USER *bp_4;

    sub_1D9A10();
    // A compiled-out check (docs/toolchain.md).
    if (!unk_3DAC)
    {
    }
    sub_1DA4D0(arg_0);
    if (unk_3DAC & 8)
    {
        if (unk_774 && unk_2918)
        {
            bp_8 = XOnlineTaskContinue(unk_774);
            if (unk_2918 == 1)
            {
                if (bp_8 != XONLINETASK_S_RUNNING)
                {
                    bp_8 = XOnlineLogonTaskGetResults(unk_774);
                    if (bp_8 == XONLINE_S_LOGON_CONNECTION_ESTABLISHED)
                    {
                        unk_2918 = 4;
                        bp_4 = XOnlineGetLogonUsers();
                        // A compiled-out check (docs/toolchain.md).
                        if (!unk_3DAC)
                        {
                        }
                        for (var_C = 0; var_C < 4; var_C++)
                        {
                            if (bp_4[var_C].szGamertag[0])
                            {
                                memcpy(&unk_700, &bp_4[var_C], sizeof(XONLINE_USER));
                                break;
                            }
                        }
                    }
                    else
                        unk_2918 = 0;
                }
            }
            else if (bp_8 != XONLINE_S_LOGON_CONNECTION_ESTABLISHED)
                unk_2918 = 0;
        }
        if (unk_291C)
        {
            bp_8 = unk_778.Process();
            switch (unk_291C)
            {
            case 1:
                switch (bp_8)
                {
                case XONLINETASK_S_RUNNING:
                    break;
                case XONLINETASK_S_SUCCESS:
                    unk_4040 = unk_778.SessionID;
                    unk_3DAC |= 4;
                    unk_291C = 2;
                    break;
                default:
                    unk_291C = 0;
                    unk_4038 = 3;
                    unk_403C = 3;
                    break;
                }
                break;
            case 3:
                if (bp_8 != XONLINETASK_S_RUNNING)
                {
                    // A compiled-out check (docs/toolchain.md).
                    if (!unk_3DAC)
                    {
                    }
                    unk_291C = 0;
                    memset(&unk_4040, 0, sizeof(unk_4040));
                    unk_3DAC &= ~4;
                }
                break;
            }
        }
        // A compiled-out check (docs/toolchain.md).
        if (!unk_3DAC)
        {
        }
        if (unk_2920 == 1)
        {
            if (is_system_link())
            {
                bp_8 = unk_18C4.sub_1D8060();
                if (bp_8 != XONLINETASK_S_RUNNING)
                {
                    // A compiled-out check (docs/toolchain.md).
                    if (!unk_3DAC)
                    {
                    }
                    unk_2920 = 2;
                }
            }
            else
            {
                bp_8 = unk_878.Process();
                switch (bp_8)
                {
                case XONLINETASK_S_RUNNING:
                    break;
                case XONLINETASK_S_SUCCESS:
                    unk_2920 = 2;
                    break;
                default:
                    unk_2920 = 0;
                    break;
                }
            }
        }
    }
}
// match: ?sub_1DBD40@cXboxLive@@QAEPAU_XONLINE_USER@@XZ @ 0x001DBD40
XONLINE_USER *cXboxLive::sub_1DBD40()
{
    return &unk_700;
}
// Peer arg_0's user id into arg_4: a connected peer's, or (arg_8 clear) a
// departed one's; 0 when there is none.
// match: ?sub_1DBD60@cXboxLive@@QAEHHPAU_XUID@@H@Z @ 0x001DBD60
RwInt32 cXboxLive::sub_1DBD60(RwInt32 arg_0, XUID *arg_4, RwInt32 arg_8)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_292C.unk_00)
    {
    }
    if (unk_292C.test(arg_0))
    {
        *arg_4 = unk_3EB4[arg_0];
        return 1;
    }
    if (!arg_8 && (check(), unk_4034.test(arg_0)))
    {
        *arg_4 = unk_3F74[arg_0];
        return 1;
    }
    return 0;
}
// match: ??0type_1DBE00@@QAE@XZ @ 0x001DBE00
type_1DBE00::type_1DBE00()
{
    unk_C0 = 0;
    unk_C4 = 0;
}
// match: ?sub_1DBE30@type_1DBE00@@QAEXPBU_XUID@@@Z @ 0x001DBE30
void type_1DBE00::sub_1DBE30(const XUID *arg_0)
{
    if (!sub_1DBED0(arg_0))
    {
        (XUID &)unk_00[unk_C4] = *arg_0;
        unk_C4++;
        if (unk_C4 >= 16)
            unk_C4 = 0;
        if (unk_C0 < 16)
            unk_C0++;
    }
}
// match: ?sub_1DBED0@type_1DBE00@@QAE_NPBU_XUID@@@Z @ 0x001DBED0
bool type_1DBE00::sub_1DBED0(const XUID *arg_0)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < unk_C0; var_4++)
    {
        if (unk_00[var_4].sub_1D8370(arg_0))
            return true;
    }
    return false;
}
// match: ?sub_1DBF20@type_1DBE00@@QAEXXZ @ 0x001DBF20
void type_1DBE00::sub_1DBF20()
{
    unk_C0 = 0;
    unk_C4 = 0;
}

// Not in the image: a stand-in for a function the original object ended with, which nothing
// called, so the link's /OPT:REF dropped it. It was the first to use "Unknown Error" (the
// image keeps that text, 0x3E5EEC, after this object's others and before unit_1DBF50's,
// though only the voice's peer table in unit_1DDBE0 points at it). Its body is unknown: this
// one only returns the text.
const RwChar *dropped_3E5EEC()
{
    return "Unknown Error";
}
