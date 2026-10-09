// The front end: its world and camera around the shell's screens. The
// original file name is not in the image, so it is named for its start
// address.

#ifdef CODFH_SP
#include "game/xboxlive.h"
#endif
#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rw/baengine.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/startup.h"
#include "game/frontend.h"
#include "types/type_4B8EF0.h"
#include "types/soundbank.h"
#if defined(CODFH_SP) && defined(CODFH_WIN32)
extern "C" void port_cli_frame(void);
#endif
#ifdef CODFH_SP
#include <string.h>
#include "rw/baframe.h"
#include "rw/batextur.h"
#include "game/waitscreen.h"
#include "game/movie.h"
#include "types/type_DA580.h"
#include "types/type_3DF8D8.h"
#include "game/cheats.h"
#include "game/debugtext.h"
#include "game/pak.h"
#include "sp/sp_fend.h"
#include "sp/sp_launch.h"
#include "game/profiles.h"
#include "game/savestate.h"
#include "game/uiglue.h"
#include "types/type_DC400.h"
#endif

#if !defined(CODFH_SP) || CODFH_SP_PART != 2 // single player compiles the slide show and the attract movie
                                             // in another file (src/sp/units/sp_unit_0DA290_2.cpp)
// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7E80
extern const RwReal flt_3D7E80 = 16.666666f;
// 0x003D7E84
extern const RwReal flt_3D7E84 = 16.666666f;
// 0x004B889C
RwInt32 dword_4B889C;
// 0x004B88B0
RwCamera *dword_4B88B0;
// 0x004B88B8
bool byte_4B88B8;
// 0x004B8920
bool byte_4B8920;
// 0x004B8924
#ifdef CODFH_SP // a float in single player (include/game/frontend.h)
RwReal dword_4B8924;
#else
RwInt32 dword_4B8924;
#endif
// 0x004B9E48
#ifndef CODFH_PLAIN
RwInt32 dword_4B9E48;
#endif
// 0x004B9E54
#ifndef CODFH_PLAIN
RwInt32 dword_4B9E54;
#endif
// 0x004F61F0
bool byte_4F61F0;
// 0x004F61F1
bool byte_4F61F1;
#ifdef CODFH_SP // single player's own front-end state (.bss): its loop, step, slide show and attract movie
// SP 0x003B4720
bool sp_byte_3B4720;                    // set: the screen is not shown for some steps
// SP 0x003B4724
type_sp_AE5D0 *sp_dword_3B4724;         // the main menu
// SP 0x003B4728
type_DA580 *sp_dword_3B4728;            // the pad shell's
// SP 0x003B4738
RwInt32 sp_dword_3B4738;                // set once Live was polled
// SP 0x003B473C
bool sp_byte_3B473C;                    // set: the language screen is shown first
// SP 0x003B4740
RwInt32 sp_dword_3B4740;                // the front end's steps
// SP 0x003B4744
RwInt32 sp_dword_3B4744;                // steps left without showing the screen
// SP 0x003B4748
RwInt32 sp_dword_3B4748;                // steps since the background movie started
// SP 0x003B474C
bool sp_byte_3B474C;                    // the background movie plays
// SP 0x003B4750
RwReal sp_flt_3B4750;                   // the time the slide has been shown
// SP 0x003B4754
RwReal sp_flt_3B4754;                   // the time a slide is shown (120)
// SP 0x003B4758
RwLLLink *sp_dword_3B4758;              // the slide shown: a texture's link
// SP 0x003B475C
RwTexDictionary *sp_dword_3B475C;       // the slide show's dictionary
// SP 0x003B4760
RwLLLink *sp_dword_3B4760;              // the slide fading out
// SP 0x003B4764
RwInt32 sp_dword_3B4764;                // set: the show does not advance itself
// SP 0x003B4768
RwReal sp_flt_3B4768;                   // the fade's time (30)
// SP 0x003B4770
RwChar sp_byte_3B4770[64];              // the attract movie's name
// SP 0x003B47B1
bool sp_byte_3B47B1;                    // set: the attract movie is on
// SP 0x003B47B8
bool sp_byte_3B47B8;                    // set once it has played
// SP 0x003B4820
bool sp_byte_3B4820;                    // asked: start the background movie
// SP 0x003B4821
bool sp_byte_3B4821;                    // asked: stop it
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7E80@@3MB @ 0x003D7E80
// match: ?flt_3D7E84@@3MB @ 0x003D7E84
// match: ??_C@_0DO@KPAEBBN@MEMORY?5LEAK?5detected?5during?5fron@ @ 0x003D7E88
// match: ??_C@_0BO@FDEIDOLC@GameFrontEnd?5Shutdown?5end?4?4?4?4?$AA@ @ 0x003D7EC8
// match: ??_C@_0DA@JOPIEECP@Shutdown?3?5Memory?5freed?5on?5RwFree@ @ 0x003D7EE8
// match: ??_C@_0CN@LNCOCMHJ@GameFrontEnd?5world?5is?5not?5empty?5@ @ 0x003D7F18
// match: ??_C@_0DI@HHJOEDGB@GameFrontEndInit?3?5Memory?5freed?5o@ @ 0x003D7F48
// match: ??_C@_0CG@BFICBGMM@GameFrontEnd?5Initialization?5begi@ @ 0x003D7F80

#ifdef CODFH_SP
// Single player's front-end loop state (SP .bss, its own; paired later).
extern RwInt32 sp_dword_3B4718;         // the pad pressed a button this step
extern RwInt32 sp_dword_3B54C8;
extern RwInt32 dword_42926C;

// Shows message 0x2C (no profile can be saved) once the front end has run
// five steps with dword_4B9E54 set and dword_42926C clear, and takes it
// down otherwise; then, with arg_0, updates the messages.
// sp-match: ?sp_sub_A4ED0@@YAXH@Z @ 0x000A4ED0
void sp_sub_A4ED0(RwInt32 arg_0)
{
    if (sp_dword_3B4740 > 5 && !dword_42926C && dword_4B9E54)
    {
        if (!sub_186F20(0x2C))
        {
            sub_186E70(0x2C, 0, 0);
            dword_4B88AC = 1;
        }
    }
    else if (sub_186F20(0x2C))
    {
        sub_186F80(0x2C, 1);
        dword_4B88AC = 0;
    }
    if (arg_0)
    {
        sub_187B30();
    }
}
#endif

#ifdef CODFH_SP
// The language screen's and the profile name editor's implicit destructors
// (sp_sub_A5780's and sp_sub_A55F0's unwinding calls them, SP 0x21ABA6,
// 0x21ABC6): both only run type_sp_AD970's, folded by /OPT:ICF.
// sp-match: ??1type_sp_AD730@@QAE@XZ @ 0x000A4F50
#endif

#ifdef CODFH_SP
// Runs the sound for half a second's worth of steps (30 at 1 a step).
// sp-match: ?sp_sub_A4F60@@YAXXZ @ 0x000A4F60
void sp_sub_A4F60()
{
    RwReal t;

    t = 0.0f;
    do
    {
        RwaCoreUpdate();
        sub_85090(deltaTime, 0);
        RwaCoreUpdate();
        RtFSManagerSyncAllFiles();
        t += deltaTime;
        sub_19A750();
    } while (t <= 30.000002f);
}
#endif

#ifdef CODFH_SP
// Draws the Live prompts over the front end on the camera arg_0: the
// pad's when it pressed a button, and the second when sp_dword_3B54C8 is
// set.
// sp-match: ?sp_sub_A4FB0@@YAXPAURwCamera@@PAUtype_DA580@@@Z @ 0x000A4FB0
void sp_sub_A4FB0(RwCamera *arg_0, type_DA580 *arg_4)
{
    RwCameraBeginUpdate(arg_0);
    if (sp_dword_3B4718)
    {
        RwV2d text;
        RwV2d button;

        text.x = 40.0f;
        text.y = 349.0f;
        button.x = 12.0f;
        button.y = 352.0f;
        dword_4F3130.sp_sub_12BE30(arg_0, &text, 0, 0, &button, 0, 0, 1);
    }
    if (sp_dword_3B54C8)
    {
        RwRGBA color;
        RwV2d text;
        RwV2d button;

        color.red = 10;
        color.green = 10;
        color.blue = 10;
        text.x = 90.0f;
        text.y = 330.0f;
        button.x = 64.0f;
        button.y = 332.0f;
        color.alpha = 255;
        dword_4F3130.sp_sub_12BE30(arg_0, &text, 0, &color, &button, 0, &color, 1);
    }
    dword_4F3130.sp_sub_12A970();
    RwCameraEndUpdate(arg_0);
}

// Single player's front end draws a full-screen picture through the raster
// arg_4 at alpha arg_8 (SP 0xA5080), for its slide show of a texture
// dictionary's textures (SP 0xA5E60 on).
// (The first vertex's z is set before the reciprocal, the others' after x and
// y: SP 0xA5098 loads it first; the nine saved render states are block-scoped:
// their stack slots, SP 0xA5165.)
// sp-match: ?sp_sub_A5080@@YAXPAURwCamera@@PAURwRaster@@H@Z @ 0x000A5080
void sp_sub_A5080(RwCamera *arg_0, RwRaster *arg_4, RwInt32 arg_8)
{
    RwIm2DVertex v[4];
    RwReal recip_z;
    RwUInt32 color;

    if (!arg_0 || !RwCameraBeginUpdate(arg_0))
    {
        return;
    }
    RwIm2DVertexSetScreenZ(&v[0], RwIm2DGetNearScreenZ());
    recip_z = 1.0f / RwCameraGetNearClipPlane(arg_0);
    color = (arg_8 << 24) | 0xFFFFFF;
    RwIm2DVertexSetScreenX(&v[0], 0.0f);
    RwIm2DVertexSetScreenY(&v[0], 0.0f);
    RwIm2DVertexSetRecipCameraZ(&v[0], recip_z);
    RwIm2DVertexSetU(&v[0], 0.0f, recip_z);
    RwIm2DVertexSetV(&v[0], 0.0f, recip_z);
    v[0].emissiveColor = color;
    RwIm2DVertexSetScreenX(&v[1], 0.0f);
    RwIm2DVertexSetScreenY(&v[1], (RwReal)(RwUInt32)Height);
    RwIm2DVertexSetScreenZ(&v[1], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&v[1], recip_z);
    RwIm2DVertexSetU(&v[1], 0.0f, recip_z);
    RwIm2DVertexSetV(&v[1], 1.0f, recip_z);
    v[1].emissiveColor = color;
    RwIm2DVertexSetScreenX(&v[2], (RwReal)(RwUInt32)Width);
    RwIm2DVertexSetScreenY(&v[2], 0.0f);
    RwIm2DVertexSetScreenZ(&v[2], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&v[2], recip_z);
    RwIm2DVertexSetU(&v[2], 1.0f, recip_z);
    RwIm2DVertexSetV(&v[2], 0.0f, recip_z);
    v[2].emissiveColor = color;
    RwIm2DVertexSetScreenX(&v[3], (RwReal)(RwUInt32)Width);
    RwIm2DVertexSetScreenY(&v[3], (RwReal)(RwUInt32)Height);
    RwIm2DVertexSetScreenZ(&v[3], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&v[3], recip_z);
    RwIm2DVertexSetU(&v[3], 1.0f, recip_z);
    RwIm2DVertexSetV(&v[3], 1.0f, recip_z);
    v[3].emissiveColor = color;
    {
        void *filter;
        void *fog;
        void *address;
        void *src_blend;
        void *ztest;
        void *vertex_alpha;
        void *zwrite;
        void *raster;
        void *dest_blend;

        raster = 0;
        RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &raster);
        RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &filter);
        RwRenderStateGet(rwRENDERSTATEFOGENABLE, &fog);
        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &ztest);
        RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &zwrite);
        RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &address);
        RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &vertex_alpha);
        RwRenderStateGet(rwRENDERSTATESRCBLEND, &src_blend);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dest_blend);
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)arg_4);
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
        RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, v, 4);
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, filter);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, fog);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, ztest);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, zwrite);
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster);
        RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, address);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, vertex_alpha);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, src_blend);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, dest_blend);
    }
    RwCameraEndUpdate(arg_0);
}

// Single player's front-end step state (SP .bss and .data, its own).
extern type_DA580 *sp_dword_3B481C;     // the front end's font
void sub_187150(RwInt32 arg_0);
extern RwInt32 sp_dword_3B66AC;
void sp_sub_A6140(RwReal arg_0);
void sp_sub_A4FB0(RwCamera *arg_0, type_DA580 *arg_4);
void sp_sub_B1D40(const RwChar *arg_0, bool arg_4);
void sp_sub_B1B20();
void sp_sub_B1A50(RwCamera *arg_0);
void sp_sub_B1A10();
RwInt32 sp_sub_12A630();

// A step of single player's front end on the camera arg_0: the clock, the
// attract movie, the sound, the background movie (started and stopped on
// request), the main menu's draw and the Live prompts, the screen shown,
// the pads, and the no-profile message or the main menu's step.
// (Whether the no-profile message is up is kept in a flag: the image lays the
// main menu's step out after the shared sp_sub_B1A10 block, SP 0xA5560.)
// sp-match: ?sp_sub_A5340@@YAXPAURwCamera@@@Z @ 0x000A5340
void sp_sub_A5340(RwCamera *arg_0)
{
    bool stop;
    bool show;
    bool msg;

    sub_D9620();
    sp_sub_A6140(deltaTime);
    sub_19A750(deltaTime);
    sub_85090(deltaTime, 0);
    sub_857B0(deltaTime);
    sub_19A750();
    sp_dword_3B4740++;
    if (sp_byte_3B4820)
    {
        stop = sp_byte_3B4821;
        if (stop)
        {
            sp_byte_3B4820 = false;
            if (!sp_byte_3B474C)
            {
                sp_byte_3B4821 = false;
                stop = false;
            }
        }
        else
        {
            sp_byte_3B474C = true;
            RwaCoreUpdate();
            sp_sub_B1D40("fend.bik", true);
            sp_dword_3B4748 = 0;
        }
    }
    else
    {
        stop = sp_byte_3B4821;
    }
    if (stop)
    {
        sp_byte_3B4821 = false;
        sp_byte_3B474C = false;
        sp_sub_B1B20();
    }
    show = true;
    if (sp_byte_3B474C)
    {
        if (sp_byte_3B4720 && ++sp_dword_3B4748 >= 10)
        {
            sp_byte_3B4720 = false;
        }
        if (!dword_4F3130.unk_20 || sp_dword_3B66AC)
        {
            sp_sub_B1A50(arg_0);
        }
    }
    else if (sp_dword_3B4744)
    {
        sp_dword_3B4744--;
        show = false;
    }
    if (unk_4292B4.unk_0C > 0)
    {
        unk_4292B4.unk_0C--;
    }
    else
    {
        sp_dword_3B4724->sp_sub_AE7A0(arg_0);
    }
    flt_4292C8 = 1.8f;
    sub_187150((RwInt32)arg_0);
    flt_4292C8 = 1.0f;
    sp_sub_A4FB0(arg_0, sp_dword_3B481C);
    if (!sp_byte_3B4720)
    {
        if (sp_byte_3B4820)
        {
            sp_byte_3B4820 = false;
        }
        else if (show)
        {
            RwCameraShowRaster(arg_0, 0, 1);
        }
    }
    unk_4B9308.sub_EE6D0();
    if (!sp_dword_3B4738)
    {
        sp_dword_3B4738 = 1;
        sp_sub_12A630();
    }
    if (sp_dword_3B4740 > 5 && sp_dword_3B66AC && dword_4B9E54)
    {
        if (!sub_186F20(0x2C))
        {
            sub_186E70(0x2C, 0, 0);
        }
        msg = true;
    }
    else if (sub_186F20(0x2C))
    {
        if (!sp_dword_3B66AC)
        {
            sub_186F80(0x2C, 1);
        }
        msg = true;
    }
    else
    {
        msg = false;
    }
    if (!msg)
    {
        sp_dword_3B4724->sp_sub_AF7A0(deltaTime);
    }
    else if (sp_byte_3B474C)
    {
        sp_sub_B1A10();
    }
#ifdef CODFH_WIN32
    // Run pending SP command-line level selection from the live front-end frame.
    port_cli_frame();
#endif
    if (dword_4B88AC)
    {
        sub_187B30();
    }
}
#endif

#ifdef CODFH_SP
// Shuts single player's front end down: the main menu, the messages, the
// background movie, the pad shell's font, the fonts, the pads and the sound.
// sp-match: ?sp_sub_A5580@@YAXXZ @ 0x000A5580
void sp_sub_A5580()
{
    sp_dword_3B4724->sp_sub_AE7D0();
    sub_1868E0();
    sp_sub_B1B20();
    delete sp_dword_3B4728;
    sp_dword_3B4728 = 0;
    dword_4B8EF0.sub_E99E0();
    sub_835E0();
    sub_198580();
    sub_19A750();
    sub_83B40();
    sub_83DE0(0);
    sp_sub_AE5A0();
}
#endif

#ifdef CODFH_SP
// The profile name editor (profile.anm) on the camera arg_0 for the slot
// arg_4 of the memory unit arg_8, run until it is done (it draws the
// messages over it); 1 when it was left with B. arg_C is not read.
// sp-match: ?sp_sub_A55F0@@YAHPAURwCamera@@HPAUtype_D9CF0@@H@Z @ 0x000A55F0
RwInt32 sp_sub_A55F0(RwCamera *arg_0, RwInt32 arg_4, type_D9CF0 *arg_8, RwInt32 arg_C)
{
    RwRGBA color;
    type_sp_B2110 screen;

    color.green = 0;
    color.blue = 0;
    color.red = 0;
    color.alpha = 255;
    screen.sp_sub_B2750(arg_4, arg_8, arg_0, 0);
    screen.sp_sub_B2810("shell\\fend\\profile.anm", "SHELL\\FEND\\INSTANCE\\XBOX\\PROFILE.TXD", 0);
    while (!screen.unk_04)
    {
        sub_D9620();
        unk_4B9308.sub_EE6D0();
        sp_sub_A4ED0(1);
        RwaCoreUpdate();
        sub_85090(deltaTime, 0);
        RwaCoreUpdate();
        RtFSManagerSyncAllFiles();
        if (dword_42926C)
        {
            screen.sp_sub_B2110(deltaTime);
        }
        sub_19A750();
        RwCameraClear(arg_0, &color, rwCAMERACLEARIMAGE | rwCAMERACLEARZ);
        screen.sp_sub_AD750(arg_0);
        sub_187150((RwInt32)arg_0);
        RwRasterShowRaster(RwCameraGetRaster(arg_0), 0, 1);
    }
    screen.sp_sub_AE7D0();
    return screen.unk_1DC;
}
#endif

#ifdef CODFH_SP
// The language screen (language.anm, its fonts from arg_4) on the camera
// arg_0, run until a language is chosen; then the sound is run out.
// sp-match: ?sp_sub_A5780@@YAXPAURwCamera@@PAURwTexDictionary@@@Z @ 0x000A5780
void sp_sub_A5780(RwCamera *arg_0, RwTexDictionary *arg_4)
{
    type_sp_AD730 screen;

    screen.sp_sub_AD730();
    screen.sp_sub_AD8C0("shell\\fend\\language.anm", "SHELL\\FEND\\INSTANCE\\XBOX\\LANGUAGE.TXD", arg_4);
    while (!screen.unk_04)
    {
        RwRGBA color;

        sub_D9620();
        unk_4B9308.sub_EE6D0();
        RwaCoreUpdate();
        sub_85090(deltaTime, 0);
        RwaCoreUpdate();
        RtFSManagerSyncAllFiles();
        screen.sp_sub_AD740(deltaTime);
        sub_19A750();
        color.green = 0;
        color.blue = 0;
        color.red = 0;
        color.alpha = 255;
        RwCameraClear(arg_0, &color, rwCAMERACLEARIMAGE | rwCAMERACLEARZ);
        screen.sp_sub_AD750(arg_0);
        RwRasterShowRaster(RwCameraGetRaster(arg_0), 0, 1);
    }
    screen.sp_sub_AE7D0();
    sp_sub_A4F60();
}
#endif

#ifdef CODFH_SP
RwUInt8 sp_sub_129230();
void sp_sub_129240(RwUInt8 arg_0);

// Before the main menu on the camera arg_0: the company movies (not when
// the multiplayer image launched it, which hands over the profile slot to
// load instead), the profiles, the language screen, the main menu's first
// screen and the intro movie.
// sp-match: ?sp_sub_A58C0@@YAXPAURwCamera@@@Z @ 0x000A58C0
void sp_sub_A58C0(RwCamera *arg_0)
{
#if !defined(CODFH_WIN32)
    if (!((sp_type_3EC3B0 *)dword_4F45F8)->unk_10)
    {
        sub_E8AC0("atvi.bik", (RwInt32)arg_0, 0, 0);
        sub_E8AC0("spark.bik", (RwInt32)arg_0, 0, 0);
        sub_E8AC0("kuju.bik", (RwInt32)arg_0, 0, 0);
    }
#endif
    dword_4B88AC = 0;
    if (sub_1A1790(0))
    {
        sub_1A1D40();
    }
    if (((sp_type_3EC3B0 *)dword_4F45F8)->unk_10)
    {
        if (dword_4F5A30)
        {
            sub_1A2680(dword_4F45F8);
        }
        unk_4B8744.sp_sub_A4CA0(((sp_type_3EC3B0 *)dword_4F45F8)->unk_14);
        dword_4F28F0->unk_44 = ((sp_type_3EC3B0 *)dword_4F45F8)->unk_14;
    }
    if (sp_byte_3B473C)
    {
        sp_sub_A5780(arg_0, sp_dword_3B4724->unk_184);
    }
    sub_186880(0);
    sp_dword_3B4724->sp_sub_AF7F0();
#if !defined(CODFH_WIN32)
    if (!((sp_type_3EC3B0 *)dword_4F45F8)->unk_10)
    {
        sub_E8AC0("Intro.bik", (RwInt32)arg_0, 0, 0);
    }
#endif
    sp_sub_129240(0);
}
#endif

#ifdef CODFH_SP
extern type_44C4E8 *sp_dword_3EC3E4;    // the front end's music
void sp_sub_A60B0();
bool sp_sub_B34A0();
void sp_sub_A6BF0(const RwChar *arg_0);

// Sets single player's front end up on the camera arg_0: the fonts, the main
// menu (fend.anm), the timers, the god assets, the pads, the pad shell's
// font and textures, the sound and the music; then the screens before the
// main menu, or the main menu's first screen.
// sp-match: ?sp_sub_A59D0@@YAXPAURwCamera@@@Z @ 0x000A59D0
void sp_sub_A59D0(RwCamera *arg_0)
{
    RwV3d position;

    sp_byte_3B4720 = false;
    sp_byte_3B473C = false;
    if (sp_sub_129230())
    {
        sp_byte_3B473C = false;
    }
    if (!((sp_type_3EC3B0 *)dword_4F45F8)->unk_10)
    {
        sub_EA560(arg_0);
    }
    sub_19AD20();
    sp_sub_B34A0();
    sp_sub_AE0B0();
    sp_sub_16BE90(sp_sub_ADF80);
    dword_4B8EF0.sub_E9790(1, (RwInt32)arg_0);
    sp_dword_3B4724 = new type_sp_AE5D0;
    sp_dword_3B4724->sp_sub_AE5D0(arg_0);
    sp_sub_A60B0();
    sub_D95A0();
    sub_198390();
    sub_83280();
    if (!dword_4B9E48)
    {
        unk_4B9308.sub_EE590();
    }
    unk_4B9308.sp_sub_B6DC0();
    sp_dword_3B4724->sp_sub_AE7E0("shell\\fend\\fend.anm", "SHELL\\FEND\\INSTANCE\\XBOX\\FEND.TXD",
                                  "SHELL\\FEND\\INSTANCE\\XBOX\\F_FEND.TXD");
    sp_dword_3B4728 = type_DA580::sub_DA680("t12");
    sp_sub_A6BF0("SHELL\\PAD\\PADSHELL.TXD");
    sub_186720();
    sub_186970(sp_dword_3B4728);
    type_825E0 bank;
    type_825E0_id id;
    id.unk_00 = 0x5F7D7350;
    id.unk_04 = 0x1035E68B;
    bank.unk_00 = id;
    bank.unk_08 = 0;
    bank.unk_0C = 0x28;
    sub_82C70(&bank, 0);
    dword_44E720[7] = 4;
    dword_44E720[6] = 4;
    dword_44E720[5] = 4;
    dword_44E720[4] = 4;
    dword_44E720[3] = 4;
    dword_44E720[2] = 4;
    dword_44E720[1] = 4;
    dword_44E720[0] = 4;
    sub_83B20();
    position.x = position.y = position.z = 0;
    do
    {
        dword_44E8AC->unk_28 = position;
        dword_44E8AC->unk_70 |= 1;
    } while (0);
    type_3DF8D8_04 key(0x06D62AE9, 0x00C7F591); // not an address: a key
    sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
    if (sp_sub_129230())
    {
        sp_sub_A58C0(arg_0);
    }
    else
    {
        sub_186880(0);
        sp_dword_3B4724->sp_sub_AF7F0();
        sub_82500();
        sp_dword_3B4724->sp_sub_AFCA0();
    }
    if (((sp_type_3EC3B0 *)dword_4F45F8)->unk_10)
    {
        if (((sp_type_3EC3B0 *)dword_4F45F8)->unk_00)
        {
            dword_4F3130.sp_sub_12BB50(0, 0);
        }
        else
        {
            dword_4F3130.sp_sub_12BB50(1, ((sp_type_3EC3B0 *)dword_4F45F8)->unk_0C);
        }
        dword_4F28F0->unk_58 = 1;
        unk_4B9308.sp_sub_B6A10(((sp_type_3EC3B0 *)dword_4F45F8)->unk_24);
        sub_82500();
        sp_dword_3B4724->sp_sub_AFCA0();
    }
}
#endif

#ifndef CODFH_SP // MP only: multiplayer's frame (single player runs its own, SP 0xA5C90: sp_sub_A5C90 above); no twin in config/sp/shared.txt
// match: ?sub_DA290@@YAXXZ @ 0x000DA290

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_DA290()
{
    RpWorld *var_C;
    RwCamera *bp_8;
    RwInt32 bp_4;

    sub_19A750(" ");
    sub_19A750(" ");
    sub_19A750("******************************************");
    sub_19A750("GameFrontEnd Initialization begin....");
    sub_19A750("******************************************");
    bp_4 = RwFreeListPurgeAllFreeLists();
    sub_19A750("GameFrontEndInit: Memory freed on RwFreeList purge - %d", bp_4);
    dword_4B889C = 0;
    sub_19A750();
    var_C = sub_1331E0();
    bp_8 = RWS::CameraHelper::CreateMainRasterCamera(Width, Height, ZDepth);
    dword_4B88B0 = bp_8;
    if (dword_4F39DC)
    {
        sub_19A750((const RwChar *)0);
    }
    if (!dword_4F30B8)
    {
        dword_4B9E54 = 0;
    }
    RwCameraSetNearClipPlane(bp_8, 1.0f);
    RwCameraSetFarClipPlane(bp_8, 100.0f);
    RpWorldAddCamera(var_C, bp_8);
    Rt2dOpen(bp_8);
    Rt2dAnimOpen();
    Rt2dDeviceSetLayerDepth(RwCameraGetNearClipPlane(bp_8) + 0.1f);
    byte_4B88B8 = false;
    dword_4B8EF0.sub_E9790(1, (RwInt32)bp_8);
    sub_D95A0();
    sub_198390();
    sub_83280();
    if (!dword_4B9E48)
    {
        unk_4B9308.sub_EE590();
    }
    sub_1A2E40(bp_8);
    if (!byte_4F61F1 && !byte_4F61F0)
    {
        dword_4B8EF0.sub_E9CA0();
    }
    dword_4B8EF0.sub_E99E0();
    sub_835E0();
    sub_198580();
    sub_19A750();
    Rt2dAnimClose();
    Rt2dClose();
    RpWorldRemoveCamera(var_C, bp_8);
    RWS::CameraHelper::Destroy(bp_8);
    dword_4B88B0 = 0;
    if (!sub_16E5C0(var_C, 0, 0))
    {
        sub_19A750("GameFrontEnd world is not empty at shutdown!");
    }
    RpWorldDestroy(var_C);
    bp_4 = RwFreeListPurgeAllFreeLists();
    sub_19A750("Shutdown: Memory freed on RwFreeList purge - %d", bp_4);
    sub_19A750("******************************************");
    sub_19A750("GameFrontEnd Shutdown end....");
    sub_19A750("******************************************");
    sub_19A750(" ");
    sub_19A750(" ");
    if (sub_12F080(1))
    {
        sub_12F060(1);
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
        sub_19A750("MEMORY LEAK detected during frontend shutdown! Show this to a");
        sub_19A750("programmer immediately (especially the last one that");
        sub_19A750("checked in) and tell him that restart/reset is broken.");
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
        sub_19A750();
    }
}
#endif

#ifdef CODFH_SP

void sp_sub_A59D0(RwCamera *arg_0);
void sp_sub_A5340(RwCamera *arg_0);
void sp_sub_A5580();
void sp_sub_12C410(void *arg_0);
bool sp_sub_B34A0();

// Single player's front end (SP 0xA5C90): multiplayer's sub_DA290 as single
// player has it. The world and camera are made as there, the pak is read,
// and the front end's own set-up (sp_sub_A59D0), steps (sp_sub_A5340, until
// the main menu is done) and shut-down (sp_sub_A5580) replace kujuUI's.
// sp-match: ?sp_sub_A5C90@@YAXXZ @ 0x000A5C90
void sp_sub_A5C90()
{
    RpWorld *world;
    RwCamera *camera;

    RwFreeListPurgeAllFreeLists();
    dword_4B889C = 0;
    sub_19A750();
    world = sub_1331E0();
    camera = RWS::CameraHelper::CreateMainRasterCamera(Width, Height, ZDepth);
    dword_4B88B0 = camera;
    if (!((sp_type_3EC3B0 *)dword_4F45F8)->unk_10)
    {
        sub_19BAC0(camera);
    }
    if (dword_4F39DC)
    {
        sp_sub_12C410(0);
    }
    sp_sub_B34A0();
    sub_16C940();
    if (!dword_4F30B8)
    {
        dword_4B9E54 = 0;
    }
    RwCameraSetNearClipPlane(camera, 1.0f);
    RwCameraSetFarClipPlane(camera, 100.0f);
    RpWorldAddCamera(world, camera);
    Rt2dOpen(camera);
    Rt2dAnimOpen();
    Rt2dDeviceSetLayerDepth(RwCameraGetNearClipPlane(camera) + 0.1f);
    sp_sub_A59D0(camera);
    sub_16C220("******************************************");
    sub_16C220("GameFrontEnd Initialization end....");
    sub_16C220("******************************************");
    sub_16C220(" ");
    sub_16C220(" ");
    dword_4B8888 = (RwUInt8 *)&dword_4F28F0->unk_2C;
    if (!((sp_type_3EC3B0 *)dword_4F45F8)->unk_18)
    {
        unk_4292B4.unk_0C = 2;
        sp_dword_3B4740 = 0;
        while (!sp_dword_3B4724->unk_04)
        {
            sp_sub_A5340(camera);
        }
    }
    else
    {
        unk_4292B4.unk_0C = 2;
    }
    sub_16C220(" ");
    sub_16C220(" ");
    sub_16C220("******************************************");
    sub_16C220("GameFrontEnd Shutdown begin....");
    sub_16C220("******************************************");
    sp_sub_A5580();
    Rt2dAnimClose();
    Rt2dClose();
    RpWorldRemoveCamera(world, camera);
    RWS::CameraHelper::Destroy(camera);
    dword_4B88B0 = 0;
    sub_16E5C0(world, 0, 0);
    RpWorldDestroy(world);
    RwFreeListPurgeAllFreeLists();
    if (sub_12F080(1))
    {
        sub_12F060(1);
    }
}

#endif
#endif // (single player: the first file ends here)
#if !defined(CODFH_SP) || CODFH_SP_PART != 1 // single player: src/sp/units/sp_unit_0DA290_2.cpp, the second file
#if defined(CODFH_SP) && CODFH_SP_PART == 2
// Its data definitions (PLAN SP5): the second file's two unreferenced 16.666666f head its .rdata
// after the first file's strings, before the attract movie's 15.945946f (SP 0x2E399C, 0x2E39A0).
// SP 0x002E399C
extern const RwReal sp_flt_2E399C = 16.666666f;
// SP 0x002E39A0
extern const RwReal sp_flt_2E39A0 = 16.666666f;
// End of its data definitions.

// The first file's front-end state (.bss) this one reads.
extern RwCamera *dword_4B88B0;
extern bool byte_4B8920;
extern RwReal dword_4B8924;
extern RwReal sp_flt_3B4750;
extern RwReal sp_flt_3B4754;
extern RwLLLink *sp_dword_3B4758;
extern RwTexDictionary *sp_dword_3B475C;
extern RwLLLink *sp_dword_3B4760;
extern RwInt32 sp_dword_3B4764;
extern RwReal sp_flt_3B4768;
extern RwChar sp_byte_3B4770[64];
extern bool sp_byte_3B47B1;
extern bool sp_byte_3B47B8;
extern type_44C4E8 *sp_dword_3EC3E4;
void sp_sub_A5080(RwCamera *arg_0, RwRaster *arg_4, RwInt32 arg_8);
#endif

#ifdef CODFH_SP
// Single player's front-end slide show (SP 0xA5E60 to 0xA6050): the
// textures of a texture dictionary shown in turn, each faded in over the
// one before. Its state is single player's (SP .bss 0x3B4750 on).
extern RwCamera *dword_4BFDBC;           // the camera drawn to by default (SP .bss 0x3BC60C, unit_0F2880)
#endif

#ifdef CODFH_SP
// Resets the slide show.
// sp-match: ?sp_sub_A5E60@@YAXXZ @ 0x000A5E60
void sp_sub_A5E60()
{
    sp_dword_3B475C = 0;
    sp_dword_3B4760 = 0;
    sp_dword_3B4758 = 0;
    sp_flt_3B4754 = 120.0f;
    sp_flt_3B4750 = 0.0f;
    sp_flt_3B4768 = 30.0f;
    sp_dword_3B4764 = 1;
}
#endif

#ifdef CODFH_SP
// Shows the textures of the dictionary arg_0, from its first.
// sp-match: ?sp_sub_A5EA0@@YAXPAURwTexDictionary@@@Z @ 0x000A5EA0
void sp_sub_A5EA0(RwTexDictionary *arg_0)
{
    sp_dword_3B475C = arg_0;
    if (arg_0)
    {
        sp_dword_3B4758 = rwLinkListGetFirstLLLink(&arg_0->texturesInDict);
    }
}
#endif

#ifdef CODFH_SP
// Draws the slide show to the camera arg_0 (the default camera when 0):
// the slide fading out under the one shown.
// sp-match: ?sp_sub_A5EC0@@YAXPAURwCamera@@@Z @ 0x000A5EC0
void sp_sub_A5EC0(RwCamera *arg_0)
{
    RwCamera *camera;
    RwUInt32 alpha;
    RwTexture *texture;

    camera = arg_0;
    if (sp_dword_3B475C)
    {
        if (!arg_0)
        {
            camera = dword_4BFDBC;
        }
        alpha = (RwInt32)(255.0f - (sp_flt_3B4768 - sp_flt_3B4750) / sp_flt_3B4768 * 255.0f);
        if (alpha > 255)
        {
            alpha = 255;
        }
        if (sp_dword_3B4760 && alpha < 255)
        {
            texture = rwLLLinkGetData(sp_dword_3B4760, RwTexture, lInDictionary);
            if (texture)
            {
                sp_sub_A5080(camera, texture->raster, 255);
            }
        }
        texture = rwLLLinkGetData(sp_dword_3B4758, RwTexture, lInDictionary);
        if (texture)
        {
            sp_sub_A5080(camera, texture->raster, alpha);
        }
    }
}
#endif

#ifdef CODFH_SP
// Starts the show again from the dictionary's first texture.
// sp-match: ?sp_sub_A5F50@@YAXXZ @ 0x000A5F50
void sp_sub_A5F50()
{
    if (sp_dword_3B475C)
    {
        sp_dword_3B4760 = 0;
        sp_dword_3B4758 = rwLinkListGetFirstLLLink(&sp_dword_3B475C->texturesInDict);
        sp_flt_3B4750 = 0.0f;
    }
}
#endif

#ifdef CODFH_SP
// Lets the show advance by itself.
// sp-match: ?sp_sub_A5F80@@YAXXZ @ 0x000A5F80
void sp_sub_A5F80()
{
    sp_dword_3B4764 = 0;
}
#endif

#ifdef CODFH_SP
// Stops the show advancing by itself, the slide shown at once.
// sp-match: ?sp_sub_A5F90@@YAXXZ @ 0x000A5F90
void sp_sub_A5F90()
{
    sp_dword_3B4764 = 1;
    sp_dword_3B4760 = sp_dword_3B4758;
    sp_flt_3B4750 = 0.0f;
}
#endif

#ifdef CODFH_SP
// Goes back a slide (from the first to the last); at once when the show
// does not advance itself.
// sp-match: ?sp_sub_A5FB0@@YAXXZ @ 0x000A5FB0
void sp_sub_A5FB0()
{
    RwLLLink *first;

    if (sp_dword_3B475C)
    {
        first = rwLinkListGetFirstLLLink(&sp_dword_3B475C->texturesInDict);
        sp_dword_3B4760 = sp_dword_3B4758;
        if (sp_dword_3B4758 == first)
        {
            sp_dword_3B4758 = sp_dword_3B475C->texturesInDict.link.prev;
        }
        else
        {
            sp_dword_3B4758 = sp_dword_3B4758->prev;
        }
        if (sp_dword_3B4764)
        {
            sp_dword_3B4760 = sp_dword_3B4758;
            sp_flt_3B4750 = 0.0f;
        }
    }
}
#endif

#ifdef CODFH_SP
// Goes on a slide (from the last to the first); at once when the show does
// not advance itself.
// sp-match: ?sp_sub_A6000@@YAXXZ @ 0x000A6000
void sp_sub_A6000()
{
    RwLLLink *last;

    if (sp_dword_3B475C)
    {
        last = sp_dword_3B475C->texturesInDict.link.prev;
        sp_dword_3B4760 = sp_dword_3B4758;
        if (sp_dword_3B4758 == last)
        {
            sp_dword_3B4758 = rwLinkListGetFirstLLLink(&sp_dword_3B475C->texturesInDict);
        }
        else
        {
            sp_dword_3B4758 = sp_dword_3B4758->next;
        }
        if (sp_dword_3B4764)
        {
            sp_dword_3B4760 = sp_dword_3B4758;
            sp_flt_3B4750 = 0.0f;
        }
    }
}
#endif

#ifdef CODFH_SP
// Advances the show by arg_0 seconds, a slide on each time a slide's time
// is up.
// sp-match: ?sp_sub_A6050@@YAXM@Z @ 0x000A6050
void sp_sub_A6050(RwReal arg_0)
{
    if (!sp_dword_3B4764)
    {
        sp_flt_3B4750 += arg_0;
        while (sp_flt_3B4750 > sp_flt_3B4754)
        {
            sp_flt_3B4750 -= sp_flt_3B4754;
            sp_sub_A6000();
        }
    }
}

// Single player's attract movie (SP 0xA60B0 to 0xA6140): its name and
// whether it is on are single player's (SP .bss 0x3B4770 on, beside
// byte_4B8920 and the idle time dword_4B8924).

// Sets the attract movie up: "Intro.bik", on, the front end not yet idle.
// (The idle flag and time are cleared before the name: SP 0xA60D1 stores
// them as constants, scheduled after the name's clear.)
// sp-match: ?sp_sub_A60B0@@YAXXZ @ 0x000A60B0
void sp_sub_A60B0()
{
    byte_4B8920 = false;
    dword_4B8924 = 0;
    memset(sp_byte_3B4770, 0, sizeof(sp_byte_3B4770));
    strcpy(sp_byte_3B4770, "Intro.bik");
#if defined(CODFH_WIN32)
    // Keep the title/menu visible while the Win32 port's Bink overlay path is incomplete.
    sp_byte_3B47B1 = false;
#else
    sp_byte_3B47B1 = true;
#endif
}

// Turns the attract movie off (the idle time cleared before the name, as
// in sp_sub_A60B0: SP 0xA6120 stores it as a constant).
// sp-match: ?sp_sub_A6100@@YAXXZ @ 0x000A6100
void sp_sub_A6100()
{
    byte_4B8920 = false;
    sp_byte_3B47B1 = false;
    sp_byte_3B47B8 = false;
    dword_4B8924 = 0;
    memset(sp_byte_3B4770, 0, sizeof(sp_byte_3B4770));
}
#endif

// match: ?sub_DA550@@YAX_N@Z @ 0x000DA550
// sp-match: ?sub_DA550@@YAX_N@Z @ 0x000A62A0
void sub_DA550(bool arg_0)
{
    byte_4B8920 = arg_0;
    sub_DA570();
}

// match: ?sub_DA570@@YAXXZ @ 0x000DA570
// sp-match: ?sub_DA570@@YAXXZ @ 0x000A6130
void sub_DA570()
{
    dword_4B8924 = 0;
}

#ifdef CODFH_SP
// The attract movie: while it is on and the front end waits (byte_4B8920),
// any pad input restarts the idle time; Live's prompts and notifications
// hold it. After about 16 seconds idle the music stops, the movie
// (sp_byte_3B4770) plays and the music starts again.
// sp-match: ?sp_sub_A6140@@YAXM@Z @ 0x000A6140
void sp_sub_A6140(RwReal arg_0)
{
    RwReal input;
    RwInt32 i;
    RwInt32 busy;

    dword_4B892C = 0;
    if (sp_byte_3B47B1 && byte_4B8920)
    {
        input = 0.0f;
        for (i = 0; i < 40; i++)
        {
            input += unk_4B9308.sub_EE9A0(0, i);
        }
        if (input != 0.0f)
        {
            sub_DA570();
        }
        busy = 0;
        if (dword_4F3130.sp_sub_12ABB0())
        {
            busy = 1;
        }
        if (!dword_4F3130.sp_sub_12AAD0() && !busy)
        {
            dword_4B8924 += arg_0 * 0.016666668f;
        }
        if (dword_4B8924 >= 15.945946f)
        {
            dword_4B8924 = 0.0f;
            if (sp_dword_3EC3E4)
            {
                SoundEmitter_Stop(sp_dword_3EC3E4, 0);
                sp_dword_3EC3E4 = 0;
            }
            for (i = 0; i < 4; i++)
            {
                RwaCoreUpdate();
            }
            dword_4B892C = 1;
            sub_E8AC0(sp_byte_3B4770, (RwInt32)dword_4B88B0, 0, 1);
            dword_4B892C = 0;
            type_3DF8D8_04 key(0x06D62AE9, 0x00C7F591); // not an address: a key
            sp_dword_3EC3E4 = (type_44C4E8 *)dword_4B1E98.sub_8A980(&key, 0, 0, (RwV3d *)&unk_4292B4, 1, 0);
            sp_byte_3B47B8 = true;
        }
    }
}
#endif

#endif
