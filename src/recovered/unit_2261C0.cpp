/*
 * The late service (game/liveservice.h): the Live engine's host, which starts
 * the engine with the UI and audio plugins, runs it each frame, starts its
 * features, follows the mute list and joins the sessions friends invite to;
 * the players list's items are kept in a std::vector, whose instances follow.
 */
#include <vector>
#include "game/liveservice.h"
#include "game/uixfont.h"
#include "game/startup.h"
#include "game/savestate.h"
#include "game/waitscreen.h"
#include "game/uiglue.h"
#include "game/data.h"
#include "game/fileio.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EAD50
extern const RwReal flt_3EAD50 = 0.01f;
// 0x003EAD54
extern const RwReal flt_3EAD54 = 0.01f;
// 0x003EAD58
extern const RwReal flt_3EAD58 = 16.666666f;
// 0x0042D2F8: the UIX wave and sound banks (their literals come after the skin's, as
// globals defined before it).
const RwChar *dword_42D2F8 = "d:\\Media\\UIXDefault.xwb";
// 0x0042D2FC
const RwChar *dword_42D2FC = "d:\\Media\\UIXDefault.xsb";
// 0x0042D300
const RwChar *pSkinFileName = "d:\\Media\\MPCoDLayout.uix";
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_22A630 unk_506318;
type_22AE00 unk_5064DC;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BJ@CIFKNJDH@d?3?2Media?2MPCoDLayout?4uix?$AA@ @ 0x003EAD04
// match: ??_C@_0BI@LGBHJLEJ@d?3?2Media?2UIXDefault?4xsb?$AA@ @ 0x003EAD20
// match: ??_C@_0BI@LBBODDJF@d?3?2Media?2UIXDefault?4xwb?$AA@ @ 0x003EAD38
// match: ?flt_3EAD50@@3MB @ 0x003EAD50
// match: ?flt_3EAD54@@3MB @ 0x003EAD54
// match: ?flt_3EAD58@@3MB @ 0x003EAD58
// match: ??_C@_08NGHCMOCB@codfontS?$AA@ @ 0x003EAD5C
// match: ??_C@_08CJBOKCDN@codfontN?$AA@ @ 0x003EAD68
// match: ??_C@_08BLCIMALP@codfontL?$AA@ @ 0x003EAD74
// match: ??_C@_0CL@LMAAPEEC@cUIXInit?3?5Creating?5the?5UIX?5Live?5@ @ 0x003EAD80
// match: ??_C@_0BH@ENIJBEKI@JOIN_GAME_CROSS_TITLE?6?$AA@ @ 0x003EADAC
// match: ??_C@_0BL@MMGFLDEI@UIX_EXIT_LOGON_SUCCESSFUL?6?$AA@ @ 0x003EADC4
// match: ??_C@_0DJ@NENICJOB@UIX_EXIT_FRIENDS_JOIN_GAME?5?$DN?$DO?5UI@ @ 0x003EADE0
// match: ??_C@_0BH@LMBPEAP@UIX_EXIT_LOGON_FAILED?6?$AA@ @ 0x003EAE1C
// match: ??_C@_0BO@LOGJMGGO@Player?5muting?5update?5stopped?6?$AA@ @ 0x003EAE34
// match: ??_C@_0BO@FGBOLKPI@Player?5muting?5update?5started?6?$AA@ @ 0x003EAE54
// match: ??_C@_0CL@GKDNHJAH@UIX_PROPERTY_DISPLAY_CONNECTION_@ @ 0x003EAE74
// match: ??_C@_0L@MGJLMDOE@JOIN_GAME?6?$AA@ @ 0x003EAEA0
// match: __ehhandler$?sub_226360@type_5051E8@@QAEHXZ>1>8 @ 0x00425F78
// match: __ehhandler$?sub_226360@type_5051E8@@QAEHXZ>1 @ 0x00425F80
// match: __ehhandler$?sub_2266D0@type_5051E8@@QAEXABUtype_1CCA10@@@Z>1>8 @ 0x00425F9C
// match: __ehhandler$?sub_2266D0@type_5051E8@@QAEXABUtype_1CCA10@@@Z>1 @ 0x00425FA4
// match: __ehhandler$?sub_227560@@YAPAUtype_5051E8@@XZ>1>8 @ 0x00425FC0
// match: __ehhandler$?sub_227560@@YAPAUtype_5051E8@@XZ>1 @ 0x00425FC8
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z>1>8 @ 0x00425FE4
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z>1>16>16 @ 0x00426004
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z>1>16>36 @ 0x00426014
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z>1>16 @ 0x00426024
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z>1 @ 0x0042604C
// match: __ehhandler$?_Xlen@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IBEXXZ>1>8 @ 0x00426068
// match: __ehhandler$?_Xlen@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IBEXXZ>1 @ 0x00426070
// match: .CRT$XCU+0 @ 0x00427370
// match: .CRT$XCU+4 @ 0x00427374
// match: ?dword_42D2F8@@3PBDB @ 0x0042D2F8
// match: ?dword_42D2FC@@3PBDB @ 0x0042D2FC
// match: ?pSkinFileName@@3PBDB @ 0x0042D300

// match: _$E2 @ 0x0030DB40
// match: _$E3 @ 0x0030F070
// match: _$E5 @ 0x0030DB60
// match: _$E6 @ 0x0030F080
// match: _$E9 @ 0x0030F090

template class std::vector<type_22AF50 *>;

// match: ??0type_5051E8@@QAE@XZ @ 0x002261C0
type_5051E8::type_5051E8()
    : unk_00(0), unk_78(0), unk_7C(0), unk_80(0), unk_84(0), unk_88(false),
      unk_8C(0), unk_90(0), unk_94(0), unk_A0(1), unk_A4(0), unk_144(0),
      unk_158(0), unk_15C(false), unk_15D(false), unk_160(0), unk_164(0),
      unk_168(0), unk_1118(0), unk_111C(0), unk_1120(0), unk_1124(0)
{
}

// match: ??1type_5051E8@@QAE@XZ @ 0x00226340

// match: ?sub_226360@type_5051E8@@QAEHXZ @ 0x00226360
// match: __ehhandler$?sub_226360@type_5051E8@@QAEHXZ-0xE @ 0x00308F60
// match: __ehhandler$?sub_226360@type_5051E8@@QAEHXZ @ 0x00308F6E
RwInt32 type_5051E8::sub_226360()
{
    XONLINE_ACCEPTED_GAMEINVITE uBC;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;

    lv_10 = 0;

    unk_94 = 0;
    unk_00 = 0;
    unk_A4 = 0;
    unk_144 = 0;
    unk_7C = D3DDevice_GetBackBuffer2(0);
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("cUIXInit: Creating the UIX Live engine...\n");
    m_18 = UIXCreateLiveEngine(pSkinFileName, sub_19BEA0(), &unk_84);
    if (XOnlineFriendsGetAcceptedGameInvite(&uBC) == S_OK)
    {
        *(XONLINE_ACCEPTED_GAMEINVITE *)dword_4F45F8->unk_398 = uBC;
        dword_4F45F8->unk_3C = 1;
    }
    if (m_18 == S_OK)
    {
        type_225220 *fp_C4 = new type_225220("codfontS", "codfontN", "codfontL");
        ITitleUIPlugin *frm_C0 = &unk_506318;

        unk_506318.sub_22A6C0(fp_C4);
        unk_84->SetUIPlugin(frm_C0);
        unk_84->SetAudioPlugin(&unk_5064DC);
        unk_84->EnableFeature(UIX_LOGON_FEATURE);
        unk_84->EnableFeature(UIX_FRIENDS_FEATURE);
        unk_84->EnableFeature(UIX_PLAYERS_FEATURE);
        unk_84->SetProperty(UIX_PROPERTY_DISPLAY_NOTIFICATIONS, 1);
        unk_84->SetProperty(UIX_PROPERTY_ALLOW_GAME_INVITES, 1);
        unk_84->SetProperty(UIX_PROPERTY_HOST_NO_MIGRATION, unk_78);
        unk_84->UseVoiceMail(UIX_VOICE_MAIL);
        lv_10 = 1;
    }
    for (ebp_14 = 0; ebp_14 < 8; ebp_14++)
        unk_98.ab[ebp_14] = 0xFF;
    unk_1114.unk_00 = 0;
    unk_1116.unk_00 = 0;
    return lv_10;
}

// match: ?sub_2266D0@type_5051E8@@QAEXABUtype_1CCA10@@@Z @ 0x002266D0
// match: __ehhandler$?sub_2266D0@type_5051E8@@QAEXABUtype_1CCA10@@@Z-0xB @ 0x00308F80
// match: __ehhandler$?sub_2266D0@type_5051E8@@QAEXABUtype_1CCA10@@@Z @ 0x00308F8B
void type_5051E8::sub_2266D0(const type_1CCA10 &arg_0)
{
    RwInt32 ebp_14;
    RwUInt32 lv_10;

    if (!unk_1114.empty())
    {
        for (lv_10 = 0; lv_10 < 0x10; lv_10++)
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_1114.unk_00)
            {
            }
            if (unk_1114.test(lv_10))
            {
                ILivePlayersList *l1C;

                unk_84->GetFeatureInterface(UIX_PLAYERS_FEATURE, 0, (VOID **)&l1C);
                type_1DDE20_mask m_18 = sub_1C48A0();

                // A compiled-out check (docs/toolchain.md).
                if (!m_18.unk_00)
                {
                }
                if (m_18.test(lv_10))
                {
                    XUID slot_28;

                    if (sub_1D8810()->sub_1DBD60(lv_10, &slot_28, 1))
                    {
                        type_22AF50 *stk_2C = new type_22AF50(lv_10, slot_28, sub_1C4630(lv_10), -1);

                        unk_148.push_back(stk_2C);
                        l1C->RegisterPlayer(stk_2C);
                        unk_1114.discard(lv_10);
                        unk_1116.include(lv_10);
                    }
                }
            }
        }
    }
    if (dword_42926C)
        unk_84->SetInput(get_dword_4B9E50(), (const XINPUT_STATE *)sub_19E4B0());
    else
        unk_84->ClearInput();
    unk_84->DoWork(&unk_80);
    if (!dword_42926C)
        unk_84->ClearInput();
    if ((unk_80 & UIX_DOWORK_PROCESSING_INPUT) && !dword_42926C)
        unk_80 &= ~UIX_DOWORK_PROCESSING_INPUT;
    if ((unk_80 & UIX_DOWORK_PROCESSING_INPUT) && !dword_42926C)
        unk_80 &= ~UIX_DOWORK_PROCESSING_INPUT;
    if (unk_80 & UIX_DOWORK_NEED_TO_REBOOT)
        unk_84->Reboot(0);
    if (unk_80 & UIX_DOWORK_FEATURE_EXIT)
    {
        UIX_EXIT_INFO stk_40;
        RwInt32 frm_30;

        sub_228090(1);
        unk_84->GetExitInfo(&stk_40);
        frm_30 = unk_90;
        unk_90 = 0;
        switch (stk_40.ExitCode)
        {
        case UIX_EXIT_LOGON_FAILED:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("UIX_EXIT_LOGON_FAILED\n");
            sub_228120(&stk_40, frm_30);
            break;
        case UIX_EXIT_FRIENDS_JOIN_GAME:
            if (sub_2281F0(&stk_40, frm_30) == 1)
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("UIX_EXIT_FRIENDS_JOIN_GAME => UIX_EXIT_LOGON_SUCCESSFUL\n");
                sub_228240(&stk_40, frm_30);
            }
            break;
        case UIX_EXIT_LOGON_SUCCESSFUL:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("UIX_EXIT_LOGON_SUCCESSFUL\n");
            sub_228240(&stk_40, frm_30);
            break;
        case UIX_EXIT_LOGON_USER_EXIT:
            sub_1D8810()->sub_1DB950();
            break;
        case UIX_EXIT_FRIENDS_JOIN_GAME_CROSS_TITLE:
        {
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("JOIN_GAME_CROSS_TITLE\n");
            DWORD v44 = (DWORD)stk_40.pExitData;
            break;
        }
        }
    }
    if (unk_111C && !(unk_80 & UIX_DOWORK_PROCESSING_INPUT))
    {
        unk_111C = 0;
        sub_226DA0(0);
    }
    if (sub_1D8810()->get_unk_2918() == 4)
    {
        DWORD slot_58 = unk_94;

        sub_227BA0();
        sub_227C00();
        sub_227C50();
        sub_227CA0();
        bool fp_51;
        XNKID ebp_50 = sub_1D8810()->get_unk_4040();

        fp_51 = true;

        for (lv_10 = 0; lv_10 < 8; lv_10++)
        {
            if (unk_98.ab[lv_10] != ebp_50.ab[lv_10])
                fp_51 = false;
        }
        if (slot_58 != unk_94 || !fp_51)
            sub_227AC0(sub_227900(0));
    }
    ebp_14 = sub_1D8810()->get_unk_2918();
    if (unk_158 != ebp_14)
    {
        unk_158 = ebp_14;
        switch (unk_158)
        {
        case 0:
            sub_226D80();
            break;
        case 4:
            sub_226D60();
            break;
        }
    }
    if (unk_4F7EB8.sub_1AF670() && unk_15C)
        sub_226DD0(arg_0);
}

// match: ?sub_226D60@type_5051E8@@QAEXXZ @ 0x00226D60
void type_5051E8::sub_226D60()
{
    sub_2279D0(true);
}

// match: ?sub_226D80@type_5051E8@@QAEXXZ @ 0x00226D80
void type_5051E8::sub_226D80()
{
    sub_2279D0(false);
    unk_00 = 0;
}

// match: ?sub_226DA0@@YAXH@Z @ 0x00226DA0
void sub_226DA0(RwInt32 arg_0)
{
    if (!((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480())
        dword_504568 = 1;
    else
    {
        sub_1C44A0();
        dword_5044DC = 0;
    }
}

// match: ?sub_226DD0@type_5051E8@@QAEXABUtype_1CCA10@@@Z @ 0x00226DD0
void type_5051E8::sub_226DD0(const type_1CCA10 &arg_0)
{
    RwInt32 var_4;

    switch (XOnlineTaskContinue(unk_160))
    {
    }
    // A compiled-out check (docs/toolchain.md).
    if (!unk_160)
    {
    }
    var_4 = 0;

    if (has_dword_4B9E50())
        var_4 = dword_4B9E50;
    if (unk_164 && !unk_16C && sub_1C4C00())
    {
        unk_164 = 0;
        if (XOnlineMutelistGet(var_4, 0xFA, 0, &unk_16C, unk_174, &unk_170))
            unk_16C = 0;
    }
    else if (!sub_1C4C00() && !unk_164)
        unk_164 = 1;
    if (unk_16C)
    {
        switch (XOnlineTaskContinue(unk_16C))
        {
        case XONLINETASK_S_SUCCESS:
            XOnlineTaskClose(unk_16C);
            unk_16C = 0;
            break;
        }
    }
    if (!unk_16C)
    {
        unk_168++;
        if (unk_168 >= 0x10)
            unk_168 = 0;
        // A compiled-out check of a dword (docs/toolchain.md): the mask's
        // copy is one load on. Which member it read is not in the code.
        if (!unk_16C)
        {
        }
        type_1DDE20_mask ebp_14 = sub_1D8810()->get_unk_292C();
        XUID lv_10;

        ebp_14.discard(unk_4F7EB8.get_unk_19C()->get_unk_B0()->sub_1CFF90());
        // Another (the test is one load on).
        if (!unk_168)
        {
        }
        if (ebp_14.test(unk_168))
        {
            if (sub_1D8810()->sub_1DBD60(unk_168, &lv_10, 1) && lv_10.qwUserID)
            {
                RwUInt32 var_18;

                for (var_18 = 0; var_18 < unk_170; var_18++)
                {
                    if (unk_174[var_18].xuid.qwUserID == lv_10.qwUserID)
                    {
                        get_dword_4F8180()->unk_3060.sub_1C7C70(unk_168, true);
                        break;
                    }
                }
                if (var_18 == unk_170)
                    get_dword_4F8180()->unk_3060.sub_1C7C70(unk_168, false);
            }
        }
    }
}

// match: ?sub_227070@type_5051E8@@QAEXXZ @ 0x00227070
void type_5051E8::sub_227070()
{
    unk_1120 = 0;
    if ((unk_80 & UIX_DOWORK_NEED_TO_RENDER) && unk_7C && dword_42926C)
    {
        _rwXbFlushCacheBuffer();
        unk_84->Render(unk_7C);
        _rwXbFlushCacheBuffer();
    }
}

// match: ?sub_2270E0@type_5051E8@@QAEXH@Z @ 0x002270E0
void type_5051E8::sub_2270E0(RwInt32 arg_0)
{
    UIX_FRIENDS_PARAMS fp_98;
    UIX_LOGON_PARAMS lv_80;
    bool bp_21;
    HRESULT t20;
    UIX_PLAYERS_PARAMS l1C;

    bp_21 = false;

    switch (arg_0)
    {
    case 1:
    case 4:
    case 5:
    {
        memset(&lv_80, 0, sizeof(lv_80));
        lv_80.LogonServiceIDs[0] = 6;
        lv_80.LogonServiceIDs[1] = 8;
        lv_80.LogonUserCount = 1;
        if (dword_4F45F8->unk_3C == 1)
        {
            lv_80.LogonType = UIX_LOGON_TYPE_RETRIEVED_GAME_INVITE;
            lv_80.pGameInvite = (XONLINE_ACCEPTED_GAMEINVITE *)dword_4F45F8->unk_398;
        }
        else if (dword_4F45F8->unk_40)
        {
            dword_4F45F8->unk_40 = 0;
            lv_80.LogonType = UIX_LOGON_TYPE_RETRIEVED_STATE;
            lv_80.pLogonState = (XONLINE_LOGON_STATE *)dword_4F45F8->unk_48A;
            RwInt32 t9C = dword_4B9E50;

            if (t9C)
            {
                XONLINE_USER *varA4;
                XONLINE_USER *locA0;

                locA0 = (XONLINE_USER *)(dword_4F45F8->unk_48A + 4);
                varA4 = &locA0[t9C];

                if (locA0->szGamertag[0] && !varA4->szGamertag[0])
                {
                    XONLINE_USER *varA8 = &locA0[t9C];

                    *varA8 = *locA0;
                    memset(locA0, 0, sizeof(XONLINE_USER));
                }
            }
        }
        else
        {
            dword_4F45F8->unk_3C = 0;
            bp_21 = true;
        }
        if (bp_21)
            lv_80.LogonType = (UIX_LOGON_TYPE)(arg_0 == 4);
        if (lv_80.LogonType == UIX_LOGON_TYPE_SILENT)
            sub_228090(0);
        lv_80.StructSize = sizeof(lv_80);
        t20 = unk_84->StartFeature(UIX_LOGON_FEATURE, &lv_80);
        if (t20 == S_OK)
            sub_1D8810()->sub_1DB970();
        unk_90 = arg_0;
        break;
    }
    case 2:
    case 6:
    {
        unk_15D = sub_2279D0(false);
        memset(&fp_98, 0, sizeof(fp_98));
        fp_98.StructSize = sizeof(fp_98);
        if (has_dword_4B9E50())
            fp_98.UserPort = get_dword_4B9E50();
        t20 = unk_84->StartFeature(UIX_FRIENDS_FEATURE, &fp_98);
        if (t20 == S_OK)
            unk_90 = arg_0;
        else
        {
            fp_98.UserPort = sub_227900(0);
            t20 = unk_84->StartFeature(UIX_FRIENDS_FEATURE, &fp_98);
        }
        if (t20 == S_OK)
            unk_90 = arg_0;
        break;
    }
    case 3:
    case 7:
    {
        unk_15D = sub_2279D0(false);
        memset(&l1C, 0, sizeof(l1C));
        l1C.StructSize = sizeof(l1C);
        l1C.DisplayType = UIX_PLAYERS_DISPLAY_CURRENT_PLAYERS | UIX_PLAYERS_DISPLAY_DEPARTED_PLAYERS;
        l1C.FilterFlags = 0;
        l1C.pPlayerControllingScreen = 0;
        l1C.SortCurrentPlayersList = FALSE;
        if (has_dword_4B9E50())
            l1C.UserPort = get_dword_4B9E50();
        t20 = unk_84->StartFeature(UIX_PLAYERS_FEATURE, &l1C);
        if (t20 == S_OK)
            unk_90 = arg_0;
        else
        {
            l1C.UserPort = sub_227900(0);
            l1C.UserPort = l1C.UserPort;
            t20 = unk_84->StartFeature(UIX_PLAYERS_FEATURE, &l1C);
        }
        if (t20 == S_OK)
            unk_90 = arg_0;
        break;
    }
    }
}

// match: ?sub_227530@type_5051E8@@QAEXXZ @ 0x00227530
void type_5051E8::sub_227530()
{
    unk_84->EndFeature();
    sub_2279D0(true);
}

// match: ?sub_227560@@YAPAUtype_5051E8@@XZ @ 0x00227560
// match: __ehhandler$?sub_227560@@YAPAUtype_5051E8@@XZ-0xE @ 0x00308FA0
// match: __ehhandler$?sub_227560@@YAPAUtype_5051E8@@XZ @ 0x00308FAE
type_5051E8 *sub_227560()
{
    static type_5051E8 s;

    return &s;
}

// (The compiler's exit thunk for sub_227560's instance: it runs the late
// service's destructor.)

// match: ?sub_2275D0@type_5051E8@@QAEHXZ @ 0x002275D0
RwInt32 type_5051E8::sub_2275D0()
{
    return unk_90;
}

// match: ?sub_2275F0@type_5051E8@@QAEXH@Z @ 0x002275F0
void type_5051E8::sub_2275F0(RwInt32 arg_0)
{
    if (!unk_1114.test(arg_0))
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_1116.unk_00)
        {
        }
        if (!unk_1116.test(arg_0))
            unk_1114.admit(arg_0);
    }
}

// match: ?sub_227660@type_5051E8@@QAEXH@Z @ 0x00227660
void type_5051E8::sub_227660(RwInt32 arg_0)
{
    if (unk_148.size())
    {
        // A compiled-out check of a dword (docs/toolchain.md): the test's
        // registers are one load on. Which member it read is not in the
        // code.
        if (!unk_90)
        {
        }
        if (unk_1116.test(arg_0))
        {
            ILivePlayersList *var_4;
            XUID var_10;

            unk_84->GetFeatureInterface(UIX_PLAYERS_FEATURE, 0, (VOID **)&var_4);
            if (sub_1D8810()->sub_1DBD60(arg_0, &var_10, 0))
            {
                for (std::vector<type_22AF50 *>::iterator var_14 = unk_148.begin(); var_14 != unk_148.end(); ++var_14)
                {
                    type_22AF50 *var_18 = *var_14;

                    if (var_18->GetXUID()->qwUserID == var_10.qwUserID)
                    {
                        var_4->UnregisterPlayer(var_18);
                        delete var_18;
                        unk_148.erase(var_14);
                        break;
                    }
                }
            }
            unk_1116.drop(arg_0);
        }
    }
    unk_1114.drop(arg_0);
}

// match: ?sub_227870@type_5051E8@@QAEXXZ @ 0x00227870
void type_5051E8::sub_227870()
{
    ILivePlayersList *var_4;

    unk_84->GetFeatureInterface(UIX_PLAYERS_FEATURE, 0, (VOID **)&var_4);
    if (var_4)
        var_4->ClearDepartedPlayersList();
}

// match: ?sub_2278C0@type_5051E8@@QAEXXZ @ 0x002278C0
void type_5051E8::sub_2278C0()
{
    sub_228040();
    unk_84->LogOff();
    sub_1D8810()->sub_1DB950();
}

// match: ?sub_227900@@YAHPAU_XONLINE_USER@@@Z @ 0x00227900
RwInt32 sub_227900(XONLINE_USER *arg_0)
{
    if (!arg_0)
        arg_0 = XOnlineGetLogonUsers();
    if (arg_0)
    {
        for (RwInt32 var_4 = 0; var_4 < 4; var_4++)
        {
            if (arg_0[var_4].szGamertag[0])
                return var_4;
        }
    }
    return -1;
}

// match: ?sub_227950@type_5051E8@@QAEHXZ @ 0x00227950
RwInt32 type_5051E8::sub_227950()
{
    RwInt32 bp_8 = sub_227900(0);
    RwInt32 bp_4 = 0;

    if (bp_8 >= 0)
    {
        DWORD slot_C;

        if (unk_84->GetNotifications(bp_8, UIX_NOTIFICATION_MENU, &slot_C) == S_OK)
        {
            if (slot_C & UIX_DOWORK_NOTIFY_FRIEND_REQUEST)
                bp_4 |= 1;
            if (slot_C & UIX_DOWORK_NOTIFY_GAME_INVITE)
                bp_4 |= 2;
        }
    }
    return bp_4;
}

// match: ?sub_2279D0@type_5051E8@@QAE_N_N@Z @ 0x002279D0
bool type_5051E8::sub_2279D0(bool arg_0)
{
    bool fp_2;
    bool l1;

    l1 = unk_15C;

    if (unk_15C != arg_0)
    {
        unk_15C = arg_0;
        if (unk_15C)
        {
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Player muting update started\n");
            switch (XOnlineMutelistStartup(0, &unk_160))
            {
            }
            // A compiled-out check (docs/toolchain.md).
            if (!unk_164)
            {
            }
            unk_164 = 1;
        }
        else
        {
            fp_2 = true;

            while (fp_2)
            {
                switch (XOnlineTaskContinue(unk_160))
                {
                case XONLINETASK_S_SUCCESS:
                case XONLINETASK_S_RUNNING_IDLE:
                    fp_2 = false;
                    if (XOnlineTaskClose(unk_160) == S_OK)
                        unk_160 = 0;
                    break;
                }
            }
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Player muting update stopped\n");
        }
    }
    return l1;
}

// match: ?sub_227AC0@type_5051E8@@QAEXH@Z @ 0x00227AC0
void type_5051E8::sub_227AC0(RwInt32 arg_0)
{
    HRESULT ebp_14;
    DWORD lv_10 = unk_94;
    XNKID slot_C = sub_1D8810()->get_unk_4040();
    if (!(sub_1D8810()->get_unk_3DAC() & 4))
        lv_10 &= ~0x10;
    ebp_14 = unk_84->NotificationSetState(arg_0, lv_10, slot_C, 0, 0);
    unk_98 = slot_C;
}

// match: ?sub_227B80@type_5051E8@@QAEXH@Z @ 0x00227B80
void type_5051E8::sub_227B80(RwInt32 arg_0)
{
    unk_A0 = arg_0;
}

// match: ?sub_227BA0@type_5051E8@@QAEXXZ @ 0x00227BA0
void type_5051E8::sub_227BA0()
{
    type_3E3860 *bp_8 = dword_4F8180;

    if (!bp_8)
        return;
    RwInt32 bp_4 = bp_8->unk_3060.sub_1C73F0();

    if (bp_4 == 1)
        unk_94 |= 8;
    else
        unk_94 &= ~8;
}

// match: ?sub_227C00@type_5051E8@@QAEXXZ @ 0x00227C00
void type_5051E8::sub_227C00()
{
    if (unk_A0)
        unk_94 |= 1;
    else
        unk_94 &= ~1;
}

// match: ?sub_227C50@type_5051E8@@QAEXXZ @ 0x00227C50
void type_5051E8::sub_227C50()
{
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480())
        unk_94 |= 2;
    else
        unk_94 &= ~2;
}

// match: ?sub_227CA0@type_5051E8@@QAEXXZ @ 0x00227CA0
void type_5051E8::sub_227CA0()
{
    if (!(unk_94 & 2) || unk_4F7EB8.get_unk_19C_direct()->vf_06C())
        unk_94 &= ~0x10;
    else
    {
        RwUInt32 slot_C;
        type_1DDE20_mask bp_8 = unk_4F7EB8.get_unk_19C()->get_unk_B0()->get_unk_0C();
        RwUInt32 bp_4;

        slot_C = bp_8.sub_1D4A60();
        bp_4 = unk_4F7EB8.get_unk_19C()->unk_43;

        if (bp_4 - slot_C >= 4)
            unk_94 |= 0x10;
        else
            unk_94 &= ~0x10;
    }
}

// match: ?sub_227D70@type_5051E8@@QAEXPBU_XONLINE_FRIEND@@@Z @ 0x00227D70
void type_5051E8::sub_227D70(const XONLINE_FRIEND *arg_0)
{
    RwInt32 t20;
    DWORD l1C;
    PXONLINE_MATCH_SEARCHRESULT *m_18;
    HRESULT ebp_14;
    XONLINETASK_HANDLE lv_10;

    unk_00 = 0;
    unk_A4 = 1;
    XNKID slot_C = arg_0->sessionID;

    ebp_14 = XOnlineMatchSessionFindFromID(slot_C, 0, &lv_10);
    while (ebp_14 == XONLINETASK_S_RUNNING)
    {
        ebp_14 = XOnlineTaskContinue(lv_10);
        Sleep(100);
    }
    if (SUCCEEDED(ebp_14))
    {
        ebp_14 = XOnlineMatchSearchGetResults(lv_10, &m_18, &l1C);
        if (SUCCEEDED(ebp_14) && l1C > 0)
        {
            unk_A4 = 0;
            bool r25;
            XONLINE_MATCH_SEARCHRESULT *frm_24;

            frm_24 = *m_18;

            memset(&unk_04, 0, sizeof(unk_04));
            unk_04.unk_2A = (RwUInt8)(frm_24->dwPrivateFilled + frm_24->dwPrivateOpen + frm_24->dwPublicFilled + frm_24->dwPublicOpen);
            unk_04.unk_5C = frm_24->SessionID;
            unk_04.unk_64 = frm_24->KeyExchangeKey;
            unk_04.unk_38 = frm_24->HostAddress;
            unk_04.unk_00 = sizeof(unk_04);
            unk_04.unk_34 = 1;
            r25 = true;
            XNKID h30 = sub_1D8810()->get_unk_4040();

            for (t20 = 0; t20 < 8; t20++)
            {
                if (h30.ab[t20] != frm_24->SessionID.ab[t20])
                    r25 = false;
            }
            if (!r25)
                unk_00 = 1;
        }
        XOnlineTaskClose(lv_10);
        lv_10 = 0;
    }
}

// match: ?sub_227F30@type_5051E8@@QAEXXZ @ 0x00227F30
void type_5051E8::sub_227F30()
{
    if (!unk_144)
        return;
    unk_144 = 0;
    sub_227D70(&unk_A8.InvitingFriend);
}

// match: ?sub_227F70@type_5051E8@@QAEXXZ @ 0x00227F70
void type_5051E8::sub_227F70()
{
    DWORD bp_8;
    type_3E3860 *bp_4 = dword_4F8180;

    bp_4->sub_1C6920(0);
    // A compiled-out check (docs/toolchain.md).
    if (!unk_84)
    {
    }
    bp_8 = (DWORD)get_dword_4F8180()->unk_3060.unk_0C;
    // A compiled-out check (docs/toolchain.md).
    if (!unk_84)
    {
    }
    unk_84->SetProperty(UIX_PROPERTY_VOICE_MAIL_ENGINE, bp_8);
    unk_88 = true;
    unk_84->SetProperty(UIX_PROPERTY_VOICE_MAIL_TO_SPEAKERS, get_dword_4F8180()->unk_3060.unk_F0);
}

// match: ?sub_228000@type_5051E8@@QAEXXZ @ 0x00228000
void type_5051E8::sub_228000()
{
    unk_84->SetProperty(UIX_PROPERTY_VOICE_MAIL_TO_SPEAKERS, get_dword_4F8180()->unk_3060.unk_F0);
}

// match: ?sub_228040@type_5051E8@@QAEXXZ @ 0x00228040
void type_5051E8::sub_228040()
{
    if (unk_88)
    {
        unk_88 = false;
        unk_84->SetProperty(UIX_PROPERTY_VOICE_MAIL_ENGINE, 0);
        type_3E3860 *var_4 = dword_4F8180;

        var_4->sub_1C69A0();
    }
}

// match: ?sub_228090@type_5051E8@@QAEXH@Z @ 0x00228090
void type_5051E8::sub_228090(RwInt32 arg_0)
{
    unk_1118 = arg_0;
    unk_84->SetProperty(UIX_PROPERTY_DISPLAY_CONNECTION_ERRORS, arg_0);
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("UIX_PROPERTY_DISPLAY_CONNECTION_ERRORS=%d\n", arg_0);
}

// match: ?sub_2280E0@type_5051E8@@QAEHXZ @ 0x002280E0
RwInt32 type_5051E8::sub_2280E0()
{
    return unk_80 & UIX_DOWORK_PROCESSING_INPUT;
}

// match: ?sub_228100@type_5051E8@@QAE_NXZ @ 0x00228100
bool type_5051E8::sub_228100()
{
    return unk_158 == 4;
}

// match: ?sub_228120@type_5051E8@@QAEXPAU_UIX_EXIT_INFO@@H@Z @ 0x00228120
void type_5051E8::sub_228120(UIX_EXIT_INFO *arg_0, RwInt32 arg_4)
{
    switch (arg_4)
    {
    case 4:
        switch (arg_0->hr)
        {
        case 0x80151082:
            sub_1D8810()->sub_1DBA20();
            break;
        default:
            sub_1D8810()->sub_1DB950();
            break;
        }
        break;
    case 1:
        switch (arg_0->hr)
        {
        default:
            sub_1D8810()->sub_1DB950();
            break;
        }
        break;
    default:
        if (unk_1118)
        {
            unk_111C = 1;
            dword_4FDA9C = 1;
        }
        unk_1124 = 0;
        switch (arg_0->hr)
        {
        case 0x80151005:
            sub_1D8810()->sub_1DBA00();
            break;
        default:
            sub_1D8810()->sub_1DB950();
            break;
        }
        break;
    }
    sub_228040();
}

// match: ?sub_2281F0@type_5051E8@@QAEHPAU_UIX_EXIT_INFO@@H@Z @ 0x002281F0
RwInt32 type_5051E8::sub_2281F0(UIX_EXIT_INFO *arg_0, RwInt32 arg_4)
{
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("JOIN_GAME\n");
    sub_227D70((const XONLINE_FRIEND *)arg_0->pExitData);
    if (!dword_4F45F8->unk_38 && !dword_4F45F8->unk_3C)
        return 0;
    return 1;
}

// match: ?sub_228240@type_5051E8@@QAEXPAU_UIX_EXIT_INFO@@H@Z @ 0x00228240
void type_5051E8::sub_228240(UIX_EXIT_INFO *arg_0, RwInt32 arg_4)
{
    DWORD bp_220[0x10];
    DWORD l1E0;
    RwInt32 fp_1DC;
    XONLINE_USER fp_1D8[4];
    XONLINE_USER *lv_10;
    bool w9;
    RwChar *bp_8;
    XONLINE_USER *bp_4;

    sub_1D8810()->sub_1DB990();
    bp_4 = sub_1D8810()->sub_1DBD40();
    bp_8 = unk_4F7EB8.get_unk_19C()->unk_80;
    strcpy(bp_8, bp_4->szGamertag);
    strcpy(dword_4F28F0->unk_183, bp_4->szGamertag);
    unk_1124 = arg_4 == 4;
    sub_227F70();
    if (dword_4F45F8->unk_38)
    {
        w9 = true;

        if (dword_4F45F8->unk_40)
        {
            l1E0 = 0x10;
            lv_10 = XOnlineGetLogonUsers();
            for (fp_1DC = 0; fp_1DC < 4; fp_1DC++)
            {
                if (lv_10[fp_1DC].szGamertag[0])
                    break;
            }
            if (fp_1DC < 4
                && XOnlineRetrieveLogonState((XONLINE_LOGON_STATE *)dword_4F45F8->unk_48A, fp_1D8, bp_220, &l1E0) == S_OK
                && strcmp(lv_10[fp_1DC].szGamertag, fp_1D8[fp_1DC].szGamertag))
                w9 = false;
        }
        if (w9)
            sub_227D70((const XONLINE_FRIEND *)dword_4F45F8->unk_434);
        dword_4F45F8->unk_38 = 0;
    }
}

// match: ?sub_2283F0@type_5051E8@@QAEXH@Z @ 0x002283F0
void type_5051E8::sub_2283F0(RwInt32 arg_0)
{
    unk_78 = arg_0;
    if (unk_84)
        unk_84->SetProperty(UIX_PROPERTY_HOST_NO_MIGRATION, unk_78);
}

// std::vector<type_22AF50 *>'s instances (the explicit instantiation above).
// match: ?push_back@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@QAEXABQAUtype_22AF50@@@Z @ 0x00228440
// match: ?insert@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@QAE?AViterator@12@V312@ABQAUtype_22AF50@@@Z @ 0x00228520
// match: ?_Buy@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAE_NI@Z @ 0x002285D0
// match: ?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z @ 0x00228670
// match: __ehhandler$?_Insert_n@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IAEXViterator@12@IABQAUtype_22AF50@@@Z @ 0x00308FC0
// match: ?_Xlen@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IBEXXZ @ 0x00228CE0
// match: __ehhandler$?_Xlen@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IBEXXZ-0x8 @ 0x00308FD0
// match: __ehhandler$?_Xlen@?$vector@PAUtype_22AF50@@V?$allocator@PAUtype_22AF50@@@std@@@std@@IBEXXZ @ 0x00308FD8
