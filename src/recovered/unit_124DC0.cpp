// The frame time and the screen fade (game/fade.h). The original file name
// is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "game/fade.h"
#include "game/functions.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA7D8
extern const RwReal flt_3DA7D8 = 16.666666f;
// 0x003DA7DC
extern const RwReal flt_3DA7DC = 16.666666f;
// 0x004CF3C0
RwReal dword_4CF3C0[10];
// 0x004CF3E8
RwInt32 dword_4CF3E8;
// 0x004CF3EC
RwInt32 dword_4CF3EC;
// 0x004CF3F0
RwInt32 dword_4CF3F0;
// 0x004CF3F4
RwRaster *dword_4CF3F4;
// 0x004CF3F8
RwReal dword_4CF3F8;
// 0x004CF3FC
RwReal dword_4CF3FC;
// 0x004CF400
RwUInt8 byte_4CF400;
// 0x004CF404
void (*dword_4CF404)();
// 0x004CF408
RwUInt8 byte_4CF408;
// 0x004CF40C
void (*dword_4CF40C)();
// 0x004CF410
RwInt32 dword_4CF410;
// 0x004CF414
RwInt32 dword_4CF414;
// 0x004CF418
RwRaster *dword_4CF418;
// 0x004CF41C
RwInt32 dword_4CF41C;
// 0x004CF420
RwInt32 dword_4CF420;
// 0x004CF424
RwInt32 dword_4CF424;
// 0x004CF428
RwUInt8 byte_4CF428;
// 0x004CF42C
RwInt32 dword_4CF42C;
// 0x004CF430
RwReal flt_4CF430;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA7D8@@3MB @ 0x003DA7D8
// match: ?flt_3DA7DC@@3MB @ 0x003DA7DC
// match: __real@3d088889 @ 0x003DA7E0
// match: __real@3ccccccd @ 0x003DA7E4

// match: ?sub_124DC0@@YAXM@Z @ 0x00124DC0

// Records the frame at time arg_0 (not while a fade runs), and reports
// (through the empty debug print) whether the last ten frames average under
// 1/40 or over 1/30.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_124DC0(RwReal arg_0)
{
    RwReal var_4;
    RwInt32 local_8;

    if (byte_4CF428)
    {
        sub_19A750(1);
        return;
    }
    var_4 = arg_0 - flt_4CF430;
    for (local_8 = 0; local_8 < 9; local_8++)
    {
        dword_4CF3C0[local_8] = dword_4CF3C0[local_8 + 1];
        var_4 += dword_4CF3C0[local_8];
    }
    dword_4CF3C0[9] = arg_0 - flt_4CF430;
    var_4 = (var_4 += dword_4CF3C0[9]) * 0.0001f;
    if (var_4 < 0.025f)
    {
        sub_19A750(1);
    }
    else if (var_4 > 0.033333335f)
    {
        sub_19A750(0);
    }
    flt_4CF430 = arg_0;
}

// match: ?sub_124E90@@YAXXZ @ 0x00124E90
void sub_124E90()
{
    byte_4CF428 = 0;
    dword_4CF3EC = 0;
    dword_4CF3F8 = 0.0f;
    dword_4CF3FC = 0.0f;
    byte_4CF408 = 0;
    dword_4CF3F4 = 0;
    byte_4CF400 = 0;
    dword_4CF410 = 0;
}

// match: ?sub_124EE0@@YAXMH@Z @ 0x00124EE0
// Starts a fade of arg_0 seconds, in (arg_4 0) or out (1).
void sub_124EE0(RwReal arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    byte_4CF428 = 1;
    dword_4CF3EC = arg_4;
    dword_4CF3F8 = 0.0f;
    dword_4CF3FC = arg_0 * 1000.0f / flt_3DA7DC;
    byte_4CF408 = 1;
    sub_19A750(1);
    dword_4CF410 = 0;
    for (var_4 = 0; var_4 < 10; var_4++)
    {
        dword_4CF3C0[var_4] = 0.0f;
    }
    dword_4CF42C = 0;
}

// match: ?sub_124F70@@YAXM@Z @ 0x00124F70
// Runs the fade by arg_0: at its end calls (once) the function for its
// direction; a fade in stops, a fade out holds.
void sub_124F70(RwReal arg_0)
{
    if (byte_4CF428)
    {
        if (dword_4CF3F8 < dword_4CF3FC)
        {
            dword_4CF3F8 += arg_0;
            if (byte_4CF408 && dword_4CF3F8 >= dword_4CF3FC)
            {
                switch (dword_4CF3EC)
                {
                case 0:
                    if (dword_4CF404)
                    {
                        dword_4CF404();
                        dword_4CF404 = 0;
                    }
                    break;
                case 1:
                    if (dword_4CF40C)
                    {
                        dword_4CF40C();
                        dword_4CF40C = 0;
                    }
                    break;
                }
            }
        }
        else
        {
            if (byte_4CF408 && dword_4CF3F8 >= dword_4CF3FC)
            {
                dword_4CF3F8 = dword_4CF3FC;
                if (!dword_4CF3EC)
                {
                    byte_4CF428 = 0;
                    byte_4CF408 = 0;
                }
            }
        }
    }
}

// match: ?sub_125060@@YAXPAURwCamera@@@Z @ 0x00125060
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the fade over the camera arg_0's view: a quad over the screen whose
// alpha follows the fade (falling as it fades in, rising as it fades out).
void sub_125060(RwCamera *arg_0)
{
    RwInt32 var_7C;
    RwIm2DVertex m_78[4];
    RwReal bp_4;

    bp_4 = 0.0f;
    if ((byte_4CF428 || byte_4CF400) && !dword_4CF410)
    {
        switch (dword_4CF3EC)
        {
        case 0:
            bp_4 = 1.0f - dword_4CF3F8 / dword_4CF3FC;
            if (bp_4 < 0.0f)
            {
                bp_4 = 0.0f;
            }
            break;
        case 1:
            bp_4 = dword_4CF3F8 / dword_4CF3FC;
            if (bp_4 > 1.0f)
            {
                bp_4 = 1.0f;
            }
            break;
        }
        if (bp_4 == 0.0f)
        {
            return;
        }
        if (byte_4CF408 && RwCameraBeginUpdate(arg_0))
        {
            sub_125320();
            sub_1253A0();
            RwIm2DVertexSetScreenX(&m_78[0], 0.0f);
            RwIm2DVertexSetScreenY(&m_78[0], 0.0f);
            RwIm2DVertexSetScreenX(&m_78[1], 0.0f);
            RwIm2DVertexSetScreenY(&m_78[1], (RwReal)(RwUInt32)Height);
            RwIm2DVertexSetScreenX(&m_78[2], (RwReal)(RwUInt32)Width);
            RwIm2DVertexSetScreenY(&m_78[2], (RwReal)(RwUInt32)Height);
            RwIm2DVertexSetScreenX(&m_78[3], (RwReal)(RwUInt32)Width);
            RwIm2DVertexSetScreenY(&m_78[3], 0.0f);
            RwIm2DVertexSetU(&m_78[0], 0.0f, 0);
            RwIm2DVertexSetV(&m_78[0], 0.0f, 0);
            RwIm2DVertexSetU(&m_78[1], 0.0f, 0);
            RwIm2DVertexSetV(&m_78[1], 1.0f, 0);
            RwIm2DVertexSetU(&m_78[2], 1.0f, 0);
            RwIm2DVertexSetV(&m_78[2], 1.0f, 0);
            RwIm2DVertexSetU(&m_78[3], 1.0f, 0);
            RwIm2DVertexSetV(&m_78[3], 0.0f, 0);
            for (var_7C = 0; var_7C < 4; var_7C++)
            {
                RwIm2DVertexSetScreenZ(&m_78[var_7C], RwIm2DGetNearScreenZ());
                RwIm2DVertexSetRecipCameraZ(&m_78[var_7C], 1.0f / RwCameraGetNearClipPlane(arg_0));
                if (dword_4CF3F4)
                {
                    RwIm2DVertexSetIntRGBA(&m_78[var_7C], 255, 255, 255, (RwInt32)(255.0f * bp_4));
                }
                else
                {
                    RwIm2DVertexSetIntRGBA(&m_78[var_7C], 0, 0, 0, (RwInt32)(255.0f * bp_4));
                }
            }
            RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, m_78, 4);
            sub_125410();
            RwCameraEndUpdate(arg_0);
        }
    }
}

// match: ?sub_1252E0@@YAXP6AXXZH@Z @ 0x001252E0
// Sets the function called at the end of a fade in (arg_4 0) or out (1),
// unless the fade out's is sub_D8C00's.
void sub_1252E0(void (*arg_0)(), RwInt32 arg_4)
{
    if (dword_4CF40C == sub_D8C00)
    {
        return;
    }
    switch (arg_4)
    {
    case 0:
        dword_4CF404 = arg_0;
        break;
    case 1:
        dword_4CF40C = arg_0;
        break;
    }
}

// match: ?sub_125320@@YAXXZ @ 0x00125320
void sub_125320()
{
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &dword_4CF420);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dword_4CF3E8);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &dword_4CF3F0);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &dword_4CF414);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &dword_4CF41C);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &dword_4CF424);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &dword_4CF418);
}

// match: ?sub_1253A0@@YAXXZ @ 0x001253A0
void sub_1253A0()
{
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)dword_4CF3F4);
}

// match: ?sub_125410@@YAXXZ @ 0x00125410
void sub_125410()
{
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)dword_4CF420);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dword_4CF3E8);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)dword_4CF3F0);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)dword_4CF414);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)dword_4CF41C);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)dword_4CF424);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)dword_4CF418);
}
