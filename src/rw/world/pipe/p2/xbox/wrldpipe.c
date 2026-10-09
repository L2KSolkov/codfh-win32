/*
 * codfh-match: RenderWare 3.6's Xbox world pipeline set-up, rebuilt from the
 * image; the file name is the image's RCS id string's, the shapes the
 * Godfather debug build's copy. The 3.7 tree has only other platforms'.
 */

#include <xtl.h>

#include <rwcore.h>
#include "baworld.h"
#include "bapipew.h"

#include "xbpipe.h"
#include "xbvtxfmt.h"
#include "xblights.h"
#include "xbpixelshader.h"
#include "nodeXBoxWorldSectorAllInOne.h"
#include "nodeXBoxAtomicAllInOne.h"

#include "wrldpipe.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/wrldpipe.c#1 $";

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419548

// match: __rxWorldDevicePluginAttach @ 0x002E15F0
// sp-match: __rxWorldDevicePluginAttach @ 0x001FC0C0
RwBool
_rxWorldDevicePluginAttach(void)
{
    _rpXboxMaterialPixelShaderOpen();
    _rpXboxVtxFmtPluginAttach();

    return TRUE;
}

// match: __rpCreatePlatformWorldSectorPipelines @ 0x002E1600
// sp-match: __rpCreatePlatformWorldSectorPipelines @ 0x001FC0D0
RwBool
_rpCreatePlatformWorldSectorPipelines(void)
{
    RxPipeline  *pipe;

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        pipe->pluginId = rwID_WORLDPLUGIN;
        if (NULL != (lpipe = RxPipelineLock(pipe)))
        {
            lpipe = RxLockedPipeAddFragment(lpipe,
                NULL,
                RxNodeDefinitionGetXboxWorldSectorAllInOne(),
                NULL);

            lpipe = RxLockedPipeUnlock(lpipe);

            if (NULL != lpipe)
            {
                RXPIPELINEGLOBAL(platformWorldSectorPipeline) = pipe;
                RpWorldSetDefaultSectorPipeline(pipe);

                return TRUE;
            }
        }

        RxPipelineDestroy(pipe);
    }

    return FALSE;
}

// match: __rpDestroyPlatformWorldSectorPipelines @ 0x002E1670
// sp-match: __rpDestroyPlatformWorldSectorPipelines @ 0x001FC140
void
_rpDestroyPlatformWorldSectorPipelines(void)
{
    RpWorldSetDefaultSectorPipeline(NULL);

    if (NULL != RXPIPELINEGLOBAL(platformWorldSectorPipeline))
    {
        RxPipelineDestroy(RXPIPELINEGLOBAL(platformWorldSectorPipeline));
        RXPIPELINEGLOBAL(platformWorldSectorPipeline) = NULL;
    }

    RwXboxLightsEnable(0, TRUE);
}

// match: __rpCreatePlatformAtomicPipelines @ 0x002E16B0
// sp-match: __rpCreatePlatformAtomicPipelines @ 0x001FC180
RwBool
_rpCreatePlatformAtomicPipelines(void)
{
    RxPipeline  *pipe;

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        pipe->pluginId = rwID_WORLDPLUGIN;
        if (NULL != (lpipe = RxPipelineLock(pipe)))
        {
            lpipe = RxLockedPipeAddFragment(lpipe,
                NULL,
                RxNodeDefinitionGetXboxAtomicAllInOne(),
                NULL);

            lpipe = RxLockedPipeUnlock(lpipe);

            if (NULL != lpipe)
            {
                RXPIPELINEGLOBAL(platformAtomicPipeline) = pipe;
                RpAtomicSetDefaultPipeline(pipe);

                return TRUE;
            }
        }

        RxPipelineDestroy(pipe);
    }

    return FALSE;
}

// match: __rpDestroyPlatformAtomicPipelines @ 0x002E1720
// sp-match: __rpDestroyPlatformAtomicPipelines @ 0x001FC1F0
void
_rpDestroyPlatformAtomicPipelines(void)
{
    _rpXboxMaterialPixelShaderClose();

    RpAtomicSetDefaultPipeline(NULL);

    if (NULL != RXPIPELINEGLOBAL(platformAtomicPipeline))
    {
        RxPipelineDestroy(RXPIPELINEGLOBAL(platformAtomicPipeline));
        RXPIPELINEGLOBAL(platformAtomicPipeline) = NULL;
    }
}

/* The material pipelines: none of the platform's own on Xbox. /OPT:ICF folded the
 * creator into _rwPipeAttach's body (`return TRUE`, 0x2B8CB0) and the destroyer into
 * an empty one (0x22C6E0). */
RwBool
_rpCreatePlatformMaterialPipelines(void)
{
    RWFUNCTION(RWSTRING("_rpCreatePlatformMaterialPipelines"));

    RWRETURN(TRUE);
}

void
_rpDestroyPlatformMaterialPipelines(void)
{
    RWFUNCTION(RWSTRING("_rpDestroyPlatformMaterialPipelines"));

    RWRETURNVOID();
}
