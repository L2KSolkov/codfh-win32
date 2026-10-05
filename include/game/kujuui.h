/*
 * kujuUI, the shared front-end library (\COD\SHARED\UI\, from 0x1DFBB0):
 * quad helpers, the pad's event mapper and the widgets. Only the widths
 * are known where no comment says more; the names are kujuUI's own where
 * its traces give them (cCaret's: "enum eEventWasHandled __thiscall
 * cCaret::processEvent(const class cStateChange &)").
 */
#ifndef GAME_KUJUUI_H
#define GAME_KUJUUI_H

#include "rw/ostypes.h"
#include "rw/badevice.h"
#include "game/fileio.h"
#include "game/loc.h"
#include "game/kujufont.h"

#include <map>
#include <list>
#include <set>
#include <vector>

typedef struct RwCamera RwCamera;

namespace kujuUI
{

// Whether an event was handled (processEvent's result; only its width is
// known).
enum eEventWasHandled
{
};

// A pad button's change: the button (unk_00) and whether it went down (0)
// or up (1).
class cStateChange
{
public:
    RwInt32 unk_00;
    RwInt32 unk_04;

    // Inline accessors with no addresses, named for their fields.
    // Evidence: the event mapper (sub_1DFE80) reads each through a slot of
    // its own.
    RwInt32 get_unk_00() const
    {
        return unk_00;
    }
    RwInt32 get_unk_04() const
    {
        return unk_04;
    }
    // Inline, with no addresses: the pad's event queue (sub_1E7560) builds
    // its 32 through an empty one, and the pad's changes (sub_1EE940) make
    // one of a button and whether it was pressed.
    cStateChange()
    {
    }
    cStateChange(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
    }
};

// What receives kujuUI's events (off_3E6CE4, both slots pure): the event
// mapper and the widgets.
struct type_3E6CE4
{
    virtual ~type_3E6CE4() = 0
    {
    }
    virtual eEventWasHandled processEvent(const cStateChange &arg_0) = 0;
};

// What the event mapper hands a button to: pressed (vf_008) when it is
// released after being pressed on it, if it takes the focus (vf_00C).
struct type_1DFE80_target : type_3E6CE4
{
    virtual void vf_008() = 0;
    virtual bool vf_00C() = 0;
};

// The pad's event mapper (off_3E6CEC): a target per button (13) and the
// button last pressed on one (14 for none).
struct type_3E6CEC : type_3E6CE4
{
    type_1DFE80_target *unk_04[13];
    RwInt32 unk_38;

    type_3E6CEC();
    virtual ~type_3E6CEC();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    // Button arg_0's target.
    void sub_1DFE50(RwInt32 arg_0, type_1DFE80_target *arg_4);
};

// An RwIm2DVertex from the screen position (arg_0, arg_4), its depth
// (arg_8, arg_C), its texture coordinates (arg_10, arg_14) and its colour
// (arg_18, red in the low byte); a quad's two triangles from the rectangle
// arg_0 and the texture rectangle arg_C; a vertex's screen x and y; and its
// screen position.
void sub_1DFBB0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                RwUInt32 arg_18, RwIm2DVertex *arg_1C);
void sub_1DFC30(const RwReal *arg_0, RwReal arg_4, RwReal arg_8, const RwReal *arg_C, RwIm2DVertex *arg_10,
                RwUInt32 arg_14);
RwReal sub_1DFD80(const RwIm2DVertex *arg_0);
RwReal sub_1DFD90(const RwIm2DVertex *arg_0);
void sub_1DFDA0(RwReal arg_0, RwReal arg_4, RwIm2DVertex *arg_8);

// A screen rectangle (left, top, right, bottom); built from its corners by
// an inline constructor (the border's creator, sub_1E04C0, keeps the four
// values in slots of their own).
struct type_1E0330_rect
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;

    type_1E0330_rect()
    {
    }
    type_1E0330_rect(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_08 = arg_8;
        unk_0C = arg_C;
    }
    // Its width and height: inlines with no addresses, named for what they
    // give. Evidence: the look (sub_1E37E0, sub_1E3A30) takes the member
    // rectangle's address into a slot of its own for each.
    RwReal width() const
    {
        return unk_08 - unk_00;
    }
    RwReal height() const
    {
        return unk_0C - unk_04;
    }
};

// The texture rectangle of an untextured quad, and the screen depth and
// its reciprocal the quads are drawn at.
extern type_1E0330_rect unk_503308;

struct type_1E4130;

// A quad (0xB0 bytes; sub_1EEAD0): its two triangles' vertices and where
// it has been moved to (unk_A8, unk_AC). Put off screen (sub_1EEB00), drawn
// (sub_1EEB60), moved to (arg_0, arg_4) (sub_1EEB80), set from a rectangle,
// depth, reciprocal depth, texture rectangle and colour (sub_1EEC20, through
// sub_1DFC30) and given a colour (sub_1EEC50). Its destructor is empty
// (pDtor, 0x1E41C0).
struct type_1EEAD0
{
    RwIm2DVertex unk_00[6];
    RwReal unk_A8;
    RwReal unk_AC;

    type_1EEAD0();
    ~type_1EEAD0();
    void sub_1EEB00();
    void sub_1EEB60();
    void sub_1EEB80(RwReal arg_0, RwReal arg_4);
    void sub_1EEC20(const type_1E0330_rect *arg_0, RwReal arg_4, RwReal arg_8, const type_1E0330_rect *arg_C,
                    RwUInt32 arg_10);
    void sub_1EEC50(RwUInt32 arg_0);
};

// What kujuUI draws with (sub_1E3FF0): the texture raster and filter last
// set (unk_00, unk_04; set only when they change, sub_1E4130 and
// sub_1E4160), and a quad over the whole screen (unk_08) that sub_1E4210
// fills with the colour arg_0. The constructor sets the render states the
// widgets draw with; sub_1E41F0 is the depth they are drawn at.
struct type_1E4130
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    type_1EEAD0 unk_08;

    type_1E4130();
    // Out of line: its quad's (empty) destructor, folded (/OPT:ICF) into a
    // list node's at 0x1EFD10.
    ~type_1E4130();
    // An empty method the interface's update (sub_1F77D0) calls first
    // (pDtor, folded by /OPT:ICF).
    void pDtor();
    void sub_1E4130(RwInt32 arg_0);
    void sub_1E4160(RwInt32 arg_0);
    void sub_1E41D0();
    RwReal sub_1E41F0();
    void sub_1E4210(RwUInt32 arg_0);
};

// A widget (off_3E7D08; its constructor and destructor are out of line,
// sub_1F76E0 and sub_1F7740): its parent and whether it has the focus.
// Slot 5 takes the time passed; slot 7 passes arg_0 and arg_4 on to the
// parent's (0 with none); givenFocus and lostFocus (named by cCaret's
// traces, as is processEvent) are told of the focus coming and going
// (sub_1F7790, sub_1F77B0).
struct type_3E7D08 : type_3E6CE4
{
    type_3E7D08 *unk_04;
    bool unk_08;

    type_3E7D08(type_3E7D08 *arg_0);
    virtual ~type_3E7D08() = 0;
    // Its parent (unk_04): an out-of-line getter shared through /OPT:ICF
    // (0x1E3480).
    type_3E7D08 *sub_1E3480() const;
    // Whether it has the focus; told it has it and has lost it (out of
    // line).
    bool sub_1F7720();
    void sub_1F7790();
    void sub_1F77B0();
    virtual void vf_008();
    virtual void vf_00C();
    virtual bool vf_010() = 0;
    virtual void vf_014(RwReal arg_0) = 0;
    virtual void vf_018(type_1E4130 *arg_0) = 0;
    virtual bool vf_01C(RwInt32 arg_0, RwInt32 arg_4);
    virtual type_1E0330_rect vf_020() = 0;
    virtual RwInt32 vf_024();
    virtual void givenFocus() = 0;
    virtual void lostFocus() = 0;
};

// The interface's root widget (dword_504390: given by sub_1F7760, set by
// sub_1F7770 with the time then, dword_504394). sub_1F77D0 updates it by
// the time passed and draws it, with the camera arg_0 cleared to
// unk_504398 before and shown after when arg_4 is set; byte_50438C is set
// meanwhile.
extern type_3E7D08 *dword_504390;
extern RwUInt32 dword_504394;
extern bool byte_50438C;
extern RwRGBA unk_504398;
type_3E7D08 *sub_1F7760();
void sub_1F7770(type_3E7D08 *arg_0);
void sub_1F77D0(RwCamera *arg_0, bool arg_4);
// Gives dword_42D254, the widget factory's log file name, as an int (the widget factory reads it
// and does nothing with it).
extern const RwChar *dword_42D254;
RwInt32 sub_1F8000();

// A border (off_3E6D0C, 0xE4 bytes; its type's name is "border"): a frame
// of quads around the rectangle unk_D0 (arg_4 set: a plain one), and a
// quad (unk_20, drawn once set over the rectangle arg_0 by sub_1E0400).
struct type_3E6D0C : type_3E7D08
{
    ::type_1F5A50 unk_0C;       // its frame's quads (a text page's array)
    type_1EEAD0 unk_20;
    type_1E0330_rect unk_D0;
    RwUInt8 unk_E0;

    type_3E6D0C(const type_1E0330_rect &arg_0, RwInt32 arg_4, type_3E7D08 *arg_8);
    virtual ~type_3E6D0C();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0)
    {
        return (eEventWasHandled)1;
    }
    virtual bool vf_010()
    {
        return false;
    }
    virtual void vf_014(RwReal arg_0)
    {
    }
    virtual void vf_018(type_1E4130 *arg_0);
    virtual type_1E0330_rect vf_020();
    virtual void givenFocus()
    {
    }
    virtual void lostFocus()
    {
    }
    // Adds a quad (arg_0 to arg_C, colour arg_10); sets the quad over the
    // rectangle arg_0.
    void sub_1E0330(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwUInt32 arg_10);
    void sub_1E0400(const type_1E0330_rect *arg_0);
};

struct type_1C8DF0;
struct type_1C9590;
class cScopeValidator;
struct type_1C8DF0_104;

// What the registry holds (off_3E70B0, both slots pure): its kind (slot 0:
// 0 an action, 1 a value, 3 a text) and its destructor (slot 1, pure, with
// a body out of line at sub_1F00C0). Evidence for the destructor: the
// editbox's actions' vtable (off_3E7264) holds their deleting destructor in
// slot 1.
struct type_3E70B0
{
    type_3E70B0()
    {
    }
    virtual RwInt32 vf_000() = 0;
    virtual ~type_3E70B0() = 0;
};

// A widget's action or focus hook (off_3E7274): its kind (0: 0x1E4CB0,
// shared through /OPT:ICF), run (slot 2) and whether it can run (slot 3:
// yes, 0x2015D0). Its destructor is pure with a body out of line
// (sub_1E5260, in the editbox's unit).
struct type_1ED670_object : type_3E70B0
{
    virtual RwInt32 vf_000()
    {
        return 0;
    }
    virtual ~type_1ED670_object() = 0;
    // Its run and whether it can run (slots 2 and 3; pvf_ names, as a
    // widget that is also an action, the keyboard's key, has its own vf_008
    // and vf_00C).
    virtual void pvf_008() = 0;
    virtual bool pvf_00C()
    {
        return true;
    }
};

// Objects by name (a std::map; its code follows cCaret's): the one named
// arg_0 (0 for none), a named one added (0 when the name is taken),
// emptied, and how many there are.
typedef std::map<type_1C8A60, type_1ED670_object *> type_1E0F80_map;
struct type_1E0F80
{
    type_1E0F80_map unk_00;

    type_1E0F80();
    ~type_1E0F80();
    type_1ED670_object *sub_1E0FC0(const RwChar *arg_0);
    RwInt32 sub_1E1030(const RwChar *arg_0, type_1ED670_object *arg_4);
    void sub_1E1080();
    RwUInt32 sub_1E10A0();
};

// The objects the widgets refer to by id: the one with the id arg_0
// (sub_1ED670); the one with the id arg_0 if it is of the kind arg_4, into
// *arg_8 (a template, instantiated with the widgets that use it).
struct type_1ED670
{
    type_1ED670_object *sub_1ED670(RwInt32 arg_0);
    template <class T> void sub_1E0D50(RwInt32 arg_0, RwInt32 arg_4, T **arg_8);
};

// Defined here as the original header had it: every unit emits the instantiations it
// uses, and /OPT:ICF folds them into one (0x1E0D50).
template <class T> void type_1ED670::sub_1E0D50(RwInt32 arg_0, RwInt32 arg_4, T **arg_8)
{
    type_1ED670_object *var_4 = sub_1ED670(arg_0);

    if (var_4 && var_4->vf_000() == arg_4)
        *arg_8 = (T *)var_4;
    else
        *arg_8 = 0;
}

// A widget type's creator (off_3E7D94, all its slots pure; its constructor
// and destructor are out of line, sub_1F7A20 and sub_1F7A40): its name,
// a widget from the scope arg_0 under the parent arg_10 into *arg_14, and
// the values it reads, added to the validator arg_0.
struct type_3E7D94
{
    type_3E7D94();
    virtual ~type_3E7D94() = 0;
    virtual const RwChar *vf_004() = 0;
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14) = 0;
    virtual void vf_00C(cScopeValidator *arg_0) = 0;
    // Its validator (for the type named by slot 1), into *arg_0.
    void sub_1F7A70(cScopeValidator **arg_0);
};

// The border's creator (off_3E6D3C).
struct type_3E6D3C : type_3E7D94
{
    type_3E6D3C();
    virtual ~type_3E6D3C();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// The widgets' value definitions (static type_1C9590s at unk_5034xx to
// unk_503Cxx, built by the file's dynamic initializers), each given by a
// function of its own (unit_1E3430).
type_1C9590 *sub_1E34D0();
type_1C9590 *sub_1E34E0();
type_1C9590 *sub_1E34F0();
type_1C9590 *sub_1E3500();
type_1C9590 *sub_1E3510();
type_1C9590 *sub_1E3520();
type_1C9590 *sub_1E3530();
type_1C9590 *sub_1E3540();
type_1C9590 *sub_1E3550();
type_1C9590 *sub_1E3560();
type_1C9590 *sub_1E3570();
type_1C9590 *sub_1E3580();
type_1C9590 *sub_1E3590();
type_1C9590 *sub_1E35A0();
type_1C9590 *sub_1E35B0();
type_1C9590 *sub_1E35C0();
type_1C9590 *sub_1E35D0();
type_1C9590 *sub_1E35E0();
type_1C9590 *sub_1E35F0();
type_1C9590 *sub_1E3600();
type_1C9590 *sub_1E3610();
type_1C9590 *sub_1E3620();
type_1C9590 *sub_1E3630();
type_1C9590 *sub_1E3740();
type_1C9590 *sub_1E3750();
type_1C9590 *sub_1E3760();
type_1C9590 *sub_1E3770();
type_1C9590 *sub_1E3780();
type_1C9590 *sub_1E3790();
// The validators of the values every widget and every selectable widget
// reads (built on first use by sub_1E3640, byte_503500 set once built).
void sub_1E3640();
const cScopeValidator &sub_1E3700();
const cScopeValidator &sub_1E3720();

// A compiled-out check of arg_0 with the message arg_4 (empty, 0x1F7A60;
// its argument types fold together).
void sub_1F7A60(const void *arg_0, const RwChar *arg_4);
void sub_1F7A60(RwInt32 arg_0, const RwChar *arg_4);
void sub_1F7A60(RwInt32 arg_0, RwInt32 arg_4);

// The object of the kind arg_8 whose id is the value arg_4 of the scope
// arg_0, from the registry arg_C, into *arg_10: 1 when found, 2 when not,
// 0 when the scope has no such value (a template, instantiated with the
// widgets that use it).
template <class T> RwInt32 sub_1E0CB0(type_1C8DF0 *arg_0, type_1C9590 *arg_4, RwInt32 arg_8, type_1ED670 *arg_C,
                                      T **arg_10);

// A selectable widget's look (the value arg_4 of the scope arg_0, looked up
// among the looks arg_4) into *arg_8; its rectangle ("position", or else a
// corner and a size in the look's texture's pixels); whether it is not
// plain; and its hooks into the registry arg_4 (for the widget's two
// interfaces). The looks and the look are typed as integers and a string
// here, as the creators pass them (1 when read, 2 when not found).
struct type_3E75E8;
struct type_3E76E4;
RwInt32 sub_1F7D80(type_1C8DF0 *arg_0, RwInt32 arg_4, const RwChar **arg_8);
RwInt32 sub_1F7B10(type_1C8DF0 *arg_0, const RwChar *arg_4, type_1E0330_rect *arg_8);
bool sub_1F7FE0(type_1C8DF0 *arg_0);
RwInt32 sub_1F7CC0(type_1C8DF0 *arg_0, type_1ED670 *arg_4, type_3E75E8 *arg_8);
RwInt32 sub_1F7DB0(type_1C8DF0 *arg_0, type_1ED670 *arg_4, type_3E76E4 *arg_8);
// The registry's objects of kinds 4 and 5, of which only this much is known:
// what uses them (unk_04), set by sub_1E7540 (a setter shared through
// /OPT:ICF), a selectable widget's rectangle interface (kind 4) or its third
// interface (kind 5). Named for their readers.
struct type_1F7CC0_hook : type_3E70B0
{
    type_3E75E8 *unk_04;

    void sub_1E7540(type_3E75E8 *arg_0);
};
struct type_1F7DB0_hook : type_3E70B0
{
    type_3E76E4 *unk_04;

    void sub_1E7540(type_3E76E4 *arg_0);
};

// The image library the looks' images come from (type_1ECCE0, below).
struct type_1ECCE0;

// One state of a look: its texture rectangle (unk_2C) and texture (unk_3C).
// Inline accessors with no addresses, named for their fields. Evidence: the
// look (sub_1E37E0, sub_1E3950) keeps the state in a slot of its own before
// reading each.
struct type_1E3BA0_state
{
    RwUInt8 unk_00[0x2C];
    type_1E0330_rect unk_2C;
    type_1ECCE0 *unk_3C;

    const type_1E0330_rect &get_unk_2C() const
    {
        return unk_2C;
    }
    type_1ECCE0 *get_unk_3C() const
    {
        return unk_3C;
    }
};

// A look's six states (sub_1E3BA0, from arg_0 and the kind arg_4; the state
// arg_0, sub_1E3BF0) and its kind (unk_18: 1 moves only the texture
// rectangle's corner, by twice the texture's offsets, and draws filtered).
// sub_1E3C10 fills the missing states from the others, sub_1E3D70 giving
// the first of arg_0 to arg_10 that is set.
struct type_1E3BA0
{
    type_1E3BA0_state *unk_00[6];
    RwInt32 unk_18;

    type_1E3BA0(type_1E3BA0_state *const *arg_0, RwInt32 arg_4);
    // Empty and out of line (pDtor, folded by /OPT:ICF): the looks'
    // libraries (sub_1EF560) destroy their temporary look with it.
    ~type_1E3BA0();
    type_1E3BA0_state *sub_1E3BF0(RwInt32 arg_0);
    // An inline accessor with no address, named for its field (sub_1E37E0
    // and sub_1E3950 read it through a slot of its own).
    RwInt32 get_unk_18() const
    {
        return unk_18;
    }
};
void sub_1E3C10(type_1E3BA0_state **arg_0);
// A look given to a widget by name (off_3E73A8, 8 bytes; a registry
// object): the look set (sub_1E7510) is handed to the widget it is bound to
// (unk_04, its slot 0).
struct type_1E7490 : type_3E70B0
{
    struct type_1E7490_target
    {
        virtual void vf_000(type_1E3BA0 *arg_0) = 0;
    } *unk_04;

    type_1E7490();
    // Its kind (slot 0, shared through /OPT:ICF at 0xA17A0).
    virtual RwInt32 vf_000();
    virtual ~type_1E7490();
    void sub_1E7510(type_1E3BA0 *arg_0);
    // Binds it to the widget arg_0 (sub_1E7540).
    void sub_1E7540(type_1E7490_target *arg_0);
};
// The looks' states' names ("normal", "highlight", "highlightalt",
// "disabled", "dishighlight" and "pressing"), and a state's index by its
// name (6 for none).
const RwChar *sub_1F80C0();
const RwChar *sub_1F80D0();
const RwChar *sub_1F80E0();
const RwChar *sub_1F80F0();
const RwChar *sub_1F8100();
const RwChar *sub_1F8110();
RwInt32 sub_1F8120(const RwChar *arg_0);
type_1E3BA0_state *sub_1E3D70(type_1E3BA0_state *arg_0, type_1E3BA0_state *arg_4, type_1E3BA0_state *arg_8,
                              type_1E3BA0_state *arg_C, type_1E3BA0_state *arg_10);
// The validator of a look's values (built on first use) and one of them.
const cScopeValidator *sub_1E3CD0();
type_1C9590 *sub_1E3D60();

// A selectable widget's look (0xCC bytes; sub_1E37A0 builds it from the
// look arg_0): its quad (unk_00), rebuilt when it changes (unk_C8, by
// sub_1E37E0) from the state's texture rectangle; its rectangle (set by
// sub_1E3A30, given by sub_1E3B60), its state (set by sub_1E3B20, given by
// sub_1E3B80), drawn by sub_1E3950; sub_1E3A00 gives it another look. Its
// destructor only calls a member's (0x39440, folded).
struct type_1E37A0
{
    type_1EEAD0 unk_00;
    type_1E3BA0 *unk_B0;
    RwInt32 unk_B4;
    type_1E0330_rect unk_B8;
    bool unk_C8;

    type_1E37A0(type_1E3BA0 *arg_0);
    ~type_1E37A0();
    void sub_1E37E0(type_1E4130 *arg_0);
    void sub_1E3950(type_1E4130 *arg_0);
    void sub_1E3A00(type_1E3BA0 *arg_0);
    void sub_1E3A30(const type_1E0330_rect *arg_0);
    void sub_1E3B20(RwInt32 arg_0);
    const type_1E0330_rect *sub_1E3B60();
    RwInt32 sub_1E3B80();
};

// The pad's button events waiting (0x104 bytes, sub_1E7560): up to 32 and
// their count; one added (sub_1E75B0).
struct type_1E7560
{
    cStateChange unk_00[32];
    RwUInt32 unk_100;

    type_1E7560();
    // Empty and out of line (pDtor, folded by /OPT:ICF): the in-game menus'
    // loop (sub_1FBE70) destroys its queue with it.
    ~type_1E7560();
    void sub_1E75B0(const cStateChange &arg_0);
    // Whether it holds an event; the first taken out.
    bool sub_1E75F0();
    cStateChange sub_1E7610();
};

// The pad's buttons held (sub_1EE900: the bits arg_0, the rest cleared) and
// a button's bit (sub_1EE930). The events for the buttons that differ from
// those held in arg_0, into arg_4 (sub_1EE940: a button whose bit is clear
// here is pressed there); the bits (sub_1EE9D0, an out-of-line getter
// shared through /OPT:ICF).
struct type_1EE900
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
    RwUInt32 unk_08;

    type_1EE900(RwUInt32 arg_0);
    // Cleared (out of line; /OPT:ICF shares it with two lookups' constructors).
    type_1EE900();
    void sub_1EE940(const type_1EE900 *arg_0, type_1E7560 *arg_4);
    RwUInt32 sub_1EE9D0() const;
};
RwUInt32 sub_1EE930(RwInt32 arg_0);

// How the pad's controls make buttons (unk_42CE80, to the button 14): the
// button (unk_00), the control (unk_04), how (unk_08: 0 pressed, 1 over
// half, 2 under minus half, with the control unk_0C under half either way).
struct type_42CE80
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};
extern type_42CE80 unk_42CE80[];

// A pad (the pad arg_0, sub_1E3F50 into *arg_4: 2 when there is one
// already): the buttons its controls make (sub_1E3DD0). Its constructor is
// out of line and folded (/OPT:ICF) into 0x12A1B0; its destructor clears
// its entry in unk_503E8C.
struct type_1E3DB0
{
    RwInt32 unk_00;

    type_1E3DB0(RwInt32 arg_0);
    ~type_1E3DB0();
    type_1EE900 sub_1E3DD0();
    // Whether it can be read: always (folded by /OPT:ICF into 0x2015D0).
    bool sub_2015D0();
};
RwInt32 sub_1E3F50(RwInt32 arg_0, type_1E3DB0 **arg_4);

// A selectable widget's second and third interfaces (off_3E75E8, whose
// destructor is out of line, sub_1EEA10; off_3E76E4): its rectangle and
// whether it is hidden; one more slot.
struct type_3E75E8
{
    virtual ~type_3E75E8();
    virtual const type_1E0330_rect *pvf_004() = 0;
    virtual void pvf_008(const type_1E0330_rect *arg_0) = 0;
    virtual bool pvf_00C() = 0;
    virtual void pvf_010(bool arg_0) = 0;
    // Moves its rectangle to (arg_0, arg_4), keeping its size.
    void sub_1EEA30(RwUInt32 arg_0, RwUInt32 arg_4);
};
struct type_3E76E4
{
    virtual void pvf_000(RwInt32 arg_0) = 0;
};

// A selectable widget (off_3E76B4, off_3E76A0 and off_3E769C; its
// constructor and destructor are out of line, sub_1EFDA0 and sub_1EFEA0,
// the destructor pure: its vtable's slot 0 is _purecall):
// its look (unk_14, from the texture name arg_0 over the rectangle arg_4)
// and whether it is hidden. It sets and gives the look's state
// (sub_1EFFA0, sub_1EFFC0).
struct type_3E76B4 : type_3E7D08, type_3E75E8, type_3E76E4
{
    type_1E37A0 *unk_14;
    bool unk_18;

    type_3E76B4(const RwChar *arg_0, const type_1E0330_rect *arg_4, type_3E7D08 *arg_8);
    virtual ~type_3E76B4() = 0;
    virtual void vf_018(type_1E4130 *arg_0);
    virtual type_1E0330_rect vf_020();
    virtual const type_1E0330_rect *pvf_004();
    virtual void pvf_008(const type_1E0330_rect *arg_0);
    virtual bool pvf_00C();
    virtual void pvf_010(bool arg_0);
    virtual void pvf_000(RwInt32 arg_0);
    void sub_1EFFA0(RwInt32 arg_0);
    RwInt32 sub_1EFFC0();
};

// A button (off_3E6D70, 0x2C bytes; its type named "button"): run (its
// action, unk_1C) when released after being pressed, told of the focus
// coming and going (unk_20, unk_24), and always selectable when unk_28 is
// set. Its look's state: 0 idle, 1 focused, 3 disabled, 4 disabled and
// focused, 5 pressed.
struct type_3E6D70 : type_3E76B4
{
    type_1ED670_object *unk_1C;
    type_1ED670_object *unk_20;
    type_1ED670_object *unk_24;
    bool unk_28;

    type_3E6D70(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1ED670_object *arg_C,
                type_1ED670_object *arg_10, type_1ED670_object *arg_14, type_3E7D08 *arg_18);
    virtual ~type_3E6D70();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual bool vf_010();
    virtual void vf_014(RwReal arg_0);
    virtual void givenFocus();
    virtual void lostFocus();
    // Whether its action can run and it is not hidden.
    bool sub_1E0930();
};

// The caret (off_3E6E20, off_3E6E0C and off_3E6E08; named by its traces,
// \COD\SHARED\UI\cCaret.cpp): a selectable widget that blinks, shown
// (unk_1C) for unk_20 seconds (0.5) and hidden as long, its time in unk_24.
// Its focus and event handlers only report being called.
class cCaret : public type_3E76B4
{
public:
    bool unk_1C;
    RwReal unk_20;
    RwReal unk_24;

    cCaret(const RwChar *arg_0, const type_1E0330_rect *arg_4, type_3E7D08 *arg_8);
    virtual ~cCaret();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual bool vf_010()
    {
        return false;
    }
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void givenFocus();
    virtual void lostFocus();
};

// A font's character as its file holds it: its code, its advance, its
// texture rectangle's corners (unk_08 to unk_0E) and its offset (unk_12).
struct type_1E2250_entry
{
    RwUInt16 unk_00;
    RwUInt8 unk_02;
    RwUInt8 unk_03[5];
    RwUInt16 unk_08;
    RwUInt16 unk_0A;
    RwUInt16 unk_0C;
    RwUInt16 unk_0E;
    RwUInt8 unk_10[2];
    RwInt16 unk_12;
};

// Half a texel of a texture arg_0 wide, and the texture rectangle of the
// texel rectangle (arg_0, arg_4)-(arg_8, arg_C) in a texture arg_10 by
// arg_14 (texel centres).
RwReal sub_1E2160(RwReal arg_0);
type_1E0330_rect sub_1E2180(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C, RwReal arg_10,
                            RwReal arg_14);

// A font's glyph (0x18 bytes): its texture rectangle, code, width, height,
// offset and advance (from its entry arg_0 in a texture arg_4 by arg_8;
// copied under the code arg_4; empty). Its destructor is empty and out of
// line (pDtor, folded): the font destroys its glyph temporaries and array
// through it.
struct type_1E2250
{
    type_1E0330_rect unk_00;
    RwUInt16 unk_10;
    RwUInt8 unk_12;
    RwUInt8 unk_13;
    RwUInt8 unk_14;
    RwUInt8 unk_15;

    type_1E2250(const type_1E2250_entry *arg_0, RwReal arg_4, RwReal arg_8);
    type_1E2250(const type_1E2250 &arg_0, RwUInt16 arg_4);
    type_1E2250();
    ~type_1E2250();
    // Inline accessors with no addresses, named for their fields. Evidence:
    // the copy under another code (sub_1E22F0) reads each byte through a
    // slot of its own, and the font's glyph search (sub_1E5940) the code.
    RwUInt16 get_unk_10() const
    {
        return unk_10;
    }
    RwUInt8 get_unk_12() const
    {
        return unk_12;
    }
    RwUInt8 get_unk_13() const
    {
        return unk_13;
    }
    RwUInt8 get_unk_14() const
    {
        return unk_14;
    }
    RwUInt8 get_unk_15() const
    {
        return unk_15;
    }
};

// A text widget's text (off_3E7A18, 0x9C bytes, sub_1F1420: in the font set
// arg_0 over the rectangle arg_4, aligned by arg_8, placed by arg_C): its four
// texture pages (unk_04), the text (unk_54), the font set (unk_70: a font and
// colour per state), its rectangle (unk_74, through the interface's slots),
// the laid-out text's top (unk_84: 0, or centred when unk_94 is 1), the
// highlight's phase (unk_88, 0 to 49), its state (unk_8C: state 1 pulses
// between its colour and state 0's), its alignment (unk_90), hidden (unk_98)
// and whether it is shown whole (unk_99, else cut to fit with the ellipsis).
// Laid out by sub_1F15C0, drawn by sub_1F1B10, told of the focus
// (sub_1F1AA0, sub_1F1AD0), its text set by sub_1F1D10 and sub_1F1D70, its
// state by sub_1F1E00, its alignment by sub_1F20E0 and its whole flag by
// sub_1F2410; a text's width in its font (sub_1F1ED0) and the text cut to
// fit (sub_1F2110).
struct type_1F1420 : type_3E75E8
{
    type_1F5A50 unk_04[4];
    type_1CB670 unk_54;
    type_1E6350 *unk_70;
    type_1E0330_rect unk_74;
    RwInt32 unk_84;
    RwUInt32 unk_88;
    RwInt32 unk_8C;
    RwInt32 unk_90;
    RwInt32 unk_94;
    bool unk_98;
    bool unk_99;

    type_1F1420(RwInt32 arg_0, const type_1E0330_rect *arg_4, RwUInt32 arg_8, RwInt32 arg_C);
    virtual ~type_1F1420();
    virtual const type_1E0330_rect *pvf_004();
    virtual void pvf_008(const type_1E0330_rect *arg_0);
    virtual bool pvf_00C();
    virtual void pvf_010(bool arg_0);
    void sub_1F15C0();
    void sub_1F1AA0();
    void sub_1F1AD0();
    void sub_1F1B10(type_1E4130 *arg_0);
    void sub_1F1D10(const type_1A5EA0 &arg_0);
    void sub_1F1D70(const RwChar *arg_0);
    void sub_1F1E00(RwInt32 arg_0);
    RwUInt32 sub_1F1ED0(const RwChar *arg_0, RwInt32 arg_4);
    void sub_1F20E0(RwInt32 arg_0);
    type_1CB670 sub_1F2110();
    void sub_1F2410(bool arg_0);
};

// The pad's held-button repeat (unk_504210, built by sub_1EF070 before
// main): the time held (unk_00), whether it runs (unk_04: sub_1EF160, stopped
// and cleared by sub_1EF140, started by sub_1EF120) and unk_05 (cleared when
// built, set only once already set). Its step by the time passed (sub_1EF090:
// whether it fires, every 0.25 s, dword_42D0DC; every 0.5 s, dword_42D0D8,
// with unk_05) and the steps held past the first 0.5 s (sub_1EF180).
struct type_1EF160
{
    RwReal unk_00;
    bool unk_04;
    bool unk_05;
    RwUInt8 unk_06[2];
    // Which way the pad's repeat moves a list box (1 down; the list box
    // sets it).
    bool unk_08;

    type_1EF160();
    // Empty, out of line: folded (/OPT:ICF) into pDtor (0x1E41C0); the
    // exit function of unk_504210 (0x30F010) calls it.
    ~type_1EF160();
    bool sub_1EF160();
    void sub_1EF140();
    void sub_1EF120();
    bool sub_1EF090(RwReal arg_0);
    RwInt32 sub_1EF180();
};
extern type_1EF160 unk_504210;
// A 4 by 4 texture raster, made on first use (dword_504370; sub_22A460
// draws with it).
RwRaster *sub_1EF040();

// A value a widget changes (off_3E7098, a registry object of kind 1; its
// constructor and destructor are out of line, sub_1E3450 and sub_1E3430):
// up and down by arg_0 (slots 2 and 3), whether it can change (slot 4:
// yes), shown again (slot 5), and the widget that shows it (unk_04, set by
// sub_1E34A0).
struct type_3E6F74;
struct type_1E34A0 : type_3E70B0
{
    type_3E76B4 *unk_04;

    type_1E34A0();
    virtual ~type_1E34A0() = 0;
    virtual RwInt32 vf_000()
    {
        return 1;
    }
    virtual void vf_008(RwUInt32 arg_0) = 0;
    virtual void vf_00C(RwUInt32 arg_0) = 0;
    virtual bool vf_010()
    {
        return true;
    }
    virtual void vf_014() = 0;
    void sub_1E34A0(type_3E76B4 *arg_0);
    // Whether a widget shows it: an inline with no address, named for what
    // it gives. Evidence: the integer value's members (sub_1E7840,
    // sub_1E7A20, sub_1E7A80) test it through setne and a test.
    bool has_unk_04()
    {
        return unk_04 != 0;
    }
    // The combobox that shows it (unk_04; out of line and folded through
    // /OPT:ICF into 0x1E3480).
    type_3E6F74 *sub_1E3480();
};

// Whether a combobox's value is being stepped up (the last press).
extern bool byte_503318;

// A combobox (off_3E6F74, off_3E6F60 and off_3E6F5C, 0x100 bytes; its type
// named "combobox"): a value (unk_1C) stepped up and down by the pad's
// buttons for its orientation (unk_24), its text (unk_28: unk_C8, the
// value, then unk_E4) and a caption (unk_C4); unk_20 set keeps it
// selectable.
struct type_3E6F74 : type_3E76B4
{
    type_1E34A0 *unk_1C;
    bool unk_20;
    RwInt32 unk_24;
    type_1F1420 unk_28;
    type_1F1420 *unk_C4;
    type_1CB670 unk_C8;
    type_1CB670 unk_E4;

    type_3E6F74(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1E34A0 *arg_C,
                const std::string &arg_10, const std::string &arg_14, RwInt32 arg_18, const type_1A5EA0 *arg_1C,
                const type_1E0330_rect *arg_20, const RwUInt32 *arg_24, RwInt32 arg_28, RwUInt32 arg_2C,
                RwInt32 arg_30, type_3E7D08 *arg_34);
    virtual ~type_3E6F74();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual bool vf_010();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void givenFocus();
    virtual void lostFocus();
    // Shows the value arg_0 between its prefix and suffix; whether its value
    // can change; its state (and its texts').
    void sub_1E2A50(const type_1A5EA0 &arg_0);
    bool sub_1E2B10();
    void sub_1E2B60(RwInt32 arg_0);
};

// The combobox's creator (off_3E6FA4).
struct type_3E6FA4 : type_3E7D94
{
    type_3E6FA4();
    virtual ~type_3E6FA4();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// A static image (off_3E7700, off_3E76EC and off_3E76E8; named by its
// traces, \COD\SHARED\UI\cStaticImage.cpp): a selectable widget that
// takes no focus and no events; its focus and event handlers only report
// being called (level 3).
class cStaticImage : public type_3E76B4
{
public:
    cStaticImage(const RwChar *arg_0, const type_1E0330_rect *arg_4, type_3E7D08 *arg_8);
    virtual ~cStaticImage();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual bool vf_010()
    {
        return false;
    }
    virtual void vf_014(RwReal arg_0)
    {
    }
    virtual void givenFocus();
    virtual void lostFocus();
};

// The static image's creator (off_3E7830; its type's name is "image").
struct type_3E7830 : type_3E7D94
{
    type_3E7830();
    virtual ~type_3E7830();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// The button's creator (off_3E6DA0).
struct type_3E6DA0 : type_3E7D94
{
    type_3E6DA0();
    virtual ~type_3E6DA0();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// The factory's readers of a scope's values (unit_1F7A60 on): the texture
// name of the value arg_4 for arg_8 into *arg_C, the widget's font for arg_4
// into *arg_8, and the font of the value arg_4 for arg_8 into *arg_C (1 when
// read). Evidence for the fonts: the editbox reads "fontkeyboard" and
// "fontkeyboardedit" through sub_1F7F40 and passes them to its keyboard.
RwInt32 sub_1F7EA0(type_1C8DF0 *arg_0, const type_1C9590 *arg_4, RwInt32 arg_8, const RwChar **arg_C);
RwInt32 sub_1F7E70(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 *arg_8);
RwInt32 sub_1F7F40(type_1C8DF0 *arg_0, const type_1C9590 *arg_4, RwInt32 arg_8, RwUInt32 *arg_C);

// What a text source tells a text field (off_3E7258, all its slots pure;
// its destructor has a body out of line, sub_1F2900): the state arg_0
// (slot 1) and the text arg_0 (slot 2).
struct type_3E7258
{
    virtual ~type_3E7258() = 0;
    virtual void pvf_004(RwInt32 arg_0) = 0;
    virtual void pvf_008(const type_1A5EA0 &arg_0) = 0;
};

// A text a widget edits (a registry object of kind 3): what shows it
// (unk_04, set by sub_1E7540, an out-of-line setter shared through
// /OPT:ICF) and the text (unk_08, set by sub_1F28C0, which tells it). The
// text is a type_1CB670: the constructor (sub_1F2790) calls its out-of-line
// default constructor (sub_E87E0); the setter assigns through the base.
struct type_1F28C0 : type_3E70B0
{
    type_3E7258 *unk_04;
    type_1CB670 unk_08;
    RwInt32 unk_24;

    // Its constructor (sub_1F2790) and destructor (sub_1F2830); it tells
    // what shows it of its text (sub_1F2890).
    type_1F28C0();
    virtual ~type_1F28C0();
    virtual RwInt32 vf_000()
    {
        return 3;
    }
    void sub_1E7540(type_3E7258 *arg_0);
    void sub_1F28C0(const type_1A5EA0 &arg_0);
    void sub_1F2890();
};

// A static text (off_3E7850 and off_3E7840, 0xAC bytes; named by its
// traces, \COD\SHARED\UI\cStaticText.cpp): a widget showing a text
// (unk_10), told its state and text by a text source (its second interface)
// and optionally bound to one (the text arg_C, sub_1F0410). It takes no focus
// and no events (its handlers only report being called); its own slots
// 12 to 15 give and set the text's rectangle and whether it is hidden.
class cStaticText : public type_3E7D08, public type_3E7258
{
public:
    type_1F1420 unk_10;

    cStaticText(RwInt32 arg_0, const type_1E0330_rect *arg_4, RwUInt32 arg_8, type_1F28C0 *arg_C,
                type_3E7D08 *arg_10);
    virtual ~cStaticText();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual bool vf_010()
    {
        return false;
    }
    virtual void vf_014(RwReal arg_0)
    {
    }
    virtual void vf_018(type_1E4130 *arg_0);
    virtual type_1E0330_rect vf_020();
    virtual void givenFocus();
    virtual void lostFocus();
    virtual const type_1E0330_rect *vf_030();
    virtual void vf_034(const type_1E0330_rect *arg_0);
    virtual bool vf_038();
    virtual void vf_03C(bool arg_0);
    virtual void pvf_004(RwInt32 arg_0);
    virtual void pvf_008(const type_1A5EA0 &arg_0);
};

// A text button (off_3E79B4, off_3E79A0, off_3E799C and off_3E7990, 0xCC
// bytes; its type named "textbutton"): a button with a text (unk_30, over
// the button's rectangle) that is its text source's (its interface at +0x2C),
// bound to the text arg_1C when there is one, else showing arg_18. The text
// follows the button's state, rectangle and focus, and is drawn over it
// unless the button is hidden.
struct type_3E79B4 : type_3E6D70, type_3E7258
{
    type_1F1420 unk_30;

    type_3E79B4(const RwChar *arg_0, const type_1E0330_rect *arg_4, bool arg_8, type_1ED670_object *arg_C,
                type_1ED670_object *arg_10, type_1ED670_object *arg_14, const type_1A5EA0 &arg_18,
                type_1F28C0 *arg_1C, RwInt32 arg_20, RwUInt32 arg_24, type_3E7D08 *arg_28);
    virtual ~type_3E79B4();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void pvf_008(const type_1E0330_rect *arg_0);
    virtual void pvf_004(RwInt32 arg_0)
    {
    }
    virtual void pvf_008(const type_1A5EA0 &arg_0);
};

// The static text's creator (off_3E7A00; its type's name is "text").
struct type_3E7A00 : type_3E7D94
{
    type_3E7A00();
    virtual ~type_3E7A00();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// A key of the on-screen keyboard (off_3E7C30, off_3E7C1C, off_3E7C18,
// off_3E7C0C and off_3E7BFC; 0xD0 bytes): a text button showing arg_8 in
// the font arg_C that runs the action arg_10, or else itself, an action
// that does nothing. It takes every event.
struct type_3E7C30 : type_3E79B4, type_1ED670_object
{
    type_3E7C30(const RwChar *arg_0, const type_1E0330_rect *arg_4, const type_1A5EA0 &arg_8, RwInt32 arg_C,
                type_1ED670_object *arg_10, type_3E7D08 *arg_14);
    virtual ~type_3E7C30();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void pvf_008()
    {
    }
};

// The text button's creator (off_3E79E4).
struct type_3E79E4 : type_3E7D94
{
    type_3E79E4();
    virtual ~type_3E79E4();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// A text field (off_3E7BCC, off_3E7BB8 and off_3E7BB4, 0xF0 bytes;
// sub_1F4D00 builds it from the texture names arg_0 and arg_4 (its caret's),
// the font arg_8, the rectangles arg_C and arg_10 (its caret's), its longest
// text arg_14 and the actions for enter (arg_18) and cancel (arg_1C)): its
// text (unk_1C: the string given by sub_1F5230, set from arg_0 by
// sub_1F51B0, cut to arg_0 by sub_1F5250), caret (unk_BC), length (unk_E4,
// given by sub_CB0A0, an out-of-line getter shared through /OPT:ICF), and a
// key typed (sub_1F52C0).
struct type_3E7BCC : type_3E76B4
{
    type_1F1420 unk_1C;
    RwInt32 unk_B8;
    cCaret unk_BC;
    RwUInt32 unk_E4;
    type_1ED670_object *unk_E8;
    type_1ED670_object *unk_EC;

    type_3E7BCC(const RwChar *arg_0, const RwChar *arg_4, RwInt32 arg_8, const type_1E0330_rect *arg_C,
                const type_1E0330_rect *arg_10, RwInt32 arg_14, type_1ED670_object *arg_18,
                type_1ED670_object *arg_1C, type_3E7D08 *arg_20);
    virtual ~type_3E7BCC();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual bool vf_010()
    {
        return false;
    }
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void givenFocus();
    virtual void lostFocus();
    // Its caret placed after the text's first unk_E4 characters (sub_1F5070);
    // whether it may be entered (sub_1F5800: its enter action's check, yes
    // without one); its longest text (sub_1F5840).
    void sub_1F5070();
    void sub_1F51B0(const RwChar *arg_0);
    const type_1A5EA0 &sub_1F5230();
    // Its text's length: an inline with no address. Evidence: the key
    // handler's delete case (sub_1F52C0) tests it with two slots fewer
    // than a direct size() check.
    RwUInt32 text_length()
    {
        return sub_1F5230().size();
    }
    void sub_1F5250(RwUInt32 arg_0);
    void sub_1F52C0(RwUInt32 arg_0);
    bool sub_1F5800();
    RwInt32 sub_1F5840();
    RwInt32 sub_CB0A0();
};

struct type_1F5D70;

// The widgets that take the pad from the others, a stack of up to four
// (off_3E73C8; dword_50420C, set by sub_1E7CE0 and given by sub_1E7CF0):
// whether arg_0 is on it (sub_1E7D00), arg_0 pushed (sub_1E7D30) and taken
// out (sub_1E7D90), the top (sub_1E7FE0), how many (sub_1E80D0). The top
// gets the events and focus; the others are drawn below a shade unless
// unk_21 is set (sub_1E8110; unk_20, sub_1E80F0). Its destructor is
// implicit; its copy sits in unit_1C5700 (0x1C5740, with the global).
struct type_1E7CF0 : type_3E7D08
{
    ::type_1E61A0<type_3E7D08 *, 4> unk_0C;
    bool unk_20;
    bool unk_21;

    type_1E7CF0();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual bool vf_010()
    {
        return true;
    }
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual type_1E0330_rect vf_020();
    virtual void givenFocus();
    virtual void lostFocus();
    bool sub_1E7D00(type_3E7D08 *arg_0);
    void sub_1E7D30(type_3E7D08 *arg_0);
    void sub_1E7D90(type_3E7D08 *arg_0);
    type_3E7D08 *sub_1E7FE0();
    RwUInt32 sub_1E80D0();
    void sub_1E80F0(bool arg_0);
    void sub_1E8110(bool arg_0);
};
void sub_1E7CE0(type_1E7CF0 *arg_0);
type_1E7CF0 *sub_1E7CF0();

// An action calling its owner's methods (off_3E7264, over off_3E7274; a
// template over the owner, 0x18 bytes): run (unk_08) and whether it can
// run (unk_10), on unk_04. Its run and check are folded (/OPT:ICF) into
// 0x20E600 and 0x20E620.
template <class T> struct type_3E7264 : type_1ED670_object
{
    T *unk_04;
    void (T::*unk_08)();
    bool (T::*unk_10)();

    type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)());
    virtual ~type_3E7264();
    virtual void pvf_008();
    virtual bool pvf_00C();
};

// An action calling its owner's method with a word of its own (a template
// over the owner, 0x10 bytes; the instant action page's, off_3E88C4): run
// (unk_08) on unk_04 with unk_0C.
template <class T> struct type_3E88C4 : type_1ED670_object
{
    T *unk_04;
    void (T::*unk_08)(RwInt32);
    RwInt32 unk_0C;

    type_3E88C4(T *arg_0, void (T::*arg_4)(RwInt32), RwInt32 arg_8);
    virtual ~type_3E88C4();
    virtual void pvf_008();
};

struct type_3E7228;
// An editbox (off_3E7228, off_3E7214, off_3E7210 and off_3E7204, 0x138
// bytes; its type named "editbox"): a text field whose text is typed on the
// on-screen keyboard (unk_F4, open while unk_134 is set) and kept in a text
// (unk_F8); a hook run on enter (unk_130) and two actions over its methods
// (unk_100 for enter, unk_118).
struct type_3E7228 : type_3E7BCC, type_3E7258
{
    type_1F5D70 *unk_F4;
    type_1F28C0 *unk_F8;
    RwUInt8 unk_FC[4];
    type_3E7264<type_3E7228> unk_100;
    type_3E7264<type_3E7228> unk_118;
    type_1ED670_object *unk_130;
    bool unk_134;

    type_3E7228(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, const RwChar *arg_C, RwInt32 arg_10,
                RwUInt32 arg_14, RwUInt32 arg_18, const type_1E0330_rect *arg_1C, const type_1E0330_rect *arg_20,
                RwInt32 arg_24, type_1ED670_object *arg_28, type_1ED670_object *arg_2C, type_1F28C0 *arg_30,
                type_3E7D08 *arg_34);
    virtual ~type_3E7228();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual bool vf_010()
    {
        return true;
    }
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void pvf_004(RwInt32 arg_0);
    virtual void pvf_008(const type_1A5EA0 &arg_0);
    // Opens the keyboard on its text; whether it hides its text (no);
    // takes the key arg_0 and tells its text; its enter hook and whether it
    // can enter; an empty action (pDtor, folded).
    void sub_1E4980();
    bool sub_1E4AA0();
    void sub_1E4AB0(RwInt32 arg_0);
    void sub_1E4BB0();
    bool sub_1E4BE0();
    void pDtor();
};

// An image of the library (0x40 bytes, sub_1E7410): its name (at most 0x2B
// characters), texture rectangle (unk_2C) and library (unk_3C). Its
// destructor is empty and out of line (pDtor, folded).
struct type_1E7410
{
    RwChar unk_00[0x2C];
    type_1E0330_rect unk_2C;
    type_1ECCE0 *unk_3C;

    type_1E7410(type_1ECCE0 *arg_0, const type_1E0330_rect *arg_4, const RwChar *arg_8);
    ~type_1E7410();
};

// The name map (type_1E0F80) over objects of the type T: the insertion of arg_4 under the
// name arg_0 (out of line, shared through /OPT:ICF at 0x1EFCF0). The map itself is the
// name map's, not one per T: the image has one copy of its code (unit_1E0F80's), which
// every user calls, and its EH-bearing map members (_Buynode, _Insert) would not fold
// across objects. Its destructor is inline: expanded in its users' destructors, out of
// line (0x20E940) where they unwind.
template <class T> struct type_1EFCF0 : type_1E0F80
{
    ~type_1EFCF0()
    {
    }
    RwInt32 sub_1EFCF0(const RwChar *arg_0, T *arg_4);
    // The object named arg_0 (out of line, shared through /OPT:ICF at
    // 0x1ED670).
    T *sub_1ED670(const RwChar *arg_0);
};

// Defined here as the original header had them: every unit emits the instantiations it
// uses, and /OPT:ICF folds them (0x1EFCF0, 0x1ED670).
template <class T> T *type_1EFCF0<T>::sub_1ED670(const RwChar *arg_0)
{
    T *var_4 = (T *)sub_1E0FC0(arg_0);
    return var_4;
}

template <class T> RwInt32 type_1EFCF0<T>::sub_1EFCF0(const RwChar *arg_0, T *arg_4)
{
    return sub_1E1030(arg_0, (type_1ED670_object *)arg_4);
}

// The library's images by name, which it owns: the image *arg_4 taken
// under the name arg_0 (sub_1E7310), and all of them deleted (sub_1E7340,
// through sub_1E7360) when it goes.
struct type_1E72C0 : type_1EFCF0<type_1E7410>
{
    ~type_1E72C0();
    RwInt32 sub_1E7310(const RwChar *arg_0, type_1E7410 **arg_4);
    void sub_1E7340();
    void sub_1E7360();
};

// kujuUI's image library (off_3E7504, 0x40 bytes; counted, type_3E7314):
// its name (unk_08), texture (unk_24, which it owns), images by name
// (unk_28, read from the name's ".index" file by sub_1ED290, its "image"
// entries), the next library loaded (unk_34; the first is dword_504224)
// and half a texel (unk_38, unk_3C: the offsets its texture rectangles are
// moved by). The image named arg_0 (sub_1ED630); the texture's raster
// (sub_1ED650, passed on as a render state's value); the library named
// arg_0 among those loaded (sub_1ED220).
struct type_1ECCE0 : type_3E7314
{
    type_1A5EA0 unk_08;
    type_1EEEE0 *unk_24;
    type_1E72C0 unk_28;
    type_1ECCE0 *unk_34;
    RwReal unk_38;
    RwReal unk_3C;

    type_1ECCE0(const RwChar *arg_0, type_1EEEE0 **arg_4, type_1ECCE0 *arg_8);
    virtual ~type_1ECCE0();
    bool sub_1ED290();
    type_1E7410 *sub_1ED630(const RwChar *arg_0);
    RwInt32 sub_1ED650();
    static type_1ECCE0 *sub_1ED220(const RwChar *arg_0);
};
// Loads the texture named arg_0 into *arg_4 (whether it could); the
// library named arg_0, loaded when it is not yet; the values an ".index"
// file has.
bool sub_1ECDE0(const RwChar *arg_0, type_1EEEE0 **arg_4);
type_E8780<type_1ECCE0> sub_1ED040(const RwChar *arg_0);
const cScopeValidator *sub_1ED1E0();

// The looks' libraries (0x50 bytes; the interface's at +0xC8, sub_1F2EC0):
// the image libraries in use (unk_00, sub_1EF460 adds the one named arg_0:
// whether it loaded) and the looks (unk_44, sub_1EF560 builds one from the
// scope arg_0 and names it in arg_4: whether its images were all found).
// The image named arg_0 in any of the libraries (sub_1EF780).
struct type_1EF3A0
{
    ::type_1E61A0<type_E8780<type_1ECCE0>, 16> unk_00;
    std::list<type_1E3BA0> unk_44;

    type_1EF3A0();
    ~type_1EF3A0();
    bool sub_1EF460(const RwChar *arg_0);
    bool sub_1EF560(type_1C8DF0 *arg_0, type_1EFCF0<type_1E3BA0> *arg_4);
    type_1E7410 *sub_1EF780(const RwChar *arg_0);
};

// An integer value (off_3E73B0, 0x7C bytes): the value (unk_08) between
// the least and the greatest (unk_0C, unk_10), stepped by unk_14 (by unk_1C
// when held long), wrapping unless unk_20 is set; shown as unk_24 at the
// least (when not empty), else between the prefix unk_40 and suffix unk_5C;
// unk_78 told when it changes and asked whether it may. The value is set by
// sub_1E7BB0 and the greatest by sub_1E7BD0.
struct type_1E76A0 : type_1E34A0
{
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwInt32 unk_20;
    type_1CB670 unk_24;
    type_1CB670 unk_40;
    type_1CB670 unk_5C;
    type_1ED670_object *unk_78;

    type_1E76A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14,
                RwInt32 arg_18, const std::string &arg_1C, const std::string &arg_20, const std::string &arg_24,
                type_1ED670_object *arg_28);
    virtual ~type_1E76A0();
    virtual void vf_008(RwUInt32 arg_0);
    virtual void vf_00C(RwUInt32 arg_0);
    virtual bool vf_010();
    virtual void vf_014();
    void sub_1E7A80();
    void sub_1E7BB0(RwInt32 arg_0);
    void sub_1E7BD0(RwInt32 arg_0);
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: the host options (sub_201A70,
    // sub_201CD0) read their values through a slot each.
    RwInt32 get_unk_08()
    {
        RwInt32 r = unk_08;
        return r;
    }
};

// A container widget (off_3E7584, 0x1C bytes; built under the parent
// arg_0 by sub_1ED730, its destructor pure with a body out of line,
// sub_1ED7A0): its children (unk_0C; sub_1ED9D0 adds arg_0 last,
// sub_1ED9F0 first, sub_1EDBC0 makes room for arg_0; sub_1EDBE0 and
// sub_1EDC10 give their first and end), which it passes its
// slots 2, 3, 5 and 6 on to and whose rectangles it bounds (vf_020: about
// the screen's centre line, x = 320), and a slot of its own: 12 (vf_030,
// empty, called before its children are updated).
struct type_3E7584 : type_3E7D08
{
    std::vector<type_3E7D08 *> unk_0C;

    type_3E7584(type_3E7D08 *arg_0);
    virtual ~type_3E7584() = 0;
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual type_1E0330_rect vf_020();
    virtual void vf_030();
    void sub_1ED9D0(type_3E7D08 *arg_0);
    void sub_1ED9F0(type_3E7D08 *arg_0);
    void sub_1EDBC0(RwUInt32 arg_0);
    // Its children's first and end.
    std::vector<type_3E7D08 *>::iterator sub_1EDBE0();
    std::vector<type_3E7D08 *>::iterator sub_1EDC10();
};

// An action calling one method of its owner (off_3E7CE8, over off_3E7274; a
// template over the owner, 0xC bytes): runs unk_08 on unk_04 and can always
// run. Named for the keyboard's instance's vtable; its run is folded
// (/OPT:ICF) into 0x219F10.
template <class T> struct type_3E7CE8 : type_1ED670_object
{
    T *unk_04;
    void (T::*unk_08)();

    type_3E7CE8(T *arg_0, void (T::*arg_4)());
    virtual ~type_3E7CE8();
    virtual void pvf_008();
};

// The on-screen keyboard (off_3E7CB4, 0x18C bytes; a container widget): a
// text field (unk_98) over a grid of keys laid out from the table
// unk_42D140 (unk_184: 0 lower case, 1 upper, 2 symbols, 3 and 4 accented;
// codes above 11 are characters, the others the keys "Done" to ">" of the
// labels unk_42D0E8, a code repeated along a row making one wide key).
// The pad moves the focus (unk_178, unk_17C) and types, B cancels and
// releasing A on "Done" enters. Its state (unk_188: 0 open, 1 cancelled, 2
// entered), its text (sub_1F7310, set by sub_1F7370), its caret (set by
// sub_1F7390, given by sub_1F73B0), whether it may be entered (sub_1F6EF0)
// and a key typed on the pad (sub_1F73D0, which finds its key and layout).
struct type_1F5D70 : type_3E7584
{
    // A counted pointer that nothing here sets; its pointee is not known
    // (the font's instance stands in: the code is the same for any).
    type_E8780<type_1E5A60> unk_1C;
    RwUInt32 unk_20[6];
    const RwChar *unk_38;                 // the keys' arg_0
    const RwChar *unk_3C;                 // the text field's arg_0 and arg_4
    const RwChar *unk_40;
    type_3E7CE8<type_1F5D70> unk_44;      // cancel (sub_1F6BF0)
    type_3E7264<type_1F5D70> unk_50;      // enter (sub_1F6BC0, when sub_1F6EF0)
    // The character keys' (with room for one more), ">"'s (caret short of
    // the longest text) and "<" and "Backspace"'s (caret past the start)
    // actions: nothing to run, their checks enabling the keys.
    type_3E7264<type_1F5D70> unk_60;
    type_3E7264<type_1F5D70> unk_70;
    type_3E7264<type_1F5D70> unk_80;
    RwUInt32 unk_90;
    type_1ED670_object *unk_94;           // whether it may be entered
    type_3E7BCC *unk_98;
    type_3E79B4 *unk_9C[5][11];           // by row and column
    RwInt32 unk_178;
    RwInt32 unk_17C;
    bool unk_180;                         // shift (for one character)
    bool unk_181;                         // caps lock
    RwInt32 unk_184;
    RwInt32 unk_188;

    type_1F5D70(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, RwUInt32 arg_C, RwUInt32 arg_10,
                const type_1E0330_rect *arg_14, const type_1E0330_rect *arg_18, RwInt32 arg_1C,
                type_1ED670_object *arg_20, type_3E7D08 *arg_24);
    virtual ~type_1F5D70();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual bool vf_010()
    {
        return true;
    }
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void givenFocus();
    virtual void lostFocus()
    {
    }
    // An inline accessor with no address, named for its field. Evidence:
    // the editbox (sub_1E45D0) switches on it through the inline's return
    // slot.
    RwInt32 get_unk_188() const
    {
        return unk_188;
    }
    // The code of the key at row arg_0, column arg_4 in the current
    // layout: an inline with no address, named for what it gives. Evidence:
    // processEvent and the constructor read it through a byte return slot.
    RwUInt8 key_at(RwInt32 arg_0, RwInt32 arg_4) const;
    // The character keys' run: empty, folded (/OPT:ICF) into pDtor.
    void pDtor()
    {
    }
    // Enters (when it may be) and cancels.
    void sub_1F6BC0();
    void sub_1F6BF0();
    // Shift pressed; shift let go after a character; caps lock pressed;
    // the accent, symbol and alphabet keys: each changes the layout
    // (sub_1F6E20, true when it changed) and relabels the keys (sub_1F6FF0).
    void sub_1F6C10();
    void sub_1F6C50();
    void sub_1F6C80();
    void sub_1F6D70();
    void sub_1F6DB0();
    void sub_1F6DE0();
    bool sub_1F6E20(RwInt32 arg_0);
    // The character keys', ">"'s and "<"'s checks.
    bool sub_1F6E50();
    bool sub_1F6E90();
    bool sub_1F6ED0();
    bool sub_1F6EF0();
    void sub_1F6FF0();
    // Moves the focus to the key at column arg_0, row arg_4; the key there
    // (0 off the grid).
    void sub_1F7200(RwInt32 arg_0, RwInt32 arg_4);
    type_3E79B4 *sub_1F72D0(RwInt32 arg_0, RwInt32 arg_4);
    type_1A5EA0 sub_1F7310();
    void sub_1F7370(const RwChar *arg_0);
    void sub_1F7390(RwInt32 arg_0);
    RwInt32 sub_1F73B0();
    void sub_1F73D0(RwInt32 arg_0);
    // The layout with the key arg_0 (the layout arg_4 first), and the key's
    // column and row (-1 when none has it); whether layout arg_4 has it.
    RwInt32 sub_1F7450(RwUInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8, RwInt32 *arg_C);
    bool sub_1F7530(RwInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8, RwInt32 *arg_C);
};
// The keyboard's layouts, key widths (by code) and labels (by code, the
// localisation's keys).
extern RwUInt8 unk_42D140[][5][11];
extern RwInt32 unk_42D114[11];
extern const RwChar *unk_42D0E8[11];

// (Indexed flat within the layout: the row-then-column form adds the
// column last, where its callers add it before the row.)
inline RwUInt8 type_1F5D70::key_at(RwInt32 arg_0, RwInt32 arg_4) const
{
    return unk_42D140[unk_184][0][arg_0 * 11 + arg_4];
}

// A widget with nothing of its own (off_3E75B8, 0xC bytes; built under the
// parent arg_0 by sub_1EE870, its destructor out of line, sub_1EE8D0): the
// game's interface's root (sub_1FF260 builds one with no parent). It takes
// every event, has no rectangle (vf_020 leaves it unset) and does nothing.
struct type_3E75B8 : type_3E7D08
{
    type_3E75B8(type_3E7D08 *arg_0);
    virtual ~type_3E75B8();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0)
    {
        return (eEventWasHandled)1;
    }
    virtual bool vf_010()
    {
        return true;
    }
    virtual void vf_014(RwReal arg_0)
    {
    }
    virtual void vf_018(type_1E4130 *arg_0)
    {
    }
    virtual type_1E0330_rect vf_020();
    virtual void givenFocus()
    {
    }
    virtual void lostFocus()
    {
    }
};

// A link of a layout page (0xC bytes; sub_1F8040 builds the key from the
// widget arg_0 and the button arg_4, sub_1F8010 the link to arg_4): the
// widget, the widget the button leads to (unk_04, set by sub_1E7540 and
// given by sub_1E3480, out-of-line accessors shared through /OPT:ICF) and
// the button. Ordered by widget then button (sub_1F8070); its destructor
// is empty and out of line (pDtor, folded).
struct type_1F8040
{
    type_3E7D08 *unk_00;
    type_3E7D08 *unk_04;
    RwInt32 unk_08;

    type_1F8040(type_3E7D08 *arg_0, RwInt32 arg_4);
    type_1F8040(type_3E7D08 *arg_0, type_3E7D08 *arg_4, RwInt32 arg_8);
    ~type_1F8040();
    bool operator<(const type_1F8040 &arg_0) const;
    type_3E7D08 *sub_1E3480() const;
    void sub_1E7540(type_3E7D08 *arg_0);
    // Its widget and button: out-of-line getters shared through /OPT:ICF
    // (0x1EE9D0, 0xFB710), which its order calls on the other link.
    type_3E7D08 *sub_1EE9D0() const;
    RwInt32 sub_FB710() const;
};

// A layout page (off_3E73F8, 0x38 bytes; named by its traces'
// "\COD\SHARED\UI\cLayoutPage.cpp"): widgets moved between by the pad's
// buttons along its links (unk_1C; sub_1E8980 links arg_0 to arg_4 by the
// button arg_8), the widget with the focus (unk_28), the one it starts on
// or goes back to (unk_2C, set by sub_1E8A40 and kept on losing the focus
// when unk_34 is set, sub_1E8C30), and the button held (unk_30, 14 for
// none; it repeats with the pad's button repeat, unk_504210).
class cLayoutPage : public type_3E7584
{
public:
    std::set<type_1F8040> unk_1C;
    type_3E7D08 *unk_28;
    type_3E7D08 *unk_2C;
    RwInt32 unk_30;
    bool unk_34;

    cLayoutPage(type_3E7D08 *arg_0);
    virtual ~cLayoutPage();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual bool vf_010()
    {
        return true;
    }
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual void givenFocus();
    virtual void lostFocus();
    virtual void vf_030();
    virtual bool vf_034(type_3E7D08 *arg_0);
    // Moves the focus by the button arg_0 (0 when it moved or could).
    eEventWasHandled sub_1E8550(const cStateChange &arg_0);
    // Moves the focus on from a widget that cannot take it.
    void focusAvailableWidget();
    void sub_1E8980(type_3E7D08 *arg_0, type_3E7D08 *arg_4, RwInt32 arg_8);
    void sub_1E8A20(type_3E7D08 *arg_0);
    void sub_1E8A40(type_3E7D08 *arg_0);
    void sub_1E8B50(type_3E7D08 *arg_0);
    bool sub_1E8BB0();
    void sub_1E8C30(bool arg_0);
    type_3E7D08 *sub_1E8C50();
    // Whether a button is held: an inline with no address, named for what
    // it gives. Evidence: processEvent (sub_1E8470) tests it through setne
    // and a test.
    bool held()
    {
        return unk_30 != 14;
    }
};

struct type_3E7490;

// A list box's column (8 bytes): its width (unk_00) and its text's
// alignment (unk_04; 1 when built).
struct type_1ECA30_column
{
    RwUInt32 unk_00;
    RwInt32 unk_04;

    type_1ECA30_column()
    {
        unk_00 = 0;
        unk_04 = 1;
    }
};

// A list box's columns (off_3E74E0, a registry object of kind 2; its
// destructor is pure with a body, sub_1EC810): the list box (unk_04, set by
// sub_1ECA30; given by sub_1E3480, an out-of-line getter shared through
// /OPT:ICF), their count (unk_08, given by sub_FB710, likewise) and
// entries (unk_0C). Told of a new selection (slot 2), whether it has the
// pad (slot 3: yes), of the buttons 4 and 7 (slots 4 and 5) and of being
// attached (slot 6); their widths fitted to the list box (sub_1EC930), the
// rows' count (sub_1ECAF0), whether one is selected (sub_1ECB40), and a
// column's width and alignment set (sub_1ECB60, sub_1ECB90).
struct type_1ECA30 : type_3E70B0
{
    type_3E7490 *unk_04;
    RwUInt32 unk_08;
    type_1ECA30_column *unk_0C;

    type_1ECA30(RwUInt32 arg_0);
    virtual RwInt32 vf_000()
    {
        return 2;
    }
    virtual ~type_1ECA30() = 0;
    virtual void pvf_008()
    {
    }
    virtual bool pvf_00C()
    {
        return true;
    }
    virtual void pvf_010()
    {
    }
    virtual void pvf_014()
    {
    }
    virtual void pvf_018()
    {
    }
    void sub_1EC930();
    void sub_1ECA30(type_3E7490 *arg_0);
    RwUInt32 sub_1ECAF0();
    bool sub_1ECB40();
    void sub_1ECB60(RwUInt32 arg_0, RwUInt32 arg_4);
    void sub_1ECB90(RwUInt32 arg_0, RwInt32 arg_4);
    type_3E7490 *sub_1E3480();
    RwUInt32 sub_FB710();
};

// A list box's row (off_3E74C0, whose slot 1 is pure: the row fills its
// texts; 0x40 bytes): a look and a text per column (unk_14, unk_28) and its
// list box (unk_3C). Shown focused and not (sub_1EBF00, sub_1EBF50),
// attached to the list box arg_0 (sub_1EBFA0) and detached (sub_1EC110),
// its state set (sub_1EC250), its column arg_4's text set to arg_0
// (sub_1EC2C0), drawn (sub_1EC2F0) and its column arg_4 placed over arg_0
// (sub_1EC370); whether it is attached (sub_1EC230).
struct type_3E74C0
{
    RwUInt8 unk_04[0x10];
    ::type_1E61A0<type_1E37A0 *, 4> unk_14;
    ::type_1E61A0<type_1F1420 *, 4> unk_28;
    type_3E7490 *unk_3C;

    type_3E74C0();
    virtual ~type_3E74C0();
    virtual void vf_004() = 0;
    void sub_1EBF00();
    void sub_1EBF50();
    void sub_1EBFA0(type_3E7490 *arg_0);
    void sub_1EC110();
    bool sub_1EC230();
    void sub_1EC250(RwInt32 arg_0);
    void sub_1EC2C0(const type_1A5EA0 &arg_0, RwUInt32 arg_4);
    void sub_1EC2F0(type_1E4130 *arg_0);
    void sub_1EC370(const type_1E0330_rect *arg_0, RwUInt32 arg_4);
};

// The row arg_4 of the rows arg_0: a free inline with no address.
// Evidence: the list box's insertion and removal (sub_1EA980, sub_1EAA50)
// copy `begin() + arg_4` through one more temporary than a direct `+`.
inline std::vector<type_3E74C0 *>::iterator row_at(std::vector<type_3E74C0 *> *arg_0, RwInt32 arg_4)
{
    return std::vector<type_3E74C0 *>::iterator(arg_0->begin() + arg_4);
}

// A list box (off_3E7490, 0x118 bytes): its rows (unk_0C), a look (unk_20)
// over its rectangle (unk_104), rows unk_F0 high of which unk_F4 show from
// unk_F8, the selected one (unk_FC, -1 for none), its columns (unk_100),
// whether it may have the focus with its columns not taking it (unk_114),
// and whether its rows must be placed again (unk_115, sub_1EB140). The pad
// moves the selection (sub_1EA540, sub_1EA5E0, the pages sub_1EA6C0 and
// sub_1EA7B0) and the columns (buttons 4 and 7).
struct type_3E7490 : type_3E7D08
{
    std::vector<type_3E74C0 *> unk_0C;
    RwInt32 unk_1C;
    type_1E37A0 unk_20;
    RwInt32 unk_EC;
    RwReal unk_F0;
    RwInt32 unk_F4;
    RwInt32 unk_F8;
    RwInt32 unk_FC;
    type_1ECA30 *unk_100;
    type_1E0330_rect unk_104;
    bool unk_114;
    bool unk_115;

    type_3E7490(RwInt32 arg_0, type_1E3BA0 *arg_4, RwInt32 arg_8, const type_1E0330_rect *arg_C, RwReal arg_10,
                RwInt32 arg_14, bool arg_18, type_1ECA30 *arg_1C, type_3E7D08 *arg_20);
    virtual ~type_3E7490();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void vf_008();
    virtual void vf_00C();
    virtual bool vf_010();
    virtual void vf_014(RwReal arg_0);
    virtual void vf_018(type_1E4130 *arg_0);
    virtual type_1E0330_rect vf_020();
    virtual void givenFocus();
    virtual void lostFocus();
    void sub_1EA260();
    bool sub_1EA410();
    void sub_1EA430(RwInt32 arg_0);
    void sub_1EA540();
    void sub_1EA5E0();
    void sub_1EA6C0();
    void sub_1EA7B0();
    void sub_1EA910(RwInt32 arg_0);
    void sub_1EA980(type_3E74C0 *arg_0, RwInt32 arg_4);
    void sub_1EAA50(RwInt32 arg_0);
    void sub_1EAB50(type_3E74C0 *arg_0);
    void sub_1EABF0(RwUInt32 arg_0);
    RwInt32 sub_1EAC10();
    type_3E74C0 *sub_1EB020();
    std::vector<type_3E74C0 *> *sub_1EB070();
    RwUInt32 sub_1EB090();
    void sub_1EB0B0(RwInt32 arg_0);
    void sub_1EB0D0();
    RwInt32 sub_1EB110(RwUInt32 arg_0);
    void sub_1EB140();
    void sub_1EB160();
    RwInt32 sub_1EB1F0();
    void sub_1EB210(RwInt32 arg_0);
    RwInt32 sub_1EB280();
    // The rows' look (unk_1C; out of line and shared through /OPT:ICF).
    type_1E3BA0 *sub_190360();
};

// The list box's creator (off_3E74C8).
struct type_3E74C8 : type_3E7D94
{
    type_3E74C8();
    virtual ~type_3E74C8();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};

// The editbox's creator (off_3E7284).
struct type_3E7284 : type_3E7D94
{
    type_3E7284();
    virtual ~type_3E7284();
    virtual const RwChar *vf_004();
    virtual void vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                        type_3E7D08 **arg_14);
    virtual void vf_00C(cScopeValidator *arg_0);
};
}

#endif
