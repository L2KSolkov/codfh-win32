/*
 * codfh-match: RenderWare Audio's interface definitions (0x2417C0-0x2418E0):
 * the listener (the database's name; the PS2 header's output interface has
 * these parameters), voice 3D and virtual voice interfaces, each a static
 * interface definition registered with its parameter tables and
 * unregistered at close.
 */
#include "rwa.h"
#include "rwaint.h"



extern RwUInt8 unk_506BEC[];        /* the listener interface */
extern RwUInt8 unk_506C14[];        /* the voice 3D interface */
extern RwUInt8 unk_506C3C[];        /* the virtual voice interface */

extern RwBool sub_243E20(void *iface);
extern void RwaWaveDictAssignID(void *iface, const void *uuid, const void *textID);
extern void sub_243CD0(void *iface, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_243EA0(void *iface);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED2AC @ 0x003ED2AC
// match: _unk_3ED2BC @ 0x003ED2BC
// match: _unk_3ED2CC @ 0x003ED2CC
// match: _unk_3ED2DC @ 0x003ED2DC
// match: _unk_3ED2EC @ 0x003ED2EC
// match: _unk_3ED2FC @ 0x003ED2FC
// match: _unk_3ED30C @ 0x003ED30C
// match: _unk_3ED31C @ 0x003ED31C
// match: _unk_3ED32C @ 0x003ED32C
// match: _unk_3ED33C @ 0x003ED33C
// match: _unk_3ED34C @ 0x003ED34C
// match: _unk_3ED35C @ 0x003ED35C
// match: _unk_3ED36C @ 0x003ED36C
// match: _unk_3ED37C @ 0x003ED37C
// match: _unk_3ED38C @ 0x003ED38C
// match: _unk_3ED39C @ 0x003ED39C
// match: _unk_3ED3AC @ 0x003ED3AC
// match: _unk_3ED3BC @ 0x003ED3BC
// match: _unk_3ED3CC @ 0x003ED3CC
// match: _unk_3ED3DC @ 0x003ED3DC
// match: _unk_3ED3EC @ 0x003ED3EC
// match: _unk_3ED3FC @ 0x003ED3FC
// match: _unk_3ED40C @ 0x003ED40C
// match: _unk_3ED41C @ 0x003ED41C
// match: _unk_3ED42C @ 0x003ED42C
// match: _unk_3ED43C @ 0x003ED43C
// match: _unk_3ED44C @ 0x003ED44C
// match: _unk_3ED45C @ 0x003ED45C
// match: _unk_3ED46C @ 0x003ED46C
// match: _unk_3ED47C @ 0x003ED47C
// match: _unk_3ED48C @ 0x003ED48C

// What its data definitions name.
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED54C[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED2AC
const RwaUUID unk_3ED2AC = { 0xFFDF7A37, 0x5CD3, 0x4871, { 0x91, 0xEF, 0xB4, 0x84, 0xEA, 0x00, 0x47, 0x23 } };
// 0x003ED2BC
const RwaUUID unk_3ED2BC = { 0xFD9E290F, 0x67EA, 0x409B, { 0xB7, 0xA7, 0xA5, 0xD2, 0x2D, 0x89, 0xD3, 0x59 } };
// 0x003ED2CC
const RwaUUID unk_3ED2CC = { 0xCF566451, 0x45F9, 0x418C, { 0xAB, 0x2C, 0x0A, 0x4D, 0xA9, 0x16, 0x15, 0x13 } };
// 0x003ED2DC
const RwaUUID unk_3ED2DC = { 0x375F32EA, 0x37F7, 0x4D48, { 0xB1, 0x0F, 0x40, 0x55, 0x2E, 0xE7, 0xD6, 0x0B } };
// 0x003ED2EC
const RwaUUID unk_3ED2EC = { 0xF82ECB78, 0xACAC, 0x4283, { 0xA4, 0xD9, 0xEC, 0x5A, 0x1F, 0x56, 0x08, 0x94 } };
// 0x003ED2FC
const RwaUUID unk_3ED2FC = { 0x693F0C0A, 0x96AE, 0x426E, { 0xA2, 0x78, 0xD9, 0x7B, 0x5D, 0xAA, 0x9F, 0x4C } };
// 0x003ED30C
const RwaUUID unk_3ED30C = { 0x60D9C3A9, 0x3CAC, 0x440F, { 0x8C, 0xA9, 0xDC, 0xF2, 0x0E, 0x19, 0xF3, 0x6D } };
// 0x003ED31C
const RwaUUID unk_3ED31C = { 0xD84564D3, 0x1F30, 0x416B, { 0x97, 0x1F, 0xBF, 0x06, 0x91, 0x32, 0x39, 0x54 } };
// 0x003ED32C
const RwaUUID unk_3ED32C = { 0x5666BF87, 0x84E8, 0x463A, { 0xB3, 0xBD, 0x23, 0x80, 0x4B, 0x5F, 0xF2, 0x84 } };
// 0x003ED33C
const RwaUUID unk_3ED33C = { 0x19301A80, 0x20D3, 0x4DD1, { 0x9A, 0x23, 0xA4, 0xC5, 0x91, 0x8A, 0x1B, 0xB6 } };
// 0x003ED34C
const RwaUUID unk_3ED34C = { 0xE636F986, 0x07C4, 0x4CD7, { 0xA0, 0x35, 0xCB, 0x5B, 0x54, 0xFE, 0x89, 0xA2 } };
// 0x003ED35C
const RwaUUID unk_3ED35C = { 0xB3130A52, 0x9180, 0x484A, { 0x86, 0xE6, 0x8B, 0x86, 0x71, 0x4B, 0x7D, 0xB8 } };
// 0x003ED36C
const RwaUUID unk_3ED36C = { 0xA84A7F26, 0x3824, 0x4C08, { 0xAC, 0x7C, 0xC8, 0x96, 0x56, 0xA4, 0x99, 0xD4 } };
// 0x003ED37C
const RwaUUID unk_3ED37C = { 0x13CFFA08, 0x6182, 0x49CC, { 0xB0, 0xFD, 0xF1, 0xD3, 0xE4, 0x46, 0x0D, 0x82 } };
// 0x003ED38C
const RwaUUID unk_3ED38C = { 0xE496ACB6, 0xC529, 0x497E, { 0x83, 0x2E, 0x24, 0x93, 0xDE, 0x54, 0xBA, 0xD2 } };
// 0x003ED39C
const RwaUUID unk_3ED39C = { 0x2017C469, 0x206B, 0x41B7, { 0xAB, 0x16, 0x7B, 0x81, 0xFA, 0x45, 0x06, 0xA5 } };
// 0x003ED3AC
const RwaUUID unk_3ED3AC = { 0x65AAD49A, 0x1E87, 0x4AAF, { 0x90, 0x2F, 0x8A, 0xA0, 0xA3, 0x2D, 0x58, 0x0B } };
// 0x003ED3BC
const RwaUUID unk_3ED3BC = { 0xEE3BA9EA, 0xC3F0, 0x4584, { 0xB8, 0xFD, 0x9F, 0xB3, 0x8E, 0xD8, 0x23, 0x35 } };
// 0x003ED3CC
const RwaUUID unk_3ED3CC = { 0xE7EB1626, 0x52A1, 0x4A06, { 0x98, 0xBB, 0xF1, 0x6E, 0x40, 0x76, 0x2C, 0xB4 } };
// 0x003ED3DC
const RwaUUID unk_3ED3DC = { 0x47C8D2BF, 0xDD68, 0x4E78, { 0x9B, 0x81, 0x1A, 0x3A, 0x73, 0x43, 0x5A, 0xCF } };
// 0x003ED3EC
const RwaUUID unk_3ED3EC = { 0x3618B7EE, 0xD269, 0x4489, { 0xB0, 0xAE, 0x3F, 0xE3, 0xC3, 0xC6, 0x45, 0x14 } };
// 0x003ED3FC
const RwaUUID unk_3ED3FC = { 0x75754CBF, 0x6552, 0x4FCD, { 0xB5, 0x72, 0x02, 0x32, 0xE6, 0xB5, 0x5D, 0x6E } };
// 0x003ED40C
const RwaUUID unk_3ED40C = { 0x539BEB39, 0x5632, 0x4814, { 0x92, 0x1E, 0xB3, 0xA6, 0x04, 0x7D, 0x08, 0xF4 } };
// 0x003ED41C
const RwaUUID unk_3ED41C = { 0x9B9C9B88, 0x5654, 0x4CFB, { 0x8A, 0x0B, 0x6F, 0x9A, 0x22, 0x8D, 0x59, 0xBA } };
// 0x003ED42C
const RwaUUID unk_3ED42C = { 0xB5B910CD, 0x83D7, 0x40E3, { 0xAC, 0x99, 0xDB, 0x7E, 0xAB, 0xCB, 0xAD, 0xE7 } };
// 0x003ED43C
const RwaUUID unk_3ED43C = { 0xFBD72A03, 0x233C, 0x4055, { 0x89, 0xE2, 0xEB, 0x81, 0x50, 0xBD, 0xD5, 0x82 } };
// 0x003ED44C
const RwaUUID unk_3ED44C = { 0x71B533BE, 0x54FD, 0x45D5, { 0xA6, 0x73, 0xD9, 0xCE, 0xC3, 0x56, 0xB0, 0x47 } };
// 0x003ED45C
const RwaUUID unk_3ED45C = { 0x3E151DEA, 0xBCE1, 0x4DDA, { 0xBA, 0x89, 0x11, 0x5F, 0x23, 0xE7, 0xF8, 0x4C } };
// 0x003ED46C
const RwaUUID unk_3ED46C = { 0x47386E2D, 0x2179, 0x456C, { 0x9B, 0x1C, 0xED, 0x38, 0xD4, 0x15, 0x80, 0x41 } };
// 0x003ED47C
const RwaUUID unk_3ED47C = { 0x38356D52, 0xEB3D, 0x4FFA, { 0xB1, 0x5F, 0x5F, 0x4A, 0xD2, 0x59, 0x45, 0x79 } };
// 0x003ED48C
const RwaUUID unk_3ED48C = { 0x7DEC584E, 0xA8EA, 0x4BF2, { 0xA8, 0xD8, 0x90, 0x4F, 0x71, 0xEF, 0xEE, 0xE3 } };
// 0x003ED49C
const RwaUUID unk_3ED49C = { 0x98653ECC, 0x78FB, 0x47ED, { 0x8A, 0x8C, 0xF0, 0xDC, 0x05, 0x30, 0x10, 0x18 } };
// 0x0042E9B0
void *unk_42E9B0[40] =
{
    (void *)&unk_3ED2BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2DC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2FC,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED31C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED33C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED35C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED37C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED3AC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
};
// 0x0042EA50
void *unk_42EA50[46] =
{
    (void *)&unk_3ED2CC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2EC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED30C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED32C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED34C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED36C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED38C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED39C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED3BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    0,
};
// 0x0042EB08
void *unk_42EB08[60] =
{
    (void *)&unk_3ED3DC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED3FC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED41C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED43C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2DC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2FC,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED31C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED33C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED35C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED37C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED3AC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
};
// 0x0042EBF8
void *unk_42EBF8[66] =
{
    (void *)&unk_3ED3EC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED40C,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED42C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED44C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2CC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2EC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED30C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED32C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED34C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED36C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED38C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED39C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED3BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    0,
};
// 0x0042ED00
void *unk_42ED00[70] =
{
    (void *)&unk_3ED46C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED48C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED3DC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED3FC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED41C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED43C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2DC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2FC,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED31C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED33C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED35C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED37C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED3AC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
};
// 0x0042EE18
void *unk_42EE18[96] =
{
    (void *)&unk_3ED47C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED49C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED3EC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED40C,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED42C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED44C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2CC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2EC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED30C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED32C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED34C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED36C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED38C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED39C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED3BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    0,
    (void *)0x800000,
    (void *)0x7F7FFFFF,
    0,
    (void *)0x1,
    (void *)0x7F80,
    (void *)0xFF00,
    (void *)0x7FFF8000,
    (void *)0xFFFF0000,
    (void *)0x80000000,
    (void *)0x7FFFFFFF,
    0,
    (void *)0xFFFFFFFF,
    0,
    (void *)0x80000000,
    (void *)0xFFFFFFFF,
    (void *)0x7FFFFFFF,
    0,
    0,
    (void *)0xFFFFFFFF,
    (void *)0xFFFFFFFF,
};
// 0x00506BEC
RwUInt8 unk_506BEC[40];
// 0x00506C14
RwUInt8 unk_506C14[40];
// 0x00506C3C
RwUInt8 unk_506C3C[796];
// End of its data definitions.

// match: _unk_3ED49C @ 0x003ED49C


// match: _unk_42E9B0 @ 0x0042E9B0


// match: _unk_42EA50 @ 0x0042EA50


// match: _unk_42EB08 @ 0x0042EB08


// match: _unk_42EBF8 @ 0x0042EBF8


// match: _unk_42ED00 @ 0x0042ED00


// match: _unk_42EE18 @ 0x0042EE18

// match: _RwaListenerInterfaceRegister @ 0x002417C0
// sp-match: _RwaListenerInterfaceRegister @ 0x00155900

void *
RwaListenerInterfaceRegister(void)
{
    if (!sub_243E20(unk_506BEC))
    {
        return NULL;
    }

    RwaWaveDictAssignID(unk_506BEC, &unk_3ED2AC, NULL);
    sub_243CD0(unk_506BEC, unk_42E9B0, 8, unk_42EA50, 9);

    return unk_506BEC;
}

// match: _sub_241810 @ 0x00241810
// sp-match: _sub_241810 @ 0x00155950
RwBool
sub_241810(void)
{
    return sub_243EA0(unk_506BEC);
}

// match: _RwaVoice3DInterfaceRegister @ 0x00241820
// sp-match: _RwaVoice3DInterfaceRegister @ 0x00155960
void *
RwaVoice3DInterfaceRegister(void)
{
    if (!sub_243E20(unk_506C14))
    {
        return NULL;
    }

    RwaWaveDictAssignID(unk_506C14, &unk_3ED3CC, NULL);
    sub_243CD0(unk_506C14, unk_42EB08, 12, unk_42EBF8, 13);

    return unk_506C14;
}

// match: _sub_241870 @ 0x00241870
// sp-match: _sub_241870 @ 0x001559B0
RwBool
sub_241870(void)
{
    return sub_243EA0(unk_506C14);
}

// match: _RwaVirtualVoiceInterfaceRegister @ 0x00241880
// sp-match: _RwaVirtualVoiceInterfaceRegister @ 0x001559C0
void *
RwaVirtualVoiceInterfaceRegister(void)
{
    if (!sub_243E20(unk_506C3C))
    {
        return NULL;
    }

    RwaWaveDictAssignID(unk_506C3C, &unk_3ED45C, NULL);
    sub_243CD0(unk_506C3C, unk_42ED00, 14, unk_42EE18, 15);

    return unk_506C3C;
}

// match: _sub_2418D0 @ 0x002418D0
// sp-match: _sub_2418D0 @ 0x00155A10
RwBool
sub_2418D0(void)
{
    return sub_243EA0(unk_506C3C);
}
