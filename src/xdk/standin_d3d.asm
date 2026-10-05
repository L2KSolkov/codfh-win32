; codfh-match: XDK D3D8 code (QFE 1, repacked)
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN _unk_31F454:BYTE
EXTERN ?FixupPushBuffer@D3D@@YGXPAUPushBufferFixup@1@@Z:NEAR
EXTERN ?FlushWCCache@D3D@@YGXXZ:NEAR
EXTERN ?GetPitch@PixelJar@D3D@@YGKPAUD3DPixelContainer@@@Z:NEAR
EXTERN ?HandleMovieFrameIdle@D3D@@YGXXZ:NEAR
EXTERN ?InitSurfaceHeader@D3D@@YGXIIW4_D3DFORMAT@@PAUD3DSurface@@II@Z:NEAR
EXTERN ?ServiceGrInterrupt@CMiniport@D3D@@AAEKXZ:NEAR
EXTERN ?ServiceQueuedFlips@CMiniport@D3D@@AAEKXZ:NEAR
EXTERN ?VBlank@CMiniport@D3D@@AAEKXZ:NEAR
EXTERN _D3DDevice_GetBackBuffer2@4:NEAR
EXTERN _D3DResource_Release@4:NEAR
EXTERN _GetDiskFreeSpaceExA@16:NEAR
EXTERN _GetLastError@0:NEAR
EXTERN _QueryPerformanceFrequency@4:NEAR
EXTERN _SetEndOfFile@4:NEAR
EXTERN _SetFilePointerEx@20:NEAR
EXTERN _Sleep@4:NEAR
EXTERN _WaitForSingleObject@8:NEAR
EXTERN _XMemAlloc@8:NEAR
EXTERN _XMemFree@8:NEAR
EXTERN __alldiv:NEAR
EXTERN __allmul:NEAR
EXTERN __imp__KeSetEvent@12:BYTE
EXTERN __imp__NtClose@4:BYTE
EXTERN __imp__NtCreateFile@36:BYTE
EXTERN __imp__NtSetInformationFile@20:BYTE
EXTERN __vsnprintf:NEAR
EXTERN _j_DbgPrint:NEAR
EXTERN _sprintf:NEAR
EXTERN _unk_31F0C8:BYTE
EXTERN _unk_31F110:BYTE
EXTERN _unk_3207BC:BYTE
EXTERN _unk_320858:BYTE
EXTERN _unk_3208B0:BYTE
EXTERN _unk_320AC4:BYTE
EXTERN _unk_322D28:BYTE
EXTERN _unk_322D2C:BYTE
EXTERN _unk_322D30:BYTE
EXTERN _unk_322D34:BYTE
EXTERN _unk_322D38:BYTE
EXTERN _unk_322D40:BYTE
EXTERN _unk_322D44:BYTE
EXTERN _unk_322D48:BYTE
EXTERN _unk_322D4C:BYTE
EXTERN _unk_322D50:BYTE
EXTERN _unk_322D54:BYTE
EXTERN _unk_322D58:BYTE
EXTERN _unk_322D5C:BYTE
EXTERN _unk_322D60:BYTE
EXTERN _unk_322D64:BYTE
EXTERN _unk_3D4018:BYTE
EXTERN _unk_400100:BYTE
EXTERN _unk_400750:BYTE
EXTERN _unk_400754:BYTE
EXTERN _unk_40186C:BYTE
EXTERN _unk_401A88:BYTE
EXTERN _unk_437860:BYTE
EXTERN ??_C@_0CF@JAIFDFBO@GetDiskFreeSpaceEx?5failed?5with?5?$CF@:BYTE
EXTERN ??_C@_0BM@PMANFOOE@createfile?5error?5?9?5st?$DN?$CF08x?6?$AA@:BYTE
EXTERN ??_C@_07LHBDFJPO@Release?$AA@:BYTE
EXTERN ??_C@_05CCMOGDN@?$CFs?3?$CFs?$AA@:BYTE
EXTERN ??_C@_0DB@PLEMIDFP@Unable?5to?5re?9open?5movie?5cache?5fi@:BYTE
EXTERN ??_C@_0CA@GJMEKBLB@Wait?5for?5image?5write?5timed?9out?6?$AA@:BYTE
EXTERN ??_C@_0BA@LPDJAFGN@SetRenderTarget?$AA@:BYTE
EXTERN ??_C@_0BF@MPBJCMNM@SetVertexShaderInput?$AA@:BYTE
EXTERN ??_C@_0L@BPHKIMHE@SetTexture?$AA@:BYTE
EXTERN ??_C@_0L@BGIJEDPF@SetPalette?$AA@:BYTE
EXTERN ??_C@_0BC@JNDDCMEE@EndVisibilityTest?$AA@:BYTE
EXTERN ??_C@_09FBGPICKC@CopyRects?$AA@:BYTE

seg0 SEGMENT PARA PUBLIC ALIAS('D3D') 'CODE'

; // match: ?GetTime@CMiniport@D3D@@QAEKXZ @ 0x00318EA0
PUBLIC ?GetTime@CMiniport@D3D@@QAEKXZ
?GetTime@CMiniport@D3D@@QAEKXZ:
        db 00Fh, 031h   ; rdtsc 
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
seg0 ENDS



seg3 SEGMENT PARA PUBLIC ALIAS('D3D') 'CODE'

; // match: ?DBGPRINT@D3D@@YAXPADZZ @ 0x0031AB50
PUBLIC ?DBGPRINT@D3D@@YAXPADZZ
?DBGPRINT@D3D@@YAXPADZZ:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 081h, 0ECh, 004h, 001h, 000h, 000h   ; sub esp, 0x104
        db 08Dh, 084h, 024h, 00Ch, 001h, 000h, 000h   ; lea eax, [esp + 0x10c]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 08Dh, 054h, 024h, 008h   ; lea edx, [esp + 8]
        db 068h, 004h, 001h, 000h, 000h   ; push 0x104
        db 052h   ; push edx
        call __vsnprintf   ; 0x2C8656
        db 08Dh, 044h, 024h, 010h   ; lea eax, [esp + 0x10]
        db 050h   ; push eax
        call _j_DbgPrint   ; 0x257AA6
        db 081h, 0C4h, 018h, 001h, 000h, 000h   ; add esp, 0x118
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
seg3 ENDS

seg4 SEGMENT PARA PUBLIC ALIAS('D3D') 'CODE'

; // match: ?HandleShaderSnapshotOpcode@D3D@@YGXXZ @ 0x0031DB50
PUBLIC ?HandleShaderSnapshotOpcode@D3D@@YGXXZ
?HandleShaderSnapshotOpcode@D3D@@YGXXZ LABEL BYTE
        db 0A1h   ; mov eax, dword ptr [0x322d50]
        dd _unk_322D50
        db 083h, 0ECh, 070h   ; sub esp, 0x70
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 08Bh, 02Dh   ; mov ebp, dword ptr [0x320858]
        dd _unk_320858
        db 083h, 0CBh, 0FFh   ; or ebx, 0xffffffff
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 074h, 014h   ; je 0x31db7d
        db 0F6h, 085h, 0D8h, 008h, 000h, 000h, 010h   ; test byte ptr [ebp + 0x8d8], 0x10
        db 074h, 00Bh   ; je 0x31db7d
        db 0A3h   ; mov dword ptr [0x3207bc], eax
        dd _unk_3207BC
        db 089h, 01Dh   ; mov dword ptr [0x322d50], ebx
        dd _unk_322D50
$L_31db7d:
        db 08Bh, 08Dh, 0D4h, 008h, 000h, 000h   ; mov ecx, dword ptr [ebp + 0x8d4]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 025h, 000h, 000h, 000h, 0FFh   ; and eax, 0xff000000
        db 03Dh, 000h, 000h, 000h, 028h   ; cmp eax, 0x28000000
        db 00Fh, 087h, 0DAh, 003h, 000h, 000h   ; ja 0x31df6f
        db 00Fh, 084h, 0B2h, 003h, 000h, 000h   ; je 0x31df4d
        db 033h, 0FFh   ; xor edi, edi
        db 03Bh, 0C7h   ; cmp eax, edi
        db 00Fh, 084h, 0BDh, 003h, 000h, 000h   ; je 0x31df62
        db 03Dh, 000h, 000h, 000h, 021h   ; cmp eax, 0x21000000
        db 00Fh, 084h, 086h, 000h, 000h, 000h   ; je 0x31dc36
        db 03Dh, 000h, 000h, 000h, 023h   ; cmp eax, 0x23000000
        db 00Fh, 085h, 0F1h, 004h, 000h, 000h   ; jne 0x31e0ac
        db 0A0h   ; mov al, byte ptr [0x322d54]
        dd _unk_322D54
        db 084h, 0C0h   ; test al, al
        db 079h, 036h   ; jns 0x31dbfa
        db 0A1h   ; mov eax, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 03Bh, 0C7h   ; cmp eax, edi
        db 074h, 02Dh   ; je 0x31dbfa
        db 06Ah, 00Dh   ; push 0xd
        db 06Ah, 001h   ; push 1
        db 08Dh, 04Ch, 024h, 01Bh   ; lea ecx, [esp + 0x1b]
        db 051h   ; push ecx
        db 068h   ; push 0x322d38
        dd _unk_322D38
        db 050h   ; push eax
        db 0C6h, 044h, 024h, 027h, 001h   ; mov byte ptr [esp + 0x27], 1
        db 0FFh, 015h   ; call dword ptr [0x3cd3b4]
        dd __imp__NtSetInformationFile@20
        db 08Bh, 015h   ; mov edx, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 052h   ; push edx
        db 0FFh, 015h   ; call dword ptr [0x3cd388]
        dd __imp__NtClose@4
        db 089h, 03Dh   ; mov dword ptr [0x322d4c], edi
        dd _unk_322D4C
$L_31dbfa:
        db 08Bh, 095h, 0D8h, 008h, 000h, 000h   ; mov edx, dword ptr [ebp + 0x8d8]
        db 08Bh, 085h, 0DCh, 008h, 000h, 000h   ; mov eax, dword ptr [ebp + 0x8dc]
        db 083h, 0E2h, 0CFh   ; and edx, 0xffffffcf
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 095h, 0D8h, 008h, 000h, 000h   ; mov dword ptr [ebp + 0x8d8], edx
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 000h, 000h, 000h, 024h   ; mov dword ptr [ebp + 0x8d4], 0x24000000
        db 074h, 00Bh   ; je 0x31dc28
        db 068h, 000h, 000h, 080h, 0A1h   ; push 0xa1800000
        db 050h   ; push eax
        call _XMemFree@8   ; 0x22FD39
$L_31dc28:
        db 089h, 0BDh, 0DCh, 008h, 000h, 000h   ; mov dword ptr [ebp + 0x8dc], edi
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31dc36:
        db 08Bh, 085h, 0DCh, 008h, 000h, 000h   ; mov eax, dword ptr [ebp + 0x8dc]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 08Bh, 050h, 008h   ; mov edx, dword ptr [eax + 8]
        db 08Bh, 070h, 004h   ; mov esi, dword ptr [eax + 4]
        db 08Bh, 040h, 00Ch   ; mov eax, dword ptr [eax + 0xc]
        db 089h, 00Dh   ; mov dword ptr [0x322d54], ecx
        dd _unk_322D54
        db 08Dh, 04Ch, 024h, 020h   ; lea ecx, [esp + 0x20]
        db 051h   ; push ecx
        db 089h, 015h   ; mov dword ptr [0x322d64], edx
        dd _unk_322D64
        db 0A3h   ; mov dword ptr [0x322d60], eax
        dd _unk_322D60
        db 089h, 01Dh   ; mov dword ptr [0x322d50], ebx
        dd _unk_322D50
        call _QueryPerformanceFrequency@4   ; 0x22D462
        db 08Bh, 054h, 024h, 024h   ; mov edx, dword ptr [esp + 0x24]
        db 08Bh, 044h, 024h, 020h   ; mov eax, dword ptr [esp + 0x20]
        db 052h   ; push edx
        db 050h   ; push eax
        db 057h   ; push edi
        db 056h   ; push esi
        call __allmul   ; 0x2C7590
        db 057h   ; push edi
        db 068h, 0E8h, 003h, 000h, 000h   ; push 0x3e8
        db 052h   ; push edx
        db 050h   ; push eax
        call __alldiv   ; 0x2C8710
        db 053h   ; push ebx
        db 0A3h   ; mov dword ptr [0x322d28], eax
        dd _unk_322D28
        db 089h, 015h   ; mov dword ptr [0x322d2c], edx
        dd _unk_322D2C
        db 089h, 03Dh   ; mov dword ptr [0x322d30], edi
        dd _unk_322D30
        db 089h, 03Dh   ; mov dword ptr [0x322d34], edi
        dd _unk_322D34
        call _D3DDevice_GetBackBuffer2@4   ; 0x312940
        db 08Bh, 0D8h   ; mov ebx, eax
        db 0A1h   ; mov eax, dword ptr [0x322d54]
        dd _unk_322D54
        db 08Bh, 073h, 010h   ; mov esi, dword ptr [ebx + 0x10]
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E0h, 004h   ; and eax, 4
        db 083h, 0E2h, 003h   ; and edx, 3
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0F8h   ; mov edi, eax
        db 089h, 05Ch, 024h, 018h   ; mov dword ptr [esp + 0x18], ebx
        db 089h, 07Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], edi
        db 075h, 011h   ; jne 0x31dcd4
        db 033h, 0C9h   ; xor ecx, ecx
        db 08Ah, 04Bh, 00Fh   ; mov cl, byte ptr [ebx + 0xf]
        db 0B8h, 001h, 000h, 000h, 000h   ; mov eax, 1
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 0D3h, 0E0h   ; shl eax, cl
        db 0EBh, 00Bh   ; jmp 0x31dcdf
$L_31dcd4:
        db 08Bh, 0C6h   ; mov eax, esi
        db 0C1h, 0E8h, 00Ch   ; shr eax, 0xc
        db 025h, 0FFh, 00Fh, 000h, 000h   ; and eax, 0xfff
        db 040h   ; inc eax
$L_31dcdf:
        db 085h, 0F6h   ; test esi, esi
        db 075h, 012h   ; jne 0x31dcf5
        db 08Bh, 04Bh, 00Ch   ; mov ecx, dword ptr [ebx + 0xc]
        db 0C1h, 0E9h, 014h   ; shr ecx, 0x14
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 0BEh, 001h, 000h, 000h, 000h   ; mov esi, 1
        db 0D3h, 0E6h   ; shl esi, cl
        db 0EBh, 007h   ; jmp 0x31dcfc
$L_31dcf5:
        db 081h, 0E6h, 0FFh, 00Fh, 000h, 000h   ; and esi, 0xfff
        db 046h   ; inc esi
$L_31dcfc:
        db 06Ah, 000h   ; push 0
        db 06Ah, 000h   ; push 0
        db 08Dh, 04Ch, 024h, 048h   ; lea ecx, [esp + 0x48]
        db 051h   ; push ecx
        db 033h, 0C9h   ; xor ecx, ecx
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 095h, 0C1h   ; setne cl
        db 08Dh, 04Ch, 009h, 01Ch   ; lea ecx, [ecx + ecx + 0x1c]
        db 051h   ; push ecx
        db 08Bh, 0CAh   ; mov ecx, edx
        db 0D3h, 0E8h   ; shr eax, cl
        db 0D3h, 0EEh   ; shr esi, cl
        db 050h   ; push eax
        db 056h   ; push esi
        call ?InitSurfaceHeader@D3D@@YGXIIW4_D3DFORMAT@@PAUD3DSurface@@II@Z   ; 0x31D6D0
        db 08Bh, 05Ch, 024h, 050h   ; mov ebx, dword ptr [esp + 0x50]
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 013h   ; jne 0x31dd39
        db 08Bh, 04Ch, 024h, 04Ch   ; mov ecx, dword ptr [esp + 0x4c]
        db 0C1h, 0E9h, 018h   ; shr ecx, 0x18
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 0BFh, 001h, 000h, 000h, 000h   ; mov edi, 1
        db 0D3h, 0E7h   ; shl edi, cl
        db 0EBh, 00Ch   ; jmp 0x31dd45
$L_31dd39:
        db 08Bh, 0FBh   ; mov edi, ebx
        db 0C1h, 0EFh, 00Ch   ; shr edi, 0xc
        db 081h, 0E7h, 0FFh, 00Fh, 000h, 000h   ; and edi, 0xfff
        db 047h   ; inc edi
$L_31dd45:
        db 08Dh, 054h, 024h, 040h   ; lea edx, [esp + 0x40]
        db 052h   ; push edx
        call ?GetPitch@PixelJar@D3D@@YGKPAUD3DPixelContainer@@@Z   ; 0x3125D0
        db 08Bh, 0F0h   ; mov esi, eax
        db 00Fh, 0AFh, 0F7h   ; imul esi, edi
        db 033h, 0FFh   ; xor edi, edi
        db 083h, 0C6h, 040h   ; add esi, 0x40
        db 03Bh, 0DFh   ; cmp ebx, edi
        db 0C7h, 044h, 024h, 058h, 028h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x58], 0x28
        db 075h, 013h   ; jne 0x31dd78
        db 08Bh, 04Ch, 024h, 04Ch   ; mov ecx, dword ptr [esp + 0x4c]
        db 0C1h, 0E9h, 014h   ; shr ecx, 0x14
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 0B8h, 001h, 000h, 000h, 000h   ; mov eax, 1
        db 0D3h, 0E0h   ; shl eax, cl
        db 0EBh, 008h   ; jmp 0x31dd80
$L_31dd78:
        db 08Bh, 0C3h   ; mov eax, ebx
        db 025h, 0FFh, 00Fh, 000h, 000h   ; and eax, 0xfff
        db 040h   ; inc eax
$L_31dd80:
        db 03Bh, 0DFh   ; cmp ebx, edi
        db 089h, 044h, 024h, 05Ch   ; mov dword ptr [esp + 0x5c], eax
        db 075h, 013h   ; jne 0x31dd9b
        db 08Bh, 04Ch, 024h, 04Ch   ; mov ecx, dword ptr [esp + 0x4c]
        db 0C1h, 0E9h, 018h   ; shr ecx, 0x18
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 0BBh, 001h, 000h, 000h, 000h   ; mov ebx, 1
        db 0D3h, 0E3h   ; shl ebx, cl
        db 0EBh, 00Ah   ; jmp 0x31dda5
$L_31dd9b:
        db 0C1h, 0EBh, 00Ch   ; shr ebx, 0xc
        db 081h, 0E3h, 0FFh, 00Fh, 000h, 000h   ; and ebx, 0xfff
        db 043h   ; inc ebx
$L_31dda5:
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 05Ch, 024h, 060h   ; mov dword ptr [esp + 0x60], ebx
        db 039h, 07Ch, 024h, 014h   ; cmp dword ptr [esp + 0x14], edi
        db 00Fh, 095h, 0C0h   ; setne al
        db 08Dh, 04Ch, 024h, 040h   ; lea ecx, [esp + 0x40]
        db 051h   ; push ecx
        db 066h, 0C7h, 044h, 024h, 068h, 001h, 000h   ; mov word ptr [esp + 0x68], 1
        db 089h, 07Ch, 024h, 06Ch   ; mov dword ptr [esp + 0x6c], edi
        db 089h, 074h, 024h, 070h   ; mov dword ptr [esp + 0x70], esi
        db 089h, 035h   ; mov dword ptr [0x322d58], esi
        dd _unk_322D58
        db 08Dh, 004h, 0C5h, 010h, 000h, 000h, 000h   ; lea eax, [eax*8 + 0x10]
        db 066h, 089h, 044h, 024h, 06Ah   ; mov word ptr [esp + 0x6a], ax
        db 089h, 07Ch, 024h, 074h   ; mov dword ptr [esp + 0x74], edi
        db 089h, 07Ch, 024h, 078h   ; mov dword ptr [esp + 0x78], edi
        db 089h, 07Ch, 024h, 07Ch   ; mov dword ptr [esp + 0x7c], edi
        call ?GetPitch@PixelJar@D3D@@YGKPAUD3DPixelContainer@@@Z   ; 0x3125D0
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 052h   ; push edx
        db 089h, 084h, 024h, 080h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x80], eax
        call _D3DResource_Release@4   ; 0x312130
        db 08Dh, 086h, 0FFh, 001h, 000h, 000h   ; lea eax, [esi + 0x1ff]
        db 025h, 000h, 0FEh, 0FFh, 0FFh   ; and eax, 0xfffffe00
        db 068h, 000h, 000h, 080h, 0AEh   ; push 0xae800000
        db 050h   ; push eax
        call _XMemAlloc@8   ; 0x22FC99
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 085h, 0DCh, 008h, 000h, 000h   ; mov dword ptr [ebp + 0x8dc], eax
        db 075h, 012h   ; jne 0x31de2c
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 003h, 000h, 000h, 025h   ; mov dword ptr [ebp + 0x8d4], 0x25000003
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31de2c:
        db 08Bh, 0F8h   ; mov edi, eax
        db 0A0h   ; mov al, byte ptr [0x322d54]
        dd _unk_322D54
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 08Dh, 074h, 024h, 058h   ; lea esi, [esp + 0x58]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 033h, 0F6h   ; xor esi, esi
        db 084h, 0C0h   ; test al, al
        db 00Fh, 089h, 0DEh, 000h, 000h, 000h   ; jns 0x31df26
        db 056h   ; push esi
        db 056h   ; push esi
        db 08Dh, 044h, 024h, 020h   ; lea eax, [esp + 0x20]
        db 050h   ; push eax
        db 068h   ; push 0x31f4ac
        dd _unk_31F4A9+3
        db 0C7h, 005h   ; mov dword ptr [0x322d4c], 0xffffffff
        dd _unk_322D4C
        db 0FFh, 0FFh, 0FFh, 0FFh
        call _GetDiskFreeSpaceExA@16   ; 0x22DE5F
        db 085h, 0C0h   ; test eax, eax
        db 075h, 013h   ; jne 0x31de7a
        call _GetLastError@0   ; 0x22EC66
        db 050h   ; push eax
        db 068h   ; push 0x31f484
        dd ??_C@_0CF@JAIFDFBO@GetDiskFreeSpaceEx?5failed?5with?5?$CF@
        call ?DBGPRINT@D3D@@YAXPADZZ   ; 0x31AB50
        db 083h, 0C4h, 008h   ; add esp, 8
$L_31de7a:
        db 039h, 074h, 024h, 01Ch   ; cmp dword ptr [esp + 0x1c], esi
        db 07Ch, 015h   ; jl 0x31de95
        db 0B8h, 000h, 000h, 000h, 040h   ; mov eax, 0x40000000
        db 07Fh, 006h   ; jg 0x31de8d
        db 039h, 044h, 024h, 018h   ; cmp dword ptr [esp + 0x18], eax
        db 076h, 008h   ; jbe 0x31de95
$L_31de8d:
        db 089h, 044h, 024h, 018h   ; mov dword ptr [esp + 0x18], eax
        db 089h, 074h, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], esi
$L_31de95:
        db 06Ah, 048h   ; push 0x48
        db 056h   ; push esi
        db 056h   ; push esi
        db 056h   ; push esi
        db 08Dh, 04Ch, 024h, 028h   ; lea ecx, [esp + 0x28]
        db 051h   ; push ecx
        db 068h   ; push 0x322d38
        dd _unk_322D38
        db 08Dh, 054h, 024h, 040h   ; lea edx, [esp + 0x40]
        db 052h   ; push edx
        db 068h, 000h, 001h, 010h, 040h   ; push 0x40100100
        db 068h   ; push 0x322d4c
        dd _unk_322D4C
        db 089h, 074h, 024h, 04Ch   ; mov dword ptr [esp + 0x4c], esi
        db 0C7h, 044h, 024h, 054h, 040h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x54], 0x40
        db 0C7h, 044h, 024h, 050h   ; mov dword ptr [esp + 0x50], 0x437860
        dd _unk_437860
        db 0FFh, 015h   ; call dword ptr [0x3cd3cc]
        dd __imp__NtCreateFile@36
        db 03Bh, 0C6h   ; cmp eax, esi
        db 07Dh, 00Bh   ; jge 0x31dedc
        db 050h   ; push eax
        db 068h   ; push 0x31f468
        dd ??_C@_0BM@PMANFOOE@createfile?5error?5?9?5st?$DN?$CF08x?6?$AA@
        db 0E9h, 0A0h, 001h, 000h, 000h   ; jmp 0x31e07c
$L_31dedc:
        db 08Bh, 044h, 024h, 01Ch   ; mov eax, dword ptr [esp + 0x1c]
        db 08Bh, 04Ch, 024h, 018h   ; mov ecx, dword ptr [esp + 0x18]
        db 08Bh, 015h   ; mov edx, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 056h   ; push esi
        db 056h   ; push esi
        db 050h   ; push eax
        db 051h   ; push ecx
        db 052h   ; push edx
        db 089h, 035h   ; mov dword ptr [0x322d40], esi
        dd _unk_322D40
        db 089h, 035h   ; mov dword ptr [0x322d44], esi
        dd _unk_322D44
        call _SetFilePointerEx@20   ; 0x22D7B7
        db 0A1h   ; mov eax, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 050h   ; push eax
        call _SetEndOfFile@4   ; 0x22D639
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x322d44]
        dd _unk_322D44
        db 08Bh, 015h   ; mov edx, dword ptr [0x322d40]
        dd _unk_322D40
        db 0A1h   ; mov eax, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 056h   ; push esi
        db 056h   ; push esi
        db 051h   ; push ecx
        db 052h   ; push edx
        db 050h   ; push eax
        call _SetFilePointerEx@20   ; 0x22D7B7
$L_31df26:
        db 08Bh, 085h, 0D8h, 008h, 000h, 000h   ; mov eax, dword ptr [ebp + 0x8d8]
        db 05Fh   ; pop edi
        db 089h, 035h   ; mov dword ptr [0x322d48], esi
        dd _unk_322D48
        db 083h, 0C8h, 010h   ; or eax, 0x10
        db 05Eh   ; pop esi
        db 089h, 085h, 0D8h, 008h, 000h, 000h   ; mov dword ptr [ebp + 0x8d8], eax
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 000h, 000h, 000h, 022h   ; mov dword ptr [ebp + 0x8d4], 0x22000000
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31df4d:
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 011h   ; je 0x31df62
$L_31df51:
        db 06Ah, 001h   ; push 1
        call _Sleep@4   ; 0x22D112
        db 08Bh, 085h, 0D4h, 008h, 000h, 000h   ; mov eax, dword ptr [ebp + 0x8d4]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 0EFh   ; jne 0x31df51
$L_31df62:
        call ?HandleMovieFrameIdle@D3D@@YGXXZ   ; 0x31D7D0
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31df6f:
        db 03Dh, 000h, 000h, 000h, 029h   ; cmp eax, 0x29000000
        db 074h, 05Ah   ; je 0x31dfd0
        db 03Dh, 000h, 000h, 000h, 041h   ; cmp eax, 0x41000000
        db 00Fh, 085h, 02Bh, 001h, 000h, 000h   ; jne 0x31e0ac
        db 08Bh, 08Dh, 0DCh, 008h, 000h, 000h   ; mov ecx, dword ptr [ebp + 0x8dc]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 0A3h   ; mov dword ptr [0x322d5c], eax
        dd _unk_322D5C
        db 048h   ; dec eax
        db 074h, 012h   ; je 0x31dfa3
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 004h, 000h, 000h, 044h   ; mov dword ptr [ebp + 0x8d4], 0x44000004
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31dfa3:
        db 08Bh, 049h, 004h   ; mov ecx, dword ptr [ecx + 4]
        db 068h   ; push 0x31f460
        dd ??_C@_07LHBDFJPO@Release?$AA@
        db 068h   ; push 0x31f454
        dd _unk_31F454
        db 068h   ; push 0x31f44c
        dd ??_C@_05CCMOGDN@?$CFs?3?$CFs?$AA@
        db 051h   ; push ecx
        call _sprintf   ; 0x2C61C4
        db 083h, 0C4h, 010h   ; add esp, 0x10
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 000h, 000h, 000h, 043h   ; mov dword ptr [ebp + 0x8d4], 0x43000000
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31dfd0:
        db 08Bh, 095h, 0D8h, 008h, 000h, 000h   ; mov edx, dword ptr [ebp + 0x8d8]
        db 083h, 0E2h, 0EFh   ; and edx, 0xffffffef
        db 083h, 0CAh, 020h   ; or edx, 0x20
        db 089h, 095h, 0D8h, 008h, 000h, 000h   ; mov dword ptr [ebp + 0x8d8], edx
        db 0A1h   ; mov eax, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 068h, 0E8h, 003h, 000h, 000h   ; push 0x3e8
        db 050h   ; push eax
        call _WaitForSingleObject@8   ; 0x22D0E6
        db 03Dh, 002h, 001h, 000h, 000h   ; cmp eax, 0x102
        db 075h, 020h   ; jne 0x31e019
        db 068h   ; push 0x31f3d8
        dd ??_C@_0CA@GJMEKBLB@Wait?5for?5image?5write?5timed?9out?6?$AA@
        call ?DBGPRINT@D3D@@YAXPADZZ   ; 0x31AB50
        db 0A1h   ; mov eax, dword ptr [0x322d48]
        dd _unk_322D48
        db 033h, 0F6h   ; xor esi, esi
        db 083h, 0C4h, 004h   ; add esp, 4
        db 03Bh, 0C6h   ; cmp eax, esi
        db 07Eh, 00Ah   ; jle 0x31e01b
        db 048h   ; dec eax
        db 0A3h   ; mov dword ptr [0x322d48], eax
        dd _unk_322D48
        db 0EBh, 002h   ; jmp 0x31e01b
$L_31e019:
        db 033h, 0F6h   ; xor esi, esi
$L_31e01b:
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x322d64]
        dd _unk_322D64
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x322d4c]
        dd _unk_322D4C
        db 083h, 0E7h, 0FEh   ; and edi, 0xfffffffe
        db 051h   ; push ecx
        db 089h, 03Dh   ; mov dword ptr [0x322d64], edi
        dd _unk_322D64
        db 0FFh, 015h   ; call dword ptr [0x3cd388]
        dd __imp__NtClose@4
        db 06Ah, 00Ch   ; push 0xc
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        db 056h   ; push esi
        db 056h   ; push esi
        db 068h   ; push 0x322d38
        dd _unk_322D38
        db 08Dh, 054h, 024h, 04Ch   ; lea edx, [esp + 0x4c]
        db 052h   ; push edx
        db 068h, 000h, 000h, 011h, 080h   ; push 0x80110000
        db 068h   ; push 0x322d4c
        dd _unk_322D4C
        db 089h, 01Dh   ; mov dword ptr [0x322d4c], ebx
        dd _unk_322D4C
        db 089h, 074h, 024h, 058h   ; mov dword ptr [esp + 0x58], esi
        db 0C7h, 044h, 024h, 060h, 040h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x60], 0x40
        db 0C7h, 044h, 024h, 05Ch   ; mov dword ptr [esp + 0x5c], 0x437860
        dd _unk_437860
        db 0FFh, 015h   ; call dword ptr [0x3cd3cc]
        dd __imp__NtCreateFile@36
        db 03Bh, 0C6h   ; cmp eax, esi
        db 07Dh, 020h   ; jge 0x31e096
        db 050h   ; push eax
        db 068h   ; push 0x31f418
        dd ??_C@_0DB@PLEMIDFP@Unable?5to?5re?9open?5movie?5cache?5fi@
$L_31e07c:
        call ?DBGPRINT@D3D@@YAXPADZZ   ; 0x31AB50
        db 083h, 0C4h, 008h   ; add esp, 8
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 004h, 000h, 000h, 025h   ; mov dword ptr [ebp + 0x8d4], 0x25000004
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
$L_31e096:
        db 089h, 035h   ; mov dword ptr [0x322d40], esi
        dd _unk_322D40
        db 089h, 035h   ; mov dword ptr [0x322d44], esi
        dd _unk_322D44
        db 0C7h, 085h, 0D4h, 008h, 000h, 000h, 000h, 000h, 000h, 02Ah   ; mov dword ptr [ebp + 0x8d4], 0x2a000000
$L_31e0ac:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 070h   ; add esp, 0x70
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
seg4 ENDS

seg4_s5 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31E0FA @ 0x0031E0FA
PUBLIC _unk_31E0FA
_unk_31E0FA LABEL BYTE
        db 000h, 000h   ; add byte ptr [eax], al
seg4_s5 ENDS

seg4_s7 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31E103 @ 0x0031E103
PUBLIC _unk_31E103
_unk_31E103 LABEL BYTE
        db 000h
seg4_s7 ENDS

seg4_s6 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31E3DC @ 0x0031E3DC
PUBLIC _unk_31E3DC
_unk_31E3DC LABEL BYTE
        db 000h, 000h   ; add byte ptr [eax], al
        db 000h, 000h   ; add byte ptr [eax], al
seg4_s6 ENDS

seg4_s8 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31E458 @ 0x0031E458
PUBLIC _unk_31E458
_unk_31E458 LABEL BYTE
        db 000h
        db 000h, 000h   ; add byte ptr [eax], al
        db 0C1h
seg4_s8 ENDS

seg4_s1 SEGMENT PARA PUBLIC ALIAS('D3D') 'CODE'

seg4_s1 ENDS

seg4_s2 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31E70C @ 0x0031E70C
PUBLIC _unk_31E70C
_unk_31E70C LABEL BYTE
        db 092h, 015h, 085h, 040h, 03Bh, 0AAh, 0B8h, 03Fh
        db 000h, 000h, 000h, 000h
seg4_s2 ENDS

seg4_s3 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31F452 @ 0x0031F452
PUBLIC _unk_31F452
_unk_31F452 LABEL BYTE
        db 000h
        db 000h
seg4_s3 ENDS

seg4_s4 SEGMENT BYTE PUBLIC READONLY ALIAS('D3D_RD') 'DATA'

; // match: _unk_31F4A9 @ 0x0031F4A9
PUBLIC _unk_31F4A9
_unk_31F4A9 LABEL BYTE
        db 000h
        db 000h
        db 000h
        db 074h
        db 03Ah
        db 000h
        db 000h
seg4_s4 ENDS

        END
