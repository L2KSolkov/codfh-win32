/*
 * The Live engine's font renderer over three kujuUI fonts (unit_225220).
 */
#ifndef GAME_UIXFONT_H
#define GAME_UIXFONT_H

#include "game/xboxlive.h"
#include "game/kujufont.h"
#include "game/voice.h"

// The font renderer the late service (type_5051E8::sub_226360) hands the
// UIX engine (vtable off_3EACF0, 0xB8 bytes): text laid out with the small,
// medium or large font (unk_54 to unk_5C, picked by the height asked,
// unk_B4) into four text pages (unk_04) and drawn in the colour unk_68,
// aligned by unk_60 (sub_225A10), at least the font's height high (unk_64);
// its references (unk_6C) are counted down by Release, which never deletes
// it; unk_70 and unk_B0 are cleared.
struct type_225220 : ITitleFontRenderer
{
    type_1F5A50 unk_04[4];
    type_E8780<type_1E5A60> unk_54;
    type_E8780<type_1E5A60> unk_58;
    type_E8780<type_1E5A60> unk_5C;
    RwInt32 unk_60;
    RwUInt32 unk_64;
    D3DCOLOR unk_68;
    RwInt32 unk_6C;
    RwUInt8 unk_70[0x40];
    bool unk_B0;
    RwInt32 unk_B4;

    type_225220(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8);
    ~type_225220();

    STDMETHOD_(ULONG, Release)();
    STDMETHOD(SetHeight)(DWORD arg_0);
    STDMETHOD(SetColor)(D3DCOLOR arg_0);
    STDMETHOD(DrawText)(LPCWSTR arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C);
    STDMETHOD(GetTextSize)(LPCWSTR arg_0, DWORD *arg_4, DWORD *arg_8);
    // The alignment set; the size, width and line height of arg_0 in the
    // font picked.
    void sub_225A10(RwInt32 arg_0);
    RwUInt32 sub_225A30(const wchar_t *arg_0, RwUInt32 *arg_4, RwUInt32 *arg_8, RwInt32 arg_C);
    RwUInt32 sub_225AD0(const wchar_t *arg_0, RwInt32 arg_4);
    RwUInt16 sub_225B60();
};

// The UIX audio plugin the late service hands the engine (vtable
// off_3EAFEC; the one instance, unk_5064DC): its references (unk_04,
// counted down by Release, which never deletes it) and the engine's sounds
// played as the front end's (MenuItemSelect, PasscodeEntry, Notification
// and Error 1, Popup 0, PressA and PressB 2). Release and DoWork are the
// Xbox Live manager's plugin's, folded (/OPT:ICF).
struct type_22AE00 : ITitleAudioPlugin
{
    RwInt32 unk_04;

    type_22AE00();
    ~type_22AE00();

    STDMETHOD_(ULONG, Release)();
    STDMETHOD(PlaySound)(LPCSTR arg_0);
    STDMETHOD(DoWork)();
};
extern type_22AE00 unk_5064DC;

// A player as the engine's players list shows it (vtable off_3EB054, 0x50
// bytes; the late service registers one per player): the player's XUID
// (unk_04), name (unk_10, 25 wide characters), flags (unk_44,
// 1), unk_48 and peer index (unk_4C, what they are ordered by, lowest
// first); its voice status and whether it talks come from the voice
// manager.
struct type_22AF50 : ITitlePlayersListItem
{
    XUID unk_04;
    WCHAR unk_10[0x1A];
    DWORD unk_44;
    RwInt32 unk_48;
    RwUInt32 unk_4C;

    type_22AF50(RwUInt32 arg_0, XUID arg_4, const RwChar *arg_10, RwInt32 arg_14);

    STDMETHOD_(CONST WCHAR *, GetName)() CONST;
    STDMETHOD_(CONST XUID *, GetXUID)() CONST;
    STDMETHOD_(UIX_VOICE_STATUS_TYPE, GetVoiceStatus)() CONST;
    STDMETHOD_(BOOL, IsTalking)() CONST;
    STDMETHOD_(DWORD, GetBitflags)() CONST;
    STDMETHOD_(INT, Compare)(CONST ITitlePlayersListItem *arg_0) CONST;
};

struct type_22A630;

// A texture the UI plugin loads from the engine's skin (unk_1A0 to unk_1B8)
// and a textbox's icon (0x14 bytes): the texture and its size, and for an
// icon the skin icon's two words.
struct type_22A6F0_image
{
    IDirect3DTexture8 *unk_00;
    DWORD unk_04;
    DWORD unk_08;
};
struct type_229170_icon
{
    IDirect3DTexture8 *unk_00;
    RwReal unk_04;
    RwReal unk_08;
    DWORD unk_0C;
    DWORD unk_10;
};

// An object the UI plugin makes for the engine (vtable off_3EAEE0; only the
// constructor and destructor are inline): its UIX object type (unk_04),
// plugin (unk_0C), skin layout (unk_10), screen and object resources
// (unk_14, unk_16) and screen instance (unk_18). Its slots: made (0),
// destroyed (1), given a key (2), its state read and set (3, 4), cleared
// (5), an item inserted (6), drawn at (arg_0, arg_4) (7, pure) and an item's
// text and icons set (8); the base's do nothing. sub_22A460 draws the
// texture arg_0 over the rectangle (arg_4, arg_8, arg_C, arg_10).
struct type_229A90
{
    UIX_OBJECT_TYPE unk_04;
    RwUInt8 unk_08[0x4];
    type_22A630 *unk_0C;
    UIX_SKIN_LAYOUT_INFO *unk_10;
    WORD unk_14;
    WORD unk_16;
    DWORD unk_18;

    type_229A90()
    {
    }
    ~type_229A90()
    {
    }
    virtual HRESULT vf_000();
    virtual void vf_004();
    virtual HRESULT vf_008(UIX_INPUT_TYPE arg_0);
    virtual HRESULT vf_00C(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD *arg_8);
    virtual HRESULT vf_010(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD arg_8);
    virtual HRESULT vf_014(BOOL arg_0);
    virtual HRESULT vf_018(DWORD arg_0, DWORD *arg_4);
    virtual HRESULT vf_01C(RwReal arg_0, RwReal arg_4) = 0;
    virtual HRESULT vf_020(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8, const UIX_SKIN_ICON_INFO *arg_C);
    void sub_22A460(IDirect3DTexture8 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10);
};

// A textbox (CUITextBoxObject, named by its trace; vtable off_3EAF04, 0x34
// bytes; also a listbox's item): shown
// greyed or highlighted (unk_1C, unk_20; the layout's colours), wrapped to
// its width when the engine asks for word wrap (unk_24; sub_22A250), its icons
// (unk_28, unk_2C of them) and text (unk_30, a copy).
struct CUITextBoxObject : type_229A90
{
    DWORD unk_1C;
    DWORD unk_20;
    DWORD unk_24;
    type_229170_icon *unk_28;
    DWORD unk_2C;
    WCHAR *unk_30;

    virtual HRESULT vf_000();
    virtual void vf_004();
    virtual HRESULT vf_010(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD arg_8);
    virtual HRESULT vf_01C(RwReal arg_0, RwReal arg_4);
    virtual HRESULT vf_020(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8, const UIX_SKIN_ICON_INFO *arg_C);
    void sub_22A250();
};

// A listbox (vtable off_3EAFA4, 0x1C0 bytes): its selection (unk_1C), first
// item shown (unk_20), rows shown (unk_24: the layout's custom parameter,
// or 5) and items (unk_2C, unk_1BC of them, textboxes), with arrows above
// and below when it scrolls (the plugin's images).
struct type_229930 : type_229A90
{
    DWORD unk_1C;
    DWORD unk_20;
    DWORD unk_24;
    RwUInt8 unk_28[0x4];
    CUITextBoxObject *unk_2C[100];
    DWORD unk_1BC;

    virtual HRESULT vf_000();
    virtual void vf_004();
    virtual HRESULT vf_008(UIX_INPUT_TYPE arg_0);
    virtual HRESULT vf_00C(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD *arg_8);
    virtual HRESULT vf_010(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD arg_8);
    virtual HRESULT vf_014(BOOL arg_0);
    virtual HRESULT vf_018(DWORD arg_0, DWORD *arg_4);
    virtual HRESULT vf_01C(RwReal arg_0, RwReal arg_4);
    virtual HRESULT vf_020(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8, const UIX_SKIN_ICON_INFO *arg_C);
    void sub_2299D0();
};

// A background (vtable off_3EAFC8, 0x20 bytes): the screen's skin image
// (unk_1C) drawn over the layout's rectangle.
struct type_228D70 : type_229A90
{
    IDirect3DTexture8 *unk_1C;

    virtual HRESULT vf_000();
    virtual HRESULT vf_01C(RwReal arg_0, RwReal arg_4);
};

// The UI plugin the late service hands the engine (vtable off_3EAF28; the
// one instance, unk_506318): its references (unk_04), objects by ID
// (unk_08), the font renderer it hands out (unk_198, held from sub_22A6C0),
// the engine's plugin support (unk_19C) and the skin's list arrows and
// selection bar (unk_1A0, unk_1AC, unk_1B8, images 0x1C to 0x1E; loaded
// by sub_22A6F0).
struct type_22A630 : ITitleUIPlugin
{
    ULONG unk_04;
    type_229A90 *unk_08[100];
    type_225220 *unk_198;
    PluginSupport *unk_19C;
    type_22A6F0_image unk_1A0;
    type_22A6F0_image unk_1AC;
    type_22A6F0_image unk_1B8;

    type_22A630();
    ~type_22A630();
    HRESULT sub_22A6C0(type_225220 *arg_0);
    HRESULT sub_22A6F0(DWORD arg_0, type_22A6F0_image *arg_4);
    // Folded (/OPT:ICF) one-liners: the render target taken (0) and left
    // (1).
    HRESULT sub_32260(IDirect3DSurface8 *arg_0);
    HRESULT sub_115460();

    STDMETHOD_(ULONG, Release)();
    STDMETHOD(DoWork)();
    STDMETHOD(SetPluginSupport)(IPluginSupport *arg_0);
    STDMETHOD(CreateObject)(UIX_OBJECT_TYPE arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C, DWORD *arg_10);
    STDMETHOD(DestroyObject)(DWORD arg_0);
    STDMETHOD(DestroyScreenObjects)(DWORD arg_0);
    STDMETHOD(SetRenderTarget)(IDirect3DSurface8 *arg_0);
    STDMETHOD(RenderObject)(DWORD arg_0);
    STDMETHOD(SetText)(DWORD arg_0, DWORD arg_4, LPCWSTR arg_8, DWORD arg_C, const UIX_SKIN_ICON_INFO *arg_10);
    STDMETHOD(InsertItem)(DWORD arg_0, DWORD arg_4, DWORD *arg_8);
    STDMETHOD(SetObjectState)(DWORD arg_0, DWORD arg_4, UIX_OBJSTATE_TYPE arg_8, DWORD arg_C);
    STDMETHOD(GetObjectState)(DWORD arg_0, DWORD arg_4, UIX_OBJSTATE_TYPE arg_8, DWORD *arg_C);
    STDMETHOD(PassInputToObject)(DWORD arg_0, UIX_INPUT_TYPE arg_4);
    STDMETHOD(Clear)(DWORD arg_0, BOOL arg_4);
    STDMETHOD(GetFont)(ITitleFontRenderer **arg_0);
};
extern type_22A630 unk_506318;

#endif
