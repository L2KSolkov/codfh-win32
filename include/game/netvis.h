/*
 * The network triggers' visibility settings: the data of the message
 * "kujuUpdateTriggerObjectVisibility" (its data type string is
 * "sNetTriggerVisibility *"), which cNetTriggerViewControl fills and sends
 * and cNetPickupTrigger and cNetSpawnPoint register. Its own header so the
 * three behaviours can share it.
 */
#ifndef GAME_NETVIS_H
#define GAME_NETVIS_H

#include "rw/ostypes.h"

// The settings: game types, team mask, teams, the "any group" flag and the
// group, as cNetTriggerViewControl's commands 0 to 4 give them.
struct sNetTriggerVisibility
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
    RwUInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
};
// The one message's data (unk_4FD6D4); the behaviours' attribute commands
// also pass it to their empty sub_15FB30.
extern sNetTriggerVisibility unk_4FD6D4;

#endif
