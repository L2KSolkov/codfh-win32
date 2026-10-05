// The Alfa files' resource handler (types/type_3DA848.h): the script system's
// data and script files loaded from the level stream. The original file
// name is not in the image, so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/cresourcehandler.h"
#include "types/type_3DA848.h"
#include "types/type_72810.h"
#include "types/scriptvm.h"
#include "game/functions.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429C04
const RwChar *off_429C04 = "spID_AlfaDataFile";
// 0x00429C08
const RwChar *off_429C08 = "spID_AlfaScriptFile";
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has these constants before the data's texts.)
// 0x003DA81C
extern const RwReal flt_3DA81C = 16.666666f;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_3DA848 dword_4CF7D4;
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA81C@@3MB @ 0x003DA81C
// match: ??_C@_0BE@HEEJLOIE@spID_AlfaScriptFile?$AA@ @ 0x003DA820
// match: ??_C@_0BC@FKMOBGAH@spID_AlfaDataFile?$AA@ @ 0x003DA834
// match: ??_7type_3DA848@@6B@ @ 0x003DA848
// match: .CRT$XCU+0 @ 0x0042709C
// match: ?off_429C04@@3PBDB @ 0x00429C04
// match: ?off_429C08@@3PBDB @ 0x00429C08

// match: _$E2 @ 0x0030B7F0
// match: _$E3 @ 0x0030E600
// match: ?Load@type_3DA848@@UAEPAXPBD00PAURwStream@@IAAI@Z @ 0x00129200

void *type_3DA848::Load(const RwChar *psName, const RwChar *psType, const RwChar *psResourcePath,
                        RwStream *pStream, RwUInt32 uiStreamSize, RwUInt32 &uiResourceSize)
{
    void *var_4;

    var_4 = 0;
    if (!_strcmpi(psType, off_429C04))
    {
        var_4 = sub_129350(pStream, uiStreamSize);
    }
    else if (!_strcmpi(psType, off_429C08))
    {
        var_4 = sub_1293A0(pStream, uiStreamSize);
    }
    return var_4;
}

// match: ?UnLoad@type_3DA848@@UAEHPBDPAX@Z @ 0x00129270
// A data file stays; a kind 3 script file's imports are released and it is
// freed.
RwBool type_3DA848::UnLoad(const RwChar *pStrType, void *pResource)
{
    type_72BA0 *var_4;
    type_72990 *local_8;

    if (!_strcmpi(pStrType, off_429C04))
    {
        return 1;
    }
    if (!_strcmpi(pStrType, off_429C08))
    {
        local_8 = (type_72990 *)sub_72BA0((RwChar *)pResource);
        var_4 = (type_72BA0 *)pResource;
        switch (var_4->unk_03)
        {
        case 3:
            sub_72960(local_8);
            operator delete(pResource);
            break;
        }
        return 1;
    }
    return 0;
}

// match: ?IsHandled@type_3DA848@@UAEHPBD@Z @ 0x00129300
RwBool type_3DA848::IsHandled(const RwChar *psType)
{
    if (!_strcmpi(psType, off_429C04))
    {
        return 1;
    }
    if (!_strcmpi(psType, off_429C08))
    {
        return 1;
    }
    return 0;
}

// match: ?sub_129350@type_3DA848@@QAEPAXPAURwStream@@I@Z @ 0x00129350
void *type_3DA848::sub_129350(RwStream *arg_0, RwUInt32 arg_4)
{
    RwChar *var_4;

    var_4 = (RwChar *)RWSMalloc(arg_4, 0x34255);  // a memory hint; not an address
    RwStreamRead(arg_0, var_4, arg_4);
    sub_67E30(var_4);
    return var_4;
}

// match: ?sub_1293A0@type_3DA848@@QAEPAXPAURwStream@@I@Z @ 0x001293A0
// Reads a script file, relocated; a kind 3 file's imports resolved.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *type_3DA848::sub_1293A0(RwStream *arg_0, RwUInt32 arg_4)
{
    RwChar *var_4;
    type_72BA0 *v8;
    type_72990 *varC;

    var_4 = (RwChar *)RWSMalloc(arg_4, 0x34255);  // a memory hint; not an address
    RwStreamRead(arg_0, var_4, arg_4);
    varC = (type_72990 *)sub_72BA0(var_4);
    v8 = (type_72BA0 *)var_4;
    switch (v8->unk_03)
    {
    case 3:
        sub_72920(varC);
        break;
    }
    return var_4;
}

// match: ??0type_3DA848@@QAE@XZ @ 0x00129410
// Out of line for dword_4CF7D4's dynamic initializer.
type_3DA848::type_3DA848()
{
}
