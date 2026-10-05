/*
 * type_DA580: the game's font, a wrapper of an Rt2d font (unk_00) named after
 * its constructor. The fonts share one brush (brush, the database's name)
 * and two texture dictionaries (the HUD's, dword_4B8958, and the pad's,
 * dword_4B895C), which go when the last font does (dword_4B8960 counts
 * them). A Unicode font's strings are widened first (sub_DA860), and its
 * characters are read two bytes at a time (FONT_CHAR).
 */
#ifndef TYPE_DA580_H
#define TYPE_DA580_H

#include "rw/ostypes.h"
#include "rw/rt2d.h"
#include "rw/batextur.h"
#include "rw/baraster.h"

struct type_DA580
{
    Rt2dFont *unk_00;

    type_DA580();
    ~type_DA580();
    // A font read from arg_0 (none when arg_0 is 0), or 0 when it will not
    // read.
    static type_DA580 *sub_DA680(const RwChar *arg_0);
    RwReal sub_DA790();
    // The width of arg_0 at the height arg_4 (the font's own when 0).
    RwReal sub_DA7B0(const RwChar *arg_0, RwReal arg_4);
    // The height of arg_0 wrapped to the box arg_4 at the height arg_8.
    RwReal sub_DA8C0(const RwChar *arg_0, Rt2dBBox *arg_4, RwReal arg_8);
    // Shows arg_0 at arg_4 in the colour arg_8 at the height arg_C, with the
    // font arg_10 for this call when given.
    void sub_DAB00(const RwChar *arg_0, RwV2d *arg_4, RwRGBA *arg_8, RwReal arg_C, Rt2dFont *arg_10);
    // Shows arg_0 wrapped to the box arg_4, arg_8 below its top, aligned by
    // arg_C (0 left, 1 centred, 2 right), in the colour arg_10 at the height
    // arg_14; lines past the box's bottom are dropped.
    void sub_DAC60(const RwChar *arg_0, Rt2dBBox *arg_4, RwReal arg_8, RwInt32 arg_C, RwRGBA *arg_10,
                   RwReal arg_14);
    // The characters of arg_0's first line (with its leading spaces) in the
    // box width arg_4 at the height arg_8.
    RwUInt32 sub_DB180(const RwChar *arg_0, RwReal arg_4, RwReal arg_8);
    // The end of the line of arg_0 that fits the width arg_4 (in heights),
    // and the line's width in arg_8 (sub_DAC60 aligns the line by it).
    const RwChar *sub_DB3E0(const RwChar *arg_0, RwReal arg_4, RwReal *arg_8);
    // Finds the $...$ tokens of arg_0 (at most two), keeps each in
    // byte_4B8940 with its place (dword_4B8938) and length (dword_4B8930),
    // and blanks those sub_DBB80 takes (drawn at arg_8, height arg_4).
    void sub_DB620(const RwChar *arg_0, RwReal arg_4, RwV2d *arg_8);
    // Draws the pad button of the token arg_0 (at arg_8 in the string arg_4,
    // shown at arg_C at the height arg_10); false when it has none.
    bool sub_DBB80(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, RwV2d *arg_C, RwReal arg_10);
    // Puts sub_DB620's tokens back into arg_0.
    void sub_DBA10(const RwChar *arg_0);
    // The pad texture's raster for the token arg_0 (unk_4292D0's), or 0.
    RwRaster *sub_DBA80(const RwChar *arg_0);
};

// Draws the raster arg_0 at arg_4, arg_8 wide and arg_C high, with the brush
// arg_10.
void sub_DC0D0(RwRaster *arg_0, RwV2d *arg_4, RwReal arg_8, RwReal arg_C, Rt2dBrush *arg_10);
// Widens the string arg_0 into arg_4.
void sub_DA860(const RwChar *arg_0, RwUInt16 *arg_4);
// Reads the texture dictionary at the path arg_0 (0 when it will not).
RwTexDictionary *sub_DC000(const RwChar *arg_0);
// The debug print: formats arg_0 and prints it with a prefix.
void sub_16C220(const RwChar *arg_0, ...);
RwInt32 sub_19BD80(const RwChar *arg_0);

extern Rt2dBrush *brush;
extern RwTexDictionary *dword_4B8958;
extern RwTexDictionary *dword_4B895C;
extern RwInt32 dword_4B8960;
extern RwInt32 dword_4E23A8;
// sub_DB620's tokens: their lengths, places, text and count.
extern RwUInt32 dword_4B8930[2];
extern RwInt32 dword_4B8938[2];
extern RwChar byte_4B8940[2][12];
extern RwInt32 dword_4B8968;

// A pad button's token ("$ac$" and the rest) and its texture number.
struct type_4292D0
{
    RwInt32 unk_00;
    RwChar unk_04[8];
};
// The pad buttons' tokens (.data; 0x4292D4 is the database's aAc).
extern type_4292D0 unk_4292D0[20];
extern RwReal flt_4292C8;

// A character of a font's string: two bytes (low first) when the font is
// Unicode (u), else one signed byte. An inline with no address and so no
// database name, named for what it reads. Evidence: sub_DA8C0 keeps each
// read in a slot placed before `this` (the result local), where the
// conditional expression's own temporaries come after it.
inline RwInt32 FONT_CHAR(bool u, const RwChar *p)
{
    RwInt32 r;

    if (u)
    {
        r = (RwUInt8)p[0] | ((RwUInt8)p[1] << 8);
    }
    else
    {
        r = *p;
    }
    return r;
}
// The next character's place: a macro (its conditional's temporaries follow
// `this`).
#define FONT_NEXT(u, p) ((u) ? (p) + 2 : (p) + 1)

// The place of the character before p.
#define FONT_PREV(u, p) ((u) ? (p) - 2 : (p) - 1)
// The place n characters on from p. An inline (no address; named for what
// it does): sub_DBB80 keeps strlen's result, its n, in a slot among
// FONT_CHAR's.
inline const RwChar *FONT_SKIP(bool u, const RwChar *p, RwUInt32 n)
{
    return u ? p + n * 2 : p + n;
}

// Stores the character c at p (two bytes when the font is Unicode). An
// inline with no address, named for what it does. Evidence: sub_DBB80's
// stores of 0 mask the constant (xor; and 0xFFFF), as a substituted
// parameter does. Only an unsigned c substitutes the constant while the
// byte store still reads a variable's low byte (movzx).
inline void FONT_PUT(bool u, RwChar *p, RwUInt32 c)
{
    if (u)
    {
        *(RwUInt16 *)p = (RwUInt16)(c & 0xFFFF);
    }
    else
    {
        *p = (RwChar)((RwUInt8)c & 0xFF);
    }
}

// Narrows the wide string s into d (the low byte of each character). An
// inline with no address, named for what it does. Evidence: sub_DB620 keeps
// the argument s in a temporary and p and q in slots of their own, placed
// among FONT_CHAR's result slots.
inline void FONT_NARROW(RwChar *d, const RwChar *s)
{
    const RwUInt16 *p = (const RwUInt16 *)s;
    RwChar *q = d;

    while (*p)
    {
        *q = (RwChar)*p;
        q++;
        p++;
    }
    *q = 0;
}

#endif
