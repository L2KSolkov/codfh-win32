/*
 * The music players (unit_0863C0): three streams, dword_44E8D8, each with
 * its file, request, state and volumes, and a 128 KB buffer the audio
 * library streams through.
 */
#ifndef TYPES_MUSICPLAYER_H
#define TYPES_MUSICPLAYER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"

struct type_44E8AC;
struct type_44E8B0;

// A music stream's header as sub_192870 reads it (0x24 bytes), and each of
// its records (0x1C bytes: a chunk header, a typed reference and a value).
struct type_44E8D8_248_hdr
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;             // the records' count
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwInt32 unk_20;
};
struct type_44E8D8_248_rec
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;             // its size, with this record
    type_3DF8D8_ref unk_0C;
    RwInt32 unk_18;
};

// What a player streams: the kind-0x2A GodAsset (a music stream), anchored at
// its vtable off_3DFB58, which its constructor sub_192B20 installs; its key
// (unk_04) is its sound alias's (sub_860E0 primes it). Its handler
// (sub_192580) registers its settings as variables; sub_192870 reads its
// header; vf_00C (sub_192BE0) plays it on player unk_20.
struct type_44E8D8_248 : type_3DFB6C
{
    RwInt32 unk_10;             // a master stream: never ducks
    RwInt32 unk_14;             // the duck's depth, in percent
    RwInt32 unk_18;             // its volume, in percent (StreamTrigger's
                                // sub_BB1F0)
    RwInt32 unk_1C;
    RwInt32 unk_20;             // its number
    RwInt32 unk_24;             // its track
    RwInt32 unk_28;
    RwInt32 unk_2C;

    type_44E8D8_248(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual RwInt32 vf_008();
    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14);
    virtual bool vf_010(RwInt32 arg_0);

    void sub_192870(RwStream *arg_0, RwInt32 arg_4);
};
// The music streams' file names: the platform prefix ("XBX_") and the
// streams' names by the sound table's entry (sub_192BE0).
extern const RwChar *dword_42B690;
extern const RwChar *off_42B698[];

// A music player (0x2025C bytes; sub_863E0 sets one up with the listener
// and the output): an "AudioStream" in its debug strings, which ducks
// (sub_86890, arg_0 how far, -1 for its own depth) and unducks (sub_86C40,
// arg_0 the rate, -1 for dword_44D4CC).
struct type_44E8D8
{
    type_44E8D8();
    ~type_44E8D8();
    // Empty: folded (/OPT:ICF) into pDtor (0x1E41C0), which sub_857B0 calls
    // on each player.
    void pDtor();
    void sub_863E0(type_44E8AC *arg_0, type_44E8B0 *arg_4);
    // Resets it (sub_86470), shuts it down (sub_866C0), stops it and waits
    // (sub_867A0), and asks it to stop (sub_86750, sub_86710).
    void sub_86470();
    void sub_866C0();
    void sub_86710();
    void sub_86750();
    void sub_867A0();
    // Whether it is idle (state 1, or no stream).
    bool sub_86830();
    void sub_86860(RwInt32 arg_0);
    void sub_86890(RwReal arg_0);
    void sub_86C40(RwReal arg_0);
    // Fades the channel arg_0's volume a step towards its target.
    void sub_86D70(RwInt32 arg_0);
    // Whether its track may play (stop streams, blacklisted tracks and
    // silenced numbers go inactive), and starts it.
    bool sub_870B0();
    // Its update: follows the stream's states and moves its own on.
    RwInt32 sub_886D0();
    void sub_87250();
    void sub_873B0();
    RwUInt8 unk_00;             // set up
    RwChar unk_01[0x100];       // the file it plays
    RwUInt8 unk_101[0x3];
    void *unk_104;              // its stream's handle
    RwInt32 unk_108;            // its request (2 pending, 4, 6, 9)
    RwInt32 unk_10C;            // its reader's state
    RwInt32 unk_110;            // its mixer's state
    RwUInt8 unk_114[0x40];
    RwChar unk_154[0x8];        // its track as four digits
    RwChar *unk_15C;            // the stream's parameters from here: its file
    RwInt32 unk_160;
    RwInt32 unk_164;
    RwInt32 unk_168;
    RwInt32 unk_16C;
    RwInt32 unk_170;
    RwInt32 unk_174;
    RwInt32 unk_178;
    RwInt32 unk_17C;
    RwInt32 unk_180;            // its state (1 idle, 2, 5, 6, 7, 9 to 19; the script
                                // commands' 0x44EA58 + n * 0x2025C:
                                // "StartPrimedAudioStream" sets 0xC)
    RwInt32 unk_184;
    RwInt32 unk_188;            // ducked
    RwInt32 unk_18C;            // unducking
    RwReal unk_190[8];          // its channels' volumes
    RwReal unk_1B0[8];          // their volumes now (fading to unk_190)
    RwReal unk_1D0[8];          // their fade rates
    RwReal unk_1F0[8];          // the volumes before the duck
    RwReal unk_210[8];          // the rates before the duck
    RwInt32 unk_230;
    RwUInt32 unk_234;           // its channels
    RwInt32 unk_238[3];         // their kinds (1 mono, 2 stereo)
    RwInt32 unk_244;
    type_44E8D8_248 *unk_248;   // its stream
    RwInt32 unk_24C;
    RwInt32 unk_250;
    type_44E8AC *unk_254;       // the listener
    type_44E8B0 *unk_258;       // the output
    RwUInt8 unk_25C[0x20000];   // not an address: its 128 KB stream buffer
};
extern type_44E8D8 dword_44E8D8[3];

// The audio library calls the players make: [RwaStreamCreate_0] makes the
// stream (its callback sub_88640 fills the buffer arg_10), sub_23FFD0 is
// only known by width, [DSPHandle_Stop] stops a handle.
extern "C" void *RwaStreamCreate_0(type_44E8B0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, void *arg_C, void *arg_10);
// The stream's callbacks: sub_88640 fills its table (sub_88670 for the
// buffer, the empty debug print for the rest) and sub_88670 hands the
// buffer arg_4 to the reader it recognises by its class id.
struct type_88640
{
    void *unk_00;
    void *unk_04;
    void *unk_08;
};
struct type_88670_8
{
    RwUInt8 unk_00[0x44];
    RwInt32 unk_44;
    void *unk_48;
};
struct type_88670_0
{
    const RwUInt32 *unk_00;     // its class id
};
RwInt32 sub_88640(void *arg_0, void *arg_4, type_88640 *arg_8);
RwInt32 sub_88670(type_88670_0 *arg_0, void *arg_4, type_88670_8 *arg_8);
// [RwaUUIDCompare]: 0 when the class ids arg_0 and arg_4 are the same.
extern "C" RwInt32 RwaUUIDCompare(const RwUInt32 *arg_0, const RwUInt32 *arg_4);
extern "C" const RwUInt32 unk_3ED29C[4];
extern "C" const RwUInt32 unk_3EDF6C[4];
void sub_885B0(RwInt32 arg_0);
// [RwaStreamCreate] (0x23B750): a voice.
extern "C" void *RwaStreamCreate(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
extern RwInt32 dword_4B2070;
void sub_82350();
void sub_82360();
void sub_19A750(void *arg_0);
extern "C" void sub_23FFD0(void *arg_0, RwInt32 arg_4);
extern "C" void DSPHandle_Stop(void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
extern RwInt32 dword_4B2068;
extern RwInt32 dword_44E860;
extern RwInt32 dword_44E864;
extern RwInt32 dword_44D4D8;
extern RwInt32 dword_44D4CC;
extern RwInt32 dword_44E868;
extern RwInt32 dword_44E5F0[];
extern RwInt32 dword_428E74;
extern RwInt32 dword_428E78;
extern RwChar byte_4B1F68[];
extern RwInt32 dword_44E8A0;
extern RwInt32 dword_44E898;
extern RwReal flt_428E30;
extern RwReal flt_44E808;
// The stream's track list as sub_87250 hands it to the library.
struct type_87250_e
{
    RwChar *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};
struct type_87250
{
    type_87250_e *unk_00;
    RwInt32 unk_04;
};
extern "C" void sub_240010(void *arg_0, RwChar **arg_4);
extern "C" void sub_23FE30(void *arg_0, type_87250 *arg_4);
// The library's stream queries and commands the update makes.
struct type_873B0_a
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwUInt32 unk_10;            // the channels
};
struct type_873B0_b
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt32 unk_08;            // the channel
    RwInt32 unk_0C;             // its kind
};
struct type_873B0_c
{
    RwUInt32 unk_00;            // the channel
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwReal unk_0C;              // its volume
};
extern "C" RwInt32 sub_240120(void *arg_0);
extern "C" RwInt32 sub_240130(void *arg_0);
extern "C" RwInt32 sub_240140(void *arg_0);
extern "C" void sub_2400E0(void *arg_0, RwInt32 arg_4);
extern "C" void sub_240240(void *arg_0, type_873B0_a *arg_4);
extern "C" void sub_240370(void *arg_0, type_873B0_b *arg_4);
extern "C" void sub_240150(void *arg_0, type_873B0_c *arg_4);
extern RwInt32 dword_4B206C;
extern RwInt32 dword_44E8C0;
extern RwInt32 dword_44E8D4;
extern RwInt32 dword_44BAD0;
extern RwInt32 dword_44D4B4;
#ifdef CODFH_PLAIN
extern RwUInt32 &dword_4B9194;
#else
extern RwUInt32 dword_4B9194;
#endif
extern "C" void sub_2401B0(void *arg_0, RwReal arg_4);
void sub_86350();
extern "C" RwBool RtFSManagerSyncAllFiles(void);

#endif
