/*
 * The sound banks (unit_0824A0): loading them from their files and the
 * table of sound ids read at start-up.
 */
#ifndef TYPES_SOUNDBANK_H
#define TYPES_SOUNDBANK_H

#include "rw/ostypes.h"
#include "rws/gftime.h"
#include "rw/bastream.h"
#include "rw/batypes.h"
#include "types/alfasched.h"
#include "game/data.h"
#include "types/musicplayer.h"

// A sound's id (two words, zeroed when made).
struct type_825E0_id
{
    RwInt32 unk_00;
    RwInt32 unk_04;

    type_825E0_id()
    {
        unk_00 = 0;
        unk_04 = 0;
    }
};

// A sound bank as asked for (16 bytes): its id, its slot in dword_4B1A20
// and the language-independent part of its file name (unk_0C).
struct type_825E0
{
    type_825E0_id unk_00;
    RwInt32 unk_08;
    RwInt16 unk_0C;
};

// A request being loaded (0x218 bytes; sub_84230 clears it): the bank, its file's two
// names (sub_858E0 builds them) and two words.
struct type_84230
{
    type_825E0 unk_00;
    RwChar unk_10[0x100];
    RwChar unk_110[0x100];
    RwInt32 unk_210;
    RwInt32 unk_214;
};

// A sound's source (12 bytes): a bank's id and the sound's index in it.
struct type_840D0
{
    type_825E0_id unk_00;
    RwInt32 unk_08;
};

// A sound (sub_199010 makes one): what the bank's records set, and its
// name in the current language (unk_28, from sub_1986B0's pool).
struct type_199010
{
    virtual void vf_00();
    virtual void vf_04();
    virtual RwInt32 vf_08();    // its kind (0x13: streamed)
    virtual void vf_0C();
    virtual void vf_10();
    // Adds it to the bank arg_0 (its type_825E0) with the record's arg_4.
    virtual void vf_14(type_825E0 *arg_0, RwInt32 arg_4);
    type_825E0_id unk_04;       // its id
    RwUInt8 unk_0C[0x4];
    RwUInt8 unk_10;
    RwUInt8 unk_11;
    RwUInt8 unk_12;
    RwUInt8 unk_13;
    RwUInt8 unk_14;
    RwUInt8 unk_15;
    RwUInt8 unk_16;
    RwUInt8 unk_17;
    RwUInt8 unk_18;
    RwUInt8 unk_19;
    RwInt8 unk_1A;              // the banks holding it
    RwUInt8 unk_1B;
    RwUInt16 unk_1C;            // its pitch
    RwInt16 unk_1E;
    RwUInt16 unk_20;            // its pitch's spread
    RwUInt16 unk_22;
    RwUInt16 unk_24;            // library parameters 2 and 3, in hundredths
    RwUInt16 unk_26;
    RwChar *unk_28;
    type_840D0 unk_2C[2];       // the banks it can play from
};

// The basic sound GodAsset (kind 0x2B, the object type_199010 views),
// anchored at its vtable off_3DFC34, which its constructor sub_192E60
// installs after type_3DFB6C's: its settings, its name (unk_28) and the
// two banks it can play from. vf_004 (sub_193140) frees its name, vf_00C
// (sub_193170) plays it through an emitter and makes it heard, vf_014
// (sub_192F30) adds it to a bank.
struct type_3DFC34 : type_3DFB6C
{
    RwUInt8 unk_10;
    RwUInt8 unk_11;
    RwUInt8 unk_12;
    RwUInt8 unk_13;
    RwUInt8 unk_14;
    RwUInt8 unk_15;             // its volume, in percent (0.6 of it while a
                                // bank request holds it)
    RwUInt8 unk_16;             // its voice list
    RwUInt8 unk_17;             // it is heard (AIHearing)
    RwUInt8 unk_18;             // heard at once (else a lasting sound)
    RwUInt8 unk_19;
    RwInt8 unk_1A;
    RwUInt8 unk_1B;             // a bank request holds it
    RwUInt16 unk_1C;
    RwUInt16 unk_1E;            // how far it is heard, in hundredths
    RwUInt16 unk_20;
    RwUInt16 unk_22;
    RwUInt16 unk_24;
    RwUInt16 unk_26;
    RwChar *unk_28;             // its name
    type_840D0 unk_2C[2];       // the banks it can play from

    type_3DFC34(const type_3DF8D8_04 &arg_0);

    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14);
    virtual bool vf_010(RwInt32 arg_0);
    virtual void vf_014(type_825E0 *arg_0, RwInt32 arg_4);
};
// Frees a sound's name (sub_1986B0's pool).
void sub_1986D0(RwChar *arg_0);
// The emit functions (unit_03C1D0): a sound heard at once, or a lasting one.
void sub_3C4B0(struct type_3D3548 *arg_0, RwInt32 arg_4, RwV3d *arg_8, RwInt32 arg_C, RwReal arg_10,
               RwInt32 arg_14, RwReal arg_18);
void sub_3C540(struct type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10,
               RwReal arg_14, RwInt32 arg_18, RwReal arg_1C);

// The random sound GodAsset (kind 0x2C?), anchored at its vtable off_3DFCA0,
// which its constructor sub_1932D0 installs after type_3DFB6C's: its sounds'
// keys (unk_10), their weights (unk_14) and their count; vf_00C (sub_193330)
// plays one of the loaded ones at random, by weight.
struct type_3DFCA0 : type_3DFB6C
{
    type_3DF8D8_04 *unk_10;
    RwInt32 *unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;

    type_3DFCA0(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14);
    virtual bool vf_010(RwInt32 arg_0);

    // Reads its sounds' keys and weights (the section loader, sub_143540).
    void sub_193A00(RwStream *arg_0, RwInt32 arg_4);
};
// The list GodAsset (kind 0x20), anchored at its vtable off_3DFDFC, which its
// constructor sub_193DB0 installs: a count and a buffer of references that
// the random sound's callback (sub_193E20) takes over.
struct type_3DFDFC : type_3DF8D8_base
{
    RwInt32 unk_10;
    type_3DF8D8_ref *unk_14;

    type_3DFDFC(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
// The random sound's list callback: takes the list arg_0's references for
// the sound arg_4 and registers each (kind 0x23) with sub_194320 filling
// its key and weight.
RwInt32 sub_193E20(type_3DFDFC *arg_0, type_3DFCA0 *arg_4, void *arg_8);
// A sound reference's callback: its sound's key and weight into *arg_4 and
// *arg_8.
RwInt32 sub_194320(type_3DFE20 *arg_0, type_3DF8D8_04 *arg_4, RwInt32 *arg_8);
// The sequence sound GodAsset (kind 0x1C), laid out as the random sound,
// anchored at its vtable off_3DFD40, which its constructor sub_193640
// installs after type_3DFB6C's; its list comes through sub_1940E0.
struct type_3DFD40 : type_3DFB6C
{
    type_3DF8D8_04 *unk_10;
    RwInt32 *unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;

    type_3DFD40(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14);
    virtual bool vf_010(RwInt32 arg_0);
};
RwInt32 sub_1940E0(type_3DFDFC *arg_0, type_3DFD40 *arg_4, void *arg_8);
// A kind-0x19 object as the sequence sound's vf_00C (sub_1936B0) views one:
// a slot playing one with a nonzero +0x28 is not taken from ("a sequence
// alias slot that has no subtitle", by its warning).
struct type_3DF8D8_19 : type_3DF8D8
{
    RwUInt8 unk_20[0x8];
    RwInt32 unk_28;             // its subtitle
};
// The index sound GodAsset (kind 0x1D), laid out as the random sound,
// anchored at its vtable off_3DFDE4, which its constructor sub_193AB0
// installs after type_3DFB6C's; it only plays by index (vf_014,
// sub_193B30, "EfuncPlayIndexSound"), its list coming through sub_193FB0.
struct type_3DFDE4 : type_3DFB6C
{
    type_3DF8D8_04 *unk_10;
    RwInt32 *unk_14;            // its sounds' indices
    RwInt32 unk_18;
    RwInt32 unk_1C;

    type_3DFDE4(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14);
    virtual bool vf_010(RwInt32 arg_0);
    virtual RwInt32 vf_014(struct type_8A980 *arg_0, RwInt32 arg_4, struct type_3D3548 *arg_8, RwInt32 arg_C,
                           RwV3d *arg_10, RwInt32 arg_14, RwInt32 arg_18);
};
RwInt32 sub_193FB0(type_3DFDFC *arg_0, type_3DFDE4 *arg_4, void *arg_8);
// The other list kinds, laid out as type_3DFDFC and sharing its functions
// (/OPT:ICF): 0x22 (off_3DFE08), 0x21 (off_3DFE14, whose handler reads the
// size at +4) and 0x1F (off_3DFE64).
struct type_3DFE08 : type_3DF8D8_base
{
    RwInt32 unk_10;
    type_3DF8D8_ref *unk_14;

    type_3DFE08(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
struct type_3DFE14 : type_3DF8D8_base
{
    RwInt32 unk_10;
    type_3DF8D8_ref *unk_14;

    type_3DFE14(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
struct type_3DFE64 : type_3DF8D8_base
{
    RwInt32 unk_10;
    type_3DF8D8_ref *unk_14;

    type_3DFE64(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
};
// The uniform random sound GodAsset (kind 0x1E), anchored at its vtable
// off_3DFE50, which its constructor sub_194550 installs after
// type_3DFB6C's: its sounds' keys (unk_10), their count and the list's
// references; vf_00C (sub_1945B0) plays one of the loaded ones at random.
struct type_3DFE50 : type_3DFB6C
{
    type_3DF8D8_04 *unk_10;
    RwInt32 unk_14;
    type_3DF8D8_ref *unk_18;

    type_3DFE50(const type_3DF8D8_04 &arg_0);

    virtual RwInt32 vf_000(RwStream *arg_0, type_3DF8D8_ev *arg_4);
    virtual void vf_004();
    virtual RwInt32 vf_008();
    virtual RwInt32 vf_00C(struct type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
                           RwInt32 arg_10, RwInt32 arg_14);
    virtual bool vf_010(RwInt32 arg_0);

    // Reads its sounds' keys (the section loader).
    void sub_1947F0(RwStream *arg_0, RwInt32 arg_4);
};
RwInt32 sub_194900(type_3DFE64 *arg_0, type_3DFE50 *arg_4, void *arg_8);

// A debug switch (types/CGlobalSounds.h): a missing index sound plays a
// warning sound instead.
extern RwInt32 dword_44E83C;

// A bank's list of its sounds (16 bytes, from operator new with a memory
// type).
struct type_825E0_node
{
    type_825E0_node *unk_00;
    type_825E0_id unk_04;
    type_199010 *unk_0C;

    type_825E0_node()
    {
        unk_00 = 0;
        unk_0C = 0;
    }
    // Releases its sound (sub_198F00 frees it when no bank holds it).
    ~type_825E0_node();
};

// A sound bank's slot (0x28 bytes): its sounds and the bank loaded there.
struct type_4B1A20
{
    RwInt32 unk_00;             // set while a bank is loaded there
    RwUInt8 unk_04[0xC];
    RwInt32 unk_10;
    type_825E0_node *unk_14;
    type_825E0 unk_18;
};
extern type_4B1A20 dword_4B1A20[6];

// A sound as a bank file stores it (0xF4C bytes): its id, its settings (one
// word each) and its name in each of fifteen languages.
struct type_825E0_rec
{
    RwInt32 unk_00;             // its id
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwInt32 unk_20;
    RwInt32 unk_24;
    RwInt32 unk_28;
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;
    RwInt32 unk_38;
    RwInt32 unk_3C;
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;
    RwChar unk_4C[15][0x100];
};

// The sound engine's wave bank (sub_23C490 loads one from a file; 0x100 at
// +0x2C when it holds a bank).
struct type_44C0A8
{
    RwInt32 unk_00;
    RwUInt8 unk_04[0x28];
    RwInt32 unk_2C;
};
extern type_44C0A8 *dword_44C0A8;
extern "C" type_44C0A8 *sub_23C490(void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, type_44C0A8 *arg_10);
// sub_23BFE0 waits for the wave bank arg_0; sub_24DB40 is the sound
// memory free, dword_44D48C its last value and dword_44E768 what the banks
// have taken. dword_44E8D4 is set while a bank loads synchronously,
// dword_44E870 turns on the loading messages.
extern "C" void sub_23BFE0(type_44C0A8 *arg_0);
extern "C" RwUInt32 sub_24DB40();
extern RwUInt32 dword_44D48C;
extern RwUInt32 dword_44E768;
extern RwInt32 dword_44E8D4;
extern RwInt32 dword_44E870;
// The pending sound bank requests (the loading thread hands over the first).
extern type_84230 dword_4AF038[0x14];
// RenderWare's file functions (RWSDK osintf.h; the image calls them
// directly).
extern "C" void *RwFopen(const RwChar *name, const RwChar *access);
extern "C" RwInt32 RwFclose(void *fptr);
void sub_19BB40(const RwChar *arg_0, RwInt32 arg_4);
// "LoadSoundBankSynchronously": loads the bank arg_0 (marking its files
// busy, from the loading thread, when arg_4).
void sub_82C70(type_825E0 *arg_0, bool arg_4);

// The sound system's set-up and shut-down (sub_82F50, sub_83100, sub_83170,
// sub_831D0) and the audio library calls they make. The database names
// several of these (in brackets); they are its guesses, so the functions
// keep address names.
struct type_44E8B0
{
    RwUInt8 unk_00[0x6C];
    void *unk_6C;               // the DirectSound object
    RwUInt8 unk_70[0x18];
    void *unk_88;               // the effects image

    // Inline accessors with no address and so no database names, named for
    // their fields. Evidence: the multiplayer manager's set-up (sub_1A9580)
    // reads each through a slot of its own before the voice manager's.
    void *get_unk_6C()
    {
        void *r = unk_6C;
        return r;
    }
    void *get_unk_88()
    {
        void *r = unk_88;
        return r;
    }
};
extern type_44E8B0 *dword_44E8B0;   // the output stream
// A stream's creation parameters (0x3C bytes; RwaObjDefGetDefaultCreationParams fills in the
// defaults, sub_82F50 sets +0x14).
struct type_82F50
{
    RwInt32 unk_00[5];
    RwInt32 unk_14;
    RwInt32 unk_18[9];
};
// The listener: its position and its dirty flags.
struct type_44E8AC
{
    RwUInt8 unk_00[0x28];
    RwV3d unk_28;               // its position (flag 1)
    RwUInt8 unk_34[0xC];
    RwV3d unk_40;               // its orientation (flag 4): up, at and
    RwV3d unk_4C;               // their cross product (the second network
    RwV3d unk_58;               // player's step, sub_1BAE40)
    RwUInt8 unk_64[0xC];
    RwUInt32 unk_70;
};
extern type_44E8AC *dword_44E8AC;   // the listener
extern void *dword_44E770[0x24];    // the voice streams
extern "C" const RwUInt32 unk_3EDF5C[4];  // the output's class id
extern RwInt32 dword_44D4C4;
extern RwInt32 dword_44E5EC;
extern RwInt32 dword_44E804;
extern RwInt32 dword_44D4AC;
extern RwInt32 dword_44D4A8;
extern void *dword_44E590;
extern "C" void *dword_506830;
extern "C" RwInt32 dword_42E484;
// RWA's listener object definition (unit_23CC10's table): its slot 54 (0x42E620)
// takes the audio set-up's result.
extern "C" void *unk_42E548[56];
extern void *dword_44E8C8;
RwInt32 sub_82F50();
RwInt32 sub_83100();
RwInt32 sub_83170();
void sub_831D0();
extern "C" void *sub_23DCA0(RwInt32 arg_0, const RwUInt32 *arg_4, RwInt32 arg_8);
// [RwaObjDefGetDefaultCreationParams]
extern "C" void RwaObjDefGetDefaultCreationParams(void *arg_0, void *arg_4);
RwInt32 sub_19CDE0(const RwChar *arg_0);
// [RwaStreamCreate_1], [RwaStreamCreate_2]
extern "C" type_44E8B0 *RwaStreamCreate_1(RwInt32 arg_0, void *arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
extern "C" void *RwaStreamCreate_2(type_44E8B0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
// [IDirectSound_SetMixBinHeadroom], the XDK's (dsound.h: __stdcall).
#ifndef __DSOUND_INCLUDED__
extern "C" RwInt32 __stdcall IDirectSound_SetMixBinHeadroom(void *pDirectSound, RwUInt32 dwMixBin,
                                                            RwUInt32 dwHeadroom);
#endif
// [nullsub_1]: the output's setting the game turns on after creating it, an
// empty C function of RenderWare Audio's Xbox layer in this build (defined
// in src/rwa/xbox/unit_24DF20.c; /OPT:ICF folds its bare ret into 0x22C6E0).
extern "C" void sub_22C6E0(type_44E8B0 *arg_0, RwInt32 arg_4);
// [RwaListenerCreate]
extern "C" type_44E8AC *RwaListenerCreate(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
extern "C" void sub_24E180(type_44E8B0 *arg_0, type_44E8AC *arg_4);
// [BinkAudioStartup], [BinkAudioOpenDrivers], [BinkAudioOpenDrivers_0]
extern "C" RwInt32 RwaCoreOpen(RwInt32 arg_0, RwInt32 arg_4);
extern "C" RwInt32 sub_23E3A0();
extern "C" void sub_23E3E0();
extern "C" RwInt32 sub_24EC10();
extern "C" RwInt32 sub_23E690(type_44E8B0 *arg_0, void **arg_4, RwInt32 arg_8);
extern "C" void sub_23C020(type_44C0A8 *arg_0);
// [DSPResourceMgr_Shutdown], [DSPHandle_Stop]
extern "C" void DSPResourceMgr_Shutdown();
extern "C" void DSPHandle_Stop(void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
extern "C" void sub_24EBD0();
extern "C" void RwaCoreClose();
RwInt32 sub_31DB0();
// RenderWare Studio's RWSMalloc (the database's AllocBuffer): allocates
// size bytes; hint is a RenderWare memory hint (rws/memoryhandler.h).
void *RWSMalloc(RwUInt32 size, RwUInt32 hint);

// The sound system's state sub_83280 resets.
// A list of sounds (16 bytes a link; deleting one deletes the rest).
struct type_837D0
{
    RwReal unk_00;              // its delay, in tenths
    type_825E0_id unk_04;       // the sound
    type_837D0 *unk_0C;

    // Defined in the class: VC7.1 does not inline it (it deletes), but a
    // caller still reserves the 8 bytes of temporaries an expansion would
    // have taken (sub_83760, sub_85730).
    ~type_837D0()
    {
        if (unk_0C)
        {
            delete unk_0C;
        }
        unk_0C = 0;
        unk_00 = 0;
        unk_04.unk_00 = 0;
        unk_04.unk_04 = 0;
    }
};
struct type_4B1CA0
{
    // Deletes its list; sub_85730 its first link.
    void sub_83760()
    {
        if (unk_04)
        {
            delete unk_04;
        }
        unk_04 = 0;
    }
    void sub_85730()
    {
        type_837D0 *var_4;

        if (!unk_04)
        {
            return;
        }
        var_4 = unk_04->unk_0C;
        unk_04->unk_0C = 0;
        delete unk_04;
        unk_04 = var_4;
    }
    type_4B1CA0();
    ~type_4B1CA0();
    // Adds the sound arg_0 after the delay arg_4, keeping the list in order.
    void sub_85A00(type_825E0_id *arg_0, RwReal arg_4);
    RwReal unk_00;              // its timer
    type_837D0 *unk_04;         // the sounds to play
    RwV3d unk_08;               // where
    type_8A980 *unk_14;         // through which emitter
};
extern type_4B1CA0 dword_4B1CA0[0x14];
struct type_4B1C20
{
    RwInt32 unk_00;
    RwInt32 unk_04;

    type_4B1C20()
    {
        unk_00 = 0;
        unk_04 = 0;
    }
};
extern type_4B1C20 dword_4B1C20[3];
extern RwInt32 dword_44C4E8[0x3E8];
extern RwInt32 dword_44D4E0[0x3E8];
// The three music players: include/types/musicplayer.h.
// Ten bank requests (sub_83C60 clears one).
extern type_825E0 dword_4B1B60[10];
void sub_83C60(type_825E0 *arg_0);
RwInt32 sub_19B0A0();
extern RwReal flt_428E28;         // how often the bank queue moves on
extern RwReal flt_4AEFF4;         // the time until it does
extern RwInt32 dword_428E2C;
extern RwInt32 dword_44E8B4;
extern RwInt32 dword_44E8B8;
extern RwInt32 dword_44E8C0;
extern RwInt32 dword_44E8A8;
#ifdef CODFH_PLAIN
// (plain builds: the first byte of the 0x100-byte buffer, 0x44E490 to
// 0x44E590, a sound's subtitle line is copied into (unit_192BE0); see
// unit_0824A0)
extern RwUInt8 &byte_44E490;
#else
extern RwUInt8 byte_44E490;
#endif
extern RwInt32 dword_44D4C0;
extern RwInt32 dword_44D4C8;
extern RwInt32 dword_44D4DC;
extern RwInt32 dword_44D49C;
extern RwInt32 dword_44E834;
RwInt32 sub_83280();
// "UnloadBank": empties the slot arg_0 (1 when done or already empty).
RwInt32 sub_84090(type_825E0_id *arg_0, type_825E0_id *arg_4);
RwInt32 sub_840D0(type_199010 *arg_0);
void sub_84170(RwInt32 arg_0, RwInt32 arg_4);
void sub_841C0();
void sub_84280();
void sub_84300(type_825E0 *arg_0);
// "LoadSoundBankAsynchronously": moves the first bank request on a step
// (dword_4AF24C: 0 to 3 while it loads, 7 when the loading thread is done).
void sub_843F0();
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4AF24C;
#else
extern RwInt32 dword_4AF24C;
#endif
extern RwInt32 dword_44E8CC;
extern RwInt32 dword_44E8D0;
extern RwUInt32 dword_4B86F8;
extern RwInt32 dword_44D4A4;
extern RwInt32 dword_44D4B4;
extern RwInt32 dword_4F30A4;
void sub_16D7F0(RwInt32 arg_0);
void sub_16D850(RwInt32 arg_0);
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
struct type_42E00_10;
struct type_67620;
struct type_3D2E7C;
void sub_6B5F0(const RwChar *arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C, RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C);
// The sound engine calls UnloadBank makes: RwaWaveDictContainsWave is whether the
// wave bank arg_0 holds the wave arg_4; [SoundEmitter_Stop] and
// sub_23B8F0 stop and release an emitter; sub_23C700 and RwaWaveDictDestroy free
// a wave bank; sub_198F00 frees the sound with the id arg_0; RwaWaveDictFindWaveByIndex
// the wave arg_4 of the wave bank arg_0.
struct type_44C4E8
{
    RwUInt8 unk_00[0x30];
    void *unk_30;               // its handle in the audio library
    RwUInt32 unk_34;            // 2: playing
    RwUInt8 unk_38[0x4];
    RwReal unk_3C;              // its pitch
    RwReal unk_40;              // its volume
    RwUInt8 unk_44[0x4];
    RwInt32 unk_48;             // library parameter 7, kept over a pause
    RwUInt8 unk_4C[0x4];
    void *unk_50;               // its wave
    RwUInt8 unk_54[0x4];
    RwV3d unk_58;               // its position
    RwUInt8 unk_64[0xC];
    RwReal unk_70;              // library parameters 2 and 3 (sub_8A440)
    RwReal unk_74;
};
// RenderWare Audio's RwaObjHandleSetParamUInt8 (0x23F910, src/rwa/rwaobject.c;
// the database's sub_23F910): sets the parameter arg_4 of the object arg_0 (5:
// the volume). Variadic in RenderWare Audio, but the game passes the value as
// one 32-bit word (the image pushes a float as a float, never a double), so
// it calls it through a fixed prototype per value type: the same direct call.
// sub_8A440 passes a sound's byte for parameter 8 as a whole value.
extern "C" void *RwaObjHandleSetParamUInt8(void *handle, RwUInt32 index, RwInt32 type, ...);
#define RWA_SET_PARAM_REAL(arg_0, arg_4, arg_8, arg_C)     ((void (*)(void *, RwInt32, RwInt32, RwReal))RwaObjHandleSetParamUInt8)(arg_0, arg_4, arg_8, arg_C)
#define RWA_SET_PARAM_INT(arg_0, arg_4, arg_8, arg_C)     ((void (*)(void *, RwInt32, RwInt32, RwInt32))RwaObjHandleSetParamUInt8)(arg_0, arg_4, arg_8, arg_C)
// The music's volumes (dword_44E88C, flt_44E890) and the two voices kept
// out of the effects volume.
extern RwReal flt_44E88C;
extern RwReal flt_44E890;
void sub_84610();
// The trace of the virtual voice calls ("<<[%d]---==$$##: %s", when
// dword_44E888 is set; dword_4B87D8 is the frame): the voices are
// "sm_VirtualVoiceMasterList" (dword_44C4E8) in the traced text.
void sub_84C40(const RwChar *arg_0);
extern RwInt32 dword_44E888;
void sub_848A0();
void sub_84C70(RwReal arg_0);
void sub_84DB0();
extern RwReal flt_44D488;
extern RwReal flt_44E808;
extern RwReal flt_44D4A0;
void sub_84EF0(RwReal arg_0);
// The sound system's update, arg_0 the frame's time (the game loop's tick,
// sub_D7880, passes 1 for arg_4, which it does not use).
void sub_85090(RwReal arg_0, RwInt32 arg_4);
// Whether no music player is starting (sub_85B90), all are settled
// (sub_85C10), any is busy (sub_85CC0); the first two keep their answers in
// dword_4B1F5C and dword_4B1F60.
RwInt32 sub_85B90();
RwInt32 sub_85C10();
RwInt32 sub_85CC0();
// Whether any music player has a request other than 9.
RwInt32 sub_86090();
extern "C" void RwaCoreUpdate();
extern RwInt32 dword_4B1F5C;
extern RwInt32 dword_4B1F60;
// A sound alias as sub_198800 finds it by its key (sub_8A980 and sub_8AA70
// look one up): it plays through the emitter arg_0 for the entity arg_4
// (vf_0C), or plays its entry arg_4 (vf_14, "EfuncPlayIndexSound"),
// returning the voice (0 or -1 for none).
struct type_8A980_alias
{
    virtual void vf_00();
    virtual void vf_04();
    virtual RwInt32 vf_08();
    virtual RwInt32 vf_0C(type_8A980 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8,
                          RwV3d *arg_C, RwInt32 arg_10, RwInt32 arg_14);
    virtual void vf_10();
    virtual RwInt32 vf_14(type_8A980 *arg_0, RwInt32 arg_4, struct type_3D3548 *arg_8,
                          RwInt32 arg_C, RwV3d *arg_10, RwInt32 arg_14, RwInt32 arg_18);
};
// The lists' switches ("... sound disabled in GlobalSounds!"): dialog,
// foley, weapons fire, vehicles, weapons foley, debris, ambience 1 and 2.
extern RwInt32 dword_44E840;
extern RwInt32 dword_44E844;
extern RwInt32 dword_44E848;
extern RwInt32 dword_44E84C;
extern RwInt32 dword_44E850;
extern RwInt32 dword_44E854;
extern RwInt32 dword_44E858;
extern RwInt32 dword_44E85C;
// Stops the voice *arg_0 if it plays, else forgets it.
void sub_85800(type_44C4E8 **arg_0);
// [Behavior_DispatchCallback] (0x23F8B0)
extern "C" void Behavior_DispatchCallback(void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C);
extern RwReal flt_429288;
extern RwReal flt_44E810;
extern RwReal flt_44C0A0;
extern RwReal flt_44E800;
extern RwReal flt_44D4B8;
extern RwReal flt_44E80C;
extern RwReal flt_44C0A4;
extern RwReal flt_44E828;
extern RwReal flt_44D4B0;
extern struct type_3D3548 *dword_4B1F58;
extern RwInt32 dword_4B1F54;
extern RwInt32 dword_44BAD0;          // a stream is open (the loading queue)
extern type_3DF8D8_04 dword_4B1C08;
void sub_84A00();
void sub_84B20();
extern RwReal flt_428E30;
extern RwReal flt_428E34;
extern RwReal flt_44D4D0;
extern RwReal flt_44E5E8;
extern RwReal flt_44D4BC;
extern RwReal flt_44E824;
extern "C" RwInt32 sub_240120(void *arg_0);
extern "C" void sub_2401B0(void *arg_0, RwReal arg_4);
RwInt32 sub_170ED0(RwReal *arg_0);
RwInt32 sub_84730();
void sub_84770();
extern "C" RwInt32 RwaWaveDictContainsWave(RwInt32 arg_0, void *arg_4);
extern "C" void SoundEmitter_Stop(type_44C4E8 *arg_0, RwInt32 arg_4);
extern "C" void sub_23B8F0(type_44C4E8 *arg_0, RwInt32 arg_4);
extern "C" void sub_23C700(RwInt32 arg_0);
extern "C" void RwaWaveDictDestroy(RwInt32 arg_0);
void sub_198F00(type_3DF8D8_04 *arg_0);
extern "C" RwInt32 RwaWaveDictFindWaveByIndex(RwInt32 arg_0, RwInt32 arg_4);
// The virtual voices: eight lists' counts per group (dword_44E600, 0x24
// bytes a group), their blocks carved from the voice manager's pool
// (dword_4B1E98, the pool at +0x24) into dword_44E5C4's eight pointers.
struct type_44E600
{
    RwInt32 unk_00[8];
    RwInt32 unk_20;
};
extern type_44E600 dword_44E600[];
// The eight lists as the manager takes them: each one's count and block.
struct type_83A70
{
    RwInt32 unk_00;
    RwInt32 *unk_04;
    RwInt32 unk_08;
    RwInt32 *unk_0C;
    RwInt32 unk_10;
    RwInt32 *unk_14;
    RwInt32 unk_18;
    RwInt32 *unk_1C;
    RwInt32 unk_20;
    RwInt32 *unk_24;
    RwInt32 unk_28;
    RwInt32 *unk_2C;
    RwInt32 unk_30;
    RwInt32 *unk_34;
    RwInt32 unk_38;
    RwInt32 *unk_3C;

    type_83A70();
};
extern RwInt32 *dword_44E5C4[8];
void sub_83850(RwInt32 arg_0, type_8A980 *arg_4, RwInt32 **arg_8);
void sub_83B20();
void sub_83B50();
void sub_83C90();
RwInt32 sub_83D30();
void sub_83D70(RwInt32 arg_0);
void sub_86350();
// The file system RenderWare manages (RWSDK rtfsyst.h).
extern "C" RwBool RtFSManagerSyncAllFilesOnFileSystem(void *fs);
extern void *dword_4F39D4;
// A frame in milliseconds (16.67), the wait sub_83BB0 doubles.
extern const RwReal flt_3D4340;
void sub_83510();
void sub_835E0();
void sub_83B40();
void sub_83B70();
void sub_83BB0();
void sub_83CF0();
RwInt32 sub_83DE0(RwInt32 arg_0);
extern RwReal flt_44E894;
extern RwInt32 dword_44E898;
extern RwInt32 dword_44E89C;
// Whether the music streams are kept over a pause (sub_85D60 keeps them in
// dword_44E480, sub_860E0 primes them again).
extern RwInt32 dword_44E884;
extern struct type_44E8D8_248 *dword_44E480[3];
// Reads the parameter arg_4 of the library object arg_0 (sub_85D60).
extern "C" RwInt32 sub_23F960(void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
extern RwInt32 dword_44E8A0;
extern RwInt32 dword_44E8BC;

// The language (0 to 6) and the 1 MB buffer a bank file is read into.
extern RwInt32 dword_44E8A4;
extern RwUInt8 *dword_44E8C4;

// Loads the bank arg_0 (from memory, holding dword_44BA98, when arg_4).
void sub_825E0(type_825E0 *arg_0, RwInt32 arg_4);
void sub_84230(type_84230 *arg_0);
void sub_858E0(RwChar *arg_0, RwChar *arg_4, RwInt16 arg_8);
void sub_83DD0(type_199010 *arg_0);
// A name from the current language's string pool for a sound (sub_83DD0).
RwChar *sub_1986B0();
// The sounds: sub_198710 finds the one with the id arg_0, sub_198770 is
// whether arg_0 is taken otherwise, sub_199010 makes one (arg_4 only known
// by width), sub_198FE0 registers it.
type_199010 *sub_198710(type_3DF8D8_04 *arg_0);
RwInt32 sub_198770(type_3DF8D8_04 *arg_0);
type_199010 *sub_199010(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
RwInt32 sub_198FE0(type_3DF8D8_base *arg_0);
void sub_82330();
void sub_82340();
// The game's operator new with a memory type (0x12F0E0).
void *operator new(size_t arg_0, RwUInt32 arg_4);
void operator delete(void *arg_0, RwUInt32 arg_4);

// The sound table sub_82500 reads (0x10E words) from the file sub_85840
// names.
extern RwInt32 dword_44C0B0[0x10E];

// Memory of arg_0 bytes (hint arg_4) aligned to 8, the block's own address
// kept in the word before it.
void *sub_824A0(RwUInt32 arg_0, RwUInt32 arg_4);
void sub_82500();
// sub_85840: the sound table's file name into arg_0 and the language's
// directory into arg_4; dword_428E38: the languages' directory names, by
// dword_44E8A8.
void sub_85840(RwChar *arg_0, RwChar *arg_4);
extern const RwChar *dword_428E38[];
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4);

// The memory functions the game allocates through (as animkey.h has them).
// The debug print, as these calls use it.
void sub_19A750(void *arg_0);

#endif
