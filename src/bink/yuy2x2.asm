; codfh-match: Bink's YUY2 converter, doubled width (the library's yuy2x2.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD

BINKYUY2X2 SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUY2_x2_8x2_MMX@4 @ 0x00354FE0
_YUY2_x2_8x2_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov esi, dword ptr [_S]
        mov edi, dword ptr [_S+4h]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov ecx, dword ptr [_S+8h]
        mov edx, dword ptr [_S+0Ch]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, esi
        mov dword ptr [_S], eax
__do_quad:
        xor eax, eax
        mov ax, word ptr [ebp]
        movd mm1, eax
        mov ax, word ptr [ebx]
        movd mm2, eax
        punpcklbw mm1, mm2
        punpcklwd mm1, mm1
        add ebp, 2
        add ebx, 2
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
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        mov dword ptr [_S+8h], ecx
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUY2_x2_8x2_MMX@4 ENDP

BINKYUY2X2 ENDS
        END
