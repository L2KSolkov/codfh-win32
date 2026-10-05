/*
 * kujuUI's widget factory and top layout page (unit_1F2920): the pieces that
 * need the layout files' parser (game/parsedfile.h) as well as the widgets.
 */
#ifndef GAME_KUJUILAYOUT_H
#define GAME_KUJUILAYOUT_H

#include "game/kujuui.h"
#include "game/parsedfile.h"

namespace kujuUI
{

// A layout file's widget while the page is built (0x24 bytes): the widget,
// its name and the names of the widgets its buttons lead to (from its
// values sub_1E35D0, sub_1E35E0, sub_1E35B0, sub_1E35C0, sub_1E35F0,
// sub_1E3600 and sub_1E3610). The widget named arg_0 among arg_8 of them
// (sub_1F31C0); arg_0's link to the one named arg_4 by the button arg_10
// on the page arg_14 (sub_1F3230); a name value's text (sub_1F3270: the
// value arg_0 of the scope arg_4 when it is one string part).
struct type_1F31C0_entry
{
    type_3E7D08 *unk_00;
    const RwChar *unk_04;
    const RwChar *unk_08[7];
};
type_3E7D08 *sub_1F31C0(const RwChar *arg_0, const type_1F31C0_entry *arg_4, RwUInt32 arg_8);
void sub_1F3230(type_3E7D08 *arg_0, const RwChar *arg_4, const type_1F31C0_entry *arg_8, RwUInt32 arg_C,
                RwInt32 arg_10, cLayoutPage *arg_14);
const RwChar *sub_1F3270(type_1C9590 *arg_0, type_1C8DF0 *arg_4);

// kujuUI's widget factory (0xAE4 bytes; one, made on first use by
// sub_1F2920 into dword_504380 and deleted by sub_1F29A0 when the last top
// layout page goes): the creators by their type's name (unk_00, sub_1F2E70
// adds one), the creators themselves (unk_0C to unk_28), the layout files'
// validator (unk_2C: the creators', the looks' and the fonts' validators as
// children, the image libraries' taken over), the creators' validators
// (unk_144) and the layout file's own values (unk_A08 "default", unk_A34
// "retainselection", unk_A60 and unk_A8C "title", unk_AB8
// "titledimensions"). A widget from a scope (sub_1F7960).
struct type_1F2A00
{
    type_1EFCF0<type_3E7D94> unk_00;
    type_3E6D3C unk_0C;
    type_3E6DA0 unk_10;
    type_3E6FA4 unk_14;
    type_3E7284 unk_18;
    type_3E74C8 unk_1C;
    type_3E7830 unk_20;
    type_3E79E4 unk_24;
    type_3E7A00 unk_28;
    cScopeValidator unk_2C;
    ::type_1E61A0<cScopeValidator, 8> unk_144;
    type_1C9590 unk_A08;
    type_1C9590 unk_A34;
    type_1C9590 unk_A60;
    type_1C9590 unk_A8C;
    type_1C9590 unk_AB8;

    type_1F2A00();
    ~type_1F2A00();
    void sub_1F2E70(type_3E7D94 *arg_0);
    void sub_1F7960(type_1C8DF0 *arg_0, type_1EFCF0<type_1E3BA0> *arg_4, type_1EFCF0<type_1E6350> *arg_8,
                    type_1ED670 *arg_C, type_3E7D08 *arg_10, type_3E7D08 **arg_14);
    // The layout file's values: inlines with no addresses, named for their
    // fields. Evidence: the top layout page's widget builder (sub_1F3510)
    // keeps the factory in a `this` slot of its own for each.
    type_1C9590 *get_unk_A08()
    {
        return &unk_A08;
    }
    type_1C9590 *get_unk_A34()
    {
        return &unk_A34;
    }
    type_1C9590 *get_unk_A60()
    {
        return &unk_A60;
    }
    type_1C9590 *get_unk_A8C()
    {
        return &unk_A8C;
    }
    type_1C9590 *get_unk_AB8()
    {
        return &unk_AB8;
    }
};
type_1F2A00 *sub_1F2920();
// The factory through an inline with no address. Evidence: the widget
// builder (sub_1F3510) fetches it before the arguments of its one widget
// call (sub_1F7960), into a temporary.
inline type_1F2A00 *widget_factory()
{
    return sub_1F2920();
}
void sub_1F29A0();

// A top layout page (off_3E7A68, 0x118 bytes; named by its traces,
// \COD\SHARED\UI\cTopLayoutPage.cpp): a layout page loaded from a file
// (unk_80, set by sub_1F44C0 with the registry unk_A0 and the widgets'
// names unk_A4) in steps (unk_A8: sub_1F4450 runs step 1 the file,
// sub_1F32D0; 2 its image libraries, sub_1F3390; 3 its looks and fonts,
// sub_1F3430; 4 its widgets, sub_1F3510; 5 loaded, 6 failed,
// throwLoadError), with its fonts (unk_38, named in unk_B8), looks
// (named in unk_AC, from the libraries unk_C8), a title (unk_C4, set by
// sub_1F4540 over a border; its text by sub_1F4790) and the pad's buttons
// handed to widgets (unk_44, sub_1F43D0). The pages alive are counted
// (dword_504384): the last to go deletes the factory and the image
// libraries' validator. Slot 14 (vf_038, empty) is told when it is loaded.
class cTopLayoutPage : public cLayoutPage
{
public:
    std::list<type_1E6350> unk_38;
    type_3E6CEC unk_44;
    std::string unk_80;
    cParsedFile *unk_9C;
    type_1ED670 *unk_A0;
    type_1EFCF0<type_3E7D08 *> *unk_A4;
    RwInt32 unk_A8;
    type_1EFCF0<type_1E3BA0> unk_AC;
    type_1EFCF0<type_1E6350> unk_B8;
    cStaticText *unk_C4;
    type_1EF3A0 unk_C8;

    cTopLayoutPage();
    virtual ~cTopLayoutPage();
    virtual eEventWasHandled processEvent(const cStateChange &arg_0);
    virtual void vf_038();
    void sub_1F32D0();
    void sub_1F3390();
    void sub_1F3430();
    void sub_1F3510();
    void throwLoadError();
    // Its loading step (unk_A8): an out-of-line getter shared through
    // /OPT:ICF (0x15FC40).
    RwInt32 sub_15FC40();
    bool sub_1F4100(type_1C8DF0 *arg_0, type_1EFCF0<type_1E6350> *arg_4);
    void sub_1F43D0(RwInt32 arg_0, type_1DFE80_target *arg_4);
    bool sub_1F4430(const RwChar *arg_0);
    void sub_1F4450();
    void sub_1F44C0(const RwChar *arg_0, type_1ED670 *arg_4, type_1EFCF0<type_3E7D08 *> *arg_8);
    void sub_1F4540(const type_1A5EA0 &arg_0, type_1E6350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    bool sub_1F4790(const type_1A5EA0 &arg_0);
};
}

#endif
