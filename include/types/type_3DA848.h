/*
 * type_3DA848: the resource handler for the Alfa script system's files
 * ("spID_AlfaDataFile", "spID_AlfaScriptFile"; off_429C04, off_429C08),
 * named after its vtable. One instance, dword_4CF7D4, built by a dynamic
 * initializer (0x30B7F0, through the constructor sub_129410).
 */
#ifndef TYPE_3DA848_H
#define TYPE_3DA848_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/cresourcehandler.h"

class type_3DA848 : public RWS::CResourceHandler
{
public:
    type_3DA848();

    virtual RwBool IsHandled(const RwChar *psType);
    virtual void *Load(const RwChar *psName, const RwChar *psType, const RwChar *psResourcePath,
                       RwStream *pStream, RwUInt32 uiStreamSize, RwUInt32 &uiResourceSize);
    virtual RwBool UnLoad(const RwChar *pStrType, void *pResource);

    // Reads a data file (sub_129350) or a script file (sub_1293A0) of
    // arg_4 bytes from the stream arg_0.
    void *sub_129350(RwStream *arg_0, RwUInt32 arg_4);
    void *sub_1293A0(RwStream *arg_0, RwUInt32 arg_4);
};

// The two resource types it handles.
extern const RwChar *off_429C04;
extern const RwChar *off_429C08;
extern type_3DA848 dword_4CF7D4;

#endif
