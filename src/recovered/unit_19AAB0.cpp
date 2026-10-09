// The game's save state (game/savestate.h): the difficulty, the state's
// defaults and set-up from the shell, and its accessors.

#ifdef CODFH_SP
#include "game/xboxlive.h"     // CXHVVoiceManager (first: it brings D3D8.h)
#endif
#include "rw/ostypes.h"
#include <string.h>
#include "game/savestate.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/functions.h"
#include "types/type_DA0A0.h"

#include "types/type_4F2940.h"
#ifdef CODFH_WIN32
// (the port's configured language, for a start with no shell settings: port/src/xpal_core.cpp)
extern "C" RwInt32 port_language(void);
#endif
#ifdef CODFH_SP
// the XDK samples' voice manager at this file's end
#include <xtl.h>
#include <xonline.h>
#include <xhv.h>
#include <assert.h>
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042B714
#ifndef CODFH_SP // single player defines it in unit_198390 (SP 0x328524)
RwInt32 dword_42B714 = -1;
#endif
// 0x004F2860
RwReal flt_4F2860[3];
// 0x004F286C
RwReal flt_4F286C[3];
// 0x004F2878
RwReal flt_4F2878[3];
// 0x004F2884
RwReal flt_4F2884[3];
// 0x004F2890
RwReal flt_4F2890[3];
// 0x004F289C
RwReal flt_4F289C[3];
// 0x004F28A8
RwReal flt_4F28A8[3];
// 0x004F28B4
RwReal flt_4F28B4[3];
// 0x004F28C0
RwReal flt_4F28C0[3];
// 0x004F28CC
RwReal flt_4F28CC[3];
// 0x004F28D8
RwReal flt_4F28D8[3];
// 0x004F28E4
RwReal flt_4F28E4[3];
// 0x004F28F0
type_4F28F0 *dword_4F28F0;
// 0x004F28F4
RwInt32 dword_4F28F4;
// 0x004F28F8
RwUInt8 byte_4F28F8;
// 0x004F28FC
RwInt32 dword_4F28FC;
// 0x004F2900
RwInt32 dword_4F2900;
// 0x004F2908
type_4F28F0 byte_4F2908;
// 0x004F5DD8
#ifndef CODFH_PLAIN
type_4F5DD8 unk_4F5DD8[1];
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
#ifndef CODFH_SP // single player has no initializer for it: the state's own constructor clears unk_38, statically (SP 0x3285C8 +0x40 = -1)
type_4F2940 unk_4F2940;
#endif
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BM@OGNKNLDP@difficulty?5?$DN?5?$CFd?5from?5shell?6?$AA@ @ 0x003E00D0
// match: ??_C@_05KMGJCOIF@MP_10?$AA@ @ 0x003E00EC
// match: ??_C@_04DLNHHPIP@MP_9?$AA@ @ 0x003E00F4
// match: ??_C@_04KFFEFCAB@MP_7?$AA@ @ 0x003E00FC
// match: ??_C@_04LMEPGDEA@MP_6?$AA@ @ 0x003E0104
// match: ??_C@_04JHGCDAID@MP_5?$AA@ @ 0x003E010C
// match: ??_C@_04IOHJABMC@MP_4?$AA@ @ 0x003E0114
// match: ??_C@_04NICDKGEE@MP_2?$AA@ @ 0x003E011C
// match: ??_C@_04PDAOPFIH@MP_1?$AA@ @ 0x003E0124
// match: ??_C@_06CCLMOILL@L_NULL?$AA@ @ 0x003E012C
// match: ??_C@_03JBJLGPFL@end?$AA@ @ 0x003E0134
// match: ??_C@_05KKCIMGE@error?$AA@ @ 0x003E0138
// match: ??_C@_02KAJCLHKP@no?$AA@ @ 0x003E0140
// match: ??_C@_03ICICOMAL@yes?$AA@ @ 0x003E0144
// match: ??_C@_0L@GPECBCMJ@Liveupdate?$AA@ @ 0x003E0148
// match: ??_C@_08JLLDKAGD@Debugger?$AA@ @ 0x003E0154
// match: ??_C@_09NBJKPNHD@Dashboard?$AA@ @ 0x003E0160
// match: ??_C@_07NBCGADJA@Unknown?$AA@ @ 0x003E016C
// match: ??_C@_05PABKJLOM@Title?$AA@ @ 0x003E0174
// match: .CRT$XCU+0 @ 0x00427194
// match: ?dword_42B714@@3HA @ 0x0042B714
// match: ?off_42B718@?1??sub_19B060@@YAPBDH@Z@4PAPBDA @ 0x0042B718

// match: _$E1 @ 0x0030C0B0
// match: ?sub_19AAB0@@YAXXZ @ 0x0019AAB0
// sp-match: ?sub_19AAB0@@YAXXZ @ 0x00128D60

// Takes the difficulty from the state and resets its multipliers.
void sub_19AAB0()
{
    RwInt32 var_4;

    dword_42B714 = sub_19B080();
#ifndef CODFH_SP // single player compiles the debug print out
    sub_19A750("difficulty = %d from shell\n", dword_42B714);
#endif
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        flt_4F286C[var_4] = 1.0f;
        flt_4F28E4[var_4] = 1.0f;
        flt_4F28A8[var_4] = 1.0f;
        flt_4F2878[var_4] = 1.0f;
        flt_4F2860[var_4] = 1.0f;
        flt_4F289C[var_4] = 1.0f;
        flt_4F2890[var_4] = 1.0f;
        flt_4F28B4[var_4] = 1.0f;
        flt_4F28D8[var_4] = 1.0f;
        flt_4F28C0[var_4] = 1.0f;
        flt_4F28CC[var_4] = 1.0f;
        flt_4F2884[var_4] = 1.0f;
    }
}

// match: ?sub_19ABA0@type_DA0A0@@QAEGXZ @ 0x0019ABA0
// sp-match: ?sub_19ABA0@type_DA0A0@@QAEGXZ @ 0x00128EE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The record's checksum: its 200 bytes' sum less the checksum's own two
// (0 for a blank record, "KNLB").
RwUInt16 type_DA0A0::sub_19ABA0()
{
    RwUInt32 var_C;
    RwUInt16 bp_8;
    RwChar *bp_4;

    if (is_blank())
        return 0;
    bp_8 = 0;
    bp_4 = (RwChar *)this;
    for (var_C = 0; var_C < 200; var_C++)
    {
        bp_8 += *bp_4;
        bp_4++;
    }
    bp_4 = (RwChar *)&unk_1C;
    bp_8 -= *bp_4;
    bp_4++;
    bp_8 -= *bp_4;
    return bp_8;
}

// match: ?sub_19AC40@type_DA0A0_64@@QAEPAU1@PAUtype_D90B0@@@Z @ 0x0019AC40
// sp-match: ?sub_19AC40@type_DA0A0_64@@QAEPAU1@PAUtype_D90B0@@@Z @ 0x00128F40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_DA0A0_64 *type_DA0A0_64::sub_19AC40(type_D90B0 *arg_0)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    unk_00.unk_54 = arg_0->unk_54;
    unk_00.unk_50 = arg_0->unk_50;
    unk_00.unk_58 = arg_0->unk_58;
    unk_00.unk_00 = arg_0->unk_00;
    unk_00.unk_04 = arg_0->unk_04;
    for (l4 = 0; l4 < 2; l4++)
    {
        unk_00.unk_10[l4] = arg_0->unk_10[l4];
        unk_00.unk_08[l4] = arg_0->unk_08[l4];
    }
    unk_00.unk_18.unk_00 = arg_0->unk_18.unk_00;
    for (var_8 = 0; var_8 < 13; var_8++)
        unk_00.unk_18.unk_04[var_8] = arg_0->unk_18.unk_04[var_8];
    memset(unk_5C, 0, 8);
    return this;
}

// match: ?sub_19AD20@@YAXXZ @ 0x0019AD20
// sp-match: ?sub_19AD20@@YAXXZ @ 0x00129110
// Sets the state up once: its defaults, then what the shell chose (the
// language, player, pad, difficulty and profile name), or with no shell
// settings the first pad and profile.
void sub_19AD20()
{
    // Unused: the image keeps three slots above its inlines' temporaries.
    RwInt32 var_4;
    RwInt32 var_8;
    RwInt32 var_C;

    if (dword_4F2900)
        return;
    dword_4F2900 = 1;
    byte_4F28F8 = 0;
    byte_4F2908.sub_19AEA0();
    dword_4F28F0 = &byte_4F2908;
    dword_4F28F4 = dword_4F28F0->unk_10;
#ifndef CODFH_SP // single player has no game set-up to copy (SP 0x129110 ends here)
    if (dword_4F45F8 && !dword_4F45F8->unk_20)
    {
        sub_19B0C0(dword_4F45F8->unk_28);
        set_4F28F0_unk_1C(dword_4F45F8->unk_30);
        unk_4B9308.sub_EEAA0(dword_4F45F8->unk_24);
        dword_4B9E5C = 0;
        set_4F28F0_unk_22(dword_4F45F8->unk_2C != 0);
        set_4F28F0_unk_18(dword_4F45F8->unk_34);
        set_4F28F0_unk_183(unk_4F5DD8[dword_4F45F8->unk_14].unk_00);
    }
    else
    {
        unk_4B9308.sub_EEAA0(0);
        dword_4B9E5C = 0;
#ifdef CODFH_WIN32
        // (a start with no shell settings: the configured language, not the debugger's French)
        sub_19B0C0(port_language());
#else
        sub_19B0C0(2);
#endif
        dword_4F28F0->unk_22 = 1;
        dword_4F45F8->unk_14 = 0;
        set_4F28F0_unk_183(unk_4F5DD8[dword_4F45F8->unk_14].unk_00);
    }
#endif
}

// A string copy with no address and so no database name, named for what it
// does. Evidence: the state's defaults (sub_19AEA0) copy "Player" through
// two temporaries holding the arguments.
inline void copy_string(RwChar *arg_0, const RwChar *arg_4)
{
    while (*arg_4)
    {
        *arg_0 = *arg_4;
        arg_0++;
        arg_4++;
    }
    *arg_0 = 0;
}

// match: ?sub_19AEA0@type_4F28F0@@QAEXXZ @ 0x0019AEA0
// sp-match: ?sub_19AEA0@type_4F28F0@@QAEXXZ @ 0x00128FB0
void type_4F28F0::sub_19AEA0()
{
    // Unused: the image keeps six slots above its inlines' temporaries.
    RwInt32 var_4;
    RwInt32 var_8;
    RwInt32 var_C;
    RwInt32 var_10;
    RwInt32 var_14;
    RwInt32 var_18;

    unk_00 = -1;
    unk_04 = -1;
    unk_08 = 0;
    unk_0C = 1;
    unk_10 = 1;
    unk_14 = 1;
    unk_18 = 1;
    unk_1C = 0;
    unk_20 = 1;
    unk_21 = 1;
    unk_22 = 0;
    unk_28 = 1;
    unk_24 = 1;
    unk_182 = 0;
    unk_2C = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_44 = 0;
    unk_48[0] = 0;
    unk_54 = 1;
    unk_58 = 0;
    unk_5C.sub_D90B0();
    unk_B8.sub_DA0A0();
    unk_38.clear();
    unk_180 = 1;
    unk_181 = 1;
    copy_string(unk_183, "Player");
}

// match: ?sub_19B000@@YAXH@Z @ 0x0019B000
// sp-match: ?sub_19B000@@YAXH@Z @ 0x00129150
// Sets the level (a negative one clears it).
void sub_19B000(RwInt32 arg_0)
{
    if (dword_4F28F0)
    {
        if (arg_0 >= 0)
        {
            dword_4F28F0->unk_08 = 1;
            dword_4F28F0->unk_10 = arg_0;
            dword_4F28F4 = arg_0;
        }
        else
            dword_4F28F0->unk_08 = 0;
    }
}

// match: ?sub_19B050@@YAHXZ @ 0x0019B050
// sp-match: ?sub_19B050@@YAHXZ @ 0x00129180
RwInt32 sub_19B050()
{
    return dword_4F28F4;
}

// match: ?sub_19B060@@YAPBDH@Z @ 0x0019B060
// sp-match: ?sub_19B060@@YAPBDH@Z @ 0x00129190
// The level arg_0's name, once there is a state.
const RwChar *sub_19B060(RwInt32 arg_0)
{
    // The levels' names (0x42B718): a static of this function, its literals come out
    // with it, after sub_19AAB0's, as the image has them.
#ifdef CODFH_SP // single player's story levels (SP 0x328528, 39 names and 0)
    static const RwChar *off_42B718[40] = {
        "L_NULL", "L_1_1", "L_1_1_B", "L_1_1_C", "L_1_2", "L_1_2_B", "L_1_2_C", "L_1_3_A",
        "L_1_3_B", "L_1_3_C", "L_1_4", "L_1_5", "L_1_5_B", "L_1_5_C", "L_2_1", "L_2_1_B",
        "L_2_1_C", "L_2_2", "L_2_2_B", "L_2_2_C", "L_2_3", "L_2_4", "L_2_5", "L_2_6", "L_3_1",
        "L_3_1_B", "L_3_1_C", "L_3_2", "L_3_2_B", "L_3_2_C", "L_3_3", "L_3_3_B", "L_3_3_C",
        "L_3_4", "L_3_4_B", "L_3_4_C", "L_3_5", "L_3_5_B", "L_3_5_C", 0
    };
#else
    static const RwChar *off_42B718[10] = { "L_NULL", "MP_1", "MP_2", "MP_4", "MP_5", "MP_6", "MP_7", "MP_9", "MP_10", 0 };
#endif
    if (dword_4F28F0)
        return off_42B718[arg_0];
    return 0;
}

// match: ?sub_19B080@@YAHXZ @ 0x0019B080
// sp-match: ?sub_19B080@@YAHXZ @ 0x001291B0
RwInt32 sub_19B080()
{
    if (dword_4F28F0)
        return dword_4F28F0->unk_24;
    return -1;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_1291D0@@YAXH@Z @ 0x001291D0
// Sets the difficulty (sub_19B080's), once there is a state: single player's
// front end sets it from its options (SP 0xB013E, 0xA4DC7).
void sp_sub_1291D0(RwInt32 arg_0)
{
    if (dword_4F28F0)
        dword_4F28F0->unk_24 = arg_0;
}
#endif

// match: ?sub_19B0A0@@YAHXZ @ 0x0019B0A0
// sp-match: ?sub_19B0A0@@YAHXZ @ 0x001291F0
// The language.
RwInt32 sub_19B0A0()
{
    if (dword_4F28F0)
        return dword_4F28F0->unk_34;
    return dword_4F28FC;
}

// match: ?sub_19B0C0@@YAXH@Z @ 0x0019B0C0
// sp-match: ?sub_19B0C0@@YAXH@Z @ 0x00129210
void sub_19B0C0(RwInt32 arg_0)
{
    if (dword_4F28F0)
        dword_4F28F0->unk_34 = arg_0;
    dword_4F28FC = arg_0;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_129230@@YAEXZ @ 0x00129230
// The state's byte unk_0C (1 before there is a state): single player's
// front end reads it for its options (SP 0xA59F7, 0xA5BF5).
RwUInt8 sp_sub_129230()
{
    if (dword_4F28F0)
        return dword_4F28F0->unk_0C;
    return 1;
}

// sp-match: ?sp_sub_129240@@YAXE@Z @ 0x00129240
// Sets the state's byte unk_0C (SP 0xA59BE jumps here).
void sp_sub_129240(RwUInt8 arg_0)
{
    if (dword_4F28F0)
        dword_4F28F0->unk_0C = arg_0;
}
#endif

// Not in the image: a stand-in for a function the original object held last, which
// the link dropped (/OPT:REF) but whose literals stayed first: "end", "error", "no",
// "yes" and the title kinds' names sit after the levels' names (0x3E0134-0x3E017C),
// before their users in later objects (unit_1E3430, XGRAPHICS, unit_216130,
// unit_19CB20's table). A function's literals come out last-referenced first.
// Unreferenced.
void dropped_3E0134(const RwChar **arg_0)
{
    arg_0[0] = "Title";
    arg_0[0] = "Unknown";
    arg_0[0] = "Dashboard";
    arg_0[0] = "Debugger";
    arg_0[0] = "Liveupdate";
    arg_0[1] = "yes";
    arg_0[2] = "no";
    arg_0[3] = "error";
    arg_0[4] = "end";
}

#ifdef CODFH_SP
// Single player links the XDK samples' voice manager (UIXFriends'
// XHVVoiceManager.cpp: three processing modes, the local talkers unregistered
// before the engine is released), whose names the database has; the functions
// the game calls are kept (SP 0x129260-0x129508), the rest /OPT:REF dropped.
// Its class is declared here (no header yet); its users are the Live
// manager's (SP 0x12AB40, 0x12BD30) and the global's initializer (SP 0x21DF90).
// (Its class is declared in game/xboxlive.h.)

// sp-match: ??0CXHVVoiceManager@@QAE@XZ @ 0x00129260
// Initializes member variables
CXHVVoiceManager::CXHVVoiceManager()
{
    m_pXHVEngine            = NULL;
    m_pDSound               = NULL;
    m_dwMaxRemoteTalkers    = 0;
    m_dwNumRemoteTalkers    = 0;
    m_pPlayerVoiceInfo      = NULL;
    for( DWORD i = 0; i < XGetPortCount(); i++ )
    {
        m_bEnabledLocalTalkers[i]   = FALSE;
        m_bVoiceThroughSpeakers[i]  = FALSE;
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?RegisterLocalTalker@CXHVVoiceManager@@QAEJK@Z @ 0x00129290
// Registers a local talker
HRESULT CXHVVoiceManager::RegisterLocalTalker( DWORD dwPort )
{
    HRESULT hr = S_OK;

    hr = m_pXHVEngine->RegisterLocalTalker( dwPort );
    if( FAILED( hr ) )
        return hr;

    m_bEnabledLocalTalkers[ dwPort ] = TRUE;

    return hr;
}
#endif

#ifdef CODFH_SP
// sp-match: ?UnregisterLocalTalker@CXHVVoiceManager@@QAEJK@Z @ 0x001292C0
// Unregisters a local talker
HRESULT CXHVVoiceManager::UnregisterLocalTalker( DWORD dwPort )
{
    HRESULT hr = S_OK;

    m_bEnabledLocalTalkers[ dwPort ] = FALSE;

    hr = m_pXHVEngine->UnregisterLocalTalker( dwPort );
    if( FAILED( hr ) )
        return hr;

    return hr;
}
#endif

#ifdef CODFH_SP
// sp-match: ?RecalculatePriorities@CXHVVoiceManager@@IAEJPAUPlayerVoiceInfo@@@Z @ 0x001292E0
// Calculates and sets the appropriate priorities of the remote talker.
HRESULT CXHVVoiceManager::RecalculatePriorities( PlayerVoiceInfo* pInfo )
{
    XHV_PLAYBACK_PRIORITY speakerPriority = XHV_PLAYBACK_PRIORITY_NEVER;
    for( DWORD dwPort = 0; dwPort < XGetPortCount(); dwPort++ )
    {
        if( !m_bEnabledLocalTalkers[ dwPort ] )
            continue;

        if( !m_bVoiceThroughSpeakers[ dwPort ] )
        {
            // If voice through speakers is disabled, set priority based on
            // muting.
            XHV_PLAYBACK_PRIORITY priority = pInfo->priority[ dwPort ];
            if( pInfo->bMuted[ dwPort ] ||
                pInfo->bRemoteMuted[ dwPort ] )
            {
                priority = XHV_PLAYBACK_PRIORITY_NEVER;
            }
            m_pXHVEngine->SetPlaybackPriority( pInfo->xuid,
                                               dwPort,
                                               priority );
        }
        else
        {
            // If voice through speakers is enabled, turn off headset
            // and set maximum speaker priority based on muting.
            m_pXHVEngine->SetPlaybackPriority( pInfo->xuid,
                                               dwPort,
                                               XHV_PLAYBACK_PRIORITY_NEVER );

            if( !pInfo->bMuted[ dwPort ] &&
                !pInfo->bRemoteMuted[ dwPort ] &&
                pInfo->priority[ dwPort ] < speakerPriority )
            {
                speakerPriority = pInfo->priority[ dwPort ];
            }
        }
    }

    // Set speaker priority based on maximum non-muted priority across
    // all local talkers in voice through speakers mode.
    m_pXHVEngine->SetPlaybackPriority( pInfo->xuid,
                                       XHV_PLAYBACK_TO_SPEAKERS,
                                       speakerPriority );

    return S_OK;
}
#endif

#ifdef CODFH_SP
// sp-match: ?SetVoiceThroughSpeakers@CXHVVoiceManager@@QAEJKH@Z @ 0x001293D0
// Turns voice-through-speakers mode off and on
HRESULT CXHVVoiceManager::SetVoiceThroughSpeakers( DWORD dwPort, BOOL bVoiceThroughSpeakers )
{
    m_bVoiceThroughSpeakers[dwPort] = bVoiceThroughSpeakers;

    // Recalculate the priorities for each remote talker
    for( DWORD i = 0; i < m_dwNumRemoteTalkers; i++ )
    {
        RecalculatePriorities( &m_pPlayerVoiceInfo[ i ] );
    }

    return S_OK;
}
#endif

#ifdef CODFH_SP
// sp-match: ?Shutdown@CXHVVoiceManager@@QAEJXZ @ 0x00129410
// Shuts down the object
HRESULT CXHVVoiceManager::Shutdown()
{
    // Unregister the local talkers first, since this uses the
    // XHVEngine, so we can not release the engine until afterwards.
    for( DWORD i = 0; i < XGetPortCount(); i++ )
    {
        if( m_bEnabledLocalTalkers[ i ] )
        {
            UnregisterLocalTalker( i );
        }
    }

    m_pDSound = NULL;

    if( m_pXHVEngine )
    {
        m_pXHVEngine->Release();
        m_pXHVEngine = NULL;
    }

    if( m_pPlayerVoiceInfo )
    {
        delete[] m_pPlayerVoiceInfo;
        m_pPlayerVoiceInfo = NULL;
    }

    m_dwMaxRemoteTalkers    = 0;
    m_dwNumRemoteTalkers    = 0;

    return S_OK;
}
#endif

#ifdef CODFH_SP
// sp-match: ??1CXHVVoiceManager@@QAE@XZ @ 0x00129470
// Performs any final cleanup that is needed
CXHVVoiceManager::~CXHVVoiceManager()
{
    Shutdown();
}
#endif

#ifdef CODFH_SP
// sp-match: ?Initialize@CXHVVoiceManager@@QAEJPAUIDirectSound@@PAU_XHV_RUNTIME_PARAMS@@PAUITitleXHV@@@Z @ 0x00129480
// Initializes the XHV voice manager
HRESULT CXHVVoiceManager::Initialize( LPDIRECTSOUND8 pDSound,
                                      XHV_RUNTIME_PARAMS* pXHVParams,
                                      ITitleXHV *pITitleXHV )
{
    assert( pDSound );
    assert( pXHVParams );
    assert( pITitleXHV );

    m_pDSound = pDSound;

    // Create the engine
    HRESULT hr = XHVEngineCreate( pXHVParams, &m_pXHVEngine );
    if( FAILED( hr ) )
        return hr;

    // Enable voicechat, loopback modes, and voice-mail only
    m_pXHVEngine->EnableProcessingMode( XHV_LOOPBACK_MODE );
    m_pXHVEngine->EnableProcessingMode( XHV_VOICECHAT_MODE );
    m_pXHVEngine->EnableProcessingMode(XHV_VOICEMAIL_MODE);
    // m_pXHVEngine->EnableProcessingMode( XHV_SR_MODE );

    m_pXHVEngine->SetCallbackInterface( pITitleXHV );

    m_dwMaxRemoteTalkers    = pXHVParams->dwMaxRemoteTalkers;

    // Allocate space for the PlayerVoiceInfo structs
    m_pPlayerVoiceInfo = new PlayerVoiceInfo[ m_dwMaxRemoteTalkers ];
    if( NULL == m_pPlayerVoiceInfo )
    {
        Shutdown();
        return E_OUTOFMEMORY;
    }

    return S_OK;
}
#endif
