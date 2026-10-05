/*
 * codfh-match: RenderWare 3.6's Xbox skin shader constant mode switch,
 * rebuilt from the image; the file name is the image's RCS id string's,
 * names the Godfather PDB's.
 */

#include <xtl.h>

#include <rwcore.h>
#include <rpworld.h>

#include "skin.h"
#include "skinxbox.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/skin2/xbox/skinxboxconstantmode.c#1 $";

static RwBool in192ConstantMode;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419078

// match: __rpSkinXboxTo192Constants @ 0x002D4B20
void
_rpSkinXboxTo192Constants(void)
{
    D3DDevice_SetShaderConstantMode(D3DSCM_192CONSTANTS | D3DSCM_NORESERVEDCONSTANTS);
    in192ConstantMode = TRUE;
}

// match: __rpSkinXboxTo96Constants @ 0x002D4B40
void
_rpSkinXboxTo96Constants(void)
{
    D3DDevice_SetShaderConstantMode(D3DSCM_96CONSTANTS);
    in192ConstantMode = FALSE;
}
