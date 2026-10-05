/*
 * The front end's options page (unit_1FC320): six option selectors over the
 * front end's settings (the controller's layout, and five more), each a
 * value a widget changes, picking one of its values and showing its label.
 */
#ifndef GAME_OPTIONS_H
#define GAME_OPTIONS_H

#include <map>

#include "game/kujuui.h"
#include "game/loc.h"

// The six options' values: distinct enumerations (six instantiations of the
// selector, each with its own vtable and map code); their names and values
// are not known. Named for the selectors' constructors.
enum type_1FCDC0_value
{
};
enum type_1FD050_value
{
};
enum type_1FD1C0_value
{
};
enum type_1FD2B0_value
{
};
enum type_1FD3A0_value
{
};
enum type_1FD490_value
{
};

// An option selector (off_3E7F6C to off_3E7FE4, one per value type; 0x20
// bytes): its values and their labels (unk_08), the one picked (unk_14),
// the setting it changes (unk_18) and a hook that must allow it (unk_1C);
// unk_14 is a const_iterator (it is copied from end() with no null store
// first). A value and its label added (sub_1FCEB0, through a pair the map's
// value is converted from; the first becomes the one picked), the value
// picked (sub_1FD030), picked by value (sub_201EC0), whether it can change
// (slot 4, sub_1FD140). The members shared through
// /OPT:ICF with other instances elsewhere (sub_201EC0, sub_203CA0, slots
// 2, 3 and 5) are declared only.
template <class T> struct type_1FCDC0 : kujuUI::type_1E34A0
{
    typedef std::map<T, type_1CB670> map_type;

    map_type unk_08;
    typename map_type::const_iterator unk_14;
    T *unk_18;
    kujuUI::type_1ED670_object *unk_1C;

    type_1FCDC0(T *arg_0, kujuUI::type_1ED670_object *arg_4);
    virtual ~type_1FCDC0();
    virtual void vf_008(RwUInt32 arg_0);
    virtual void vf_00C(RwUInt32 arg_0);
    virtual bool vf_010();
    virtual void vf_014();
    void sub_1FCEB0(const T &arg_0, const type_1CB670 &arg_4);
    const T &sub_1FD030();
    // The value picked, as a copy: an inline accessor with no address,
    // named for what it gives. Evidence: the host options' write
    // (sub_201A70) stores each through a slot of its own.
    T get_value()
    {
        T r = sub_1FD030();
        return r;
    }
    void sub_201EC0(const T &arg_0);
    bool sub_203CA0(const T &arg_0);
    // The value arg_0 taken out (another picked when it was; sub_202350),
    // whether one is picked (sub_203CF0) and its hook told (sub_2251F0).
    void sub_202350(const T &arg_0);
    bool sub_203CF0();
    void sub_2251F0();
};

// Its members, defined here as the original header had them: every unit that uses an
// instantiation emits it (a COMDAT), and /OPT:ICF folds the identical ones.
template <class T> type_1FCDC0<T>::type_1FCDC0(T *arg_0, kujuUI::type_1ED670_object *arg_4) : unk_14(unk_08.end())
{
    unk_18 = arg_0;
    unk_1C = arg_4;
}

template <class T> type_1FCDC0<T>::~type_1FCDC0()
{
}

template <class T> void type_1FCDC0<T>::sub_1FCEB0(const T &arg_0, const type_1CB670 &arg_4)
{
    if (!sub_203CA0(arg_0))
    {
        std::pair<T, type_1CB670> var_30(arg_0, arg_4);
        if (unk_14 == unk_08.end())
        {
            unk_14 = unk_08.insert(var_30).first;
            vf_014();
        }
        else
        {
            unk_08.insert(var_30);
        }
    }
}

template <class T> const T &type_1FCDC0<T>::sub_1FD030()
{
    return unk_14->first;
}

template <class T> void type_1FCDC0<T>::sub_201EC0(const T &arg_0)
{
    if (sub_203CA0(arg_0))
    {
        unk_14 = unk_08.find(arg_0);
        vf_014();
    }
}

template <class T> void type_1FCDC0<T>::sub_202350(const T &arg_0)
{
    if (sub_203CA0(arg_0))
    {
        typename map_type::iterator var_4 = unk_08.find(arg_0);
        if (var_4 == unk_14)
        {
            unk_14 = unk_08.begin();
            sub_2251F0();
        }
        unk_08.erase(var_4);
    }
}

template <class T> bool type_1FCDC0<T>::sub_203CA0(const T &arg_0)
{
    return unk_08.find(arg_0) != unk_08.end();
}

template <class T> bool type_1FCDC0<T>::sub_203CF0()
{
    return unk_14 != unk_08.end();
}

template <class T> void type_1FCDC0<T>::sub_2251F0()
{
    if (unk_1C)
        unk_1C->pvf_008();
}

template <class T> void type_1FCDC0<T>::vf_008(RwUInt32 arg_0)
{
    ++unk_14;
    if (unk_14 == unk_08.end())
    {
        if (!unk_18)
            unk_14 = unk_08.begin();
        else
            --unk_14;
    }
    sub_2251F0();
    vf_014();
}

template <class T> void type_1FCDC0<T>::vf_00C(RwUInt32 arg_0)
{
    if (unk_14 == unk_08.begin())
    {
        if (!unk_18)
        {
            unk_14 = unk_08.end();
            --unk_14;
        }
    }
    else
        --unk_14;
    sub_2251F0();
    vf_014();
}

template <class T> bool type_1FCDC0<T>::vf_010()
{
    return has_unk_04() && !unk_08.empty() && (unk_1C ? unk_1C->pvf_00C() : true);
}

template <class T> void type_1FCDC0<T>::vf_014()
{
    if (sub_203CF0() && has_unk_04())
        sub_1E3480()->sub_1E2A50(unk_14->second);
}


// The options page (0x1B8 bytes; sub_1FC320 builds it): two integer values'
// widgets (unk_00, unk_7C) and the six selectors; the settings read into
// them (sub_1FCC80) and written back from them (sub_1FCD10, which marks
// them changed, byte_4FDAA8).
struct type_1FC320
{
    kujuUI::type_1E76A0 unk_00;
    kujuUI::type_1E76A0 unk_7C;
    type_1FCDC0<type_1FCDC0_value> unk_F8;
    type_1FCDC0<type_1FD050_value> unk_118;
    type_1FCDC0<type_1FD1C0_value> unk_138;
    type_1FCDC0<type_1FD2B0_value> unk_158;
    type_1FCDC0<type_1FD3A0_value> unk_178;
    type_1FCDC0<type_1FD490_value> unk_198;

    // The in-game options pass zeros; the last is the speakers' selector's
    // hook.
    type_1FC320(kujuUI::type_1ED670_object *arg_0, kujuUI::type_1ED670_object *arg_4,
                kujuUI::type_1ED670_object *arg_8, kujuUI::type_1ED670_object *arg_C);
    ~type_1FC320();
    void sub_1FCC80();
    void sub_1FCD10();
    // The last selector: an inline accessor with no address, named for its
    // field. Evidence: the constructor adds its last label through it (the
    // frame is 8 bytes larger with a direct member access).
    type_1FCDC0<type_1FD490_value> *get_unk_198()
    {
        return &unk_198;
    }
};

// The front end's settings the page reads and writes (unit_1C3D20).
RwInt32 sub_1C4F30();
void sub_1C4F70(RwInt32 arg_0);
RwInt32 sub_1C4FF0();
void sub_1C5020(RwInt32 arg_0);
RwInt32 sub_1C5040();
void sub_1C5080(RwInt32 arg_0);
RwInt32 sub_1C5100();
void sub_1C5120(RwInt32 arg_0);
RwInt32 sub_1C5160();
void sub_1C5180(RwInt32 arg_0);
// The voice chat's speakers off (sub_1C51A0), set (sub_1C51D0); the
// settings' changed mark cleared (sub_1C5220).
RwInt32 sub_1C51A0();
void sub_1C51D0(RwInt32 arg_0);
void sub_1C5220();
extern RwUInt8 byte_4FDAA8;

#endif
