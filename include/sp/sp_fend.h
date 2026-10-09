/*
 * Single player's front end (src/sp/units/sp_fend.cpp, SP 0xAD730-0xB19AB, and its profile
 * name editor, src/sp/units/sp_fendname.cpp, SP 0xB2110-0xB2973): screens played from Rt2d
 * maestro files (Flash movies converted by RenderWare's 2d animation toolkit). The game finds
 * the movies' string labels (buttons, "url..." actions, "sound..." cues) by name, receives the
 * maestro's GETURL messages (Rt2dMessageHandlerCallBack, SP 0xADD40) and sends its own
 * button presses back as button-by-label messages. Not in the multiplayer image, which uses
 * kujuUI and UIX screens instead.
 *
 * The Rt2d animation declarations are copied from RenderWare 3.7.2
 * RWSDK/tool/2danim/rt2danim.h (Rt2dMessage, Rt2dStringLabel, the prototypes); Rt2dObject is
 * reduced to its type (RWSDK/tool/2d/object.h).
 */
#ifndef SP_SP_FEND_H
#define SP_SP_FEND_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rt2d.h"
#include "rw/baengine.h"
#include "rw/bastream.h"

#ifdef CODFH_SP
// shape: SP 0xAFEE0's selector copy and one-word flag reads.
union sp_movie_selection_encoding
{
    RwUInt64 raw;
    struct { RwUInt32 low, high; } words;
};
struct sp_movie_flag_word
{
    RwInt32 bits;
};

// shape: SP 0xAD990's copied path/id aggregate.
union sp_path_encoding
{
    RwUInt64 raw;
    struct { RwUInt32 low, high; } words;
};
#endif

// RenderWare's texture dictionary (rwcore.h's stock definition; the game's
// RenderWare headers keep it opaque).
struct RwTexDictionary
{
    RwObject object;
    RwLinkList texturesInDict;
    RwLLLink lInInstance;
};

typedef struct Rt2dObject Rt2dObject;
struct Rt2dObject
{
    RwInt32 type;               // rt2DOBJECTTYPESCENE 1, rt2DOBJECTTYPEOBJECTSTRING 4
};
typedef struct Rt2dAnim Rt2dAnim;
typedef struct Rt2dAnimProps Rt2dAnimProps;

typedef struct Rt2dMessage Rt2dMessage;
struct Rt2dMessage
{
    RwUInt32 messageType;
    RwInt32 index;
    RwInt32 intParam1;
    RwInt32 intParam2;
};

typedef struct Rt2dStringLabel Rt2dStringLabel;
struct Rt2dStringLabel
{
    RwUInt32 entityType;
    RwInt32 nameIndex;
    void *internalData;
    void *userData;
};

typedef Rt2dObject *(*Rt2dObjectCallBack)(Rt2dObject *object, Rt2dObject *parent, void *data);
typedef Rt2dMaestro *(*Rt2dMaestroAnimationsCallBack)(Rt2dMaestro *maestro, Rt2dAnim *anim,
                                                       Rt2dAnimProps *props, void *pData);
typedef Rt2dMessage *(*Rt2dMessageHandlerCallBack)(Rt2dMaestro *maestro, Rt2dMessage *message);

extern "C"
{
extern Rt2dObject *Rt2dSceneForAllChildren(Rt2dObject *scene, Rt2dObjectCallBack callback,
                                           void *pData);
extern Rt2dObject *Rt2dSceneUpdateLTM(Rt2dObject *scene);
extern RwBool Rt2dObjectIsScene(Rt2dObject *object);
extern RwBool Rt2dObjectIsObjectString(Rt2dObject *object);
extern Rt2dObject *Rt2dObjectMTMScale(Rt2dObject *object, RwReal x, RwReal y);
extern Rt2dObject *Rt2dObjectMTMTranslate(Rt2dObject *object, RwReal x, RwReal y);
extern Rt2dObject *Rt2dObjectStringSetText(Rt2dObject *object, const RwChar *text);
extern Rt2dAnim *Rt2dAnimGotoKeyFrameListByIndex(Rt2dAnim *anim, Rt2dAnimProps *props,
                                                 RwInt32 frameIndex);
extern RwInt32 Rt2dAnimGetPrevFrameIndex(Rt2dAnim *anim);
extern Rt2dMaestro *Rt2dMaestroStreamRead(Rt2dMaestro *maestro, RwStream *stream);
extern Rt2dMaestro *Rt2dMaestroForAllAnimations(Rt2dMaestro *maestro,
                                                Rt2dMaestroAnimationsCallBack callback,
                                                void *data);
extern Rt2dMaestro *Rt2dMaestroForAllVisibleAnimations(Rt2dMaestro *maestro,
                                                       Rt2dMaestroAnimationsCallBack callback,
                                                       void *data);
extern Rt2dAnim *Rt2dMaestroGetAnimationsByIndex(Rt2dMaestro *maestro, RwInt32 index);
extern Rt2dAnimProps *Rt2dMaestroGetAnimPropsByIndex(Rt2dMaestro *maestro, RwInt32 index);
extern Rt2dMaestro *Rt2dMaestroUpdateAnimations(Rt2dMaestro *maestro);
extern Rt2dMaestro *Rt2dMaestroAddDeltaTime(Rt2dMaestro *maestro, RwReal deltaTime);
extern Rt2dObject *Rt2dMaestroGetScene(Rt2dMaestro *maestro);
extern Rt2dMaestro *Rt2dMaestroRender(Rt2dMaestro *maestro);
extern Rt2dBBox *Rt2dMaestroGetBBox(Rt2dMaestro *maestro);
extern Rt2dMaestro *Rt2dMaestroSetMessageHandler(Rt2dMaestro *maestro,
                                                 Rt2dMessageHandlerCallBack handler);
extern Rt2dMaestro *Rt2dMaestroPostMessages(Rt2dMaestro *maestro, Rt2dMessage *message,
                                            RwInt32 num);
extern Rt2dMaestro *Rt2dMaestroProcessMessages(Rt2dMaestro *maestro);
extern Rt2dMessage *Rt2dMessageHandlerDefaultCallBack(Rt2dMaestro *maestro,
                                                      Rt2dMessage *message);
extern Rt2dStringLabel *Rt2dMaestroFindStringLabel(Rt2dMaestro *maestro, RwInt32 entityType,
                                                   const RwChar *lookupName, RwInt32 *index);
// The image's Rt2d library keeps a user pointer in its maestro (+0x158, the word
// src/rw/tool/2danim/maestro.h's Rt2dMaestro calls unknown): its getter and setter (SP
// 0x170B80, 0x170B90; not in RenderWare 3.7.2). The front end keeps its screen there.
extern void *sp_sub_170B80(Rt2dMaestro *maestro);
extern Rt2dMaestro *sp_sub_170B90(Rt2dMaestro *maestro, void *data);
// The text of a string object (RenderWare's Rt2dObjectStringGetText, SP 0x16BB70).
extern const RwChar *Rt2dObjectStringGetText(Rt2dObject *object);
// Sets the font render callback the front end's strings are drawn through (SP 0x16BE90,
// after Rt2dObjectStringRender; it keeps it at SP 0x40693C). sp_sub_A59D0 sets sp_sub_ADF80.
extern void sp_sub_16BE90(Rt2dFont *(*callback)(Rt2dFont *, const RwChar *, RwReal, RwV2d *,
                                                Rt2dBrush *));
}

// What sp_sub_ADF20 finds for an animation label: the animation, its props and the label.
struct type_sp_ADF20
{
    Rt2dAnim *unk_00;
    Rt2dAnimProps *unk_04;
    Rt2dStringLabel *unk_08;
};

// The list sp_sub_ADD00 collects a scene's string objects into.
struct type_sp_ADD00
{
    RwUInt32 unk_00;            // the count
    RwUInt32 unk_04;            // the room
    Rt2dObject **unk_08;
};

// A front end screen: one maestro, its texture dictionaries, the pad's buttons as the
// maestro's button labels and the last twenty pad buttons pressed (for the cheat codes).
// Named for its constructor; its vtable (SP 0x2E4150) holds only the message handler, pure.
struct type_sp_AD970
{
    type_sp_AD970();
    ~type_sp_AD970();
    // Receives the maestro's GETURL message for the string label arg_0.
    virtual void vf_000(RwInt32 arg_0) = 0;

    // Sets it up (arg_0 kept in unk_178); its unk_06.
    bool sp_sub_AD990(RwCamera *arg_0);
    // Lets the maestro and its texture dictionaries go.
    void sp_sub_ADA70();
    // Whether the last arg_4 pad buttons pressed were arg_0's (and, with arg_8, the second
    // pad's button 0x21 is down).
    bool sp_sub_ADAE0(const RwInt32 *arg_0, RwUInt32 arg_4, bool arg_8);
    // Draws the maestro on the camera arg_0 (the 2d camera when 0).
    void sp_sub_ADB50(RwCamera *arg_0);
    // Finds the string label arg_0 of the type arg_8 into arg_4.
    void sp_sub_ADE30(const RwChar *arg_0, RwInt32 *arg_4, RwInt32 arg_8);
    // Finds the pad buttons' labels.
    void sp_sub_ADE60();
    // The animation labelled arg_0.
    type_sp_ADF20 sp_sub_ADF20(const RwChar *arg_0);
    // Steps it by arg_0 frames: sends the pad's new presses to the maestro.
    void sp_sub_AE0D0(RwReal arg_0);
    // Reads the maestro file arg_0 with the texture dictionary arg_4 and the fonts' arg_8.
    bool sp_sub_AE3C0(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8);
    // Lets it go (sp_sub_ADA70): the language and profile screens call it too (SP 0xA587E,
    // 0xA5730), so it is the base's.
    void sp_sub_AE7D0();

    bool unk_04;                // it is done
    bool unk_05;                // the pad is ignored
    bool unk_06;                // set up
    RwUInt8 unk_07;
    RwInt32 unk_08;             // the screen's height
    RwInt32 unk_0C;             // and width
    bool unk_10;                // the fonts' dictionary is someone else's
    // Not a byte array: sp_sub_A5780's language screen local gets no /GS cookie (SP 0xA5795).
    RwUInt8 unk_11;
    RwUInt8 unk_12;
    RwUInt8 unk_13;
    RwInt32 unk_14[0x4E];
    RwInt32 unk_14C;            // btnUp
    RwInt32 unk_150;            // btnDown
    RwInt32 unk_154;            // btnLeft
    RwInt32 unk_158;            // btnRight
    RwInt32 unk_15C;            // btnAction
    RwInt32 unk_160;            // btnCancel
    RwInt32 unk_164;            // btnSquare
    RwInt32 unk_168;            // btnStart
    RwInt32 unk_16C;            // btnSelect
    RwInt32 unk_170;
    RwInt32 unk_174;
    RwCamera *unk_178;
    Rt2dMaestro *unk_17C;
    RwTexDictionary *unk_180;
    RwTexDictionary *unk_184;   // the fonts'
    RwUInt32 unk_188;           // the pad buttons pressed (at most 20)
    RwInt32 unk_18C[20];
};

Rt2dObject *sp_sub_ADD00(Rt2dObject *arg_0, Rt2dObject *arg_4, void *arg_8);
Rt2dMessage *sp_sub_ADD40(Rt2dMaestro *arg_0, Rt2dMessage *arg_4);
Rt2dMaestro *sp_sub_ADDF0(Rt2dMaestro *arg_0, Rt2dAnim *arg_4, Rt2dAnimProps *arg_8, void *arg_C);
Rt2dFont *sp_sub_ADF80(Rt2dFont *arg_0, const RwChar *arg_4, RwReal arg_8, RwV2d *arg_C,
                       Rt2dBrush *arg_10);
void sp_sub_AE0B0();
void sp_sub_AE5A0();

// The language screen (its handler SP 0xAD7C0, vtable SP 0x2E37F0).
struct type_sp_AD730 : type_sp_AD970
{
    bool sp_sub_AD730();
    void sp_sub_AD740(RwReal arg_0);
    void sp_sub_AD750(RwCamera *arg_0);
    void sp_sub_AD760();
    virtual void vf_000(RwInt32 arg_0);
    bool sp_sub_AD8C0(const RwChar *arg_0, const RwChar *arg_4, RwTexDictionary *arg_8);

    RwInt32 unk_1DC;            // languageSelected
    RwInt32 unk_1E0;            // streamBG
    RwInt32 unk_1E4;            // soundScroll
    RwInt32 unk_1E8;            // soundSelect
};

struct type_sp_AE5D0;
// A step's callback of the main menu (sp_sub_AE800): called with its data (after unk_08 steps)
// while it returns true, unk_0C times (-1: always).
typedef bool (*type_sp_AE5D0_fn)(type_sp_AE5D0 *arg_0, void *arg_4);
struct type_sp_AE5D0_cb
{
    type_sp_AE5D0_fn unk_00;
    void *unk_04;
    RwInt32 unk_08;
    RwInt32 unk_0C;
};

// A level of the level select: its clip and the level (sub_19B000's number).
struct type_sp_AE5D0_level
{
    type_sp_ADF20 unk_00;
    RwInt32 unk_0C;
};

// The main menu (its handler SP 0xB07C0, vtable SP 0x2E37EC): profiles, the level select by
// act, options, extras (making-of movies, galleries) and cheats.
struct type_sp_AE5D0 : type_sp_AD970
{
    // Inline (SP 0xA5A63, in sp_sub_A59D0).
    type_sp_AE5D0()
    {
        unk_7CE = false;
        unk_7CF = true;
        unk_7D0 = false;
        unk_7D1 = false;
        unk_7D4 = 0.0f;
        unk_7D8 = 3.402823466e+38f;     // FLT_MAX
    }
    void sp_sub_AE5D0(RwCamera *arg_0);
    bool sp_sub_AE6F0();
    void sp_sub_AE7A0(RwCamera *arg_0);
    bool sp_sub_AE7E0(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8);
    bool sp_sub_AE800(const type_sp_AE5D0_cb *arg_0);
    void sp_sub_AE860();
    void sp_sub_AE8C0();
    void sp_sub_AE980();
    void sp_sub_AE9A0();
    bool sp_sub_AEB20(RwInt32 arg_0);
    void sp_sub_AEB80();
    RwInt32 sp_sub_AF700(const RwChar *arg_0);
    void sp_sub_AF730(const RwChar *arg_0, RwInt32 arg_4);
    void sp_sub_AF760(RwInt32 arg_0);
    void sp_sub_AF7A0(RwReal arg_0);
    void sp_sub_AF7F0();
    void sp_sub_AFCA0();
    void sp_sub_B0130();
    void sp_sub_B0220();
    bool sp_sub_B0250(RwInt32 arg_0);
    bool sp_sub_B0300(RwInt32 arg_0);
    bool sp_sub_B0590(RwInt32 arg_0);
    bool sp_sub_B0770(RwInt32 arg_0);
    virtual void vf_000(RwInt32 arg_0);

    RwUInt32 unk_1DC;           // the act shown
    RwUInt32 unk_1E0;           // its level selected
    RwInt32 unk_1E4;            // the furthest level reached
    bool unk_1E8;
    RwUInt8 unk_1E9[0x3];
    type_sp_AE5D0_level unk_1EC[3][9];
    type_sp_ADF20 unk_39C[3];   // "/mcAct1/".."/mcAct3/"
    RwInt32 unk_3C0;            // the extras' item selected
    RwInt32 unk_3C4[5];         // btnDownAction, btnGotoAct1..3, vBtnJumpToMain
    RwInt32 unk_3D8;            // urlQuit
    RwInt32 unk_3DC;            // enableBG
    RwInt32 unk_3E0;            // disableBG
    RwInt32 unk_3E4;            // enableDemo
    RwInt32 unk_3E8;            // disableDemo
    RwInt32 unk_3EC;            // streamProfileSelect
    RwInt32 unk_3F0;            // streamContinueGame
    RwInt32 unk_3F4;            // streamOptions
    RwInt32 unk_3F8;            // streamExtras
    RwInt32 unk_3FC;            // streamUnlockables
    RwInt32 unk_400;            // streamCheats
    RwInt32 unk_404;            // streamMusic
    RwInt32 unk_408;            // soundPressStart
    RwInt32 unk_40C;            // soundPSScroll
    RwInt32 unk_410;            // soundPSSelect
    RwInt32 unk_414;            // soundPSNew
    RwInt32 unk_418;            // soundMSScroll
    RwInt32 unk_41C;            // soundMSSelect
    RwInt32 unk_420;            // soundCGScroll
    RwInt32 unk_424;            // soundCGScrollAcross
    RwInt32 unk_428;            // soundCGSelect
    RwInt32 unk_42C;            // soundCGBack
    RwInt32 unk_430;            // soundOSScrollDown
    RwInt32 unk_434;            // soundOSScrollAcross
    RwInt32 unk_438;            // soundOSSelect
    RwInt32 unk_43C;            // soundOSBack
    RwInt32 unk_440;            // soundCCScroll
    RwInt32 unk_444;            // soundCCSelect
    RwInt32 unk_448;            // soundCCBack
    RwInt32 unk_44C;            // soundCSBack
    RwInt32 unk_450;            // soundEXScroll
    RwInt32 unk_454;            // soundEXSelect
    RwInt32 unk_458;            // soundEXBack
    RwInt32 unk_45C;            // soundDOScroll
    RwInt32 unk_460;            // soundDOSelect
    RwInt32 unk_464;            // soundDOBack
    RwInt32 unk_468;            // soundUNScroll
    RwInt32 unk_46C;            // soundUNSelect
    RwInt32 unk_470;            // soundUNBack
    RwInt32 unk_474;            // soundGAScroll
    RwInt32 unk_478;            // soundGASelect
    RwInt32 unk_47C;            // soundGABack
    RwInt32 unk_480;            // soundCHScroll
    RwInt32 unk_484;            // soundCHSelect
    RwInt32 unk_488;            // soundLPScroll
    RwInt32 unk_48C;            // soundLPSelect
    RwInt32 unk_490;            // soundLPBack
    RwInt32 unk_494;            // enteringProfileSelect
    RwInt32 unk_498;            // enableMemCardMonitoring
    RwInt32 unk_49C;            // selectProfile
    RwInt32 unk_4A0;            // createNewProfile
    RwInt32 unk_4A4;            // leavingSelectProfile
    RwInt32 unk_4A8;            // urlLevelMamaevKurgen
    RwInt32 unk_4AC;            // urlLevel1_1B
    RwInt32 unk_4B0;            // urlLevelTractorFactory
    RwInt32 unk_4B4;            // urlLevel1_2B
    RwInt32 unk_4B8;            // urlLevelTrainStation
    RwInt32 unk_4BC;            // urlLevel1_3B
    RwInt32 unk_4C0;            // urlLevelPitomnik
    RwInt32 unk_4C4;            // urlLevelTatsinskaya
    RwInt32 unk_4C8;            // urlLevel1_5B
    RwInt32 unk_4CC;            // urlLevelMatmata
    RwInt32 unk_4D0;            // urlLevel2_1B
    RwInt32 unk_4D4;            // urlLevelKsarTarsine
    RwInt32 unk_4D8;            // urlLevel2_2B
    RwInt32 unk_4DC;            // urlLevelAachen
    RwInt32 unk_4E0;            // urlLevel3_1B
    RwInt32 unk_4E4;            // urlLevel3_1C
    RwInt32 unk_4E8;            // urlLevelStavelot
    RwInt32 unk_4EC;            // urlLevel3_2B
    RwInt32 unk_4F0;            // urlLevelTillet1
    RwInt32 unk_4F4;            // urlLevel3_3B
    RwInt32 unk_4F8;            // urlLevelTillet2
    RwInt32 unk_4FC;            // urlLevel3_4B
    RwInt32 unk_500;            // urlLevelRemagen
    RwInt32 unk_504;            // urlLevel3_5B
    RwInt32 unk_508;            // urlLevel3_5C
    RwInt32 unk_50C;            // playAct1Movie
    RwInt32 unk_510;            // playAct2Movie
    RwInt32 unk_514;            // playAct3Movie
    RwInt32 unk_518;            // urlPlayMakingOf1
    RwInt32 unk_51C;            // urlPlayMakingOf2
    RwInt32 unk_520;            // urlPlayMakingOf3
    RwInt32 unk_524;            // movieCredits
    RwInt32 unk_528;            // movieAnimReel
    RwInt32 unk_52C;            // movieTeaser
    RwInt32 unk_530[7];
    RwInt32 unk_54C;            // urlRefresh
    RwInt32 unk_550;            // urlSaveOptions
    RwInt32 unk_554;            // urlResetOptions
    RwInt32 unk_558;            // enteringControllerConfig
    RwInt32 unk_55C;            // setControllerConfig
    RwInt32 unk_560;            // setOutgoingCC
    RwInt32 unk_564;            // shakeIt
    RwInt32 unk_568;            // profileOptionsSave
    RwInt32 unk_56C;            // profileOptionsLoad
    RwInt32 unk_570;            // profileOptionsCreateNew
    RwInt32 unk_574;            // urlEnterCheatsScreen
    RwInt32 unk_578;            // urlExitCheatsScreen
    RwInt32 unk_57C;            // urlCheckButtonSequence
    RwInt32 unk_580;            // urlBigHeadsOff
    RwInt32 unk_584;            // urlBigHeadsOn
    RwInt32 unk_588;            // urlRicochetPlayerOff
    RwInt32 unk_58C;            // urlRicochetPlayerOn
    RwInt32 unk_590;            // urlHeadShotKillsOff
    RwInt32 unk_594;            // urlHeadShotKillsOn
    RwInt32 unk_598;            // urlRicochetAllOff
    RwInt32 unk_59C;            // urlRicochetAllOn
    RwInt32 unk_5A0;            // urlShrinkingSoldiersOff
    RwInt32 unk_5A4;            // urlShrinkingSoldiersOn
    RwInt32 unk_5A8;            // urlOneShotKillsOff
    RwInt32 unk_5AC;            // urlOneShotKillsOn
    RwInt32 unk_5B0;            // urlBigNSmallOff
    RwInt32 unk_5B4;            // urlBigNSmallOn
    RwInt32 unk_5B8;            // urlPersonalScreensEnter
    RwInt32 unk_5BC;            // urlGalleryEnter
    RwInt32 unk_5C0;            // urlSelectedAnimation
    RwInt32 unk_5C4;            // urlSelectedArtwork
    RwInt32 unk_5C8;            // urlSelectedMaking1
    RwInt32 unk_5CC;            // urlSelectedMaking2
    RwInt32 unk_5D0;            // urlSelectedMaking3
    RwInt32 unk_5D4;            // urlArtGalleryEnter
    RwInt32 unk_5D8;            // urlSlideshowLeave
    RwInt32 unk_5DC;            // urlSlideshowPlay
    RwInt32 unk_5E0;            // urlSlideshowPause
    RwInt32 unk_5E4;            // urlSlideshowPrev
    RwInt32 unk_5E8;            // urlSlideshowNext
    RwInt32 unk_5EC;            // urlDisableRender
    RwInt32 unk_5F0;            // enteringLevelSelect
    RwInt32 unk_5F4;            // updateLevelStates
    RwInt32 unk_5F8;            // selectPreviousAct
    RwInt32 unk_5FC;            // selectNextAct
    RwInt32 unk_600;            // selectPreviousLevel
    RwInt32 unk_604;            // selectNextLevel
    RwInt32 unk_608;            // checkUnlockSPLvlsMBS
    RwInt32 unk_60C;            // urlMultiplayer
    Rt2dObject *unk_610[4][2];  // the profile slots' texts ("$slot1".."$slot4")
    RwUInt8 unk_630[0xF0];
    type_sp_AE5D0_cb unk_720[10];
    RwChar unk_7C0[0xE];        // an empty slot's text
    bool unk_7CE;
    bool unk_7CF;
    bool unk_7D0;
    bool unk_7D1;
    RwUInt8 unk_7D2[0x2];
    RwReal unk_7D4;
    RwReal unk_7D8;
    RwInt32 unk_7DC;            // 1: a gallery is up
};

bool sp_sub_AE960(type_sp_AE5D0 *arg_0, void *arg_4);
void sp_sub_AE970(RwCamera *arg_0, void *arg_4);
void sp_sub_AE9B0();
void sp_sub_AE9E0(RwCamera *arg_0, RwInt32 arg_4);
bool sp_sub_AFCC0(type_sp_AE5D0 *arg_0, void *arg_4);
bool sp_sub_AFDD0(type_sp_AE5D0 *arg_0, void *arg_4);
bool sp_sub_AFEE0(type_sp_AE5D0 *arg_0, void *arg_4);
bool sp_sub_AFFC0(type_sp_AE5D0 *arg_0, void *arg_4);
bool sp_sub_B0700(type_sp_AE5D0 *arg_0, void *arg_4);

// What the profile name editor hands its callback (sp_sub_B21B0) when the name is accepted.
struct type_sp_B21B0
{
    RwChar *unk_00;             // the name
    RwInt32 unk_04;             // the profile's slot
    void *unk_08;               // the editor (the draw callback's data)
    struct type_D9CF0 *unk_0C;  // the memory unit
    RwInt32 unk_10;
    RwCamera *unk_14;
};

// The profile name editor (src/sp/units/sp_fendname.cpp; its handler SP 0xB2470, vtable SP
// 0x2E37E8): a keyboard clip, the name typed (at most 11 characters) and what to do with it.
struct type_sp_B2110 : type_sp_AD970
{
    // Inline (SP 0xA562A, in sp_sub_A55F0).
    type_sp_B2110()
    {
        unk_248 = 0.0f;
        unk_24C = 3.402823466e+38f;     // FLT_MAX
    }
    void sp_sub_B2110(RwReal arg_0);
    void sp_sub_B2180(bool (*arg_0)(type_sp_B21B0 *, void *), void *arg_4);
    void sp_sub_B2420();
    virtual void vf_000(RwInt32 arg_0);
    void sp_sub_B2750(RwInt32 arg_0, struct type_D9CF0 *arg_4, RwCamera *arg_8, RwInt32 arg_C);
    bool sp_sub_B2810(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8);
    // Draws it: identical to type_sp_AD730's and folded into it (/OPT:ICF, SP 0xAD750).
    void sp_sub_AD750(RwCamera *arg_0);

    RwInt32 unk_1DC;            // 1: left with B
    RwInt32 unk_1E0;            // kbHit
    RwInt32 unk_1E4;            // soundScroll
    RwInt32 unk_1E8;            // playBGStream
    Rt2dObject *unk_1EC;        // the name's text ("$playernameedit")
    type_sp_ADF20 unk_1F0;      // "/imcEditor/"
    type_sp_ADF20 unk_1FC;      // "/imcEditor/imcHorizontalEdit/"
    type_sp_ADF20 unk_208;      // "/imcEditor/imcHorizontalEditLarge/"
    type_sp_ADF20 unk_214;      // "/imcEditor/imcKeyboard/"
    RwInt32 unk_220;            // the name's length
    RwInt32 unk_224;            // 0, or -0x20 for capitals
    RwChar unk_228[0xC];
    bool (*unk_234)(type_sp_B21B0 *, void *);
    void *unk_238;
    struct type_D9CF0 *unk_23C;
    RwInt32 unk_240;
    RwInt32 unk_244;
    RwReal unk_248;
    RwReal unk_24C;
};

bool sp_sub_B21B0(type_sp_B21B0 *arg_0, void *arg_4);
void sp_sub_B21A0(RwCamera *arg_0, void *arg_4);
Rt2dObject *sp_sub_B23A0(Rt2dObject *arg_0, Rt2dObject *arg_4, void *arg_8);

// Sets the text of the string objects arg_0 (arg_4 of them) from the table arg_8 (SP 0xB39F0).
bool sp_sub_B39F0(Rt2dObject **arg_0, RwUInt32 arg_4, const RwChar *arg_8);

#endif
