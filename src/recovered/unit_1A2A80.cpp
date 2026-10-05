// Split from unit_1A26F0.cpp at 0x1A2A80, where the image starts another object (the network
// step and the message factories): its .rdata begins at 0x3E0EAC with its own constant block
// (16.666666, 0.01, 0.01) before its vtables (PLAN M7).

#include "game/liveservice.h"
#include <stdio.h>
#include "game/pak.h"
#include "game/waitscreen.h"
#include "game/startup.h"
#include "game/debugtext.h"
#include "game/savestate.h"
#include "types/type_DC400.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/frontend.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/babintex.h"
#include "game/ingamepages.h"
#include "game/fade.h"
#include "game/uiglue.h"
#include "types/cXboxLive.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E0EAC
extern const RwReal flt_3E0EAC = 16.666666f;
// 0x003E0EB0
extern const RwReal flt_3E0EB0 = 0.01f;
// 0x003E0EB4
extern const RwReal flt_3E0EB4 = 0.01f;

// match: ?flt_3E0EAC@@3MB @ 0x003E0EAC
// match: ?flt_3E0EB0@@3MB @ 0x003E0EB0
// match: ?flt_3E0EB4@@3MB @ 0x003E0EB4


// match: _$E3 @ 0x0030EA50
// match: _$E11 @ 0x0030EA40
// match: _$E13 @ 0x0030EA30
// match: _$E18 @ 0x0030EA20

// match: __ehhandler$?sub_1A2A80@@YAXM@Z>1>8 @ 0x0041E980
// match: __ehhandler$?sub_1A2A80@@YAXM@Z>1 @ 0x0041E990
// match: __ehhandler$?sub_1A2E40@@YAXPAURwCamera@@@Z>1>8 @ 0x0041E9AC
// match: __ehhandler$?sub_1A2E40@@YAXPAURwCamera@@@Z>1 @ 0x0041E9BC
// match: __ehhandler$?sub_1A32B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z>1>8 @ 0x0041E9D8
// match: __ehhandler$?sub_1A32B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z>1 @ 0x0041E9E0
// match: __ehhandler$?sub_1A3330@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z>1>8 @ 0x0041E9FC
// match: __ehhandler$?sub_1A3330@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z>1 @ 0x0041EA04
// match: __ehhandler$?sub_1A34A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z>1>8 @ 0x0041EA20
// match: __ehhandler$?sub_1A34A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z>1 @ 0x0041EA28
// match: ??_7type_3E0EB8@@6B@ @ 0x003E0EB8
// match: ??_7type_3E0EC4@@6B@ @ 0x003E0EC4
// match: ??_C@_0BJ@NOCGKFAA@NO_SYSTEMLINK_CONNECTION?$AA@ @ 0x003E0ED0
// match: ??_C@_0BG@CLGPCLAB@NO_NETWORK_CONNECTION?$AA@ @ 0x003E0EEC
// match: ??_C@_0CK@IDJFDNPL@Loading?5Texture?5Dictionary?5file?5@ @ 0x003E0F04
// match: ??_C@_0CE@CEIIHLNI@SHELL?2FEND?2INSTANCE?2XBOX?2F_FEND?4@ @ 0x003E0F30
// match: ??_7type_3E0F54@@6B@ @ 0x003E0F54
// match: ??_7type_3E0F60@@6B@ @ 0x003E0F60
// match: ??_7type_3E0F6C@@6B@ @ 0x003E0F6C
// match: ??_7type_3E0F78@@6B@ @ 0x003E0F78
// match: ??_7type_3E0F84@@6B@ @ 0x003E0F84
// match: ??_7type_3E0F90@@6B@ @ 0x003E0F90
// match: ??_7type_3E0F9C@@6B@ @ 0x003E0F9C
// match: ??_7type_3E0FA8@@6B@ @ 0x003E0FA8
// match: ??_7type_3E0FB4@@6B@ @ 0x003E0FB4
// match: ??_7type_3E0FC0@@6B@ @ 0x003E0FC0
// match: ??_7type_3E0FCC@@6B@ @ 0x003E0FCC
// match: ??_7type_3E0FD8@@6B@ @ 0x003E0FD8
// match: ??_7type_3E0FE4@@6B@ @ 0x003E0FE4
// match: ??_7type_3E0FF0@@6B@ @ 0x003E0FF0
// match: ??_7type_3E0FFC@@6B@ @ 0x003E0FFC
// match: ??_7type_3E1008@@6B@ @ 0x003E1008
// match: ??_7type_3E1014@@6B@ @ 0x003E1014
// match: ??_7type_3E1020@@6B@ @ 0x003E1020
// match: ??_7type_3E102C@@6B@ @ 0x003E102C
// match: ??_7type_3E1038@@6B@ @ 0x003E1038
// match: ??_7type_3E1044@@6B@ @ 0x003E1044
// match: ??_7type_3E1050@@6B@ @ 0x003E1050
// match: ??_7type_3E105C@@6B@ @ 0x003E105C
// match: ??_7type_3E1068@@6B@ @ 0x003E1068
// match: ??_7type_3E1074@@6B@ @ 0x003E1074
// match: ??_7type_3E1080@@6B@ @ 0x003E1080
// match: ??_7type_3E108C@@6B@ @ 0x003E108C
// match: ??_7type_3E1098@@6B@ @ 0x003E1098
// match: ??_7type_3E10A4@@6B@ @ 0x003E10A4
// match: ??_7type_3E10B0@@6B@ @ 0x003E10B0
// match: ??_7type_3E10BC@@6B@ @ 0x003E10BC
// match: ??_7type_3E10C8@@6B@ @ 0x003E10C8
// match: ??_7type_3E10D4@@6B@ @ 0x003E10D4
// match: ??_7type_3E10E0@@6B@ @ 0x003E10E0
// match: ??_7type_3E10EC@@6B@ @ 0x003E10EC
// match: ??_7type_3E10F8@@6B@ @ 0x003E10F8
// match: ??_7type_3E1104@@6B@ @ 0x003E1104
// match: ??_7type_3E1110@@6B@ @ 0x003E1110
// match: ??_7type_3E111C@@6B@ @ 0x003E111C
// match: ??_7type_3E1128@@6B@ @ 0x003E1128
// match: ??_7type_3E1134@@6B@ @ 0x003E1134
// match: ??_7type_3E1140@@6B@ @ 0x003E1140
// match: ??_7type_3E114C@@6B@ @ 0x003E114C
// match: ??_7type_3E1158@@6B@ @ 0x003E1158
// match: ??_7type_3E1164@@6B@ @ 0x003E1164
// match: ??_7type_3E1170@@6B@ @ 0x003E1170
// match: ??_7type_3E117C@@6B@ @ 0x003E117C
// match: ??_7type_3E1188@@6B@ @ 0x003E1188
// match: ??_7type_3E1194@@6B@ @ 0x003E1194
// match: ??_7type_3E11A0@@6B@ @ 0x003E11A0
// match: ??_7type_3E11AC@@6B@ @ 0x003E11AC
// match: ??_7type_3E11B8@@6B@ @ 0x003E11B8

// match: ?sub_1A2A80@@YAXM@Z @ 0x001A2A80
// match: __ehhandler$?sub_1A2A80@@YAXM@Z-0x10 @ 0x003027E0
// match: __ehhandler$?sub_1A2A80@@YAXM@Z @ 0x003027F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The network's step by arg_0: the multiplayer manager's step; then, where
// the in-game warnings screen exists, the lost connection's warning: shown
// ("NO_NETWORK_CONNECTION" while the voice runs, else
// "NO_SYSTEMLINK_CONNECTION"; a client tells the others, then the manager
// ends the game) once the network game reports it, hidden again (going back
// to the game) once it no longer does.
void sub_1A2A80(RwReal arg_0)
{
    unk_4F7EB8.sub_1AAB50(arg_0);
    if (type_215740::sub_215A50())
    {
        RwInt32 m_18;
        type_4F8054 *ebp_14;
        bool bp_D;

        ebp_14 = dword_4F8054;
        m_18 = sub_1CCA10().get_unk_00();
        bp_D = true;
        if (ebp_14 && ebp_14->vf_050())
            bp_D = false;
        if (type_215740::sub_215910(&dword_5051D0))
        {
            dword_4CF410 = 1;
            if (!bp_D)
            {
                type_215740::sub_2156B0(&dword_5051D0);
                sub_1C44A0();
            }
        }
        else if (bp_D && !dword_4FB9E0.get_unk_C8() && type_215740::sub_2155A0(&dword_5051D0))
        {
            if (sub_1D8810()->voice_running())
                type_215740::sub_215970(type_1CB670("NO_NETWORK_CONNECTION", 0), &dword_5051D0);
            else
                type_215740::sub_215970(type_1CB670("NO_SYSTEMLINK_CONNECTION", 0), &dword_5051D0);
            if (!dword_4F62FC)
            {
                type_1DDE20_mask var_20;
                type_3E0EB8 l1C;

                var_20 = type_4F8054::get()->get_unk_B0_checked()->others_checked();
                type_4F8058::get()->sub_1DDDB0(&l1C, var_20);
            }
            unk_4F7EB8.sub_1AF6F0();
        }
    }
}
// match: ?sub_1A2D00@@YAXXZ @ 0x001A2D00
// Draws the log.
void sub_1A2D00()
{
    sub_1B18D0()->sub_1B00F0();
}
// match: ?sub_1A2D20@@YAXXZ @ 0x001A2D20
void sub_1A2D20()
{
    unk_4F7EB8.sub_1A9960();
    sub_16BAC0();
}
// match: ?sub_1A2D40@@YAXXZ @ 0x001A2D40
void sub_1A2D40()
{
    unk_4F7EB8.sub_1A8E80();
}
// match: ?sub_1A2D50@@YAXXZ @ 0x001A2D50
void sub_1A2D50()
{
    unk_4F7EB8.sub_1A9160();
}
// match: ?sub_1A2D60@@YAXXZ @ 0x001A2D60
void sub_1A2D60()
{
    dword_4FB9E0.sub_1B52D0();
}
// match: ?sub_1A2D70@@YAXXZ @ 0x001A2D70
void sub_1A2D70()
{
    dword_4FB9E0.sub_1B4F40();
}
// match: ?sub_1A2D80@@YAXXZ @ 0x001A2D80
void sub_1A2D80()
{
    dword_4FB9E0.sub_1B4DF0();
}
// match: ?sub_1A2D90@@YAPAURwTexDictionary@@PBD@Z @ 0x001A2D90
// Reads the texture dictionary in the level file arg_0 (its path built by
// sub_D7F20); 0 when there is none.
RwTexDictionary *sub_1A2D90(const RwChar *arg_0)
{
    RwChar ebp_210[0x200];
    RwTexDictionary *lv_8 = 0;
    RwStream *var_4 = 0;

    sub_D7F20(ebp_210, arg_0);
    printf("Loading Texture Dictionary file from: %s\n", ebp_210);
    var_4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, ebp_210);
    if (var_4)
    {
        if (RwStreamFindChunk(var_4, rwID_TEXDICTIONARY, 0, 0))
            lv_8 = RwTexDictionaryStreamRead(var_4, 0);
        RwStreamClose(var_4, 0);
    }
    return lv_8;
}
// match: ?sub_1A2E40@@YAXPAURwCamera@@@Z @ 0x001A2E40
// match: __ehhandler$?sub_1A2E40@@YAXPAURwCamera@@@Z-0x13 @ 0x00302800
// match: __ehhandler$?sub_1A2E40@@YAXPAURwCamera@@@Z @ 0x00302813
// Runs the shell's screens on the camera arg_0: the front end's textures and
// font, the pads, the memory card, then the shell with its hooks, all put
// away again after it.
void sub_1A2E40(RwCamera *arg_0)
{
    RwTexDictionary *var_F0;
    type_DA580 *var_F4;

    var_F0 = sub_1A2D90("SHELL\\FEND\\INSTANCE\\XBOX\\F_FEND.TXD");
    sub_186720();
    var_F4 = type_DA580::sub_DA680("t12");
    sub_186970(var_F4);
    sub_186880(0);
    unk_4B8744.sub_D9CF0(0, 0);
    sub_20A540();
    dword_4F7E98 = arg_0;
    type_3E83E4 var_EC;
    dword_504378 = &var_EC;
    if (dword_504378)
        dword_504378->vf_08();
    type_200960 l3C(arg_0);
    l3C.sub_200AE0();
    if (dword_504378)
        dword_504378->vf_0C();
    dword_504378 = 0;
    sub_1868E0();
    unk_4B8744.pDtor();
    if (var_F0)
    {
        delete var_F4;
        var_F4 = 0;
        RwTexDictionaryDestroy(var_F0);
        var_F0 = 0;
    }
    dword_4F7E98 = 0;
}
// match: ?sub_1A3020@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3020
type_3DA44C *sub_1A3020(type_1F8560 *arg_0)
{
    static type_3E0F54 unk_4F6304;

    unk_4F6304.vf_004(arg_0);
    return &unk_4F6304;
}
// match: ?sub_1A30A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A30A0
type_3DA44C *sub_1A30A0(type_1F8560 *arg_0)
{
    static type_3DA434 unk_4F6318;

    unk_4F6318.vf_004(arg_0);
    return &unk_4F6318;
}
// match: ?sub_1A30F0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A30F0
type_3DA44C *sub_1A30F0(type_1F8560 *arg_0)
{
    static type_3E0F6C unk_4F632C;

    unk_4F632C.vf_004(arg_0);
    return &unk_4F632C;
}
// match: ?sub_1A3140@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3140
type_3DA44C *sub_1A3140(type_1F8560 *arg_0)
{
    static type_3E0F84 unk_4F6340;

    unk_4F6340.vf_004(arg_0);
    return &unk_4F6340;
}
// match: ?vf_008@type_3E0F90@@UAEHXZ @ 0x001A3190
// Its id (0x13).
RwInt32 type_3E0F90::vf_008()
{
    return 0x13;
}
// match: ?sub_1A31A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A31A0
type_3DA44C *sub_1A31A0(type_1F8560 *arg_0)
{
    static type_3E0F9C unk_4F6350;

    unk_4F6350.vf_004(arg_0);
    return &unk_4F6350;
}
// match: ?sub_1A31F0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A31F0
type_3DA44C *sub_1A31F0(type_1F8560 *arg_0)
{
    static type_3E0FB4 unk_4F65D8;

    unk_4F65D8.vf_004(arg_0);
    return &unk_4F65D8;
}
// match: ?vf_008@type_3E0FC0@@UAEHXZ @ 0x001A3240
// Its id (0x15).
RwInt32 type_3E0FC0::vf_008()
{
    return 0x15;
}
// match: ?sub_1A3250@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3250
type_3DA44C *sub_1A3250(type_1F8560 *arg_0)
{
    static type_3E0FCC unk_4F6600;

    unk_4F6600.vf_004(arg_0);
    return &unk_4F6600;
}
// match: ?vf_008@type_3E0FD8@@UAEHXZ @ 0x001A32A0
// Its id (0x14).
RwInt32 type_3E0FD8::vf_008()
{
    return 0x14;
}
// match: ?sub_1A32B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A32B0
// match: __ehhandler$?sub_1A32B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z-0xE @ 0x00302820
// match: __ehhandler$?sub_1A32B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x0030282E
type_3DA44C *sub_1A32B0(type_1F8560 *arg_0)
{
    static type_3E1E3C unk_4F6628;

    unk_4F6628.vf_004(arg_0);
    return &unk_4F6628;
}
// match: ?sub_1A3330@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3330
// match: __ehhandler$?sub_1A3330@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z-0xE @ 0x00302840
// match: __ehhandler$?sub_1A3330@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x0030284E
type_3DA44C *sub_1A3330(type_1F8560 *arg_0)
{
    static type_3E1FC4 unk_4F66F8;

    unk_4F66F8.vf_004(arg_0);
    return &unk_4F66F8;
}
// match: ?sub_1A33B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A33B0
type_3DA44C *sub_1A33B0(type_1F8560 *arg_0)
{
    static type_3E0FE4 unk_4F67C8;

    unk_4F67C8.vf_004(arg_0);
    return &unk_4F67C8;
}
// match: ?sub_1A3400@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3400
type_3DA44C *sub_1A3400(type_1F8560 *arg_0)
{
    static type_3E0FFC unk_4F67E0;

    unk_4F67E0.vf_004(arg_0);
    return &unk_4F67E0;
}
// match: ?sub_1A3450@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3450
type_3DA44C *sub_1A3450(type_1F8560 *arg_0)
{
    static type_3E1014 unk_4F67F0;

    unk_4F67F0.vf_004(arg_0);
    return &unk_4F67F0;
}
// match: ?sub_1A34A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A34A0
// match: __ehhandler$?sub_1A34A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z-0xE @ 0x00302860
// match: __ehhandler$?sub_1A34A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x0030286E
type_3DA44C *sub_1A34A0(type_1F8560 *arg_0)
{
    static type_3E102C unk_4F6804;

    unk_4F6804.vf_004(arg_0);
    return &unk_4F6804;
}
// match: ?sub_1A3550@@YAXIHPAUtype_1F8560@@@Z @ 0x001A3550
// Takes player arg_4's update numbered arg_0 from the stream arg_8 when it
// is newer than the last: reads it and applies it.
void sub_1A3550(RwUInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8)
{
    RwInt32 var_4 = arg_4;

    if (dword_4F6AB8[var_4] < arg_0)
    {
        unk_4F6B00[var_4].vf_004(arg_8);
        unk_4F6B00[var_4].sub_1A71E0();
        dword_4F6AB8[var_4] = arg_0;
    }
}
// match: ?sub_1A35B0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A35B0
type_3DA44C *sub_1A35B0(type_1F8560 *arg_0)
{
    static type_3E1044 unk_4F6828;

    unk_4F6828.vf_004(arg_0);
    return &unk_4F6828;
}
// match: ?sub_1A3600@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3600
type_3DA44C *sub_1A3600(type_1F8560 *arg_0)
{
    static type_3E0EB8 unk_4F6830;

    unk_4F6830.vf_004(arg_0);
    return &unk_4F6830;
}
// match: ?sub_1A3650@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3650
type_3DA44C *sub_1A3650(type_1F8560 *arg_0)
{
    static type_3E105C unk_4F6838;

    unk_4F6838.vf_004(arg_0);
    return &unk_4F6838;
}
// match: ?sub_1A36A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A36A0
type_3DA44C *sub_1A36A0(type_1F8560 *arg_0)
{
    static type_3E1074 unk_4F6840;

    unk_4F6840.vf_004(arg_0);
    return &unk_4F6840;
}
// match: ?sub_1A36F0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A36F0
type_3DA44C *sub_1A36F0(type_1F8560 *arg_0)
{
    static type_3E108C unk_4F6848;

    unk_4F6848.vf_004(arg_0);
    return &unk_4F6848;
}
// match: ?sub_1A3740@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3740
type_3DA44C *sub_1A3740(type_1F8560 *arg_0)
{
    static type_3E10A4 unk_4F6850;

    unk_4F6850.vf_004(arg_0);
    return &unk_4F6850;
}
// match: ?sub_1A3790@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3790
type_3DA44C *sub_1A3790(type_1F8560 *arg_0)
{
    static type_3E10BC unk_4F6858;

    unk_4F6858.vf_004(arg_0);
    return &unk_4F6858;
}
// match: ?sub_1A37E0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A37E0
type_3DA44C *sub_1A37E0(type_1F8560 *arg_0)
{
    static type_3E10D4 unk_4F6864;

    unk_4F6864.vf_004(arg_0);
    return &unk_4F6864;
}
// match: ?sub_1A3830@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3830
type_3DA44C *sub_1A3830(type_1F8560 *arg_0)
{
    static type_3E10EC unk_4F6870;

    unk_4F6870.vf_004(arg_0);
    return &unk_4F6870;
}
// match: ?sub_1A3880@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3880
type_3DA44C *sub_1A3880(type_1F8560 *arg_0)
{
    static type_3E1104 unk_4F6880;

    unk_4F6880.vf_004(arg_0);
    return &unk_4F6880;
}
// match: ?sub_1A38D0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A38D0
type_3DA44C *sub_1A38D0(type_1F8560 *arg_0)
{
    static type_3E111C unk_4F688C;

    unk_4F688C.vf_004(arg_0);
    return &unk_4F688C;
}
// match: ?sub_1A3950@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3950
type_3DA44C *sub_1A3950(type_1F8560 *arg_0)
{
    static type_3E1134 unk_4F68AC;

    unk_4F68AC.vf_004(arg_0);
    return &unk_4F68AC;
}
// match: ?sub_1A39A0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A39A0
type_3DA44C *sub_1A39A0(type_1F8560 *arg_0)
{
    static type_3E114C unk_4F68C0;

    unk_4F68C0.vf_004(arg_0);
    return &unk_4F68C0;
}
// match: ?sub_1A39F0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A39F0
type_3DA44C *sub_1A39F0(type_1F8560 *arg_0)
{
    static type_3E1164 unk_4F68D8;

    unk_4F68D8.vf_004(arg_0);
    return &unk_4F68D8;
}
// match: ?sub_1A3A70@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3A70
type_3DA44C *sub_1A3A70(type_1F8560 *arg_0)
{
    static type_3E117C unk_4F68FC;

    unk_4F68FC.vf_004(arg_0);
    return &unk_4F68FC;
}
// match: ?sub_1A3AC0@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3AC0
type_3DA44C *sub_1A3AC0(type_1F8560 *arg_0)
{
    static type_3E1194 unk_4F690C;

    unk_4F690C.vf_004(arg_0);
    return &unk_4F690C;
}
// match: ?sub_1A3B40@@YAPAUtype_3DA44C@@PAUtype_1F8560@@@Z @ 0x001A3B40
type_3DA44C *sub_1A3B40(type_1F8560 *arg_0)
{
    static type_3E11AC unk_4F6928;

    unk_4F6928.vf_004(arg_0);
    return &unk_4F6928;
}
