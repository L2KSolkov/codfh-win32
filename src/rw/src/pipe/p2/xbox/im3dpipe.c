/*
 * codfh-match: RenderWare 3.6's Xbox Im3D pipeline construction
 * (src/pipe/p2/xbox/im3dpipe.c), after 3.7.2's src/pipe/p2/d3d8/im3dpipe.c;
 * the Xbox version opens and closes no Im3D renderer.
 */

/****************************************************************************
 Includes
 */

#include "batypes.h"

#include "bapipe.h"
#include "p2core.h"
#include "p2define.h"
#include "p2stdcls.h"

#include "im3dpipe.h"

#include "nodeXBoxSubmitNoLight.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/src/pipe/p2/xbox/im3dpipe.c#1 $";

/****************************************************************************
 _rwIm3DCreatePlatformTransformPipeline
 */
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x004170B0

// match: __rwIm3DCreatePlatformTransformPipeline @ 0x002B9670
RwBool
_rwIm3DCreatePlatformTransformPipeline(RxPipeline **globalPipe)
{
    RxPipeline  *pipe;

    RWFUNCTION(RWSTRING("_rwIm3DCreatePlatformTransformPipeline"));
    RWASSERT(globalPipe != NULL);

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxPipeline  *lpipe;

        pipe->pluginId = rwID_COREPLUGIN;

        lpipe = RxPipelineLock(pipe);
        if (lpipe)
        {
            /* Add the fragment */
            lpipe = RxLockedPipeAddFragment(lpipe,
                        NULL,
                        RxNodeDefinitionGetXboxImmInstance(),
                        NULL);  /* Dispatch to mat pipe */
            RWASSERT(lpipe != NULL);

            pipe = RxLockedPipeUnlock(lpipe);

            RWASSERT(pipe != NULL);
            RWASSERT(pipe == lpipe);

            if (pipe != NULL)
            {
               *globalPipe = pipe;

                RwIm3DSetTransformPipeline(pipe);

                RWRETURN(TRUE);
            }
        }

        /* Failed to lock it */
        RxPipelineDestroy(pipe);
    }

    /* Failed to create it - ran out of memory? */
    RWRETURN(FALSE);
}

/****************************************************************************
 _rwIm3DDestroyPlatformTransformPipeline
 */
// match: __rwIm3DDestroyPlatformTransformPipeline @ 0x002B96E0
void
_rwIm3DDestroyPlatformTransformPipeline(RxPipeline **globalPipe)
{
    RWFUNCTION(RWSTRING("_rwIm3DDestroyPlatformTransformPipeline"));
    RWASSERT(globalPipe != NULL);

    /* Resinstate the generic transform pipe */
    RwIm3DSetTransformPipeline(NULL);

    if (NULL != *globalPipe)
    {
        RxPipelineDestroy(*globalPipe);
       *globalPipe = NULL;
    }

    RWRETURNVOID();
}

/****************************************************************************
 _rwIm3DDestroyPlatformRenderPipelines
 */
// match: __rwIm3DDestroyPlatformRenderPipelines @ 0x002B9710
void
_rwIm3DDestroyPlatformRenderPipelines(rwIm3DRenderPipelines *globalPipes)
{
    RWFUNCTION(RWSTRING("_rwIm3DDestroyPlatformRenderPipelines"));
    RWASSERT(globalPipes != NULL);

    /* Resinstate the generic lines pipes pipe */
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPETRILIST);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPETRIFAN);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPETRISTRIP);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPELINELIST);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPEPOLYLINE);

    if (NULL != globalPipes->triList)
    {
        RxPipelineDestroy(globalPipes->triList);
    }

    globalPipes->triList  = NULL;
    globalPipes->triFan   = NULL;
    globalPipes->triStrip = NULL;
    globalPipes->lineList = NULL;
    globalPipes->polyLine = NULL;

    RWRETURNVOID();
}

/****************************************************************************
 _rwIm3DCreatePlatformRenderPipelines
 */
// match: __rwIm3DCreatePlatformRenderPipelines @ 0x002B9770
RwBool
_rwIm3DCreatePlatformRenderPipelines(rwIm3DRenderPipelines *globalPipes)
{
    RxPipeline  *pipe;

    RWFUNCTION(RWSTRING("_rwIm3DCreatePlatformRenderPipelines"));
    RWASSERT(globalPipes != NULL);

    /* Same pipe for all primitive types, yay! */
    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe    *lpipe;

        pipe->pluginId = rwID_COREPLUGIN;

        lpipe = RxPipelineLock(pipe);
        if (lpipe)
        {
            lpipe = RxLockedPipeAddFragment(lpipe,
                NULL,
                RxNodeDefinitionGetXboxSubmitNoLight(),
                NULL);
            RWASSERT(lpipe != NULL);

            pipe = RxLockedPipeUnlock(lpipe);

            RWASSERT(pipe != NULL);
            RWASSERT(pipe == lpipe);

            if (NULL != pipe)
            {
                globalPipes->triList  = pipe;
                globalPipes->triFan   = pipe;
                globalPipes->triStrip = pipe;
                globalPipes->lineList = pipe;
                globalPipes->polyLine = pipe;

                /* Set our pipe as the default for all primitives... */
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPETRILIST);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPETRIFAN);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPETRISTRIP);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPELINELIST);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPEPOLYLINE);

                RWRETURN(TRUE);
            }
        }

        /* Failed to lock/add/unlock the pipe */
        RxPipelineDestroy(pipe);
    }

    /* Failed to create the pipe - ran out of memory? */
    RWRETURN(FALSE);
}
