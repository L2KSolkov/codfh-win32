// Split from unit_188380.cpp at 0x18AF40, where the image starts another object (the memory
// card messages): its .rdata begins at 0x3DF2DC with its own 16.666666, the unreferenced
// constant every game object starts its constants with (PLAN M7).

#include "game/xboxlive.h"
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/functions.h"
#include "game/waitscreen.h"
#include "game/data.h"
#include "game/objectives.h"
#include "game/gameloop.h"
#include <string.h>
#include <stdio.h>
#include "xbox/xapi.h"
#include "rw/baengine.h"
#include "rw/osintf.h"
#include <stdlib.h>
#include "rws/gftime.h"
#include "types/type_DA0A0.h"
#include "types/type_DA580.h"
#include "types/type_DC400.h"
#include "types/soundbank.h"
#include "types/type_10F710.h"
#include "types/PlayerTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DF2DC
extern const RwReal flt_3DF2DC = 16.666666f;

// match: ?flt_3DF2DC@@3MB @ 0x003DF2DC


// match: ?sub_18AF40@@YAPADPAD@Z @ 0x0018AF40
// match: ??_C@_0CA@PGPFOFHK@shell?2fend?2instance?2xbox?2mc?4csv?$AA@ @ 0x003DF2E0
// match: ??_C@_0BG@PMAAKHNO@$MCNoControllerLineUS?$AA@ @ 0x003DF300
// match: ??_C@_0M@NCHCOIAH@$MCExitFree?$AA@ @ 0x003DF318
// match: ??_C@_0BB@GAEDHDGA@$MCUnknownDevice?$AA@ @ 0x003DF324
// match: ??_C@_0P@LHNKEPHB@$MCSaveCorrupt?$AA@ @ 0x003DF338
// match: ??_C@_0BG@EBBMAKMC@$MCLoadProfileWarning?$AA@ @ 0x003DF348
// match: ??_C@_0BE@BMKGHLLA@$MCResetDataWarning?$AA@ @ 0x003DF360
// match: ??_C@_0L@BCHHHKDP@$MCWarning?$AA@ @ 0x003DF374
// match: ??_C@_0BK@EDJDOPNF@$MCMenuButtonChangeOption?$AA@ @ 0x003DF380
// match: ??_C@_0BG@LPHPDPJD@$MCMenuButtonNavigate?$AA@ @ 0x003DF39C
// match: ??_C@_0BF@BCPBCLIA@$MCMenuButtonUnPause?$AA@ @ 0x003DF3B4
// match: ??_C@_0BE@OLCGDNCN@$MCMenuButtonCancel?$AA@ @ 0x003DF3CC
// match: ??_C@_0BE@MOFEALKC@$MCMenuButtonSelect?$AA@ @ 0x003DF3E0
// match: ??_C@_0BE@FCHHPHFO@$MCNoControllerLine?$AA@ @ 0x003DF3F4
// match: ??_C@_0BJ@CMBNCLHJ@$MCDupProfilesNotAllowed?$AA@ @ 0x003DF408
// match: ??_C@_0BJ@INIPJGDL@$MCDupProfileNameEntered?$AA@ @ 0x003DF424
// match: ??_C@_0P@MPBNOFC@$MCConfirmSave?$AA@ @ 0x003DF440
// match: ??_C@_0L@DDOKHJFN@$MCCheckOK?$AA@ @ 0x003DF450
// match: ??_C@_0BH@CNHEHNBP@$MCSelectCreateNewSlot?$AA@ @ 0x003DF45C
// match: ??_C@_0BC@IKKAJMFF@$MCSelectLoadSlot?$AA@ @ 0x003DF474
// match: ??_C@_0BC@IFHGHCCC@$MCSelectSaveSlot?$AA@ @ 0x003DF488
// match: ??_C@_0N@CJFEAPBH@$MCEmptySlot?$AA@ @ 0x003DF49C
// match: ??_C@_0BC@LHHIGKND@$MCAutosaveFailed?$AA@ @ 0x003DF4AC
// match: ??_C@_05GDKDKFPF@$MCNo?$AA@ @ 0x003DF4C0
// match: ??_C@_06JPPGFPD@$MCYes?$AA@ @ 0x003DF4C8
// match: ??_C@_0P@OKJIMOFC@$MCCardChanged?$AA@ @ 0x003DF4D0
// match: ??_C@_0P@JJFJEHBG@$MCCardRemoved?$AA@ @ 0x003DF4E0
// match: ??_C@_0P@NHAMKHAJ@$MCLoadNewGame?$AA@ @ 0x003DF4F0
// match: ??_C@_0BE@PEAGIAJC@$MCContinueWOSaving?$AA@ @ 0x003DF500
// match: ??_C@_0BF@NMMHMIL@$MCOverwriteContinue?$AA@ @ 0x003DF514
// match: ??_C@_0BI@EIFJJABE@$MCOverwriteNewContinue?$AA@ @ 0x003DF52C
// match: ??_C@_05JDIJCOGE@$MCOK?$AA@ @ 0x003DF544
// match: ??_C@_09OMICBKMH@$MCCancel?$AA@ @ 0x003DF54C
// match: ??_C@_08FMNBJIKN@$MCRetry?$AA@ @ 0x003DF558
// match: ??_C@_09EEGNGJCF@$MCFormat?$AA@ @ 0x003DF564
// match: ??_C@_09CBDJBION@$MCDelete?$AA@ @ 0x003DF570
// match: ??_C@_0M@FHMJGELD@$MCContinue?$AA@ @ 0x003DF57C
// match: ??_C@_0BF@EMINDFMI@$MCAutosaveReconfirm?$AA@ @ 0x003DF588
// match: ??_C@_0BA@KKLMJHOP@$MCDataRequired?$AA@ @ 0x003DF5A0
// match: ??_C@_0N@IBCBIMJ@$MCCorrupted?$AA@ @ 0x003DF5B0
// match: ??_C@_0BA@LKHFINCC@$MCCorruptedNew?$AA@ @ 0x003DF5C0
// match: ??_C@_0BE@LNEIBJBI@$MCAutosaveDisabled?$AA@ @ 0x003DF5D0
// match: ??_C@_0O@KCJDONPG@$MCAutosaving?$AA@ @ 0x003DF5E4
// match: ??_C@_0BI@BECKDKPI@$MCFormatFailedContinue?$AA@ @ 0x003DF5F4
// match: ??_C@_0BA@DDLAONCI@$MCFormatFailed?$AA@ @ 0x003DF60C
// match: ??_C@_0M@LENGBBEF@$MCFormatOK?$AA@ @ 0x003DF61C
// match: ??_C@_0BA@EDBCIEMB@$MCFormatCancel?$AA@ @ 0x003DF628
// match: ??_C@_0O@FDIBNKAM@$MCFormatting?$AA@ @ 0x003DF638
// match: ??_C@_0BB@NEHIINCH@$MCConfirmFormat?$AA@ @ 0x003DF648
// match: ??_C@_0BF@MLMHNILB@$MCFormattedRequired?$AA@ @ 0x003DF65C
// match: ??_C@_0P@EFPGMGNB@$MCUnformatted?$AA@ @ 0x003DF674
// match: ??_C@_0BL@GMOPCCMN@$MCOverwriteFailedContinue?$AA@ @ 0x003DF684
// match: ??_C@_0BD@FLADINCO@$MCOverwriteFailed?$AA@ @ 0x003DF6A0
// match: ??_C@_0P@PLBCFDGI@$MCOverwriteOK?$AA@ @ 0x003DF6B4
// match: ??_C@_0P@LBHKKLKJ@$MCOverwriting?$AA@ @ 0x003DF6C4
// match: ??_C@_0BG@DEHDJMAC@$MCSaveFailedContinue?$AA@ @ 0x003DF6D4
// match: ??_C@_0O@MNDHEDJG@$MCSaveFailed?$AA@ @ 0x003DF6EC
// match: ??_C@_09BBLIHEMF@$MCSaveOK?$AA@ @ 0x003DF6FC
// match: ??_C@_09FLNAIMAE@$MCSaving?$AA@ @ 0x003DF708
// match: ??_C@_0BA@BPGLBBHC@$MCWrongVersion?$AA@ @ 0x003DF714
// match: ??_C@_0BI@CBKLADOA@$MCCreateFailedContinue?$AA@ @ 0x003DF724
// match: ??_C@_0BA@HHJPLFGE@$MCCreateFailed?$AA@ @ 0x003DF73C
// match: ??_C@_0M@IMOBDKMD@$MCCreateOK?$AA@ @ 0x003DF74C
// match: ??_C@_0BF@HDGHKPCK@$MCNewGameOKAutosave?$AA@ @ 0x003DF758
// match: ??_C@_0M@MGIJMCAC@$MCCreating?$AA@ @ 0x003DF770
// match: ??_C@_0BC@MHBIAEEB@$MCCreateSaveFile?$AA@ @ 0x003DF77C
// match: ??_C@_0O@OKPLGMAO@$MCLoadFailed?$AA@ @ 0x003DF790
// match: ??_C@_09NAFINFGF@$MCLoadOK?$AA@ @ 0x003DF7A0
// match: ??_C@_0L@KMGLEEIL@$MCLoading?$AA@ @ 0x003DF7AC
// match: ??_C@_0BH@IENCNJLH@$MCCheckFailedContinue?$AA@ @ 0x003DF7B8
// match: ??_C@_0P@OAPGGHLM@$MCCheckFailed?$AA@ @ 0x003DF7D0
// match: ??_C@_0M@IEIKEOLJ@$MCChecking?$AA@ @ 0x003DF7E0
// match: ??_C@_0BD@LJLPJCPF@$MCNoSpaceContinue?$AA@ @ 0x003DF7EC
// match: ??_C@_0L@MNMGANCM@$MCNoSpace?$AA@ @ 0x003DF800
// match: ??_C@_0BK@PGAOCOAI@$MCNoCardSaveContinueGame?$AA@ @ 0x003DF80C
// match: ??_C@_0BG@KJHNMHPO@$MCNoCardSaveContinue?$AA@ @ 0x003DF828
// match: ??_C@_0O@EGAMMGDK@$MCNoCardLoad?$AA@ @ 0x003DF840
// match: ??_C@_0O@EEBBDFOO@$MCNoCardSave?$AA@ @ 0x003DF850
// match: ??_C@_06GBJPAJP@?$CFname?$CF?$AA@ @ 0x003DF860
// match: ??_C@_0BL@HHILJDNL@ERROR?3?5MC_SelectSlotMenu?$CI?$CJ?$AA@ @ 0x003DF868
// match: ??_C@_0EM@PCPKKLE@RwaOsOutputSetSpeakerConfig?5?5?$CIAu@ @ 0x003DF888
// sp-match: ?sub_18AF40@@YAPADPAD@Z @ 0x0011EE40
// Loads the memory card messages (shell\fend\instance\xbox\mc.csv) into
// dword_4F2370, into arg_0 when given; the strings. $MCExitFree takes
// $MCSaveCorrupt's string, and dword_4F249C is not loaded.
RwChar *sub_18AF40(RwChar *arg_0)
{
    type_18A470 var_278[] =
    {
        {"$MCNoCardSave", &dword_4F2370[0]},
        {"$MCNoCardLoad", &dword_4F2370[1]},
        {"$MCNoCardSaveContinue", &dword_4F2370[2]},
        {"$MCNoCardSaveContinueGame", &dword_4F2370[3]},
        {"$MCNoSpace", &dword_4F2370[4]},
        {"$MCNoSpaceContinue", &dword_4F2370[5]},
        {"$MCChecking", &dword_4F2370[6]},
        {"$MCCheckFailed", &dword_4F2370[7]},
        {"$MCCheckFailedContinue", &dword_4F2370[8]},
        {"$MCLoading", &dword_4F2370[9]},
        {"$MCLoadOK", &dword_4F2370[10]},
        {"$MCLoadFailed", &dword_4F2370[11]},
        {"$MCCreateSaveFile", &dword_4F2370[12]},
        {"$MCCreating", &dword_4F2370[13]},
        {"$MCNewGameOKAutosave", &dword_4F2370[14]},
        {"$MCCreateOK", &dword_4F2370[15]},
        {"$MCCreateFailed", &dword_4F2370[16]},
        {"$MCCreateFailedContinue", &dword_4F2370[17]},
        {"$MCWrongVersion", &dword_4F2370[18]},
        {"$MCSaving", &dword_4F2370[19]},
        {"$MCSaveOK", &dword_4F2370[20]},
        {"$MCSaveFailed", &dword_4F2370[21]},
        {"$MCSaveFailedContinue", &dword_4F2370[22]},
        {"$MCOverwriting", &dword_4F2370[23]},
        {"$MCOverwriteOK", &dword_4F2370[24]},
        {"$MCOverwriteFailed", &dword_4F2370[25]},
        {"$MCOverwriteFailedContinue", &dword_4F2370[26]},
        {"$MCUnformatted", &dword_4F2370[27]},
        {"$MCFormattedRequired", &dword_4F2370[28]},
        {"$MCConfirmFormat", &dword_4F2370[29]},
        {"$MCFormatting", &dword_4F2370[30]},
        {"$MCFormatCancel", &dword_4F2370[31]},
        {"$MCFormatOK", &dword_4F2370[32]},
        {"$MCFormatFailed", &dword_4F2370[33]},
        {"$MCFormatFailedContinue", &dword_4F2370[34]},
        {"$MCAutosaving", &dword_4F2370[35]},
        {"$MCAutosaveDisabled", &dword_4F2370[36]},
        {"$MCCorruptedNew", &dword_4F2370[37]},
        {"$MCCorrupted", &dword_4F2370[38]},
        {"$MCDataRequired", &dword_4F2370[39]},
        {"$MCAutosaveReconfirm", &dword_4F2370[40]},
        {"$MCContinue", &dword_4F2370[41]},
        {"$MCDelete", &dword_4F2370[42]},
        {"$MCFormat", &dword_4F2370[43]},
        {"$MCRetry", &dword_4F2370[44]},
        {"$MCCancel", &dword_4F2370[45]},
        {"$MCOK", &dword_4F2370[46]},
        {"$MCOverwriteNewContinue", &dword_4F2370[47]},
        {"$MCOverwriteContinue", &dword_4F2370[48]},
        {"$MCContinueWOSaving", &dword_4F2370[49]},
        {"$MCLoadNewGame", &dword_4F2370[50]},
        {"$MCCardRemoved", &dword_4F2370[51]},
        {"$MCCardChanged", &dword_4F2370[52]},
        {"$MCYes", &dword_4F2370[53]},
        {"$MCNo", &dword_4F2370[54]},
        {"$MCAutosaveFailed", &dword_4F2370[55]},
        {"$MCAutosaveFailed", &dword_4F2370[55]},
        {"$MCEmptySlot", &dword_4F2370[56]},
        {"$MCSelectSaveSlot", &dword_4F2370[57]},
        {"$MCSelectLoadSlot", &dword_4F2370[58]},
        {"$MCSelectCreateNewSlot", &dword_4F2370[59]},
        {"$MCCheckOK", &dword_4F2370[60]},
        {"$MCConfirmSave", &dword_4F2370[61]},
        {"$MCDupProfileNameEntered", &dword_4F2370[62]},
        {"$MCDupProfilesNotAllowed", &dword_4F2370[63]},
        {"$MCNoControllerLine", &dword_4F2370[64]},
        {"$MCMenuButtonSelect", &dword_4F2370[65]},
        {"$MCMenuButtonCancel", &dword_4F2370[66]},
        {"$MCMenuButtonUnPause", &dword_4F2370[67]},
        {"$MCMenuButtonNavigate", &dword_4F2370[68]},
        {"$MCMenuButtonChangeOption", &dword_4F2370[69]},
        {"$MCWarning", &dword_4F2370[70]},
        {"$MCResetDataWarning", &dword_4F2370[71]},
        {"$MCLoadProfileWarning", &dword_4F2370[72]},
        {"$MCSaveCorrupt", &dword_4F2370[73]},
        {"$MCUnknownDevice", &dword_4F2370[74]},
        {"$MCExitFree", &dword_4F2370[73]},
        {"$MCNoControllerLineUS", &dword_4F2370[76]},
        {0, 0},
    };

    return sub_18A890("shell\\fend\\instance\\xbox\\mc.csv", var_278, arg_0);
}
// match: ?sub_18B540@@YAXPAUtype_4EBE00@@PADH@Z @ 0x0018B540
// sp-match: ?sub_18B540@@YAXPAUtype_4EBE00@@PADH@Z @ 0x0011F4C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Wraps the text arg_4 into the box arg_0's lines: a new line at each
// newline, or at a space once a line has arg_8 characters.
void sub_18B540(type_4EBE00 *arg_0, RwChar *arg_4, RwInt32 arg_8)
{
    RwChar *var_C;
    type_4EBE00_DC *bp_8;
    RwInt32 bp_4;

    var_C = arg_4;
    for (bp_4 = 0; *arg_4; arg_4++, bp_4++)
    {
        if ((bp_4 >= arg_8 && *arg_4 == ' ') || *arg_4 == '\n')
        {
            bp_4 = 0;
            *arg_4 = 0;
            bp_8 = arg_0->sub_188970();
            strcpy(bp_8->unk_00, var_C);
            *arg_4 = '\n';
            var_C = arg_4 + 1;
        }
    }
    if (arg_4 != var_C)
    {
        bp_8 = arg_0->sub_188970();
        strcpy(bp_8->unk_00, var_C);
    }
}
// match: ?sub_18B5F0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018B5F0
// sp-match: ?sub_18B5F0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0011F530
// The answers' selects: the answer (arg_C, an int's address) set to 1 to
// 4.
void sub_18B5F0(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 *var_4;

    var_4 = (RwInt32 *)arg_C;
    *var_4 = 1;
}
// match: ?sub_18B610@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018B610
// sp-match: ?sub_18B610@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0011F540
void sub_18B610(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 *var_4;

    var_4 = (RwInt32 *)arg_C;
    *var_4 = 2;
}
// match: ?sub_18B630@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018B630
// sp-match: ?sub_18B630@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0011F550
void sub_18B630(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 *var_4;

    var_4 = (RwInt32 *)arg_C;
    *var_4 = 3;
}
// match: ?sub_18B650@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018B650
// sp-match: ?sub_18B650@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0011F560
void sub_18B650(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 *var_4;

    var_4 = (RwInt32 *)arg_C;
    *var_4 = 4;
}
// match: ?sub_18B670@@YAXPAUtype_4EBE00@@H@Z @ 0x0018B670
// sp-match: ?sub_18B670@@YAXPAUtype_4EBE00@@H@Z @ 0x0011F570
// A card message's update (its argument a type_18B670): once a second, the
// card looked for and its free space kept (-1 without one).
void sub_18B670(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_18B670 *var_4;

    var_4 = (type_18B670 *)arg_4;
    if (var_4->unk_0C < RWS::Time::GetTime())
    {
        var_4->unk_0C = RWS::Time::GetTime() + 1000;
        var_4->unk_04 = var_4->unk_00->sub_D9D30();
        var_4->unk_08 = var_4->unk_04 != 0 && var_4->unk_04 != -2 ? -1 : var_4->unk_00->get_unk_04();
    }
}
// match: ?sub_18B6F0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018B6F0
// sp-match: ?sub_18B6F0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0011F5C0
// A select that closes the box.
void sub_18B6F0(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    sub_1870D0();
}
// match: ?sub_18B700@@YAXPAUtype_4EBE00@@H@Z @ 0x0018B700
// sp-match: ?sub_18B700@@YAXPAUtype_4EBE00@@H@Z @ 0x0011F5D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCDupProfilesNotAllowed (the record's name for %name%) as a yes
// or cancel question; the answer (1 or 3) into the int at arg_4.
void sub_18B700(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_114;
    RwChar *var_110;
    type_4EBE00_100 *local_10C;
    RwChar var_108[0x100];
    type_4EBE00_DC *l4;

    var_110 = strstr(dword_4F2370[63], "%name%");
    if (!var_110)
        strcpy(var_108, dword_4F2370[63]);
    else
    {
        var_114 = var_110 - dword_4F2370[63];
        strncpy(var_108, dword_4F2370[63], var_110 - dword_4F2370[63]);
        strcpy(&var_108[var_114], dword_4F28F0->unk_48);
        strcat(var_108, dword_4F2370[63] + var_114 + strlen("%name%"));
    }
    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, var_108, 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    local_10C = l4->sub_18A190(dword_4F2370[53]);
    local_10C->unk_24 = sub_18B5F0;
    local_10C->unk_28 = arg_4;
    l4 = arg_0->sub_188970();
    local_10C = l4->sub_18A190(dword_4F2370[45]);
    local_10C->unk_24 = sub_18B630;
    local_10C->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18B8C0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018B8C0
// sp-match: ?sub_18B8C0@@YAXPAUtype_4EBE00@@H@Z @ 0x0011F730
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCDupProfileNameEntered (the record's name for %name%) with an OK
// (1 into the int at arg_4).
void sub_18B8C0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_114;
    RwChar *var_110;
    type_4EBE00_100 *local_10C;
    RwChar var_108[0x100];
    type_4EBE00_DC *l4;

    var_110 = strstr(dword_4F2370[62], "%name%");
    if (!var_110)
        strcpy(var_108, dword_4F2370[62]);
    else
    {
        var_114 = var_110 - dword_4F2370[62];
        strncpy(var_108, dword_4F2370[62], var_110 - dword_4F2370[62]);
        strcpy(&var_108[var_114], dword_4F28F0->unk_48);
        strcat(var_108, dword_4F2370[62] + var_114 + strlen("%name%"));
    }
    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, var_108, 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    local_10C = l4->sub_18A190(dword_4F2370[46]);
    local_10C->unk_24 = sub_18B5F0;
    local_10C->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BA40@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BA40
// sp-match: ?sub_18BA40@@YAXPAUtype_4EBE00@@H@Z @ 0x0011F870
// Opens $MCSaving, or $MCOverwriting when arg_4 is set.
void sub_18BA40(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    arg_0->unk_2CF0 = 1;
    if (!arg_4)
        sub_18B540(arg_0, dword_4F2370[19], 0x19);
    else
        sub_18B540(arg_0, dword_4F2370[23], 0x19);
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BA90@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BA90
// sp-match: ?sub_18BA90@@YAXPAUtype_4EBE00@@H@Z @ 0x0011F8B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCResetDataWarning as a yes or no question, no selected; the
// answer (1 or 2) into the int at arg_4.
void sub_18BA90(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4EBE00_100 *bp_8;
    type_4EBE00_DC *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[71], 0x19);
    bp_4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_4->unk_00, pEmpty);
    }
#else
    strcpy(bp_4->unk_00, "");
#endif
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[53]);
    bp_8->unk_24 = sub_18B5F0;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[54]);
    bp_8->unk_24 = sub_18B610;
    bp_8->unk_28 = arg_4;
    var_C = arg_0->unk_2C;
    if ((var_10 = var_C - 1) >= 0 && var_10 < arg_0->unk_2C && arg_0->unk_DC[var_10].sub_18A380())
        arg_0->unk_38 = var_10;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BBB0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BBB0
// sp-match: ?sub_18BBB0@@YAXPAUtype_4EBE00@@H@Z @ 0x0011F970
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCLoadProfileWarning as a yes or no question, no selected; the
// answer (1 or 2) into the int at arg_4.
void sub_18BBB0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4EBE00_100 *bp_8;
    type_4EBE00_DC *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[72], 0x19);
    bp_4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_4->unk_00, pEmpty);
    }
#else
    strcpy(bp_4->unk_00, "");
#endif
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[53]);
    bp_8->unk_24 = sub_18B5F0;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[54]);
    bp_8->unk_24 = sub_18B610;
    bp_8->unk_28 = arg_4;
    var_C = arg_0->unk_2C;
    if ((var_10 = var_C - 1) >= 0 && var_10 < arg_0->unk_2C && arg_0->unk_DC[var_10].sub_18A380())
        arg_0->unk_38 = var_10;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BCD0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BCD0
// sp-match: ?sub_18BCD0@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FA30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCSaveOK, or $MCOverwriteOK when overwriting (arg_4 a
// type_18BCD0), with an OK (1 into its answer).
void sub_18BCD0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    bp_4 = (type_18BCD0 *)arg_4;
    if (!bp_4->unk_08)
        sub_18B540(arg_0, dword_4F2370[20], 0x19);
    else
        sub_18B540(arg_0, dword_4F2370[24], 0x19);
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[46]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BD90@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BD90
// sp-match: ?sub_18BD90@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FAC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCSaveFailedContinue, or $MCOverwriteFailedContinue when
// overwriting (arg_4 a type_18BCD0), as continue or retry (and cancel when
// it can be cancelled), retry selected; the answer (1, 4 or 3) into it.
void sub_18BD90(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    bp_4 = (type_18BCD0 *)arg_4;
    if (!bp_4->unk_08)
        sub_18B540(arg_0, dword_4F2370[22], 0x19);
    else
        sub_18B540(arg_0, dword_4F2370[26], 0x19);
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[53]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = (RwInt32)bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[44]);
    var_C->unk_24 = sub_18B650;
    var_C->unk_28 = (RwInt32)bp_4;
    if (bp_4->unk_04)
    {
        bp_8 = arg_0->sub_188970();
        var_C = bp_8->sub_18A190(dword_4F2370[45]);
        var_C->unk_24 = sub_18B630;
        var_C->unk_28 = (RwInt32)bp_4;
    }
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BF10@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BF10
// sp-match: ?sub_18BF10@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FBC0
// Opens $MCLoading.
void sub_18BF10(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[9], 0x19);
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BF50@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BF50
// sp-match: ?sub_18BF50@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FBF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCLoadOK with an OK (1 into the int at arg_4).
void sub_18BF50(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[10], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18BFF0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018BFF0
// sp-match: ?sub_18BFF0@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FC70
// Opens $MCLoadFailed with an OK (1 into the int at arg_4).
void sub_18BFF0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[11], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C090@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C090
// sp-match: ?sub_18C090@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FCF0
// Opens $MCCardChanged with an OK (1 into the int at arg_4).
void sub_18C090(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[52], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C130@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C130
// sp-match: ?sub_18C130@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FD70
// Opens $MCNoCardLoad with an OK (1 into the int at arg_4).
void sub_18C130(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[1], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C1D0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C1D0
// sp-match: ?sub_18C1D0@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FDF0
// Opens $MCNoCardSave with an OK (1 into the int at arg_4).
void sub_18C1D0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[0], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C270@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C270
// sp-match: ?sub_18C270@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FE70
// Opens $MCDataRequired with an OK (1 into the int at arg_4).
void sub_18C270(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[39], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C310@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C310
// sp-match: ?sub_18C310@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FEF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCContinueWOSaving as a yes or no question, no selected; the answer (1 or
// 2) into the int at arg_4.
void sub_18C310(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4EBE00_100 *bp_8;
    type_4EBE00_DC *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[49], 0x19);
    bp_4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_4->unk_00, pEmpty);
    }
#else
    strcpy(bp_4->unk_00, "");
#endif
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[53]);
    bp_8->unk_24 = sub_18B5F0;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[54]);
    bp_8->unk_24 = sub_18B610;
    bp_8->unk_28 = arg_4;
    var_C = arg_0->unk_2C;
    if ((var_10 = var_C - 1) >= 0 && var_10 < arg_0->unk_2C && arg_0->unk_DC[var_10].sub_18A380())
        arg_0->unk_38 = var_10;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C430@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C430
// sp-match: ?sub_18C430@@YAXPAUtype_4EBE00@@H@Z @ 0x0011FFB0
// Opens $MCCorrupted with an OK (1 into the int at arg_4).
void sub_18C430(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[38], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C4D0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C4D0
// sp-match: ?sub_18C4D0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCOverwriteContinue as a yes or no question, no selected; the answer (1 or
// 2) into the int at arg_4.
void sub_18C4D0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4EBE00_100 *bp_8;
    type_4EBE00_DC *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[48], 0x19);
    bp_4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_4->unk_00, pEmpty);
    }
#else
    strcpy(bp_4->unk_00, "");
#endif
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[53]);
    bp_8->unk_24 = sub_18B5F0;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[54]);
    bp_8->unk_24 = sub_18B610;
    bp_8->unk_28 = arg_4;
    var_C = arg_0->unk_2C;
    if ((var_10 = var_C - 1) >= 0 && var_10 < arg_0->unk_2C && arg_0->unk_DC[var_10].sub_18A380())
        arg_0->unk_38 = var_10;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C5F0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C5F0
// sp-match: ?sub_18C5F0@@YAXPAUtype_4EBE00@@H@Z @ 0x001200F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCNoSpace with an OK (1 into the answer of arg_4, a
// type_18BCD0).
void sub_18C5F0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[4], 0x19);
    bp_4 = (type_18BCD0 *)arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[46]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = (RwInt32)bp_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C6A0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C6A0
// sp-match: ?sub_18C6A0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120170
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCNoSpaceContinue as continue or retry (and cancel when it can
// be cancelled), retry selected; the answer (1, 4 or 3) into arg_4, a
// type_18BCD0.
void sub_18C6A0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[5], 0x19);
    bp_4 = (type_18BCD0 *)arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[53]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = (RwInt32)bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[44]);
    var_C->unk_24 = sub_18B650;
    var_C->unk_28 = (RwInt32)bp_4;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    if (bp_4->unk_04)
    {
        bp_8 = arg_0->sub_188970();
        var_C = bp_8->sub_18A190(dword_4F2370[45]);
        var_C->unk_24 = sub_18B630;
        var_C->unk_28 = (RwInt32)bp_4;
    }
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C800@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C800
// sp-match: ?sub_18C800@@YAXPAUtype_4EBE00@@H@Z @ 0x00120260
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCConfirmFormat as a yes or no question, no selected; the answer (1 or
// 2) into the int at arg_4.
void sub_18C800(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4EBE00_100 *bp_8;
    type_4EBE00_DC *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[29], 0x19);
    bp_4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_4->unk_00, pEmpty);
    }
#else
    strcpy(bp_4->unk_00, "");
#endif
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[53]);
    bp_8->unk_24 = sub_18B5F0;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[54]);
    bp_8->unk_24 = sub_18B610;
    bp_8->unk_28 = arg_4;
    var_C = arg_0->unk_2C;
    if ((var_10 = var_C - 1) >= 0 && var_10 < arg_0->unk_2C && arg_0->unk_DC[var_10].sub_18A380())
        arg_0->unk_38 = var_10;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C920@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C920
// sp-match: ?sub_18C920@@YAXPAUtype_4EBE00@@H@Z @ 0x00120320
// Opens $MCFormatOK with an OK (1 into the int at arg_4).
void sub_18C920(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_DC *l4;
    type_4EBE00_100 *var_8;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[32], 0x19);
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F2370[46]);
    var_8->unk_24 = sub_18B5F0;
    var_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18C9C0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018C9C0
// sp-match: ?sub_18C9C0@@YAXPAUtype_4EBE00@@H@Z @ 0x001203A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCFormatFailedContinue as yes, no or retry, retry selected; the
// answer (1, 2 or 4) into the int at arg_4.
void sub_18C9C0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4EBE00_100 *bp_8;
    type_4EBE00_DC *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[34], 0x19);
    bp_4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_4->unk_00, pEmpty);
    }
#else
    strcpy(bp_4->unk_00, "");
#endif
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[53]);
    bp_8->unk_24 = sub_18B5F0;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[54]);
    bp_8->unk_24 = sub_18B610;
    bp_8->unk_28 = arg_4;
    bp_4 = arg_0->sub_188970();
    bp_8 = bp_4->sub_18A190(dword_4F2370[44]);
    bp_8->unk_24 = sub_18B650;
    bp_8->unk_28 = arg_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    var_C = arg_0->unk_2C;
    if ((var_10 = var_C - 1) >= 0 && var_10 < arg_0->unk_2C && arg_0->unk_DC[var_10].sub_18A380())
        arg_0->unk_38 = var_10;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18CB10@@YAXPAUtype_4EBE00@@H@Z @ 0x0018CB10
// sp-match: ?sub_18CB10@@YAXPAUtype_4EBE00@@H@Z @ 0x00120480
// Opens $MCFormatting.
void sub_18CB10(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[30], 0x19);
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18CB50@@YAXPAUtype_4EBE00@@H@Z @ 0x0018CB50
// sp-match: ?sub_18CB50@@YAXPAUtype_4EBE00@@H@Z @ 0x001204B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCUnformatted as format, continue or retry (and cancel when it
// can be cancelled), continue selected; the answer (1, 2, 4 or 3) into
// arg_4, a type_18BCD0.
void sub_18CB50(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_1C;
    RwInt32 var_18;
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[27], 0x19);
    bp_4 = (type_18BCD0 *)arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[43]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = (RwInt32)bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[41]);
    var_C->unk_24 = sub_18B610;
    var_C->unk_28 = (RwInt32)bp_4;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[44]);
    var_C->unk_24 = sub_18B650;
    var_C->unk_28 = (RwInt32)bp_4;
    if (bp_4->unk_04)
    {
        bp_8 = arg_0->sub_188970();
        var_C = bp_8->sub_18A190(dword_4F2370[45]);
        var_C->unk_24 = sub_18B630;
        var_C->unk_28 = (RwInt32)bp_4;
    }
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    var_18 = arg_0->unk_2C;
    if ((var_1C = var_18 - 2) >= 0 && var_1C < arg_0->unk_2C && arg_0->unk_DC[var_1C].sub_18A380())
        arg_0->unk_38 = var_1C;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18CD20@@YAXPAUtype_4EBE00@@H@Z @ 0x0018CD20
// sp-match: ?sub_18CD20@@YAXPAUtype_4EBE00@@H@Z @ 0x001205E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCConfirmSave as a yes or no question, no selected; the answer
// (1 or 2) into the int at arg_4.
void sub_18CD20(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    RwInt32 bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[61], 0x19);
    bp_4 = arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[53]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[54]);
    var_C->unk_24 = sub_18B610;
    var_C->unk_28 = bp_4;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18CE40@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018CE40
// sp-match: ?sub_18CE40@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001206A0
// A slot's select (arg_C a type_4F24A8): the slot and whether it is empty
// kept, unless it is empty and cannot be chosen.
void sub_18CE40(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    type_4F24A8 *var_4;

    var_4 = (type_4F24A8 *)arg_C;
    if (var_4->unk_0D && var_4->unk_0C)
    {
    }
    else
    {
        *var_4->unk_00 = var_4->unk_04;
        *var_4->unk_08 = var_4->unk_0C;
    }
}
// match: ?sub_18CE90@@YAXPAUtype_4EBE00@@H@Z @ 0x0018CE90
// sp-match: ?sub_18CE90@@YAXPAUtype_4EBE00@@H@Z @ 0x001206D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The slot menu's update (arg_4 a type_18CFA0): the card looked for, and
// when it has come back (or the menu asks), the slots' choices named from
// the card's saves ($MCEmptySlot for an empty one).
void sub_18CE90(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwChar var_4C[4][12];
    type_4EBE00_100 *var_5C;
    RwChar *bp_58;
    type_4EBE00_100 *p54;
    RwInt32 var_50;
    type_4F24A8 *bp_18;
    RwInt32 var_14[4];
    type_18CFA0 *l4;

    sub_18B670(arg_0, arg_4);
    l4 = (type_18CFA0 *)arg_4;
    if (l4->unk_04 == -2 || (l4->unk_04 == 0 && l4->unk_1C))
    {
        l4->unk_1C = 0;
        bp_18 = l4->unk_20;
        l4->unk_00->sub_D9D60(var_14, var_4C);
        for (var_50 = 0; var_50 < 4; var_50++)
        {
            if (var_4C[var_50][0])
            {
                p54 = l4->unk_30[var_50];
                strcpy(p54->unk_00, var_4C[var_50]);
                bp_18[var_50].unk_0C = 0;
            }
            else
            {
                bp_58 = dword_4F2370[56];
                var_5C = l4->unk_30[var_50];
                strcpy(var_5C->unk_00, bp_58);
                bp_18[var_50].unk_0C = 1;
            }
        }
    }
}
// match: ?sub_18CFA0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018CFA0
// sp-match: ?sub_18CFA0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the memory card slot menu (arg_4 a type_18CFA0): a heading for its
// mode, four slots (named by its update, sub_18CE90) and cancel.
void sub_18CFA0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_30;
    RwInt32 var_2C;
    RwInt32 var_28;
    type_4EBE00_100 *ebp_24;
    const RwChar *var_20;
    RwChar l1C[14];
    type_4EBE00_DC *bp_8;
    type_18CFA0 *bp_4;

    arg_0->unk_2CF0 = 1;
    bp_4 = (type_18CFA0 *)arg_4;
    var_20 = "ERROR: MC_SelectSlotMenu()";
    switch (bp_4->unk_18)
    {
    case 0:
    case 1:
        var_20 = dword_4F2370[57];
        break;
    case 2:
        var_20 = dword_4F2370[58];
        break;
    case 3:
        var_20 = dword_4F2370[59];
    }
    sub_18B540(arg_0, (RwChar *)var_20, 0x19);
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    memset(l1C, 'W', 14);
    l1C[13] = 0;
    for (var_28 = 0; var_28 < 4; var_28++)
    {
        dword_4F24A8[var_28].unk_04 = var_28;
        dword_4F24A8[var_28].unk_00 = &bp_4->unk_28;
        dword_4F24A8[var_28].unk_0C = 1;
        dword_4F24A8[var_28].unk_08 = &bp_4->unk_2C;
        dword_4F24A8[var_28].unk_0D = (RwInt32)(bp_4->unk_18 == 2);
        bp_8 = arg_0->sub_188970();
        ebp_24 = bp_8->sub_18A190(l1C);
        ebp_24->unk_24 = sub_18CE40;
        ebp_24->unk_28 = (RwInt32)&dword_4F24A8[var_28];
        bp_4->unk_30[var_28] = ebp_24;
        if (var_28 == bp_4->unk_24)
        {
            var_2C = arg_0->unk_2C;
            if ((var_30 = var_2C - 1) >= 0 && var_30 < arg_0->unk_2C && arg_0->unk_DC[var_30].sub_18A380())
                arg_0->unk_38 = var_30;
            bp_8->unk_264 = 0;
        }
    }
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    ebp_24 = bp_8->sub_18A190(dword_4F2370[45]);
    ebp_24->unk_24 = sub_18B630;
    ebp_24->unk_28 = (RwInt32)&bp_4->unk_10;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    bp_4->unk_1C = 1;
    bp_4->unk_20 = dword_4F24A8;
    arg_0->unk_2CE8 = sub_18CE90;
    arg_0->unk_2CEC = arg_4;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D220@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D220
// sp-match: ?sub_18D220@@YAXPAUtype_4EBE00@@H@Z @ 0x00120970
// Opens $MCChecking.
void sub_18D220(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[6], 0x19);
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D260@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D260
// sp-match: ?sub_18D260@@YAXPAUtype_4EBE00@@H@Z @ 0x001209A0
// Opens $MCCheckOK.
void sub_18D260(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[60], 0x19);
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D2A0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D2A0
// sp-match: ?sub_18D2A0@@YAXPAUtype_4EBE00@@H@Z @ 0x001209D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCCheckFailed as yes or retry, retry selected; the answer (1 or
// 4) into the int at arg_4.
void sub_18D2A0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    RwInt32 bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[7], 0x19);
    bp_4 = arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[53]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[44]);
    var_C->unk_24 = sub_18B650;
    var_C->unk_28 = bp_4;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D3C0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D3C0
// sp-match: ?sub_18D3C0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120A90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCNoCardSaveContinueGame as continue or retry (and cancel when it can
// be cancelled), retry selected; the answer (1, 4 or 3) into arg_4, a
// type_18BCD0.
void sub_18D3C0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[3], 0x19);
    bp_4 = (type_18BCD0 *)arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[53]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = (RwInt32)bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[44]);
    var_C->unk_24 = sub_18B650;
    var_C->unk_28 = (RwInt32)bp_4;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    if (bp_4->unk_04)
    {
        bp_8 = arg_0->sub_188970();
        var_C = bp_8->sub_18A190(dword_4F2370[45]);
        var_C->unk_24 = sub_18B630;
        var_C->unk_28 = (RwInt32)bp_4;
    }
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D520@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D520
// sp-match: ?sub_18D520@@YAXPAUtype_4EBE00@@H@Z @ 0x00120B80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens $MCNoCardSaveContinue as continue or retry (and cancel when it can
// be cancelled), retry selected; the answer (1, 4 or 3) into arg_4, a
// type_18BCD0.
void sub_18D520(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    type_4EBE00_100 *var_C;
    type_4EBE00_DC *bp_8;
    type_18BCD0 *bp_4;

    arg_0->unk_2CF0 = 1;
    sub_18B540(arg_0, dword_4F2370[2], 0x19);
    bp_4 = (type_18BCD0 *)arg_4;
    bp_8 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(bp_8->unk_00, pEmpty);
    }
#else
    strcpy(bp_8->unk_00, "");
#endif
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[53]);
    var_C->unk_24 = sub_18B5F0;
    var_C->unk_28 = (RwInt32)bp_4;
    bp_8 = arg_0->sub_188970();
    var_C = bp_8->sub_18A190(dword_4F2370[44]);
    var_C->unk_24 = sub_18B650;
    var_C->unk_28 = (RwInt32)bp_4;
    lv_10 = arg_0->unk_2C;
    if ((var_14 = lv_10 - 1) >= 0 && var_14 < arg_0->unk_2C && arg_0->unk_DC[var_14].sub_18A380())
        arg_0->unk_38 = var_14;
    if (bp_4->unk_04)
    {
        bp_8 = arg_0->sub_188970();
        var_C = bp_8->sub_18A190(dword_4F2370[45]);
        var_C->unk_24 = sub_18B630;
        var_C->unk_28 = (RwInt32)bp_4;
    }
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D680@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D680
// Opens $MCNoControllerLineUS ($MCNoControllerLine chosen first, then
// replaced).
void sub_18D680(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    arg_0->unk_2CF0 = 1;
    var_4 = 64;
    var_4 = 76;
    sub_18B540(arg_0, dword_4F2370[var_4], 0x19);
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D6D0@@YAXPAUtype_4EBE00@@PAD@Z @ 0x0018D6D0
// sp-match: ?sub_18D6D0@@YAXPAUtype_4EBE00@@PAD@Z @ 0x00120C70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Adds the text arg_4 to the box arg_0, a line for each of its lines.
void sub_18D6D0(type_4EBE00 *arg_0, RwChar *arg_4)
{
    type_4EBE00_DC *var_114;
    RwInt32 var_110;
    RwUInt32 local_10C;
    RwChar var_108[0x100];

    var_110 = 1;
    while (var_110)
    {
        var_110 = 0;
        for (local_10C = 0; local_10C < strlen(arg_4); local_10C++)
        {
            var_108[local_10C] = arg_4[local_10C];
            if (arg_4[local_10C] == '\n')
            {
                var_110 = 1;
                arg_4 = arg_4 + local_10C + 1;
                break;
            }
        }
        var_108[local_10C] = 0;
        var_114 = arg_0->sub_188970();
        strcpy(var_114->unk_00, var_108);
    }
}
// match: ?sub_18D7C0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D7C0
// sp-match: ?sub_18D7C0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The not enough free blocks screen's update: the first button closes the
// messages (sub_187040), the second goes to the dashboard's memory page to
// free blocks on the hard disk.
void sub_18D7C0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    LAUNCH_DATA var_C10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwReal bp_4;

#ifdef CODFH_SP
    // Single player's bindings number these actions 8 and 9 (SP 0x120D2F, 0x120D44).
    var_C = unk_4B9308.sub_EE790(8, 0);
    bp_8 = unk_4B9308.sub_EE790(9, 0);
#else
    var_C = unk_4B9308.sub_EE790(10, 0);
    bp_8 = unk_4B9308.sub_EE790(11, 0);
#endif
    bp_4 = unk_4B9308.sub_EE8F0(0, var_C);
    if (bp_4 != 0.0f)
    {
        dword_4F5A30 = 1;
        sub_187040();
        dword_4B88AC = 0;
    }
    bp_4 = unk_4B9308.sub_EE8F0(0, bp_8);
    if (bp_4 != 0.0f)
    {
        ((LD_LAUNCH_DASHBOARD *)&var_C10)->dwReason = XLD_LAUNCH_DASHBOARD_MEMORY;
        ((LD_LAUNCH_DASHBOARD *)&var_C10)->dwContext = 0;
        ((LD_LAUNCH_DASHBOARD *)&var_C10)->dwParameter1 = 'U';
        ((LD_LAUNCH_DASHBOARD *)&var_C10)->dwParameter2 = 30;
        XLaunchNewImage(0, &var_C10);
    }
}
// match: ?sub_18D8A0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D8A0
// sp-match: ?sub_18D8A0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120DF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the not enough free blocks screen: the language's text with the
// blocks needed (dword_4F616C), nothing selected, sub_18D7C0 its update.
void sub_18D8A0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_20C;
    RwChar loc208[0x200];

    var_20C = sub_19B0A0();
    sprintf(loc208, off_42C7F4[var_20C], dword_4F616C);
    sub_18D6D0(arg_0, loc208);
    dword_4B88AC = 1;
    arg_0->unk_38 = -1;
    arg_0->unk_2CE8 = sub_18D7C0;
    arg_0->unk_2CEC = 0;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18D940@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D940
// sp-match: ?sub_18D940@@YAXPAUtype_4EBE00@@H@Z @ 0x00120E80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens _Xbox_Live_Cant_Connect (two lines), then sets unk_18.
void sub_18D940(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->unk_2CF0 = 1;
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[8]);
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[9]);
    l4->unk_264 = 0;
    arg_0->sub_1884B0(0, 0);
    arg_0->unk_18 = 1;
}
// match: ?sub_18D9E0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018D9E0
// sp-match: ?sub_18D9E0@@YAXPAUtype_4EBE00@@H@Z @ 0x00120F00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens _Important_Xbox_Message (two lines).
void sub_18D9E0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->unk_2CF0 = 1;
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[19]);
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[20]);
    l4->unk_264 = 0;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18DA80@@YAXPAUtype_4EBE00@@H@Z @ 0x0018DA80
// sp-match: ?sub_18DA80@@YAXPAUtype_4EBE00@@H@Z @ 0x00120F80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens _Xbox_Multiple_Accounts (three lines).
void sub_18DA80(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->unk_2CF0 = 1;
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[21]);
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[22]);
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[23]);
    l4->unk_264 = 0;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18DB40@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DB40
// sp-match: ?sub_18DB40@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121020
// _Friends_List's select.
void sub_18DB40(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    dword_4F3130.sub_19C440();
}
// match: ?sub_18DB50@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DB50
// sp-match: ?sub_18DB50@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121030
// _Appear_Offline's select.
void sub_18DB50(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    dword_4F3130.sub_19C3A0();
}
// match: ?sub_18DB60@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DB60
// sp-match: ?sub_18DB60@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121040
// _Sign_Out's select.
void sub_18DB60(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    dword_4F3130.sub_19C4D0();
}
// match: ?sub_18DB70@@YAXPAUtype_4EBE00@@H@Z @ 0x0018DB70
// sp-match: ?sub_18DB70@@YAXPAUtype_4EBE00@@H@Z @ 0x00121050
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the Xbox Live options while appearing online: the friends list,
// appear offline and sign out (raised while paused).
void sub_18DB70(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->set_heading(0, dword_4F6178[6]);
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[15]);
    var_8->unk_24 = sub_18DB40;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[16]);
    var_8->unk_24 = sub_18DB50;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[25]);
    var_8->unk_24 = sub_18DB60;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    arg_0->unk_04.unk_00[1] = 1;
    if ((dword_4B86F8 >> 4) & 1)
        arg_0->sub_1884B0(0, -60.0f);
    else
        arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18DC90@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DC90
// sp-match: ?sub_18DC90@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121110
// _Appear_Online's select.
void sub_18DC90(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    dword_4F3130.sub_19C3F0();
}
// match: ?sub_18DCA0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018DCA0
// sp-match: ?sub_18DCA0@@YAXPAUtype_4EBE00@@H@Z @ 0x00121120
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the Xbox Live options while appearing offline: the friends list,
// appear online and sign out (raised while paused).
void sub_18DCA0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->set_heading(0, dword_4F6178[6]);
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[15]);
    var_8->unk_24 = sub_18DB40;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[17]);
    var_8->unk_24 = sub_18DC90;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[25]);
    var_8->unk_24 = sub_18DB60;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    arg_0->unk_04.unk_00[1] = 1;
    if ((dword_4B86F8 >> 4) & 1)
        arg_0->sub_1884B0(0, -60.0f);
    else
        arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18DDC0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DDC0
// sp-match: ?sub_18DDC0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001211E0
// _Sign_In's select.
void sub_18DDC0(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    dword_4F3130.sub_19C490();
}
// match: ?sub_18DDD0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018DDD0
// sp-match: ?sub_18DDD0@@YAXPAUtype_4EBE00@@H@Z @ 0x001211F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the Xbox Live options while signed out: sign in (raised while
// paused).
void sub_18DDD0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->set_heading(0, dword_4F6178[6]);
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[24]);
    var_8->unk_24 = sub_18DDC0;
    var_8->unk_28 = 0;
    l4->unk_264 = 0;
    arg_0->unk_04.unk_00[1] = 1;
    if ((dword_4B86F8 >> 4) & 1)
        arg_0->sub_1884B0(0, -60.0f);
    else
        arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18DE80@@YAXPAUtype_4EBE00@@H@Z @ 0x0018DE80
// sp-match: ?sub_18DE80@@YAXPAUtype_4EBE00@@H@Z @ 0x00121270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens _Quit_Question with _Unsaved_Lost.
void sub_18DE80(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_8;
    type_4EBE00_DC *l4;

    arg_0->unk_2CF0 = 1;
    l4 = arg_0->sub_188970();
#ifdef CODFH_SP
    // shape: the empty text through a pointer: the image copies it byte by byte.
    {
        const RwChar *pEmpty = "";
        strcpy(l4->unk_00, pEmpty);
    }
#else
    strcpy(l4->unk_00, "");
#endif
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[2]);
    l4->unk_264 = 0;
    l4 = arg_0->sub_188970();
    var_8 = l4->sub_18A190(dword_4F6178[4]);
    l4->unk_264 = 0;
    arg_0->sub_1884B0(0, 0);
}
// match: ?sub_18DF20@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DF20
// sp-match: ?sub_18DF20@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001212F0
// The pause menu's second choice: opens message 2.
void sub_18DF20(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    sub_186E70(2, 0, 0);
}
// match: ?sub_18DF40@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DF40
// sp-match: ?sub_18DF40@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121300
// The pause menu's third choice: opens message 3.
void sub_18DF40(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    sub_186E70(3, 0, 0);
}
// match: ?sub_18DF60@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018DF60
// sp-match: ?sub_18DF60@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121310
// The pause menu's first choice: opens message 1.
void sub_18DF60(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    sub_186E70(1, 0, 0);
}
// match: ?sub_18DF80@@YAXPAUtype_4EBE00@@H@Z @ 0x0018DF80
// sp-match: ?sub_18DF80@@YAXPAUtype_4EBE00@@H@Z @ 0x00121320
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the pause menu: its heading and options, restart and quit (the bar
// shown with the pad's buttons when dword_42926C is set).
void sub_18DF80(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_1C;
    type_3DF8D8 *var_18;
    const RwChar *var_14;
    const RwChar *lv_10;
    const RwChar *var_C;
    type_4EBE00_DC *bp_8;
    const RwChar *bp_4;

    var_18 = 0;
    var_18 = sub_198880("COD_InGameText+Event_PauseMenuHeading");
    var_14 = var_18->sub_197550(0, 0);
    var_18 = sub_198880("COD_InGameText+Event_PauseMenuItemOptions");
    bp_4 = var_18->sub_197550(0, 0);
    var_18 = sub_198880("COD_InGameText+Event_PauseMenuItemRestart");
    lv_10 = var_18->sub_197550(0, 0);
    var_18 = sub_198880("COD_InGameText+Event_PauseMenuItemQuit");
    var_C = var_18->sub_197550(0, 0);
    arg_0->set_heading(0, var_14);
    bp_8 = arg_0->sub_188970();
    var_1C = bp_8->sub_18A190(bp_4);
    var_1C->unk_24 = sub_18DF60;
    var_1C->unk_28 = 0;
    bp_8->unk_264 = 0;
    bp_8 = arg_0->sub_188970();
    var_1C = bp_8->sub_18A190(lv_10);
    var_1C->unk_24 = sub_18DF20;
    var_1C->unk_28 = 0;
    bp_8->unk_264 = 0;
    bp_8 = arg_0->sub_188970();
    var_1C = bp_8->sub_18A190(var_C);
    var_1C->unk_24 = sub_18DF40;
    var_1C->unk_28 = 0;
    bp_8->unk_264 = 0;
    if (dword_42926C)
    {
        arg_0->unk_2CE4 = 1;
        arg_0->unk_04.unk_00[3] = 1;
        arg_0->unk_04.unk_00[0] = 1;
        arg_0->unk_04.unk_00[1] = 1;
    }
    if (sub_19B0A0() != 6)
        arg_0->sub_1884B0(0, flt_42B510);
    else
        arg_0->sub_1884B0(10.0f, flt_42B510);
}
// match: ?sub_18E140@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E140
// sp-match: ?sub_18E140@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121980
// An options line's change: the difficulty (dword_4F234C) from its choice, then
// applied (sub_18E380).
void sub_18E140(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F234C = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E180@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E180
// sp-match: ?sub_18E180@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001219A0
// An options line's change: option unk_21 (dword_4F2354) from its choice, then
// applied (sub_18E380).
void sub_18E180(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F2354 = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E1C0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E1C0
// sp-match: ?sub_18E1C0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001219C0
// An options line's change: option unk_22 (dword_4F2358) from its choice, then
// applied (sub_18E380).
void sub_18E1C0(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F2358 = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E200@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E200
// sp-match: ?sub_18E200@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001219E0
// An options line's change: option unk_1C (dword_4F2350) from its choice, then
// applied (sub_18E380).
void sub_18E200(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F2350 = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E240@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E240
// sp-match: ?sub_18E240@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121A00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The rumble line's change: dword_4F235C from its choice, the pad rumbled
// once when it is turned on, then applied (sub_18E380).
void sub_18E240(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = arg_4->unk_264;
    dword_4F235C = l4;
    if (l4)
    {
        var_8 = dword_4F28F0->get_unk_20();
        dword_4F28F0->unk_20 = 1;
        unk_4B9308.sub_EED30(0, 1, 0xDC, 4);
        dword_4F28F0->unk_20 = var_8 != 0;
    }
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E2C0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E2C0
// sp-match: ?sub_18E2C0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121A60
// An options line's change: the help messages (dword_4F2360) from its choice, then
// applied (sub_18E380).
void sub_18E2C0(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F2360 = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E300@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E300
// sp-match: ?sub_18E300@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121A80
// An options line's change: option unk_180 (dword_4F2364) from its choice, then
// applied (sub_18E380).
void sub_18E300(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F2364 = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E340@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E340
// sp-match: ?sub_18E340@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121AA0
// An options line's change: option unk_181 (dword_4F2368) from its choice, then
// applied (sub_18E380).
void sub_18E340(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    var_4 = arg_4->unk_264;
    dword_4F2368 = var_4;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
}
// match: ?sub_18E380@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E380
// sp-match: ?sub_18E380@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121470
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Applies the pause menu's options to the player, the save state, the
// sound output and the HUD.
void sub_18E380(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    PlayerTrigger *var_8;
    type_10F710 *l4;

    l4 = (type_10F710 *)sub_1745A0(0);
    if (!l4)
        return;
    var_8 = (PlayerTrigger *)l4->get_unk_34C();
    switch (dword_4F2348)
    {
    case 0:
        dword_44D4C4 = 2;
        break;
    case 1:
        dword_44D4C4 = 1;
        break;
    case 2:
        dword_44D4C4 = 4;
        break;
    default:
        dword_44D4C4 = 1;
    }
    set_4F28F0_unk_14(dword_44D4C4);
    sub_84C40("RwaOsOutputSetSpeakerConfig  (Audio::sm_osoutput, Audio::sm_SpeakerConfig);");
    sub_22C6E0(dword_44E8B0, dword_44D4C4);
    switch (dword_4F234C)
    {
    case 0:
        dword_4F28F0->unk_18 = 0;
        break;
    case 2:
        dword_4F28F0->unk_18 = 2;
        break;
    default:
        dword_4F28F0->unk_18 = 1;
    }
    var_8->sub_ACA70();
    set_4F28F0_unk_1C(dword_4F2350);
    l4->unk_3DC = dword_4F2350;
    l4->sub_FEFE0();
    sub_1882C0();
    if (dword_4F2354)
        dword_4F28F0->unk_21 = 1;
    else
        dword_4F28F0->unk_21 = 0;
    if (dword_4F2358)
        dword_4F28F0->unk_22 = 1;
    else
        dword_4F28F0->unk_22 = 0;
    if (dword_4F235C)
        dword_4F28F0->unk_20 = 1;
    else
        dword_4F28F0->unk_20 = 0;
    if (dword_4F2360)
        dword_4F28F0->unk_28 = 1;
    else
    {
        sub_17C6C0(0);
        dword_4F28F0->unk_28 = 0;
    }
    set_4F28F0_unk_180(dword_4F2364 != 0);
    dword_4B9190->set_unk_1A020(dword_4F2364);
    set_4F28F0_unk_181(dword_4F2368 != 0);
    var_8->unk_304 = dword_4F2368;
}
// match: ?sub_18E5A0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018E5A0
// sp-match: ?sub_18E5A0@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121600
// The options' defaults: set, applied (sub_18E380), then the box closed
// and the pause menu (message 1) opened again.
void sub_18E5A0(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    dword_4F2368 = 1;
    dword_4F2350 = 0;
    dword_4F2364 = 1;
    dword_4F2360 = 1;
    dword_4F2358 = 0;
    dword_4F2348 = 1;
    dword_4F2354 = 1;
    dword_4F234C = 1;
    dword_4F235C = 1;
    sub_18E380(arg_0, arg_4, arg_8, arg_C);
    sub_186F80(1, 0);
    sub_186E70(1, 0, 0);
}
#ifdef CODFH_SP
// shape: single player copies seven of the menu titles stepping the destination, the source read at
// its offset (SP 0x121D80...: sub ebp, edi; mov cl, [eax+ebp]; mov [eax], cl; inc eax; cmp cl, bl), a loop
// no strcpy spelling gives; the last one (the aim-assist title, loc7C) is a strcpy
#define SP_MENU_COPY(d, s) { RwChar *d_ = (d); RwChar c_; do { c_ = d_[(s) - (d)]; *d_ = c_; d_++; } while (c_); }
#else
#define SP_MENU_COPY(d, s) strcpy(d, s)
#endif
// match: ?sub_18E640@@YAXPAUtype_4EBE00@@H@Z @ 0x0018E640
// sp-match: ?sub_18E640@@YAXPAUtype_4EBE00@@H@Z @ 0x00121AC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the options menu (while the player exists): turn speed, control
// set, subtitles, invert aim, controller shake, hint messages, friendly
// fire block and aim assist, each line showing the save state's value and
// its change applying it; then set defaults (sub_18E5A0). The sound
// line's texts are looked up but not shown.
void sub_18E640(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    const RwChar *var_94;
    const RwChar *stk_90;
    RwInt32 w8C;
    const RwChar *bp_88;
    RwInt32 m_84;
    const RwChar *m_80;
    const RwChar *loc7C;
    RwInt32 local_78;
    const RwChar *local_74;
    type_4EBE00_100 *local_70;
    const RwChar *var_6C;
    const RwChar *loc68;
    const RwChar *p64;
    const RwChar *w60;
    RwInt32 u5C;
    type_3DF8D8 *y58;
    const RwChar *y54;
    type_3D3548 *stk_50;
    const RwChar *var_4C;
    type_4EBE00_DC *frm_48;
    const RwChar *w44;
    const RwChar *s40;
    RwInt32 w3C;
    const RwChar *var_38;
    const RwChar *l34;
    const RwChar *var30;
    const RwChar *ebp_2C;
    RwInt32 lcl_28;
    const RwChar *frm_24;
    const RwChar *var_20;
    const RwChar *l1C;
    const RwChar *m_18;
    const RwChar *ebp_14;
    RwInt32 lv_10;
    const RwChar *var_C;
    const RwChar *bp_8;
    const RwChar *bp_4;

    stk_50 = sub_1745A0(0);
    if (!stk_50)
        return;
    y58 = 0;
    y58 = sub_198880("COD_InGameText+Event_OptionsMenuHeading");
    y54 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemSound");
    w44 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemSound_Stereo");
    local_74 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemSound_Mono");
    p64 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemSound_Dolby");
    m_18 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemTurnSpeed");
    bp_88 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemTurnSpd_Slow");
    var_C = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemTurnSpd_Norm");
    var_94 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemTurnSpd_Fast");
    var_38 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemControlConfig");
    var_6C = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemCtlr_Set1");
    loc68 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemCtlr_Set2");
    var_4C = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemCtlr_Set3");
    frm_24 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemCtlr_Set4");
    s40 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemCtlr_Set5");
    bp_8 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemSubtitles");
    l34 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_MenuGenericText_On");
    var_20 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_MenuGenericText_Off");
    bp_4 = y58->sub_197550(0, 0);
    var30 = dword_4F6178[7];
    y58 = sub_198880("COD_InGameText+Event_MenuGenericText_Yes");
    ebp_2C = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_MenuGenericText_No");
    stk_90 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuControllerShake");
    w60 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuItemHintMsgs");
    m_80 = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuAimAssist");
    loc7C = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuFFireBlock");
    l1C = y58->sub_197550(0, 0);
    y58 = sub_198880("COD_InGameText+Event_OptMenuSetDefaults");
    ebp_14 = y58->sub_197550(0, 0);
#ifdef CODFH_SP
    // shape: SP 0x121AC0 steps the source and addresses the heading by its
    // offset. Subtract through a reference to keep the destination's LEA
    // separate and the source as the store's base register.
    {
        RwChar *d = arg_0->unk_27DC[0];
        RwInt32 o = (RwInt32)d;
        { RwInt32 &r = o; r -= (RwInt32)y54; }
        RwChar *s = (RwChar *)y54;
        RwChar c;
        do {
            c = *s;
            s[o] = c;
            ++s;
        } while (c);
    }
#else
    // MP 0x18E640.
    arg_0->set_heading(0, y54);
#endif
    arg_0->unk_2CE0 = 0;
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, bp_88);
    local_70 = frm_48->sub_18A190(var_C);
    local_70->unk_1C = sub_18E140;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_94);
    local_70->unk_1C = sub_18E140;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_38);
    local_70->unk_1C = sub_18E140;
    local_70->unk_20 = 0;
    m_84 = 0;
    switch (dword_4F28F0->get_unk_18_direct())
    {
    case 0:
        m_84 = 0;
        break;
    case 1:
        m_84 = 1;
        break;
    case 2:
        m_84 = 2;
        break;
    default:
        m_84 = 3;
    }
    frm_48->unk_264 = m_84;
    dword_4F234C = m_84;
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, var_6C);
    local_70 = frm_48->sub_18A190(loc68);
    local_70->unk_1C = sub_18E200;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_4C);
    local_70->unk_1C = sub_18E200;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(frm_24);
    local_70->unk_1C = sub_18E200;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(s40);
    local_70->unk_1C = sub_18E200;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(bp_8);
    local_70->unk_1C = sub_18E200;
    local_70->unk_20 = 0;
    frm_48->unk_264 = dword_4F28F0->get_unk_1C();
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, l34);
    local_70 = frm_48->sub_18A190(bp_4);
    local_70->unk_1C = sub_18E180;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_20);
    local_70->unk_1C = sub_18E180;
    local_70->unk_20 = 0;
    lv_10 = 0;
    if (dword_4F28F0->get_unk_21())
        lv_10 = 1;
    else
        lv_10 = 0;
    frm_48->unk_264 = lv_10;
    dword_4F2354 = lv_10;
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, var30);
    local_70 = frm_48->sub_18A190(stk_90);
    local_70->unk_1C = sub_18E1C0;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(ebp_2C);
    local_70->unk_1C = sub_18E1C0;
    local_70->unk_20 = 0;
    w3C = 0;
    if (dword_4F28F0->get_unk_22())
        w3C = 1;
    else
        w3C = 0;
    frm_48->unk_264 = w3C;
    dword_4F2358 = w3C;
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, w60);
    local_70 = frm_48->sub_18A190(bp_4);
    local_70->unk_1C = sub_18E240;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_20);
    local_70->unk_1C = sub_18E240;
    local_70->unk_20 = 0;
    u5C = 0;
    if (dword_4F28F0->get_unk_20())
        u5C = 1;
    else
        u5C = 0;
    frm_48->unk_264 = u5C;
    dword_4F235C = u5C;
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, m_80);
    local_70 = frm_48->sub_18A190(bp_4);
    local_70->unk_1C = sub_18E2C0;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_20);
    local_70->unk_1C = sub_18E2C0;
    local_70->unk_20 = 0;
    w8C = 0;
    if (dword_4F28F0->get_unk_28())
        w8C = 1;
    else
        w8C = 0;
    frm_48->unk_264 = w8C;
    dword_4F2360 = w8C;
    frm_48 = arg_0->sub_188970();
    SP_MENU_COPY(frm_48->unk_00, l1C);
    local_70 = frm_48->sub_18A190(bp_4);
    local_70->unk_1C = sub_18E300;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_20);
    local_70->unk_1C = sub_18E300;
    local_70->unk_20 = 0;
    lcl_28 = 0;
    if (dword_4F28F0->unk_180)
        lcl_28 = 1;
    else
        lcl_28 = 0;
    frm_48->unk_264 = lcl_28;
    dword_4F2364 = lcl_28;
    frm_48 = arg_0->sub_188970();
    strcpy(frm_48->unk_00, loc7C);
    local_70 = frm_48->sub_18A190(bp_4);
    local_70->unk_1C = sub_18E340;
    local_70->unk_20 = 0;
    local_70 = frm_48->sub_18A190(var_20);
    local_70->unk_1C = sub_18E340;
    local_70->unk_20 = 0;
    if (dword_4F28F0->unk_181)
        local_78 = 1;
    else
        local_78 = 0;
    frm_48->unk_264 = local_78;
    dword_4F2368 = local_78;
    frm_48 = arg_0->sub_188970();
    local_70 = frm_48->sub_18A190(ebp_14);
    local_70->unk_24 = sub_18E5A0;
    local_70->unk_28 = 0;
    frm_48->unk_264 = 0;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[4] = 1;
    arg_0->unk_04.unk_00[2] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, flt_42B510);
}
// match: ?sub_18F000@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018F000
// sp-match: ?sub_18F000@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x00121680
// The quit question's yes: queues the quit (sub_D8BC0).
void sub_18F000(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    sub_D8BC0();
    dword_4EBCD8 = 1;
}
// match: ?sub_18F020@@YAXPAUtype_4EBE00@@H@Z @ 0x0018F020
// sp-match: ?sub_18F020@@YAXPAUtype_4EBE00@@H@Z @ 0x00121690
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the quit question (with _Unsaved_Lost): no closes it, yes quits
// (sub_18F000).
void sub_18F020(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    const RwChar *var_1C;
    const RwChar *var_18;
    type_4EBE00_100 *var_14;
    const RwChar *lv_10;
    type_3DF8D8 *var_C;
    type_4EBE00_DC *bp_8;
    const RwChar *bp_4;

    var_C = 0;
    var_18 = 0;
    var_C = sub_198880("COD_InGameText+Event_QuitMenuHeading");
    lv_10 = var_C->sub_197550(0, 0);
    var_18 = dword_4F6178[4];
    var_C = sub_198880("COD_InGameText+Event_MenuGenericText_Yes");
    bp_4 = var_C->sub_197550(0, 0);
    var_C = sub_198880("COD_InGameText+Event_MenuGenericText_No");
    var_1C = var_C->sub_197550(0, 0);
    arg_0->set_heading(0, lv_10);
    if (var_18)
        arg_0->set_heading(1, var_18);
    bp_8 = arg_0->sub_188970();
    var_14 = bp_8->sub_18A190(var_1C);
    var_14->unk_24 = sub_18B6F0;
    var_14->unk_28 = 0;
    bp_8->unk_264 = 0;
    bp_8 = arg_0->sub_188970();
    var_14 = bp_8->sub_18A190(bp_4);
    var_14->unk_24 = sub_18F000;
    var_14->unk_28 = 0;
    bp_8->unk_264 = 0;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, -55.0f);
}
// match: ?sub_18F190@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x0018F190
// sp-match: ?sub_18F190@@YAXPAUtype_4EBE00@@PAUtype_4EBE00_DC@@PADH@Z @ 0x001217A0
// The restart question's yes: the checkpoint restored (sub_D93F0) and the
// restart flagged.
void sub_18F190(type_4EBE00 *arg_0, type_4EBE00_DC *arg_4, RwChar *arg_8, RwInt32 arg_C)
{
    sub_D93F0();
    dword_4B8780 = 0;
    dword_4B86F8 |= 8;
    dword_4EBCD8 = 1;
}
// match: ?sub_18F1C0@@YAXPAUtype_4EBE00@@H@Z @ 0x0018F1C0
// sp-match: ?sub_18F1C0@@YAXPAUtype_4EBE00@@H@Z @ 0x001217D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens the restart question (with _Unsaved_Lost): no closes it, yes
// restarts (sub_18F190).
void sub_18F1C0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    const RwChar *var_1C;
    const RwChar *var_18;
    const RwChar *var_14;
    type_4EBE00_100 *lv_10;
    type_3DF8D8 *var_C;
    type_4EBE00_DC *bp_8;
    const RwChar *bp_4;

    var_C = 0;
    var_14 = 0;
    var_C = sub_198880("COD_InGameText+Event_RestartMenuHeading");
    var_18 = var_C->sub_197550(0, 0);
    var_14 = dword_4F6178[4];
    var_C = sub_198880("COD_InGameText+Event_MenuGenericText_Yes");
    bp_4 = var_C->sub_197550(0, 0);
    var_C = sub_198880("COD_InGameText+Event_MenuGenericText_No");
    var_1C = var_C->sub_197550(0, 0);
    arg_0->set_heading(0, var_18);
    if (var_14)
        arg_0->set_heading(1, var_14);
    bp_8 = arg_0->sub_188970();
    lv_10 = bp_8->sub_18A190(var_1C);
    lv_10->unk_24 = sub_18B6F0;
    lv_10->unk_28 = 0;
    bp_8->unk_264 = 0;
    bp_8 = arg_0->sub_188970();
    lv_10 = bp_8->sub_18A190(bp_4);
    lv_10->unk_24 = sub_18F190;
    lv_10->unk_28 = 0;
    bp_8->unk_264 = 0;
    arg_0->unk_2CE4 = 1;
    arg_0->unk_04.unk_00[3] = 1;
    arg_0->unk_04.unk_00[1] = 1;
    arg_0->sub_1884B0(0, -55.0f);
}
// match: ?sub_18F330@@YAXPAUtype_4EBE00@@H@Z @ 0x0018F330
// sp-match: ?sub_18F330@@YAXPAUtype_4EBE00@@H@Z @ 0x001218E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Opens _Insert_Controller_1 for the pad that was removed (numbered from
// 1).
void sub_18F330(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    type_4EBE00_100 *var_90;
    type_4EBE00_DC *l8C;
    RwChar var_88[0x80];

    sprintf(var_88, dword_4F6178[0], get_dword_4B9E50() + 1);
    l8C = arg_0->sub_188970();
    var_90 = l8C->sub_18A190(var_88);
    l8C->unk_264 = 0;
    arg_0->sub_1884B0(0, 0);
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_121960@@YAPADXZ @ 0x00121960
// The text $MCEmptySlot (single player's profile list, SP 0xAF80B and 0xAF82C).
RwChar *sp_sub_121960()
{
    return dword_4F2370[56];
}

// sp-match: ?sp_sub_121970@@YAXPAUtype_4EBE00@@H@Z @ 0x00121970
// Opens _Insert_Controller_1 (sub_18F330): single player's message table's
// entry for it (SP 0x328464).
void sp_sub_121970(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    sub_18F330(arg_0, arg_4);
}
#endif
