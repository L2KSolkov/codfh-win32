/*
 * codfh-match: RenderWare 3.6's Xbox world lights, rebuilt from the image;
 * names from the Godfather PDB's copy. The file name is the image's own RCS
 * id string's (Godfather keeps none: the lights assert nothing).
 */

#include <xtl.h>

#include <rwcore.h>
#include "bamateri.h"
#include "baworld.h"
#include "balight.h"

#include "xbcache.h"

#include "xblights.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/world/pipe/p2/xbox/xblights.c#1 $";

/****************************************************************************
 Local variables
 */

static RwInt32 numActiveLights = 0;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x004193C8
// match: ?newLight@?1??_rwXBLightsGlobalEnable@@9@9 @ 0x00436BE8
// match: ?newLight@?1??_rxXBLightLocalEnable@@9@9 @ 0x00436C50

// match: __rwXBLightsGlobalEnable @ 0x002DF190

RwBool
_rwXBLightsGlobalEnable(RwUInt32 *numLights, RwUInt32 flags, RwBool hasNormals)
{
    static D3DLIGHT8 newLight =
    {
        D3DLIGHT_DIRECTIONAL,
        { 0.0f, 0.0f, 0.0f, 1.0f },     /* Diffuse */
        { 0.0f, 0.0f, 0.0f, 1.0f },     /* Specular */
        { 0.0f, 0.0f, 0.0f, 1.0f },     /* Ambient */
        { 0.0f, 0.0f, 0.0f },           /* Position */
        { 0.0f, 0.0f, 1.0f },           /* Direction */
        0.0f,                           /* Range */
        0.0f,                           /* Falloff */
        0.0f,                           /* Attenuation0 */
        0.0f,                           /* Attenuation1 */
        0.0f,                           /* Attenuation2 */
        0.0f,                           /* Theta */
        0.0f                            /* Phi */
    };
    RwReal              maxValue = 255.0f;
    RwRGBAReal          ambient;
    RpWorld             *world;
    RwLLLink            *cur, *end;
    RwBool              lighting = FALSE;
    RwUInt32            color;

    ambient.red = 0.0f;
    ambient.green = 0.0f;
    ambient.blue = 0.0f;
    ambient.alpha = 0.0f;

    world = (RpWorld *)RWSRCGLOBAL(curWorld);

    cur = rwLinkListGetFirstLLLink(&world->directionalLightList);
    end = rwLinkListGetTerminator(&world->directionalLightList);
    while (cur != end)
    {
        RpLight *light;

        light = rwLLLinkGetData(cur, RpLight, inWorld);

        /* NB light may actually be a dummyTie from a enclosing ForAll */
        if (light && (rwObjectTestFlags(light, flags)))
        {
            if (RpLightGetType(light) == rpLIGHTDIRECTIONAL)
            {
                if (hasNormals)
                {
                    const RwV3d *at;

                    const RwRGBAReal *color = RpLightGetColor(light);

                    newLight.Diffuse.r = color->red;
                    newLight.Diffuse.g = color->green;
                    newLight.Diffuse.b = color->blue;
                    newLight.Diffuse.a = color->alpha;

                    at = RwMatrixGetAt(RwFrameGetLTM(RpLightGetFrame(light)));

                    newLight.Direction.x = at->x;
                    newLight.Direction.y = at->y;
                    newLight.Direction.z = at->z;

                    D3DDevice_SetLight(*numLights, &newLight);

                    (*numLights)++;

                    lighting = TRUE;
                }
            }
            else
            {
                const RwRGBAReal    *lightColor;

                lightColor = RpLightGetColor(light);

                /* Accumulate ambient light color */
                RwRGBARealAdd(&ambient, &ambient, lightColor);

                lighting = TRUE;
            }
        }

        /* Next */
        cur = rwLLLinkGetNext(cur);
    }

    /* Scale, clamp and then set the ambient color */
    RwRGBARealScale(&ambient, &ambient, 255.0f);

    if (*(RwUInt32 *)&ambient.red > *(RwUInt32 *)&maxValue)
    {
        *(RwUInt32 *)&ambient.red = (*(RwInt32 *)&ambient.red < 0) ? 0 : *(RwUInt32 *)&maxValue;
    }
    if (*(RwUInt32 *)&ambient.green > *(RwUInt32 *)&maxValue)
    {
        *(RwUInt32 *)&ambient.green = (*(RwInt32 *)&ambient.green < 0) ? 0 : *(RwUInt32 *)&maxValue;
    }
    if (*(RwUInt32 *)&ambient.blue > *(RwUInt32 *)&maxValue)
    {
        *(RwUInt32 *)&ambient.blue = (*(RwInt32 *)&ambient.blue < 0) ? 0 : *(RwUInt32 *)&maxValue;
    }
    if (*(RwUInt32 *)&ambient.alpha > *(RwUInt32 *)&maxValue)
    {
        *(RwUInt32 *)&ambient.alpha = (*(RwInt32 *)&ambient.alpha < 0) ? 0 : *(RwUInt32 *)&maxValue;
    }

    color = (RwFastRealToUInt32(ambient.alpha) << 24) |
            (RwFastRealToUInt32(ambient.red) << 16) |
            (RwFastRealToUInt32(ambient.green) << 8) |
            RwFastRealToUInt32(ambient.blue);

    _rwXbRenderStateForce(D3DRS_AMBIENT, color);

    return lighting;
}

// match: __rxXBLightLocalEnable @ 0x002DF410
RwBool
_rxXBLightLocalEnable(RpLight *light, RwUInt32 *numLights)
{
    static D3DLIGHT8 newLight =
    {
        (D3DLIGHTTYPE)0,
        { 0.0f, 0.0f, 0.0f, 1.0f },     /* Diffuse */
        { 0.0f, 0.0f, 0.0f, 1.0f },     /* Specular */
        { 0.0f, 0.0f, 0.0f, 1.0f },     /* Ambient */
        { 0.0f, 0.0f, 0.0f },           /* Position */
        { 0.0f, 0.0f, 1.0f },           /* Direction */
        0.0f,                           /* Range */
        1.0f,                           /* Falloff */
        1.0f,                           /* Attenuation0 */
        0.0f,                           /* Attenuation1 */
        0.0f,                           /* Attenuation2 */
        0.0f,                           /* Theta */
        0.0f                            /* Phi */
    };
    const RwMatrix     *matrix;
    RwReal              radius;

    newLight.Diffuse.r = RpLightGetColor(light)->red;
    newLight.Diffuse.g = RpLightGetColor(light)->green;
    newLight.Diffuse.b = RpLightGetColor(light)->blue;
    newLight.Diffuse.a = RpLightGetColor(light)->alpha;

    matrix = RwFrameGetLTM(RpLightGetFrame(light));

    newLight.Position.x = matrix->pos.x;
    newLight.Position.y = matrix->pos.y;
    newLight.Position.z = matrix->pos.z;

    radius = RpLightGetRadius(light);

    newLight.Range = radius;
    newLight.Attenuation0 = 1.0f;
    newLight.Attenuation1 = 0.0f;
    newLight.Attenuation2 = 5.0f / (radius * radius);

    switch (RpLightGetType(light))
    {
        case rpLIGHTPOINT:
            newLight.Type = D3DLIGHT_POINT;
            break;

        case rpLIGHTSPOT:
            newLight.Type = D3DLIGHT_SPOT;
            newLight.Direction.x = matrix->at.x;
            newLight.Direction.y = matrix->at.y;
            newLight.Direction.z = matrix->at.z;
            newLight.Theta = RpLightGetConeAngle(light) * 2.0f;
            newLight.Phi = newLight.Theta;
            break;

        case rpLIGHTSPOTSOFT:
            newLight.Type = D3DLIGHT_SPOT;
            newLight.Direction.x = matrix->at.x;
            newLight.Direction.y = matrix->at.y;
            newLight.Direction.z = matrix->at.z;
            newLight.Theta = 0.0f;
            newLight.Phi = RpLightGetConeAngle(light) * 2.0f;
            break;

        default:
            return FALSE;
    }

    D3DDevice_SetLight(*numLights, &newLight);

    (*numLights)++;

    return TRUE;
}

// match: _RwXboxLightsEnable @ 0x002DF5A0
void
RwXboxLightsEnable(RwInt32 numLights, RwBool enable)
{
    if (enable)
    {
        while (numLights > numActiveLights)
        {
            D3DDevice_LightEnable(numActiveLights, TRUE);
            numActiveLights++;
        }

        while (numLights < numActiveLights)
        {
            D3DDevice_LightEnable(--numActiveLights, FALSE);
        }

        _rwXbRenderStateForce(D3DRS_LIGHTING, TRUE);
    }
    else
    {
        while (numActiveLights > 0)
        {
            D3DDevice_LightEnable(--numActiveLights, FALSE);
        }

        _rwXbRenderStateForce(D3DRS_LIGHTING, FALSE);
    }
}
