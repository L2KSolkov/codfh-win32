/*
 *
 * Functionality for 2D rendering
 *
 * Copyright (c) 2001 Criterion Software Ltd.
 */

/****************************************************************************
 *                                                                          *
 *  Module  :   bucket.c                                                    *
 *                                                                          *
 *  Purpose :   simple 2d animation maestro functionality                  *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 Includes
 */

#include <string.h>

#include "rwcore.h"
#include <rpdbgerr.h>
#include <rpcriter.h>
#include "rt2danim.h"

#include "maestro.h"
#include "bucket.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/tool/2danim/bucket.c#1 $";

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

/****************************************************************************
 Local (static) Globals
 */

/****************************************************************************
 Local functions
 */

RwSList *
// sp-match: __rt2dByteBucketCreate @ 0x00173880
_rt2dByteBucketCreate(void)
{
    RwSList    *result;

    RWFUNCTION(RWSTRING("_rt2dByteBucketCreate"));

    result = _rwSListCreate(sizeof(RwChar),
        rwID_2DANIM | rwMEMHINTDUR_EVENT);

    /* Create a dummy entry to occupy position zero. */
#if (0)
    if (result)
    {
        RwChar      *tmp;

        tmp = _rwSListGetNewEntry(result);
    }
#endif /* (0) */

    RWRETURN(result);
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x003EE7D0

// match: __rt2dByteBucketDestroy @ 0x00257A20
// sp-match: __rt2dByteBucketDestroy @ 0x00173890
RwBool
_rt2dByteBucketDestroy(RwSList * ByteBucket)
{
    RWFUNCTION(RWSTRING("_rt2dByteBucketDestroy"));

    RWASSERT(ByteBucket);

    _rwSListDestroy(ByteBucket);

    RWRETURN(TRUE);
}

RwInt32
// sp-match: __rt2dByteBucketAddData @ 0x001738B0
_rt2dByteBucketAddData(RwSList * ByteBucket, const void * data, RwInt32 length)
{
    RwInt32             newIdx;
    RwChar              *newData;

    RWFUNCTION(RWSTRING("_rt2dByteBucketAddData"));

    RWASSERT(ByteBucket);
    RWASSERT(length > 0);

    newIdx = _rwSListGetNumEntries(ByteBucket);

    /* Ask for a new data area. */
    if ((newData = (RwChar *)_rwSListGetNewEntries(ByteBucket, length,
        rwID_2DANIM | rwMEMHINTDUR_EVENT)) == NULL)
    {
        RWRETURN(-1);
    }

    /* Copy the data into the bit bucket. */
    if (data)
    {
        memcpy(newData, data, length);
    }

    RWRETURN(newIdx);
}

void *
// sp-match: __rt2dByteBucketGetDataByIndex @ 0x00173900
_rt2dByteBucketGetDataByIndex(RwSList * ByteBucket, RwInt32 idx)
{
    RwChar        *newData;

    RWFUNCTION(RWSTRING("_rt2dByteBucketGetDataByIndex"));

    RWASSERT(ByteBucket);
    RWASSERT(idx < _rwSListGetNumEntries(ByteBucket));

    newData = (RwChar *)_rwSListGetEntry(ByteBucket, idx);

    RWRETURN(newData);
}

/****************************************************************************
 API functions
 */
