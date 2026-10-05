/*
 * ParticleEditor (the class name it registers with the class factory at
 * 0x30B5A9, with its MakeNew, sub_F1320, and its size, 0x258): a RenderWare
 * Studio behaviour for editing a particle system live, anchored at its
 * vtables off_3D91E0 and off_3D91D8 (CEventHandler part, at +0x18), which
 * its constructor (sub_F13A0) and destructor (sub_F15D0) install.
 *
 * Its attributes fill a particle definition (unk_28, type_F3130) and name
 * three messages: on the first (unk_240) it copies the definition to the
 * live one (unk_134) and starts it at its matrix (unk_24, the entity's
 * CSystemCommands matrix); on the second (unk_250) it sends the first; on
 * the third (unk_248) it clears every particle system (sub_F2A00).
 */
#ifndef PARTICLEEDITOR_H
#define PARTICLEEDITOR_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/batextur.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/type_F3130.h"

class ParticleEditor : public RWS::CAttributeHandler, public RWS::CEventHandler,
                       public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(ParticleEditor);
    RWS_DECLARE_CLASSID(ParticleEditor);

    ParticleEditor(const RWS::CAttributePacket &attr);
    ~ParticleEditor();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Reads the entity's matrix (CSystemCommands::CMD_LoadMatrix) into
    // unk_24.
    void sub_F2360(const RWS::CAttributePacket &attr);
    // Sets the definition arg_0's defaults.
    void sub_F23F0(type_F3130 *arg_0);

    RwInt32 unk_20;
    RwMatrix *unk_24;
    type_F3130 unk_28;          // the edited definition
    type_F3130 unk_134;         // the live one
    RWS::CEventId unk_240;      // command 0: start
    RWS::CEventId unk_248;      // command 2: clear all
    RWS::CEventId unk_250;      // command 1: restart
};
typedef RwChar ParticleEditor_size_check[sizeof(ParticleEditor) == 0x258 ? 1 : -1];

#endif
