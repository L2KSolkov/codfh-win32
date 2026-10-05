/*
 * kujuUI's fonts (\COD\SHARED\UI\, unit_1E5280): the reference-counted
 * font, its texture pages and glyphs, kujuUI's reference-counted pointer,
 * the text pages a layout fills, and the font sets. Global names: the HUD
 * (types/type_DC400.h) used them first.
 */
#ifndef GAME_KUJUFONT_H
#define GAME_KUJUFONT_H

#include <string>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/batextur.h"
#include "rw/baraster.h"
#include "rw/baimage.h"
#include "rw/badevice.h"
#include "types/type_505188.h"
#include "rws/memoryhandler.h"

namespace kujuUI
{
struct type_1E0330_rect;
struct type_1E2250;
struct type_1E2250_entry;
class cScopeValidator;
}

// A kujuUI text page: the quads of one texture page of a laid-out string
// (0x14 bytes; sub_1E6690 fills four). Named for its constructor.
struct type_1F5A50
{
    RwIm2DVertex *unk_00;       // the vertices (six a quad)
    RwUInt32 unk_04;            // their count, zero when the page is empty
    RwUInt32 unk_08;            // the room for them
    RwReal unk_0C;              // the page's position (sub_1F5CD0 moves
    RwReal unk_10;              // its vertices by the change)

    type_1F5A50();
    // With room for arg_0 vertices.
    type_1F5A50(RwUInt32 arg_0);
    ~type_1F5A50();
    // Makes room for arg_0 vertices, keeping those it has.
    void sub_1F5B20(RwUInt32 arg_0);
    // Places the page at (arg_0, arg_4), and draws it; empties it
    // (sub_1F5BA0); adds a quad (the rectangle arg_0 at the depth arg_4 and
    // reciprocal depth arg_8, the texture rectangle arg_C and the colour
    // arg_10; sub_1F5C30).
    void sub_1F5CD0(RwReal arg_0, RwReal arg_4);
    void sub_1F5C00();
    void sub_1F5BA0();
    void sub_1F5C30(const kujuUI::type_1E0330_rect *arg_0, RwReal arg_4, RwReal arg_8,
                    const kujuUI::type_1E0330_rect *arg_C, RwUInt32 arg_10);
    // An inline test of unk_04, with no address and so no database name;
    // named for its field. Evidence: the HUD's text (type_DC400::sub_E7600)
    // tests it as a bool result (sete, then a test).
    bool test_unk_04()
    {
        return unk_04 == 0;
    }
};

// kujuUI's reference-counted pointer: the object's count is at +4, and the
// last release deletes it through its virtual destructor (sub_1ED6C0).
// Named for its constructor. Its members are out of line in the image and
// shared by every pointee (ICF): the HUD's unit places the constructors and
// the null test it instantiates first; all are defined here, and every unit
// emits the instantiations it uses (config/aliases.txt places the folded
// ones by address). The default constructor is the
// copy constructor with a default argument of 0: a default-constructed
// pointer copies a null temporary (sub_E8780, then sub_E8740, then
// sub_1ED6A0), and kujuUI's default constructor closures (sub_1E63F0,
// sub_21EFC0) are exactly that.
template <class T> struct type_E8780
{
    T *unk_00;

    type_E8780(T *arg_0);                       // sub_E8780
    type_E8780(const type_E8780 &arg_0 = 0); // sub_E8740
    ~type_E8780();                              // sub_1ED6A0
    // Releases its pointee (deleted on the last release) and clears it.
    void sub_1ED6C0();
    type_E8780 &operator=(const type_E8780 &arg_0); // sub_21C950
    type_E8780 &operator=(T *arg_0);             // sub_21C900
    T *operator->() const;                      // sub_1EE9D0
    // Whether it points at nothing (sub_E87C0, out of line, which the HUD's
    // unit instantiates first).
    bool sub_E87C0() const;
};

template <class T> type_E8780<T>::type_E8780(T *arg_0)
{
    unk_00 = arg_0;
    if (unk_00)
    {
        unk_00->inc_unk_04();
    }
}

template <class T> type_E8780<T>::type_E8780(const type_E8780 &arg_0)
{
    unk_00 = arg_0.unk_00;
    if (unk_00)
    {
        unk_00->inc_unk_04();
    }
}

template <class T> bool type_E8780<T>::sub_E87C0() const
{
    return unk_00 == 0;
}

// The pointee (out of line; /OPT:ICF folds every instantiation into 0x1EE9D0).
template <class T> T *type_E8780<T>::operator->() const
{
    return unk_00;
}

// Its members, defined here as the original header had them: every unit that uses an
// instantiation emits it (a COMDAT), and /OPT:ICF folds the identical ones.
template <class T> type_E8780<T> &type_E8780<T>::operator=(T *arg_0)
{
    if (unk_00 != arg_0)
    {
        sub_1ED6C0();
        unk_00 = arg_0;
        if (unk_00)
        {
            unk_00->inc_unk_04();
        }
    }
    return *this;
}

template <class T> type_E8780<T> &type_E8780<T>::operator=(const type_E8780 &arg_0)
{
    if (unk_00 != arg_0.unk_00)
    {
        sub_1ED6C0();
        unk_00 = arg_0.unk_00;
        if (unk_00)
        {
            unk_00->inc_unk_04();
        }
    }
    return *this;
}

template <class T> void type_E8780<T>::sub_1ED6C0()
{
    if (unk_00)
    {
        if (!unk_00->dec_unk_04())
            delete unk_00;
        unk_00 = 0;
    }
}

template <class T> type_E8780<T>::~type_E8780()
{
    sub_1ED6C0();
}


// kujuUI's reference-counted object (off_3E7314): its count (unk_04, which
// kujuUI's pointer type_E8780 bumps), deleted through its virtual
// destructor on the last release (sub_1ED6C0). Its constructor and
// destructor are inline; the destructor's out-of-line copy is at sub_1E5600
// (the font's constructor unwinds through it).
struct type_3E7314
{
    RwInt32 unk_04;

    type_3E7314()
    {
        unk_04 = 0;
    }
    virtual ~type_3E7314()
    {
    }
    // An inline bump of unk_04, with no address and so no database name;
    // named for its field. Evidence: the pointer's constructors
    // (type_E8780) bump it through a `this` copy of their own.
    void inc_unk_04()
    {
        unk_04++;
    }
    // Likewise its drop, returning the count left (the release sub_1ED6C0
    // tests it through a slot of its own).
    RwInt32 dec_unk_04()
    {
        return --unk_04;
    }
};

// kujuUI's texture (sub_1EEFB0 loads it from a .bin, sub_1EEF20 from a
// .tga): its raster (unk_00), or the texture it was read into (unk_04,
// destroyed by sub_1C9BE0); its destructor is sub_1EEEE0.
struct type_1EECE0;
struct type_1EEEE0
{
    RwRaster *unk_00;
    RwTexture *unk_04;

    // A raster made from the image arg_0 (sub_1EEE30); the texture arg_0's
    // (sub_1EEEB0, which it then owns).
    type_1EEEE0(const type_1EECE0 &arg_0);
    type_1EEEE0(RwTexture *arg_0);
    ~type_1EEEE0();
    // Its raster: an inline accessor with no address, named for its field.
    // Evidence: the image library's constructor (sub_1ECBD0) reads each
    // raster dimension through a slot of its own.
    RwRaster *get_unk_00()
    {
        return unk_00;
    }
};
struct type_1E6B50;
// The texture made from the image arg_0 into *arg_4 (sub_1EEDA0).
void sub_1EEDA0(type_1E6B50 *arg_0, type_1EEEE0 **arg_4);
void sub_1EEF20(const RwChar *arg_0, type_1EEEE0 **arg_4);
void sub_1EEFB0(const RwChar *arg_0, type_1EEEE0 **arg_4);

// A 32-bit image (0xC bytes; sub_1E6B50 takes the pixels *arg_8 over): its
// width, height and pixels; flipped top to bottom (sub_1E6FD0) and halved
// into *arg_0 (sub_1E7100: each pixel the mean of four, sub_1E70A0 by the
// channel at bit arg_4).
struct type_1E6B50
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
    RwUInt32 *unk_08;

    type_1E6B50(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 **arg_8);
    ~type_1E6B50();
    // Inline accessors with no addresses, named for their fields. Evidence:
    // the RwImage over it (sub_1EECE0) reads each through a slot of its own.
    RwUInt32 get_unk_00() const
    {
        return unk_00;
    }
    RwUInt32 get_unk_04() const
    {
        return unk_04;
    }
    void sub_1E6FD0();
    void sub_1E7100(type_1E6B50 **arg_0);
};
namespace kujuUI
{
struct cFileIn;
}
// Reads arg_8 pixels of 32, 24 and 8 bits (the last into alpha) from the
// file arg_0 into arg_4; a .tga's image into *arg_4 (0 when it cannot);
// the mean of four pixels' channel; the directory the image libraries'
// files are in (dword_42D0CC, ""; the image library reads it).
bool sub_1E6BC0(kujuUI::cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8);
bool sub_1E6BF0(kujuUI::cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8);
bool sub_1E6C50(kujuUI::cFileIn *arg_0, RwUInt32 *arg_4, RwUInt32 arg_8);
void sub_1E6CD0(const RwChar *arg_0, type_1E6B50 **arg_4);
RwUInt32 sub_1E70A0(const RwUInt32 *arg_0, RwUInt32 arg_4);
const RwChar *sub_1E72B0();

// An RwImage over a 32-bit image's pixels (sub_1EECE0; its destructor,
// sub_1EED80, destroys it).
struct type_1EECE0
{
    RwImage *unk_00;

    type_1EECE0(type_1E6B50 *arg_0);
    // Sets the image's stride for the depth arg_0 and width arg_4: an
    // inline with no address, named for what it does. Evidence: the
    // constructor computes 32 >> 3 unfolded (the depth substituted).
    void set_stride(RwUInt32 arg_0, RwUInt32 arg_4)
    {
        unk_00->stride = (arg_0 >> 3) * arg_4;
    }
    ~type_1EECE0();
};

// A font's texture page (0x24 bytes): its file name, texture and unk_20
// (1).
struct type_1E5830
{
    type_1A5EA0 unk_00;
    type_1EEEE0 *unk_1C;
    RwInt32 unk_20;

    type_1E5830(const RwChar *arg_0, type_1EEEE0 *arg_4) : unk_00(arg_0), unk_1C(arg_4), unk_20(1)
    {
    }
    ~type_1E5830()
    {
        delete unk_1C;
    }
};

// A font file's header (0x24 bytes): its characters' count (unk_12), its
// pages' count (unk_14) and its measures (unk_16 to unk_1C: the font's
// unk_0E, unk_08, unk_0A and unk_0C).
struct type_1E5A80_header
{
    RwUInt8 unk_00[0x12];
    RwUInt16 unk_12;
    RwUInt16 unk_14;
    RwUInt16 unk_16;
    RwUInt16 unk_18;
    RwUInt16 unk_1A;
    RwUInt16 unk_1C;
    RwUInt8 unk_1E[6];
};

// A font file's page record (0xC bytes; read and not used).
struct type_1E5A80_page
{
    RwUInt8 unk_00[0xC];
};

// kujuUI's arrays of up to N items of T with their count (a template, out
// of line; the font loader's scratch arrays and the focus stack's widgets:
// sub_1E61A0, sub_1E6240 and sub_1E8190 are its constructors). Its members
// are named for what they do, their instances having addresses of their
// own, many shared through /OPT:ICF: the next item (sub_1E61C0, sub_1E6260,
// 0x1EC3E0), the count (sub_1E6200, 0x191D80), the items (sub_1E6220), the
// item's size (sub_1E62A0, sub_1E62B0, 0x200B80), the item arg_0
// (sub_1E81B0), erasing it (sub_1E81E0), the index of arg_0 or -1
// (sub_1E8250), the iterators at the start and end (0x1CA450, sub_1E82A0),
// whether it is empty (sub_1E82D0), emptied (sub_1EC420) and its last item
// (sub_1EC470).
template <class T, RwInt32 N> struct type_1E61A0;
// An iterator over a type_1E61A0 (its item and its array; out of line and
// shared through /OPT:ICF: built at 0x1EFD70, stepped on at 0x204990, its
// item at 0x1EE9D0), stepped back (sub_1E82F0) and compared (sub_1E8310:
// whether they differ).
template <class T, RwInt32 N> struct type_1E61A0_it
{
    T *unk_00;
    const type_1E61A0<T, N> *unk_04;

    type_1E61A0_it(T *arg_0, const type_1E61A0<T, N> *arg_4);
    type_1E61A0_it &inc();
    type_1E61A0_it &dec();
    bool ne(const type_1E61A0_it &arg_0) const;
    T *get() const;
};
template <class T, RwInt32 N> struct type_1E61A0
{
    RwUInt8 unk_00[sizeof(T) * N];
    RwUInt32 unk_count;

    type_1E61A0();
    static RwUInt32 item_size();
    // How many items it holds at most (N; the in-game menus', 0x204800).
    static RwUInt32 capacity();
    T *next();
    RwUInt32 count();
    T *items();
    T *at(RwUInt32 arg_0);
    void erase(RwUInt32 arg_0);
    RwInt32 find(const T &arg_0);
    type_1E61A0_it<T, N> begin();
    type_1E61A0_it<T, N> end();
    bool empty();
    void clear();
    // Deletes each item's slot (operator delete on its address) and
    // empties it (the shell's items, 0x200B20).
    void delete_all();
    T *back();
    // Takes the item *arg_0 over (its bytes; arg_0's memory is freed
    // without destroying it).
    void take(T *arg_0);
};

template <class T, RwInt32 N> type_1E61A0<T, N>::type_1E61A0()
{
    unk_count = 0;
}

template <class T, RwInt32 N> T *type_1E61A0<T, N>::next()
{
    T *var_8;
    RwUInt8 *var_4 = &unk_00[item_size() * unk_count];
    ++unk_count;
    var_8 = (T *)var_4;
    return var_8;
}

template <class T, RwInt32 N> RwUInt32 type_1E61A0<T, N>::count()
{
    return unk_count;
}

template <class T, RwInt32 N> T *type_1E61A0<T, N>::items()
{
    T *var_4 = (T *)unk_00;
    return var_4;
}

template <class T, RwInt32 N> RwUInt32 type_1E61A0<T, N>::item_size()
{
    return sizeof(T);
}

template <class T, RwInt32 N> T *type_1E61A0<T, N>::at(RwUInt32 arg_0)
{
    T *var_8;
    RwUInt8 *var_4 = &unk_00[item_size() * arg_0];
    var_8 = (T *)var_4;
    return var_8;
}

template <class T, RwInt32 N> void type_1E61A0<T, N>::erase(RwUInt32 arg_0)
{
    at(arg_0);
    for (RwUInt32 var_4 = arg_0; var_4 != unk_count - 1; ++var_4)
        *at(var_4) = *at(var_4 + 1);
    --unk_count;
}

template <class T, RwInt32 N> RwInt32 type_1E61A0<T, N>::find(const T &arg_0)
{
    for (RwUInt32 var_4 = 0; var_4 != unk_count; ++var_4)
    {
        if (*at(var_4) == arg_0)
            return var_4;
    }
    return -1;
}

template <class T, RwInt32 N> type_1E61A0_it<T, N> type_1E61A0<T, N>::begin()
{
    return type_1E61A0_it<T, N>((T *)unk_00, this);
}

template <class T, RwInt32 N> type_1E61A0_it<T, N> type_1E61A0<T, N>::end()
{
    return type_1E61A0_it<T, N>((T *)unk_00 + unk_count, this);
}

template <class T, RwInt32 N> bool type_1E61A0<T, N>::empty()
{
    return unk_count == 0;
}

template <class T, RwInt32 N> void type_1E61A0<T, N>::clear()
{
    for (RwUInt32 var_4 = 0; var_4 != unk_count; ++var_4)
    {
        // The item, destroyed (nothing to do for a pointer): the item's
        // address is kept in a slot of its own.
        T *var_8 = at(var_4);
        var_8->~T();
    }
    unk_count = 0;
}

template <class T, RwInt32 N> void type_1E61A0<T, N>::delete_all()
{
    for (RwUInt32 var_4 = 0; var_4 != unk_count; ++var_4)
    {
        T *var_8 = at(var_4);
        delete var_8;
    }
    unk_count = 0;
}

template <class T, RwInt32 N> void type_1E61A0<T, N>::take(T *arg_0)
{
    T *var_4 = next();
    memcpy(var_4, arg_0, sizeof(T));
    RWSFree(arg_0);
}

template <class T, RwInt32 N> T *type_1E61A0<T, N>::back()
{
    return at(unk_count - 1);
}

template <class T, RwInt32 N> type_1E61A0_it<T, N>::type_1E61A0_it(T *arg_0, const type_1E61A0<T, N> *arg_4)
{
    unk_00 = arg_0;
    unk_04 = arg_4;
}

// (It returns the iterator, as dec does: the image folds its instances into
// type_1E61A0_cit's operator++, which does.)
template <class T, RwInt32 N> type_1E61A0_it<T, N> &type_1E61A0_it<T, N>::inc()
{
    ++unk_00;
    return *this;
}

template <class T, RwInt32 N> type_1E61A0_it<T, N> &type_1E61A0_it<T, N>::dec()
{
    --unk_00;
    return *this;
}

template <class T, RwInt32 N> bool type_1E61A0_it<T, N>::ne(const type_1E61A0_it &arg_0) const
{
    return !(unk_04 == arg_0.unk_04 && unk_00 == arg_0.unk_00);
}

template <class T, RwInt32 N> T *type_1E61A0_it<T, N>::get() const
{
    return unk_00;
}

template <class T, RwInt32 N> RwUInt32 type_1E61A0<T, N>::capacity()
{
    return N;
}

// A const iterator over a type_1E61A0, made from an iterator by its
// out-of-line constructor (the in-game menus', 0x204960) and stepped on by
// its pre-increment (0x204990); its item and its comparison are the
// iterator's (folded through /OPT:ICF into 0x1EE9D0 and 0x1E8310).
template <class T, RwInt32 N> struct type_1E61A0_cit
{
    T *unk_00;
    const type_1E61A0<T, N> *unk_04;

    type_1E61A0_cit(const type_1E61A0_it<T, N> &arg_0);
    type_1E61A0_cit &operator++();
    bool ne(const type_1E61A0_cit &arg_0) const;
    T *get() const;
};

template <class T, RwInt32 N> type_1E61A0_cit<T, N>::type_1E61A0_cit(const type_1E61A0_it<T, N> &arg_0)
{
    unk_00 = arg_0.unk_00;
    unk_04 = arg_0.unk_04;
}

template <class T, RwInt32 N> type_1E61A0_cit<T, N> &type_1E61A0_cit<T, N>::operator++()
{
    ++unk_00;
    return *this;
}

template <class T, RwInt32 N> bool type_1E61A0_cit<T, N>::ne(const type_1E61A0_cit &arg_0) const
{
    return !(unk_04 == arg_0.unk_04 && unk_00 == arg_0.unk_00);
}

template <class T, RwInt32 N> T *type_1E61A0_cit<T, N>::get() const
{
    return unk_00;
}

// The characters every font gets as copies of others (0x42CF80): the new
// code and the code copied, ended by -1 (the font's constructor,
// sub_1E5280, adds them after its own).
struct type_42CF80
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};
extern type_42CF80 unk_42CF80[];

// A kujuUI font (0x4C bytes, \COD\SHARED\UI\: sub_1E5A80 warns "Maximum
// number of textures per font"; off_3E7310): its space's width (unk_08),
// the gap between characters (unk_0A), its line's height above and below
// (unk_0C, unk_0E: sub_1E6100, sub_1E6120, set by sub_1E6140; the height,
// sub_1E60E0), its name (unk_10), the next font (unk_2C, from
// dword_503FD0), its glyphs (unk_30: unk_38 of them, the last, unk_34,
// for the missing ones), its pages (unk_3C: unk_3A of them). Named for its
// lowest known method: the texture of its page arg_0.
struct type_1E5A60 : type_3E7314
{
    RwUInt16 unk_08;
    RwUInt16 unk_0A;
    RwUInt16 unk_0C;
    RwUInt16 unk_0E;
    type_1A5EA0 unk_10;
    type_1E5A60 *unk_2C;
    kujuUI::type_1E2250 *unk_30;
    kujuUI::type_1E2250 *unk_34;
    RwUInt16 unk_38;
    RwUInt16 unk_3A;
    type_1E5830 *unk_3C[4];

    type_1E5A60(const RwChar *arg_0, const type_1E5A80_header *arg_4, const kujuUI::type_1E2250_entry *arg_8,
                RwInt32 arg_C, type_1E5830 *const *arg_10, RwInt32 arg_14);
    virtual ~type_1E5A60();
    // The font named arg_0 among those loaded (0 when none).
    static type_1E5A60 *sub_1E58C0(const RwChar *arg_0);
    // The glyph for missing characters, and the glyph of the character
    // arg_0 (a binary search, or the missing one).
    kujuUI::type_1E2250 *sub_1E5920();
    kujuUI::type_1E2250 *sub_1E5940(RwUInt16 arg_0);
    RwInt32 sub_1E5A40();
    RwTexture *sub_1E5A60(RwInt32 arg_0);
    RwUInt16 sub_1E60E0();
    RwUInt16 sub_1E6100();
    RwUInt16 sub_1E6120();
    void sub_1E6140(RwUInt16 arg_0);
    // The width of arg_0 (arg_4 characters, -1 for all) in pixels, and its
    // height into *arg_8 (sub_1F2460; sub_1F26B0 wraps at arg_4 pixels);
    // how many of arg_0's characters fit arg_4 pixels (sub_1F24C0).
    RwUInt32 sub_1F2490(const RwChar *arg_0, RwInt32 arg_4);
    RwUInt32 sub_1F2460(const RwChar *arg_0, RwUInt32 *arg_4, RwUInt32 *arg_8, RwInt32 arg_C);
    RwInt32 sub_1F24C0(const RwChar *arg_0, RwInt32 arg_4);
    RwUInt32 sub_1F26B0(const RwChar *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwUInt32 *arg_C, RwInt32 arg_10);
    // Lays out arg_0 in the colour arg_4 into the four pages arg_10, arg_8
    // wide, aligned by arg_C (0 left, 1 centre, 2 right); arg_14 set to the
    // height. The codes 1 to 8 set the colour, tab is 16 spaces.
    void sub_1E6690(const RwChar *arg_0, RwInt32 arg_4, RwUInt32 arg_8, RwInt32 arg_C, type_1F5A50 *arg_10,
                    RwInt32 *arg_14);
    // The line of arg_0 that fits arg_4 pixels: its width into *arg_8, the
    // start of the next into *arg_10 (arg_C steps over its spaces).
    void sub_1E69D0(const RwChar *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwInt32 *arg_C, const RwChar **arg_10);
    // A character's code: an inline with no address, named for what it
    // gives. Evidence: the layouts (sub_1E6690, sub_1E69D0) widen the
    // character into a 16-bit local of the expansion's before masking it.
    static RwUInt16 char_code(RwChar arg_0)
    {
        RwUInt16 var_0 = arg_0;
        return var_0 & 0xFF;
    }
    // The same for wide strings (the Live engine's font renderer's,
    // unit_225220): the size of arg_0 (sub_225BE0; sub_225F70 wraps at arg_4
    // pixels, copying arg_10 bytes when not -1), its width (sub_225F40),
    // its layout (sub_225C10) and the line that fits (sub_226050).
    RwUInt32 sub_225BE0(const wchar_t *arg_0, RwUInt32 *arg_4, RwUInt32 *arg_8, RwInt32 arg_C);
    void sub_225C10(const wchar_t *arg_0, RwInt32 arg_4, RwUInt32 arg_8, RwInt32 arg_C, type_1F5A50 *arg_10,
                    RwInt32 *arg_14);
    RwUInt32 sub_225F40(const wchar_t *arg_0, RwInt32 arg_4);
    RwUInt32 sub_225F70(const wchar_t *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwUInt32 *arg_C, RwInt32 arg_10);
    void sub_226050(const wchar_t *arg_0, RwUInt32 arg_4, RwUInt32 *arg_8, RwInt32 *arg_C, const wchar_t **arg_10);
};
extern type_1E5A60 *dword_503FD0;
// The length of the string arg_0 (and of the wide string arg_0).
RwInt32 sub_1E6160(const RwChar *arg_0);
RwInt32 sub_1E6180(const wchar_t *arg_0);

// A kujuUI font by name, loaded on first use (sub_E0E90 loads "codfontl"
// and "codfontn"): the file prefix unk_42D0C0 (dword_503FD4 long), the name,
// then ".bin" (unk_42D0C8, dword_503FD8 long); each page's texture is its
// name with ".bin" (unk_42D0C4, dword_503FDC long), else ".tga".
type_E8780<type_1E5A60> sub_1E5A80(const RwChar *arg_0);

// A set of six fonts and their colours (0x30 bytes; sub_1E6350 from arrays,
// sub_1E6450 a copy): the font arg_0 (sub_1E6610). sub_1E6510 fills the
// missing ones from the others (sub_1E62C0 each: arg_0 from arg_4, else
// from arg_8), and sub_1E6590 is the validator of its values.
struct type_1E6350
{
    type_E8780<type_1E5A60> unk_00[6];
    RwUInt32 unk_18[6];

    type_1E6350(const type_E8780<type_1E5A60> *arg_0, const RwUInt32 *arg_4);
    type_1E6350(const type_1E6350 &arg_0);
    ~type_1E6350();
    type_E8780<type_1E5A60> sub_1E6610(RwInt32 arg_0);
    // The colour arg_0: an inline with no address. Evidence: the text
    // layout (sub_1F15C0) reads colour 0 through an unfolded index.
    RwUInt32 get_colour(RwInt32 arg_0)
    {
        return unk_18[arg_0];
    }
};
void sub_1E62C0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_E8780<type_1E5A60> *arg_C, RwUInt32 *arg_10);
void sub_1E6510(type_E8780<type_1E5A60> *arg_0, RwUInt32 *arg_4);
const kujuUI::cScopeValidator *sub_1E6590();

#endif
