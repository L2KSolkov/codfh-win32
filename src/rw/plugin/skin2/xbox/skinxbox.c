/*
 * codfh-match: RenderWare 3.6's Xbox skin pipeline set-up, rebuilt from the
 * image; the file name is the image's RCS id string's, names the Godfather
 * PDB's. 3.6 has only the plain pipeline: every skin type attaches it.
 */

#include <xtl.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"
#include "skinxbox.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/skin2/xbox/skinxbox.c#1 $";

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00418518

// match: __rpSkinPipelinesCreate @ 0x002D1800
// sp-match: __rpSkinPipelinesCreate @ 0x001EC150
RwBool
_rpSkinPipelinesCreate(RwUInt32 pipes)
{
    RwBool  rv = TRUE;

    if (pipes & rpSKINPIPELINESKINGENERIC)
    {
        if (NULL == _rpSkinXboxCreatePlainPipe())
        {
            rv = FALSE;
        }
    }

    return rv;
}

// match: __rpSkinPipelinesDestroy @ 0x002D1820
// sp-match: __rpSkinPipelinesDestroy @ 0x001EC170
RwBool
_rpSkinPipelinesDestroy(void)
{
    _rpSkinXboxDestroyPlainPipe();

    return TRUE;
}

// match: __rpSkinPipelinesAttach @ 0x002D1830
// sp-match: __rpSkinPipelinesAttach @ 0x001EC180
RpAtomic *
_rpSkinPipelinesAttach(RpAtomic *atomic, RpSkinType type __RWUNUSED__)
{
    return RpAtomicSetPipeline(atomic, _rpSkinPipeline(rpSKINXBOXPIPELINEGENERIC));
}
