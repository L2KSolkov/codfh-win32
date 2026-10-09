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

#ifdef CODFH_SP
    // shape: in the class in single player (unit_19BF20 defines it in MP): it then
    // calls the destructor's out-of-line copy (SP 0x12AE70 -> SP 0x12A770).
    STDMETHOD_(ULONG, Release)()
    {
        delete this;
        return 0;
    }
#else
    STDMETHOD_(ULONG, Release)();
#endif
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

#ifdef CODFH_SP
struct RwCamera;
struct RwV2d;
struct RwRGBA;
// Single player: the Live status texts sp_sub_12B440 fills (SP 0x12B870 draws
// them): one or two lines and their count.
struct type_4F3130_texts
{
    RwChar *unk_00[2];
    RwInt32 unk_08;
};
#endif

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
#ifdef CODFH_SP
    // Single player's uses of these bytes (SP 0x12A970, 0x12C090, 0x12BE30,
    // 0x12AA00, 0x12BF20, 0x12AC10, 0x12AB10, 0x12B600).
    RwUInt8 unk_2C;             // the engine was drawn (its input is kept)
    RwUInt8 unk_2D[0x3];
    RwCamera *unk_30;           // the camera its front end draws on
#else
    RwUInt8 unk_2C[0x8];
#endif
    RwInt32 unk_34;
    RwInt32 unk_38;             // the step it is at
#ifdef CODFH_SP
    RwInt32 unk_3C;             // the step before a message (SP 0x12AA00)
#else
    RwUInt8 unk_3C[0x4];
#endif
    RwInt32 unk_40;             // the message the friends list closes
#ifdef CODFH_SP
    RwInt32 unk_44;             // how the friends feature exited (SP 0x12BF20)
    XONLINE_USER unk_48[XONLINE_MAX_STORED_ONLINE_USERS];   // the users (SP 0x12AC10)
    DWORD unk_748;              // and their count
#else
    RwUInt8 unk_44[0x708];
#endif
    RwInt32 unk_74C;
    RwInt32 unk_750;
#ifdef CODFH_SP
    RwReal unk_754;             // the fade's alpha, following unk_758 (SP 0x12A9C0, 0x12BC30)
#else
    RwInt32 unk_754;
#endif
    RwReal unk_758;
    RwInt32 unk_75C;
    RwInt32 unk_760;
    RwInt32 unk_764;            // the state (1 signed in, 2 online, 3
                                // offline, 4 signed out, 6 ...)
#ifdef CODFH_SP
    RwChar unk_768[0x80];       // the status texts (SP 0x12B440)
    RwChar unk_7E8[0x80];
#else
    RwUInt8 unk_768[0x100];
#endif
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
#ifdef CODFH_SP
    // Single player only (SP 0x12AD50): whether its front end has a Live message up:
    // never while sp_dword_3B66AC is set, at steps 3 and 6 or with unk_75C; else unk_868.
    RwInt32 sp_sub_12AD50();
    // Single player only (SP 0x12AAD0): whether Live is busy (the friends
    // feature up, unk_75C, unk_760 or unk_868 set, or at step 1 or 5); the
    // fade (sub_125060) is not drawn meanwhile.
    RwInt32 sp_sub_12AAD0();
    // Single player's other Live front end (SP 0x12A840-0x12C230; no MP twins):
    // the font and plugins it hands the engine, its set-up, update and render,
    // its messages and status texts and the voice it starts after signing in.
    HRESULT sp_sub_12A840();
    HRESULT sp_sub_12A8A0();
    HRESULT sp_sub_12A8B0();
    void sp_sub_12A900(RwReal arg_0, RwReal arg_4);
    void sp_sub_12A960();
    void sp_sub_12A970();
    void sp_sub_12A9C0(RwCamera *arg_0);
    void sp_sub_12AA00(RwInt32 arg_0);
    void sp_sub_12AA40();
    RwInt32 sp_sub_12AAB0();
    RwChar *sp_sub_12AB10();
    void sp_sub_12AB40(RwInt32 arg_0);
    RwInt32 sp_sub_12ABB0();
    RwInt32 sp_sub_12ABF0(RwInt32 arg_0);
    HRESULT sp_sub_12AC10();
    HRESULT sp_sub_12AF40();
    void sp_sub_12B140();
    void sp_sub_12B1C0();
    void sp_sub_12B240();
    void sp_sub_12B2E0();
    void sp_sub_12B310();
    void sp_sub_12B380();
    void sp_sub_12B440(struct type_4F3130_texts *arg_0);
    RwInt32 sp_sub_12B600(RwInt32 arg_0);
    void sp_sub_12B830();
    void sp_sub_12B870(RwCamera *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwRGBA *arg_C,
                       RwV2d *arg_10, RwInt32 arg_14, RwRGBA *arg_18);
    HRESULT sp_sub_12BB50(RwInt32 arg_0, RwInt32 arg_4);
    RwInt32 sp_sub_12BC30();
    HRESULT sp_sub_12BD30(UIX_EXIT_INFO *arg_0);
    void sp_sub_12BE30(RwCamera *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwRGBA *arg_C,
                       RwV2d *arg_10, RwInt32 arg_14, RwRGBA *arg_18, RwInt32 arg_1C);
    void sp_sub_12BF20();
    void sp_sub_12C090();
#endif
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
#ifdef CODFH_SP
#include <xhv.h>
// Single player links the XDK samples' voice manager (UIXFriends'
// XHVVoiceManager.cpp, defined in unit_19AAB0, SP 0x129260-0x129508); the
// Live manager keeps one (sp_dword_3EB728, right after it in .bss, built by
// SP 0x21DF90) for voice after signing in (SP 0x12AB40, 0x12BD30, 0x12BF20,
// 0x12C090, 0x12B050, 0x12B0C0).
#ifndef CODFH_CXHVVOICEMANAGER
#define CODFH_CXHVVOICEMANAGER
// Used to keep track of voice-related details about each player
struct PlayerVoiceInfo
{
    XUID                    xuid;
    XHV_PLAYBACK_PRIORITY   priority[4];
    BOOL                    bMuted[4];
    BOOL                    bRemoteMuted[4];
};

class CXHVVoiceManager
{
public:
    CXHVVoiceManager();
    ~CXHVVoiceManager();

    BOOL IsInitialized() const { return m_pXHVEngine != 0; }

    PXHVENGINE GetXHVEngine() const { return m_pXHVEngine; }

    HRESULT Initialize( LPDIRECTSOUND8 pDSound,
                        XHV_RUNTIME_PARAMS* pXHVParams,
                        ITitleXHV* pTitleXHV );
    HRESULT Shutdown();

    // These functions wrap handling local and remote talkers, so that we can
    // manage the list of PlayerVoiceInfo structs
    HRESULT RegisterLocalTalker( DWORD dwPort );
    HRESULT UnregisterLocalTalker( DWORD dwPort );

    // These functions handle higher-level logical operations such as
    // muting and voice-through-speaker control
    HRESULT SetVoiceThroughSpeakers( DWORD dwPort, BOOL bVoiceThroughSpeakers );

protected:
    HRESULT RecalculatePriorities( PlayerVoiceInfo* pInfo );

    LPDIRECTSOUND8      m_pDSound;
    PXHVENGINE          m_pXHVEngine;
    DWORD               m_dwMaxRemoteTalkers;
    DWORD               m_dwNumRemoteTalkers;
    PlayerVoiceInfo*    m_pPlayerVoiceInfo;

    BOOL                m_bEnabledLocalTalkers[ XGetPortCount() ];
    BOOL                m_bVoiceThroughSpeakers[ XGetPortCount() ];
};
#endif
extern CXHVVoiceManager sp_dword_3EB728;    // the Live manager's voice (SP 0x3EB728)
#endif
extern D3DSurface *dword_4F312C;   // where the font renderer draws
extern RwInt32 dword_4B88AC;
extern RwInt32 dword_4B8738;
// Whether message arg_0 is open (the message boxes, game/waitscreen.h).
RwInt32 sub_186F20(RwInt32 arg_0);

#endif
