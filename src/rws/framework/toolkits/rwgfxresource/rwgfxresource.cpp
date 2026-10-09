// RenderWare Studio's RenderWare resource handler (the game framework's
// framework/toolkits/rwgfxresource/rwgfxresource.cpp) as the game has it:
// it loads texture dictionaries only (a PI texture dictionary reads as
// nothing: PiTexDictionaryStreamRead returns 0 off the PC drivers and is
// folded, config/aliases.txt), and it unloads and recognises every
// "rwID_..." type, the Xbox's MTEffectDict too. The constructor is the
// compiler's, out of line for the global instance; its destructor and
// scalar deleting destructor are shared with the other resource handlers'
// (/OPT:ICF).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/badevice.h"
#include "rw/baimage.h"
#include "rw/batextur.h"
#include "rw/baengine.h"
#include "rw/rpworld.h"
#include "rw/rpatomic.h"
#include "rw/rtanim.h"
#include "rw/rt2d.h"
#include "rw/rpmteffect.h"
#include "rws/rwgfxresource.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0N@MIIBDKGH@MTEFFECTDICT?$AA@ @ 0x003DAB94
// match: ??_C@_06HJLBABJI@2DFONT?$AA@ @ 0x003DABA4
// match: ??_C@_09NPHJCBFD@2DMAESTRO?$AA@ @ 0x003DABAC
// match: ??_C@_0P@IIAEGPIA@HANIMANIMATION?$AA@ @ 0x003DABB8
// match: ??_C@_06DCPBFM@ATOMIC?$AA@ @ 0x003DABC8
// match: ??_C@_05GENICPIB@CLUMP?$AA@ @ 0x003DABD0
// match: ??_C@_0BA@BOBMJDEJ@PITEXDICTIONARY?$AA@ @ 0x003DABD8
// match: ??_C@_0O@FHMMAFKN@TEXDICTIONARY?$AA@ @ 0x003DABE8
// match: ??_C@_05JIEJAAH@WORLD?$AA@ @ 0x003DABF8
// match: ??_7CRenderwareResource@RWS@@6B@ @ 0x003DAC00
// match: .CRT$XCU+0 @ 0x0042710C

// match: _$E1 @ 0x0030BB40
// match: _$E2 @ 0x0030E800
// match: ?TexDictionaryStreamRead@CRenderwareResource@RWS@@AAEPAURwTexDictionary@@PAURwStream@@@Z @ 0x00132730
// sp-match: ?TexDictionaryStreamRead@CRenderwareResource@RWS@@AAEPAURwTexDictionary@@PAURwStream@@@Z @ 0x000E3140

RwTexDictionary* RWS::CRenderwareResource::TexDictionaryStreamRead (RwStream *stream)
      {
         RwTexDictionary *tex_dictionary;

         tex_dictionary = RwTexDictionaryStreamRead (stream, 0);

         RwTexDictionarySetCurrent (tex_dictionary);

         return( tex_dictionary );
      }

// The PC drivers' reader; nothing here (folded, config/aliases.txt).
RwTexDictionary* RWS::CRenderwareResource::PiTexDictionaryStreamRead (RwStream *stream)
      {
         return(0);
      }

// match: ?Load@CRenderwareResource@RWS@@UAEPAXPBD00PAURwStream@@IAAI@Z @ 0x00132760
// sp-match: ?Load@CRenderwareResource@RWS@@UAEPAXPBD00PAURwStream@@IAAI@Z @ 0x000E3160
void *RWS::CRenderwareResource::Load( const RwChar *psName,
                                       const RwChar *psType,
                                       const RwChar *psResourcePath,
                                       RwStream* pStream,
                                       RwUInt32 uiStreamSize,
                                       RwUInt32 &uiResourceSize)
      {
         void *ret = 0;

         if (uiStreamSize == 0)
         {
            return(ret);
         }

         if (psResourcePath) RwImageSetPath(psResourcePath);

         RwChunkHeaderInfo _RwChunkHeaderInfo;

         RwStreamReadChunkHeaderInfo(pStream, &_RwChunkHeaderInfo);

         RwBool bHandled = FALSE;

         switch (_RwChunkHeaderInfo.type)
         {
            case rwID_TEXDICTIONARY:   bHandled = TRUE; ret = TexDictionaryStreamRead(pStream);    break;
            case rwID_PITEXDICTIONARY: bHandled = TRUE; ret = PiTexDictionaryStreamRead(pStream);  break;
         }

         return( ret );
      }

// match: ?UnLoad@CRenderwareResource@RWS@@UAEHPBDPAX@Z @ 0x001327F0
// sp-match: ?UnLoad@CRenderwareResource@RWS@@UAEHPBDPAX@Z @ 0x000E31E0
RwBool RWS::CRenderwareResource::UnLoad (const RwChar *pStrType, void *pResource)
      {
         RwBool ret = FALSE;

         const RwChar *_pStrType = &pStrType[5];

         if (rwstrcmp(_pStrType, "WORLD") == 0)
         {
            ret = RpWorldDestroy(reinterpret_cast<RpWorld*>(pResource));
         }
         else if ((rwstrcmp(_pStrType, "TEXDICTIONARY") == 0)
               || (rwstrcmp(_pStrType, "PITEXDICTIONARY") == 0))
         {
            ret = RwTexDictionaryDestroy(reinterpret_cast<RwTexDictionary*>(pResource));
         }
         else if (rwstrcmp(_pStrType, "CLUMP") == 0)
         {
            ret = RpClumpDestroy(reinterpret_cast<RpClump*>(pResource));
         }
         else if (rwstrcmp(_pStrType, "ATOMIC") == 0)
         {
            ret = RpAtomicDestroy(reinterpret_cast<RpAtomic*>(pResource));
         }
         else if (rwstrcmp(_pStrType, "HANIMANIMATION") == 0)
         {
            ret = RtAnimAnimationDestroy (reinterpret_cast<RtAnimAnimation*>(pResource));
         }
         else if (rwstrcmp(_pStrType, "2DMAESTRO") == 0)
         {
            ret = ( Rt2dMaestroDestroy (reinterpret_cast<Rt2dMaestro*>(pResource)) );
         }
         else if (rwstrcmp(_pStrType, "2DFONT") == 0)
         {
            ret = TRUE;
         }
         else if (rwstrcmp(_pStrType, "MTEFFECTDICT") == 0)
         {
            RpMTEffectDictDestroy(static_cast<RpMTEffectDict*>(pResource));

            ret = TRUE;
         }
         else
         {
         }

         return(ret);
      }

// match: ?IsHandled@CRenderwareResource@RWS@@UAEHPBD@Z @ 0x00132970
// sp-match: ?IsHandled@CRenderwareResource@RWS@@UAEHPBD@Z @ 0x000E3340
RwBool RWS::CRenderwareResource::IsHandled(const RwChar *psType)
      {
         if (psType[0] == 'r'
         && psType[1] == 'w'
         && psType[2] == 'I'
         && psType[3] == 'D')
         {
            const RwChar *_pStrType = &psType[5];

            if (rwstrcmp(_pStrType, "WORLD") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "TEXDICTIONARY") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "CLUMP") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "ATOMIC") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "HANIMANIMATION") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "2DMAESTRO") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "2DFONT") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "PITEXDICTIONARY") == 0) {return(TRUE);}
            else if (rwstrcmp(_pStrType, "MTEFFECTDICT") == 0) {return(TRUE);}
         }

         return(FALSE);
      }

namespace RWS
{
   namespace
   {
      CRenderwareResource gCRenderwareResource;
   }
}

// The compiler's constructor (the global instance's), and the scalar
// deleting destructor the resource handlers share.
// match: ??0CRenderwareResource@RWS@@QAE@XZ @ 0x00132AE0
// match: ??_GCRenderwareResource@RWS@@UAEPAXI@Z @ 0x00132B00
// sp-match: ??0CRenderwareResource@RWS@@QAE@XZ @ 0x000E3440
// sp-match: ??_GCRenderwareResource@RWS@@UAEPAXI@Z @ 0x000E1B90
