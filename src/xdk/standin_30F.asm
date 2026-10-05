; codfh-match: XDK crypto thunks, C++ EH handlers and UIX initializers
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ??0CAlertFeature@UIXNamespace@@QAE@XZ:NEAR
EXTERN ??0CFriendsFeature@UIXNamespace@@QAE@XZ:NEAR
EXTERN ??0CLogonFeature@UIXNamespace@@QAE@XZ:NEAR
EXTERN ??0CPlayersFeature@UIXNamespace@@QAE@XZ:NEAR
EXTERN ??0CVoiceMailPseudoFeature@UIXNamespace@@QAE@XZ:NEAR
EXTERN ??1CLogonFeature@UIXNamespace@@UAE@XZ:NEAR
EXTERN ??1CPlayersFeature@UIXNamespace@@UAE@XZ:NEAR
EXTERN ?DestroyFeature@CVoiceMailPseudoFeature@UIXNamespace@@UAGXXZ:NEAR
EXTERN ?g_AlertFeature@@3VCAlertFeature@UIXNamespace@@A:BYTE
EXTERN ___CxxFrameHandler:NEAR
EXTERN ??1MyErrorLog@XGRAPHICS@@QAE@XZ:NEAR
EXTERN ??1CD3DXAssembler@XGRAPHICS@@QAE@XZ:NEAR
EXTERN _atexit:NEAR
EXTERN ?DestroyFeature@CAlertFeature@UIXNamespace@@UAGXXZ:NEAR
EXTERN _sub_262BEB:NEAR
EXTERN __imp__XcBlockCryptCBC@28:BYTE
EXTERN __imp__XcKeyTable@12:BYTE
EXTERN __imp__XcDESKeyParity@8:BYTE
EXTERN __imp__XcRC4Crypt@12:BYTE
EXTERN __imp__XcRC4Key@12:BYTE
EXTERN __imp__XcModExp@20:BYTE
EXTERN __imp__XcVerifyPKCS1Signature@12:BYTE
EXTERN __imp__RtlUnwind@16:BYTE
EXTERN _unk_3F1730:BYTE
EXTERN _unk_3F18F8:BYTE
EXTERN ??_7CVoiceMailPseudoFeature@UIXNamespace@@6BCFeature@1@@:BYTE
EXTERN _unk_426108:BYTE
EXTERN _unk_4263D8:BYTE
EXTERN _unk_4264E0:BYTE
EXTERN _unk_426578:BYTE
EXTERN _unk_4265EC:BYTE
EXTERN _unk_4266F0:BYTE
EXTERN _unk_426714:BYTE
EXTERN _unk_426878:BYTE
EXTERN _unk_426A44:BYTE
EXTERN _unk_426AE8:BYTE
EXTERN _unk_426B24:BYTE
EXTERN _unk_508650:BYTE
EXTERN _unk_508718:BYTE
EXTERN _unk_508A34:BYTE
EXTERN _unk_508A3C:BYTE
EXTERN _unk_508A68:BYTE

seg0 SEGMENT PARA PUBLIC ALIAS('.text') 'CODE'

; // match: _XcBlockCryptCBC@28 @ 0x002FEC60
PUBLIC _XcBlockCryptCBC@28
_XcBlockCryptCBC@28:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4d4]
        dd __imp__XcBlockCryptCBC@28

; // match: _XcKeyTable@12 @ 0x002FEC66
PUBLIC _XcKeyTable@12
_XcKeyTable@12:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4d8]
        dd __imp__XcKeyTable@12

; // match: _XcDESKeyParity@8 @ 0x002FEC6C
PUBLIC _XcDESKeyParity@8
_XcDESKeyParity@8:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4dc]
        dd __imp__XcDESKeyParity@8

; // match: _XcRC4Crypt@12 @ 0x002FEC72
PUBLIC _XcRC4Crypt@12
_XcRC4Crypt@12:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4e0]
        dd __imp__XcRC4Crypt@12

; // match: _XcRC4Key@12 @ 0x002FEC78
PUBLIC _XcRC4Key@12
_XcRC4Key@12:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4e4]
        dd __imp__XcRC4Key@12

; // match: _XcModExp@20 @ 0x002FEC7E
PUBLIC _XcModExp@20
_XcModExp@20:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4e8]
        dd __imp__XcModExp@20

; // match: _XcVerifyPKCS1Signature@12 @ 0x002FEC84
PUBLIC _XcVerifyPKCS1Signature@12
_XcVerifyPKCS1Signature@12:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd4ec]
        dd __imp__XcVerifyPKCS1Signature@12

; // match: _RtlUnwind@16 @ 0x002FEC8A
PUBLIC _RtlUnwind@16
_RtlUnwind@16:
        db 0FFh, 025h   ; jmp dword ptr [0x3cd52c]
        dd __imp__RtlUnwind@16
seg0 ENDS

seg1 SEGMENT BYTE PUBLIC ALIAS('.text$x') 'CODE'

; // match: _sub_309017 @ 0x00309017
PUBLIC _sub_309017
_sub_309017:
        db 08Dh, 04Dh, 0CCh   ; lea ecx, [ebp-0x34]
        jmp ??1MyErrorLog@XGRAPHICS@@QAE@XZ   ; 0x391E6B
        db 08Dh, 08Dh, 0E8h, 0FBh, 0FFh, 0FFh   ; lea ecx, [ebp-0x418]
        jmp ??1CD3DXAssembler@XGRAPHICS@@QAE@XZ   ; 0x3A0FF3

; // match: _sub_30902A @ 0x0030902A
PUBLIC _sub_30902A
_sub_30902A:
        db 0B8h   ; mov eax, 0x426108
        dd _unk_426108
        jmp ___CxxFrameHandler   ; 0x2C588B
seg1 ENDS













        END
