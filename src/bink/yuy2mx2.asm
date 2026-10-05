; codfh-match: Bink's YUY2 converter for mono, doubled width (the library's yuy2mx2.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD
EXTERN _pmemb80:DWORD

BINKYUY2MX SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUY2_mx2_4x2_MMX@4 @ 0x00354F40
_YUY2_mx2_4x2_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        movq mm1, qword ptr [_pmemb80]
        mov esi, dword ptr [_S]
        mov edi, dword ptr [_S+4h]
        mov ecx, dword ptr [_S+8h]
        mov edx, dword ptr [_S+0Ch]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, esi
        mov dword ptr [_S], eax
        ALIGN16 segstart
__do_quad:
        movd mm5, dword ptr [edx]
        add edx, 4
        punpcklbw mm5, mm5
        movq mm3, mm5
        punpckhbw mm3, mm1
        movq qword ptr [edi + 8], mm3
        punpcklbw mm5, mm1
        movq qword ptr [edi], mm5
        add edi, 10h
        movd mm6, dword ptr [ecx]
        add ecx, 4
        punpcklbw mm6, mm6
        movq mm4, mm6
        punpckhbw mm4, mm1
        movq qword ptr [esi + 8], mm4
        punpcklbw mm6, mm1
        movq qword ptr [esi], mm6
        add esi, 10h
        mov eax, dword ptr [_S]
        cmp esi, eax
        jb __do_quad
        mov dword ptr [_S+4h], edi
        mov dword ptr [_S+8h], ecx
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUY2_mx2_4x2_MMX@4 ENDP

BINKYUY2MX ENDS
        END
