// kujuUI's parsed files (game/parsedfile.h).

#include <string.h>

#include "game/parsedfile.h"
#include "game/assert.h"
#include "types/type_505188.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BK@EADHPOBG@Binary?5file?5load?5failed?4?6?$AA@ @ 0x003E3BA4
// match: ??_C@_0BF@NEPPECMJ@Failed?5binary?5load?4?6?$AA@ @ 0x003E3BC0
// match: ??_C@_0CD@JBHLNDMA@?2COD?2SHARED?2fileIO?2cParsedFile?4c@ @ 0x003E3BD8
// match: ??_C@_0ID@OAKKCNDO@void?5__cdecl?5kujuUI?3?3cParsedFile@ @ 0x003E3C00
// match: __ehhandler$?sub_1C96B0@type_1C9590@kujuUI@@QBEHPBDHPBUtype_1C8DF0_104_00@2@IPAPAUtype_1C8DF0_104@2@@Z>1>8 @ 0x0041F700
// match: __ehhandler$?sub_1C96B0@type_1C9590@kujuUI@@QBEHPBDHPBUtype_1C8DF0_104_00@2@IPAPAUtype_1C8DF0_104@2@@Z>1 @ 0x0041F708
// match: __ehhandler$?loadBinaryFile@cParsedFile@kujuUI@@SAXPBDPBVcScopeValidator@2@PAPAV12@@Z>1>8 @ 0x0041F724
// match: __ehhandler$?loadBinaryFile@cParsedFile@kujuUI@@SAXPBDPBVcScopeValidator@2@PAPAV12@@Z>1 @ 0x0041F734
// match: __ehhandler$?sub_1C9FC0@cScopeValidator@kujuUI@@QBEHPBD0PAUtype_1C8DF0@2@PAPAU32@@Z>1>8 @ 0x0041F750
// match: __ehhandler$?sub_1C9FC0@cScopeValidator@kujuUI@@QBEHPBD0PAUtype_1C8DF0@2@PAPAU32@@Z>1 @ 0x0041F758
// match: __ehhandler$?sub_1CA470@type_1A5EA0@@QAEAAU1@PBD@Z>1>8 @ 0x0041F774
// match: __ehhandler$?sub_1CA470@type_1A5EA0@@QAEAAU1@PBD@Z>1 @ 0x0041F77C
// match: __ehhandler$?sub_1CA4E0@kujuUI@@YAXPAUcFileIn@1@PAPAUtype_1CA4E0@1@@Z>1>8 @ 0x0041F798
// match: __ehhandler$?sub_1CA4E0@kujuUI@@YAXPAUcFileIn@1@PAPAUtype_1CA4E0@1@@Z>1 @ 0x0041F7A0

// match: ??0type_1C8DF0@kujuUI@@QAE@PAUtype_1CA4E0@1@PBVcScopeValidator@1@@Z @ 0x001C8DF0

kujuUI::type_1C8DF0::type_1C8DF0(type_1CA4E0 *arg_0, const cScopeValidator *arg_4)
{
    unk_100 = 0;
    unk_184 = 0;
    unk_188 = 0;
    unk_18C = 0;
    unk_190 = arg_0;
    unk_194 = arg_4;
}

// match: ??0type_1C8DF0@kujuUI@@QAE@PBDPAU01@PBVcScopeValidator@1@@Z @ 0x001C8E50
kujuUI::type_1C8DF0::type_1C8DF0(const RwChar *arg_0, type_1C8DF0 *arg_4, const cScopeValidator *arg_8)
{
    unk_100 = 0;
    unk_184 = 0;
    unk_188 = 0;
    unk_18C = arg_4;
    unk_190 = arg_4->unk_190;
    unk_194 = arg_8;
    if (arg_0)
        unk_188 = arg_4->unk_190->sub_1CA620(arg_0);
}

// match: ??1type_1C8DF0@kujuUI@@QAE@XZ @ 0x001C8EE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
kujuUI::type_1C8DF0::~type_1C8DF0()
{
    RwUInt32 var_8;
    RwUInt32 l4;

    for (l4 = 0; l4 != unk_100; l4++)
        delete unk_00[l4];
    for (var_8 = 0; var_8 != unk_184; var_8++)
        delete unk_104[var_8];
}

// match: ?sub_1C8FC0@type_1C8DF0@kujuUI@@QAEPBDXZ @ 0x001C8FC0
const RwChar *kujuUI::type_1C8DF0::sub_1C8FC0()
{
    return unk_188;
}

// match: ?sub_1C8FE0@type_1C8DF0@kujuUI@@QAEPBVcScopeValidator@2@XZ @ 0x001C8FE0
const kujuUI::cScopeValidator *kujuUI::type_1C8DF0::sub_1C8FE0()
{
    return unk_194;
}

// match: ?sub_1C9000@type_1C8DF0@kujuUI@@QAEXPAPAUtype_1C8DF0_104@2@@Z @ 0x001C9000
void kujuUI::type_1C8DF0::sub_1C9000(type_1C8DF0_104 **arg_0)
{
    unk_104[unk_184] = *arg_0;
    unk_184++;
    *arg_0 = 0;
}

// match: ?sub_1C9050@type_1C8DF0@kujuUI@@QAEXPAPAU12@@Z @ 0x001C9050
void kujuUI::type_1C8DF0::sub_1C9050(type_1C8DF0 **arg_0)
{
    unk_00[unk_100] = *arg_0;
    *arg_0 = 0;
    unk_100++;
}

// match: ?sub_1C9090@type_1C8DF0@kujuUI@@QAEIXZ @ 0x001C9090
RwUInt32 kujuUI::type_1C8DF0::sub_1C9090()
{
    return unk_100;
}

// match: ?sub_1C90B0@type_1C8DF0@kujuUI@@QAEPAUtype_1C8DF0_104@2@PBUtype_1C9590@2@@Z @ 0x001C90B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
kujuUI::type_1C8DF0_104 *kujuUI::type_1C8DF0::sub_1C90B0(const type_1C9590 *arg_0)
{
    RwUInt32 var_8;
    type_1C8DF0_104 *l4;

    l4 = 0;
    var_8 = 0;
    while (!l4 && var_8 < unk_184)
    {
        if (unk_104[var_8]->get_unk_44() == arg_0)
            l4 = unk_104[var_8];
        var_8++;
    }
    return l4;
}

// match: ?sub_1C9120@type_1C8DF0@kujuUI@@QAEIXZ @ 0x001C9120
RwUInt32 kujuUI::type_1C8DF0::sub_1C9120()
{
    return unk_184;
}

// match: ?sub_1C9140@type_1C8DF0@kujuUI@@QAEPAUtype_1C8DF0_104@2@I@Z @ 0x001C9140
kujuUI::type_1C8DF0_104 *kujuUI::type_1C8DF0::sub_1C9140(RwUInt32 arg_0)
{
    return unk_104[arg_0];
}

// match: ?sub_1C9160@type_1C8DF0@kujuUI@@QAE_NPAUcFileIn@2@@Z @ 0x001C9160
bool kujuUI::type_1C8DF0::sub_1C9160(cFileIn *arg_0)
{
    return sub_1C9190(arg_0, unk_190);
}

// match: ?sub_1C9190@type_1C8DF0@kujuUI@@QAE_NPAUcFileIn@2@PAUtype_1CA4E0@2@@Z @ 0x001C9190
bool kujuUI::type_1C8DF0::sub_1C9190(cFileIn *arg_0, type_1CA4E0 *arg_4)
{
    RwUInt32 varC = 0;
    RwUInt32 var_4 = 0;
    bool local_5 = true;

    if (arg_0->sub_1C8BA0(&varC, 4))
    {
        for (RwUInt32 var_54 = 0; var_54 != varC && local_5; var_54++)
        {
            RwUInt32 var_58 = 0;
            RwUInt32 var5C = 0;

            local_5 &= arg_0->sub_1C8BE0(&var_58);
            local_5 &= arg_0->sub_1C8BE0(&var5C);
            local_5 &= var_58 < (RwUInt32)arg_4->sub_1EE9D0();
            local_5 &= var5C < (RwUInt32)arg_4->sub_1EE9D0() || var5C == -1;
            if (local_5)
            {
                const RwChar *local_60 = arg_4->sub_1CA720(var_58);
                const RwChar *l64 = var5C != -1 ? arg_4->sub_1CA720(var5C) : 0;

                if (local_60)
                {
                    type_1C8DF0 *var_68 = 0;

                    if (!unk_194->sub_1C9F90(local_60, l64, this, &var_68) && var_68->sub_1C9190(arg_0, arg_4))
                        sub_1C9050(&var_68);
                    else
                    {
                        delete var_68;
                        local_5 = false;
                    }
                }
                else
                    local_5 = false;
            }
            else
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Failed binary load.\n");
            }
        }
        local_5 = arg_0->sub_1C8BA0(&var_4, 4);
        type_1C8DF0_104_00 var_50[8];

        for (RwUInt32 var_6C = 0; var_6C != var_4 && local_5; var_6C++)
        {
            type_1C8DF0_104 *local_78 = 0;
            RwUInt32 var80 = 0;
            RwUInt32 var_70 = 0;
            RwInt32 local_7C = 0;

            local_5 &= arg_0->sub_1C8BE0(&var_70);
            local_5 &= arg_0->sub_1C8BE0(&var80);
            local_5 &= arg_0->sub_1C8BE0(&local_7C);
            const RwChar *local_74 = arg_4->sub_1CA720(var_70);

            local_5 = local_74 != 0;
            for (RwUInt32 var_84 = 0; var_84 != var80; var_84++)
            {
                type_1C8DF0_104_00 var_8C(arg_0, arg_4);

                var_50[var_84] = var_8C;
                local_5 &= var_8C.sub_1EE9D0() != 0;
            }
            if (!local_5)
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Binary file load failed.\n");
            }
            sub_1C8FE0()->sub_1CA110(local_74, local_7C, var_50, var80, &local_78);
            if (local_78)
                sub_1C9000(&local_78);
            else
                local_5 = false;
        }
    }
    return local_5;
}

// match: ??0type_1C9590@kujuUI@@QAE@PBDHHHHHHHH@Z @ 0x001C9590
kujuUI::type_1C9590::type_1C9590(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                                 RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C, RwInt32 arg_20)
    : unk_00(arg_0)
{
    unk_28 = -1;
    if (sub_1C9660(arg_4) && sub_1C9660(arg_8) && sub_1C9660(arg_C) && sub_1C9660(arg_10) && sub_1C9660(arg_14) &&
        sub_1C9660(arg_18) && sub_1C9660(arg_1C))
        sub_1C9660(arg_20);
    unk_28 ^= *arg_0;
}

// match: ?sub_1C9660@type_1C9590@kujuUI@@QAE_NH@Z @ 0x001C9660
bool kujuUI::type_1C9590::sub_1C9660(RwInt32 arg_0)
{
    if (arg_0)
    {
        unk_28 <<= 3;
        unk_28 |= arg_0;
        *unk_04.sub_1C97A0() = arg_0;
        return true;
    }
    return false;
}

// match: ?sub_1C96B0@type_1C9590@kujuUI@@QBEHPBDHPBUtype_1C8DF0_104_00@2@IPAPAUtype_1C8DF0_104@2@@Z @ 0x001C96B0
// match: __ehhandler$?sub_1C96B0@type_1C9590@kujuUI@@QBEHPBDHPBUtype_1C8DF0_104_00@2@IPAPAUtype_1C8DF0_104@2@@Z-0xB @ 0x00303350
// match: __ehhandler$?sub_1C96B0@type_1C9590@kujuUI@@QBEHPBDHPBUtype_1C8DF0_104_00@2@IPAPAUtype_1C8DF0_104@2@@Z @ 0x0030335B
RwInt32 kujuUI::type_1C9590::sub_1C96B0(const RwChar *arg_0, RwInt32 arg_4, const type_1C8DF0_104_00 *arg_8, RwUInt32 arg_C,
                                        type_1C8DF0_104 **arg_10) const
{
    if (arg_4 != unk_28)
        return 1;
    type_1C8A60 lhs(arg_0);
    type_1C8A60 rhs(unk_00);

    if (lhs == rhs)
    {
        *arg_10 = new type_1C8DF0_104(arg_8, arg_C, this);
        return 0;
    }
    return 2;
}

// match: ??0type_1C9780@kujuUI@@QAE@XZ @ 0x001C9780
kujuUI::type_1C9780::type_1C9780()
{
    unk_20 = 0;
}

// match: ?sub_1C97A0@type_1C9780@kujuUI@@QAEPAHXZ @ 0x001C97A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 *kujuUI::type_1C9780::sub_1C97A0()
{
    RwInt32 *var_8;
    RwInt32 *l4;

    var_8 = (RwInt32 *)((RwUInt32)this + sub_200B80() * unk_20);
    unk_20++;
    l4 = var_8;
    return l4;
}

// match: ??0type_1C8DF0_104@kujuUI@@QAE@PBUtype_1C8DF0_104_00@1@IPBUtype_1C9590@1@@Z @ 0x001C97E0
kujuUI::type_1C8DF0_104::type_1C8DF0_104(const type_1C8DF0_104_00 *arg_0, RwUInt32 arg_4, const type_1C9590 *arg_8)
{
    RwUInt32 var_4;

    unk_40 = arg_4;
    unk_44 = arg_8;
    for (var_4 = 0; var_4 != arg_4; var_4++)
        unk_00[var_4] = arg_0[var_4];
}

// match: ?sub_1C9870@type_1C8DF0_104@kujuUI@@QAEPBDXZ @ 0x001C9870
const RwChar *kujuUI::type_1C8DF0_104::sub_1C9870()
{
    const RwChar *var_4;

    var_4 = unk_44->unk_00;
    return var_4;
}

// match: ?sub_1C9890@type_1C8DF0_104@kujuUI@@QAEPAUtype_1C8DF0_104_00@2@I@Z @ 0x001C9890
kujuUI::type_1C8DF0_104_00 *kujuUI::type_1C8DF0_104::sub_1C9890(RwUInt32 arg_0)
{
    return &unk_00[arg_0];
}

// match: ??0cParsedFile@kujuUI@@QAE@PAPAUtype_1C8DF0@1@PAPAUtype_1CA4E0@1@@Z @ 0x001C98B0
kujuUI::cParsedFile::cParsedFile(type_1C8DF0 **arg_0, type_1CA4E0 **arg_4)
{
    unk_00 = *arg_4;
    unk_04 = *arg_0;
    *arg_0 = 0;
    *arg_4 = 0;
}

// match: ??1cParsedFile@kujuUI@@QAE@XZ @ 0x001C98F0
kujuUI::cParsedFile::~cParsedFile()
{
    delete unk_04;
    delete unk_00;
}

// match: ?loadBinaryFile@cParsedFile@kujuUI@@SAXPBDPBVcScopeValidator@2@PAPAV12@@Z @ 0x001C9980
// match: __ehhandler$?loadBinaryFile@cParsedFile@kujuUI@@SAXPBDPBVcScopeValidator@2@PAPAV12@@Z-0x16 @ 0x00303370
// match: __ehhandler$?loadBinaryFile@cParsedFile@kujuUI@@SAXPBDPBVcScopeValidator@2@PAPAV12@@Z @ 0x00303386
void kujuUI::cParsedFile::loadBinaryFile(const RwChar *arg_0, const cScopeValidator *arg_4, cParsedFile **arg_8)
{
    cFileIn *var_10;

    *arg_8 = 0;
    var_10 = 0;
    sub_1C8CA0(arg_0, &var_10);
    if (var_10)
    {
        RwInt32 var_14 = 0;

        var_10->sub_1C8BA0(&var_14, 4);
        RwInt32 var_18 = 0;

        var_10->sub_1C8BA0(&var_18, 4);
        RwInt32 var_1C = arg_4->sub_6FCB0();

        sub_1C7F20(var_18 == var_1C, "\\COD\\SHARED\\fileIO\\cParsedFile.cpp", 0x7C,
                   "void __cdecl kujuUI::cParsedFile::loadBinaryFile(const char *,const class kujuUI::cScopeValidator *,"
                   "class kujuUI::cParsedFile ** )",
                   0);
        if (var_14 == 2000)
        {
            type_1CA4E0 *var_20 = 0;

            sub_1CA4E0(var_10, &var_20);
            if (var_20)
            {
                type_1C8DF0 *var_24 = new type_1C8DF0(var_20, arg_4);

                if (var_24->sub_1C9160(var_10))
                    *arg_8 = new cParsedFile(&var_24, &var_20);
            }
        }
        delete var_10;
    }
}

// match: ??0cScopeValidator@kujuUI@@QAE@XZ @ 0x001C9EA0
kujuUI::cScopeValidator::cScopeValidator()
{
    unk_108 = 0;
    unk_10C = 0;
    unk_110 = -1;
    unk_114 = 0;
}

// match: ??0cScopeValidator@kujuUI@@QAE@PBD0H@Z @ 0x001C9F00
kujuUI::cScopeValidator::cScopeValidator(const RwChar *arg_0, const RwChar *arg_4, RwInt32 arg_8)
{
    unk_108 = arg_0;
    unk_10C = arg_4;
    unk_114 = arg_8;
}

// match: ?sub_1C9F50@cScopeValidator@kujuUI@@QAEXPAUtype_1C9590@2@@Z @ 0x001C9F50
void kujuUI::cScopeValidator::sub_1C9F50(type_1C9590 *arg_0)
{
    *unk_84.sub_1CA3C0() = arg_0;
}

// match: ?sub_1C9F70@cScopeValidator@kujuUI@@QAEXPAV12@@Z @ 0x001C9F70
void kujuUI::cScopeValidator::sub_1C9F70(cScopeValidator *arg_0)
{
    *unk_00.sub_1CA3C0() = arg_0;
}

// match: ?sub_1C9F90@cScopeValidator@kujuUI@@QBEHPBD0PAUtype_1C8DF0@2@PAPAU32@@Z @ 0x001C9F90
RwInt32 kujuUI::cScopeValidator::sub_1C9F90(const RwChar *arg_0, const RwChar *arg_4, type_1C8DF0 *arg_8,
                                            type_1C8DF0 **arg_C) const
{
    *arg_C = 0;
    return sub_1C9FC0(arg_0, arg_4, arg_8, arg_C);
}

// match: ?sub_1C9FC0@cScopeValidator@kujuUI@@QBEHPBD0PAUtype_1C8DF0@2@PAPAU32@@Z @ 0x001C9FC0
// match: __ehhandler$?sub_1C9FC0@cScopeValidator@kujuUI@@QBEHPBD0PAUtype_1C8DF0@2@PAPAU32@@Z-0xB @ 0x00303390
// match: __ehhandler$?sub_1C9FC0@cScopeValidator@kujuUI@@QBEHPBD0PAUtype_1C8DF0@2@PAPAU32@@Z @ 0x0030339B
RwInt32 kujuUI::cScopeValidator::sub_1C9FC0(const RwChar *arg_0, const RwChar *arg_4, type_1C8DF0 *arg_8,
                                            type_1C8DF0 **arg_C) const
{
    RwInt32 var_10 = 1;

    for (type_1EFD70 var_18 = ((type_1CA430 &)unk_00).sub_1CA450();
         var_18.sub_1E8310(((type_1CA430 &)unk_00).sub_1CA400()); var_18.sub_204990())
    {
        cScopeValidator *var_1C = (cScopeValidator *)*var_18.sub_1EE9D0();

        {
            const RwChar *var_20 = var_1C->sub_1CA280();

            if (!strcmp(var_20, arg_0))
            {
                if (!arg_4)
                {
                    if (var_1C->sub_1CA260() != 2)
                        var_10 = 0;
                    else
                        var_10 = 3;
                }
                else if (arg_4)
                {
                    if (var_1C->sub_1CA260())
                        var_10 = 0;
                    else
                        var_10 = 4;
                }
                if (!var_10)
                {
                    *arg_C = new type_1C8DF0(arg_4, arg_8, var_1C);
                    break;
                }
            }
        }
    }
    return var_10;
}

// match: ?sub_1CA110@cScopeValidator@kujuUI@@QBEXPBDHPAUtype_1C8DF0_104_00@2@IPAPAUtype_1C8DF0_104@2@@Z @ 0x001CA110
void kujuUI::cScopeValidator::sub_1CA110(const RwChar *arg_0, RwInt32 arg_4, type_1C8DF0_104_00 *arg_8, RwUInt32 arg_C,
                                         type_1C8DF0_104 **arg_10) const
{
    for (type_1EFD70 var_8 = ((type_1CA430 &)unk_84).sub_1CA450();
         var_8.sub_1E8310(((type_1CA430 &)unk_84).sub_1CA400()); var_8.sub_204990())
    {
        type_1C9590 *var_C = (type_1C9590 *)*var_8.sub_1EE9D0();

        var_C->sub_1C96B0(arg_0, arg_4, arg_8, arg_C, arg_10);
        if (*arg_10)
            break;
    }
}

// match: ?sub_1CA1A0@cScopeValidator@kujuUI@@QAEXABV12@@Z @ 0x001CA1A0
void kujuUI::cScopeValidator::sub_1CA1A0(const cScopeValidator &arg_0)
{
    type_1CA430 *var_C = (type_1CA430 *)&arg_0.unk_00;
    type_1CA430 *var_10 = (type_1CA430 *)&arg_0.unk_84;

    for (type_1EFD70 var_18 = var_C->sub_1CA450(); var_18.sub_1E8310(var_C->sub_1CA400()); var_18.sub_204990())
        *unk_00.sub_1CA3C0() = *var_18.sub_1EE9D0();
    type_1EFD70 bp_8 = var_10->sub_1CA400();

    for (type_1EFD70 var_20 = var_10->sub_1CA450(); var_20.sub_1E8310(bp_8); var_20.sub_204990())
        *unk_84.sub_1CA3C0() = *var_20.sub_1EE9D0();
}

// match: ?sub_1CA260@cScopeValidator@kujuUI@@QBEHXZ @ 0x001CA260
RwInt32 kujuUI::cScopeValidator::sub_1CA260() const
{
    return unk_114;
}

// match: ?sub_1CA280@cScopeValidator@kujuUI@@QBEPBDXZ @ 0x001CA280
const RwChar *kujuUI::cScopeValidator::sub_1CA280() const
{
    return unk_108;
}

// match: ?sub_1CA2A0@cScopeValidator@kujuUI@@QAEXXZ @ 0x001CA2A0
void kujuUI::cScopeValidator::sub_1CA2A0()
{
    unk_110 = sub_1CA2C0();
}

// match: ?sub_1CA2C0@cScopeValidator@kujuUI@@QAEHXZ @ 0x001CA2C0
RwInt32 kujuUI::cScopeValidator::sub_1CA2C0()
{
    unk_110 = -1;
    for (type_1EFD70 var_8 = unk_00.sub_1CA450(); var_8.sub_1E8310(unk_00.sub_1CA400()); var_8.sub_204990())
    {
        cScopeValidator *var_C = (cScopeValidator *)*var_8.sub_1EE9D0();

        unk_110 += var_C->sub_1CA2C0();
    }
    for (type_204960 var_14 = unk_84.sub_1CA450(); var_14.sub_1E8310(unk_84.sub_1CA400()); var_14.sub_204990())
    {
        type_1C9590 *var_18 = (type_1C9590 *)*var_14.sub_1EE9D0();

        unk_110 += var_18->get_unk_28();
    }
    return unk_110;
}

// match: ?sub_1CA3C0@type_1CA430@kujuUI@@QAEPAPAXXZ @ 0x001CA3C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void **kujuUI::type_1CA430::sub_1CA3C0()
{
    void **var_8;
    void **l4;

    var_8 = (void **)((RwUInt32)this + sub_200B80() * unk_80);
    unk_80++;
    l4 = var_8;
    return l4;
}

// match: ?sub_1CA400@type_1CA430@kujuUI@@QAE?AUtype_1EFD70@2@XZ @ 0x001CA400
kujuUI::type_1EFD70 kujuUI::type_1CA430::sub_1CA400()
{
    return type_1EFD70(&unk_00[unk_80], this);
}

// match: ??0type_1CA430@kujuUI@@QAE@XZ @ 0x001CA430
kujuUI::type_1CA430::type_1CA430()
{
    unk_80 = 0;
}

// match: ?sub_1CA450@type_1CA430@kujuUI@@QAE?AUtype_1EFD70@2@XZ @ 0x001CA450
kujuUI::type_1EFD70 kujuUI::type_1CA430::sub_1CA450()
{
    return type_1EFD70(unk_00, this);
}

// match: ?sub_1CA470@type_1A5EA0@@QAEAAU1@PBD@Z @ 0x001CA470
// match: __ehhandler$?sub_1CA470@type_1A5EA0@@QAEAAU1@PBD@Z-0x8 @ 0x003033B0
// match: __ehhandler$?sub_1CA470@type_1A5EA0@@QAEAAU1@PBD@Z @ 0x003033B8
type_1A5EA0 &type_1A5EA0::sub_1CA470(const RwChar *arg_0)
{
    return sub_1C84F0(arg_0);
}

// match: ?sub_1CA4E0@kujuUI@@YAXPAUcFileIn@1@PAPAUtype_1CA4E0@1@@Z @ 0x001CA4E0
// match: __ehhandler$?sub_1CA4E0@kujuUI@@YAXPAUcFileIn@1@PAPAUtype_1CA4E0@1@@Z-0xB @ 0x003033D0
// match: __ehhandler$?sub_1CA4E0@kujuUI@@YAXPAUcFileIn@1@PAPAUtype_1CA4E0@1@@Z @ 0x003033DB
void kujuUI::sub_1CA4E0(cFileIn *arg_0, type_1CA4E0 **arg_4)
{
    type_1CA4E0 *var_10;

    var_10 = new type_1CA4E0;
    if (arg_0->sub_1C8BA0(&var_10->unk_00, 4) && arg_0->sub_1C8BA0(&var_10->unk_04, 4) &&
        arg_0->readVector(var_10->unk_08, 4, var_10->unk_00, 0x400) &&
        arg_0->readVector(var_10->unk_1008, 1, var_10->unk_04, 0x4000))
        *arg_4 = var_10;
    if (var_10 != *arg_4)
        delete var_10;
}

// match: ?sub_1CA620@type_1CA4E0@kujuUI@@QAEPBDPBD@Z @ 0x001CA620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
const RwChar *kujuUI::type_1CA4E0::sub_1CA620(const RwChar *arg_0)
{
    RwUInt32 var_10;
    const RwChar *var_C;
    RwInt32 bp_8;
    const RwChar *bp_4;

    bp_4 = 0;
    for (bp_8 = 0; bp_8 < unk_00 && !bp_4; bp_8++)
    {
        var_C = &unk_1008[unk_08[bp_8]];
        if (!strcmp(var_C, arg_0))
            bp_4 = var_C;
    }
    if (!bp_4)
    {
        unk_08[unk_00] = unk_04;
        unk_00++;
        var_10 = strlen(arg_0);
        strcpy(&unk_1008[unk_04], arg_0);
        unk_1008[unk_04 + var_10] = 0;
        bp_4 = &unk_1008[unk_04];
        unk_04 = var_10 + unk_04 + 1;
    }
    return bp_4;
}

// match: ?sub_1CA720@type_1CA4E0@kujuUI@@QAEPBDI@Z @ 0x001CA720
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
const RwChar *kujuUI::type_1CA4E0::sub_1CA720(RwUInt32 arg_0)
{
    RwUInt32 var_8;
    const RwChar *l4;

    if (arg_0 == -1)
        return 0;
    l4 = 0;
    if (arg_0 < 0x400)
    {
        var_8 = unk_08[arg_0];
        if (var_8 < 0x4000)
            l4 = &unk_1008[var_8];
    }
    return l4;
}

// match: ??0type_1C8DF0_104_00@kujuUI@@QAE@PAUcFileIn@1@PAUtype_1CA4E0@1@@Z @ 0x001CA780
kujuUI::type_1C8DF0_104_00::type_1C8DF0_104_00(cFileIn *arg_0, type_1CA4E0 *arg_4)
{
    unk_00 = 0;
    unk_04 = 0;
    if (arg_0->sub_1C8BA0(&unk_00, 4))
    {
        if (arg_0->sub_1C8BA0(&unk_04, 4))
        {
            switch (unk_00)
            {
            case 3:
            case 4:
                break;
            case 1:
            case 2:
                unk_04 = (RwInt32)arg_4->sub_1CA720(unk_04);
                if (!unk_04)
                    unk_00 = 0;
                break;
            default:
                unk_00 = 0;
            }
        }
        else
        {
            unk_00 = 0;
            unk_04 = 0;
        }
    }
    else
    {
        unk_00 = 0;
        unk_04 = 0;
    }
}

// match: ?sub_1CA870@type_1C8DF0_104_00@kujuUI@@QBEMXZ @ 0x001CA870
RwReal kujuUI::type_1C8DF0_104_00::sub_1CA870() const
{
    return *(const RwReal *)&unk_04;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_1C8DF0_104_00@kujuUI@@QAE@XZ (folded into 0xED650)
kujuUI::type_1C8DF0_104_00::type_1C8DF0_104_00()
{
    unk_00 = 0;
    unk_04 = 0;
}

// ??0type_1CA4E0@kujuUI@@QAE@XZ (folded into 0xED650)
kujuUI::type_1CA4E0::type_1CA4E0()
{
    unk_00 = 0;
    unk_04 = 0;
}

// ??1cScopeValidator@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::cScopeValidator::~cScopeValidator()
{
}

// ??1type_1C8DF0_104@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1C8DF0_104::~type_1C8DF0_104()
{
}

// ??1type_1C9590@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1C9590::~type_1C9590()
{
}

// ??1type_1CA4E0@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1CA4E0::~type_1CA4E0()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3BF0@type_1C8DF0@kujuUI@@QAEPAU12@I@Z (folded into 0x1E3BF0)
struct kujuUI::type_1C8DF0 * kujuUI::type_1C8DF0::sub_1E3BF0(RwUInt32 arg_0)
{
    return unk_00[arg_0];
}

// ?sub_21D030@type_1C8DF0_104@kujuUI@@QAEIXZ (folded into 0x21D030)
RwUInt32 kujuUI::type_1C8DF0_104::sub_21D030()
{
    return unk_40;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3480@cParsedFile@kujuUI@@QAEPAUtype_1C8DF0@2@XZ (folded into 0x1E3480)
struct kujuUI::type_1C8DF0 * kujuUI::cParsedFile::sub_1E3480()
{
    return unk_04;
}

// ?sub_1EE9D0@type_1C8DF0_104_00@kujuUI@@QBEHXZ (folded into 0x1EE9D0)
RwInt32 kujuUI::type_1C8DF0_104_00::sub_1EE9D0() const
{
    return unk_00;
}

// ?sub_1EE9D0@type_1CA4E0@kujuUI@@QBEHXZ (folded into 0x1EE9D0)
RwInt32 kujuUI::type_1CA4E0::sub_1EE9D0() const
{
    return unk_00;
}

// ?sub_1EE9D0@type_1EFD70@kujuUI@@QBEPAPAXXZ (folded into 0x1EE9D0)
void * * kujuUI::type_1EFD70::sub_1EE9D0() const
{
    return unk_00;
}

// ?sub_1EE9D0@type_204960@kujuUI@@QBEPBQAXXZ (folded into 0x1EE9D0)
void * const * kujuUI::type_204960::sub_1EE9D0() const
{
    return unk_00;
}

// ?sub_6FCB0@cScopeValidator@kujuUI@@QBEHXZ (folded into 0x6FCB0)
RwInt32 kujuUI::cScopeValidator::sub_6FCB0() const
{
    return unk_110;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_6FCD0@type_1C8DF0_104@kujuUI@@QAEPAUtype_1C8DF0_104_00@2@XZ (folded into 0x6FCD0)
struct kujuUI::type_1C8DF0_104_00 * kujuUI::type_1C8DF0_104::sub_6FCD0()
{
    return (kujuUI::type_1C8DF0_104_00 *)(this);
}

// The definitions' id arrays' element size (game/parsedfile.h), the body
// /OPT:ICF shares at 0x200B80.
// ?sub_200B80@kujuUI@@YAHXZ (folded into 0x200B80)
RwInt32 kujuUI::sub_200B80()
{
    return 4;
}

// The pointer array's iterators (game/parsedfile.h): built, compared and
// stepped on with the bodies /OPT:ICF shares with the arrays' iterators
// (game/kujufont.h's type_1E61A0_it and type_1E61A0_cit); defined here for
// the authentic link (PLAN M7).
// ??0type_1EFD70@kujuUI@@QAE@PAPAXPBUtype_1CA430@1@@Z (folded into 0x1EFD70)
kujuUI::type_1EFD70::type_1EFD70(void **arg_0, const type_1CA430 *arg_4)
{
    unk_00 = arg_0;
    unk_04 = arg_4;
}

// ?sub_1E8310@type_1EFD70@kujuUI@@QBE_NABU12@@Z (folded into 0x1E8310)
bool kujuUI::type_1EFD70::sub_1E8310(const type_1EFD70 &arg_0) const
{
    return !(unk_04 == arg_0.unk_04 && unk_00 == arg_0.unk_00);
}

// ?sub_204990@type_1EFD70@kujuUI@@QAEAAU12@XZ (folded into 0x204990)
kujuUI::type_1EFD70 &kujuUI::type_1EFD70::sub_204990()
{
    ++unk_00;
    return *this;
}

// ??0type_204960@kujuUI@@QAE@ABUtype_1EFD70@1@@Z (folded into 0x204960)
kujuUI::type_204960::type_204960(const type_1EFD70 &arg_0)
{
    unk_00 = arg_0.unk_00;
    unk_04 = arg_0.unk_04;
}

// ?sub_1E8310@type_204960@kujuUI@@QBE_NABU12@@Z (folded into 0x1E8310)
bool kujuUI::type_204960::sub_1E8310(const type_204960 &arg_0) const
{
    return !(unk_04 == arg_0.unk_04 && unk_00 == arg_0.unk_00);
}

// ?sub_204990@type_204960@kujuUI@@QAEAAU12@XZ (folded into 0x204990)
kujuUI::type_204960 &kujuUI::type_204960::sub_204990()
{
    ++unk_00;
    return *this;
}
