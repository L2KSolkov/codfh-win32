// The Xbox platform (game/platform.h) and the movie player's Bink side
// (game/movie.h): the Bink player, the file system on d:, a file read
// ahead, the DDS texture read callback, the gamma ramp, the frame's end, and
// the movie object's open, step, draw, pause and volume.

#include <xtl.h>
#include <stdio.h>
#include <stdlib.h>

#include "game/xboxlive.h"
#include "game/platform.h"
#include "game/gameloop.h"
#include "game/movie.h"
#include "game/savestate.h"
#include "game/functions.h"
#include "game/clones.h"
#include "rw/rwxbox.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042C5A0
RwInt32 dword_42C5A0 = 1;
// 0x0042C5A4
const RwChar *off_42C5A4[13] = {
    "Title",
    "Unknown",
    "Dashboard",
    "Debugger",
    "Liveupdate",
    "d:\\Media\\codlayout.uix",
    "There is a problem with the disc you are using.\012It may be dirty or damaged.",
    "Bei der benutzten CD ist ein Problem aufgetreten.\012Moglicherweise ist sie verschmutzt oder beschadigt.",
    "Le disque utilise presente une anomalie.\012Il est peut-etre sale ou endommage.",
    "Bei der benutzten CD ist ein Problem aufgetreten.\012Moglicherweise ist sie verschmutzt oder beschadigt.",
    "Le disque utilise presente une anomalie.\012Il est peut-etre sale ou endommage.",
    "Il disco in uso ha qualche problema.\012Potrebbe essere sporco o danneggiato.",
    "Hay un problema con el disco que esta usando.\012Puede estar sucio o danado.",
};
// 0x004B8880
RwInt32 dword_4B8880;
// 0x004F2B64
RwReal dword_4F2B64;
// 0x004F2B70
RwInt32 dword_4F2B70;
// 0x004F307C
RwInt32 dword_4F307C;
// 0x004F3080
RwInt32 dword_4F3080;
// 0x004F30B8
#ifndef CODFH_PLAIN
RwInt32 dword_4F30B8;
#endif
// 0x004F30BC
#ifndef CODFH_PLAIN
RwInt32 dword_4F30BC;
#endif
// 0x004F30C0
RwUInt32 dword_4F30C0;
// 0x004F39A8
type_4F39A8 dword_4F39A8;
// 0x004F39D4
void *dword_4F39D4;
// 0x004F39DC
RwInt32 dword_4F39DC;
// 0x004F39E0
RwTextureCallBackRead dword_4F39E0;
// 0x004F39E4
RwInt32 dword_4F39E4;
// 0x004F39EC
RwUInt16 word_4F39EC;
// 0x004F39F0
void *dword_4F39F0;
// 0x004F39F8
RwUInt8 unk_4F39F8[3072];
// 0x004F45F8
type_4F45F8 *dword_4F45F8;
// 0x004F45FC
RwUInt32 dword_4F45FC;
// 0x004F4600
type_4F4600 unk_4F4600;
// 0x004F4628
RwUInt32 dword_4F4628;
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has these constants before the data's texts.)
// 0x003E0430
extern const RwReal flt_3E0430 = 16.666666f;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E0430@@3MB @ 0x003E0430
// match: ??_C@_0EK@BBAHCLIG@Hay?5un?5problema?5con?5el?5disco?5que@ @ 0x003E0438
// match: ??_C@_0EL@KPIDKOFB@Il?5disco?5in?5uso?5ha?5qualche?5probl@ @ 0x003E0488
// match: ??_C@_0EN@GGOMMJBP@Le?5disque?5utilise?5presente?5une?5a@ @ 0x003E04D8
// match: ??_C@_0GG@GKIMFNAF@Bei?5der?5benutzten?5CD?5ist?5ein?5Pro@ @ 0x003E0528
// match: ??_C@_0EM@IJMCFEIP@There?5is?5a?5problem?5with?5the?5disc@ @ 0x003E0590
// match: ?dword_42C5A0@@3HA @ 0x0042C5A0
// match: ?off_42C5A4@@3PAPBDA @ 0x0042C5A4

// match: ?sub_19CB20@type_4F39A8@@QAEXH@Z @ 0x0019CB20
// sp-match: ?sub_19CB20@type_4F39A8@@QAEXH@Z @ 0x0012C240

void type_4F39A8::sub_19CB20(RwInt32 arg_0)
{
    unk_10 = 0;
    unk_14 = arg_0;
    unk_18 = 1.0f;
    unk_1C = 1.0f;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
}

// match: ?sub_19CB80@type_4F39A8@@QAEPAUBINK@@PBDPAH@Z @ 0x0019CB80
// sp-match: ?sub_19CB80@type_4F39A8@@QAEPAUBINK@@PBDPAH@Z @ 0x0012C270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the movie d:\arg_0 with sound tracks 0 and 1 at half volume, and
// keeps the screen's scale to it; 0 on failure.
HBINK type_4F39A8::sub_19CB80(const RwChar *arg_0, RwInt32 *arg_4)
{
    RwUInt32 var_214[2] = {0, 1};
    RwInt32 var_218;
    HBINK var_20C;
    RwChar loc208[0x200];

    BinkSetSoundTrack(2, var_214);
    sprintf(loc208, "d:\\%s", arg_0);
    var_20C = BinkOpen(loc208, BINKSNDTRACK);
    if (!var_20C)
        return 0;
    for (var_218 = 0; var_218 < var_20C->NumTracks; var_218++)
        BinkSetVolume(var_20C, BinkGetTrackID(var_20C, var_218), 0x8000);
    if (var_20C)
    {
        unk_18 = (RwReal)(RwUInt32)Width / (RwReal)var_20C->Width;
        unk_1C = (RwReal)(RwUInt32)Height / (RwReal)var_20C->Height;
        unk_28 = 1;
        return var_20C;
    }
    return 0;
}

// match: ?sub_19CD10@type_4F39A8@@QAEXPAUBINK@@PAX@Z @ 0x0019CD10
// sp-match: ?sub_19CD10@type_4F39A8@@QAEXPAUBINK@@PAX@Z @ 0x0012C390
// Closes the movie arg_0 (and its file arg_4) after the next vertical blank.
void type_4F39A8::sub_19CD10(HBINK arg_0, void *arg_4)
{
    D3DDevice_BlockUntilVerticalBlank();
    D3DDevice_EnableOverlay(FALSE);
    if (arg_4)
        RwFclose(arg_4);
    unk_28 = 0;
    BinkClose(arg_0);
}






















RwInt32 type_4F39A8::sub_32260(HBINK arg_0)
{
    return 0;
}
