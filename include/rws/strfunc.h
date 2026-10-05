/*
 * RenderWare Studio's stream functions (the chunk ids its stream carries),
 * copied from the game framework (framework/core/streamhandler/strfunc.h),
 * with RenderWare's MAKECHUNKID and rwVENDORID_CRITERIONRM (rwplcore.h).
 * The image's chunk handlers register at MAKECHUNKID(7, strfunc_...):
 * 0x704 for strfunc_CreateEntity, 0x71A for strfunc_FunctionProfiler.
 */
#ifndef RWS_STRFUNC_H
#define RWS_STRFUNC_H

#define rwVENDORID_CRITERIONRM 0x000007L
#define MAKECHUNKID(vendorID, chunkID) (((vendorID & 0xFFFFFF) << 8) | (chunkID & 0xFF))

namespace RWS
{
   enum strfunc_func
   {
      strfunc_VersionNumber = -1,
      strfunc_Reset = 0,
      strfunc_Reserved1 = 1,
      strfunc_Reserved2 = 2,
      strfunc_SetDirectorsCameraMatrix = 3,
      strfunc_CreateEntity = 4,
      strfunc_UpdateEntityAttributes = 5,
      strfunc_SetFrozenMode = 6,
      strfunc_SetRunningMode = 7,
      strfunc_EnableDirectorsCamera = 8,
      strfunc_DisableDirectorsCamera = 9,
      strfunc_TextComment = 10,
      strfunc_StartSystem = 11,
      strfunc_StopSystem = 12,
      strfunc_DeleteEntity = 13,
      strfunc_DeleteAllEntities = 14,
      strfunc_UnLoadAsset = 15,
      strfunc_Shutdown = 16,
      strfunc_CloseConnection = 17,
      strfunc_SendTestEvent = 18,
      strfunc_Reserved3 = 19,
      strfunc_Reserved3b = 20,
      strfunc_LoadAsset = 21,
      strfunc_LoadEmbeddedAsset = 22,
      strfunc_Reserved4 = 23,
      strfunc_GetEntityMatrix = 24,
      strfunc_CustomData = 25,
      strfunc_FunctionProfiler = 26,
      strfunc_ResetEntity = 27,
      strfunc_PlacementNew = 28,
      strfunc_Initialize = 29,
      strfunc_UpdateAsset = 30,
      strfunc_DynamicSequence = 31
   };
}

#endif
