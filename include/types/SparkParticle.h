/*
 * SparkParticle (the class name it registers with the class factory at
 * 0x30B636, with its MakeNew, sub_F4570, and its size, 0x28): a RenderWare
 * Studio behaviour that starts the particle system its command 0 names
 * ("<name>.spp", sub_F3070) at the entity's matrix, anchored at its
 * vtables off_3D9324 and off_3D931C (CEventHandler part, at +0x18), which
 * its constructor (sub_F45F0) and destructor (sub_F46A0) install.
 */
#ifndef SPARKPARTICLE_H
#define SPARKPARTICLE_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class SparkParticle : public RWS::CAttributeHandler, public RWS::CEventHandler,
                      public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(SparkParticle);
    RWS_DECLARE_CLASSID(SparkParticle);

    SparkParticle(const RWS::CAttributePacket &attr);
    ~SparkParticle();

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Reads the entity's matrix into unk_24, as ParticleEditor's; /OPT:ICF
    // folded the two (0xF2360).
    void sub_F2360(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;
    RwMatrix *unk_24;
};
typedef RwChar SparkParticle_size_check[sizeof(SparkParticle) == 0x28 ? 1 : -1];

#endif
