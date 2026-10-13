// The sound banks: loading them from their files, and the sound table. The
// file's original name is not recovered (M1), so it is named for its start
// address.

#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/soundbank.h"
#include "types/type_3D3548.h"
#include "game/data.h"
#include "game/textmanager.h"
#include "types/type_8A980.h"
#include "types/musicplayer.h"
#include "types/type_10F710.h"
#include "types/type_4C19C0.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D4340
extern const RwReal flt_3D4340 = 16.666666f;
// 0x00428E28
RwReal flt_428E28 = 1800.0f;
// 0x00428E2C
RwInt32 dword_428E2C = 50;
// 0x00428E30
RwReal flt_428E30 = 1.0f;
// 0x00428E34
RwReal flt_428E34 = 1.0f;
// 0x00428E38
const RwChar *dword_428E38[15] = {
    "English",
    "German",
    "French",
    "SGerman",
    "SFrench",
    "Italian",
    "Spanish",
    "Korean",
    "Swedish",
    "Norway",
    "Dutch",
    "Finnish",
    "Portug",
    "Japanese",
    "TChinese",
};
// 0x0044C0A0
RwReal flt_44C0A0;
// 0x0044C0A4
RwReal flt_44C0A4;
// 0x0044C0A8
type_44C0A8 *dword_44C0A8;
// 0x0044C0B0
RwInt32 dword_44C0B0[0x10E];
// 0x0044C4E8
RwInt32 dword_44C4E8[0x3E8];
// 0x0044D488
RwReal flt_44D488;
// 0x0044D48C
RwUInt32 dword_44D48C;
// 0x0044D49C
RwInt32 dword_44D49C;
// 0x0044D4A0
RwReal flt_44D4A0;
// 0x0044D4A4
RwInt32 dword_44D4A4;
// 0x0044D4A8
RwInt32 dword_44D4A8;
// 0x0044D4AC
RwInt32 dword_44D4AC;
// 0x0044D4B0
RwReal flt_44D4B0;
// 0x0044D4B4
RwInt32 dword_44D4B4;
// 0x0044D4B8
RwReal flt_44D4B8;
// 0x0044D4BC
RwReal flt_44D4BC;
// 0x0044D4C0
RwInt32 dword_44D4C0;
// 0x0044D4C4
RwInt32 dword_44D4C4;
// 0x0044D4C8
RwInt32 dword_44D4C8;
// 0x0044D4D0
RwReal flt_44D4D0;
// 0x0044D4DC
RwInt32 dword_44D4DC;
// 0x0044D4E0
RwInt32 dword_44D4E0[0x3E8];
// 0x0044E480
struct type_44E8D8_248 *dword_44E480[3];
// 0x0044E490
#ifdef CODFH_PLAIN
// (plain builds: the image's 0x100 bytes up to dword_44E590, a line of text
// strcpy'd in (unit_192BE0); one byte here let a single-player level's
// subtitles overwrite the variables after it)
static RwUInt8 byte_44E490_text[0x100];
RwUInt8 &byte_44E490 = byte_44E490_text[0];
#else
RwUInt8 byte_44E490;
#endif
// 0x0044E590
void *dword_44E590;
// 0x0044E5C4
RwInt32 *dword_44E5C4[8];
// 0x0044E5E8
RwReal flt_44E5E8;
// 0x0044E5EC
RwInt32 dword_44E5EC;
// 0x0044E5F0
RwInt32 dword_44E5F0[4];
// 0x0044E600
type_44E600 dword_44E600[10];
// 0x0044E768
RwUInt32 dword_44E768;
// 0x0044E770
void *dword_44E770[0x24];
// 0x0044E800
RwReal flt_44E800;
// 0x0044E804
RwInt32 dword_44E804;
// 0x0044E808
RwReal flt_44E808;
// 0x0044E80C
RwReal flt_44E80C;
// 0x0044E810
RwReal flt_44E810;
// 0x0044E824
RwReal flt_44E824;
// 0x0044E828
RwReal flt_44E828;
// 0x0044E834
RwInt32 dword_44E834;
// 0x0044E870
RwInt32 dword_44E870;
// 0x0044E884
RwInt32 dword_44E884;
// 0x0044E888
RwInt32 dword_44E888;
// 0x0044E88C
RwReal flt_44E88C;
// 0x0044E890
RwReal flt_44E890;
// 0x0044E894
RwReal flt_44E894;
// 0x0044E898
RwInt32 dword_44E898;
// 0x0044E89C
RwInt32 dword_44E89C;
// 0x0044E8A0
RwInt32 dword_44E8A0;
// 0x0044E8A4
RwInt32 dword_44E8A4;
// 0x0044E8A8
RwInt32 dword_44E8A8;
// 0x0044E8AC
type_44E8AC *dword_44E8AC;
// 0x0044E8B0
type_44E8B0 *dword_44E8B0;
// 0x0044E8B4
RwInt32 dword_44E8B4;
// 0x0044E8B8
RwInt32 dword_44E8B8;
// 0x0044E8BC
RwInt32 dword_44E8BC;
// 0x0044E8C0
RwInt32 dword_44E8C0;
// 0x0044E8C4
RwUInt8 *dword_44E8C4;
// 0x0044E8C8
void *dword_44E8C8;
// 0x0044E8CC
RwInt32 dword_44E8CC;
// 0x0044E8D0
RwInt32 dword_44E8D0;
// 0x0044E8D4
RwInt32 dword_44E8D4;
// 0x004AF24C
#ifndef CODFH_PLAIN
RwInt32 dword_4AF24C;
#endif
// 0x004B1F54
RwInt32 dword_4B1F54;
// 0x004B1F58
struct type_3D3548 *dword_4B1F58;
// 0x004B1F5C
RwInt32 dword_4B1F5C;
// 0x004B1F60
RwInt32 dword_4B1F60;
// 0x004F30A4
RwInt32 dword_4F30A4;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
// The sound keys (CGlobalSounds and the triggers use them) and the
// GodAsset tables, constructed before the banks (the image's .CRT$XCU order).
type_3DF8D8_04 dword_4B1B30;
type_3DF8D8_04 dword_4B1C60[3];
type_3DF8D8_04 dword_4B1C08;
type_3DF8D8_04 dword_4B1C98;
type_3DF8D8_04 dword_4B1B48;
type_3DF8D8_04 dword_4B1C88;
type_3DF8D8_04 dword_4B1C00;
type_3DF8D8_04 dword_4B1C50;
type_3DF8D8_04 dword_4B1C78;
type_3DF8D8_04 dword_4B1E88;
type_3DF8D8_04 dword_4AEFEC;
type_3DF8D8_04 dword_4B1F3C;
type_3DF8D8_04 dword_4AF010;
type_3DF8D8_04 dword_4B1C40;
type_3DF8D8_04 dword_4B1F4C;
type_3DF8D8_04 dword_4B1B58;
type_3DF8D8_04 dword_4B1B18;
type_3DF8D8_04 dword_4B1B38;
type_3DF8D8_04 dword_4B1E90;
type_3DF8D8_04 dword_4AF030;
type_3DF8D8_04 dword_4B1C80;
type_3DF8D8_04 dword_4B1C18;
type_3DF8D8_04 dword_4AF018;
type_3DF8D8_04 dword_4AF000;
type_3DF8D8_04 dword_4B1B40;
type_3DF8D8_04 dword_4AF020;
type_3DF8D8_04 dword_4B1B28;
type_3DF8D8_04 dword_4AEFF8;
type_3DF8D8_04 dword_4B1B10;
type_3DF8D8_04 dword_4B1C90;
type_3DF8D8_04 dword_4B1E80;
type_3DF8D8_04 dword_4B1C48;
type_3DF8D8_04 dword_4B1B50;
type_3DF8D8_04 dword_4B1C38;
type_3DF8D8_04 dword_4B1B20;
type_3DF8D8_04 dword_4B1F1C;
type_3DF8D8_04 dword_4AF008;
type_3DF8D8_04 dword_4B1F44;
type_3DF8D8_04 dword_4B1C10;
type_3DF8D8_04 dword_4AF028;
type_3DF8D8_04 dword_4B1C58;
type_3DF8D8_04 dword_4B1A18;
// The bank queue's period, copied at start-up.
RwReal flt_4AEFF4 = flt_428E28;
type_4B1CA0 dword_4B1CA0[0x14];
type_44E8D8 dword_44E8D8[3];
type_8A980 dword_4B1E98;
type_4B1A20 dword_4B1A20[SOUND_BANK_SLOTS];
type_4B1C20 dword_4B1C20[3];
type_825E0 dword_4B1B60[10];
// Constructed last (its .CRT$XCU entry follows the banks').
type_3DF8D8_04 dword_4B1F24[3];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_08GCDPOFMD@TChinese?$AA@ @ 0x003D42C0
// match: ??_C@_08FAMEJMP@Japanese?$AA@ @ 0x003D42CC
// match: ??_C@_06KHCNKHAG@Portug?$AA@ @ 0x003D42D8
// match: ??_C@_07MCEAMKOD@Finnish?$AA@ @ 0x003D42E0
// match: ??_C@_05OICONKIE@Dutch?$AA@ @ 0x003D42E8
// match: ??_C@_06ENBHNLAI@Norway?$AA@ @ 0x003D42F0
// match: ??_C@_07OBINPKFN@Swedish?$AA@ @ 0x003D42F8
// match: ??_C@_06OALMOPCN@Korean?$AA@ @ 0x003D4300
// match: ??_C@_07PFALJOGE@Spanish?$AA@ @ 0x003D4308
// match: ??_C@_07NPAHBEGM@Italian?$AA@ @ 0x003D4310
// match: ??_C@_07ENNLNEOB@SFrench?$AA@ @ 0x003D4318
// match: ??_C@_07GANEHKOC@SGerman?$AA@ @ 0x003D4320
// match: ??_C@_06GODMCAND@French?$AA@ @ 0x003D4328
// match: ??_C@_07NEKHPBCG@English?$AA@ @ 0x003D4338
// match: ?flt_3D4340@@3MB @ 0x003D4340
// match: ??_C@_0CA@LGANHCBM@ERROR?3?5Could?5not?5open?5file?5?$CFs?$CB?6?$AA@ @ 0x003D4344
// match: ??_C@_0BE@PPAOACMA@Sound?5Bank?5Loaded?$CB?6?$AA@ @ 0x003D4364
// match: ??_C@_0BI@HILDBLGC@Loading?5sound?5bank?5AGD?6?$AA@ @ 0x003D4378
// match: ??_C@_02JDPG@rb?$AA@ @ 0x003D4390
// match: ??_C@_0BF@CKDEEIOJ@JB?5SYNC?3?5Loading?5?$CFs?6?$AA@ @ 0x003D4394
// match: ??_C@_0DK@EJBNHBBP@Loading?5sound?5bank?5god?5ID?3?5?$CFx?0?$CFx@ @ 0x003D43AC
// match: ??_C@_0HM@KOEMLDOC@LoadSoundBankSynchronously?3?5Atte@ @ 0x003D43E8
// match: ??_C@_0BE@DMHEMAHN@d?3?2data?2dsstdfx?4bin?$AA@ @ 0x003D4464
// match: ??_C@_0BD@OMKPPAGA@Virtual?5Voice?5List?$AA@ @ 0x003D4478
// match: ??_C@_0DO@BOIENIOB@ERROR?3?5Some?5virtual?5voice?5were?5n@ @ 0x003D448C
// match: ??_C@_0GK@LGMKMKON@Error?5Unloading?5sound?5bank?4?5The?5@ @ 0x003D44D0
// match: ??_C@_0DA@OAEOAGKD@Unloading?5sound?5bank?5god?5ID?3?5?$CFx?0@ @ 0x003D453C
// match: ??_C@_0DC@JEEEPDBP@UnloadBank?3Sound?5bank?5slot?5?$CFd?5is@ @ 0x003D456C
// match: ??_C@_0DD@HFADMMEC@Too?5many?5things?5in?5the?5sound?5ban@ @ 0x003D45A0
// match: ??_C@_0DO@OALFPDCG@?$FO?$FO?$FO?$FO?$FO?$FO?$FOADDING?5BANK?5?$CFd?5TO?5SOUND?5B@ @ 0x003D45D4
// match: ??_C@_0BA@NJFNAAAL@SoundBankLoaded?$AA@ @ 0x003D4614
// match: ??_C@_0FN@PAKJGFFK@LoadSoundBankAsynchronously?3?5Ban@ @ 0x003D4628
// match: ??_C@_0EB@COFMFMNL@RwaVirtualVoiceSetFreq?$CIsm_Virtua@ @ 0x003D4688
// match: ??_C@_0DP@MADMPKDC@RwaVirtualVoiceSetGain?$CIsm_Virtua@ @ 0x003D46CC
// match: ??_C@_0BF@CMMDKLPH@?$DM?$DM?$FL?$CFd?$FN?9?9?9?$DN?$DN$$?$CD?$CD?3?5?$CFs?6?$AA@ @ 0x003D470C
// match: ??_C@_0N@OAKMNBFI@d?3?2Audio?2?$CFs?2?$AA@ @ 0x003D4724
// match: ??_C@_0BJ@CCGHGBKK@d?3?2Audio?2?$CFs?2ASLocate?4agd?$AA@ @ 0x003D4734
// match: ??_C@_07GNPFCMPI@SB_AGD?2?$AA@ @ 0x003D4750
// match: ??_C@_0O@OFGCDOHD@d?3?2?$CFs?$CFs?$CFs?$CFs?$CFs?$AA@ @ 0x003D4758
// match: ??_C@_07DNOMHLGH@SB_AWD?2?$AA@ @ 0x003D4768
// match: ??_C@_05FDIDLMPP@?2XBX_?$AA@ @ 0x003D4770
// match: ??_C@_06BIAMANEE@?$CFd_?$CFd?2?$AA@ @ 0x003D4778
// match: ??_C@_08EDEHOCNB@?$CF?44d?4agd?$AA@ @ 0x003D4780
// match: ??_C@_08FPGBEBKB@?$CF?44d?4awd?$AA@ @ 0x003D478C
// match: .CRT$XCU+0 @ 0x00426DFC
// match: .CRT$XCU+4 @ 0x00426E00
// match: .CRT$XCU+8 @ 0x00426E04
// match: .CRT$XCU+12 @ 0x00426E08
// match: .CRT$XCU+16 @ 0x00426E0C
// match: .CRT$XCU+20 @ 0x00426E10
// match: .CRT$XCU+24 @ 0x00426E14
// match: .CRT$XCU+28 @ 0x00426E18
// match: .CRT$XCU+32 @ 0x00426E1C
// match: .CRT$XCU+36 @ 0x00426E20
// match: .CRT$XCU+40 @ 0x00426E24
// match: .CRT$XCU+44 @ 0x00426E28
// match: .CRT$XCU+48 @ 0x00426E2C
// match: .CRT$XCU+52 @ 0x00426E30
// match: .CRT$XCU+56 @ 0x00426E34
// match: .CRT$XCU+60 @ 0x00426E38
// match: .CRT$XCU+64 @ 0x00426E3C
// match: .CRT$XCU+68 @ 0x00426E40
// match: .CRT$XCU+72 @ 0x00426E44
// match: .CRT$XCU+76 @ 0x00426E48
// match: .CRT$XCU+80 @ 0x00426E4C
// match: .CRT$XCU+84 @ 0x00426E50
// match: .CRT$XCU+88 @ 0x00426E54
// match: .CRT$XCU+92 @ 0x00426E58
// match: .CRT$XCU+96 @ 0x00426E5C
// match: .CRT$XCU+100 @ 0x00426E60
// match: .CRT$XCU+104 @ 0x00426E64
// match: .CRT$XCU+108 @ 0x00426E68
// match: .CRT$XCU+112 @ 0x00426E6C
// match: .CRT$XCU+116 @ 0x00426E70
// match: .CRT$XCU+120 @ 0x00426E74
// match: .CRT$XCU+124 @ 0x00426E78
// match: .CRT$XCU+128 @ 0x00426E7C
// match: .CRT$XCU+132 @ 0x00426E80
// match: .CRT$XCU+136 @ 0x00426E84
// match: .CRT$XCU+140 @ 0x00426E88
// match: .CRT$XCU+144 @ 0x00426E8C
// match: .CRT$XCU+148 @ 0x00426E90
// match: .CRT$XCU+152 @ 0x00426E94
// match: .CRT$XCU+156 @ 0x00426E98
// match: .CRT$XCU+160 @ 0x00426E9C
// match: .CRT$XCU+164 @ 0x00426EA0
// match: .CRT$XCU+168 @ 0x00426EA4
// match: .CRT$XCU+172 @ 0x00426EA8
// match: .CRT$XCU+176 @ 0x00426EAC
// match: .CRT$XCU+180 @ 0x00426EB0
// match: .CRT$XCU+184 @ 0x00426EB4
// match: .CRT$XCU+188 @ 0x00426EB8
// match: .CRT$XCU+192 @ 0x00426EBC
// match: .CRT$XCU+196 @ 0x00426EC0
// match: ?flt_428E28@@3MA @ 0x00428E28
// match: ?dword_428E2C@@3HA @ 0x00428E2C
// match: ?flt_428E30@@3MA @ 0x00428E30
// match: ?flt_428E34@@3MA @ 0x00428E34
// match: ?dword_428E38@@3PAPBDA @ 0x00428E38

// match: _$E2 @ 0x00309C90
// match: _$E4 @ 0x00309CB0
// match: _$E6 @ 0x00309D00
// match: _$E8 @ 0x00309D20
// match: _$E10 @ 0x00309D40
// match: _$E12 @ 0x00309D60
// match: _$E14 @ 0x00309D80
// match: _$E16 @ 0x00309DA0
// match: _$E18 @ 0x00309DC0
// match: _$E20 @ 0x00309DE0
// match: _$E22 @ 0x00309E00
// match: _$E24 @ 0x00309E20
// match: _$E26 @ 0x00309E40
// match: _$E28 @ 0x00309E60
// match: _$E30 @ 0x00309E80
// match: _$E32 @ 0x00309EA0
// match: _$E34 @ 0x00309EC0
// match: _$E36 @ 0x00309EE0
// match: _$E38 @ 0x00309F00
// match: _$E40 @ 0x00309F20
// match: _$E42 @ 0x00309F40
// match: _$E44 @ 0x00309F60
// match: _$E46 @ 0x00309F80
// match: _$E48 @ 0x00309FA0
// match: _$E50 @ 0x00309FC0
// match: _$E52 @ 0x00309FE0
// match: _$E54 @ 0x0030A000
// match: _$E56 @ 0x0030A020
// match: _$E58 @ 0x0030A040
// match: _$E60 @ 0x0030A060
// match: _$E62 @ 0x0030A080
// match: _$E64 @ 0x0030A0A0
// match: _$E66 @ 0x0030A0C0
// match: _$E68 @ 0x0030A0E0
// match: _$E70 @ 0x0030A100
// match: _$E72 @ 0x0030A120
// match: _$E74 @ 0x0030A140
// match: _$E76 @ 0x0030A160
// match: _$E78 @ 0x0030A180
// match: _$E80 @ 0x0030A1A0
// match: _$E82 @ 0x0030A1C0
// match: _$E84 @ 0x0030A1E0
// match: _$E86 @ 0x0030A200
// match: _$E88 @ 0x0030A210
// match: _$E89 @ 0x0030DE90
// match: _$E91 @ 0x0030A240
// match: _$E92 @ 0x0030DEB0
// match: _$E94 @ 0x0030A270
// match: _$E95 @ 0x0030DED0
// match: _$E97 @ 0x0030A290
// match: _$E99 @ 0x0030A2F0
// match: _$E101 @ 0x0030A340
// match: _$E103 @ 0x0030A390
// match: ?sub_824A0@@YAPAXII@Z @ 0x000824A0
// sp-match: _$E86 @ 0x0021C6F0
// sp-match: _$E88 @ 0x0021C700
// sp-match: _$E91 @ 0x0021C730
// sp-match: _$E94 @ 0x0021C760
// sp-match: _$E89 @ 0x0021E2F0
// sp-match: _$E92 @ 0x0021E2C0
// sp-match: _$E95 @ 0x0021E2E0
// sp-match: ?sub_824A0@@YAPAXII@Z @ 0x00069550

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_824A0(RwUInt32 arg_0, RwUInt32 arg_4)
{
    RwUInt32 *var_10;
    RwUInt32 var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    bp_8 = arg_0 + 8;
    var_C = (RwUInt32)RwMalloc(bp_8, arg_4);
    if (var_C > 0)
    {
#ifdef CODFH_SP // shape:
        bp_4 = ((var_C + 8) >> 3) * 8;
#else
        bp_4 = (var_C + 8) >> 3;
        bp_4 <<= 3;
#endif
        var_10 = (RwUInt32 *)(bp_4 - 4);
        *var_10 = var_C;
    }
    else
    {
        return 0;
    }
    return (void *)bp_4;
}

#ifdef CODFH_SP
// Single player's disc-error handler (unit_19CD50, SP 0x12C410): its one-argument checks
// after the stream reads call it where multiplayer calls the empty sub_19A750.
void sp_sub_12C410(void *arg_0);
#endif

// match: ?sub_82500@@YAXXZ @ 0x00082500
// sp-match: ?sub_82500@@YAXXZ @ 0x0006A3D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_82500()
{
    RwInt32 local_124;
    RwChar var_120[0x100];
    RwStream *slot_1C;
    RwChunkHeaderInfo var_18;
    RwStream *var_4;

    sub_85840(var_120, 0);
    var_4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_120);
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out (no string in SP; SP 0x6A3D0)
    if (var_4)
    {
#else
    if (!var_4)
    {
        sub_19A750("ERROR: Could not open file %s!\n", var_120);
    }
    else
    {
#endif
        slot_1C = RwStreamReadChunkHeaderInfo(var_4, &var_18);
#ifdef CODFH_SP // the disc-error check (SP 0x6A414 calls 0x12C410)
        sp_sub_12C410((void *)slot_1C);
#else
        sub_19A750(slot_1C);
#endif
        for (local_124 = 0; local_124 < 0x10E; local_124++)
        {
            RwStreamRead(var_4, &dword_44C0B0[local_124], sizeof(RwInt32));
        }
        RwStreamClose(var_4, 0);
    }
}


// match: ?sub_825E0@@YAXPAUtype_825E0@@H@Z @ 0x000825E0
// sp-match: ?sub_825E0@@YAXPAUtype_825E0@@H@Z @ 0x0006A460
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_825E0(type_825E0 *arg_0, RwInt32 arg_4)
{
    type_199010 *var_250;
#ifndef CODFH_SP // shape: single player scopes it to the memory stream's block (SP 0x6A460 shares its slot)
    RwMemory var_24C;
#endif
    RwUInt32 var_244;
    type_84230 local_240;
    RwInt32 var_20;
    type_4B1A20 *l1C;
    RwChunkHeaderInfo m_18;
    RwStream *bp_4;

    l1C = &dword_4B1A20[arg_0->unk_08];
    sub_84230(&local_240);
    local_240.unk_00 = *arg_0;
    l1C->unk_18 = *arg_0;
    sub_858E0(local_240.unk_110, local_240.unk_10, local_240.unk_00.unk_0C);
    bp_4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, local_240.unk_110);
    if (!bp_4)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (no string in SP; SP 0x6A460)
        sub_19A750("ERROR: Could not open file %s!\n", local_240.unk_110);
#endif
        return;
    }
    if (arg_4)
    {
        var_244 = RwStreamRead(bp_4, dword_44E8C4, 0x100000); // not an address: 1 MB
#ifdef CODFH_SP // the disc-error check (SP 0x6A51F calls 0x12C410)
        sp_sub_12C410((void *)var_244);
#else
        sub_19A750((void *)var_244);
#endif
        RwStreamClose(bp_4, 0);
        sub_82330();
#ifdef CODFH_SP // shape:
        RwMemory var_24C;
#endif
        var_24C.start = dword_44E8C4;
        var_24C.length = var_244;
        bp_4 = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &var_24C);
        if (!bp_4)
        {
            sub_82340();
            return;
        }
    }
    RwStreamReadChunkHeaderInfo(bp_4, &m_18);
    RwStreamRead(bp_4, &var_20, sizeof(RwInt32));
    RwStreamReadChunkHeaderInfo(bp_4, &m_18);
    while (var_20)
    {
        var_20--;
        type_825E0_id var_258;
        type_825E0_rec var_11A8;
        RwStreamRead(bp_4, &var_11A8, sizeof(type_825E0_rec));
        var_258.unk_00 = var_11A8.unk_00;
        var_258.unk_04 = var_11A8.unk_04;
        var_250 = sub_198710((type_3DF8D8_04 *)(&var_258));
        if (!var_250 && !sub_198770((type_3DF8D8_04 *)(&var_258)))
        {
            var_250 = sub_199010((type_3DF8D8_04 *)(&var_258), 0x19);
            sub_198FE0((type_3DF8D8_base *)var_250);
            var_250->unk_1C = (RwInt16)var_11A8.unk_08;
            var_250->unk_11 = (RwUInt8)var_11A8.unk_0C;
            var_250->unk_12 = (RwUInt8)var_11A8.unk_10;
            var_250->unk_13 = (RwUInt8)var_11A8.unk_14;
            var_250->unk_20 = (RwUInt16)var_11A8.unk_18;
            var_250->unk_22 = (RwUInt16)var_11A8.unk_1C;
            var_250->unk_24 = (RwUInt16)var_11A8.unk_20;
            var_250->unk_26 = (RwUInt16)var_11A8.unk_24;
            var_250->unk_10 = (RwUInt8)var_11A8.unk_28;
            var_250->unk_14 = (RwUInt8)var_11A8.unk_2C;
            var_250->unk_15 = (RwUInt8)var_11A8.unk_30;
            var_250->unk_16 = (RwUInt8)var_11A8.unk_34;
            var_250->unk_17 = (RwUInt8)var_11A8.unk_3C;
            var_250->unk_1E = (RwInt16)var_11A8.unk_44;
            var_250->unk_18 = (RwUInt8)var_11A8.unk_40;
            var_250->unk_19 = (RwUInt8)var_11A8.unk_48;
            switch (dword_44E8A4)
            {
            case 0:
            {
                RwUInt32 var_11B0 = strlen(var_11A8.unk_4C[0]);

                if (var_11B0)
                {
                    sub_83DD0(var_250);
                    strcpy(var_250->unk_28, var_11A8.unk_4C[0]);
                }
                else
                {
                    var_250->unk_28 = 0;
                }
                break;
            }
            case 1:
            {
                RwUInt32 var_11B4 = strlen(var_11A8.unk_4C[1]);

                if (var_11B4)
                {
                    sub_83DD0(var_250);
                    strcpy(var_250->unk_28, var_11A8.unk_4C[1]);
                }
                else
                {
                    var_250->unk_28 = 0;
                }
                break;
            }
            case 2:
            {
                RwUInt32 var_11B8 = strlen(var_11A8.unk_4C[2]);

                if (var_11B8)
                {
                    sub_83DD0(var_250);
                    strcpy(var_250->unk_28, var_11A8.unk_4C[2]);
                }
                else
                {
                    var_250->unk_28 = 0;
                }
                break;
            }
            case 5:
            {
                RwUInt32 var_11BC = strlen(var_11A8.unk_4C[5]);

                if (var_11BC)
                {
                    sub_83DD0(var_250);
                    strcpy(var_250->unk_28, var_11A8.unk_4C[5]);
                }
                else
                {
                    var_250->unk_28 = 0;
                }
                break;
            }
            case 6:
            {
                RwUInt32 var_11C0 = strlen(var_11A8.unk_4C[6]);

                if (var_11C0)
                {
                    sub_83DD0(var_250);
                    strcpy(var_250->unk_28, var_11A8.unk_4C[6]);
                }
                else
                {
                    var_250->unk_28 = 0;
                }
                break;
            }
            }
        }
        var_250->unk_1A++;
        var_250->vf_14(&l1C->unk_18, var_11A8.unk_38);
        type_825E0_node *var_11AC = new (4) type_825E0_node;
        var_11AC->unk_04.unk_00 = var_258.unk_00;
        var_11AC->unk_04.unk_04 = var_258.unk_04;
        var_11AC->unk_0C = var_250;
        var_11AC->unk_00 = l1C->unk_14;
        l1C->unk_14 = var_11AC;
        if (var_20)
        {
            RwStreamReadChunkHeaderInfo(bp_4, &m_18);
        }
    }
    RwStreamClose(bp_4, 0);
    if (arg_4)
    {
        sub_82340();
    }
}

// "LoadSoundBankSynchronously".
// match: ?sub_82C70@@YAXPAUtype_825E0@@_N@Z @ 0x00082C70
// sp-match: ?sub_82C70@@YAXPAUtype_825E0@@_N@Z @ 0x0006A8D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_82C70(type_825E0 *arg_0, bool arg_4)
{
    RwUInt32 var_218;
    RwUInt32 var_214;
    RwChar var_210[0x100];
    void *m_10C;
    RwChar var_108[0x100];
    type_4B1A20 *l4;

    if (!dword_44C0A8)
    {
        return;
    }
    if (arg_0->unk_08 < 0)
    {
        return;
    }
    dword_44E8D4 = 1;
    l4 = &dword_4B1A20[arg_0->unk_08];
    sub_23BFE0(dword_44C0A8);
    if (l4->unk_00)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug prints out (no strings in SP; SP 0x6A8D0)
        sub_19A750("LoadSoundBankSynchronously: Attempting to load a sound bank into slot %d that has not been "
                   "unloaded! (Or is still loading!)",
                   arg_0->unk_08);
#endif
        dword_44E8D4 = 0;
        return;
    }
    l4->unk_18 = *arg_0;
    sub_858E0(var_108, var_210, l4->unk_18.unk_0C);
    if (arg_4)
    {
        sub_19BB40(var_210, 1);
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    if (dword_44E870)
    {
        sub_19A750("Loading sound bank god ID: %x,%x to slot %d from file %s\n", l4->unk_18.unk_00.unk_00,
                   l4->unk_18.unk_00.unk_04, arg_0->unk_08, var_210);
    }
    sub_19A750("JB SYNC: Loading %s\n", var_210);
#endif
    m_10C = RwFopen(var_210, "rb");
    if (!m_10C)
    {
        dword_44E8D4 = 0;
        if (arg_4)
        {
            sub_19BB40(var_210, 0);
        }
        return;
    }
    if (m_10C)
    {
        dword_44C0A8 = sub_23C490(m_10C, 0, 0, 0, dword_44C0A8);
#ifdef CODFH_SP // the disc-error check (SP 0x6AA00 calls 0x12C410)
        sp_sub_12C410((void *)dword_44C0A8);
#else
        sub_19A750(dword_44C0A8);
#endif
        if (dword_44C0A8->unk_2C == 0x100)
        {
            l4->unk_10 = dword_44C0A8->unk_00;
        }
        else
        {
#ifdef CODFH_SP // the disc-error check (SP 0x6AA21 calls 0x12C410)
            sp_sub_12C410((void *)0);
#else
            sub_19A750((void *)0);
#endif
        }
        RwFclose(m_10C);
        if (arg_4)
        {
            sub_19BB40(var_210, 0);
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    if (dword_44E870)
    {
        sub_19A750("Loading sound bank AGD\n");
    }
#endif
    if (arg_4)
    {
        sub_19BB40(var_108, 1);
    }
    sub_825E0(arg_0, arg_4);
    if (arg_4)
    {
        sub_19BB40(var_108, 0);
    }
    sub_23BFE0(dword_44C0A8);
    if (!arg_4)
    {
        sub_84230(&dword_4AF038[0]);
    }
    var_214 = sub_24DB40();
    var_218 = dword_44D48C - var_214;
    dword_44D48C = var_214;
    dword_44E768 += var_218;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    if (dword_44E870)
    {
        sub_19A750("Sound Bank Loaded!\n");
    }
#endif
    dword_44E8D4 = 0;
}

// The sound system's set-up: the DSP image, the output stream and its
// listener, the wave bank and the voice streams.
// match: ?sub_82F50@@YAHXZ @ 0x00082F50
// sp-match: ?sub_82F50@@YAHXZ @ 0x0006AAD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_82F50()
{
    RwUInt32 var_48;
    void *loc44;
    RwInt32 var_40;
    type_82F50 l3C;

    var_40 = 0;
    RwaObjDefGetDefaultCreationParams(sub_23DCA0(0, unk_3EDF5C, 0), &l3C);
#ifdef CODFH_WIN32
    // (the port: room for a test level's extra sound banks, port_sound_banks: 16 MB of wave
    // memory, within the wave allocator's bitmap, unk_516CC0's 33 MB of 144-byte units)
    l3C.unk_14 = SOUND_WAVE_MEMORY;
#else
    l3C.unk_14 = 0x2EE000; // not an address: a buffer size (3 MB)
#endif
    loc44 = (void *)sub_19CDE0("d:\\data\\dsstdfx.bin");
    if (!loc44)
    {
        dword_44E8B0 = 0;
        return 0;
    }
    dword_44E8B0 = RwaStreamCreate_1(0, &l3C, 6, 0, 0);
    if (!dword_44E8B0)
    {
        return 0;
    }
    for (var_48 = 6; var_48 < 9; var_48++)
    {
        IDirectSound_SetMixBinHeadroom(dword_44E8B0->unk_6C, var_48, 0);
    }
    dword_44D4C4 = 1;
    sub_22C6E0(dword_44E8B0, dword_44D4C4);
    dword_44E8AC = RwaListenerCreate(4, 0, 0);
    sub_24E180(dword_44E8B0, dword_44E8AC);
    dword_44E5EC = 0x8000;
    dword_44E804 = 0x10000;
    dword_44D4AC = 0x100000; // not an address: a size (1 MB)
    dword_44C0A8 = (type_44C0A8 *)RWSMalloc(0x48, 0x30000); // not an address: an allocation tag
    sub_23BFE0(dword_44C0A8);
    dword_44D4A8 = 0;
    dword_44E590 = sub_824A0(dword_44E804, 0x30000); // not an address: an allocation tag
    do
    {
        if (dword_44E590)
        {
            dword_506830 = dword_44E590;
            dword_42E484 = dword_44E804;
        }
        else
        {
            dword_506830 = 0;
            dword_42E484 = 0;
        }
    } while (0);
    var_40 = sub_83170();
    return var_40;
}

#ifdef CODFH_SP // rwabase.c's pair (SP 0x32A850); multiplayer's copy is unk_42E548[54]
extern "C" void *unk_42E620[2];
#endif

// match: ?sub_83100@@YAHXZ @ 0x00083100
// sp-match: ?sub_83100@@YAHXZ @ 0x00069580
RwInt32 sub_83100()
{
    RwInt32 var_4;

#ifdef CODFH_SP // single player keeps the core in rwabase's own pair unk_42E620 (SP 0x6958A stores it at 0x32A850)
    unk_42E620[0] = (void *)RwaCoreOpen(0, 1);
    var_4 = (RwInt32)unk_42E620[0];
#else
    unk_42E548[54] = (void *)RwaCoreOpen(0, 1);
    var_4 = (RwInt32)unk_42E548[54];
#endif
    var_4 = sub_23E3A0();
    var_4 = sub_24EC10();
    dword_44E8C4 = (RwUInt8 *)RWSMalloc(0x100000, 0x34250); // not an address: an allocation tag
    dword_44E8C8 = RWSMalloc(0x80000, 0x34250); // not an address: an allocation tag
    return var_4;
}

// match: ?sub_83170@@YAHXZ @ 0x00083170
// sp-match: ?sub_83170@@YAHXZ @ 0x000695D0
RwInt32 sub_83170()
{
    RwInt32 var_4;
    RwInt32 local_8;

    for (local_8 = 0; local_8 < 0x24; local_8++)
    {
        dword_44E770[local_8] = RwaStreamCreate_2(dword_44E8B0, 0, 6, 0, 0);
    }
    var_4 = sub_23E690(dword_44E8B0, dword_44E770, 0x24);
    return var_4;
}

// The sound system's shut-down.
// match: ?sub_831D0@@YAXXZ @ 0x000831D0
void sub_831D0()
{
    RwInt32 var_4;

    if (dword_44C0A8)
    {
        sub_23C020(dword_44C0A8);
        operator delete(dword_44C0A8);
        dword_44C0A8 = 0;
    }
    DSPResourceMgr_Shutdown();
    for (var_4 = 0; var_4 < 0x24; var_4++)
    {
        DSPHandle_Stop(dword_44E770[var_4], 0, 0);
    }
    DSPHandle_Stop(dword_44E8B0, 0, 0);
    DSPHandle_Stop(dword_44E8AC, 0, 0);
    sub_31DB0();
    sub_24EBD0();
    sub_23E3E0();
    RwaCoreClose();
}

// Resets the sound system's state.
// match: ?sub_83280@@YAHXZ @ 0x00083280
// sp-match: ?sub_83280@@YAHXZ @ 0x0006AC10
RwInt32 sub_83280()
{
    RwInt32 var_4;
    RwInt32 v8;
    type_4B1CA0 *varC;

    v8 = 1;
    flt_4AEFF4 = flt_428E28;
    dword_428E2C = 0x32;
    dword_44E8B4 = 0;
    dword_44E8B8 = 0;
    dword_44E8C0 = 0;
    dword_44E8A4 = sub_19B0A0();
    dword_44E8A8 = dword_44E8A4;
    byte_44E490 = 0;
    dword_44D4C0 = 0;
    dword_44D4C8 = 0;
    dword_44D4DC = 0;
    dword_44D49C = 0;
#ifdef CODFH_WIN32
    dword_44D48C = SOUND_WAVE_MEMORY; // (the port's, as sub_82F50's)
#else
    dword_44D48C = 0x2EE000; // not an address: a size (3 MB)
#endif
    dword_44E768 = 0;
    for (var_4 = 0; var_4 < 0x14; var_4++)
    {
        sub_84230(&dword_4AF038[var_4]);
    }
    for (var_4 = 0; var_4 < SOUND_BANK_SLOTS; var_4++)
    {
        dword_4B1A20[var_4].unk_18.unk_00.unk_00 = -1;
        dword_4B1A20[var_4].unk_18.unk_00.unk_04 = -1;
        dword_4B1A20[var_4].unk_10 = 0;
        dword_4B1A20[var_4].unk_14 = 0;
        dword_4B1A20[var_4].unk_18.unk_08 = -1;
        dword_4B1A20[var_4].unk_18.unk_0C = -1;
        dword_4B1A20[var_4].unk_00 = 0;
    }
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        dword_4B1C20[var_4].unk_00 = 0;
        dword_4B1C20[var_4].unk_04 = 0;
    }
    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        dword_44C4E8[var_4] = 0;
        dword_44D4E0[var_4] = 0;
    }
    for (var_4 = 0; var_4 < 0x14; var_4++)
    {
        varC = &dword_4B1CA0[var_4];
        varC->unk_04 = 0;
        varC->unk_00 = 0;
        varC->unk_14 = 0;
    }
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        dword_44E8D8[var_4].sub_863E0(dword_44E8AC, dword_44E8B0);
    }
    for (var_4 = 0; var_4 < 10; var_4++)
    {
        sub_83C60(&dword_4B1B60[var_4]);
    }
    sub_82500();
    dword_44E834 = 0;
    return v8;
}

// Restarts the sound system, keeping dword_4B1C20.
// match: ?sub_83510@@YAXXZ @ 0x00083510
// sp-match: ?sub_83510@@YAXXZ @ 0x0006BD70
void sub_83510()
{
    type_4B1C20 var_18[3];
    RwInt32 var_1C;

    for (var_1C = 0; var_1C < 3; var_1C++)
    {
        var_18[var_1C].unk_00 = dword_4B1C20[var_1C].unk_00;
        var_18[var_1C].unk_04 = dword_4B1C20[var_1C].unk_04;
    }
    sub_835E0();
    sub_83280();
    for (var_1C = 0; var_1C < 3; var_1C++)
    {
        dword_4B1C20[var_1C].unk_00 = var_18[var_1C].unk_00;
        dword_4B1C20[var_1C].unk_04 = var_18[var_1C].unk_04;
    }
}

// Stops the sound system's sounds and resets its state.
// match: ?sub_835E0@@YAXXZ @ 0x000835E0
// sp-match: ?sub_835E0@@YAXXZ @ 0x0006BC30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_835E0()
{
    RwInt32 var_1C;
    RwInt32 var_18;
    RwInt32 var_14;
    RwInt32 lv_10;
    RwV3d var_C;

    var_C.x = var_C.y = var_C.z = 0;
    do
    {
        dword_44E8AC->unk_28 = var_C;
        dword_44E8AC->unk_70 |= 1;
    } while (0);
    for (lv_10 = 0; lv_10 < 0x14; lv_10++)
    {
        dword_4B1CA0[lv_10].sub_83760();
    }
    sub_83B40();
    for (var_14 = 0; var_14 < SOUND_BANK_SLOTS; var_14++)
    {
        sub_83DE0(var_14);
    }
    for (var_18 = 0; var_18 < 10; var_18++)
    {
        sub_83C60(&dword_4B1B60[var_18]);
    }
    sub_83CF0();
    sub_83BB0();
    for (var_1C = 2; var_1C >= 0; var_1C--)
    {
        dword_44E8D8[var_1C].sub_866C0();
    }
    sub_83B70();
    flt_44E894 = 0;
    dword_44E8A0 = 0;
    dword_44E898 = 0;
    dword_44E89C = 0;
    dword_44E8B4 = 0;
    dword_44E8B8 = 0;
    dword_44E8BC = 0;
    dword_44E8C0 = 0;
    flt_4AEFF4 = flt_428E28;
    dword_428E2C = 0x32;
}

// match: ??1type_837D0@@QAE@XZ @ 0x000837D0
// (Defined in the class, in soundbank.h.)
// sp-match: ??_Gtype_837D0@@QAEPAXI@Z @ 0x00069500
// (Single player: the destructor expanded into its scalar deleting destructor, which
// deletes the rest of the list by calling itself; no separate destructor.)

// Carves the group arg_0's virtual voice lists from arg_4's pool into
// arg_8.
// match: ?sub_83850@@YAXHPAUtype_8A980@@PAPAH@Z @ 0x00083850
// sp-match: ?sub_83850@@YAXHPAUtype_8A980@@PAPAH@Z @ 0x00069620
void sub_83850(RwInt32 arg_0, type_8A980 *arg_4, RwInt32 **arg_8)
{
    RwInt32 var_4;

    var_4 = (dword_44E600[arg_0].unk_00[0] + dword_44E600[arg_0].unk_00[1] + dword_44E600[arg_0].unk_00[2]
             + dword_44E600[arg_0].unk_00[3] + dword_44E600[arg_0].unk_00[4] + dword_44E600[arg_0].unk_00[5]
             + dword_44E600[arg_0].unk_00[6] + dword_44E600[arg_0].unk_00[7])
            * sizeof(RwInt32);
    if (var_4)
    {
        arg_4->unk_24.sub_16C2C0(1, var_4, "Virtual Voice List", 4, 1);
        type_83A70 var_48;

        var_48.unk_00 = dword_44E600[arg_0].unk_00[0];
        arg_8[0] = (RwInt32 *)arg_4->unk_24.sub_16C5A0(0);
        var_48.unk_04 = arg_8[0];
        var_48.unk_08 = dword_44E600[arg_0].unk_00[1];
        arg_8[1] = arg_8[0] + var_48.unk_00;
        var_48.unk_0C = arg_8[1];
        var_48.unk_10 = dword_44E600[arg_0].unk_00[2];
        arg_8[2] = arg_8[1] + var_48.unk_08;
        var_48.unk_14 = arg_8[2];
        var_48.unk_18 = dword_44E600[arg_0].unk_00[3];
        arg_8[3] = arg_8[2] + var_48.unk_10;
        var_48.unk_1C = arg_8[3];
        var_48.unk_20 = dword_44E600[arg_0].unk_00[4];
        arg_8[4] = arg_8[3] + var_48.unk_18;
        var_48.unk_24 = arg_8[4];
        var_48.unk_28 = dword_44E600[arg_0].unk_00[5];
        arg_8[5] = arg_8[4] + var_48.unk_20;
        var_48.unk_2C = arg_8[5];
        var_48.unk_30 = dword_44E600[arg_0].unk_00[6];
        arg_8[6] = arg_8[5] + var_48.unk_28;
        var_48.unk_34 = arg_8[6];
        var_48.unk_38 = dword_44E600[arg_0].unk_00[7];
        arg_8[7] = arg_8[6] + var_48.unk_30;
        var_48.unk_3C = arg_8[7];
        arg_4->sub_88950(&var_48, arg_0);
    }
    else
    {
        arg_4->unk_24.sub_16C2C0(1, 4, "Virtual Voice List", 4, 1);
    }
}

// match: ??0type_83A70@@QAE@XZ @ 0x00083A70
#ifdef CODFH_SP
inline // SP has no out-of-line copy: SP 0x69620 expands it
#endif
type_83A70::type_83A70()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_3C = 0;
}

// match: ?sub_83B20@@YAXXZ @ 0x00083B20
// sp-match: ?sub_83B20@@YAXXZ @ 0x000697B0
void sub_83B20()
{
    sub_83850(8, &dword_4B1E98, dword_44E5C4);
}

// match: ?sub_83B40@@YAXXZ @ 0x00083B40
// sp-match: ?sub_83B40@@YAXXZ @ 0x000697D0
void sub_83B40()
{
    dword_4B1E98.sub_88DF0();
}

// match: ?sub_83B50@@YAXXZ @ 0x00083B50
// sp-match: ?sub_83B50@@YAXXZ @ 0x000697E0
void sub_83B50()
{
    if (dword_4F39D4)
    {
        RtFSManagerSyncAllFilesOnFileSystem(dword_4F39D4);
    }
}

// match: ?sub_83B70@@YAXXZ @ 0x00083B70
void sub_83B70()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (dword_44C4E8[var_4])
        {
            sub_19A750("ERROR: Some virtual voice were not freed on restart/shutdown!");
        }
    }
}

// Waits for the three music players to stop.
// match: ?sub_83BB0@@YAXXZ @ 0x00083BB0
// sp-match: ?sub_83BB0@@YAXXZ @ 0x0006AD80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_83BB0()
{
    RwUInt32 var_10;
    RwUInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    while (1)
    {
        bp_8 = 1;
        for (bp_4 = 0; bp_4 < 3; bp_4++)
        {
            if (!dword_44E8D8[bp_4].sub_86830())
            {
                bp_8 = 0;
            }
        }
        if (bp_8 == 0)
        {
            var_10 = RWS::Time::GetTime();
            var_C = 0;
            while (var_C < (RwUInt32)((RwInt32)flt_3D4340 * 2))
            {
                var_C = RWS::Time::GetTime() - var_10;
            }
            sub_86350();
            sub_83B50();
        }
        else
        {
            break;
        }
    }
}

// match: ?sub_83C60@@YAXPAUtype_825E0@@@Z @ 0x00083C60
// sp-match: ?sub_83C60@@YAXPAUtype_825E0@@@Z @ 0x00069800
void sub_83C60(type_825E0 *arg_0)
{
    arg_0->unk_00.unk_00 = -1;
    arg_0->unk_00.unk_04 = -1;
    arg_0->unk_08 = -1;
    arg_0->unk_0C = -1;
}

// match: ?sub_83C90@@YAXXZ @ 0x00083C90
// sp-match: ?sub_83C90@@YAXXZ @ 0x00069820
void sub_83C90()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_4B1C20[var_4].unk_00 && dword_4B1C20[var_4].unk_04)
        {
            dword_4B1E98.sub_8A980((type_3DF8D8_04 *)&dword_4B1C20[var_4], 0, 0x20, 0, 0, 0);
        }
    }
}

// match: ?sub_83CF0@@YAXXZ @ 0x00083CF0
// sp-match: ?sub_83CF0@@YAXXZ @ 0x00069860
void sub_83CF0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        dword_44E8D8[var_4].sub_867A0();
    }
}

// A free virtual voice slot, or -1.
// match: ?sub_83D30@@YAHXZ @ 0x00083D30
// sp-match: ?sub_83D30@@YAHXZ @ 0x00069880
RwInt32 sub_83D30()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (!dword_44C4E8[var_4])
        {
            return var_4;
        }
    }
    return -1;
}

// match: ?sub_83D70@@YAXH@Z @ 0x00083D70
// sp-match: ?sub_83D70@@YAXH@Z @ 0x000698A0
void sub_83D70(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (dword_44C4E8[var_4] == arg_0)
        {
            dword_44C4E8[var_4] = 0;
            dword_44D4E0[var_4] = 0;
            break;
        }
    }
}

// match: ?sub_83DD0@@YAXPAUtype_199010@@@Z @ 0x00083DD0
// sp-match: ?sub_83DD0@@YAXPAUtype_199010@@@Z @ 0x000698E0
// Gives the sound arg_0 its name in the current language (sub_1986B0).
void sub_83DD0(type_199010 *arg_0)
{
    arg_0->unk_28 = sub_1986B0();
}

// "UnloadBank".
// match: ?sub_83DE0@@YAHH@Z @ 0x00083DE0
// sp-match: ?sub_83DE0@@YAHH@Z @ 0x0006ADE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_83DE0(RwInt32 arg_0)
{
    void *var_1C;
    RwInt32 var_18;
    type_825E0_node *var_14;
    type_825E0_node *lv_10;
    RwInt32 var_C;
    type_199010 *bp_8;
    type_4B1A20 *bp_4;

    bp_4 = &dword_4B1A20[arg_0];
    if (bp_4->unk_18.unk_00.unk_00 == -1 && bp_4->unk_18.unk_00.unk_04 == -1 && !bp_4->unk_14
        && !bp_4->unk_10)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug prints out (no strings in SP; SP 0x6ADE0)
        sub_19A750("UnloadBank:Sound bank slot %d is already empty...", arg_0);
#endif
        return 1;
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    if (dword_44E870)
    {
        sub_19A750("Unloading sound bank god ID: %x,%x from slot %d", bp_4->unk_18.unk_00.unk_00,
                   bp_4->unk_18.unk_00.unk_04, arg_0);
    }
#endif
    if (bp_4->unk_00)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        if (dword_44E870)
        {
            sub_19A750("Error Unloading sound bank. The sound bank you tried to unload is still loading! Ignoring "
                       "unload request.");
        }
#endif
        return 0;
    }
    if (bp_4->unk_14)
    {
        lv_10 = bp_4->unk_14;
        while (lv_10)
        {
            var_14 = lv_10->unk_00;
            delete lv_10;
            lv_10 = var_14;
        }
        bp_4->unk_14 = 0;
    }
    var_C = bp_4->unk_10;
    if (var_C)
    {
        bp_4->unk_10 = 0;
        for (var_18 = 0; var_18 < 0x3E8; var_18++)
        {
            if (dword_44C4E8[var_18])
            {
                var_1C = ((type_44C4E8 *)dword_44C4E8[var_18])->unk_50;
                if (var_1C && RwaWaveDictContainsWave(var_C, var_1C))
                {
                    SoundEmitter_Stop((type_44C4E8 *)dword_44C4E8[var_18], 0);
                    sub_23B8F0((type_44C4E8 *)dword_44C4E8[var_18], 0);
                    if (dword_44E8B4 == dword_44C4E8[var_18])
                    {
                        dword_44E8B4 = 0;
                    }
                }
            }
        }
        sub_86350();
        sub_83B50();
        sub_23C700(var_C);
        RwaWaveDictDestroy(var_C);
    }
    bp_8 = sub_198710((type_3DF8D8_04 *)(&bp_4->unk_18.unk_00));
    if (bp_8 && bp_8->vf_08() == 0x13)
    {
        sub_198F00((type_3DF8D8_04 *)(&bp_8->unk_04));
    }
    sub_83C60(&bp_4->unk_18);
    return 1;
}

// match: ??1type_825E0_node@@QAE@XZ @ 0x00084020
#ifdef CODFH_SP
inline // SP has no out-of-line copy: SP 0x6ADE0 expands it
#endif
type_825E0_node::~type_825E0_node()
{
    unk_0C->unk_1A--;
    if (!unk_0C->unk_1A)
    {
        sub_198F00((type_3DF8D8_04 *)(&unk_04));
    }
    unk_00 = 0;
    unk_0C = 0;
    unk_04.unk_00 = 0;
    unk_04.unk_04 = 0;
}

// match: ?sub_84090@@YAHPAUtype_825E0_id@@0@Z @ 0x00084090
// sp-match: ?sub_84090@@YAHPAUtype_825E0_id@@0@Z @ 0x000698F0
RwInt32 sub_84090(type_825E0_id *arg_0, type_825E0_id *arg_4)
{
    RwInt32 var_4;

    if (arg_0->unk_00 == arg_4->unk_00 && arg_0->unk_04 == arg_4->unk_04)
    {
        var_4 = 1;
    }
    else
    {
        var_4 = 0;
    }
    return var_4;
}

// The wave of the sound arg_0 in a loaded bank, or 0.
// match: ?sub_840D0@@YAHPAUtype_199010@@@Z @ 0x000840D0
// sp-match: ?sub_840D0@@YAHPAUtype_199010@@@Z @ 0x00069910
RwInt32 sub_840D0(type_199010 *arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        for (local_8 = 0; local_8 < SOUND_BANK_SLOTS; local_8++)
        {
            if (dword_4B1A20[local_8].unk_10 && sub_84090(&arg_0->unk_2C[var_4].unk_00, &dword_4B1A20[local_8].unk_18.unk_00))
            {
                return RwaWaveDictFindWaveByIndex(dword_4B1A20[local_8].unk_10, arg_0->unk_2C[var_4].unk_08);
            }
        }
    }
    return 0;
}

// match: ?sub_84170@@YAXHH@Z @ 0x00084170
// sp-match: ?sub_84170@@YAXHH@Z @ 0x00069980
void sub_84170(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (dword_44C4E8[var_4] == arg_4)
        {
            dword_44D4E0[var_4] = arg_0;
            break;
        }
    }
}

// Moves dword_428E2C on to the next bank request in use.
// match: ?sub_841C0@@YAXXZ @ 0x000841C0
// sp-match: ?sub_841C0@@YAXXZ @ 0x000699B0
void sub_841C0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 10; var_4++)
    {
        dword_428E2C++;
        if (dword_428E2C >= 10)
        {
            dword_428E2C = 0;
        }
        if (dword_4B1B60[dword_428E2C].unk_00.unk_00 != -1 && dword_4B1B60[dword_428E2C].unk_00.unk_04 != -1)
        {
            break;
        }
    }
}

// match: ?sub_84230@@YAXPAUtype_84230@@@Z @ 0x00084230
// sp-match: ?sub_84230@@YAXPAUtype_84230@@@Z @ 0x00069A70
// Clears the load request arg_0.
void sub_84230(type_84230 *arg_0)
{
    arg_0->unk_00.unk_00.unk_00 = -1;
    arg_0->unk_00.unk_00.unk_04 = -1;
    arg_0->unk_00.unk_08 = -1;
    arg_0->unk_00.unk_0C = -1;
    arg_0->unk_210 = 0;
    arg_0->unk_214 = 0;
}

// Drops the first bank request, moving the rest up.
// match: ?sub_84280@@YAXXZ @ 0x00084280
// sp-match: ?sub_84280@@YAXXZ @ 0x0006AF20
void sub_84280()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x13; var_4++)
    {
        dword_4AF038[var_4] = dword_4AF038[var_4 + 1];
    }
    sub_84230(&dword_4AF038[0x13]);
    if (dword_4AF038[0].unk_00.unk_0C >= 0)
    {
        sub_858E0(dword_4AF038[0].unk_110, dword_4AF038[0].unk_10, dword_4AF038[0].unk_00.unk_0C);
    }
}

// Queues the bank request arg_0.
// match: ?sub_84300@@YAXPAUtype_825E0@@@Z @ 0x00084300
// sp-match: ?sub_84300@@YAXPAUtype_825E0@@@Z @ 0x0006AF70
void sub_84300(type_825E0 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x14; var_4++)
    {
        if (arg_0->unk_08 < 0)
        {
            return;
        }
        if (dword_4AF038[var_4].unk_00.unk_00.unk_00 == -1 && dword_4AF038[var_4].unk_00.unk_00.unk_04 == -1)
        {
            dword_4AF038[var_4].unk_00 = *arg_0;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
            // Single player compiles the debug prints out (SP 0x6AF70).
            if (dword_44E870)
            {
                sub_19A750("^^^^^^^ADDING BANK %d TO SOUND BANK LOADING QUEUE^^^^^^^^^^^^", arg_0->unk_0C);
            }
#endif
            sub_858E0(dword_4AF038[var_4].unk_110, dword_4AF038[var_4].unk_10, dword_4AF038[var_4].unk_00.unk_0C);
            return;
        }
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Too many things in the sound bank loading queue!!!");
#endif
}

// "LoadSoundBankAsynchronously".
// match: ?sub_843F0@@YAXXZ @ 0x000843F0
// sp-match: ?sub_843F0@@YAXXZ @ 0x0006AFF0
void sub_843F0()
{
    RwInt32 var_4;
    type_4B1A20 *v8;
    RwInt32 varC;

    var_4 = dword_4AF038[0].unk_00.unk_00.unk_00 != -1 && dword_4AF038[0].unk_00.unk_00.unk_04 != -1;
    if (!var_4 && dword_4AF24C != 7)
    {
        return;
    }
    v8 = 0;
    varC = dword_4AF038[0].unk_00.unk_08;
    v8 = &dword_4B1A20[varC];
    switch (dword_4AF24C)
    {
    case 0:
        if (dword_44E8CC)
        {
            dword_4B86F8 |= 8;
        }
        dword_4AF24C = 1;
        break;
    case 1:
        sub_16D7F0(0x29);
        if (dword_44E8D0)
        {
            dword_4B86F8 |= 8;
        }
        if (v8->unk_14 || v8->unk_10)
        {
            if (v8->unk_18.unk_00.unk_00 == dword_4AF038[0].unk_00.unk_00.unk_00
                && v8->unk_18.unk_00.unk_04 == dword_4AF038[0].unk_00.unk_00.unk_04)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x6AFF0)
                sub_19A750("LoadSoundBankAsynchronously: Bank %d is already loaded in slot %d!! Ignoring load request...",
                           dword_4AF038[0].unk_00.unk_0C, dword_4AF038[0].unk_00.unk_08);
#endif
                sub_84280();
                sub_6B5F0("SoundBankLoaded", 0, 0, 0, 0, 0, 1, 0);
                v8->unk_00 = 0;
                sub_16D850(0x29);
                break;
            }
            sub_83DE0(varC);
        }
        dword_44D4A4 = 0;
        dword_44D4B4 = 0;
        dword_44D4DC++;
        dword_4F30A4 = 0;
        dword_4AF24C = 2;
        sub_16D850(0x29);
        break;
    case 2:
        sub_81EB0(1, dword_4AF038[0].unk_10, 0);
        dword_4AF24C = 3;
        break;
    case 7:
        v8->unk_00 = 0;
        sub_84280();
        sub_6B5F0("SoundBankLoaded", 0, 0, 0, 0, 0, 1, 0);
        dword_44D49C++;
        sub_16D850(0x30);
        break;
    }
}

// Silences the effects: each playing voice's volume becomes its sound's
// volume scaled by (100 - unk_13)%, and the music players' -1.
// match: ?sub_84610@@YAXXZ @ 0x00084610
// sp-match: ?sub_84610@@YAXXZ @ 0x00069AA0
void sub_84610()
{
    RwReal var_4;
    RwInt32 v8;
    RwInt32 varC;

    for (v8 = 0; v8 < 0x3E8; v8++)
    {
        if (dword_44C4E8[v8] && ((((type_44C4E8 *)dword_44C4E8[v8])->unk_34 & 2) != 0) != 0)
        {
#ifdef CODFH_SP // shape:
            RwReal sp_a = (100 - ((type_199010 *)dword_44D4E0[v8])->unk_13) / 100.0f;
            RwReal sp_b = ((type_199010 *)dword_44D4E0[v8])->unk_10 / 100.0f;
            var_4 = sp_a * sp_b;
#else
            var_4 = (100 - ((type_199010 *)dword_44D4E0[v8])->unk_13) / 100.0f
                    * (((type_199010 *)dword_44D4E0[v8])->unk_10 / 100.0f);
#endif
            do
            {
                ((type_44C4E8 *)dword_44C4E8[v8])->unk_40 = var_4;
                if (((type_44C4E8 *)dword_44C4E8[v8])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[v8])->unk_30, 5, 1, var_4);
                }
            } while (0);
        }
    }
    for (varC = 0; varC < 3; varC++)
    {
        dword_44E8D8[varC].sub_86890(-1.0f);
    }
    dword_44E8C0 = 1;
}

// Whether the first music player is playing (asked three times).
// match: ?sub_84730@@YAHXZ @ 0x00084730
// sp-match: ?sub_84730@@YAHXZ @ 0x00069B60
RwInt32 sub_84730()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_44E8D8->unk_248 && dword_44E8D8->unk_248->unk_10)
        {
            return 1;
        }
    }
    return 0;
}

// Sets the effects' volumes from the music volume.
// match: ?sub_84770@@YAXXZ @ 0x00084770
// sp-match: ?sub_84770@@YAXXZ @ 0x00069B90
void sub_84770()
{
    RwInt32 var_4;
    RwReal v8;
    RwInt32 varC;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (dword_44C4E8[var_4] && ((((type_44C4E8 *)dword_44C4E8[var_4])->unk_34 & 2) != 0) != 0
            && dword_44C4E8[var_4] != dword_44E8BC && dword_44C4E8[var_4] != dword_44E8B8)
        {
            v8 = (((type_199010 *)dword_44D4E0[var_4])->unk_10 / 100.0f) * (1.0f - flt_44E88C);
            do
            {
                ((type_44C4E8 *)dword_44C4E8[var_4])->unk_40 = v8;
                if (((type_44C4E8 *)dword_44C4E8[var_4])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[var_4])->unk_30, 5, 1, v8);
                }
            } while (0);
        }
    }
    for (varC = 0; varC < 3; varC++)
    {
        dword_44E8D8[varC].sub_86890(flt_44E890);
    }
}

// Sets the effects' pitches (dword_428E30 scales them).
// match: ?sub_848A0@@YAXXZ @ 0x000848A0
// sp-match: ?sub_848A0@@YAXXZ @ 0x0006B190
void sub_848A0()
{
    RwInt32 var_4;
    RwInt32 v8;
    RwReal stk_C;
    RwInt32 var_10;

    for (v8 = 0; v8 < 0x3E8; v8++)
    {
        if (dword_44C4E8[v8] && ((((type_44C4E8 *)dword_44C4E8[v8])->unk_34 & 2) != 0) != 0
            && dword_44C4E8[v8] != dword_44E8BC && dword_44C4E8[v8] != dword_44E8B8)
        {
            stk_C = ((type_199010 *)dword_44D4E0[v8])->unk_1C * flt_428E30;
#ifndef CODFH_SP // single player compiles the debug trace out (no string in SP; SP 0x6B190)
            sub_84C40("RwaVirtualVoiceSetFreq(sm_VirtualVoiceMasterList[i], TempPitch);");
#endif
            sub_170ED0(&stk_C);
            do
            {
                ((type_44C4E8 *)dword_44C4E8[v8])->unk_3C = stk_C;
                if (((type_44C4E8 *)dword_44C4E8[v8])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[v8])->unk_30, 4, 1, stk_C);
                }
            } while (0);
        }
    }
    for (var_10 = 0; var_10 < 3; var_10++)
    {
        var_4 = sub_240120(dword_44E8D8[var_10].unk_104);
        if (var_4 == 6)
        {
            sub_2401B0(dword_44E8D8[var_10].unk_104, flt_428E34);
        }
    }
}

// Sets the effects' volumes from flt_44D4D0 (all but dword_44E8B8).
// match: ?sub_84A00@@YAXXZ @ 0x00084A00
void sub_84A00()
{
    RwInt32 var_4;
    RwReal v8;
    RwInt32 varC;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (dword_44C4E8[var_4] && ((((type_44C4E8 *)dword_44C4E8[var_4])->unk_34 & 2) != 0) != 0
            && dword_44C4E8[var_4] != dword_44E8B8)
        {
            v8 = ((type_199010 *)dword_44D4E0[var_4])->unk_10 / 100.0f * (1.0f - flt_44D4D0);
            sub_84C40("RwaVirtualVoiceSetGain(sm_VirtualVoiceMasterList[i], TempVol);");
            do
            {
                ((type_44C4E8 *)dword_44C4E8[var_4])->unk_40 = v8;
                if (((type_44C4E8 *)dword_44C4E8[var_4])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[var_4])->unk_30, 5, 1, v8);
                }
            } while (0);
        }
    }
    for (varC = 0; varC < 3; varC++)
    {
        dword_44E8D8[varC].sub_86890(flt_44D4BC);
    }
}

// Likewise from flt_44E5E8.
// match: ?sub_84B20@@YAXXZ @ 0x00084B20
// sp-match: ?sub_84B20@@YAXXZ @ 0x0006B260
void sub_84B20()
{
    RwInt32 var_4;
    RwReal v8;
    RwInt32 varC;

    for (var_4 = 0; var_4 < 0x3E8; var_4++)
    {
        if (dword_44C4E8[var_4] && ((((type_44C4E8 *)dword_44C4E8[var_4])->unk_34 & 2) != 0) != 0
            && dword_44C4E8[var_4] != dword_44E8B8)
        {
            v8 = (((type_199010 *)dword_44D4E0[var_4])->unk_10 / 100.0f) * (1.0f - flt_44E5E8);
#ifndef CODFH_SP // single player compiles the debug trace out (no string in SP; SP 0x6B260)
            sub_84C40("RwaVirtualVoiceSetGain(sm_VirtualVoiceMasterList[i], TempVol);");
#endif
            do
            {
                ((type_44C4E8 *)dword_44C4E8[var_4])->unk_40 = v8;
                if (((type_44C4E8 *)dword_44C4E8[var_4])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[var_4])->unk_30, 5, 1, v8);
                }
            } while (0);
        }
    }
    for (varC = 0; varC < 3; varC++)
    {
        dword_44E8D8[varC].sub_86890(flt_44E824);
    }
}

// match: ?sub_84C40@@YAXPBD@Z @ 0x00084C40
void sub_84C40(const RwChar *arg_0)
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // MP only: single player compiles the debug print out (an empty function folded into sp_nullsub_1, SP 0xC2A96 calls it)
    if (dword_44E888)
    {
        sub_19A750("<<[%d]---==$$##: %s\n", dword_4B87D8, arg_0);
    }
#endif
}

// Fades the effects: arg_0 + 1 over flt_44D488, clamped to [0, 1].
// match: ?sub_84C70@@YAXM@Z @ 0x00084C70
// sp-match: ?sub_84C70@@YAXM@Z @ 0x00069C40
void sub_84C70(RwReal arg_0)
{
    RwReal var_4;
    RwInt32 v8;
    RwReal stk_C;
    RwInt32 var_10;

    var_4 = (arg_0 + 1.0f) / flt_44D488;
    if (var_4 > 1.0f)
    {
        var_4 = 1.0f;
    }
    if (var_4 < 0.0f)
    {
        var_4 = 0.0f;
    }
    for (v8 = 0; v8 < 0x3E8; v8++)
    {
        if (dword_44C4E8[v8] && ((((type_44C4E8 *)dword_44C4E8[v8])->unk_34 & 2) != 0) != 0)
        {
#ifdef CODFH_SP // shape:
            RwReal sp_b = ((type_199010 *)dword_44D4E0[v8])->unk_10 / 100.0f;
            stk_C = sp_b * (1.0f - (1.0f - var_4) * flt_44E5E8);
#else
            stk_C = ((type_199010 *)dword_44D4E0[v8])->unk_10 / 100.0f * (1.0f - (1.0f - var_4) * flt_44E5E8);
#endif
            do
            {
                ((type_44C4E8 *)dword_44C4E8[v8])->unk_40 = stk_C;
                if (((type_44C4E8 *)dword_44C4E8[v8])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[v8])->unk_30, 5, 1, stk_C);
                }
            } while (0);
        }
    }
    for (var_10 = 0; var_10 < 3; var_10++)
    {
        dword_44E8D8[var_10].sub_86C40(-1.0f);
    }
}

// Sets the effects' pitches from flt_44E808 (all but dword_44E8B8).
// match: ?sub_84DB0@@YAXXZ @ 0x00084DB0
// sp-match: ?sub_84DB0@@YAXXZ @ 0x00069D30
void sub_84DB0()
{
    RwInt32 var_4;
    RwInt32 v8;
    RwReal stk_C;
    RwInt32 var_10;

    for (v8 = 0; v8 < 0x3E8; v8++)
    {
        if (dword_44C4E8[v8] && ((((type_44C4E8 *)dword_44C4E8[v8])->unk_34 & 2) != 0) != 0
            && dword_44C4E8[v8] != dword_44E8B8)
        {
            stk_C = ((type_199010 *)dword_44D4E0[v8])->unk_1C * flt_44E808;
#ifndef CODFH_SP // single player compiles the debug trace out (no string in SP; SP 0x69D30)
            sub_84C40("RwaVirtualVoiceSetFreq(sm_VirtualVoiceMasterList[i], TempPitch);");
#endif
            sub_170ED0(&stk_C);
            do
            {
                ((type_44C4E8 *)dword_44C4E8[v8])->unk_3C = stk_C;
                if (((type_44C4E8 *)dword_44C4E8[v8])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[v8])->unk_30, 4, 1, stk_C);
                }
            } while (0);
        }
    }
    for (var_10 = 0; var_10 < 3; var_10++)
    {
        var_4 = sub_240120(dword_44E8D8[var_10].unk_104);
        if (var_4 == 6)
        {
            sub_2401B0(dword_44E8D8[var_10].unk_104, flt_44D4A0);
        }
    }
}

// Fades the effects' pitches like sub_84C70 their volumes.
// match: ?sub_84EF0@@YAXM@Z @ 0x00084EF0
// sp-match: ?sub_84EF0@@YAXM@Z @ 0x00069DF0
void sub_84EF0(RwReal arg_0)
{
    RwInt32 var_4;
    RwReal v8;
    RwInt32 stk_C;
    RwReal var_10;
    RwInt32 lv_14;

    v8 = (arg_0 + 1.0f) / flt_44D488;
    if (v8 > 1.0f)
    {
        v8 = 1.0f;
    }
    if (v8 < 0.0f)
    {
        v8 = 0.0f;
    }
    for (stk_C = 0; stk_C < 0x3E8; stk_C++)
    {
        if (dword_44C4E8[stk_C] && ((((type_44C4E8 *)dword_44C4E8[stk_C])->unk_34 & 2) != 0) != 0)
        {
            var_10 = ((type_199010 *)dword_44D4E0[stk_C])->unk_1C * v8
                     + (1.0f - v8) * ((type_199010 *)dword_44D4E0[stk_C])->unk_1C * flt_44E808;
#ifndef CODFH_SP // single player compiles the debug trace out (no string in SP; SP 0x69DF0)
            sub_84C40("RwaVirtualVoiceSetFreq(sm_VirtualVoiceMasterList[i], TempPitch);");
#endif
            sub_170ED0(&var_10);
            do
            {
                ((type_44C4E8 *)dword_44C4E8[stk_C])->unk_3C = var_10;
                if (((type_44C4E8 *)dword_44C4E8[stk_C])->unk_30)
                {
                    RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[stk_C])->unk_30, 4, 1, var_10);
                }
            } while (0);
        }
    }
    for (lv_14 = 0; lv_14 < 3; lv_14++)
    {
        var_4 = sub_240120(dword_44E8D8[lv_14].unk_104);
        if (var_4 == 6)
        {
            sub_2401B0(dword_44E8D8[lv_14].unk_104, (1.0f - v8) * flt_44D4A0 + v8);
        }
    }
}

// match: ?sub_85090@@YAXMH@Z @ 0x00085090
// sp-match: ?sub_85090@@YAXMH@Z @ 0x0006B310
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_85090(RwReal arg_0, RwInt32 arg_4)
{
    type_44C4E8 *var_14;
    RwReal lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    sub_16D7F0(0x27);
    sub_843F0();
    sub_16D850(0x27);
    if (dword_4B8710 && !((dword_4B86F8 >> 4) & 1))
    {
        flt_4AEFF4 = flt_4AEFF4 - arg_0;
    }
    if (flt_4AEFF4 <= 0.0f)
    {
        flt_4AEFF4 = flt_428E28;
        if (!dword_44BAD0)
        {
            sub_841C0();
        }
    }
    sub_16D7F0(0x28);
    for (bp_4 = 0; bp_4 < 3; bp_4++)
    {
        dword_44E8D8[bp_4].sub_873B0();
    }
    sub_16D850(0x28);
    bp_8 = 0;
    if (dword_44E8C0)
    {
        if (dword_44E8B4)
        {
            if (((((type_44C4E8 *)dword_44E8B4)->unk_34 & 2) != 0) != 0)
            {
                bp_8 = 1;
            }
            else
            {
                bp_8 = 0;
                dword_44E8B4 = 0;
            }
        }
        if (!bp_8 && !sub_84730())
        {
            for (bp_4 = 0; bp_4 < 0x3E8; bp_4++)
            {
                if (dword_44C4E8[bp_4] && ((((type_44C4E8 *)dword_44C4E8[bp_4])->unk_34 & 2) != 0) != 0)
                {
                    // An empty branch for a sound not loaded: the check
                    // guards the gain macro as `if (!s) ; else ...`.
                    if (!dword_44D4E0[bp_4])
                    {
                    }
                    else
                    {
                        do
                        {
                            ((type_44C4E8 *)dword_44C4E8[bp_4])->unk_40 =
                                ((type_199010 *)dword_44D4E0[bp_4])->unk_10 / 100.0f;
                            if (((type_44C4E8 *)dword_44C4E8[bp_4])->unk_30)
                            {
                                RWA_SET_PARAM_REAL(((type_44C4E8 *)dword_44C4E8[bp_4])->unk_30, 5, 1,
                                           ((type_199010 *)dword_44D4E0[bp_4])->unk_10 / 100.0f);
                            }
                        } while (0);
                    }
                }
            }
            for (var_C = 0; var_C < 3; var_C++)
            {
                dword_44E8D8[var_C].sub_86C40(-1.0f);
            }
            dword_44E8C0 = 0;
        }
    }
    for (bp_4 = 0; bp_4 < 0x14; bp_4++)
    {
        if (dword_4B1CA0[bp_4].unk_04)
        {
#ifdef CODFH_SP // single player holds the delayed sounds while paused (SP 0x6B48F tests dword_4B86F8 bit 4)
            if (!((dword_4B86F8 >> 4) & 1))
            {
                lv_10 = flt_429288 * flt_3D4340 * 0.001f;
                dword_4B1CA0[bp_4].unk_00 = lv_10 + dword_4B1CA0[bp_4].unk_00;
            }
#else
            lv_10 = flt_429288 * flt_3D4340 * 0.001f;
            dword_4B1CA0[bp_4].unk_00 = lv_10 + dword_4B1CA0[bp_4].unk_00;
#endif
            if (dword_4B1CA0[bp_4].unk_00 >= dword_4B1CA0[bp_4].unk_04->unk_00 * 0.1f)
            {
                if (!dword_4B1CA0[bp_4].unk_14)
                {
                    while (dword_4B1CA0[bp_4].unk_04)
                    {
                        dword_4B1CA0[bp_4].sub_85730();
                    }
                    dword_4B1CA0[bp_4].unk_00 = 0;
                    dword_4B1CA0[bp_4].unk_14 = 0;
                    continue;
                }
                var_14 = (type_44C4E8 *)dword_4B1CA0[bp_4].unk_14->sub_8A980(
                    (type_3DF8D8_04 *)&dword_4B1CA0[bp_4].unk_04->unk_04, 0, 0x80, &dword_4B1CA0[bp_4].unk_08, 0, 0);
                if (var_14 && var_14 != (type_44C4E8 *)-1 && dword_4B1CA0[bp_4].unk_14)
                {
                    do
                    {
                        var_14->unk_58 = dword_4B1CA0[bp_4].unk_08;
                        if (var_14->unk_30)
                        {
                            Behavior_DispatchCallback(var_14->unk_30, 0, 1, &dword_4B1CA0[bp_4].unk_08);
                        }
                    } while (0);
                }
                dword_4B1CA0[bp_4].sub_85730();
            }
        }
    }
    switch (dword_44E8A0)
    {
    case 1:
        flt_428E30 = 1.0f;
        flt_428E34 = 1.0f;
        flt_44E88C = 0;
        flt_44E890 = 0;
        dword_44E8A0 = 2;
        break;
    case 2:
        if (flt_428E30 > flt_44E810)
        {
            flt_428E30 = flt_428E30 - flt_44C0A0;
        }
        if (flt_428E30 < flt_44E810)
        {
            flt_428E30 = flt_44E810;
        }
        if (flt_428E34 > flt_44E800)
        {
            flt_428E34 = flt_428E34 - flt_44D4B8;
        }
        if (flt_428E34 < flt_44E800)
        {
            flt_428E34 = flt_44E800;
        }
        if (flt_44E88C < flt_44E80C)
        {
            flt_44E88C = flt_44E88C + flt_44C0A4;
        }
        if (flt_44E88C > flt_44E80C)
        {
            flt_44E88C = flt_44E80C;
        }
        if (flt_44E890 < flt_44E828)
        {
            flt_44E890 = flt_44E890 + flt_44D4B0;
        }
        if (flt_44E890 > flt_44E828)
        {
            flt_44E890 = flt_44E828;
        }
        sub_84770();
        sub_848A0();
        break;
    case 3:
        sub_84C70(flt_44D488);
        sub_84EF0(flt_44D488);
        dword_44E8A0 = 0;
        break;
    }
    switch (dword_44E898)
    {
    case 1:
        sub_84B20();
        sub_84DB0();
        dword_4B1F58 = sub_1745A0(0);
        if (dword_4B1F58)
        {
            dword_4B1F54 = dword_4B1F58->unk_1C0.sub_8A980(&dword_4B1C08, dword_4B1F58, 0, dword_4B1F58->sub_CD550(), 0, 0);
        }
        dword_44E898 = 2;
        break;
    case 2:
        flt_44E894 = 0;
        break;
    case 3:
        sub_84C70(flt_44E894);
        sub_84EF0(flt_44E894);
        flt_44E894 = flt_44E894 + 1.0f;
        if (flt_44E894 >= flt_44D488)
        {
            dword_44E898 = 0;
            flt_44E894 = 0;
        }
        break;
    }
#ifndef CODFH_SP // single player pauses and resumes directly (sub_85D60, sub_860E0); SP 0x6B310 has no such switch
    switch (dword_44E89C)
    {
    case 1:
        sub_84A00();
        dword_44E89C = 2;
        break;
    case 3:
        sub_84C70(flt_44D488);
        dword_44E89C = 0;
        break;
    }
#endif
    sub_16D7F0(0x24);
    sub_86350();
    sub_83B50();
    sub_16D850(0x24);
}

// match: ?sub_857B0@@YAXM@Z @ 0x000857B0
// sp-match: ?sub_857B0@@YAXM@Z @ 0x0006B7F0
// Stops the sound system's voice (dword_4B1E98) and calls an empty method of
// each of the three music players (pDtor, not their destructor, sub_866A0).
void sub_857B0(RwReal arg_0)
{
    RwInt32 var_4;

    sub_85800(&dword_4B1E98.unk_00);
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        dword_44E8D8[var_4].pDtor();
    }
}

// match: ?sub_85800@@YAXPAPAUtype_44C4E8@@@Z @ 0x00085800
// sp-match: ?sub_85800@@YAXPAPAUtype_44C4E8@@@Z @ 0x00069F20
// Stops the voice *arg_0: fades it out when playing (sub_EAB80), else
// forgets it.
void sub_85800(type_44C4E8 **arg_0)
{
    if (*arg_0 != 0)
    {
        if ((((*arg_0)->unk_34 & 2) != 0) != 0)
        {
            sub_EAB80((const RwChar *)&byte_44E490, 0, 0.1f);
        }
        else
        {
            *arg_0 = 0;
        }
    }
}

// The sound table's files for the current language: ASLocate.agd into
// arg_0 and the language's directory into arg_4 (either may be 0).
// match: ?sub_85840@@YAXPAD0@Z @ 0x00085840
// sp-match: ?sub_85840@@YAXPAD0@Z @ 0x00069F50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_85840(RwChar *arg_0, RwChar *arg_4)
{
    RwChar var_108[0x80];
    RwChar stk_88[0x80];

    sprintf(stk_88, "d:\\Audio\\%s\\ASLocate.agd", dword_428E38[dword_44E8A8]);
    sprintf(var_108, "d:\\Audio\\%s\\", dword_428E38[dword_44E8A8]);
    if (arg_0)
    {
        sub_D7F20(arg_0, stk_88);
    }
    if (arg_4)
    {
        sub_D7F20(arg_4, var_108);
    }
}

// The bank arg_8's two files: its .agd into arg_0 and its .awd into arg_4
// (banks are grouped by thirty).
// match: ?sub_858E0@@YAXPAD0F@Z @ 0x000858E0
// sp-match: ?sub_858E0@@YAXPAD0F@Z @ 0x00069FF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_858E0(RwChar *arg_0, RwChar *arg_4, RwInt16 arg_8)
{
    RwChar var_288[0x80];
    RwChar lv_208[0x80];
    RwChar var188[0x80];
    RwChar var_108[0x80];
    RwChar stk_88[0x80];

    sprintf(stk_88, "%.4d.awd", arg_8);
    sprintf(lv_208, "%.4d.agd", arg_8);
    sprintf(var188, "%d_%d\\", arg_8 / 30 * 30, arg_8 / 30 * 30 + 29);
    sprintf(var_288, "d:\\%s%s%s%s%s", "SB_AWD\\", var188, dword_428E38[dword_44E8A8], "\\XBX_", stk_88);
    sprintf(var_108, "d:\\%s%s%s%s%s", "SB_AGD\\", var188, dword_428E38[dword_44E8A8], "\\XBX_", lv_208);
    sub_D7F20(arg_0, var_108);
    sub_D7F20(arg_4, var_288);
}

// match: ?sub_83760@type_4B1CA0@@QAEXXZ @ 0x00083760
// sp-match: ?sub_83760@type_4B1CA0@@QAEXXZ @ 0x0006A390
// (Defined in the class, in soundbank.h.)

// match: ?sub_85730@type_4B1CA0@@QAEXXZ @ 0x00085730
// (Defined in the class, in soundbank.h.)

// match: ?sub_85A00@type_4B1CA0@@QAEXPAUtype_825E0_id@@M@Z @ 0x00085A00
// sp-match: ?sub_85A00@type_4B1CA0@@QAEXPAUtype_825E0_id@@M@Z @ 0x0006A110
void type_4B1CA0::sub_85A00(type_825E0_id *arg_0, RwReal arg_4)
{
    type_837D0 *var_4;
    type_837D0 *v8;
    type_837D0 *varC;

    if (!unk_04)
    {
        unk_04 = new (4) type_837D0;
        unk_04->unk_0C = 0;
        unk_04->unk_00 = arg_4;
        unk_04->unk_04.unk_00 = arg_0->unk_00;
        unk_04->unk_04.unk_04 = arg_0->unk_04;
        return;
    }
    v8 = unk_04;
    var_4 = 0;
    varC = new (4) type_837D0;
    varC->unk_00 = arg_4;
    varC->unk_04.unk_00 = arg_0->unk_00;
    varC->unk_04.unk_04 = arg_0->unk_04;
    varC->unk_0C = 0;
    while (v8)
    {
        if (arg_4 < v8->unk_00)
        {
            if (v8 == unk_04)
            {
                varC->unk_0C = unk_04;
                unk_04 = varC;
                return;
            }
            varC->unk_0C = v8;
            var_4->unk_0C = varC;
            return;
        }
        var_4 = v8;
        v8 = v8->unk_0C;
    }
    var_4->unk_0C = varC;
}

// match: ?sub_85B90@@YAHXZ @ 0x00085B90
// sp-match: ?sub_85B90@@YAHXZ @ 0x0006A1F0
RwInt32 sub_85B90()
{
    RwInt32 var_4;

    dword_4B1F5C = 1;
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_44E8D8[var_4].unk_180 == 9 || dword_44E8D8[var_4].unk_180 == 0xB
            || dword_44E8D8[var_4].unk_180 == 0xA)
        {
            dword_4B1F5C = 0;
        }
    }
    return dword_4B1F5C;
}

// match: ?sub_85C10@@YAHXZ @ 0x00085C10
// sp-match: ?sub_85C10@@YAHXZ @ 0x0006A250
RwInt32 sub_85C10()
{
    RwInt32 var_4;

    dword_4B1F60 = 1;
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_44E8D8[var_4].unk_108 == 9)
        {
            continue;
        }
        if (dword_44E8D8[var_4].unk_180 != 0xB
            && (dword_44E8D8[var_4].unk_180 != 0xA || dword_44E8D8[var_4].unk_108 != 4)
            && dword_44E8D8[var_4].unk_180 != 0xF && dword_44E8D8[var_4].unk_180 != 1)
        {
            dword_4B1F60 = 0;
        }
    }
    return dword_4B1F60;
}

// match: ?sub_85CC0@@YAHXZ @ 0x00085CC0
// sp-match: ?sub_85CC0@@YAHXZ @ 0x0006A2F0
RwInt32 sub_85CC0()
{
    RwInt32 var_4;
    RwInt32 local_8;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_44E8D8[var_4].unk_108 == 2)
        {
            return 1;
        }
    }
    for (local_8 = 0; local_8 < 3; local_8++)
    {
        if (dword_44E8D8[local_8].unk_180 == 2 || dword_44E8D8[local_8].unk_180 == 5 || dword_44E8D8[local_8].unk_180 == 6)
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_85D60@@YAXXZ @ 0x00085D60
// sp-match: ?sub_85D60@@YAXXZ @ 0x0006B820
// Sets dword_44E89C and returns: the rest (pausing the playing voices,
// keeping their parameter 7, and waiting for the music players to settle)
// is dead code that the image still carries. Single player runs it.
void sub_85D60()
{
    // Names for the frame slots (tools/local_names.py).
    RwInt32 l4;
    RwInt32 var_8;
    RwInt32 fp_C;
    RwInt32 local_10;
    RwInt32 stk_14;
    RwInt32 loc18;

#ifndef CODFH_SP // single player pauses the voices (SP 0x6B820 has no early return)
    dword_44E89C = 1;
    return;
#endif
    for (var_8 = 0; var_8 < 0x3E8; var_8++)
    {
        if (dword_44C4E8[var_8])
        {
            if ((((type_44C4E8 *)dword_44C4E8[var_8])->unk_34 & 2) ? 1 : 0)
            {
                l4 = ((type_44C4E8 *)dword_44C4E8[var_8])->unk_48 =
                    ((type_44C4E8 *)dword_44C4E8[var_8])->unk_30
                            && (((type_44C4E8 *)dword_44C4E8[var_8])->unk_34 & 2)
                        ? sub_23F960(((type_44C4E8 *)dword_44C4E8[var_8])->unk_30, 7, 2, 0)
                        : ((type_44C4E8 *)dword_44C4E8[var_8])->unk_48;
                SoundEmitter_Stop((type_44C4E8 *)dword_44C4E8[var_8], 0);
                do
                {
                    ((type_44C4E8 *)dword_44C4E8[var_8])->unk_48 = l4;
                    if (((type_44C4E8 *)dword_44C4E8[var_8])->unk_30)
                    {
                        RWA_SET_PARAM_INT(((type_44C4E8 *)dword_44C4E8[var_8])->unk_30, 7, 1, l4);
                    }
                } while (0);
                if (!(var_8 % 2))
                {
                    sub_86350();
                    sub_83B50();
                }
            }
            else
            {
                sub_23B8F0((type_44C4E8 *)dword_44C4E8[var_8], 0);
            }
        }
    }
    if (sub_86090())
    {
        while (sub_85CC0())
        {
            for (fp_C = 0; fp_C < 3; fp_C++)
            {
                dword_44E8D8[fp_C].sub_873B0();
            }
            sub_86350();
            sub_83B50();
        }
        if (!dword_44E884)
        {
            for (local_10 = 0; local_10 < 3; local_10++)
            {
                if (dword_44E8D8[local_10].unk_180 != 1 && dword_44E8D8[local_10].unk_180 != 0xD
                    && dword_44E8D8[local_10].unk_180 != 0xE && dword_44E8D8[local_10].unk_180 != 0xF
                    && dword_44E8D8[local_10].unk_180 != 0x10 && dword_44E8D8[local_10].unk_180 != 0x11
                    && dword_44E8D8[local_10].unk_180 != 0x12)
                {
                    dword_44E8D8[local_10].unk_180 = 9;
                }
            }
        }
        else
        {
            for (stk_14 = 0; stk_14 < 3; stk_14++)
            {
                dword_44E480[stk_14] = dword_44E8D8[stk_14].unk_248;
                if (dword_44E8D8[stk_14].unk_180 == 7)
                {
                    dword_44E8D8[stk_14].unk_180 = 0x10;
                }
            }
        }
        if (!dword_44E884)
        {
            if (dword_44E5F0[0] || dword_44E5F0[1] || dword_44E5F0[2])
            {
                return;
            }
            while (!sub_85C10())
            {
                for (loc18 = 0; loc18 < 3; loc18++)
                {
                    dword_44E8D8[loc18].sub_873B0();
                }
                sub_86350();
                sub_83B50();
            }
        }
    }
}

// match: ?sub_86090@@YAHXZ @ 0x00086090
// sp-match: ?sub_86090@@YAHXZ @ 0x0006A340
RwInt32 sub_86090()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (dword_44E8D8[var_4].unk_108 != 9 && dword_44E8D8[var_4].unk_108 != 0)
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_860E0@@YAXXZ @ 0x000860E0
// sp-match: ?sub_860E0@@YAXXZ @ 0x0006BA60
// sub_85D60's counterpart: sets dword_44E89C to 3 and returns; the rest
// (resuming the voices, the music players' streams and the current player's
// weapon sound) is dead code that the image still carries. Single player
// runs it, after one update of the sound core.
void sub_860E0()
{
    // Names for the frame slots (tools/local_names.py).
    type_10F710 *l4;
    RwInt32 var_8;
    RwInt32 fp_C;
    RwInt32 local_10;
    RwInt32 stk_14;
    type_4C19C0 *loc18;

#ifdef CODFH_SP // single player resumes the voices (SP 0x6BA60 has no early return)
    sub_86350();
    sub_83B50();
#else
    dword_44E89C = 3;
    return;
#endif
    for (var_8 = 0; var_8 < 0x3E8; var_8++)
    {
        if (dword_44C4E8[var_8] && ((type_44C4E8 *)dword_44C4E8[var_8])->unk_50)
        {
            SoundEmitter_Stop((type_44C4E8 *)dword_44C4E8[var_8], 1);
        }
    }
    if (!dword_44E884)
    {
        if (sub_86090())
        {
            if (dword_44E5F0[0] || dword_44E5F0[1] || dword_44E5F0[2])
            {
                return;
            }
            for (fp_C = 0; fp_C < 3; fp_C++)
            {
                if (dword_44E8D8[fp_C].unk_180 == 0xB || dword_44E8D8[fp_C].unk_180 == 0xA)
                {
                    dword_44E8D8[fp_C].unk_180 = 0xC;
                }
            }
            while (!sub_85B90())
            {
                for (local_10 = 0; local_10 < 3; local_10++)
                {
                    dword_44E8D8[local_10].sub_873B0();
                }
                sub_86350();
                sub_83B50();
            }
        }
    }
    else
    {
        for (stk_14 = 0; stk_14 < 3; stk_14++)
        {
            if (dword_44E480[stk_14] && dword_44E480[stk_14]->unk_24 != -1)
            {
                dword_4B1E98.sub_8A980(&dword_44E480[stk_14]->unk_04, 0, 0, 0, 0, 0);
            }
        }
    }
    l4 = (type_10F710 *)sub_1745A0(0);
    if (l4 && l4->unk_1A48 && l4->unk_1A48[l4->unk_1AE4]->unk_46)
    {
        l4->unk_1C0.sub_8A910(l4->unk_1A48[l4->unk_1AE4]->unk_21C);
        l4->unk_1A48[l4->unk_1AE4]->unk_21C = 0;
        loc18 = l4->unk_1A48[l4->unk_1AE4]->unk_448;
        l4->unk_1C0.sub_8A980(&loc18->unk_14, l4, 1, l4->sub_CD550(), 0, 0);
        l4->unk_1A48[l4->unk_1AE4]->unk_46 = 0;
    }
}

// match: ?sub_86350@@YAXXZ @ 0x00086350
// sp-match: ?sub_86350@@YAXXZ @ 0x0006A370
void sub_86350()
{
    bool var_1;

    var_1 = true;
    if (var_1)
    {
        RwaCoreUpdate();
    }
}

// match: ??0type_4B1CA0@@QAE@XZ @ 0x00086370
// sp-match: ??0type_4B1CA0@@QAE@XZ @ 0x0006A380
type_4B1CA0::type_4B1CA0()
{
    unk_04 = 0;
    unk_00 = 0;
    unk_14 = 0;
}

// match: ??1type_4B1CA0@@QAE@XZ @ 0x000863A0
type_4B1CA0::~type_4B1CA0()
{
    sub_83760();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_170ED0@@YAHPAM@Z (folded into 0x170ED0)
#ifndef CODFH_SP // single player calls it (SP 0x69D30 calls the folded SP 0x6CEB0); a body here lets /O2 drop the calls
RwInt32 sub_170ED0(RwReal * arg_0)
{
    return 0;
}
#endif


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
struct type_3DF8D8_04_data;
// 0x0044E720: dword_44E600 + 0x120
RwInt32 (&dword_44E720)[8] = *(RwInt32 (*)[8])((RwUInt8 *)&dword_44E600 + 0x120);
// 0x004B1C68: dword_4B1C60 + 0x8
type_3DF8D8_04_data &dword_4B1C68 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B1C60 + 0x8);
// 0x004B1C70: dword_4B1C60 + 0x10
type_3DF8D8_04_data &dword_4B1C70 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B1C60 + 0x10);
// 0x004B1F2C: dword_4B1F24 + 0x8
type_3DF8D8_04_data &dword_4B1F2C = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B1F24 + 0x8);
// 0x004B1F34: dword_4B1F24 + 0x10
type_3DF8D8_04_data &dword_4B1F34 = *(type_3DF8D8_04_data *)((RwUInt8 *)&dword_4B1F24 + 0x10);
#endif
