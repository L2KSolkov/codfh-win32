// SparkParticle: its MakeNew, constructor, destructor and attribute handler
// (types/SparkParticle.h). Its original file name is not in the image, so it
// is named for its start address.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/particles.h"
#include "types/SparkParticle.h"
#include "types/ParticleEditor.h"
#include "rws/csystemcommands.h"


RWS_IMPLEMENT_CLASSID(SparkParticle);
RWS_REGISTERCLASS(SparkParticle);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@JCMFKPNJ@SparkParticle?$AA@ @ 0x003D930C
// match: ??_7SparkParticle@@6BCEventHandler@RWS@@@ @ 0x003D931C
// match: ??_7SparkParticle@@6BCAttributeHandler@RWS@@@ @ 0x003D9324
// match: __ehhandler$?MakeNew@SparkParticle@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041D04C
// match: __ehhandler$?MakeNew@SparkParticle@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041D054
// match: __ehhandler$??1SparkParticle@@UAE@XZ>1>8 @ 0x0041D070
// match: __ehhandler$??1SparkParticle@@UAE@XZ>1 @ 0x0041D078
// match: .CRT$XCU+0 @ 0x0042706C
// match: ?pSparkParticleClassID@SparkParticle@@2PBDB @ 0x004296D4

// match: _$E2 @ 0x0030B620
// match: _$E3 @ 0x0030E530

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SparkParticle@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000F4570
// match: __ehhandler$?MakeNew@SparkParticle@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00301090
// match: __ehhandler$?MakeNew@SparkParticle@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030109F
RWS_DEFINE_MAKENEW(SparkParticle)

// match: ??0SparkParticle@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000F45F0
SparkParticle::SparkParticle(const RWS::CAttributePacket &attr)
{
    unk_24 = RwMatrixCreate();
}

// match: ??_GSparkParticle@@UAEPAXI@Z @ 0x000F4680

// match: ??1SparkParticle@@UAE@XZ @ 0x000F46A0
// match: __ehhandler$??1SparkParticle@@UAE@XZ-0x8 @ 0x003010B0
// match: __ehhandler$??1SparkParticle@@UAE@XZ @ 0x003010B8
SparkParticle::~SparkParticle()
{
    if (unk_24)
    {
        RwMatrixDestroy(unk_24);
        unk_24 = 0;
    }
}

// match: ?HandleAttributes@SparkParticle@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000F4740
void SparkParticle::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    sub_F2360(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SparkParticle));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            if (const RwChar *p0 = attrIt->GetAs_RwChar_ptr())
            {
                sub_F3070(p0, unk_24, 0, 1, false, false);
            }
            break;
        }
        ++attrIt;
    }
}

// match: ??_ESparkParticle@@WBI@AEPAXI@Z @ 0x000F47E0

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@SparkParticle@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void SparkParticle::HandleEvents(RWS::CMsg &pMsg)
{
}

// Reads the entity's matrix into unk_24, as ParticleEditor's does: /OPT:ICF folded
// the two into one body (0xF2360), which ParticleEditor's places.
void SparkParticle::sub_F2360(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS::CSystemCommands::pCSystemCommandsClassID);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case RWS::CSystemCommands::CMD_LoadMatrix:
        {
            const RwMatrix *pMatrix = (const RwMatrix *)attrIt->GetAs_RwChar_ptr();

            *unk_24 = *pMatrix;
            RwMatrixOptimize(unk_24, 0);
            break;
        }
        }
        ++attrIt;
    }
}
