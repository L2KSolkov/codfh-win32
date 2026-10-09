; codfh-match: yuv.obj's blit setup and the per-format blit entry points (the library's yuv.obj, C++)
; Image transcriptions: setup (setevenodd, with checkzoombufs and setdbls), the generic blitter (YUV_blit), init, and the masked
; blitter and six entry points that call the first two in their register conventions (owner,
; 2026-10-04: unmatched Bink may be binarized). The rest is restored in yuv.cpp.

        .686p
        .model flat


EXTERN ?checkrdtsc@@YAXXZ:NEAR
EXTERN ?dorightedge@@YAXXZ:NEAR
EXTERN ?timedbleven@@YGXJ@Z:BYTE
EXTERN ?timedblodd@@YGXJ@Z:BYTE
EXTERN ?zoom2heven@@YGXJ@Z:BYTE
EXTERN ?zoom2hevenbuf@@YGXJ@Z:BYTE
EXTERN ?zoom2hodd@@YGXJ@Z:BYTE
EXTERN ?zoom2hoddbuf@@YGXJ@Z:BYTE
EXTERN _EVEN:BYTE
EXTERN _EVENt:BYTE
EXTERN _EVENx:BYTE
EXTERN _ODD:BYTE
EXTERN _ODDt:BYTE
EXTERN _ODDx:BYTE
EXTERN _RGBshift:BYTE
EXTERN _S:BYTE
EXTERN _YUVTables:BYTE
EXTERN _align:BYTE
EXTERN _alignm1:BYTE
EXTERN _alignshift:BYTE
EXTERN _alnaddr:BYTE
EXTERN _blits16:BYTE
EXTERN _blits16a1:BYTE
EXTERN _blits16a4:BYTE
EXTERN _blits32:BYTE
EXTERN _blits32a:BYTE
EXTERN _blitsyuy2:BYTE
EXTERN _check_for_MMX:NEAR
EXTERN _clamp_b:BYTE
EXTERN _clamp_g:BYTE
EXTERN _clamp_r:BYTE
EXTERN _clamp_ytable:BYTE
EXTERN _dbltimeaddr:BYTE
EXTERN _decode_use_MMX:BYTE
EXTERN _dounalignedcol:BYTE
EXTERN _dounalignedrow:BYTE
EXTERN _lastleft:BYTE
EXTERN _mono16:BYTE
EXTERN _mono32:BYTE
EXTERN _pmemw7F00m:BYTE
EXTERN _pmemwRGB:BYTE
EXTERN _pmemwYscalem:BYTE
EXTERN _radfree@4:NEAR
EXTERN _radmalloc@4:NEAR
EXTERN _rdtscavail:BYTE
EXTERN _testing:BYTE
EXTERN _unk_4311D4:BYTE
EXTERN _unk_4311DC:BYTE
EXTERN _unk_4311E4:BYTE
EXTERN _ytable_x4:BYTE
EXTERN _clamp_rr:BYTE
EXTERN _clamp_gg:BYTE
EXTERN _clamp_bb:BYTE
EXTERN _clamp32:BYTE
EXTERN _mono16x2:BYTE
EXTERN _unk_5388D0:BYTE
EXTERN _unk_5388D4:BYTE
EXTERN _unk_5388E4:BYTE
EXTERN _whichyuv:BYTE
EXTERN _z2hbuf1:BYTE
EXTERN _z2hbuf2:BYTE
EXTERN _z2hsize:BYTE


segcz SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: ?checkzoombufs@@YAXK@Z @ 0x0034A2B0
; // sp-match: ?checkzoombufs@@YAXK@Z @ 0x0025A2B0
?checkzoombufs@@YAXK@Z PROC PUBLIC
        db 056h   ; push esi
        db 08Bh, 0F0h   ; mov esi, eax
        db 0A1h   ; mov eax, dword ptr [0x5388d8]
        dd _z2hsize
        db 083h, 0C6h, 01Fh   ; add esi, 0x1f
        db 083h, 0E6h, 0E0h   ; and esi, 0xffffffe0
        db 057h   ; push edi
        db 08Dh, 03Ch, 036h   ; lea edi, [esi + esi]
        db 03Bh, 0F8h   ; cmp edi, eax
        db 0A1h   ; mov eax, dword ptr [0x5388dc]
        dd _z2hbuf1
        db 076h, 025h   ; jbe 0x34a2f0
        db 085h, 0C0h   ; test eax, eax
        db 074h, 010h   ; je 0x34a2df
        db 050h   ; push eax
        call _radfree@4   ; 0x258D00
        db 0C7h, 005h   ; mov dword ptr [0x5388dc], 0
        dd _z2hbuf1
        db 000h, 000h, 000h, 000h
$L_34a2df:
        db 057h   ; push edi
        call _radmalloc@4   ; 0x258C90
        db 0A3h   ; mov dword ptr [0x5388dc], eax
        dd _z2hbuf1
        db 089h, 03Dh   ; mov dword ptr [0x5388d8], edi
        dd _z2hsize
$L_34a2f0:
        db 003h, 0C6h   ; add eax, esi
        db 05Fh   ; pop edi
        db 0A3h   ; mov dword ptr [0x5388e0], eax
        dd _z2hbuf2
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
?checkzoombufs@@YAXK@Z ENDP

segcz ENDS

seg1 SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'


; // match: ?setdbls@@YAXPAKK@Z @ 0x0034A7B0
; // sp-match: ?setdbls@@YAXPAKK@Z @ 0x0025A7B0
?setdbls@@YAXPAKK@Z PROC PUBLIC
        db 0A1h   ; mov eax, dword ptr [0x5388c8]
        dd _rdtscavail
        db 0BAh, 001h, 000h, 000h, 000h   ; mov edx, 1
        db 03Bh, 0C2h   ; cmp eax, edx
        db 075h, 01Ah   ; jne 0x34a7d8
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 084h, 0C2h   ; test dl, al
        db 074h, 03Eh   ; je 0x34a802
        db 03Dh, 000h, 020h, 000h, 000h   ; cmp eax, 0x2000
        db 077h, 037h   ; ja 0x34a802
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Dh, 004h, 090h   ; lea eax, [eax + edx*4]
        db 0A8h, 002h   ; test al, 2
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 074h, 015h   ; je 0x34a7ed
$L_34a7d8:
        db 0C7h, 005h   ; mov dword ptr [0x508280], 0x34a4d0
        dd _EVEN
        dd ?zoom2hevenbuf@@YGXJ@Z
        db 0C7h, 005h   ; mov dword ptr [0x508258], 0x34a590
        dd _ODD
        dd ?zoom2hoddbuf@@YGXJ@Z
        db 0C3h   ; ret 
$L_34a7ed:
        db 0C7h, 005h   ; mov dword ptr [0x508280], 0x34a330
        dd _EVEN
        dd ?zoom2heven@@YGXJ@Z
        db 0C7h, 005h   ; mov dword ptr [0x508258], 0x34a400
        dd _ODD
        dd ?zoom2hodd@@YGXJ@Z
        db 0C3h   ; ret 
$L_34a802:
        db 0C7h, 005h   ; mov dword ptr [0x508280], 0x34a730
        dd _EVEN
        dd ?timedbleven@@YGXJ@Z
        db 0C7h, 005h   ; mov dword ptr [0x508258], 0x34a770
        dd _ODD
        dd ?timedblodd@@YGXJ@Z
        db 089h, 00Dh   ; mov dword ptr [0x50828c], ecx
        dd _dbltimeaddr
        db 0C7h, 001h, 082h, 000h, 000h, 000h   ; mov dword ptr [ecx], 0x82
        db 0C7h, 005h   ; mov dword ptr [0x508264], 0x34a330
        dd _EVENt
        dd ?zoom2heven@@YGXJ@Z
        db 0C7h, 005h   ; mov dword ptr [0x508270], 0x34a400
        dd _ODDt
        dd ?zoom2hodd@@YGXJ@Z
        db 089h, 015h   ; mov dword ptr [0x508278], edx
        dd _testing
        db 0C3h   ; ret 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
?setdbls@@YAXPAKK@Z ENDP

; // match: ?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z @ 0x0034A840
; // sp-match: ?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z @ 0x0025A840
?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z PROC PUBLIC
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 055h   ; push ebp
        db 08Bh, 06Ch, 024h, 008h   ; mov ebp, dword ptr [esp + 8]
        db 056h   ; push esi
        db 08Bh, 0F0h   ; mov esi, eax
        db 033h, 0C0h   ; xor eax, eax
        db 0F7h, 0C3h, 000h, 000h, 001h, 000h   ; test ebx, 0x10000
        db 089h, 00Dh   ; mov dword ptr [0x536890], ecx
        dd _S+020h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388cc]
        dd _whichyuv
        db 0A3h   ; mov dword ptr [0x508278], eax
        dd _testing
        db 00Fh, 084h, 094h, 000h, 000h, 000h   ; je 0x34a8fd
        db 0B8h, 001h, 000h, 000h, 000h   ; mov eax, 1
        db 03Bh, 0C8h   ; cmp ecx, eax
        db 00Fh, 084h, 0DAh, 000h, 000h, 000h   ; je 0x34a950
        db 0A3h   ; mov dword ptr [0x5388cc], eax
        dd _whichyuv
        db 0B8h   ; mov eax, 0x537498
        dd _YUVTables+0C00h
        db 0BAh, 000h, 001h, 000h, 000h   ; mov edx, 0x100
$L_34a885:
        db 08Bh, 0A8h, 000h, 0F4h, 0FFh, 0FFh   ; mov ebp, dword ptr [eax - 0xc00]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 028h   ; mov dword ptr [eax], ebp
        db 089h, 088h, 000h, 0F4h, 0FFh, 0FFh   ; mov dword ptr [eax - 0xc00], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 04Ah   ; dec edx
        db 075h, 0EAh   ; jne 0x34a885
        db 0B8h   ; mov eax, 0x536c98
        dd _YUVTables+0400h
        db 0BAh, 000h, 001h, 000h, 000h   ; mov edx, 0x100
$L_34a8a5:
        db 08Bh, 0A8h, 000h, 004h, 000h, 000h   ; mov ebp, dword ptr [eax + 0x400]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 028h   ; mov dword ptr [eax], ebp
        db 089h, 088h, 000h, 004h, 000h, 000h   ; mov dword ptr [eax + 0x400], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 04Ah   ; dec edx
        db 075h, 0EAh   ; jne 0x34a8a5
        db 0B8h   ; mov eax, 0x538498
        dd _YUVTables+01C00h
        db 0BAh, 000h, 001h, 000h, 000h   ; mov edx, 0x100
$L_34a8c5:
        db 08Bh, 0A8h, 000h, 0F4h, 0FFh, 0FFh   ; mov ebp, dword ptr [eax - 0xc00]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 028h   ; mov dword ptr [eax], ebp
        db 089h, 088h, 000h, 0F4h, 0FFh, 0FFh   ; mov dword ptr [eax - 0xc00], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 04Ah   ; dec edx
        db 075h, 0EAh   ; jne 0x34a8c5
        db 0B8h   ; mov eax, 0x537c98
        dd _YUVTables+01400h
        db 0BAh, 000h, 001h, 000h, 000h   ; mov edx, 0x100
$L_34a8e5:
        db 08Bh, 0A8h, 000h, 004h, 000h, 000h   ; mov ebp, dword ptr [eax + 0x400]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 028h   ; mov dword ptr [eax], ebp
        db 089h, 088h, 000h, 004h, 000h, 000h   ; mov dword ptr [eax + 0x400], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 04Ah   ; dec edx
        db 075h, 0EAh   ; jne 0x34a8e5
        db 0EBh, 049h   ; jmp 0x34a946
$L_34a8fd:
        db 03Bh, 0C8h   ; cmp ecx, eax
        db 074h, 04Fh   ; je 0x34a950
        db 0A3h   ; mov dword ptr [0x5388cc], eax
        dd _whichyuv
        db 0B8h   ; mov eax, 0x537498
        dd _YUVTables+0C00h
        db 0BAh, 000h, 001h, 000h, 000h   ; mov edx, 0x100
$L_34a910:
        db 08Bh, 0A8h, 000h, 0F4h, 0FFh, 0FFh   ; mov ebp, dword ptr [eax - 0xc00]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 028h   ; mov dword ptr [eax], ebp
        db 089h, 088h, 000h, 0F4h, 0FFh, 0FFh   ; mov dword ptr [eax - 0xc00], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 04Ah   ; dec edx
        db 075h, 0EAh   ; jne 0x34a910
        db 0B8h   ; mov eax, 0x536c98
        dd _YUVTables+0400h
        db 0BAh, 000h, 001h, 000h, 000h   ; mov edx, 0x100
$L_34a930:
        db 08Bh, 0A8h, 000h, 004h, 000h, 000h   ; mov ebp, dword ptr [eax + 0x400]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 028h   ; mov dword ptr [eax], ebp
        db 089h, 088h, 000h, 004h, 000h, 000h   ; mov dword ptr [eax + 0x400], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 04Ah   ; dec edx
        db 075h, 0EAh   ; jne 0x34a930
$L_34a946:
        db 08Bh, 06Ch, 024h, 00Ch   ; mov ebp, dword ptr [esp + 0xc]
        db 08Dh, 09Bh, 000h, 000h, 000h, 000h   ; lea ebx, [ebx]
$L_34a950:
        db 053h   ; push ebx
        call _check_for_MMX   ; 0x25D910
        db 0A1h   ; mov eax, dword ptr [0x51ef5c]
        dd _decode_use_MMX
        db 083h, 0C4h, 004h   ; add esp, 4
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 0B4h, 002h, 000h, 000h   ; je 0x34ac1a
        db 08Bh, 0C3h   ; mov eax, ebx
        db 025h, 000h, 000h, 000h, 070h   ; and eax, 0x70000000
        db 03Dh, 000h, 000h, 000h, 010h   ; cmp eax, 0x10000000
        db 00Fh, 085h, 0B7h, 000h, 000h, 000h   ; jne 0x34aa2f
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 00Fh, 0AFh, 0C5h   ; imul eax, ebp
        call ?checkzoombufs@@YAXK@Z   ; 0x34A2B0
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 0D1h, 0E0h   ; shl eax, 1
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 08Bh, 016h   ; mov edx, dword ptr [esi]
        db 00Fh, 0AFh, 0D5h   ; imul edx, ebp
        db 02Bh, 0C2h   ; sub eax, edx
        db 0F7h, 0C3h, 000h, 000h, 002h, 000h   ; test ebx, 0x20000
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 074h, 046h   ; je 0x34a9e3
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 08Dh, 056h, 060h   ; lea edx, [esi + 0x60]
        db 050h   ; push eax
        db 08Dh, 04Eh, 040h   ; lea ecx, [esi + 0x40]
        db 089h, 015h   ; mov dword ptr [0x50827c], edx
        dd _alnaddr
        db 0E8h, 0FDh, 0FDh, 0FFh, 0FFh   ; call 0x34a7b0
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 08Eh, 09Ch, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x9c]
        db 08Bh, 096h, 0A0h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xa0]
        db 0A3h   ; mov dword ptr [0x50826c], eax
        dd _EVENx
        db 0A3h   ; mov dword ptr [0x50825c], eax
        dd _ODDx
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 083h, 0C4h, 004h   ; add esp, 4
        db 089h, 00Dh   ; mov dword ptr [0x508288], ecx
        dd _dounalignedrow
        db 089h, 015h   ; mov dword ptr [0x508268], edx
        dd _dounalignedcol
        db 0E9h, 032h, 002h, 000h, 000h   ; jmp 0x34ac15
$L_34a9e3:
        db 08Bh, 054h, 024h, 010h   ; mov edx, dword ptr [esp + 0x10]
        db 08Dh, 04Eh, 058h   ; lea ecx, [esi + 0x58]
        db 089h, 00Dh   ; mov dword ptr [0x50827c], ecx
        dd _alnaddr
        db 052h   ; push edx
        db 08Dh, 04Eh, 038h   ; lea ecx, [esi + 0x38]
        db 0E8h, 0B7h, 0FDh, 0FFh, 0FFh   ; call 0x34a7b0
        db 08Bh, 086h, 094h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0x94]
        db 08Bh, 08Eh, 098h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x98]
        db 08Bh, 056h, 008h   ; mov edx, dword ptr [esi + 8]
        db 0A3h   ; mov dword ptr [0x508288], eax
        dd _dounalignedrow
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 0A3h   ; mov dword ptr [0x50825c], eax
        dd _ODDx
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 08Bh, 076h, 004h   ; mov esi, dword ptr [esi + 4]
        db 083h, 0C4h, 004h   ; add esp, 4
        db 089h, 00Dh   ; mov dword ptr [0x508268], ecx
        dd _dounalignedcol
        db 089h, 015h   ; mov dword ptr [0x50826c], edx
        dd _EVENx
        db 0E9h, 0DCh, 001h, 000h, 000h   ; jmp 0x34ac0b
$L_34aa2f:
        db 03Dh, 000h, 000h, 000h, 030h   ; cmp eax, 0x30000000
        db 00Fh, 084h, 049h, 001h, 000h, 000h   ; je 0x34ab83
        db 03Dh, 000h, 000h, 000h, 050h   ; cmp eax, 0x50000000
        db 00Fh, 084h, 03Eh, 001h, 000h, 000h   ; je 0x34ab83
        db 03Dh, 000h, 000h, 000h, 040h   ; cmp eax, 0x40000000
        db 00Fh, 085h, 0B4h, 000h, 000h, 000h   ; jne 0x34ab04
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 00Fh, 0AFh, 0C5h   ; imul eax, ebp
        db 0D1h, 0E0h   ; shl eax, 1
        call ?checkzoombufs@@YAXK@Z   ; 0x34A2B0
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 0D1h, 0E0h   ; shl eax, 1
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 00Fh, 0AFh, 0CDh   ; imul ecx, ebp
        db 0D1h, 0E1h   ; shl ecx, 1
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0F7h, 0C3h, 000h, 000h, 002h, 000h   ; test ebx, 0x20000
        db 089h, 002h   ; mov dword ptr [edx], eax
        db 074h, 04Ah   ; je 0x34aac3
        db 08Bh, 04Ch, 024h, 010h   ; mov ecx, dword ptr [esp + 0x10]
        db 08Dh, 046h, 070h   ; lea eax, [esi + 0x70]
        db 051h   ; push ecx
        db 08Dh, 04Eh, 050h   ; lea ecx, [esi + 0x50]
        db 0A3h   ; mov dword ptr [0x50827c], eax
        dd _alnaddr
        db 0E8h, 022h, 0FDh, 0FFh, 0FFh   ; call 0x34a7b0
        db 08Bh, 086h, 0B0h, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0xb0]
        db 08Bh, 096h, 0ACh, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xac]
        db 08Bh, 04Eh, 02Ch   ; mov ecx, dword ptr [esi + 0x2c]
        db 0A3h   ; mov dword ptr [0x508268], eax
        dd _dounalignedcol
        db 08Bh, 046h, 030h   ; mov eax, dword ptr [esi + 0x30]
        db 083h, 0C4h, 004h   ; add esp, 4
        db 089h, 015h   ; mov dword ptr [0x508288], edx
        dd _dounalignedrow
        db 0A3h   ; mov dword ptr [0x50826c], eax
        dd _EVENx
        db 0A3h   ; mov dword ptr [0x50825c], eax
        dd _ODDx
        db 089h, 00Dh   ; mov dword ptr [0x508254], ecx
        dd _alignshift
        db 0E9h, 057h, 001h, 000h, 000h   ; jmp 0x34ac1a
$L_34aac3:
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 08Dh, 056h, 068h   ; lea edx, [esi + 0x68]
        db 050h   ; push eax
        db 08Dh, 04Eh, 048h   ; lea ecx, [esi + 0x48]
        db 089h, 015h   ; mov dword ptr [0x50827c], edx
        dd _alnaddr
        db 0E8h, 0D7h, 0FCh, 0FFh, 0FFh   ; call 0x34a7b0
        db 08Bh, 08Eh, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0xa4]
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 096h, 0A8h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0xa8]
        db 089h, 00Dh   ; mov dword ptr [0x508288], ecx
        dd _dounalignedrow
        db 08Bh, 04Eh, 028h   ; mov ecx, dword ptr [esi + 0x28]
        db 083h, 0C4h, 004h   ; add esp, 4
        db 0A3h   ; mov dword ptr [0x50826c], eax
        dd _EVENx
        db 089h, 00Dh   ; mov dword ptr [0x50825c], ecx
        dd _ODDx
        db 0E9h, 0FBh, 000h, 000h, 000h   ; jmp 0x34abff
$L_34ab04:
        db 08Bh, 016h   ; mov edx, dword ptr [esi]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 00Fh, 0AFh, 0D5h   ; imul edx, ebp
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 02Bh, 0C2h   ; sub eax, edx
        db 0F7h, 0C3h, 000h, 000h, 002h, 000h   ; test ebx, 0x20000
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 074h, 038h   ; je 0x34ab53
        db 08Bh, 046h, 07Ch   ; mov eax, dword ptr [esi + 0x7c]
        db 08Bh, 08Eh, 080h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x80]
        db 08Dh, 056h, 060h   ; lea edx, [esi + 0x60]
        db 089h, 015h   ; mov dword ptr [0x50827c], edx
        dd _alnaddr
        db 08Bh, 056h, 014h   ; mov edx, dword ptr [esi + 0x14]
        db 0A3h   ; mov dword ptr [0x508288], eax
        dd _dounalignedrow
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 089h, 00Dh   ; mov dword ptr [0x508268], ecx
        dd _dounalignedcol
        db 0A3h   ; mov dword ptr [0x508280], eax
        dd _EVEN
        db 0A3h   ; mov dword ptr [0x508258], eax
        dd _ODD
        db 089h, 015h   ; mov dword ptr [0x508254], edx
        dd _alignshift
        db 0E9h, 0C7h, 000h, 000h, 000h   ; jmp 0x34ac1a
$L_34ab53:
        db 08Bh, 04Eh, 074h   ; mov ecx, dword ptr [esi + 0x74]
        db 08Bh, 056h, 078h   ; mov edx, dword ptr [esi + 0x78]
        db 08Dh, 046h, 058h   ; lea eax, [esi + 0x58]
        db 0A3h   ; mov dword ptr [0x50827c], eax
        dd _alnaddr
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 089h, 00Dh   ; mov dword ptr [0x508288], ecx
        dd _dounalignedrow
        db 08Bh, 04Eh, 010h   ; mov ecx, dword ptr [esi + 0x10]
        db 0A3h   ; mov dword ptr [0x508280], eax
        dd _EVEN
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 08Bh, 076h, 004h   ; mov esi, dword ptr [esi + 4]
        db 089h, 00Dh   ; mov dword ptr [0x508258], ecx
        dd _ODD
        db 0E9h, 082h, 000h, 000h, 000h   ; jmp 0x34ac05
$L_34ab83:
        db 08Bh, 016h   ; mov edx, dword ptr [esi]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 00Fh, 0AFh, 0D5h   ; imul edx, ebp
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 0D1h, 0E2h   ; shl edx, 1
        db 02Bh, 0C2h   ; sub eax, edx
        db 0F7h, 0C3h, 000h, 000h, 002h, 000h   ; test ebx, 0x20000
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 074h, 038h   ; je 0x34abd4
        db 08Bh, 086h, 08Ch, 000h, 000h, 000h   ; mov eax, dword ptr [esi + 0x8c]
        db 08Bh, 08Eh, 090h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x90]
        db 08Dh, 056h, 070h   ; lea edx, [esi + 0x70]
        db 089h, 015h   ; mov dword ptr [0x50827c], edx
        dd _alnaddr
        db 08Bh, 056h, 02Ch   ; mov edx, dword ptr [esi + 0x2c]
        db 0A3h   ; mov dword ptr [0x508288], eax
        dd _dounalignedrow
        db 08Bh, 046h, 030h   ; mov eax, dword ptr [esi + 0x30]
        db 089h, 00Dh   ; mov dword ptr [0x508268], ecx
        dd _dounalignedcol
        db 0A3h   ; mov dword ptr [0x508280], eax
        dd _EVEN
        db 0A3h   ; mov dword ptr [0x508258], eax
        dd _ODD
        db 089h, 015h   ; mov dword ptr [0x508254], edx
        dd _alignshift
        db 0EBh, 046h   ; jmp 0x34ac1a
$L_34abd4:
        db 08Bh, 08Eh, 084h, 000h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x84]
        db 08Bh, 096h, 088h, 000h, 000h, 000h   ; mov edx, dword ptr [esi + 0x88]
        db 08Dh, 046h, 068h   ; lea eax, [esi + 0x68]
        db 0A3h   ; mov dword ptr [0x50827c], eax
        dd _alnaddr
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 089h, 00Dh   ; mov dword ptr [0x508288], ecx
        dd _dounalignedrow
        db 08Bh, 04Eh, 028h   ; mov ecx, dword ptr [esi + 0x28]
        db 0A3h   ; mov dword ptr [0x508280], eax
        dd _EVEN
        db 089h, 00Dh   ; mov dword ptr [0x508258], ecx
        dd _ODD
$L_34abff:
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Bh, 076h, 01Ch   ; mov esi, dword ptr [esi + 0x1c]
$L_34ac05:
        db 089h, 015h   ; mov dword ptr [0x508268], edx
        dd _dounalignedcol
$L_34ac0b:
        db 03Bh, 0F0h   ; cmp esi, eax
        db 089h, 035h   ; mov dword ptr [0x508254], esi
        dd _alignshift
        db 077h, 005h   ; ja 0x34ac1a
$L_34ac15:
        db 0A3h   ; mov dword ptr [0x508254], eax
        dd _alignshift
$L_34ac1a:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x508254]
        dd _alignshift
        db 0B8h, 001h, 000h, 000h, 000h   ; mov eax, 1
        db 0D3h, 0E0h   ; shl eax, cl
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0A3h   ; mov dword ptr [0x508260], eax
        dd _align
        db 048h   ; dec eax
        db 0A3h   ; mov dword ptr [0x508284], eax
        dd _alignm1
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
?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z ENDP
seg1 ENDS

seg2 SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z @ 0x0034ACD0
; // sp-match: ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z @ 0x0025ACD0
?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z PROC PUBLIC
$L_34acd0:
        db 08Bh, 04Ch, 024h, 02Ch   ; mov ecx, dword ptr [esp + 0x2c]
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 08Bh, 06Ch, 024h, 02Ch   ; mov ebp, dword ptr [esp + 0x2c]
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 034h   ; mov esi, dword ptr [esp + 0x34]
        db 081h, 0E1h, 000h, 000h, 000h, 070h   ; and ecx, 0x70000000
        db 081h, 0F9h, 000h, 000h, 000h, 060h   ; cmp ecx, 0x60000000
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 01Ch   ; mov edi, dword ptr [esp + 0x1c]
        db 075h, 01Fh   ; jne 0x34ad11
        db 08Bh, 044h, 024h, 028h   ; mov eax, dword ptr [esp + 0x28]
        db 08Bh, 05Ch, 024h, 030h   ; mov ebx, dword ptr [esp + 0x30]
        db 0D1h, 0E8h   ; shr eax, 1
        db 089h, 044h, 024h, 028h   ; mov dword ptr [esp + 0x28], eax
        db 0D1h, 0EBh   ; shr ebx, 1
        db 08Dh, 004h, 03Fh   ; lea eax, [edi + edi]
        db 0D1h, 0EEh   ; shr esi, 1
        db 089h, 05Ch, 024h, 030h   ; mov dword ptr [esp + 0x30], ebx
        db 089h, 044h, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], eax
        db 003h, 0EDh   ; add ebp, ebp
$L_34ad11:
        db 08Bh, 044h, 024h, 044h   ; mov eax, dword ptr [esp + 0x44]
        db 089h, 015h   ; mov dword ptr [0x536894], edx
        dd _S+024h
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 083h, 0F8h, 002h   ; cmp eax, 2
        db 075h, 013h   ; jne 0x34ad35
        db 08Bh, 0DAh   ; mov ebx, edx
        db 080h, 0E3h, 003h   ; and bl, 3
        db 03Ah, 0D8h   ; cmp bl, al
        db 075h, 049h   ; jne 0x34ad74
        db 08Bh, 05Ch, 024h, 014h   ; mov ebx, dword ptr [esp + 0x14]
        db 043h   ; inc ebx
        db 083h, 0E2h, 0FCh   ; and edx, 0xfffffffc
        db 0EBh, 03Bh   ; jmp 0x34ad70
$L_34ad35:
        db 083h, 0F8h, 003h   ; cmp eax, 3
        db 075h, 03Ah   ; jne 0x34ad74
        db 08Dh, 05Ah, 001h   ; lea ebx, [edx + 1]
        db 084h, 0D8h   ; test al, bl
        db 075h, 009h   ; jne 0x34ad4a
        db 08Bh, 05Ch, 024h, 014h   ; mov ebx, dword ptr [esp + 0x14]
        db 043h   ; inc ebx
        db 02Bh, 0D0h   ; sub edx, eax
        db 0EBh, 026h   ; jmp 0x34ad70
$L_34ad4a:
        db 08Dh, 05Ah, 0FEh   ; lea ebx, [edx - 2]
        db 0F6h, 0C3h, 003h   ; test bl, 3
        db 075h, 00Ch   ; jne 0x34ad5e
        db 08Bh, 05Ch, 024h, 014h   ; mov ebx, dword ptr [esp + 0x14]
        db 083h, 0C3h, 002h   ; add ebx, 2
        db 083h, 0EAh, 006h   ; sub edx, 6
        db 0EBh, 012h   ; jmp 0x34ad70
$L_34ad5e:
        db 08Dh, 05Ah, 0FFh   ; lea ebx, [edx - 1]
        db 0F6h, 0C3h, 003h   ; test bl, 3
        db 075h, 00Eh   ; jne 0x34ad74
        db 08Bh, 05Ch, 024h, 014h   ; mov ebx, dword ptr [esp + 0x14]
        db 083h, 0C3h, 003h   ; add ebx, 3
        db 083h, 0EAh, 009h   ; sub edx, 9
$L_34ad70:
        db 089h, 05Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], ebx
$L_34ad74:
        db 00Fh, 0AFh, 044h, 024h, 014h   ; imul eax, dword ptr [esp + 0x14]
        db 00Fh, 0AFh, 07Ch, 024h, 018h   ; imul edi, dword ptr [esp + 0x18]
        db 003h, 0C2h   ; add eax, edx
        db 003h, 0F8h   ; add edi, eax
        db 081h, 0F9h, 000h, 000h, 000h, 020h   ; cmp ecx, 0x20000000
        db 089h, 03Dh   ; mov dword ptr [0x536870], edi
        dd _S
        db 074h, 008h   ; je 0x34ad98
        db 081h, 0F9h, 000h, 000h, 000h, 050h   ; cmp ecx, 0x50000000
        db 075h, 00Bh   ; jne 0x34ada3
$L_34ad98:
        db 08Bh, 04Ch, 024h, 01Ch   ; mov ecx, dword ptr [esp + 0x1c]
        db 08Dh, 014h, 009h   ; lea edx, [ecx + ecx]
        db 089h, 054h, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], edx
$L_34ada3:
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 08Bh, 05Ch, 024h, 03Ch   ; mov ebx, dword ptr [esp + 0x3c]
        db 08Dh, 044h, 024h, 018h   ; lea eax, [esp + 0x18]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 048h   ; mov eax, dword ptr [esp + 0x48]
        db 051h   ; push ecx
        db 052h   ; push edx
        db 08Dh, 07Ch, 024h, 028h   ; lea edi, [esp + 0x28]
        call ?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z   ; 0x34A840
        db 08Bh, 04Ch, 024h, 028h   ; mov ecx, dword ptr [esp + 0x28]
        db 0A1h   ; mov eax, dword ptr [0x536870]
        dd _S
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 003h, 0C1h   ; add eax, ecx
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+04h
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 00Fh, 0AFh, 0C5h   ; imul eax, ebp
        db 08Dh, 00Ch, 010h   ; lea ecx, [eax + edx]
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 003h, 0CAh   ; add ecx, edx
        db 08Dh, 03Ch, 029h   ; lea edi, [ecx + ebp]
        db 089h, 03Dh   ; mov dword ptr [0x53687c], edi
        dd _S+0Ch
        db 08Dh, 03Ch, 010h   ; lea edi, [eax + edx]
        db 08Bh, 044h, 024h, 04Ch   ; mov eax, dword ptr [esp + 0x4c]
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        db 003h, 0F8h   ; add edi, eax
        db 08Dh, 004h, 02Fh   ; lea eax, [edi + ebp]
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 0C5h   ; mov eax, ebp
        db 02Bh, 0C2h   ; sub eax, edx
        db 089h, 044h, 024h, 040h   ; mov dword ptr [esp + 0x40], eax
        db 08Bh, 0C5h   ; mov eax, ebp
        db 08Bh, 0DAh   ; mov ebx, edx
        db 0D1h, 0E8h   ; shr eax, 1
        db 0D1h, 0EBh   ; shr ebx, 1
        db 08Bh, 0D0h   ; mov edx, eax
        db 02Bh, 0D3h   ; sub edx, ebx
        db 0B3h, 001h   ; mov bl, 1
        db 083h, 0C4h, 00Ch   ; add esp, 0xc
        db 084h, 05Ch, 024h, 02Ch   ; test byte ptr [esp + 0x2c], bl
        db 089h, 00Dh   ; mov dword ptr [0x536878], ecx
        dd _S+08h
        db 089h, 03Dh   ; mov dword ptr [0x536888], edi
        dd _S+018h
        db 089h, 054h, 024h, 044h   ; mov dword ptr [esp + 0x44], edx
        db 074h, 00Bh   ; je 0x34ae3f
        db 084h, 05Ch, 024h, 024h   ; test byte ptr [esp + 0x24], bl
        db 074h, 005h   ; je 0x34ae3f
        db 04Ah   ; dec edx
        db 089h, 054h, 024h, 044h   ; mov dword ptr [esp + 0x44], edx
$L_34ae3f:
        db 08Bh, 054h, 024h, 03Ch   ; mov edx, dword ptr [esp + 0x3c]
        db 08Bh, 05Ch, 024h, 020h   ; mov ebx, dword ptr [esp + 0x20]
        db 0F7h, 0C2h, 000h, 000h, 001h, 000h   ; test edx, 0x10000
        db 08Bh, 0D5h   ; mov edx, ebp
        db 074h, 014h   ; je 0x34ae65
        db 00Fh, 0AFh, 0D6h   ; imul edx, esi
        db 0D1h, 0EEh   ; shr esi, 1
        db 00Fh, 0AFh, 0F0h   ; imul esi, eax
        db 003h, 0D3h   ; add edx, ebx
        db 003h, 0F2h   ; add esi, edx
        db 089h, 035h   ; mov dword ptr [0x536884], esi
        dd _S+014h
        db 0EBh, 014h   ; jmp 0x34ae79
$L_34ae65:
        db 00Fh, 0AFh, 0D6h   ; imul edx, esi
        db 0D1h, 0EEh   ; shr esi, 1
        db 00Fh, 0AFh, 0F0h   ; imul esi, eax
        db 003h, 0D3h   ; add edx, ebx
        db 003h, 0F2h   ; add esi, edx
        db 089h, 015h   ; mov dword ptr [0x536884], edx
        dd _S+014h
        db 08Bh, 0D6h   ; mov edx, esi
$L_34ae79:
        db 08Bh, 05Ch, 024h, 028h   ; mov ebx, dword ptr [esp + 0x28]
        db 08Bh, 074h, 024h, 024h   ; mov esi, dword ptr [esp + 0x24]
        db 0D1h, 0EBh   ; shr ebx, 1
        db 00Fh, 0AFh, 0D8h   ; imul ebx, eax
        db 08Bh, 0C6h   ; mov eax, esi
        db 0D1h, 0E8h   ; shr eax, 1
        db 003h, 0C3h   ; add eax, ebx
        db 003h, 0D0h   ; add edx, eax
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 015h   ; mov edx, dword ptr [0x536884]
        dd _S+014h
        db 003h, 0D0h   ; add edx, eax
        db 08Bh, 044h, 024h, 03Ch   ; mov eax, dword ptr [esp + 0x3c]
        db 0F6h, 0C4h, 008h   ; test ah, 8
        db 089h, 015h   ; mov dword ptr [0x536884], edx
        dd _S+014h
        db 074h, 022h   ; je 0x34aecd
        db 0A1h   ; mov eax, dword ptr [0x53687c]
        dd _S+0Ch
        db 089h, 00Dh   ; mov dword ptr [0x536888], ecx
        dd _S+018h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x53688c]
        dd _S+01Ch
        db 089h, 03Dh   ; mov dword ptr [0x536878], edi
        dd _S+08h
        db 089h, 00Dh   ; mov dword ptr [0x53687c], ecx
        dd _S+0Ch
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
$L_34aecd:
        db 08Bh, 05Ch, 024h, 028h   ; mov ebx, dword ptr [esp + 0x28]
        db 0F6h, 0C3h, 001h   ; test bl, 1
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 08Dh, 044h, 013h, 0FFh   ; lea eax, [ebx + edx - 1]
        db 089h, 05Ch, 024h, 028h   ; mov dword ptr [esp + 0x28], ebx
        db 089h, 044h, 024h, 020h   ; mov dword ptr [esp + 0x20], eax
        db 00Fh, 084h, 081h, 000h, 000h, 000h   ; je 0x34af6b
        db 03Bh, 0D8h   ; cmp ebx, eax
        db 07Fh, 07Dh   ; jg 0x34af6b
        db 08Bh, 07Ch, 024h, 02Ch   ; mov edi, dword ptr [esp + 0x2c]
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 015h   ; call dword ptr [0x508288]
        dd _dounalignedrow
        db 08Bh, 04Ch, 024h, 03Ch   ; mov ecx, dword ptr [esp + 0x3c]
        db 0A1h   ; mov eax, dword ptr [0x536878]
        dd _S+08h
        db 08Bh, 015h   ; mov edx, dword ptr [0x536884]
        dd _S+014h
        db 003h, 0C1h   ; add eax, ecx
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+08h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+0Ch
        db 0A1h   ; mov eax, dword ptr [0x536888]
        dd _S+018h
        db 003h, 0C1h   ; add eax, ecx
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536880]
        dd _S+010h
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 044h, 024h, 04Ch   ; mov eax, dword ptr [esp + 0x4c]
        db 003h, 0C8h   ; add ecx, eax
        db 003h, 0D0h   ; add edx, eax
        db 0A1h   ; mov eax, dword ptr [0x536870]
        dd _S
        db 089h, 00Dh   ; mov dword ptr [0x536880], ecx
        dd _S+010h
        db 003h, 044h, 024h, 020h   ; add eax, dword ptr [esp + 0x20]
        db 08Bh, 04Ch, 024h, 024h   ; mov ecx, dword ptr [esp + 0x24]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 083h, 0C4h, 008h   ; add esp, 8
        db 043h   ; inc ebx
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+04h
        db 08Bh, 044h, 024h, 020h   ; mov eax, dword ptr [esp + 0x20]
        db 089h, 015h   ; mov dword ptr [0x536884], edx
        dd _S+014h
        db 089h, 05Ch, 024h, 028h   ; mov dword ptr [esp + 0x28], ebx
        db 0EBh, 004h   ; jmp 0x34af6f
$L_34af6b:
        db 08Bh, 07Ch, 024h, 02Ch   ; mov edi, dword ptr [esp + 0x2c]
$L_34af6f:
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 0F7h, 0D9h   ; neg ecx
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 089h, 04Ch, 024h, 03Ch   ; mov dword ptr [esp + 0x3c], ecx
        db 076h, 004h   ; jbe 0x34af84
        db 089h, 07Ch, 024h, 03Ch   ; mov dword ptr [esp + 0x3c], edi
$L_34af84:
        db 08Bh, 0D6h   ; mov edx, esi
        db 083h, 0E2h, 001h   ; and edx, 1
        db 03Bh, 0D7h   ; cmp edx, edi
        db 089h, 054h, 024h, 014h   ; mov dword ptr [esp + 0x14], edx
        db 076h, 006h   ; jbe 0x34af97
        db 089h, 07Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], edi
        db 08Bh, 0D7h   ; mov edx, edi
$L_34af97:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x50827c]
        dd _alnaddr
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 0F6h, 0C3h, 001h   ; test bl, 1
        db 074h, 017h   ; je 0x34afbb
        db 081h, 0FBh, 000h, 020h, 000h, 000h   ; cmp ebx, 0x2000
        db 077h, 013h   ; ja 0x34afbf
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 08Dh, 004h, 083h   ; lea eax, [ebx + eax*4]
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 08Bh, 044h, 024h, 020h   ; mov eax, dword ptr [esp + 0x20]
        db 0EBh, 00Ah   ; jmp 0x34afc5
$L_34afbb:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 006h   ; jne 0x34afc5
$L_34afbf:
        db 0C7h, 001h, 080h, 000h, 000h, 000h   ; mov dword ptr [ecx], 0x80
$L_34afc5:
        db 08Bh, 05Ch, 024h, 028h   ; mov ebx, dword ptr [esp + 0x28]
        db 03Bh, 0D8h   ; cmp ebx, eax
        db 00Fh, 08Dh, 04Fh, 001h, 000h, 000h   ; jge 0x34b120
        db 02Bh, 0C3h   ; sub eax, ebx
        db 048h   ; dec eax
        db 0D1h, 0E8h   ; shr eax, 1
        db 040h   ; inc eax
        db 089h, 044h, 024h, 040h   ; mov dword ptr [esp + 0x40], eax
        db 08Dh, 004h, 043h   ; lea eax, [ebx + eax*2]
        db 089h, 044h, 024h, 028h   ; mov dword ptr [esp + 0x28], eax
        db 0EBh, 00Ch   ; jmp 0x34aff0
$L_34afe4:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x50827c]
        dd _alnaddr
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 08Bh, 0FFh   ; mov edi, edi
$L_34aff0:
        db 0A1h   ; mov eax, dword ptr [0x508278]
        dd _testing
        db 085h, 0C0h   ; test eax, eax
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 089h, 074h, 024h, 030h   ; mov dword ptr [esp + 0x30], esi
        db 075h, 02Ah   ; jne 0x34b029
        db 08Bh, 074h, 024h, 03Ch   ; mov esi, dword ptr [esp + 0x3c]
        db 03Bh, 0F2h   ; cmp esi, edx
        db 074h, 022h   ; je 0x34b029
        db 083h, 03Dh   ; cmp dword ptr [0x5388c8], 1
        dd _rdtscavail
        db 001h
        db 075h, 024h   ; jne 0x34b034
        db 0F6h, 0C3h, 001h   ; test bl, 1
        db 075h, 014h   ; jne 0x34b029
        db 08Bh, 0D3h   ; mov edx, ebx
        db 083h, 0CAh, 004h   ; or edx, 4
        db 089h, 011h   ; mov dword ptr [ecx], edx
        db 0B9h   ; mov ecx, 0x508274
        dd _lastleft
        db 00Fh, 031h   ; rdtsc 
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
$L_34b029:
        db 0F6h, 0C3h, 002h   ; test bl, 2
        db 08Bh, 0F2h   ; mov esi, edx
        db 075h, 004h   ; jne 0x34b034
        db 08Bh, 074h, 024h, 03Ch   ; mov esi, dword ptr [esp + 0x3c]
$L_34b034:
        db 085h, 0F6h   ; test esi, esi
        db 074h, 019h   ; je 0x34b051
        db 08Bh, 044h, 024h, 024h   ; mov eax, dword ptr [esp + 0x24]
        db 050h   ; push eax
        db 056h   ; push esi
        db 0FFh, 015h   ; call dword ptr [0x508268]
        dd _dounalignedcol
        db 08Bh, 07Ch, 024h, 034h   ; mov edi, dword ptr [esp + 0x34]
        db 083h, 0C4h, 008h   ; add esp, 8
        db 089h, 044h, 024h, 030h   ; mov dword ptr [esp + 0x30], eax
        db 02Bh, 0FEh   ; sub edi, esi
$L_34b051:
        db 08Bh, 035h   ; mov esi, dword ptr [0x508284]
        dd _alignm1
        db 0F7h, 0D6h   ; not esi
        db 08Bh, 0DFh   ; mov ebx, edi
        db 0C1h, 0EEh, 002h   ; shr esi, 2
        db 0C1h, 0EFh, 002h   ; shr edi, 2
        db 023h, 0F7h   ; and esi, edi
        db 08Dh, 00Ch, 0B5h, 000h, 000h, 000h, 000h   ; lea ecx, [esi*4]
        db 02Bh, 0D9h   ; sub ebx, ecx
        db 085h, 0F6h   ; test esi, esi
        db 074h, 016h   ; je 0x34b086
        db 0F6h, 044h, 024h, 030h, 001h   ; test byte ptr [esp + 0x30], 1
        db 056h   ; push esi
        db 074h, 008h   ; je 0x34b080
        db 0FFh, 015h   ; call dword ptr [0x508258]
        dd _ODD
        db 0EBh, 006h   ; jmp 0x34b086
$L_34b080:
        db 0FFh, 015h   ; call dword ptr [0x508280]
        dd _EVEN
$L_34b086:
        db 085h, 0DBh   ; test ebx, ebx
        db 074h, 012h   ; je 0x34b09c
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 08Dh, 004h, 0B2h   ; lea eax, [edx + esi*4]
        db 050h   ; push eax
        db 053h   ; push ebx
        db 0FFh, 015h   ; call dword ptr [0x508268]
        dd _dounalignedcol
        db 083h, 0C4h, 008h   ; add esp, 8
$L_34b09c:
        call ?dorightedge@@YAXXZ   ; 0x34AC40
        db 08Bh, 015h   ; mov edx, dword ptr [0x53687c]
        dd _S+0Ch
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 08Dh, 004h, 00Ah   ; lea eax, [edx + ecx]
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+08h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+0Ch
        db 0A1h   ; mov eax, dword ptr [0x53688c]
        dd _S+01Ch
        db 003h, 0C1h   ; add eax, ecx
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536884]
        dd _S+014h
        db 08Bh, 07Ch, 024h, 02Ch   ; mov edi, dword ptr [esp + 0x2c]
        db 08Bh, 074h, 024h, 024h   ; mov esi, dword ptr [esp + 0x24]
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 044h, 024h, 044h   ; mov eax, dword ptr [esp + 0x44]
        db 003h, 0C8h   ; add ecx, eax
        db 003h, 0D0h   ; add edx, eax
        db 089h, 00Dh   ; mov dword ptr [0x536884], ecx
        dd _S+014h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536874]
        dd _S+04h
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 08Dh, 004h, 011h   ; lea eax, [ecx + edx]
        db 08Bh, 04Ch, 024h, 01Ch   ; mov ecx, dword ptr [esp + 0x1c]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+04h
        db 0FFh, 04Ch, 024h, 040h   ; dec dword ptr [esp + 0x40]
        db 00Fh, 085h, 0C8h, 0FEh, 0FFh, 0FFh   ; jne 0x34afe4
        db 08Bh, 044h, 024h, 020h   ; mov eax, dword ptr [esp + 0x20]
$L_34b120:
        db 039h, 044h, 024h, 028h   ; cmp dword ptr [esp + 0x28], eax
        db 07Fh, 00Bh   ; jg 0x34b131
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 015h   ; call dword ptr [0x508288]
        dd _dounalignedrow
        db 083h, 0C4h, 008h   ; add esp, 8
$L_34b131:
        db 0A1h   ; mov eax, dword ptr [0x51ef5c]
        dd _decode_use_MMX
        db 085h, 0C0h   ; test eax, eax
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 074h, 002h   ; je 0x34b140
        db 00Fh, 077h   ; emms 
$L_34b140:
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
        db 0CCh   ; int3 
        db 0CCh   ; int3 
?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z ENDP

seg2 ENDS

seg3 SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: _YUV_init@4 @ 0x0034BB90
; // sp-match: _YUV_init@4 @ 0x0025BB90
_YUV_init@4 PROC PUBLIC
        db 0A1h   ; mov eax, dword ptr [0x5388c8]
        dd _rdtscavail
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 033h, 0DBh   ; xor ebx, ebx
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 075h, 005h   ; jne 0x34bba4
        call ?checkrdtsc@@YAXXZ   ; 0x34BB10
$L_34bba4:
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 08Dh, 041h, 0F9h   ; lea eax, [ecx - 7]
        db 0BAh, 005h, 000h, 000h, 000h   ; mov edx, 5
        db 03Bh, 0C2h   ; cmp eax, edx
        db 00Fh, 087h, 0C1h, 004h, 000h, 000h   ; ja 0x34c079
        db 0FFh, 024h, 085h   ; jmp dword ptr [eax*4 + 0x34c3e0]
        dd $L_34c3e0
$L_34bbbf:
        db 0B8h, 003h, 000h, 000h, 000h   ; mov eax, 3
        db 08Bh, 0E8h   ; mov ebp, eax
        db 0A3h   ; mov dword ptr [0x5388b0], eax
        dd _RGBshift+018h
        db 0A3h   ; mov dword ptr [0x5388c0], eax
        dd _RGBshift+028h
        db 0B8h, 042h, 025h, 042h, 025h   ; mov eax, 0x25422542
        db 0A3h   ; mov dword ptr [0x4311d8], eax
        dd _pmemwYscalem
        db 0A3h   ; mov dword ptr [0x4311dc], eax
        dd _unk_4311DC
        db 0B8h, 0E0h, 07Fh, 0E0h, 07Fh   ; mov eax, 0x7fe07fe0
        db 0A3h   ; mov dword ptr [0x4311e0], eax
        dd _pmemw7F00m
        db 0A3h   ; mov dword ptr [0x4311e4], eax
        dd _unk_4311E4
        db 089h, 01Dh   ; mov dword ptr [0x538898], ebx
        dd _RGBshift
        db 089h, 02Dh   ; mov dword ptr [0x5388b8], ebp
        dd _RGBshift+020h
        db 089h, 015h   ; mov dword ptr [0x5388a0], edx
        dd _RGBshift+08h
        db 0C7h, 005h   ; mov dword ptr [0x5388a8], 0xa
        dd _RGBshift+010h
        db 00Ah, 000h, 000h, 000h
        db 0B8h, 021h, 004h, 021h, 004h   ; mov eax, 0x4210421
$L_34bc0f:
        db 0A3h   ; mov dword ptr [0x4311d0], eax
        dd _pmemwRGB
        db 0A3h   ; mov dword ptr [0x4311d4], eax
        dd _unk_4311D4
        db 0A1h   ; mov eax, dword ptr [0x5388d0]
        dd _unk_5388D0
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 00Fh, 084h, 002h, 005h, 000h, 000h   ; je 0x34c128
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 00Fh, 085h, 008h, 001h, 000h, 000h   ; jne 0x34bd37
        db 033h, 0C0h   ; xor eax, eax
        db 0A3h   ; mov dword ptr [0x52f7c0], eax
        dd _ytable_x4
        db 0A3h   ; mov dword ptr [0x52f7c4], eax
        dd _ytable_x4+04h
        db 0A3h   ; mov dword ptr [0x52f7c8], eax
        dd _ytable_x4+08h
        db 0A3h   ; mov dword ptr [0x52f7cc], eax
        dd _ytable_x4+0Ch
        db 0A3h   ; mov dword ptr [0x52f7d0], eax
        dd _ytable_x4+010h
        db 0A3h   ; mov dword ptr [0x52f7d4], eax
        dd _ytable_x4+014h
        db 0A3h   ; mov dword ptr [0x52f7d8], eax
        dd _ytable_x4+018h
        db 0A3h   ; mov dword ptr [0x52f7dc], eax
        dd _ytable_x4+01Ch
        db 0A3h   ; mov dword ptr [0x52f7e0], eax
        dd _ytable_x4+020h
        db 0A3h   ; mov dword ptr [0x52f7e4], eax
        dd _ytable_x4+024h
        db 0A3h   ; mov dword ptr [0x52f7e8], eax
        dd _ytable_x4+028h
        db 0A3h   ; mov dword ptr [0x52f7ec], eax
        dd _ytable_x4+02Ch
        db 0A3h   ; mov dword ptr [0x52f7f0], eax
        dd _ytable_x4+030h
        db 0A3h   ; mov dword ptr [0x52f7f4], eax
        dd _ytable_x4+034h
        db 0A3h   ; mov dword ptr [0x52f7f8], eax
        dd _ytable_x4+038h
        db 0A3h   ; mov dword ptr [0x52f7fc], eax
        dd _ytable_x4+03Ch
        db 0A3h   ; mov dword ptr [0x52f800], eax
        dd _ytable_x4+040h
        db 0BEh   ; mov esi, 0x52f804
        dd _ytable_x4+044h
        db 0B9h, 0ADh, 07Dh, 000h, 000h   ; mov ecx, 0x7dad
$L_34bc90:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 081h, 0C1h, 0ADh, 07Dh, 000h, 000h   ; add ecx, 0x7dad
        db 083h, 0C6h, 004h   ; add esi, 4
        db 081h, 0F9h, 052h, 005h, 06Bh, 000h   ; cmp ecx, 0x6b0552
        db 07Eh, 0DCh   ; jle 0x34bc90
        db 0B9h, 0FCh, 003h, 000h, 000h   ; mov ecx, 0x3fc
        db 089h, 00Dh   ; mov dword ptr [0x52fb6c], ecx
        dd _ytable_x4+03ACh
        db 089h, 00Dh   ; mov dword ptr [0x52fb70], ecx
        dd _ytable_x4+03B0h
        db 089h, 00Dh   ; mov dword ptr [0x52fb74], ecx
        dd _ytable_x4+03B4h
        db 089h, 00Dh   ; mov dword ptr [0x52fb78], ecx
        dd _ytable_x4+03B8h
        db 089h, 00Dh   ; mov dword ptr [0x52fb7c], ecx
        dd _ytable_x4+03BCh
        db 089h, 00Dh   ; mov dword ptr [0x52fb80], ecx
        dd _ytable_x4+03C0h
        db 089h, 00Dh   ; mov dword ptr [0x52fb84], ecx
        dd _ytable_x4+03C4h
        db 089h, 00Dh   ; mov dword ptr [0x52fb88], ecx
        dd _ytable_x4+03C8h
        db 089h, 00Dh   ; mov dword ptr [0x52fb8c], ecx
        dd _ytable_x4+03CCh
        db 089h, 00Dh   ; mov dword ptr [0x52fb90], ecx
        dd _ytable_x4+03D0h
        db 089h, 00Dh   ; mov dword ptr [0x52fb94], ecx
        dd _ytable_x4+03D4h
        db 089h, 00Dh   ; mov dword ptr [0x52fb98], ecx
        dd _ytable_x4+03D8h
        db 089h, 00Dh   ; mov dword ptr [0x52fb9c], ecx
        dd _ytable_x4+03DCh
        db 089h, 00Dh   ; mov dword ptr [0x52fba0], ecx
        dd _ytable_x4+03E0h
        db 089h, 00Dh   ; mov dword ptr [0x52fba4], ecx
        dd _ytable_x4+03E4h
        db 089h, 00Dh   ; mov dword ptr [0x52fba8], ecx
        dd _ytable_x4+03E8h
        db 089h, 00Dh   ; mov dword ptr [0x52fbac], ecx
        dd _ytable_x4+03ECh
        db 089h, 00Dh   ; mov dword ptr [0x52fbb0], ecx
        dd _ytable_x4+03F0h
        db 089h, 00Dh   ; mov dword ptr [0x52fbb4], ecx
        dd _ytable_x4+03F4h
        db 089h, 00Dh   ; mov dword ptr [0x52fbb8], ecx
        dd _ytable_x4+03F8h
        db 089h, 00Dh   ; mov dword ptr [0x52fbbc], ecx
        dd _ytable_x4+03FCh
$L_34bd37:
        db 08Bh, 015h   ; mov edx, dword ptr [0x5388b0]
        dd _RGBshift+018h
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 033h, 0C0h   ; xor eax, eax
        db 0BFh   ; mov edi, 0x52ffe0
        dd _clamp_r
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 0EBh, 003h   ; jmp 0x34bd50
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34bd50:
        db 08Bh, 0F0h   ; mov esi, eax
        db 08Bh, 0CAh   ; mov ecx, edx
        db 0D3h, 0FEh   ; sar esi, cl
        db 040h   ; inc eax
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 089h, 034h, 085h   ; mov dword ptr [eax*4 + 0x5303dc], esi
        dd _clamp_r+03FCh
        db 07Ch, 0EBh   ; jl 0x34bd50
        db 0B9h, 008h, 000h, 000h, 000h   ; mov ecx, 8
        db 02Bh, 0CAh   ; sub ecx, edx
        db 0BBh, 001h, 000h, 000h, 000h   ; mov ebx, 1
        db 0D3h, 0E3h   ; shl ebx, cl
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 0BFh   ; mov edi, 0x5307e0
        dd _clamp_r+0800h
        db 04Bh   ; dec ebx
        db 08Bh, 0C3h   ; mov eax, ebx
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 033h, 0C0h   ; xor eax, eax
        db 0BFh   ; mov edi, 0x530bf0
        dd _clamp_g
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
$L_34bd90:
        db 08Bh, 0D0h   ; mov edx, eax
        db 08Bh, 0CDh   ; mov ecx, ebp
        db 0D3h, 0FAh   ; sar edx, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a0]
        dd _RGBshift+08h
        db 0D3h, 0E2h   ; shl edx, cl
        db 040h   ; inc eax
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 089h, 014h, 085h   ; mov dword ptr [eax*4 + 0x530fec], edx
        dd _clamp_g+03FCh
        db 07Ch, 0E3h   ; jl 0x34bd90
        db 0B9h, 008h, 000h, 000h, 000h   ; mov ecx, 8
        db 02Bh, 0CDh   ; sub ecx, ebp
        db 0BAh, 001h, 000h, 000h, 000h   ; mov edx, 1
        db 0D3h, 0E2h   ; shl edx, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a0]
        dd _RGBshift+08h
        db 0BFh   ; mov edi, 0x5313f0
        dd _clamp_g+0800h
        db 04Ah   ; dec edx
        db 0D3h, 0E2h   ; shl edx, cl
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 08Bh, 0C2h   ; mov eax, edx
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 033h, 0C0h   ; xor eax, eax
        db 0BFh   ; mov edi, 0x531800
        dd _clamp_b
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
$L_34bde0:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388c0]
        dd _RGBshift+028h
        db 08Bh, 0F0h   ; mov esi, eax
        db 0D3h, 0FEh   ; sar esi, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a8]
        dd _RGBshift+010h
        db 0D3h, 0E6h   ; shl esi, cl
        db 040h   ; inc eax
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 089h, 034h, 085h   ; mov dword ptr [eax*4 + 0x531bfc], esi
        dd _clamp_b+03FCh
        db 07Ch, 0DFh   ; jl 0x34bde0
        db 0A1h   ; mov eax, dword ptr [0x5388c0]
        dd _RGBshift+028h
        db 0B9h, 008h, 000h, 000h, 000h   ; mov ecx, 8
        db 02Bh, 0C8h   ; sub ecx, eax
        db 0BEh, 001h, 000h, 000h, 000h   ; mov esi, 1
        db 0D3h, 0E6h   ; shl esi, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a8]
        dd _RGBshift+010h
        db 0BFh   ; mov edi, 0x532000
        dd _clamp_b+0800h
        db 04Eh   ; dec esi
        db 0D3h, 0E6h   ; shl esi, cl
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 08Bh, 0C6h   ; mov eax, esi
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 033h, 0C0h   ; xor eax, eax
        db 0BFh   ; mov edi, 0x533840
        dd _clamp_gg
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h   ; lea esp, [esp]
$L_34be40:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388b0]
        dd _RGBshift+018h
        db 08Bh, 0F8h   ; mov edi, eax
        db 0D3h, 0FFh   ; sar edi, cl
        db 069h, 0FFh, 001h, 000h, 001h, 000h   ; imul edi, edi, 0x10001
        db 089h, 03Ch, 085h   ; mov dword ptr [eax*4 + 0x533c40], edi
        dd _clamp_gg+0400h
        db 040h   ; inc eax
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 07Ch, 0E1h   ; jl 0x34be40
        db 069h, 0DBh, 001h, 000h, 001h, 000h   ; imul ebx, ebx, 0x10001
        db 08Bh, 0C3h   ; mov eax, ebx
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 0BFh   ; mov edi, 0x534040
        dd _clamp_gg+0800h
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 033h, 0C0h   ; xor eax, eax
        db 0BFh   ; mov edi, 0x534450
        dd _clamp_bb
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
$L_34be81:
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Bh, 0CDh   ; mov ecx, ebp
        db 0D3h, 0FFh   ; sar edi, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a0]
        dd _RGBshift+08h
        db 0D3h, 0E7h   ; shl edi, cl
        db 069h, 0FFh, 001h, 000h, 001h, 000h   ; imul edi, edi, 0x10001
        db 089h, 03Ch, 085h   ; mov dword ptr [eax*4 + 0x534850], edi
        dd _clamp_bb+0400h
        db 040h   ; inc eax
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 07Ch, 0DDh   ; jl 0x34be81
        db 069h, 0D2h, 001h, 000h, 001h, 000h   ; imul edx, edx, 0x10001
        db 08Bh, 0C2h   ; mov eax, edx
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 0BFh   ; mov edi, 0x534c50
        dd _clamp_bb+0800h
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 033h, 0C0h   ; xor eax, eax
        db 0BFh   ; mov edi, 0x535060
        dd _clamp32
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
$L_34bec6:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388c0]
        dd _RGBshift+028h
        db 08Bh, 0D0h   ; mov edx, eax
        db 0D3h, 0FAh   ; sar edx, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a8]
        dd _RGBshift+010h
        db 0D3h, 0E2h   ; shl edx, cl
        db 069h, 0D2h, 001h, 000h, 001h, 000h   ; imul edx, edx, 0x10001
        db 089h, 014h, 085h   ; mov dword ptr [eax*4 + 0x535460], edx
        dd _clamp32+0400h
        db 040h   ; inc eax
        db 03Dh, 000h, 001h, 000h, 000h   ; cmp eax, 0x100
        db 07Ch, 0D9h   ; jl 0x34bec6
        db 069h, 0F6h, 001h, 000h, 001h, 000h   ; imul esi, esi, 0x10001
        db 08Bh, 0C6h   ; mov eax, esi
        db 0B9h, 000h, 001h, 000h, 000h   ; mov ecx, 0x100
        db 0BFh   ; mov edi, 0x535860
        dd _clamp32+0800h
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 0A3h   ; mov dword ptr [0x5388d0], eax
        dd _unk_5388D0
        db 033h, 0DBh   ; xor ebx, ebx
        db 0E9h, 017h, 002h, 000h, 000h   ; jmp 0x34c128
$L_34bf11:
        db 0B8h, 003h, 000h, 000h, 000h   ; mov eax, 3
        db 0A3h   ; mov dword ptr [0x5388b0], eax
        dd _RGBshift+018h
        db 0A3h   ; mov dword ptr [0x5388c0], eax
        dd _RGBshift+028h
        db 0B8h, 042h, 025h, 042h, 025h   ; mov eax, 0x25422542
        db 0A3h   ; mov dword ptr [0x4311d8], eax
        dd _pmemwYscalem
        db 0A3h   ; mov dword ptr [0x4311dc], eax
        dd _unk_4311DC
        db 0B8h, 0E0h, 07Fh, 0E0h, 07Fh   ; mov eax, 0x7fe07fe0
        db 0BDh, 002h, 000h, 000h, 000h   ; mov ebp, 2
        db 0A3h   ; mov dword ptr [0x4311e0], eax
        dd _pmemw7F00m
        db 0A3h   ; mov dword ptr [0x4311e4], eax
        dd _unk_4311E4
        db 089h, 01Dh   ; mov dword ptr [0x538898], ebx
        dd _RGBshift
        db 089h, 02Dh   ; mov dword ptr [0x5388b8], ebp
        dd _RGBshift+020h
        db 089h, 015h   ; mov dword ptr [0x5388a0], edx
        dd _RGBshift+08h
        db 0C7h, 005h   ; mov dword ptr [0x5388a8], 0xb
        dd _RGBshift+010h
        db 00Bh, 000h, 000h, 000h
        db 0B8h, 041h, 008h, 041h, 008h   ; mov eax, 0x8410841
        db 0E9h, 0A6h, 0FCh, 0FFh, 0FFh   ; jmp 0x34bc0f
$L_34bf69:
        db 0B8h, 0A1h, 012h, 0A1h, 012h   ; mov eax, 0x12a112a1
        db 0BDh, 004h, 000h, 000h, 000h   ; mov ebp, 4
        db 0A3h   ; mov dword ptr [0x4311d8], eax
        dd _pmemwYscalem
        db 0A3h   ; mov dword ptr [0x4311dc], eax
        dd _unk_4311DC
        db 0B8h, 0F0h, 07Fh, 0F0h, 07Fh   ; mov eax, 0x7ff07ff0
        db 0A3h   ; mov dword ptr [0x4311e0], eax
        dd _pmemw7F00m
        db 0A3h   ; mov dword ptr [0x4311e4], eax
        dd _unk_4311E4
        db 089h, 02Dh   ; mov dword ptr [0x5388b0], ebp
        dd _RGBshift+018h
        db 089h, 01Dh   ; mov dword ptr [0x538898], ebx
        dd _RGBshift
        db 089h, 02Dh   ; mov dword ptr [0x5388b8], ebp
        dd _RGBshift+020h
        db 089h, 02Dh   ; mov dword ptr [0x5388a0], ebp
        dd _RGBshift+08h
        db 089h, 02Dh   ; mov dword ptr [0x5388c0], ebp
        dd _RGBshift+028h
        db 0C7h, 005h   ; mov dword ptr [0x5388a8], 8
        dd _RGBshift+010h
        db 008h, 000h, 000h, 000h
        db 0B8h, 011h, 001h, 011h, 001h   ; mov eax, 0x1110111
        db 0E9h, 051h, 0FCh, 0FFh, 0FFh   ; jmp 0x34bc0f
$L_34bfbe:
        db 0B8h, 0A1h, 012h, 0A1h, 012h   ; mov eax, 0x12a112a1
        db 0A3h   ; mov dword ptr [0x4311d8], eax
        dd _pmemwYscalem
        db 0A3h   ; mov dword ptr [0x4311dc], eax
        dd _unk_4311DC
        db 0B8h, 0F0h, 07Fh, 0F0h, 07Fh   ; mov eax, 0x7ff07ff0
        db 0BDh, 002h, 000h, 000h, 000h   ; mov ebp, 2
        db 0A3h   ; mov dword ptr [0x4311e0], eax
        dd _pmemw7F00m
        db 0A3h   ; mov dword ptr [0x4311e4], eax
        dd _unk_4311E4
        db 089h, 02Dh   ; mov dword ptr [0x5388b0], ebp
        dd _RGBshift+018h
        db 089h, 01Dh   ; mov dword ptr [0x538898], ebx
        dd _RGBshift
        db 089h, 02Dh   ; mov dword ptr [0x5388b8], ebp
        dd _RGBshift+020h
        db 0C7h, 005h   ; mov dword ptr [0x5388a0], 6
        dd _RGBshift+08h
        db 006h, 000h, 000h, 000h
        db 0C7h, 005h   ; mov dword ptr [0x5388c0], 4
        dd _RGBshift+028h
        db 004h, 000h, 000h, 000h
        db 0C7h, 005h   ; mov dword ptr [0x5388a8], 0xc
        dd _RGBshift+010h
        db 00Ch, 000h, 000h, 000h
        db 0B8h, 004h, 011h, 004h, 011h   ; mov eax, 0x11041104
        db 0E9h, 0F4h, 0FBh, 0FFh, 0FFh   ; jmp 0x34bc0f
$L_34c01b:
        db 0B8h, 003h, 000h, 000h, 000h   ; mov eax, 3
        db 08Bh, 0E8h   ; mov ebp, eax
        db 0A3h   ; mov dword ptr [0x5388c0], eax
        dd _RGBshift+028h
        db 0B8h, 042h, 025h, 042h, 025h   ; mov eax, 0x25422542
        db 0A3h   ; mov dword ptr [0x4311d8], eax
        dd _pmemwYscalem
        db 0A3h   ; mov dword ptr [0x4311dc], eax
        dd _unk_4311DC
        db 0B8h, 0E0h, 07Fh, 0E0h, 07Fh   ; mov eax, 0x7fe07fe0
        db 0A3h   ; mov dword ptr [0x4311e0], eax
        dd _pmemw7F00m
        db 0A3h   ; mov dword ptr [0x4311e4], eax
        dd _unk_4311E4
        db 0C7h, 005h   ; mov dword ptr [0x5388b0], 2
        dd _RGBshift+018h
        db 002h, 000h, 000h, 000h
        db 089h, 01Dh   ; mov dword ptr [0x538898], ebx
        dd _RGBshift
        db 089h, 02Dh   ; mov dword ptr [0x5388b8], ebp
        dd _RGBshift+020h
        db 0C7h, 005h   ; mov dword ptr [0x5388a0], 6
        dd _RGBshift+08h
        db 006h, 000h, 000h, 000h
        db 0C7h, 005h   ; mov dword ptr [0x5388a8], 0xb
        dd _RGBshift+010h
        db 00Bh, 000h, 000h, 000h
        db 0B8h, 042h, 008h, 042h, 008h   ; mov eax, 0x8420842
        db 0E9h, 096h, 0FBh, 0FFh, 0FFh   ; jmp 0x34bc0f
$L_34c079:
        db 0A1h   ; mov eax, dword ptr [0x5388d4]
        dd _unk_5388D4
        db 033h, 0EDh   ; xor ebp, ebp
        db 0BFh, 001h, 000h, 000h, 000h   ; mov edi, 1
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 01Dh   ; mov dword ptr [0x5388b0], ebx
        dd _RGBshift+018h
        db 089h, 01Dh   ; mov dword ptr [0x538898], ebx
        dd _RGBshift
        db 089h, 02Dh   ; mov dword ptr [0x5388b8], ebp
        dd _RGBshift+020h
        db 089h, 01Dh   ; mov dword ptr [0x5388a0], ebx
        dd _RGBshift+08h
        db 089h, 01Dh   ; mov dword ptr [0x5388c0], ebx
        dd _RGBshift+028h
        db 089h, 01Dh   ; mov dword ptr [0x5388a8], ebx
        dd _RGBshift+010h
        db 074h, 07Bh   ; je 0x34c128
        db 033h, 0C9h   ; xor ecx, ecx
        db 0BEh, 030h, 025h, 0F8h, 0FFh   ; mov esi, 0xfff82530
$L_34c0b4:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Fh, 004h   ; jg 0x34c0bc
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 01Dh   ; jmp 0x34c0d9
$L_34c0bc:
        db 081h, 0FEh, 0FFh, 082h, 06Bh, 000h   ; cmp esi, 0x6b82ff
        db 07Ch, 007h   ; jl 0x34c0cb
        db 0B8h, 0FFh, 000h, 000h, 000h   ; mov eax, 0xff
        db 0EBh, 00Eh   ; jmp 0x34c0d9
$L_34c0cb:
        db 08Bh, 0C6h   ; mov eax, esi
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
$L_34c0d9:
        db 08Dh, 014h, 085h   ; lea edx, [eax*4 + 0x533030]
        dd _clamp_rr+0400h
        db 089h, 014h, 08Dh   ; mov dword ptr [ecx*4 + 0x532820], edx
        dd _clamp_ytable
        db 08Bh, 0D0h   ; mov edx, eax
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D0h   ; or edx, eax
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 00Bh, 0D0h   ; or edx, eax
        db 089h, 01Ch, 08Dh   ; mov dword ptr [ecx*4 + 0x532c30], ebx
        dd _clamp_rr
        db 089h, 00Ch, 08Dh   ; mov dword ptr [ecx*4 + 0x533030], ecx
        dd _clamp_rr+0400h
        db 0C7h, 004h, 08Dh   ; mov dword ptr [ecx*4 + 0x533430], 0xff
        dd _clamp_rr+0800h
        db 0FFh, 000h, 000h, 000h
        db 089h, 014h, 08Dh   ; mov dword ptr [ecx*4 + 0x536470], edx
        dd _mono32
        db 081h, 0C6h, 0ADh, 07Dh, 000h, 000h   ; add esi, 0x7dad
        db 041h   ; inc ecx
        db 081h, 0FEh, 030h, 0D2h, 075h, 000h   ; cmp esi, 0x75d230
        db 07Ch, 092h   ; jl 0x34c0b4
        db 089h, 03Dh   ; mov dword ptr [0x5388d4], edi
        dd _unk_5388D4
$L_34c128:
        db 039h, 01Dh   ; cmp dword ptr [0x5388e4], ebx
        dd _unk_5388E4
        db 00Fh, 085h, 0A3h, 002h, 000h, 000h   ; jne 0x34c3d7
        db 0BEh   ; mov esi, 0x536c98
        dd _YUVTables+0400h
        db 0B9h   ; mov ecx, 0x340580
        dd 0340580h   ; not an address: a fixed-point constant
        db 08Bh, 0FFh   ; mov edi, edi
$L_34c140:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 081h, 0E9h, 00Bh, 068h, 000h, 000h   ; sub ecx, 0x680b
        db 083h, 0C6h, 004h   ; add esi, 4
        db 081h, 0F9h, 080h, 0FAh, 0CBh, 0FFh   ; cmp ecx, 0xffcbfa80
        db 07Fh, 0DFh   ; jg 0x34c140
        db 0BEh   ; mov esi, 0x537098
        dd _YUVTables+0800h
        db 0B9h, 000h, 002h, 019h, 000h   ; mov ecx, 0x190200
        db 0EBh, 003h   ; jmp 0x34c170
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34c170:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 081h, 0E9h, 004h, 032h, 000h, 000h   ; sub ecx, 0x3204
        db 083h, 0C6h, 004h   ; add esi, 4
        db 081h, 0F9h, 000h, 0FEh, 0E6h, 0FFh   ; cmp ecx, 0xffe6fe00
        db 07Fh, 0DFh   ; jg 0x34c170
        db 0BEh   ; mov esi, 0x537498
        dd _YUVTables+0C00h
        db 0B9h, 080h, 0F1h, 099h, 0FFh   ; mov ecx, 0xff99f180
        db 0EBh, 003h   ; jmp 0x34c1a0
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34c1a0:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 081h, 0C1h, 01Dh, 0CCh, 000h, 000h   ; add ecx, 0xcc1d
        db 083h, 0C6h, 004h   ; add esi, 4
        db 081h, 0F9h, 080h, 00Eh, 066h, 000h   ; cmp ecx, 0x660e80
        db 07Ch, 0DFh   ; jl 0x34c1a0
        db 0BEh   ; mov esi, 0x536898
        dd _YUVTables
        db 0B9h, 000h, 0EEh, 07Eh, 0FFh   ; mov ecx, 0xff7eee00
        db 0EBh, 003h   ; jmp 0x34c1d0
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34c1d0:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 081h, 0C1h, 024h, 002h, 001h, 000h   ; add ecx, 0x10224
        db 083h, 0C6h, 004h   ; add esi, 4
        db 081h, 0F9h, 000h, 012h, 081h, 000h   ; cmp ecx, 0x811200
        db 07Ch, 0DFh   ; jl 0x34c1d0
        db 0B8h   ; mov eax, 0x537c98
        dd _YUVTables+01400h
        db 0EBh, 008h   ; jmp 0x34c200
        db 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h   ; lea esp, [esp]
        db 090h   ; nop 
$L_34c200:
        db 08Bh, 088h, 000h, 0F0h, 0FFh, 0FFh   ; mov ecx, dword ptr [eax - 0x1000]
        db 081h, 0E1h, 0FFh, 0FFh, 000h, 000h   ; and ecx, 0xffff
        db 069h, 0C9h, 001h, 000h, 001h, 000h   ; imul ecx, ecx, 0x10001
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 03Dh   ; cmp eax, 0x538098
        dd _YUVTables+01800h
        db 07Ch, 0E2h   ; jl 0x34c200
        db 0B8h   ; mov eax, 0x538098
        dd _YUVTables+01800h
$L_34c223:
        db 08Bh, 090h, 000h, 0F0h, 0FFh, 0FFh   ; mov edx, dword ptr [eax - 0x1000]
        db 081h, 0E2h, 0FFh, 0FFh, 000h, 000h   ; and edx, 0xffff
        db 069h, 0D2h, 001h, 000h, 001h, 000h   ; imul edx, edx, 0x10001
        db 089h, 010h   ; mov dword ptr [eax], edx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 03Dh   ; cmp eax, 0x538498
        dd _YUVTables+01C00h
        db 07Ch, 0E2h   ; jl 0x34c223
        db 0B8h   ; mov eax, 0x538498
        dd _YUVTables+01C00h
        db 0EBh, 008h   ; jmp 0x34c250
        db 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h   ; lea esp, [esp]
        db 090h   ; nop 
$L_34c250:
        db 08Bh, 088h, 000h, 0F0h, 0FFh, 0FFh   ; mov ecx, dword ptr [eax - 0x1000]
        db 081h, 0E1h, 0FFh, 0FFh, 000h, 000h   ; and ecx, 0xffff
        db 069h, 0C9h, 001h, 000h, 001h, 000h   ; imul ecx, ecx, 0x10001
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 03Dh   ; cmp eax, 0x538898
        dd _RGBshift
        db 07Ch, 0E2h   ; jl 0x34c250
        db 0B8h   ; mov eax, 0x537898
        dd _YUVTables+01000h
$L_34c273:
        db 08Bh, 090h, 000h, 0F0h, 0FFh, 0FFh   ; mov edx, dword ptr [eax - 0x1000]
        db 081h, 0E2h, 0FFh, 0FFh, 000h, 000h   ; and edx, 0xffff
        db 069h, 0D2h, 001h, 000h, 001h, 000h   ; imul edx, edx, 0x10001
        db 089h, 010h   ; mov dword ptr [eax], edx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 03Dh   ; cmp eax, 0x537c98
        dd _YUVTables+01400h
        db 07Ch, 0E2h   ; jl 0x34c273
        db 033h, 0C0h   ; xor eax, eax
        db 0A3h   ; mov dword ptr [0x535c70], eax
        dd _mono16
        db 0A3h   ; mov dword ptr [0x535c74], eax
        dd _mono16+04h
        db 0A3h   ; mov dword ptr [0x535c78], eax
        dd _mono16+08h
        db 0A3h   ; mov dword ptr [0x535c7c], eax
        dd _mono16+0Ch
        db 0A3h   ; mov dword ptr [0x535c80], eax
        dd _mono16+010h
        db 0A3h   ; mov dword ptr [0x535c84], eax
        dd _mono16+014h
        db 0A3h   ; mov dword ptr [0x535c88], eax
        dd _mono16+018h
        db 0A3h   ; mov dword ptr [0x535c8c], eax
        dd _mono16+01Ch
        db 0A3h   ; mov dword ptr [0x535c90], eax
        dd _mono16+020h
        db 0A3h   ; mov dword ptr [0x535c94], eax
        dd _mono16+024h
        db 0A3h   ; mov dword ptr [0x535c98], eax
        dd _mono16+028h
        db 0A3h   ; mov dword ptr [0x535c9c], eax
        dd _mono16+02Ch
        db 0A3h   ; mov dword ptr [0x535ca0], eax
        dd _mono16+030h
        db 0A3h   ; mov dword ptr [0x535ca4], eax
        dd _mono16+034h
        db 0A3h   ; mov dword ptr [0x535ca8], eax
        dd _mono16+038h
        db 0A3h   ; mov dword ptr [0x535cac], eax
        dd _mono16+03Ch
        db 0A3h   ; mov dword ptr [0x535cb0], eax
        dd _mono16+040h
        db 0BFh   ; mov edi, 0x535cb4
        dd _mono16+044h
        db 0BEh, 0ADh, 07Dh, 000h, 000h   ; mov esi, 0x7dad
$L_34c2f2:
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388c0]
        dd _RGBshift+028h
        db 08Bh, 0C6h   ; mov eax, esi
        db 099h   ; cdq 
        db 081h, 0E2h, 0FFh, 07Fh, 000h, 000h   ; and edx, 0x7fff
        db 003h, 0C2h   ; add eax, edx
        db 0C1h, 0F8h, 00Fh   ; sar eax, 0xf
        db 08Bh, 0D0h   ; mov edx, eax
        db 0D3h, 0FAh   ; sar edx, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a8]
        dd _RGBshift+010h
        db 08Bh, 0D8h   ; mov ebx, eax
        db 081h, 0C6h, 0ADh, 07Dh, 000h, 000h   ; add esi, 0x7dad
        db 0D3h, 0E2h   ; shl edx, cl
        db 08Bh, 0CDh   ; mov ecx, ebp
        db 0D3h, 0FBh   ; sar ebx, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388a0]
        dd _RGBshift+08h
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D3h, 0E3h   ; shl ebx, cl
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x5388b0]
        dd _RGBshift+018h
        db 0D3h, 0F8h   ; sar eax, cl
        db 00Bh, 0D3h   ; or edx, ebx
        db 00Bh, 0D0h   ; or edx, eax
        db 081h, 0FEh, 052h, 005h, 06Bh, 000h   ; cmp esi, 0x6b0552
        db 089h, 057h, 0FCh   ; mov dword ptr [edi - 4], edx
        db 07Eh, 0B2h   ; jle 0x34c2f2
        db 0B8h, 0FFh, 000h, 000h, 000h   ; mov eax, 0xff
        db 0A3h   ; mov dword ptr [0x53601c], eax
        dd _mono16+03ACh
        db 0A3h   ; mov dword ptr [0x536020], eax
        dd _mono16+03B0h
        db 0A3h   ; mov dword ptr [0x536024], eax
        dd _mono16+03B4h
        db 0A3h   ; mov dword ptr [0x536028], eax
        dd _mono16+03B8h
        db 0A3h   ; mov dword ptr [0x53602c], eax
        dd _mono16+03BCh
        db 0A3h   ; mov dword ptr [0x536030], eax
        dd _mono16+03C0h
        db 0A3h   ; mov dword ptr [0x536034], eax
        dd _mono16+03C4h
        db 0A3h   ; mov dword ptr [0x536038], eax
        dd _mono16+03C8h
        db 0A3h   ; mov dword ptr [0x53603c], eax
        dd _mono16+03CCh
        db 0A3h   ; mov dword ptr [0x536040], eax
        dd _mono16+03D0h
        db 0A3h   ; mov dword ptr [0x536044], eax
        dd _mono16+03D4h
        db 0A3h   ; mov dword ptr [0x536048], eax
        dd _mono16+03D8h
        db 0A3h   ; mov dword ptr [0x53604c], eax
        dd _mono16+03DCh
        db 0A3h   ; mov dword ptr [0x536050], eax
        dd _mono16+03E0h
        db 0A3h   ; mov dword ptr [0x536054], eax
        dd _mono16+03E4h
        db 0A3h   ; mov dword ptr [0x536058], eax
        dd _mono16+03E8h
        db 0A3h   ; mov dword ptr [0x53605c], eax
        dd _mono16+03ECh
        db 0A3h   ; mov dword ptr [0x536060], eax
        dd _mono16+03F0h
        db 0A3h   ; mov dword ptr [0x536064], eax
        dd _mono16+03F4h
        db 0A3h   ; mov dword ptr [0x536068], eax
        dd _mono16+03F8h
        db 0A3h   ; mov dword ptr [0x53606c], eax
        dd _mono16+03FCh
        db 033h, 0C0h   ; xor eax, eax
$L_34c3b0:
        db 08Bh, 088h   ; mov ecx, dword ptr [eax + 0x535c70]
        dd _mono16
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E2h, 010h   ; shl edx, 0x10
        db 00Bh, 0D1h   ; or edx, ecx
        db 089h, 090h   ; mov dword ptr [eax + 0x536070], edx
        dd _mono16x2
        db 083h, 0C0h, 004h   ; add eax, 4
        db 03Dh, 000h, 004h, 000h, 000h   ; cmp eax, 0x400
        db 07Ch, 0E3h   ; jl 0x34c3b0
        db 0C7h, 005h   ; mov dword ptr [0x5388e4], 1
        dd _unk_5388E4
        db 001h, 000h, 000h, 000h
$L_34c3d7:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 0C2h, 004h, 000h   ; ret 4
        db 08Bh, 0FFh   ; mov edi, edi
$L_34c3e0:
        dd $L_34bf69
        dd $L_34bbbf
        dd $L_34bbbf
        dd $L_34bf11
        dd $L_34c01b
        dd $L_34bfbe
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
_YUV_init@4 ENDP
seg3 ENDS







segbm SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'

; // match: ?YUV_blit_mask@@YAXPAXKKKPAEK0KKKKKKK0PAUBLITS@@@Z @ 0x0034B150
; // sp-match: ?YUV_blit_mask@@YAXPAXKKKPAEK0KKKKKKK0PAUBLITS@@@Z @ 0x0025B150
?YUV_blit_mask@@YAXPAXKKKPAEK0KKKKKKK0PAUBLITS@@@Z PROC PUBLIC
        db 081h, 0ECh, 084h, 000h, 000h, 000h   ; sub esp, 0x84
        db 08Bh, 08Ch, 024h, 094h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0x94]
        db 08Bh, 094h, 024h, 0B0h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xb0]
        db 08Bh, 084h, 024h, 0B8h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xb8]
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 08Bh, 0ACh, 024h, 0BCh, 000h, 000h, 000h   ; mov ebp, dword ptr [esp + 0xbc]
        db 056h   ; push esi
        db 08Bh, 0B4h, 024h, 0C8h, 000h, 000h, 000h   ; mov esi, dword ptr [esp + 0xc8]
        db 057h   ; push edi
        db 081h, 0E6h, 000h, 000h, 000h, 070h   ; and esi, 0x70000000
        db 081h, 0FEh, 000h, 000h, 000h, 060h   ; cmp esi, 0x60000000
        db 08Bh, 0F9h   ; mov edi, ecx
        db 089h, 054h, 024h, 030h   ; mov dword ptr [esp + 0x30], edx
        db 089h, 044h, 024h, 04Ch   ; mov dword ptr [esp + 0x4c], eax
        db 089h, 06Ch, 024h, 054h   ; mov dword ptr [esp + 0x54], ebp
        db 089h, 07Ch, 024h, 040h   ; mov dword ptr [esp + 0x40], edi
        db 075h, 038h   ; jne 0x34b1d5
        db 0D1h, 0ACh, 024h, 0B8h, 000h, 000h, 000h   ; shr dword ptr [esp + 0xb8], 1
        db 0D1h, 0ACh, 024h, 0C8h, 000h, 000h, 000h   ; shr dword ptr [esp + 0xc8], 1
        db 08Bh, 084h, 024h, 0ACh, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xac]
        db 0D1h, 0EAh   ; shr edx, 1
        db 003h, 0C9h   ; add ecx, ecx
        db 003h, 0EDh   ; add ebp, ebp
        db 089h, 044h, 024h, 018h   ; mov dword ptr [esp + 0x18], eax
        db 003h, 0C0h   ; add eax, eax
        db 089h, 094h, 024h, 0C0h, 000h, 000h, 000h   ; mov dword ptr [esp + 0xc0], edx
        db 089h, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov dword ptr [esp + 0xa4], ecx
        db 089h, 084h, 024h, 0ACh, 000h, 000h, 000h   ; mov dword ptr [esp + 0xac], eax
        db 0EBh, 008h   ; jmp 0x34b1dd
$L_34b1d5:
        db 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x18], 0
$L_34b1dd:
        db 08Bh, 084h, 024h, 098h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0x98]
        db 00Fh, 0AFh, 0BCh, 024h, 0A0h, 000h, 000h, 000h   ; imul edi, dword ptr [esp + 0xa0]
        db 0A3h   ; mov dword ptr [0x536894], eax
        dd _S+024h
        db 08Bh, 084h, 024h, 0D4h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xd4]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 00Fh, 0AFh, 09Ch, 024h, 09Ch, 000h, 000h, 000h   ; imul ebx, dword ptr [esp + 0x9c]
        db 003h, 09Ch, 024h, 098h, 000h, 000h, 000h   ; add ebx, dword ptr [esp + 0x98]
        db 003h, 0FBh   ; add edi, ebx
        db 081h, 0FEh, 000h, 000h, 000h, 020h   ; cmp esi, 0x20000000
        db 089h, 03Dh   ; mov dword ptr [0x536870], edi
        dd _S
        db 074h, 008h   ; je 0x34b221
        db 081h, 0FEh, 000h, 000h, 000h, 050h   ; cmp esi, 0x50000000
        db 075h, 009h   ; jne 0x34b22a
$L_34b221:
        db 003h, 0C9h   ; add ecx, ecx
        db 089h, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov dword ptr [esp + 0xa4], ecx
$L_34b22a:
        db 08Bh, 09Ch, 024h, 0BCh, 000h, 000h, 000h   ; mov ebx, dword ptr [esp + 0xbc]
        db 08Bh, 0BCh, 024h, 0ACh, 000h, 000h, 000h   ; mov edi, dword ptr [esp + 0xac]
        db 089h, 04Ch, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], ecx
        db 08Dh, 04Ch, 024h, 02Ch   ; lea ecx, [esp + 0x2c]
        db 0C1h, 0EBh, 004h   ; shr ebx, 4
        db 051h   ; push ecx
        db 02Bh, 0FBh   ; sub edi, ebx
        db 08Bh, 09Ch, 024h, 0D0h, 000h, 000h, 000h   ; mov ebx, dword ptr [esp + 0xd0]
        db 052h   ; push edx
        db 089h, 07Ch, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], edi
        db 06Ah, 010h   ; push 0x10
        db 08Dh, 07Ch, 024h, 028h   ; lea edi, [esp + 0x28]
        call ?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z   ; 0x34A840
        db 08Bh, 084h, 024h, 0CCh, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xcc]
        db 08Dh, 054h, 024h, 048h   ; lea edx, [esp + 0x48]
        db 052h   ; push edx
        db 050h   ; push eax
        db 08Bh, 084h, 024h, 0E8h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xe8]
        db 06Ah, 020h   ; push 0x20
        db 08Dh, 0BCh, 024h, 0BCh, 000h, 000h, 000h   ; lea edi, [esp + 0xbc]
        call ?setevenodd@@YAXKPAKKKPAUBLITS@@0@Z   ; 0x34A840
        db 083h, 0C4h, 018h   ; add esp, 0x18
        db 081h, 0FEh, 000h, 000h, 000h, 030h   ; cmp esi, 0x30000000
        db 074h, 018h   ; je 0x34b2a2
        db 081h, 0FEh, 000h, 000h, 000h, 050h   ; cmp esi, 0x50000000
        db 074h, 010h   ; je 0x34b2a2
        db 081h, 0FEh, 000h, 000h, 000h, 040h   ; cmp esi, 0x40000000
        db 0C7h, 044h, 024h, 024h, 001h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x24], 1
        db 075h, 008h   ; jne 0x34b2aa
$L_34b2a2:
        db 0C7h, 044h, 024h, 024h, 002h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x24], 2
$L_34b2aa:
        db 08Bh, 08Ch, 024h, 0D4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xd4]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xa4]
        db 00Fh, 0AFh, 054h, 024h, 024h   ; imul edx, dword ptr [esp + 0x24]
        db 0A1h   ; mov eax, dword ptr [0x536870]
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 08Bh, 0B4h, 024h, 0B4h, 000h, 000h, 000h   ; mov esi, dword ptr [esp + 0xb4]
        db 08Bh, 08Ch, 024h, 0B0h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xb0]
        db 08Bh, 09Ch, 024h, 0D0h, 000h, 000h, 000h   ; mov ebx, dword ptr [esp + 0xd0]
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
        db 08Bh, 084h, 024h, 0B8h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xb8]
        db 00Fh, 0AFh, 0C5h   ; imul eax, ebp
        db 003h, 0C8h   ; add ecx, eax
        db 003h, 0CEh   ; add ecx, esi
        db 003h, 0C6h   ; add eax, esi
        db 003h, 0C3h   ; add eax, ebx
        db 089h, 00Dh   ; mov dword ptr [0x536878], ecx
        dd _S+008h
        db 003h, 0CDh   ; add ecx, ebp
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 089h, 00Dh   ; mov dword ptr [0x53687c], ecx
        dd _S+00Ch
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 0F5h   ; mov esi, ebp
        db 06Bh, 0F6h, 00Fh   ; imul esi, esi, 0xf
        db 08Bh, 0C5h   ; mov eax, ebp
        db 0D1h, 0E8h   ; shr eax, 1
        db 08Dh, 048h, 0F0h   ; lea ecx, [eax - 0x10]
        db 089h, 04Ch, 024h, 064h   ; mov dword ptr [esp + 0x64], ecx
        db 08Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xbc]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 083h, 0E7h, 00Fh   ; and edi, 0xf
        db 02Bh, 0F1h   ; sub esi, ecx
        db 003h, 0F7h   ; add esi, edi
        db 0D1h, 0E9h   ; shr ecx, 1
        db 089h, 07Ch, 024h, 01Ch   ; mov dword ptr [esp + 0x1c], edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 083h, 0E7h, 007h   ; and edi, 7
        db 0C1h, 0E2h, 004h   ; shl edx, 4
        db 08Dh, 03Ch, 0C7h   ; lea edi, [edi + eax*8]
        db 02Bh, 0F9h   ; sub edi, ecx
        db 08Bh, 04Ch, 024h, 01Ch   ; mov ecx, dword ptr [esp + 0x1c]
        db 089h, 054h, 024h, 034h   ; mov dword ptr [esp + 0x34], edx
        db 0C1h, 0EAh, 004h   ; shr edx, 4
        db 089h, 07Ch, 024h, 044h   ; mov dword ptr [esp + 0x44], edi
        db 02Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h   ; sub ecx, dword ptr [esp + 0xbc]
        db 00Fh, 0AFh, 0CAh   ; imul ecx, edx
        db 08Bh, 094h, 024h, 0A4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xa4]
        db 06Bh, 0D2h, 00Fh   ; imul edx, edx, 0xf
        db 003h, 0CAh   ; add ecx, edx
        db 0F7h, 084h, 024h, 0CCh, 000h, 000h, 000h, 000h, 000h, 001h, 000h   ; test dword ptr [esp + 0xcc], 0x10000
        db 08Bh, 094h, 024h, 0C8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xc8]
        db 08Dh, 058h, 0F8h   ; lea ebx, [eax - 8]
        db 089h, 074h, 024h, 058h   ; mov dword ptr [esp + 0x58], esi
        db 089h, 04Ch, 024h, 048h   ; mov dword ptr [esp + 0x48], ecx
        db 08Bh, 0FDh   ; mov edi, ebp
        db 074h, 01Fh   ; je 0x34b3a4
        db 00Fh, 0AFh, 0FAh   ; imul edi, edx
        db 003h, 0BCh, 024h, 0B0h, 000h, 000h, 000h   ; add edi, dword ptr [esp + 0xb0]
        db 0D1h, 0EAh   ; shr edx, 1
        db 00Fh, 0AFh, 0D0h   ; imul edx, eax
        db 003h, 0D7h   ; add edx, edi
        db 089h, 03Dh   ; mov dword ptr [0x536880], edi
        dd _S+010h
        db 089h, 015h   ; mov dword ptr [0x536884], edx
        dd _S+014h
        db 0EBh, 01Dh   ; jmp 0x34b3c1
$L_34b3a4:
        db 00Fh, 0AFh, 0FAh   ; imul edi, edx
        db 003h, 0BCh, 024h, 0B0h, 000h, 000h, 000h   ; add edi, dword ptr [esp + 0xb0]
        db 0D1h, 0EAh   ; shr edx, 1
        db 00Fh, 0AFh, 0D0h   ; imul edx, eax
        db 003h, 0D7h   ; add edx, edi
        db 089h, 03Dh   ; mov dword ptr [0x536884], edi
        dd _S+014h
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
$L_34b3c1:
        db 08Bh, 094h, 024h, 0B8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xb8]
        db 08Bh, 0FAh   ; mov edi, edx
        db 0D1h, 0EFh   ; shr edi, 1
        db 00Fh, 0AFh, 0F8h   ; imul edi, eax
        db 08Bh, 084h, 024h, 0B4h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xb4]
        db 0D1h, 0E8h   ; shr eax, 1
        db 003h, 0C7h   ; add eax, edi
        db 001h, 005h   ; add dword ptr [0x536880], eax
        dd _S+010h
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x536884]
        dd _S+014h
        db 003h, 0F8h   ; add edi, eax
        db 08Bh, 084h, 024h, 0CCh, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xcc]
        db 0F6h, 0C4h, 008h   ; test ah, 8
        db 089h, 03Dh   ; mov dword ptr [0x536884], edi
        dd _S+014h
        db 074h, 02Ch   ; je 0x34b426
        db 0A1h   ; mov eax, dword ptr [0x536878]
        dd _S+008h
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x536888]
        dd _S+018h
        db 089h, 03Dh   ; mov dword ptr [0x536878], edi
        dd _S+008h
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x53688c]
        dd _S+01Ch
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 0A1h   ; mov eax, dword ptr [0x53687c]
        dd _S+00Ch
        db 089h, 03Dh   ; mov dword ptr [0x53687c], edi
        dd _S+00Ch
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
$L_34b426:
        db 08Bh, 084h, 024h, 0C0h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xc0]
        db 08Bh, 0BCh, 024h, 0BCh, 000h, 000h, 000h   ; mov edi, dword ptr [esp + 0xbc]
        db 08Dh, 044h, 002h, 0FFh   ; lea eax, [edx + eax - 1]
        db 0C1h, 0EAh, 004h   ; shr edx, 4
        db 00Fh, 0AFh, 094h, 024h, 0ACh, 000h, 000h, 000h   ; imul edx, dword ptr [esp + 0xac]
        db 089h, 044h, 024h, 05Ch   ; mov dword ptr [esp + 0x5c], eax
        db 08Bh, 084h, 024h, 0B4h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xb4]
        db 08Dh, 07Ch, 038h, 0FFh   ; lea edi, [eax + edi - 1]
        db 089h, 054h, 024h, 020h   ; mov dword ptr [esp + 0x20], edx
        db 099h   ; cdq 
        db 083h, 0E2h, 00Fh   ; and edx, 0xf
        db 003h, 0C2h   ; add eax, edx
        db 08Bh, 094h, 024h, 0A8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xa8]
        db 089h, 07Ch, 024h, 028h   ; mov dword ptr [esp + 0x28], edi
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Bh, 044h, 024h, 020h   ; mov eax, dword ptr [esp + 0x20]
        db 003h, 0C2h   ; add eax, edx
        db 08Bh, 054h, 024h, 05Ch   ; mov edx, dword ptr [esp + 0x5c]
        db 0C1h, 0FFh, 004h   ; sar edi, 4
        db 003h, 0F8h   ; add edi, eax
        db 08Bh, 084h, 024h, 0B8h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xb8]
        db 083h, 0C0h, 00Fh   ; add eax, 0xf
        db 03Bh, 0C2h   ; cmp eax, edx
        db 089h, 07Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], edi
        db 00Fh, 08Fh, 01Dh, 005h, 000h, 000h   ; jg 0x34b9ab
        db 089h, 044h, 024h, 020h   ; mov dword ptr [esp + 0x20], eax
        db 0EBh, 00Ch   ; jmp 0x34b4a0
        db 08Dh, 0A4h, 024h, 000h, 000h, 000h, 000h   ; lea esp, [esp]
        db 0EBh, 003h   ; jmp 0x34b4a0
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34b4a0:
        db 08Bh, 084h, 024h, 0B4h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xb4]
        db 08Bh, 054h, 024h, 028h   ; mov edx, dword ptr [esp + 0x28]
        db 089h, 044h, 024h, 038h   ; mov dword ptr [esp + 0x38], eax
        db 083h, 0C0h, 01Fh   ; add eax, 0x1f
        db 03Bh, 0C2h   ; cmp eax, edx
        db 00Fh, 08Fh, 053h, 003h, 000h, 000h   ; jg 0x34b80d
        db 089h, 044h, 024h, 060h   ; mov dword ptr [esp + 0x60], eax
        db 08Bh, 044h, 024h, 018h   ; mov eax, dword ptr [esp + 0x18]
        db 0BEh, 001h, 000h, 000h, 000h   ; mov esi, 1
        db 08Dh, 00Ch, 007h   ; lea ecx, [edi + eax]
        db 02Bh, 0F0h   ; sub esi, eax
        db 089h, 04Ch, 024h, 050h   ; mov dword ptr [esp + 0x50], ecx
        db 089h, 074h, 024h, 068h   ; mov dword ptr [esp + 0x68], esi
        db 0EBh, 00Ah   ; jmp 0x34b4e0
$L_34b4d6:
        db 08Bh, 074h, 024h, 068h   ; mov esi, dword ptr [esp + 0x68]
        db 08Dh, 09Bh, 000h, 000h, 000h, 000h   ; lea ebx, [ebx]
$L_34b4e0:
        db 08Ah, 004h, 00Eh   ; mov al, byte ptr [esi + ecx]
        db 033h, 0D2h   ; xor edx, edx
        db 084h, 0C0h   ; test al, al
        db 00Fh, 095h, 0C2h   ; setne dl
        db 033h, 0C0h   ; xor eax, eax
        db 038h, 007h   ; cmp byte ptr [edi], al
        db 00Fh, 095h, 0C0h   ; setne al
        db 08Dh, 034h, 050h   ; lea esi, [eax + edx*2]
        db 08Bh, 044h, 024h, 018h   ; mov eax, dword ptr [esp + 0x18]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 015h   ; je 0x34b511
        db 033h, 0D2h   ; xor edx, edx
        db 038h, 054h, 007h, 001h   ; cmp byte ptr [edi + eax + 1], dl
        db 00Fh, 095h, 0C2h   ; setne dl
        db 033h, 0C0h   ; xor eax, eax
        db 038h, 001h   ; cmp byte ptr [ecx], al
        db 00Fh, 095h, 0C0h   ; setne al
        db 08Dh, 00Ch, 050h   ; lea ecx, [eax + edx*2]
        db 00Bh, 0F1h   ; or esi, ecx
$L_34b511:
        db 04Eh   ; dec esi
        db 00Fh, 084h, 0A6h, 001h, 000h, 000h   ; je 0x34b6be
        db 04Eh   ; dec esi
        db 00Fh, 084h, 09Ch, 000h, 000h, 000h   ; je 0x34b5bb
        db 04Eh   ; dec esi
        db 00Fh, 085h, 033h, 002h, 000h, 000h   ; jne 0x34b759
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 0BEh   ; mov esi, 0x536870
        dd _S
        db 08Dh, 07Ch, 024h, 06Ch   ; lea edi, [esp + 0x6c]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 0BEh, 008h, 000h, 000h, 000h   ; mov esi, 8
        db 0EBh, 003h   ; jmp 0x34b540
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34b540:
        db 06Ah, 008h   ; push 8
        db 0FFh, 015h   ; call dword ptr [0x508280]
        dd _EVEN
        db 08Bh, 015h   ; mov edx, dword ptr [0x53687c]
        dd _S+00Ch
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536884]
        dd _S+014h
        db 08Dh, 044h, 02Ah, 0E0h   ; lea eax, [edx + ebp - 0x20]
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+008h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+00Ch
        db 0A1h   ; mov eax, dword ptr [0x53688c]
        dd _S+01Ch
        db 08Dh, 044h, 028h, 0E0h   ; lea eax, [eax + ebp - 0x20]
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 044h, 024h, 064h   ; mov eax, dword ptr [esp + 0x64]
        db 003h, 0C8h   ; add ecx, eax
        db 003h, 0D0h   ; add edx, eax
        db 089h, 00Dh   ; mov dword ptr [0x536884], ecx
        dd _S+014h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536874]
        dd _S+004h
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 054h, 024h, 03Ch   ; mov edx, dword ptr [esp + 0x3c]
        db 08Dh, 004h, 011h   ; lea eax, [ecx + edx]
        db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xa4]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 04Eh   ; dec esi
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
        db 075h, 08Ah   ; jne 0x34b540
        db 0E9h, 08Ah, 001h, 000h, 000h   ; jmp 0x34b745
$L_34b5bb:
        db 08Bh, 015h   ; mov edx, dword ptr [0x536888]
        dd _S+018h
        db 0B8h, 010h, 000h, 000h, 000h   ; mov eax, 0x10
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 0BEh   ; mov esi, 0x536870
        dd _S
        db 08Dh, 07Ch, 024h, 06Ch   ; lea edi, [esp + 0x6c]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 035h   ; mov esi, dword ptr [0x53687c]
        dd _S+00Ch
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x536878]
        dd _S+008h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x53688c]
        dd _S+01Ch
        db 003h, 0F0h   ; add esi, eax
        db 003h, 0F8h   ; add edi, eax
        db 003h, 0D0h   ; add edx, eax
        db 003h, 0C8h   ; add ecx, eax
        db 0A1h   ; mov eax, dword ptr [0x536880]
        dd _S+010h
        db 089h, 035h   ; mov dword ptr [0x53687c], esi
        dd _S+00Ch
        db 0BEh, 008h, 000h, 000h, 000h   ; mov esi, 8
        db 003h, 0C6h   ; add eax, esi
        db 089h, 03Dh   ; mov dword ptr [0x536878], edi
        dd _S+008h
        db 08Bh, 03Dh   ; mov edi, dword ptr [0x536884]
        dd _S+014h
        db 089h, 015h   ; mov dword ptr [0x536888], edx
        dd _S+018h
        db 08Bh, 015h   ; mov edx, dword ptr [0x536870]
        dd _S
        db 089h, 00Dh   ; mov dword ptr [0x53688c], ecx
        dd _S+01Ch
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536874]
        dd _S+004h
        db 0A3h   ; mov dword ptr [0x536880], eax
        dd _S+010h
        db 08Bh, 044h, 024h, 034h   ; mov eax, dword ptr [esp + 0x34]
        db 003h, 0FEh   ; add edi, esi
        db 003h, 0D0h   ; add edx, eax
        db 003h, 0C8h   ; add ecx, eax
        db 089h, 03Dh   ; mov dword ptr [0x536884], edi
        dd _S+014h
        db 089h, 015h   ; mov dword ptr [0x536870], edx
        dd _S
        db 089h, 00Dh   ; mov dword ptr [0x536874], ecx
        dd _S+004h
$L_34b647:
        db 06Ah, 004h   ; push 4
        db 0FFh, 015h   ; call dword ptr [0x508280]
        dd _EVEN
        db 08Bh, 015h   ; mov edx, dword ptr [0x53687c]
        dd _S+00Ch
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536884]
        dd _S+014h
        db 08Dh, 044h, 02Ah, 0F0h   ; lea eax, [edx + ebp - 0x10]
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+008h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+00Ch
        db 0A1h   ; mov eax, dword ptr [0x53688c]
        dd _S+01Ch
        db 08Dh, 044h, 028h, 0F0h   ; lea eax, [eax + ebp - 0x10]
        db 003h, 0CBh   ; add ecx, ebx
        db 003h, 0D3h   ; add edx, ebx
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 089h, 00Dh   ; mov dword ptr [0x536884], ecx
        dd _S+014h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536874]
        dd _S+004h
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Dh, 004h, 011h   ; lea eax, [ecx + edx]
        db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xa4]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 04Eh   ; dec esi
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
        db 075h, 08Eh   ; jne 0x34b647
        db 0E9h, 087h, 000h, 000h, 000h   ; jmp 0x34b745
$L_34b6be:
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 0BEh   ; mov esi, 0x536870
        dd _S
        db 08Dh, 07Ch, 024h, 06Ch   ; lea edi, [esp + 0x6c]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 0BEh, 008h, 000h, 000h, 000h   ; mov esi, 8
$L_34b6d3:
        db 06Ah, 004h   ; push 4
        db 0FFh, 015h   ; call dword ptr [0x508280]
        dd _EVEN
        db 08Bh, 015h   ; mov edx, dword ptr [0x53687c]
        dd _S+00Ch
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536884]
        dd _S+014h
        db 08Dh, 044h, 02Ah, 0F0h   ; lea eax, [edx + ebp - 0x10]
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+008h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+00Ch
        db 0A1h   ; mov eax, dword ptr [0x53688c]
        dd _S+01Ch
        db 08Dh, 044h, 028h, 0F0h   ; lea eax, [eax + ebp - 0x10]
        db 003h, 0CBh   ; add ecx, ebx
        db 003h, 0D3h   ; add edx, ebx
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 089h, 00Dh   ; mov dword ptr [0x536884], ecx
        dd _S+014h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536874]
        dd _S+004h
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Dh, 004h, 011h   ; lea eax, [ecx + edx]
        db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xa4]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 04Eh   ; dec esi
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
        db 075h, 08Eh   ; jne 0x34b6d3
$L_34b745:
        db 08Dh, 074h, 024h, 06Ch   ; lea esi, [esp + 0x6c]
        db 0BFh   ; mov edi, 0x536870
        dd _S
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 07Ch, 024h, 010h   ; mov edi, dword ptr [esp + 0x10]
$L_34b759:
        db 0A1h   ; mov eax, dword ptr [0x536878]
        dd _S+008h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536888]
        dd _S+018h
        db 08Bh, 035h   ; mov esi, dword ptr [0x53687c]
        dd _S+00Ch
        db 0BAh, 020h, 000h, 000h, 000h   ; mov edx, 0x20
        db 003h, 0C2h   ; add eax, edx
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+008h
        db 0A1h   ; mov eax, dword ptr [0x53688c]
        dd _S+01Ch
        db 003h, 0C2h   ; add eax, edx
        db 003h, 0CAh   ; add ecx, edx
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 089h, 00Dh   ; mov dword ptr [0x536888], ecx
        dd _S+018h
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536884]
        dd _S+014h
        db 003h, 0F2h   ; add esi, edx
        db 0B8h, 010h, 000h, 000h, 000h   ; mov eax, 0x10
        db 003h, 0C8h   ; add ecx, eax
        db 089h, 035h   ; mov dword ptr [0x53687c], esi
        dd _S+00Ch
        db 08Bh, 035h   ; mov esi, dword ptr [0x536880]
        dd _S+010h
        db 003h, 0F0h   ; add esi, eax
        db 0A1h   ; mov eax, dword ptr [0x536870]
        dd _S
        db 089h, 00Dh   ; mov dword ptr [0x536884], ecx
        dd _S+014h
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 003h, 0C9h   ; add ecx, ecx
        db 003h, 0C1h   ; add eax, ecx
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 08Bh, 044h, 024h, 038h   ; mov eax, dword ptr [esp + 0x38]
        db 003h, 0C2h   ; add eax, edx
        db 089h, 035h   ; mov dword ptr [0x536880], esi
        dd _S+010h
        db 08Bh, 035h   ; mov esi, dword ptr [0x536874]
        dd _S+004h
        db 003h, 0F1h   ; add esi, ecx
        db 08Bh, 04Ch, 024h, 050h   ; mov ecx, dword ptr [esp + 0x50]
        db 089h, 044h, 024h, 038h   ; mov dword ptr [esp + 0x38], eax
        db 08Bh, 044h, 024h, 060h   ; mov eax, dword ptr [esp + 0x60]
        db 003h, 0C2h   ; add eax, edx
        db 08Bh, 054h, 024h, 028h   ; mov edx, dword ptr [esp + 0x28]
        db 083h, 0C7h, 002h   ; add edi, 2
        db 083h, 0C1h, 002h   ; add ecx, 2
        db 03Bh, 0C2h   ; cmp eax, edx
        db 089h, 035h   ; mov dword ptr [0x536874], esi
        dd _S+004h
        db 089h, 07Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], edi
        db 089h, 04Ch, 024h, 050h   ; mov dword ptr [esp + 0x50], ecx
        db 089h, 044h, 024h, 060h   ; mov dword ptr [esp + 0x60], eax
        db 00Fh, 08Eh, 0D1h, 0FCh, 0FFh, 0FFh   ; jle 0x34b4d6
        db 08Bh, 04Ch, 024h, 048h   ; mov ecx, dword ptr [esp + 0x48]
        db 08Bh, 074h, 024h, 058h   ; mov esi, dword ptr [esp + 0x58]
$L_34b80d:
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        db 08Bh, 044h, 024h, 028h   ; mov eax, dword ptr [esp + 0x28]
        db 083h, 0C2h, 00Fh   ; add edx, 0xf
        db 03Bh, 0D0h   ; cmp edx, eax
        db 00Fh, 08Fh, 00Ah, 001h, 000h, 000h   ; jg 0x34b92a
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 0B6h, 007h   ; movzx eax, byte ptr [edi]
        db 074h, 006h   ; je 0x34b831
        db 00Fh, 0B6h, 014h, 017h   ; movzx edx, byte ptr [edi + edx]
        db 00Bh, 0C2h   ; or eax, edx
$L_34b831:
        db 047h   ; inc edi
        db 085h, 0C0h   ; test eax, eax
        db 089h, 07Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], edi
        db 00Fh, 084h, 0A2h, 000h, 000h, 000h   ; je 0x34b8e0
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 0BEh   ; mov esi, 0x536870
        dd _S
        db 08Dh, 07Ch, 024h, 06Ch   ; lea edi, [esp + 0x6c]
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 0BEh, 008h, 000h, 000h, 000h   ; mov esi, 8
$L_34b853:
        db 06Ah, 004h   ; push 4
        db 0FFh, 015h   ; call dword ptr [0x508280]
        dd _EVEN
        db 0A1h   ; mov eax, dword ptr [0x53687c]
        dd _S+00Ch
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x53688c]
        dd _S+01Ch
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 08Dh, 044h, 028h, 0F0h   ; lea eax, [eax + ebp - 0x10]
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+008h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+00Ch
        db 08Dh, 044h, 029h, 0F0h   ; lea eax, [ecx + ebp - 0x10]
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x536884]
        dd _S+014h
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 003h, 0D3h   ; add edx, ebx
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 044h, 024h, 02Ch   ; mov eax, dword ptr [esp + 0x2c]
        db 003h, 0CBh   ; add ecx, ebx
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 015h   ; mov edx, dword ptr [0x536874]
        dd _S+004h
        db 003h, 0C2h   ; add eax, edx
        db 089h, 00Dh   ; mov dword ptr [0x536884], ecx
        dd _S+014h
        db 08Bh, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xa4]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C1h   ; add eax, ecx
        db 04Eh   ; dec esi
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
        db 075h, 08Fh   ; jne 0x34b853
        db 0B9h, 00Ah, 000h, 000h, 000h   ; mov ecx, 0xa
        db 08Dh, 074h, 024h, 06Ch   ; lea esi, [esp + 0x6c]
        db 0BFh   ; mov edi, 0x536870
        dd _S
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 07Ch, 024h, 010h   ; mov edi, dword ptr [esp + 0x10]
        db 08Bh, 04Ch, 024h, 048h   ; mov ecx, dword ptr [esp + 0x48]
        db 08Bh, 074h, 024h, 058h   ; mov esi, dword ptr [esp + 0x58]
$L_34b8e0:
        db 08Bh, 015h   ; mov edx, dword ptr [0x53687c]
        dd _S+00Ch
        db 0B8h, 010h, 000h, 000h, 000h   ; mov eax, 0x10
        db 003h, 0D0h   ; add edx, eax
        db 089h, 015h   ; mov dword ptr [0x53687c], edx
        dd _S+00Ch
        db 001h, 005h   ; add dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 0B8h, 008h, 000h, 000h, 000h   ; mov eax, 8
        db 003h, 0D0h   ; add edx, eax
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 015h   ; mov edx, dword ptr [0x536884]
        dd _S+014h
        db 003h, 0D0h   ; add edx, eax
        db 0A1h   ; mov eax, dword ptr [0x536874]
        dd _S+004h
        db 089h, 015h   ; mov dword ptr [0x536884], edx
        dd _S+014h
        db 08Bh, 054h, 024h, 034h   ; mov edx, dword ptr [esp + 0x34]
        db 003h, 0C2h   ; add eax, edx
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
$L_34b92a:
        db 0A1h   ; mov eax, dword ptr [0x53687c]
        dd _S+00Ch
        db 08Bh, 015h   ; mov edx, dword ptr [0x53688c]
        dd _S+01Ch
        db 003h, 0C6h   ; add eax, esi
        db 0A3h   ; mov dword ptr [0x536878], eax
        dd _S+008h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53687c], eax
        dd _S+00Ch
        db 08Dh, 004h, 016h   ; lea eax, [esi + edx]
        db 08Bh, 015h   ; mov edx, dword ptr [0x536880]
        dd _S+010h
        db 0A3h   ; mov dword ptr [0x536888], eax
        dd _S+018h
        db 003h, 0C5h   ; add eax, ebp
        db 0A3h   ; mov dword ptr [0x53688c], eax
        dd _S+01Ch
        db 08Bh, 044h, 024h, 044h   ; mov eax, dword ptr [esp + 0x44]
        db 003h, 0D0h   ; add edx, eax
        db 089h, 015h   ; mov dword ptr [0x536880], edx
        dd _S+010h
        db 08Bh, 015h   ; mov edx, dword ptr [0x536884]
        dd _S+014h
        db 003h, 0D0h   ; add edx, eax
        db 0A1h   ; mov eax, dword ptr [0x536874]
        dd _S+004h
        db 003h, 0C1h   ; add eax, ecx
        db 089h, 015h   ; mov dword ptr [0x536884], edx
        dd _S+014h
        db 08Bh, 094h, 024h, 0A4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xa4]
        db 0A3h   ; mov dword ptr [0x536870], eax
        dd _S
        db 003h, 0C2h   ; add eax, edx
        db 08Bh, 054h, 024h, 05Ch   ; mov edx, dword ptr [esp + 0x5c]
        db 0A3h   ; mov dword ptr [0x536874], eax
        dd _S+004h
        db 003h, 07Ch, 024h, 014h   ; add edi, dword ptr [esp + 0x14]
        db 08Bh, 044h, 024h, 020h   ; mov eax, dword ptr [esp + 0x20]
        db 083h, 0C0h, 010h   ; add eax, 0x10
        db 03Bh, 0C2h   ; cmp eax, edx
        db 089h, 07Ch, 024h, 010h   ; mov dword ptr [esp + 0x10], edi
        db 089h, 044h, 024h, 020h   ; mov dword ptr [esp + 0x20], eax
        db 00Fh, 08Eh, 0F5h, 0FAh, 0FFh, 0FFh   ; jle 0x34b4a0
$L_34b9ab:
        db 08Bh, 044h, 024h, 01Ch   ; mov eax, dword ptr [esp + 0x1c]
        db 085h, 0C0h   ; test eax, eax
        db 08Bh, 07Ch, 024h, 030h   ; mov edi, dword ptr [esp + 0x30]
        db 08Bh, 05Ch, 024h, 054h   ; mov ebx, dword ptr [esp + 0x54]
        db 074h, 072h   ; je 0x34ba2d
        db 08Bh, 094h, 024h, 0D4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd4]
        db 08Bh, 08Ch, 024h, 0BCh, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xbc]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0D4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd4]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0D4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd4]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 058h   ; mov edx, dword ptr [esp + 0x58]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0C4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xc4]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 053h   ; push ebx
        db 083h, 0E0h, 0F0h   ; and eax, 0xfffffff0
        db 057h   ; push edi
        db 02Bh, 0C8h   ; sub ecx, eax
        db 051h   ; push ecx
        db 08Bh, 08Ch, 024h, 0D4h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xd4]
        db 051h   ; push ecx
        db 08Dh, 00Ch, 010h   ; lea ecx, [eax + edx]
        db 00Fh, 0AFh, 044h, 024h, 044h   ; imul eax, dword ptr [esp + 0x44]
        db 08Bh, 094h, 024h, 0D0h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd0]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 064h   ; mov ecx, dword ptr [esp + 0x64]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0C8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xc8]
        db 051h   ; push ecx
        db 052h   ; push edx
        db 003h, 084h, 024h, 0CCh, 000h, 000h, 000h   ; add eax, dword ptr [esp + 0xcc]
        db 08Bh, 094h, 024h, 0C8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xc8]
        db 050h   ; push eax
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
$L_34ba2d:
        db 08Bh, 084h, 024h, 0C0h, 000h, 000h, 000h   ; mov eax, dword ptr [esp + 0xc0]
        db 0A8h, 00Fh   ; test al, 0xf
        db 00Fh, 084h, 0B2h, 000h, 000h, 000h   ; je 0x34baee
        db 083h, 0E0h, 0F0h   ; and eax, 0xfffffff0
        db 089h, 044h, 024h, 014h   ; mov dword ptr [esp + 0x14], eax
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 0F7h, 0E1h   ; mul ecx
        db 08Bh, 08Ch, 024h, 0C0h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xc0]
        db 0F7h, 0F1h   ; div ecx
        db 08Bh, 0F0h   ; mov esi, eax
        db 08Bh, 044h, 024h, 040h   ; mov eax, dword ptr [esp + 0x40]
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 00Fh, 0AFh, 0C5h   ; imul eax, ebp
        db 00Fh, 0AFh, 08Ch, 024h, 0A4h, 000h, 000h, 000h   ; imul ecx, dword ptr [esp + 0xa4]
        db 089h, 074h, 024h, 03Ch   ; mov dword ptr [esp + 0x3c], esi
        db 089h, 044h, 024h, 014h   ; mov dword ptr [esp + 0x14], eax
        db 089h, 04Ch, 024h, 044h   ; mov dword ptr [esp + 0x44], ecx
        db 08Bh, 044h, 024h, 03Ch   ; mov eax, dword ptr [esp + 0x3c]
        db 08Bh, 04Ch, 024h, 044h   ; mov ecx, dword ptr [esp + 0x44]
        db 0F7h, 0E1h   ; mul ecx
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 0F7h, 0F1h   ; div ecx
        db 08Bh, 094h, 024h, 0D4h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd4]
        db 08Bh, 08Ch, 024h, 0D0h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xd0]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0D0h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd0]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 054h   ; mov ecx, dword ptr [esp + 0x54]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0C8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xc8]
        db 051h   ; push ecx
        db 08Bh, 08Ch, 024h, 0C8h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xc8]
        db 053h   ; push ebx
        db 02Bh, 0FEh   ; sub edi, esi
        db 057h   ; push edi
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0D0h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xd0]
        db 003h, 0F1h   ; add esi, ecx
        db 08Bh, 08Ch, 024h, 0CCh, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xcc]
        db 056h   ; push esi
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 064h   ; mov edx, dword ptr [esp + 0x64]
        db 051h   ; push ecx
        db 08Bh, 08Ch, 024h, 0C8h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xc8]
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0C8h, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xc8]
        db 003h, 0C1h   ; add eax, ecx
        db 050h   ; push eax
        db 052h   ; push edx
        db 08Bh, 094h, 024h, 0CCh, 000h, 000h, 000h   ; mov edx, dword ptr [esp + 0xcc]
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
$L_34baee:
        db 0A1h   ; mov eax, dword ptr [0x51ef5c]
        dd _decode_use_MMX
        db 085h, 0C0h   ; test eax, eax
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 074h, 002h   ; je 0x34bafd
        db 00Fh, 077h   ; emms 
$L_34bafd:
        db 081h, 0C4h, 084h, 000h, 000h, 000h   ; add esp, 0x84
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
?YUV_blit_mask@@YAXPAXKKKPAEK0KKKKKKK0PAUBLITS@@@Z ENDP
segbm ENDS

segw32 SEGMENT PARA PUBLIC ALIAS('BINK32') 'CODE'

; // match: _YUV_blit_32bpp@52 @ 0x0034EBD0
; // sp-match: _YUV_blit_32bpp@52 @ 0x0025EBD0
_YUV_blit_32bpp@52 PROC PUBLIC
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 068h   ; push 0x538900
        dd _blits32
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
        db 0C2h, 034h, 000h   ; ret 0x34
_YUV_blit_32bpp@52 ENDP
segw32 ENDS

segw32a SEGMENT PARA PUBLIC ALIAS('BINK32A') 'CODE'

; // match: _YUV_blit_32abpp@52 @ 0x0034FFA0
; // sp-match: _YUV_blit_32abpp@52 @ 0x0025FFA0
_YUV_blit_32abpp@52 PROC PUBLIC
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 068h   ; push 0x5389c0
        dd _blits32a
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
        db 0C2h, 034h, 000h   ; ret 0x34
_YUV_blit_32abpp@52 ENDP
segw32a ENDS

segw16 SEGMENT PARA PUBLIC ALIAS('BINK16') 'CODE'

; // match: _YUV_blit_16bpp@52 @ 0x00351290
; // sp-match: _YUV_blit_16bpp@52 @ 0x00261290
_YUV_blit_16bpp@52 PROC PUBLIC
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 068h   ; push 0x538a80
        dd _blits16
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
        db 0C2h, 034h, 000h   ; ret 0x34
_YUV_blit_16bpp@52 ENDP
segw16 ENDS

segw4444 SEGMENT PARA PUBLIC ALIAS('BINK4444') 'CODE'

; // match: _YUV_blit_16a4bpp@52 @ 0x00352760
; // sp-match: _YUV_blit_16a4bpp@52 @ 0x00262760
_YUV_blit_16a4bpp@52 PROC PUBLIC
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 068h   ; push 0x538b40
        dd _blits16a4
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
        db 0C2h, 034h, 000h   ; ret 0x34
_YUV_blit_16a4bpp@52 ENDP
segw4444 ENDS

segw5551 SEGMENT PARA PUBLIC ALIAS('BINK5551') 'CODE'

; // match: _YUV_blit_16a1bpp@52 @ 0x00353C80
; // sp-match: _YUV_blit_16a1bpp@52 @ 0x00263C80
_YUV_blit_16a1bpp@52 PROC PUBLIC
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 08Bh, 04Ch, 024h, 034h   ; mov ecx, dword ptr [esp + 0x34]
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 068h   ; push 0x538c00
        dd _blits16a1
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 030h   ; mov eax, dword ptr [esp + 0x30]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 030h   ; mov ecx, dword ptr [esp + 0x30]
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 030h   ; mov edx, dword ptr [esp + 0x30]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 052h   ; push edx
        db 08Bh, 054h, 024h, 038h   ; mov edx, dword ptr [esp + 0x38]
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
        db 0C2h, 034h, 000h   ; ret 0x34
_YUV_blit_16a1bpp@52 ENDP
segw5551 ENDS

segwyuy2 SEGMENT PARA PUBLIC ALIAS('BINKYUY2') 'CODE'

; // match: _YUV_blit_YUY2@52 @ 0x00354D70
; // sp-match: _YUV_blit_YUY2@52 @ 0x00264D70
_YUV_blit_YUY2@52 PROC PUBLIC
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 0C2h   ; mov eax, edx
        db 053h   ; push ebx
        db 08Bh, 05Ch, 024h, 00Ch   ; mov ebx, dword ptr [esp + 0xc]
        db 024h, 003h   ; and al, 3
        db 03Ch, 002h   ; cmp al, 2
        db 056h   ; push esi
        db 075h, 004h   ; jne 0x354d86
        db 043h   ; inc ebx
        db 083h, 0E2h, 0FCh   ; and edx, 0xfffffffc
$L_354d86:
        db 0F6h, 0C3h, 001h   ; test bl, 1
        db 08Bh, 04Ch, 024h, 020h   ; mov ecx, dword ptr [esp + 0x20]
        db 074h, 00Dh   ; je 0x354d9c
        db 0F6h, 0C1h, 001h   ; test cl, 1
        db 074h, 001h   ; je 0x354d95
        db 041h   ; inc ecx
$L_354d95:
        db 08Bh, 044h, 024h, 028h   ; mov eax, dword ptr [esp + 0x28]
        db 043h   ; inc ebx
        db 0EBh, 00Ah   ; jmp 0x354da6
$L_354d9c:
        db 0F6h, 0C1h, 001h   ; test cl, 1
        db 08Bh, 044h, 024h, 028h   ; mov eax, dword ptr [esp + 0x28]
        db 074h, 002h   ; je 0x354da7
        db 041h   ; inc ecx
$L_354da6:
        db 048h   ; dec eax
$L_354da7:
        db 0A8h, 001h   ; test al, 1
        db 074h, 001h   ; je 0x354dac
        db 048h   ; dec eax
$L_354dac:
        db 08Bh, 074h, 024h, 038h   ; mov esi, dword ptr [esp + 0x38]
        db 068h   ; push 0x538cc0
        dd _blitsyuy2
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 044h   ; mov esi, dword ptr [esp + 0x44]
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 040h   ; mov esi, dword ptr [esp + 0x40]
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 040h   ; mov esi, dword ptr [esp + 0x40]
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 040h   ; mov esi, dword ptr [esp + 0x40]
        db 056h   ; push esi
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 040h   ; mov eax, dword ptr [esp + 0x40]
        db 050h   ; push eax
        db 08Bh, 044h, 024h, 038h   ; mov eax, dword ptr [esp + 0x38]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 040h   ; mov ecx, dword ptr [esp + 0x40]
        db 051h   ; push ecx
        db 08Bh, 04Ch, 024h, 03Ch   ; mov ecx, dword ptr [esp + 0x3c]
        db 050h   ; push eax
        db 051h   ; push ecx
        db 053h   ; push ebx
        call ?YUV_blit@@YAXPAXKKK0KKKKKKK0PAUBLITS@@@Z   ; 0x34ACD0
        db 083h, 0C4h, 034h   ; add esp, 0x34
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 034h, 000h   ; ret 0x34
        db 0CCh   ; int3 
        db 0CCh   ; int3 
_YUV_blit_YUY2@52 ENDP
segwyuy2 ENDS

        END
