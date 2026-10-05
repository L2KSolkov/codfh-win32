; codfh-match: Bink's plane decoder (the library's expand.obj): the bundle readers and the plane expander
; Seven bundle/table readers are restored in expand.c. simpmergesort, ReadHuffTable,
; CheckReadHuff4PairBundle, ExpandPlane and ExpandBink stay image transcriptions (their C did
; not match, or their callers depend on their register conventions; owner, 2026-10-04).

        .686p
        .model flat

EXTERN _CheckReadRLEHuff4Bundle:NEAR
EXTERN _CheckReadHuff8Bundle:NEAR
EXTERN _NewCheckReadHuff8Bundle:NEAR
EXTERN _CheckReadHuff4Bundle:NEAR
EXTERN _CheckReadHuff4SBundle:NEAR
EXTERN _CheckReadDelta16Bundle:NEAR

EXTERN _FastIDCT8x8@16:NEAR
EXTERN _StartReadHuff8Bundle:NEAR
EXTERN _decode_use_MMX:BYTE
EXTERN _FastIDCT8x8d@16:NEAR
EXTERN _FastmIDCT8x8WithMotion@20:NEAR
EXTERN _huff4reads:BYTE
EXTERN _mask2:BYTE
EXTERN _mask1:BYTE
EXTERN _mask4:BYTE
EXTERN _mask3:BYTE
EXTERN _huff4decodes:BYTE

EXTERN _patterns:BYTE
EXTERN _ReadBPLossless@8:NEAR
EXTERN _ReadBPLossyWithMotion@20:NEAR
EXTERN __bitlevels:BYTE

seg0 SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: _simpmergesort @ 0x00346170
_simpmergesort PROC PUBLIC
$L_346170:
        db 053h   ; push ebx
        db 08Bh, 05Ch, 024h, 008h   ; mov ebx, dword ptr [esp + 8]
        db 055h   ; push ebp
        db 08Bh, 06Ch, 024h, 010h   ; mov ebp, dword ptr [esp + 0x10]
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Bh, 0F2h   ; mov esi, edx
        db 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x14], 0
$L_346188:
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 040h   ; inc eax
        db 0F6h, 0C3h, 001h   ; test bl, 1
        db 089h, 044h, 024h, 014h   ; mov dword ptr [esp + 0x14], eax
        db 074h, 00Ah   ; je 0x3461a0
        db 08Ah, 045h, 000h   ; mov al, byte ptr [ebp]
        db 088h, 001h   ; mov byte ptr [ecx], al
        db 041h   ; inc ecx
        db 045h   ; inc ebp
        db 04Eh   ; dec esi
        db 0EBh, 007h   ; jmp 0x3461a7
$L_3461a0:
        db 08Ah, 007h   ; mov al, byte ptr [edi]
        db 088h, 001h   ; mov byte ptr [ecx], al
        db 041h   ; inc ecx
        db 047h   ; inc edi
        db 04Ah   ; dec edx
$L_3461a7:
        db 0D1h, 0EBh   ; shr ebx, 1
        db 085h, 0D2h   ; test edx, edx
        db 074h, 016h   ; je 0x3461c3
        db 085h, 0F6h   ; test esi, esi
        db 075h, 0D7h   ; jne 0x346188
$L_3461b1:
        db 08Ah, 007h   ; mov al, byte ptr [edi]
        db 088h, 001h   ; mov byte ptr [ecx], al
        db 041h   ; inc ecx
        db 047h   ; inc edi
        db 04Ah   ; dec edx
        db 075h, 0F7h   ; jne 0x3461b1
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
$L_3461c3:
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x3461d1
$L_3461c7:
        db 08Ah, 055h, 000h   ; mov dl, byte ptr [ebp]
        db 088h, 011h   ; mov byte ptr [ecx], dl
        db 041h   ; inc ecx
        db 045h   ; inc ebp
        db 04Eh   ; dec esi
        db 075h, 0F6h   ; jne 0x3461c7
$L_3461d1:
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
_simpmergesort ENDP

seg0 ENDS

segrh SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: _ReadHuffTable @ 0x003461E0
_ReadHuffTable PROC PUBLIC
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 083h, 0ECh, 020h   ; sub esp, 0x20
        db 053h   ; push ebx
        db 08Bh, 058h, 004h   ; mov ebx, dword ptr [eax + 4]
        db 055h   ; push ebp
        db 08Bh, 06Ch, 024h, 038h   ; mov ebp, dword ptr [esp + 0x38]
        db 056h   ; push esi
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 078h, 008h   ; mov edi, dword ptr [eax + 8]
        db 083h, 0FFh, 004h   ; cmp edi, 4
        db 072h, 00Dh   ; jb 0x346209
        db 08Bh, 0C6h   ; mov eax, esi
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 0C1h, 0EEh, 004h   ; shr esi, 4
        db 083h, 0EFh, 004h   ; sub edi, 4
        db 0EBh, 01Eh   ; jmp 0x346227
$L_346209:
        db 08Bh, 013h   ; mov edx, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0C2h   ; mov eax, edx
        db 0D3h, 0E0h   ; shl eax, cl
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0EAh   ; shr edx, cl
        db 00Bh, 0C6h   ; or eax, esi
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 083h, 0C7h, 01Ch   ; add edi, 0x1c
        db 08Bh, 0F2h   ; mov esi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_346227:
        db 085h, 0C0h   ; test eax, eax
        db 08Bh, 00Ch, 085h   ; mov ecx, dword ptr [eax*4 + 0x52f780]
        dd _huff4decodes
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 00Fh, 0B6h, 088h   ; movzx ecx, byte ptr [eax + 0x3eed38]
        dd _huff4reads
        db 08Bh, 054h, 024h, 03Ch   ; mov edx, dword ptr [esp + 0x3c]
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 075h, 01Dh   ; jne 0x346262
$L_346245:
        db 088h, 004h, 028h   ; mov byte ptr [eax + ebp], al
        db 040h   ; inc eax
        db 083h, 0F8h, 010h   ; cmp eax, 0x10
        db 072h, 0F7h   ; jb 0x346245
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
$L_346262:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 00Ah   ; je 0x346270
        db 08Bh, 0C6h   ; mov eax, esi
        db 083h, 0E0h, 001h   ; and eax, 1
        db 0D1h, 0EEh   ; shr esi, 1
        db 04Fh   ; dec edi
        db 0EBh, 011h   ; jmp 0x346281
$L_346270:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0F0h   ; mov esi, eax
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 0D1h, 0EEh   ; shr esi, 1
        db 0BFh, 01Fh, 000h, 000h, 000h   ; mov edi, 0x1f
        db 083h, 0E0h, 001h   ; and eax, 1
$L_346281:
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 085h, 01Bh, 005h, 000h, 000h   ; jne 0x3467a4
        db 083h, 0FFh, 002h   ; cmp edi, 2
        db 072h, 00Dh   ; jb 0x34629b
        db 08Bh, 0EEh   ; mov ebp, esi
        db 083h, 0E5h, 003h   ; and ebp, 3
        db 0C1h, 0EEh, 002h   ; shr esi, 2
        db 083h, 0EFh, 002h   ; sub edi, 2
        db 0EBh, 01Eh   ; jmp 0x3462b9
$L_34629b:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0E8h   ; mov ebp, eax
        db 0D3h, 0E5h   ; shl ebp, cl
        db 0B9h, 002h, 000h, 000h, 000h   ; mov ecx, 2
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0E8h   ; shr eax, cl
        db 00Bh, 0EEh   ; or ebp, esi
        db 083h, 0E5h, 003h   ; and ebp, 3
        db 083h, 0C7h, 01Eh   ; add edi, 0x1e
        db 08Bh, 0F0h   ; mov esi, eax
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_3462b9:
        db 033h, 0C9h   ; xor ecx, ecx
        db 085h, 0EDh   ; test ebp, ebp
        db 075h, 075h   ; jne 0x346334
        db 08Bh, 044h, 024h, 040h   ; mov eax, dword ptr [esp + 0x40]
        db 08Dh, 050h, 001h   ; lea edx, [eax + 1]
        db 02Bh, 0C2h   ; sub eax, edx
        db 089h, 054h, 024h, 03Ch   ; mov dword ptr [esp + 0x3c], edx
        db 089h, 044h, 024h, 038h   ; mov dword ptr [esp + 0x38], eax
$L_3462d0:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 00Ah   ; je 0x3462de
        db 08Bh, 0C6h   ; mov eax, esi
        db 083h, 0E0h, 001h   ; and eax, 1
        db 0D1h, 0EEh   ; shr esi, 1
        db 04Fh   ; dec edi
        db 0EBh, 011h   ; jmp 0x3462ef
$L_3462de:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0F0h   ; mov esi, eax
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 0D1h, 0EEh   ; shr esi, 1
        db 0BFh, 01Fh, 000h, 000h, 000h   ; mov edi, 0x1f
        db 083h, 0E0h, 001h   ; and eax, 1
$L_3462ef:
        db 085h, 0C0h   ; test eax, eax
        db 08Dh, 02Ch, 00Ah   ; lea ebp, [edx + ecx]
        db 074h, 014h   ; je 0x34630a
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        db 08Ah, 0C1h   ; mov al, cl
        db 0FEh, 0C0h   ; inc al
        db 088h, 004h, 02Ah   ; mov byte ptr [edx + ebp], al
        db 08Bh, 054h, 024h, 03Ch   ; mov edx, dword ptr [esp + 0x3c]
        db 088h, 04Dh, 000h   ; mov byte ptr [ebp], cl
        db 0EBh, 00Eh   ; jmp 0x346318
$L_34630a:
        db 08Bh, 044h, 024h, 038h   ; mov eax, dword ptr [esp + 0x38]
        db 088h, 00Ch, 028h   ; mov byte ptr [eax + ebp], cl
        db 08Ah, 0C1h   ; mov al, cl
        db 0FEh, 0C0h   ; inc al
        db 088h, 045h, 000h   ; mov byte ptr [ebp], al
$L_346318:
        db 083h, 0C1h, 002h   ; add ecx, 2
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 072h, 0B0h   ; jb 0x3462d0
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
$L_346334:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 00Ah   ; je 0x346342
        db 08Bh, 0C6h   ; mov eax, esi
        db 083h, 0E0h, 001h   ; and eax, 1
        db 0D1h, 0EEh   ; shr esi, 1
        db 04Fh   ; dec edi
        db 0EBh, 011h   ; jmp 0x346353
$L_346342:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0F0h   ; mov esi, eax
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 0D1h, 0EEh   ; shr esi, 1
        db 0BFh, 01Fh, 000h, 000h, 000h   ; mov edi, 0x1f
        db 083h, 0E0h, 001h   ; and eax, 1
$L_346353:
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Eh   ; je 0x346365
        db 08Ah, 0D1h   ; mov dl, cl
        db 0FEh, 0C2h   ; inc dl
        db 088h, 054h, 00Ch, 010h   ; mov byte ptr [esp + ecx + 0x10], dl
        db 088h, 04Ch, 00Ch, 011h   ; mov byte ptr [esp + ecx + 0x11], cl
        db 0EBh, 00Ch   ; jmp 0x346371
$L_346365:
        db 08Ah, 0C1h   ; mov al, cl
        db 0FEh, 0C0h   ; inc al
        db 088h, 04Ch, 00Ch, 010h   ; mov byte ptr [esp + ecx + 0x10], cl
        db 088h, 044h, 00Ch, 011h   ; mov byte ptr [esp + ecx + 0x11], al
$L_346371:
        db 083h, 0C1h, 002h   ; add ecx, 2
        db 083h, 0F9h, 010h   ; cmp ecx, 0x10
        db 072h, 0BBh   ; jb 0x346334
        db 083h, 0FDh, 001h   ; cmp ebp, 1
        db 00Fh, 085h, 037h, 001h, 000h, 000h   ; jne 0x3464b9
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x34638b
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x346393
$L_34638b:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_346393:
        db 08Bh, 06Ch, 024h, 040h   ; mov ebp, dword ptr [esp + 0x40]
        db 08Dh, 04Ch, 024h, 012h   ; lea ecx, [esp + 0x12]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 018h   ; lea eax, [esp + 0x18]
        db 08Bh, 0CDh   ; mov ecx, ebp
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x3463bf
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x3463d1
$L_3463bf:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_3463d1:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x3463da
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x3463e2
$L_3463da:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_3463e2:
        db 08Dh, 04Ch, 024h, 016h   ; lea ecx, [esp + 0x16]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 08Dh, 04Dh, 004h   ; lea ecx, [ebp + 4]
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 01Ch   ; lea eax, [esp + 0x1c]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x34640b
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x34641d
$L_34640b:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_34641d:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x346426
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x34642e
$L_346426:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_34642e:
        db 08Dh, 04Ch, 024h, 01Ah   ; lea ecx, [esp + 0x1a]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 020h   ; lea eax, [esp + 0x20]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x346457
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x346469
$L_346457:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_346469:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x346472
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x34647a
$L_346472:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_34647a:
        db 08Dh, 04Ch, 024h, 01Eh   ; lea ecx, [esp + 0x1e]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 08Dh, 04Dh, 00Ch   ; lea ecx, [ebp + 0xc]
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 024h   ; lea eax, [esp + 0x24]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 00Fh, 082h, 0DDh, 002h, 000h, 000h   ; jb 0x34677e
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
$L_3464b9:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x3464c2
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x3464ca
$L_3464c2:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_3464ca:
        db 08Dh, 04Ch, 024h, 012h   ; lea ecx, [esp + 0x12]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 018h   ; lea eax, [esp + 0x18]
        db 08Dh, 04Ch, 024h, 028h   ; lea ecx, [esp + 0x28]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x3464f4
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x346506
$L_3464f4:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_346506:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x34650f
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x346517
$L_34650f:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_346517:
        db 08Dh, 04Ch, 024h, 016h   ; lea ecx, [esp + 0x16]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 01Ch   ; lea eax, [esp + 0x1c]
        db 08Dh, 04Ch, 024h, 02Ch   ; lea ecx, [esp + 0x2c]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x346541
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x346553
$L_346541:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_346553:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x34655c
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x346564
$L_34655c:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_346564:
        db 08Dh, 04Ch, 024h, 01Ah   ; lea ecx, [esp + 0x1a]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 020h   ; lea eax, [esp + 0x20]
        db 08Dh, 04Ch, 024h, 030h   ; lea ecx, [esp + 0x30]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x34658e
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x3465a0
$L_34658e:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_3465a0:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 004h   ; jb 0x3465a9
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x3465b1
$L_3465a9:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_3465b1:
        db 08Dh, 04Ch, 024h, 01Eh   ; lea ecx, [esp + 0x1e]
        db 083h, 0E0h, 007h   ; and eax, 7
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 002h, 000h, 000h, 000h   ; mov edx, 2
        db 08Dh, 044h, 024h, 024h   ; lea eax, [esp + 0x24]
        db 08Dh, 04Ch, 024h, 034h   ; lea ecx, [esp + 0x34]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x3465db
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x3465ed
$L_3465db:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_3465ed:
        db 083h, 0FDh, 002h   ; cmp ebp, 2
        db 00Fh, 085h, 09Fh, 000h, 000h, 000h   ; jne 0x346695
        db 083h, 0FFh, 007h   ; cmp edi, 7
        db 072h, 004h   ; jb 0x3465ff
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x346607
$L_3465ff:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_346607:
        db 08Bh, 06Ch, 024h, 040h   ; mov ebp, dword ptr [esp + 0x40]
        db 08Dh, 04Ch, 024h, 024h   ; lea ecx, [esp + 0x24]
        db 083h, 0E0h, 07Fh   ; and eax, 0x7f
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 004h, 000h, 000h, 000h   ; mov edx, 4
        db 08Dh, 044h, 024h, 028h   ; lea eax, [esp + 0x28]
        db 08Bh, 0CDh   ; mov ecx, ebp
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x346633
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x346645
$L_346633:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_346645:
        db 083h, 0FFh, 007h   ; cmp edi, 7
        db 072h, 004h   ; jb 0x34664e
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x346656
$L_34664e:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_346656:
        db 08Dh, 04Ch, 024h, 02Ch   ; lea ecx, [esp + 0x2c]
        db 083h, 0E0h, 07Fh   ; and eax, 0x7f
        db 051h   ; push ecx
        db 050h   ; push eax
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 0BAh, 004h, 000h, 000h, 000h   ; mov edx, 4
        db 08Dh, 044h, 024h, 030h   ; lea eax, [esp + 0x30]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 00Fh, 082h, 001h, 001h, 000h, 000h   ; jb 0x34677e
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
$L_346695:
        db 083h, 0FFh, 007h   ; cmp edi, 7
        db 072h, 004h   ; jb 0x34669e
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x3466a6
$L_34669e:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_3466a6:
        db 08Dh, 04Ch, 024h, 024h   ; lea ecx, [esp + 0x24]
        db 083h, 0E0h, 07Fh   ; and eax, 0x7f
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 004h, 000h, 000h, 000h   ; mov edx, 4
        db 08Dh, 044h, 024h, 028h   ; lea eax, [esp + 0x28]
        db 08Dh, 04Ch, 024h, 018h   ; lea ecx, [esp + 0x18]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x3466d0
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x3466e2
$L_3466d0:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_3466e2:
        db 083h, 0FFh, 007h   ; cmp edi, 7
        db 072h, 004h   ; jb 0x3466eb
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x3466f3
$L_3466eb:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_3466f3:
        db 08Dh, 04Ch, 024h, 02Ch   ; lea ecx, [esp + 0x2c]
        db 083h, 0E0h, 07Fh   ; and eax, 0x7f
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0BAh, 004h, 000h, 000h, 000h   ; mov edx, 4
        db 08Dh, 044h, 024h, 030h   ; lea eax, [esp + 0x30]
        db 08Dh, 04Ch, 024h, 020h   ; lea ecx, [esp + 0x20]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 006h   ; jb 0x34671d
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 0EBh, 012h   ; jmp 0x34672f
$L_34671d:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_34672f:
        db 083h, 0FFh, 00Fh   ; cmp edi, 0xf
        db 072h, 004h   ; jb 0x346738
        db 08Bh, 0C6h   ; mov eax, esi
        db 0EBh, 008h   ; jmp 0x346740
$L_346738:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 0C6h   ; or eax, esi
$L_346740:
        db 08Dh, 04Ch, 024h, 018h   ; lea ecx, [esp + 0x18]
        db 025h, 0FFh, 07Fh, 000h, 000h   ; and eax, 0x7fff
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 044h   ; mov ecx, dword ptr [esp + 0x44]
        db 050h   ; push eax
        db 0BAh, 008h, 000h, 000h, 000h   ; mov edx, 8
        db 08Dh, 044h, 024h, 018h   ; lea eax, [esp + 0x18]
        call _simpmergesort   ; 0x346170
        db 083h, 0C4h, 008h   ; add esp, 8
        db 03Bh, 0F8h   ; cmp edi, eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 072h, 018h   ; jb 0x34677e
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0F8h   ; sub edi, eax
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
$L_34677e:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 02Bh, 0D0h   ; sub edx, eax
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 0D3h, 0EEh   ; shr esi, cl
        db 003h, 0FAh   ; add edi, edx
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
$L_3467a4:
        db 083h, 0FFh, 003h   ; cmp edi, 3
        db 072h, 00Dh   ; jb 0x3467b6
        db 08Bh, 0EEh   ; mov ebp, esi
        db 083h, 0E5h, 007h   ; and ebp, 7
        db 0C1h, 0EEh, 003h   ; shr esi, 3
        db 083h, 0EFh, 003h   ; sub edi, 3
        db 0EBh, 01Eh   ; jmp 0x3467d4
$L_3467b6:
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0E8h   ; mov ebp, eax
        db 0D3h, 0E5h   ; shl ebp, cl
        db 0B9h, 003h, 000h, 000h, 000h   ; mov ecx, 3
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0E8h   ; shr eax, cl
        db 00Bh, 0EEh   ; or ebp, esi
        db 083h, 0E5h, 007h   ; and ebp, 7
        db 083h, 0C7h, 01Dh   ; add edi, 0x1d
        db 08Bh, 0F0h   ; mov esi, eax
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_3467d4:
        db 0C7h, 044h, 024h, 038h, 0FFh, 0FFh, 000h, 000h   ; mov dword ptr [esp + 0x38], 0xffff
        db 0C7h, 044h, 024h, 03Ch, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x3c], 0
$L_3467e4:
        db 083h, 0FFh, 004h   ; cmp edi, 4
        db 072h, 00Dh   ; jb 0x3467f6
        db 08Bh, 0C6h   ; mov eax, esi
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 0C1h, 0EEh, 004h   ; shr esi, 4
        db 083h, 0EFh, 004h   ; sub edi, 4
        db 0EBh, 01Eh   ; jmp 0x346814
$L_3467f6:
        db 08Bh, 013h   ; mov edx, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0C2h   ; mov eax, edx
        db 0D3h, 0E0h   ; shl eax, cl
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0EAh   ; shr edx, cl
        db 00Bh, 0C6h   ; or eax, esi
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 083h, 0C7h, 01Ch   ; add edi, 0x1c
        db 08Bh, 0F2h   ; mov esi, edx
        db 083h, 0C3h, 004h   ; add ebx, 4
$L_346814:
        db 08Bh, 0C8h   ; mov ecx, eax
        db 0BAh, 001h, 000h, 000h, 000h   ; mov edx, 1
        db 0D3h, 0E2h   ; shl edx, cl
        db 08Bh, 04Ch, 024h, 038h   ; mov ecx, dword ptr [esp + 0x38]
        db 0F7h, 0D2h   ; not edx
        db 023h, 0CAh   ; and ecx, edx
        db 08Bh, 054h, 024h, 040h   ; mov edx, dword ptr [esp + 0x40]
        db 089h, 04Ch, 024h, 038h   ; mov dword ptr [esp + 0x38], ecx
        db 08Bh, 04Ch, 024h, 03Ch   ; mov ecx, dword ptr [esp + 0x3c]
        db 088h, 004h, 011h   ; mov byte ptr [ecx + edx], al
        db 041h   ; inc ecx
        db 03Bh, 0CDh   ; cmp ecx, ebp
        db 089h, 04Ch, 024h, 03Ch   ; mov dword ptr [esp + 0x3c], ecx
        db 076h, 0A7h   ; jbe 0x3467e4
        db 08Bh, 04Ch, 024h, 038h   ; mov ecx, dword ptr [esp + 0x38]
        db 033h, 0C0h   ; xor eax, eax
        db 003h, 0EAh   ; add ebp, edx
$L_346845:
        db 0F6h, 0C1h, 001h   ; test cl, 1
        db 074h, 004h   ; je 0x34684e
        db 045h   ; inc ebp
        db 088h, 045h, 000h   ; mov byte ptr [ebp], al
$L_34684e:
        db 0D1h, 0E9h   ; shr ecx, 1
        db 040h   ; inc eax
        db 085h, 0C9h   ; test ecx, ecx
        db 075h, 0F0h   ; jne 0x346845
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
        db 05Fh   ; pop edi
        db 089h, 030h   ; mov dword ptr [eax], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
_ReadHuffTable ENDP
segrh ENDS

seg1 SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'





; // match: _CheckReadHuff4PairBundle @ 0x00347300
_CheckReadHuff4PairBundle PROC PUBLIC
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 04Fh, 004h   ; mov ecx, dword ptr [edi + 4]
        db 083h, 0ECh, 01Ch   ; sub esp, 0x1c
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 00Fh, 085h, 0EBh, 001h, 000h, 000h   ; jne 0x3474fb
        db 08Bh, 057h, 028h   ; mov edx, dword ptr [edi + 0x28]
        db 053h   ; push ebx
        db 08Bh, 05Ch, 024h, 024h   ; mov ebx, dword ptr [esp + 0x24]
        db 08Bh, 043h, 008h   ; mov eax, dword ptr [ebx + 8]
        db 08Bh, 04Bh, 004h   ; mov ecx, dword ptr [ebx + 4]
        db 055h   ; push ebp
        db 083h, 0CDh, 0FFh   ; or ebp, 0xffffffff
        db 03Bh, 0C2h   ; cmp eax, edx
        db 056h   ; push esi
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 089h, 04Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], ecx
        db 072h, 013h   ; jb 0x347340
        db 0B9h, 020h, 000h, 000h, 000h   ; mov ecx, 0x20
        db 02Bh, 0CAh   ; sub ecx, edx
        db 0D3h, 0EDh   ; shr ebp, cl
        db 08Bh, 0CAh   ; mov ecx, edx
        db 023h, 0EEh   ; and ebp, esi
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0C2h   ; sub eax, edx
        db 0EBh, 045h   ; jmp 0x347385
$L_347340:
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 0B9h, 020h, 000h, 000h, 000h   ; mov ecx, 0x20
        db 02Bh, 0CAh   ; sub ecx, edx
        db 0D3h, 0EDh   ; shr ebp, cl
        db 08Bh, 0C8h   ; mov ecx, eax
        db 089h, 06Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ebp
        db 08Bh, 0EBh   ; mov ebp, ebx
        db 0D3h, 0E5h   ; shl ebp, cl
        db 08Bh, 04Ch, 024h, 020h   ; mov ecx, dword ptr [esp + 0x20]
        db 00Bh, 0EEh   ; or ebp, esi
        db 023h, 0CDh   ; and ecx, ebp
        db 089h, 04Ch, 024h, 018h   ; mov dword ptr [esp + 0x18], ecx
        db 08Bh, 06Ch, 024h, 018h   ; mov ebp, dword ptr [esp + 0x18]
        db 08Bh, 0CAh   ; mov ecx, edx
        db 02Bh, 0C8h   ; sub ecx, eax
        db 0D3h, 0EBh   ; shr ebx, cl
        db 0B9h, 020h, 000h, 000h, 000h   ; mov ecx, 0x20
        db 02Bh, 0CAh   ; sub ecx, edx
        db 003h, 0C1h   ; add eax, ecx
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 083h, 0C1h, 004h   ; add ecx, 4
        db 08Bh, 0F3h   ; mov esi, ebx
        db 08Bh, 05Ch, 024h, 02Ch   ; mov ebx, dword ptr [esp + 0x2c]
        db 089h, 04Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], ecx
$L_347385:
        db 085h, 0EDh   ; test ebp, ebp
        db 08Bh, 04Fh, 02Ch   ; mov ecx, dword ptr [edi + 0x2c]
        db 00Fh, 084h, 054h, 001h, 000h, 000h   ; je 0x3474e4
        db 08Dh, 014h, 029h   ; lea edx, [ecx + ebp]
        db 089h, 00Fh   ; mov dword ptr [edi], ecx
        db 089h, 04Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ecx
        db 08Bh, 04Fh, 024h   ; mov ecx, dword ptr [edi + 0x24]
        db 089h, 04Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], ecx
        db 089h, 057h, 004h   ; mov dword ptr [edi + 4], edx
        db 08Bh, 057h, 020h   ; mov edx, dword ptr [edi + 0x20]
        db 0B9h, 020h, 000h, 000h, 000h   ; mov ecx, 0x20
        db 02Bh, 0CAh   ; sub ecx, edx
        db 083h, 0CBh, 0FFh   ; or ebx, 0xffffffff
        db 0D3h, 0EBh   ; shr ebx, cl
        db 089h, 054h, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], edx
        db 089h, 05Ch, 024h, 024h   ; mov dword ptr [esp + 0x24], ebx
        db 0EBh, 00Ch   ; jmp 0x3473c8
$L_3473bc:
        db 08Bh, 06Ch, 024h, 018h   ; mov ebp, dword ptr [esp + 0x18]
        db 08Bh, 05Ch, 024h, 024h   ; mov ebx, dword ptr [esp + 0x24]
        db 08Bh, 054h, 024h, 01Ch   ; mov edx, dword ptr [esp + 0x1c]
$L_3473c8:
        db 04Dh   ; dec ebp
        db 03Bh, 0C2h   ; cmp eax, edx
        db 089h, 06Ch, 024h, 018h   ; mov dword ptr [esp + 0x18], ebp
        db 072h, 022h   ; jb 0x3473f3
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 023h, 0D6h   ; and edx, esi
        db 00Fh, 0B6h, 00Ch, 00Ah   ; movzx ecx, byte ptr [edx + ecx]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 08Ah, 054h, 03Ah, 010h   ; mov dl, byte ptr [edx + edi + 0x10]
        db 0C1h, 0E9h, 004h   ; shr ecx, 4
        db 0D3h, 0EEh   ; shr esi, cl
        db 088h, 054h, 024h, 00Fh   ; mov byte ptr [esp + 0xf], dl
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0EBh, 04Eh   ; jmp 0x347441
$L_3473f3:
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 08Bh, 029h   ; mov ebp, dword ptr [ecx]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 08Bh, 0D5h   ; mov edx, ebp
        db 0D3h, 0E2h   ; shl edx, cl
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 00Bh, 0D6h   ; or edx, esi
        db 023h, 0D3h   ; and edx, ebx
        db 00Fh, 0B6h, 014h, 00Ah   ; movzx edx, byte ptr [edx + ecx]
        db 08Bh, 0CAh   ; mov ecx, edx
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 08Ah, 04Ch, 039h, 010h   ; mov cl, byte ptr [ecx + edi + 0x10]
        db 0C1h, 0EAh, 004h   ; shr edx, 4
        db 03Bh, 0C2h   ; cmp eax, edx
        db 088h, 04Ch, 024h, 00Fh   ; mov byte ptr [esp + 0xf], cl
        db 08Bh, 0CAh   ; mov ecx, edx
        db 072h, 006h   ; jb 0x347427
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0C2h   ; sub eax, edx
        db 0EBh, 01Ah   ; jmp 0x347441
$L_347427:
        db 02Bh, 0C8h   ; sub ecx, eax
        db 0D3h, 0EDh   ; shr ebp, cl
        db 0B9h, 020h, 000h, 000h, 000h   ; mov ecx, 0x20
        db 02Bh, 0CAh   ; sub ecx, edx
        db 003h, 0C1h   ; add eax, ecx
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 083h, 0C1h, 004h   ; add ecx, 4
        db 08Bh, 0F5h   ; mov esi, ebp
        db 089h, 04Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], ecx
$L_347441:
        db 03Bh, 044h, 024h, 01Ch   ; cmp eax, dword ptr [esp + 0x1c]
        db 072h, 01Ch   ; jb 0x347463
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 023h, 0DEh   ; and ebx, esi
        db 00Fh, 0B6h, 00Ch, 013h   ; movzx ecx, byte ptr [ebx + edx]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E9h, 004h   ; shr ecx, 4
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 08Ah, 05Ch, 03Ah, 010h   ; mov bl, byte ptr [edx + edi + 0x10]
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0EBh, 04Ah   ; jmp 0x3474ad
$L_347463:
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 08Bh, 029h   ; mov ebp, dword ptr [ecx]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 08Bh, 0D5h   ; mov edx, ebp
        db 0D3h, 0E2h   ; shl edx, cl
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 00Bh, 0D6h   ; or edx, esi
        db 023h, 0D3h   ; and edx, ebx
        db 00Fh, 0B6h, 014h, 00Ah   ; movzx edx, byte ptr [edx + ecx]
        db 08Bh, 0CAh   ; mov ecx, edx
        db 083h, 0E1h, 00Fh   ; and ecx, 0xf
        db 08Ah, 05Ch, 039h, 010h   ; mov bl, byte ptr [ecx + edi + 0x10]
        db 0C1h, 0EAh, 004h   ; shr edx, 4
        db 03Bh, 0C2h   ; cmp eax, edx
        db 08Bh, 0CAh   ; mov ecx, edx
        db 072h, 006h   ; jb 0x347493
        db 0D3h, 0EEh   ; shr esi, cl
        db 02Bh, 0C2h   ; sub eax, edx
        db 0EBh, 01Ah   ; jmp 0x3474ad
$L_347493:
        db 02Bh, 0C8h   ; sub ecx, eax
        db 0D3h, 0EDh   ; shr ebp, cl
        db 0B9h, 020h, 000h, 000h, 000h   ; mov ecx, 0x20
        db 02Bh, 0CAh   ; sub ecx, edx
        db 003h, 0C1h   ; add eax, ecx
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 083h, 0C1h, 004h   ; add ecx, 4
        db 08Bh, 0F5h   ; mov esi, ebp
        db 089h, 04Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], ecx
$L_3474ad:
        db 08Ah, 04Ch, 024h, 00Fh   ; mov cl, byte ptr [esp + 0xf]
        db 0C0h, 0E3h, 004h   ; shl bl, 4
        db 00Ah, 0D9h   ; or bl, cl
        db 08Bh, 04Ch, 024h, 020h   ; mov ecx, dword ptr [esp + 0x20]
        db 088h, 019h   ; mov byte ptr [ecx], bl
        db 041h   ; inc ecx
        db 089h, 04Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ecx
        db 08Bh, 04Ch, 024h, 018h   ; mov ecx, dword ptr [esp + 0x18]
        db 085h, 0C9h   ; test ecx, ecx
        db 00Fh, 085h, 0EFh, 0FEh, 0FFh, 0FFh   ; jne 0x3473bc
        db 08Bh, 05Ch, 024h, 02Ch   ; mov ebx, dword ptr [esp + 0x2c]
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 089h, 033h   ; mov dword ptr [ebx], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 04Bh, 004h   ; mov dword ptr [ebx + 4], ecx
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
        db 05Bh   ; pop ebx
        db 083h, 0C4h, 01Ch   ; add esp, 0x1c
        db 0C3h   ; ret 
$L_3474e4:
        db 08Dh, 051h, 004h   ; lea edx, [ecx + 4]
        db 089h, 04Fh, 004h   ; mov dword ptr [edi + 4], ecx
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 089h, 017h   ; mov dword ptr [edi], edx
        db 089h, 033h   ; mov dword ptr [ebx], esi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 089h, 04Bh, 004h   ; mov dword ptr [ebx + 4], ecx
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
        db 05Bh   ; pop ebx
$L_3474fb:
        db 083h, 0C4h, 01Ch   ; add esp, 0x1c
        db 0C3h   ; ret 
        db 0CCh   ; int3 
_CheckReadHuff4PairBundle ENDP


seg1 ENDS

segep SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: _ExpandPlane @ 0x00347B40
_ExpandPlane PROC PUBLIC
$L_347b40:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 081h, 0ECh, 034h, 004h, 000h, 000h   ; sub esp, 0x434
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 018h   ; mov esi, dword ptr [ebp + 0x18]
        db 057h   ; push edi
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Dh, 004h, 0F5h, 000h, 000h, 000h, 000h   ; lea eax, [esi*8]
        db 02Bh, 0C1h   ; sub eax, ecx
        db 089h, 085h, 064h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x9c], eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 089h, 045h, 0E4h   ; mov dword ptr [ebp - 0x1c], eax
        db 089h, 055h, 0ECh   ; mov dword ptr [ebp - 0x14], edx
        db 033h, 0D2h   ; xor edx, edx
        db 0B8h, 010h, 000h, 000h, 000h   ; mov eax, 0x10
        db 0F7h, 075h, 01Ch   ; div dword ptr [ebp + 0x1c]
        db 033h, 0D2h   ; xor edx, edx
        db 0C7h, 045h, 0E8h, 000h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x18], 0
        db 089h, 07Dh, 0FCh   ; mov dword ptr [ebp - 4], edi
        db 089h, 07Dh, 0F4h   ; mov dword ptr [ebp - 0xc], edi
        db 0C7h, 085h, 068h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x98], 0x346b60
        dd _CheckReadHuff8Bundle
        db 08Bh, 0D8h   ; mov ebx, eax
        db 08Bh, 0C6h   ; mov eax, esi
        db 0F7h, 0F3h   ; div ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 089h, 05Dh, 0F8h   ; mov dword ptr [ebp - 8], ebx
        db 089h, 05Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ebx
        db 089h, 05Dh, 0D4h   ; mov dword ptr [ebp - 0x2c], ebx
        db 089h, 085h, 060h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xa0], eax
        db 08Bh, 045h, 024h   ; mov eax, dword ptr [ebp + 0x24]
        db 084h, 0E4h   ; test ah, ah
        db 078h, 00Ah   ; js 0x347bbd
        db 0C7h, 085h, 068h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x98], 0x346e30
        dd _NewCheckReadHuff8Bundle
$L_347bbd:
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0C1h, 0EFh, 003h   ; shr edi, 3
        db 08Dh, 087h, 0FFh, 001h, 000h, 000h   ; lea eax, [edi + 0x1ff]
        db 03Dh, 080h, 000h, 000h, 000h   ; cmp eax, 0x80
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 077h, 009h   ; ja 0x347be0
        db 00Fh, 0B6h, 0BFh   ; movzx edi, byte ptr [edi + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 043h   ; jmp 0x347c23
$L_347be0:
        db 03Dh, 000h, 008h, 000h, 000h   ; cmp eax, 0x800
        db 072h, 01Fh   ; jb 0x347c06
        db 03Dh, 000h, 020h, 000h, 000h   ; cmp eax, 0x2000
        db 072h, 00Ch   ; jb 0x347bfa
        db 03Dh, 000h, 040h, 000h, 000h   ; cmp eax, 0x4000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Fh   ; add edi, 0xf
        db 0EBh, 029h   ; jmp 0x347c23
$L_347bfa:
        db 03Dh, 000h, 010h, 000h, 000h   ; cmp eax, 0x1000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Dh   ; add edi, 0xd
        db 0EBh, 01Dh   ; jmp 0x347c23
$L_347c06:
        db 03Dh, 000h, 002h, 000h, 000h   ; cmp eax, 0x200
        db 072h, 00Ch   ; jb 0x347c19
        db 03Dh, 000h, 004h, 000h, 000h   ; cmp eax, 0x400
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Bh   ; add edi, 0xb
        db 0EBh, 00Ah   ; jmp 0x347c23
$L_347c19:
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 009h   ; add edi, 9
$L_347c23:
        db 089h, 095h, 08Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x174], edx
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 0D1h, 0E9h   ; shr ecx, 1
        db 0C1h, 0E9h, 003h   ; shr ecx, 3
        db 089h, 0BDh, 088h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x178], edi
        db 08Bh, 07Ah, 004h   ; mov edi, dword ptr [edx + 4]
        db 08Dh, 091h, 0FFh, 001h, 000h, 000h   ; lea edx, [ecx + 0x1ff]
        db 081h, 0FAh, 080h, 000h, 000h, 000h   ; cmp edx, 0x80
        db 089h, 09Dh, 060h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1a0], ebx
        db 089h, 09Dh, 064h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x19c], ebx
        db 0C7h, 085h, 068h, 0FEh, 0FFh, 0FFh, 004h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x198], 4
        db 089h, 09Dh, 06Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x194], ebx
        db 077h, 009h   ; ja 0x347c6d
        db 00Fh, 0B6h, 089h   ; movzx ecx, byte ptr [ecx + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 056h   ; jmp 0x347cc3
$L_347c6d:
        db 081h, 0FAh, 000h, 008h, 000h, 000h   ; cmp edx, 0x800
        db 072h, 028h   ; jb 0x347c9d
        db 081h, 0FAh, 000h, 020h, 000h, 000h   ; cmp edx, 0x2000
        db 072h, 013h   ; jb 0x347c90
        db 081h, 0FAh, 000h, 040h, 000h, 000h   ; cmp edx, 0x4000
        db 01Bh, 0D2h   ; sbb edx, edx
        db 083h, 0C2h, 00Fh   ; add edx, 0xf
        db 089h, 095h, 058h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1a8], edx
        db 0EBh, 039h   ; jmp 0x347cc9
$L_347c90:
        db 081h, 0FAh, 000h, 010h, 000h, 000h   ; cmp edx, 0x1000
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 00Dh   ; add ecx, 0xd
        db 0EBh, 026h   ; jmp 0x347cc3
$L_347c9d:
        db 081h, 0FAh, 000h, 002h, 000h, 000h   ; cmp edx, 0x200
        db 072h, 013h   ; jb 0x347cb8
        db 081h, 0FAh, 000h, 004h, 000h, 000h   ; cmp edx, 0x400
        db 01Bh, 0D2h   ; sbb edx, edx
        db 083h, 0C2h, 00Bh   ; add edx, 0xb
        db 089h, 095h, 058h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1a8], edx
        db 0EBh, 011h   ; jmp 0x347cc9
$L_347cb8:
        db 081h, 0FAh, 000h, 001h, 000h, 000h   ; cmp edx, 0x100
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 009h   ; add ecx, 9
$L_347cc3:
        db 089h, 08Dh, 058h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1a8], ecx
$L_347cc9:
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 0C1h, 0E1h, 006h   ; shl ecx, 6
        db 089h, 0BDh, 05Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1a4], edi
        db 08Bh, 07Ah, 008h   ; mov edi, dword ptr [edx + 8]
        db 08Dh, 091h, 0FFh, 001h, 000h, 000h   ; lea edx, [ecx + 0x1ff]
        db 081h, 0FAh, 080h, 000h, 000h, 000h   ; cmp edx, 0x80
        db 089h, 09Dh, 030h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1d0], ebx
        db 089h, 09Dh, 034h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1cc], ebx
        db 0C7h, 085h, 038h, 0FEh, 0FFh, 0FFh, 004h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x1c8], 4
        db 089h, 09Dh, 03Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1c4], ebx
        db 077h, 009h   ; ja 0x347d0e
        db 00Fh, 0B6h, 089h   ; movzx ecx, byte ptr [ecx + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 050h   ; jmp 0x347d5e
$L_347d0e:
        db 081h, 0FAh, 000h, 008h, 000h, 000h   ; cmp edx, 0x800
        db 072h, 025h   ; jb 0x347d3b
        db 081h, 0FAh, 000h, 020h, 000h, 000h   ; cmp edx, 0x2000
        db 072h, 010h   ; jb 0x347d2e
        db 081h, 0FAh, 000h, 040h, 000h, 000h   ; cmp edx, 0x4000
        db 01Bh, 0D2h   ; sbb edx, edx
        db 083h, 0C2h, 00Fh   ; add edx, 0xf
        db 089h, 055h, 0CCh   ; mov dword ptr [ebp - 0x34], edx
        db 0EBh, 033h   ; jmp 0x347d61
$L_347d2e:
        db 081h, 0FAh, 000h, 010h, 000h, 000h   ; cmp edx, 0x1000
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 00Dh   ; add ecx, 0xd
        db 0EBh, 023h   ; jmp 0x347d5e
$L_347d3b:
        db 081h, 0FAh, 000h, 002h, 000h, 000h   ; cmp edx, 0x200
        db 072h, 010h   ; jb 0x347d53
        db 081h, 0FAh, 000h, 004h, 000h, 000h   ; cmp edx, 0x400
        db 01Bh, 0D2h   ; sbb edx, edx
        db 083h, 0C2h, 00Bh   ; add edx, 0xb
        db 089h, 055h, 0CCh   ; mov dword ptr [ebp - 0x34], edx
        db 0EBh, 00Eh   ; jmp 0x347d61
$L_347d53:
        db 081h, 0FAh, 000h, 001h, 000h, 000h   ; cmp edx, 0x100
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 009h   ; add ecx, 9
$L_347d5e:
        db 089h, 04Dh, 0CCh   ; mov dword ptr [ebp - 0x34], ecx
$L_347d61:
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 08Bh, 052h, 00Ch   ; mov edx, dword ptr [edx + 0xc]
        db 08Dh, 00Ch, 0CDh, 0FFh, 001h, 000h, 000h   ; lea ecx, [ecx*8 + 0x1ff]
        db 081h, 0F9h, 080h, 000h, 000h, 000h   ; cmp ecx, 0x80
        db 089h, 05Dh, 0A4h   ; mov dword ptr [ebp - 0x5c], ebx
        db 089h, 05Dh, 0A8h   ; mov dword ptr [ebp - 0x58], ebx
        db 0C7h, 045h, 0ACh, 008h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x54], 8
        db 089h, 05Dh, 0B0h   ; mov dword ptr [ebp - 0x50], ebx
        db 089h, 07Dh, 0D0h   ; mov dword ptr [ebp - 0x30], edi
        db 077h, 00Dh   ; ja 0x347d99
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 00Fh, 0B6h, 00Ch, 0CDh   ; movzx ecx, byte ptr [ecx*8 + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 04Ah   ; jmp 0x347de3
$L_347d99:
        db 081h, 0F9h, 000h, 008h, 000h, 000h   ; cmp ecx, 0x800
        db 072h, 022h   ; jb 0x347dc3
        db 081h, 0F9h, 000h, 020h, 000h, 000h   ; cmp ecx, 0x2000
        db 072h, 00Dh   ; jb 0x347db6
        db 081h, 0F9h, 000h, 040h, 000h, 000h   ; cmp ecx, 0x4000
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 00Fh   ; add ecx, 0xf
        db 0EBh, 02Dh   ; jmp 0x347de3
$L_347db6:
        db 081h, 0F9h, 000h, 010h, 000h, 000h   ; cmp ecx, 0x1000
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 00Dh   ; add ecx, 0xd
        db 0EBh, 020h   ; jmp 0x347de3
$L_347dc3:
        db 081h, 0F9h, 000h, 002h, 000h, 000h   ; cmp ecx, 0x200
        db 072h, 00Dh   ; jb 0x347dd8
        db 081h, 0F9h, 000h, 004h, 000h, 000h   ; cmp ecx, 0x400
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 00Bh   ; add ecx, 0xb
        db 0EBh, 00Bh   ; jmp 0x347de3
$L_347dd8:
        db 081h, 0F9h, 000h, 001h, 000h, 000h   ; cmp ecx, 0x100
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 009h   ; add ecx, 9
$L_347de3:
        db 03Dh, 080h, 000h, 000h, 000h   ; cmp eax, 0x80
        db 089h, 055h, 098h   ; mov dword ptr [ebp - 0x68], edx
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 089h, 04Dh, 094h   ; mov dword ptr [ebp - 0x6c], ecx
        db 08Bh, 04Ah, 010h   ; mov ecx, dword ptr [edx + 0x10]
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 089h, 09Dh, 070h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x90], ebx
        db 0C7h, 085h, 074h, 0FFh, 0FFh, 0FFh, 008h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x8c], 8
        db 089h, 09Dh, 078h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x88], ebx
        db 077h, 00Ch   ; ja 0x347e1e
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 00Fh, 0B6h, 0BFh   ; movzx edi, byte ptr [edi + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 043h   ; jmp 0x347e61
$L_347e1e:
        db 03Dh, 000h, 008h, 000h, 000h   ; cmp eax, 0x800
        db 072h, 01Fh   ; jb 0x347e44
        db 03Dh, 000h, 020h, 000h, 000h   ; cmp eax, 0x2000
        db 072h, 00Ch   ; jb 0x347e38
        db 03Dh, 000h, 040h, 000h, 000h   ; cmp eax, 0x4000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Fh   ; add edi, 0xf
        db 0EBh, 029h   ; jmp 0x347e61
$L_347e38:
        db 03Dh, 000h, 010h, 000h, 000h   ; cmp eax, 0x1000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Dh   ; add edi, 0xd
        db 0EBh, 01Dh   ; jmp 0x347e61
$L_347e44:
        db 03Dh, 000h, 002h, 000h, 000h   ; cmp eax, 0x200
        db 072h, 00Ch   ; jb 0x347e57
        db 03Dh, 000h, 004h, 000h, 000h   ; cmp eax, 0x400
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Bh   ; add edi, 0xb
        db 0EBh, 00Ah   ; jmp 0x347e61
$L_347e57:
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 009h   ; add edi, 9
$L_347e61:
        db 03Dh, 080h, 000h, 000h, 000h   ; cmp eax, 0x80
        db 089h, 08Dh, 02Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd4], ecx
        db 08Bh, 04Ah, 014h   ; mov ecx, dword ptr [edx + 0x14]
        db 089h, 0BDh, 028h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd8], edi
        db 089h, 09Dh, 000h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x100], ebx
        db 089h, 09Dh, 004h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xfc], ebx
        db 0C7h, 085h, 008h, 0FFh, 0FFh, 0FFh, 005h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0xf8], 5
        db 0C7h, 085h, 00Ch, 0FFh, 0FFh, 0FFh, 010h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0xf4], 0x10
        db 077h, 00Ch   ; ja 0x347ea3
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 00Fh, 0B6h, 0BFh   ; movzx edi, byte ptr [edi + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 043h   ; jmp 0x347ee6
$L_347ea3:
        db 03Dh, 000h, 008h, 000h, 000h   ; cmp eax, 0x800
        db 072h, 01Fh   ; jb 0x347ec9
        db 03Dh, 000h, 020h, 000h, 000h   ; cmp eax, 0x2000
        db 072h, 00Ch   ; jb 0x347ebd
        db 03Dh, 000h, 040h, 000h, 000h   ; cmp eax, 0x4000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Fh   ; add edi, 0xf
        db 0EBh, 029h   ; jmp 0x347ee6
$L_347ebd:
        db 03Dh, 000h, 010h, 000h, 000h   ; cmp eax, 0x1000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Dh   ; add edi, 0xd
        db 0EBh, 01Dh   ; jmp 0x347ee6
$L_347ec9:
        db 03Dh, 000h, 002h, 000h, 000h   ; cmp eax, 0x200
        db 072h, 00Ch   ; jb 0x347edc
        db 03Dh, 000h, 004h, 000h, 000h   ; cmp eax, 0x400
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Bh   ; add edi, 0xb
        db 0EBh, 00Ah   ; jmp 0x347ee6
$L_347edc:
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 009h   ; add edi, 9
$L_347ee6:
        db 03Dh, 080h, 000h, 000h, 000h   ; cmp eax, 0x80
        db 089h, 08Dh, 0FCh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x104], ecx
        db 08Bh, 04Ah, 018h   ; mov ecx, dword ptr [edx + 0x18]
        db 089h, 0BDh, 0F8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x108], edi
        db 089h, 09Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x130], ebx
        db 089h, 09Dh, 0D4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x12c], ebx
        db 0C7h, 085h, 0D8h, 0FEh, 0FFh, 0FFh, 005h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x128], 5
        db 0C7h, 085h, 0DCh, 0FEh, 0FFh, 0FFh, 010h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x124], 0x10
        db 077h, 00Ch   ; ja 0x347f28
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 00Fh, 0B6h, 0BFh   ; movzx edi, byte ptr [edi + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 043h   ; jmp 0x347f6b
$L_347f28:
        db 03Dh, 000h, 008h, 000h, 000h   ; cmp eax, 0x800
        db 072h, 01Fh   ; jb 0x347f4e
        db 03Dh, 000h, 020h, 000h, 000h   ; cmp eax, 0x2000
        db 072h, 00Ch   ; jb 0x347f42
        db 03Dh, 000h, 040h, 000h, 000h   ; cmp eax, 0x4000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Fh   ; add edi, 0xf
        db 0EBh, 029h   ; jmp 0x347f6b
$L_347f42:
        db 03Dh, 000h, 010h, 000h, 000h   ; cmp eax, 0x1000
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Dh   ; add edi, 0xd
        db 0EBh, 01Dh   ; jmp 0x347f6b
$L_347f4e:
        db 03Dh, 000h, 002h, 000h, 000h   ; cmp eax, 0x200
        db 072h, 00Ch   ; jb 0x347f61
        db 03Dh, 000h, 004h, 000h, 000h   ; cmp eax, 0x400
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 00Bh   ; add edi, 0xb
        db 0EBh, 00Ah   ; jmp 0x347f6b
$L_347f61:
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 01Bh, 0FFh   ; sbb edi, edi
        db 083h, 0C7h, 009h   ; add edi, 9
$L_347f6b:
        db 03Dh, 080h, 000h, 000h, 000h   ; cmp eax, 0x80
        db 089h, 0BDh, 028h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1d8], edi
        db 0BFh, 00Bh, 000h, 000h, 000h   ; mov edi, 0xb
        db 089h, 08Dh, 02Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1d4], ecx
        db 08Bh, 04Ah, 01Ch   ; mov ecx, dword ptr [edx + 0x1c]
        db 089h, 09Dh, 000h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x200], ebx
        db 089h, 09Dh, 004h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1fc], ebx
        db 089h, 0BDh, 008h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1f8], edi
        db 089h, 09Dh, 00Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1f4], ebx
        db 077h, 00Ch   ; ja 0x347faa
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 00Fh, 0B6h, 080h   ; movzx eax, byte ptr [eax + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 042h   ; jmp 0x347fec
$L_347faa:
        db 03Dh, 000h, 008h, 000h, 000h   ; cmp eax, 0x800
        db 072h, 01Fh   ; jb 0x347fd0
        db 03Dh, 000h, 020h, 000h, 000h   ; cmp eax, 0x2000
        db 072h, 00Ch   ; jb 0x347fc4
        db 03Dh, 000h, 040h, 000h, 000h   ; cmp eax, 0x4000
        db 01Bh, 0C0h   ; sbb eax, eax
        db 083h, 0C0h, 00Fh   ; add eax, 0xf
        db 0EBh, 028h   ; jmp 0x347fec
$L_347fc4:
        db 03Dh, 000h, 010h, 000h, 000h   ; cmp eax, 0x1000
        db 01Bh, 0C0h   ; sbb eax, eax
        db 083h, 0C0h, 00Dh   ; add eax, 0xd
        db 0EBh, 01Ch   ; jmp 0x347fec
$L_347fd0:
        db 03Dh, 000h, 002h, 000h, 000h   ; cmp eax, 0x200
        db 072h, 00Bh   ; jb 0x347fe2
        db 03Dh, 000h, 004h, 000h, 000h   ; cmp eax, 0x400
        db 01Bh, 0C0h   ; sbb eax, eax
        db 003h, 0C7h   ; add eax, edi
        db 0EBh, 00Ah   ; jmp 0x347fec
$L_347fe2:
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 01Bh, 0C0h   ; sbb eax, eax
        db 083h, 0C0h, 009h   ; add eax, 9
$L_347fec:
        db 08Bh, 052h, 020h   ; mov edx, dword ptr [edx + 0x20]
        db 089h, 085h, 0F8h, 0FDh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x208], eax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 08Dh, 004h, 040h   ; lea eax, [eax + eax*2]
        db 0C1h, 0E0h, 004h   ; shl eax, 4
        db 089h, 08Dh, 0FCh, 0FDh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x204], ecx
        db 08Dh, 088h, 0FFh, 001h, 000h, 000h   ; lea ecx, [eax + 0x1ff]
        db 081h, 0F9h, 080h, 000h, 000h, 000h   ; cmp ecx, 0x80
        db 089h, 09Dh, 0D0h, 0FDh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x230], ebx
        db 089h, 09Dh, 0D4h, 0FDh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x22c], ebx
        db 089h, 0BDh, 0D8h, 0FDh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x228], edi
        db 0C7h, 085h, 0DCh, 0FDh, 0FFh, 0FFh, 000h, 004h, 000h, 000h   ; mov dword ptr [ebp - 0x224], 0x400
        db 077h, 009h   ; ja 0x348037
        db 00Fh, 0B6h, 088h   ; movzx ecx, byte ptr [eax + 0x3ef097]
        dd __bitlevels+01FFh
        db 0EBh, 055h   ; jmp 0x34808c
$L_348037:
        db 081h, 0F9h, 000h, 008h, 000h, 000h   ; cmp ecx, 0x800
        db 072h, 028h   ; jb 0x348067
        db 081h, 0F9h, 000h, 020h, 000h, 000h   ; cmp ecx, 0x2000
        db 072h, 013h   ; jb 0x34805a
        db 081h, 0F9h, 000h, 040h, 000h, 000h   ; cmp ecx, 0x4000
        db 01Bh, 0C0h   ; sbb eax, eax
        db 083h, 0C0h, 00Fh   ; add eax, 0xf
        db 089h, 085h, 058h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xa8], eax
        db 0EBh, 038h   ; jmp 0x348092
$L_34805a:
        db 081h, 0F9h, 000h, 010h, 000h, 000h   ; cmp ecx, 0x1000
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 00Dh   ; add ecx, 0xd
        db 0EBh, 025h   ; jmp 0x34808c
$L_348067:
        db 081h, 0F9h, 000h, 002h, 000h, 000h   ; cmp ecx, 0x200
        db 072h, 012h   ; jb 0x348081
        db 081h, 0F9h, 000h, 004h, 000h, 000h   ; cmp ecx, 0x400
        db 01Bh, 0C0h   ; sbb eax, eax
        db 003h, 0C7h   ; add eax, edi
        db 089h, 085h, 058h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xa8], eax
        db 0EBh, 011h   ; jmp 0x348092
$L_348081:
        db 081h, 0F9h, 000h, 001h, 000h, 000h   ; cmp ecx, 0x100
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 083h, 0C1h, 009h   ; add ecx, 9
$L_34808c:
        db 089h, 08Dh, 058h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xa8], ecx
$L_348092:
        db 089h, 095h, 05Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xa4], edx
        db 08Dh, 095h, 070h, 0FEh, 0FFh, 0FFh   ; lea edx, [ebp - 0x190]
        db 052h   ; push edx
        db 08Dh, 085h, 080h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x180]
        db 050h   ; push eax
        db 08Dh, 08Dh, 084h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x17c]
        db 051h   ; push ecx
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 052h   ; push edx
        db 089h, 09Dh, 030h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd0], ebx
        db 089h, 09Dh, 034h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xcc], ebx
        db 0C7h, 085h, 038h, 0FFh, 0FFh, 0FFh, 004h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0xc8], 4
        db 089h, 09Dh, 03Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xc4], ebx
        call _ReadHuffTable   ; 0x3461E0
        db 08Dh, 085h, 040h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x1c0]
        db 050h   ; push eax
        db 08Dh, 08Dh, 050h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x1b0]
        db 051h   ; push ecx
        db 08Dh, 095h, 054h, 0FEh, 0FFh, 0FFh   ; lea edx, [ebp - 0x1ac]
        db 052h   ; push edx
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        call _ReadHuffTable   ; 0x3461E0
        db 08Dh, 08Dh, 0CCh, 0FBh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x434]
        db 051h   ; push ecx
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 052h   ; push edx
        db 08Dh, 045h, 0A4h   ; lea eax, [ebp - 0x5c]
        db 050h   ; push eax
        call _StartReadHuff8Bundle   ; 0x346870
        db 08Dh, 08Dh, 07Ch, 0FFh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x84]
        db 051h   ; push ecx
        db 08Dh, 055h, 08Ch   ; lea edx, [ebp - 0x74]
        db 052h   ; push edx
        db 08Dh, 045h, 090h   ; lea eax, [ebp - 0x70]
        db 050h   ; push eax
        db 08Dh, 04Dh, 0F0h   ; lea ecx, [ebp - 0x10]
        db 051h   ; push ecx
        call _ReadHuffTable   ; 0x3461E0
        db 08Dh, 095h, 010h, 0FFh, 0FFh, 0FFh   ; lea edx, [ebp - 0xf0]
        db 052h   ; push edx
        db 08Dh, 085h, 020h, 0FFh, 0FFh, 0FFh   ; lea eax, [ebp - 0xe0]
        db 050h   ; push eax
        db 08Dh, 08Dh, 024h, 0FFh, 0FFh, 0FFh   ; lea ecx, [ebp - 0xdc]
        db 051h   ; push ecx
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 052h   ; push edx
        call _ReadHuffTable   ; 0x3461E0
        db 083h, 0C4h, 04Ch   ; add esp, 0x4c
        db 08Dh, 085h, 0E0h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x120]
        db 050h   ; push eax
        db 08Dh, 08Dh, 0F0h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x110]
        db 051h   ; push ecx
        db 08Dh, 095h, 0F4h, 0FEh, 0FFh, 0FFh   ; lea edx, [ebp - 0x10c]
        db 052h   ; push edx
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        call _ReadHuffTable   ; 0x3461E0
        db 08Dh, 08Dh, 040h, 0FFh, 0FFh, 0FFh   ; lea ecx, [ebp - 0xc0]
        db 051h   ; push ecx
        db 08Dh, 095h, 050h, 0FFh, 0FFh, 0FFh   ; lea edx, [ebp - 0xb0]
        db 052h   ; push edx
        db 08Dh, 085h, 054h, 0FFh, 0FFh, 0FFh   ; lea eax, [ebp - 0xac]
        db 050h   ; push eax
        db 08Dh, 04Dh, 0F0h   ; lea ecx, [ebp - 0x10]
        db 051h   ; push ecx
        call _ReadHuffTable   ; 0x3461E0
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 083h, 0C4h, 020h   ; add esp, 0x20
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 089h, 05Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ebx
        db 00Fh, 086h, 024h, 018h, 000h, 000h   ; jbe 0x3499ae
        db 08Bh, 09Dh, 064h, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x9c]
$L_348190:
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 052h   ; push edx
        db 08Dh, 085h, 060h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x1a0]
        db 050h   ; push eax
        call _CheckReadRLEHuff4Bundle   ; 0x3468E0
        db 08Dh, 04Dh, 0F0h   ; lea ecx, [ebp - 0x10]
        db 051h   ; push ecx
        db 08Dh, 095h, 030h, 0FEh, 0FFh, 0FFh   ; lea edx, [ebp - 0x1d0]
        db 052h   ; push edx
        call _CheckReadRLEHuff4Bundle   ; 0x3468E0
        db 08Dh, 085h, 0CCh, 0FBh, 0FFh, 0FFh   ; lea eax, [ebp - 0x434]
        db 050h   ; push eax
        db 08Dh, 04Dh, 0F0h   ; lea ecx, [ebp - 0x10]
        db 051h   ; push ecx
        db 08Dh, 055h, 0A4h   ; lea edx, [ebp - 0x5c]
        db 052h   ; push edx
        db 0FFh, 095h, 068h, 0FFh, 0FFh, 0FFh   ; call dword ptr [ebp - 0x98]
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Dh, 0BDh, 06Ch, 0FFh, 0FFh, 0FFh   ; lea edi, [ebp - 0x94]
        call _CheckReadHuff4PairBundle   ; 0x347300
        db 08Dh, 04Dh, 0F0h   ; lea ecx, [ebp - 0x10]
        db 051h   ; push ecx
        db 08Dh, 095h, 000h, 0FFh, 0FFh, 0FFh   ; lea edx, [ebp - 0x100]
        db 052h   ; push edx
        call _CheckReadHuff4SBundle   ; 0x347500
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Dh, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x130]
        db 051h   ; push ecx
        call _CheckReadHuff4SBundle   ; 0x347500
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 052h   ; push edx
        db 08Dh, 085h, 000h, 0FEh, 0FFh, 0FFh   ; lea eax, [ebp - 0x200]
        db 050h   ; push eax
        call _CheckReadDelta16Bundle   ; 0x347780
        db 08Dh, 04Dh, 0F0h   ; lea ecx, [ebp - 0x10]
        db 051h   ; push ecx
        db 08Dh, 095h, 0D0h, 0FDh, 0FFh, 0FFh   ; lea edx, [ebp - 0x230]
        db 052h   ; push edx
        call _CheckReadDelta16Bundle   ; 0x347780
        db 083h, 0C4h, 040h   ; add esp, 0x40
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Dh, 08Dh, 030h, 0FFh, 0FFh, 0FFh   ; lea ecx, [ebp - 0xd0]
        db 051h   ; push ecx
        call _CheckReadHuff4Bundle   ; 0x3470F0
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 083h, 0C4h, 008h   ; add esp, 8
        db 085h, 0C0h   ; test eax, eax
        db 089h, 045h, 0D8h   ; mov dword ptr [ebp - 0x28], eax
        db 00Fh, 084h, 0F6h, 00Dh, 000h, 000h   ; je 0x34902e
        db 08Bh, 045h, 0A4h   ; mov eax, dword ptr [ebp - 0x5c]
        db 0EBh, 003h   ; jmp 0x348240
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_348240:
        db 08Bh, 095h, 060h, 0FEh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0x1a0]
        db 00Fh, 0B6h, 00Ah   ; movzx ecx, byte ptr [edx]
        db 042h   ; inc edx
        db 083h, 0F9h, 009h   ; cmp ecx, 9
        db 089h, 095h, 060h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1a0], edx
        db 00Fh, 087h, 0A1h, 00Dh, 000h, 000h   ; ja 0x348ffa
        db 0FFh, 024h, 08Dh   ; jmp dword ptr [ecx*4 + 0x3499c0]
        dd $L_3499c0
$L_348260:
        db 08Bh, 055h, 0E4h   ; mov edx, dword ptr [ebp - 0x1c]
        db 089h, 055h, 020h   ; mov dword ptr [ebp + 0x20], edx
        db 056h   ; push esi
        db 057h   ; push edi
        db 055h   ; push ebp
        db 053h   ; push ebx
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 06Dh, 018h   ; mov ebp, dword ptr [ebp + 0x18]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 08Dh, 034h, 06Eh   ; lea esi, [esi + ebp*2]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 08Dh, 034h, 06Eh   ; lea esi, [esi + ebp*2]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 08Dh, 034h, 06Eh   ; lea esi, [esi + ebp*2]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Bh, 075h, 018h   ; mov esi, dword ptr [ebp + 0x18]
        db 0D1h, 0E8h   ; shr eax, 1
        db 080h, 03Ch, 008h, 000h   ; cmp byte ptr [eax + ecx], 0
        db 00Fh, 085h, 0F9h, 00Ch, 000h, 000h   ; jne 0x348ff7
        db 0FFh, 045h, 0D4h   ; inc dword ptr [ebp - 0x2c]
        db 0E9h, 0F1h, 00Ch, 000h, 000h   ; jmp 0x348ff7
$L_348306:
        db 0F6h, 045h, 0DCh, 008h   ; test byte ptr [ebp - 0x24], 8
        db 00Fh, 085h, 0EAh, 00Bh, 000h, 000h   ; jne 0x348efa
        db 08Bh, 095h, 030h, 0FEh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0x1d0]
        db 00Fh, 0B6h, 00Ah   ; movzx ecx, byte ptr [edx]
        db 042h   ; inc edx
        db 083h, 0E9h, 003h   ; sub ecx, 3
        db 083h, 0F9h, 006h   ; cmp ecx, 6
        db 089h, 095h, 030h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x1d0], edx
        db 00Fh, 087h, 0CEh, 00Bh, 000h, 000h   ; ja 0x348efa
        db 0FFh, 024h, 08Dh   ; jmp dword ptr [ecx*4 + 0x3499e8]
        dd $L_3499e8
$L_348333:
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 089h, 05Dh, 024h   ; mov dword ptr [ebp + 0x24], ebx
        db 072h, 010h   ; jb 0x348351
        db 08Bh, 07Dh, 0F0h   ; mov edi, dword ptr [ebp - 0x10]
        db 08Bh, 0D7h   ; mov edx, edi
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 0EBh, 022h   ; jmp 0x348373
$L_348351:
        db 08Bh, 03Bh   ; mov edi, dword ptr [ebx]
        db 08Bh, 0D7h   ; mov edx, edi
        db 0D3h, 0E2h   ; shl edx, cl
        db 00Bh, 055h, 0F0h   ; or edx, dword ptr [ebp - 0x10]
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 04Dh, 0F8h   ; sub ecx, dword ptr [ebp - 8]
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 0D3h, 0EFh   ; shr edi, cl
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 083h, 0C1h, 01Ch   ; add ecx, 0x1c
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 089h, 05Dh, 024h   ; mov dword ptr [ebp + 0x24], ebx
$L_348373:
        db 0C1h, 0E2h, 006h   ; shl edx, 6
        db 081h, 0C2h   ; add edx, 0x3f0fc8
        dd _patterns
        db 089h, 04Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ecx
        db 089h, 055h, 09Ch   ; mov dword ptr [ebp - 0x64], edx
        db 033h, 0DBh   ; xor ebx, ebx
$L_348384:
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 010h   ; je 0x34839b
        db 08Bh, 055h, 00Ch   ; mov edx, dword ptr [ebp + 0xc]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 083h, 0E1h, 001h   ; and ecx, 1
        db 0D1h, 0EFh   ; shr edi, 1
        db 04Ah   ; dec edx
        db 089h, 055h, 00Ch   ; mov dword ptr [ebp + 0xc], edx
        db 0EBh, 01Bh   ; jmp 0x3483b6
$L_34839b:
        db 08Bh, 055h, 024h   ; mov edx, dword ptr [ebp + 0x24]
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 08Bh, 0FAh   ; mov edi, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 089h, 07Dh, 024h   ; mov dword ptr [ebp + 0x24], edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0D1h, 0EFh   ; shr edi, 1
        db 0C7h, 045h, 00Ch, 01Fh, 000h, 000h, 000h   ; mov dword ptr [ebp + 0xc], 0x1f
        db 083h, 0E1h, 001h   ; and ecx, 1
$L_3483b6:
        db 085h, 0C9h   ; test ecx, ecx
        db 08Bh, 095h, 030h, 0FFh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0xd0]
        db 074h, 03Ah   ; je 0x3483fa
        db 08Ah, 008h   ; mov cl, byte ptr [eax]
        db 040h   ; inc eax
        db 088h, 04Dh, 023h   ; mov byte ptr [ebp + 0x23], cl
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B6h, 00Ah   ; movzx ecx, byte ptr [edx]
        db 041h   ; inc ecx
        db 042h   ; inc edx
        db 085h, 0C9h   ; test ecx, ecx
        db 089h, 095h, 030h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd0], edx
        db 074h, 056h   ; je 0x34842e
        db 089h, 04Dh, 0E0h   ; mov dword ptr [ebp - 0x20], ecx
        db 08Ah, 04Dh, 023h   ; mov cl, byte ptr [ebp + 0x23]
        db 08Bh, 0FFh   ; mov edi, edi
$L_3483e0:
        db 08Bh, 055h, 09Ch   ; mov edx, dword ptr [ebp - 0x64]
        db 00Fh, 0B6h, 014h, 013h   ; movzx edx, byte ptr [ebx + edx]
        db 088h, 08Ch, 015h, 090h, 0FEh, 0FFh, 0FFh   ; mov byte ptr [ebp + edx - 0x170], cl
        db 08Bh, 055h, 0E0h   ; mov edx, dword ptr [ebp - 0x20]
        db 043h   ; inc ebx
        db 04Ah   ; dec edx
        db 089h, 055h, 0E0h   ; mov dword ptr [ebp - 0x20], edx
        db 075h, 0E8h   ; jne 0x3483e0
        db 0EBh, 034h   ; jmp 0x34842e
$L_3483fa:
        db 00Fh, 0B6h, 00Ah   ; movzx ecx, byte ptr [edx]
        db 041h   ; inc ecx
        db 042h   ; inc edx
        db 085h, 0C9h   ; test ecx, ecx
        db 089h, 095h, 030h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd0], edx
        db 074h, 025h   ; je 0x34842e
        db 089h, 04Dh, 020h   ; mov dword ptr [ebp + 0x20], ecx
        db 08Dh, 064h, 024h, 000h   ; lea esp, [esp]
$L_348410:
        db 08Bh, 04Dh, 09Ch   ; mov ecx, dword ptr [ebp - 0x64]
        db 00Fh, 0B6h, 014h, 00Bh   ; movzx edx, byte ptr [ebx + ecx]
        db 08Ah, 008h   ; mov cl, byte ptr [eax]
        db 088h, 08Ch, 015h, 090h, 0FEh, 0FFh, 0FFh   ; mov byte ptr [ebp + edx - 0x170], cl
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 043h   ; inc ebx
        db 040h   ; inc eax
        db 049h   ; dec ecx
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 089h, 04Dh, 020h   ; mov dword ptr [ebp + 0x20], ecx
        db 075h, 0E2h   ; jne 0x348410
$L_34842e:
        db 083h, 0FBh, 03Fh   ; cmp ebx, 0x3f
        db 00Fh, 08Ch, 04Dh, 0FFh, 0FFh, 0FFh   ; jl 0x348384
        db 089h, 07Dh, 0A0h   ; mov dword ptr [ebp - 0x60], edi
        db 075h, 014h   ; jne 0x348450
        db 08Bh, 055h, 09Ch   ; mov edx, dword ptr [ebp - 0x64]
        db 00Fh, 0B6h, 04Ah, 03Fh   ; movzx ecx, byte ptr [edx + 0x3f]
        db 08Ah, 010h   ; mov dl, byte ptr [eax]
        db 040h   ; inc eax
        db 088h, 094h, 00Dh, 090h, 0FEh, 0FFh, 0FFh   ; mov byte ptr [ebp + ecx - 0x170], dl
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
$L_348450:
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Dh, 00Ch, 037h   ; lea ecx, [edi + esi]
        db 089h, 04Dh, 020h   ; mov dword ptr [ebp + 0x20], ecx
        db 08Dh, 08Dh, 094h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x16c]
        db 0C7h, 045h, 0E0h, 002h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x20], 2
        db 0EBh, 008h   ; jmp 0x348470
        db 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h   ; lea esp, [esp]
        db 090h   ; nop 
$L_348470:
        db 00Fh, 0B7h, 059h, 0FCh   ; movzx ebx, word ptr [ecx - 4]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 089h, 017h   ; mov dword ptr [edi], edx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 013h   ; mov dword ptr [ebx], edx
        db 00Fh, 0B7h, 059h, 0FEh   ; movzx ebx, word ptr [ecx - 2]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 089h, 057h, 004h   ; mov dword ptr [edi + 4], edx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 053h, 004h   ; mov dword ptr [ebx + 4], edx
        db 00Fh, 0B7h, 019h   ; movzx ebx, word ptr [ecx]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 008h   ; mov dword ptr [edi + 8], edx
        db 089h, 053h, 008h   ; mov dword ptr [ebx + 8], edx
        db 00Fh, 0B7h, 059h, 002h   ; movzx ebx, word ptr [ecx + 2]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 00Fh, 0B7h, 059h, 004h   ; movzx ebx, word ptr [ecx + 4]
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 003h, 0FEh   ; add edi, esi
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 055h, 020h   ; mov dword ptr [ebp + 0x20], edx
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 017h   ; mov dword ptr [edi], edx
        db 089h, 013h   ; mov dword ptr [ebx], edx
        db 00Fh, 0B7h, 059h, 006h   ; movzx ebx, word ptr [ecx + 6]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 004h   ; mov dword ptr [edi + 4], edx
        db 089h, 053h, 004h   ; mov dword ptr [ebx + 4], edx
        db 00Fh, 0B7h, 059h, 008h   ; movzx ebx, word ptr [ecx + 8]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 008h   ; mov dword ptr [edi + 8], edx
        db 089h, 053h, 008h   ; mov dword ptr [ebx + 8], edx
        db 00Fh, 0B7h, 059h, 00Ah   ; movzx ebx, word ptr [ecx + 0xa]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 00Fh, 0B7h, 059h, 00Ch   ; movzx ebx, word ptr [ecx + 0xc]
        db 003h, 0FEh   ; add edi, esi
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 055h, 020h   ; mov dword ptr [ebp + 0x20], edx
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 089h, 017h   ; mov dword ptr [edi], edx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 013h   ; mov dword ptr [ebx], edx
        db 00Fh, 0B7h, 059h, 00Eh   ; movzx ebx, word ptr [ecx + 0xe]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 004h   ; mov dword ptr [edi + 4], edx
        db 089h, 053h, 004h   ; mov dword ptr [ebx + 4], edx
        db 00Fh, 0B7h, 059h, 010h   ; movzx ebx, word ptr [ecx + 0x10]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 008h   ; mov dword ptr [edi + 8], edx
        db 089h, 053h, 008h   ; mov dword ptr [ebx + 8], edx
        db 00Fh, 0B7h, 059h, 012h   ; movzx ebx, word ptr [ecx + 0x12]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 00Fh, 0B7h, 059h, 014h   ; movzx ebx, word ptr [ecx + 0x14]
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 003h, 0FEh   ; add edi, esi
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 055h, 020h   ; mov dword ptr [ebp + 0x20], edx
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 017h   ; mov dword ptr [edi], edx
        db 089h, 013h   ; mov dword ptr [ebx], edx
        db 00Fh, 0B7h, 059h, 016h   ; movzx ebx, word ptr [ecx + 0x16]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 004h   ; mov dword ptr [edi + 4], edx
        db 089h, 053h, 004h   ; mov dword ptr [ebx + 4], edx
        db 00Fh, 0B7h, 059h, 018h   ; movzx ebx, word ptr [ecx + 0x18]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 057h, 008h   ; mov dword ptr [edi + 8], edx
        db 089h, 053h, 008h   ; mov dword ptr [ebx + 8], edx
        db 00Fh, 0B7h, 059h, 01Ah   ; movzx ebx, word ptr [ecx + 0x1a]
        db 08Bh, 0D3h   ; mov edx, ebx
        db 081h, 0E2h, 000h, 0FFh, 0FFh, 0FFh   ; and edx, 0xffffff00
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D3h   ; or edx, ebx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0D3h   ; or edx, ebx
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 057h, 00Ch   ; mov dword ptr [edi + 0xc], edx
        db 003h, 0FEh   ; add edi, esi
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 055h, 020h   ; mov dword ptr [ebp + 0x20], edx
        db 08Bh, 055h, 0E0h   ; mov edx, dword ptr [ebp - 0x20]
        db 083h, 0C1h, 020h   ; add ecx, 0x20
        db 04Ah   ; dec edx
        db 089h, 055h, 0E0h   ; mov dword ptr [ebp - 0x20], edx
        db 00Fh, 085h, 089h, 0FDh, 0FFh, 0FFh   ; jne 0x348470
        db 08Bh, 04Dh, 024h   ; mov ecx, dword ptr [ebp + 0x24]
        db 08Bh, 055h, 0A0h   ; mov edx, dword ptr [ebp - 0x60]
        db 089h, 04Dh, 0F4h   ; mov dword ptr [ebp - 0xc], ecx
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 089h, 04Dh, 0F8h   ; mov dword ptr [ebp - 8], ecx
        db 0E9h, 0FCh, 007h, 000h, 000h   ; jmp 0x348efa
$L_3486fe:
        db 08Bh, 085h, 000h, 0FEh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x200]
        db 066h, 08Bh, 010h   ; mov dx, word ptr [eax]
        db 083h, 0C0h, 002h   ; add eax, 2
        db 089h, 085h, 000h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x200], eax
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Dh, 08Dh, 050h, 0FDh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x2b0]
        db 051h   ; push ecx
        db 066h, 089h, 095h, 050h, 0FDh, 0FFh, 0FFh   ; mov word ptr [ebp - 0x2b0], dx
        call _ReadBPLossless@8   ; 0x34CEC0
        db 08Bh, 07Dh, 0F8h   ; mov edi, dword ptr [ebp - 8]
        db 083h, 0FFh, 004h   ; cmp edi, 4
        db 072h, 013h   ; jb 0x348742
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 004h   ; shr ecx, 4
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
        db 083h, 0EFh, 004h   ; sub edi, 4
        db 0EBh, 026h   ; jmp 0x348768
$L_348742:
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 08Bh, 013h   ; mov edx, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0C2h   ; mov eax, edx
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 045h, 0F0h   ; or eax, dword ptr [ebp - 0x10]
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0EAh   ; shr edx, cl
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 083h, 0C7h, 01Ch   ; add edi, 0x1c
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 089h, 05Dh, 0F4h   ; mov dword ptr [ebp - 0xc], ebx
$L_348768:
        db 050h   ; push eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Dh, 095h, 050h, 0FDh, 0FFh, 0FFh   ; lea edx, [ebp - 0x2b0]
        db 052h   ; push edx
        db 056h   ; push esi
        db 050h   ; push eax
        db 089h, 07Dh, 0F8h   ; mov dword ptr [ebp - 8], edi
        call _FastIDCT8x8d@16   ; 0x34CB00
        db 08Bh, 045h, 0A4h   ; mov eax, dword ptr [ebp - 0x5c]
        db 0E9h, 075h, 007h, 000h, 000h   ; jmp 0x348efa
$L_348785:
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0CAh   ; or ecx, edx
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E2h, 010h   ; shl edx, 0x10
        db 040h   ; inc eax
        db 00Bh, 0CAh   ; or ecx, edx
        db 089h, 00Fh   ; mov dword ptr [edi], ecx
        db 089h, 04Fh, 004h   ; mov dword ptr [edi + 4], ecx
        db 089h, 04Fh, 008h   ; mov dword ptr [edi + 8], ecx
        db 089h, 04Fh, 00Ch   ; mov dword ptr [edi + 0xc], ecx
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 04Ch, 037h, 004h   ; mov dword ptr [edi + esi + 4], ecx
        db 089h, 04Ch, 037h, 008h   ; mov dword ptr [edi + esi + 8], ecx
        db 089h, 04Ch, 037h, 00Ch   ; mov dword ptr [edi + esi + 0xc], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 089h, 04Ch, 032h, 008h   ; mov dword ptr [edx + esi + 8], ecx
        db 089h, 04Ch, 032h, 00Ch   ; mov dword ptr [edx + esi + 0xc], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 04Ch, 037h, 004h   ; mov dword ptr [edi + esi + 4], ecx
        db 089h, 04Ch, 037h, 008h   ; mov dword ptr [edi + esi + 8], ecx
        db 089h, 04Ch, 037h, 00Ch   ; mov dword ptr [edi + esi + 0xc], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 089h, 04Ch, 032h, 008h   ; mov dword ptr [edx + esi + 8], ecx
        db 089h, 04Ch, 032h, 00Ch   ; mov dword ptr [edx + esi + 0xc], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 04Ch, 037h, 004h   ; mov dword ptr [edi + esi + 4], ecx
        db 089h, 04Ch, 037h, 008h   ; mov dword ptr [edi + esi + 8], ecx
        db 089h, 04Ch, 037h, 00Ch   ; mov dword ptr [edi + esi + 0xc], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 089h, 04Ch, 032h, 008h   ; mov dword ptr [edx + esi + 8], ecx
        db 089h, 04Ch, 032h, 00Ch   ; mov dword ptr [edx + esi + 0xc], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 04Ch, 037h, 004h   ; mov dword ptr [edi + esi + 4], ecx
        db 089h, 04Ch, 037h, 008h   ; mov dword ptr [edi + esi + 8], ecx
        db 089h, 04Ch, 037h, 00Ch   ; mov dword ptr [edi + esi + 0xc], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 089h, 04Ch, 032h, 008h   ; mov dword ptr [edx + esi + 8], ecx
        db 089h, 04Ch, 032h, 00Ch   ; mov dword ptr [edx + esi + 0xc], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 04Ch, 037h, 004h   ; mov dword ptr [edi + esi + 4], ecx
        db 089h, 04Ch, 037h, 008h   ; mov dword ptr [edi + esi + 8], ecx
        db 089h, 04Ch, 037h, 00Ch   ; mov dword ptr [edi + esi + 0xc], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 04Fh, 004h   ; mov dword ptr [edi + 4], ecx
        db 089h, 04Fh, 008h   ; mov dword ptr [edi + 8], ecx
        db 089h, 04Fh, 00Ch   ; mov dword ptr [edi + 0xc], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 089h, 04Ah, 004h   ; mov dword ptr [edx + 4], ecx
        db 089h, 04Ah, 008h   ; mov dword ptr [edx + 8], ecx
        db 089h, 04Ah, 00Ch   ; mov dword ptr [edx + 0xc], ecx
        db 08Dh, 01Ch, 037h   ; lea ebx, [edi + esi]
        db 089h, 00Fh   ; mov dword ptr [edi], ecx
        db 089h, 04Fh, 004h   ; mov dword ptr [edi + 4], ecx
        db 089h, 04Fh, 008h   ; mov dword ptr [edi + 8], ecx
        db 089h, 04Fh, 00Ch   ; mov dword ptr [edi + 0xc], ecx
        db 08Dh, 014h, 033h   ; lea edx, [ebx + esi]
        db 089h, 00Bh   ; mov dword ptr [ebx], ecx
        db 089h, 04Bh, 004h   ; mov dword ptr [ebx + 4], ecx
        db 089h, 04Bh, 008h   ; mov dword ptr [ebx + 8], ecx
        db 089h, 04Bh, 00Ch   ; mov dword ptr [ebx + 0xc], ecx
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 089h, 04Ah, 004h   ; mov dword ptr [edx + 4], ecx
        db 089h, 04Ah, 008h   ; mov dword ptr [edx + 8], ecx
        db 089h, 04Ah, 00Ch   ; mov dword ptr [edx + 0xc], ecx
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 089h, 04Ch, 032h, 008h   ; mov dword ptr [edx + esi + 8], ecx
        db 089h, 04Ch, 032h, 00Ch   ; mov dword ptr [edx + esi + 0xc], ecx
        db 0E9h, 055h, 006h, 000h, 000h   ; jmp 0x348efa
$L_3488a5:
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 040h   ; inc eax
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B6h, 010h   ; movzx edx, byte ptr [eax]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0CFh   ; or ecx, edi
        db 08Bh, 0FAh   ; mov edi, edx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0D7h   ; or edx, edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0C1h, 0E7h, 010h   ; shl edi, 0x10
        db 00Bh, 0CFh   ; or ecx, edi
        db 08Bh, 0FAh   ; mov edi, edx
        db 0C1h, 0E7h, 010h   ; shl edi, 0x10
        db 00Bh, 0D7h   ; or edx, edi
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 040h   ; inc eax
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 003h, 0FEh   ; add edi, esi
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 0C7h, 045h, 0E0h, 002h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x20], 2
$L_3488e1:
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 024h   ; mov dword ptr [ebp + 0x24], edi
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 002h   ; shr edi, 2
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 006h   ; shr edi, 6
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 0DFh   ; mov ebx, edi
        db 08Bh, 0BBh   ; mov edi, dword ptr [ebx + 0x3eedd0]
        dd _mask4
        db 08Bh, 09Bh   ; mov ebx, dword ptr [ebx + 0x3eede0]
        dd _mask3
        db 023h, 0FAh   ; and edi, edx
        db 023h, 0D9h   ; and ebx, ecx
        db 00Bh, 0FBh   ; or edi, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Dh, 03Ch, 033h   ; lea edi, [ebx + esi]
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 003h, 0FEh   ; add edi, esi
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 024h   ; mov dword ptr [ebp + 0x24], edi
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 002h   ; shr edi, 2
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 023h, 0DAh   ; and ebx, edx
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 006h   ; shr edi, 6
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 0DFh   ; mov ebx, edi
        db 08Bh, 0BBh   ; mov edi, dword ptr [ebx + 0x3eedd0]
        dd _mask4
        db 08Bh, 09Bh   ; mov ebx, dword ptr [ebx + 0x3eede0]
        dd _mask3
        db 023h, 0FAh   ; and edi, edx
        db 023h, 0D9h   ; and ebx, ecx
        db 00Bh, 0FBh   ; or edi, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Dh, 03Ch, 033h   ; lea edi, [ebx + esi]
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 003h, 0FEh   ; add edi, esi
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 024h   ; mov dword ptr [ebp + 0x24], edi
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 002h   ; shr edi, 2
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 006h   ; shr edi, 6
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 0DFh   ; mov ebx, edi
        db 08Bh, 0BBh   ; mov edi, dword ptr [ebx + 0x3eedd0]
        dd _mask4
        db 08Bh, 09Bh   ; mov ebx, dword ptr [ebx + 0x3eede0]
        dd _mask3
        db 023h, 0FAh   ; and edi, edx
        db 023h, 0D9h   ; and ebx, ecx
        db 00Bh, 0FBh   ; or edi, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Dh, 03Ch, 033h   ; lea edi, [ebx + esi]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 003h, 0FEh   ; add edi, esi
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 024h   ; mov dword ptr [ebp + 0x24], edi
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 002h   ; shr edi, 2
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 083h, 0E7h, 003h   ; and edi, 3
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eedd0]
        dd _mask4
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eede0]
        dd _mask3
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 008h   ; mov dword ptr [edi + 8], ebx
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 0C1h, 0EFh, 006h   ; shr edi, 6
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 0DFh   ; mov ebx, edi
        db 08Bh, 0BBh   ; mov edi, dword ptr [ebx + 0x3eedd0]
        dd _mask4
        db 08Bh, 09Bh   ; mov ebx, dword ptr [ebx + 0x3eede0]
        dd _mask3
        db 023h, 0FAh   ; and edi, edx
        db 023h, 0D9h   ; and ebx, ecx
        db 00Bh, 0FBh   ; or edi, ebx
        db 08Bh, 05Dh, 020h   ; mov ebx, dword ptr [ebp + 0x20]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 089h, 07Bh, 00Ch   ; mov dword ptr [ebx + 0xc], edi
        db 08Dh, 03Ch, 033h   ; lea edi, [ebx + esi]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 003h, 0FEh   ; add edi, esi
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 0FFh, 04Dh, 0E0h   ; dec dword ptr [ebp - 0x20]
        db 00Fh, 085h, 003h, 0FDh, 0FFh, 0FFh   ; jne 0x3488e1
        db 0E9h, 017h, 003h, 000h, 000h   ; jmp 0x348efa
$L_348be3:
        db 0A8h, 003h   ; test al, 3
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 08Dh, 014h, 031h   ; lea edx, [ecx + esi]
        db 00Fh, 084h, 0ADh, 000h, 000h, 000h   ; je 0x348c9e
        db 02Bh, 0D1h   ; sub edx, ecx
        db 0C7h, 045h, 00Ch, 008h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0xc], 8
        db 08Dh, 09Bh, 000h, 000h, 000h, 000h   ; lea ebx, [ebx]
$L_348c00:
        db 00Fh, 0B6h, 058h, 001h   ; movzx ebx, byte ptr [eax + 1]
        db 00Fh, 0B6h, 038h   ; movzx edi, byte ptr [eax]
        db 089h, 05Dh, 020h   ; mov dword ptr [ebp + 0x20], ebx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 05Dh, 020h   ; or ebx, dword ptr [ebp + 0x20]
        db 083h, 0C0h, 008h   ; add eax, 8
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 039h   ; mov dword ptr [ecx], edi
        db 089h, 03Ch, 00Ah   ; mov dword ptr [edx + ecx], edi
        db 00Fh, 0B6h, 058h, 0FBh   ; movzx ebx, byte ptr [eax - 5]
        db 00Fh, 0B6h, 078h, 0FAh   ; movzx edi, byte ptr [eax - 6]
        db 089h, 05Dh, 020h   ; mov dword ptr [ebp + 0x20], ebx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 05Dh, 020h   ; or ebx, dword ptr [ebp + 0x20]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 004h   ; mov dword ptr [ecx + 4], edi
        db 089h, 07Ch, 00Ah, 004h   ; mov dword ptr [edx + ecx + 4], edi
        db 00Fh, 0B6h, 058h, 0FDh   ; movzx ebx, byte ptr [eax - 3]
        db 00Fh, 0B6h, 078h, 0FCh   ; movzx edi, byte ptr [eax - 4]
        db 089h, 05Dh, 020h   ; mov dword ptr [ebp + 0x20], ebx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 05Dh, 020h   ; or ebx, dword ptr [ebp + 0x20]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 008h   ; mov dword ptr [ecx + 8], edi
        db 089h, 07Ch, 00Ah, 008h   ; mov dword ptr [edx + ecx + 8], edi
        db 00Fh, 0B6h, 058h, 0FFh   ; movzx ebx, byte ptr [eax - 1]
        db 00Fh, 0B6h, 078h, 0FEh   ; movzx edi, byte ptr [eax - 2]
        db 089h, 05Dh, 020h   ; mov dword ptr [ebp + 0x20], ebx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 05Dh, 020h   ; or ebx, dword ptr [ebp + 0x20]
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 00Ch   ; mov dword ptr [ecx + 0xc], edi
        db 089h, 07Ch, 00Ah, 00Ch   ; mov dword ptr [edx + ecx + 0xc], edi
        db 08Dh, 03Ch, 036h   ; lea edi, [esi + esi]
        db 003h, 0CFh   ; add ecx, edi
        db 0FFh, 04Dh, 00Ch   ; dec dword ptr [ebp + 0xc]
        db 00Fh, 085h, 067h, 0FFh, 0FFh, 0FFh   ; jne 0x348c00
        db 0E9h, 05Ch, 002h, 000h, 000h   ; jmp 0x348efa
$L_348c9e:
        db 0C7h, 045h, 020h, 002h, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x20], 2
$L_348ca5:
        db 00Fh, 0B7h, 018h   ; movzx ebx, word ptr [eax]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 039h   ; mov dword ptr [ecx], edi
        db 089h, 03Ah   ; mov dword ptr [edx], edi
        db 00Fh, 0B7h, 058h, 002h   ; movzx ebx, word ptr [eax + 2]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 004h   ; mov dword ptr [ecx + 4], edi
        db 089h, 07Ah, 004h   ; mov dword ptr [edx + 4], edi
        db 00Fh, 0B7h, 058h, 004h   ; movzx ebx, word ptr [eax + 4]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 008h   ; mov dword ptr [ecx + 8], edi
        db 089h, 07Ah, 008h   ; mov dword ptr [edx + 8], edi
        db 00Fh, 0B7h, 058h, 006h   ; movzx ebx, word ptr [eax + 6]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 00Ch   ; mov dword ptr [ecx + 0xc], edi
        db 089h, 07Ah, 00Ch   ; mov dword ptr [edx + 0xc], edi
        db 083h, 0C0h, 008h   ; add eax, 8
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B7h, 018h   ; movzx ebx, word ptr [eax]
        db 08Dh, 03Ch, 036h   ; lea edi, [esi + esi]
        db 003h, 0CFh   ; add ecx, edi
        db 003h, 0D7h   ; add edx, edi
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 039h   ; mov dword ptr [ecx], edi
        db 089h, 03Ah   ; mov dword ptr [edx], edi
        db 00Fh, 0B7h, 058h, 002h   ; movzx ebx, word ptr [eax + 2]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 004h   ; mov dword ptr [ecx + 4], edi
        db 089h, 07Ah, 004h   ; mov dword ptr [edx + 4], edi
        db 00Fh, 0B7h, 058h, 004h   ; movzx ebx, word ptr [eax + 4]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 008h   ; mov dword ptr [ecx + 8], edi
        db 089h, 07Ah, 008h   ; mov dword ptr [edx + 8], edi
        db 00Fh, 0B7h, 058h, 006h   ; movzx ebx, word ptr [eax + 6]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 00Ch   ; mov dword ptr [ecx + 0xc], edi
        db 089h, 07Ah, 00Ch   ; mov dword ptr [edx + 0xc], edi
        db 083h, 0C0h, 008h   ; add eax, 8
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B7h, 018h   ; movzx ebx, word ptr [eax]
        db 08Dh, 03Ch, 036h   ; lea edi, [esi + esi]
        db 003h, 0CFh   ; add ecx, edi
        db 003h, 0D7h   ; add edx, edi
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 039h   ; mov dword ptr [ecx], edi
        db 089h, 03Ah   ; mov dword ptr [edx], edi
        db 00Fh, 0B7h, 058h, 002h   ; movzx ebx, word ptr [eax + 2]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 004h   ; mov dword ptr [ecx + 4], edi
        db 089h, 07Ah, 004h   ; mov dword ptr [edx + 4], edi
        db 00Fh, 0B7h, 058h, 004h   ; movzx ebx, word ptr [eax + 4]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 008h   ; mov dword ptr [ecx + 8], edi
        db 089h, 07Ah, 008h   ; mov dword ptr [edx + 8], edi
        db 00Fh, 0B7h, 058h, 006h   ; movzx ebx, word ptr [eax + 6]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 00Ch   ; mov dword ptr [ecx + 0xc], edi
        db 089h, 07Ah, 00Ch   ; mov dword ptr [edx + 0xc], edi
        db 083h, 0C0h, 008h   ; add eax, 8
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B7h, 018h   ; movzx ebx, word ptr [eax]
        db 08Dh, 03Ch, 036h   ; lea edi, [esi + esi]
        db 003h, 0CFh   ; add ecx, edi
        db 003h, 0D7h   ; add edx, edi
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 039h   ; mov dword ptr [ecx], edi
        db 089h, 03Ah   ; mov dword ptr [edx], edi
        db 00Fh, 0B7h, 058h, 002h   ; movzx ebx, word ptr [eax + 2]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 004h   ; mov dword ptr [ecx + 4], edi
        db 089h, 07Ah, 004h   ; mov dword ptr [edx + 4], edi
        db 00Fh, 0B7h, 058h, 004h   ; movzx ebx, word ptr [eax + 4]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 008h   ; mov dword ptr [ecx + 8], edi
        db 089h, 07Ah, 008h   ; mov dword ptr [edx + 8], edi
        db 00Fh, 0B7h, 058h, 006h   ; movzx ebx, word ptr [eax + 6]
        db 08Bh, 0FBh   ; mov edi, ebx
        db 081h, 0E7h, 000h, 0FFh, 0FFh, 0FFh   ; and edi, 0xffffff00
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0E3h, 0FFh, 000h, 000h, 000h   ; and ebx, 0xff
        db 00Bh, 0FBh   ; or edi, ebx
        db 089h, 079h, 00Ch   ; mov dword ptr [ecx + 0xc], edi
        db 089h, 07Ah, 00Ch   ; mov dword ptr [edx + 0xc], edi
        db 08Dh, 03Ch, 036h   ; lea edi, [esi + esi]
        db 003h, 0CFh   ; add ecx, edi
        db 003h, 0D7h   ; add edx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 083h, 0C0h, 008h   ; add eax, 8
        db 04Fh   ; dec edi
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 00Fh, 085h, 0ABh, 0FDh, 0FFh, 0FFh   ; jne 0x348ca5
$L_348efa:
        db 08Bh, 05Dh, 0E4h   ; mov ebx, dword ptr [ebp - 0x1c]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Bh, 07Dh, 0D8h   ; mov edi, dword ptr [ebp - 0x28]
        db 0B9h, 008h, 000h, 000h, 000h   ; mov ecx, 8
        db 003h, 0D9h   ; add ebx, ecx
        db 02Bh, 0F9h   ; sub edi, ecx
        db 003h, 0D1h   ; add edx, ecx
        db 08Bh, 04Dh, 0E8h   ; mov ecx, dword ptr [ebp - 0x18]
        db 089h, 05Dh, 0E4h   ; mov dword ptr [ebp - 0x1c], ebx
        db 08Bh, 05Dh, 01Ch   ; mov ebx, dword ptr [ebp + 0x1c]
        db 089h, 07Dh, 0D8h   ; mov dword ptr [ebp - 0x28], edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 003h, 0CBh   ; add ecx, ebx
        db 089h, 055h, 008h   ; mov dword ptr [ebp + 8], edx
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 0D1h, 0EFh   ; shr edi, 1
        db 089h, 04Dh, 0E8h   ; mov dword ptr [ebp - 0x18], ecx
        db 0D1h, 0E9h   ; shr ecx, 1
        db 0C6h, 004h, 017h, 001h   ; mov byte ptr [edi + edx], 1
        db 0C6h, 004h, 011h, 001h   ; mov byte ptr [ecx + edx], 1
        db 0E9h, 0C2h, 000h, 000h, 000h   ; jmp 0x348ffa
$L_348f38:
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Bh, 05Dh, 0E4h   ; mov ebx, dword ptr [ebp - 0x1c]
        db 0D1h, 0E8h   ; shr eax, 1
        db 0C6h, 004h, 008h, 001h   ; mov byte ptr [eax + ecx], 1
        db 08Bh, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x130]
        db 00Fh, 0BEh, 011h   ; movsx edx, byte ptr [ecx]
        db 08Bh, 085h, 000h, 0FFh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x100]
        db 00Fh, 0AFh, 0D6h   ; imul edx, esi
        db 00Fh, 0BEh, 030h   ; movsx esi, byte ptr [eax]
        db 003h, 0D3h   ; add edx, ebx
        db 003h, 0F2h   ; add esi, edx
        db 040h   ; inc eax
        db 041h   ; inc ecx
        db 089h, 075h, 020h   ; mov dword ptr [ebp + 0x20], esi
        db 089h, 085h, 000h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x100], eax
        db 089h, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x130], ecx
        db 056h   ; push esi
        db 057h   ; push edi
        db 055h   ; push ebp
        db 053h   ; push ebx
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 06Dh, 018h   ; mov ebp, dword ptr [ebp + 0x18]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 08Dh, 034h, 06Eh   ; lea esi, [esi + ebp*2]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 08Dh, 034h, 06Eh   ; lea esi, [esi + ebp*2]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 08Dh, 034h, 06Eh   ; lea esi, [esi + ebp*2]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 02Eh   ; mov ecx, dword ptr [esi + ebp]
        db 08Bh, 054h, 02Eh, 004h   ; mov edx, dword ptr [esi + ebp + 4]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
$L_348ff4:
        db 08Bh, 075h, 018h   ; mov esi, dword ptr [ebp + 0x18]
$L_348ff7:
        db 08Bh, 045h, 0A4h   ; mov eax, dword ptr [ebp - 0x5c]
$L_348ffa:
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 08Bh, 04Dh, 0E8h   ; mov ecx, dword ptr [ebp - 0x18]
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 08Bh, 07Dh, 0E4h   ; mov edi, dword ptr [ebp - 0x1c]
        db 003h, 0CAh   ; add ecx, edx
        db 08Bh, 055h, 0D8h   ; mov edx, dword ptr [ebp - 0x28]
        db 089h, 04Dh, 0E8h   ; mov dword ptr [ebp - 0x18], ecx
        db 0B9h, 008h, 000h, 000h, 000h   ; mov ecx, 8
        db 003h, 0D9h   ; add ebx, ecx
        db 003h, 0F9h   ; add edi, ecx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 089h, 05Dh, 008h   ; mov dword ptr [ebp + 8], ebx
        db 089h, 07Dh, 0E4h   ; mov dword ptr [ebp - 0x1c], edi
        db 089h, 055h, 0D8h   ; mov dword ptr [ebp - 0x28], edx
        db 00Fh, 085h, 018h, 0F2h, 0FFh, 0FFh   ; jne 0x348240
        db 08Bh, 09Dh, 064h, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x9c]
$L_34902e:
        db 083h, 07Dh, 01Ch, 001h   ; cmp dword ptr [ebp + 0x1c], 1
        db 00Fh, 085h, 02Bh, 009h, 000h, 000h   ; jne 0x349963
        db 0F6h, 045h, 0DCh, 008h   ; test byte ptr [ebp - 0x24], 8
        db 00Fh, 084h, 02Fh, 009h, 000h, 000h   ; je 0x349971
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Bh, 085h, 060h, 0FFh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0xa0]
        db 003h, 0C8h   ; add ecx, eax
        db 089h, 04Dh, 0ECh   ; mov dword ptr [ebp - 0x14], ecx
        db 0E9h, 01Ch, 009h, 000h, 000h   ; jmp 0x349971
$L_349055:
        db 08Bh, 07Dh, 0F8h   ; mov edi, dword ptr [ebp - 8]
        db 083h, 0FFh, 004h   ; cmp edi, 4
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 089h, 05Dh, 024h   ; mov dword ptr [ebp + 0x24], ebx
        db 072h, 013h   ; jb 0x349076
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E9h, 004h   ; shr ecx, 4
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 089h, 04Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ecx
        db 083h, 0C7h, 0FCh   ; add edi, -4
        db 0EBh, 023h   ; jmp 0x349099
$L_349076:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0D6h   ; mov edx, esi
        db 0D3h, 0E2h   ; shl edx, cl
        db 00Bh, 055h, 0F0h   ; or edx, dword ptr [ebp - 0x10]
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0EEh   ; shr esi, cl
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 083h, 0C7h, 01Ch   ; add edi, 0x1c
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 089h, 075h, 00Ch   ; mov dword ptr [ebp + 0xc], esi
        db 089h, 05Dh, 024h   ; mov dword ptr [ebp + 0x24], ebx
$L_349099:
        db 08Bh, 04Dh, 0E8h   ; mov ecx, dword ptr [ebp - 0x18]
        db 0C1h, 0E2h, 006h   ; shl edx, 6
        db 081h, 0C2h   ; add edx, 0x3f0fc8
        dd _patterns
        db 08Bh, 0DAh   ; mov ebx, edx
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 0D1h, 0E9h   ; shr ecx, 1
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 0C6h, 004h, 011h, 001h   ; mov byte ptr [ecx + edx], 1
        db 033h, 0F6h   ; xor esi, esi
$L_3490b5:
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 016h   ; je 0x3490d2
        db 08Bh, 055h, 00Ch   ; mov edx, dword ptr [ebp + 0xc]
        db 08Bh, 0CAh   ; mov ecx, edx
        db 0D1h, 0EAh   ; shr edx, 1
        db 089h, 055h, 00Ch   ; mov dword ptr [ebp + 0xc], edx
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 083h, 0E1h, 001h   ; and ecx, 1
        db 04Ah   ; dec edx
        db 089h, 055h, 020h   ; mov dword ptr [ebp + 0x20], edx
        db 0EBh, 01Ch   ; jmp 0x3490ee
$L_3490d2:
        db 08Bh, 055h, 024h   ; mov edx, dword ptr [ebp + 0x24]
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 083h, 0C2h, 004h   ; add edx, 4
        db 0D1h, 0EFh   ; shr edi, 1
        db 089h, 055h, 024h   ; mov dword ptr [ebp + 0x24], edx
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 0C7h, 045h, 020h, 01Fh, 000h, 000h, 000h   ; mov dword ptr [ebp + 0x20], 0x1f
        db 083h, 0E1h, 001h   ; and ecx, 1
$L_3490ee:
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 02Fh   ; je 0x349121
        db 08Ah, 010h   ; mov dl, byte ptr [eax]
        db 08Bh, 0BDh, 030h, 0FFh, 0FFh, 0FFh   ; mov edi, dword ptr [ebp - 0xd0]
        db 040h   ; inc eax
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B6h, 00Fh   ; movzx ecx, byte ptr [edi]
        db 041h   ; inc ecx
        db 047h   ; inc edi
        db 085h, 0C9h   ; test ecx, ecx
        db 089h, 0BDh, 030h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd0], edi
        db 074h, 044h   ; je 0x349151
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_349110:
        db 00Fh, 0B6h, 03Ch, 01Eh   ; movzx edi, byte ptr [esi + ebx]
        db 046h   ; inc esi
        db 049h   ; dec ecx
        db 088h, 094h, 03Dh, 090h, 0FEh, 0FFh, 0FFh   ; mov byte ptr [ebp + edi - 0x170], dl
        db 075h, 0F1h   ; jne 0x349110
        db 0EBh, 030h   ; jmp 0x349151
$L_349121:
        db 08Bh, 095h, 030h, 0FFh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0xd0]
        db 00Fh, 0B6h, 00Ah   ; movzx ecx, byte ptr [edx]
        db 041h   ; inc ecx
        db 042h   ; inc edx
        db 085h, 0C9h   ; test ecx, ecx
        db 089h, 095h, 030h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0xd0], edx
        db 074h, 01Bh   ; je 0x349151
$L_349136:
        db 00Fh, 0B6h, 014h, 01Eh   ; movzx edx, byte ptr [esi + ebx]
        db 089h, 05Dh, 0A0h   ; mov dword ptr [ebp - 0x60], ebx
        db 08Ah, 018h   ; mov bl, byte ptr [eax]
        db 046h   ; inc esi
        db 040h   ; inc eax
        db 049h   ; dec ecx
        db 088h, 09Ch, 015h, 090h, 0FEh, 0FFh, 0FFh   ; mov byte ptr [ebp + edx - 0x170], bl
        db 08Bh, 05Dh, 0A0h   ; mov ebx, dword ptr [ebp - 0x60]
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 075h, 0E5h   ; jne 0x349136
$L_349151:
        db 083h, 0FEh, 03Fh   ; cmp esi, 0x3f
        db 00Fh, 08Ch, 05Bh, 0FFh, 0FFh, 0FFh   ; jl 0x3490b5
        db 075h, 011h   ; jne 0x34916d
        db 08Ah, 010h   ; mov dl, byte ptr [eax]
        db 00Fh, 0B6h, 04Bh, 03Fh   ; movzx ecx, byte ptr [ebx + 0x3f]
        db 040h   ; inc eax
        db 088h, 094h, 00Dh, 090h, 0FEh, 0FFh, 0FFh   ; mov byte ptr [ebp + ecx - 0x170], dl
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
$L_34916d:
        db 056h   ; push esi
        db 057h   ; push edi
        db 053h   ; push ebx
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 075h, 018h   ; mov esi, dword ptr [ebp + 0x18]
        db 08Bh, 085h, 090h, 0FEh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x170]
        db 08Bh, 09Dh, 094h, 0FEh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x16c]
        db 08Bh, 08Dh, 098h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x168]
        db 08Bh, 095h, 09Ch, 0FEh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0x164]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 054h, 037h, 004h   ; mov dword ptr [edi + esi + 4], edx
        db 08Dh, 03Ch, 077h   ; lea edi, [edi + esi*2]
        db 08Bh, 085h, 0A0h, 0FEh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x160]
        db 08Bh, 09Dh, 0A4h, 0FEh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x15c]
        db 08Bh, 08Dh, 0A8h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x158]
        db 08Bh, 095h, 0ACh, 0FEh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0x154]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 054h, 037h, 004h   ; mov dword ptr [edi + esi + 4], edx
        db 08Dh, 03Ch, 077h   ; lea edi, [edi + esi*2]
        db 08Bh, 085h, 0B0h, 0FEh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x150]
        db 08Bh, 09Dh, 0B4h, 0FEh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x14c]
        db 08Bh, 08Dh, 0B8h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x148]
        db 08Bh, 095h, 0BCh, 0FEh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0x144]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 054h, 037h, 004h   ; mov dword ptr [edi + esi + 4], edx
        db 08Dh, 03Ch, 077h   ; lea edi, [edi + esi*2]
        db 08Bh, 085h, 0C0h, 0FEh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x140]
        db 08Bh, 09Dh, 0C4h, 0FEh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x13c]
        db 08Bh, 08Dh, 0C8h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x138]
        db 08Bh, 095h, 0CCh, 0FEh, 0FFh, 0FFh   ; mov edx, dword ptr [ebp - 0x134]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 054h, 037h, 004h   ; mov dword ptr [edi + esi + 4], edx
        db 05Bh   ; pop ebx
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 045h, 024h   ; mov eax, dword ptr [ebp + 0x24]
        db 08Bh, 04Dh, 00Ch   ; mov ecx, dword ptr [ebp + 0xc]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
        db 089h, 055h, 0F8h   ; mov dword ptr [ebp - 8], edx
        db 0E9h, 0CBh, 0FDh, 0FFh, 0FFh   ; jmp 0x348ff4
$L_349229:
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Bh, 05Dh, 0E4h   ; mov ebx, dword ptr [ebp - 0x1c]
        db 0D1h, 0E8h   ; shr eax, 1
        db 0C6h, 004h, 008h, 001h   ; mov byte ptr [eax + ecx], 1
        db 08Bh, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x130]
        db 00Fh, 0BEh, 011h   ; movsx edx, byte ptr [ecx]
        db 08Bh, 085h, 000h, 0FFh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x100]
        db 00Fh, 0AFh, 0D6h   ; imul edx, esi
        db 00Fh, 0BEh, 030h   ; movsx esi, byte ptr [eax]
        db 003h, 0D3h   ; add edx, ebx
        db 003h, 0F2h   ; add esi, edx
        db 040h   ; inc eax
        db 041h   ; inc ecx
        db 089h, 075h, 020h   ; mov dword ptr [ebp + 0x20], esi
        db 089h, 085h, 000h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x100], eax
        db 089h, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x130], ecx
        db 056h   ; push esi
        db 057h   ; push edi
        db 053h   ; push ebx
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 08Bh, 07Dh, 018h   ; mov edi, dword ptr [ebp + 0x18]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 08Dh, 034h, 07Eh   ; lea esi, [esi + edi*2]
        db 089h, 085h, 090h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x170], eax
        db 089h, 09Dh, 094h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x16c], ebx
        db 089h, 08Dh, 098h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x168], ecx
        db 089h, 095h, 09Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x164], edx
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 08Dh, 034h, 07Eh   ; lea esi, [esi + edi*2]
        db 089h, 085h, 0A0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x160], eax
        db 089h, 09Dh, 0A4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x15c], ebx
        db 089h, 08Dh, 0A8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x158], ecx
        db 089h, 095h, 0ACh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x154], edx
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 08Dh, 034h, 07Eh   ; lea esi, [esi + edi*2]
        db 089h, 085h, 0B0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x150], eax
        db 089h, 09Dh, 0B4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x14c], ebx
        db 089h, 08Dh, 0B8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x148], ecx
        db 089h, 095h, 0BCh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x144], edx
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 089h, 085h, 0C0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x140], eax
        db 089h, 09Dh, 0C4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x13c], ebx
        db 089h, 08Dh, 0C8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x138], ecx
        db 089h, 095h, 0CCh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x134], edx
        db 05Bh   ; pop ebx
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 075h, 0F8h   ; mov esi, dword ptr [ebp - 8]
        db 083h, 0FEh, 007h   ; cmp esi, 7
        db 072h, 013h   ; jb 0x349322
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 007h   ; shr ecx, 7
        db 083h, 0E0h, 07Fh   ; and eax, 0x7f
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
        db 083h, 0EEh, 007h   ; sub esi, 7
        db 0EBh, 028h   ; jmp 0x34934a
$L_349322:
        db 08Bh, 07Dh, 0F4h   ; mov edi, dword ptr [ebp - 0xc]
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 05Dh, 0F0h   ; mov ebx, dword ptr [ebp - 0x10]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 08Bh, 0C2h   ; mov eax, edx
        db 0D3h, 0E0h   ; shl eax, cl
        db 0B9h, 007h, 000h, 000h, 000h   ; mov ecx, 7
        db 02Bh, 0CEh   ; sub ecx, esi
        db 0D3h, 0EAh   ; shr edx, cl
        db 00Bh, 0C3h   ; or eax, ebx
        db 083h, 0E0h, 07Fh   ; and eax, 0x7f
        db 083h, 0C6h, 019h   ; add esi, 0x19
        db 083h, 0C7h, 004h   ; add edi, 4
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 089h, 07Dh, 0F4h   ; mov dword ptr [ebp - 0xc], edi
$L_34934a:
        db 08Dh, 08Dh, 090h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x170]
        db 051h   ; push ecx
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 052h   ; push edx
        db 050h   ; push eax
        db 051h   ; push ecx
        db 089h, 075h, 0F8h   ; mov dword ptr [ebp - 8], esi
        call _ReadBPLossyWithMotion@20   ; 0x34DCB0
        db 0E9h, 089h, 0FCh, 0FFh, 0FFh   ; jmp 0x348ff4
$L_34936b:
        db 08Bh, 055h, 0E8h   ; mov edx, dword ptr [ebp - 0x18]
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 0D1h, 0EAh   ; shr edx, 1
        db 0C6h, 004h, 002h, 001h   ; mov byte ptr [edx + eax], 1
        db 08Bh, 085h, 000h, 0FEh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x200]
        db 066h, 08Bh, 008h   ; mov cx, word ptr [eax]
        db 083h, 0C0h, 002h   ; add eax, 2
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 089h, 085h, 000h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x200], eax
        db 052h   ; push edx
        db 08Dh, 085h, 050h, 0FDh, 0FFh, 0FFh   ; lea eax, [ebp - 0x2b0]
        db 050h   ; push eax
        db 066h, 089h, 08Dh, 050h, 0FDh, 0FFh, 0FFh   ; mov word ptr [ebp - 0x2b0], cx
        call _ReadBPLossless@8   ; 0x34CEC0
        db 08Bh, 07Dh, 0F8h   ; mov edi, dword ptr [ebp - 8]
        db 083h, 0FFh, 004h   ; cmp edi, 4
        db 072h, 013h   ; jb 0x3493bb
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 004h   ; shr ecx, 4
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
        db 083h, 0EFh, 004h   ; sub edi, 4
        db 0EBh, 026h   ; jmp 0x3493e1
$L_3493bb:
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 08Bh, 013h   ; mov edx, dword ptr [ebx]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0C2h   ; mov eax, edx
        db 0D3h, 0E0h   ; shl eax, cl
        db 00Bh, 045h, 0F0h   ; or eax, dword ptr [ebp - 0x10]
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 0CFh   ; sub ecx, edi
        db 0D3h, 0EAh   ; shr edx, cl
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 083h, 0C7h, 01Ch   ; add edi, 0x1c
        db 083h, 0C3h, 004h   ; add ebx, 4
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 089h, 05Dh, 0F4h   ; mov dword ptr [ebp - 0xc], ebx
$L_3493e1:
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 08Dh, 08Dh, 050h, 0FDh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x2b0]
        db 051h   ; push ecx
        db 056h   ; push esi
        db 052h   ; push edx
        db 089h, 07Dh, 0F8h   ; mov dword ptr [ebp - 8], edi
        call _FastIDCT8x8@16   ; 0x34CAD0
        db 0E9h, 0FCh, 0FBh, 0FFh, 0FFh   ; jmp 0x348ff7
$L_3493fb:
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 08Bh, 055h, 0E8h   ; mov edx, dword ptr [ebp - 0x18]
        db 08Bh, 07Dh, 0ECh   ; mov edi, dword ptr [ebp - 0x14]
        db 0D1h, 0EAh   ; shr edx, 1
        db 0C6h, 004h, 03Ah, 001h   ; mov byte ptr [edx + edi], 1
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0CAh   ; or ecx, edx
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E2h, 010h   ; shl edx, 0x10
        db 040h   ; inc eax
        db 00Bh, 0CAh   ; or ecx, edx
        db 089h, 00Fh   ; mov dword ptr [edi], ecx
        db 089h, 04Fh, 004h   ; mov dword ptr [edi + 4], ecx
        db 089h, 00Ch, 037h   ; mov dword ptr [edi + esi], ecx
        db 089h, 04Ch, 037h, 004h   ; mov dword ptr [edi + esi + 4], ecx
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 08Dh, 014h, 037h   ; lea edx, [edi + esi]
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 089h, 04Ah, 004h   ; mov dword ptr [edx + 4], ecx
        db 08Dh, 03Ch, 032h   ; lea edi, [edx + esi]
        db 089h, 00Fh   ; mov dword ptr [edi], ecx
        db 089h, 04Fh, 004h   ; mov dword ptr [edi + 4], ecx
        db 08Dh, 01Ch, 037h   ; lea ebx, [edi + esi]
        db 08Dh, 014h, 033h   ; lea edx, [ebx + esi]
        db 089h, 00Bh   ; mov dword ptr [ebx], ecx
        db 089h, 04Bh, 004h   ; mov dword ptr [ebx + 4], ecx
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 089h, 04Ah, 004h   ; mov dword ptr [edx + 4], ecx
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 089h, 00Ch, 032h   ; mov dword ptr [edx + esi], ecx
        db 089h, 04Ch, 032h, 004h   ; mov dword ptr [edx + esi + 4], ecx
        db 0E9h, 096h, 0FBh, 0FFh, 0FFh   ; jmp 0x348ffa
$L_349464:
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Bh, 05Dh, 0E4h   ; mov ebx, dword ptr [ebp - 0x1c]
        db 0D1h, 0E8h   ; shr eax, 1
        db 0C6h, 004h, 008h, 001h   ; mov byte ptr [eax + ecx], 1
        db 08Bh, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0x130]
        db 00Fh, 0BEh, 011h   ; movsx edx, byte ptr [ecx]
        db 08Bh, 085h, 000h, 0FFh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x100]
        db 00Fh, 0AFh, 0D6h   ; imul edx, esi
        db 00Fh, 0BEh, 030h   ; movsx esi, byte ptr [eax]
        db 003h, 0D3h   ; add edx, ebx
        db 003h, 0F2h   ; add esi, edx
        db 040h   ; inc eax
        db 041h   ; inc ecx
        db 089h, 075h, 020h   ; mov dword ptr [ebp + 0x20], esi
        db 089h, 085h, 000h, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x100], eax
        db 089h, 08Dh, 0D0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x130], ecx
        db 056h   ; push esi
        db 057h   ; push edi
        db 053h   ; push ebx
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 08Bh, 07Dh, 018h   ; mov edi, dword ptr [ebp + 0x18]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 08Dh, 034h, 07Eh   ; lea esi, [esi + edi*2]
        db 089h, 085h, 090h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x170], eax
        db 089h, 09Dh, 094h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x16c], ebx
        db 089h, 08Dh, 098h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x168], ecx
        db 089h, 095h, 09Ch, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x164], edx
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 08Dh, 034h, 07Eh   ; lea esi, [esi + edi*2]
        db 089h, 085h, 0A0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x160], eax
        db 089h, 09Dh, 0A4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x15c], ebx
        db 089h, 08Dh, 0A8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x158], ecx
        db 089h, 095h, 0ACh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x154], edx
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 08Dh, 034h, 07Eh   ; lea esi, [esi + edi*2]
        db 089h, 085h, 0B0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x150], eax
        db 089h, 09Dh, 0B4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x14c], ebx
        db 089h, 08Dh, 0B8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x148], ecx
        db 089h, 095h, 0BCh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x144], edx
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 03Eh   ; mov ecx, dword ptr [esi + edi]
        db 08Bh, 054h, 03Eh, 004h   ; mov edx, dword ptr [esi + edi + 4]
        db 089h, 085h, 0C0h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x140], eax
        db 089h, 09Dh, 0C4h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x13c], ebx
        db 089h, 08Dh, 0C8h, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x138], ecx
        db 089h, 095h, 0CCh, 0FEh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x134], edx
        db 05Bh   ; pop ebx
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 085h, 0D0h, 0FDh, 0FFh, 0FFh   ; mov eax, dword ptr [ebp - 0x230]
        db 066h, 08Bh, 008h   ; mov cx, word ptr [eax]
        db 083h, 0C0h, 002h   ; add eax, 2
        db 08Dh, 055h, 0F0h   ; lea edx, [ebp - 0x10]
        db 089h, 085h, 0D0h, 0FDh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x230], eax
        db 052h   ; push edx
        db 08Dh, 085h, 050h, 0FDh, 0FFh, 0FFh   ; lea eax, [ebp - 0x2b0]
        db 050h   ; push eax
        db 066h, 089h, 08Dh, 050h, 0FDh, 0FFh, 0FFh   ; mov word ptr [ebp - 0x2b0], cx
        call _ReadBPLossless@8   ; 0x34CEC0
        db 08Bh, 055h, 0F8h   ; mov edx, dword ptr [ebp - 8]
        db 083h, 0FAh, 004h   ; cmp edx, 4
        db 072h, 013h   ; jb 0x349586
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 004h   ; shr ecx, 4
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
        db 083h, 0EAh, 004h   ; sub edx, 4
        db 0EBh, 028h   ; jmp 0x3495ae
$L_349586:
        db 08Bh, 07Dh, 0F4h   ; mov edi, dword ptr [ebp - 0xc]
        db 08Bh, 037h   ; mov esi, dword ptr [edi]
        db 08Bh, 05Dh, 0F0h   ; mov ebx, dword ptr [ebp - 0x10]
        db 08Bh, 0CAh   ; mov ecx, edx
        db 08Bh, 0C6h   ; mov eax, esi
        db 0D3h, 0E0h   ; shl eax, cl
        db 0B9h, 004h, 000h, 000h, 000h   ; mov ecx, 4
        db 02Bh, 0CAh   ; sub ecx, edx
        db 0D3h, 0EEh   ; shr esi, cl
        db 00Bh, 0C3h   ; or eax, ebx
        db 083h, 0E0h, 00Fh   ; and eax, 0xf
        db 083h, 0C2h, 01Ch   ; add edx, 0x1c
        db 083h, 0C7h, 004h   ; add edi, 4
        db 089h, 075h, 0F0h   ; mov dword ptr [ebp - 0x10], esi
        db 089h, 07Dh, 0F4h   ; mov dword ptr [ebp - 0xc], edi
$L_3495ae:
        db 08Dh, 08Dh, 090h, 0FEh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x170]
        db 051h   ; push ecx
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 089h, 055h, 0F8h   ; mov dword ptr [ebp - 8], edx
        db 08Dh, 095h, 050h, 0FDh, 0FFh, 0FFh   ; lea edx, [ebp - 0x2b0]
        db 052h   ; push edx
        db 050h   ; push eax
        db 051h   ; push ecx
        call _FastmIDCT8x8WithMotion@20   ; 0x34CB30
        db 0E9h, 022h, 0FAh, 0FFh, 0FFh   ; jmp 0x348ff4
$L_3495d2:
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 08Bh, 07Dh, 0E8h   ; mov edi, dword ptr [ebp - 0x18]
        db 0D1h, 0EFh   ; shr edi, 1
        db 08Bh, 05Dh, 0ECh   ; mov ebx, dword ptr [ebp - 0x14]
        db 040h   ; inc eax
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B6h, 010h   ; movzx edx, byte ptr [eax]
        db 0C6h, 004h, 01Fh, 001h   ; mov byte ptr [edi + ebx], 1
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0CFh   ; or ecx, edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0C1h, 0E7h, 010h   ; shl edi, 0x10
        db 00Bh, 0CFh   ; or ecx, edi
        db 08Bh, 0FAh   ; mov edi, edx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0D7h   ; or edx, edi
        db 040h   ; inc eax
        db 08Bh, 0FAh   ; mov edi, edx
        db 0C1h, 0E7h, 010h   ; shl edi, 0x10
        db 00Bh, 0D7h   ; or edx, edi
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 00Fh, 0B6h, 07Bh, 0FFh   ; movzx edi, byte ptr [ebx - 1]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 0FBh   ; mov edi, ebx
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 089h, 07Bh, 004h   ; mov dword ptr [ebx + 4], edi
        db 08Bh, 0BDh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov edi, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Fh   ; movzx edi, byte ptr [edi]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 0FFh, 085h, 06Ch, 0FFh, 0FFh, 0FFh   ; inc dword ptr [ebp - 0x94]
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 003h, 0DEh   ; add ebx, esi
        db 003h, 0DEh   ; add ebx, esi
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 089h, 01Ch, 037h   ; mov dword ptr [edi + esi], ebx
        db 003h, 0FEh   ; add edi, esi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 003h, 0FEh   ; add edi, esi
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 003h, 0DEh   ; add ebx, esi
        db 089h, 05Dh, 024h   ; mov dword ptr [ebp + 0x24], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 043h   ; inc ebx
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 05Dh, 024h   ; mov ebx, dword ptr [ebp + 0x24]
        db 003h, 0DEh   ; add ebx, esi
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 043h   ; inc ebx
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 003h, 0DEh   ; add ebx, esi
        db 089h, 05Dh, 024h   ; mov dword ptr [ebp + 0x24], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 05Dh, 024h   ; mov ebx, dword ptr [ebp + 0x24]
        db 003h, 0DEh   ; add ebx, esi
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 024h   ; mov edi, dword ptr [ebp + 0x24]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 01Fh   ; mov dword ptr [edi], ebx
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 00Ch   ; mov edi, dword ptr [ebp + 0xc]
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 08Bh, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov ebx, dword ptr [ebp - 0x94]
        db 00Fh, 0B6h, 03Bh   ; movzx edi, byte ptr [ebx]
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 043h   ; inc ebx
        db 089h, 09Dh, 06Ch, 0FFh, 0FFh, 0FFh   ; mov dword ptr [ebp - 0x94], ebx
        db 08Bh, 09Fh   ; mov ebx, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed90]
        dd _mask1
        db 023h, 0F9h   ; and edi, ecx
        db 023h, 0DAh   ; and ebx, edx
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 0FBh   ; mov edi, ebx
        db 08Bh, 05Dh, 00Ch   ; mov ebx, dword ptr [ebp + 0xc]
        db 089h, 03Ch, 033h   ; mov dword ptr [ebx + esi], edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 0C1h, 0EFh, 004h   ; shr edi, 4
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 08Bh, 0BFh   ; mov edi, dword ptr [edi + 0x3eed50]
        dd _mask2
        db 023h, 0FAh   ; and edi, edx
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 08Bh, 092h   ; mov edx, dword ptr [edx + 0x3eed90]
        dd _mask1
        db 023h, 0D1h   ; and edx, ecx
        db 00Bh, 0FAh   ; or edi, edx
        db 089h, 07Ch, 033h, 004h   ; mov dword ptr [ebx + esi + 4], edi
        db 0E9h, 02Dh, 0F7h, 0FFh, 0FFh   ; jmp 0x348ffa
$L_3498cd:
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 0D1h, 0E8h   ; shr eax, 1
        db 0C6h, 004h, 008h, 001h   ; mov byte ptr [eax + ecx], 1
        db 056h   ; push esi
        db 057h   ; push edi
        db 055h   ; push ebp
        db 053h   ; push ebx
        db 08Bh, 075h, 0A4h   ; mov esi, dword ptr [ebp - 0x5c]
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 06Dh, 018h   ; mov ebp, dword ptr [ebp + 0x18]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 08Bh, 04Eh, 008h   ; mov ecx, dword ptr [esi + 8]
        db 08Bh, 056h, 00Ch   ; mov edx, dword ptr [esi + 0xc]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 08Bh, 05Eh, 014h   ; mov ebx, dword ptr [esi + 0x14]
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 08Bh, 056h, 01Ch   ; mov edx, dword ptr [esi + 0x1c]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 05Eh, 024h   ; mov ebx, dword ptr [esi + 0x24]
        db 08Bh, 04Eh, 028h   ; mov ecx, dword ptr [esi + 0x28]
        db 08Bh, 056h, 02Ch   ; mov edx, dword ptr [esi + 0x2c]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 08Dh, 03Ch, 06Fh   ; lea edi, [edi + ebp*2]
        db 08Bh, 046h, 030h   ; mov eax, dword ptr [esi + 0x30]
        db 08Bh, 05Eh, 034h   ; mov ebx, dword ptr [esi + 0x34]
        db 08Bh, 04Eh, 038h   ; mov ecx, dword ptr [esi + 0x38]
        db 08Bh, 056h, 03Ch   ; mov edx, dword ptr [esi + 0x3c]
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 089h, 05Fh, 004h   ; mov dword ptr [edi + 4], ebx
        db 089h, 00Ch, 02Fh   ; mov dword ptr [edi + ebp], ecx
        db 089h, 054h, 02Fh, 004h   ; mov dword ptr [edi + ebp + 4], edx
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 045h, 0A4h   ; mov eax, dword ptr [ebp - 0x5c]
        db 08Bh, 075h, 018h   ; mov esi, dword ptr [ebp + 0x18]
        db 083h, 0C0h, 040h   ; add eax, 0x40
        db 089h, 045h, 0A4h   ; mov dword ptr [ebp - 0x5c], eax
        db 0E9h, 097h, 0F6h, 0FFh, 0FFh   ; jmp 0x348ffa
$L_349963:
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 08Bh, 08Dh, 060h, 0FFh, 0FFh, 0FFh   ; mov ecx, dword ptr [ebp - 0xa0]
        db 003h, 0C1h   ; add eax, ecx
        db 089h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], eax
$L_349971:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 07Dh, 0E4h   ; mov edi, dword ptr [ebp - 0x1c]
        db 08Bh, 04Dh, 014h   ; mov ecx, dword ptr [ebp + 0x14]
        db 003h, 0C3h   ; add eax, ebx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 08Bh, 045h, 0DCh   ; mov eax, dword ptr [ebp - 0x24]
        db 083h, 0C0h, 008h   ; add eax, 8
        db 003h, 0FBh   ; add edi, ebx
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 0C7h, 045h, 0E8h, 000h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x18], 0
        db 089h, 07Dh, 0E4h   ; mov dword ptr [ebp - 0x1c], edi
        db 089h, 045h, 0DCh   ; mov dword ptr [ebp - 0x24], eax
        db 00Fh, 082h, 0F4h, 0E7h, 0FFh, 0FFh   ; jb 0x348190
        db 08Bh, 045h, 0D4h   ; mov eax, dword ptr [ebp - 0x2c]
        db 08Bh, 055h, 028h   ; mov edx, dword ptr [ebp + 0x28]
        db 089h, 002h   ; mov dword ptr [edx], eax
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 08Bh, 0E5h   ; mov esp, ebp
        db 05Dh   ; pop ebp
        db 0C3h   ; ret 
$L_3499ae:
        db 08Bh, 04Dh, 028h   ; mov ecx, dword ptr [ebp + 0x28]
        db 08Bh, 055h, 0D4h   ; mov edx, dword ptr [ebp - 0x2c]
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 089h, 011h   ; mov dword ptr [ecx], edx
        db 05Bh   ; pop ebx
        db 08Bh, 0E5h   ; mov esp, ebp
        db 05Dh   ; pop ebp
        db 0C3h   ; ret 
$L_3499c0:
        dd $L_348260
        dd $L_348306
        dd $L_348f38
        dd $L_349055
        dd $L_349229
        dd $L_34936b
        dd $L_3493fb
        dd $L_349464
        dd $L_3495d2
        dd $L_3498cd
$L_3499e8:
        dd $L_348333
        dd $L_348efa
        dd $L_3486fe
        dd $L_348785
        dd $L_348efa
        dd $L_3488a5
        dd $L_348be3
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
_ExpandPlane ENDP

; // match: _ExpandBink@56 @ 0x00349A10
_ExpandBink@56 PROC PUBLIC
        db 0F7h, 044h, 024h, 038h, 000h, 000h, 010h, 000h   ; test dword ptr [esp + 0x38], 0x100000
        db 053h   ; push ebx
        db 08Bh, 05Ch, 024h, 024h   ; mov ebx, dword ptr [esp + 0x24]
        db 055h   ; push ebp
        db 08Bh, 06Ch, 024h, 03Ch   ; mov ebp, dword ptr [esp + 0x3c]
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 024h   ; mov esi, dword ptr [esp + 0x24]
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 02Ch   ; mov edi, dword ptr [esp + 0x2c]
        db 074h, 04Bh   ; je 0x349a79
        db 0F7h, 0C5h, 000h, 000h, 010h, 000h   ; test ebp, 0x100000
        db 074h, 039h   ; je 0x349a6f
        db 08Bh, 04Ch, 024h, 040h   ; mov ecx, dword ptr [esp + 0x40]
        db 08Dh, 044h, 024h, 048h   ; lea eax, [esp + 0x48]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 03Ch   ; mov eax, dword ptr [esp + 0x3c]
        db 055h   ; push ebp
        db 051h   ; push ecx
        db 06Ah, 001h   ; push 1
        db 053h   ; push ebx
        db 08Dh, 057h, 007h   ; lea edx, [edi + 7]
        db 083h, 0E2h, 0F8h   ; and edx, 0xfffffff8
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        db 08Dh, 04Eh, 007h   ; lea ecx, [esi + 7]
        db 083h, 0E1h, 0F8h   ; and ecx, 0xfffffff8
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 038h   ; mov ecx, dword ptr [esp + 0x38]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 044h   ; mov edx, dword ptr [esp + 0x44]
        db 083h, 0C0h, 004h   ; add eax, 4
        db 051h   ; push ecx
        db 0E8h, 0D4h, 0E0h, 0FFh, 0FFh   ; call 0x347b40
        db 083h, 0C4h, 024h   ; add esp, 0x24
$L_349a6f:
        db 08Bh, 044h, 024h, 038h   ; mov eax, dword ptr [esp + 0x38]
        db 003h, 000h   ; add eax, dword ptr [eax]
        db 089h, 044h, 024h, 038h   ; mov dword ptr [esp + 0x38], eax
$L_349a79:
        db 08Bh, 0C5h   ; mov eax, ebp
        db 025h, 000h, 080h, 000h, 000h   ; and eax, 0x8000
        db 0C7h, 044h, 024h, 048h, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x48], 0
        db 089h, 044h, 024h, 030h   ; mov dword ptr [esp + 0x30], eax
        db 075h, 005h   ; jne 0x349a93
        db 083h, 044h, 024h, 038h, 004h   ; add dword ptr [esp + 0x38], 4
$L_349a93:
        db 08Bh, 044h, 024h, 040h   ; mov eax, dword ptr [esp + 0x40]
        db 08Dh, 054h, 024h, 048h   ; lea edx, [esp + 0x48]
        db 052h   ; push edx
        db 055h   ; push ebp
        db 08Bh, 06Ch, 024h, 01Ch   ; mov ebp, dword ptr [esp + 0x1c]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 024h   ; mov eax, dword ptr [esp + 0x24]
        db 06Ah, 001h   ; push 1
        db 053h   ; push ebx
        db 08Dh, 04Fh, 007h   ; lea ecx, [edi + 7]
        db 083h, 0E1h, 0F8h   ; and ecx, 0xfffffff8
        db 051h   ; push ecx
        db 08Dh, 056h, 007h   ; lea edx, [esi + 7]
        db 083h, 0E2h, 0F8h   ; and edx, 0xfffffff8
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 040h   ; mov edx, dword ptr [esp + 0x40]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 058h   ; mov eax, dword ptr [esp + 0x58]
        db 055h   ; push ebp
        db 0E8h, 07Ah, 0E0h, 0FFh, 0FFh   ; call 0x347b40
        db 08Bh, 04Ch, 024h, 054h   ; mov ecx, dword ptr [esp + 0x54]
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 085h, 0C9h   ; test ecx, ecx
        db 075h, 00Bh   ; jne 0x349adc
        db 08Bh, 044h, 024h, 038h   ; mov eax, dword ptr [esp + 0x38]
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 08Dh, 044h, 001h, 0FCh   ; lea eax, [ecx + eax - 4]
$L_349adc:
        db 08Bh, 04Ch, 024h, 048h   ; mov ecx, dword ptr [esp + 0x48]
        db 08Bh, 054h, 024h, 044h   ; mov edx, dword ptr [esp + 0x44]
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 0F7h, 0C2h, 000h, 000h, 002h, 000h   ; test edx, 0x20000
        db 00Fh, 085h, 097h, 000h, 000h, 000h   ; jne 0x349b8a
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 00Fh, 0AFh, 04Ch, 024h, 034h   ; imul ecx, dword ptr [esp + 0x34]
        db 003h, 0D1h   ; add edx, ecx
        db 089h, 054h, 024h, 018h   ; mov dword ptr [esp + 0x18], edx
        db 08Bh, 054h, 024h, 034h   ; mov edx, dword ptr [esp + 0x34]
        db 003h, 0E9h   ; add ebp, ecx
        db 08Bh, 04Ch, 024h, 044h   ; mov ecx, dword ptr [esp + 0x44]
        db 0D1h, 0EAh   ; shr edx, 1
        db 046h   ; inc esi
        db 089h, 054h, 024h, 034h   ; mov dword ptr [esp + 0x34], edx
        db 0D1h, 0EEh   ; shr esi, 1
        db 08Dh, 054h, 024h, 048h   ; lea edx, [esp + 0x48]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 044h   ; mov edx, dword ptr [esp + 0x44]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 020h   ; mov ecx, dword ptr [esp + 0x20]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 083h, 0C6h, 007h   ; add esi, 7
        db 083h, 0E6h, 0F8h   ; and esi, 0xfffffff8
        db 047h   ; inc edi
        db 06Ah, 002h   ; push 2
        db 0D1h, 0EFh   ; shr edi, 1
        db 083h, 0C7h, 007h   ; add edi, 7
        db 0D1h, 0EBh   ; shr ebx, 1
        db 053h   ; push ebx
        db 083h, 0E7h, 0F8h   ; and edi, 0xfffffff8
        db 057h   ; push edi
        db 056h   ; push esi
        db 051h   ; push ecx
        db 055h   ; push ebp
        db 0E8h, 0F9h, 0DFh, 0FFh, 0FFh   ; call 0x347b40
        db 08Dh, 054h, 024h, 06Ch   ; lea edx, [esp + 0x6c]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 06Ch   ; mov edx, dword ptr [esp + 0x6c]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 06Ch   ; mov edx, dword ptr [esp + 0x6c]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 048h   ; mov edx, dword ptr [esp + 0x48]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 00Fh, 0AFh, 04Ch, 024h, 064h   ; imul ecx, dword ptr [esp + 0x64]
        db 06Ah, 002h   ; push 2
        db 053h   ; push ebx
        db 057h   ; push edi
        db 003h, 0D1h   ; add edx, ecx
        db 056h   ; push esi
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 068h   ; mov edx, dword ptr [esp + 0x68]
        db 003h, 0CDh   ; add ecx, ebp
        db 051h   ; push ecx
        db 0C7h, 084h, 024h, 090h, 000h, 000h, 000h, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x90], 0
        db 0E8h, 0C0h, 0DFh, 0FFh, 0FFh   ; call 0x347b40
        db 08Bh, 08Ch, 024h, 090h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0x90]
        db 083h, 0C4h, 048h   ; add esp, 0x48
$L_349b8a:
        db 0A1h   ; mov eax, dword ptr [0x51ef5c]
        dd _decode_use_MMX
        db 085h, 0C0h   ; test eax, eax
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 074h, 002h   ; je 0x349b99
        db 00Fh, 077h   ; emms 
$L_349b99:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C2h, 038h, 000h   ; ret 0x38
        db 0CCh   ; int3 
        db 0CCh   ; int3 
_ExpandBink@56 ENDP
segep ENDS

        END
