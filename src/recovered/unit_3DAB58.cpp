// An object whose code the original link dropped (/OPT:REF): only its texts are in
// the image, at 0x3DAB58-0x3DAB94, between RenderWare Studio's render.obj and
// rwgfxresource.obj: "" and the names of RenderWare's video mode flags, which
// nothing in the image reads. They survived the link, so they were not COMDAT
// literals: the object was built without /GF (config/flags.txt), which puts a
// unit's texts in one .rdata section, in the order they appear.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include <string.h>

// Its texts (one .rdata section, PLAN M5):
// match: $SG683 @ 0x003DAB58
// match: $SG685 @ 0x003DAB5C
// match: $SG687 @ 0x003DAB68
// match: $SG689 @ 0x003DAB74
// match: $SG691 @ 0x003DAB84
// match: $SG693 @ 0x003DAB8C

// Not in the image: a stand-in for the dropped code that used the texts (the
// video mode's flags as text). Unreferenced.
void dropped_3DAB58(RwChar *arg_0, RwUInt32 arg_4)
{
    strcpy(arg_0, "");
    if (arg_4 & 0x01)
        strcat(arg_0, "EXCLUSIVE ");
    if (arg_4 & 0x02)
        strcat(arg_0, "INTERLACE ");
    if (arg_4 & 0x04)
        strcat(arg_0, "FFINTERLACE ");
    if (arg_4 & 0x08)
        strcat(arg_0, "FSAA0 ");
    if (arg_4 & 0x10)
        strcat(arg_0, "FSAA1 ");
}
