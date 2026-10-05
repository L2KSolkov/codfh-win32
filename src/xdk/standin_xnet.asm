; codfh-match: XDK XNET code (repacked)
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ?XNetGetConfigStatus@CXn@@QAEHPAUXNetConfigStatus@@@Z:NEAR
EXTERN ?XNetConfig@CXn@@QAEHPBUXNetConfigParams@@K@Z:NEAR
EXTERN ?BaseStop@CXnBase@@QAEXXZ:NEAR
EXTERN ?DefaultMask@CIpAddr@@QBE?AU1@XZ:NEAR
EXTERN ?GetEnetHdr@CPacket@@QAEPAUCEnetHdr@@XZ:NEAR
EXTERN ?HalQueryTsc@@YGXPAT_LARGE_INTEGER@@@Z:NEAR
EXTERN ?IpConfigCopyString@CXnIp@@IAEHPADIPBDI@Z:NEAR
EXTERN ?IpConfigReset@CXnIp@@IAEXXZ:NEAR
EXTERN ?IpConfigSetState@CXnIp@@IAEXEH@Z:NEAR
EXTERN ?IpConfigStatus@CXnIp@@IAEHPAUXNetConfigStatus@@@Z:NEAR
EXTERN ?IpDnsRelease@CXnIp@@QAEHPAUXNDNS@@@Z:NEAR
EXTERN ?IpLogoff@CXnIp@@QAEXXZ:NEAR
EXTERN ?IpLogon@CXnIp@@QAEXUCIpAddr@@PA_KPAX@Z:NEAR
EXTERN ?IpLogonChangeUsers@CXnIp@@QAEHPA_K@Z:NEAR
EXTERN ?IpLogonClearQEvent@CXnIp@@QAEHII@Z:NEAR
EXTERN ?IpLogonSetBwLimit@CXnIp@@QAEXKK@Z:NEAR
EXTERN ?IpLogonSetQEvent@CXnIp@@QAEIIPAX@Z:NEAR
EXTERN ?IpQosCliContinue@CXnIp@@QAEXPAUCQosCli@1@@Z:NEAR
EXTERN ?IpQosSrvContinue@CXnIp@@QAEXPAUCQosSrv@1@@Z:NEAR
EXTERN ?IsValidUnicast@CIpAddr@@QBEHXZ:NEAR
EXTERN ?NicGetOtherXnAddr@CXnNic@@QAEKPAUXNADDR@@@Z:NEAR
EXTERN ?NicSetEa@CXnNic@@IAEXPBUCEnetAddr@@@Z:NEAR
EXTERN ?NicStart@CXnNic@@IAEXXZ:NEAR
EXTERN ?NicStop@CXnNic@@IAEXXZ:NEAR
EXTERN ?PacketFree@CXnBase@@QAEXPAVCPacket@@@Z:NEAR
EXTERN ?PoolAlloc@CXnBase@@QAEPAXIK@Z:NEAR
EXTERN ?PoolAllocZ@CXnBase@@QAEPAXIK@Z_0:NEAR
EXTERN ?RemoveHead@CPacketQueue@@QAEPAVCPacket@@XZ:NEAR
EXTERN ?SetInitFlag@CXnHal@@QAEXK@Z:NEAR
EXTERN ?SockClose@CXnSock@@AAEJPAVCSocket@@H@Z:NEAR
EXTERN ?SockInit@CXnSock@@QAEJPAUXNetInitParams@@@Z:NEAR
EXTERN ?SockTerm@CXnSock@@QAEXXZ:NEAR
EXTERN ?TcpTimer@CXnSock@@AAEXPAVCTimer@@@Z:BYTE
EXTERN ?g_pXn@@3PAVCXn@@A:BYTE
EXTERN _SetLastError@4:NEAR
EXTERN _Sleep@4:NEAR
EXTERN _XNetCloseConfigVolume@4:NEAR
EXTERN _XNetLoadConfigParams@4:NEAR
EXTERN _XNetSaveConfigParams@4:NEAR
EXTERN __alldiv:NEAR
EXTERN __imp_@KfLowerIrql@4:BYTE
EXTERN __imp__ExAllocatePoolWithTag@8:BYTE
EXTERN __imp__ExFreePool@4:BYTE
EXTERN __imp__KeQuerySystemTime@4:BYTE
EXTERN __imp__KeRaiseIrqlToDpcLevel@0:BYTE
EXTERN __imp__MmFreeContiguousMemory@4:BYTE
EXTERN __imp__MmLockUnlockBufferPages@12:BYTE
EXTERN __imp__NtOpenFile@24:BYTE
EXTERN __imp__PhyGetLinkState@4:BYTE
EXTERN __imp__RtlInitAnsiString@8:BYTE
EXTERN __imp__RtlNtStatusToDosError@4:BYTE
EXTERN _loc_376E60:NEAR
EXTERN _loc_376E71:NEAR
EXTERN _loc_376E82:NEAR
EXTERN _loc_376E93:NEAR
EXTERN _loc_376EB0:NEAR
EXTERN _loc_376EBF:NEAR
EXTERN _loc_376EE6:NEAR
EXTERN _loc_3770A8:NEAR
EXTERN _loc_3775C6:NEAR
EXTERN _loc_37870D:NEAR
EXTERN _loc_37912A:NEAR
EXTERN _loc_379BAC:NEAR
EXTERN _sub_12000:NEAR
EXTERN _sub_376ED0:NEAR
EXTERN _sub_37F2BC:NEAR
EXTERN _unk_389AB8:BYTE
EXTERN _unk_389ABC:BYTE
EXTERN _unk_3EB318:BYTE
EXTERN _unk_3F13C8:BYTE
EXTERN _unk_50829C:BYTE

seg1 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _sub_376EB0 @ 0x00376EB0
PUBLIC _sub_376EB0
_sub_376EB0:
        db 085h, 0C9h   ; test ecx, ecx
        db 075h, 006h   ; jne 0x376eba
        db 033h, 0C0h   ; xor eax, eax
        db 040h   ; inc eax
        db 0C2h, 004h, 000h   ; ret 4
$L_376eba:
        jmp ?NicGetOtherXnAddr@CXnNic@@QAEKPAUXNADDR@@@Z   ; 0x37A5D9

seg1 ENDS

seg2 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _XNetConfig@8 @ 0x00376F19
PUBLIC _XNetConfig@8
_XNetConfig@8:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp ?XNetConfig@CXn@@QAEHPBUXNetConfigParams@@K@Z   ; 0x376EF7

; // match: _XNetGetConfigStatus@4 @ 0x00376F24
PUBLIC _XNetGetConfigStatus@4
_XNetGetConfigStatus@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp ?XNetGetConfigStatus@CXn@@QAEHPAUXNetConfigStatus@@@Z   ; 0x376F08

; // match: _XNetRandom@8 @ 0x00376F2F
PUBLIC _XNetRandom@8
_XNetRandom@8:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376E93   ; 0x376E93

; // match: _XNetCreateKey@8 @ 0x00376F3A
PUBLIC _XNetCreateKey@8
_XNetCreateKey@8:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376E60   ; 0x376E60

; // match: _XNetRegisterKey@8 @ 0x00376F45
PUBLIC _XNetRegisterKey@8
_XNetRegisterKey@8:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376E71   ; 0x376E71

; // match: _XNetUnregisterKey@4 @ 0x00376F50
PUBLIC _XNetUnregisterKey@4
_XNetUnregisterKey@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376E82   ; 0x376E82
seg2 ENDS

seg3 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _XNetDnsRelease@4 @ 0x00376F89
PUBLIC _XNetDnsRelease@4
_XNetDnsRelease@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376EBF   ; 0x376EBF

; // match: _XNetQosListen@20 @ 0x00376F94
PUBLIC _XNetQosListen@20
_XNetQosListen@20:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        db 05Dh   ; pop ebp
        jmp _sub_376ED0   ; 0x376ED0
seg3 ENDS

seg4 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _XNetQosRelease@4 @ 0x00376FBF
PUBLIC _XNetQosRelease@4
_XNetQosRelease@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376EE6   ; 0x376EE6

; // match: _XNetGetTitleXnAddr@4 @ 0x00376FCA
PUBLIC _XNetGetTitleXnAddr@4
_XNetGetTitleXnAddr@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_376EB0   ; 0x376EB0
seg4 ENDS

seg5 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _closesocket@4 @ 0x00376FE0
PUBLIC _closesocket@4
_closesocket@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_37912A   ; 0x37912A

; // match: _shutdown@8 @ 0x00376FEB
PUBLIC _shutdown@8
_shutdown@8:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_3775C6   ; 0x3775C6
seg5 ENDS

seg8 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _WSACancelOverlappedIO@4 @ 0x00377044
PUBLIC _WSACancelOverlappedIO@4
_WSACancelOverlappedIO@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_37870D   ; 0x37870D
seg8 ENDS

seg9 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _sub_3770A5 @ 0x003770A5
PUBLIC _sub_3770A5
_sub_3770A5:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C3h   ; ret 

seg9 ENDS

seg10 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _XNetUnregisterInAddr@4 @ 0x003770E7
PUBLIC _XNetUnregisterInAddr@4
_XNetUnregisterInAddr@4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5082a0]
        dd ?g_pXn@@3PAVCXn@@A
        jmp _loc_3770A8   ; 0x3770A8

seg10 ENDS


seg14 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: _XNetOpenConfigVolume@0 @ 0x003793B7
PUBLIC _XNetOpenConfigVolume@0
_XNetOpenConfigVolume@0:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 020h   ; sub esp, 0x20
        db 068h   ; push 0x3eb318
        dd _unk_3EB318
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 0FFh, 015h   ; call dword ptr [0x3cd33c]
        dd __imp__RtlInitAnsiString@8
        db 083h, 065h, 0E0h, 000h   ; and dword ptr [ebp - 0x20], 0
        db 06Ah, 010h   ; push 0x10
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 089h, 045h, 0E4h   ; mov dword ptr [ebp - 0x1c], eax
        db 06Ah, 003h   ; push 3
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 050h   ; push eax
        db 08Dh, 045h, 0E0h   ; lea eax, [ebp - 0x20]
        db 050h   ; push eax
        db 068h, 000h, 000h, 010h, 0C0h   ; push 0xc0100000
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 0C7h, 045h, 0E8h, 040h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x18], 0x40
        db 0FFh, 015h   ; call dword ptr [0x3cd3d4]
        dd __imp__NtOpenFile@24
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 004h   ; jge 0x379400
        db 083h, 04Dh, 0FCh, 0FFh   ; or dword ptr [ebp - 4], 0xffffffff
$L_379400:
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 0C9h   ; leave 
        db 0C3h   ; ret 
seg14 ENDS








seg24 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: ?PoolAllocZ@CXnBase@@QAEPAXIK@Z @ 0x0037EEAA
PUBLIC ?PoolAllocZ@CXnBase@@QAEPAXIK@Z
?PoolAllocZ@CXnBase@@QAEPAXIK@Z:
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        call ?PoolAlloc@CXnBase@@QAEPAXIK@Z   ; 0x37EDA7
        db 08Bh, 0D0h   ; mov edx, eax
        db 085h, 0D2h   ; test edx, edx
        db 074h, 01Ah   ; je 0x37eed7
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 057h   ; push edi
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 033h, 0C0h   ; xor eax, eax
        db 08Bh, 0FAh   ; mov edi, edx
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 08Bh, 0CEh   ; mov ecx, esi
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F3h, 0AAh   ; rep stosb byte ptr es:[edi], al
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
$L_37eed7:
        db 08Bh, 0C2h   ; mov eax, edx
        db 0C2h, 008h, 000h   ; ret 8
seg24 ENDS

seg25 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: ?BaseTerm@CXnBase@@QAEXXZ @ 0x0037F378
PUBLIC ?BaseTerm@CXnBase@@QAEXXZ
?BaseTerm@CXnBase@@QAEXXZ:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call ?BaseStop@CXnBase@@QAEXXZ   ; 0x37F340
        db 0F6h, 006h, 080h   ; test byte ptr [esi], 0x80
        db 074h, 016h   ; je 0x37f39b
        db 08Bh, 046h, 050h   ; mov eax, dword ptr [esi + 0x50]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 007h   ; je 0x37f393
        db 050h   ; push eax
        db 0FFh, 015h   ; call dword ptr [0x3cd414]
        dd __imp__ExFreePool@4
$L_37f393:
        db 083h, 066h, 050h, 000h   ; and dword ptr [esi + 0x50], 0
        db 083h, 066h, 054h, 000h   ; and dword ptr [esi + 0x54], 0
$L_37f39b:
        db 068h, 000h, 002h, 000h, 000h   ; push 0x200
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?SetInitFlag@CXnHal@@QAEXK@Z   ; 0x38682A
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg25 ENDS

seg26 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: ?TimerDpc@CXnBase@@CGXPAU_KDPC@@PAX11@Z @ 0x0037F4E6
PUBLIC ?TimerDpc@CXnBase@@CGXPAU_KDPC@@PAX11@Z
?TimerDpc@CXnBase@@CGXPAU_KDPC@@PAX11@Z:
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        call _sub_37F2BC   ; 0x37F2BC
        db 0C2h, 010h, 000h   ; ret 0x10
seg26 ENDS

seg28 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: ?NicTerm@CXnNic@@IAEXXZ @ 0x0037FDE5
PUBLIC ?NicTerm@CXnNic@@IAEXXZ
?NicTerm@CXnNic@@IAEXXZ:
        db 053h   ; push ebx
        db 08Bh, 0D9h   ; mov ebx, ecx
        call ?NicStop@CXnNic@@IAEXXZ   ; 0x37FD7B
        db 068h, 000h, 040h, 000h, 000h   ; push 0x4000
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?SetInitFlag@CXnHal@@QAEXK@Z   ; 0x38682A
        db 0F6h, 043h, 001h, 004h   ; test byte ptr [ebx + 1], 4
        db 074h, 06Ch   ; je 0x37fe6b
        db 08Dh, 083h, 060h, 002h, 000h, 000h   ; lea eax, [ebx + 0x260]
        db 083h, 038h, 000h   ; cmp dword ptr [eax], 0
        db 074h, 009h   ; je 0x37fe13
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 0FFh, 052h, 00Ch   ; call dword ptr [edx + 0xc]
$L_37fe13:
        db 057h   ; push edi
        db 08Dh, 0BBh, 038h, 002h, 000h, 000h   ; lea edi, [ebx + 0x238]
        db 083h, 03Fh, 000h   ; cmp dword ptr [edi], 0
        db 074h, 03Ah   ; je 0x37fe59
        db 056h   ; push esi
$L_37fe20:
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?RemoveHead@CPacketQueue@@QAEPAVCPacket@@XZ   ; 0x37EB25
        db 08Bh, 0F0h   ; mov esi, eax
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 00Fh, 0B7h, 04Eh, 004h   ; movzx ecx, word ptr [esi + 4]
        db 0C1h, 0E8h, 013h   ; shr eax, 0x13
        db 083h, 0E0h, 001h   ; and eax, 1
        db 08Dh, 044h, 0C1h, 00Eh   ; lea eax, [ecx + eax*8 + 0xe]
        db 06Ah, 001h   ; push 1
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?GetEnetHdr@CPacket@@QAEPAUCEnetHdr@@XZ   ; 0x37F061
        db 050h   ; push eax
        db 0FFh, 015h   ; call dword ptr [0x3cd458]
        dd __imp__MmLockUnlockBufferPages@12
        db 056h   ; push esi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?PacketFree@CXnBase@@QAEXPAVCPacket@@@Z   ; 0x37F046
        db 083h, 03Fh, 000h   ; cmp dword ptr [edi], 0
        db 075h, 0C8h   ; jne 0x37fe20
        db 05Eh   ; pop esi
$L_37fe59:
        db 08Bh, 083h, 028h, 002h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x228]
        db 085h, 0C0h   ; test eax, eax
        db 05Fh   ; pop edi
        db 074h, 007h   ; je 0x37fe6b
        db 050h   ; push eax
        db 0FFh, 015h   ; call dword ptr [0x3cd37c]
        dd __imp__MmFreeContiguousMemory@4
$L_37fe6b:
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 05Bh   ; pop ebx
        jmp ?BaseTerm@CXnBase@@QAEXXZ   ; 0x37F378
seg28 ENDS

seg31 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: ?IpQosSrvComplete@CXnIp@@QAEXPAUCQosPkt@1@@Z @ 0x00381A2E
PUBLIC ?IpQosSrvComplete@CXnIp@@QAEXPAUCQosPkt@1@@Z
?IpQosSrvComplete@CXnIp@@QAEXPAUCQosPkt@1@@Z:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 0FFh, 070h, 018h   ; push dword ptr [eax + 0x18]
        db 083h, 060h, 014h, 000h   ; and dword ptr [eax + 0x14], 0
        call ?IpQosSrvContinue@CXnIp@@QAEXPAUCQosSrv@1@@Z   ; 0x380FF0
        db 0C2h, 004h, 000h   ; ret 4
seg31 ENDS

seg32 SEGMENT BYTE PUBLIC ALIAS('XNET') 'CODE'

; // match: ?IpQosCliComplete@CXnIp@@QAEXPAUCQosPkt@1@@Z @ 0x00382726
PUBLIC ?IpQosCliComplete@CXnIp@@QAEXPAUCQosPkt@1@@Z
?IpQosCliComplete@CXnIp@@QAEXPAUCQosPkt@1@@Z:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 0FFh, 070h, 018h   ; push dword ptr [eax + 0x18]
        db 083h, 060h, 014h, 000h   ; and dword ptr [eax + 0x14], 0
        call ?IpQosCliContinue@CXnIp@@QAEXPAUCQosCli@1@@Z   ; 0x381D90
        db 0C2h, 004h, 000h   ; ret 4
seg32 ENDS


seg37 SEGMENT BYTE PUBLIC READONLY ALIAS('XNET_RD') 'DATA'

; // match: _g_ostCdRomDeviceName @ 0x00389900
PUBLIC _g_ostCdRomDeviceName
_g_ostCdRomDeviceName LABEL BYTE
        db 00Eh   ; push cs
        db 000h, 00Fh   ; add byte ptr [edi], cl
        db 000h, 0C8h   ; add al, cl
        db 0B5h, 03Eh   ; mov ch, 0x3e
        db 000h, 0FFh   ; add bh, bh
        db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 020h, 036h, 03Ah, 0A6h, 0E9h, 042h, 04Ch, 0F4h, 0C6h
        db 07Eh, 05Eh, 062h, 076h, 0B5h, 085h, 0E4h, 045h, 0C2h, 051h, 06Dh, 06Dh, 035h, 0E1h, 04Fh, 037h
        db 014h, 05Fh, 0F2h, 06Dh, 00Ah, 02Bh, 030h, 01Bh, 043h, 03Ah, 0CDh, 0B3h, 019h, 095h, 0EFh, 0DDh
        db 004h, 034h, 08Eh, 079h, 008h, 04Ah, 051h, 022h, 09Bh, 013h, 03Bh, 0A6h, 0BEh, 00Bh, 002h, 074h
        db 0CCh, 067h, 08Ah, 008h, 04Eh, 002h, 029h, 0D1h, 01Ch, 0DCh, 080h, 08Bh, 062h, 0C6h, 0C4h, 034h
        db 0C2h, 068h, 021h, 0A2h, 0DAh, 00Fh, 0C9h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 002h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 00Ch, 008h, 004h, 008h, 040h, 010h, 010h, 004h, 020h, 040h, 00Ah, 004h, 001h, 00Ah, 001h
        db 03Ch, 000h, 040h, 003h, 009h, 004h, 004h, 004h, 002h, 00Ah, 03Ch, 005h, 078h, 002h, 00Eh, 005h
        db 003h, 008h, 009h, 005h, 008h, 002h, 014h, 00Dh, 00Ah, 003h, 001h, 005h, 005h, 03Fh, 03Fh, 01Eh
        db 014h, 03Ch, 005h, 003h, 001h, 008h, 005h, 009h, 001h, 004h, 002h, 004h, 002h, 005h, 014h, 00Dh
        db 008h, 004h, 020h, 002h, 040h, 002h, 003h, 002h, 003h, 002h, 003h, 000h, 000h, 000h, 000h, 000h
        db 000h, 004h, 004h, 001h, 004h, 001h, 001h, 001h, 001h, 001h, 001h, 004h, 001h, 001h, 001h, 001h
        db 001h, 000h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h
        db 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h
        db 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h, 001h
        db 001h, 001h, 004h, 001h, 004h, 001h, 001h, 001h, 001h, 001h, 001h, 000h, 000h, 000h, 000h, 000h
        db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0E8h, 03Fh, 03Fh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
        db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
        db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 03Fh, 03Fh, 0FFh
        db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
        db 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
seg37 ENDS

seg37_s1 SEGMENT BYTE PUBLIC READONLY ALIAS('XNET_RD') 'DATA'

; // match: _unk_389AC9 @ 0x00389AC9
PUBLIC _unk_389AC9
_unk_389AC9 LABEL BYTE
        db 000h, 000h, 000h, 054h, 03Ah, 000h, 000h, 078h, 0A4h, 06Ah, 0D7h, 056h, 0B7h, 0C7h, 0E8h, 0DBh
        db 070h, 020h, 024h, 0EEh, 0CEh, 0BDh, 0C1h, 0AFh, 00Fh, 07Ch, 0F5h, 02Ah, 0C6h, 087h, 047h, 013h
        db 046h, 030h, 0A8h, 001h, 095h, 046h, 0FDh, 0D8h, 098h, 080h, 069h, 0AFh, 0F7h, 044h, 08Bh, 0B1h
        db 05Bh, 0FFh, 0FFh, 0BEh, 0D7h, 05Ch, 089h, 022h, 011h, 090h, 06Bh, 093h, 071h, 098h, 0FDh, 08Eh
        db 043h, 079h, 0A6h, 021h, 008h, 0B4h, 049h, 062h, 025h, 01Eh, 0F6h, 040h, 0B3h, 040h, 0C0h, 051h
        db 05Ah, 05Eh, 026h, 0AAh, 0C7h, 0B6h, 0E9h, 05Dh, 010h, 02Fh, 0D6h, 053h, 014h, 044h, 002h, 081h
        db 0E6h, 0A1h, 0D8h, 0C8h, 0FBh, 0D3h, 0E7h, 0E6h, 0CDh, 0E1h, 021h, 0D6h, 007h, 037h, 0C3h, 087h
        db 00Dh, 0D5h, 0F4h, 0EDh, 014h, 05Ah, 045h, 005h, 0E9h, 0E3h, 0A9h, 0F8h, 0A3h, 0EFh, 0FCh, 0D9h
        db 002h, 06Fh, 067h, 08Ah, 04Ch, 02Ah, 08Dh, 042h, 039h, 0FAh, 0FFh, 081h, 0F6h, 071h, 087h, 022h
        db 061h, 09Dh, 06Dh, 00Ch, 038h, 0E5h, 0FDh, 044h, 0EAh, 0BEh, 0A4h, 0A9h, 0CFh, 0DEh, 04Bh, 060h
        db 04Bh, 0BBh, 0F6h, 070h, 0BCh, 0BFh, 0BEh, 0C6h, 07Eh, 09Bh, 028h, 0FAh, 027h, 0A1h, 0EAh, 085h
        db 030h, 0EFh, 0D4h, 005h, 01Dh, 088h, 004h, 039h, 0D0h, 0D4h, 0D9h, 0E5h, 099h, 0DBh, 0E6h, 0F8h
        db 07Ch, 0A2h, 01Fh, 065h, 056h, 0ACh, 0C4h, 044h, 022h, 029h, 0F4h, 097h, 0FFh, 02Ah, 043h, 0A7h
        db 023h, 094h, 0ABh, 039h, 0A0h, 093h, 0FCh, 0C3h, 059h, 05Bh, 065h, 092h, 0CCh, 00Ch, 08Fh, 07Dh
        db 0F4h, 0EFh, 0FFh, 0D1h, 05Dh, 084h, 085h, 04Fh, 07Eh, 0A8h, 06Fh, 0E0h, 0E6h, 02Ch, 0FEh, 014h
        db 043h, 001h, 0A3h, 0A1h, 011h, 008h, 04Eh, 082h, 07Eh, 053h, 0F7h, 035h, 0F2h, 03Ah, 0BDh, 0BBh
        db 0D2h, 0D7h, 02Ah, 091h, 0D3h, 086h, 0EBh
seg37_s1 ENDS

        END
