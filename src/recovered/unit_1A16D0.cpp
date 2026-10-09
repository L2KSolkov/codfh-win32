// The profiles' save files (game/profiles.h): the slots, the save games they
// are kept in, their signatures, and the damaged-profile message box.

#include <stdio.h>
#include <string.h>

#include "game/profiles.h"
#include "game/savestate.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042C7F4
const RwChar *off_42C7F4[7] = { "Your Xbox doesn\222t have enough free blocks to save games.\012You need %d more free blocks.\012\012Press $ms$ to continue without saving\012or $mc$ to free more blocks.", "Die Xbox hat nicht gen\374gend freie Bl\366cke\012um Spiele zu speichern.\012Sie ben\366tigen %d weitere freie Bl\366cke.\012\012$ms$ dr\374cken, um ohne zu speichern weiterzuspielen\012 $mc$ dr\374cken, um f\374r mehr freie Bl\366cke zu sorgen.", "La Xbox ne comporte pas assez de bloc(s) libre(s)\012pour sauvegarder les parties.\012Vous avez besoin de %d blocs libres suppl\351mentaires.\012\012Appuyer sur $ms$ pour jouer sans sauvegarder.\012Appuyer sur $mc$ pour lib\351rer des blocs.", "Die Xbox hat nicht gen\374gend freie Bl\366cke\012um Spiele zu speichern.\012Sie ben\366tigen %d weitere freie Bl\366cke.\012\012$ms$ dr\374cken, um ohne zu speichern weiterzuspielen\012 $mc$ dr\374cken, um f\374r mehr freie Bl\366cke zu sorgen.", "La Xbox ne comporte pas assez de bloc(s) libre(s)\012pour sauvegarder les parties.\012Vous avez besoin de %d blocs libres suppl\351mentaires.\012\012Appuyer sur $ms$ pour jouer sans sauvegarder.\012Appuyer sur $mc$ pour lib\351rer des blocs.", "Xbox non dispone di sufficienti blocchi liberi per salvare.\012Sono necessari %d ulteriori blocchi liberi.\012\012Premi $ms$ per continuare senza salvare\012oppure $mc$ per liberare dei blocchi.", "Tu Xbox no tiene suficientes bloques libres\012para guardar partidas.\012Se necesitan %d bloques libres mas.\012\012Presionar $ms$ para continuar sin guardar\012\363 $mc$ para liberar m\341s bloques." };
// 0x0042C810
const RwChar *off_42C810[7] = { "%s appears to be damaged.\012\012Please delete it using the Xbox Dashboard and try again.\012\012Press $ms$ to continue.", "%s scheint besch\344digt zu sein.\012\012Mit Hilfe der Xbox Steuerung l\366schen\012und erneut versuchen.\012\012Weiter mit $ms$-Taste.", "%s semble endommag\351.\012\012Supprimez-le depuis l'Interface Xbox et r\351essayez.\012\012Appuyer sur $ms$ pour continuer.", "%s scheint besch\344digt zu sein.\012\012Mit Hilfe der Xbox Steuerung l\366schen\012und erneut versuchen.\012\012Weiter mit $ms$-Taste.", "%s semble endommag\351.\012\012Supprimez-le depuis l'Interface Xbox et r\351essayez.\012\012Appuyer sur $ms$ pour continuer.", "%s \350 danneggiato.\012\012Eliminarlo utilizzando l'interfaccia Xbox\012e riprovare.\012\012Premi $ms$ per continuare.", "%s parece estar da\361ado.\012\012Eliminar mediante la interfaz Xbox\012e intentar de nuevo.\012\012Presionar $ms$ para continuar." };
// 0x0042C82C
const RwChar *off_42C82C[7] = { "Profile", "Profil", "Profil", "Profil", "Profil", "Profilo", "Perfil" };
// 0x004F2B74
RwInt32 dword_4F2B74;
// 0x004F3078
RwInt32 dword_4F3078;
// 0x004F5A30
RwInt32 dword_4F5A30;
// 0x004F5A38
RwChar byte_4F5A38[0x40];
// 0x004F5A78
XGAME_FIND_DATA unk_4F5A78;
// 0x004F5DC0
type_4F5DC0 dword_4F5DC0[4];
// 0x004F5DC4
#ifndef CODFH_PLAIN
type_4F5DC4 dword_4F5DC4[4];
#endif
// 0x004F6110
RwChar byte_4F6110[4];
// 0x004F6114
HANDLE dword_4F6114;
// 0x004F6118
RwChar byte_4F6118[0x40];
// 0x004F6158
RwInt32 dword_4F6158[4];
// 0x004F6168
RwInt32 dword_4F6168;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4F6170 unk_4F6170;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_06KGOJIKL@Perfil?$AA@ @ 0x003E0638
// match: ??_C@_07LOFKNAJF@Profilo?$AA@ @ 0x003E0640
// match: ??_C@_06IMMNPJLL@Profil?$AA@ @ 0x003E0648
// match: ??_C@_07EELFDIBP@Profile?$AA@ @ 0x003E0650
// match: ??_C@_0HB@IHNDLGJI@?$CFs?5parece?5estar?5da?qado?4?6?6Elimina@ @ 0x003E0658
// match: ??_C@_0GG@IBECPFLK@?$CFs?5?h?5danneggiato?4?6?6Eliminarlo?5ut@ @ 0x003E06D0
// match: ??_C@_0GL@OHHGDFGJ@?$CFs?5semble?5endommag?i?4?6?6Supprimez?9@ @ 0x003E0738
// match: ??_C@_0HD@IBCDLCEI@?$CFs?5scheint?5besch?ddigt?5zu?5sein?4?6?6@ @ 0x003E07A8
// match: ??_C@_0GN@EJKAKHHM@?$CFs?5appears?5to?5be?5damaged?4?6?6Pleas@ @ 0x003E0820
// match: ??_C@_0LD@NEEAECEH@Tu?5Xbox?5no?5tiene?5suficientes?5blo@ @ 0x003E0890
// match: ??_C@_0LH@FIHILDGO@Xbox?5non?5dispone?5di?5sufficienti?5@ @ 0x003E0948
// match: ??_C@_0NN@LCBCIHMP@La?5Xbox?5ne?5comporte?5pas?5assez?5de@ @ 0x003E0A00
// match: ??_C@_0MP@EHCFKGMC@Die?5Xbox?5hat?5nicht?5gen?$PMgend?5frei@ @ 0x003E0AE0
// match: ??_C@_0JL@LBFKGJGC@Your?5Xbox?5doesn?$JCt?5have?5enough?5fr@ @ 0x003E0BB0
// match: ??_C@_0O@HHKDPNFL@saveimage?4xbx?$AA@ @ 0x003E0C4C
// match: ??_C@_0BB@KBNNLHPJ@d?3?2saveimage?4xbx?$AA@ @ 0x003E0C5C
// match: ??_C@_03LNKIACFD@u?3?2?$AA@ @ 0x003E0C70
// match: ??_C@_0M@KICKCPHD@DANTE?$CFd?4dat?$AA@ @ 0x003E0C74
// match: ??_C@_05DIALNFFA@?$CFs?5?$CFd?$AA@ @ 0x003E0C80
// match: .CRT$XCU+0 @ 0x004271A0
// match: ?off_42C7F4@@3PAPBDA @ 0x0042C7F4
// match: ?off_42C810@@3PAPBDA @ 0x0042C810
// match: ?off_42C82C@@3PAPBDA @ 0x0042C82C

// match: _$E1 @ 0x0030C110
// match: ??0type_4F6170@@QAE@XZ @ 0x001A16D0
// sp-match: ??0type_4F6170@@QAE@XZ @ 0x0012F5B0

type_4F6170::type_4F6170()
{
    strcpy(byte_4F6110, "u:\\");
    strcpy(byte_4F6118, "d:\\saveimage.xbx");
    strcpy(byte_4F5A38, "saveimage.xbx");
    sub_1A1720();
}

// match: ?sub_1A1720@@YAXXZ @ 0x001A1720
// sp-match: ?sub_1A1720@@YAXXZ @ 0x0012EFE0
void sub_1A1720()
{
    RwInt32 lv_14[4];           // unused: the frame keeps 0x10 bytes below the counter
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        dword_4F5DC0[var_4].unk_00 = -1;
        dword_4F5DC0[var_4].unk_04 = 0;
        dword_4F5DC0[var_4].unk_08.sub_DA0A0();
    }
    dword_4F5A30 = 0;
}

#ifdef CODFH_SP
// Single player only (SP 0x12F120): whether the save drive lacks the 30
// blocks (16 KB each) a save needs; if so the shortfall goes into the blocks
// needed (dword_4F616C) for the not enough free blocks text.
// sp-match: ?sp_sub_12F120@@YAHXZ @ 0x0012F120
RwInt32 sp_sub_12F120()
{
    ULARGE_INTEGER avail;
    ULARGE_INTEGER total;
    ULARGE_INTEGER total_free;
    RwInt32 blocks;

    GetDiskFreeSpaceExA(byte_4F6110, &avail, &total, &total_free);
    blocks = avail.LowPart >> 14;
    if (blocks < 30)
    {
        dword_4F616C = 30 - blocks;
        return 1;
    }
    return 0;
}
#endif

// match: ?sub_1A1790@@YAHH@Z @ 0x001A1790
// sp-match: ?sub_1A1790@@YAHH@Z @ 0x0012F170
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1A1790(RwInt32 arg_0)
{
    RwInt32 var_8;
    HANDLE l4;

    var_8 = 10;
    do
    {
        l4 = XFindFirstSaveGame(byte_4F6110, &unk_4F5A78);
        if (l4 == INVALID_HANDLE_VALUE)
        {
            DWORD var_C = GetLastError();

            if (var_C == ERROR_SHARING_VIOLATION)
                Sleep(10);
            else
                return 0;
        }
    } while (l4 == INVALID_HANDLE_VALUE && var_8--);
    if (l4 == INVALID_HANDLE_VALUE)
        return 0;
    dword_4F6114 = l4;
    if (arg_0)
        XFindClose(l4);
    return 1;
}

// match: ?sub_1A1820@@YAHPAUtype_DA0A0@@H@Z @ 0x001A1820
// sp-match: ?sub_1A1820@@YAHPAUtype_DA0A0@@H@Z @ 0x0012F680
// Saves the record arg_0 into slot arg_4: the slot is taken (and nothing
// written while saving is off), the slot's old save game deleted, a new one
// made ("Profile <n>: <name>"), its file written behind the header, and the
// image copied in. 1 on success.
RwInt32 sub_1A1820(type_DA0A0 *arg_0, RwInt32 arg_4)
{
    HANDLE frm_72C;
    XGAME_FIND_DATA fp_728;
    RwChar stk_3E0[0x40];
    RwChar var_3A0[MAX_PATH];
    RwChar var298[0x100];
    RwChar v198[0x100];
    DWORD var_94;
    type_4F5DC0 *var90;
    DWORD v8C;
    WCHAR var_88[0x40];

    var90 = &dword_4F5DC0[arg_4];
    var90->unk_08 = *arg_0;
    var90->unk_00 = arg_4;
    if (dword_4F5A30)
    {
        var90->unk_04 = 1;
        return 0;
    }
    var_94 = sizeof(type_4F5DC0);
    sprintf(stk_3E0, "DANTE%d.dat", arg_4);
    sprintf(var298, "%s %d: %s", "Profile", arg_4 + 1, arg_0->unk_10);
    sub_1A20C0(var298, var_88);
    if (dword_4F6158[arg_4] || var90->unk_04)
    {
        RwInt32 bp_73C;
        RwChar *var738;
        RwInt32 var_734;
        BOOL var_730;

        frm_72C = XFindFirstSaveGame(byte_4F6110, &fp_728);
        while (frm_72C != INVALID_HANDLE_VALUE)
        {
            sub_1A2060(fp_728.szSaveGameName, v198);
            var738 = v198;
            var_734 = strlen(v198);
            for (bp_73C = 0; bp_73C < var_734; bp_73C++)
            {
                if (var738[bp_73C] == ':' && bp_73C > 0)
                {
                    RwChar var_73D = var738[bp_73C - 1] - '1';

                    if (var_73D == arg_4)
                    {
                        v8C = XDeleteSaveGame(byte_4F6110, fp_728.szSaveGameName);
                        break;
                    }
                }
            }
            var_730 = XFindNextSaveGame(frm_72C, &fp_728);
            if (!var_730)
            {
                XFindClose(frm_72C);
                break;
            }
        }
    }
    dword_4F6158[arg_4] = 0;
    var90->unk_04 = 1;
    if (!XCreateSaveGame(byte_4F6110, var_88, OPEN_ALWAYS, 1, var_3A0, MAX_PATH))
    {
        RwChar *v764;
        HANDLE v760;
        type_1A1820 lv_75C;
        DWORD var_744;

        v764 = &var_3A0[strlen(var_3A0)];
        strcpy(v764, stk_3E0);
        v760 = CreateFileA(var_3A0, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if (v760 == INVALID_HANDLE_VALUE)
            return 0;
        memset(&lv_75C, 0, sizeof(lv_75C));
        if (!sub_1A2000(var90, var_94, (XCALCSIG_SIGNATURE *)lv_75C.unk_04))
            return 0;
        lv_75C.unk_00 = var_94;
        if (!WriteFile(v760, &lv_75C, sizeof(lv_75C), &var_744, 0))
            return 0;
        if (!WriteFile(v760, var90, var_94, &var_744, 0))
            return 0;
        CloseHandle(v760);
        strcpy(v764, byte_4F5A38);
        if (CopyFileA(byte_4F6118, var_3A0, FALSE))
            return 1;
    }
    return 0;
}

// match: ?sub_1A1BB0@@YAXPADH@Z @ 0x001A1BB0
// sp-match: ?sub_1A1BB0@@YAXPADH@Z @ 0x0012F950
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Slot arg_4's profile name into arg_0: the name after "<n>: " in its save
// game's name, or "Profile <n>" when it has none.
void sub_1A1BB0(RwChar *arg_0, RwInt32 arg_4)
{
    RwChar var_458[0x100];
    HANDLE var_358;
    RwInt32 local_354;
    XGAME_FIND_DATA var_350;

    local_354 = 0;
    var_358 = XFindFirstSaveGame(byte_4F6110, &var_350);
    while (var_358 != INVALID_HANDLE_VALUE)
    {
        BOOL var_45C;

        sub_1A2060(var_350.szSaveGameName, var_458);
        if (!local_354)
        {
            RwChar *var_464 = var_458;
            RwInt32 local_460 = strlen(var_458);
            RwInt32 var_468;

            for (var_468 = 0; var_468 < local_460; var_468++)
            {
                if (var_464[var_468] == ':' && var_468 > 0)
                {
                    RwChar var_469 = var_464[var_468 - 1] - '1';

                    if (var_469 == arg_4)
                    {
                        local_354 = 1;
                        strcpy(arg_0, &var_464[var_468 + 2]);
                        break;
                    }
                }
            }
        }
        var_45C = XFindNextSaveGame(var_358, &var_350);
        if (!var_45C)
        {
            XFindClose(var_358);
            break;
        }
    }
    if (!local_354)
        sprintf(arg_0, "%s %d", "Profile", arg_4 + 1);
}

// match: ?sub_1A1D40@@YAHXZ @ 0x001A1D40
// sp-match: ?sub_1A1D40@@YAHXZ @ 0x0012FA50
// Reads the profiles from the save games found (sub_1A1790's search): each
// "DANTE<n>.dat" whose header, size and signature check out goes into its
// slot; a damaged one is marked (dword_4F6158) and its slot takes what was
// read. The number read.
RwInt32 sub_1A1D40()
{
    RwChar loc445;
    DWORD v444;
    DWORD var_440;
    HANDLE local_43C;
    DWORD slot_438;
    DWORD var_434[5];
    RwInt32 var420;
    type_1A1820 local_41C;
    HANDLE local_404;
    RwChar v400[MAX_PATH];
    RwChar l2F8[MAX_PATH];
    type_4F5DC0 v1F0;
    RwChar slot_118[0x100];
    RwInt32 v10;
    DWORD fp_C;
    BOOL lv_8;
    XGAME_FIND_DATA *var_4;

    var_4 = &unk_4F5A78;
    fp_C = sizeof(type_4F5DC0);
    local_404 = dword_4F6114;
    v10 = 0;
    memset(dword_4F6158, 0, sizeof(dword_4F6158));
    while (local_404 != INVALID_HANDLE_VALUE)
    {
        sub_1A2060(var_4->szSaveGameName, slot_118);
        loc445 = slot_118[8];
        var420 = loc445 - '1';
        sprintf(v400, "DANTE%d.dat", var420);
        lstrcpynA(l2F8, var_4->szSaveGameDirectory, MAX_PATH);
        lstrcatA(l2F8, v400);
        local_43C = CreateFileA(l2F8, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
        if (local_43C == INVALID_HANDLE_VALUE)
            goto damaged;
        memset(&dword_4F5DC0[var420], 0, sizeof(type_4F5DC0));
        slot_438 = GetFileSize(local_43C, &slot_438);
        if (!ReadFile(local_43C, &local_41C, sizeof(local_41C), &v444, 0))
            goto damaged;
        if (v444 != sizeof(local_41C))
            goto damaged;
        var_440 = local_41C.unk_00 + sizeof(local_41C);
        if (!ReadFile(local_43C, &v1F0, fp_C, &v444, 0))
            goto damaged;
        if (v444 != fp_C)
            goto damaged;
        if (slot_438 != var_440)
            goto damaged;
        if (!sub_1A2000(&v1F0, fp_C, (XCALCSIG_SIGNATURE *)var_434))
            goto damaged;
        if (memcmp(var_434, local_41C.unk_04, sizeof(var_434)))
            goto damaged;
        dword_4F5DC0[v1F0.unk_00] = v1F0;
        v10++;
        CloseHandle(local_43C);
        goto next;
    damaged:
        dword_4F6158[var420] = 1;
        dword_4F5DC0[var420] = v1F0;
        v10++;
        CloseHandle(local_43C);
    next:
        lv_8 = XFindNextSaveGame(dword_4F6114, &unk_4F5A78);
        if (!lv_8)
            break;
    }
    XFindClose(dword_4F6114);
    return v10;
}

// match: ?sub_1A2000@@YA_NPAXKPAUXCALCSIG_SIGNATURE@@@Z @ 0x001A2000
// sp-match: ?sub_1A2000@@YA_NPAXKPAUXCALCSIG_SIGNATURE@@@Z @ 0x0012F1D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool sub_1A2000(void *arg_0, DWORD arg_4, XCALCSIG_SIGNATURE *arg_8)
{
    DWORD var_8;
    HANDLE l4;

    l4 = XCalculateSignatureBegin(0);
    if (l4 == INVALID_HANDLE_VALUE)
        return false;
    var_8 = XCalculateSignatureUpdate(l4, (const BYTE *)arg_0, arg_4);
    if (var_8 != ERROR_SUCCESS)
        return false;
    var_8 = XCalculateSignatureEnd(l4, arg_8);
    if (var_8 != ERROR_SUCCESS)
        return false;
    return true;
}

// match: ?sub_1A2060@@YAPADPAGPAD@Z @ 0x001A2060
// sp-match: ?sub_1A2060@@YAPADPAGPAD@Z @ 0x0012F630
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwChar *sub_1A2060(WCHAR *arg_0, RwChar *arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = wcslen(arg_0);
    for (var_8 = 0; var_8 < l4; var_8++)
        arg_4[var_8] = sub_1A2110(arg_0[var_8]);
    arg_4[var_8] = 0;
    return arg_4;
}

// match: ?sub_1A20C0@@YAXPBDPAG@Z @ 0x001A20C0
// sp-match: ?sub_1A20C0@@YAXPBDPAG@Z @ 0x0012F210
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1A20C0(const RwChar *arg_0, WCHAR *arg_4)
{
    WCHAR *var_8;
    const RwChar *l4;

    var_8 = arg_4;
    l4 = arg_0;
    while (*l4)
    {
        *var_8 = *l4;
        l4++;
        var_8++;
    }
    *var_8 = 0;
}

// match: ?sub_1A2110@@YADG@Z @ 0x001A2110
// sp-match: ?sub_1A2110@@YADG@Z @ 0x0012F240
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// One wide character narrowed: the printable ASCII, the space and the
// Latin-1 letters and marks the fonts have pass; everything else is 0xDB.
RwChar sub_1A2110(WCHAR arg_0)
{
    RwUInt8 var_6;
    RwUInt8 lv_5;
    RwUInt8 *l4;

    l4 = (RwUInt8 *)&arg_0;
    lv_5 = l4[0];
    var_6 = l4[1];
    if (var_6 != 0 && var_6 != 0xFF)
        return (RwChar)0xDB;
    if (lv_5 >= 0x21 && lv_5 <= 0x7A)
        return lv_5;
    if (lv_5 == 0x20)
        return lv_5;
    if (lv_5 == 0xD1)
        return lv_5;
    if (lv_5 == 0xF1)
        return lv_5;
    if (lv_5 == 0xBF)
        return lv_5;
    if (lv_5 == 0xA1)
        return lv_5;
    if (lv_5 == 0xC1)
        return lv_5;
    if (lv_5 == 0xC9)
        return lv_5;
    if (lv_5 == 0xCD)
        return lv_5;
    if (lv_5 == 0xD3)
        return lv_5;
    if (lv_5 == 0xDA)
        return lv_5;
    if (lv_5 == 0xE1)
        return lv_5;
    if (lv_5 == 0xE9)
        return lv_5;
    if (lv_5 == 0xED)
        return lv_5;
    if (lv_5 == 0xF3)
        return lv_5;
    if (lv_5 == 0xFA)
        return lv_5;
    if (lv_5 == 0xAA)
        return lv_5;
    if (lv_5 == 0xB0)
        return lv_5;
    if (lv_5 == 0xFC)
        return lv_5;
    if (lv_5 == 0xE4)
        return lv_5;
    if (lv_5 == 0xC4)
        return lv_5;
    if (lv_5 == 0xF6)
        return lv_5;
    if (lv_5 == 0xD6)
        return lv_5;
    if (lv_5 == 0xDC)
        return lv_5;
    if (lv_5 == 0xDF)
        return lv_5;
    if (lv_5 == 0xE8)
        return lv_5;
    if (lv_5 == 0xEA)
        return lv_5;
    if (lv_5 == 0xEB)
        return lv_5;
    if (lv_5 == 0xE2)
        return lv_5;
    if (lv_5 == 0xE0)
        return lv_5;
    if (lv_5 == 0xF9)
        return lv_5;
    if (lv_5 == 0xF4)
        return lv_5;
    if (lv_5 == 0xEE)
        return lv_5;
    if (lv_5 == 0xEF)
        return lv_5;
    if (lv_5 == 0xFF)
        return lv_5;
    if (lv_5 == 0xE7)
        return lv_5;
    if (lv_5 == 0xC7)
        return lv_5;
    if (lv_5 == 0x8C)
        return lv_5;
    if (lv_5 == 0x9C)
        return lv_5;
    if (lv_5 == 0xEC)
        return lv_5;
    if (lv_5 == 0xF2)
        return lv_5;
    if (lv_5 == 0xC0)
        return lv_5;
    if (lv_5 == 0xC8)
        return lv_5;
    if (lv_5 == 0xCC)
        return lv_5;
    if (lv_5 == 0xD2)
        return lv_5;
    if (lv_5 == 0xD9)
        return lv_5;
    return (RwChar)0xDB;
}

// match: ?sub_1A24D0@@YAXPAUtype_4EBE00@@H@Z @ 0x001A24D0
// sp-match: ?sub_1A24D0@@YAXPAUtype_4EBE00@@H@Z @ 0x0012F3A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The damaged-profile box's update: the accept button, once let go since
// the box opened, closes it.
void sub_1A24D0(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_8;
    RwReal l4;

#ifdef CODFH_SP
    // Single player's bindings number the accept action 8 (SP 0x12F3A2).
    var_8 = unk_4B9308.sub_EE790(8, 0);
#else
    var_8 = unk_4B9308.sub_EE790(10, 0);
#endif
    l4 = unk_4B9308.sub_EE8F0(0, var_8);
    if (dword_4F2B74)
    {
        dword_4F2B74 = 0;
        if (l4 != 0.0f)
            dword_4F3078 = 1;
    }
    if (dword_4F3078 && l4 == 0.0f)
        dword_4F3078 = 0;
    if (l4 != 0.0f && !dword_4F3078)
    {
        sub_187040();
        dword_4B88AC = 0;
    }
}

// match: ?sub_1A2580@@YAXPAUtype_4EBE00@@H@Z @ 0x001A2580
// sp-match: ?sub_1A2580@@YAXPAUtype_4EBE00@@H@Z @ 0x0012F440
// Opens the damaged-profile box: the language's text naming profile
// dword_4F6168, nothing selected, sub_1A24D0 its update. IDA has no function
// here; it is message 0x2D's opener in off_42B518.
void sub_1A2580(type_4EBE00 *arg_0, RwInt32 arg_4)
{
    RwChar loc228[0x20];
    RwChar loc208[0x200];
    RwInt32 lv_22C = sub_19B0A0();

    sprintf(loc228, "%s %d", off_42C82C[lv_22C], dword_4F6168 + 1);
    sprintf(loc208, off_42C810[lv_22C], loc228);
    sub_18D6D0(arg_0, loc208);
    dword_4B88AC = 1;
    arg_0->unk_38 = -1;
    arg_0->unk_2CE8 = sub_1A24D0;
    arg_0->unk_2CEC = 0;
    arg_0->sub_1884B0(0, -60.0f);
}

// match: ?sub_1A2650@@YAXPAX@Z @ 0x001A2650
// sp-match: ?sub_1A2650@@YAXPAX@Z @ 0x0012F4F0
void sub_1A2650(void *arg_0)
{
    type_4F45F8 *var_4;

    var_4 = (type_4F45F8 *)arg_0;
    memcpy(var_4->unk_44, dword_4F5DC0, sizeof(dword_4F5DC0));
}

// match: ?sub_1A2680@@YAXPAX@Z @ 0x001A2680
// sp-match: ?sub_1A2680@@YAXPAX@Z @ 0x0012F510
void sub_1A2680(void *arg_0)
{
    type_4F45F8 *var_4;

    var_4 = (type_4F45F8 *)arg_0;
    memcpy(dword_4F5DC0, var_4->unk_44, sizeof(dword_4F5DC0));
}

// match: ?sub_1A26B0@@YAXH@Z @ 0x001A26B0
// sp-match: ?sub_1A26B0@@YAXH@Z @ 0x0012F530
// Marks slot arg_0 the chosen one.
void sub_1A26B0(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
        dword_4F5DC0[var_4].unk_D0 = var_4 == arg_0;
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
struct type_4F5DC4;
struct type_4F5DD8;
// 0x004F5DC4: dword_4F5DC0 + 0x4
type_4F5DC4 (&dword_4F5DC4)[4] = *(type_4F5DC4 (*)[4])((RwUInt8 *)&dword_4F5DC0 + 0x4);
// 0x004F5DD8: dword_4F5DC0 + 0x18
type_4F5DD8 (&unk_4F5DD8)[1] = *(type_4F5DD8 (*)[1])((RwUInt8 *)&dword_4F5DC0 + 0x18);
#endif

#ifdef CODFH_SP
// Single player only (SP 0x12F570): loads the chosen slot's save (the first
// slot when none is chosen) through the memory card's load (SP 0xA4CA0).
// sp-match: ?sp_sub_12F570@@YAXXZ @ 0x0012F570
void sp_sub_12F570()
{
    RwInt32 slot;
    RwInt32 i;

    slot = 0;
    for (i = 0; i < 4; i++)
    {
        if (dword_4F5DC0[i].unk_D0)
        {
            slot = i;
            break;
        }
    }
    unk_4B8744.sp_sub_A4CA0(slot);
}
#endif
