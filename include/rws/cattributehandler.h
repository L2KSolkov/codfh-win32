/*
 * RWS::CAttributeHandler and the attribute packet classes, copied from
 * RenderWare Studio's game framework (Studio\console\game_framework\source\
 * framework\core\attributehandler\cattributehandler.h).
 *
 * CAttributeHandler: the image's version has two virtual functions, the
 * destructor and HandleAttributes (??_7CAttributeHandler@RWS@@6B@ holds the
 * scalar deleting destructor, then the empty HandleAttributes folded into
 * sub_15FB30); the later GetAttributeTable and GetAttrPostUpdateFunc of the
 * Studio sources are not in it. Its data members fix its layout (vtable,
 * m_Flags at +0x04, m_InstanceId at +0x08, 0x18 bytes). The image names its
 * vtable ??_7CAttributeHandler@RWS@@6B@ and its destructor
 * ??1CAttributeHandler@RWS@@UAE@XZ.
 *
 * CAttributeDataChunk, CAttributePacket, CAttributeCommand and
 * CAttributeCommandIterator: the members a behaviour's HandleAttributes uses
 * (CDebugScript's, sub_43200): the iterator's out-of-line functions, which
 * the image names, and the command's inline accessors. The design-time
 * command tables, the static registry functions and the rest of the inline
 * helpers are left out until something needs them.
 */
#ifndef RWS_CATTRIBUTEHANDLER_H
#define RWS_CATTRIBUTEHANDLER_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rws/rwsguid.h"

namespace RWS
{
   #define RWS_DECLARE_CLASSID(className) static const RwChar* p##className##ClassID
   #define RWS_IMPLEMENT_CLASSID(className) const RwChar* className::p##className##ClassID = #className
   #define RWS_CLASSID_OF(className) (className::p##className##ClassID)

   typedef RwUInt32 RWS_DWORD;
   typedef RwReal RWS_FLOAT;

   class CAttributePacket;

   typedef void (*NewAttributeHandlerCallBack)(void);

   class CAttributeHandler
   {
   public:
      virtual ~CAttributeHandler();

      virtual void HandleAttributes(const CAttributePacket& attr);

      void Add(const RWSGUID & instanceId);
      static void Remove(const RWSGUID & instanceId);
      static CAttributeHandler* Find(const RWSGUID & instanceId);
      // Deletes the handlers not locked (Purge) or every one (PurgeAll; the
      // game loop's module shutdown, sub_D7040).
      static void Purge();
      static void PurgeAll(void);

      static void Open(NewAttributeHandlerCallBack pNewAttributeHandlerCallBack_)
      {
         pNewAttributeHandlerCallBack = pNewAttributeHandlerCallBack_;
      }

      static void Close() { Purge(); pNewAttributeHandlerCallBack = 0;}

      static void RegisterStreamChunkHandlers(void);
      static void UnRegisterStreamChunkHandlers(void);

      static void NewAttributeHandlerCreated(void)
      {
         if (pNewAttributeHandlerCallBack) pNewAttributeHandlerCallBack();
      }

      #define uATTRIBUTEHANDLER_FLAG_DEBUG    (static_cast<RwUInt32>(0x1 << 0))
      #define uATTRIBUTEHANDLER_FLAG_LOCKED   (static_cast<RwUInt32>(0x1 << 1))

      void Lock()
      {
         m_Flags |= uATTRIBUTEHANDLER_FLAG_LOCKED;
      }

      RwBool IsLocked()
      {
         if (m_Flags & uATTRIBUTEHANDLER_FLAG_LOCKED)
         {
            return TRUE;
         }
         else
         {
            return FALSE;
         }
      }

      // The image's name for RWS's sm_pNewAttributeHandlerCallBack.
      static NewAttributeHandlerCallBack pNewAttributeHandlerCallBack;

   protected:
      RwUInt32 m_Flags;

      CAttributeHandler() : m_Flags(0)
      {
         m_InstanceId.Clear();
      }

   private:
      CAttributeHandler( const CAttributeHandler& );
      CAttributeHandler& operator = ( const CAttributeHandler& );

   protected:
      RWSGUID m_InstanceId;
   };

   class CAttributeDataChunk
   {
   public:
      const RWS_DWORD size_;
      const RWS_DWORD type_;
      const RWS_DWORD data_;

   private:
      friend class CAttributeDataChunkIterator;

      bool IsEndChunk() const;

      const CAttributeDataChunk* pNextChunk() const;

      CAttributeDataChunk();
      CAttributeDataChunk( const CAttributeDataChunk& );
      CAttributeDataChunk& operator = ( const CAttributeDataChunk& );
   };

   class CAttributePacket
   {
   public:
      const RwChar* GetNameOfClassToCreate() const;
      RWSGUID GetInstanceId() const;

   private:
      CAttributePacket();
      CAttributePacket( const CAttributePacket& );
      CAttributePacket& operator = ( const CAttributePacket& );

      friend class CAttributeCommandIterator;
      const CAttributeDataChunk firstChunk_;
   };

   class CAttributeCommand
   {
   public:
      RwUInt32 GetCommandId() const;

      template<class T> void GetCommandData(T &dest) const
      { dest = *(reinterpret_cast<const T*>(&chunk_.data_)); }
      // A flag, 1 or 0 by a branch. Evidence: CWeaponBehavior's
      // HandleAttributes (sub_C12C0, commands 13 and 153) computes the flag's
      // address before this command (arguments right to left), with the
      // value's temporary first, as for an inline member's body.
      void GetCommandData(bool &dest) const
      {
         if (GetAs_RwInt32())
         {
            dest = true;
         }
         else
         {
            dest = false;
         }
      }

      const void *GetAs_void_ptr(void) const
         {return reinterpret_cast<const void *>(&chunk_.data_);}
      const RwChar *GetAs_RwChar_ptr(void) const
         {return reinterpret_cast<const RwChar *>(&chunk_.data_);}
      const RwInt32 GetAs_RwInt32(void) const
         {return *(reinterpret_cast<const RwInt32 *>(&chunk_.data_));}
      const RwUInt32 GetAs_RwUInt32(void) const
         {return *(reinterpret_cast<const RwUInt32 *>(&chunk_.data_));}
      const RwReal GetAs_RwReal(void) const
         {return *(reinterpret_cast<const RwReal *>(&chunk_.data_));}

   private:
      CAttributeCommand();
      CAttributeCommand( const CAttributeCommand& );
      CAttributeCommand& operator = ( const CAttributeCommand& );

      const CAttributeDataChunk chunk_;
   };

   class CAttributeDataChunkIterator
   {
   public:
      CAttributeDataChunkIterator(const CAttributeDataChunk& begin);

      bool IsFinished() const;
      CAttributeDataChunkIterator& operator++();
      const CAttributeDataChunk* operator->() const;

   private:
      const CAttributeDataChunk* pCurrChunk_;
   };

   class CAttributeCommandIterator
   {
   public:
      CAttributeCommandIterator(
         const CAttributePacket& packet,
         const RwChar *targetClass
         );

      bool IsFinished() const;
      CAttributeCommandIterator& operator++();
      const CAttributeCommand* operator->() const;

   private:
      void SkipToNextAttributeCommand( bool lastClassIdChunkWasForTargetClass );
      CAttributeDataChunkIterator chunkIt_;
      const RwChar* pTargetClass_;
   };
}

#endif
