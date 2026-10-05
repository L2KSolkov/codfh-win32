// The game's start-up: RenderWare's start and stop, and the outer loop that
// runs the game loop between the front end's screens. The original file
// name is not in the image, so it is named for its start address.

#include <stdio.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/startup.h"
#include "rws/memoryhandler.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7E28
extern const RwReal flt_3D7E28 = 16.666666f;
// 0x003D7E2C
extern const RwReal flt_3D7E2C = 0.01f;
// 0x003D7E30
extern const RwReal flt_3D7E30 = 0.01f;
// 0x004292A0
// RenderWare's memory functions (RWS's; the free one is its operator delete).
RwMemoryFunctions off_4292A0 = { RWSMalloc, operator delete, RWSReAlloc, RWSCalloc };
// 0x004B87FC
void *dword_4B87FC;
// 0x004B8884
RwUInt8 *dword_4B8884;
// 0x004B8888
RwUInt8 *dword_4B8888;
// 0x004B888C
RwUInt8 dword_4B888C[4];
// 0x004FBA9C
#ifndef CODFH_PLAIN
RwInt32 dword_4FBA9C;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7E28@@3MB @ 0x003D7E28
// match: ?flt_3D7E2C@@3MB @ 0x003D7E2C
// match: ?flt_3D7E30@@3MB @ 0x003D7E30
// match: ??_C@_0BH@CHIOMPCP@Cheatflags?5Address?5?$CFx?6?$AA@ @ 0x003D7E34
// match: ?off_4292A0@@3URwMemoryFunctions@@A @ 0x004292A0

// match: ?sub_D99F0@@YAHPAUtype_D9950@@@Z @ 0x000D99F0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D99F0(type_D9950 *arg_0)
{
    RwMatrixTolerance var_1C;
    RwCamera *local_10;
    RwEngineOpenParams var_C;
    RwInt32 bp_8;
    RwMemoryFunctions *bp_4;

    dword_4B8970 = 1.225f;
    bp_8 = 0;
    bp_4 = sub_170ED0();
    if (!bp_4)
    {
        bp_4 = &off_4292A0;
    }
    sub_19A750();
    if (RwEngineInit(bp_4, 0, 0x20000)) // not an address: a size
    {
        if (RWS::StartUp::AttachPlugins())
        {
            var_C.displayID = dword_4B87FC;
            RwTextureSetFreeListCreateParams(5, 5);
            Rt2dBrushSetFreeListCreateParams(1, 1);
            Rt2dFontSetFreeListCreateParams(1, 1);
            Rt2dFontDictNodeSetFreeListCreateParams(1, 1);
            Rt2dPathSetFreeListCreateParams(1, 1);
            Rt2dObjectSetFreeListCreateParams(1, 1);
            Rt2dTriVertSetFreeListCreateParams(1, 1);
            Rt2dTriPolySetFreeListCreateParams(1, 1);
            if (RwEngineOpen(&var_C))
            {
                Direct3D_SetPushBufferSize(0x400000, 0x8000); // not an address: a size
                if (RwEngineStart())
                {
                    if (!dword_4F4628)
                    {
                        local_10 = RWS::CameraHelper::CreateMainRasterCamera(Width, Height, ZDepth);
                        RwCameraShowRaster(local_10, 0, 0);
                        RWS::CameraHelper::Destroy(local_10);
                    }
                    if (RWS::StartUp::RegisterImageLoaders())
                    {
                        var_1C.Normal = 0.015f;
                        var_1C.Orthogonal = 0.01f;
                        var_1C.Identity = 0.1f;
                        RwEngineSetMatrixTolerances(&var_1C);
                        unk_4B9308.sub_EE590();
                        sub_83100();
                        sub_19A750();
                        sub_19CD50();
                        sub_19A750();
                        sub_19A750();
                        sub_82F50();
                        sub_19A750();
                        sub_1A2910();
                        bp_8 = 1;
                    }
                    if (!bp_8)
                    {
                        RwEngineStop();
                    }
                }
                if (!bp_8)
                {
                    RwEngineClose();
                }
            }
        }
        if (!bp_8)
        {
            RwEngineTerm();
        }
    }
    return bp_8;
}

// match: ?sub_D9BC0@@YAXXZ @ 0x000D9BC0
void sub_D9BC0()
{
    sub_1A2D20();
    sub_831D0();
    unk_4B9308.sub_EE840();
    RwEngineStop();
    RwEngineClose();
    RwEngineTerm();
    sub_19A750();
    sub_12F060(0);
}

// match: ?sub_D9C00@@YAXXZ @ 0x000D9C00
void sub_D9C00()
{
    RwInt32 var_4;

    if (dword_4B8884)
    {
        dword_4B8888 = dword_4B8884 + 0x2C;
        printf("Cheatflags Address %x\n", dword_4B8888);
    }
    else
    {
        dword_4B8888 = dword_4B888C;
    }
    sub_D9950();
    sub_DA290();
    if (byte_4F61F0 || byte_4F61F1)
    {
        sub_D99D0();
        return;
    }
    sub_1B6F90();
    while (always_true())
    {
        var_4 = dword_4FBAA8;
        if (var_4)
        {
            unk_4F7EB8.sub_1AF6F0();
            dword_4FB9E0.sub_1B4AA0();
            sub_DA290();
            if (byte_4F61F0 || byte_4F61F1)
            {
                sub_D99D0();
                return;
            }
            sub_1B6F90();
        }
        else
        {
            dword_4FBA9C = 0;
        }
        if (unk_4F7EB8.sub_1AF670())
        {
            sub_D99B0();
        }
        else
        {
            dword_4FBAA8 = 1;
        }
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_170ED0@@YAPAURwMemoryFunctions@@XZ (folded into 0x170ED0)
struct RwMemoryFunctions * sub_170ED0()
{
    return 0;
}
