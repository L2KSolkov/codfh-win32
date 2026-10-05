/*
 * The animated textures (unit_143CE0): type_143DC0, a named texture
 * animation (0x108 bytes) holding up to 16 textures and a sequence of up to
 * 32 frames (indices into them) played at unk_2C frames a second, with the
 * materials it drives (type_143D90 entries in a list); the manager
 * unk_4E5CC8 (game/gameloop.h) keeps them in a list of its own. Built by the
 * section streaming (unit_141BB0, sub_142D70).
 */
#ifndef TYPE_143DC0_H
#define TYPE_143DC0_H

#include "rw/ostypes.h"
#include "rw/rpmaterial.h"
#include "rw/batextur.h"
#include "rw/bastream.h"

// The empty base both kinds of list entry share: its constructor is 0x6FCD0
// (folded by /OPT:ICF with the functions returning this) and its destructor
// pDtor (0x1E41C0); the list links its first two words.
struct type_6FCD0
{
    void *unk_00;
    void *unk_04;

    type_6FCD0();
    ~type_6FCD0();
    // Unlinks it from its list (a template instantiation's method).
    void sub_16BA30();
};

// A material an animation drives, and a value kept with it (sub_144110
// adds one, sub_1441A0 finds one by both). Its getters are shared (/OPT:ICF)
// with other classes' (sub_FB710, sub_6CB40); its destructor is sub_39440.
struct type_143D90 : type_6FCD0
{
    RpMaterial *unk_08;
    RwInt32 unk_0C;

    type_143D90(RpMaterial *arg_0, RwInt32 arg_4);
    ~type_143D90();
    RpMaterial *sub_FB710();
    RwInt32 sub_6CB40();
};

// The lists (a head, a sentinel's link and an owner; sub_16B830 empties
// one) and their iterator: out-of-line methods named for their addresses,
// defined in their own unit (unit_16B810); both destructors are pDtor.
struct type_16B810
{
    void *unk_00;
    void *unk_04;
    void *unk_08;

    type_16B810();
    ~type_16B810();
    void sub_16B830();
    void sub_16B860(type_6FCD0 *arg_0);
    void sub_16B8B0(type_6FCD0 *arg_0);
};
struct type_16B900
{
    type_16B810 *unk_00;
    type_6FCD0 *unk_04;

    type_16B900(type_16B810 *arg_0);
    ~type_16B900();
    bool sub_16B9D0();
    type_6FCD0 *sub_16B990();
    // Steps to the next node and the previous one, returning it.
    type_6FCD0 *sub_16B930();
    type_6FCD0 *sub_16B960();
    type_6FCD0 *sub_1E3480();
    void sub_16BA10(RwInt32 arg_0);
};

struct type_143DC0 : type_6FCD0
{
    RwChar unk_08[0x20];        // its name (sub_144260)
    RwInt32 unk_28;             // frames since the last step
    RwInt32 unk_2C;             // steps a second (60 at first, 1 after
                                // sub_143F10)
    RwInt32 unk_30;             // the current step
    type_16B810 unk_34;         // the materials (type_143D90)
    RwTexture *unk_40[0x10];    // its textures (sub_144070)
    RwInt32 unk_80;             // how many
    RwInt32 unk_84[0x20];       // the steps' textures (sub_1440C0)
    RwInt32 unk_104;            // how many

    type_143DC0();
    ~type_143DC0();
    void sub_143F10();
    void sub_143F60();
    void sub_144070(RwTexture *arg_0);
    void sub_1440C0(RwInt32 arg_0);
    void sub_144110(RpMaterial *arg_0, RwInt32 arg_4);
    type_143D90 *sub_1441A0(RpMaterial *arg_0, RwInt32 arg_4);
    void sub_144260(const RwChar *arg_0);

    // An inline setter for unk_2C, with no address and so no database name;
    // named for its field. Evidence: the section streaming's sub_142D70
    // stores the value through a temporary placed after the frame's `new`
    // temporaries (an inline's local) and no parameter slot (a by-value
    // parameter would take one).
    void set_unk_2C(const RwInt32 &arg_0)
    {
        RwInt32 r = arg_0;
        unk_2C = r;
    }
};
typedef RwChar type_143DC0_size_check[sizeof(type_143DC0) == 0x108 ? 1 : -1];

// The spline paths' table (256; sub_143D60 adds one and returns its index),
// its count, a flag set by sub_143CE0 and cleared by sub_143D40, and a word
// sub_143CE0 clears.
struct SplinePath;
extern SplinePath *dword_4CFA18[0x100];
extern RwInt32 dword_4CFE18;
extern RwUInt32 dword_4CFE1C;
extern RwInt32 dword_4CFE20;

// The shared texture dictionary (the database's name, 0x4CFE28): created
// by sub_1446B0, its textures destroyed with it by sub_1446C0 (through
// fpCallBack), and read into by sub_144740.
extern RwTexDictionary *object;
void sub_1446B0();
void sub_1446C0();
RwTexture *fpCallBack(RwTexture *texture, void *pData);

// What sub_144740 (RenderWare's RwTexDictionaryStreamRead, adapted) uses:
// the dictionary's header (its texture count and device), the open device
// (RenderWare's globals are static in this build: byte_5200F0), the native
// texture reader (dword_520190) and the plugin registries.
struct type_144740
{
    RwUInt16 unk_00;
    RwUInt16 unk_02;
};
#define rwID_STRUCT 0x01
// The stream versions RenderWare reads (RWSDK badevice.h's names).
#define rwLIBRARYBASEVERSION 0x34000 // not an address: a library version
#define rwLIBRARYCURRENTVERSION 0x36003 // not an address: a library version
#define rwID_TEXTURENATIVE 0x15
#define rwDEVICESYSTEMGETID 0x16
struct RwPluginRegistry;
extern "C" RwPluginRegistry textureTKList;
extern "C" RwPluginRegistry texDictTKList;
extern "C" RwBool _rwDeviceSystemRequest(void *device, RwInt32 requestID, void *pOut, void *pInOut,
                                         RwInt32 numIn);
extern "C" const RwPluginRegistry *_rwPluginRegistryReadDataChunks(const RwPluginRegistry *reg,
                                                                   RwStream *stream, void *object);
extern "C" RwTexDictionary *RwTexDictionaryCreate(void);
extern "C" RwTexture *RwTexDictionaryAddTexture(RwTexDictionary *dict, RwTexture *texture);
extern "C" RwBool RwTextureDestroy(RwTexture *texture);
RwTexDictionary *sub_144740(RwStream *arg_0, RwInt32 arg_4);

#endif
