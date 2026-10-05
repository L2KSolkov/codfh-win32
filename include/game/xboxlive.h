/*
 * The Xbox Live manager (unit_19BF20, dword_4F3130): the UIX engine's sign-in
 * (logon) and friends features, the online state it tells the engine, and
 * the font renderer and audio plugin it hands the engine.
 */
#ifndef GAME_XBOXLIVE_H
#define GAME_XBOXLIVE_H

#include <xtl.h>
#include <xfont.h>
#include <uix.h>

#include "rw/ostypes.h"

// The UIX font renderer over an XFONT (vtable off_3E0404): text drawn into
// the surface dword_4F312C.
struct type_3E0404 : ITitleFontRenderer
{
    XFONT *unk_04;

    type_3E0404()
    {
        unk_04 = 0;
    }
    ~type_3E0404()
    {
        if (unk_04)
            unk_04->Release();
    }

    STDMETHOD_(ULONG, Release)();
    STDMETHOD(SetHeight)(DWORD arg_0);
    STDMETHOD(SetColor)(D3DCOLOR arg_0);
    STDMETHOD(DrawText)(LPCWSTR arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C);
    STDMETHOD(GetTextSize)(LPCWSTR arg_0, DWORD *arg_4, DWORD *arg_8);
};
// The UIX audio plugin (vtable off_3E03F8): plays nothing; PlaySound is
// sub_1C7830, identical to another plugin's and folded (/OPT:ICF).
struct type_3E03F8 : ITitleAudioPlugin
{
    RwInt32 unk_04;             // its references

    type_3E03F8()
    {
        unk_04 = 0;
    }

    STDMETHOD_(ULONG, Release)();
    STDMETHOD(PlaySound)(LPCSTR arg_0);
    STDMETHOD(DoWork)();
};
// The interface the manager implements for the engine (vtable off_3E0418,
// six slots); no UIX header declares it, so only the slots' widths are the
// image's (novtable, as UIX's interfaces: the constructor stores one
// vtable). Slot 3 is sub_1C7810, and slots 2 and 4 are folded into slot 0.
struct __declspec(novtable) type_3E0418
{
    virtual HRESULT __stdcall vf_000(DWORD arg_0, DWORD arg_4, DWORD arg_8) = 0;
    virtual HRESULT __stdcall vf_004(DWORD arg_0, DWORD arg_4) = 0;
    virtual HRESULT __stdcall vf_008(DWORD arg_0, DWORD arg_4, DWORD arg_8) = 0;
    virtual HRESULT __stdcall vf_00C(DWORD arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C) = 0;
    virtual HRESULT __stdcall vf_010(DWORD arg_0, DWORD arg_4, DWORD arg_8) = 0;
    virtual HRESULT __stdcall vf_014(DWORD arg_0) = 0;
};

// The Xbox Live state: sub_19C440 shows the friends list, sub_19C3A0 and
// sub_19C3F0 appear offline and online, sub_19C490 and sub_19C4D0 sign in
// and out.
struct type_4F3130 : type_3E0418
{
    ILiveEngine *unk_04;
    type_3E0404 unk_08;
    RwUInt8 unk_10[0x4];
    type_3E03F8 unk_14;
    RwInt32 unk_1C;
    RwInt32 unk_20;             // the friends feature is up
    RwInt32 unk_24;
    RwInt32 unk_28;
    RwUInt8 unk_2C[0x8];
    RwInt32 unk_34;
    RwInt32 unk_38;             // the step it is at
    RwUInt8 unk_3C[0x4];
    RwInt32 unk_40;             // the message the friends list closes
    RwUInt8 unk_44[0x708];
    RwInt32 unk_74C;
    RwInt32 unk_750;
    RwInt32 unk_754;
    RwReal unk_758;
    RwInt32 unk_75C;
    RwInt32 unk_760;
    RwInt32 unk_764;            // the state (1 signed in, 2 online, 3
                                // offline, 4 signed out, 6 ...)
    RwUInt8 unk_768[0x100];
    RwInt32 unk_868;
    RwInt32 unk_86C;
    RwInt32 unk_870;
    RwInt32 unk_874;

    type_4F3130();

    virtual HRESULT __stdcall vf_000(DWORD arg_0, DWORD arg_4, DWORD arg_8);
    virtual HRESULT __stdcall vf_004(DWORD arg_0, DWORD arg_4);
    virtual HRESULT __stdcall vf_008(DWORD arg_0, DWORD arg_4, DWORD arg_8);
    virtual HRESULT __stdcall vf_00C(DWORD arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C);
    virtual HRESULT __stdcall vf_010(DWORD arg_0, DWORD arg_4, DWORD arg_8);
    virtual HRESULT __stdcall vf_014(DWORD arg_0);

    void sub_19BF20(HRESULT arg_0);
    HRESULT sub_19C160();
    HRESULT sub_19C200();
    HRESULT sub_19C280();
    void sub_19C2C0(RwInt32 arg_0);
    void sub_19C310();
    void sub_19C380(RwReal arg_0);
    void sub_19C3A0();
    void sub_19C3F0();
    void sub_19C440();
    void sub_19C490();
    void sub_19C4D0();
    RwInt32 sub_19C500();
    void sub_19C530();
    void sub_19C560();
    HRESULT sub_19C590(RwInt32 arg_0);
    RwInt32 sub_19C620();
    void sub_19C6D0(RwInt32 arg_0);
    RwInt32 sub_19C740();
    void sub_19C790();
};
extern type_4F3130 dword_4F3130;
extern D3DSurface *dword_4F312C;   // where the font renderer draws
extern RwInt32 dword_4B88AC;
extern RwInt32 dword_4B8738;
// Whether message arg_0 is open (the message boxes, game/waitscreen.h).
RwInt32 sub_186F20(RwInt32 arg_0);


#endif
