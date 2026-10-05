/*
 * RWSGUID, copied from RenderWare Studio's game framework
 * (Studio\console\game_framework\source\framework\core\misc\rwsguid.h): the
 * class, its data, Clear(), operator== (the resource manager's FindById)
 * and operator< (the attribute handlers' map's ordering; the image calls
 * it out of line, ??MRWSGUID@RWS@@QBE_NABV01@@Z).
 * CAttributeHandler's inline constructor expands Clear() in the image
 * (sub_B9F20 zeroes +0x08 to +0x14 through a pointer temporary), so the
 * image's framework has this four-dword layout.
 */
#ifndef RWS_RWSGUID_H
#define RWS_RWSGUID_H

#include "rw/ostypes.h"

namespace RWS
{
   class RWSGUID
   {
   public:
      void Clear()
      {
         m_Data[0] = 0;
         m_Data[1] = 0;
         m_Data[2] = 0;
         m_Data[3] = 0;
      }

      bool operator == ( const RWSGUID & Guid ) const
      {
         return (m_Data[0] == Guid.m_Data[0]
                 && m_Data[1] == Guid.m_Data[1]
                 && m_Data[2] == Guid.m_Data[2]
                 && m_Data[3] == Guid.m_Data[3]);
      }

      bool operator < ( const RWSGUID & Guid ) const
      {
         if (m_Data[0] != Guid.m_Data[0])
         {
            return (m_Data[0] < Guid.m_Data[0]);
         }
         else
         {
            if (m_Data[1] != Guid.m_Data[1])
            {
               return (m_Data[1] < Guid.m_Data[1]);
            }
            else
            {
               if (m_Data[2] != Guid.m_Data[2])
               {
                  return (m_Data[2] < Guid.m_Data[2]);
               }
               else
               {
                  return (m_Data[3] < Guid.m_Data[3]);
               }
            }
         }
      }

      RwUInt32 m_Data[4];
   };
}

#endif
