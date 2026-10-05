// CDebugScript, a RenderWare Studio behaviour setting the message system's
// debug settings: its registration with the class factory (whose dynamic
// initializer the image keeps at 0x309910), MakeNew and the linear
// allocation policy's operator new, CLinearMemoryManager::Instance (inline,
// with its vector's reserve), its constructor, destructor and
// HandleAttributes, then the Dinkumware STL functions they instantiate
// (std::vector and the length_error it throws). It follows the action
// queue's unit. Its original file name is not in the image, so it is named
// for its start address.

#include <ctype.h>
#include <string.h>

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CDebugScript.h"
#include "rws/debugswitches.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00449316
RwUInt8 byte_449316;
// 0x00449317
RwUInt8 byte_449317;
// End of its data definitions.



// A compiled-out check: the command-11 store in sub_43200 requires two
// register steps after reading its value (docs/toolchain.md). The original
// condition is unknown; this condition is chosen for its loads.
#define DEBUGSCRIPT_CHECK(e) { if (!(e)) { } }

RWS_IMPLEMENT_CLASSID(CDebugScript);
RWS_REGISTERCLASS(CDebugScript);
// 0x003CE954 (defined after the class id: VC7.1 emits data definitions in reverse order,
// and the image has this constant before the class name)
extern const RwReal flt_3CE954 = 16.666666f;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE954@@3MB @ 0x003CE954
// match: ??_C@_0N@BBOBFIMC@CDebugScript?$AA@ @ 0x003CE958
// match: ??_7CDebugScript@@6BCEventHandler@RWS@@@ @ 0x003CE968
// match: ??_7CDebugScript@@6BCAttributeHandler@RWS@@@ @ 0x003CE970
// match: ??_7CEventHandler@RWS@@6B@ @ 0x003CE978
// match: ??_7CAttributeHandler@RWS@@6B@ @ 0x003CE980
// match: ??_7length_error@std@@6B@ @ 0x003CE988
// match: ??_C@_0BD@OLBABOEK@vector?$DMT?$DO?5too?5long?$AA@ @ 0x003CE990
// match: ?npos@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@2IB @ 0x003CE9A4
// match: ??_7logic_error@std@@6B@ @ 0x003CE9A8
// match: __ehhandler$?MakeNew@CDebugScript@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041B0DC
// match: __ehhandler$?MakeNew@CDebugScript@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041B0E4
// match: __ehhandler$?Instance@CLinearMemoryManager@RWS@@SAPAV12@XZ>1>8 @ 0x0041B100
// match: __ehhandler$?Instance@CLinearMemoryManager@RWS@@SAPAV12@XZ>1 @ 0x0041B108
// match: __ehhandler$??1CDebugScript@@UAE@XZ>1>8 @ 0x0041B124
// match: __ehhandler$??1CDebugScript@@UAE@XZ>1 @ 0x0041B12C
// match: __ehhandler$?reserve@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXI@Z>1>8 @ 0x0041B148
// match: __ehhandler$?reserve@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXI@Z>1>16>16 @ 0x0041B158
// match: __ehhandler$?reserve@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXI@Z>1>16 @ 0x0041B168
// match: __ehhandler$?reserve@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXI@Z>1 @ 0x0041B17C
// match: __CT??_R0?AVexception@@@8??0exception@@QAE@ABV0@@Z12 @ 0x0041B198
// match: __CT??_R0?AVlogic_error@std@@@8??0logic_error@std@@QAE@ABV01@@Z40 @ 0x0041B1B4
// match: __CT??_R0?AVlength_error@std@@@8??0length_error@std@@QAE@ABV01@@Z40 @ 0x0041B1D0
// match: __CTA3?AVlength_error@std@@ @ 0x0041B1EC
// match: __TI3?AVlength_error@std@@ @ 0x0041B1FC
// match: __ehhandler$?_Xlen@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IBEXXZ>1>8 @ 0x0041B20C
// match: __ehhandler$?_Xlen@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IBEXXZ>1 @ 0x0041B214
// match: __ehhandler$??0logic_error@std@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@@Z>1>8 @ 0x0041B230
// match: __ehhandler$??0logic_error@std@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@@Z>1 @ 0x0041B238
// match: __ehhandler$??1logic_error@std@@UAE@XZ>1>8 @ 0x0041B254
// match: __ehhandler$??1logic_error@std@@UAE@XZ>1 @ 0x0041B25C
// match: __ehhandler$??1length_error@std@@UAE@XZ>1>8 @ 0x0041B278
// match: __ehhandler$??1length_error@std@@UAE@XZ>1 @ 0x0041B280
// match: __ehhandler$??0logic_error@std@@QAE@ABV01@@Z>1>8 @ 0x0041B29C
// match: __ehhandler$??0logic_error@std@@QAE@ABV01@@Z>1 @ 0x0041B2A4
// match: __ehhandler$?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z>1>8 @ 0x0041B2C0
// match: __ehhandler$?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z>1>16>16 @ 0x0041B2E0
// match: __ehhandler$?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z>1>16>36 @ 0x0041B2F0
// match: __ehhandler$?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z>1>16 @ 0x0041B300
// match: __ehhandler$?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z>1 @ 0x0041B328
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@3@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@0@0PAPAU123@AAV?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1>8 @ 0x0041B344
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@3@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@0@0PAPAU123@AAV?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1>16>16 @ 0x0041B354
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@3@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@0@0PAPAU123@AAV?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1>16 @ 0x0041B364
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@3@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@0@0PAPAU123@AAV?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z>1 @ 0x0041B378
// match: .CRT$XCU+0 @ 0x00426D9C
// match: ?pCDebugScriptClassID@CDebugScript@@2PBDB @ 0x00427684
// match: ??_R0?AVexception@@@8 @ 0x00427688
// match: ??_R0?AVlogic_error@std@@@8 @ 0x004276A0
// match: ??_R0?AVlength_error@std@@@8 @ 0x004276C0

// match: _$E2 @ 0x00309910
// match: _$E3 @ 0x0030DD10

// (The class factory's registration and its exit thunk.)

// MakeNew (RWS_DEFINE_MAKENEW), then the inlines it calls, which the image
// keeps here: the policy's operator new and Instance.
// match: ?MakeNew@CDebugScript@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00042F40
// match: __ehhandler$?MakeNew@CDebugScript@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FF710
// match: __ehhandler$?MakeNew@CDebugScript@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FF71F
// match: ??2LinearAllocationPolicy@RWS@@SAPAXII@Z @ 0x00042FC0
// match: ?Instance@CLinearMemoryManager@RWS@@SAPAV12@XZ @ 0x00043010
// match: __ehhandler$?Instance@CLinearMemoryManager@RWS@@SAPAV12@XZ-0xE @ 0x002FF730
// match: __ehhandler$?Instance@CLinearMemoryManager@RWS@@SAPAV12@XZ @ 0x002FF73E
RWS_DEFINE_MAKENEW(CDebugScript)

// match: ??0CDebugScript@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00043070
CDebugScript::CDebugScript(const RWS::CAttributePacket &attr) : unk_20(0)
{
}

// match: ??_GCAttributeHandler@RWS@@UAEPAXI@Z @ 0x00043100
// match: ??_GCEventHandler@RWS@@UAEPAXI@Z @ 0x00043130
// match: ??_GCDebugScript@@UAEPAXI@Z @ 0x00043160

// match: ??1CDebugScript@@UAE@XZ @ 0x00043180
// match: __ehhandler$??1CDebugScript@@UAE@XZ-0x8 @ 0x002FF750
// match: __ehhandler$??1CDebugScript@@UAE@XZ @ 0x002FF758
CDebugScript::~CDebugScript()
{
}

// match: ?HandleAttributes@CDebugScript@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00043200
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CDebugScript::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 var_C;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator bp_8(attr, RWS_CLASSID_OF(CDebugScript));
    while (!bp_8.IsFinished())
    {
        switch (bp_8->GetCommandId())
        {
        case 0:
            dword_44928C = bp_8->GetAs_RwInt32();
            break;
        case 1:
            dword_4492A8 = bp_8->GetAs_RwInt32();
            break;
        case 2:
            dword_449294 = bp_8->GetAs_RwInt32();
            break;
        case 7:
            strcpy(String, bp_8->GetAs_RwChar_ptr());
            if (isdigit(String[0]))
                byte_44930C = 1;
            else
                byte_44930C = 0;
            break;
        case 13:
            RWS::DebugSwitches::SetSwitch(0x19, (bool)bp_8->GetAs_RwInt32());
            break;
        case 3:
            dword_4492B0 = bp_8->GetAs_RwInt32();
            break;
        case 6:
            dword_449310 = bp_8->GetAs_RwInt32();
            break;
        case 4:
            byte_449316 = (bool)bp_8->GetAs_RwInt32();
            break;
        case 5:
            byte_449317 = (bool)bp_8->GetAs_RwInt32();
            break;
        case 8:
            sub_19A750(bp_8->GetAs_RwInt32());
            break;
        case 11:
            bp_8->GetCommandData(var_C);
            DEBUGSCRIPT_CHECK(unk_20 & 1);
            unk_20 = var_C;
            break;
        }
        ++bp_8;
    }
}

// The Dinkumware STL functions the unit instantiates (the XDK's headers,
// compiled here at /Od): std::vector's reserve (CLinearMemoryManager's
// constructor) and _Xlen, which throws std::length_error, and the
// std::string, logic_error and length_error functions that brings in. The
// unwind funclets and handlers of the logic_error constructors and of the
// two exception destructors are identical, and /OPT:ICF kept one pair each.
// match: ?reserve@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXI@Z @ 0x00043450
// match: __ehhandler$?reserve@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXI@Z @ 0x002FF770
// match: ?_Xlen@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IBEXXZ @ 0x00043680
// match: __ehhandler$?_Xlen@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IBEXXZ-0x8 @ 0x002FF780
// match: __ehhandler$?_Xlen@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IBEXXZ @ 0x002FF788
// match: ??0logic_error@std@@QAE@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@@Z @ 0x00043710
// match: ?what@logic_error@std@@UBEPBDXZ @ 0x00043790
// match: ??_Glogic_error@std@@UAEPAXI@Z @ 0x000437D0
// match: ??1logic_error@std@@UAE@XZ @ 0x00043800
// match: ??1length_error@std@@UAE@XZ @ 0x00043860
// match: __ehhandler$??1length_error@std@@UAE@XZ-0x8 @ 0x002FF7A0
// match: __ehhandler$??1length_error@std@@UAE@XZ @ 0x002FF7A8
// match: ??_Glength_error@std@@UAEPAXI@Z @ 0x000438D0
// match: ??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@XZ @ 0x00043900
// match: ?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@ABV12@II@Z @ 0x00043920
// match: ?_Tidy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEX_NI@Z @ 0x00043A40
// match: ??0length_error@std@@QAE@ABV01@@Z @ 0x00043AE0
// match: ??0logic_error@std@@QAE@ABV01@@Z @ 0x00043B10
// match: __ehhandler$??0logic_error@std@@QAE@ABV01@@Z-0x8 @ 0x002FF7C0
// match: __ehhandler$??0logic_error@std@@QAE@ABV01@@Z @ 0x002FF7C8
// match: ?erase@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@II@Z @ 0x00043B90
// match: ?_Grow@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAE_NI_N@Z @ 0x00043C80
// match: ?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z @ 0x00043D80
// match: __ehhandler$?_Copy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAEXII@Z @ 0x002FF7E0
// match: ?assign@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@PBDI@Z @ 0x00043F80
// match: ?_Inside@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@IAE_NPBD@Z @ 0x00044060
// match: ??$_Uninit_copy@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@3@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@0@0PAPAU123@AAV?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z @ 0x000440D0
// match: __ehhandler$??$_Uninit_copy@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@3@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@Viterator@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@0@0PAPAU123@AAV?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@0@U_Nonscalar_ptr_iterator_tag@0@@Z @ 0x002FF7F0

// The this-adjusting thunk the CEventHandler part's vtable (off_3CE968) holds
// for the scalar deleting destructor.
// match: ??_ECDebugScript@@WBI@AEPAXI@Z @ 0x000441A0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3LinearAllocationPolicy@RWS@@SAXPAXI@Z (folded into 0x19A750)
void RWS::LinearAllocationPolicy::operator delete(void * arg_0, RwUInt32 arg_4)
{
}
