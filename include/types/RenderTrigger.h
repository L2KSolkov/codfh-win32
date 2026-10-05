/*
 * RenderTrigger (the class name it registers with the class factory at
 * 0x30A946, with its MakeNew, sub_AF150, and its size, 0x18): a RenderWare
 * Studio attribute handler that sets the renderer's settings (globals from
 * 0x4CF450 to 0x4CF793), anchored at its vtable off_3D635C, which its
 * constructor (sub_AF1D0) and destructor (sub_AF250) install.
 */
#ifndef RENDERTRIGGER_H
#define RENDERTRIGGER_H

#include "rw/batypes.h"
#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/linearallocationpolicy.h"

class RenderTrigger : public RWS::CAttributeHandler, public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(RenderTrigger);
    RWS_DECLARE_CLASSID(RenderTrigger);

    RenderTrigger(const RWS::CAttributePacket &attr);
    ~RenderTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Its kind (2): a new virtual (slot 8; the image's vtable ends with it), folded
    // (/OPT:ICF) into type_3DFE94's (sub_195D00).
    virtual RwInt32 vf_008();

    // Maps a setting's choice (1 to 10) to its value (2 to 11; 1 otherwise).
    RwInt32 sub_AF270(RwInt32 arg_0);
};
typedef RwChar RenderTrigger_size_check[sizeof(RenderTrigger) == 0x18 ? 1 : -1];

// The render settings it sets; only their widths are known, but for the far
// clip distance (flt_4CF458, which it copies to farClip) and two colours.
extern RwInt32 dword_4CF450;
extern RwInt32 dword_4CF454;
extern RwReal flt_4CF458;
extern RwInt32 dword_4CF45C;
extern RwInt32 dword_4CF460;
extern RwInt32 dword_4CF468;
extern RwInt32 dword_4CF46C;
extern RwInt32 dword_4CF474;
extern RwInt32 dword_4CF4DC;
extern RwInt32 dword_4CF4F0;
extern RwInt32 dword_4CF4F4;
extern RwInt32 dword_4CF4FC;
extern RwInt32 dword_4CF500;
extern RwInt32 dword_4CF504;
extern RwInt32 dword_4CF50C;
extern RwInt32 dword_4CF518;
extern RwInt32 dword_4CF540;
extern RwInt32 dword_4CF5B8;
extern RwUInt32 dword_4CF5BC;   // flags: commands 20 to 22 set bits 0 to 2
extern RwInt32 dword_4CF754;
extern RwInt32 dword_4CF760;
extern RwInt32 dword_4CF764;
extern RwRGBA stru_4CF768;
extern RwReal farClip;
extern RwInt32 dword_4CF778;
extern RwInt32 dword_4CF780;
extern RwInt32 dword_4CF784;
extern RwRGBA stru_4CF790;

// Apply the settings dword_4CF50C and dword_4CF754 set.
void sub_126770();
void sub_1268D0();

#endif
