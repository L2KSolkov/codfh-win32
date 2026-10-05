
/*
 *
 * Functionality for 2D rendering
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 */

/****************************************************************************
 *                                                                          *
 *  Module  :   gstate.c                                                    *
 *                                                                          *
 *  Purpose :   graphics state                                              *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 Includes
 */

#include "rwcore.h"
#include <rpdbgerr.h>
#include <rpcriter.h>

#include "anim.h"
#include "button.h"
#include "maestro.h"
#include "strlabel.h"
#include "message.h"
#include "keyframe.h"
#include "props.h"
#include "cel.h"
#include "gstate.h"

#include "rt2d.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@(#)$Id: //RenderWare/dev_branches/fast2d/dev/rwsdk/tool/2d/gstate.c#1 $";


/****************************************************************************
 Local Types
 */

/****************************************************************************
 Local (Static) Prototypes
 */

/****************************************************************************
 Local Defines
 */

/****************************************************************************
 Globals (across program)
 */
Rt2dAnimGlobalVars      Rt2dAnimGlobals;
RwBool                  _rt2dAnimOpenCalled = FALSE;

#if 0 /* codfh-match: the image's Rt2dAnim (RenderWare 3.6.0.3) has neither these variables
       * (its .data has no room for them between the 2D toolkit's and the message table)
       * nor Rt2dAnimSetFreeListCreateParams (docs/rw-differences.md) */
static RwInt32 _rt2dAnimFListBlockSize = 20;
static RwInt32 _rt2dAnimFListPreallocBlocks = 1;
#endif

/****************************************************************************
 Local (static) Globals
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   Functions

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


/****************************************************************************/

/**
 * \ingroup rt2danimsub
 * \ref Rt2dAnimOpen
 * is used to perform various initializations that are required
 * before the 2D animation toolkit API can be used.
 * \see Rt2dAnimClose
 * \see Rt2dAnimSetFreeListCreateParams
 */
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x003EE558

// match: _Rt2dAnimOpen @ 0x002573B0
void
Rt2dAnimOpen(void)
{
    RWAPIFUNCTION(RWSTRING("Rt2dAnimOpen"));

    /* codfh-match: 3.6 creates the free lists (16-byte aligned) */
    Rt2dAnimGlobals.animFreeList =
        RwFreeListCreate(sizeof(Rt2dAnim), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.buttonFreeList =
        RwFreeListCreate(sizeof(Rt2dButton), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.maestroFreeList =
        RwFreeListCreate(sizeof(Rt2dMaestro), 20, 16,
                         rwID_2DMAESTRO | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.stringLabelFreeList =
        RwFreeListCreate(sizeof(Rt2dStringLabel), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.messageFreeList =
        RwFreeListCreate(sizeof(Rt2dMessage), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.messageQueueFreeList =
        RwFreeListCreate(sizeof(Rt2dMessageQueue), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.animObjectUpdateFreeList =
        RwFreeListCreate(sizeof(Rt2dAnimObjectUpdate), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.keyFrameListFreeList =
        RwFreeListCreate(sizeof(Rt2dKeyFrameList), 20, 16,
                         rwID_2DKEYFRAME | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.animPropsFreeList =
        RwFreeListCreate(sizeof(Rt2dAnimProps), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.celListFreeList =
        RwFreeListCreate(sizeof(Rt2dCelList), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);
    Rt2dAnimGlobals.celFreeList =
        RwFreeListCreate(sizeof(Rt2dCel), 20, 16,
                         rwID_2DANIM | rwMEMHINTDUR_GLOBAL);

    _rt2dAnimOpenCalled = TRUE;

    RWRETURNVOID();
}

/****************************************************************************/

/**
 * \ingroup rt2danimsub
 * \ref Rt2dAnimClose
 * is used to perform various clean-up operations that are
 * required to close- down the 2D animation tools API. This function
 * complements \ref Rt2dAnimOpen and should be used before closing down an
 * application.
 * \return None
 *
 * \see Rt2dAnimOpen
 */
// match: _Rt2dAnimClose @ 0x002574C0
void
Rt2dAnimClose(void)
{
    RWAPIFUNCTION(RWSTRING("Rt2dAnimClose"));

    RwFreeListDestroy(Rt2dAnimGlobals.animFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.buttonFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.maestroFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.stringLabelFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.messageFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.messageQueueFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.animObjectUpdateFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.keyFrameListFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.animPropsFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.celListFreeList);
    RwFreeListDestroy(Rt2dAnimGlobals.celFreeList);

    RWRETURNVOID();
}

/**
 * \ingroup rt2danimsub
 * \ref Rt2dAnimSetFreeListCreateParams allows the developer to specify
 * how many 2d animation objects to preallocate space for. This applies to all
 * the 2d animations objects.
 * Call before \ref RwEngineInit.
 *
 * \param blockSize  number of entries per freelist block.
 * \param numBlocksToPrealloc  number of blocks to allocate on
 * \ref RwFreeListCreateAndPreallocateSpace.
 *
 * \see RwFreeList
 */
#if 0 /* codfh-match: not in the image's Rt2dAnim (see the variables above) */
void
Rt2dAnimSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc )
{
    /*
     * Can not use debugging macros since the debugger is not initialized before
     * RwEngineInit.
     */
    /* Do NOT comment out RWAPIFUNCTION as gnumake verify will not function */
#if 0
    RWAPIFUNCTION(RWSTRING("Rt2dAnimSetFreeListCreateParams"));
#endif
    _rt2dAnimFListBlockSize = blockSize;
    _rt2dAnimFListPreallocBlocks = numBlocksToPrealloc;
#if 0
    RWRETURNVOID();
#endif
}
#endif
