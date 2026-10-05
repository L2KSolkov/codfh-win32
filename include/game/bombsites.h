/*
 * The multiplayer game's bomb sites (dword_4F6950, unit_1A3D50): up to five
 * sites, each declared at a trigger ("DeclareBombSite", while the game type
 * is 8, search and destroy), with its state (0 none, 3 planted, 4 and 5 as
 * the game runs them), its position, the entity that planted it and a value
 * passed with it ("DeclareBombPlanted"); then twenty records the constructor
 * clears.
 */
#ifndef GAME_BOMBSITES_H
#define GAME_BOMBSITES_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

struct type_1F8560;

struct type_4F6950_site
{
    class type_712B0 *unk_00;   // its trigger
    RwInt32 unk_04;             // its state
    RwV3d unk_08;               // its position
    struct type_3D2E7C *unk_14; // what planted it
    RwInt32 unk_18;
};

// A flag and a value, cleared by the inline constructor.
struct type_4F6950_8C
{
    bool unk_00;
    RwInt32 unk_04;

    type_4F6950_8C()
    {
        unk_00 = 0;
        unk_04 = 0;
    }
};

struct type_4F6950
{
    type_4F6950_site unk_00[5];
    type_4F6950_8C unk_8C[20];

    type_4F6950();
    // The state of site arg_0 as the HUD shows it (type_DC400::sub_E7D00):
    // 1 for an empty site while not every team is in, 6 for state 5 in the
    // same case, else the state.
    RwInt32 sub_1A3D50(RwInt32 arg_0);
    // Explodes site arg_0 (sub_1A3E60), then sets it to state 5 with the
    // manager told (sub_1A41C0) or not (sub_1A4200).
    void sub_1A3E00(RwInt32 arg_0);
    void sub_1A3E30(RwInt32 arg_0);
    void sub_1A3E60(RwInt32 arg_0);
    // Whether site arg_0 is empty.
    RwInt32 sub_1A4090(RwInt32 arg_0);
    // The first site (planted ones only, unless arg_4) within reach of the
    // point arg_0, or -1.
    RwInt32 sub_1A40C0(RwV3d *arg_0, RwInt32 arg_4);
    // Whether the state arg_0 is 3 or 4.
    RwInt32 sub_1A4140(RwInt32 arg_0);
    // The site at the trigger arg_0, or -1.
    RwInt32 sub_1A4170(class type_712B0 *arg_0);
    // Sets site arg_0's state to arg_4, telling the manager first
    // (sub_1A41C0) or not (sub_1A4200): a bomb made at the point arg_C when
    // one is planted, taken away when it is not, the objective's flags,
    // and the defused and planted texts naming player arg_8.
    void sub_1A41C0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C);
    void sub_1A4200(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C);
    // Declares the bomb planted at site arg_4 by arg_0, with arg_8
    // ("DeclareBombPlanted").
    void sub_1A47B0(struct type_3D2E7C *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Clears the sites.
    void sub_1A4850();
    // Declares the bomb site arg_0 at the trigger arg_4 ("DeclareBombSite").
    void sub_1A48B0(RwInt32 arg_0, class type_712B0 *arg_4);
};
extern type_4F6950 dword_4F6950;

// A site as the multiplayer manager keeps it (0x24 bytes): its state, the
// updates sent, the round, the player who set the state, the bomb's timer
// (30 on planting), the planter and the bomb's position.
struct type_4F8184_site
{
    RwInt32 unk_00;
    RwUInt32 unk_04;
    RwReal unk_08;
    RwUInt32 unk_0C;
    RwReal unk_10;
    RwUInt32 unk_14;
    RwV3d unk_18;
};

// The multiplayer manager's part the sites report to (unk_4F7EB8 + 0x2CC):
// the five sites and the round. A site's new state (sub_1A7D80: sent when
// hosting, else kept and sent on) and a planted bomb (sub_1A84A0).
struct type_4F8184
{
    type_4F8184_site unk_00[5];
    RwReal unk_B4;              // the round's time

    void sub_1A7D80(RwInt32 arg_0, RwInt32 arg_4, RwV3d *arg_8);
    void sub_1A84A0(RwInt32 arg_0, RwInt32 arg_4);
    // A site's state from a peer (the handler sub_1AEB90); only the width is
    // known.
    void sub_1A80B0(struct type_3E0FCC *arg_0);
    // Whether player arg_0 carries (state 2), defuses (4) or either at a
    // site.
    RwInt32 sub_1A8620(RwUInt32 arg_0);
    RwInt32 sub_1A8680(RwUInt32 arg_0);
    RwInt32 sub_1A86E0(RwUInt32 arg_0);
    // Clears the sites and the round.
    void sub_1A7CF0();
    // Steps the round by arg_0 frames: counts planted bombs down (exploding
    // them) and puts back what was carried or defused too long.
    void sub_1A84C0(RwReal arg_0);
    // Writes and reads all the sites (the full state).
    void sub_1A8730(type_1F8560 *arg_0);
    void sub_1A87F0(type_1F8560 *arg_0);
};
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_4F8184 &unk_4F8184;
#else
extern type_4F8184 unk_4F8184;
#endif
// Formats the text arg_4 with the player's name arg_8 into arg_0; only the
// widths are known.
void sub_1CB000(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8);
// Whether arg_0 is within the upright cylinder at arg_4 of radius arg_8
// and half-height arg_C (unit_08AB60).
RwInt32 sub_92860(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C);

#endif
