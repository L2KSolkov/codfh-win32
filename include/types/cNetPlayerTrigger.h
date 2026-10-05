/*
 * cNetPlayerTrigger (the class name it registers with the class factory at
 * 0x30C2E9, with its MakeNew, sub_1BE4D0, and its size, 0x480): the network
 * game's player trigger, derived from PlayerTrigger, anchored at its vtables
 * off_3E2F78 and off_3E2F70 (+0x18), which its constructor (sub_1BE550)
 * installs. The last one built is dword_4F8130. It respawns the local player
 * with the weapons chosen (unk_470) and the ammunition given (unk_47C).
 */
#ifndef TYPES_CNETPLAYERTRIGGER_H
#define TYPES_CNETPLAYERTRIGGER_H

#include "types/PlayerTrigger.h"

struct type_1BABA0;

class cNetPlayerTrigger : public PlayerTrigger
{
public:
    RWS_MAKENEWCLASS(cNetPlayerTrigger);
    RWS_DECLARE_CLASSID(cNetPlayerTrigger);

    cNetPlayerTrigger(const RWS::CAttributePacket &attr);
    // Its destructor is the compiler's (sub_1BE5C0: PlayerTrigger's only,
    // with no vtable stored first).

    virtual void HandleEvents(RWS::CMsg &pMsg);

    // Respawns the player entity it holds (or the one sub_1BEB00 finds) with
    // the weapons chosen: its camera and itself leave the world first.
    void sub_1BE5E0();
    // Sets up the network player sub_1BAA90 gives it (dword_4F8060).
    void sub_1BE9B0();
    // Moves it to the matrix arg_0, raised by unk_144.
    void sub_1BEAC0(const RwMatrixTag *arg_0);
    // Holds the player sub_1B7B20 gives it and tells the multiplayer
    // manager.
    void sub_1BEB00();

    RwInt32 unk_470[2];         // the weapons chosen (-1 for none)
    RwInt32 unk_478;            // a weapon given unk_47C rounds
    RwInt32 unk_47C;
};

#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern cNetPlayerTrigger *&dword_4F8130;
#else
extern cNetPlayerTrigger *dword_4F8130;
#endif
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_1BABA0 *&dword_4F8060;
#else
extern type_1BABA0 *dword_4F8060;
#endif
// The asynchronous loads' wait (types/asynchload.h, not included here: its
// kernel header clashes with the XDK's).
void sub_821C0();

#endif
