; codfh-match: XDK Intel IPP signal-processing pieces (voice)
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN _ippsFree@4:NEAR
EXTERN _ippsMalloc_8u@4:NEAR
EXTERN _ippsMin_32f@12:NEAR
EXTERN _ipps_createTabTwdCcsRec_32f:NEAR
EXTERN _ownsMinIndx_32f_M6:NEAR
EXTERN _sub_28BF18:NEAR
EXTERN _sub_28C028:NEAR
EXTERN _sub_28DB04:NEAR
EXTERN _unk_53A380:BYTE
EXTERN _unk_53A384:BYTE
EXTERN _unk_53A388:BYTE
EXTERN _unk_53A38C:BYTE
EXTERN _unk_53A3D8:BYTE
EXTERN _unk_53A400:BYTE
EXTERN _unk_53A428:BYTE
EXTERN _unk_53A42C:BYTE



seg2 SEGMENT DWORD PUBLIC ALIAS('.text') 'CODE'

; // match: _ippsFFTInitAlloc_R_32f@16 @ 0x0028C0F8
PUBLIC _ippsFFTInitAlloc_R_32f@16
_ippsFFTInitAlloc_R_32f@16:
        db 053h   ; push ebx
        db 08Bh, 0DCh   ; mov ebx, esp
        db 083h, 0E4h, 0F0h   ; and esp, 0xfffffff0
        db 057h   ; push edi
        db 056h   ; push esi
        db 055h   ; push ebp
        db 083h, 0ECh, 024h   ; sub esp, 0x24
        db 08Bh, 043h, 008h   ; mov eax, dword ptr [ebx + 8]
        db 08Bh, 06Bh, 00Ch   ; mov ebp, dword ptr [ebx + 0xc]
        db 08Bh, 07Bh, 010h   ; mov edi, dword ptr [ebx + 0x10]
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 00Ah, 002h, 000h, 000h   ; je 0x28c31f
        db 085h, 0EDh   ; test ebp, ebp
        db 07Ch, 005h   ; jl 0x28c11e
        db 083h, 0FDh, 01Eh   ; cmp ebp, 0x1e
        db 07Eh, 011h   ; jle 0x28c12f
$L_28c11e:
        db 0B8h, 0F1h, 0FFh, 0FFh, 0FFh   ; mov eax, 0xfffffff1
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 010h, 000h   ; ret 0x10
$L_28c12f:
        db 06Ah, 04Ch   ; push 0x4c
        call _ippsMalloc_8u@4   ; 0x2952F4
        db 08Bh, 0F0h   ; mov esi, eax
        db 085h, 0F6h   ; test esi, esi
        db 00Fh, 084h, 0F0h, 001h, 000h, 000h   ; je 0x28c330
        db 033h, 0D2h   ; xor edx, edx
        db 081h, 0E2h, 0FFh, 000h, 000h, 000h   ; and edx, 0xff
        db 08Bh, 0C2h   ; mov eax, edx
        db 0C1h, 0E0h, 008h   ; shl eax, 8
        db 00Bh, 0D0h   ; or edx, eax
        db 08Bh, 0C2h   ; mov eax, edx
        db 0C1h, 0E0h, 010h   ; shl eax, 0x10
        db 00Bh, 0D0h   ; or edx, eax
        db 089h, 016h   ; mov dword ptr [esi], edx
        db 089h, 056h, 004h   ; mov dword ptr [esi + 4], edx
        db 089h, 056h, 008h   ; mov dword ptr [esi + 8], edx
        db 089h, 056h, 00Ch   ; mov dword ptr [esi + 0xc], edx
        db 089h, 056h, 010h   ; mov dword ptr [esi + 0x10], edx
        db 089h, 056h, 014h   ; mov dword ptr [esi + 0x14], edx
        db 089h, 056h, 018h   ; mov dword ptr [esi + 0x18], edx
        db 089h, 056h, 01Ch   ; mov dword ptr [esi + 0x1c], edx
        db 089h, 056h, 020h   ; mov dword ptr [esi + 0x20], edx
        db 089h, 056h, 024h   ; mov dword ptr [esi + 0x24], edx
        db 089h, 056h, 028h   ; mov dword ptr [esi + 0x28], edx
        db 089h, 056h, 02Ch   ; mov dword ptr [esi + 0x2c], edx
        db 089h, 056h, 030h   ; mov dword ptr [esi + 0x30], edx
        db 089h, 056h, 034h   ; mov dword ptr [esi + 0x34], edx
        db 089h, 056h, 038h   ; mov dword ptr [esi + 0x38], edx
        db 089h, 056h, 03Ch   ; mov dword ptr [esi + 0x3c], edx
        db 089h, 056h, 040h   ; mov dword ptr [esi + 0x40], edx
        db 089h, 056h, 044h   ; mov dword ptr [esi + 0x44], edx
        db 089h, 056h, 048h   ; mov dword ptr [esi + 0x48], edx
        db 0C7h, 006h, 006h, 000h, 000h, 000h   ; mov dword ptr [esi], 6
        db 08Bh, 053h, 014h   ; mov edx, dword ptr [ebx + 0x14]
        db 08Bh, 0CDh   ; mov ecx, ebp
        db 089h, 06Eh, 004h   ; mov dword ptr [esi + 4], ebp
        db 089h, 056h, 014h   ; mov dword ptr [esi + 0x14], edx
        db 0BAh, 001h, 000h, 000h, 000h   ; mov edx, 1
        db 0D3h, 0E2h   ; shl edx, cl
        db 083h, 0FFh, 008h   ; cmp edi, 8
        db 00Fh, 084h, 063h, 001h, 000h, 000h   ; je 0x28c312
        db 083h, 0FFh, 004h   ; cmp edi, 4
        db 00Fh, 084h, 031h, 001h, 000h, 000h   ; je 0x28c2e9
        db 083h, 0FFh, 001h   ; cmp edi, 1
        db 00Fh, 084h, 000h, 001h, 000h, 000h   ; je 0x28c2c1
        db 083h, 0FFh, 002h   ; cmp edi, 2
        db 074h, 01Bh   ; je 0x28c1e1
        db 0BFh, 0F0h, 0FFh, 0FFh, 0FFh   ; mov edi, 0xfffffff0
$L_28c1cb:
        db 089h, 034h, 024h   ; mov dword ptr [esp], esi
        call _sub_28C028   ; 0x28C028
        db 08Bh, 0C7h   ; mov eax, edi
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 010h, 000h   ; ret 0x10
$L_28c1e1:
        db 0C7h, 046h, 008h, 000h, 000h, 000h, 000h   ; mov dword ptr [esi + 8], 0
        db 0F3h, 00Fh, 010h, 005h   ; movss xmm0, dword ptr [0x53a3d8]
        dd _unk_53A3D8
        db 0C7h, 046h, 00Ch, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 1
        db 0F3h, 00Fh, 02Ah, 0CAh   ; cvtsi2ss xmm1, edx
        db 0F3h, 00Fh, 05Eh, 0C1h   ; divss xmm0, xmm1
        db 0F3h, 00Fh, 011h, 046h, 010h   ; movss dword ptr [esi + 0x10], xmm0
$L_28c204:
        db 083h, 0FDh, 003h   ; cmp ebp, 3
        db 07Fh, 01Ah   ; jg 0x28c223
        db 0C7h, 046h, 018h, 000h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x18], 0
        db 08Bh, 053h, 008h   ; mov edx, dword ptr [ebx + 8]
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 032h   ; mov dword ptr [edx], esi
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 010h, 000h   ; ret 0x10
$L_28c223:
        db 089h, 02Ch, 024h   ; mov dword ptr [esp], ebp
        call _ipps_createTabTwdBase_32f   ; 0x293BB4
        db 089h, 044h, 024h, 014h   ; mov dword ptr [esp + 0x14], eax
        db 08Bh, 0D0h   ; mov edx, eax
        db 085h, 0D2h   ; test edx, edx
        db 075h, 007h   ; jne 0x28c23c
        db 0BFh, 0F7h, 0FFh, 0FFh, 0FFh   ; mov edi, 0xfffffff7
        db 0EBh, 08Fh   ; jmp 0x28c1cb
$L_28c23c:
        db 089h, 034h, 024h   ; mov dword ptr [esp], esi
        db 08Dh, 055h, 0FFh   ; lea edx, [ebp - 1]
        db 08Bh, 0F8h   ; mov edi, eax
        db 089h, 054h, 024h, 004h   ; mov dword ptr [esp + 4], edx
        db 089h, 07Ch, 024h, 008h   ; mov dword ptr [esp + 8], edi
        db 089h, 06Ch, 024h, 00Ch   ; mov dword ptr [esp + 0xc], ebp
        call _sub_28BF18   ; 0x28BF18
        db 08Bh, 0F8h   ; mov edi, eax
        db 085h, 0FFh   ; test edi, edi
        db 075h, 03Ah   ; jne 0x28c295
        db 089h, 02Ch, 024h   ; mov dword ptr [esp], ebp
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 089h, 054h, 024h, 004h   ; mov dword ptr [esp + 4], edx
        call _ipps_createTabTwdRealRec_32f   ; 0x2953A4
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 085h, 0C0h   ; test eax, eax
        db 075h, 007h   ; jne 0x28c279
        db 0BFh, 0F7h, 0FFh, 0FFh, 0FFh   ; mov edi, 0xfffffff7
        db 0EBh, 01Ch   ; jmp 0x28c295
$L_28c279:
        db 089h, 02Ch, 024h   ; mov dword ptr [esp], ebp
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 089h, 054h, 024h, 004h   ; mov dword ptr [esp + 4], edx
        call _ipps_createTabTwdCcsRec_32f   ; 0x2955D4
        db 089h, 046h, 030h   ; mov dword ptr [esi + 0x30], eax
        db 085h, 0C0h   ; test eax, eax
        db 075h, 014h   ; jne 0x28c2a4
        db 0BFh, 0F7h, 0FFh, 0FFh, 0FFh   ; mov edi, 0xfffffff7
$L_28c295:
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 052h   ; push edx
        call _ippsFree@4   ; 0x295374
        db 0E9h, 027h, 0FFh, 0FFh, 0FFh   ; jmp 0x28c1cb
$L_28c2a4:
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 052h   ; push edx
        call _ippsFree@4   ; 0x295374
        db 08Bh, 053h, 008h   ; mov edx, dword ptr [ebx + 8]
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 032h   ; mov dword ptr [edx], esi
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 010h, 000h   ; ret 0x10
$L_28c2c1:
        db 0C7h, 046h, 008h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 8], 1
        db 0F3h, 00Fh, 010h, 005h   ; movss xmm0, dword ptr [0x53a3d8]
        dd _unk_53A3D8
        db 0C7h, 046h, 00Ch, 000h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 0
        db 0F3h, 00Fh, 02Ah, 0CAh   ; cvtsi2ss xmm1, edx
        db 0F3h, 00Fh, 05Eh, 0C1h   ; divss xmm0, xmm1
        db 0F3h, 00Fh, 011h, 046h, 010h   ; movss dword ptr [esi + 0x10], xmm0
        db 0E9h, 01Bh, 0FFh, 0FFh, 0FFh   ; jmp 0x28c204
$L_28c2e9:
        db 0BFh, 001h, 000h, 000h, 000h   ; mov edi, 1
        db 0F3h, 00Fh, 010h, 00Dh   ; movss xmm1, dword ptr [0x53a3d8]
        dd _unk_53A3D8
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        db 089h, 07Eh, 00Ch   ; mov dword ptr [esi + 0xc], edi
        db 0F3h, 00Fh, 02Ah, 0C2h   ; cvtsi2ss xmm0, edx
        db 0F3h, 00Fh, 051h, 0D0h   ; sqrtss xmm2, xmm0
        db 0F3h, 00Fh, 05Eh, 0CAh   ; divss xmm1, xmm2
        db 0F3h, 00Fh, 011h, 04Eh, 010h   ; movss dword ptr [esi + 0x10], xmm1
        db 0E9h, 0F2h, 0FEh, 0FFh, 0FFh   ; jmp 0x28c204
$L_28c312:
        db 033h, 0D2h   ; xor edx, edx
        db 089h, 056h, 008h   ; mov dword ptr [esi + 8], edx
        db 089h, 056h, 00Ch   ; mov dword ptr [esi + 0xc], edx
        db 0E9h, 0E5h, 0FEh, 0FFh, 0FFh   ; jmp 0x28c204
$L_28c31f:
        db 0B8h, 0F8h, 0FFh, 0FFh, 0FFh   ; mov eax, 0xfffffff8
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 010h, 000h   ; ret 0x10
$L_28c330:
        db 0B8h, 0F7h, 0FFh, 0FFh, 0FFh   ; mov eax, 0xfffffff7
        db 083h, 0C4h, 024h   ; add esp, 0x24
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 010h, 000h   ; ret 0x10
        db 08Dh, 0B4h, 026h, 000h, 000h, 000h, 000h   ; lea esi, [esi]
seg2 ENDS


seg5 SEGMENT DWORD PUBLIC ALIAS('.text') 'CODE'

; // match: _ipps_createTabTwdBase_32f @ 0x00293BB4
PUBLIC _ipps_createTabTwdBase_32f
_ipps_createTabTwdBase_32f:
        db 053h   ; push ebx
        db 08Bh, 0DCh   ; mov ebx, esp
        db 083h, 0E4h, 0F0h   ; and esp, 0xfffffff0
        db 056h   ; push esi
        db 055h   ; push ebp
        db 083h, 0ECh, 018h   ; sub esp, 0x18
        db 08Bh, 04Bh, 008h   ; mov ecx, dword ptr [ebx + 8]
        db 0BDh, 001h, 000h, 000h, 000h   ; mov ebp, 1
        db 0D3h, 0E5h   ; shl ebp, cl
        db 08Bh, 0F5h   ; mov esi, ebp
        db 0D1h, 0FEh   ; sar esi, 1
        db 0C1h, 0EEh, 01Eh   ; shr esi, 0x1e
        db 003h, 0F5h   ; add esi, ebp
        db 0C1h, 0FEh, 002h   ; sar esi, 2
        db 08Dh, 004h, 0B5h, 004h, 000h, 000h, 000h   ; lea eax, [esi*4 + 4]
        db 050h   ; push eax
        call _ippsMalloc_8u@4   ; 0x2952F4
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 072h, 000h, 000h, 000h   ; je 0x293c5c
        db 0DDh, 005h   ; fld qword ptr [0x53a400]
        dd _unk_53A400
        db 033h, 0D2h   ; xor edx, edx
        db 08Bh, 0CDh   ; mov ecx, ebp
        db 089h, 06Ch, 024h, 008h   ; mov dword ptr [esp + 8], ebp
        db 0C1h, 0F9h, 002h   ; sar ecx, 2
        db 0C1h, 0E9h, 01Dh   ; shr ecx, 0x1d
        db 0DBh, 044h, 024h, 008h   ; fild dword ptr [esp + 8]
        db 0DEh, 0F9h   ; fdivp st(1)
        db 003h, 0E9h   ; add ebp, ecx
        db 0C1h, 0FDh, 003h   ; sar ebp, 3
        db 085h, 0EDh   ; test ebp, ebp
        db 07Ch, 020h   ; jl 0x293c2d
        db 0EBh, 009h   ; jmp 0x293c18
        db 090h   ; nop 
        db 08Dh, 074h, 026h, 000h   ; lea esi, [esi]
$L_293c14:
        db 0D9h, 05Ch, 090h, 0FCh   ; fstp dword ptr [eax + edx*4 - 4]
$L_293c18:
        db 089h, 054h, 024h, 008h   ; mov dword ptr [esp + 8], edx
        db 0DBh, 044h, 024h, 008h   ; fild dword ptr [esp + 8]
        db 0D8h, 0C9h   ; fmul st(1)
        db 0D9h, 0FEh   ; fsin 
        db 042h   ; inc edx
        db 03Bh, 0D5h   ; cmp edx, ebp
        db 07Eh, 0EBh   ; jle 0x293c14
        db 0D9h, 05Ch, 090h, 0FCh   ; fstp dword ptr [eax + edx*4 - 4]
$L_293c2d:
        db 045h   ; inc ebp
        db 03Bh, 0EEh   ; cmp ebp, esi
        db 07Fh, 035h   ; jg 0x293c67
        db 0EBh, 004h   ; jmp 0x293c38
$L_293c34:
        db 0D9h, 05Ch, 0A8h, 0FCh   ; fstp dword ptr [eax + ebp*4 - 4]
$L_293c38:
        db 08Bh, 0D6h   ; mov edx, esi
        db 02Bh, 0D5h   ; sub edx, ebp
        db 089h, 054h, 024h, 008h   ; mov dword ptr [esp + 8], edx
        db 0DBh, 044h, 024h, 008h   ; fild dword ptr [esp + 8]
        db 0D8h, 0C9h   ; fmul st(1)
        db 0D9h, 0FFh   ; fcos 
        db 045h   ; inc ebp
        db 03Bh, 0EEh   ; cmp ebp, esi
        db 07Eh, 0E7h   ; jle 0x293c34
        db 0D9h, 05Ch, 0A8h, 0FCh   ; fstp dword ptr [eax + ebp*4 - 4]
        db 0DDh, 0D8h   ; fstp st(0)
        db 083h, 0C4h, 018h   ; add esp, 0x18
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
$L_293c5c:
        db 033h, 0C0h   ; xor eax, eax
        db 083h, 0C4h, 018h   ; add esp, 0x18
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
$L_293c67:
        db 0DDh, 0D8h   ; fstp st(0)
        db 083h, 0C4h, 018h   ; add esp, 0x18
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
        db 08Bh, 0F6h   ; mov esi, esi
seg5 ENDS

seg7 SEGMENT DWORD PUBLIC ALIAS('.text') 'CODE'

; // match: _ipps_createTabTwdRealRec_32f @ 0x002953A4
PUBLIC _ipps_createTabTwdRealRec_32f
_ipps_createTabTwdRealRec_32f:
        db 053h   ; push ebx
        db 08Bh, 0DCh   ; mov ebx, esp
        db 083h, 0E4h, 0F0h   ; and esp, 0xfffffff0
        db 057h   ; push edi
        db 056h   ; push esi
        db 055h   ; push ebp
        db 083h, 0ECh, 014h   ; sub esp, 0x14
        db 08Bh, 04Bh, 008h   ; mov ecx, dword ptr [ebx + 8]
        db 0BEh, 001h, 000h, 000h, 000h   ; mov esi, 1
        db 0D3h, 0E6h   ; shl esi, cl
        db 08Bh, 0EEh   ; mov ebp, esi
        db 0D1h, 0FDh   ; sar ebp, 1
        db 0C1h, 0EDh, 01Eh   ; shr ebp, 0x1e
        db 003h, 0EEh   ; add ebp, esi
        db 0C1h, 0FDh, 002h   ; sar ebp, 2
        db 0B8h, 002h, 000h, 000h, 000h   ; mov eax, 2
        db 083h, 0FEh, 008h   ; cmp esi, 8
        db 00Fh, 04Fh, 0C5h   ; cmovg eax, ebp
        db 003h, 0C0h   ; add eax, eax
        db 003h, 0C0h   ; add eax, eax
        db 003h, 0C0h   ; add eax, eax
        db 050h   ; push eax
        call _ippsMalloc_8u@4   ; 0x2952F4
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 0E1h, 001h, 000h, 000h   ; je 0x2955c6
        db 083h, 0FEh, 008h   ; cmp esi, 8
        db 00Fh, 08Fh, 0FBh, 000h, 000h, 000h   ; jg 0x2954e9
        db 033h, 0FFh   ; xor edi, edi
        db 085h, 0EDh   ; test ebp, ebp
        db 00Fh, 08Eh, 0E7h, 000h, 000h, 000h   ; jle 0x2954df
        db 083h, 0FDh, 004h   ; cmp ebp, 4
        db 00Fh, 08Ch, 0BAh, 001h, 000h, 000h   ; jl 0x2955bb
        db 08Dh, 04Dh, 0FCh   ; lea ecx, [ebp - 4]
        db 08Bh, 053h, 00Ch   ; mov edx, dword ptr [ebx + 0xc]
        db 08Dh, 034h, 0AAh   ; lea esi, [edx + ebp*4]
        db 0F3h, 00Fh, 010h, 00Dh   ; movss xmm1, dword ptr [0x53a42c]
        dd _unk_53A42C
        db 0F3h, 00Fh, 010h, 005h   ; movss xmm0, dword ptr [0x53a428]
        dd _unk_53A428
        db 08Bh, 0D7h   ; mov edx, edi
        db 0F7h, 0DAh   ; neg edx
        db 089h, 06Ch, 024h, 004h   ; mov dword ptr [esp + 4], ebp
        db 08Bh, 06Bh, 00Ch   ; mov ebp, dword ptr [ebx + 0xc]
$L_295425:
        db 0F3h, 00Fh, 010h, 014h, 096h   ; movss xmm2, dword ptr [esi + edx*4]
        db 0F3h, 00Fh, 059h, 0D1h   ; mulss xmm2, xmm1
        db 0F3h, 00Fh, 011h, 014h, 0F8h   ; movss dword ptr [eax + edi*8], xmm2
        db 0F3h, 00Fh, 010h, 05Ch, 0BDh, 000h   ; movss xmm3, dword ptr [ebp + edi*4]
        db 0F3h, 00Fh, 059h, 0D8h   ; mulss xmm3, xmm0
        db 0F3h, 00Fh, 058h, 0D9h   ; addss xmm3, xmm1
        db 0F3h, 00Fh, 011h, 05Ch, 0F8h, 004h   ; movss dword ptr [eax + edi*8 + 4], xmm3
        db 0F3h, 00Fh, 010h, 064h, 096h, 0FCh   ; movss xmm4, dword ptr [esi + edx*4 - 4]
        db 0F3h, 00Fh, 059h, 0E1h   ; mulss xmm4, xmm1
        db 0F3h, 00Fh, 011h, 064h, 0F8h, 008h   ; movss dword ptr [eax + edi*8 + 8], xmm4
        db 0F3h, 00Fh, 010h, 06Ch, 0BDh, 004h   ; movss xmm5, dword ptr [ebp + edi*4 + 4]
        db 0F3h, 00Fh, 059h, 0E8h   ; mulss xmm5, xmm0
        db 0F3h, 00Fh, 058h, 0E9h   ; addss xmm5, xmm1
        db 0F3h, 00Fh, 011h, 06Ch, 0F8h, 00Ch   ; movss dword ptr [eax + edi*8 + 0xc], xmm5
        db 0F3h, 00Fh, 010h, 074h, 096h, 0F8h   ; movss xmm6, dword ptr [esi + edx*4 - 8]
        db 0F3h, 00Fh, 059h, 0F1h   ; mulss xmm6, xmm1
        db 083h, 0C2h, 0FDh   ; add edx, -3
        db 0F3h, 00Fh, 011h, 074h, 0F8h, 010h   ; movss dword ptr [eax + edi*8 + 0x10], xmm6
        db 0F3h, 00Fh, 010h, 07Ch, 0BDh, 008h   ; movss xmm7, dword ptr [ebp + edi*4 + 8]
        db 0F3h, 00Fh, 059h, 0F8h   ; mulss xmm7, xmm0
        db 0F3h, 00Fh, 058h, 0F9h   ; addss xmm7, xmm1
        db 0F3h, 00Fh, 011h, 07Ch, 0F8h, 014h   ; movss dword ptr [eax + edi*8 + 0x14], xmm7
        db 083h, 0C7h, 003h   ; add edi, 3
        db 03Bh, 0F9h   ; cmp edi, ecx
        db 07Eh, 08Ch   ; jle 0x295425
        db 08Bh, 06Ch, 024h, 004h   ; mov ebp, dword ptr [esp + 4]
$L_29549d:
        db 0F3h, 00Fh, 010h, 00Dh   ; movss xmm1, dword ptr [0x53a42c]
        dd _unk_53A42C
        db 0F3h, 00Fh, 010h, 005h   ; movss xmm0, dword ptr [0x53a428]
        dd _unk_53A428
        db 08Bh, 0D7h   ; mov edx, edi
        db 0F7h, 0DAh   ; neg edx
        db 08Dh, 014h, 096h   ; lea edx, [esi + edx*4]
        db 08Bh, 04Bh, 00Ch   ; mov ecx, dword ptr [ebx + 0xc]
$L_2954b7:
        db 0F3h, 00Fh, 010h, 012h   ; movss xmm2, dword ptr [edx]
        db 0F3h, 00Fh, 059h, 0D1h   ; mulss xmm2, xmm1
        db 083h, 0C2h, 0FCh   ; add edx, -4
        db 0F3h, 00Fh, 011h, 014h, 0F8h   ; movss dword ptr [eax + edi*8], xmm2
        db 0F3h, 00Fh, 010h, 01Ch, 0B9h   ; movss xmm3, dword ptr [ecx + edi*4]
        db 0F3h, 00Fh, 059h, 0D8h   ; mulss xmm3, xmm0
        db 0F3h, 00Fh, 058h, 0D9h   ; addss xmm3, xmm1
        db 0F3h, 00Fh, 011h, 05Ch, 0F8h, 004h   ; movss dword ptr [eax + edi*8 + 4], xmm3
        db 047h   ; inc edi
        db 03Bh, 0FDh   ; cmp edi, ebp
        db 07Ch, 0D8h   ; jl 0x2954b7
$L_2954df:
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
$L_2954e9:
        db 033h, 0D2h   ; xor edx, edx
        db 085h, 0EDh   ; test ebp, ebp
        db 00Fh, 08Eh, 0BEh, 000h, 000h, 000h   ; jle 0x2955b1
        db 08Bh, 04Bh, 00Ch   ; mov ecx, dword ptr [ebx + 0xc]
        db 08Dh, 034h, 0A9h   ; lea esi, [ecx + ebp*4]
        db 0F3h, 00Fh, 010h, 00Dh   ; movss xmm1, dword ptr [0x53a42c]
        dd _unk_53A42C
        db 0F3h, 00Fh, 010h, 005h   ; movss xmm0, dword ptr [0x53a428]
        dd _unk_53A428
        db 08Dh, 03Ch, 012h   ; lea edi, [edx + edx]
        db 003h, 0FFh   ; add edi, edi
        db 0F7h, 0DFh   ; neg edi
        db 08Bh, 04Bh, 00Ch   ; mov ecx, dword ptr [ebx + 0xc]
        db 090h   ; nop 
$L_295514:
        db 0F3h, 00Fh, 010h, 054h, 037h, 0FCh   ; movss xmm2, dword ptr [edi + esi - 4]
        db 0F3h, 00Fh, 059h, 0D1h   ; mulss xmm2, xmm1
        db 0F3h, 00Fh, 011h, 014h, 0D0h   ; movss dword ptr [eax + edx*8], xmm2
        db 0F3h, 00Fh, 010h, 054h, 037h, 0F8h   ; movss xmm2, dword ptr [edi + esi - 8]
        db 0F3h, 00Fh, 059h, 0D1h   ; mulss xmm2, xmm1
        db 0F3h, 00Fh, 011h, 054h, 0D0h, 004h   ; movss dword ptr [eax + edx*8 + 4], xmm2
        db 0F3h, 00Fh, 010h, 07Ch, 037h, 0F4h   ; movss xmm7, dword ptr [edi + esi - 0xc]
        db 0F3h, 00Fh, 059h, 0F9h   ; mulss xmm7, xmm1
        db 0F3h, 00Fh, 011h, 07Ch, 0D0h, 008h   ; movss dword ptr [eax + edx*8 + 8], xmm7
        db 0F3h, 00Fh, 010h, 074h, 037h, 0F0h   ; movss xmm6, dword ptr [edi + esi - 0x10]
        db 0F3h, 00Fh, 059h, 0F1h   ; mulss xmm6, xmm1
        db 0F3h, 00Fh, 011h, 074h, 0D0h, 00Ch   ; movss dword ptr [eax + edx*8 + 0xc], xmm6
        db 0F3h, 00Fh, 010h, 06Ch, 091h, 004h   ; movss xmm5, dword ptr [ecx + edx*4 + 4]
        db 0F3h, 00Fh, 059h, 0E8h   ; mulss xmm5, xmm0
        db 0F3h, 00Fh, 058h, 0E9h   ; addss xmm5, xmm1
        db 083h, 0C7h, 0F0h   ; add edi, -0x10
        db 0F3h, 00Fh, 011h, 06Ch, 0D0h, 010h   ; movss dword ptr [eax + edx*8 + 0x10], xmm5
        db 0F3h, 00Fh, 010h, 064h, 091h, 008h   ; movss xmm4, dword ptr [ecx + edx*4 + 8]
        db 0F3h, 00Fh, 059h, 0E0h   ; mulss xmm4, xmm0
        db 0F3h, 00Fh, 058h, 0E1h   ; addss xmm4, xmm1
        db 0F3h, 00Fh, 011h, 064h, 0D0h, 014h   ; movss dword ptr [eax + edx*8 + 0x14], xmm4
        db 0F3h, 00Fh, 010h, 05Ch, 091h, 00Ch   ; movss xmm3, dword ptr [ecx + edx*4 + 0xc]
        db 0F3h, 00Fh, 059h, 0D8h   ; mulss xmm3, xmm0
        db 0F3h, 00Fh, 058h, 0D9h   ; addss xmm3, xmm1
        db 0F3h, 00Fh, 011h, 05Ch, 0D0h, 018h   ; movss dword ptr [eax + edx*8 + 0x18], xmm3
        db 0F3h, 00Fh, 010h, 054h, 091h, 010h   ; movss xmm2, dword ptr [ecx + edx*4 + 0x10]
        db 0F3h, 00Fh, 059h, 0D0h   ; mulss xmm2, xmm0
        db 0F3h, 00Fh, 058h, 0D1h   ; addss xmm2, xmm1
        db 0F3h, 00Fh, 011h, 054h, 0D0h, 01Ch   ; movss dword ptr [eax + edx*8 + 0x1c], xmm2
        db 083h, 0C2h, 004h   ; add edx, 4
        db 03Bh, 0D5h   ; cmp edx, ebp
        db 00Fh, 08Ch, 063h, 0FFh, 0FFh, 0FFh   ; jl 0x295514
$L_2955b1:
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
$L_2955bb:
        db 08Bh, 053h, 00Ch   ; mov edx, dword ptr [ebx + 0xc]
        db 08Dh, 034h, 0AAh   ; lea esi, [edx + ebp*4]
        db 0E9h, 0D7h, 0FEh, 0FFh, 0FFh   ; jmp 0x29549d
$L_2955c6:
        db 033h, 0C0h   ; xor eax, eax
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 05Dh   ; pop ebp
        db 05Eh   ; pop esi
        db 05Fh   ; pop edi
        db 08Bh, 0E3h   ; mov esp, ebx
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 
        db 08Bh, 0F6h   ; mov esi, esi
seg7 ENDS

seg8 SEGMENT DWORD PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_29CE68 @ 0x0029CE68
PUBLIC _sub_29CE68
_sub_29CE68:
        db 000h, 000h   ; add byte ptr [eax], al
        db 000h, 000h   ; add byte ptr [eax], al
        db 000h, 000h   ; add byte ptr [eax], al
        db 000h, 000h   ; add byte ptr [eax], al
seg8 ENDS


        END
