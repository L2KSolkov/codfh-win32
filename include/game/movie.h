/*
 * The movie player (sub_E8BA0: "Failed to load movie for movie player.
 * Bailing out!"): plays a movie from SHELL\MOVIES\ (in the language's folder
 * when there is one) on a camera until it ends or a pad's button is
 * pressed, pausing the music object unk_4B8C70 meanwhile. The level's
 * opening and closing movies are named by the shell level behaviour
 * (CShellLevelBehaviorClass's commands 6 and 7: sub_E8DB0, sub_E8E30).
 */
#ifndef GAME_MOVIE_H
#define GAME_MOVIE_H

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "bink/bink.h"

// A movie object of 0x118 bytes: three are global and
// the player keeps one of its own. Named for its lowest known method, its
// open. Only its handle, unk_84, is known beyond the fields sub_19D580
// clears; its name arrays are guesses that give the player's /GS cookie.
struct type_19D580
{
    bool unk_00;
    bool unk_01;
    RwChar unk_02[0x1F];
    RwChar unk_21[0x23];
    RwInt32 unk_44;
    RwUInt8 unk_48[0x3C];
    HBINK unk_84;               // its Bink movie
    RwUInt32 unk_88;            // the frames shown
    RwChar unk_8C[0x80];
    RwUInt8 unk_10C;            // it opened
    RwUInt8 unk_10D[0x3];
    void *unk_110;              // its file (closed with it)
    RwUInt8 unk_114[0x4];

    // Clears it; its unk_01 (true).
    bool sub_19D580();
    // Closes it; true.
    bool sub_19D5E0();
    // Opens the file arg_0 (arg_4 1 from the player); false on failure.
    bool sub_19D640(const RwChar *arg_0, RwInt32 arg_4);
    // Steps it: 1 at the end (arg_0: loop instead), 2 with no new frame, -1
    // with no movie.
    RwInt32 sub_19D720(bool arg_0);
    // Draws its frame on the camera arg_0 (arg_4 0).
    void sub_19D810(RwCamera *arg_0, RwInt32 arg_4);
    // Pauses (true) or resumes it.
    void sub_19D890(bool arg_0);
    // Nonzero while it is still changing state.
    RwInt32 sub_19D8C0();
    // Fades it (arg_4 nonzero in, else out); only the widths are known.
    void sub_19D8E0(RwInt32 arg_0, RwInt32 arg_4);
};
// The Bink player (dword_4F39A8, one for all movies): it opens a movie from
// d: with its sound tracks at half volume and the screen's scale to the
// movie (sub_19CB80), and closes it (sub_19CD10).
struct type_4F39A8
{
    RwUInt8 unk_00[0x10];
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwReal unk_18;              // the screen's width over the movie's
    RwReal unk_1C;              // and its height over the movie's
    RwInt32 unk_20;
    RwInt32 unk_24;
    RwInt32 unk_28;             // a movie is open

    void sub_19CB20(RwInt32 arg_0);
    HBINK sub_19CB80(const RwChar *arg_0, RwInt32 *arg_4);
    void sub_19CD10(HBINK arg_0, void *arg_4);
    // Starts the movie arg_0: 0, identical to other methods and folded
    // (/OPT:ICF) into sub_32260.
    RwInt32 sub_32260(HBINK arg_0);
};
extern type_4F39A8 dword_4F39A8;

extern type_19D580 unk_4B8B58;
extern type_19D580 unk_4B8C70;
extern type_19D580 unk_4B8D88;

// Whether the level has an opening (byte_4B8E9C, in gameloop.h) and a
// closing (byte_4B8E9D) movie, and whether the movies are set up
// (byte_4B8E9E).
#ifdef CODFH_PLAIN
extern bool &byte_4B8E9D;
#else
extern bool byte_4B8E9D;
#endif
#ifdef CODFH_PLAIN
extern bool &byte_4B8E9E;
#else
extern bool byte_4B8E9E;
#endif
// The movies' names (keys of their objects, whose unk_10 is the file name).
extern type_3DF8D8_04 unk_4B8EA8;
extern type_3DF8D8_04 unk_4B8EB0;
// Set while a movie plays (the front end's byte_4B88A8 clear), and whether
// the music is paused for it.
extern bool byte_4B88A8;
extern bool byte_4B8EA1;
// Set to stop the playing movie.
extern RwInt32 dword_4B8EA4;
// Set when all four pads can skip a movie.
extern RwInt32 dword_4B892C;
// The languages' folder names, by sub_19B0A0 (0 and 1 have none).
extern const RwChar *off_428E38[];
// Called after the opening movie with its camera; only the width is known.
void sub_19BAC0(RwCamera *arg_0);

// Pause the music for a movie (arg_0 set) or fade it (sub_E8860), and
// resume it after (sub_E88B0).
void sub_E8860(bool arg_0);
void sub_E88B0(bool arg_0);
// Plays the movie file arg_0 on the camera arg_4.
void sub_E8BA0(const RwChar *arg_0, RwCamera *arg_4);
// Whether the file arg_0 (a level path, sub_D7F20) exists on d:.
bool sub_E8EB0(const RwChar *arg_0);

#endif
