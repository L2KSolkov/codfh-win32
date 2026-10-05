/*
 * type_8A980: a sound emitter (0x84 bytes). The sound system's is
 * dword_4B1E98, and every entity embeds one at +0x1C0 (type_3D3548's
 * constructor builds it with sub_88830; sub_88DA0 destroys it).
 */
#ifndef TYPE_8A980_H
#define TYPE_8A980_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/alfasched.h"

struct type_3D3548;
struct type_3DF8D8_04;

// dword_4B1E98: an object only known by its method sub_8A980, which primes
// the stream alias under the key *arg_0 ("PrimeAudioStream" passes 0 for the
// rest); only the widths are known.
// Entities embed one at +0x1C0 ("EfuncPlaySound" plays the sound under
// the key *arg_0 from the entity arg_4 at *arg_C with arg_10 through it,
// returning its id; "EfuncPlayIndexSound" plays entry arg_4 of an index
// sound alias with sub_8AA70).
struct type_8A980
{
    // The sound system's (dword_4B1E98): sub_88950 takes the virtual voice
    // lists (unit_0824A0's sub_83850 carves them from the pool at +0x24),
    // sub_88DF0 lets them go.
    type_8A980();
    ~type_8A980();
    void sub_88950(struct type_83A70 *arg_0, RwInt32 arg_4);
    void sub_88DF0();
    // Lets the voice arg_0 go: ends its lasting sound and stops it if it
    // plays (sub_88DF0 calls it for each of lists 1 to 7).
    void sub_8A910(RwInt32 arg_0);
    // Whether the voice arg_0 (0 and -1 are none) is playing.
    static RwInt32 sub_8A950(RwInt32 arg_0);
    // Moves every playing voice to arg_0 (and tells the library).
    void sub_89540(RwV3d *arg_0);
    // A free voice from the list arg_0 (8 is list 0 again); with none free,
    // it steals the next in turn when arg_4 is set or the list is 0. 0 when
    // the list is disabled or there is none.
    RwInt32 sub_89B00(RwInt32 arg_0, RwInt32 arg_4);
    // Plays the sound arg_0 with the wave arg_4 on a voice of the list arg_8
    // (stealing as sub_89B00 does with arg_C); arg_10 keeps it out of the
    // ducking. Returns the voice, or 0.
    RwInt32 sub_8A440(struct type_199010 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                      RwInt32 arg_10);
    RwInt32 sub_8A980(struct type_3DF8D8_04 *arg_0, struct type_3D3548 *arg_4, RwInt32 arg_8,
                      RwV3d *arg_C, RwInt32 arg_10, RwInt32 arg_14);
    RwInt32 sub_8AA70(struct type_3DF8D8_04 *arg_0, RwInt32 arg_4, struct type_3D3548 *arg_8,
                      RwInt32 arg_C, RwV3d *arg_10, RwInt32 arg_14, RwInt32 arg_18);
    struct type_44C4E8 *unk_00; // its voice (sub_89540 stops it through sub_85800)
    RwInt32 *unk_04[8];         // the virtual voice lists
    type_16C2A0 unk_24;
    RwInt32 unk_44[8];          // their lengths
    RwInt32 unk_64[8];          // the next voice each steals (sub_89B00)
};

#endif
