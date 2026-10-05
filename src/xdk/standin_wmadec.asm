; codfh-match: XDK DSOUND WMA decoder code (QFE 1, repacked)
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN _prvDecodeRunLevel_XDS@20:NEAR
EXTERN ??_GCWMADecoder@@QAEPAXI@Z:NEAR
EXTERN _GetFileSize@8:NEAR
EXTERN _GetLastError@0:NEAR
EXTERN _SetEvent@4:NEAR
EXTERN _WMAFileSeek@8:NEAR
EXTERN _WMARawDecReset@4:NEAR
EXTERN _WMA_GetBuffer@16:NEAR
EXTERN _WMA_ParsePacketHeader@4:NEAR
EXTERN _WMA_ParsePayloadHeader@4:NEAR
EXTERN _WaitForSingleObject@8:NEAR
EXTERN __imp__RtlEnterCriticalSection@4:BYTE
EXTERN __imp__RtlLeaveCriticalSection@4:BYTE
EXTERN _ibstrmGetMoreData@8:NEAR
EXTERN _prvGetNextRunDEC_XDS@12:NEAR
EXTERN _unk_3AB56A:NEAR

seg2 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: ?GetInfo@CWMAXMediaObject@@UAGJPAU_XMEDIAINFO@@@Z @ 0x003AB227
PUBLIC ?GetInfo@CWMAXMediaObject@@UAGJPAU_XMEDIAINFO@@@Z
?GetInfo@CWMAXMediaObject@@UAGJPAU_XMEDIAINFO@@@Z:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 083h, 060h, 00Ch, 000h   ; and dword ptr [eax + 0xc], 0
        db 083h, 060h, 004h, 000h   ; and dword ptr [eax + 4], 0
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 0C7h, 000h, 003h, 000h, 000h, 000h   ; mov dword ptr [eax], 3
        db 08Bh, 049h, 014h   ; mov ecx, dword ptr [ecx + 0x14]
        db 0C1h, 0E1h, 00Ch   ; shl ecx, 0xc
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 033h, 0C0h   ; xor eax, eax
        db 0C2h, 008h, 000h   ; ret 8
seg2 ENDS

seg14 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: ?GetStatus@CWMAXMediaObject@@UAGJPAK@Z @ 0x003AB250
PUBLIC ?GetStatus@CWMAXMediaObject@@UAGJPAK@Z
?GetStatus@CWMAXMediaObject@@UAGJPAK@Z:
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 00Ch   ; mov edi, dword ptr [esp + 0xc]
        db 085h, 0FFh   ; test edi, edi
        db 074h, 035h   ; je 0x3ab28e
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 00Ch   ; mov esi, dword ptr [esp + 0xc]
        db 0C7h, 007h, 002h, 000h, 000h, 000h   ; mov dword ptr [edi], 2
        db 083h, 0BEh, 0C4h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xc4], 0
        db 074h, 020h   ; je 0x3ab28d
        db 053h   ; push ebx
        db 08Dh, 05Eh, 07Ch   ; lea ebx, [esi + 0x7c]
        db 053h   ; push ebx
        db 0FFh, 015h   ; call dword ptr [0x3cd304]
        dd __imp__RtlEnterCriticalSection@4
        db 08Dh, 086h, 0ACh, 000h, 000h, 000h   ; lea eax, [esi + 0xac]
        db 039h, 000h   ; cmp dword ptr [eax], eax
        db 075h, 003h   ; jne 0x3ab285
        db 083h, 027h, 000h   ; and dword ptr [edi], 0
$L_3ab285:
        db 053h   ; push ebx
        db 0FFh, 015h   ; call dword ptr [0x3cd300]
        dd __imp__RtlLeaveCriticalSection@4
        db 05Bh   ; pop ebx
$L_3ab28d:
        db 05Eh   ; pop esi
$L_3ab28e:
        db 033h, 0C0h   ; xor eax, eax
        db 05Fh   ; pop edi
        db 0C2h, 008h, 000h   ; ret 8
seg14 ENDS

seg4 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: ?SeekToTime@CWMAXMediaObject@@UAGJKPAK@Z @ 0x003AB300
PUBLIC ?SeekToTime@CWMAXMediaObject@@UAGJKPAK@Z
?SeekToTime@CWMAXMediaObject@@UAGJKPAK@Z:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 083h, 07Eh, 034h, 000h   ; cmp dword ptr [esi + 0x34], 0
        db 00Fh, 084h, 084h, 000h, 000h, 000h   ; je 0x3ab393
        db 083h, 0BEh, 0C4h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xc4], 0
        db 074h, 056h   ; je 0x3ab36e
        db 08Bh, 046h, 050h   ; mov eax, dword ptr [esi + 0x50]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 074h   ; je 0x3ab393
        db 050h   ; push eax
        call _SetEvent@4   ; 0x22CEB7
        db 068h, 0D0h, 007h, 000h, 000h   ; push 0x7d0
        db 0FFh, 076h, 054h   ; push dword ptr [esi + 0x54]
        call _WaitForSingleObject@8   ; 0x22D0E6
        db 085h, 0C0h   ; test eax, eax
        db 075h, 05Dh   ; jne 0x3ab393
        db 08Dh, 08Eh, 0B4h, 000h, 000h, 000h   ; lea ecx, [esi + 0xb4]
        db 039h, 009h   ; cmp dword ptr [ecx], ecx
        db 074h, 026h   ; je 0x3ab366
        db 053h   ; push ebx
        db 08Dh, 096h, 0ACh, 000h, 000h, 000h   ; lea edx, [esi + 0xac]
        db 057h   ; push edi
$L_3ab348:
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 08Bh, 058h, 004h   ; mov ebx, dword ptr [eax + 4]
        db 089h, 03Bh   ; mov dword ptr [ebx], edi
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 03Ah   ; mov edi, dword ptr [edx]
        db 089h, 038h   ; mov dword ptr [eax], edi
        db 089h, 050h, 004h   ; mov dword ptr [eax + 4], edx
        db 089h, 047h, 004h   ; mov dword ptr [edi + 4], eax
        db 089h, 002h   ; mov dword ptr [edx], eax
        db 039h, 009h   ; cmp dword ptr [ecx], ecx
        db 075h, 0E4h   ; jne 0x3ab348
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
$L_3ab366:
        db 0FFh, 076h, 050h   ; push dword ptr [esi + 0x50]
        call _SetEvent@4   ; 0x22CEB7
$L_3ab36e:
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 0FFh, 076h, 034h   ; push dword ptr [esi + 0x34]
        call _WMAFileSeek@8   ; 0x3AC2B3
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 002h   ; je 0x3ab384
        db 089h, 001h   ; mov dword ptr [ecx], eax
$L_3ab384:
        db 083h, 066h, 058h, 000h   ; and dword ptr [esi + 0x58], 0
        db 0C7h, 046h, 008h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 8], 1
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 005h   ; jmp 0x3ab398
$L_3ab393:
        db 0B8h, 005h, 040h, 000h, 080h   ; mov eax, 0x80004005
$L_3ab398:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg4 ENDS

seg15 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: ?SetFileIOCallbacks@CWMAXMediaObject@@UAGXPAU_XWMA_FILEIO_CALLBACKS@@@Z @ 0x003AB39C
PUBLIC ?SetFileIOCallbacks@CWMAXMediaObject@@UAGXPAU_XWMA_FILEIO_CALLBACKS@@@Z
?SetFileIOCallbacks@CWMAXMediaObject@@UAGXPAU_XWMA_FILEIO_CALLBACKS@@@Z:
        db 0C2h, 008h, 000h   ; ret 8
; // match: ?GetLength@CWMAXMediaObject@@UAGJPAK@Z @ 0x003AB39F
PUBLIC ?GetLength@CWMAXMediaObject@@UAGJPAK@Z
?GetLength@CWMAXMediaObject@@UAGJPAK@Z:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 056h   ; push esi
        db 033h, 0F6h   ; xor esi, esi
        db 056h   ; push esi
        db 0FFh, 070h, 060h   ; push dword ptr [eax + 0x60]
        call _GetFileSize@8   ; 0x22D8E4
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 08Bh, 04Ch, 024h, 00Ch   ; mov ecx, dword ptr [esp + 0xc]
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 075h, 025h   ; jne 0x3ab3df
        call _GetLastError@0   ; 0x22EC66
        db 085h, 0C0h   ; test eax, eax
        db 07Fh, 009h   ; jg 0x3ab3cc
        call _GetLastError@0   ; 0x22EC66
        db 08Bh, 0F0h   ; mov esi, eax
        db 0EBh, 013h   ; jmp 0x3ab3df
$L_3ab3cc:
        call _GetLastError@0   ; 0x22EC66
        db 08Bh, 0F0h   ; mov esi, eax
        db 081h, 0E6h, 0FFh, 0FFh, 000h, 000h   ; and esi, 0xffff
        db 081h, 0CEh, 000h, 000h, 007h, 080h   ; or esi, 0x80070000
$L_3ab3df:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 008h, 000h   ; ret 8
; // match: ?DoWork@CWMAXMediaObject@@UAGXXZ @ 0x003AB3E5
PUBLIC ?DoWork@CWMAXMediaObject@@UAGXXZ
?DoWork@CWMAXMediaObject@@UAGXXZ:
        db 0C2h, 004h, 000h   ; ret 4
seg15 ENDS

seg7 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: ?WmaXmoThreadProc@@YGKPAX@Z @ 0x003AB91C
PUBLIC ?WmaXmoThreadProc@@YGKPAX@Z
?WmaXmoThreadProc@@YGKPAX@Z:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        call _unk_3AB56A   ; 0x3AB56A
        db 0CCh   ; int3 

; // match: ?Release@CWMAXMediaObject@@UAGKXZ @ 0x003AB926
PUBLIC ?Release@CWMAXMediaObject@@UAGKXZ
?Release@CWMAXMediaObject@@UAGKXZ:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Dh, 082h, 09Ch, 000h, 000h, 000h   ; lea eax, [edx + 0x9c]
        db 056h   ; push esi
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 0B8h, 0FFh, 0FFh, 0FFh, 0FFh   ; mov eax, 0xffffffff
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 00Fh, 0C1h, 001h   ; xadd dword ptr [ecx], eax
        db 048h   ; dec eax
        db 08Bh, 0F0h   ; mov esi, eax
        db 085h, 0F6h   ; test esi, esi
        db 075h, 00Dh   ; jne 0x3ab955
        db 085h, 0D2h   ; test edx, edx
        db 074h, 009h   ; je 0x3ab955
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CAh   ; mov ecx, edx
        call ??_GCWMADecoder@@QAEPAXI@Z   ; 0x3AB701
$L_3ab955:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C2h, 004h, 000h   ; ret 4
seg7 ENDS

seg8 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: _WMAFileContentDesc@8 @ 0x003AC055
PUBLIC _WMAFileContentDesc@8
_WMAFileContentDesc@8:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 033h, 0DBh   ; xor ebx, ebx
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 057h   ; push edi
        db 00Fh, 084h, 041h, 002h, 000h, 000h   ; je 0x3ac2a9
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 00Fh, 084h, 036h, 002h, 000h, 000h   ; je 0x3ac2a9
        db 039h, 09Eh, 098h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x98], ebx
        db 075h, 018h   ; jne 0x3ac093
        db 066h, 089h, 01Fh   ; mov word ptr [edi], bx
        db 066h, 089h, 05Fh, 002h   ; mov word ptr [edi + 2], bx
        db 066h, 089h, 05Fh, 004h   ; mov word ptr [edi + 4], bx
        db 066h, 089h, 05Fh, 006h   ; mov word ptr [edi + 6], bx
        db 066h, 089h, 05Fh, 008h   ; mov word ptr [edi + 8], bx
        db 0E9h, 012h, 002h, 000h, 000h   ; jmp 0x3ac2a5
$L_3ac093:
        db 066h, 08Bh, 00Fh   ; mov cx, word ptr [edi]
        db 066h, 03Bh, 0CBh   ; cmp cx, bx
        db 07Eh, 04Ch   ; jle 0x3ac0e7
        db 08Bh, 057h, 00Ah   ; mov edx, dword ptr [edi + 0xa]
        db 03Bh, 0D3h   ; cmp edx, ebx
        db 074h, 03Bh   ; je 0x3ac0dd
        db 066h, 08Bh, 086h, 09Ch, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0x9c]
        db 066h, 03Bh, 0C3h   ; cmp ax, bx
        db 076h, 025h   ; jbe 0x3ac0d3
        db 00Fh, 0B7h, 0C0h   ; movzx eax, ax
        db 00Fh, 0BFh, 0C9h   ; movsx ecx, cx
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 08Bh, 0D8h   ; mov ebx, eax
        db 07Ch, 002h   ; jl 0x3ac0bc
        db 08Bh, 0D9h   ; mov ebx, ecx
$L_3ac0bc:
        db 052h   ; push edx
        db 053h   ; push ebx
        db 0FFh, 0B6h, 098h, 000h, 000h, 000h   ; push dword ptr [esi + 0x98]
        db 056h   ; push esi
        call _WMA_GetBuffer@16   ; 0x3ACA06
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 00Fh   ; je 0x3ac0dd
        db 0E9h, 0B9h, 001h, 000h, 000h   ; jmp 0x3ac28c
$L_3ac0d3:
        db 0C6h, 042h, 001h, 000h   ; mov byte ptr [edx + 1], 0
        db 08Bh, 047h, 00Ah   ; mov eax, dword ptr [edi + 0xa]
        db 0C6h, 000h, 000h   ; mov byte ptr [eax], 0
$L_3ac0dd:
        db 066h, 08Bh, 086h, 09Ch, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0x9c]
        db 066h, 089h, 007h   ; mov word ptr [edi], ax
$L_3ac0e7:
        db 066h, 08Bh, 057h, 002h   ; mov dx, word ptr [edi + 2]
        db 066h, 085h, 0D2h   ; test dx, dx
        db 07Eh, 05Ah   ; jle 0x3ac14a
        db 08Bh, 047h, 00Eh   ; mov eax, dword ptr [edi + 0xe]
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 074h, 045h   ; je 0x3ac13f
        db 066h, 08Bh, 08Eh, 09Eh, 000h, 000h, 000h   ; mov cx, word ptr [esi + 0x9e]
        db 066h, 085h, 0C9h   ; test cx, cx
        db 076h, 02Fh   ; jbe 0x3ac135
        db 00Fh, 0B7h, 086h, 09Ch, 000h, 000h, 000h   ; movzx eax, word ptr [esi + 0x9c]
        db 003h, 086h, 098h, 000h, 000h, 000h   ; add eax, dword ptr [esi + 0x98]
        db 00Fh, 0B7h, 0C9h   ; movzx ecx, cx
        db 00Fh, 0BFh, 0D2h   ; movsx edx, dx
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 07Ch, 002h   ; jl 0x3ac121
        db 08Bh, 0DAh   ; mov ebx, edx
$L_3ac121:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 050h   ; push eax
        db 056h   ; push esi
        call _WMA_GetBuffer@16   ; 0x3ACA06
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 00Fh   ; je 0x3ac13f
        db 0E9h, 057h, 001h, 000h, 000h   ; jmp 0x3ac28c
$L_3ac135:
        db 0C6h, 040h, 001h, 000h   ; mov byte ptr [eax + 1], 0
        db 08Bh, 047h, 00Eh   ; mov eax, dword ptr [edi + 0xe]
        db 0C6h, 000h, 000h   ; mov byte ptr [eax], 0
$L_3ac13f:
        db 066h, 08Bh, 086h, 09Eh, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0x9e]
        db 066h, 089h, 047h, 002h   ; mov word ptr [edi + 2], ax
$L_3ac14a:
        db 066h, 08Bh, 057h, 004h   ; mov dx, word ptr [edi + 4]
        db 066h, 085h, 0D2h   ; test dx, dx
        db 07Eh, 063h   ; jle 0x3ac1b6
        db 08Bh, 047h, 012h   ; mov eax, dword ptr [edi + 0x12]
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 074h, 04Eh   ; je 0x3ac1ab
        db 066h, 08Bh, 08Eh, 0A0h, 000h, 000h, 000h   ; mov cx, word ptr [esi + 0xa0]
        db 066h, 085h, 0C9h   ; test cx, cx
        db 076h, 038h   ; jbe 0x3ac1a1
        db 00Fh, 0B7h, 09Eh, 09Ch, 000h, 000h, 000h   ; movzx ebx, word ptr [esi + 0x9c]
        db 00Fh, 0B7h, 086h, 09Eh, 000h, 000h, 000h   ; movzx eax, word ptr [esi + 0x9e]
        db 003h, 0C3h   ; add eax, ebx
        db 003h, 086h, 098h, 000h, 000h, 000h   ; add eax, dword ptr [esi + 0x98]
        db 00Fh, 0B7h, 0C9h   ; movzx ecx, cx
        db 00Fh, 0BFh, 0D2h   ; movsx edx, dx
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 07Ch, 002h   ; jl 0x3ac18d
        db 08Bh, 0DAh   ; mov ebx, edx
$L_3ac18d:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 050h   ; push eax
        db 056h   ; push esi
        call _WMA_GetBuffer@16   ; 0x3ACA06
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 00Fh   ; je 0x3ac1ab
        db 0E9h, 0EBh, 000h, 000h, 000h   ; jmp 0x3ac28c
$L_3ac1a1:
        db 0C6h, 040h, 001h, 000h   ; mov byte ptr [eax + 1], 0
        db 08Bh, 047h, 012h   ; mov eax, dword ptr [edi + 0x12]
        db 0C6h, 000h, 000h   ; mov byte ptr [eax], 0
$L_3ac1ab:
        db 066h, 08Bh, 086h, 0A0h, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0xa0]
        db 066h, 089h, 047h, 004h   ; mov word ptr [edi + 4], ax
$L_3ac1b6:
        db 066h, 08Bh, 057h, 006h   ; mov dx, word ptr [edi + 6]
        db 066h, 085h, 0D2h   ; test dx, dx
        db 07Eh, 069h   ; jle 0x3ac228
        db 08Bh, 047h, 016h   ; mov eax, dword ptr [edi + 0x16]
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 074h, 054h   ; je 0x3ac21d
        db 066h, 08Bh, 08Eh, 0A2h, 000h, 000h, 000h   ; mov cx, word ptr [esi + 0xa2]
        db 066h, 085h, 0C9h   ; test cx, cx
        db 076h, 03Eh   ; jbe 0x3ac213
        db 00Fh, 0B7h, 09Eh, 09Eh, 000h, 000h, 000h   ; movzx ebx, word ptr [esi + 0x9e]
        db 00Fh, 0B7h, 086h, 0A0h, 000h, 000h, 000h   ; movzx eax, word ptr [esi + 0xa0]
        db 003h, 0C3h   ; add eax, ebx
        db 00Fh, 0B7h, 09Eh, 09Ch, 000h, 000h, 000h   ; movzx ebx, word ptr [esi + 0x9c]
        db 003h, 0C3h   ; add eax, ebx
        db 003h, 086h, 098h, 000h, 000h, 000h   ; add eax, dword ptr [esi + 0x98]
        db 00Fh, 0B7h, 0C9h   ; movzx ecx, cx
        db 00Fh, 0BFh, 0D2h   ; movsx edx, dx
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 07Ch, 002h   ; jl 0x3ac202
        db 08Bh, 0DAh   ; mov ebx, edx
$L_3ac202:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 050h   ; push eax
        db 056h   ; push esi
        call _WMA_GetBuffer@16   ; 0x3ACA06
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 00Ch   ; je 0x3ac21d
        db 0EBh, 079h   ; jmp 0x3ac28c
$L_3ac213:
        db 0C6h, 040h, 001h, 000h   ; mov byte ptr [eax + 1], 0
        db 08Bh, 047h, 016h   ; mov eax, dword ptr [edi + 0x16]
        db 0C6h, 000h, 000h   ; mov byte ptr [eax], 0
$L_3ac21d:
        db 066h, 08Bh, 086h, 0A2h, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0xa2]
        db 066h, 089h, 047h, 006h   ; mov word ptr [edi + 6], ax
$L_3ac228:
        db 066h, 08Bh, 057h, 008h   ; mov dx, word ptr [edi + 8]
        db 066h, 085h, 0D2h   ; test dx, dx
        db 07Eh, 074h   ; jle 0x3ac2a5
        db 08Bh, 047h, 01Ah   ; mov eax, dword ptr [edi + 0x1a]
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 074h, 05Fh   ; je 0x3ac29a
        db 066h, 08Bh, 08Eh, 0A4h, 000h, 000h, 000h   ; mov cx, word ptr [esi + 0xa4]
        db 066h, 085h, 0C9h   ; test cx, cx
        db 076h, 049h   ; jbe 0x3ac290
        db 00Fh, 0B7h, 09Eh, 0A0h, 000h, 000h, 000h   ; movzx ebx, word ptr [esi + 0xa0]
        db 00Fh, 0B7h, 086h, 0A2h, 000h, 000h, 000h   ; movzx eax, word ptr [esi + 0xa2]
        db 003h, 0C3h   ; add eax, ebx
        db 00Fh, 0B7h, 09Eh, 09Eh, 000h, 000h, 000h   ; movzx ebx, word ptr [esi + 0x9e]
        db 003h, 0C3h   ; add eax, ebx
        db 00Fh, 0B7h, 09Eh, 09Ch, 000h, 000h, 000h   ; movzx ebx, word ptr [esi + 0x9c]
        db 003h, 0C3h   ; add eax, ebx
        db 003h, 086h, 098h, 000h, 000h, 000h   ; add eax, dword ptr [esi + 0x98]
        db 00Fh, 0B7h, 0C9h   ; movzx ecx, cx
        db 00Fh, 0BFh, 0D2h   ; movsx edx, dx
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 07Ch, 002h   ; jl 0x3ac27d
        db 08Bh, 0DAh   ; mov ebx, edx
$L_3ac27d:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 050h   ; push eax
        db 056h   ; push esi
        call _WMA_GetBuffer@16   ; 0x3ACA06
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 00Eh   ; je 0x3ac29a
$L_3ac28c:
        db 06Ah, 003h   ; push 3
        db 0EBh, 01Bh   ; jmp 0x3ac2ab
$L_3ac290:
        db 0C6h, 040h, 001h, 000h   ; mov byte ptr [eax + 1], 0
        db 08Bh, 047h, 01Ah   ; mov eax, dword ptr [edi + 0x1a]
        db 0C6h, 000h, 000h   ; mov byte ptr [eax], 0
$L_3ac29a:
        db 066h, 08Bh, 086h, 0A4h, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0xa4]
        db 066h, 089h, 047h, 008h   ; mov word ptr [edi + 8], ax
$L_3ac2a5:
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 003h   ; jmp 0x3ac2ac
$L_3ac2a9:
        db 06Ah, 002h   ; push 2
$L_3ac2ab:
        db 058h   ; pop eax
$L_3ac2ac:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 008h, 000h   ; ret 8
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 00Ch   ; mov esi, dword ptr [esp + 0xc]
        db 085h, 0F6h   ; test esi, esi
        db 057h   ; push edi
        db 00Fh, 084h, 0B8h, 000h, 000h, 000h   ; je 0x3ac37a
        db 083h, 0BEh, 058h, 001h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x158], 0
        db 00Fh, 084h, 0ABh, 000h, 000h, 000h   ; je 0x3ac37a
        db 08Bh, 07Eh, 018h   ; mov edi, dword ptr [esi + 0x18]
        db 033h, 0DBh   ; xor ebx, ebx
        db 085h, 0FFh   ; test edi, edi
        db 076h, 01Dh   ; jbe 0x3ac2f5
        db 033h, 0D2h   ; xor edx, edx
        db 08Bh, 0C7h   ; mov eax, edi
        db 0F7h, 076h, 014h   ; div dword ptr [esi + 0x14]
        db 033h, 0D2h   ; xor edx, edx
        db 08Bh, 0C8h   ; mov ecx, eax
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 0F7h, 0F1h   ; div ecx
        db 08Bh, 0D8h   ; mov ebx, eax
        db 085h, 0DBh   ; test ebx, ebx
        db 074h, 006h   ; je 0x3ac2f5
        db 0F6h, 0C3h, 00Fh   ; test bl, 0xf
        db 075h, 001h   ; jne 0x3ac2f5
        db 043h   ; inc ebx
$L_3ac2f5:
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 03Bh, 0D8h   ; cmp ebx, eax
        db 073h, 04Eh   ; jae 0x3ac34a
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 00Fh, 0AFh, 0C3h   ; imul eax, ebx
        db 003h, 046h, 008h   ; add eax, dword ptr [esi + 8]
        db 056h   ; push esi
        db 089h, 006h   ; mov dword ptr [esi], eax
        call _WMA_ParsePacketHeader@4   ; 0x3AD813
        db 085h, 0C0h   ; test eax, eax
        db 075h, 029h   ; jne 0x3ac33a
        db 039h, 086h, 0E4h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xe4], eax
        db 074h, 008h   ; je 0x3ac321
        db 039h, 086h, 0DCh, 000h, 000h, 000h   ; cmp dword ptr [esi + 0xdc], eax
        db 075h, 019h   ; jne 0x3ac33a
$L_3ac321:
        db 056h   ; push esi
        db 089h, 086h, 048h, 001h, 000h, 000h   ; mov dword ptr [esi + 0x148], eax
        call _WMA_ParsePayloadHeader@4   ; 0x3ADC1B
        db 085h, 0C0h   ; test eax, eax
        db 075h, 009h   ; jne 0x3ac33a
        db 080h, 0BEh, 038h, 001h, 000h, 000h, 001h   ; cmp byte ptr [esi + 0x138], 1
        db 075h, 005h   ; jne 0x3ac33f
$L_3ac33a:
        db 08Bh, 07Eh, 018h   ; mov edi, dword ptr [esi + 0x18]
        db 0EBh, 00Dh   ; jmp 0x3ac34c
$L_3ac33f:
        db 08Bh, 0BEh, 034h, 001h, 000h, 000h   ; mov edi, dword ptr [esi + 0x134]
        db 02Bh, 07Eh, 01Ch   ; sub edi, dword ptr [esi + 0x1c]
        db 0EBh, 002h   ; jmp 0x3ac34c
$L_3ac34a:
        db 08Bh, 0D8h   ; mov ebx, eax
$L_3ac34c:
        db 0FFh, 0B6h, 058h, 001h, 000h, 000h   ; push dword ptr [esi + 0x158]
        call _WMARawDecReset@4   ; 0x3ADFBB
        db 085h, 0C0h   ; test eax, eax
        db 074h, 005h   ; je 0x3ac360
        db 033h, 0C0h   ; xor eax, eax
        db 040h   ; inc eax
        db 0EBh, 01Dh   ; jmp 0x3ac37d
$L_3ac360:
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 00Fh, 0AFh, 0C3h   ; imul eax, ebx
        db 003h, 046h, 008h   ; add eax, dword ptr [esi + 8]
        db 0C7h, 086h, 0C8h, 000h, 000h, 000h, 003h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc8], 3
        db 089h, 046h, 004h   ; mov dword ptr [esi + 4], eax
        db 08Bh, 0C7h   ; mov eax, edi
        db 0EBh, 003h   ; jmp 0x3ac37d
$L_3ac37a:
        db 06Ah, 002h   ; push 2
        db 058h   ; pop eax
$L_3ac37d:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8
seg8 ENDS

seg10 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: _ibstrmPeekBits@12 @ 0x003B0F2A
PUBLIC _ibstrmPeekBits@12
_ibstrmPeekBits@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 033h, 0C0h   ; xor eax, eax
        db 083h, 07Eh, 024h, 018h   ; cmp dword ptr [esi + 0x24], 0x18
        db 077h, 049h   ; ja 0x3b0f82
        db 053h   ; push ebx
        db 057h   ; push edi

; // match: _sub_3B0F3B @ 0x003B0F3B
PUBLIC _sub_3B0F3B
_sub_3B0F3B:
$L_3b0f3b:
        db 08Bh, 056h, 01Ch   ; mov edx, dword ptr [esi + 0x1c]

; // match: _sub_3B0F3E @ 0x003B0F3E
PUBLIC _sub_3B0F3E
_sub_3B0F3E:
        db 085h, 0D2h   ; test edx, edx
        db 07Eh, 024h   ; jle 0x3b0f66
        db 0C1h, 066h, 020h, 008h   ; shl dword ptr [esi + 0x20], 8
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 00Fh, 0B6h, 019h   ; movzx ebx, byte ptr [ecx]
        db 08Bh, 07Eh, 020h   ; mov edi, dword ptr [esi + 0x20]
        db 083h, 046h, 024h, 008h   ; add dword ptr [esi + 0x24], 8
        db 00Bh, 0DFh   ; or ebx, edi
        db 041h   ; inc ecx
        db 04Ah   ; dec edx
        db 089h, 05Eh, 020h   ; mov dword ptr [esi + 0x20], ebx
        db 089h, 04Eh, 018h   ; mov dword ptr [esi + 0x18], ecx
        db 089h, 056h, 01Ch   ; mov dword ptr [esi + 0x1c], edx
        db 083h, 07Eh, 024h, 018h   ; cmp dword ptr [esi + 0x24], 0x18
        db 076h, 0D5h   ; jbe 0x3b0f3b
$L_3b0f66:
        db 083h, 07Eh, 024h, 018h   ; cmp dword ptr [esi + 0x24], 0x18
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
        db 077h, 014h   ; ja 0x3b0f82
        db 083h, 07Eh, 01Ch, 000h   ; cmp dword ptr [esi + 0x1c], 0
        db 07Fh, 00Eh   ; jg 0x3b0f82
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 056h   ; push esi
        call _ibstrmGetMoreData@8   ; 0x3B0CBE
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 027h   ; jl 0x3b0fa9
$L_3b0f82:
        db 08Bh, 055h, 00Ch   ; mov edx, dword ptr [ebp + 0xc]
        db 039h, 056h, 024h   ; cmp dword ptr [esi + 0x24], edx
        db 073h, 007h   ; jae 0x3b0f91
        db 0B8h, 004h, 000h, 004h, 080h   ; mov eax, 0x80040004
        db 0EBh, 018h   ; jmp 0x3b0fa9
$L_3b0f91:
        db 033h, 0C9h   ; xor ecx, ecx
        db 08Ah, 04Eh, 024h   ; mov cl, byte ptr [esi + 0x24]
        db 08Bh, 076h, 020h   ; mov esi, dword ptr [esi + 0x20]
        db 02Ah, 0CAh   ; sub cl, dl
        db 0D3h, 0EEh   ; shr esi, cl
        db 06Ah, 020h   ; push 0x20
        db 059h   ; pop ecx
        db 02Bh, 0CAh   ; sub ecx, edx
        db 0D3h, 0E6h   ; shl esi, cl
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 089h, 031h   ; mov dword ptr [ecx], esi
$L_3b0fa9:
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg10 ENDS


seg12 SEGMENT BYTE PUBLIC ALIAS('WMADEC') 'CODE'

; // match: _prvDecodeCoefficientMono_XDS@12 @ 0x003B3F68
PUBLIC _prvDecodeCoefficientMono_XDS@12
_prvDecodeCoefficientMono_XDS@12:
$L_3b3f68:
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        db 033h, 0C0h   ; xor eax, eax
        db 039h, 041h, 024h   ; cmp dword ptr [ecx + 0x24], eax
        db 074h, 012h   ; je 0x3b3f85
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 0FFh, 071h, 020h   ; push dword ptr [ecx + 0x20]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        call _prvDecodeRunLevel_XDS@20   ; 0x3B3412
$L_3b3f85:
        db 0C2h, 00Ch, 000h   ; ret 0xc

; // match: _prvDecodeCoefficientStereo_XDS@12 @ 0x003B3F88
PUBLIC _prvDecodeCoefficientStereo_XDS@12
_prvDecodeCoefficientStereo_XDS@12:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 00Ch   ; mov esi, dword ptr [esp + 0xc]
        db 08Bh, 01Eh   ; mov ebx, dword ptr [esi]
        db 00Fh, 0BFh, 04Eh, 024h   ; movsx ecx, word ptr [esi + 0x24]
        db 00Fh, 0B7h, 053h, 058h   ; movzx edx, word ptr [ebx + 0x58]
        db 033h, 0C0h   ; xor eax, eax
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 07Dh, 04Fh   ; jge 0x3b3fed
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 018h   ; mov edi, dword ptr [esp + 0x18]
$L_3b3fa3:
        db 00Fh, 0BFh, 046h, 024h   ; movsx eax, word ptr [esi + 0x24]
        db 06Bh, 0C0h, 070h   ; imul eax, eax, 0x70
        db 003h, 044h, 024h, 014h   ; add eax, dword ptr [esp + 0x14]
        db 057h   ; push edi
        db 050h   ; push eax
        db 056h   ; push esi
        db 0E8h, 0B2h, 0FFh, 0FFh, 0FFh   ; call 0x3b3f68
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 032h   ; jl 0x3b3fec
        db 083h, 07Bh, 044h, 001h   ; cmp dword ptr [ebx + 0x44], 1
        db 075h, 015h   ; jne 0x3b3fd5
        db 08Bh, 04Eh, 054h   ; mov ecx, dword ptr [esi + 0x54]
        db 083h, 0E1h, 007h   ; and ecx, 7
        db 001h, 00Fh   ; add dword ptr [edi], ecx
        db 08Bh, 04Eh, 054h   ; mov ecx, dword ptr [esi + 0x54]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 083h, 0E2h, 007h   ; and edx, 7
        db 02Bh, 0CAh   ; sub ecx, edx
        db 089h, 04Eh, 054h   ; mov dword ptr [esi + 0x54], ecx
$L_3b3fd5:
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 066h, 083h, 061h, 074h, 000h   ; and word ptr [ecx + 0x74], 0
        db 066h, 0FFh, 046h, 024h   ; inc word ptr [esi + 0x24]
        db 00Fh, 0BFh, 04Eh, 024h   ; movsx ecx, word ptr [esi + 0x24]
        db 00Fh, 0B7h, 053h, 058h   ; movzx edx, word ptr [ebx + 0x58]
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 07Ch, 0B7h   ; jl 0x3b3fa3
$L_3b3fec:
        db 05Fh   ; pop edi
$L_3b3fed:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc

seg12 ENDS

seg13 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

; // match: _sub_3B635C @ 0x003B635C
PUBLIC _sub_3B635C
_sub_3B635C LABEL BYTE
        db 0CCh, 0CCh, 0CCh, 0CCh, 020h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h
        db 002h, 000h, 000h, 000h, 003h, 000h, 000h, 000h, 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h
        db 005h, 040h, 000h, 080h, 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h
        db 001h, 000h, 004h, 080h, 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h
seg13 ENDS

seg13_s1 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

; // match: _unk_3B64DC @ 0x003B64DC
PUBLIC _unk_3B64DC
_unk_3B64DC LABEL BYTE
        db 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 002h, 000h, 000h, 000h, 003h, 000h, 000h, 000h
        db 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h, 006h, 000h, 000h, 000h, 005h, 040h, 000h, 080h
        db 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h, 001h, 000h, 004h, 080h
        db 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h, 005h, 000h, 004h, 080h
        db 006h, 000h, 004h, 080h, 007h, 000h, 004h, 080h, 008h, 000h, 004h, 080h, 009h, 000h, 004h, 080h
        db 080h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 002h, 000h, 000h, 000h
        db 003h, 000h, 000h, 000h, 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h, 006h, 000h, 000h, 000h
        db 005h, 040h, 000h, 080h, 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h
        db 001h, 000h, 004h, 080h, 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h
        db 005h, 000h, 004h, 080h, 006h, 000h, 004h, 080h, 007h, 000h, 004h, 080h, 008h, 000h, 004h, 080h
        db 009h, 000h, 004h, 080h, 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 002h, 000h, 000h, 000h
        db 003h, 000h, 000h, 000h, 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h, 006h, 000h, 000h, 000h
        db 005h, 040h, 000h, 080h, 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h
        db 001h, 000h, 004h, 080h, 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h
        db 005h, 000h, 004h, 080h, 006h, 000h, 004h, 080h, 007h, 000h, 004h, 080h, 008h, 000h, 004h, 080h
        db 009h, 000h, 004h, 080h
seg13_s1 ENDS

seg13_s2 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

seg13_s2 ENDS


seg13_s3 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

; // match: _unk_3B6768 @ 0x003B6768
PUBLIC _unk_3B6768
_unk_3B6768 LABEL BYTE
        db 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 002h, 000h, 000h, 000h, 003h, 000h, 000h, 000h
        db 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h, 006h, 000h, 000h, 000h, 005h, 040h, 000h, 080h
        db 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h, 001h, 000h, 004h, 080h
        db 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h, 005h, 000h, 004h, 080h
        db 006h, 000h, 004h, 080h, 007h, 000h, 004h, 080h, 008h, 000h, 004h, 080h, 009h, 000h, 004h, 080h
seg13_s3 ENDS

seg13_s4 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

seg13_s4 ENDS

seg13_s5 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

; // match: _unk_3C4058 @ 0x003C4058
PUBLIC _unk_3C4058
_unk_3C4058 LABEL BYTE
        db 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 002h, 000h, 000h, 000h, 003h, 000h, 000h, 000h
        db 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h, 006h, 000h, 000h, 000h, 005h, 040h, 000h, 080h
        db 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h, 001h, 000h, 004h, 080h
        db 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h, 005h, 000h, 004h, 080h
        db 006h, 000h, 004h, 080h, 007h, 000h, 004h, 080h, 008h, 000h, 004h, 080h, 009h, 000h, 004h, 080h
        db 00Ah, 0D7h, 0A3h, 03Ch, 000h, 000h, 000h, 031h
seg13_s5 ENDS

seg13_s6 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

seg13_s6 ENDS

seg13_s7 SEGMENT BYTE PUBLIC READONLY ALIAS('WMADEC_RD') 'DATA'

; // match: _unk_3C43D8 @ 0x003C43D8
PUBLIC _unk_3C43D8
_unk_3C43D8 LABEL BYTE
        db 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 002h, 000h, 000h, 000h, 003h, 000h, 000h, 000h
        db 004h, 000h, 000h, 000h, 005h, 000h, 000h, 000h, 006h, 000h, 000h, 000h, 005h, 040h, 000h, 080h
        db 00Eh, 000h, 007h, 080h, 057h, 000h, 007h, 080h, 000h, 000h, 004h, 080h, 001h, 000h, 004h, 080h
        db 002h, 000h, 004h, 080h, 003h, 000h, 004h, 080h, 004h, 000h, 004h, 080h, 005h, 000h, 004h, 080h
        db 006h, 000h, 004h, 080h, 007h, 000h, 004h, 080h, 008h, 000h, 004h, 080h, 009h, 000h, 004h, 080h
        db 0A0h, 000h, 000h, 000h
seg13_s7 ENDS

seg13_s8 SEGMENT BYTE PUBLIC ALIAS('WMADEC_RW') 'DATA'

; // match: _unk_3C445C @ 0x003C445C
PUBLIC _unk_3C445C
_unk_3C445C LABEL BYTE
        db 000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
        db 0FFh, 0FFh, 0FFh, 0FFh
seg13_s8 ENDS

        END
