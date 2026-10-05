// The text manager (game/textmanager.h). The original file name is not in
// the image, so it is named for its start address.

#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "rw/rt2d.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/startup.h"
#include "game/textmanager.h"
#include "types/type_DC400.h"
#include "types/type_DA580.h"
#include "types/type_3D3548.h"
#include "types/type_8A980.h"
#include "types/CGlobalSounds.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D8E8C
extern const RwReal flt_3D8E8C = 16.666666f;
// 0x004B8EF4
#ifndef CODFH_PLAIN
RwV2d unk_4B8EF4;
#endif
// 0x004B8EFC
#ifndef CODFH_PLAIN
RwRGBA unk_4B8EFC;
#endif
// 0x004B8F00
#ifndef CODFH_PLAIN
RwRGBA unk_4B8F00;
#endif
// 0x004B8F04
#ifndef CODFH_PLAIN
RwRGBA unk_4B8F04;
#endif
// 0x004B8F08
#ifndef CODFH_PLAIN
RwReal flt_4B8F08;
#endif
// 0x004B9190
#ifndef CODFH_PLAIN
type_DC400 *dword_4B9190;
#endif
// 0x004B919C
#ifndef CODFH_PLAIN
RwChar path[132];
#endif
// 0x004B9220
bool byte_4B9220;
// 0x004B9224
RwInt32 dword_4B9224;
// 0x004B9228
type_DA580 *dword_4B9228;
// 0x004B922C
RwInt32 dword_4B922C;
// 0x004B9230
RwV2d unk_4B9230;
// 0x004B9238
RwReal dword_4B9238;
// 0x004B923C
type_EB0A0 *dword_4B923C[8];
// 0x004B9264
RwV2d unk_4B9264;
// 0x004B926C
type_EB0A0 *dword_4B926C[8];
// 0x004B9294
type_DA580 *dword_4B9294;
// 0x004B9298
RwInt32 dword_4B9298;
// 0x004B929C
RwReal dword_4B929C;
// 0x004B92A0
RwInt32 dword_4B92A0;
// 0x004B92A4
RwInt32 dword_4B92A4;
// 0x004B92A8
RwInt32 dword_4B92A8;
// 0x004B92AC
bool byte_4B92AC;
// 0x004B92AD
bool byte_4B92AD;
// 0x004B92AE
bool byte_4B92AE;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4B92B0;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8E8C@@3MB @ 0x003D8E8C
// match: ??_C@_03PCDPMMPO@t12?$AA@ @ 0x003D8E90
// match: ??_C@_04BMJJLDLC@?5?0?4?$DL?$AA@ @ 0x003D8E94
// match: ??_C@_0DD@FGDNNFAE@Failed?5to?5open?5text?5map?5for?5read@ @ 0x003D8E9C
// match: ??_C@_0BF@EPOGBBDF@textmanager?3?3console?$AA@ @ 0x003D8ED0
// match: .CRT$XCU+0 @ 0x00427050

// match: _$E2 @ 0x0030B520
// match: _$E3 @ 0x0030E4B0
// match: ?sub_EAA60@@YA_NXZ @ 0x000EAA60

bool sub_EAA60()
{
    RwInt32 var_4;

    sub_EB030();
    unk_4B9230.x = 0;
    unk_4B9230.y = 0;
    byte_4B92AC = false;
    dword_4B9228 = 0;
    for (var_4 = 0; var_4 < 10; var_4++)
    {
        dword_4B923C[var_4] = 0;
        dword_4B926C[var_4] = 0;
    }
    dword_4B9294 = 0;
    return true;
}

// match: ?sub_EAAE0@@YAXM@Z @ 0x000EAAE0
void sub_EAAE0(RwReal arg_0)
{
    if (byte_4B92AC)
    {
        sub_EB2D0(arg_0);
    }
}

// match: ?sub_EAB00@@YAXXZ @ 0x000EAB00
void sub_EAB00()
{
    sub_EB0D0();
}

// match: ?sub_EAB10@@YAXXZ @ 0x000EAB10
void sub_EAB10()
{
    sub_EB190();
    if (dword_4B9294)
    {
        delete dword_4B9294;
        dword_4B9294 = 0;
    }
}

// match: ?sub_EAB80@@YAXPBDHM@Z @ 0x000EAB80
void sub_EAB80(const RwChar *arg_0, RwInt32 arg_4, RwReal arg_8)
{
    if (dword_4B9190)
    {
        switch (arg_4)
        {
        case 1:
            dword_4B9190->sub_E7380(0xF, arg_0);
            break;
        case 3:
            dword_4B9190->sub_E7380(0x11, arg_0);
            break;
        case 2:
            dword_4B9190->sub_E7380(0x10, arg_0);
            break;
        case 4:
            dword_4B9190->sub_E7380(0x1B, arg_0);
            break;
        case 0:
            dword_4B9190->sub_E7380(2, arg_0);
            break;
        case 6:
            dword_4B9190->sub_E7380(0x81, arg_0);
            break;
        case 7:
            dword_4B9190->sub_E7380(9, arg_0);
            break;
        }
    }
}

// match: ?sub_EAC60@@YAXXZ @ 0x000EAC60
void sub_EAC60()
{
    dword_4E23A8 = 1;
    if (!dword_4B9294)
    {
        dword_4B9294 = type_DA580::sub_DA680("t12");
    }
    dword_4E23A8 = 0;
}

// match: ?sub_EACA0@@YAXPBDHH@Z @ 0x000EACA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EACA0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwChar local_34[0x30];
    RwChar *x4C;
    RwInt32 w48;
    RwInt32 loc44;
    RwChar *fp_40;
    RwInt32 ebp_3C;
    type_EB0A0 *lcl_38;

    memset(local_34, 0, 0x30);
    if (!byte_4B92AC)
    {
        return;
    }
    if (!arg_0)
    {
        return;
    }
    if (dword_4B92A8 < 7)
    {
        lcl_38 = (type_EB0A0 *)dword_4B92B0.sub_16C5A0(0);
        ebp_3C = strlen(arg_0);
        memset(lcl_38->unk_0E, 0, 0x30);
        strncpy(lcl_38->unk_0E, arg_0, ebp_3C > 47 ? 47 : ebp_3C);
        lcl_38->unk_00 = arg_4;
        lcl_38->unk_0D = (bool)arg_8;
        memset(lcl_38->unk_0E, 0, 0x30);
        if (ebp_3C > 47)
        {
            strncpy(local_34, arg_0, 47);
            w48 = 0;
            loc44 = 0;
            RwChar var_54[] = " ,.;";

            fp_40 = strtok(local_34, var_54);
            if (fp_40 != local_34)
            {
                fp_40 = strtok(0, var_54);
            }
            while (fp_40)
            {
                x4C = fp_40;
                if (w48 > 46)
                {
                    break;
                }
                loc44 = w48;
                w48 += strlen(fp_40);
                fp_40 = strtok(0, var_54);
                if (fp_40)
                {
                    w48 += fp_40 - (x4C + strlen(x4C));
                    if (w48 > 46)
                    {
                        w48 = 46;
                        break;
                    }
                }
            }
            if (loc44)
            {
                strncpy(lcl_38->unk_0E, arg_0, loc44);
                sub_EBDB0(lcl_38);
                if (!sub_EBCD0(lcl_38))
                {
                    dword_4B92B0.sub_16C710(lcl_38);
                }
                else
                {
                    byte_4B9220 = true;
                }
                sub_EACA0(arg_0 + loc44, arg_4, arg_8);
            }
        }
        else
        {
            strncpy(lcl_38->unk_0E, arg_0, ebp_3C);
            sub_EBDB0(lcl_38);
            if (!sub_EBCD0(lcl_38))
            {
                dword_4B92B0.sub_16C710(lcl_38);
            }
            else
            {
                byte_4B9220 = true;
            }
        }
    }
}

// Not in the image: a stand-in for a function the original object held here,
// which the link dropped (/OPT:REF) but whose literal stayed first: the text
// map reader's failure message sits between sub_EACA0's and sub_EAF30's literals
// (0x3D8E9C), before its user in unit_188380 (sub_18A890). Unreferenced.
void dropped_3D8E9C()
{
    printf("Failed to open text map for reading. Bailing out!\n");
}

// match: ?sub_EAF10@@YAXPAURwCamera@@@Z @ 0x000EAF10
void sub_EAF10(RwCamera *arg_0)
{
    if (!sub_17C630())
    {
        sub_EB770(arg_0);
    }
}

// match: ?sub_EAF30@@YAXXZ @ 0x000EAF30
void sub_EAF30()
{
    RwInt32 var_4;

    dword_4B92B0.sub_16C2C0(16, 0x40, "textmanager::console", 4, 1);
    unk_4B9264.x = 350.0f;
    unk_4B9264.y = 350.0f;
    unk_4B9230 = unk_4B9264;
    for (var_4 = 0; var_4 < 10; var_4++)
    {
        dword_4B923C[var_4] = 0;
        dword_4B926C[var_4] = 0;
    }
    sub_EB030();
    Rt2dFontSetPath(path);
    dword_4E23A8 = 1;
    if (dword_4B9190)
    {
        dword_4B9228 = dword_4B9190->unk_1A028;
        byte_4B92AD = false;
    }
    else
    {
        dword_4B9228 = type_DA580::sub_DA680("t10");
        if (dword_4B9228)
        {
            byte_4B92AD = true;
        }
    }
    dword_4E23A8 = 0;
    byte_4B92AC = true;
}

// match: ?sub_EB030@@YAXXZ @ 0x000EB030
void sub_EB030()
{
    dword_4B9298 = 0;
    dword_4B92A8 = 0;
    dword_4B92A0 = dword_4B9224 = 0;
    dword_4B922C = 0;
    dword_4B92A4 = 0;
    dword_4B9238 = 0.01f;
    dword_4B929C = 0;
    byte_4B9220 = false;
    byte_4B92AE = false;
}

// match: ?sub_EB0A0@@YAXPAUtype_EB0A0@@@Z @ 0x000EB0A0
void sub_EB0A0(type_EB0A0 *arg_0)
{
    arg_0->unk_0E[0] = 0;
    arg_0->unk_00 = -1;
    arg_0->unk_04 = -1.0f;
    arg_0->unk_0C = false;
}

// match: ?sub_EB0D0@@YAXXZ @ 0x000EB0D0
void sub_EB0D0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 8; var_4++)
    {
        if (dword_4B926C[var_4])
        {
            sub_EBE20(dword_4B926C[var_4]);
            dword_4B92B0.sub_16C710(dword_4B926C[var_4]);
            dword_4B926C[var_4] = 0;
        }
        if (dword_4B923C[var_4])
        {
            sub_EBE20(dword_4B923C[var_4]);
            dword_4B92B0.sub_16C710(dword_4B923C[var_4]);
            dword_4B923C[var_4] = 0;
        }
    }
    sub_EB030();
}

// match: ?sub_EB190@@YAXXZ @ 0x000EB190
void sub_EB190()
{
    RwInt32 var_4;

    if (!byte_4B92AC)
    {
        return;
    }
    for (var_4 = 0; var_4 < 8; var_4++)
    {
        if (dword_4B926C[var_4])
        {
            sub_EBE20(dword_4B926C[var_4]);
            dword_4B92B0.sub_16C710(dword_4B926C[var_4]);
            dword_4B926C[var_4] = 0;
        }
        if (dword_4B923C[var_4])
        {
            sub_EBE20(dword_4B923C[var_4]);
            dword_4B92B0.sub_16C710(dword_4B923C[var_4]);
            dword_4B923C[var_4] = 0;
        }
    }
    if (dword_4B9228)
    {
        if (byte_4B92AD)
        {
            delete dword_4B9228;
        }
        dword_4B9228 = 0;
    }
    dword_4B92B0.sub_16C4D0(1);
    byte_4B92AC = false;
}

// match: ?sub_EB2D0@@YAXM@Z @ 0x000EB2D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EB2D0(RwReal arg_0)
{
    type_3D3548 *lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (sub_1FF250() && sub_1FF250()->sub_200740())
    {
        return;
    }
    unk_4B9264 = unk_4B8EF4;
    dword_4B9238 = flt_4B8F08 * 1000.0f;
    dword_4B929C += arg_0 * flt_3D8E8C;
    for (bp_4 = 0; bp_4 < 8; bp_4++)
    {
        if (dword_4B926C[bp_4] && dword_4B926C[bp_4]->unk_0C)
        {
            dword_4B926C[bp_4]->unk_04 -= arg_0 * flt_3D8E8C;
            if (dword_4B926C[bp_4]->unk_04 <= 0.0f)
            {
                sub_EBE40(bp_4);
            }
        }
    }
    if (byte_4B9220 && dword_4B9298 < 8 && dword_4B929C >= dword_4B9238)
    {
        if (dword_4B922C == strlen(dword_4B923C[dword_4B92A0]->unk_0E))
        {
            sub_EBD20(0);
            dword_4B922C = 0;
            if (!dword_4B923C[dword_4B92A0])
            {
                byte_4B9220 = false;
            }
            if (dword_4B926C[dword_4B9298])
            {
                dword_4B926C[dword_4B9298]->unk_0C = true;
            }
            dword_4B9298++;
        }
        else
        {
            if (!dword_4B926C[dword_4B9298])
            {
                dword_4B926C[dword_4B9298] = (type_EB0A0 *)dword_4B92B0.sub_16C5A0(0);
                sub_EB0A0(dword_4B926C[dword_4B9298]);
                dword_4B926C[dword_4B9298]->unk_08 = dword_4B923C[dword_4B92A0]->unk_08;
                dword_4B926C[dword_4B9298]->unk_00 = dword_4B923C[dword_4B92A0]->unk_00;
                dword_4B926C[dword_4B9298]->unk_04 = dword_4B923C[dword_4B92A0]->unk_04;
                dword_4B926C[dword_4B9298]->unk_0C = false;
                dword_4B922C = 0;
            }
            dword_4B926C[dword_4B9298]->unk_0E[dword_4B922C] = dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C];
            dword_4B926C[dword_4B9298]->unk_0E[dword_4B922C + 1] = 0;
            if (dword_4B923C[dword_4B92A0]->unk_0D)
            {
                lv_10 = sub_1745A0(0);
                dword_4B1E98.sub_8A980(&dword_4B1B18, 0, 0, (RwV3d *)lv_10->vf_0C4(), 1, 0);
            }
            if (dword_4B926C[dword_4B9298]->unk_0E[dword_4B922C] == '$')
            {
                bp_8 = 0;
                do
                {
                    bp_8++;
                } while (dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C + bp_8]
                         && dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C + bp_8] != '$'
                         && dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C + bp_8] != ' ');
                if (dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C + bp_8]
                    && dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C + bp_8] == '$')
                {
                    for (slot_C = 0; slot_C <= bp_8; slot_C++)
                    {
                        dword_4B926C[dword_4B9298]->unk_0E[dword_4B922C] =
                            dword_4B923C[dword_4B92A0]->unk_0E[dword_4B922C];
                        dword_4B922C++;
                    }
                    dword_4B926C[dword_4B9298]->unk_0E[dword_4B922C + 1] = 0;
                }
                else
                {
                    dword_4B922C++;
                }
            }
            else
            {
                dword_4B922C++;
            }
        }
        dword_4B929C = 0;
    }
    if (byte_4B92AE)
    {
        sub_EACA0("Console initialized -- Standard Message", 0, 0);
        sub_EACA0("Console initialized -- High Level Message", 1, 0);
        sub_EACA0("Console initialized -- Low Level Message", 2, 0);
        byte_4B92AE = false;
    }
}

// match: ?sub_EB770@@YAXPAURwCamera@@@Z @ 0x000EB770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EB770(RwCamera *arg_0)
{
    const RwChar *q28;
    RwChar *frm_24;
    RwUInt32 loc20;
    RwChar l19;
    RwUInt32 l18;
    bool loc11;
    RwInt32 lv_10;
    void *slot_C;
    RwReal bp_8;
    void *bp_4;

    if (sub_1FF250() && sub_1FF250()->sub_200740())
    {
        return;
    }
    if (!dword_42926C)
    {
        return;
    }
    if (byte_4B92AC)
    {
        if (!dword_4B9228)
        {
            return;
        }
        bp_8 = 1.0f;
        if (dword_4CF9A8)
        {
            bp_8 = 1.3333f;
        }
        RwCameraBeginUpdate(arg_0);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &slot_C);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &bp_4);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
        Rt2dCTMPush();
        Rt2dCTMSetIdentity();
        Rt2dCTMScale(1.0f / (RwReal)(RwUInt32)Height * dword_4B8970, 1.0f / (RwReal)(RwUInt32)Height);
        unk_4B9230.x = (RwReal)(RwUInt32)Height * unk_4B9264.x / (RwReal)(RwUInt32)Width * bp_8;
        unk_4B9230.y = unk_4B9264.y;
        unk_4B9230.x = unk_4B9264.x * bp_8;
        unk_4B9230.y = unk_4B9264.y;
        unk_4B9230.x = unk_4B9230.x * dword_4B8970;
        for (lv_10 = 0; lv_10 < 8; lv_10++)
        {
            if (dword_4B926C[lv_10])
            {
                frm_24 = dword_4B926C[lv_10]->unk_0E;
                loc20 = 0;
                l18 = 0;
                loc11 = false;
                if (!dword_4B926C[lv_10]->unk_0C)
                {
                    loc11 = true;
                }
                while (frm_24[loc20] && strlen(frm_24) > loc20)
                {
                    if (loc11)
                    {
                        q28 = &dword_4B923C[dword_4B92A0]->unk_0E[loc20];
                    }
                    else
                    {
                        q28 = frm_24 + loc20;
                    }
                    l18 = dword_4B9228->sub_DB180(q28, (RwReal)(RwUInt32)Height - unk_4B9230.x, 0.0f) + loc20;
                    l19 = frm_24[l18];
                    frm_24[l18] = 0;
                    dword_4B9228->sub_DAB00(frm_24 + loc20, &unk_4B9230, dword_4B926C[lv_10]->unk_08, 0.0f, 0);
                    unk_4B9230.x = (RwReal)(RwUInt32)Height * unk_4B9264.x / (RwReal)(RwUInt32)Width * bp_8;
                    unk_4B9230.x = (unk_4B9230.x = unk_4B9264.x * bp_8) * dword_4B8970;
                    unk_4B9230.y -= dword_4B9228->sub_DA790();
                    frm_24[l18] = l19;
                    loc20 = l18;
                    while (frm_24[loc20] == ' ')
                    {
                        loc20++;
                    }
                }
            }
        }
        Rt2dCTMPop();
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, slot_C);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, bp_4);
        RwCameraEndUpdate(arg_0);
    }
}

// match: ?sub_EBAE0@@YAXPAURwCamera@@PBDPAURwV2d@@PAUtype_DA580@@MMM@Z @ 0x000EBAE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EBAE0(RwCamera *arg_0, const RwChar *arg_4, RwV2d *arg_8, type_DA580 *arg_C, RwReal arg_10,
               RwReal arg_14, RwReal arg_18)
{
    RwV2d l1C;
    void *ebp_14;
    void *lv_10;
    void *slot_C;
    type_DA580 *bp_8;
    RwRGBA bp_4;

    if (!arg_4 || !arg_0 || !dword_4B9228)
    {
        return;
    }
    l1C = unk_4B9264;
    bp_8 = arg_C;
    if (arg_8)
    {
        l1C = *arg_8;
    }
    if (!bp_8)
    {
        bp_8 = dword_4B9228;
    }
    bp_4.alpha = 0xFF;
    bp_4.blue = 0xFF;
    bp_4.green = 0xFF;
    bp_4.red = 0xFF;
    if (arg_10 >= 0.0f && arg_14 >= 0.0f && arg_18 >= 0.0f)
    {
        bp_4.red = (RwUInt8)(arg_10 * 255.0f);
        bp_4.green = (RwUInt8)(arg_14 * 255.0f);
        bp_4.blue = (RwUInt8)(arg_18 * 255.0f);
        bp_4.alpha = 0xFF;
    }
    RwCameraBeginUpdate(arg_0);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &ebp_14);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &lv_10);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &slot_C);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    Rt2dCTMPush();
    Rt2dCTMSetIdentity();
    Rt2dCTMScale(1.0f / (RwReal)(RwUInt32)Height * dword_4B8970, 1.0f / (RwReal)(RwUInt32)Height);
    l1C.x /= dword_4B8970;
    bp_8->sub_DAB00(arg_4, &l1C, &bp_4, 0.0f, 0);
    Rt2dCTMPop();
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, ebp_14);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, lv_10);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, slot_C);
    RwCameraEndUpdate(arg_0);
}

// match: ?sub_EBCD0@@YA_NPAUtype_EB0A0@@@Z @ 0x000EBCD0
bool sub_EBCD0(type_EB0A0 *arg_0)
{
    if (dword_4B92A8 != 8)
    {
        dword_4B923C[(dword_4B92A8 + dword_4B92A0) % 8] = arg_0;
        dword_4B92A8++;
        return true;
    }
    return false;
}

// match: ?sub_EBD20@@YAXH@Z @ 0x000EBD20
void sub_EBD20(RwInt32 arg_0)
{
    if (dword_4B92A8 > 0)
    {
        if (arg_0)
        {
            sub_EBE20(dword_4B923C[dword_4B92A0]);
        }
        dword_4B92B0.sub_16C710(dword_4B923C[dword_4B92A0]);
        dword_4B923C[dword_4B92A0] = 0;
        dword_4B92A8--;
        dword_4B92A0++;
        if (dword_4B92A0 == 8)
        {
            dword_4B92A0 = 0;
        }
    }
}

// match: ?sub_EBDB0@@YAXPAUtype_EB0A0@@@Z @ 0x000EBDB0
void sub_EBDB0(type_EB0A0 *arg_0)
{
    arg_0->unk_0C = false;
    switch (arg_0->unk_00)
    {
    case 0:
        arg_0->unk_08 = &unk_4B8EFC;
        arg_0->unk_04 = 5000.0f;
        break;
    case 1:
        arg_0->unk_08 = &unk_4B8F04;
        arg_0->unk_04 = 7000.0f;
        break;
    case 2:
        arg_0->unk_08 = &unk_4B8F00;
        arg_0->unk_04 = 3000.0f;
        break;
    }
}

// match: ?sub_EBE20@@YAXPAUtype_EB0A0@@@Z @ 0x000EBE20
void sub_EBE20(type_EB0A0 *arg_0)
{
    sub_EB0A0(arg_0);
}

// match: ?sub_EBE40@@YAXH@Z @ 0x000EBE40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_EBE40(RwInt32 arg_0)
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    sub_EBE20(dword_4B926C[arg_0]);
    dword_4B92B0.sub_16C710(dword_4B926C[arg_0]);
    dword_4B926C[arg_0] = 0;
    for (bp_4 = arg_0; bp_4 < 7; bp_4++)
    {
        dword_4B926C[bp_4] = dword_4B926C[bp_4 + 1];
        if (dword_4B9298 == bp_4 + 1)
        {
            dword_4B9298 = bp_4;
        }
        dword_4B926C[bp_4 + 1] = 0;
    }
    if (dword_4B9298 >= 8)
    {
        for (bp_8 = 7; bp_8 >= 0; bp_8--)
        {
            if (!dword_4B926C[bp_8])
            {
                dword_4B9298 = bp_8;
                break;
            }
        }
    }
}
