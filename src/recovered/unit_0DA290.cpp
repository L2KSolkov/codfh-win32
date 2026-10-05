// The front end: its world and camera around the shell's screens. The
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rw/baengine.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/startup.h"
#include "game/frontend.h"
#include "types/type_4B8EF0.h"
#include "types/soundbank.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7E80
extern const RwReal flt_3D7E80 = 16.666666f;
// 0x003D7E84
extern const RwReal flt_3D7E84 = 16.666666f;
// 0x004B889C
RwInt32 dword_4B889C;
// 0x004B88B0
RwCamera *dword_4B88B0;
// 0x004B88B8
bool byte_4B88B8;
// 0x004B8920
bool byte_4B8920;
// 0x004B8924
RwInt32 dword_4B8924;
// 0x004B9E48
#ifndef CODFH_PLAIN
RwInt32 dword_4B9E48;
#endif
// 0x004B9E54
#ifndef CODFH_PLAIN
RwInt32 dword_4B9E54;
#endif
// 0x004F61F0
bool byte_4F61F0;
// 0x004F61F1
bool byte_4F61F1;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7E80@@3MB @ 0x003D7E80
// match: ?flt_3D7E84@@3MB @ 0x003D7E84
// match: ??_C@_0DO@KPAEBBN@MEMORY?5LEAK?5detected?5during?5fron@ @ 0x003D7E88
// match: ??_C@_0BO@FDEIDOLC@GameFrontEnd?5Shutdown?5end?4?4?4?4?$AA@ @ 0x003D7EC8
// match: ??_C@_0DA@JOPIEECP@Shutdown?3?5Memory?5freed?5on?5RwFree@ @ 0x003D7EE8
// match: ??_C@_0CN@LNCOCMHJ@GameFrontEnd?5world?5is?5not?5empty?5@ @ 0x003D7F18
// match: ??_C@_0DI@HHJOEDGB@GameFrontEndInit?3?5Memory?5freed?5o@ @ 0x003D7F48
// match: ??_C@_0CG@BFICBGMM@GameFrontEnd?5Initialization?5begi@ @ 0x003D7F80

// match: ?sub_DA290@@YAXXZ @ 0x000DA290

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_DA290()
{
    RpWorld *var_C;
    RwCamera *bp_8;
    RwInt32 bp_4;

    sub_19A750(" ");
    sub_19A750(" ");
    sub_19A750("******************************************");
    sub_19A750("GameFrontEnd Initialization begin....");
    sub_19A750("******************************************");
    bp_4 = RwFreeListPurgeAllFreeLists();
    sub_19A750("GameFrontEndInit: Memory freed on RwFreeList purge - %d", bp_4);
    dword_4B889C = 0;
    sub_19A750();
    var_C = sub_1331E0();
    bp_8 = RWS::CameraHelper::CreateMainRasterCamera(Width, Height, ZDepth);
    dword_4B88B0 = bp_8;
    if (dword_4F39DC)
    {
        sub_19A750((const RwChar *)0);
    }
    if (!dword_4F30B8)
    {
        dword_4B9E54 = 0;
    }
    RwCameraSetNearClipPlane(bp_8, 1.0f);
    RwCameraSetFarClipPlane(bp_8, 100.0f);
    RpWorldAddCamera(var_C, bp_8);
    Rt2dOpen(bp_8);
    Rt2dAnimOpen();
    Rt2dDeviceSetLayerDepth(RwCameraGetNearClipPlane(bp_8) + 0.1f);
    byte_4B88B8 = false;
    dword_4B8EF0.sub_E9790(1, (RwInt32)bp_8);
    sub_D95A0();
    sub_198390();
    sub_83280();
    if (!dword_4B9E48)
    {
        unk_4B9308.sub_EE590();
    }
    sub_1A2E40(bp_8);
    if (!byte_4F61F1 && !byte_4F61F0)
    {
        dword_4B8EF0.sub_E9CA0();
    }
    dword_4B8EF0.sub_E99E0();
    sub_835E0();
    sub_198580();
    sub_19A750();
    Rt2dAnimClose();
    Rt2dClose();
    RpWorldRemoveCamera(var_C, bp_8);
    RWS::CameraHelper::Destroy(bp_8);
    dword_4B88B0 = 0;
    if (!sub_16E5C0(var_C, 0, 0))
    {
        sub_19A750("GameFrontEnd world is not empty at shutdown!");
    }
    RpWorldDestroy(var_C);
    bp_4 = RwFreeListPurgeAllFreeLists();
    sub_19A750("Shutdown: Memory freed on RwFreeList purge - %d", bp_4);
    sub_19A750("******************************************");
    sub_19A750("GameFrontEnd Shutdown end....");
    sub_19A750("******************************************");
    sub_19A750(" ");
    sub_19A750(" ");
    if (sub_12F080(1))
    {
        sub_12F060(1);
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
        sub_19A750("MEMORY LEAK detected during frontend shutdown! Show this to a");
        sub_19A750("programmer immediately (especially the last one that");
        sub_19A750("checked in) and tell him that restart/reset is broken.");
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
        sub_19A750();
    }
}

// match: ?sub_DA550@@YAX_N@Z @ 0x000DA550
void sub_DA550(bool arg_0)
{
    byte_4B8920 = arg_0;
    sub_DA570();
}

// match: ?sub_DA570@@YAXXZ @ 0x000DA570
void sub_DA570()
{
    dword_4B8924 = 0;
}
