/*
 * Reading a DDS texture from a kujuUI file (unit_1C9B40): while RenderWare
 * reads it, its file interface is replaced by functions that read the
 * open file (dword_4FEAE4) for names containing the extension
 * dword_4FEAE0; the interface is kept in dword_4FEAB4 meanwhile.
 */
#ifndef GAME_DDSLOAD_H
#define GAME_DDSLOAD_H

#include "rw/ostypes.h"
#include "rw/osintf.h"
#include "rw/batextur.h"
#include "rw/rwxbox.h"
#include "rw/rt2d.h"
#include "game/fileio.h"

extern "C" RwBool RwTextureDestroy(RwTexture *texture);
// A function that returns 1 (folded by /OPT:ICF); the replacement close.
RwInt32 sub_31DB0(void *arg_0);

extern RwFileFunctions dword_4FEAB4;
extern const RwChar *dword_4FEAE0;
extern kujuUI::cFileIn *dword_4FEAE4;
extern bool byte_4FEAE8;

// Reads the DDS texture arg_0 through the kujuUI file of that name.
RwTexture *sub_1C9B40(const RwChar *arg_0);
// Destroys the texture arg_0, or its dictionary when it has one.
void sub_1C9BE0(RwTexture *arg_0);
// Replaces RenderWare's file interface for names containing arg_0 (false
// when already replaced), and puts it back (false when not replaced).
bool sub_1C9C20(const RwChar *arg_0);
bool sub_1C9CC0();
// The replacements: whether a name has the extension (also the open),
// read, seek (forward, by reading) and end of file.
RwBool sub_1C9D10(const RwChar *arg_0);
size_t sub_1C9D40(void *arg_0, size_t arg_4, size_t arg_8, void *arg_C);
RwInt32 sub_1C9DC0(void *arg_0, RwFileSeekOffset arg_4, RwInt32 arg_8);
RwInt32 sub_1C9E80(void *arg_0);

#endif
