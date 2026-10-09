// RenderWare Studio's stream handler (the game framework's
// framework/core/streamhandler/streamhandler.cpp): reads a stream's chunks
// and hands each to the handler registered for its id. The version check
// only reads the chunk (its assertion is compiled out), and the debug build's
// id names are not in the image.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/osintf.h"
#include "rws/streamhandler.h"
#include "rws/memoryhandler.h"
#include "rws/strfunc.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?Instance@CStreamHandler@RWS@@SAPAV12@XZ>1>8 @ 0x0041D96C
// match: __ehhandler$?Instance@CStreamHandler@RWS@@SAPAV12@XZ>1 @ 0x0041D974
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z>1>8 @ 0x0041D990
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z>1 @ 0x0041D998
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x0041D9B4
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x0041D9BC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z>1>8 @ 0x0041D9D8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z>1>16>16 @ 0x0041D9E8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z>1>16 @ 0x0041D9F8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z>1 @ 0x0041DA0C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x0041DA28
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x0041DA38
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x0041DA48
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ>1 @ 0x0041DA5C

// STL template members single player calls out of line (MP expands them):
// sp-match: ?_Max@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@KAPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@@Z @ 0x000E1C40
// sp-match: ?_Min@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@KAPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@@Z @ 0x000E1C60
// sp-match: ?equal_range@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@V123@@2@ABI@Z @ 0x000E1E90
// sp-match: ??$_Distance@Viterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@I@std@@YAXViterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@0@0AAI@Z @ 0x000E1F00

// match: _$E2 @ 0x0030E6E0
// match: ?Instance@CStreamHandler@RWS@@SAPAV12@XZ @ 0x00130620
// match: __ehhandler$?Instance@CStreamHandler@RWS@@SAPAV12@XZ-0xE @ 0x00301790
// match: __ehhandler$?Instance@CStreamHandler@RWS@@SAPAV12@XZ @ 0x0030179E
// sp-match: ?Instance@CStreamHandler@RWS@@SAPAV12@XZ @ 0x000E25C0

RWS::CStreamHandler *RWS::CStreamHandler::Instance(void)
   {
      static CStreamHandler _CStreamHandler;

      return (&_CStreamHandler);
   }

// match: ?RegisterChunkHandler@CStreamHandler@RWS@@SAXIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@Z @ 0x001306B0
// sp-match: ?RegisterChunkHandler@CStreamHandler@RWS@@SAXIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@Z @ 0x000E2650
void RWS::CStreamHandler::RegisterChunkHandler(RwUInt32 ChunkType, StreamChunkHandler ChunkHandler)
   {
      CStreamHandler *pCStreamHandler = Instance();

      const StreamChunkHandlerMap::iterator it = pCStreamHandler->m_StreamChunkHandlerMap.find(ChunkType);

      if (it != pCStreamHandler->m_StreamChunkHandlerMap.end())
      {
      }
      else
      {
         pCStreamHandler->m_StreamChunkHandlerMap.insert(StreamChunkHandlerMap::value_type(ChunkType, ChunkHandler));
      }
   }

// match: ?UnRegisterChunkHandler@CStreamHandler@RWS@@SAXI@Z @ 0x00130720
// sp-match: ?UnRegisterChunkHandler@CStreamHandler@RWS@@SAXI@Z @ 0x000E26A0
void RWS::CStreamHandler::UnRegisterChunkHandler(RwUInt32 ChunkType)
   {
      CStreamHandler *pCStreamHandler = Instance();

      pCStreamHandler->m_StreamChunkHandlerMap.erase(ChunkType);
   }

// match: ?RwStreamEOF@CStreamHandler@RWS@@KA_NPAURwStream@@@Z @ 0x00130750
// sp-match: ?RwStreamEOF@CStreamHandler@RWS@@KA_NPAURwStream@@@Z @ 0x000E1BB0
bool RWS::CStreamHandler::RwStreamEOF(RwStream *_pStream)
   {
      switch (_pStream->type)
      {
      case rwSTREAMFILENAME:
      case rwSTREAMFILE:
         {
            void *fp = _pStream->Type.file.fpFile;

            if (RwOsGetFileInterface()->rwfeof(fp)) return (true);
         }
         break;

      case rwSTREAMMEMORY:
         {
            RwStreamMemory     *smpMem = &_pStream->Type.memory;

            if (smpMem->nSize == smpMem->position)
            {
               return (true);
            }
         }
         break;

      case rwSTREAMCUSTOM:
         {
            if (_pStream->Type.custom.sfnread(_pStream->Type.custom.data, 0, 0) == 0)
            {
               return (true);
            }
         }
         break;

      default:
         {
         }
      }

      return (false);
   }

// match: ?ProcessStream@CStreamHandler@RWS@@SAXPAURwStream@@@Z @ 0x001307F0
// sp-match: ?ProcessStream@CStreamHandler@RWS@@SAXPAURwStream@@@Z @ 0x000E26C0
void RWS::CStreamHandler::ProcessStream(RwStream* pStream)
   {
      while (!RwStreamEOF(pStream))
      {
         RwStreamReadChunkHeaderInfo(pStream, &Instance()->m_RwChunkHeaderInfo);

         const StreamChunkHandlerMap::iterator it =
            Instance()->m_StreamChunkHandlerMap.find(Instance()->m_RwChunkHeaderInfo.type);

         if (it != Instance()->m_StreamChunkHandlerMap.end())
         {
            StreamChunkHandler pFunc = it->second;

            pFunc(Instance()->m_RwChunkHeaderInfo, pStream);
         }
         else
         {
            RwStreamSkip(pStream, Instance()->m_RwChunkHeaderInfo.length);
         }
      }
   }

// match: ?VersionNumber@?A0x8c4e8a5a@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x001308B0
// sp-match: ?VersionNumber@?A0x8c4e8a5a@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E1C10
namespace RWS
{
   namespace
   {
      void VersionNumber (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         RwChar *buffer = static_cast<RwChar*>(RWS_OP_NEW(rChunkHeader.length) );

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         operator delete (buffer);
      }
   }
}

// match: ?RegisterStreamChunkHandlers@CStreamHandler@RWS@@SAXXZ @ 0x001308F0
// sp-match: ?RegisterStreamChunkHandlers@CStreamHandler@RWS@@SAXXZ @ 0x000E2750
void RWS::CStreamHandler::RegisterStreamChunkHandlers(void)
   {
      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_VersionNumber), VersionNumber);
   }

// match: ?UnRegisterStreamChunkHandlers@CStreamHandler@RWS@@SAXXZ @ 0x00130910
// sp-match: ?UnRegisterStreamChunkHandlers@CStreamHandler@RWS@@SAXXZ @ 0x000E2770
void RWS::CStreamHandler::UnRegisterStreamChunkHandlers(void)
   {
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_VersionNumber));
   }

// The singleton's destructor (the compiler's; its map's), emitted for
// Instance's function-local static.
// match: ??1CStreamHandler@RWS@@QAE@XZ @ 0x00130690

// (the map's _Rrotate: single player keeps this file's copy, after _Lrotate)
// sp-match: ?_Rrotate@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@@Z @ 0x000E1D40

// The handlers' map's instantiations (the XDK's Dinkumware <map>/<xtree>),
// in the image's order; _Rrotate and const_iterator::_Dec are identical to
// the class factory's map's and are aliased there (config/aliases.txt).
// match: ?insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z @ 0x00130930
// match: ?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAEIABI@Z @ 0x00130AC0
// match: ?find@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@ABI@Z @ 0x00130B80
// match: ?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00130C10
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z @ 0x00130CE0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z-0x8 @ 0x003017B0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z @ 0x003017B8
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00131030
// match: ?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x001310B0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x003017D0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x003017D8
// match: ?clear@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00131630
// match: ?_Init@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00131690
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABI@Z @ 0x00131700
// match: ?_Lrotate@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@@Z @ 0x00131770
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z @ 0x00131820
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z @ 0x003017F0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@@Z @ 0x001318F0
// match: ?_Ubound@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABI@Z @ 0x00131940
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ @ 0x001319B0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ @ 0x00301800
// match: ?_Inc@const_iterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00131AD0
// sp-match: ?_Inc@const_iterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x000DF390
// sp-match: ?insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z @ 0x000E2470
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAEIABI@Z @ 0x000E2530
// sp-match: ?find@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@ABI@Z @ 0x000E1E20
// sp-match: ?_Lrotate@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@@Z @ 0x000E1CE0
// sp-match: ?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@D@Z @ 0x000E1DA0
// sp-match: ?_Insert@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@2@@Z @ 0x000E22C0
// sp-match: ?_Buynode@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@XZ @ 0x000DF430
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x000E2200
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x000E1F40
// sp-match: ?_Erase@?$_Tree@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IP6AXAAURwChunkHeaderInfo@@PAURwStream@@@ZU?$less@I@std@@V?$allocator@U?$pair@$$CBIP6AXAAURwChunkHeaderInfo@@PAURwStream@@@Z@std@@@4@$0A@@std@@@2@@Z @ 0x000E1DE0
