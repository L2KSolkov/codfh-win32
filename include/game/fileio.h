/*
 * The debug print and kujuUI's file input (\COD\SHARED\fileIO\cFileIn.cpp,
 * unit_1C8A30): a file read through RenderWare's file interface.
 */
#ifndef GAME_FILEIO_H
#define GAME_FILEIO_H

#include "rw/ostypes.h"
#include "rw/osintf.h"

// A debug print (vsprintf into OutputString, then OutputDebugStringA).
void sub_1C8A30(const RwChar *arg_0, ...);
extern RwChar OutputString[];

// A string key: a pointer to its text, copied, equal and ordered by
// strcmp (the maps' keys call these; kujuUI's name map, std::map's less,
// calls operator<).
struct type_1C8A60
{
    const RwChar *unk_00;

    // Its text is arg_0 (out of line; folded by /OPT:ICF with RWS's
    // CAttributeDataChunkIterator constructor, 0x12A1B0).
    type_1C8A60(const RwChar *arg_0);
    // A copy through operator= (inline: the name map's insert, sub_1E1030,
    // builds its pair's key through a call to it).
    type_1C8A60(const type_1C8A60 &arg_0)
    {
        *this = arg_0;
    }
    type_1C8A60 &operator=(const type_1C8A60 &arg_0);
    bool operator==(const type_1C8A60 &arg_0) const;
    bool operator<(const type_1C8A60 &arg_0) const;
};

namespace kujuUI
{
// A file being read (its handle from RenderWare's file interface).
struct cFileIn
{
    void *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;

    cFileIn(void *arg_0);
    // Closes it.
    ~cFileIn();
    // Reads arg_8 items of arg_4 bytes into arg_0 (at most arg_C bytes).
    // Named by its assertion's function name.
    bool readVector(void *arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C);
    // Reads arg_4 bytes into arg_0; four bytes; a string of at most arg_4
    // characters ending in a zero byte.
    bool sub_1C8BA0(void *arg_0, RwUInt32 arg_4);
    bool sub_1C8BE0(void *arg_0);
    bool sub_1C8C00(RwChar *arg_0, RwUInt32 arg_4);
    // Whether it is at its end.
    bool sub_1C8DC0();
};
// Opens the file arg_0 (under dword_42CC60) into *arg_4, or leaves it 0.
void sub_1C8CA0(const RwChar *arg_0, cFileIn **arg_4);
}
// RenderWare's file interface, taken on the first open.
extern RwFileFunctions *dword_4FEAAC;
// The files' path prefix (empty).
extern const RwChar *dword_42CC60;

#endif
