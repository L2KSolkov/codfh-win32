; codfh-match: XDK XONLINES code (QFE 9, repacked)
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ?StorageUploadInitializeContext@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@KKPAXPBDK1@Z:NEAR
EXTERN ?ClearServiceTicketCache@CXo@@IAEXXZ:NEAR
EXTERN ?GetServiceTicketContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?MessagingSendContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?GetMachineAccountContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?MessagingDoWork@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z:NEAR
EXTERN ?GetServiceTicket@CXo@@IAEJPAUXKERB_TGT_CONTEXT@@PBKKHPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?GetCombinedTicketContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?storulScanFilesCrawlOnFileContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?ConfigureUPnPNatVerifyDiscoveryReply@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z:NEAR
EXTERN ?AppendTeamTicketsIfNecessary@CXo@@IAEJKKPAEPAKPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?BuildPreamble@CXo@@IAEJKGKPADEKKKPAU_FILETIME@@PAE2PAK@Z:NEAR
EXTERN ?BuildUploadPreamble@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@EKPAEPAK@Z:NEAR
EXTERN ?CacheClose@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?CacheDelete@CXo@@IAEJPAXPAUXONLC_CONTEXT@@@Z:NEAR
EXTERN ?CacheIndexFlush@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?CacheLookup@CXo@@IAEJPAXPAUXONLC_CONTEXT@@@Z:NEAR
EXTERN ?CacheLookupNext@CXo@@IAEJPAXPAUXONLC_CONTEXT@@@Z:NEAR
EXTERN ?CacheOpen@CXo@@IAEJW4XONLC_TYPE@@P6GHPBE1@ZPAXHPAPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?CacheRetrieve@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@PAUXONLC_CONTEXT@@@Z:NEAR
EXTERN ?CacheUpdate@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@PAE2H@Z:NEAR
EXTERN ?CheckReadWrite@CCacheTask@@AAEJK@Z:NEAR
EXTERN ?ClearSentInvites@CXo@@IAEXPAUXPRESENCE_FRIEND_LIST@@@Z:NEAR
EXTERN ?CloseCombinedTicketCache@CXo@@IAEXXZ:NEAR
EXTERN ?CloseLogonTimeCache@CXo@@IAEXXZ:NEAR
EXTERN ?CloseServiceTicketCache@CXo@@IAEXXZ:NEAR
EXTERN ?ConfigureUPnPNat@CXo@@IAEJUin_addr@@GPAXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z:NEAR
EXTERN ?ConfigureUPnPNatBuildAddPortRequest@CXo@@IAEXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@G@Z:NEAR
EXTERN ?ConfigureUPnPNatClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?ConfigureUPnPNatGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAG@Z:NEAR
EXTERN ?ConfigureUPnPNatSelectNewPort@CXo@@IAEXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z:NEAR
EXTERN ?ConfigureUPnPNatSendDiscoveryRequest@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z:NEAR
EXTERN ?ConfigureUPnPNatVerifyAddPortResponse@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@K@Z:NEAR
EXTERN ?ConfigureUPnPNatVerifyGetDescriptionResponse@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z:NEAR
EXTERN ?DNSLookup@CXo@@IAEJKPAXPAUXONLINETASK_DNS_LOOKUP@@@Z:NEAR
EXTERN ?DNSLookupContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?DNSLookupGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAPAUXNDNS@@@Z:NEAR
EXTERN ?DecryptSessionKey@CXo@@IAEHPAE0@Z:NEAR
EXTERN ?Delete@CLocalCache@@QAEXXZ:NEAR
EXTERN ?DircrawlInitializeContext@CXo@@IAEJPAD0KKPAUXONLINETASK_HANDLE__@@1PAXPAUXONLINETASK_DIRCRAWL@@@Z:NEAR
EXTERN ?Download@CXo@@IAEJPBDPBEKPBU_FILETIME@@T_LARGE_INTEGER@@PAUXRL_ASYNC@@@Z:NEAR
EXTERN ?EncryptSessionKey@CXo@@IAEXPAE0@Z:NEAR
EXTERN ?FeedbackCreateContext@CXo@@IAEJPAPAUXONFEEDBACK_EXTENDED_HANDLE@@KPAX@Z:NEAR
EXTERN ?FeedbackResetHistory@CXo@@IAEJK@Z:NEAR
EXTERN ?FeedbackSetHistory@CXo@@IAEHKU_XUID@@W4XONLINE_FEEDBACK_TYPE@@@Z:NEAR
EXTERN ?FriendlistCacheCleanup@CXo@@IAEXPAUXPRESENCE_EXTENDED_HANDLE@@@Z:NEAR
EXTERN ?FriendlistCacheClose@CXo@@IAEJPBUXPRESENCE_EXTENDED_HANDLE@@@Z:NEAR
EXTERN ?FriendlistCacheOpen@CXo@@IAEJPAUXPRESENCE_EXTENDED_HANDLE@@@Z:NEAR
EXTERN ?FriendsAreBeingEnumerated@CXo@@IAEHK@Z:NEAR
EXTERN ?FriendsEnumerateClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?FriendsNotifyCallback@CXo@@IAEHPAXKHPBUQ_MESSAGE_SUMMARY@@@Z:BYTE
EXTERN ?GetAddressFromURL@CXo@@IAEJQADPAUin_addr@@GPAUsockaddr_in@@PAPAD@Z:NEAR
EXTERN ?GetCombinedTicket@CXo@@IAEJPAU_XC_ONLINE_USER_ACCOUNT_STRUCT@@HPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?GetCombinedTicketGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAPAUXKERB_TGT_CONTEXT@@PAH@Z:NEAR
EXTERN ?GetMachineAccountSendAsRequest@CXo@@IAEJPAUXONLINETASK_GET_MACHINE_ACCOUNT@@@Z:NEAR
EXTERN ?GetMessageNotifications@CAdvNotif@@QAEHKHPAUXONLINE_ADVNOTIF_NOTIFICATIONS@@0@Z:NEAR
EXTERN ?GetRemoteFileReferenceSize@@YGJPAUXONLINESTORAGE_REMOTE_FILE_REFERENCE@@PAK@Z:NEAR
EXTERN ?GetSendRecvResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAK1PAPAU_WSABUF@@@Z:NEAR
EXTERN ?GetServiceTicketGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAPAUXKERB_SERVICE_CONTEXT@@PAH@Z:NEAR
EXTERN ?GetServiceTicketSendTgsRequest@CXo@@IAEJPAUXONLINETASK_GET_SERVICE_TICKET@@@Z:NEAR
EXTERN ?GetSingleTicketGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAPAUXKERB_TGT_CONTEXT@@@Z:NEAR
EXTERN ?GetSingleTicketSendAsRequest@CXo@@IAEJPAUXONLINETASK_GET_SINGLE_TICKET@@@Z:NEAR
EXTERN ?GetUserFromSeqNum@CXo@@IAEPAUXPRESENCE_USER@@K@Z:NEAR
EXTERN ?KRB5_Module_Startup@@YGXPAUtagASN1module_t@@@Z:NEAR
EXTERN ?KerbComputeKdcRequestNonceHmacKey@@YGXPAVCScratchMemoryAllocator@@PBUKERB_ENCRYPTION_KEY@@KPAE@Z:NEAR
EXTERN ?MessageNotifyCallbackHandler@CAdvNotif@@QAEXKPBUQ_MESSAGE_SUMMARY@@@Z:NEAR
EXTERN ?MessagingClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?MessagingDetailsContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:BYTE
EXTERN ?MessagingDoNotifyCallbacksRemove@CXo@@IAEXKPBUQ_MESSAGE_SUMMARY@@@Z:NEAR
EXTERN ?MessagingEnumerateMsgs@CXo@@IAEJKPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?MessagingGetAttachmentExpiration@@YGXGPAU_FILETIME@@@Z:NEAR
EXTERN ?MessagingGetDetailsInternal@CXo@@IAEJHKKGKKPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?MessagingGetSummary@CXo@@IAEJKKPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?MessagingHasMsgExpired@@YGHPBUQ_MESSAGE_SUMMARY@@PBU_FILETIME@@@Z:NEAR
EXTERN ?MessagingInsertSummaryIntoCache@CXo@@IAEHKPAUQ_MESSAGE_SUMMARY@@@Z:NEAR
EXTERN ?MessagingIsSummarySafeForTitle@CXo@@QAEHPBUQ_MESSAGE_SUMMARY@@PAH@Z:NEAR
EXTERN ?MessagingIsTaskSummaryForID@CXo@@IAEHPAUXONLINETASK_HANDLE__@@KK@Z:NEAR
EXTERN ?MessagingRequestNotifications@CXo@@IAEXP81@AEHPAXKHPBUQ_MESSAGE_SUMMARY@@@ZP81@AEX0K1PAUXONLINETASK_HANDLE__@@@ZK0@Z:NEAR
EXTERN ?MessagingValidateQMessageSummary@CXo@@IAEHPAUQ_MESSAGE_SUMMARY@@@Z:NEAR
EXTERN ?MutelistCacheCleanup@CXo@@IAEXPAUXPRESENCE_EXTENDED_HANDLE@@@Z:NEAR
EXTERN ?MutelistCacheClose@CXo@@IAEJPBUXPRESENCE_EXTENDED_HANDLE@@@Z:NEAR
EXTERN ?MutelistCacheOpen@CXo@@IAEJPAUXPRESENCE_EXTENDED_HANDLE@@@Z:NEAR
EXTERN ?NotificationTerm@CXo@@IAEXXZ:NEAR
EXTERN ?ParseUPnPHeaders@@YGXQADPAU_UPNP_HEADER_INFO@@@Z:NEAR
EXTERN ?PathnameSpecialCompare@@YGHPBE0@Z:BYTE
EXTERN ?PoolAlloc@CXo@@IAEPAXIK@Z:NEAR
EXTERN ?PoolAllocZ@CXo@@IAEPAXIK@Z:NEAR
EXTERN ?PoolFree@CXo@@IAEXPAX@Z:NEAR
EXTERN ?PresenceCreateContext@CXo@@IAEJPAPAUXPRESENCE_EXTENDED_HANDLE@@PAXW4XPRESENCE_REQUESTTYPE@@K@Z:NEAR
EXTERN ?PresenceGetPresenceThrottleType@@YGKW4P_MSG_TYPES@@@Z:NEAR
EXTERN ?ProcessStorageResolvedName@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAU_XONLINE_SERVICE_INFO@@@Z:NEAR
EXTERN ?ResetFriendlist@CXo@@IAEJPAUXPRESENCE_FRIEND_LIST@@GKPAPAEPAE@Z:NEAR
EXTERN ?ResetMutelist@CXo@@IAEJPAUXPRESENCE_MUTE_LIST@@GKPAPAEPAE@Z:NEAR
EXTERN ?RevertLogonState@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z:NEAR
EXTERN ?SaveMachineAccountConfig@CXo@@QAEHXZ:NEAR
EXTERN ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z:NEAR
EXTERN ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z:NEAR
EXTERN ?SetTitleName@CTitleCache@@IAEJKGPBG@Z:NEAR
EXTERN ?SortFriends@CXo@@IAEJPAUXPRESENCE_FRIEND_LIST@@@Z:NEAR
EXTERN ?StorageValidateFacility@CXo@@IAEJK@Z:NEAR
EXTERN ?SysAlloc@CXo@@IAEPAXIK@Z:NEAR
EXTERN ?SysAllocZ@CXo@@IAEPAXIK@Z:NEAR
EXTERN ?SysFree@CXo@@IAEXPAX@Z:NEAR
EXTERN ?SysFree@CXo@@IAEXPAXK@Z:NEAR
EXTERN ?TaskInitializeContext@CXo@@IAEXPAUXONLINETASK_CONTEXT@@@Z:NEAR
EXTERN ?TeamsGetTickets@CXo@@IAEJKPAEPAK@Z:NEAR
EXTERN ?TeamsTicketMessageNotifyCallback@CXo@@IAEXKPBUQ_MESSAGE_SUMMARY@@@Z:NEAR
EXTERN ?UpdateCurrentIndexEntry@CLocalCache@@QAEXPAE@Z:NEAR
EXTERN ?UpdateMRUList@CLocalCache@@QAEXPAE0@Z:NEAR
EXTERN ?Upload@CXo@@IAEJPBDPBEK1KPAUXRL_ASYNC@@@Z:NEAR
EXTERN ?UploadFromMemoryInternal@CXo@@IAEJKKPBDPAEKPBEK2KKPAXPAUXRL_ASYNC_EXTENDED@@PBUXRL_SPECIAL@@PAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?VerifyOnlineUserSignature@CXo@@IAEHPAU_XC_ONLINE_USER_ACCOUNT_STRUCT@@PAE@Z:NEAR
EXTERN ?WToUtf8@CXo@@IAEPAEPAGPAEPBG@Z:NEAR
EXTERN ?WriteAndAdvanceCffile@@YGJPAUXONLINETASK_STORAGE_UPLOAD@@KPADKGG@Z:NEAR
EXTERN ?XOnlineGetServiceInfo@CXo@@QAEJKPAU_XONLINE_SERVICE_INFO@@@Z:NEAR
EXTERN ?XOnlineMessageDestroy@CXo@@QAEJPAUXONLINE_MSG_HANDLE__@@@Z:NEAR
EXTERN ?XOnlineSaveLogonState@CXo@@QAEJPAU_XONLINE_LOGON_STATE@@@Z:NEAR
EXTERN ?XOnlineStorageGetProgress@CXo@@QAEJPAUXONLINETASK_HANDLE__@@PAKPA_K2@Z:NEAR
EXTERN ?XOnlineStorageResolveName@CXo@@IAEJPAGHHPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?XOnlineStorageUploadFromMemory@CXo@@QAEJKKPBGU_FILETIME@@PAEKKPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?XOnlineTitleNameStartup@CXo@@QAEJPAXPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?XOnlineUploadFromMemory@CXo@@QAEJKKPBDPAEPAKPBEK3KKPAXHPAPAUXONLINETASK_HANDLE__@@@Z:NEAR
EXTERN ?XOnlineUploadGetResults@CXo@@QAEJPAUXONLINETASK_HANDLE__@@PAPAEPAKPAT_ULARGE_INTEGER@@32PAU_FILETIME@@@Z:NEAR
EXTERN ?XRL_BuildPostRequest@CXo@@IAEJKPBDKPADPAKPBEKT_ULARGE_INTEGER@@K@Z:NEAR
EXTERN ?XRL_CleanupHandler@CXo@@IAEXPAUXRL_ASYNC@@@Z:NEAR
EXTERN ?XRL_ProcessHttp@CXo@@IAEJPAUXRL_ASYNC@@KPAH@Z:NEAR
EXTERN ?XRL_RetrieveThrottleSettings@CXo@@IAEJKKPAUXRL_ASYNC@@_KPAK2@Z:NEAR
EXTERN ?XkerbVerifyAsReply@CXo@@IAEJPAEKPAUXKERB_TGT_CONTEXT@@@Z:NEAR
EXTERN ?XkerbVerifyTgsReply@CXo@@IAEJPAUXKERB_TGT_CONTEXT@@PAEKPAUXKERB_SERVICE_CONTEXT@@@Z:NEAR
EXTERN ?XnLogonGetStatus@CXoBase@@QAEKPAU_SGADDR@@PAK@Z:NEAR
EXTERN ?XnNatDetect@CXoBase@@QAEKUin_addr@@H@Z:NEAR
EXTERN ?XnSetEventTimer@CXoBase@@QAEXPAEPAXK@Z:NEAR
EXTERN ?XnSetXoBase@CXoBase@@QAEXPAV1@@Z:NEAR
EXTERN ?_XOnlineCleanupAsyncIO@CXo@@QAEHXZ:NEAR
EXTERN ?g_pXo@@3PAVCXo@@A:BYTE
EXTERN ?storulClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z:BYTE
EXTERN ?storulContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:BYTE
EXTERN ?xrldtmCompleted@CXo@@IAEJPAX@Z:BYTE
EXTERN ?xrldtmDoneHeaders@CXo@@IAEJPAX@Z:BYTE
EXTERN ?xrlufContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:BYTE
EXTERN ?xrlufInitializeTask@CXo@@IAEJW4XRLUPLOAD_EXTTYPE@@PAXPAUXONLINETASK_HANDLE__@@@Z:BYTE
EXTERN ?xrlufmInitializeTask@CXo@@IAEJW4XRLUPLOAD_EXTTYPE@@PAXPAUXONLINETASK_HANDLE__@@@Z:BYTE
EXTERN ?xrlulsCompleted@CXo@@IAEJPAX@Z:BYTE
EXTERN ?xsnprintf@@YAHPADIPBDZZ:NEAR
EXTERN _CloseHandle@4:NEAR
EXTERN _CompareFileTime:NEAR
EXTERN _CreateFileA@28:NEAR
EXTERN _DeleteFileA@4:NEAR
EXTERN _GetDiskFreeSpaceExA@16:NEAR
EXTERN _GetFileAttributesExA@12:NEAR
EXTERN _GetLastError@0:NEAR
EXTERN _GetSystemTimeAsFileTime@4:NEAR
EXTERN _GetTickCount@0:NEAR
EXTERN _HeapCreate@12:NEAR
EXTERN _MultiByteToWideChar@24:NEAR
EXTERN _SetEvent@4:NEAR
EXTERN _SetLastError@4:NEAR
EXTERN _WSACancelOverlappedIO:NEAR
EXTERN _WideCharToMultiByte@32:NEAR
EXTERN _XNetConfigUPnP:NEAR
EXTERN _XNetGetConfigStatus@4:NEAR
EXTERN _XNetGetTitleXnAddr@4:NEAR
EXTERN _XNetLoadConfigSector@16:NEAR
EXTERN _XNetOpenConfigVolume@0:NEAR
EXTERN _XNetRandom@8:NEAR
EXTERN _XNetServerToInAddr@12:NEAR
EXTERN _XWriteTitleInfoAndRebootA@20:NEAR
EXTERN _XWriteTitleInfoNoReboot@24:NEAR
EXTERN _XapipUpdateDashIfNecessary@4:NEAR
EXTERN _XapipUpdateGetCurrentDDriveMapping@8:NEAR
EXTERN _XapipUpdateSaveDDriveMappingToLaunchPage@8:NEAR
EXTERN _XcHMAC@28:NEAR
EXTERN _XcModExp@20:NEAR
EXTERN _XcSHAInit@4:NEAR
EXTERN _XcsCreateSignatureFile@8:NEAR
EXTERN _XcsRegisterSignatureWithData@36:NEAR
EXTERN _XcsSetSignatureFileInformationEx@28:NEAR
EXTERN _XcsWriteSignatureFile@0:NEAR
EXTERN __allmul:NEAR
EXTERN __imp__HalReturnToFirmware@4:BYTE
EXTERN __imp__NtClose@4:BYTE
EXTERN __imp__NtCreateFile@36:BYTE
EXTERN __imp__NtDeleteFile@4:BYTE
EXTERN __imp__NtOpenFile@24:BYTE
EXTERN __imp__RtlInitAnsiString@8:BYTE
EXTERN __imp__RtlNtStatusToDosError@4:BYTE
EXTERN __wcsicmp:NEAR
EXTERN _closesocket@4:NEAR
EXTERN _g_abOakleyGroup1BaseIntel:BYTE
EXTERN _g_abOakleyGroup1ModIntel:BYTE
EXTERN _j__XcspFreeEverything@0:NEAR
EXTERN _loc_35E817:NEAR
EXTERN _lstrcpynA@12:NEAR
EXTERN _lstrlenW@4:NEAR
EXTERN _memmove:NEAR
EXTERN _setsockopt@20:NEAR
EXTERN _shutdown:NEAR
EXTERN _socket@12:NEAR
EXTERN _strtok:NEAR
EXTERN _sub_356E16:NEAR
EXTERN _sub_356E2B:NEAR
EXTERN _sub_3575F7:NEAR
EXTERN _sub_3589A9:NEAR
EXTERN _sub_3627F0:BYTE
EXTERN _sub_3665EB:NEAR
EXTERN _sub_366774:NEAR
EXTERN _sub_366FEA:NEAR
EXTERN _sub_3682D6:NEAR
EXTERN _sub_3682F5:NEAR
EXTERN ?XnLogonChangeUsers@CXoBase@@QAEHPA_K@Z:NEAR
EXTERN ?XnLogonSetQEvent@CXoBase@@QAEIIPAX@Z:NEAR
EXTERN ?XnLogonClearQEvent@CXoBase@@QAEHII@Z:NEAR
EXTERN ?XnLogonSetBwLimit@CXoBase@@QAEXKK@Z:NEAR
EXTERN ?XnLogoff@CXoBase@@QAEXXZ:NEAR
EXTERN ?XnRaiseToDpc@CXoBase@@QAEXH@Z:NEAR
EXTERN ?XnLogon@CXoBase@@QAEXUin_addr@@PA_KPAX@Z:NEAR
EXTERN _unk_0205D0:BYTE
EXTERN _unk_0219F4:BYTE
EXTERN _unk_021BF4:BYTE
EXTERN _unk_021DF8:BYTE
EXTERN _unk_021E28:BYTE
EXTERN _unk_021F20:BYTE
EXTERN _unk_021F48:BYTE
EXTERN _unk_021F4C:BYTE
EXTERN _unk_021F58:BYTE
EXTERN _unk_3D28E4:BYTE
EXTERN _unk_3D292F:BYTE
EXTERN _unk_3D51A4:BYTE
EXTERN _unk_3D8C40:BYTE
EXTERN _unk_3E3D54:BYTE
EXTERN _unk_3E3D98:BYTE
EXTERN _unk_3E5300:BYTE
EXTERN _unk_3E8E24:BYTE
EXTERN _unk_3EB4F8:BYTE
EXTERN _unk_400000:BYTE
EXTERN _unk_4311F8:BYTE
EXTERN _unk_431204:BYTE
EXTERN _unk_431234:BYTE
EXTERN _unk_431264:BYTE
EXTERN _unk_431268:BYTE
EXTERN _unk_4312A8:BYTE
EXTERN _unk_432B68:BYTE
EXTERN _unk_432B6C:BYTE
EXTERN _unk_5082A8:BYTE
EXTERN _unk_538DC8:BYTE
EXTERN _unk_538DD4:BYTE
EXTERN _unk_538DEC:BYTE
EXTERN _unk_538E04:BYTE
EXTERN _unk_538E2C:BYTE
EXTERN _unk_538E50:BYTE
EXTERN _unk_538E60:BYTE
EXTERN _unk_538F80:BYTE
EXTERN _unk_538FF0:BYTE
EXTERN _unk_539040:BYTE
EXTERN _unk_5393FA:BYTE
EXTERN _unk_53947C:BYTE
EXTERN _unk_5394B8:BYTE
EXTERN _unk_539748:BYTE
EXTERN _unk_539778:BYTE
EXTERN _unk_5397F4:BYTE
EXTERN _unk_539B3C:BYTE
EXTERN _unk_539B6C:BYTE
EXTERN _unk_539BE0:BYTE
EXTERN _unk_539BE4:BYTE
EXTERN _unk_539BE8:BYTE
EXTERN _unk_539BF4:BYTE
EXTERN _unk_539C00:BYTE
EXTERN _unk_539EB0:BYTE
EXTERN _unk_539EDC:BYTE
EXTERN _unk_539F00:BYTE
EXTERN _unk_539F64:BYTE
EXTERN _unk_539FF8:BYTE
EXTERN _unk_53A000:BYTE
EXTERN _unk_53A018:BYTE
EXTERN _unk_53A2E0:BYTE
EXTERN _unk_53A2E4:BYTE
EXTERN _unk_53A318:BYTE
EXTERN _wcscpy:NEAR
EXTERN _wcslen:NEAR
EXTERN ?GetServiceTicketClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z:NEAR

seg6 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: _XOnlineFriendsEnumerate@12 @ 0x00356418
PUBLIC _XOnlineFriendsEnumerate@12
_XOnlineFriendsEnumerate@12:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x508290]
        dd ?g_pXo@@3PAVCXo@@A
        jmp _sub_3613FE   ; 0x3613FE

seg6 ENDS

seg7 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: _XOnlineFriendsJoinGame@8 @ 0x003564C9
PUBLIC _XOnlineFriendsJoinGame@8
_XOnlineFriendsJoinGame@8:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x508290]
        dd ?g_pXo@@3PAVCXo@@A
        jmp _loc_35E817   ; 0x35E817
seg7 ENDS

seg8 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?Init@CXo@@QAEJPBU_XONLINE_STARTUP_PARAMS@@@Z @ 0x0035658C
PUBLIC ?Init@CXo@@QAEJPBU_XONLINE_STARTUP_PARAMS@@@Z
?Init@CXo@@QAEJPBU_XONLINE_STARTUP_PARAMS@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 081h, 0ECh, 0ECh, 001h, 000h, 000h   ; sub esp, 0x1ec
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 033h, 0F6h   ; xor esi, esi
        db 03Bh, 0C6h   ; cmp eax, esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 074h, 009h   ; je 0x3565ab
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 03Bh, 0C6h   ; cmp eax, esi
        db 074h, 003h   ; je 0x3565ab
        db 050h   ; push eax
        db 0EBh, 005h   ; jmp 0x3565b0
$L_3565ab:
        db 068h, 000h, 000h, 002h, 000h   ; push 0x20000
$L_3565b0:
        db 068h, 000h, 010h, 000h, 000h   ; push 0x1000
        db 056h   ; push esi
        call _HeapCreate@12   ; 0x2311E7
        db 03Bh, 0C6h   ; cmp eax, esi
        db 089h, 083h, 098h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x98], eax
        db 075h, 00Ah   ; jne 0x3565cf
        db 0B8h, 00Eh, 000h, 007h, 080h   ; mov eax, 0x8007000e
        db 0E9h, 049h, 001h, 000h, 000h   ; jmp 0x356718
$L_3565cf:
        db 0A1h, 018h, 001h, 001h, 000h   ; mov eax, dword ptr [0x10118]
        db 08Bh, 048h, 008h   ; mov ecx, dword ptr [eax + 8]
        db 089h, 04Bh, 004h   ; mov dword ptr [ebx + 4], ecx
        db 08Bh, 088h, 0ACh, 000h, 000h, 000h   ; mov ecx, dword ptr [eax + 0xac]
        db 089h, 04Bh, 008h   ; mov dword ptr [ebx + 8], ecx
        db 08Bh, 088h, 0A0h, 000h, 000h, 000h   ; mov ecx, dword ptr [eax + 0xa0]
        db 089h, 04Bh, 00Ch   ; mov dword ptr [ebx + 0xc], ecx
        db 08Bh, 080h, 0D4h, 001h, 000h, 000h   ; mov eax, dword ptr [eax + 0x1d4]
        db 03Bh, 0C6h   ; cmp eax, esi
        db 074h, 003h   ; je 0x3565f9
        db 089h, 043h, 01Ch   ; mov dword ptr [ebx + 0x1c], eax
$L_3565f9:
        db 08Bh, 043h, 004h   ; mov eax, dword ptr [ebx + 4]
        db 057h   ; push edi
        db 08Dh, 07Bh, 010h   ; lea edi, [ebx + 0x10]
        db 0BEh   ; mov esi, 0x538dd4
        dd _unk_538DD4
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 033h, 0F6h   ; xor esi, esi
        db 089h, 083h, 050h, 018h, 000h, 000h   ; mov dword ptr [ebx + 0x1850], eax
        db 089h, 0B3h, 054h, 018h, 000h, 000h   ; mov dword ptr [ebx + 0x1854], esi
        db 089h, 083h, 058h, 018h, 000h, 000h   ; mov dword ptr [ebx + 0x1858], eax
        db 089h, 0B3h, 05Ch, 018h, 000h, 000h   ; mov dword ptr [ebx + 0x185c], esi
        db 08Dh, 0BBh, 0ECh, 005h, 000h, 000h   ; lea edi, [ebx + 0x5ec]
$L_356628:
        db 08Dh, 043h, 01Ch   ; lea eax, [ebx + 0x1c]
        db 080h, 038h, 000h   ; cmp byte ptr [eax], 0
        db 0B9h   ; mov ecx, 0x3d292f
        dd _unk_3D292F
        db 074h, 005h   ; je 0x35663a
        db 0B9h   ; mov ecx, 0x3e3d98
        dd _unk_3E3D98
$L_35663a:
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 0B6h   ; push dword ptr [esi + 0x4311f8]
        dd _unk_4311F8
        db 06Ah, 018h   ; push 0x18
        db 057h   ; push edi
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 083h, 0C6h, 004h   ; add esi, 4
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 083h, 0C7h, 044h   ; add edi, 0x44
        db 083h, 0FEh, 00Ch   ; cmp esi, 0xc
        db 072h, 0D0h   ; jb 0x356628
        call _XNetOpenConfigVolume@0   ; 0x3793B7
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 089h, 083h, 094h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x94], eax
        db 075h, 00Ah   ; jne 0x356672
        db 0B8h, 005h, 040h, 000h, 080h   ; mov eax, 0x80004005
        db 0E9h, 0A5h, 000h, 000h, 000h   ; jmp 0x356717
$L_356672:
        db 08Dh, 083h, 028h, 007h, 000h, 000h   ; lea eax, [ebx + 0x728]
        db 050h   ; push eax
        db 08Dh, 083h, 024h, 007h, 000h, 000h   ; lea eax, [ebx + 0x724]
        db 050h   ; push eax
        db 033h, 0F6h   ; xor esi, esi
        db 056h   ; push esi
        db 056h   ; push esi
        db 056h   ; push esi
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?CacheOpen@CXo@@IAEJW4XONLC_TYPE@@P6GHPBE1@ZPAXHPAPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x36895D
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 009h   ; jge 0x35669a
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?CloseLogonTimeCache@CXo@@IAEXXZ   ; 0x3577D6
        db 0EBh, 00Ah   ; jmp 0x3566a4
$L_35669a:
        db 0C7h, 083h, 02Ch, 007h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x72c], 1
$L_3566a4:
        db 081h, 07Bh, 01Ch, 047h, 053h, 052h, 056h   ; cmp dword ptr [ebx + 0x1c], 0x56525347
        db 075h, 005h   ; jne 0x3566b2
        db 06Ah, 00Ch   ; push 0xc
        db 058h   ; pop eax
        db 0EBh, 002h   ; jmp 0x3566b4
$L_3566b2:
        db 033h, 0C0h   ; xor eax, eax
$L_3566b4:
        db 08Bh, 08Bh, 094h, 000h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x94]
        db 068h, 0ECh, 001h, 000h, 000h   ; push 0x1ec
        db 08Dh, 095h, 014h, 0FEh, 0FFh, 0FFh   ; lea edx, [ebp - 0x1ec]
        db 052h   ; push edx
        db 040h   ; inc eax
        db 050h   ; push eax
        db 051h   ; push ecx
        call _XNetLoadConfigSector@16   ; 0x3794D9
        db 085h, 0C0h   ; test eax, eax
        db 074h, 029h   ; je 0x3566fb
        db 06Ah, 01Ch   ; push 0x1c
        db 08Dh, 043h, 024h   ; lea eax, [ebx + 0x24]
        db 059h   ; pop ecx
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Dh, 0B5h, 014h, 0FEh, 0FFh, 0FFh   ; lea esi, [ebp - 0x1ec]
        db 068h   ; push 0x538dc8
        dd _unk_538DC8
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?VerifyOnlineUserSignature@CXo@@IAEHPAU_XC_ONLINE_USER_ACCOUNT_STRUCT@@PAE@Z   ; 0x356F94
        db 085h, 0C0h   ; test eax, eax
        db 075h, 008h   ; jne 0x3566fb
        db 06Ah, 01Bh   ; push 0x1b
        db 059h   ; pop ecx
        db 08Dh, 07Bh, 024h   ; lea edi, [ebx + 0x24]
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
$L_3566fb:
        db 08Dh, 083h, 0A0h, 000h, 000h, 000h   ; lea eax, [ebx + 0xa0]
        db 050h   ; push eax
        call ?KRB5_Module_Startup@@YGXPAUtagASN1module_t@@@Z   ; 0x36369B
        db 053h   ; push ebx
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?XnSetXoBase@CXoBase@@QAEXPAV1@@Z   ; 0x37941C
        db 0C7h, 003h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebx], 1
        db 033h, 0C0h   ; xor eax, eax
$L_356717:
        db 05Fh   ; pop edi
$L_356718:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4

seg8 ENDS

seg9 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: _XoUpdateLaunchNewImageInternal@16 @ 0x00356A2D
PUBLIC _XoUpdateLaunchNewImageInternal@16
_XoUpdateLaunchNewImageInternal@16:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 081h, 0ECh, 0F0h, 002h, 000h, 000h   ; sub esp, 0x2f0
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 033h, 0C9h   ; xor ecx, ecx
        db 03Bh, 0F1h   ; cmp esi, ecx
        db 057h   ; push edi
        db 00Fh, 085h, 089h, 001h, 000h, 000h   ; jne 0x356bcf
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 03Bh, 0D9h   ; cmp ebx, ecx
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 00Fh, 084h, 031h, 001h, 000h, 000h   ; je 0x356b85
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 083h, 0F8h, 005h   ; cmp eax, 5
        db 00Fh, 086h, 058h, 001h, 000h, 000h   ; jbe 0x356bb7
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 072h, 00Bh   ; jb 0x356a71
        db 03Dh, 000h, 000h, 001h, 000h   ; cmp eax, 0x10000
        db 00Fh, 082h, 046h, 001h, 000h, 000h   ; jb 0x356bb7
$L_356a71:
        db 033h, 0C0h   ; xor eax, eax
        db 0B9h, 0F9h, 002h, 000h, 000h   ; mov ecx, 0x2f9
        db 08Dh, 07Bh, 01Ch   ; lea edi, [ebx + 0x1c]
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 083h, 03Bh, 008h   ; cmp dword ptr [ebx], 8
        db 075h, 01Bh   ; jne 0x356a9d
        db 0C7h, 043h, 010h, 0FCh, 009h, 000h, 000h   ; mov dword ptr [ebx + 0x10], 0x9fc
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x508290]
        dd ?g_pXo@@3PAVCXo@@A
        db 081h, 0C3h, 0FCh, 009h, 000h, 000h   ; add ebx, 0x9fc
        db 053h   ; push ebx
        call ?XOnlineSaveLogonState@CXo@@QAEJPAU_XONLINE_LOGON_STATE@@@Z   ; 0x3576A7
        db 0EBh, 004h   ; jmp 0x356aa1
$L_356a9d:
        db 083h, 063h, 010h, 000h   ; and dword ptr [ebx + 0x10], 0
$L_356aa1:
        db 0A1h, 018h, 001h, 001h, 000h   ; mov eax, dword ptr [0x10118]
        db 083h, 065h, 0FCh, 000h   ; and dword ptr [ebp - 4], 0
        db 081h, 0B8h, 0D4h, 001h, 000h, 000h, 047h, 053h, 052h, 056h   ; cmp dword ptr [eax + 0x1d4], 0x56525347
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x3cd33c]
        dd __imp__RtlInitAnsiString@8
        db 08Bh, 01Dh   ; mov ebx, dword ptr [0x3cd3d4]
        dd __imp__NtOpenFile@24
        db 074h, 05Dh   ; je 0x356b1f
        db 0F6h, 045h, 010h, 001h   ; test byte ptr [ebp + 0x10], 1
        db 074h, 008h   ; je 0x356ad0
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        call _XapipUpdateDashIfNecessary@4   ; 0x22F934
$L_356ad0:
        db 068h   ; push 0x538e60
        dd _unk_538E60
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 050h   ; push eax
        db 0FFh, 0D7h   ; call edi
        db 083h, 065h, 0F0h, 000h   ; and dword ptr [ebp - 0x10], 0
        db 06Ah, 010h   ; push 0x10
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 06Ah, 001h   ; push 1
        db 08Dh, 045h, 0E0h   ; lea eax, [ebp - 0x20]
        db 050h   ; push eax
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 068h, 000h, 000h, 010h, 080h   ; push 0x80100000
        db 08Dh, 045h, 014h   ; lea eax, [ebp + 0x14]
        db 050h   ; push eax
        db 0C7h, 045h, 0F8h, 040h, 000h, 000h, 000h   ; mov dword ptr [ebp - 8], 0x40
        db 0FFh, 0D3h   ; call ebx
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        db 07Ch, 015h   ; jl 0x356b1f
        db 0FFh, 075h, 014h   ; push dword ptr [ebp + 0x14]
        db 0BEh   ; mov esi, 0x538e50
        dd _unk_538E50
        db 0C7h, 045h, 008h   ; mov dword ptr [ebp + 8], 0x538e2c
        dd _unk_538E2C
        db 0FFh, 015h   ; call dword ptr [0x3cd388]
        dd __imp__NtClose@4
$L_356b1f:
        db 0A1h, 018h, 001h, 001h, 000h   ; mov eax, dword ptr [0x10118]
        db 081h, 0B8h, 0D4h, 001h, 000h, 000h, 047h, 053h, 052h, 056h   ; cmp dword ptr [eax + 0x1d4], 0x56525347
        db 074h, 006h   ; je 0x356b36
        db 083h, 07Dh, 0FCh, 000h   ; cmp dword ptr [ebp - 4], 0
        db 07Dh, 04Ch   ; jge 0x356b82
$L_356b36:
        db 068h   ; push 0x538e04
        dd _unk_538E04
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 050h   ; push eax
        db 0FFh, 0D7h   ; call edi
        db 083h, 065h, 0F0h, 000h   ; and dword ptr [ebp - 0x10], 0
        db 06Ah, 010h   ; push 0x10
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 06Ah, 001h   ; push 1
        db 08Dh, 045h, 0E0h   ; lea eax, [ebp - 0x20]
        db 050h   ; push eax
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 068h, 000h, 000h, 010h, 080h   ; push 0x80100000
        db 08Dh, 045h, 014h   ; lea eax, [ebp + 0x14]
        db 050h   ; push eax
        db 0C7h, 045h, 0F8h, 040h, 000h, 000h, 000h   ; mov dword ptr [ebp - 8], 0x40
        db 0FFh, 0D3h   ; call ebx
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 015h   ; jl 0x356b82
        db 0FFh, 075h, 014h   ; push dword ptr [ebp + 0x14]
        db 0BEh   ; mov esi, 0x538e50
        dd _unk_538E50
        db 0C7h, 045h, 008h   ; mov dword ptr [ebp + 8], 0x538dec
        dd _unk_538DEC
        db 0FFh, 015h   ; call dword ptr [0x3cd388]
        dd __imp__NtClose@4
$L_356b82:
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
$L_356b85:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x508290]
        dd ?g_pXo@@3PAVCXo@@A
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 005h   ; je 0x356b94
        call ?_XOnlineCleanupAsyncIO@CXo@@QAEHXZ   ; 0x35671E
$L_356b94:
        db 0A1h, 018h, 001h, 001h, 000h   ; mov eax, dword ptr [0x10118]
        db 053h   ; push ebx
        db 0FFh, 070h, 008h   ; push dword ptr [eax + 8]
        db 033h, 0C0h   ; xor eax, eax
        db 085h, 0DBh   ; test ebx, ebx
        db 00Fh, 095h, 0C0h   ; setne al
        db 08Dh, 044h, 000h, 0FFh   ; lea eax, [eax + eax - 1]
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 056h   ; push esi
        call _XWriteTitleInfoAndRebootA@20   ; 0x22D3C6
        db 0E9h, 06Ch, 001h, 000h, 000h   ; jmp 0x356d23
$L_356bb7:
        db 0A1h, 018h, 001h, 001h, 000h   ; mov eax, dword ptr [0x10118]
        db 081h, 0B8h, 0D4h, 001h, 000h, 000h, 047h, 053h, 052h, 056h   ; cmp dword ptr [eax + 0x1d4], 0x56525347
        db 075h, 0BDh   ; jne 0x356b85
        db 033h, 0F6h   ; xor esi, esi
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 0EBh, 0B6h   ; jmp 0x356b85
$L_356bcf:
        db 0A1h, 018h, 001h, 001h, 000h   ; mov eax, dword ptr [0x10118]
        db 08Bh, 040h, 008h   ; mov eax, dword ptr [eax + 8]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 0BFh, 068h, 001h, 000h, 000h   ; mov edi, 0x168
        db 057h   ; push edi
        db 08Dh, 085h, 010h, 0FDh, 0FFh, 0FFh   ; lea eax, [ebp - 0x2f0]
        db 033h, 0DBh   ; xor ebx, ebx
        db 050h   ; push eax
        db 043h   ; inc ebx
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        call _XapipUpdateGetCurrentDDriveMapping@8   ; 0x22F69F
        db 08Ah, 006h   ; mov al, byte ptr [esi]
        db 03Ch, 044h   ; cmp al, 0x44
        db 0B2h, 05Ch   ; mov dl, 0x5c
        db 074h, 004h   ; je 0x356bfe
        db 03Ch, 064h   ; cmp al, 0x64
        db 075h, 022h   ; jne 0x356c20
$L_356bfe:
        db 080h, 07Eh, 001h, 03Ah   ; cmp byte ptr [esi + 1], 0x3a
        db 075h, 01Ch   ; jne 0x356c20
        db 038h, 056h, 002h   ; cmp byte ptr [esi + 2], dl
        db 075h, 017h   ; jne 0x356c20
        db 08Dh, 046h, 003h   ; lea eax, [esi + 3]
        db 08Bh, 0F0h   ; mov esi, eax
        db 08Dh, 08Dh, 010h, 0FDh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x2f0]
        db 0C7h, 045h, 0FCh, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp - 4], 1
        db 0E9h, 08Eh, 000h, 000h, 000h   ; jmp 0x356cae
$L_356c20:
        db 03Ch, 054h   ; cmp al, 0x54
        db 074h, 004h   ; je 0x356c28
        db 03Ch, 074h   ; cmp al, 0x74
        db 075h, 031h   ; jne 0x356c59
$L_356c28:
        db 080h, 07Eh, 001h, 03Ah   ; cmp byte ptr [esi + 1], 0x3a
        db 075h, 02Bh   ; jne 0x356c59
        db 038h, 056h, 002h   ; cmp byte ptr [esi + 2], dl
        db 075h, 026h   ; jne 0x356c59
        db 080h, 07Eh, 003h, 024h   ; cmp byte ptr [esi + 3], 0x24
        db 075h, 020h   ; jne 0x356c59
        db 08Ah, 04Eh, 004h   ; mov cl, byte ptr [esi + 4]
        db 080h, 0F9h, 055h   ; cmp cl, 0x55
        db 074h, 005h   ; je 0x356c46
        db 080h, 0F9h, 075h   ; cmp cl, 0x75
        db 075h, 013h   ; jne 0x356c59
$L_356c46:
        db 038h, 056h, 005h   ; cmp byte ptr [esi + 5], dl
        db 075h, 00Eh   ; jne 0x356c59
        db 083h, 0C6h, 006h   ; add esi, 6
        db 056h   ; push esi
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 068h   ; push 0x431234
        dd _unk_431234
        db 0EBh, 037h   ; jmp 0x356c90
$L_356c59:
        db 0F6h, 045h, 010h, 002h   ; test byte ptr [ebp + 0x10], 2
        db 00Fh, 084h, 0BDh, 000h, 000h, 000h   ; je 0x356d20
        db 03Ch, 059h   ; cmp al, 0x59
        db 074h, 008h   ; je 0x356c6f
        db 03Ch, 079h   ; cmp al, 0x79
        db 00Fh, 085h, 0B1h, 000h, 000h, 000h   ; jne 0x356d20
$L_356c6f:
        db 080h, 07Eh, 001h, 03Ah   ; cmp byte ptr [esi + 1], 0x3a
        db 00Fh, 085h, 0A7h, 000h, 000h, 000h   ; jne 0x356d20
        db 038h, 056h, 002h   ; cmp byte ptr [esi + 2], dl
        db 00Fh, 085h, 09Eh, 000h, 000h, 000h   ; jne 0x356d20
        db 083h, 0C6h, 003h   ; add esi, 3
        db 056h   ; push esi
        db 068h   ; push 0x431204
        dd _unk_431204
        db 068h   ; push 0x3d8c40
        dd _unk_3D8C40
$L_356c90:
        db 08Dh, 085h, 078h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x188]
        db 057h   ; push edi
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 07Ch   ; jl 0x356d20
        db 033h, 0C9h   ; xor ecx, ecx
        db 08Dh, 085h, 078h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x188]
        db 033h, 0DBh   ; xor ebx, ebx
$L_356cae:
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 074h, 005h   ; je 0x356cb9
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 0EBh, 003h   ; jmp 0x356cbc
$L_356cb9:
        db 083h, 0CAh, 0FFh   ; or edx, 0xffffffff
$L_356cbc:
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 052h   ; push edx
        db 053h   ; push ebx
        db 051h   ; push ecx
        db 050h   ; push eax
        call _XWriteTitleInfoNoReboot@24   ; 0x22D281
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 05Dh, 0FCh   ; cmp dword ptr [ebp - 4], ebx
        db 08Bh, 0F8h   ; mov edi, eax
        db 074h, 005h   ; je 0x356cd9
        db 039h, 05Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ebx
        db 074h, 00Dh   ; je 0x356ce6
$L_356cd9:
        db 056h   ; push esi
        db 08Dh, 085h, 010h, 0FDh, 0FFh, 0FFh   ; lea eax, [ebp - 0x2f0]
        db 050h   ; push eax
        call _XapipUpdateSaveDDriveMappingToLaunchPage@8   ; 0x22F731
$L_356ce6:
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 07Ch, 02Dh   ; jl 0x356d17
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x508290]
        dd ?g_pXo@@3PAVCXo@@A
        db 03Bh, 0CBh   ; cmp ecx, ebx
        db 074h, 005h   ; je 0x356cf9
        call ?_XOnlineCleanupAsyncIO@CXo@@QAEHXZ   ; 0x35671E
$L_356cf9:
        db 064h, 0A1h, 020h, 000h, 000h, 000h   ; mov eax, dword ptr fs:[0x20]
        db 08Bh, 080h, 050h, 002h, 000h, 000h   ; mov eax, dword ptr [eax + 0x250]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 006h   ; je 0x356d0f
        db 053h   ; push ebx
        db 06Ah, 002h   ; push 2
        db 0FFh, 050h, 014h   ; call dword ptr [eax + 0x14]
$L_356d0f:
        db 06Ah, 002h   ; push 2
        db 0FFh, 015h   ; call dword ptr [0x3cd384]
        dd __imp__HalReturnToFirmware@4
$L_356d17:
        db 057h   ; push edi
        db 0FFh, 015h   ; call dword ptr [0x3cd380]
        dd __imp__RtlNtStatusToDosError@4
        db 0EBh, 003h   ; jmp 0x356d23
$L_356d20:
        db 06Ah, 057h   ; push 0x57
        db 058h   ; pop eax
$L_356d23:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 010h, 000h   ; ret 0x10
seg9 ENDS




seg17 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?LogonTaskClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z @ 0x00359DD4
PUBLIC ?LogonTaskClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z
?LogonTaskClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z:
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 056h   ; push esi
        db 057h   ; push edi
        db 033h, 0EDh   ; xor ebp, ebp
        db 055h   ; push ebp
        db 055h   ; push ebp
        db 08Bh, 0F1h   ; mov esi, ecx
        call ?XnLogonGetStatus@CXoBase@@QAEKPAU_SGADDR@@PAK@Z   ; 0x379868
        db 08Bh, 07Ch, 024h, 014h   ; mov edi, dword ptr [esp + 0x14]
        db 06Ah, 0FFh   ; push -1
        db 055h   ; push ebp
        db 08Dh, 047h, 018h   ; lea eax, [edi + 0x18]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnSetEventTimer@CXoBase@@QAEXPAEPAXK@Z   ; 0x379499
        db 089h, 0AEh, 09Ch, 01Bh, 000h, 000h   ; mov dword ptr [esi + 0x1b9c], ebp
        db 08Bh, 047h, 04Ch   ; mov eax, dword ptr [edi + 0x4c]
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 074h, 00Ah   ; je 0x359e0d
        db 050h   ; push eax
        call _closesocket@4   ; 0x376FE0
        db 083h, 04Fh, 04Ch, 0FFh   ; or dword ptr [edi + 0x4c], 0xffffffff
$L_359e0d:
        db 08Bh, 047h, 054h   ; mov eax, dword ptr [edi + 0x54]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e1c
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
$L_359e1c:
        db 08Bh, 047h, 050h   ; mov eax, dword ptr [edi + 0x50]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 00Dh   ; je 0x359e30
        db 068h, 043h, 080h, 000h, 000h   ; push 0x8043
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?SysFree@CXo@@IAEXPAXK@Z   ; 0x36990B
$L_359e30:
        db 08Bh, 047h, 058h   ; mov eax, dword ptr [edi + 0x58]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e3f
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
$L_359e3f:
        db 08Bh, 047h, 05Ch   ; mov eax, dword ptr [edi + 0x5c]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e4e
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
$L_359e4e:
        db 08Bh, 087h, 0A8h, 000h, 000h, 000h   ; mov eax, dword ptr [edi + 0xa8]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e60
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
$L_359e60:
        db 08Bh, 087h, 0B4h, 000h, 000h, 000h   ; mov eax, dword ptr [edi + 0xb4]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e72
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
$L_359e72:
        db 08Bh, 047h, 060h   ; mov eax, dword ptr [edi + 0x60]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e81
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
$L_359e81:
        db 08Bh, 087h, 0ACh, 000h, 000h, 000h   ; mov eax, dword ptr [edi + 0xac]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359e93
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
$L_359e93:
        db 057h   ; push edi
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?RevertLogonState@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z   ; 0x357590
        db 039h, 0BEh, 0C8h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xc8], edi
        db 00Fh, 085h, 090h, 000h, 000h, 000h   ; jne 0x359f37
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?CloseCombinedTicketCache@CXo@@IAEXXZ   ; 0x357813
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?CloseServiceTicketCache@CXo@@IAEXXZ   ; 0x357850
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?NotificationTerm@CXo@@IAEXXZ   ; 0x35E3C6
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnLogoff@CXoBase@@QAEXXZ   ; 0x37948E
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 0AEh, 0A8h, 005h, 000h, 000h   ; cmp dword ptr [esi + 0x5a8], ebp
        db 089h, 0AEh, 0D0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd0], ebp
        db 089h, 0AEh, 0B8h, 006h, 000h, 000h   ; mov dword ptr [esi + 0x6b8], ebp
        db 076h, 01Dh   ; jbe 0x359ef6
        db 08Dh, 0BEh, 0ACh, 005h, 000h, 000h   ; lea edi, [esi + 0x5ac]
$L_359edf:
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
        db 089h, 02Fh   ; mov dword ptr [edi], ebp
        db 043h   ; inc ebx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 03Bh, 09Eh, 0A8h, 005h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0x5a8]
        db 072h, 0E9h   ; jb 0x359edf
$L_359ef6:
        db 06Ah, 050h   ; push 0x50
        db 033h, 0C0h   ; xor eax, eax
        db 059h   ; pop ecx
        db 08Dh, 0BEh, 0D4h, 000h, 000h, 000h   ; lea edi, [esi + 0xd4]
        db 089h, 0AEh, 0A8h, 005h, 000h, 000h   ; mov dword ptr [esi + 0x5a8], ebp
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 08Dh, 0BEh, 0C0h, 000h, 000h, 000h   ; lea edi, [esi + 0xc0]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 03Bh, 0C5h   ; cmp eax, ebp
        db 074h, 008h   ; je 0x359f1d
        db 050h   ; push eax
        call _CloseHandle@4   ; 0x22D40D
        db 089h, 02Fh   ; mov dword ptr [edi], ebp
$L_359f1d:
        db 068h, 01Ah, 080h, 000h, 000h   ; push 0x801a
        db 0FFh, 0B6h, 0C8h, 000h, 000h, 000h   ; push dword ptr [esi + 0xc8]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?SysFree@CXo@@IAEXPAXK@Z   ; 0x36990B
        db 089h, 0AEh, 0C8h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc8], ebp
        db 0EBh, 01Bh   ; jmp 0x359f52
$L_359f37:
        db 08Dh, 09Eh, 0CCh, 000h, 000h, 000h   ; lea ebx, [esi + 0xcc]
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 075h, 00Fh   ; jne 0x359f52
        db 068h, 01Ah, 080h, 000h, 000h   ; push 0x801a
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?SysFree@CXo@@IAEXPAXK@Z   ; 0x36990B
        db 089h, 02Bh   ; mov dword ptr [ebx], ebp
$L_359f52:
        db 05Fh   ; pop edi
        db 089h, 0AEh, 0C4h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc4], ebp
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 0C2h, 004h, 000h   ; ret 4
seg17 ENDS

seg18 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?LogonTaskContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z @ 0x0035A107
PUBLIC ?LogonTaskContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z
?LogonTaskContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:
        db 055h   ; push ebp
        db 08Dh, 06Ch, 024h, 08Ch   ; lea ebp, [esp - 0x74]
        db 081h, 0ECh, 0E0h, 000h, 000h, 000h   ; sub esp, 0xe0
        db 053h   ; push ebx
        db 08Bh, 05Dh, 07Ch   ; mov ebx, dword ptr [ebp + 0x7c]
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 039h, 09Eh, 0C8h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xc8], ebx
        db 057h   ; push edi
        db 089h, 075h, 070h   ; mov dword ptr [ebp + 0x70], esi
        db 00Fh, 085h, 0C3h, 001h, 000h, 000h   ; jne 0x35a2ec
        db 08Bh, 08Eh, 0B0h, 00Ch, 000h, 000h   ; mov ecx, dword ptr [esi + 0xcb0]
        db 033h, 0FFh   ; xor edi, edi
        db 047h   ; inc edi
        db 033h, 0C0h   ; xor eax, eax
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 074h, 00Ah   ; je 0x35a142
        db 083h, 0F9h, 003h   ; cmp ecx, 3
        db 074h, 005h   ; je 0x35a142
        db 083h, 0F9h, 005h   ; cmp ecx, 5
        db 075h, 04Ah   ; jne 0x35a18c
$L_35a142:
        db 0FFh, 0B6h, 0ACh, 00Ch, 000h, 000h   ; push dword ptr [esi + 0xcac]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E16   ; 0x356E16
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 075h, 036h   ; jne 0x35a18c
        db 08Bh, 08Eh, 0B0h, 00Ch, 000h, 000h   ; mov ecx, dword ptr [esi + 0xcb0]
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 075h, 00Ch   ; jne 0x35a16c
        db 0C7h, 086h, 0B0h, 00Ch, 000h, 000h, 002h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xcb0], 2
        db 0EBh, 020h   ; jmp 0x35a18c
$L_35a16c:
        db 083h, 0F9h, 003h   ; cmp ecx, 3
        db 075h, 00Ch   ; jne 0x35a17d
        db 0C7h, 086h, 0B0h, 00Ch, 000h, 000h, 004h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xcb0], 4
        db 0EBh, 00Fh   ; jmp 0x35a18c
$L_35a17d:
        db 083h, 0F9h, 005h   ; cmp ecx, 5
        db 075h, 00Ah   ; jne 0x35a18c
        db 0C7h, 086h, 0B0h, 00Ch, 000h, 000h, 006h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xcb0], 6
$L_35a18c:
        db 083h, 0BEh, 0B4h, 00Ch, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xcb4], 0
        db 074h, 03Eh   ; je 0x35a1d3
        db 083h, 07Bh, 014h, 00Fh   ; cmp dword ptr [ebx + 0x14], 0xf
        db 072h, 038h   ; jb 0x35a1d3
        db 08Bh, 08Eh, 0B0h, 00Ch, 000h, 000h   ; mov ecx, dword ptr [esi + 0xcb0]
        db 083h, 0F9h, 002h   ; cmp ecx, 2
        db 074h, 005h   ; je 0x35a1ab
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 075h, 028h   ; jne 0x35a1d3
$L_35a1ab:
        db 0FFh, 0B6h, 0ACh, 00Ch, 000h, 000h   ; push dword ptr [esi + 0xcac]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 0B6h, 0A8h, 00Ch, 000h, 000h   ; push dword ptr [esi + 0xca8]
        call ?CacheIndexFlush@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@@Z   ; 0x367DB7
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 00Ah   ; jl 0x35a1cc
        db 0C7h, 086h, 0B0h, 00Ch, 000h, 000h, 005h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xcb0], 5
$L_35a1cc:
        db 083h, 0A6h, 0B4h, 00Ch, 000h, 000h, 000h   ; and dword ptr [esi + 0xcb4], 0
$L_35a1d3:
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 007h   ; jge 0x35a1de
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?CloseServiceTicketCache@CXo@@IAEXXZ   ; 0x357850
$L_35a1de:
        db 08Bh, 08Eh, 038h, 007h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x738]
        db 033h, 0C0h   ; xor eax, eax
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 074h, 00Ah   ; je 0x35a1f4
        db 083h, 0F9h, 003h   ; cmp ecx, 3
        db 074h, 005h   ; je 0x35a1f4
        db 083h, 0F9h, 005h   ; cmp ecx, 5
        db 075h, 04Ah   ; jne 0x35a23e
$L_35a1f4:
        db 0FFh, 0B6h, 034h, 007h, 000h, 000h   ; push dword ptr [esi + 0x734]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E16   ; 0x356E16
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 075h, 036h   ; jne 0x35a23e
        db 08Bh, 08Eh, 038h, 007h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x738]
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 075h, 00Ch   ; jne 0x35a21e
        db 0C7h, 086h, 038h, 007h, 000h, 000h, 002h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x738], 2
        db 0EBh, 020h   ; jmp 0x35a23e
$L_35a21e:
        db 083h, 0F9h, 003h   ; cmp ecx, 3
        db 075h, 00Ch   ; jne 0x35a22f
        db 0C7h, 086h, 038h, 007h, 000h, 000h, 004h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x738], 4
        db 0EBh, 00Fh   ; jmp 0x35a23e
$L_35a22f:
        db 083h, 0F9h, 005h   ; cmp ecx, 5
        db 075h, 00Ah   ; jne 0x35a23e
        db 0C7h, 086h, 038h, 007h, 000h, 000h, 006h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x738], 6
$L_35a23e:
        db 083h, 0BEh, 03Ch, 007h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x73c], 0
        db 074h, 03Eh   ; je 0x35a285
        db 083h, 07Bh, 014h, 00Fh   ; cmp dword ptr [ebx + 0x14], 0xf
        db 072h, 038h   ; jb 0x35a285
        db 08Bh, 08Eh, 038h, 007h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x738]
        db 083h, 0F9h, 002h   ; cmp ecx, 2
        db 074h, 005h   ; je 0x35a25d
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 075h, 028h   ; jne 0x35a285
$L_35a25d:
        db 0FFh, 0B6h, 034h, 007h, 000h, 000h   ; push dword ptr [esi + 0x734]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 0B6h, 030h, 007h, 000h, 000h   ; push dword ptr [esi + 0x730]
        call ?CacheIndexFlush@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@@Z   ; 0x367DB7
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 00Ah   ; jl 0x35a27e
        db 0C7h, 086h, 038h, 007h, 000h, 000h, 005h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x738], 5
$L_35a27e:
        db 083h, 0A6h, 03Ch, 007h, 000h, 000h, 000h   ; and dword ptr [esi + 0x73c], 0
$L_35a285:
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 007h   ; jge 0x35a290
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?CloseCombinedTicketCache@CXo@@IAEXXZ   ; 0x357813
$L_35a290:
        db 08Bh, 043h, 054h   ; mov eax, dword ptr [ebx + 0x54]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 055h   ; je 0x35a2ec
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?ConfigureUPnPNatContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z   ; 0x370400
        db 085h, 0C0h   ; test eax, eax
        db 074h, 049h   ; je 0x35a2ec
        db 08Dh, 045h, 064h   ; lea eax, [ebp + 0x64]
        db 050h   ; push eax
        db 0FFh, 073h, 054h   ; push dword ptr [ebx + 0x54]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?ConfigureUPnPNatGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAG@Z   ; 0x36F58B
        db 0FFh, 073h, 054h   ; push dword ptr [ebx + 0x54]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 08Bh, 0F8h   ; mov edi, eax
        call ?ConfigureUPnPNatClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z   ; 0x36FDB9
        db 083h, 063h, 054h, 000h   ; and dword ptr [ebx + 0x54], 0
        db 068h, 043h, 080h, 000h, 000h   ; push 0x8043
        db 0FFh, 073h, 050h   ; push dword ptr [ebx + 0x50]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?SysFree@CXo@@IAEXPAXK@Z   ; 0x36990B
        db 083h, 063h, 050h, 000h   ; and dword ptr [ebx + 0x50], 0
        db 081h, 0FFh, 0F0h, 000h, 015h, 000h   ; cmp edi, 0x1500f0
        db 074h, 008h   ; je 0x35a2e4
        db 081h, 0FFh, 017h, 019h, 015h, 080h   ; cmp edi, 0x80151917
        db 075h, 008h   ; jne 0x35a2ec
$L_35a2e4:
        db 0FFh, 075h, 064h   ; push dword ptr [ebp + 0x64]
        call _XNetConfigUPnP   ; 0x3797E3
$L_35a2ec:
        db 08Bh, 08Eh, 02Ch, 007h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x72c]
        db 083h, 0F9h, 008h   ; cmp ecx, 8
        db 00Fh, 084h, 016h, 001h, 000h, 000h   ; je 0x35a411
        db 033h, 0C0h   ; xor eax, eax
        db 083h, 0F9h, 001h   ; cmp ecx, 1
        db 074h, 005h   ; je 0x35a307
        db 083h, 0F9h, 005h   ; cmp ecx, 5
        db 075h, 03Ah   ; jne 0x35a341
$L_35a307:
        db 0FFh, 0B6h, 028h, 007h, 000h, 000h   ; push dword ptr [esi + 0x728]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E16   ; 0x356E16
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 075h, 026h   ; jne 0x35a341
        db 08Bh, 08Eh, 02Ch, 007h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x72c]
        db 083h, 0F9h, 001h   ; cmp ecx, 1
        db 075h, 00Ch   ; jne 0x35a332
        db 0C7h, 086h, 02Ch, 007h, 000h, 000h, 002h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x72c], 2
        db 0EBh, 00Fh   ; jmp 0x35a341
$L_35a332:
        db 083h, 0F9h, 005h   ; cmp ecx, 5
        db 075h, 00Ah   ; jne 0x35a341
        db 0C7h, 086h, 02Ch, 007h, 000h, 000h, 006h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x72c], 6
$L_35a341:
        db 083h, 0BBh, 0B0h, 000h, 000h, 000h, 000h   ; cmp dword ptr [ebx + 0xb0], 0
        db 00Fh, 085h, 0B8h, 000h, 000h, 000h   ; jne 0x35a406
        db 08Bh, 08Eh, 02Ch, 007h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x72c]
        db 083h, 0F9h, 002h   ; cmp ecx, 2
        db 074h, 009h   ; je 0x35a362
        db 083h, 0F9h, 006h   ; cmp ecx, 6
        db 00Fh, 085h, 0A4h, 000h, 000h, 000h   ; jne 0x35a406
$L_35a362:
        db 06Ah, 006h   ; push 6
        db 059h   ; pop ecx
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 07Dh, 034h   ; lea edi, [ebp + 0x34]
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 08Dh, 045h, 03Ch   ; lea eax, [ebp + 0x3c]
        db 050h   ; push eax
        call _GetSystemTimeAsFileTime@4   ; 0x22F25F
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35a379:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 003h, 0C3h   ; add eax, ebx
        db 08Bh, 088h, 0CCh, 000h, 000h, 000h   ; mov ecx, dword ptr [eax + 0xcc]
        db 08Bh, 090h, 0D0h, 000h, 000h, 000h   ; mov edx, dword ptr [eax + 0xd0]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 00Bh, 0FAh   ; or edi, edx
        db 074h, 03Fh   ; je 0x35a3d2
        db 0F6h, 080h, 0D4h, 000h, 000h, 000h, 003h   ; test byte ptr [eax + 0xd4], 3
        db 075h, 036h   ; jne 0x35a3d2
        db 06Ah, 000h   ; push 0
        db 06Ah, 000h   ; push 0
        db 08Dh, 045h, 034h   ; lea eax, [ebp + 0x34]
        db 050h   ; push eax
        db 0FFh, 0B6h, 028h, 007h, 000h, 000h   ; push dword ptr [esi + 0x728]
        db 089h, 04Dh, 034h   ; mov dword ptr [ebp + 0x34], ecx
        db 0FFh, 0B6h, 024h, 007h, 000h, 000h   ; push dword ptr [esi + 0x724]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 055h, 038h   ; mov dword ptr [ebp + 0x38], edx
        call ?CacheUpdate@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@PAE2H@Z   ; 0x368A5A
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 011h   ; jl 0x35a3d2
$L_35a3c1:
        db 0FFh, 0B6h, 028h, 007h, 000h, 000h   ; push dword ptr [esi + 0x728]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E16   ; 0x356E16
        db 085h, 0C0h   ; test eax, eax
        db 074h, 0EFh   ; je 0x35a3c1
$L_35a3d2:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 09Eh   ; jb 0x35a379
        db 0FFh, 0B6h, 028h, 007h, 000h, 000h   ; push dword ptr [esi + 0x728]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 0B6h, 024h, 007h, 000h, 000h   ; push dword ptr [esi + 0x724]
        call ?CacheIndexFlush@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@@Z   ; 0x367DB7
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 00Ah   ; jl 0x35a3fc
        db 0C7h, 086h, 02Ch, 007h, 000h, 000h, 005h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x72c], 5
$L_35a3fc:
        db 0C7h, 083h, 0B0h, 000h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0xb0], 1
$L_35a406:
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 007h   ; jge 0x35a411
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?CloseLogonTimeCache@CXo@@IAEXXZ   ; 0x3577D6
$L_35a411:
        db 08Bh, 043h, 014h   ; mov eax, dword ptr [ebx + 0x14]
        db 083h, 0F8h, 001h   ; cmp eax, 1
        db 076h, 01Bh   ; jbe 0x35a434
        db 083h, 0F8h, 063h   ; cmp eax, 0x63
        db 073h, 016h   ; jae 0x35a434
        call _GetTickCount@0   ; 0x22D120
        db 03Bh, 043h, 02Ch   ; cmp eax, dword ptr [ebx + 0x2c]
        db 072h, 00Ch   ; jb 0x35a434
        db 0C7h, 043h, 010h, 011h, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151911
        db 0E9h, 092h, 004h, 000h, 000h   ; jmp 0x35a8c6
$L_35a434:
        db 033h, 0FFh   ; xor edi, edi
$L_35a436:
        db 08Bh, 043h, 014h   ; mov eax, dword ptr [ebx + 0x14]
        db 083h, 0F8h, 00Fh   ; cmp eax, 0xf
        db 089h, 07Dh, 068h   ; mov dword ptr [ebp + 0x68], edi
        db 00Fh, 087h, 012h, 00Ch, 000h, 000h   ; ja 0x35b057
        db 00Fh, 084h, 04Fh, 007h, 000h, 000h   ; je 0x35ab9a
        db 048h   ; dec eax
        db 00Fh, 084h, 0C5h, 006h, 000h, 000h   ; je 0x35ab17
        db 083h, 0E8h, 008h   ; sub eax, 8
        db 00Fh, 084h, 066h, 006h, 000h, 000h   ; je 0x35aac1
        db 048h   ; dec eax
        db 00Fh, 084h, 07Fh, 006h, 000h, 000h   ; je 0x35aae1
        db 048h   ; dec eax
        db 00Fh, 084h, 091h, 005h, 000h, 000h   ; je 0x35a9fa
        db 048h   ; dec eax
        db 00Fh, 084h, 0AEh, 005h, 000h, 000h   ; je 0x35aa1e
        db 048h   ; dec eax
        db 074h, 009h   ; je 0x35a47c
        db 048h   ; dec eax
        db 00Fh, 085h, 04Ch, 004h, 000h, 000h   ; jne 0x35a8c6
        db 0EBh, 076h   ; jmp 0x35a4f2
$L_35a47c:
        db 039h, 07Bh, 040h   ; cmp dword ptr [ebx + 0x40], edi
        db 075h, 00Eh   ; jne 0x35a48f
        db 039h, 07Bh, 060h   ; cmp dword ptr [ebx + 0x60], edi
        db 075h, 009h   ; jne 0x35a48f
$L_35a486:
        db 0C7h, 043h, 014h, 00Bh, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xb
        db 0EBh, 0A7h   ; jmp 0x35a436
$L_35a48f:
        db 089h, 0BBh, 0A4h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0xa4], edi
        db 089h, 07Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], edi
$L_35a498:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Dh, 004h, 080h   ; lea eax, [eax + eax*4]
        db 08Bh, 084h, 083h, 08Ch, 002h, 000h, 000h   ; mov eax, dword ptr [ebx + eax*4 + 0x28c]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 074h, 010h   ; je 0x35a4b9
        db 08Bh, 08Bh, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0xa4]
        db 089h, 044h, 08Bh, 064h   ; mov dword ptr [ebx + ecx*4 + 0x64], eax
        db 0FFh, 083h, 0A4h, 000h, 000h, 000h   ; inc dword ptr [ebx + 0xa4]
$L_35a4b9:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 010h   ; cmp dword ptr [ebp + 0x7c], 0x10
        db 072h, 0D6h   ; jb 0x35a498
        db 08Dh, 083h, 0A8h, 000h, 000h, 000h   ; lea eax, [ebx + 0xa8]
        db 050h   ; push eax
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Dh, 043h, 064h   ; lea eax, [ebx + 0x64]
        db 0FFh, 073h, 040h   ; push dword ptr [ebx + 0x40]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 0B3h, 0A4h, 000h, 000h, 000h   ; push dword ptr [ebx + 0xa4]
        db 050h   ; push eax
        db 0FFh, 073h, 060h   ; push dword ptr [ebx + 0x60]
        call ?GetServiceTicket@CXo@@IAEJPAUXKERB_TGT_CONTEXT@@PBKKHPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x359B41
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 041h, 011h, 000h, 000h   ; jl 0x35b62c
        db 0C7h, 043h, 014h, 00Eh, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xe
$L_35a4f2:
        db 08Dh, 0BBh, 0A8h, 000h, 000h, 000h   ; lea edi, [ebx + 0xa8]
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?GetServiceTicketContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z   ; 0x3592F1
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 00Fh, 085h, 049h, 004h, 000h, 000h   ; jne 0x35a955
        db 08Dh, 04Dh, 064h   ; lea ecx, [ebp + 0x64]
        db 051h   ; push ecx
        db 08Dh, 083h, 0ACh, 000h, 000h, 000h   ; lea eax, [ebx + 0xac]
        db 050h   ; push eax
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?GetServiceTicketGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAPAUXKERB_SERVICE_CONTEXT@@PAH@Z   ; 0x357558
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 08Bh, 083h, 0ACh, 000h, 000h, 000h   ; mov eax, dword ptr [ebx + 0xac]
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
        db 083h, 0A3h, 0A4h, 000h, 000h, 000h, 000h   ; and dword ptr [ebx + 0xa4], 0
        db 083h, 078h, 030h, 00Ch   ; cmp dword ptr [eax + 0x30], 0xc
        db 00Fh, 087h, 0B3h, 000h, 000h, 000h   ; ja 0x35a5f6
        db 033h, 0F6h   ; xor esi, esi
        db 089h, 075h, 07Ch   ; mov dword ptr [ebp + 0x7c], esi
        db 039h, 070h, 030h   ; cmp dword ptr [eax + 0x30], esi
        db 00Fh, 086h, 0CEh, 001h, 000h, 000h   ; jbe 0x35a71f
$L_35a551:
        db 08Bh, 093h, 0ACh, 000h, 000h, 000h   ; mov edx, dword ptr [ebx + 0xac]
        db 08Bh, 07Ch, 0B2h, 034h   ; mov edi, dword ptr [edx + esi*4 + 0x34]
        db 033h, 0C9h   ; xor ecx, ecx
        db 08Dh, 083h, 08Ch, 002h, 000h, 000h   ; lea eax, [ebx + 0x28c]
$L_35a563:
        db 039h, 038h   ; cmp dword ptr [eax], edi
        db 074h, 00Ch   ; je 0x35a573
        db 041h   ; inc ecx
        db 083h, 0C0h, 014h   ; add eax, 0x14
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 07Ch, 0F3h   ; jl 0x35a563
        db 083h, 0C9h, 0FFh   ; or ecx, 0xffffffff
$L_35a573:
        db 08Bh, 094h, 0B2h, 000h, 002h, 000h, 000h   ; mov edx, dword ptr [edx + esi*4 + 0x200]
        db 083h, 0FAh, 001h   ; cmp edx, 1
        db 08Dh, 004h, 089h   ; lea eax, [ecx + ecx*4]
        db 08Dh, 004h, 083h   ; lea eax, [ebx + eax*4]
        db 089h, 090h, 098h, 002h, 000h, 000h   ; mov dword ptr [eax + 0x298], edx
        db 075h, 018h   ; jne 0x35a5a3
        db 08Bh, 08Bh, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0xa4]
        db 08Bh, 080h, 08Ch, 002h, 000h, 000h   ; mov eax, dword ptr [eax + 0x28c]
        db 089h, 044h, 08Bh, 064h   ; mov dword ptr [ebx + ecx*4 + 0x64], eax
        db 0FFh, 083h, 0A4h, 000h, 000h, 000h   ; inc dword ptr [ebx + 0xa4]
        db 0EBh, 038h   ; jmp 0x35a5db
$L_35a5a3:
        db 085h, 0D2h   ; test edx, edx
        db 075h, 034h   ; jne 0x35a5db
        db 08Bh, 07Dh, 07Ch   ; mov edi, dword ptr [ebp + 0x7c]
        db 08Dh, 093h, 0ACh, 000h, 000h, 000h   ; lea edx, [ebx + 0xac]
        db 08Bh, 032h   ; mov esi, dword ptr [edx]
        db 066h, 08Bh, 0B4h, 07Eh, 030h, 002h, 000h, 000h   ; mov si, word ptr [esi + edi*2 + 0x230]
        db 08Dh, 08Ch, 089h, 0A5h, 000h, 000h, 000h   ; lea ecx, [ecx + ecx*4 + 0xa5]
        db 066h, 089h, 034h, 08Bh   ; mov word ptr [ebx + ecx*4], si
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 08Bh, 089h, 0B8h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x1b8]
        db 089h, 088h, 090h, 002h, 000h, 000h   ; mov dword ptr [eax + 0x290], ecx
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 089h, 088h, 09Ch, 002h, 000h, 000h   ; mov dword ptr [eax + 0x29c], ecx
$L_35a5db:
        db 08Bh, 075h, 07Ch   ; mov esi, dword ptr [ebp + 0x7c]
        db 08Bh, 083h, 0ACh, 000h, 000h, 000h   ; mov eax, dword ptr [ebx + 0xac]
        db 046h   ; inc esi
        db 089h, 075h, 07Ch   ; mov dword ptr [ebp + 0x7c], esi
        db 03Bh, 070h, 030h   ; cmp esi, dword ptr [eax + 0x30]
        db 00Fh, 082h, 060h, 0FFh, 0FFh, 0FFh   ; jb 0x35a551
        db 0E9h, 029h, 001h, 000h, 000h   ; jmp 0x35a71f
$L_35a5f6:
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35a5fa:
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Ah, 04Ch, 008h, 034h   ; mov cl, byte ptr [eax + ecx + 0x34]
        db 084h, 0C9h   ; test cl, cl
        db 074h, 07Ah   ; je 0x35a67f
        db 00Fh, 0B6h, 0F1h   ; movzx esi, cl
        db 033h, 0D2h   ; xor edx, edx
        db 08Dh, 08Bh, 08Ch, 002h, 000h, 000h   ; lea ecx, [ebx + 0x28c]
$L_35a610:
        db 039h, 031h   ; cmp dword ptr [ecx], esi
        db 074h, 00Ch   ; je 0x35a620
        db 042h   ; inc edx
        db 083h, 0C1h, 014h   ; add ecx, 0x14
        db 083h, 0FAh, 010h   ; cmp edx, 0x10
        db 07Ch, 0F3h   ; jl 0x35a610
        db 083h, 0CAh, 0FFh   ; or edx, 0xffffffff
$L_35a620:
        db 08Bh, 075h, 07Ch   ; mov esi, dword ptr [ebp + 0x7c]
        db 08Bh, 0B4h, 0B0h, 000h, 002h, 000h, 000h   ; mov esi, dword ptr [eax + esi*4 + 0x200]
        db 083h, 0FEh, 001h   ; cmp esi, 1
        db 08Dh, 00Ch, 092h   ; lea ecx, [edx + edx*4]
        db 08Dh, 00Ch, 08Bh   ; lea ecx, [ebx + ecx*4]
        db 089h, 0B1h, 098h, 002h, 000h, 000h   ; mov dword ptr [ecx + 0x298], esi
        db 075h, 018h   ; jne 0x35a653
        db 08Bh, 093h, 0A4h, 000h, 000h, 000h   ; mov edx, dword ptr [ebx + 0xa4]
        db 08Bh, 089h, 08Ch, 002h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x28c]
        db 089h, 04Ch, 093h, 064h   ; mov dword ptr [ebx + edx*4 + 0x64], ecx
        db 0FFh, 083h, 0A4h, 000h, 000h, 000h   ; inc dword ptr [ebx + 0xa4]
        db 0EBh, 02Ch   ; jmp 0x35a67f
$L_35a653:
        db 085h, 0F6h   ; test esi, esi
        db 075h, 028h   ; jne 0x35a67f
        db 08Bh, 075h, 07Ch   ; mov esi, dword ptr [ebp + 0x7c]
        db 066h, 08Bh, 0B4h, 070h, 0C0h, 001h, 000h, 000h   ; mov si, word ptr [eax + esi*2 + 0x1c0]
        db 08Dh, 094h, 092h, 0A5h, 000h, 000h, 000h   ; lea edx, [edx + edx*4 + 0xa5]
        db 066h, 089h, 034h, 093h   ; mov word ptr [ebx + edx*4], si
        db 08Bh, 090h, 0B8h, 001h, 000h, 000h   ; mov edx, dword ptr [eax + 0x1b8]
        db 089h, 091h, 090h, 002h, 000h, 000h   ; mov dword ptr [ecx + 0x290], edx
        db 089h, 081h, 09Ch, 002h, 000h, 000h   ; mov dword ptr [ecx + 0x29c], eax
$L_35a67f:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 00Ch   ; cmp dword ptr [ebp + 0x7c], 0xc
        db 00Fh, 082h, 06Eh, 0FFh, 0FFh, 0FFh   ; jb 0x35a5fa
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35a690:
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Bh, 074h, 088h, 054h   ; mov esi, dword ptr [eax + ecx*4 + 0x54]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 077h   ; je 0x35a712
        db 033h, 0D2h   ; xor edx, edx
        db 08Dh, 08Bh, 08Ch, 002h, 000h, 000h   ; lea ecx, [ebx + 0x28c]
$L_35a6a3:
        db 039h, 031h   ; cmp dword ptr [ecx], esi
        db 074h, 00Ch   ; je 0x35a6b3
        db 042h   ; inc edx
        db 083h, 0C1h, 014h   ; add ecx, 0x14
        db 083h, 0FAh, 010h   ; cmp edx, 0x10
        db 07Ch, 0F3h   ; jl 0x35a6a3
        db 083h, 0CAh, 0FFh   ; or edx, 0xffffffff
$L_35a6b3:
        db 08Bh, 075h, 07Ch   ; mov esi, dword ptr [ebp + 0x7c]
        db 08Bh, 0B4h, 0B0h, 030h, 002h, 000h, 000h   ; mov esi, dword ptr [eax + esi*4 + 0x230]
        db 083h, 0FEh, 001h   ; cmp esi, 1
        db 08Dh, 00Ch, 092h   ; lea ecx, [edx + edx*4]
        db 08Dh, 00Ch, 08Bh   ; lea ecx, [ebx + ecx*4]
        db 089h, 0B1h, 098h, 002h, 000h, 000h   ; mov dword ptr [ecx + 0x298], esi
        db 075h, 018h   ; jne 0x35a6e6
        db 08Bh, 093h, 0A4h, 000h, 000h, 000h   ; mov edx, dword ptr [ebx + 0xa4]
        db 08Bh, 089h, 08Ch, 002h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x28c]
        db 089h, 04Ch, 093h, 064h   ; mov dword ptr [ebx + edx*4 + 0x64], ecx
        db 0FFh, 083h, 0A4h, 000h, 000h, 000h   ; inc dword ptr [ebx + 0xa4]
        db 0EBh, 02Ch   ; jmp 0x35a712
$L_35a6e6:
        db 085h, 0F6h   ; test esi, esi
        db 075h, 028h   ; jne 0x35a712
        db 08Bh, 075h, 07Ch   ; mov esi, dword ptr [ebp + 0x7c]
        db 066h, 08Bh, 0B4h, 070h, 0D8h, 001h, 000h, 000h   ; mov si, word ptr [eax + esi*2 + 0x1d8]
        db 08Dh, 094h, 092h, 0A5h, 000h, 000h, 000h   ; lea edx, [edx + edx*4 + 0xa5]
        db 066h, 089h, 034h, 093h   ; mov word ptr [ebx + edx*4], si
        db 08Bh, 090h, 0B8h, 001h, 000h, 000h   ; mov edx, dword ptr [eax + 0x1b8]
        db 089h, 091h, 090h, 002h, 000h, 000h   ; mov dword ptr [ecx + 0x290], edx
        db 089h, 081h, 09Ch, 002h, 000h, 000h   ; mov dword ptr [ecx + 0x29c], eax
$L_35a712:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 00Fh, 082h, 071h, 0FFh, 0FFh, 0FFh   ; jb 0x35a690
$L_35a71f:
        db 08Dh, 093h, 0ACh, 000h, 000h, 000h   ; lea edx, [ebx + 0xac]
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 08Dh, 081h, 0DCh, 000h, 000h, 000h   ; lea eax, [ecx + 0xdc]
        db 08Dh, 0B1h, 0B8h, 002h, 000h, 000h   ; lea esi, [ecx + 0x2b8]
        db 08Dh, 0B8h, 0C0h, 000h, 000h, 000h   ; lea edi, [eax + 0xc0]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 08Bh, 0CCh, 003h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x3cc]
        db 089h, 088h, 0D0h, 000h, 000h, 000h   ; mov dword ptr [eax + 0xd0], ecx
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 08Bh, 089h, 0DCh, 002h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x2dc]
        db 08Bh, 055h, 070h   ; mov edx, dword ptr [ebp + 0x70]
        db 081h, 0C1h, 018h, 001h, 000h, 000h   ; add ecx, 0x118
        db 089h, 088h, 0D4h, 000h, 000h, 000h   ; mov dword ptr [eax + 0xd4], ecx
        db 03Bh, 09Ah, 0CCh, 000h, 000h, 000h   ; cmp ebx, dword ptr [edx + 0xcc]
        db 089h, 045h, 068h   ; mov dword ptr [ebp + 0x68], eax
        db 075h, 05Eh   ; jne 0x35a7c9
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
$L_35a770:
        db 08Dh, 034h, 089h   ; lea esi, [ecx + ecx*4]
        db 08Bh, 0B4h, 0B2h, 0E4h, 000h, 000h, 000h   ; mov esi, dword ptr [edx + esi*4 + 0xe4]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Eh   ; je 0x35a78c
        db 08Bh, 0B6h, 0ACh, 001h, 000h, 000h   ; mov esi, dword ptr [esi + 0x1ac]
        db 03Bh, 0B0h, 0D0h, 000h, 000h, 000h   ; cmp esi, dword ptr [eax + 0xd0]
        db 074h, 00Bh   ; je 0x35a797
$L_35a78c:
        db 041h   ; inc ecx
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
        db 072h, 0DBh   ; jb 0x35a770
        db 0EBh, 035h   ; jmp 0x35a7cc
$L_35a797:
        db 08Dh, 00Ch, 089h   ; lea ecx, [ecx + ecx*4]
        db 08Bh, 0B4h, 08Ah, 0E4h, 000h, 000h, 000h   ; mov esi, dword ptr [edx + ecx*4 + 0xe4]
        db 06Ah, 018h   ; push 0x18
        db 081h, 0C6h, 0DCh, 000h, 000h, 000h   ; add esi, 0xdc
        db 059h   ; pop ecx
        db 08Bh, 0F8h   ; mov edi, eax
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Dh, 00Ch, 089h   ; lea ecx, [ecx + ecx*4]
        db 08Bh, 0B4h, 08Ah, 0E4h, 000h, 000h, 000h   ; mov esi, dword ptr [edx + ecx*4 + 0xe4]
        db 06Ah, 018h   ; push 0x18
        db 081h, 0C6h, 03Ch, 001h, 000h, 000h   ; add esi, 0x13c
        db 08Dh, 078h, 060h   ; lea edi, [eax + 0x60]
        db 059h   ; pop ecx
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
$L_35a7c9:
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
$L_35a7cc:
        db 03Bh, 09Ah, 0C8h, 000h, 000h, 000h   ; cmp ebx, dword ptr [edx + 0xc8]
        db 074h, 005h   ; je 0x35a7d9
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 075h, 029h   ; jne 0x35a802
$L_35a7d9:
        db 08Bh, 075h, 068h   ; mov esi, dword ptr [ebp + 0x68]
        db 06Ah, 060h   ; push 0x60
        db 056h   ; push esi
        call _XNetRandom@8   ; 0x376F2F
        db 06Ah, 018h   ; push 0x18
        db 068h   ; push 0x389908
        dd _g_abOakleyGroup1ModIntel
        db 056h   ; push esi
        db 068h   ; push 0x389968
        dd _g_abOakleyGroup1BaseIntel
        db 083h, 0C6h, 060h   ; add esi, 0x60
        db 056h   ; push esi
        call _XcModExp@20   ; 0x2FEC7E
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 038h, 00Ch, 000h, 000h   ; je 0x35b43a
$L_35a802:
        db 083h, 065h, 06Ch, 000h   ; and dword ptr [ebp + 0x6c], 0
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35a80a:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 08Dh, 034h, 018h   ; lea esi, [eax + ebx]
        db 08Bh, 096h, 0CCh, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xcc]
        db 08Bh, 0BEh, 0D0h, 000h, 000h, 000h   ; mov edi, dword ptr [esi + 0xd0]
        db 08Bh, 0C2h   ; mov eax, edx
        db 00Bh, 0C7h   ; or eax, edi
        db 074h, 035h   ; je 0x35a85a
        db 08Bh, 083h, 0ACh, 000h, 000h, 000h   ; mov eax, dword ptr [ebx + 0xac]
        db 033h, 0C9h   ; xor ecx, ecx
        db 083h, 0C0h, 008h   ; add eax, 8
$L_35a830:
        db 03Bh, 010h   ; cmp edx, dword ptr [eax]
        db 075h, 005h   ; jne 0x35a839
        db 03Bh, 078h, 004h   ; cmp edi, dword ptr [eax + 4]
        db 074h, 00Bh   ; je 0x35a844
$L_35a839:
        db 041h   ; inc ecx
        db 083h, 0C0h, 008h   ; add eax, 8
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 072h, 0EEh   ; jb 0x35a830
        db 0EBh, 016h   ; jmp 0x35a85a
$L_35a844:
        db 08Ah, 086h, 0D4h, 000h, 000h, 000h   ; mov al, byte ptr [esi + 0xd4]
        db 0C0h, 0E1h, 006h   ; shl cl, 6
        db 024h, 01Fh   ; and al, 0x1f
        db 00Ah, 0C1h   ; or al, cl
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 00Ch, 020h   ; or al, 0x20
        db 088h, 044h, 00Dh, 06Ch   ; mov byte ptr [ebp + ecx + 0x6c], al
$L_35a85a:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0A7h   ; jb 0x35a80a
        db 08Bh, 045h, 06Ch   ; mov eax, dword ptr [ebp + 0x6c]
        db 08Bh, 04Dh, 068h   ; mov ecx, dword ptr [ebp + 0x68]
        db 089h, 081h, 0D8h, 000h, 000h, 000h   ; mov dword ptr [ecx + 0xd8], eax
        db 08Bh, 08Bh, 0CCh, 003h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x3cc]
        db 08Dh, 083h, 0ACh, 000h, 000h, 000h   ; lea eax, [ebx + 0xac]
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 089h, 094h, 08Bh, 0D0h, 003h, 000h, 000h   ; mov dword ptr [ebx + ecx*4 + 0x3d0], edx
        db 083h, 020h, 000h   ; and dword ptr [eax], 0
        db 08Bh, 083h, 0A4h, 000h, 000h, 000h   ; mov eax, dword ptr [ebx + 0xa4]
        db 0FFh, 083h, 0CCh, 003h, 000h, 000h   ; inc dword ptr [ebx + 0x3cc]
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 086h, 0ABh, 000h, 000h, 000h   ; jbe 0x35a946
        db 08Dh, 08Bh, 0A8h, 000h, 000h, 000h   ; lea ecx, [ebx + 0xa8]
        db 051h   ; push ecx
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Bh, 04Dh, 070h   ; mov ecx, dword ptr [ebp + 0x70]
        db 0FFh, 073h, 040h   ; push dword ptr [ebx + 0x40]
        db 050h   ; push eax
        db 08Dh, 043h, 064h   ; lea eax, [ebx + 0x64]
        db 050h   ; push eax
        db 0FFh, 073h, 060h   ; push dword ptr [ebx + 0x60]
        call ?GetServiceTicket@CXo@@IAEJPAUXKERB_TGT_CONTEXT@@PBKKHPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x359B41
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Dh, 08Dh, 000h, 000h, 000h   ; jge 0x35a94d
        db 089h, 043h, 010h   ; mov dword ptr [ebx + 0x10], eax
$L_35a8c3:
        db 08Bh, 075h, 070h   ; mov esi, dword ptr [ebp + 0x70]
$L_35a8c6:
        db 08Bh, 043h, 010h   ; mov eax, dword ptr [ebx + 0x10]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 06Ch   ; je 0x35a939
        db 089h, 043h, 00Ch   ; mov dword ptr [ebx + 0xc], eax
        db 025h, 000h, 0FFh, 0FFh, 0FFh   ; and eax, 0xffffff00
        db 03Dh, 000h, 019h, 015h, 080h   ; cmp eax, 0x80151900
        db 075h, 007h   ; jne 0x35a8e3
        db 0C7h, 043h, 00Ch, 001h, 010h, 015h, 080h   ; mov dword ptr [ebx + 0xc], 0x80151001
$L_35a8e3:
        db 08Dh, 0BBh, 0B4h, 000h, 000h, 000h   ; lea edi, [ebx + 0xb4]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 085h, 0C0h   ; test eax, eax
        db 0C7h, 043h, 014h, 063h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x63
        db 074h, 00Bh   ; je 0x35a901
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
$L_35a901:
        db 08Bh, 043h, 04Ch   ; mov eax, dword ptr [ebx + 0x4c]
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 074h, 00Ah   ; je 0x35a913
        db 050h   ; push eax
        call _closesocket@4   ; 0x376FE0
        db 083h, 04Bh, 04Ch, 0FFh   ; or dword ptr [ebx + 0x4c], 0xffffffff
$L_35a913:
        db 083h, 07Bh, 010h, 000h   ; cmp dword ptr [ebx + 0x10], 0
        db 07Dh, 020h   ; jge 0x35a939
        db 03Bh, 09Eh, 0CCh, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xcc]
        db 075h, 018h   ; jne 0x35a939
        db 08Dh, 086h, 0D0h, 000h, 000h, 000h   ; lea eax, [esi + 0xd0]
        db 08Dh, 08Eh, 0D4h, 003h, 000h, 000h   ; lea ecx, [esi + 0x3d4]
        db 039h, 008h   ; cmp dword ptr [eax], ecx
        db 075h, 008h   ; jne 0x35a939
        db 081h, 0C6h, 014h, 002h, 000h, 000h   ; add esi, 0x214
        db 089h, 030h   ; mov dword ptr [eax], esi
$L_35a939:
        db 08Bh, 043h, 00Ch   ; mov eax, dword ptr [ebx + 0xc]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 083h, 0C5h, 074h   ; add ebp, 0x74
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
$L_35a946:
        db 0C7h, 043h, 014h, 00Fh, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xf
$L_35a94d:
        db 08Bh, 075h, 070h   ; mov esi, dword ptr [ebp + 0x70]
        db 0E9h, 0DFh, 0FAh, 0FFh, 0FFh   ; jmp 0x35a434
$L_35a955:
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Dh, 069h, 0FFh, 0FFh, 0FFh   ; jge 0x35a8c6
        db 03Dh, 00Ch, 019h, 015h, 080h   ; cmp eax, 0x8015190c
        db 075h, 03Bh   ; jne 0x35a99f
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
        db 083h, 07Bh, 03Ch, 000h   ; cmp dword ptr [ebx + 0x3c], 0
        db 075h, 00Ah   ; jne 0x35a980
        db 083h, 07Bh, 038h, 000h   ; cmp dword ptr [ebx + 0x38], 0
        db 00Fh, 084h, 0C6h, 00Ah, 000h, 000h   ; je 0x35b446
$L_35a980:
        db 053h   ; push ebx
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?RevertLogonState@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z   ; 0x357590
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 043h, 038h   ; mov dword ptr [ebx + 0x38], eax
        db 089h, 043h, 03Ch   ; mov dword ptr [ebx + 0x3c], eax
        db 089h, 043h, 040h   ; mov dword ptr [ebx + 0x40], eax
        db 0C7h, 043h, 014h, 009h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 9
        db 0E9h, 095h, 0FAh, 0FFh, 0FFh   ; jmp 0x35a434
$L_35a99f:
        db 03Dh, 016h, 019h, 015h, 080h   ; cmp eax, 0x80151916
        db 075h, 024h   ; jne 0x35a9ca
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
        db 053h   ; push ebx
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?RevertLogonState@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z   ; 0x357590
        db 083h, 063h, 040h, 000h   ; and dword ptr [ebx + 0x40], 0
        db 0C7h, 043h, 014h, 00Bh, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xb
        db 0E9h, 06Ah, 0FAh, 0FFh, 0FFh   ; jmp 0x35a434
$L_35a9ca:
        db 03Dh, 015h, 019h, 015h, 080h   ; cmp eax, 0x80151915
        db 00Fh, 085h, 057h, 00Ch, 000h, 000h   ; jne 0x35b62c
        db 0FFh, 037h   ; push dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
        db 083h, 07Bh, 03Ch, 000h   ; cmp dword ptr [ebx + 0x3c], 0
        db 00Fh, 084h, 06Bh, 00Ah, 000h, 000h   ; je 0x35b456
        db 053h   ; push ebx
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?RevertLogonState@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z   ; 0x357590
        db 033h, 0FFh   ; xor edi, edi
        db 0E9h, 012h, 001h, 000h, 000h   ; jmp 0x35ab0c
$L_35a9fa:
        db 08Dh, 043h, 05Ch   ; lea eax, [ebx + 0x5c]
        db 050h   ; push eax
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Dh, 046h, 024h   ; lea eax, [esi + 0x24]
        db 0FFh, 073h, 03Ch   ; push dword ptr [ebx + 0x3c]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 050h   ; push eax
        call ?GetCombinedTicket@CXo@@IAEJPAU_XC_ONLINE_USER_ACCOUNT_STRUCT@@HPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x359146
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 015h, 00Ch, 000h, 000h   ; jl 0x35b62c
        db 0C7h, 043h, 014h, 00Ch, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xc
$L_35aa1e:
        db 0FFh, 073h, 05Ch   ; push dword ptr [ebx + 0x5c]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?GetCombinedTicketContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z   ; 0x358AB8
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 075h, 03Eh   ; jne 0x35aa6d
        db 08Dh, 07Bh, 060h   ; lea edi, [ebx + 0x60]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 008h   ; je 0x35aa40
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
$L_35aa40:
        db 08Dh, 045h, 064h   ; lea eax, [ebp + 0x64]
        db 050h   ; push eax
        db 057h   ; push edi
        db 0FFh, 073h, 05Ch   ; push dword ptr [ebx + 0x5c]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?GetCombinedTicketGetResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAPAUXKERB_TGT_CONTEXT@@PAH@Z   ; 0x357520
        db 0FFh, 073h, 05Ch   ; push dword ptr [ebx + 0x5c]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 083h, 063h, 05Ch, 000h   ; and dword ptr [ebx + 0x5c], 0
        db 083h, 063h, 040h, 000h   ; and dword ptr [ebx + 0x40], 0
        db 0C7h, 043h, 014h, 00Dh, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xd
        db 0E9h, 0C7h, 0F9h, 0FFh, 0FFh   ; jmp 0x35a434
$L_35aa6d:
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Dh, 051h, 0FEh, 0FFh, 0FFh   ; jge 0x35a8c6
        db 03Dh, 014h, 019h, 015h, 080h   ; cmp eax, 0x80151914
        db 075h, 02Bh   ; jne 0x35aaa7
        db 0FFh, 073h, 05Ch   ; push dword ptr [ebx + 0x5c]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 039h, 07Bh, 038h   ; cmp dword ptr [ebx + 0x38], edi
        db 089h, 07Bh, 05Ch   ; mov dword ptr [ebx + 0x5c], edi
        db 00Fh, 084h, 0D0h, 009h, 000h, 000h   ; je 0x35b462
        db 089h, 07Bh, 038h   ; mov dword ptr [ebx + 0x38], edi
$L_35aa95:
        db 089h, 07Bh, 03Ch   ; mov dword ptr [ebx + 0x3c], edi
        db 089h, 07Bh, 040h   ; mov dword ptr [ebx + 0x40], edi
$L_35aa9b:
        db 0C7h, 043h, 014h, 009h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 9
        db 0E9h, 08Fh, 0F9h, 0FFh, 0FFh   ; jmp 0x35a436
$L_35aaa7:
        db 03Dh, 016h, 019h, 015h, 080h   ; cmp eax, 0x80151916
        db 00Fh, 085h, 07Ah, 00Bh, 000h, 000h   ; jne 0x35b62c
        db 0FFh, 073h, 05Ch   ; push dword ptr [ebx + 0x5c]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 089h, 07Bh, 05Ch   ; mov dword ptr [ebx + 0x5c], edi
        db 0EBh, 0D4h   ; jmp 0x35aa95
$L_35aac1:
        db 08Dh, 043h, 058h   ; lea eax, [ebx + 0x58]
        db 050h   ; push eax
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 073h, 038h   ; push dword ptr [ebx + 0x38]
        call _sub_3589A9   ; 0x3589A9
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 094h, 009h, 000h, 000h   ; jl 0x35b46e
        db 0C7h, 043h, 014h, 00Ah, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xa
$L_35aae1:
        db 0FFh, 073h, 058h   ; push dword ptr [ebx + 0x58]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?GetMachineAccountContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z   ; 0x358534
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 00Fh, 085h, 063h, 008h, 000h, 000h   ; jne 0x35b359
        db 0FFh, 073h, 058h   ; push dword ptr [ebx + 0x58]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 039h, 07Bh, 038h   ; cmp dword ptr [ebx + 0x38], edi
        db 089h, 07Bh, 058h   ; mov dword ptr [ebx + 0x58], edi
        db 00Fh, 085h, 05Eh, 007h, 000h, 000h   ; jne 0x35b26a
$L_35ab0c:
        db 089h, 07Bh, 03Ch   ; mov dword ptr [ebx + 0x3c], edi
        db 089h, 07Bh, 040h   ; mov dword ptr [ebx + 0x40], edi
        db 0E9h, 06Fh, 0F9h, 0FFh, 0FFh   ; jmp 0x35a486
$L_35ab17:
        db 08Dh, 045h, 094h   ; lea eax, [ebp - 0x6c]
        db 050h   ; push eax
        call _XNetGetTitleXnAddr@4   ; 0x376FCA
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 03Eh, 008h, 000h, 000h   ; je 0x35b366
        db 08Bh, 0C8h   ; mov ecx, eax
        db 083h, 0E1h, 060h   ; and ecx, 0x60
        db 080h, 0F9h, 060h   ; cmp cl, 0x60
        db 00Fh, 085h, 062h, 009h, 000h, 000h   ; jne 0x35b498
        db 084h, 0E4h   ; test ah, ah
        db 00Fh, 088h, 05Ah, 009h, 000h, 000h   ; js 0x35b498
        db 039h, 09Eh, 0C8h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xc8], ebx
        db 075h, 02Fh   ; jne 0x35ab75
        db 08Dh, 045h, 0B8h   ; lea eax, [ebp - 0x48]
        db 050h   ; push eax
        call _XNetGetConfigStatus@4   ; 0x376F24
        db 039h, 07Dh, 0ECh   ; cmp dword ptr [ebp - 0x14], edi
        db 074h, 021h   ; je 0x35ab75
        db 0FFh, 073h, 050h   ; push dword ptr [ebx + 0x50]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 0FFh, 075h, 0C4h   ; push dword ptr [ebp - 0x3c]
        call ?ConfigureUPnPNat@CXo@@IAEJUin_addr@@GPAXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z   ; 0x37097C
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 00Bh, 009h, 000h, 000h   ; jl 0x35b47a
        db 08Bh, 043h, 050h   ; mov eax, dword ptr [ebx + 0x50]
        db 089h, 043h, 054h   ; mov dword ptr [ebx + 0x54], eax
$L_35ab75:
        call _GetTickCount@0   ; 0x22D120
        db 08Bh, 0C8h   ; mov ecx, eax
        db 0B8h, 090h, 05Fh, 001h, 000h   ; mov eax, 0x15f90
        db 050h   ; push eax
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 003h, 0C8h   ; add ecx, eax
        db 08Dh, 043h, 018h   ; lea eax, [ebx + 0x18]
        db 089h, 04Bh, 02Ch   ; mov dword ptr [ebx + 0x2c], ecx
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnSetEventTimer@CXoBase@@QAEXPAEPAXK@Z   ; 0x379499
        db 0E9h, 001h, 0FFh, 0FFh, 0FFh   ; jmp 0x35aa9b
$L_35ab9a:
        db 039h, 07Bh, 054h   ; cmp dword ptr [ebx + 0x54], edi
        db 00Fh, 085h, 023h, 0FDh, 0FFh, 0FFh   ; jne 0x35a8c6
        db 089h, 07Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], edi
$L_35aba6:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Bh, 08Bh, 0D0h, 003h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x3d0]
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 083h, 065h, 06Ch, 000h   ; and dword ptr [ebp + 0x6c], 0
        db 003h, 0C3h   ; add eax, ebx
        db 08Dh, 051h, 008h   ; lea edx, [ecx + 8]
$L_35abbb:
        db 08Bh, 0B8h, 0CCh, 000h, 000h, 000h   ; mov edi, dword ptr [eax + 0xcc]
        db 03Bh, 03Ah   ; cmp edi, dword ptr [edx]
        db 075h, 00Bh   ; jne 0x35abd0
        db 08Bh, 0B8h, 0D0h, 000h, 000h, 000h   ; mov edi, dword ptr [eax + 0xd0]
        db 03Bh, 07Ah, 004h   ; cmp edi, dword ptr [edx + 4]
        db 074h, 00Eh   ; je 0x35abde
$L_35abd0:
        db 0FFh, 045h, 06Ch   ; inc dword ptr [ebp + 0x6c]
        db 083h, 0C2h, 008h   ; add edx, 8
        db 083h, 07Dh, 06Ch, 004h   ; cmp dword ptr [ebp + 0x6c], 4
        db 072h, 0DFh   ; jb 0x35abbb
        db 0EBh, 064h   ; jmp 0x35ac42
$L_35abde:
        db 08Bh, 055h, 06Ch   ; mov edx, dword ptr [ebp + 0x6c]
        db 08Bh, 08Ch, 091h, 0F0h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + edx*4 + 0x1f0]
        db 009h, 088h, 0D4h, 000h, 000h, 000h   ; or dword ptr [eax + 0xd4], ecx
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Bh, 083h, 0D0h, 003h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x3d0]
        db 06Bh, 0C9h, 070h   ; imul ecx, ecx, 0x70
        db 08Bh, 084h, 090h, 0E0h, 001h, 000h, 000h   ; mov eax, dword ptr [eax + edx*4 + 0x1e0]
        db 089h, 084h, 019h, 038h, 001h, 000h, 000h   ; mov dword ptr [ecx + ebx + 0x138], eax
        db 03Bh, 09Eh, 0CCh, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xcc]
        db 075h, 016h   ; jne 0x35ac26
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 06Bh, 0C9h, 070h   ; imul ecx, ecx, 0x70
        db 08Bh, 08Ch, 019h, 038h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + ebx + 0x138]
        db 089h, 08Ch, 083h, 0BCh, 000h, 000h, 000h   ; mov dword ptr [ebx + eax*4 + 0xbc], ecx
$L_35ac26:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 06Bh, 0C9h, 070h   ; imul ecx, ecx, 0x70
        db 083h, 0BCh, 019h, 038h, 001h, 000h, 000h, 000h   ; cmp dword ptr [ecx + ebx + 0x138], 0
        db 07Dh, 00Ah   ; jge 0x35ac42
        db 08Dh, 084h, 030h, 0B8h, 006h, 000h, 000h   ; lea eax, [eax + esi + 0x6b8]
        db 080h, 008h, 002h   ; or byte ptr [eax], 2
$L_35ac42:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 00Fh, 082h, 057h, 0FFh, 0FFh, 0FFh   ; jb 0x35aba6
        db 033h, 0D2h   ; xor edx, edx
        db 032h, 0C9h   ; xor cl, cl
        db 089h, 055h, 07Ch   ; mov dword ptr [ebp + 0x7c], edx
$L_35ac56:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 003h, 0C3h   ; add eax, ebx
        db 08Bh, 0B8h, 0CCh, 000h, 000h, 000h   ; mov edi, dword ptr [eax + 0xcc]
        db 00Bh, 0B8h, 0D0h, 000h, 000h, 000h   ; or edi, dword ptr [eax + 0xd0]
        db 074h, 015h   ; je 0x35ac81
        db 08Ah, 080h, 0D5h, 000h, 000h, 000h   ; mov al, byte ptr [eax + 0xd5]
        db 038h, 086h, 090h, 000h, 000h, 000h   ; cmp byte ptr [esi + 0x90], al
        db 075h, 005h   ; jne 0x35ac7f
        db 033h, 0D2h   ; xor edx, edx
        db 042h   ; inc edx
        db 0EBh, 002h   ; jmp 0x35ac81
$L_35ac7f:
        db 08Ah, 0C8h   ; mov cl, al
$L_35ac81:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0CCh   ; jb 0x35ac56
        db 033h, 0FFh   ; xor edi, edi
        db 03Bh, 0D7h   ; cmp edx, edi
        db 075h, 011h   ; jne 0x35aca1
        db 084h, 0C9h   ; test cl, cl
        db 074h, 00Dh   ; je 0x35aca1
        db 088h, 08Eh, 090h, 000h, 000h, 000h   ; mov byte ptr [esi + 0x90], cl
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?SaveMachineAccountConfig@CXo@@QAEHXZ   ; 0x3573BE
$L_35aca1:
        db 08Bh, 083h, 0D0h, 003h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x3d0]
        db 08Bh, 080h, 0BCh, 001h, 000h, 000h   ; mov eax, dword ptr [eax + 0x1bc]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 081h, 0E1h, 0FFh, 000h, 000h, 000h   ; and ecx, 0xff
        db 051h   ; push ecx
        db 025h, 000h, 0FFh, 0FFh, 0FFh   ; and eax, 0xffffff00
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnLogonSetBwLimit@CXoBase@@QAEXKK@Z   ; 0x379478
        db 03Bh, 09Eh, 0CCh, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xcc]
        db 00Fh, 085h, 09Ch, 001h, 000h, 000h   ; jne 0x35ae6b
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
$L_35acd4:
        db 08Dh, 004h, 089h   ; lea eax, [ecx + ecx*4]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 039h, 0BCh, 030h, 0E0h, 000h, 000h, 000h   ; cmp dword ptr [eax + esi + 0xe0], edi
        db 07Ch, 00Dh   ; jl 0x35acf0
        db 039h, 0BCh, 018h, 098h, 002h, 000h, 000h   ; cmp dword ptr [eax + ebx + 0x298], edi
        db 00Fh, 08Ch, 072h, 008h, 000h, 000h   ; jl 0x35b562
$L_35acf0:
        db 041h   ; inc ecx
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
        db 072h, 0DBh   ; jb 0x35acd4
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnRaiseToDpc@CXoBase@@QAEXH@Z   ; 0x3794A4
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
$L_35ad07:
        db 08Dh, 004h, 080h   ; lea eax, [eax + eax*4]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 08Dh, 00Ch, 030h   ; lea ecx, [eax + esi]
        db 039h, 0B9h, 0E0h, 000h, 000h, 000h   ; cmp dword ptr [ecx + 0xe0], edi
        db 075h, 00Dh   ; jne 0x35ad25
        db 08Bh, 084h, 018h, 09Ch, 002h, 000h, 000h   ; mov eax, dword ptr [eax + ebx + 0x29c]
        db 089h, 081h, 0E4h, 000h, 000h, 000h   ; mov dword ptr [ecx + 0xe4], eax
$L_35ad25:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 040h   ; inc eax
        db 083h, 0F8h, 010h   ; cmp eax, 0x10
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
        db 072h, 0D6h   ; jb 0x35ad07
        db 057h   ; push edi
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnRaiseToDpc@CXoBase@@QAEXH@Z   ; 0x3794A4
        db 039h, 0BEh, 0A8h, 005h, 000h, 000h   ; cmp dword ptr [esi + 0x5a8], edi
        db 089h, 07Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], edi
        db 076h, 01Fh   ; jbe 0x35ad63
$L_35ad44:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 0FFh, 0B4h, 086h, 0ACh, 005h, 000h, 000h   ; push dword ptr [esi + eax*4 + 0x5ac]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 03Bh, 086h, 0A8h, 005h, 000h, 000h   ; cmp eax, dword ptr [esi + 0x5a8]
        db 072h, 0E1h   ; jb 0x35ad44
$L_35ad63:
        db 08Bh, 055h, 070h   ; mov edx, dword ptr [ebp + 0x70]
        db 08Dh, 083h, 0CCh, 003h, 000h, 000h   ; lea eax, [ebx + 0x3cc]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 08Ah, 0A8h, 005h, 000h, 000h   ; mov dword ptr [edx + 0x5a8], ecx
        db 08Dh, 0B3h, 0D0h, 003h, 000h, 000h   ; lea esi, [ebx + 0x3d0]
        db 08Dh, 0BAh, 0ACh, 005h, 000h, 000h   ; lea edi, [edx + 0x5ac]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 083h, 020h, 000h   ; and dword ptr [eax], 0
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
$L_35ad8a:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 003h, 0C3h   ; add eax, ebx
        db 0F6h, 080h, 0D4h, 000h, 000h, 000h, 003h   ; test byte ptr [eax + 0xd4], 3
        db 074h, 006h   ; je 0x35ada0
        db 033h, 0D2h   ; xor edx, edx
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 00Ch   ; jmp 0x35adac
$L_35ada0:
        db 08Bh, 090h, 0CCh, 000h, 000h, 000h   ; mov edx, dword ptr [eax + 0xcc]
        db 08Bh, 080h, 0D0h, 000h, 000h, 000h   ; mov eax, dword ptr [eax + 0xd0]
$L_35adac:
        db 089h, 054h, 0CDh, 014h   ; mov dword ptr [ebp + ecx*8 + 0x14], edx
        db 089h, 044h, 0CDh, 018h   ; mov dword ptr [ebp + ecx*8 + 0x18], eax
        db 041h   ; inc ecx
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
        db 072h, 0CDh   ; jb 0x35ad8a
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
        db 08Bh, 075h, 070h   ; mov esi, dword ptr [ebp + 0x70]
$L_35adc4:
        db 0FFh, 075h, 07Ch   ; push dword ptr [ebp + 0x7c]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?FeedbackResetHistory@CXo@@IAEJK@Z   ; 0x361897
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0EDh   ; jb 0x35adc4
        db 08Dh, 045h, 014h   ; lea eax, [ebp + 0x14]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnLogonChangeUsers@CXoBase@@QAEHPA_K@Z   ; 0x379427
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 0C1h, 006h, 000h, 000h   ; je 0x35b4ab
        db 0C7h, 043h, 00Ch, 0F0h, 013h, 015h, 000h   ; mov dword ptr [ebx + 0xc], 0x1513f0
        db 08Bh, 086h, 0C8h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xc8]
        db 083h, 078h, 008h, 000h   ; cmp dword ptr [eax + 8], 0
        db 074h, 03Fh   ; je 0x35ae3c
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
$L_35ae02:
        db 08Dh, 00Ch, 0C0h   ; lea ecx, [eax + eax*8]
        db 083h, 0BCh, 0CEh, 0E0h, 013h, 000h, 000h, 000h   ; cmp dword ptr [esi + ecx*8 + 0x13e0], 0
        db 074h, 024h   ; je 0x35ae33
        db 08Bh, 08Eh, 0C8h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xc8]
        db 0FFh, 071h, 008h   ; push dword ptr [ecx + 8]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 050h   ; push eax
        call ?XnLogonSetQEvent@CXoBase@@QAEIIPAX@Z   ; 0x379453
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Dh, 00Ch, 0C9h   ; lea ecx, [ecx + ecx*8]
        db 08Bh, 08Ch, 0CEh, 0E0h, 013h, 000h, 000h   ; mov ecx, dword ptr [esi + ecx*8 + 0x13e0]
        db 089h, 041h, 008h   ; mov dword ptr [ecx + 8], eax
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
$L_35ae33:
        db 040h   ; inc eax
        db 083h, 0F8h, 004h   ; cmp eax, 4
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
        db 072h, 0C6h   ; jb 0x35ae02
$L_35ae3c:
        db 08Bh, 043h, 030h   ; mov eax, dword ptr [ebx + 0x30]
        db 08Bh, 07Dh, 070h   ; mov edi, dword ptr [ebp + 0x70]
        db 025h, 0FFh, 0FFh, 0FFh, 0DFh   ; and eax, 0xdfffffff
        db 00Dh, 000h, 000h, 000h, 010h   ; or eax, 0x10000000
        db 089h, 043h, 030h   ; mov dword ptr [ebx + 0x30], eax
        db 0C7h, 043h, 014h, 010h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x10
        db 08Bh, 086h, 0C8h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xc8]
        db 0C7h, 080h, 0B8h, 000h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0xb8], 1
        db 0E9h, 0A6h, 001h, 000h, 000h   ; jmp 0x35b011
$L_35ae6b:
        db 08Bh, 045h, 070h   ; mov eax, dword ptr [ebp + 0x70]
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
        db 083h, 0B8h, 0A8h, 005h, 000h, 000h, 000h   ; cmp dword ptr [eax + 0x5a8], 0
        db 06Ah, 050h   ; push 0x50
        db 08Dh, 0B3h, 08Ch, 002h, 000h, 000h   ; lea esi, [ebx + 0x28c]
        db 08Dh, 0B8h, 0D4h, 000h, 000h, 000h   ; lea edi, [eax + 0xd4]
        db 059h   ; pop ecx
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 076h, 024h   ; jbe 0x35aeb0
        db 08Bh, 0F0h   ; mov esi, eax
$L_35ae8e:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 0FFh, 0B4h, 086h, 0ACh, 005h, 000h, 000h   ; push dword ptr [esi + eax*4 + 0x5ac]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 03Bh, 086h, 0A8h, 005h, 000h, 000h   ; cmp eax, dword ptr [esi + 0x5a8]
        db 072h, 0E1h   ; jb 0x35ae8e
        db 08Bh, 045h, 070h   ; mov eax, dword ptr [ebp + 0x70]
$L_35aeb0:
        db 08Dh, 093h, 0CCh, 003h, 000h, 000h   ; lea edx, [ebx + 0x3cc]
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 089h, 088h, 0A8h, 005h, 000h, 000h   ; mov dword ptr [eax + 0x5a8], ecx
        db 08Dh, 0B3h, 0D0h, 003h, 000h, 000h   ; lea esi, [ebx + 0x3d0]
        db 08Dh, 0B8h, 0ACh, 005h, 000h, 000h   ; lea edi, [eax + 0x5ac]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 083h, 022h, 000h   ; and dword ptr [edx], 0
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35aed3:
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Dh, 00Ch, 089h   ; lea ecx, [ecx + ecx*4]
        db 08Dh, 00Ch, 088h   ; lea ecx, [eax + ecx*4]
        db 08Bh, 091h, 0D4h, 000h, 000h, 000h   ; mov edx, dword ptr [ecx + 0xd4]
        db 085h, 0D2h   ; test edx, edx
        db 074h, 03Bh   ; je 0x35af21
        db 08Bh, 0B1h, 0D8h, 000h, 000h, 000h   ; mov esi, dword ptr [ecx + 0xd8]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 031h   ; je 0x35af21
        db 083h, 0B9h, 0E0h, 000h, 000h, 000h, 000h   ; cmp dword ptr [ecx + 0xe0], 0
        db 075h, 028h   ; jne 0x35af21
        db 08Dh, 045h, 04Ch   ; lea eax, [ebp + 0x4c]
        db 050h   ; push eax
        db 052h   ; push edx
        db 056h   ; push esi
        call _XNetServerToInAddr@12   ; 0x3770B9
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 085h, 0ABh, 005h, 000h, 000h   ; jne 0x35b4b7
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Bh, 055h, 070h   ; mov edx, dword ptr [ebp + 0x70]
        db 08Bh, 04Dh, 04Ch   ; mov ecx, dword ptr [ebp + 0x4c]
        db 08Dh, 004h, 080h   ; lea eax, [eax + eax*4]
        db 089h, 08Ch, 082h, 0D8h, 000h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0xd8], ecx
        db 08Bh, 0C2h   ; mov eax, edx
$L_35af21:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 010h   ; cmp dword ptr [ebp + 0x7c], 0x10
        db 072h, 0A9h   ; jb 0x35aed3
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
$L_35af2f:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 003h, 0C3h   ; add eax, ebx
        db 0F6h, 080h, 0D4h, 000h, 000h, 000h, 003h   ; test byte ptr [eax + 0xd4], 3
        db 074h, 006h   ; je 0x35af45
        db 033h, 0D2h   ; xor edx, edx
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 00Ch   ; jmp 0x35af51
$L_35af45:
        db 08Bh, 090h, 0CCh, 000h, 000h, 000h   ; mov edx, dword ptr [eax + 0xcc]
        db 08Bh, 080h, 0D0h, 000h, 000h, 000h   ; mov eax, dword ptr [eax + 0xd0]
$L_35af51:
        db 089h, 054h, 0CDh, 0F4h   ; mov dword ptr [ebp + ecx*8 - 0xc], edx
        db 089h, 044h, 0CDh, 0F8h   ; mov dword ptr [ebp + ecx*8 - 8], eax
        db 041h   ; inc ecx
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 089h, 04Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], ecx
        db 072h, 0CDh   ; jb 0x35af2f
        db 08Bh, 07Dh, 070h   ; mov edi, dword ptr [ebp + 0x70]
        db 08Dh, 045h, 050h   ; lea eax, [ebp + 0x50]
        db 050h   ; push eax
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?XOnlineGetServiceInfo@CXo@@QAEJKPAU_XONLINE_SERVICE_INFO@@@Z   ; 0x359F5F
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 005h   ; jl 0x35af7b
        db 08Bh, 075h, 054h   ; mov esi, dword ptr [ebp + 0x54]
        db 0EBh, 002h   ; jmp 0x35af7d
$L_35af7b:
        db 033h, 0F6h   ; xor esi, esi
$L_35af7d:
        db 085h, 0F6h   ; test esi, esi
        db 075h, 018h   ; jne 0x35af99
        db 08Dh, 045h, 050h   ; lea eax, [ebp + 0x50]
        db 050h   ; push eax
        db 06Ah, 00Ch   ; push 0xc
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?XOnlineGetServiceInfo@CXo@@QAEJKPAU_XONLINE_SERVICE_INFO@@@Z   ; 0x359F5F
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 005h   ; jl 0x35af97
        db 08Bh, 075h, 054h   ; mov esi, dword ptr [ebp + 0x54]
        db 0EBh, 002h   ; jmp 0x35af99
$L_35af97:
        db 033h, 0F6h   ; xor esi, esi
$L_35af99:
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 056h   ; push esi
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?XnLogon@CXoBase@@QAEXUin_addr@@PA_KPAX@Z   ; 0x3796C9
        db 033h, 0C0h   ; xor eax, eax
        db 03Bh, 0F0h   ; cmp esi, eax
        db 075h, 010h   ; jne 0x35afbe
        db 0C7h, 043h, 014h, 013h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x13
        db 0C7h, 045h, 068h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x68], 1
        db 0EBh, 053h   ; jmp 0x35b011
$L_35afbe:
        db 039h, 043h, 008h   ; cmp dword ptr [ebx + 8], eax
        db 074h, 037h   ; je 0x35affa
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
$L_35afc6:
        db 08Dh, 00Ch, 0C0h   ; lea ecx, [eax + eax*8]
        db 083h, 0BCh, 0CFh, 0E0h, 013h, 000h, 000h, 000h   ; cmp dword ptr [edi + ecx*8 + 0x13e0], 0
        db 074h, 01Eh   ; je 0x35aff1
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?XnLogonSetQEvent@CXoBase@@QAEIIPAX@Z   ; 0x379453
        db 08Bh, 04Dh, 07Ch   ; mov ecx, dword ptr [ebp + 0x7c]
        db 08Dh, 00Ch, 0C9h   ; lea ecx, [ecx + ecx*8]
        db 08Bh, 08Ch, 0CFh, 0E0h, 013h, 000h, 000h   ; mov ecx, dword ptr [edi + ecx*8 + 0x13e0]
        db 089h, 041h, 008h   ; mov dword ptr [ecx + 8], eax
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
$L_35aff1:
        db 040h   ; inc eax
        db 083h, 0F8h, 004h   ; cmp eax, 4
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
        db 072h, 0CCh   ; jb 0x35afc6
$L_35affa:
        db 08Bh, 043h, 030h   ; mov eax, dword ptr [ebx + 0x30]
        db 025h, 0FFh, 0FFh, 0FFh, 0DFh   ; and eax, 0xdfffffff
        db 00Dh, 000h, 000h, 000h, 010h   ; or eax, 0x10000000
        db 089h, 043h, 030h   ; mov dword ptr [ebx + 0x30], eax
        db 0C7h, 043h, 014h, 010h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x10
$L_35b011:
        db 08Dh, 045h, 050h   ; lea eax, [ebp + 0x50]
        db 050h   ; push eax
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?XOnlineGetServiceInfo@CXo@@QAEJKPAU_XONLINE_SERVICE_INFO@@@Z   ; 0x359F5F
        db 03Dh, 001h, 011h, 015h, 080h   ; cmp eax, 0x80151101
        db 00Fh, 085h, 09Fh, 002h, 000h, 000h   ; jne 0x35b2c8
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35b02d:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Bh, 04Dh, 070h   ; mov ecx, dword ptr [ebp + 0x70]
        db 08Dh, 004h, 0C0h   ; lea eax, [eax + eax*8]
        db 08Dh, 004h, 0C1h   ; lea eax, [ecx + eax*8]
        db 083h, 0B8h, 0E0h, 013h, 000h, 000h, 000h   ; cmp dword ptr [eax + 0x13e0], 0
        db 074h, 007h   ; je 0x35b049
        db 083h, 088h, 0B4h, 013h, 000h, 000h, 040h   ; or dword ptr [eax + 0x13b4], 0x40
$L_35b049:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0DBh   ; jb 0x35b02d
        db 0E9h, 071h, 002h, 000h, 000h   ; jmp 0x35b2c8
$L_35b057:
        db 083h, 0E8h, 010h   ; sub eax, 0x10
        db 00Fh, 084h, 0C2h, 001h, 000h, 000h   ; je 0x35b222
        db 048h   ; dec eax
        db 00Fh, 084h, 04Dh, 001h, 000h, 000h   ; je 0x35b1b4
        db 048h   ; dec eax
        db 048h   ; dec eax
        db 00Fh, 084h, 0B9h, 000h, 000h, 000h   ; je 0x35b128
        db 048h   ; dec eax
        db 00Fh, 085h, 061h, 002h, 000h, 000h   ; jne 0x35b2d7
        db 08Bh, 083h, 010h, 004h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x410]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 098h, 000h, 000h, 000h   ; je 0x35b11c
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E16   ; 0x356E16
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 032h, 0F8h, 0FFh, 0FFh   ; je 0x35a8c6
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 075h, 041h   ; jne 0x35b0dc
        db 08Bh, 075h, 070h   ; mov esi, dword ptr [ebp + 0x70]
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 050h   ; push eax
        db 050h   ; push eax
        db 050h   ; push eax
        db 08Dh, 045h, 07Ch   ; lea eax, [ebp + 0x7c]
        db 050h   ; push eax
        db 08Dh, 045h, 05Ch   ; lea eax, [ebp + 0x5c]
        db 050h   ; push eax
        db 0FFh, 0B3h, 010h, 004h, 000h, 000h   ; push dword ptr [ebx + 0x410]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XOnlineUploadGetResults@CXo@@QAEJPAUXONLINETASK_HANDLE__@@PAPAEPAKPAT_ULARGE_INTEGER@@32PAU_FILETIME@@@Z   ; 0x36296E
        db 08Bh, 045h, 070h   ; mov eax, dword ptr [ebp + 0x70]
        db 08Dh, 0BEh, 0BCh, 006h, 000h, 000h   ; lea edi, [esi + 0x6bc]
        db 08Bh, 075h, 05Ch   ; mov esi, dword ptr [ebp + 0x5c]
        db 06Ah, 019h   ; push 0x19
        db 059h   ; pop ecx
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 033h, 0D2h   ; xor edx, edx
        db 0C7h, 080h, 020h, 007h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x720], 1
        db 08Bh, 0F0h   ; mov esi, eax
        db 033h, 0FFh   ; xor edi, edi
        db 0EBh, 005h   ; jmp 0x35b0e1
$L_35b0dc:
        db 0BAh, 001h, 010h, 015h, 080h   ; mov edx, 0x80151001
$L_35b0e1:
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 08Bh, 08Ch, 002h, 000h, 000h   ; lea ecx, [ebx + 0x28c]
$L_35b0e9:
        db 083h, 039h, 00Ch   ; cmp dword ptr [ecx], 0xc
        db 074h, 00Ch   ; je 0x35b0fa
        db 040h   ; inc eax
        db 083h, 0C1h, 014h   ; add ecx, 0x14
        db 083h, 0F8h, 010h   ; cmp eax, 0x10
        db 07Ch, 0F2h   ; jl 0x35b0e9
        db 083h, 0C8h, 0FFh   ; or eax, 0xffffffff
$L_35b0fa:
        db 08Dh, 004h, 080h   ; lea eax, [eax + eax*4]
        db 089h, 094h, 086h, 0E0h, 000h, 000h, 000h   ; mov dword ptr [esi + eax*4 + 0xe0], edx
        db 0FFh, 0B3h, 010h, 004h, 000h, 000h   ; push dword ptr [ebx + 0x410]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 089h, 0BBh, 010h, 004h, 000h, 000h   ; mov dword ptr [ebx + 0x410], edi
        db 0E9h, 01Ah, 0F3h, 0FFh, 0FFh   ; jmp 0x35a436
$L_35b11c:
        db 0C7h, 043h, 014h, 015h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x15
        db 0E9h, 00Eh, 0F3h, 0FFh, 0FFh   ; jmp 0x35a436
$L_35b128:
        db 08Dh, 0BBh, 010h, 004h, 000h, 000h   ; lea edi, [ebx + 0x410]
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 00Fh   ; mov dword ptr [edi], ecx
        db 08Dh, 083h, 08Ch, 002h, 000h, 000h   ; lea eax, [ebx + 0x28c]
$L_35b138:
        db 083h, 038h, 00Ch   ; cmp dword ptr [eax], 0xc
        db 074h, 072h   ; je 0x35b1af
        db 041h   ; inc ecx
        db 083h, 0C0h, 014h   ; add eax, 0x14
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 07Ch, 0F2h   ; jl 0x35b138
        db 083h, 04Dh, 06Ch, 0FFh   ; or dword ptr [ebp + 0x6c], 0xffffffff
$L_35b14a:
        db 03Bh, 09Eh, 0CCh, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xcc]
        db 074h, 04Ah   ; je 0x35b19c
        db 083h, 07Dh, 06Ch, 0FFh   ; cmp dword ptr [ebp + 0x6c], -1
        db 074h, 044h   ; je 0x35b19c
        db 057h   ; push edi
        db 06Ah, 001h   ; push 1
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 033h, 0C0h   ; xor eax, eax
        db 068h, 010h, 027h, 000h, 000h   ; push 0x2710
        db 050h   ; push eax
        db 08Dh, 04Dh, 07Ch   ; lea ecx, [ebp + 0x7c]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 050h   ; push eax
        db 051h   ; push ecx
        db 050h   ; push eax
        db 068h   ; push 0x538f80
        dd _unk_538F80
        db 050h   ; push eax
        db 06Ah, 00Ch   ; push 0xc
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0C7h, 045h, 07Ch, 000h, 004h, 000h, 000h   ; mov dword ptr [ebp + 0x7c], 0x400
        call ?XOnlineUploadFromMemory@CXo@@QAEJKKPBDPAEPAKPBEK3KKPAXHPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x363155
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 01Bh   ; jge 0x35b1a3
        db 08Bh, 045h, 06Ch   ; mov eax, dword ptr [ebp + 0x6c]
        db 08Dh, 004h, 080h   ; lea eax, [eax + eax*4]
        db 0C7h, 084h, 086h, 0E0h, 000h, 000h, 000h, 001h, 010h, 015h, 080h   ; mov dword ptr [esi + eax*4 + 0xe0], 0x80151001
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
$L_35b19c:
        db 0C7h, 045h, 068h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x68], 1
$L_35b1a3:
        db 0C7h, 043h, 014h, 014h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x14
        db 0E9h, 019h, 001h, 000h, 000h   ; jmp 0x35b2c8
$L_35b1af:
        db 089h, 04Dh, 06Ch   ; mov dword ptr [ebp + 0x6c], ecx
        db 0EBh, 096h   ; jmp 0x35b14a
$L_35b1b4:
        db 08Dh, 045h, 060h   ; lea eax, [ebp + 0x60]
        db 050h   ; push eax
        db 057h   ; push edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 07Dh, 060h   ; mov dword ptr [ebp + 0x60], edi
        call ?XnLogonGetStatus@CXoBase@@QAEKPAU_SGADDR@@PAK@Z   ; 0x379868
        db 048h   ; dec eax
        db 00Fh, 084h, 023h, 004h, 000h, 000h   ; je 0x35b5ed
        db 08Bh, 083h, 0B4h, 000h, 000h, 000h   ; mov eax, dword ptr [ebx + 0xb4]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 0EEh, 0F6h, 0FFh, 0FFh   ; je 0x35a8c6
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E16   ; 0x356E16
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 084h, 0DCh, 0F6h, 0FFh, 0FFh   ; je 0x35a8c6
        db 0FFh, 0B3h, 0B4h, 000h, 000h, 000h   ; push dword ptr [ebx + 0xb4]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_356E2B   ; 0x356E2B
        db 083h, 0A3h, 0B4h, 000h, 000h, 000h, 000h   ; and dword ptr [ebx + 0xb4], 0
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 0BDh, 002h, 000h, 000h   ; jl 0x35b4c3
        db 08Bh, 043h, 030h   ; mov eax, dword ptr [ebx + 0x30]
        db 025h, 0FFh, 0FFh, 0FFh, 03Fh   ; and eax, 0x3fffffff
        db 00Dh, 000h, 000h, 000h, 080h   ; or eax, 0x80000000
        db 089h, 043h, 030h   ; mov dword ptr [ebx + 0x30], eax
        db 0C7h, 043h, 014h, 013h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x13
        db 0E9h, 012h, 0F2h, 0FFh, 0FFh   ; jmp 0x35a434
$L_35b222:
        db 057h   ; push edi
        db 057h   ; push edi
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnLogonGetStatus@CXoBase@@QAEKPAU_SGADDR@@PAK@Z   ; 0x379868
        db 083h, 0F8h, 001h   ; cmp eax, 1
        db 075h, 046h   ; jne 0x35b276
        db 080h, 04Bh, 033h, 030h   ; or byte ptr [ebx + 0x33], 0x30
        db 039h, 07Bh, 048h   ; cmp dword ptr [ebx + 0x48], edi
        db 00Fh, 085h, 0D9h, 003h, 000h, 000h   ; jne 0x35b616
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 043h, 048h   ; mov dword ptr [ebx + 0x48], eax
        call ?XnLogoff@CXoBase@@QAEXXZ   ; 0x37948E
        db 089h, 07Dh, 07Ch   ; mov dword ptr [ebp + 0x7c], edi
$L_35b24a:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Dh, 004h, 0C0h   ; lea eax, [eax + eax*8]
        db 08Bh, 084h, 0C6h, 0E0h, 013h, 000h, 000h   ; mov eax, dword ptr [esi + eax*8 + 0x13e0]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 074h, 003h   ; je 0x35b25e
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_35b25e:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0E3h   ; jb 0x35b24a
        db 089h, 07Bh, 040h   ; mov dword ptr [ebx + 0x40], edi
$L_35b26a:
        db 0C7h, 043h, 014h, 00Dh, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0xd
        db 0E9h, 0C0h, 0F1h, 0FFh, 0FFh   ; jmp 0x35a436
$L_35b276:
        db 083h, 0F8h, 006h   ; cmp eax, 6
        db 00Fh, 085h, 047h, 0F6h, 0FFh, 0FFh   ; jne 0x35a8c6
        db 08Bh, 07Bh, 030h   ; mov edi, dword ptr [ebx + 0x30]
        db 08Dh, 045h, 050h   ; lea eax, [ebp + 0x50]
        db 081h, 0E7h, 0FFh, 0FFh, 0FFh, 0EFh   ; and edi, 0xefffffff
        db 050h   ; push eax
        db 081h, 0CFh, 000h, 000h, 000h, 020h   ; or edi, 0x20000000
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 07Bh, 030h   ; mov dword ptr [ebx + 0x30], edi
        call ?XOnlineGetServiceInfo@CXo@@QAEJKPAU_XONLINE_SERVICE_INFO@@@Z   ; 0x359F5F
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 018h   ; jl 0x35b2ba
        db 081h, 0E7h, 0FFh, 0FFh, 0FFh, 03Fh   ; and edi, 0x3fffffff
        db 081h, 0CFh, 000h, 000h, 000h, 040h   ; or edi, 0x40000000
        db 089h, 07Bh, 030h   ; mov dword ptr [ebx + 0x30], edi
        db 0C7h, 043h, 014h, 011h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x11
        db 0EBh, 007h   ; jmp 0x35b2c1
$L_35b2ba:
        db 0C7h, 043h, 014h, 013h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x13
$L_35b2c1:
        db 0C7h, 045h, 068h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x68], 1
$L_35b2c8:
        db 083h, 07Dh, 068h, 000h   ; cmp dword ptr [ebp + 0x68], 0
        db 00Fh, 084h, 0F1h, 0F5h, 0FFh, 0FFh   ; je 0x35a8c3
        db 0E9h, 076h, 0F6h, 0FFh, 0FFh   ; jmp 0x35a94d
$L_35b2d7:
        db 048h   ; dec eax
        db 00Fh, 084h, 0A0h, 000h, 000h, 000h   ; je 0x35b37e
        db 083h, 0E8h, 04Eh   ; sub eax, 0x4e
        db 00Fh, 085h, 0DFh, 0F5h, 0FFh, 0FFh   ; jne 0x35a8c6
        db 03Bh, 09Eh, 0C8h, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xc8]
        db 00Fh, 085h, 0D3h, 0F5h, 0FFh, 0FFh   ; jne 0x35a8c6
        db 039h, 07Bh, 010h   ; cmp dword ptr [ebx + 0x10], edi
        db 00Fh, 08Ch, 0CAh, 0F5h, 0FFh, 0FFh   ; jl 0x35a8c6
        db 08Dh, 045h, 060h   ; lea eax, [ebp + 0x60]
        db 050h   ; push eax
        db 057h   ; push edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 07Dh, 060h   ; mov dword ptr [ebp + 0x60], edi
        call ?XnLogonGetStatus@CXoBase@@QAEKPAU_SGADDR@@PAK@Z   ; 0x379868
        db 048h   ; dec eax
        db 00Fh, 084h, 0DBh, 002h, 000h, 000h   ; je 0x35b5ed
        db 083h, 0E8h, 005h   ; sub eax, 5
        db 00Fh, 085h, 0ABh, 0F5h, 0FFh, 0FFh   ; jne 0x35a8c6
        db 08Dh, 083h, 0B8h, 000h, 000h, 000h   ; lea eax, [ebx + 0xb8]
        db 083h, 038h, 001h   ; cmp dword ptr [eax], 1
        db 075h, 01Ah   ; jne 0x35b340
        db 089h, 038h   ; mov dword ptr [eax], edi
        db 08Bh, 086h, 0CCh, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xcc]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 074h, 00Eh   ; je 0x35b340
        db 08Bh, 040h, 008h   ; mov eax, dword ptr [eax + 8]
        db 03Bh, 043h, 008h   ; cmp eax, dword ptr [ebx + 8]
        db 074h, 006h   ; je 0x35b340
        db 050h   ; push eax
        call _SetEvent@4   ; 0x22CEB7
$L_35b340:
        db 039h, 0BEh, 0CCh, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xcc], edi
        db 00Fh, 085h, 07Ah, 0F5h, 0FFh, 0FFh   ; jne 0x35a8c6
        db 053h   ; push ebx
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?MessagingDoWork@CXo@@IAEXPAUXONLINETASK_LOGON@@@Z   ; 0x36F072
        db 0E9h, 06Dh, 0F5h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b359:
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 0CBh, 002h, 000h, 000h   ; jl 0x35b62c
        db 0E9h, 060h, 0F5h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b366:
        db 068h, 0C8h, 000h, 000h, 000h   ; push 0xc8
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        db 08Dh, 043h, 018h   ; lea eax, [ebx + 0x18]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnSetEventTimer@CXoBase@@QAEXPAEPAXK@Z   ; 0x379499
        db 0E9h, 048h, 0F5h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b37e:
        db 033h, 0C0h   ; xor eax, eax
        db 0C6h, 045h, 068h, 000h   ; mov byte ptr [ebp + 0x68], 0
        db 08Dh, 07Dh, 069h   ; lea edi, [ebp + 0x69]
        db 066h, 0ABh   ; stosw word ptr es:[edi], ax
        db 033h, 0C9h   ; xor ecx, ecx
        db 0AAh   ; stosb byte ptr es:[edi], al
        db 08Bh, 07Dh, 068h   ; mov edi, dword ptr [ebp + 0x68]
        db 089h, 04Dh, 064h   ; mov dword ptr [ebp + 0x64], ecx
        db 089h, 04Dh, 06Ch   ; mov dword ptr [ebp + 0x6c], ecx
        db 08Dh, 086h, 0D8h, 000h, 000h, 000h   ; lea eax, [esi + 0xd8]
$L_35b39b:
        db 083h, 078h, 0FCh, 014h   ; cmp dword ptr [eax - 4], 0x14
        db 075h, 018h   ; jne 0x35b3b9
        db 083h, 078h, 008h, 000h   ; cmp dword ptr [eax + 8], 0
        db 07Ch, 02Bh   ; jl 0x35b3d2
        db 08Bh, 048h, 00Ch   ; mov ecx, dword ptr [eax + 0xc]
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 033h, 0D2h   ; xor edx, edx
        db 083h, 079h, 030h, 001h   ; cmp dword ptr [ecx + 0x30], 1
        db 00Fh, 094h, 0C2h   ; sete dl
        db 08Bh, 0CAh   ; mov ecx, edx
        db 0EBh, 00Dh   ; jmp 0x35b3c6
$L_35b3b9:
        db 083h, 078h, 008h, 000h   ; cmp dword ptr [eax + 8], 0
        db 07Ch, 007h   ; jl 0x35b3c6
        db 0C7h, 045h, 064h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x64], 1
$L_35b3c6:
        db 0FFh, 045h, 06Ch   ; inc dword ptr [ebp + 0x6c]
        db 083h, 0C0h, 014h   ; add eax, 0x14
        db 083h, 07Dh, 06Ch, 010h   ; cmp dword ptr [ebp + 0x6c], 0x10
        db 07Ch, 0C9h   ; jl 0x35b39b
$L_35b3d2:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 021h   ; je 0x35b3f7
        db 083h, 07Dh, 064h, 000h   ; cmp dword ptr [ebp + 0x64], 0
        db 074h, 01Bh   ; je 0x35b3f7
        db 051h   ; push ecx
        db 057h   ; push edi
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnNatDetect@CXoBase@@QAEKUin_addr@@H@Z   ; 0x3796D4
        db 083h, 0F8h, 004h   ; cmp eax, 4
        db 075h, 00Dh   ; jne 0x35b3f7
        db 0FFh, 073h, 008h   ; push dword ptr [ebx + 8]
        call _SetEvent@4   ; 0x22CEB7
        db 0E9h, 0CFh, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b3f7:
        db 08Bh, 045h, 070h   ; mov eax, dword ptr [ebp + 0x70]
        db 033h, 0C9h   ; xor ecx, ecx
        db 03Bh, 098h, 0C8h, 000h, 000h, 000h   ; cmp ebx, dword ptr [eax + 0xc8]
        db 08Dh, 090h, 014h, 002h, 000h, 000h   ; lea edx, [eax + 0x214]
        db 00Fh, 095h, 0C1h   ; setne cl
        db 06Ah, 070h   ; push 0x70
        db 08Dh, 0B3h, 0CCh, 000h, 000h, 000h   ; lea esi, [ebx + 0xcc]
        db 08Bh, 0FAh   ; mov edi, edx
        db 049h   ; dec ecx
        db 081h, 0E1h, 0FFh, 0FCh, 0FFh, 0FFh   ; and ecx, 0xfffffcff
        db 081h, 0C1h, 0F1h, 013h, 015h, 000h   ; add ecx, 0x1513f1
        db 089h, 04Bh, 010h   ; mov dword ptr [ebx + 0x10], ecx
        db 059h   ; pop ecx
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 089h, 090h, 0D0h, 000h, 000h, 000h   ; mov dword ptr [eax + 0xd0], edx
        db 0C7h, 043h, 014h, 063h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14], 0x63
        db 0E9h, 089h, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c3
$L_35b43a:
        db 0C7h, 043h, 010h, 007h, 000h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80150007
        db 0E9h, 07Dh, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c3
$L_35b446:
        db 083h, 04Bh, 030h, 004h   ; or dword ptr [ebx + 0x30], 4
        db 0C7h, 043h, 010h, 00Ch, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x8015190c
        db 0E9h, 070h, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b456:
        db 0C7h, 043h, 010h, 00Ah, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x8015190a
        db 0E9h, 064h, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b462:
        db 0C7h, 043h, 010h, 008h, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151908
        db 0E9h, 058h, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b46e:
        db 0C7h, 043h, 010h, 006h, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151906
        db 0E9h, 04Ch, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b47a:
        db 068h, 043h, 080h, 000h, 000h   ; push 0x8043
        db 0FFh, 073h, 050h   ; push dword ptr [ebx + 0x50]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0C7h, 043h, 010h, 019h, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151919
        call ?SysFree@CXo@@IAEXPAXK@Z   ; 0x36990B
        db 089h, 07Bh, 050h   ; mov dword ptr [ebx + 0x50], edi
        db 0E9h, 02Eh, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b498:
        db 083h, 04Bh, 030h, 001h   ; or dword ptr [ebx + 0x30], 1
        db 089h, 043h, 034h   ; mov dword ptr [ebx + 0x34], eax
        db 0C7h, 043h, 010h, 001h, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151901
        db 0E9h, 01Bh, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b4ab:
        db 0C7h, 043h, 010h, 000h, 013h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151300
        db 0E9h, 00Ch, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c3
$L_35b4b7:
        db 0C7h, 043h, 010h, 00Eh, 019h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x8015190e
        db 0E9h, 000h, 0F4h, 0FFh, 0FFh   ; jmp 0x35a8c3
$L_35b4c3:
        db 081h, 0FFh, 005h, 020h, 015h, 080h   ; cmp edi, 0x80152005
        db 00Fh, 085h, 09Fh, 000h, 000h, 000h   ; jne 0x35b56e
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XnLogoff@CXoBase@@QAEXXZ   ; 0x37948E
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?ClearServiceTicketCache@CXo@@IAEXXZ   ; 0x359DC1
        db 03Bh, 09Eh, 0C8h, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xc8]
        db 075h, 039h   ; jne 0x35b51e
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35b4e9:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Dh, 004h, 0C0h   ; lea eax, [eax + eax*8]
        db 08Bh, 084h, 0C6h, 0E0h, 013h, 000h, 000h   ; mov eax, dword ptr [esi + eax*8 + 0x13e0]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 004h   ; je 0x35b4fe
        db 083h, 060h, 008h, 000h   ; and dword ptr [eax + 8], 0
$L_35b4fe:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0E2h   ; jb 0x35b4e9
        db 080h, 04Bh, 033h, 0C0h   ; or byte ptr [ebx + 0x33], 0xc0
        db 0C7h, 043h, 034h, 005h, 020h, 015h, 080h   ; mov dword ptr [ebx + 0x34], 0x80152005
$L_35b512:
        db 0C7h, 043h, 010h, 004h, 010h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151004
        db 0E9h, 0A8h, 0F3h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b51e:
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
$L_35b523:
        db 08Bh, 0C8h   ; mov ecx, eax
        db 06Bh, 0C9h, 070h   ; imul ecx, ecx, 0x70
        db 08Bh, 08Ch, 019h, 038h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + ebx + 0x138]
        db 089h, 08Ch, 083h, 0BCh, 000h, 000h, 000h   ; mov dword ptr [ebx + eax*4 + 0xbc], ecx
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Dh, 00Ch, 0C0h   ; lea ecx, [eax + eax*8]
        db 08Bh, 08Ch, 0CEh, 0E0h, 013h, 000h, 000h   ; mov ecx, dword ptr [esi + ecx*8 + 0x13e0]
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 007h   ; je 0x35b54e
        db 083h, 061h, 008h, 000h   ; and dword ptr [ecx + 8], 0
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
$L_35b54e:
        db 040h   ; inc eax
        db 083h, 0F8h, 004h   ; cmp eax, 4
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
        db 072h, 0CCh   ; jb 0x35b523
        db 080h, 04Bh, 033h, 0C0h   ; or byte ptr [ebx + 0x33], 0xc0
        db 0C7h, 043h, 034h, 005h, 020h, 015h, 080h   ; mov dword ptr [ebx + 0x34], 0x80152005
$L_35b562:
        db 0C7h, 043h, 010h, 000h, 013h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151300
        db 0E9h, 058h, 0F3h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b56e:
        db 080h, 04Bh, 033h, 0C0h   ; or byte ptr [ebx + 0x33], 0xc0
        db 089h, 07Bh, 034h   ; mov dword ptr [ebx + 0x34], edi
        db 03Bh, 09Eh, 0CCh, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xcc]
        db 075h, 058h   ; jne 0x35b5d5
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35b581:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 06Bh, 0C9h, 070h   ; imul ecx, ecx, 0x70
        db 08Bh, 08Ch, 019h, 038h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + ebx + 0x138]
        db 089h, 08Ch, 083h, 0BCh, 000h, 000h, 000h   ; mov dword ptr [ebx + eax*4 + 0xbc], ecx
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0E1h   ; jb 0x35b581
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0C7h, 043h, 010h, 000h, 013h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151300
        call ?XnLogoff@CXoBase@@QAEXXZ   ; 0x37948E
        db 083h, 065h, 07Ch, 000h   ; and dword ptr [ebp + 0x7c], 0
$L_35b5b2:
        db 08Bh, 045h, 07Ch   ; mov eax, dword ptr [ebp + 0x7c]
        db 08Dh, 004h, 0C0h   ; lea eax, [eax + eax*8]
        db 08Bh, 084h, 0C6h, 0E0h, 013h, 000h, 000h   ; mov eax, dword ptr [esi + eax*8 + 0x13e0]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 004h   ; je 0x35b5c7
        db 083h, 060h, 008h, 000h   ; and dword ptr [eax + 8], 0
$L_35b5c7:
        db 0FFh, 045h, 07Ch   ; inc dword ptr [ebp + 0x7c]
        db 083h, 07Dh, 07Ch, 004h   ; cmp dword ptr [ebp + 0x7c], 4
        db 072h, 0E2h   ; jb 0x35b5b2
        db 0E9h, 0F1h, 0F2h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b5d5:
        db 033h, 0C0h   ; xor eax, eax
        db 081h, 0FFh, 001h, 020h, 015h, 080h   ; cmp edi, 0x80152001
        db 00Fh, 095h, 0C0h   ; setne al
        db 048h   ; dec eax
        db 025h, 0F4h, 0F6h, 0FFh, 0FFh   ; and eax, 0xfffff6f4
        db 005h, 00Fh, 019h, 015h, 080h   ; add eax, 0x8015190f
        db 0EBh, 03Fh   ; jmp 0x35b62c
$L_35b5ed:
        db 083h, 07Dh, 060h, 002h   ; cmp dword ptr [ebp + 0x60], 2
        db 00Fh, 085h, 01Bh, 0FFh, 0FFh, 0FFh   ; jne 0x35b512
        db 03Bh, 09Eh, 0C8h, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xc8]
        db 00Fh, 085h, 00Fh, 0FFh, 0FFh, 0FFh   ; jne 0x35b512
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?ClearServiceTicketCache@CXo@@IAEXXZ   ; 0x359DC1
        db 0C7h, 043h, 010h, 005h, 010h, 015h, 080h   ; mov dword ptr [ebx + 0x10], 0x80151005
        db 0E9h, 0B0h, 0F2h, 0FFh, 0FFh   ; jmp 0x35a8c6
$L_35b616:
        db 033h, 0C0h   ; xor eax, eax
        db 03Bh, 09Eh, 0C8h, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xc8]
        db 00Fh, 095h, 0C0h   ; setne al
        db 048h   ; dec eax
        db 025h, 00Eh, 006h, 000h, 000h   ; and eax, 0x60e
        db 005h, 000h, 013h, 015h, 080h   ; add eax, 0x80151300
$L_35b62c:
        db 089h, 043h, 010h   ; mov dword ptr [ebx + 0x10], eax
        db 0E9h, 092h, 0F2h, 0FFh, 0FFh   ; jmp 0x35a8c6
seg18 ENDS




seg37 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: _sub_3613FE @ 0x003613FE
PUBLIC _sub_3613FE
_sub_3613FE:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 010h   ; sub esp, 0x10
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 033h, 0F6h   ; xor esi, esi
        db 03Bh, 0DEh   ; cmp ebx, esi
        db 089h, 05Dh, 0FCh   ; mov dword ptr [ebp - 4], ebx
        db 075h, 00Ah   ; jne 0x36141b
        db 0B8h, 005h, 000h, 015h, 080h   ; mov eax, 0x80150005
        db 0E9h, 039h, 003h, 000h, 000h   ; jmp 0x361754
$L_36141b:
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 039h, 0B3h, 0D0h, 014h, 000h, 000h   ; cmp dword ptr [ebx + 0x14d0], esi
        db 057h   ; push edi
        db 089h, 075h, 0F0h   ; mov dword ptr [ebp - 0x10], esi
        db 075h, 00Ah   ; jne 0x361436
        db 0BFh, 00Ch, 020h, 015h, 080h   ; mov edi, 0x8015200c
        db 0E9h, 01Bh, 003h, 000h, 000h   ; jmp 0x361751
$L_361436:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 06Ah, 003h   ; push 3
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 050h   ; push eax
        call ?PresenceCreateContext@CXo@@IAEJPAPAUXPRESENCE_EXTENDED_HANDLE@@PAXW4XPRESENCE_REQUESTTYPE@@K@Z   ; 0x36112D
        db 08Bh, 0F8h   ; mov edi, eax
        db 03Bh, 0FEh   ; cmp edi, esi
        db 08Bh, 075h, 0F0h   ; mov esi, dword ptr [ebp - 0x10]
        db 00Fh, 08Ch, 0E8h, 002h, 000h, 000h   ; jl 0x36173e
        db 0EBh, 060h   ; jmp 0x3614b8
$L_361458:
        db 08Bh, 083h, 0D0h, 014h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x14d0]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 012h   ; je 0x361474
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call _sub_356E16   ; 0x356E16
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 0CAh, 002h, 000h, 000h   ; jl 0x36173e
$L_361474:
        db 083h, 065h, 0F8h, 000h   ; and dword ptr [ebp - 8], 0
        db 08Dh, 083h, 0B4h, 013h, 000h, 000h   ; lea eax, [ebx + 0x13b4]
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
$L_361481:
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 08Bh, 040h, 028h   ; mov eax, dword ptr [eax + 0x28]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 020h   ; je 0x3614ab
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call _sub_356E16   ; 0x356E16
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 0A1h, 002h, 000h, 000h   ; jl 0x36173e
        db 081h, 0FFh, 0F1h, 000h, 015h, 000h   ; cmp edi, 0x1500f1
        db 075h, 006h   ; jne 0x3614ab
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 083h, 008h, 008h   ; or dword ptr [eax], 8
$L_3614ab:
        db 0FFh, 045h, 0F8h   ; inc dword ptr [ebp - 8]
        db 083h, 045h, 0F4h, 048h   ; add dword ptr [ebp - 0xc], 0x48
        db 083h, 07Dh, 0F8h, 004h   ; cmp dword ptr [ebp - 8], 4
        db 072h, 0C9h   ; jb 0x361481
$L_3614b8:
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 056h   ; push esi
        call ?FriendlistCacheOpen@CXo@@IAEJPAUXPRESENCE_EXTENDED_HANDLE@@@Z   ; 0x35DB90
        db 08Bh, 0F8h   ; mov edi, eax
        db 083h, 0FFh, 001h   ; cmp edi, 1
        db 074h, 091h   ; je 0x361458
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 06Fh, 002h, 000h, 000h   ; jl 0x36173e
$L_3614cf:
        db 0FFh, 0B3h, 0D8h, 014h, 000h, 000h   ; push dword ptr [ebx + 0x14d8]
        db 08Bh, 0CBh   ; mov ecx, ebx
        call _sub_356E16   ; 0x356E16
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 074h, 0EDh   ; je 0x3614cf
        db 00Fh, 08Ch, 056h, 002h, 000h, 000h   ; jl 0x36173e
        db 068h, 033h, 020h, 000h, 000h   ; push 0x2033
        db 068h, 080h, 02Dh, 000h, 000h   ; push 0x2d80
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SysAllocZ@CXo@@IAEPAXIK@Z   ; 0x3698D9
        db 085h, 0C0h   ; test eax, eax
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 08Dh, 00Ch, 0C9h   ; lea ecx, [ecx + ecx*8]
        db 08Dh, 01Ch, 0CBh   ; lea ebx, [ebx + ecx*8]
        db 089h, 083h, 0D4h, 013h, 000h, 000h   ; mov dword ptr [ebx + 0x13d4], eax
        db 00Fh, 084h, 0D4h, 001h, 000h, 000h   ; je 0x3616e4
        db 08Bh, 08Bh, 0A8h, 013h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x13a8]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 08Bh, 08Bh, 0ACh, 013h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x13ac]
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 04Eh, 01Ch   ; lea ecx, [esi + 0x1c]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 08Bh, 083h, 0D4h, 013h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x13d4]
        db 089h, 046h, 024h   ; mov dword ptr [esi + 0x24], eax
        db 08Bh, 083h, 0D4h, 013h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x13d4]
        db 051h   ; push ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 0C7h, 046h, 028h, 080h, 02Dh, 000h, 000h   ; mov dword ptr [esi + 0x28], 0x2d80
        db 0FFh, 0B1h, 0D4h, 014h, 000h, 000h   ; push dword ptr [ecx + 0x14d4]
        call ?CacheLookup@CXo@@IAEJPAXPAUXONLC_CONTEXT@@@Z   ; 0x367DF0
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 0DCh, 001h, 000h, 000h   ; jl 0x36173b
        db 08Dh, 046h, 01Ch   ; lea eax, [esi + 0x1c]
        db 083h, 038h, 000h   ; cmp dword ptr [eax], 0
        db 00Fh, 084h, 0CBh, 001h, 000h, 000h   ; je 0x361736
        db 083h, 07Eh, 020h, 000h   ; cmp dword ptr [esi + 0x20], 0
        db 074h, 01Fh   ; je 0x361590
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 050h   ; push eax
        db 0FFh, 0B1h, 0D8h, 014h, 000h, 000h   ; push dword ptr [ecx + 0x14d8]
        db 0FFh, 0B1h, 0D4h, 014h, 000h, 000h   ; push dword ptr [ecx + 0x14d4]
        call ?CacheRetrieve@CXo@@IAEJPAXPAUXONLINETASK_HANDLE__@@PAUXONLC_CONTEXT@@@Z   ; 0x36829B
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 0ABh, 001h, 000h, 000h   ; jl 0x36173b
$L_361590:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 0FFh, 0B1h, 0D8h, 014h, 000h, 000h   ; push dword ptr [ecx + 0x14d8]
        call _sub_356E16   ; 0x356E16
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 074h, 0ECh   ; je 0x361590
        db 00Fh, 08Ch, 091h, 001h, 000h, 000h   ; jl 0x36173b
        db 08Bh, 083h, 0B4h, 013h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x13b4]
        db 0A8h, 002h   ; test al, 2
        db 08Bh, 0BBh, 0D4h, 013h, 000h, 000h   ; mov edi, dword ptr [ebx + 0x13d4]
        db 089h, 07Dh, 0F4h   ; mov dword ptr [ebp - 0xc], edi
        db 074h, 050h   ; je 0x36160d
        db 083h, 0E0h, 0F9h   ; and eax, 0xfffffff9
        db 033h, 0D2h   ; xor edx, edx
        db 089h, 083h, 0B4h, 013h, 000h, 000h   ; mov dword ptr [ebx + 0x13b4], eax
        db 066h, 039h, 057h, 00Ch   ; cmp word ptr [edi + 0xc], dx
        db 076h, 034h   ; jbe 0x361602
        db 08Dh, 04Fh, 04Ch   ; lea ecx, [edi + 0x4c]
$L_3615d1:
        db 081h, 021h, 000h, 000h, 000h, 0C0h   ; and dword ptr [ecx], 0xc0000000
        db 083h, 061h, 014h, 000h   ; and dword ptr [ecx + 0x14], 0
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 079h, 00Ch   ; lea edi, [ecx + 0xc]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 079h, 004h   ; lea edi, [ecx + 4]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 079h, 04Ch   ; lea edi, [ecx + 0x4c]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 00Fh, 0B7h, 040h, 00Ch   ; movzx eax, word ptr [eax + 0xc]
        db 042h   ; inc edx
        db 083h, 0C1h, 074h   ; add ecx, 0x74
        db 03Bh, 0D0h   ; cmp edx, eax
        db 072h, 0D2h   ; jb 0x3615d1
        db 08Bh, 07Dh, 0F4h   ; mov edi, dword ptr [ebp - 0xc]
$L_361602:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 057h   ; push edi
        call ?SortFriends@CXo@@IAEJPAUXPRESENCE_FRIEND_LIST@@@Z   ; 0x35EFE9
        db 0EBh, 016h   ; jmp 0x361623
$L_36160d:
        db 0A8h, 004h   ; test al, 4
        db 074h, 012h   ; je 0x361623
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 083h, 0E0h, 0FBh   ; and eax, 0xfffffffb
        db 057h   ; push edi
        db 089h, 083h, 0B4h, 013h, 000h, 000h   ; mov dword ptr [ebx + 0x13b4], eax
        call ?ClearSentInvites@CXo@@IAEXPAUXPRESENCE_FRIEND_LIST@@@Z   ; 0x35F969
$L_361623:
        db 083h, 065h, 0F8h, 000h   ; and dword ptr [ebp - 8], 0
        db 066h, 083h, 07Fh, 00Ch, 000h   ; cmp word ptr [edi + 0xc], 0
        db 076h, 042h   ; jbe 0x361670
        db 08Dh, 047h, 04Ch   ; lea eax, [edi + 0x4c]
$L_361631:
        db 06Ah, 002h   ; push 2
        db 059h   ; pop ecx
        db 0BFh   ; mov edi, 0x5082a8
        dd _unk_5082A8
        db 08Dh, 0B3h, 0BCh, 013h, 000h, 000h   ; lea esi, [ebx + 0x13bc]
        db 033h, 0D2h   ; xor edx, edx
        db 0F3h, 0A7h   ; repe cmpsd dword ptr [esi], dword ptr es:[edi]
        db 074h, 016h   ; je 0x36165b
        db 06Ah, 002h   ; push 2
        db 059h   ; pop ecx
        db 08Dh, 0BBh, 0BCh, 013h, 000h, 000h   ; lea edi, [ebx + 0x13bc]
        db 08Dh, 070h, 00Ch   ; lea esi, [eax + 0xc]
        db 033h, 0D2h   ; xor edx, edx
        db 0F3h, 0A7h   ; repe cmpsd dword ptr [esi], dword ptr es:[edi]
        db 075h, 004h   ; jne 0x36165b
        db 080h, 060h, 003h, 0C3h   ; and byte ptr [eax + 3], 0xc3
$L_36165b:
        db 08Bh, 04Dh, 0F4h   ; mov ecx, dword ptr [ebp - 0xc]
        db 00Fh, 0B7h, 049h, 00Ch   ; movzx ecx, word ptr [ecx + 0xc]
        db 0FFh, 045h, 0F8h   ; inc dword ptr [ebp - 8]
        db 083h, 0C0h, 074h   ; add eax, 0x74
        db 039h, 04Dh, 0F8h   ; cmp dword ptr [ebp - 8], ecx
        db 072h, 0C4h   ; jb 0x361631
        db 08Bh, 075h, 0F0h   ; mov esi, dword ptr [ebp - 0x10]
$L_361670:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 056h   ; push esi
        call ?FriendlistCacheClose@CXo@@IAEJPBUXPRESENCE_EXTENDED_HANDLE@@@Z   ; 0x35DBD2
$L_361679:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 0FFh, 0B1h, 0D8h, 014h, 000h, 000h   ; push dword ptr [ecx + 0x14d8]
        call _sub_356E16   ; 0x356E16
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 074h, 0ECh   ; je 0x361679
        db 00Fh, 08Ch, 0A8h, 000h, 000h, 000h   ; jl 0x36173b
        db 08Bh, 07Dh, 0FCh   ; mov edi, dword ptr [ebp - 4]
        db 056h   ; push esi
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?FriendlistCacheCleanup@CXo@@IAEXPAUXPRESENCE_EXTENDED_HANDLE@@@Z   ; 0x35DBF8
        db 083h, 0A3h, 0B4h, 013h, 000h, 000h, 0D7h   ; and dword ptr [ebx + 0x13b4], 0xffffffd7
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 0C7h, 046h, 010h, 005h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 5
        call _SetEvent@4   ; 0x22CEB7
        db 06Ah, 034h   ; push 0x34
        db 058h   ; pop eax
        db 06Ah, 020h   ; push 0x20
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 046h, 044h   ; mov dword ptr [esi + 0x44], eax
        call ?SysAlloc@CXo@@IAEPAXIK@Z   ; 0x3698D4
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 040h   ; mov dword ptr [esi + 0x40], eax
        db 074h, 019h   ; je 0x3616e4
        db 0B8h, 000h, 008h, 000h, 000h   ; mov eax, 0x800
        db 06Ah, 020h   ; push 0x20
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 046h, 04Ch   ; mov dword ptr [esi + 0x4c], eax
        call ?SysAlloc@CXo@@IAEPAXIK@Z   ; 0x3698D4
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 048h   ; mov dword ptr [esi + 0x48], eax
        db 075h, 007h   ; jne 0x3616eb
$L_3616e4:
        db 0BFh, 00Eh, 000h, 007h, 080h   ; mov edi, 0x8007000e
        db 0EBh, 050h   ; jmp 0x36173b
$L_3616eb:
        db 08Dh, 046h, 060h   ; lea eax, [esi + 0x60]
        db 050h   ; push eax
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?XOnlineTitleNameStartup@CXo@@QAEJPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x35D2D5
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 07Ch, 03Ch   ; jl 0x36173b
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 056h   ; push esi
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 06Ah, 000h   ; push 0
        db 068h   ; push 0x35f1db
        dd ?FriendsNotifyCallback@CXo@@IAEHPAXKHPBUQ_MESSAGE_SUMMARY@@@Z
        call ?MessagingRequestNotifications@CXo@@IAEXP81@AEHPAXKHPBUQ_MESSAGE_SUMMARY@@@ZP81@AEX0K1PAUXONLINETASK_HANDLE__@@@ZK0@Z   ; 0x36D203
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 074h, 011h   ; je 0x361729
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call ?XnLogonSetQEvent@CXoBase@@QAEIIPAX@Z   ; 0x379453
        db 089h, 046h, 054h   ; mov dword ptr [esi + 0x54], eax
$L_361729:
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 089h, 0B3h, 0DCh, 013h, 000h, 000h   ; mov dword ptr [ebx + 0x13dc], esi
        db 0EBh, 01Bh   ; jmp 0x361751
$L_361736:
        db 0BFh, 005h, 040h, 000h, 080h   ; mov edi, 0x80004005
$L_36173b:
        db 08Bh, 05Dh, 0FCh   ; mov ebx, dword ptr [ebp - 4]
$L_36173e:
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Fh   ; je 0x361751
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0C7h, 046h, 010h, 00Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 0xc
        call ?FriendsEnumerateClose@CXo@@IAEXPAUXONLINETASK_HANDLE__@@@Z   ; 0x35F2A1
$L_361751:
        db 08Bh, 0C7h   ; mov eax, edi
        db 05Fh   ; pop edi
$L_361754:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg37 ENDS


seg41 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?xrldlSendHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z @ 0x003620E9
PUBLIC ?xrldlSendHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
?xrldlSendHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 00Ch   ; mov esi, dword ptr [esp + 0xc]
        db 057h   ; push edi
        db 08Dh, 07Eh, 070h   ; lea edi, [esi + 0x70]
        db 057h   ; push edi
        db 08Bh, 0D9h   ; mov ebx, ecx
        call _sub_356E16   ; 0x356E16
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 08Eh, 000h, 000h, 000h   ; je 0x362191
        db 07Ch, 04Bh   ; jl 0x362150
        db 0F6h, 046h, 01Ah, 010h   ; test byte ptr [esi + 0x1a], 0x10
        db 075h, 006h   ; jne 0x362111
        db 080h, 07Eh, 034h, 000h   ; cmp byte ptr [esi + 0x34], 0
        db 075h, 00Dh   ; jne 0x36211e
$L_362111:
        db 06Ah, 001h   ; push 1
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        call _shutdown   ; 0x376FEB
$L_36211e:
        db 08Bh, 08Eh, 0B4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xb4]
        db 057h   ; push edi
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 08Dh, 086h, 0A8h, 000h, 000h, 000h   ; lea eax, [esi + 0xa8]
        db 06Ah, 000h   ; push 0
        db 06Ah, 001h   ; push 1
        db 050h   ; push eax
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 06Ah, 000h   ; push 0
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 00Ch   ; jge 0x36215c
$L_362150:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0C7h, 046h, 014h, 007h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 7
        db 0EBh, 035h   ; jmp 0x362191
$L_36215c:
        db 080h, 04Eh, 01Bh, 020h   ; or byte ptr [esi + 0x1b], 0x20
        db 0F6h, 046h, 01Ah, 080h   ; test byte ptr [esi + 0x1a], 0x80
        db 074h, 013h   ; je 0x362179
        db 08Bh, 086h, 0B4h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb4]
        db 083h, 0A6h, 0D4h, 000h, 000h, 000h, 000h   ; and dword ptr [esi + 0xd4], 0
        db 089h, 086h, 0D0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd0], eax
$L_362179:
        db 083h, 0A6h, 0F0h, 000h, 000h, 000h, 000h   ; and dword ptr [esi + 0xf0], 0
        db 0C7h, 046h, 014h, 004h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 4
        db 0C7h, 086h, 0F4h, 000h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xf4], 1
$L_362191:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 033h, 0C0h   ; xor eax, eax
        db 05Bh   ; pop ebx
        db 0C2h, 004h, 000h   ; ret 4

seg41 ENDS

seg81 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?xrldlProcessDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z @ 0x0036238C
PUBLIC ?xrldlProcessDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
?xrldlProcessDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 00Ch   ; mov esi, dword ptr [esp + 0xc]
        db 0FFh, 0B6h, 020h, 001h, 000h, 000h   ; push dword ptr [esi + 0x120]
        db 08Bh, 0D9h   ; mov ebx, ecx
        call _sub_356E16   ; 0x356E16
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 0B3h, 000h, 000h, 000h   ; je 0x36245a
        db 00Fh, 08Ch, 096h, 000h, 000h, 000h   ; jl 0x362443
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0FFh, 096h, 010h, 001h, 000h, 000h   ; call dword ptr [esi + 0x110]
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 085h, 000h, 000h, 000h   ; jl 0x362443
        db 075h, 036h   ; jne 0x3623f6
        db 06Ah, 002h   ; push 2
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        call _shutdown   ; 0x376FEB
        db 08Bh, 086h, 024h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x124]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 06Fh   ; je 0x362446
        db 08Bh, 096h, 014h, 001h, 000h, 000h   ; mov edx, dword ptr [esi + 0x114]
        db 085h, 0D2h   ; test edx, edx
        db 074h, 00Ch   ; je 0x3623ed
        db 050h   ; push eax
        db 056h   ; push esi
        db 06Ah, 002h   ; push 2
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0FFh, 0D2h   ; call edx
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 056h   ; jl 0x362443
$L_3623ed:
        db 0C7h, 046h, 014h, 006h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 6
        db 0EBh, 064h   ; jmp 0x36245a
$L_3623f6:
        db 08Bh, 08Eh, 0F0h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xf0]
        db 08Bh, 086h, 0B0h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb0]
        db 08Bh, 096h, 0B4h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xb4]
        db 057h   ; push edi
        db 08Dh, 07Eh, 070h   ; lea edi, [esi + 0x70]
        db 057h   ; push edi
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 003h, 0C1h   ; add eax, ecx
        db 06Ah, 000h   ; push 0
        db 089h, 086h, 0ACh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xac], eax
        db 08Dh, 086h, 0A8h, 000h, 000h, 000h   ; lea eax, [esi + 0xa8]
        db 06Ah, 001h   ; push 1
        db 050h   ; push eax
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        db 02Bh, 0D1h   ; sub edx, ecx
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 010h   ; mov dword ptr [eax], edx
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 06Ah, 000h   ; push 0
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 085h, 0C0h   ; test eax, eax
        db 05Fh   ; pop edi
        db 07Dh, 00Ch   ; jge 0x36244f
$L_362443:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
$L_362446:
        db 0C7h, 046h, 014h, 007h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 7
        db 0EBh, 00Bh   ; jmp 0x36245a
$L_36244f:
        db 080h, 04Eh, 01Bh, 020h   ; or byte ptr [esi + 0x1b], 0x20
        db 0C7h, 046h, 014h, 004h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 4
$L_36245a:
        db 05Eh   ; pop esi
        db 033h, 0C0h   ; xor eax, eax
        db 05Bh   ; pop ebx
        db 0C2h, 004h, 000h   ; ret 4
seg81 ENDS

seg43 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?xrlulsResponseHeaders@CXo@@IAEJPAX@Z @ 0x00362786
PUBLIC ?xrlulsResponseHeaders@CXo@@IAEJPAX@Z
?xrlulsResponseHeaders@CXo@@IAEJPAX@Z:
        db 033h, 0C0h   ; xor eax, eax
        db 0C2h, 004h, 000h   ; ret 4
seg43 ENDS

seg45 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?xrlulSendDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z @ 0x00362A70
PUBLIC ?xrlulSendDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
?xrlulSendDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 057h   ; push edi
        db 08Dh, 07Eh, 070h   ; lea edi, [esi + 0x70]
        db 057h   ; push edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        call _sub_356E16   ; 0x356E16
        db 033h, 0DBh   ; xor ebx, ebx
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 084h, 096h, 001h, 000h, 000h   ; je 0x362c26
        db 00Fh, 08Ch, 07Dh, 001h, 000h, 000h   ; jl 0x362c13
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 057h   ; push edi
        call ?GetSendRecvResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAK1PAPAU_WSABUF@@@Z   ; 0x369ABB
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 066h, 001h, 000h, 000h   ; jl 0x362c13
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 0A8h, 002h   ; test al, 2
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 074h, 010h   ; je 0x362ac7
        db 08Dh, 08Eh, 0F4h, 000h, 000h, 000h   ; lea ecx, [esi + 0xf4]
        db 02Bh, 011h   ; sub edx, dword ptr [ecx]
        db 083h, 0E0h, 0FDh   ; and eax, 0xfffffffd
        db 089h, 019h   ; mov dword ptr [ecx], ebx
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
$L_362ac7:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 086h, 0E0h, 000h, 000h, 000h   ; lea eax, [esi + 0xe0]
        db 001h, 010h   ; add dword ptr [eax], edx
        db 056h   ; push esi
        db 011h, 058h, 004h   ; adc dword ptr [eax + 4], ebx
        db 0FFh, 096h, 004h, 001h, 000h, 000h   ; call dword ptr [esi + 0x104]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 02Fh, 001h, 000h, 000h   ; jl 0x362c13
        db 00Fh, 085h, 0B7h, 000h, 000h, 000h   ; jne 0x362ba1
        db 033h, 0FFh   ; xor edi, edi
        db 047h   ; inc edi
        db 0F6h, 046h, 01Ah, 010h   ; test byte ptr [esi + 0x1a], 0x10
        db 075h, 005h   ; jne 0x362af8
        db 038h, 05Eh, 034h   ; cmp byte ptr [esi + 0x34], bl
        db 075h, 00Ch   ; jne 0x362b04
$L_362af8:
        db 057h   ; push edi
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        call _shutdown   ; 0x376FEB
$L_362b04:
        db 08Bh, 086h, 0B0h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb0]
        db 08Bh, 08Eh, 0B4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xb4]
        db 089h, 086h, 0ACh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xac], eax
        db 08Dh, 086h, 0A8h, 000h, 000h, 000h   ; lea eax, [esi + 0xa8]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 08Dh, 04Eh, 070h   ; lea ecx, [esi + 0x70]
        db 051h   ; push ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 057h   ; push edi
        db 050h   ; push eax
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 08Dh, 046h, 070h   ; lea eax, [esi + 0x70]
        db 050h   ; push eax
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 0C8h, 000h, 000h, 000h   ; jl 0x362c13
        db 080h, 04Eh, 01Bh, 020h   ; or byte ptr [esi + 0x1b], 0x20
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 0A9h, 000h, 000h, 080h, 000h   ; test eax, 0x800000
        db 089h, 09Eh, 0D8h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd8], ebx
        db 089h, 09Eh, 0DCh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xdc], ebx
        db 089h, 09Eh, 0D4h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd4], ebx
        db 074h, 00Eh   ; je 0x362b79
        db 08Bh, 08Eh, 0B4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xb4]
        db 089h, 08Eh, 0D0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd0], ecx
        db 0EBh, 006h   ; jmp 0x362b7f
$L_362b79:
        db 089h, 09Eh, 0D0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd0], ebx
$L_362b7f:
        db 025h   ; and eax, 0x400000
        dd _unk_400000
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 0F7h, 0D8h   ; neg eax
        db 083h, 0C0h, 005h   ; add eax, 5
        db 089h, 09Eh, 0F0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xf0], ebx
        db 089h, 0BEh, 0F4h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xf4], edi
        db 089h, 046h, 014h   ; mov dword ptr [esi + 0x14], eax
        db 0E9h, 085h, 000h, 000h, 000h   ; jmp 0x362c26
$L_362ba1:
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Dh, 08Eh, 0A8h, 000h, 000h, 000h   ; lea ecx, [esi + 0xa8]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 03Bh, 0D0h   ; cmp edx, eax
        db 073h, 039h   ; jae 0x362be9
        db 001h, 096h, 0ACh, 000h, 000h, 000h   ; add dword ptr [esi + 0xac], edx
        db 057h   ; push edi
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 033h, 0FFh   ; xor edi, edi
        db 053h   ; push ebx
        db 047h   ; inc edi
        db 057h   ; push edi
        db 051h   ; push ecx
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        db 02Bh, 0C2h   ; sub eax, edx
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 057h   ; push edi
        db 08Dh, 046h, 070h   ; lea eax, [esi + 0x70]
        db 050h   ; push eax
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 07Ch, 030h   ; jl 0x362c13
        db 080h, 04Eh, 01Bh, 020h   ; or byte ptr [esi + 0x1b], 0x20
        db 0EBh, 03Dh   ; jmp 0x362c26
$L_362be9:
        db 08Bh, 086h, 0B0h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb0]
        db 089h, 086h, 0ACh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xac], eax
        db 089h, 019h   ; mov dword ptr [ecx], ebx
        db 08Bh, 086h, 00Ch, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x10c]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 01Eh   ; je 0x362c1f
        db 0FFh, 0B6h, 018h, 001h, 000h, 000h   ; push dword ptr [esi + 0x118]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 056h   ; push esi
        db 06Ah, 001h   ; push 1
        db 0FFh, 0D0h   ; call eax
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 07Dh, 00Ch   ; jge 0x362c1f
$L_362c13:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0C7h, 046h, 014h, 009h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 9
        db 0EBh, 009h   ; jmp 0x362c28
$L_362c1f:
        db 0C7h, 046h, 014h, 003h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 3
$L_362c26:
        db 033h, 0C0h   ; xor eax, eax
$L_362c28:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?xrlulReceiveStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z @ 0x00362C2F
PUBLIC ?xrlulReceiveStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
?xrlulReceiveStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 057h   ; push edi
        db 08Dh, 046h, 070h   ; lea eax, [esi + 0x70]
        db 050h   ; push eax
        db 08Bh, 0D9h   ; mov ebx, ecx
        call _sub_356E16   ; 0x356E16
        db 033h, 0FFh   ; xor edi, edi
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 07Bh, 001h, 000h, 000h   ; je 0x362dc9
        db 00Fh, 08Ch, 065h, 001h, 000h, 000h   ; jl 0x362db9
        db 057h   ; push edi
        db 057h   ; push edi
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Dh, 046h, 070h   ; lea eax, [esi + 0x70]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?GetSendRecvResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAK1PAPAU_WSABUF@@@Z   ; 0x369ABB
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 04Ch, 001h, 000h, 000h   ; jl 0x362db9
        db 039h, 07Dh, 008h   ; cmp dword ptr [ebp + 8], edi
        db 074h, 05Fh   ; je 0x362cd1
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 056h   ; push esi
        call ?XRL_ProcessHttp@CXo@@IAEJPAUXRL_ASYNC@@KPAH@Z   ; 0x3693A1
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 030h, 001h, 000h, 000h   ; jl 0x362db9
        db 039h, 07Dh, 0FCh   ; cmp dword ptr [ebp - 4], edi
        db 074h, 024h   ; je 0x362cb2
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0FFh, 096h, 008h, 001h, 000h, 000h   ; call dword ptr [esi + 0x108]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 01Ah, 001h, 000h, 000h   ; jl 0x362db9
        db 08Bh, 096h, 0F0h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xf0]
        db 08Dh, 08Eh, 0D8h, 000h, 000h, 000h   ; lea ecx, [esi + 0xd8]
        db 001h, 011h   ; add dword ptr [ecx], edx
        db 011h, 079h, 004h   ; adc dword ptr [ecx + 4], edi
        db 0EBh, 044h   ; jmp 0x362cf6
$L_362cb2:
        db 0F6h, 086h, 0F4h, 000h, 000h, 000h, 003h   ; test byte ptr [esi + 0xf4], 3
        db 075h, 03Bh   ; jne 0x362cf6
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Dh, 08Eh, 0D8h, 000h, 000h, 000h   ; lea ecx, [esi + 0xd8]
        db 001h, 011h   ; add dword ptr [ecx], edx
        db 011h, 079h, 004h   ; adc dword ptr [ecx + 4], edi
        db 001h, 096h, 0F0h, 000h, 000h, 000h   ; add dword ptr [esi + 0xf0], edx
        db 0EBh, 025h   ; jmp 0x362cf6
$L_362cd1:
        db 0F6h, 046h, 01Ah, 080h   ; test byte ptr [esi + 0x1a], 0x80
        db 074h, 01Ah   ; je 0x362cf1
        db 08Bh, 08Eh, 0D8h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xd8]
        db 089h, 08Eh, 0D0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd0], ecx
        db 08Bh, 08Eh, 0DCh, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xdc]
        db 089h, 08Eh, 0D4h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd4], ecx
        db 0EBh, 005h   ; jmp 0x362cf6
$L_362cf1:
        db 0B8h, 046h, 027h, 007h, 080h   ; mov eax, 0x80072746
$L_362cf6:
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 08Ch, 0BBh, 000h, 000h, 000h   ; jl 0x362db9
        db 0F6h, 086h, 0F4h, 000h, 000h, 000h, 003h   ; test byte ptr [esi + 0xf4], 3
        db 075h, 066h   ; jne 0x362d6d
        db 08Dh, 086h, 0D8h, 000h, 000h, 000h   ; lea eax, [esi + 0xd8]
        db 08Bh, 048h, 004h   ; mov ecx, dword ptr [eax + 4]
        db 03Bh, 08Eh, 0D4h, 000h, 000h, 000h   ; cmp ecx, dword ptr [esi + 0xd4]
        db 077h, 016h   ; ja 0x362d2e
        db 072h, 00Ah   ; jb 0x362d24
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 03Bh, 08Eh, 0D0h, 000h, 000h, 000h   ; cmp ecx, dword ptr [esi + 0xd0]
        db 073h, 00Ah   ; jae 0x362d2e
$L_362d24:
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 03Bh, 086h, 0B4h, 000h, 000h, 000h   ; cmp eax, dword ptr [esi + 0xb4]
        db 072h, 03Fh   ; jb 0x362d6d
$L_362d2e:
        db 06Ah, 002h   ; push 2
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        call _shutdown   ; 0x376FEB
        db 08Bh, 086h, 01Ch, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x11c]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 074h, 01Fh   ; je 0x362d64
        db 08Bh, 096h, 00Ch, 001h, 000h, 000h   ; mov edx, dword ptr [esi + 0x10c]
        db 03Bh, 0D7h   ; cmp edx, edi
        db 074h, 00Ch   ; je 0x362d5b
        db 050h   ; push eax
        db 056h   ; push esi
        db 06Ah, 002h   ; push 2
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0FFh, 0D2h   ; call edx
        db 03Bh, 0C7h   ; cmp eax, edi
        db 07Ch, 05Eh   ; jl 0x362db9
$L_362d5b:
        db 0C7h, 046h, 014h, 008h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 8
        db 0EBh, 065h   ; jmp 0x362dc9
$L_362d64:
        db 0C7h, 046h, 014h, 009h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 9
        db 0EBh, 05Ch   ; jmp 0x362dc9
$L_362d6d:
        db 08Bh, 08Eh, 0F0h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xf0]
        db 08Bh, 086h, 0B0h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb0]
        db 08Bh, 096h, 0B4h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xb4]
        db 003h, 0C1h   ; add eax, ecx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 08Dh, 04Eh, 070h   ; lea ecx, [esi + 0x70]
        db 051h   ; push ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 089h, 086h, 0ACh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xac], eax
        db 057h   ; push edi
        db 08Dh, 086h, 0A8h, 000h, 000h, 000h   ; lea eax, [esi + 0xa8]
        db 06Ah, 001h   ; push 1
        db 050h   ; push eax
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 010h   ; mov dword ptr [eax], edx
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 057h   ; push edi
        db 08Dh, 046h, 070h   ; lea eax, [esi + 0x70]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 03Bh, 0C7h   ; cmp eax, edi
        db 07Dh, 00Ch   ; jge 0x362dc5
$L_362db9:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0C7h, 046h, 014h, 009h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 9
        db 0EBh, 006h   ; jmp 0x362dcb
$L_362dc5:
        db 080h, 04Eh, 01Bh, 020h   ; or byte ptr [esi + 0x1b], 0x20
$L_362dc9:
        db 033h, 0C0h   ; xor eax, eax
$L_362dcb:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?xrlulReceivePagedStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z @ 0x00362DD2
PUBLIC ?xrlulReceivePagedStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
?xrlulReceivePagedStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 057h   ; push edi
        db 08Dh, 07Eh, 070h   ; lea edi, [esi + 0x70]
        db 057h   ; push edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        call _sub_356E16   ; 0x356E16
        db 033h, 0DBh   ; xor ebx, ebx
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 084h, 06Fh, 001h, 000h, 000h   ; je 0x362f62
        db 00Fh, 08Ch, 059h, 001h, 000h, 000h   ; jl 0x362f52
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 057h   ; push edi
        call ?GetSendRecvResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAK1PAPAU_WSABUF@@@Z   ; 0x369ABB
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 042h, 001h, 000h, 000h   ; jl 0x362f52
        db 039h, 05Dh, 008h   ; cmp dword ptr [ebp + 8], ebx
        db 074h, 061h   ; je 0x362e76
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 056h   ; push esi
        call ?XRL_ProcessHttp@CXo@@IAEJPAUXRL_ASYNC@@KPAH@Z   ; 0x3693A1
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 025h, 001h, 000h, 000h   ; jl 0x362f52
        db 039h, 05Dh, 0F8h   ; cmp dword ptr [ebp - 8], ebx
        db 074h, 025h   ; je 0x362e57
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 056h   ; push esi
        db 0FFh, 096h, 008h, 001h, 000h, 000h   ; call dword ptr [esi + 0x108]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 00Eh, 001h, 000h, 000h   ; jl 0x362f52
        db 08Bh, 096h, 0F0h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xf0]
        db 08Dh, 08Eh, 0D8h, 000h, 000h, 000h   ; lea ecx, [esi + 0xd8]
        db 001h, 011h   ; add dword ptr [ecx], edx
        db 011h, 059h, 004h   ; adc dword ptr [ecx + 4], ebx
        db 0EBh, 044h   ; jmp 0x362e9b
$L_362e57:
        db 0F6h, 086h, 0F4h, 000h, 000h, 000h, 003h   ; test byte ptr [esi + 0xf4], 3
        db 075h, 03Bh   ; jne 0x362e9b
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Dh, 08Eh, 0D8h, 000h, 000h, 000h   ; lea ecx, [esi + 0xd8]
        db 001h, 011h   ; add dword ptr [ecx], edx
        db 011h, 059h, 004h   ; adc dword ptr [ecx + 4], ebx
        db 001h, 096h, 0F0h, 000h, 000h, 000h   ; add dword ptr [esi + 0xf0], edx
        db 0EBh, 025h   ; jmp 0x362e9b
$L_362e76:
        db 0F6h, 046h, 01Ah, 080h   ; test byte ptr [esi + 0x1a], 0x80
        db 074h, 01Ah   ; je 0x362e96
        db 08Bh, 08Eh, 0D8h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xd8]
        db 089h, 08Eh, 0D0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd0], ecx
        db 08Bh, 08Eh, 0DCh, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xdc]
        db 089h, 08Eh, 0D4h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xd4], ecx
        db 0EBh, 005h   ; jmp 0x362e9b
$L_362e96:
        db 0B8h, 046h, 027h, 007h, 080h   ; mov eax, 0x80072746
$L_362e9b:
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 0AFh, 000h, 000h, 000h   ; jl 0x362f52
        db 0F6h, 086h, 0F4h, 000h, 000h, 000h, 003h   ; test byte ptr [esi + 0xf4], 3
        db 075h, 05Bh   ; jne 0x362f07
        db 08Bh, 086h, 0DCh, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xdc]
        db 08Bh, 08Eh, 0D4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xd4]
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 08Bh, 096h, 0D8h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xd8]
        db 08Bh, 0BEh, 0D0h, 000h, 000h, 000h   ; mov edi, dword ptr [esi + 0xd0]
        db 077h, 01Eh   ; ja 0x362ee6
        db 072h, 004h   ; jb 0x362ece
        db 03Bh, 0D7h   ; cmp edx, edi
        db 073h, 00Eh   ; jae 0x362edc
$L_362ece:
        db 08Bh, 09Eh, 0D8h, 000h, 000h, 000h   ; mov ebx, dword ptr [esi + 0xd8]
        db 03Bh, 09Eh, 0B4h, 000h, 000h, 000h   ; cmp ebx, dword ptr [esi + 0xb4]
        db 072h, 029h   ; jb 0x362f05
$L_362edc:
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 072h, 013h   ; jb 0x362ef3
        db 077h, 004h   ; ja 0x362ee6
        db 03Bh, 0D7h   ; cmp edx, edi
        db 072h, 00Dh   ; jb 0x362ef3
$L_362ee6:
        db 06Ah, 002h   ; push 2
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        call _shutdown   ; 0x376FEB
$L_362ef3:
        db 080h, 04Eh, 01Ah, 020h   ; or byte ptr [esi + 0x1a], 0x20
        db 0C7h, 046h, 014h, 007h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 7
        db 0B8h, 0FDh, 0FFh, 015h, 000h   ; mov eax, 0x15fffd
        db 0EBh, 05Fh   ; jmp 0x362f64
$L_362f05:
        db 033h, 0DBh   ; xor ebx, ebx
$L_362f07:
        db 08Bh, 08Eh, 0F0h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xf0]
        db 08Bh, 086h, 0B0h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb0]
        db 08Bh, 096h, 0B4h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xb4]
        db 08Dh, 07Eh, 070h   ; lea edi, [esi + 0x70]
        db 057h   ; push edi
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 003h, 0C1h   ; add eax, ecx
        db 053h   ; push ebx
        db 089h, 086h, 0ACh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xac], eax
        db 08Dh, 086h, 0A8h, 000h, 000h, 000h   ; lea eax, [esi + 0xa8]
        db 06Ah, 001h   ; push 1
        db 050h   ; push eax
        db 0FFh, 0B6h, 080h, 000h, 000h, 000h   ; push dword ptr [esi + 0x80]
        db 02Bh, 0D1h   ; sub edx, ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 089h, 010h   ; mov dword ptr [eax], edx
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 057h   ; push edi
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 07Dh, 00Ch   ; jge 0x362f5e
$L_362f52:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0C7h, 046h, 014h, 009h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 9
        db 0EBh, 006h   ; jmp 0x362f64
$L_362f5e:
        db 080h, 04Eh, 01Bh, 020h   ; or byte ptr [esi + 0x1b], 0x20
$L_362f62:
        db 033h, 0C0h   ; xor eax, eax
$L_362f64:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
seg45 ENDS

seg48 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?CacheFileDelete@CXo@@IAEJW4XONLC_TYPE@@@Z @ 0x00366F43
PUBLIC ?CacheFileDelete@CXo@@IAEJW4XONLC_TYPE@@@Z
?CacheFileDelete@CXo@@IAEJW4XONLC_TYPE@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 078h   ; sub esp, 0x78
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 08Dh, 0B4h, 087h, 070h, 018h, 000h, 000h   ; lea esi, [edi + eax*4 + 0x1870]
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 033h, 0DBh   ; xor ebx, ebx
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 007h   ; je 0x366f67
        call ?Delete@CLocalCache@@QAEXXZ   ; 0x3667CD
        db 021h, 01Eh   ; and dword ptr [esi], ebx
$L_366f67:
        db 083h, 0C7h, 01Ch   ; add edi, 0x1c
        db 081h, 03Fh, 047h, 053h, 052h, 056h   ; cmp dword ptr [edi], 0x56525347
        db 074h, 005h   ; je 0x366f77
        db 0BFh   ; mov edi, 0x3d292f
        dd _unk_3D292F
$L_366f77:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Dh, 045h, 088h   ; lea eax, [ebp - 0x78]
        db 057h   ; push edi
        db 068h   ; push 0x53947c
        dd _unk_53947C
        db 06Ah, 064h   ; push 0x64
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 08Dh, 045h, 088h   ; lea eax, [ebp - 0x78]
        db 050h   ; push eax
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 0FFh, 015h   ; call dword ptr [0x3cd33c]
        dd __imp__RtlInitAnsiString@8
        db 083h, 065h, 0ECh, 000h   ; and dword ptr [ebp - 0x14], 0
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 089h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], eax
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 050h   ; push eax
        db 0C7h, 045h, 0F4h, 040h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0xc], 0x40
        db 0FFh, 015h   ; call dword ptr [0x3cd4f0]
        dd __imp__NtDeleteFile@4
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 07Dh, 024h   ; jge 0x366fe1
        db 08Bh, 035h   ; mov esi, dword ptr [0x3cd380]
        dd __imp__RtlNtStatusToDosError@4
        db 057h   ; push edi
        db 0FFh, 0D6h   ; call esi
        db 085h, 0C0h   ; test eax, eax
        db 057h   ; push edi
        db 07Fh, 006h   ; jg 0x366fd1
        db 0FFh, 0D6h   ; call esi
        db 08Bh, 0D8h   ; mov ebx, eax
        db 0EBh, 010h   ; jmp 0x366fe1
$L_366fd1:
        db 0FFh, 0D6h   ; call esi
        db 08Bh, 0D8h   ; mov ebx, eax
        db 081h, 0E3h, 0FFh, 0FFh, 000h, 000h   ; and ebx, 0xffff
        db 081h, 0CBh, 000h, 000h, 007h, 080h   ; or ebx, 0x80070000
$L_366fe1:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 0C3h   ; mov eax, ebx
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
seg48 ENDS

seg49 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: _sub_3670B6 @ 0x003670B6
PUBLIC _sub_3670B6
_sub_3670B6:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 083h, 07Eh, 014h, 001h   ; cmp dword ptr [esi + 0x14], 1
        db 074h, 040h   ; je 0x3670ff
        db 0FFh, 076h, 018h   ; push dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 030h   ; mov ecx, dword ptr [esi + 0x30]
        call _sub_356E16   ; 0x356E16
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 074h, 021h   ; je 0x3670f2
        db 0C7h, 046h, 014h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x14], 1
        db 07Ch, 018h   ; jl 0x3670f2
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 08Bh, 040h, 010h   ; mov eax, dword ptr [eax + 0x10]
        db 0C1h, 0E0h, 009h   ; shl eax, 9
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?CheckReadWrite@CCacheTask@@AAEJK@Z   ; 0x366746
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 003h   ; jge 0x3670f2
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
$L_3670f2:
        db 083h, 07Eh, 014h, 001h   ; cmp dword ptr [esi + 0x14], 1
        db 075h, 007h   ; jne 0x3670ff
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_366774   ; 0x366774
$L_3670ff:
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg49 ENDS

seg51 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?OpenCacheFile@CLocalCache@@QAEJXZ @ 0x0036739B
PUBLIC ?OpenCacheFile@CLocalCache@@QAEJXZ
?OpenCacheFile@CLocalCache@@QAEJXZ:
        db 055h   ; push ebp
        db 08Dh, 06Ch, 024h, 088h   ; lea ebp, [esp - 0x78]
        db 081h, 0ECh, 0F4h, 000h, 000h, 000h   ; sub esp, 0xf4
        db 08Bh, 081h, 0BCh, 008h, 000h, 000h   ; mov eax, dword ptr [ecx + 0x8bc]
        db 083h, 065h, 070h, 000h   ; and dword ptr [ebp + 0x70], 0
        db 083h, 0C0h, 01Ch   ; add eax, 0x1c
        db 081h, 038h, 047h, 053h, 052h, 056h   ; cmp dword ptr [eax], 0x56525347
        db 089h, 04Dh, 06Ch   ; mov dword ptr [ebp + 0x6c], ecx
        db 074h, 005h   ; je 0x3673c3
        db 0B8h   ; mov eax, 0x3d292f
        dd _unk_3D292F
$L_3673c3:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 0FFh, 031h   ; push dword ptr [ecx]
        db 050h   ; push eax
        db 068h   ; push 0x53947c
        dd _unk_53947C
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 06Ah, 064h   ; push 0x64
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 08Bh, 035h   ; mov esi, dword ptr [0x3cd33c]
        dd __imp__RtlInitAnsiString@8
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x3cd3cc]
        dd __imp__NtCreateFile@36
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 0BBh, 080h, 000h, 000h, 000h   ; mov ebx, 0x80
$L_3673ed:
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 050h   ; push eax
        db 08Dh, 045h, 058h   ; lea eax, [ebp + 0x58]
        db 050h   ; push eax
        db 0FFh, 0D6h   ; call esi
        db 083h, 065h, 060h, 000h   ; and dword ptr [ebp + 0x60], 0
        db 06Ah, 068h   ; push 0x68
        db 06Ah, 003h   ; push 3
        db 06Ah, 001h   ; push 1
        db 053h   ; push ebx
        db 08Dh, 045h, 058h   ; lea eax, [ebp + 0x58]
        db 089h, 045h, 064h   ; mov dword ptr [ebp + 0x64], eax
        db 06Ah, 000h   ; push 0
        db 08Dh, 045h, 04Ch   ; lea eax, [ebp + 0x4c]
        db 050h   ; push eax
        db 08Dh, 045h, 060h   ; lea eax, [ebp + 0x60]
        db 050h   ; push eax
        db 08Bh, 045h, 06Ch   ; mov eax, dword ptr [ebp + 0x6c]
        db 068h, 080h, 000h, 010h, 0C0h   ; push 0xc0100080
        db 083h, 0C0h, 004h   ; add eax, 4
        db 050h   ; push eax
        db 0C7h, 045h, 068h, 040h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x68], 0x40
        db 0FFh, 0D7h   ; call edi
        db 089h, 045h, 074h   ; mov dword ptr [ebp + 0x74], eax
        db 08Bh, 045h, 06Ch   ; mov eax, dword ptr [ebp + 0x6c]
        db 083h, 0C0h, 004h   ; add eax, 4
        db 083h, 038h, 0FFh   ; cmp dword ptr [eax], -1
        db 00Fh, 085h, 0B3h, 000h, 000h, 000h   ; jne 0x3674ec
        db 081h, 07Dh, 074h, 03Ah, 000h, 000h, 0C0h   ; cmp dword ptr [ebp + 0x74], 0xc000003a
        db 00Fh, 085h, 093h, 000h, 000h, 000h   ; jne 0x3674d9
        db 08Bh, 045h, 06Ch   ; mov eax, dword ptr [ebp + 0x6c]
        db 08Bh, 080h, 0BCh, 008h, 000h, 000h   ; mov eax, dword ptr [eax + 0x8bc]
        db 083h, 0C0h, 01Ch   ; add eax, 0x1c
        db 081h, 038h, 047h, 053h, 052h, 056h   ; cmp dword ptr [eax], 0x56525347
        db 074h, 005h   ; je 0x36745f
        db 0B8h   ; mov eax, 0x3d292f
        dd _unk_3D292F
$L_36745f:
        db 050h   ; push eax
        db 068h   ; push 0x5394b8
        dd _unk_5394B8
        db 08Dh, 045h, 084h   ; lea eax, [ebp - 0x7c]
        db 06Ah, 064h   ; push 0x64
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 083h, 0C4h, 010h   ; add esp, 0x10
        db 08Dh, 045h, 084h   ; lea eax, [ebp - 0x7c]
        db 050h   ; push eax
        db 08Dh, 045h, 058h   ; lea eax, [ebp + 0x58]
        db 050h   ; push eax
        db 0FFh, 0D6h   ; call esi
        db 083h, 065h, 060h, 000h   ; and dword ptr [ebp + 0x60], 0
        db 068h, 021h, 040h, 000h, 000h   ; push 0x4021
        db 06Ah, 002h   ; push 2
        db 06Ah, 003h   ; push 3
        db 053h   ; push ebx
        db 08Dh, 045h, 058h   ; lea eax, [ebp + 0x58]
        db 089h, 045h, 064h   ; mov dword ptr [ebp + 0x64], eax
        db 06Ah, 000h   ; push 0
        db 08Dh, 045h, 04Ch   ; lea eax, [ebp + 0x4c]
        db 050h   ; push eax
        db 08Dh, 045h, 060h   ; lea eax, [ebp + 0x60]
        db 050h   ; push eax
        db 068h, 001h, 000h, 010h, 000h   ; push 0x100001
        db 08Dh, 045h, 054h   ; lea eax, [ebp + 0x54]
        db 050h   ; push eax
        db 0C7h, 045h, 068h, 040h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x68], 0x40
        db 0FFh, 0D7h   ; call edi
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 074h   ; mov dword ptr [ebp + 0x74], eax
        db 07Ch, 00Eh   ; jl 0x3674c2
        db 0FFh, 075h, 054h   ; push dword ptr [ebp + 0x54]
        db 0FFh, 015h   ; call dword ptr [0x3cd388]
        dd __imp__NtClose@4
        db 0E9h, 02Bh, 0FFh, 0FFh, 0FFh   ; jmp 0x3673ed
$L_3674c2:
        db 050h   ; push eax
$L_3674c3:
        db 08Bh, 035h   ; mov esi, dword ptr [0x3cd380]
        dd __imp__RtlNtStatusToDosError@4
        db 0FFh, 0D6h   ; call esi
        db 085h, 0C0h   ; test eax, eax
        db 0FFh, 075h, 074h   ; push dword ptr [ebp + 0x74]
        db 07Fh, 00Ch   ; jg 0x3674de
        db 0FFh, 0D6h   ; call esi
$L_3674d4:
        db 089h, 045h, 070h   ; mov dword ptr [ebp + 0x70], eax
        db 0EBh, 023h   ; jmp 0x3674fc
$L_3674d9:
        db 0FFh, 075h, 074h   ; push dword ptr [ebp + 0x74]
        db 0EBh, 0E5h   ; jmp 0x3674c3
$L_3674de:
        db 0FFh, 0D6h   ; call esi
        db 025h, 0FFh, 0FFh, 000h, 000h   ; and eax, 0xffff
        db 00Dh, 000h, 000h, 007h, 080h   ; or eax, 0x80070000
        db 0EBh, 0E8h   ; jmp 0x3674d4
$L_3674ec:
        db 083h, 07Dh, 050h, 001h   ; cmp dword ptr [ebp + 0x50], 1
        db 075h, 00Ah   ; jne 0x3674fc
        db 068h, 0B7h, 000h, 000h, 000h   ; push 0xb7
        call _SetLastError@4   ; 0x22EC8E
$L_3674fc:
        db 08Bh, 045h, 070h   ; mov eax, dword ptr [ebp + 0x70]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 083h, 0C5h, 078h   ; add ebp, 0x78
        db 0C9h   ; leave 
        db 0C3h   ; ret 
seg51 ENDS





seg61 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?MessagingContinuePrivateSendTask@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z @ 0x0036E0AA
PUBLIC ?MessagingContinuePrivateSendTask@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z
?MessagingContinuePrivateSendTask@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:
        jmp ?MessagingSendContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z   ; 0x36D741
seg61 ENDS




seg67 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?ConfigureUPnPNatContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z @ 0x00370400
PUBLIC ?ConfigureUPnPNatContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z
?ConfigureUPnPNatContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 081h, 0ECh, 024h, 001h, 000h, 000h   ; sub esp, 0x124
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 083h, 0E8h, 000h   ; sub eax, 0
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 057h   ; push edi
        db 089h, 05Dh, 0FCh   ; mov dword ptr [ebp - 4], ebx
        db 00Fh, 084h, 00Bh, 003h, 000h, 000h   ; je 0x37072b
        db 048h   ; dec eax
        db 00Fh, 084h, 083h, 003h, 000h, 000h   ; je 0x3707aa
        db 048h   ; dec eax
        db 00Fh, 084h, 088h, 001h, 000h, 000h   ; je 0x3705b6
        db 048h   ; dec eax
        db 00Fh, 085h, 010h, 005h, 000h, 000h   ; jne 0x370945
        db 08Dh, 0BEh, 098h, 000h, 000h, 000h   ; lea edi, [esi + 0x98]
        db 057h   ; push edi
        call _sub_356E16   ; 0x356E16
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 074h, 008h   ; je 0x370450
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Dh, 0F5h, 004h, 000h, 000h   ; jge 0x370945
$L_370450:
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 051h   ; push ecx
        db 08Dh, 04Dh, 0DCh   ; lea ecx, [ebp - 0x24]
        db 051h   ; push ecx
        db 08Dh, 04Dh, 0E4h   ; lea ecx, [ebp - 0x1c]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 050h   ; push eax
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 0E4h   ; mov dword ptr [ebp - 0x1c], eax
        call ?XOnlineUploadGetResults@CXo@@QAEJPAUXONLINETASK_HANDLE__@@PAPAEPAKPAT_ULARGE_INTEGER@@32PAU_FILETIME@@@Z   ; 0x36296E
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?XRL_CleanupHandler@CXo@@IAEXPAUXRL_ASYNC@@@Z   ; 0x3697BC
        db 08Bh, 045h, 0E4h   ; mov eax, dword ptr [ebp - 0x1c]
        db 085h, 0C0h   ; test eax, eax
        db 089h, 086h, 0F0h, 008h, 000h, 000h   ; mov dword ptr [esi + 0x8f0], eax
        db 00Fh, 084h, 07Bh, 004h, 000h, 000h   ; je 0x370900
        db 03Dh, 000h, 030h, 000h, 000h   ; cmp eax, 0x3000
        db 00Fh, 083h, 070h, 004h, 000h, 000h   ; jae 0x370900
        db 0C6h, 084h, 030h, 0F4h, 008h, 000h, 000h, 000h   ; mov byte ptr [eax + esi + 0x8f4], 0
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 056h   ; push esi
        call ?ConfigureUPnPNatVerifyAddPortResponse@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@K@Z   ; 0x37035F
        db 03Dh, 01Ah, 019h, 015h, 080h   ; cmp eax, 0x8015191a
        db 00Fh, 085h, 0EDh, 000h, 000h, 000h   ; jne 0x37059b
        db 0FFh, 046h, 014h   ; inc dword ptr [esi + 0x14]
        db 083h, 07Eh, 014h, 005h   ; cmp dword ptr [esi + 0x14], 5
        db 00Fh, 087h, 045h, 004h, 000h, 000h   ; ja 0x370900
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?ConfigureUPnPNatSelectNewPort@CXo@@IAEXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z   ; 0x3701A3
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 046h, 03Eh   ; mov ax, word ptr [esi + 0x3e]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 050h   ; push eax
        db 056h   ; push esi
        call ?ConfigureUPnPNatBuildAddPortRequest@CXo@@IAEXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@G@Z   ; 0x36FD44
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 07Dh, 0ECh   ; lea edi, [ebp - 0x14]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 08Bh, 046h, 038h   ; mov eax, dword ptr [esi + 0x38]
        db 083h, 04Dh, 0F0h, 0FFh   ; or dword ptr [ebp - 0x10], 0xffffffff
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 066h, 08Bh, 046h, 042h   ; mov ax, word ptr [esi + 0x42]
        db 066h, 089h, 045h, 0F8h   ; mov word ptr [ebp - 8], ax
        db 06Ah, 054h   ; push 0x54
        db 033h, 0C0h   ; xor eax, eax
        db 059h   ; pop ecx
        db 08Dh, 0BEh, 098h, 000h, 000h, 000h   ; lea edi, [esi + 0x98]
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 039h, 086h, 0E8h, 001h, 000h, 000h   ; cmp dword ptr [esi + 0x1e8], eax
        db 0A1h   ; mov eax, dword ptr [0x432b6c]
        dd _unk_432B6C
        db 0C7h, 045h, 0ECh, 000h, 000h, 090h, 058h   ; mov dword ptr [ebp - 0x14], 0x58900000
        db 075h, 005h   ; jne 0x370513
        db 0A1h   ; mov eax, dword ptr [0x432b68]
        dd _unk_432B68
$L_370513:
        db 050h   ; push eax
        db 00Fh, 0B7h, 046h, 042h   ; movzx eax, word ptr [esi + 0x42]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 03Bh   ; movzx eax, byte ptr [esi + 0x3b]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 03Ah   ; movzx eax, byte ptr [esi + 0x3a]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 039h   ; movzx eax, byte ptr [esi + 0x39]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 038h   ; movzx eax, byte ptr [esi + 0x38]
        db 050h   ; push eax
        db 068h   ; push 0x539edc
        dd _unk_539EDC
        db 08Dh, 085h, 0DCh, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x124]
        db 068h, 000h, 001h, 000h, 000h   ; push 0x100
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 06Ah, 000h   ; push 0
        db 08Dh, 04Dh, 0ECh   ; lea ecx, [ebp - 0x14]
        db 051h   ; push ecx
        db 08Dh, 08Eh, 098h, 000h, 000h, 000h   ; lea ecx, [esi + 0x98]
        db 051h   ; push ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 08Dh, 08Eh, 0F0h, 002h, 000h, 000h   ; lea ecx, [esi + 0x2f0]
        db 068h, 088h, 013h, 000h, 000h   ; push 0x1388
        db 0FFh, 0B6h, 0ECh, 002h, 000h, 000h   ; push dword ptr [esi + 0x2ec]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 08Dh, 085h, 0DCh, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x124]
        db 050h   ; push eax
        db 068h, 000h, 030h, 000h, 000h   ; push 0x3000
        db 08Dh, 086h, 0F4h, 008h, 000h, 000h   ; lea eax, [esi + 0x8f4]
        db 050h   ; push eax
        db 08Dh, 086h, 06Ch, 002h, 000h, 000h   ; lea eax, [esi + 0x26c]
        db 050h   ; push eax
        db 06Ah, 0FFh   ; push -1
        db 06Ah, 0FFh   ; push -1
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?UploadFromMemoryInternal@CXo@@IAEJKKPBDPAEKPBEK2KKPAXPAUXRL_ASYNC_EXTENDED@@PBUXRL_SPECIAL@@PAUXONLINETASK_HANDLE__@@@Z   ; 0x36301A
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Dh, 0AFh, 003h, 000h, 000h   ; jge 0x370945
        db 0E9h, 065h, 003h, 000h, 000h   ; jmp 0x370900
$L_37059b:
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 05Dh, 003h, 000h, 000h   ; jl 0x370900
        db 0C7h, 046h, 00Ch, 0F0h, 000h, 015h, 000h   ; mov dword ptr [esi + 0xc], 0x1500f0
        db 0C7h, 046h, 010h, 063h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 0x63
        db 0E9h, 08Fh, 003h, 000h, 000h   ; jmp 0x370945
$L_3705b6:
        db 08Dh, 0BEh, 098h, 000h, 000h, 000h   ; lea edi, [esi + 0x98]
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call _sub_356E16   ; 0x356E16
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 00Fh, 085h, 04Ah, 001h, 000h, 000h   ; jne 0x370719
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 051h   ; push ecx
        db 08Dh, 04Dh, 0DCh   ; lea ecx, [ebp - 0x24]
        db 051h   ; push ecx
        db 08Dh, 04Dh, 0E4h   ; lea ecx, [ebp - 0x1c]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 050h   ; push eax
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?XOnlineUploadGetResults@CXo@@QAEJPAUXONLINETASK_HANDLE__@@PAPAEPAKPAT_ULARGE_INTEGER@@32PAU_FILETIME@@@Z   ; 0x36296E
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        call ?XRL_CleanupHandler@CXo@@IAEXPAUXRL_ASYNC@@@Z   ; 0x3697BC
        db 083h, 07Dh, 0FCh, 000h   ; cmp dword ptr [ebp - 4], 0
        db 00Fh, 08Ch, 003h, 003h, 000h, 000h   ; jl 0x370900
        db 08Bh, 045h, 0E4h   ; mov eax, dword ptr [ebp - 0x1c]
        db 03Dh, 000h, 030h, 000h, 000h   ; cmp eax, 0x3000
        db 089h, 086h, 0F0h, 008h, 000h, 000h   ; mov dword ptr [esi + 0x8f0], eax
        db 00Fh, 083h, 0EFh, 002h, 000h, 000h   ; jae 0x370900
        db 0C6h, 084h, 030h, 0F4h, 008h, 000h, 000h, 000h   ; mov byte ptr [eax + esi + 0x8f4], 0
        db 081h, 07Dh, 008h, 0C8h, 000h, 000h, 000h   ; cmp dword ptr [ebp + 8], 0xc8
        db 00Fh, 085h, 0DAh, 002h, 000h, 000h   ; jne 0x370900
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?ConfigureUPnPNatVerifyGetDescriptionResponse@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z   ; 0x37023E
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 0CAh, 002h, 000h, 000h   ; jl 0x370900
        db 083h, 066h, 014h, 000h   ; and dword ptr [esi + 0x14], 0
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 046h, 03Eh   ; mov ax, word ptr [esi + 0x3e]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 050h   ; push eax
        db 056h   ; push esi
        call ?ConfigureUPnPNatBuildAddPortRequest@CXo@@IAEXPAUXONLINETASK_CONFIGURE_UPNP_NAT@@G@Z   ; 0x36FD44
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 07Dh, 0ECh   ; lea edi, [ebp - 0x14]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 08Bh, 046h, 038h   ; mov eax, dword ptr [esi + 0x38]
        db 083h, 04Dh, 0F0h, 0FFh   ; or dword ptr [ebp - 0x10], 0xffffffff
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 066h, 08Bh, 046h, 042h   ; mov ax, word ptr [esi + 0x42]
        db 066h, 089h, 045h, 0F8h   ; mov word ptr [ebp - 8], ax
        db 06Ah, 054h   ; push 0x54
        db 033h, 0C0h   ; xor eax, eax
        db 059h   ; pop ecx
        db 08Dh, 0BEh, 098h, 000h, 000h, 000h   ; lea edi, [esi + 0x98]
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 039h, 086h, 0E8h, 001h, 000h, 000h   ; cmp dword ptr [esi + 0x1e8], eax
        db 0A1h   ; mov eax, dword ptr [0x432b6c]
        dd _unk_432B6C
        db 0C7h, 045h, 0ECh, 000h, 000h, 090h, 058h   ; mov dword ptr [ebp - 0x14], 0x58900000
        db 075h, 005h   ; jne 0x37068a
        db 0A1h   ; mov eax, dword ptr [0x432b68]
        dd _unk_432B68
$L_37068a:
        db 050h   ; push eax
        db 00Fh, 0B7h, 046h, 042h   ; movzx eax, word ptr [esi + 0x42]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 03Bh   ; movzx eax, byte ptr [esi + 0x3b]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 03Ah   ; movzx eax, byte ptr [esi + 0x3a]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 039h   ; movzx eax, byte ptr [esi + 0x39]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 038h   ; movzx eax, byte ptr [esi + 0x38]
        db 050h   ; push eax
        db 068h   ; push 0x539edc
        dd _unk_539EDC
        db 08Dh, 085h, 0DCh, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x124]
        db 068h, 000h, 001h, 000h, 000h   ; push 0x100
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 06Ah, 000h   ; push 0
        db 08Dh, 04Dh, 0ECh   ; lea ecx, [ebp - 0x14]
        db 051h   ; push ecx
        db 08Dh, 08Eh, 098h, 000h, 000h, 000h   ; lea ecx, [esi + 0x98]
        db 051h   ; push ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 08Dh, 08Eh, 0F0h, 002h, 000h, 000h   ; lea ecx, [esi + 0x2f0]
        db 068h, 088h, 013h, 000h, 000h   ; push 0x1388
        db 0FFh, 0B6h, 0ECh, 002h, 000h, 000h   ; push dword ptr [esi + 0x2ec]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 08Dh, 085h, 0DCh, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x124]
        db 050h   ; push eax
        db 068h, 000h, 030h, 000h, 000h   ; push 0x3000
        db 08Dh, 086h, 0F4h, 008h, 000h, 000h   ; lea eax, [esi + 0x8f4]
        db 050h   ; push eax
        db 08Dh, 086h, 06Ch, 002h, 000h, 000h   ; lea eax, [esi + 0x26c]
        db 050h   ; push eax
        db 06Ah, 0FFh   ; push -1
        db 06Ah, 0FFh   ; push -1
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?UploadFromMemoryInternal@CXo@@IAEJKKPBDPAEKPBEK2KKPAXPAUXRL_ASYNC_EXTENDED@@PBUXRL_SPECIAL@@PAUXONLINETASK_HANDLE__@@@Z   ; 0x36301A
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 0F3h, 001h, 000h, 000h   ; jl 0x370900
        db 0C7h, 046h, 010h, 003h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 3
        db 0E9h, 02Ch, 002h, 000h, 000h   ; jmp 0x370945
$L_370719:
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Dh, 024h, 002h, 000h, 000h   ; jge 0x370945
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?XRL_CleanupHandler@CXo@@IAEXPAUXRL_ASYNC@@@Z   ; 0x3697BC
        db 0EBh, 013h   ; jmp 0x37073e
$L_37072b:
        db 06Ah, 000h   ; push 0
        db 06Ah, 002h   ; push 2
        db 06Ah, 002h   ; push 2
        call _socket@12   ; 0x376FD5
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 089h, 046h, 034h   ; mov dword ptr [esi + 0x34], eax
        db 075h, 00Ch   ; jne 0x37074a
$L_37073e:
        db 0C7h, 046h, 00Ch, 019h, 019h, 015h, 080h   ; mov dword ptr [esi + 0xc], 0x80151919
        db 0E9h, 0FBh, 001h, 000h, 000h   ; jmp 0x370945
$L_37074a:
        db 06Ah, 004h   ; push 4
        db 053h   ; push ebx
        db 068h, 001h, 040h, 000h, 000h   ; push 0x4001
        db 068h, 0FFh, 0FFh, 000h, 000h   ; push 0xffff
        db 050h   ; push eax
        call _setsockopt@20   ; 0x377001
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 057h   ; push edi
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 08Dh, 046h, 058h   ; lea eax, [esi + 0x58]
        db 06Ah, 000h   ; push 0
        db 06Ah, 001h   ; push 1
        db 08Dh, 08Eh, 0F4h, 008h, 000h, 000h   ; lea ecx, [esi + 0x8f4]
        db 050h   ; push eax
        db 0FFh, 076h, 034h   ; push dword ptr [esi + 0x34]
        db 089h, 04Eh, 05Ch   ; mov dword ptr [esi + 0x5c], ecx
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0C7h, 000h, 000h, 030h, 000h, 000h   ; mov dword ptr [eax], 0x3000
        call ?SendRecvInitializeContext@CXo@@IAEXIPAU_WSABUF@@KKPAXPAUXONLINETASK_SOCKIO@@@Z   ; 0x369D40
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?ConfigureUPnPNatSendDiscoveryRequest@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z   ; 0x36FA95
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 0ADh, 001h, 000h, 000h   ; jl 0x370942
        db 06Ah, 000h   ; push 0
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 09Bh   ; jl 0x37073e
        db 0C7h, 046h, 010h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 1
$L_3707aa:
        db 08Dh, 046h, 060h   ; lea eax, [esi + 0x60]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call _sub_356E16   ; 0x356E16
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 00Fh, 085h, 052h, 001h, 000h, 000h   ; jne 0x370912
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 050h   ; push eax
        db 08Dh, 0BEh, 0F0h, 008h, 000h, 000h   ; lea edi, [esi + 0x8f0]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 057h   ; push edi
        db 08Dh, 046h, 060h   ; lea eax, [esi + 0x60]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?GetSendRecvResults@CXo@@IAEJPAUXONLINETASK_HANDLE__@@PAK1PAPAU_WSABUF@@@Z   ; 0x369ABB
        db 08Bh, 03Fh   ; mov edi, dword ptr [edi]
        db 081h, 0FFh, 000h, 030h, 000h, 000h   ; cmp edi, 0x3000
        db 073h, 017h   ; jae 0x3707f9
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0C6h, 084h, 037h, 0F4h, 008h, 000h, 000h, 000h   ; mov byte ptr [edi + esi + 0x8f4], 0
        call ?ConfigureUPnPNatVerifyDiscoveryReply@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z   ; 0x36FB95
        db 03Dh, 018h, 019h, 015h, 080h   ; cmp eax, 0x80151918
        db 075h, 01Ah   ; jne 0x370813
$L_3707f9:
        db 06Ah, 000h   ; push 0
        db 08Dh, 046h, 060h   ; lea eax, [esi + 0x60]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SendRecvBegin@CXo@@IAEJPAUXONLINETASK_SOCKIO@@H@Z   ; 0x369CC3
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Dh, 037h, 001h, 000h, 000h   ; jge 0x370945
        db 0E9h, 02Bh, 0FFh, 0FFh, 0FFh   ; jmp 0x37073e
$L_370813:
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 027h, 001h, 000h, 000h   ; jl 0x370942
        db 06Ah, 054h   ; push 0x54
        db 059h   ; pop ecx
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 09Eh, 098h, 000h, 000h, 000h   ; lea ebx, [esi + 0x98]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 00Fh, 0B7h, 046h, 040h   ; movzx eax, word ptr [esi + 0x40]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 03Bh   ; movzx eax, byte ptr [esi + 0x3b]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 03Ah   ; movzx eax, byte ptr [esi + 0x3a]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 039h   ; movzx eax, byte ptr [esi + 0x39]
        db 050h   ; push eax
        db 00Fh, 0B6h, 046h, 038h   ; movzx eax, byte ptr [esi + 0x38]
        db 050h   ; push eax
        db 068h   ; push 0x539eb0
        dd _unk_539EB0
        db 08Dh, 085h, 05Ch, 0FFh, 0FFh, 0FFh   ; lea eax, [ebp - 0xa4]
        db 068h, 080h, 000h, 000h, 000h   ; push 0x80
        db 050h   ; push eax
        call ?xsnprintf@@YAHPADIPBDZZ   ; 0x368A98
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Dh, 086h, 0F4h, 008h, 000h, 000h   ; lea eax, [esi + 0x8f4]
        db 053h   ; push ebx
        db 089h, 083h, 0B0h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0xb0], eax
        db 0C7h, 083h, 0B4h, 000h, 000h, 000h, 000h, 030h, 000h, 000h   ; mov dword ptr [ebx + 0xb4], 0x3000
        call ?TaskInitializeContext@CXo@@IAEXPAUXONLINETASK_CONTEXT@@@Z   ; 0x356E05
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 083h, 04Bh, 030h, 0FFh   ; or dword ptr [ebx + 0x30], 0xffffffff
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 04Bh, 00Ch   ; mov dword ptr [ebx + 0xc], ecx
        db 089h, 04Bh, 010h   ; mov dword ptr [ebx + 0x10], ecx
        db 08Bh, 046h, 038h   ; mov eax, dword ptr [esi + 0x38]
        db 089h, 043h, 034h   ; mov dword ptr [ebx + 0x34], eax
        db 066h, 08Bh, 046h, 040h   ; mov ax, word ptr [esi + 0x40]
        db 083h, 04Bh, 024h, 0FFh   ; or dword ptr [ebx + 0x24], 0xffffffff
        db 066h, 089h, 043h, 038h   ; mov word ptr [ebx + 0x38], ax
        db 089h, 04Bh, 028h   ; mov dword ptr [ebx + 0x28], ecx
        db 08Dh, 083h, 004h, 001h, 000h, 000h   ; lea eax, [ebx + 0x104]
        db 0C7h, 043h, 018h, 000h, 000h, 090h, 043h   ; mov dword ptr [ebx + 0x18], 0x43900000
        db 0C7h, 043h, 01Ch, 088h, 013h, 000h, 000h   ; mov dword ptr [ebx + 0x1c], 0x1388
        db 053h   ; push ebx
        db 051h   ; push ecx
        db 089h, 048h, 014h   ; mov dword ptr [eax + 0x14], ecx
        db 089h, 048h, 010h   ; mov dword ptr [eax + 0x10], ecx
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 089h, 048h, 01Ch   ; mov dword ptr [eax + 0x1c], ecx
        db 089h, 048h, 020h   ; mov dword ptr [eax + 0x20], ecx
        db 0C7h, 040h, 004h   ; mov dword ptr [eax + 4], 0x361f33
        dd ?xrldtmDoneHeaders@CXo@@IAEJPAX@Z
        db 0C7h, 040h, 008h   ; mov dword ptr [eax + 8], 0x362786
        dd ?xrlulsResponseHeaders@CXo@@IAEJPAX@Z
        db 0C7h, 040h, 00Ch   ; mov dword ptr [eax + 0xc], 0x361f82
        dd ?xrldtmCompleted@CXo@@IAEJPAX@Z
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 051h   ; push ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 057h   ; push edi
        db 08Dh, 085h, 05Ch, 0FFh, 0FFh, 0FFh   ; lea eax, [ebp - 0xa4]
        db 050h   ; push eax
        db 08Dh, 086h, 0ECh, 001h, 000h, 000h   ; lea eax, [esi + 0x1ec]
        db 050h   ; push eax
        call ?Download@CXo@@IAEJPBDPBEKPBU_FILETIME@@T_LARGE_INTEGER@@PAUXRL_ASYNC@@@Z   ; 0x362461
        db 085h, 0C0h   ; test eax, eax
        db 08Bh, 05Dh, 0FCh   ; mov ebx, dword ptr [ebp - 4]
        db 07Dh, 009h   ; jge 0x370909
$L_370900:
        db 0C7h, 046h, 00Ch, 018h, 019h, 015h, 080h   ; mov dword ptr [esi + 0xc], 0x80151918
        db 0EBh, 03Ch   ; jmp 0x370945
$L_370909:
        db 0C7h, 046h, 010h, 002h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 2
        db 0EBh, 033h   ; jmp 0x370945
$L_370912:
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 024h, 0FEh, 0FFh, 0FFh   ; jl 0x37073e
        call _GetTickCount@0   ; 0x22D120
        db 03Bh, 046h, 01Ch   ; cmp eax, dword ptr [esi + 0x1c]
        db 072h, 021h   ; jb 0x370945
        db 0FFh, 046h, 014h   ; inc dword ptr [esi + 0x14]
        db 083h, 07Eh, 014h, 006h   ; cmp dword ptr [esi + 0x14], 6
        db 072h, 009h   ; jb 0x370936
        db 0C7h, 046h, 00Ch, 017h, 019h, 015h, 080h   ; mov dword ptr [esi + 0xc], 0x80151917
        db 0EBh, 00Fh   ; jmp 0x370945
$L_370936:
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?ConfigureUPnPNatSendDiscoveryRequest@CXo@@IAEJPAUXONLINETASK_CONFIGURE_UPNP_NAT@@@Z   ; 0x36FA95
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 003h   ; jge 0x370945
$L_370942:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
$L_370945:
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 026h   ; je 0x370972
        db 03Dh, 0F0h, 000h, 015h, 000h   ; cmp eax, 0x1500f0
        db 08Bh, 09Bh, 0C4h, 000h, 000h, 000h   ; mov ebx, dword ptr [ebx + 0xc4]
        db 075h, 00Eh   ; jne 0x370967
        db 08Bh, 043h, 030h   ; mov eax, dword ptr [ebx + 0x30]
        db 083h, 0E0h, 0DFh   ; and eax, 0xffffffdf
        db 083h, 0C8h, 040h   ; or eax, 0x40
        db 089h, 043h, 030h   ; mov dword ptr [ebx + 0x30], eax
        db 0EBh, 004h   ; jmp 0x37096b
$L_370967:
        db 083h, 04Bh, 030h, 060h   ; or dword ptr [ebx + 0x30], 0x60
$L_37096b:
        db 0C7h, 046h, 010h, 063h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x10], 0x63
$L_370972:
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
seg67 ENDS


seg73 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?storulStartUpload@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z @ 0x0037288F
PUBLIC ?storulStartUpload@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z
?storulStartUpload@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Dh, 0B7h   ; lea esi, [edi + 0x21df8]
        dd _unk_021DF8
        db 08Dh, 087h, 0F4h, 095h, 000h, 000h   ; lea eax, [edi + 0x95f4]
        db 056h   ; push esi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 089h, 086h, 0B0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xb0], eax
        db 0C7h, 086h, 0B4h, 000h, 000h, 000h, 000h, 084h, 000h, 000h   ; mov dword ptr [esi + 0xb4], 0x8400
        call ?TaskInitializeContext@CXo@@IAEXPAUXONLINETASK_CONTEXT@@@Z   ; 0x356E05
        db 08Bh, 047h, 008h   ; mov eax, dword ptr [edi + 8]
        db 033h, 0DBh   ; xor ebx, ebx
        db 089h, 046h, 008h   ; mov dword ptr [esi + 8], eax
        db 089h, 05Eh, 00Ch   ; mov dword ptr [esi + 0xc], ebx
        db 089h, 05Eh, 010h   ; mov dword ptr [esi + 0x10], ebx
        db 089h, 05Eh, 018h   ; mov dword ptr [esi + 0x18], ebx
        db 08Bh, 087h, 0DCh, 015h, 000h, 000h   ; mov eax, dword ptr [edi + 0x15dc]
        db 089h, 046h, 058h   ; mov dword ptr [esi + 0x58], eax
        db 08Bh, 087h, 044h, 002h, 000h, 000h   ; mov eax, dword ptr [edi + 0x244]
        db 099h   ; cdq 
        db 089h, 086h, 0E8h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xe8], eax
        db 08Dh, 04Eh, 02Ch   ; lea ecx, [esi + 0x2c]
        db 051h   ; push ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 046h, 028h   ; lea eax, [esi + 0x28]
        db 050h   ; push eax
        db 052h   ; push edx
        db 0FFh, 0B6h, 0E8h, 000h, 000h, 000h   ; push dword ptr [esi + 0xe8]
        db 089h, 096h, 0ECh, 000h, 000h, 000h   ; mov dword ptr [esi + 0xec], edx
        db 056h   ; push esi
        db 053h   ; push ebx
        db 06Ah, 00Fh   ; push 0xf
        db 089h, 09Eh, 0E0h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xe0], ebx
        db 089h, 09Eh, 0E4h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xe4], ebx
        db 0C7h, 046h, 01Ch, 060h, 0EAh, 000h, 000h   ; mov dword ptr [esi + 0x1c], 0xea60
        db 089h, 05Eh, 024h   ; mov dword ptr [esi + 0x24], ebx
        call ?XRL_RetrieveThrottleSettings@CXo@@IAEJKKPAUXRL_ASYNC@@_KPAK2@Z   ; 0x368FB0
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 08Ch, 0ECh, 000h, 000h, 000h   ; jl 0x372a11
        db 080h, 04Eh, 01Ah, 001h   ; or byte ptr [esi + 0x1a], 1
        db 0B8h, 060h, 0EAh, 000h, 000h   ; mov eax, 0xea60
        db 039h, 046h, 028h   ; cmp dword ptr [esi + 0x28], eax
        db 076h, 003h   ; jbe 0x372936
        db 089h, 046h, 028h   ; mov dword ptr [esi + 0x28], eax
$L_372936:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 086h, 040h, 001h, 000h, 000h   ; lea eax, [esi + 0x140]
        db 050h   ; push eax
        call ?TaskInitializeContext@CXo@@IAEXPAUXONLINETASK_CONTEXT@@@Z   ; 0x356E05
        db 08Dh, 08Eh, 040h, 001h, 000h, 000h   ; lea ecx, [esi + 0x140]
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x362889
        dd ?xrlufContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z
        db 08Bh, 047h, 008h   ; mov eax, dword ptr [edi + 8]
        db 089h, 086h, 048h, 001h, 000h, 000h   ; mov dword ptr [esi + 0x148], eax
        db 08Dh, 086h, 004h, 001h, 000h, 000h   ; lea eax, [esi + 0x104]
        db 089h, 09Eh, 04Ch, 001h, 000h, 000h   ; mov dword ptr [esi + 0x14c], ebx
        db 089h, 048h, 014h   ; mov dword ptr [eax + 0x14], ecx
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 051h   ; push ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 0C7h, 000h   ; mov dword ptr [eax], 0x36275a
        dd ?xrlulsCompleted@CXo@@IAEJPAX@Z
        db 0C7h, 040h, 004h   ; mov dword ptr [eax + 4], 0x362786
        dd ?xrlulsResponseHeaders@CXo@@IAEJPAX@Z
        db 0C7h, 040h, 008h   ; mov dword ptr [eax + 8], 0x363240
        dd ?xrlufInitializeTask@CXo@@IAEJW4XRLUPLOAD_EXTTYPE@@PAXPAUXONLINETASK_HANDLE__@@@Z
        db 089h, 058h, 00Ch   ; mov dword ptr [eax + 0xc], ebx
        db 089h, 058h, 010h   ; mov dword ptr [eax + 0x10], ebx
        db 089h, 058h, 018h   ; mov dword ptr [eax + 0x18], ebx
        db 08Dh, 087h, 0F4h, 015h, 000h, 000h   ; lea eax, [edi + 0x15f4]
        db 050h   ; push eax
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 057h   ; push edi
        db 0C7h, 045h, 008h, 000h, 080h, 000h, 000h   ; mov dword ptr [ebp + 8], 0x8000
        call ?BuildUploadPreamble@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@EKPAEPAK@Z   ; 0x371CB5
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 07Ch, 06Ah   ; jl 0x372a11
        db 083h, 07Fh, 020h, 003h   ; cmp dword ptr [edi + 0x20], 3
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 075h, 037h   ; jne 0x3729e7
        db 0B9h, 000h, 080h, 000h, 000h   ; mov ecx, 0x8000
        db 02Bh, 0C8h   ; sub ecx, eax
        db 089h, 04Dh, 0F8h   ; mov dword ptr [ebp - 8], ecx
        db 08Dh, 08Fh   ; lea ecx, [edi + 0x21f4c]
        dd _unk_021F4C
        db 051h   ; push ecx
        db 0FFh, 077h, 008h   ; push dword ptr [edi + 8]
        db 08Dh, 04Dh, 0F8h   ; lea ecx, [ebp - 8]
        db 051h   ; push ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 084h, 038h, 0F4h, 015h, 000h, 000h   ; lea eax, [eax + edi + 0x15f4]
        db 050h   ; push eax
        db 0FFh, 077h, 01Ch   ; push dword ptr [edi + 0x1c]
        db 06Ah, 003h   ; push 3
        call ?AppendTeamTicketsIfNecessary@CXo@@IAEJKKPAEPAKPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x376481
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 07Ch, 030h   ; jl 0x372a11
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 003h, 045h, 0F8h   ; add eax, dword ptr [ebp - 8]
$L_3729e7:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 056h   ; push esi
        db 050h   ; push eax
        db 08Dh, 087h, 0F4h, 015h, 000h, 000h   ; lea eax, [edi + 0x15f4]
        db 050h   ; push eax
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 068h   ; push 0x53a000
        dd _unk_53A000
        call ?Upload@CXo@@IAEJPBDPBEK1KPAUXRL_ASYNC@@@Z   ; 0x3625EB
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 07Ch, 00Eh   ; jl 0x372a11
        db 080h, 04Fh, 01Bh, 080h   ; or byte ptr [edi + 0x1b], 0x80
        db 0C7h, 087h, 0D4h, 001h, 000h, 000h, 00Eh, 000h, 000h, 000h   ; mov dword ptr [edi + 0x1d4], 0xe
$L_372a11:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4

seg73 ENDS

seg74 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: ?XOnlineStorageUploadByServerPath@CXo@@QAEJKKPBGU_FILETIME@@PBDKPAXPAPAUXONLINETASK_HANDLE__@@@Z @ 0x00372DFD
PUBLIC ?XOnlineStorageUploadByServerPath@CXo@@QAEJKKPBGU_FILETIME@@PBDKPAXPAPAUXONLINETASK_HANDLE__@@@Z
?XOnlineStorageUploadByServerPath@CXo@@QAEJKKPBGU_FILETIME@@PBDKPAXPAPAUXONLINETASK_HANDLE__@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 081h, 0ECh, 010h, 003h, 000h, 000h   ; sub esp, 0x310
        db 053h   ; push ebx
        db 057h   ; push edi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 033h, 0FFh   ; xor edi, edi
        db 03Bh, 0DFh   ; cmp ebx, edi
        db 089h, 05Dh, 0FCh   ; mov dword ptr [ebp - 4], ebx
        db 075h, 00Ah   ; jne 0x372e1d
        db 0B8h, 005h, 000h, 015h, 080h   ; mov eax, 0x80150005
        db 0E9h, 0CBh, 002h, 000h, 000h   ; jmp 0x3730e8
$L_372e1d:
        db 08Bh, 0CBh   ; mov ecx, ebx
        call _sub_3575F7   ; 0x3575F7
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 0B7h, 002h, 000h, 000h   ; je 0x3730e3
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 06Bh, 0C9h, 070h   ; imul ecx, ecx, 0x70
        db 08Bh, 014h, 001h   ; mov edx, dword ptr [ecx + eax]
        db 00Bh, 054h, 001h, 004h   ; or edx, dword ptr [ecx + eax + 4]
        db 00Fh, 084h, 0A4h, 002h, 000h, 000h   ; je 0x3730e3
        db 083h, 07Dh, 00Ch, 004h   ; cmp dword ptr [ebp + 0xc], 4
        db 072h, 00Ah   ; jb 0x372e4f
        db 0B8h, 006h, 010h, 015h, 080h   ; mov eax, 0x80151006
        db 0E9h, 099h, 002h, 000h, 000h   ; jmp 0x3730e8
$L_372e4f:
        db 056h   ; push esi
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 0C1h, 0EEh, 01Eh   ; shr esi, 0x1e
        db 083h, 0E6h, 001h   ; and esi, 1
        db 083h, 07Dh, 008h, 003h   ; cmp dword ptr [ebp + 8], 3
        db 089h, 075h, 0F0h   ; mov dword ptr [ebp - 0x10], esi
        db 0C7h, 045h, 0F4h, 00Ch, 021h, 002h, 000h   ; mov dword ptr [ebp - 0xc], 0x2210c
        db 075h, 007h   ; jne 0x372e70
        db 0C7h, 045h, 0F4h, 060h, 021h, 002h, 000h   ; mov dword ptr [ebp - 0xc], 0x22160
$L_372e70:
        db 03Bh, 0F7h   ; cmp esi, edi
        db 068h, 0ACh, 020h, 000h, 000h   ; push 0x20ac
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 074h, 007h   ; je 0x372e85
        call ?PoolAllocZ@CXo@@IAEPAXIK@Z   ; 0x369932
        db 0EBh, 005h   ; jmp 0x372e8a
$L_372e85:
        call ?SysAllocZ@CXo@@IAEPAXIK@Z   ; 0x3698D9
$L_372e8a:
        db 08Bh, 0D8h   ; mov ebx, eax
        db 03Bh, 0DFh   ; cmp ebx, edi
        db 075h, 00Ch   ; jne 0x372e9c
        db 0C7h, 045h, 0F8h, 00Eh, 000h, 007h, 080h   ; mov dword ptr [ebp - 8], 0x8007000e
        db 0E9h, 041h, 002h, 000h, 000h   ; jmp 0x3730dd
$L_372e9c:
        db 057h   ; push edi
        db 057h   ; push edi
        db 068h, 000h, 001h, 000h, 000h   ; push 0x100
        db 08Dh, 085h, 0F0h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x110]
        db 050h   ; push eax
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 089h, 0B3h   ; mov dword ptr [ebx + 0x21f20], esi
        dd _unk_021F20
        call _wcslen   ; 0x2C8189
        db 059h   ; pop ecx
        db 040h   ; inc eax
        db 050h   ; push eax
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 057h   ; push edi
        db 057h   ; push edi
        call _WideCharToMultiByte@32   ; 0x2FCDA9
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 075h, 00Ch   ; jne 0x372ed8
        db 0C7h, 045h, 0F8h, 008h, 0C0h, 015h, 080h   ; mov dword ptr [ebp - 8], 0x8015c008
        db 0E9h, 0DEh, 001h, 000h, 000h   ; jmp 0x3730b6
$L_372ed8:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 0B3h   ; lea esi, [ebx + 0x21f58]
        dd _unk_021F58
        db 08Dh, 046h, 018h   ; lea eax, [esi + 0x18]
        db 050h   ; push eax
        db 0C7h, 000h, 098h, 001h, 000h, 000h   ; mov dword ptr [eax], 0x198
        db 08Dh, 046h, 01Ch   ; lea eax, [esi + 0x1c]
        db 050h   ; push eax
        db 057h   ; push edi
        db 08Dh, 045h, 014h   ; lea eax, [ebp + 0x14]
        db 050h   ; push eax
        db 057h   ; push edi
        db 057h   ; push edi
        db 057h   ; push edi
        db 057h   ; push edi
        db 08Dh, 085h, 0F0h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x110]
        db 050h   ; push eax
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 06Ah, 001h   ; push 1
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call ?BuildPreamble@CXo@@IAEJKGKPADEKKKPAU_FILETIME@@PAE2PAK@Z   ; 0x376070
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 00Fh, 08Ch, 09Ch, 001h, 000h, 000h   ; jl 0x3730b3
        db 0FFh, 075h, 024h   ; push dword ptr [ebp + 0x24]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 0FFh, 075h, 020h   ; push dword ptr [ebp + 0x20]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 0FFh, 075h, 01Ch   ; push dword ptr [ebp + 0x1c]
        db 081h, 046h, 018h, 070h, 0FFh, 0FFh, 0FFh   ; add dword ptr [esi + 0x18], 0xffffff70
        db 056h   ; push esi
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 089h, 07Eh, 004h   ; mov dword ptr [esi + 4], edi
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        db 089h, 07Eh, 00Ch   ; mov dword ptr [esi + 0xc], edi
        db 089h, 07Eh, 010h   ; mov dword ptr [esi + 0x10], edi
        db 089h, 07Eh, 014h   ; mov dword ptr [esi + 0x14], edi
        db 0FFh, 0B1h, 050h, 018h, 000h, 000h   ; push dword ptr [ecx + 0x1850]
        db 053h   ; push ebx
        call ?StorageUploadInitializeContext@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@KKPAXPBDK1@Z   ; 0x372C66
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 00Fh, 08Ch, 05Ah, 001h, 000h, 000h   ; jl 0x3730b3
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 0B3h, 024h, 014h, 000h, 000h   ; lea esi, [ebx + 0x1424]
        db 056h   ; push esi
        db 089h, 083h   ; mov dword ptr [ebx + 0x21f20], eax
        dd _unk_021F20
        call ?TaskInitializeContext@CXo@@IAEXPAUXONLINETASK_CONTEXT@@@Z   ; 0x356E05
        db 08Bh, 045h, 024h   ; mov eax, dword ptr [ebp + 0x24]
        db 089h, 083h, 02Ch, 014h, 000h, 000h   ; mov dword ptr [ebx + 0x142c], eax
        db 08Dh, 083h   ; lea eax, [ebx + 0x219f4]
        dd _unk_0219F4
        db 08Dh, 08Bh   ; lea ecx, [ebx + 0x21bf4]
        dd _unk_021BF4
        db 0C7h, 006h   ; mov dword ptr [esi], 0x371de1
        dd ?storulScanFilesCrawlOnFileContinue@CXo@@IAEJPAUXONLINETASK_HANDLE__@@@Z
        db 089h, 0BBh, 028h, 014h, 000h, 000h   ; mov dword ptr [ebx + 0x1428], edi
        db 02Bh, 0C8h   ; sub ecx, eax
$L_372f94:
        db 08Ah, 010h   ; mov dl, byte ptr [eax]
        db 088h, 014h, 001h   ; mov byte ptr [ecx + eax], dl
        db 040h   ; inc eax
        db 084h, 0D2h   ; test dl, dl
        db 075h, 0F6h   ; jne 0x372f94
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 083h, 0ACh, 010h, 000h, 000h   ; lea eax, [ebx + 0x10ac]
        db 050h   ; push eax
        db 0FFh, 075h, 024h   ; push dword ptr [ebp + 0x24]
        db 08Dh, 083h   ; lea eax, [ebx + 0x21bf4]
        dd _unk_021BF4
        db 056h   ; push esi
        db 057h   ; push edi
        db 057h   ; push edi
        db 068h, 000h, 002h, 000h, 000h   ; push 0x200
        db 057h   ; push edi
        db 050h   ; push eax
        call ?DircrawlInitializeContext@CXo@@IAEJPAD0KKPAUXONLINETASK_HANDLE__@@1PAXPAUXONLINETASK_DIRCRAWL@@@Z   ; 0x370E57
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 00Fh, 08Ch, 0E8h, 000h, 000h, 000h   ; jl 0x3730b3
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 083h   ; lea eax, [ebx + 0x21f48]
        dd _unk_021F48
        db 050h   ; push eax
        db 0FFh, 075h, 024h   ; push dword ptr [ebp + 0x24]
        db 06Ah, 001h   ; push 1
        db 057h   ; push edi
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        call ?XOnlineStorageResolveName@CXo@@IAEJPAGHHPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x376D3D
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 00Fh, 08Ch, 0C5h, 000h, 000h, 000h   ; jl 0x3730b3
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Dh, 083h   ; lea eax, [ebx + 0x21f4c]
        dd _unk_021F4C
        db 050h   ; push eax
        db 0FFh, 075h, 024h   ; push dword ptr [ebp + 0x24]
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Dh, 083h, 0F4h, 015h, 000h, 000h   ; lea eax, [ebx + 0x15f4]
        db 050h   ; push eax
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 0C7h, 045h, 0F4h, 000h, 080h, 000h, 000h   ; mov dword ptr [ebp - 0xc], 0x8000
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call ?AppendTeamTicketsIfNecessary@CXo@@IAEJKKPAEPAKPAXPAPAUXONLINETASK_HANDLE__@@@Z   ; 0x376481
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 00Fh, 08Ch, 090h, 000h, 000h, 000h   ; jl 0x3730b3
        db 08Bh, 045h, 01Ch   ; mov eax, dword ptr [ebp + 0x1c]
        db 08Dh, 095h, 0F0h, 0FCh, 0FFh, 0FFh   ; lea edx, [ebp - 0x310]
        db 02Bh, 0D0h   ; sub edx, eax
$L_37302e:
        db 08Ah, 008h   ; mov cl, byte ptr [eax]
        db 088h, 00Ch, 002h   ; mov byte ptr [edx + eax], cl
        db 040h   ; inc eax
        db 084h, 0C9h   ; test cl, cl
        db 075h, 0F6h   ; jne 0x37302e
        db 08Dh, 0BDh, 0F0h, 0FCh, 0FFh, 0FFh   ; lea edi, [ebp - 0x310]
        db 04Fh   ; dec edi
$L_37303f:
        db 08Ah, 047h, 001h   ; mov al, byte ptr [edi + 1]
        db 047h   ; inc edi
        db 084h, 0C0h   ; test al, al
        db 075h, 0F8h   ; jne 0x37303f
        db 0FFh, 075h, 01Ch   ; push dword ptr [ebp + 0x1c]
        db 0BEh   ; mov esi, 0x53a018
        dd _unk_53A018
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 0A5h   ; movsd dword ptr es:[edi], dword ptr [esi]
        db 08Dh, 085h, 0F0h, 0FCh, 0FFh, 0FFh   ; lea eax, [ebp - 0x310]
        db 050h   ; push eax
        db 0A4h   ; movsb byte ptr es:[edi], byte ptr [esi]
        call _XcsCreateSignatureFile@8   ; 0x25E01A
        db 085h, 0C0h   ; test eax, eax
        db 074h, 02Bh   ; je 0x37308f
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 08Dh, 08Dh, 0F0h, 0FCh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x310]
        db 051h   ; push ecx
        db 068h, 000h, 000h, 000h, 080h   ; push 0x80000000
        db 050h   ; push eax
        db 050h   ; push eax
        db 050h   ; push eax
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 0FFh, 0B0h, 050h, 018h, 000h, 000h   ; push dword ptr [eax + 0x1850]
        call _XcsSetSignatureFileInformationEx@28   ; 0x25E064
        db 085h, 0C0h   ; test eax, eax
        db 074h, 007h   ; je 0x37308f
        db 08Bh, 045h, 028h   ; mov eax, dword ptr [ebp + 0x28]
        db 089h, 018h   ; mov dword ptr [eax], ebx
        db 0EBh, 04Eh   ; jmp 0x3730dd
$L_37308f:
        call _GetLastError@0   ; 0x22EC66
        db 085h, 0C0h   ; test eax, eax
        db 07Fh, 007h   ; jg 0x37309f
        call _GetLastError@0   ; 0x22EC66
        db 0EBh, 00Fh   ; jmp 0x3730ae
$L_37309f:
        call _GetLastError@0   ; 0x22EC66
        db 025h, 0FFh, 0FFh, 000h, 000h   ; and eax, 0xffff
        db 00Dh, 000h, 000h, 007h, 080h   ; or eax, 0x80070000
$L_3730ae:
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 033h, 0FFh   ; xor edi, edi
$L_3730b3:
        db 08Bh, 075h, 0F0h   ; mov esi, dword ptr [ebp - 0x10]
$L_3730b6:
        db 08Bh, 083h   ; mov eax, dword ptr [ebx + 0x21f48]
        dd _unk_021F48
        db 03Bh, 0C7h   ; cmp eax, edi
        db 074h, 009h   ; je 0x3730c9
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 050h   ; push eax
        call _sub_356E2B   ; 0x356E2B
$L_3730c9:
        db 03Bh, 0F7h   ; cmp esi, edi
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 074h, 007h   ; je 0x3730d8
        call ?PoolFree@CXo@@IAEXPAX@Z   ; 0x369946
        db 0EBh, 005h   ; jmp 0x3730dd
$L_3730d8:
        call ?SysFree@CXo@@IAEXPAX@Z   ; 0x369910
$L_3730dd:
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 05Eh   ; pop esi
        db 0EBh, 005h   ; jmp 0x3730e8
$L_3730e3:
        db 0B8h, 003h, 000h, 015h, 080h   ; mov eax, 0x80150003
$L_3730e8:
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 024h, 000h   ; ret 0x24
seg74 ENDS





seg80 SEGMENT BYTE PUBLIC ALIAS('XONLINE') 'CODE'

; // match: _sub_376E4E @ 0x00376E4E
PUBLIC _sub_376E4E
_sub_376E4E:
        db 000h, 000h   ; add byte ptr [eax], al
seg80 ENDS

        END
