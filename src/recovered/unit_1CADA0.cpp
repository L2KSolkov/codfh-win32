// Split from unit_1CA890.cpp at 0x1CADA0, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include <stdio.h>
#include <string.h>
#include "game/loc.h"
#include "game/assert.h"
#include "types/type_DC400.h"
#include "game/pool.h"

// Conditions retain the loads of the image's compiled-out checks.
#define LOCTEXT_CHECK(condition) { if (!(condition)) { } }

// match: _$E3 @ 0x0030EB60
// match: _$E5 @ 0x0030EB70
// match: _$E7 @ 0x0030EB80
// match: _$E9 @ 0x0030EB90
// match: _$E11 @ 0x0030EBA0

extern const RwChar *dword_42CCF8[3];

extern const RwUInt32 dword_3E3D48[3];

extern const RwUInt32 dword_3E3D3C[3];

// match: __ehhandler$?sub_1CB260@type_1CB260@@QAEXII@Z>1>8 @ 0x0041F7BC
// match: __ehhandler$?sub_1CB260@type_1CB260@@QAEXII@Z>1 @ 0x0041F7C4
// match: __ehhandler$?sub_1CB720@@YA?AUtype_1CB670@@PBD@Z>1>8 @ 0x0041F7E0
// match: __ehhandler$?sub_1CB720@@YA?AUtype_1CB670@@PBD@Z>1 @ 0x0041F7F0
// match: __ehhandler$?sub_1CB8B0@@YA?AUtype_1CB670@@PBD00H@Z>1>8 @ 0x0041F80C
// match: __ehhandler$?sub_1CB8B0@@YA?AUtype_1CB670@@PBD00H@Z>1 @ 0x0041F814
// match: __ehhandler$?sub_1CB7B0@@YA?AUtype_1CB670@@PBD0H@Z>1>8 @ 0x0041F830
// match: __ehhandler$?sub_1CB7B0@@YA?AUtype_1CB670@@PBD0H@Z>1 @ 0x0041F838
// match: __ehhandler$?sub_1CB9B0@@YAPAUtype_1CB670@@XZ>1>8 @ 0x0041F854
// match: __ehhandler$?sub_1CB9B0@@YAPAUtype_1CB670@@XZ>1 @ 0x0041F85C
// match: __ehhandler$?sub_1CBA30@@YAPAUtype_1CB670@@XZ>1>8 @ 0x0041F878
// match: __ehhandler$?sub_1CBA30@@YAPAUtype_1CB670@@XZ>1 @ 0x0041F880
// match: __ehhandler$?sub_1CBAB0@@YAPAUtype_1CB670@@XZ>1>8 @ 0x0041F89C
// match: __ehhandler$?sub_1CBAB0@@YAPAUtype_1CB670@@XZ>1 @ 0x0041F8A4
// match: __ehhandler$?sub_1CBB30@@YAPAUtype_1CB670@@XZ>1>8 @ 0x0041F8C0
// match: __ehhandler$?sub_1CBB30@@YAPAUtype_1CB670@@XZ>1 @ 0x0041F8C8
// match: __ehhandler$?sub_1CBBB0@@YAABUtype_1CB670@@XZ>1>8 @ 0x0041F8E4
// match: __ehhandler$?sub_1CBBB0@@YAABUtype_1CB670@@XZ>1 @ 0x0041F8EC
// match: ??_C@_01KICIPPFI@?2?$AA@ @ 0x003E3D54
// match: ??_C@_0DA@MMFFFABP@Translation?5for?5string?5?8?$CFs?8?5coul@ @ 0x003E3D58
// match: ??_C@_04DLIHGFEF@?4loc?$AA@ @ 0x003E3D88
// match: ??_C@_04DHLNEAA@LOC?2?$AA@ @ 0x003E3D90
// match: ??_C@_01LFCBOECM@?4?$AA@ @ 0x003E3D98
// match: ??_C@_01FGNFDNOH@?$CF?$AA@ @ 0x003E3D9C
// match: ??_C@_03KHICJKCI@?4?4?4?$AA@ @ 0x003E3DA0

// match: ?sub_1CADA0@type_1CAC10@@QAEXHPA_N@Z @ 0x001CADA0
void type_1CAC10::sub_1CADA0(RwInt32 arg_0, bool *arg_4)
{
    RwChar var_24[0x20] = "";

    if (!unk_00[arg_0])
    {
        unk_00[arg_0] = new type_1CB260;
        unk_00[arg_0]->sub_1CB260(dword_3E3D3C[arg_0], dword_3E3D48[arg_0]);
    }
    strcpy(var_24, sub_1CA890(unk_0C));
    strcat(var_24, "\\");
    strcat(var_24, dword_42CCF8[arg_0]);
    unk_00[arg_0]->sub_1CB390(var_24);
}
// match: ?sub_1CAEA0@type_1CAC10@@QAEPBGPBDH@Z @ 0x001CAEA0
const RwUInt16 *type_1CAC10::sub_1CAEA0(const RwChar *arg_0, RwInt32 arg_4)
{
    const RwUInt16 *var_4;

    var_4 = 0;
    if (unk_00[arg_4])
        var_4 = unk_00[arg_4]->sub_1CB640(arg_0);
    if (var_4)
        return var_4;
    if (arg_4 && unk_00[0])
        var_4 = unk_00[0]->sub_1CB640(arg_0);
    if (var_4)
        return var_4;
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("Translation for string '%s' could not be found\n", arg_0);
    return 0;
}
// The narrow result is the null-safe string itself. sub_E3970 forwards
// its return buffer, and type_1CB670's localized constructor initializes
// its type_1A5EA0 base directly from that result (sub_1CB6B0).
// match: ?sub_1CAF30@type_1CAC10@@QAE?AUtype_1A5EA0@@PBDH@Z @ 0x001CAF30
type_1A5EA0 type_1CAC10::sub_1CAF30(const RwChar *arg_0, RwInt32 arg_4)
{
    const RwUInt16 *var_4;
    RwChar var_408[0x400];

    if (!arg_0 || !*arg_0)
        return type_1A5EA0("");
    var_4 = sub_1CAEA0(arg_0, arg_4);
    // Compiled-out language check: one load advances the registers after
    // the lookup, as at 0x1CAF9E (docs/toolchain.md).
    LOCTEXT_CHECK(unk_0C >= 0);
    if (var_4)
    {
        sub_1C80D0(var_408, var_4);
        return type_1A5EA0(var_408);
    }
    return type_1A5EA0(arg_0);
}
// match: ?sub_1CB000@@YAXPADPBD1@Z @ 0x001CB000
void sub_1CB000(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8)
{
    bool var_1;
    RwChar var_108[0x100];
    RwUInt32 var_10C;

    var_1 = false;
    for (var_10C = 0; var_10C <= strlen(arg_4); var_10C++)
    {
        if (var_1)
        {
            if (arg_4[var_10C] == '1')
                var_108[var_10C] = 's';
            else
                var_108[var_10C] = arg_4[var_10C];
        }
        else
            var_108[var_10C] = arg_4[var_10C];
        if (arg_4[var_10C] == '%')
            var_1 = true;
        else
            var_1 = false;
    }
    sprintf(arg_0, var_108, arg_8);
}
// Formats arg_4 into arg_0 with its "%1" and "%2" as "%s", taking arg_8 and
// arg_C in the order they appear (swapped when "%2" comes first).
// match: ?sub_1CB0F0@@YAXPADPBD11@Z @ 0x001CB0F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1CB0F0(RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, const RwChar *arg_C)
{
    bool var_2;
    bool local_3;
    bool var_1;
    RwChar local_108[0x100];
    RwUInt32 var_10C;

    var_2 = false;
    local_3 = false;
    var_1 = true;
    for (var_10C = 0; var_10C <= strlen(arg_4); var_10C++)
    {
        if (var_2)
        {
            if (arg_4[var_10C] == '1')
            {
                local_108[var_10C] = 's';
                var_1 = false;
            }
            else if (arg_4[var_10C] == '2')
            {
                local_108[var_10C] = 's';
                if (var_1)
                {
                    local_3 = true;
                    var_1 = false;
                }
            }
            else
                local_108[var_10C] = arg_4[var_10C];
        }
        else
            local_108[var_10C] = arg_4[var_10C];
        if (arg_4[var_10C] == '%')
            var_2 = true;
        else
            var_2 = false;
    }
    if (local_3)
        sprintf(arg_0, local_108, arg_C, arg_8);
    else
        sprintf(arg_0, local_108, arg_8, arg_C);
}
// match: ??1type_1CB260@@QAE@XZ @ 0x001CB240
type_1CB260::~type_1CB260()
{
    sub_1CB310();
}
// match: ?sub_1CB260@type_1CB260@@QAEXII@Z @ 0x001CB260
// match: __ehhandler$?sub_1CB260@type_1CB260@@QAEXII@Z-0xB @ 0x003033F0
// match: __ehhandler$?sub_1CB260@type_1CB260@@QAEXII@Z @ 0x003033FB
void type_1CB260::sub_1CB260(RwUInt32 arg_0, RwUInt32 arg_4)
{
    unk_08 = arg_0;
    unk_0C = arg_4;
    unk_00 = new RwUInt8[arg_0];
    unk_04 = new type_1CA8A0(arg_4, 1);
}
// match: ?sub_1CB310@type_1CB260@@QAEXXZ @ 0x001CB310
void type_1CB260::sub_1CB310()
{
    delete[] unk_00;
    unk_00 = 0;
    delete unk_04;
    unk_04 = 0;
}
// match: ?sub_1CB390@type_1CB260@@QAE_NPBD@Z @ 0x001CB390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_1CB260::sub_1CB390(const RwChar *arg_0)
{
    RwChar var_A8[0x80];
    const RwChar *var_20;
    RwUInt32 l1C;
    kujuUI::cFileIn *m_18;
    const RwChar *ebp_14;
    RwUInt32 lv_10;
    RwUInt32 var_C;
    const RwUInt16 *bp_8;
    RwUInt32 bp_4;

    ebp_14 = 0;
    bp_8 = 0;
    unk_04->sub_reset();
    strcpy(var_A8, "LOC\\");
    strcat(var_A8, arg_0);
    strcat(var_A8, ".loc");
    kujuUI::sub_1C8CA0(var_A8, &m_18);
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    if (!m_18)
        return false;
    if (m_18->sub_1C8BA0(&l1C, 4))
    {
        if (!unk_04)
        {
        }
        if (l1C < unk_08)
        {
            if (!unk_04)
            {
            }
            if (m_18->sub_1C8BA0(&bp_4, 4))
            {
                if (!unk_04)
                {
                }
                if (bp_4 < unk_0C)
                {
                    if (m_18->sub_1C8BA0(unk_00, l1C - 8))
                    {
                        var_20 = (const RwChar *)unk_00;
                        ebp_14 = var_20;
                        var_C = 0;
                        while (var_C < bp_4)
                        {
                            ebp_14 += strlen(ebp_14) + 1;
                            var_C++;
                        }
                        bp_8 = (const RwUInt16 *)(((RwUInt32)ebp_14 + 1) & ~1);
                        ebp_14 = var_20;
                    }
                    for (lv_10 = 0; lv_10 < bp_4; lv_10++)
                    {
                        const RwChar *var_AC = ebp_14;
                        const RwUInt16 *pB0 = bp_8;

                        ebp_14 += strlen(ebp_14) + 1;
                        bp_8 += sub_1C80A0(bp_8) + 1;
                        unk_04->sub_1CABA0(var_AC, pB0);
                    }
                    delete m_18;
                    return true;
                }
            }
        }
    }
    delete m_18;
    return true;
}
// match: ?sub_1CB640@type_1CB260@@QAEPBGPBD@Z @ 0x001CB640
const RwUInt16 *type_1CB260::sub_1CB640(const RwChar *arg_0)
{
    const RwUInt16 *var_4;

    var_4 = unk_04->sub_1CAB70(arg_0);
    if (var_4)
        return var_4;
    return 0;
}
// Their frames' unused slots are the string constructor's expansion,
// reserved though it is not inlined (docs/toolchain.md).
// match: ??0type_1CB670@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z @ 0x001CB670
type_1CB670::type_1CB670(const std::string &arg_0) : type_1A5EA0(arg_0.c_str())
{
}
// match: ??0type_1CB670@@QAE@PBDH@Z @ 0x001CB6B0
type_1CB670::type_1CB670(const RwChar *arg_0, RwInt32 arg_4) : type_1A5EA0(sub_E3970(arg_0, arg_4))
{
}
// match: ??0type_1CB670@@QAE@HABUtype_1A5EA0@@@Z @ 0x001CB6E0
type_1CB670::type_1CB670(RwInt32 arg_0, const type_1A5EA0 &arg_4) : type_1A5EA0(arg_4.c_str())
{
}
// The string's constructor is not inlined but its slots are reserved
// (docs/toolchain.md); the temporary comes from the implicit conversion.
// match: ?sub_1CB720@@YA?AUtype_1CB670@@PBD@Z @ 0x001CB720
// match: __ehhandler$?sub_1CB720@@YA?AUtype_1CB670@@PBD@Z-0x21 @ 0x00303410
// match: __ehhandler$?sub_1CB720@@YA?AUtype_1CB670@@PBD@Z @ 0x00303431
type_1CB670 sub_1CB720(const RwChar *arg_0)
{
    return type_1CB670(1, arg_0);
}
// match: ?sub_1CB790@type_1CB670@@QAEXXZ @ 0x001CB790
void type_1CB670::sub_1CB790()
{
    sub_1C84D0();
}
// match: ?sub_1CB7B0@@YA?AUtype_1CB670@@PBD0H@Z @ 0x001CB7B0
// match: __ehhandler$?sub_1CB7B0@@YA?AUtype_1CB670@@PBD0H@Z-0xB @ 0x00303440
// match: __ehhandler$?sub_1CB7B0@@YA?AUtype_1CB670@@PBD0H@Z @ 0x0030344B
type_1CB670 sub_1CB7B0(const RwChar *arg_0, const RwChar *arg_4, RwInt32 arg_8)
{
    RwChar var_214[0x200];

    sub_1CB000(var_214, sub_E3970(arg_0, arg_8).c_str(), arg_4);
    return sub_1CB720(var_214);
}
// The same unwinding and handler as sub_1CB7B0's (folded by /OPT:ICF).
// symbol: __ehhandler$?sub_1CB8B0@@YA?AUtype_1CB670@@PBD00H@Z = 0x0030344B
// match: ?sub_1CB8B0@@YA?AUtype_1CB670@@PBD00H@Z @ 0x001CB8B0
type_1CB670 sub_1CB8B0(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, RwInt32 arg_C)
{
    RwChar var_214[0x200];

    sub_1CB0F0(var_214, sub_E3970(arg_0, arg_C).c_str(), arg_4, arg_8);
    return sub_1CB720(var_214);
}
// match: ?sub_1CB9B0@@YAPAUtype_1CB670@@XZ @ 0x001CB9B0
// match: __ehhandler$?sub_1CB9B0@@YAPAUtype_1CB670@@XZ-0xE @ 0x00303460
// match: __ehhandler$?sub_1CB9B0@@YAPAUtype_1CB670@@XZ @ 0x0030346E
type_1CB670 *sub_1CB9B0()
{
    static type_1CB670 unk_4FEB1C = sub_1CB720("\n");

    return &unk_4FEB1C;
}
// match: ?sub_1CBA30@@YAPAUtype_1CB670@@XZ @ 0x001CBA30
// match: __ehhandler$?sub_1CBA30@@YAPAUtype_1CB670@@XZ-0xE @ 0x00303480
// match: __ehhandler$?sub_1CBA30@@YAPAUtype_1CB670@@XZ @ 0x0030348E
type_1CB670 *sub_1CBA30()
{
    static type_1CB670 unk_4FEB3C = sub_1CB720(".");

    return &unk_4FEB3C;
}
// match: ?sub_1CBAB0@@YAPAUtype_1CB670@@XZ @ 0x001CBAB0
// match: __ehhandler$?sub_1CBAB0@@YAPAUtype_1CB670@@XZ-0xE @ 0x003034A0
// match: __ehhandler$?sub_1CBAB0@@YAPAUtype_1CB670@@XZ @ 0x003034AE
type_1CB670 *sub_1CBAB0()
{
    static type_1CB670 unk_4FEB5C = sub_1CB720("%");

    return &unk_4FEB5C;
}
// match: ?sub_1CBB30@@YAPAUtype_1CB670@@XZ @ 0x001CBB30
// match: __ehhandler$?sub_1CBB30@@YAPAUtype_1CB670@@XZ-0xE @ 0x003034C0
// match: __ehhandler$?sub_1CBB30@@YAPAUtype_1CB670@@XZ @ 0x003034CE
type_1CB670 *sub_1CBB30()
{
    static type_1CB670 unk_4FEB7C = sub_1CB720("/");

    return &unk_4FEB7C;
}
// match: ?sub_1CBBB0@@YAABUtype_1CB670@@XZ @ 0x001CBBB0
// match: __ehhandler$?sub_1CBBB0@@YAABUtype_1CB670@@XZ-0xE @ 0x003034E0
// match: __ehhandler$?sub_1CBBB0@@YAABUtype_1CB670@@XZ @ 0x003034EE
const type_1CB670 &sub_1CBBB0()
{
    static type_1CB670 unk_4FEB9C = sub_1CB720("...");

    return unk_4FEB9C;
}
// match: ?sub_1CBC30@@YAPAUtype_1F8BF0@@XZ @ 0x001CBC30
type_1F8BF0 *sub_1CBC30()
{
    return &unk_4FEBDC;
}
// match: ?sub_1CBC40@@YAPAUtype_1F8BF0@@XZ @ 0x001CBC40
type_1F8BF0 *sub_1CBC40()
{
    return &unk_4FEBFC;
}
// match: ?sub_1CBC50@@YAPAUtype_1F8BF0@@XZ @ 0x001CBC50
type_1F8BF0 *sub_1CBC50()
{
    return &unk_4FEC1C;
}
// match: ?sub_1CBC60@@YAPAUtype_1F8BF0@@XZ @ 0x001CBC60
type_1F8BF0 *sub_1CBC60()
{
    return &unk_4FEBBC;
}
// match: ?sub_1CBC70@@YAPAUtype_1F8BF0@@XZ @ 0x001CBC70
type_1F8BF0 *sub_1CBC70()
{
    return &unk_4FEC3C;
}
