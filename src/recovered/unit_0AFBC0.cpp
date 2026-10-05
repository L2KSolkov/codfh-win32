// SectionInfo: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/SectionInfo.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042918C
RwReal flt_42918C = 8.0f;
// 0x00429190
RwReal flt_429190 = 8.0f;
// 0x00429194
RwReal flt_429194 = 4.0f;
// 0x004B67F0
RwUInt32 dword_4B67F0[4];
// 0x004B6800
RwUInt32 dword_4B6800[4];
// 0x004B6810
RwUInt32 dword_4B6810[4];
// 0x004B6820
RwInt32 dword_4B6820;
// 0x004B6824
RwInt32 dword_4B6824;
// 0x004B6828
RwInt32 dword_4B6828;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(SectionInfo);
RWS_REGISTERCLASS(SectionInfo);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0M@NJFCDFPI@SectionInfo?$AA@ @ 0x003D63B0
// match: ??_7SectionInfo@@6BCEventHandler@RWS@@@ @ 0x003D63BC
// match: ??_7SectionInfo@@6BCAttributeHandler@RWS@@@ @ 0x003D63C4
// match: __ehhandler$?MakeNew@SectionInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BF90
// match: __ehhandler$?MakeNew@SectionInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BF98
// match: __ehhandler$??1SectionInfo@@UAE@XZ>1>8 @ 0x0041BFB4
// match: __ehhandler$??1SectionInfo@@UAE@XZ>1 @ 0x0041BFBC
// match: .CRT$XCU+0 @ 0x00426F48
// match: ?flt_42918C@@3MA @ 0x0042918C
// match: ?flt_429190@@3MA @ 0x00429190
// match: ?flt_429194@@3MA @ 0x00429194
// match: ?pSectionInfoClassID@SectionInfo@@2PBDB @ 0x00429198

// match: _$E2 @ 0x0030A990
// match: _$E3 @ 0x0030E100

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SectionInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000AFBC0
// match: __ehhandler$?MakeNew@SectionInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003001B0
// match: __ehhandler$?MakeNew@SectionInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003001BF
RWS_DEFINE_MAKENEW(SectionInfo)

// match: ??0SectionInfo@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000AFC40
SectionInfo::SectionInfo(const RWS::CAttributePacket &attr)
{
}

// match: ??_GSectionInfo@@UAEPAXI@Z @ 0x000AFCD0

// match: ??1SectionInfo@@UAE@XZ @ 0x000AFCF0
// match: __ehhandler$??1SectionInfo@@UAE@XZ-0x8 @ 0x003001D0
// match: __ehhandler$??1SectionInfo@@UAE@XZ @ 0x003001D8
// (Defined in the class, in SectionInfo.h.)

// match: ?sub_AFD70@SectionInfo@@SAXXZ @ 0x000AFD70
void SectionInfo::sub_AFD70()
{
    RwInt32 var_4;

    flt_42918C = 8.0f;
    dword_4B6820 = 0;
    flt_429190 = 8.0f;
    dword_4B6824 = 0;
    flt_429194 = 4.0f;
    dword_4B6828 = 0;
    for (var_4 = 0; var_4 < 4; var_4++)
    {
        dword_4B6800[var_4] = 0x180000; // not an address: 1.5 MB
        dword_4B67F0[var_4] = 0x200000; // not an address: 2 MB
        dword_4B6810[var_4] = 0x80000;  // not an address: 512 KB
    }
}

// Commands 0 to 17: the three sections' settings in turn.
// match: ?HandleAttributes@SectionInfo@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000AFE00
void SectionInfo::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SectionInfo));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            flt_42918C = attrIt->GetAs_RwReal();
            break;
        case 1:
            dword_4B6820 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            dword_4B6800[0] = attrIt->GetAs_RwInt32();
            break;
        case 3:
            dword_4B6800[1] = attrIt->GetAs_RwInt32();
            break;
        case 4:
            dword_4B6800[2] = attrIt->GetAs_RwInt32();
            break;
        case 5:
            dword_4B6800[3] = attrIt->GetAs_RwInt32();
            break;
        case 6:
            flt_429190 = attrIt->GetAs_RwReal();
            if (flt_429190 == 10.0f)
            {
                flt_429190 = 8.0f;
            }
            break;
        case 7:
            dword_4B6824 = attrIt->GetAs_RwInt32();
            break;
        case 8:
            dword_4B67F0[0] = attrIt->GetAs_RwInt32();
            break;
        case 9:
            dword_4B67F0[1] = attrIt->GetAs_RwInt32();
            break;
        case 10:
            dword_4B67F0[2] = attrIt->GetAs_RwInt32();
            break;
        case 11:
            dword_4B67F0[3] = attrIt->GetAs_RwInt32();
            break;
        case 12:
            flt_429194 = attrIt->GetAs_RwReal();
            break;
        case 13:
            dword_4B6828 = attrIt->GetAs_RwInt32();
            break;
        case 14:
            dword_4B6810[0] = attrIt->GetAs_RwInt32();
            break;
        case 15:
            dword_4B6810[1] = attrIt->GetAs_RwInt32();
            break;
        case 16:
            dword_4B6810[2] = attrIt->GetAs_RwInt32();
            break;
        case 17:
            dword_4B6810[3] = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_B0140@SectionInfo@@SAHXZ @ 0x000B0140
RwInt32 SectionInfo::sub_B0140()
{
    return dword_4B6824;
}

// match: ?sub_B0150@SectionInfo@@SAPAIXZ @ 0x000B0150
RwUInt32 *SectionInfo::sub_B0150()
{
    return dword_4B67F0;
}

// match: ?sub_B0160@SectionInfo@@SAMXZ @ 0x000B0160
RwReal SectionInfo::sub_B0160()
{
    return flt_429190;
}

// match: ??_ESectionInfo@@WBI@AEPAXI@Z @ 0x000B0170

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@SectionInfo@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void SectionInfo::HandleEvents(RWS::CMsg &pMsg)
{
}
