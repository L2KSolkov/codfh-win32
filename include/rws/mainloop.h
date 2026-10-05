/*
 * RWS::MainLoop, after RenderWare Studio's game framework
 * (framework/mainloop/mainloop.h, logic.h and render.h): the main loop's
 * set-up and shutdown, its logic (the running and frozen modes and the tick
 * messages) and its render. The game's level load (sub_D83C0) calls the
 * system messages' handlers directly, so the image's version has them
 * outside the anonymous namespace (the database's names are signature
 * matches: config/aliases.txt).
 */
#ifndef RWS_MAINLOOP_H
#define RWS_MAINLOOP_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/baengine.h"

namespace RWS
{
   namespace MainLoop
   {
      void Open(RwInt32 ScreenWidth, RwInt32 ScreenHeight, RwInt32 ZBitDepth);
      void Close(void);

      // The game's: the logic only (the game loop, sub_D7570).
      void Poll(void);

      void RegisterStreamChunkHandlers(void);
      void UnRegisterStreamChunkHandlers(void);

      void Init(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream);
      void StartSystem(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream);
      void StopSystem(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream);

      namespace Logic
      {
         // Sends iMsgSetRunningMode or iMsgSetFrozenMode and sets the tick
         // messages (the level load calls both; the database calls Frozen
         // SetFrozenMode).
         void Running(void);
         void Frozen(void);

         void SetEnabled(RwBool benabled);
         void Poll(void);
         void Open(void);
         void Close(void);
         void RegisterStreamChunkHandlers(void);
         void UnRegisterStreamChunkHandlers(void);
      }

      namespace Render
      {
         // The main camera, and the sub-raster camera (the game's: the
         // database names its accessors GetCamera and SetCamera too).
         RwCamera *GetCamera(void);
         RwCamera *sub_1323C0(void);
         void SetCamera(RwCamera * const pCamera);
         void sub_1323E0(RwCamera * const pCamera);

         void Open(void);
         void Close(void);
         void SetEnabled(RwBool bEnabled);
         // Draws RenderWare Studio's own render entities (the main render,
         // sub_125F20, calls it between the effects and the player's view).
         void Poll(void);
         void RegisterStreamChunkHandlers(void);
         void UnRegisterStreamChunkHandlers(void);
      }
   }
}

#endif
