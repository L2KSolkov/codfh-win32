// The debug print, a string key's comparisons and kujuUI's file input
// (game/fileio.h).

#include <xtl.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "game/fileio.h"
#include "game/assert.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CBE8
RwChar unk_42CBE8[] = "@Ih\x94" "\x90" "\x93" "\x95" "fij\x96" "{C|D^FGq\x81" "rH\x97" "m\x8F" "nOQeobpP";
// 0x0042CC0C
RwChar unk_42CC0C[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 0x0042CC34
RwChar unk_42CC34[] = "0123456789abcdefghijklmnopqrstuvwxyz";
// 0x0042CC5C
const RwChar *unk_42CC5C = "filein.log";
// 0x0042CC60
const RwChar *dword_42CC60 = "";
// 0x004FE6A8
RwChar OutputString[1028];
// 0x004FEAAC
RwFileFunctions *dword_4FEAAC;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@GJFBCOAC@filein?4log?$AA@ @ 0x003E3AFC
// match: ??_C@_0BP@IIKJBKOA@?2COD?2SHARED?2fileIO?2cFileIn?4cpp?$AA@ @ 0x003E3B08
// match: ??_C@_0FO@GLBJIOGK@bool?5__thiscall?5kujuUI?3?3cFileIn?3@ @ 0x003E3B28
// match: ??_C@_0BJ@JJAFICHF@Unable?5to?5open?5file?5?$CFs?$CB?6?$AA@ @ 0x003E3B88
// match: __ehhandler$?sub_1C8CA0@kujuUI@@YAXPBDPAPAUcFileIn@1@@Z>1>8 @ 0x0041F6DC
// match: __ehhandler$?sub_1C8CA0@kujuUI@@YAXPBDPAPAUcFileIn@1@@Z>1 @ 0x0041F6E4
// match: ?unk_42CBE8@@3PADA @ 0x0042CBE8
// match: ?unk_42CC0C@@3PADA @ 0x0042CC0C
// match: ?unk_42CC34@@3PADA @ 0x0042CC34
// match: ?unk_42CC5C@@3PBDB @ 0x0042CC5C
// match: ?dword_42CC60@@3PBDB @ 0x0042CC60

// match: ?sub_1C8A30@@YAXPBDZZ @ 0x001C8A30

void sub_1C8A30(const RwChar *arg_0, ...)
{
    va_list var_4;

    va_start(var_4, arg_0);
    vsprintf(OutputString, arg_0, var_4);
    OutputDebugStringA(OutputString);
}

// match: ??4type_1C8A60@@QAEAAU0@ABU0@@Z @ 0x001C8A60
type_1C8A60 &type_1C8A60::operator=(const type_1C8A60 &arg_0)
{
    unk_00 = arg_0.unk_00;
    return *this;
}

// match: ??8type_1C8A60@@QBE_NABU0@@Z @ 0x001C8A80
bool type_1C8A60::operator==(const type_1C8A60 &arg_0) const
{
    return !strcmp(arg_0.unk_00, unk_00);
}

// match: ??Mtype_1C8A60@@QBE_NABU0@@Z @ 0x001C8AB0
bool type_1C8A60::operator<(const type_1C8A60 &arg_0) const
{
    return strcmp(arg_0.unk_00, unk_00) > 0;
}

// match: ??0cFileIn@kujuUI@@QAE@PAX@Z @ 0x001C8AE0
kujuUI::cFileIn::cFileIn(void *arg_0)
{
    unk_00 = arg_0;
    unk_04 = 0;
}

// match: ??1cFileIn@kujuUI@@QAE@XZ @ 0x001C8B10
kujuUI::cFileIn::~cFileIn()
{
    RwInt32 var_4;

    var_4 = dword_4FEAAC->rwfclose(unk_00);
}

// match: ?readVector@cFileIn@kujuUI@@QAE_NPAXIII@Z @ 0x001C8B40
bool kujuUI::cFileIn::readVector(void *arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C)
{
    bool var_1;

    if (arg_4 * arg_8 > arg_C)
    {
        sub_1C7F20(false, "\\COD\\SHARED\\fileIO\\cFileIn.cpp", 0x9F,
                   "bool __thiscall kujuUI::cFileIn::readVector(void *,unsigned long,unsigned long,unsigned long)", 3);
        return false;
    }
    var_1 = sub_1C8BA0(arg_0, arg_4 * arg_8);
    return var_1;
}

// match: ?sub_1C8BA0@cFileIn@kujuUI@@QAE_NPAXI@Z @ 0x001C8BA0
bool kujuUI::cFileIn::sub_1C8BA0(void *arg_0, RwUInt32 arg_4)
{
    RwUInt32 var_4;
    bool l5;

    var_4 = dword_4FEAAC->rwfread(arg_0, 1, arg_4, unk_00);
    l5 = var_4 == arg_4;
    return l5;
}

// match: ?sub_1C8BE0@cFileIn@kujuUI@@QAE_NPAX@Z @ 0x001C8BE0
bool kujuUI::cFileIn::sub_1C8BE0(void *arg_0)
{
    return sub_1C8BA0(arg_0, 4);
}

// match: ?sub_1C8C00@cFileIn@kujuUI@@QAE_NPADI@Z @ 0x001C8C00
bool kujuUI::cFileIn::sub_1C8C00(RwChar *arg_0, RwUInt32 arg_4)
{
    bool var_5 = true;
    RwUInt32 l4 = 0;
    RwChar lv_6 = ' ';

    do
    {
        var_5 = sub_1C8BA0(&lv_6, 1);
        if (var_5)
        {
            if (l4 < arg_4 && !sub_1C8DC0())
            {
                arg_0[l4] = lv_6;
                l4++;
            }
            else
            {
                var_5 = false;
                arg_0[l4] = 0;
            }
        }
    } while (lv_6 && var_5);
    if (!var_5)
        *arg_0 = 0;
    return var_5;
}

// match: ?sub_1C8CA0@kujuUI@@YAXPBDPAPAUcFileIn@1@@Z @ 0x001C8CA0
// match: __ehhandler$?sub_1C8CA0@kujuUI@@YAXPBDPAPAUcFileIn@1@@Z-0xE @ 0x00303330
// match: __ehhandler$?sub_1C8CA0@kujuUI@@YAXPBDPAPAUcFileIn@1@@Z @ 0x0030333E
void kujuUI::sub_1C8CA0(const RwChar *arg_0, cFileIn **arg_4)
{
    RwChar var_114[0x100];
    void *var_10;

    *arg_4 = 0;
    if (!dword_4FEAAC)
        dword_4FEAAC = RwOsGetFileInterface();
    strcpy(var_114, dword_42CC60);
    strcat(var_114, arg_0);
    var_10 = dword_4FEAAC->rwfopen(var_114, "rb");
    if (var_10)
        *arg_4 = new cFileIn(var_10);
    else if (0)
        sub_1C8A30("Unable to open file %s!\n", arg_0);
}

// match: ?sub_1C8DC0@cFileIn@kujuUI@@QAE_NXZ @ 0x001C8DC0
bool kujuUI::cFileIn::sub_1C8DC0()
{
    if (unk_04)
        return false;
    return dword_4FEAAC->rwfeof(unk_00);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_1C8A60@@QAE@PBD@Z (folded into 0x12A1B0)
type_1C8A60::type_1C8A60(RwChar const *arg_0) : unk_00(arg_0)
{
}
