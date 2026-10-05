// The queued messages' data (game/netqueue.h): each kind copies it into
// its own pool and gives it back, and the same for what came in.

#include <string.h>

#include "game/netqueue.h"

// match: ?vf_004@type_3E4E58@@UAEHPBEH@Z @ 0x001D7A50
RwInt32 type_3E4E58::vf_004(const RwUInt8 *arg_0, RwInt32 arg_4)
{
    RwUInt32 bytes;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_10)
    {
    }
    bytes = (RwUInt32)(arg_4 + 7) >> 3;
    unk_10 = (RwUInt8 *)sub_1CBC50()->sub_1F8BF0(bytes);
    unk_14 = arg_4;
    if (!unk_10)
        return 0;
    memcpy(unk_10, arg_0, bytes);
    return 1;
}

// match: ?vf_008@type_3E4E58@@UAEXXZ @ 0x001D7AC0
void type_3E4E58::vf_008()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_10)
    {
    }
    sub_1CBC50()->sub_1F8C30(unk_10);
    unk_10 = 0;
}

// match: ?vf_004@type_3E4E4C@@UAEHPBEH@Z @ 0x001D7AF0
RwInt32 type_3E4E4C::vf_004(const RwUInt8 *arg_0, RwInt32 arg_4)
{
    RwUInt32 bytes;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_10)
    {
    }
    bytes = (RwUInt32)(arg_4 + 7) >> 3;
    unk_10 = (RwUInt8 *)sub_1CBC40()->sub_1F8BF0(bytes);
    unk_14 = arg_4;
    if (!unk_10)
        return 0;
    memcpy(unk_10, arg_0, bytes);
    return 1;
}

// match: ?vf_008@type_3E4E4C@@UAEXXZ @ 0x001D7B60
void type_3E4E4C::vf_008()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_10)
    {
    }
    sub_1CBC40()->sub_1F8C30(unk_10);
    unk_10 = 0;
}

// match: ?vf_004@type_3E4E40@@UAEHPBEH@Z @ 0x001D7B90
RwInt32 type_3E4E40::vf_004(const RwUInt8 *arg_0, RwInt32 arg_4)
{
    RwUInt32 bytes;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_10)
    {
    }
    bytes = (RwUInt32)(arg_4 + 7) >> 3;
    unk_10 = (RwUInt8 *)sub_1CBC70()->sub_1F8BF0(bytes);
    unk_14 = arg_4;
    if (!unk_10)
        return 0;
    memcpy(unk_10, arg_0, bytes);
    return 1;
}

// match: ?vf_008@type_3E4E40@@UAEXXZ @ 0x001D7C00
void type_3E4E40::vf_008()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_10)
    {
    }
    sub_1CBC70()->sub_1F8C30(unk_10);
    unk_10 = 0;
}

// match: ?sub_1D7C30@type_1D7CA0@@QAEHPBEH@Z @ 0x001D7C30
RwInt32 type_1D7CA0::sub_1D7C30(const RwUInt8 *arg_0, RwInt32 arg_4)
{
    RwUInt32 bytes;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_08)
    {
    }
    bytes = (RwUInt32)(arg_4 + 7) >> 3;
    unk_08 = (RwUInt8 *)sub_1CBC60()->sub_1F8BF0(bytes);
    if (!unk_08)
        return 0;
    unk_0C = arg_4;
    memcpy(unk_08, arg_0, bytes);
    return 1;
}

// match: ?sub_1D7CA0@type_1D7CA0@@QAEXXZ @ 0x001D7CA0
void type_1D7CA0::sub_1D7CA0()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (unk_08)
    {
    }
    sub_1CBC60()->sub_1F8C30(unk_08);
    unk_08 = 0;
    unk_0C = 0;
}
