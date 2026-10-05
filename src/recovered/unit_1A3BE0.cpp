// The multiplayer game's settings and names (game/mpgame.h).

#include "game/mpgame.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_03EBKHDLCO@Any?$AA@ @ 0x003E11C4
// match: ??_C@_09CNKIHGHP@Supremacy?$AA@ @ 0x003E11C8
// match: ??_C@_0BD@FCICOBGD@Search?5And?5Destroy?$AA@ @ 0x003E11D4
// match: ??_C@_03OMGOFJGM@ANY?$AA@ @ 0x003E11E8
// match: ??_C@_03NHMPDBKA@SUP?$AA@ @ 0x003E11EC
// match: ??_C@_02PKFBDMAF@SD?$AA@ @ 0x003E11F0
// match: ??_C@_03JKIMLJNP@CTF?$AA@ @ 0x003E11F4
// match: ??_C@_03KIJAKMEC@TDM?$AA@ @ 0x003E11F8
// match: ??_C@_02DCPKDCLJ@DM?$AA@ @ 0x003E11FC
// match: .CRT$XCU+0 @ 0x004271A4

// match: _$E1 @ 0x0030C120

// The settings themselves, built by their dynamic initializer.
type_4F61F8 unk_4F61F8;

// match: ??0type_4F61F8@@QAE@XZ @ 0x001A3BE0
type_4F61F8::type_4F61F8()
{
    unk_104 = 0;
    unk_100 = 2000;
}

// match: ?sub_1A3C10@@YAPBDH@Z @ 0x001A3C10
const RwChar *sub_1A3C10(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 1:
        return "Deathmatch";
    case 2:
        return "Team Deathmatch";
    case 4:
        return "Capture The Flag";
    case 8:
        return "Search And Destroy";
    case 16:
        return "Supremacy";
    case 32:
        return "Any";
    default:
        return "";
    }
}

// match: ?sub_1A3CB0@@YAPBDH@Z @ 0x001A3CB0
const RwChar *sub_1A3CB0(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 1:
        return "DM";
    case 2:
        return "TDM";
    case 4:
        return "CTF";
    case 8:
        return "SD";
    case 16:
        return "SUP";
    case 32:
        return "ANY";
    default:
        return "";
    }
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004F62F8: unk_4F61F8 + 0x100
RwUInt16 &word_4F62F8 = *(RwUInt16 *)((RwUInt8 *)&unk_4F61F8 + 0x100);
// 0x004F62FC: unk_4F61F8 + 0x104
RwInt32 &dword_4F62FC = *(RwInt32 *)((RwUInt8 *)&unk_4F61F8 + 0x104);
// 0x004F6300: unk_4F61F8 + 0x108
RwInt32 &dword_4F6300 = *(RwInt32 *)((RwUInt8 *)&unk_4F61F8 + 0x108);
#endif
