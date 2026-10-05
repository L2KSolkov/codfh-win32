/*
 * The network session (type_4F8058, dword_4F8058) and the network game's
 * message listener (type_3E3860_10): their vtables (off_3E66B0, off_3E66C8)
 * follow cXboxLive's file's data.
 */
#include <new>

#include "game/netmsg.h"
#include "game/netplayer.h"
#include "game/voice.h"
#include "types/type_DC400.h"
#include "game/mpgame.h"

// Its data definitions (PLAN M5), in the image's address order.
// End of its data definitions.

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E3860_10@@6B@ @ 0x003E66B0
// match: ??_7type_4F8054_A4@@6B@ @ 0x003E66B8
// match: .CRT$XCU+0 @ 0x00427230
// match: .CRT$XCU+4 @ 0x00427234
// match: ?vf_000@type_4F8054_A4@@UAEXHHHHH@Z @ 0x001DE440

// match: _$E2 @ 0x0030C9A0
// match: _$E4 @ 0x0030C9D0

// The stream the sends write their message into.
extern type_1F8560 unk_502EF0;

// match: ??0type_3E3860_10@@QAE@PAUtype_4F8054@@@Z @ 0x001DDBE0
type_3E3860_10::type_3E3860_10(type_4F8054 *arg_0)
{
    unk_04 = arg_0;
    unk_08 = 0;
}

// match: ??_Gtype_3E3860_10@@UAEPAXI@Z @ 0x001DDC20

// match: ?sub_1DDC50@type_3E3860_10@@QAEHPAUtype_1F8560@@HABUtype_1DDE20_mask@@@Z @ 0x001DDC50
RwInt32 type_3E3860_10::sub_1DDC50(type_1F8560 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    return unk_04->sub_1CC730(arg_8, arg_0, arg_4);
}

// match: ?vf_000@type_3E3860_10@@UAEXHHHHH@Z @ 0x001DDC80
void type_3E3860_10::vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    if (unk_08)
        unk_08->vf_000(arg_0, arg_4, arg_8, arg_C, arg_10);
}














// The voice channel (type_3E3870, game/voice.h): the voice manager's
// packets to and from the peers, relayed through the peers the routing
// table gives, the incoming ones queued per sender in number order and
// played when they are next or have waited too long.

// How long an incoming packet may wait, in milliseconds.
extern RwInt32 dword_503304;
// The routing table: for each number of peers, the peer to send through.
























// The bit stream messages are written to (sub_1F8B90), over its buffer.
RwUInt8 unk_502EFC[0x408];
type_1F8560 unk_502EF0(unk_502EFC, 0x205F);
// The voice packets' wait. It has a dynamic initializer, so its value
// comes through an inline function, not a constant expression.
inline RwInt32 voice_timing(RwInt32 arg_0)
{
    return arg_0;
}
RwInt32 dword_503304 = voice_timing(800);

// Empty and out of line (folded by /OPT:ICF into the shared pDtor, 0x1E41C0).
void type_3E3870::pDtor()
{
}
