; codfh-match: XDK crypto thunks, UIX and XHV pieces
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ??1CVoiceMailPseudoFeature@UIXNamespace@@UAE@XZ:NEAR
EXTERN ?ShutdownVoiceMailMode@CLocalTalker@XHVNamespace@@QAEXXZ:NEAR
EXTERN ??0CPopupScreen@UIXNamespace@@QAE@K@Z:NEAR
EXTERN ??3@YAXPAXI@Z:NEAR
EXTERN ??_ECRemoteTalker@XHVNamespace@@QAEPAXI@Z:NEAR
EXTERN ?AddGreyListItem@CScreen@UIXNamespace@@IAEXKPBGKPBU_UIX_SKIN_ICON_INFO@@@Z:NEAR
EXTERN ?AddListItem@CScreen@UIXNamespace@@IAEXKPBGKPBU_UIX_SKIN_ICON_INFO@@@Z:NEAR
EXTERN ?ClearList@CScreen@UIXNamespace@@IAEXKH@Z:NEAR
EXTERN ?Destroy@CScreen@UIXNamespace@@IAEXXZ:NEAR
EXTERN ?DestroyFeature@CVoiceMailPseudoFeature@UIXNamespace@@UAGXXZ:NEAR
EXTERN ?DisableEncoding@CMicrophoneProxy@XHVNamespace@@QAEXXZ:NEAR
EXTERN ?EnableVoiceMailEncoding@CMicrophoneProxy@XHVNamespace@@QAEJXZ:NEAR
EXTERN ?FreeMemory@UIXNamespace@@YGXPAXW4UIX_PTAG_ENUM@1@@Z:NEAR
EXTERN ?HeadphoneCallbackWork@CLocalTalker@XHVNamespace@@AAEXPAX@Z:NEAR
EXTERN ?InitializeInactiveMode@CLocalTalker@XHVNamespace@@QAEJXZ:NEAR
EXTERN ?InitializeLoopbackMode@CLocalTalker@XHVNamespace@@QAEJXZ_0:NEAR
EXTERN ?LaunchDash@CLiveEngine@UIXNamespace@@QAEXKKK@Z:NEAR
EXTERN ?MicrophoneCallbackWork@CLocalTalker@XHVNamespace@@AAEXPAX@Z:NEAR
EXTERN ?SeparateTextAndIcons@CLiveEngine@UIXNamespace@@QAEXPAPBGPAKPAPAU_UIX_SKIN_ICON_INFO@@@Z:NEAR
EXTERN ?SetText@CScreen@UIXNamespace@@IAEXKW4_UIX_RES_STRING_ENUM@@@Z:NEAR
EXTERN ?SetTextWithData@CScreen@UIXNamespace@@IAEXKPBG@Z:NEAR
EXTERN ?Shutdown@CBaseMode@XHVNamespace@@UAEXXZ:NEAR
EXTERN ?Shutdown@CFriendsList@UIXNamespace@@QAEXXZ:NEAR
EXTERN ?ShutdownFeature@CAlertFeature@UIXNamespace@@AAEXXZ:NEAR
EXTERN ?ShutdownInactiveMode@CLocalTalker@XHVNamespace@@QAEXXZ:NEAR
EXTERN ?ShutdownVoiceChatMode@CRemoteTalker@XHVNamespace@@QAEXXZ:NEAR
EXTERN ?StreamCallbackDoubleBufferingWork@CRemoteTalker@XHVNamespace@@QAEXPAX@Z:NEAR
EXTERN ?StreamCallbackTriggerPacketsWork@CRemoteTalker@XHVNamespace@@QAEXPAX@Z:NEAR
EXTERN ?XHVSysAlloc@XHVNamespace@@YGPAXIK@Z:NEAR
EXTERN _CloseHandle@4:NEAR
EXTERN _CreateFileA@28:NEAR
EXTERN _GetFileSize@8:NEAR
EXTERN _IDirectSound_Release@4:NEAR
EXTERN _LocalAlloc@8:NEAR
EXTERN _LocalFree@4:NEAR
EXTERN _ReadFile@20:NEAR
EXTERN _RootDirectory:BYTE
EXTERN _SetFilePointer@16:NEAR
EXTERN _SetLastError@4:NEAR
EXTERN _XcspAllocateSignature@12:NEAR
EXTERN _XcspDeleteSignature@4:NEAR
EXTERN _XcspGrowTable@8:NEAR
EXTERN _XcspLookupFile@8:NEAR
EXTERN __alloca_probe:NEAR
EXTERN _sprintf:NEAR
EXTERN _sub_260EE2:NEAR
EXTERN _sub_26B617:NEAR
EXTERN __imp__ExQueryNonVolatileSetting@20:BYTE
EXTERN __imp__XcSHAUpdate@12:BYTE
EXTERN __imp__XcSHAInit@4:BYTE
EXTERN __imp__XcSHAFinal@8:BYTE
EXTERN __imp__XcHMAC@28:BYTE
EXTERN __imp__DbgPrint:BYTE
EXTERN ??_7CScreen@UIXNamespace@@6B@:BYTE
EXTERN _unk_3F18F8:BYTE
EXTERN ??_7CVoiceMailPseudoFeature@UIXNamespace@@6BCFeature@1@@:BYTE
EXTERN _unk_3F1980:BYTE
EXTERN _unk_539EF8:BYTE

seg0 SEGMENT DWORD PUBLIC ALIAS('.text') 'CODE'

; // match: _ExQueryNonVolatileSetting@20 @ 0x00257A88
PUBLIC _ExQueryNonVolatileSetting@20
_ExQueryNonVolatileSetting@20:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd3dc]
        dd __imp__ExQueryNonVolatileSetting@20

; // match: _XcSHAUpdate@12 @ 0x00257A8E
PUBLIC _XcSHAUpdate@12
_XcSHAUpdate@12:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd3f4]
        dd __imp__XcSHAUpdate@12

; // match: _XcSHAInit@4 @ 0x00257A94
PUBLIC _XcSHAInit@4
_XcSHAInit@4:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd3f8]
        dd __imp__XcSHAInit@4

; // match: _XcSHAFinal@8 @ 0x00257A9A
PUBLIC _XcSHAFinal@8
_XcSHAFinal@8:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd3fc]
        dd __imp__XcSHAFinal@8

; // match: _XcHMAC@28 @ 0x00257AA0
PUBLIC _XcHMAC@28
_XcHMAC@28:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd450]
        dd __imp__XcHMAC@28

; // match: _j_DbgPrint @ 0x00257AA6
PUBLIC _j_DbgPrint
_j_DbgPrint:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4ac]
        dd __imp__DbgPrint
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
seg0 ENDS

seg1 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _XcsRegisterSignatureWithData@36 @ 0x0025DDB2
PUBLIC _XcsRegisterSignatureWithData@36
_XcsRegisterSignatureWithData@36:
        db 055h   ; push ebp
        db 0B8h, 088h, 021h, 000h, 000h   ; mov eax, 0x2188
        db 08Dh, 06Ch, 024h, 0ACh   ; lea ebp, [esp - 0x54]
        call __alloca_probe   ; 0x2C6260
        db 08Bh, 045h, 060h   ; mov eax, dword ptr [ebp + 0x60]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 033h, 0DBh   ; xor ebx, ebx
        db 057h   ; push edi
        db 083h, 0CFh, 0FFh   ; or edi, 0xffffffff
        db 08Bh, 0F0h   ; mov esi, eax
        db 083h, 0E6h, 001h   ; and esi, 1
        db 089h, 07Dh, 050h   ; mov dword ptr [ebp + 0x50], edi
        db 089h, 05Dh, 04Ch   ; mov dword ptr [ebp + 0x4c], ebx
        db 089h, 05Dh, 048h   ; mov dword ptr [ebp + 0x48], ebx
        db 074h, 005h   ; je 0x25dde1
        db 039h, 05Dh, 06Ch   ; cmp dword ptr [ebp + 0x6c], ebx
        db 074h, 021h   ; je 0x25de02
$L_25dde1:
        db 089h, 045h, 060h   ; mov dword ptr [ebp + 0x60], eax
        db 083h, 065h, 060h, 002h   ; and dword ptr [ebp + 0x60], 2
        db 075h, 005h   ; jne 0x25ddef
        db 039h, 05Dh, 068h   ; cmp dword ptr [ebp + 0x68], ebx
        db 074h, 013h   ; je 0x25de02
$L_25ddef:
        db 039h, 05Dh, 068h   ; cmp dword ptr [ebp + 0x68], ebx
        db 074h, 005h   ; je 0x25ddf9
        db 039h, 05Dh, 064h   ; cmp dword ptr [ebp + 0x64], ebx
        db 074h, 009h   ; je 0x25de02
$L_25ddf9:
        db 039h, 07Dh, 05Ch   ; cmp dword ptr [ebp + 0x5c], edi
        db 075h, 010h   ; jne 0x25de0e
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 075h, 00Ch   ; jne 0x25de0e
$L_25de02:
        db 06Ah, 057h   ; push 0x57
        call _SetLastError@4   ; 0x22EC8E
        db 0E9h, 0B1h, 001h, 000h, 000h   ; jmp 0x25dfbf
$L_25de0e:
        db 039h, 05Dh, 060h   ; cmp dword ptr [ebp + 0x60], ebx
        db 074h, 007h   ; je 0x25de1a
        db 0C7h, 045h, 068h, 014h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x68], 0x14
$L_25de1a:
        db 0FFh, 075h, 068h   ; push dword ptr [ebp + 0x68]
        db 050h   ; push eax
        db 0FFh, 075h, 05Ch   ; push dword ptr [ebp + 0x5c]
        call _XcspAllocateSignature@12   ; 0x25DB54
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 089h, 045h, 05Ch   ; mov dword ptr [ebp + 0x5c], eax
        db 00Fh, 084h, 08Eh, 001h, 000h, 000h   ; je 0x25dfbf
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 00Fh, 084h, 0D9h, 000h, 000h, 000h   ; je 0x25df12
        db 039h, 05Dh, 078h   ; cmp dword ptr [ebp + 0x78], ebx
        db 075h, 051h   ; jne 0x25de8f
        db 0FFh, 075h, 06Ch   ; push dword ptr [ebp + 0x6c]
        db 08Dh, 085h, 0CCh, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x134]
        db 068h   ; push 0x51f0a0
        dd _RootDirectory
        db 068h   ; push 0x539ef8
        dd _unk_539EF8
        db 050h   ; push eax
        call _sprintf   ; 0x2C61C4
        db 083h, 0C4h, 010h   ; add esp, 0x10
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 06Ah, 003h   ; push 3
        db 053h   ; push ebx
        db 06Ah, 001h   ; push 1
        db 068h, 000h, 000h, 000h, 080h   ; push 0x80000000
        db 08Dh, 085h, 0CCh, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x134]
        db 050h   ; push eax
        call _CreateFileA@28   ; 0x22D91F
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 050h   ; mov dword ptr [ebp + 0x50], eax
        db 00Fh, 084h, 03Ah, 001h, 000h, 000h   ; je 0x25dfb7
        db 053h   ; push ebx
        db 050h   ; push eax
        call _GetFileSize@8   ; 0x22D8E4
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 045h, 07Ch   ; mov dword ptr [ebp + 0x7c], eax
        db 00Fh, 084h, 000h, 001h, 000h, 000h   ; je 0x25df8f
$L_25de8f:
        db 0FFh, 075h, 07Ch   ; push dword ptr [ebp + 0x7c]
        db 0FFh, 075h, 06Ch   ; push dword ptr [ebp + 0x6c]
        call _XcspLookupFile@8   ; 0x25DCF6
        db 08Bh, 0D8h   ; mov ebx, eax
        db 085h, 0DBh   ; test ebx, ebx
        db 089h, 05Dh, 06Ch   ; mov dword ptr [ebp + 0x6c], ebx
        db 00Fh, 084h, 0EBh, 000h, 000h, 000h   ; je 0x25df92
        db 08Bh, 07Dh, 074h   ; mov edi, dword ptr [ebp + 0x74]
        db 085h, 0FFh   ; test edi, edi
        db 08Bh, 075h, 070h   ; mov esi, dword ptr [ebp + 0x70]
        db 075h, 005h   ; jne 0x25deb6
        db 08Bh, 07Bh, 008h   ; mov edi, dword ptr [ebx + 8]
        db 02Bh, 0FEh   ; sub edi, esi
$L_25deb6:
        db 08Dh, 004h, 03Eh   ; lea eax, [esi + edi]
        db 03Bh, 043h, 008h   ; cmp eax, dword ptr [ebx + 8]
        db 00Fh, 087h, 0D0h, 000h, 000h, 000h   ; ja 0x25df92
        db 06Ah, 00Ch   ; push 0xc
        db 06Ah, 000h   ; push 0
        call _LocalAlloc@8   ; 0x23126F
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 04Ch   ; mov dword ptr [ebp + 0x4c], eax
        db 00Fh, 084h, 0BCh, 000h, 000h, 000h   ; je 0x25df92
        db 08Bh, 04Dh, 05Ch   ; mov ecx, dword ptr [ebp + 0x5c]
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 089h, 078h, 004h   ; mov dword ptr [eax + 4], edi
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 08Bh, 073h, 018h   ; mov esi, dword ptr [ebx + 0x18]
        db 08Dh, 046h, 001h   ; lea eax, [esi + 1]
        db 050h   ; push eax
        db 083h, 0C3h, 014h   ; add ebx, 0x14
        db 053h   ; push ebx
        call _XcspGrowTable@8   ; 0x25DAD3
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 094h, 000h, 000h, 000h   ; je 0x25df8f
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 04Dh, 04Ch   ; mov ecx, dword ptr [ebp + 0x4c]
        db 083h, 065h, 04Ch, 000h   ; and dword ptr [ebp + 0x4c], 0
        db 089h, 00Ch, 0B0h   ; mov dword ptr [eax + esi*4], ecx
        db 0C7h, 045h, 048h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x48], 1
        db 033h, 0DBh   ; xor ebx, ebx
        db 0EBh, 003h   ; jmp 0x25df15
$L_25df12:
        db 08Bh, 07Dh, 074h   ; mov edi, dword ptr [ebp + 0x74]
$L_25df15:
        db 039h, 05Dh, 060h   ; cmp dword ptr [ebp + 0x60], ebx
        db 00Fh, 084h, 0C7h, 000h, 000h, 000h   ; je 0x25dfe5
        db 08Dh, 045h, 0D0h   ; lea eax, [ebp - 0x30]
        db 050h   ; push eax
        call _XcSHAInit@4   ; 0x257A94
        db 08Bh, 045h, 078h   ; mov eax, dword ptr [ebp + 0x78]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 085h, 091h, 000h, 000h, 000h   ; jne 0x25dfc3
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 0FFh, 075h, 070h   ; push dword ptr [ebp + 0x70]
        db 0FFh, 075h, 050h   ; push dword ptr [ebp + 0x50]
        call _SetFilePointer@16   ; 0x22D6BD
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 074h, 04Bh   ; je 0x25df8f
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 00Fh, 084h, 087h, 000h, 000h, 000h   ; je 0x25dfd3
        db 0BBh, 000h, 020h, 000h, 000h   ; mov ebx, 0x2000
$L_25df51:
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 08Bh, 0F3h   ; mov esi, ebx
        db 073h, 002h   ; jae 0x25df59
        db 08Bh, 0F7h   ; mov esi, edi
$L_25df59:
        db 06Ah, 000h   ; push 0
        db 08Dh, 045h, 044h   ; lea eax, [ebp + 0x44]
        db 050h   ; push eax
        db 056h   ; push esi
        db 08Dh, 085h, 0CCh, 0DEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x2134]
        db 050h   ; push eax
        db 0FFh, 075h, 050h   ; push dword ptr [ebp + 0x50]
        call _ReadFile@20   ; 0x22D476
        db 085h, 0C0h   ; test eax, eax
        db 074h, 01Ch   ; je 0x25df8f
        db 039h, 075h, 044h   ; cmp dword ptr [ebp + 0x44], esi
        db 075h, 017h   ; jne 0x25df8f
        db 056h   ; push esi
        db 08Dh, 085h, 0CCh, 0DEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x2134]
        db 050h   ; push eax
        db 08Dh, 045h, 0D0h   ; lea eax, [ebp - 0x30]
        db 050h   ; push eax
        call _XcSHAUpdate@12   ; 0x257A8E
        db 02Bh, 0FEh   ; sub edi, esi
        db 075h, 0C4h   ; jne 0x25df51
        db 0EBh, 044h   ; jmp 0x25dfd3
$L_25df8f:
        db 08Bh, 05Dh, 06Ch   ; mov ebx, dword ptr [ebp + 0x6c]
$L_25df92:
        db 083h, 07Dh, 050h, 0FFh   ; cmp dword ptr [ebp + 0x50], -1
        db 074h, 008h   ; je 0x25dfa0
        db 0FFh, 075h, 050h   ; push dword ptr [ebp + 0x50]
        call _CloseHandle@4   ; 0x22D40D
$L_25dfa0:
        db 083h, 07Dh, 04Ch, 000h   ; cmp dword ptr [ebp + 0x4c], 0
        db 074h, 008h   ; je 0x25dfae
        db 0FFh, 075h, 04Ch   ; push dword ptr [ebp + 0x4c]
        call _LocalFree@4   ; 0x23128C
$L_25dfae:
        db 083h, 07Dh, 048h, 000h   ; cmp dword ptr [ebp + 0x48], 0
        db 074h, 003h   ; je 0x25dfb7
        db 0FFh, 04Bh, 018h   ; dec dword ptr [ebx + 0x18]
$L_25dfb7:
        db 0FFh, 075h, 05Ch   ; push dword ptr [ebp + 0x5c]
        call _XcspDeleteSignature@4   ; 0x25DC36
$L_25dfbf:
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 04Dh   ; jmp 0x25e010
$L_25dfc3:
        db 08Bh, 04Dh, 070h   ; mov ecx, dword ptr [ebp + 0x70]
        db 057h   ; push edi
        db 003h, 0C8h   ; add ecx, eax
        db 051h   ; push ecx
        db 08Dh, 045h, 0D0h   ; lea eax, [ebp - 0x30]
        db 050h   ; push eax
        call _XcSHAUpdate@12   ; 0x257A8E
$L_25dfd3:
        db 08Bh, 045h, 05Ch   ; mov eax, dword ptr [ebp + 0x5c]
        db 083h, 0C0h, 010h   ; add eax, 0x10
        db 050h   ; push eax
        db 08Dh, 045h, 0D0h   ; lea eax, [ebp - 0x30]
        db 050h   ; push eax
        call _XcSHAFinal@8   ; 0x257A9A
        db 0EBh, 01Ah   ; jmp 0x25dfff
$L_25dfe5:
        db 08Bh, 04Dh, 068h   ; mov ecx, dword ptr [ebp + 0x68]
        db 08Bh, 07Dh, 05Ch   ; mov edi, dword ptr [ebp + 0x5c]
        db 08Bh, 075h, 064h   ; mov esi, dword ptr [ebp + 0x64]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 083h, 0C7h, 010h   ; add edi, 0x10
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F3h, 0A4h   ; rep movsb byte ptr es:[edi], byte ptr [esi]
$L_25dfff:
        db 083h, 07Dh, 050h, 0FFh   ; cmp dword ptr [ebp + 0x50], -1
        db 074h, 008h   ; je 0x25e00d
        db 0FFh, 075h, 050h   ; push dword ptr [ebp + 0x50]
        call _CloseHandle@4   ; 0x22D40D
$L_25e00d:
        db 033h, 0C0h   ; xor eax, eax
        db 040h   ; inc eax
$L_25e010:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 083h, 0C5h, 054h   ; add ebp, 0x54
        db 0C9h   ; leave 
        db 0C2h, 024h, 000h   ; ret 0x24
seg1 ENDS

seg4 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: ?CreateFeature@CAlertFeature@UIXNamespace@@UAGJXZ @ 0x0025EF21
PUBLIC ?CreateFeature@CAlertFeature@UIXNamespace@@UAGJXZ
?CreateFeature@CAlertFeature@UIXNamespace@@UAGJXZ:
        db 033h, 0C0h   ; xor eax, eax
        db 0C2h, 004h, 000h   ; ret 4
seg4 ENDS

seg5 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _XapiShutdownChannelStartPacket@8 @ 0x0025F653
PUBLIC _XapiShutdownChannelStartPacket@8
_XapiShutdownChannelStartPacket@8:
        db 0C2h, 008h, 000h   ; ret 8
seg5 ENDS




seg9 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: ?LaunchDash@CFeatureContext@UIXNamespace@@UAGJKKK@Z @ 0x0026007C
PUBLIC ?LaunchDash@CFeatureContext@UIXNamespace@@UAGJKKK@Z
?LaunchDash@CFeatureContext@UIXNamespace@@UAGJKKK@Z:
        db 0FFh, 074h, 024h, 010h   ; push dword ptr [esp + 0x10]
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0FFh, 074h, 024h, 010h   ; push dword ptr [esp + 0x10]
        db 08Bh, 048h, 004h   ; mov ecx, dword ptr [eax + 4]
        db 0FFh, 074h, 024h, 010h   ; push dword ptr [esp + 0x10]
        call ?LaunchDash@CLiveEngine@UIXNamespace@@QAEXKKK@Z   ; 0x25EA16
        db 033h, 0C0h   ; xor eax, eax
        db 0C2h, 010h, 000h   ; ret 0x10
seg9 ENDS

seg27 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: ??_GCExtFeatureScreen@UIXNamespace@@UAEPAXI@Z @ 0x00260099
PUBLIC ??_GCExtFeatureScreen@UIXNamespace@@UAEPAXI@Z
??_GCExtFeatureScreen@UIXNamespace@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x3f16f0
        dd ??_7CScreen@UIXNamespace@@6B@
        call ?Destroy@CScreen@UIXNamespace@@IAEXXZ   ; 0x25ECAF
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x2600b9
        db 068h, 019h, 080h, 000h, 000h   ; push 0x8019
        db 056h   ; push esi
        call ?FreeMemory@UIXNamespace@@YGXPAXW4UIX_PTAG_ENUM@1@@Z   ; 0x26917D
$L_2600b9:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg27 ENDS



seg15 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_265E10 @ 0x00265E10
PUBLIC _sub_265E10
_sub_265E10:
        db 08Bh, 041h, 010h   ; mov eax, dword ptr [ecx + 0x10]
        db 0C3h   ; ret 
seg15 ENDS

seg16 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_265E1E @ 0x00265E1E
PUBLIC _sub_265E1E
_sub_265E1E:
        db 08Bh, 041h, 02Ch   ; mov eax, dword ptr [ecx + 0x2c]
        db 0C3h   ; ret 

seg16 ENDS

seg28 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_265E36 @ 0x00265E36
PUBLIC _sub_265E36
_sub_265E36:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call ??1CVoiceMailPseudoFeature@UIXNamespace@@UAE@XZ   ; 0x265E22
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 007h   ; je 0x265e4c
        db 056h   ; push esi
        call ??3@YAXPAXI@Z   ; 0x12F130
        db 059h   ; pop ecx
$L_265e4c:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg28 ENDS


seg25 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_269DD1 @ 0x00269DD1
PUBLIC _sub_269DD1
_sub_269DD1:
        db 0B8h, 005h, 040h, 000h, 080h   ; mov eax, 0x80004005
        db 0C2h, 00Ch, 000h   ; ret 0xc

seg25 ENDS

seg29 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: ?IsTalking@CBaseMode@XHVNamespace@@UAEHU_XUID@@@Z @ 0x00269DDC
PUBLIC ?IsTalking@CBaseMode@XHVNamespace@@UAEHU_XUID@@@Z
?IsTalking@CBaseMode@XHVNamespace@@UAEHU_XUID@@@Z:
        db 033h, 0C0h   ; xor eax, eax
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg29 ENDS

seg26 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: ?VoiceMailStop@CBaseMode@XHVNamespace@@UAEJPAVCLocalTalker@2@H@Z @ 0x00269DF1
PUBLIC ?VoiceMailStop@CBaseMode@XHVNamespace@@UAEJPAVCLocalTalker@2@H@Z
?VoiceMailStop@CBaseMode@XHVNamespace@@UAEJPAVCLocalTalker@2@H@Z:
        db 0B8h, 005h, 040h, 000h, 080h   ; mov eax, 0x80004005
        db 0C2h, 008h, 000h   ; ret 8

; // match: ?InitializeMode@CVoiceMailMode@XHVNamespace@@UAEJPAVCLocalTalker@2@@Z @ 0x00269DF9
PUBLIC ?InitializeMode@CVoiceMailMode@XHVNamespace@@UAEJPAVCLocalTalker@2@@Z
?InitializeMode@CVoiceMailMode@XHVNamespace@@UAEJPAVCLocalTalker@2@@Z:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        call ?InitializeLoopbackMode@CLocalTalker@XHVNamespace@@QAEJXZ_0   ; 0x26BEE6
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?Shutdown@CVoiceMailMode@XHVNamespace@@UAEXPAVCLocalTalker@2@@Z @ 0x00269E05
PUBLIC ?Shutdown@CVoiceMailMode@XHVNamespace@@UAEXPAVCLocalTalker@2@@Z
?Shutdown@CVoiceMailMode@XHVNamespace@@UAEXPAVCLocalTalker@2@@Z:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        call ?ShutdownVoiceMailMode@CLocalTalker@XHVNamespace@@QAEXXZ   ; 0x26B7D2
        db 0C2h, 004h, 000h   ; ret 4
seg26 ENDS










        END
