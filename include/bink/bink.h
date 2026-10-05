/*
 * The RAD Game Tools Bink functions the movie player calls (the image's BINK
 * section), declared as Bink's API names them. None of Bink's headers is at
 * hand: each name is taken from its use (the player's open, step, pause,
 * volume and error text), and the stdcall widths are the image's.
 * config/aliases.txt places them.
 */
#ifndef BINK_BINK_H
#define BINK_BINK_H

#include "rw/ostypes.h"

// A playing movie; only the fields the player reads are known.
typedef struct BINK
{
    RwUInt32 Width;
    RwUInt32 Height;
    RwUInt32 Frames;            // how many
    RwUInt32 FrameNum;          // the current one
    RwUInt8 unk_10[0xE0];
    RwInt32 NumTracks;          // its sound tracks
} BINK, *HBINK;

#define BINKSNDTRACK 0x4000

#ifdef __cplusplus
extern "C"
{
#endif

HBINK __stdcall BinkOpen(const RwChar *name, RwUInt32 flags);
void __stdcall BinkClose(HBINK bink);
const RwChar *__stdcall BinkGetError(void);
void __stdcall BinkSetSoundTrack(RwUInt32 total, RwUInt32 *tracks);
RwUInt32 __stdcall BinkGetTrackID(HBINK bink, RwUInt32 trackindex);
void __stdcall BinkSetVolume(HBINK bink, RwUInt32 trackid, RwInt32 volume);
RwInt32 __stdcall BinkWait(HBINK bink);
RwInt32 __stdcall BinkDoFrame(HBINK bink);
void __stdcall BinkNextFrame(HBINK bink);
RwInt32 __stdcall BinkPause(HBINK bink, RwInt32 pause);
RwInt32 __stdcall BinkCopyToBuffer(HBINK bink, void *dest, RwInt32 destpitch, RwUInt32 destheight,
                                   RwUInt32 destx, RwUInt32 desty, RwUInt32 flags);

#ifdef __cplusplus
}
#endif

#endif
