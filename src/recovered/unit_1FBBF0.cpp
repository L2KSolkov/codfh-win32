/*
 * The in-game menus' manager (game/ingamemenu.h): the one instance, its
 * passing of kujuUI's events, updates and drawing to the pad's widget stack,
 * the menu shown and hidden.
 */
#include "game/liveservice.h"
#include "game/ingamemenu.h"
#include "game/frontend.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/render.h"
#include "game/startup.h"
#include "game/waitscreen.h"
#include "rws/gftime.h"
#include "types/musicplayer.h"
#include "types/soundbank.h"
#include "types/type_DC400.h"
#include "game/kujuui.h"
#include "game/livebase.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E7E5C
extern const RwReal flt_3E7E5C = 16.666666f;
// 0x003E7E60
extern const RwReal flt_3E7E60 = 0.01f;
// 0x003E7E64
extern const RwReal flt_3E7E64 = 0.01f;
// 0x005043B0
InGameMenuManager *dword_5043B0;
// 0x005043B4
kujuUI::type_1E3DB0 *dword_5043B4;
// 0x005043B8
RwRGBA unk_5043B8;
// End of its data definitions.


using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E7E5C@@3MB @ 0x003E7E5C
// match: ?flt_3E7E60@@3MB @ 0x003E7E60
// match: ?flt_3E7E64@@3MB @ 0x003E7E64
// match: ??_7InGameMenuManager@@6B@ @ 0x003E7E68
// match: ??_C@_0DE@GPDFBHFK@cContextSequencer?5InGameMenuMana@ @ 0x003E7E70
// match: ??_C@_0DE@LJJBIANI@cContextSequencer?5InGameMenuMana@ @ 0x003E7EA4
// match: __ehhandler$??0InGameMenuManager@@QAE@PAUtype_1FBDA0_menu@@@Z>1>8 @ 0x00421588
// match: __ehhandler$??0InGameMenuManager@@QAE@PAUtype_1FBDA0_menu@@@Z>1 @ 0x00421590
// match: __ehhandler$?sub_1FBE70@InGameMenuManager@@QAEXPAURwCamera@@@Z>1>8 @ 0x004215AC
// match: __ehhandler$?sub_1FBE70@InGameMenuManager@@QAEXPAURwCamera@@@Z>1 @ 0x004215BC

// match: ??0InGameMenuManager@@QAE@PAUtype_1FBDA0_menu@@@Z @ 0x001FBBF0
// match: __ehhandler$??0InGameMenuManager@@QAE@PAUtype_1FBDA0_menu@@@Z-0x8 @ 0x00304C20
// match: __ehhandler$??0InGameMenuManager@@QAE@PAUtype_1FBDA0_menu@@@Z @ 0x00304C28

InGameMenuManager::InGameMenuManager(type_1FBDA0_menu *arg_0) : unk_04(arg_0)
{
    dword_5043B0 = this;
    if (arg_0)
        sub_1E7CF0()->sub_1E7D30(arg_0);
    sub_1F7770(sub_1E7CF0());
}

// match: ??1type_3E6CE4@kujuUI@@UAE@XZ @ 0x001FBC80

// match: ??_GInGameMenuManager@@UAEPAXI@Z @ 0x001FBCA0

// match: ??1InGameMenuManager@@UAE@XZ @ 0x001FBCD0
InGameMenuManager::~InGameMenuManager()
{
    dword_5043B0 = 0;
}

// match: ?sub_1FBD00@InGameMenuManager@@QAEXM@Z @ 0x001FBD00
void InGameMenuManager::sub_1FBD00(RwReal arg_0)
{
    if (showing())
        sub_1E7CF0()->vf_014(arg_0);
}

// match: ?sub_1FBD40@InGameMenuManager@@QAEXPAUtype_1E4130@kujuUI@@@Z @ 0x001FBD40
void InGameMenuManager::sub_1FBD40(type_1E4130 *arg_0)
{
    sub_1E7CF0()->vf_018(arg_0);
}

// match: ?processEvent@InGameMenuManager@@UAE?AW4eEventWasHandled@kujuUI@@ABVcStateChange@3@@Z @ 0x001FBD70
eEventWasHandled InGameMenuManager::processEvent(const cStateChange &arg_0)
{
    return sub_1E7CF0()->processEvent(arg_0);
}

// match: ?sub_1FBDA0@InGameMenuManager@@QAEXPAUtype_1FBDA0_menu@@@Z @ 0x001FBDA0
void InGameMenuManager::sub_1FBDA0(type_1FBDA0_menu *arg_0)
{
    if (unk_04)
    {
        unk_04->vf_040();
        sub_1E7CF0()->sub_1E7D90(unk_04);
    }
    unk_04 = arg_0;
    ((type_20E850 *)unk_04)->sub_20EA40();
    unk_04->vf_03C();
    sub_1E7CF0()->sub_1E7D30(unk_04);
}

// match: ?sub_1FBE20@InGameMenuManager@@QAEXXZ @ 0x001FBE20
void InGameMenuManager::sub_1FBE20()
{
    if (unk_04)
    {
        unk_04->vf_040();
        sub_1E7CF0()->sub_1E7D90(unk_04);
        unk_04 = 0;
    }
}

// match: ?sub_1FBE70@InGameMenuManager@@QAEXPAURwCamera@@@Z @ 0x001FBE70
// match: __ehhandler$?sub_1FBE70@InGameMenuManager@@QAEXPAURwCamera@@@Z-0x16 @ 0x00304C40
// match: __ehhandler$?sub_1FBE70@InGameMenuManager@@QAEXPAURwCamera@@@Z @ 0x00304C56
void InGameMenuManager::sub_1FBE70(RwCamera *arg_0)
{
    if (!dword_5043B4)
    {
        sub_1E3F50(0, &dword_5043B4);
        unk_08 = dword_5043B4;
    }
    type_1EE900 v120;
    type_1E7560 l114;
    sub_1C40F0();
    unk_0C = RWS::Time::GetTime();
    while (showing())
    {
        unk_4F7EB8.get_unk_19C_direct()->vf_054(0);
        unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
        sub_1B18D0()->sub_1B00B0();
        sub_D9620();
        RwUInt32 frm_124 = RWS::Time::GetTime() - unk_0C;
        unk_0C += frm_124;
        RwReal o1E0 = frm_124 / 1000.0f;
        unk_4B9308.sub_EE6D0();
        if (unk_04)
        {
            if (unk_08->sub_2015D0())
            {
                type_1EE900 local_1EC = unk_08->sub_1E3DD0();
                local_1EC.sub_1EE940(&v120, &l114);
                v120 = local_1EC;
            }
            while (l114.sub_1E75F0())
            {
                if (sub_227560()->sub_2280E0())
                    l114.sub_1E7610();
                else
                    processEvent(l114.sub_1E7610());
            }
        }
        if (dword_42926C == 0)
        {
            if (sub_188350() != 4)
            {
                if (0)
                {
                    sub_1C8A30("cContextSequencer InGameMenuManager::ShowMenu() %d\n", sub_186D00());
                }
                sub_186E70(4, 0, arg_0);
            }
            sub_187B30();
        }
        else
        {
            if (sub_188350() == 4)
            {
                if (0)
                {
                    sub_1C8A30("cContextSequencer InGameMenuManager::KillMenu() %d\n", sub_186D00());
                }
                sub_186F80(4, 1);
            }
            sub_1FBD00(o1E0);
        }
        sub_19A750(o1E0);
        sub_85090(o1E0, 0);
        sub_857B0(o1E0);
        if (dword_504378)
            dword_504378->vf_00();
        RwCameraClear(arg_0, &unk_5043B8, 3);
        RwCameraBeginUpdate(arg_0);
        type_1E4130 u1DC;
        u1DC.pDtor();
        sub_1FBD40(&u1DC);
        u1DC.sub_1E41D0();
        sub_227560()->sub_227070();
        sub_187150((RwInt32)arg_0);
        sub_1B18D0()->sub_1B00F0();
        RwCameraEndUpdate(arg_0);
        RwCameraShowRaster(arg_0, 0, 1);
        sub_19A750();
        if (((kujuUI::type_1EE900 *)sub_227560())->sub_1EE9D0())
        {
            if (sub_1E7CF0()->sub_1E7D00(sub_20A540()))
                sub_1E7CF0()->sub_1E7D90(sub_20A540());
            if (unk_04 != sub_2046C0(3))
                sub_1FBDA0(sub_2046C0(3));
        }
    }
    delete unk_08;
    dword_5043B4 = 0;
    sub_204620();
    sub_1C41F0();
}

// match: ?sub_1FC310@@YAPAVInGameMenuManager@@XZ @ 0x001FC310
InGameMenuManager *sub_1FC310()
{
    return dword_5043B0;
}
