/*
 * type_1DDE20_mask: the peers a network message goes to (the session's
 * sub_1DDE20 takes it), one bit each.
 */
#ifndef TYPE_1DDE20_MASK_H
#define TYPE_1DDE20_MASK_H

#include "rw/ostypes.h"

// What sub_1D48B0 builds a mask from: 0 for every peer (its only case).
enum type_1DDE20_mask_fill
{
    type_1DDE20_mask_fill_all = 0
};

// The peers a message goes to, one bit each; cleared by its constructor.
struct type_1DDE20_mask
{
    RwUInt16 unk_00;

    type_1DDE20_mask()
    {
        unk_00 = 0;
    }
    // Inline: the voice manager's send (sub_1C6700) builds its copy in place
    // on the stack through a `this` temporary.
    type_1DDE20_mask(type_1DDE20_mask &arg_0)
    {
        unk_00 = arg_0.unk_00;
    }
    // Const packet copies use a checked overload. Evidence: the implicit
    // message/ack copy constructors (sub_1D43B0/sub_1D4320) advance the
    // register between the mask's destination temporary and member copy.
    // Two word checks supply that one-register step (docs/toolchain.md).
    type_1DDE20_mask(const type_1DDE20_mask &arg_0)
    {
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        unk_00 = arg_0.unk_00;
    }
    // Just the peers arg_0 (the voice chat sends to one peer with it). A
    // compiled-out check: the players' calls with it (sub_1CD690) load a
    // register one on (docs/toolchain.md).
    type_1DDE20_mask(RwUInt16 arg_0)
    {
        if (!unk_00)
        {
        }
        unk_00 = arg_0;
    }
    // Whether the masks are equal: an inline with no address. Evidence: the
    // player vote's update (sub_223130) compares through a bool return with
    // the member mask as `this`.
    bool operator==(const type_1DDE20_mask &arg_0) const
    {
        return unk_00 == arg_0.unk_00;
    }
    // Whether the masks differ: an inline with no address. Evidence: the
    // scoreboards' update (sub_220300) compares through a bool return with
    // the member mask loaded first.
    bool operator!=(const type_1DDE20_mask &arg_0) const
    {
        return unk_00 != arg_0.unk_00;
    }
    // Adds peer arg_0; an inline with no address, named for what it does.
    // Evidence: the bomb sites' sync (sub_1A7D80) stores the literal peer
    // number in a slot of its own and shifts by it, as a reference
    // parameter gives.
    void set(const RwInt32 &arg_0)
    {
        unk_00 |= 1 << arg_0;
    }
    // Whether it is empty, and takes peer arg_0 out; inlines with no
    // address, named for what they do (the players' sub_1A8050).
    RwInt32 empty() const
    {
        return unk_00 == 0;
    }
    void clear(RwInt32 arg_0)
    {
        // Two compiled-out checks: the registers after them are two loads
        // on (docs/toolchain.md).
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        unk_00 &= ~(1 << arg_0);
    }
    // Takes peer arg_0 out, by reference: an inline with no address, named
    // for what it does. Evidence: the players' connection report
    // (sub_1CFFF0) clears a member mask's bit through a `this` temporary
    // with no slot for the peer, two loads on.
    void remove(const RwInt32 &arg_0)
    {
        // Two compiled-out checks (docs/toolchain.md).
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        unk_00 &= ~(1 << arg_0);
    }
    // Just peer arg_0, by reference: an inline with no address, named for
    // what it does. Evidence: the game data's sends (sub_1B4EA0, sub_1B4F40)
    // store the literal peer in a slot of its own and store the shifted bit
    // over the mask.
    void only(const RwInt32 &arg_0)
    {
        unk_00 = 1 << arg_0;
    }
    // The same by value, through a local of its own: an inline with no
    // address, named for what it does. Evidence: the game data's level load
    // (sub_1B4F40) stores the literal peer in a slot allocated with the
    // inlines' after its accessors' temporaries.
    void just(RwInt32 arg_0)
    {
        RwInt32 r = arg_0;

        unk_00 = 1 << r;
    }
    // Adds peer arg_0 by value through a local of its own: an inline with
    // no address, named for what it does. Evidence: the flag part's and the
    // bomb sites' sends (sub_1B1B00, sub_1A7D80) store the literal peer in a
    // slot allocated with the inlines', after the other sends' temporaries.
    void put(RwInt32 arg_0)
    {
        RwInt32 r = arg_0;

        unk_00 |= 1 << r;
    }
    // Adds peer arg_0 by value with no checks: an inline with no address,
    // named for what it does. Evidence: the game data's sub_1B4D40 sets its
    // mask's bits through it (no slot for the peer, registers as no check).
    void include(RwInt32 arg_0)
    {
        unk_00 |= 1 << arg_0;
    }
    // Adds peer arg_0 by value: an inline with no address, named for what
    // it does. Evidence: the voice chat (sub_1C6530) sets a member mask's
    // bit through a `this` temporary with no slot for the peer.
    void add(RwInt32 arg_0)
    {
        // Two compiled-out checks: the registers after them are two loads
        // on (docs/toolchain.md).
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        unk_00 |= 1 << arg_0;
    }
    // Adds peer arg_0 by reference: an inline with no address, named for
    // what it does. Evidence: the players' connection report (sub_1CFFF0)
    // sets a member mask's bit through a `this` temporary and no slot for
    // the peer where add's by-value peer gets one.
    void insert(const RwInt32 &arg_0)
    {
        // Two compiled-out checks (docs/toolchain.md).
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        unk_00 |= 1 << arg_0;
    }
    // Adds the peers in arg_0: an inline with no address, named for what
    // it does. Evidence: the voice channel's sends (sub_1DF2A0, sub_1DEE60)
    // or a mask into theirs with no checks.
    void merge(const type_1DDE20_mask &arg_0)
    {
        unk_00 |= arg_0.unk_00;
    }
    // The same with two compiled-out checks (docs/toolchain.md): the voice
    // channel's microphone send (sub_1DEE60) ors the peers into a packet's
    // mask through a `this` temporary, the registers after them two loads
    // on.
    void join(const type_1DDE20_mask &arg_0)
    {
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        unk_00 |= arg_0.unk_00;
    }
    // Sets its peers to arg_0 by value: an inline with no address, named
    // for what it does. Evidence: the voice channel's receive (sub_1DE900)
    // keeps the value read in a word slot of its own before the store.
    void bits(RwUInt16 arg_0)
    {
        unk_00 = arg_0;
    }
    // Takes peer arg_0 out with no checks: an inline with no address, named
    // for what it does. Evidence: the voice channel's routing (sub_1DF1E0)
    // clears a bit with no register shift.
    void drop(RwInt32 arg_0)
    {
        unk_00 &= ~(1 << arg_0);
    }
    // Likewise after a compiled-out check (docs/toolchain.md): an inline
    // with no address, named for what it does. Evidence: the late service's
    // frame (sub_2266D0) takes a registered peer out through a `this` slot,
    // the registers two loads on and no slot for the peer.
    void discard(RwInt32 arg_0)
    {
        if (!unk_00)
        {
        }
        unk_00 &= ~(1 << arg_0);
    }
    // Its counterpart, setting the bit. Evidence: the late service's
    // registration request (sub_2275F0) sets a peer through a `this` slot,
    // the registers two loads on.
    void admit(RwInt32 arg_0)
    {
        if (!unk_00)
        {
        }
        unk_00 |= 1 << arg_0;
    }
    // Takes peer arg_0 out by value through a local of its own: an inline
    // with no address, named for what it does. Evidence: the kick page's
    // fill (sub_2184D0) keeps the literal peer 0 in a slot allocated with
    // the inlines' and shifts by it; a compiled-out check puts the registers
    // after it one load on.
    void unset(RwInt32 arg_0)
    {
        if (!unk_00)
        {
        }
        RwInt32 r = arg_0;

        unk_00 &= ~(1 << r);
    }
    // The same by reference: the kick page's kick (sub_218800) keeps the
    // literal peer 0 in a slot allocated in order with its other
    // temporaries.
    void reset(const RwInt32 &arg_0)
    {
        if (!unk_00)
        {
        }
        unk_00 &= ~(1 << arg_0);
    }
    // Peer arg_0's bit if it is in it: an inline with no address, named for
    // what it does. Evidence: the kick page's fill and kick (sub_2184D0,
    // sub_218800) shift before they load the mask, the registers one load on
    // from a compiled-out check.
    RwInt32 in(const RwUInt32 &arg_0) const
    {
        if (!unk_00)
        {
        }
        return unk_00 & (1 << arg_0);
    }
    // Whether it shares a peer with arg_0: an inline with no address, named
    // for what it does. Evidence: the network queue's sub_1D0B30 and
    // sub_1D4530 test it as a 1 or 0.
    RwInt32 overlaps(const type_1DDE20_mask &arg_0)
    {
        return (unk_00 & arg_0.unk_00) ? 1 : 0;
    }
    // Peer arg_0's bit if it is in it: an inline with no address, named for
    // what it does. Evidence: the voice chat's tests shift before they load
    // the mask, as an inline's return expression gives.
    RwInt32 test(RwInt32 arg_0) const
    {
        return unk_00 & (1 << arg_0);
    }
    // The same after a compiled-out check on the peer (docs/toolchain.md).
    // Evidence: the voice status update (sub_1C7840) tests a peer's mute bit
    // with the registers one load on.
    RwInt32 test_checked(RwInt32 arg_0) const
    {
        if (!(arg_0 & 1))
        {
        }
        return unk_00 & (1 << arg_0);
    }
    // The same after a compiled-out check: an inline with no address, named
    // for what it gives. Evidence: the log's debug display (sub_1B00F0)
    // tests the peers' bits a register load on.
    RwInt32 bit(RwInt32 arg_0) const
    {
        if (!unk_00)
        {
        }
        return unk_00 & (1 << arg_0);
    }
    // Whether peer arg_0 is in it, and adds or takes out peer arg_0 as
    // arg_4 says: inlines with no address, named for what they do (the
    // voice chat's sub_1C7840 and sub_1C7C70).
    // include() after one compiled-out check: an inline with no address,
    // named for what it does. Evidence: the time keeper's step
    // (sub_1D4CA0) shifts by the peer in its parameter's slot with the
    // registers one load on (docs/toolchain.md).
    void include_checked(RwInt32 arg_0)
    {
        if (!unk_00)
        {
        }
        unk_00 |= 1 << arg_0;
    }
    // The peers in both: an inline with no address, named for what it
    // does. Evidence: the time keeper's step (sub_1D4CA0) builds the result
    // in a local of its own and returns it through a temporary.
    friend type_1DDE20_mask operator&(const type_1DDE20_mask &arg_0, const type_1DDE20_mask &arg_4)
    {
        type_1DDE20_mask r;
        r.unk_00 = arg_0.unk_00 & arg_4.unk_00;
        // A compiled-out check: the copies after it are one load on
        // (docs/toolchain.md).
        if (!r.unk_00)
        {
        }
        return r;
    }
    // Adds peer arg_0 after two compiled-out checks, through a local of its
    // own: an inline with no address, named for what it does. Evidence:
    // the vote call (sub_1C32B0) fills the client's mask with the peer in a
    // slot after the checks' register shift (docs/toolchain.md).
    void mark(RwInt32 arg_0)
    {
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        RwInt32 r = arg_0;

        unk_00 |= 1 << r;
    }
    // Whether it holds exactly one peer (its lowest bit is all of it): an
    // inline with no address, named for what it does. Evidence: the
    // network game's message checks (sNetGameEP.cpp) keep the mask in a
    // local of their own and compare through a 1 or 0.
    RwInt32 single() const
    {
        RwInt32 r = unk_00;
        if ((-r & unk_00) == unk_00)
            return 1;
        // A compiled-out check: the registers after the call are one load
        // on (docs/toolchain.md).
        if (!(r & 1))
        {
        }
        return 0;
    }
    RwInt32 has(RwInt32 arg_0)
    {
        return (unk_00 & (1 << arg_0)) != 0;
    }
    // The same after a compiled-out check on the peer (docs/toolchain.md).
    // Evidence: the voice status update (sub_1C7840) tests the speaker and
    // mute masks with the registers one load on.
    RwInt32 has_checked(RwInt32 arg_0)
    {
        if (!(arg_0 & 1))
        {
        }
        return (unk_00 & (1 << arg_0)) != 0;
    }
    // Out of line (sub_1D48B0): every peer for type_1DDE20_mask_fill_all,
    // otherwise left as it is.
    type_1DDE20_mask(type_1DDE20_mask_fill arg_0);
    // Out of line: its highest peer, its lowest peer (the players' join
    // step prints it as the player it failed to connect to) and how many
    // peers it holds.
    RwInt32 sub_1D48E0();
    RwInt32 sub_1D4900();
    RwInt32 sub_1D4A60();
    // Out of line: the peers in it as text, "Empty" or "1, 3" (the server's
    // join step prints it).
    const RwChar *sub_1D4990();
    void assign(RwInt32 arg_0, RwInt32 arg_4)
    {
        // Two compiled-out checks: the registers after them are two loads
        // on (docs/toolchain.md).
        if (!unk_00)
        {
        }
        if (!unk_00)
        {
        }
        if (arg_4)
            unk_00 |= 1 << arg_0;
        else
            unk_00 &= ~(1 << arg_0);
    }
};
// Takes peer arg_4 out of the mask arg_0 through locals of its own: a free
// inline with no address, named for what it does. Evidence: the player
// vote's fill (sub_222D20) stores the peer before the mask's address, both
// in slots placed after the function's temporaries.
inline void take_out_peer(type_1DDE20_mask &arg_0, RwInt32 arg_4)
{
    RwInt32 r = arg_4;
    type_1DDE20_mask *m = &arg_0;

    m->unk_00 &= ~(1 << r);
}
// Peer arg_4's bit in the mask arg_0 after a compiled-out check on the peer
// (docs/toolchain.md): a free inline with no address, named for what it
// does. Evidence: the voice chat's status tests (sub_22B040, sub_22B0C0)
// shift by the peer one register on at their first and third tests, with
// no `this` slot (a member variant adds one).
inline RwInt32 peer_in(const type_1DDE20_mask *arg_0, RwInt32 arg_4)
{
    if (!(arg_4 & 1))
    {
    }
    return arg_0->unk_00 & (1 << arg_4);
}


#endif
