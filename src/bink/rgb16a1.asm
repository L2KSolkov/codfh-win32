; codfh-match: Bink's 16-bit 1555 YUV-to-RGB 4x2 block converters (the library's rgb16a1.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD
EXTERN _YUVTables:DWORD
EXTERN _pmemw16:DWORD
EXTERN _pmemw7F00:DWORD
EXTERN _pmemwYscale:DWORD

BINK5551 SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUV_16a1_4x2_even_MMX@4 @ 0x00353D30
_YUV_16a1_4x2_even_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, dword ptr [_S]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov edx, dword ptr [_S+8h]
        mov ecx, dword ptr [_S+18h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 3
        add eax, edi
        mov dword ptr [_S], eax
        movq mm7, qword ptr [_pmemw7F00]
        ALIGN16 segstart
L0040:
        movd mm4, dword ptr [edx]
        pxor mm0, mm0
        xor eax, eax
        add edx, 4
        mov al, byte ptr [ebp]
        punpcklbw mm4, mm0
        movd mm2, dword ptr [eax*4 + _YUVTables+1800h]
        movd mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebp + 1]
        add ebp, 2
        psubusw mm4, qword ptr [_pmemw16]
        movd mm6, dword ptr [eax*4 + _YUVTables+1800h]
        punpckldq mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebx]
        psllw mm4, 2
        pmulhw mm4, qword ptr [_pmemwYscale]
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        movd mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm2, mm5
        mov al, byte ptr [ebx + 1]
        add ebx, 2
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        punpckldq mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm6, mm5
        punpckldq mm2, mm6
        paddw mm1, mm4
        mov eax, dword ptr [ecx]
        paddw mm2, mm4
        and eax, 80808080h
        paddsw mm1, mm7
        movd mm6, eax
        paddw mm3, mm4
        punpcklbw mm0, mm6
        psubusw mm1, mm7
        psrlw mm1, 3
        paddsw mm2, mm7
        psubusw mm2, mm7
        psrlw mm2, 3
        paddsw mm3, mm7
        psllw mm2, 5
        psubusw mm3, mm7
        psrlw mm3, 3
        por mm1, mm2
        psllw mm3, 0ah
        por mm1, mm0
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S]
        add ecx, 4
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L0040
        mov dword ptr [_S+8h], edx
        mov dword ptr [_S+18h], ecx
        mov edi, dword ptr [_S+4h]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov edx, dword ptr [_S+0Ch]
        mov ecx, dword ptr [_S+1Ch]
        mov eax, dword ptr [esp + 14h]
        shl eax, 3
        add eax, edi
        mov dword ptr [_S+4h], eax
        movq mm7, qword ptr [_pmemw7F00]
        ALIGN16 segstart
L0160:
        movd mm4, dword ptr [edx]
        pxor mm0, mm0
        xor eax, eax
        add edx, 4
        mov al, byte ptr [ebp]
        punpcklbw mm4, mm0
        movd mm2, dword ptr [eax*4 + _YUVTables+1800h]
        movd mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebp + 1]
        add ebp, 2
        psubusw mm4, qword ptr [_pmemw16]
        movd mm6, dword ptr [eax*4 + _YUVTables+1800h]
        punpckldq mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebx]
        psllw mm4, 2
        pmulhw mm4, qword ptr [_pmemwYscale]
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        movd mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm2, mm5
        mov al, byte ptr [ebx + 1]
        add ebx, 2
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        punpckldq mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm6, mm5
        punpckldq mm2, mm6
        paddw mm1, mm4
        mov eax, dword ptr [ecx]
        paddw mm2, mm4
        and eax, 80808080h
        paddsw mm1, mm7
        movd mm6, eax
        paddw mm3, mm4
        punpcklbw mm0, mm6
        psubusw mm1, mm7
        psrlw mm1, 3
        paddsw mm2, mm7
        psubusw mm2, mm7
        psrlw mm2, 3
        paddsw mm3, mm7
        psllw mm2, 5
        psubusw mm3, mm7
        psrlw mm3, 3
        por mm1, mm2
        psllw mm3, 0ah
        por mm1, mm0
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S+4h]
        add ecx, 4
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L0160
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        mov dword ptr [_S+0Ch], edx
        mov dword ptr [_S+1Ch], ecx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
        ALIGN16 segstart
_YUV_16a1_4x2_even_MMX@4 ENDP

; // match: _YUV_16a1_4x2_odd_MMX@4 @ 0x00353F90
_YUV_16a1_4x2_odd_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, dword ptr [_S]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov edx, dword ptr [_S+8h]
        mov ecx, dword ptr [_S+18h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 3
        add eax, edi
        mov dword ptr [_S], eax
        movq mm7, qword ptr [_pmemw7F00]
        ALIGN16 segstart
L02A0:
        movd mm4, dword ptr [edx]
        pxor mm0, mm0
        xor eax, eax
        add edx, 4
        mov al, byte ptr [ebp]
        punpcklbw mm4, mm0
        movd mm2, dword ptr [eax*4 + _YUVTables+1800h]
        movd mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebp + 1]
        add ebp, 2
        psubusw mm4, qword ptr [_pmemw16]
        movd mm6, dword ptr [eax*4 + _YUVTables+1800h]
        punpckldq mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebx]
        psllw mm4, 2
        pmulhw mm4, qword ptr [_pmemwYscale]
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        movd mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm2, mm5
        mov al, byte ptr [ebx + 1]
        add ebx, 2
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        punpckldq mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm6, mm5
        mov al, byte ptr [ebp]
        punpckldq mm2, mm6
        psrlq mm1, 10h
        movd mm6, dword ptr [eax*4 + _YUVTables+1000h]
        psrlq mm2, 10h
        movd mm5, dword ptr [eax*4 + _YUVTables+1800h]
        psrlq mm3, 10h
        mov al, byte ptr [ebx]
        psllq mm6, 30h
        por mm1, mm6
        movd mm6, dword ptr [eax*4 + _YUVTables+1400h]
        paddw mm5, mm6
        movd mm6, dword ptr [eax*4 + _YUVTables+1C00h]
        psllq mm5, 30h
        psllq mm6, 30h
        por mm2, mm5
        por mm3, mm6
        paddw mm1, mm4
        mov eax, dword ptr [ecx]
        paddw mm2, mm4
        and eax, 80808080h
        paddsw mm1, mm7
        movd mm6, eax
        paddw mm3, mm4
        punpcklbw mm0, mm6
        psubusw mm1, mm7
        psrlw mm1, 3
        paddsw mm2, mm7
        psubusw mm2, mm7
        psrlw mm2, 3
        paddsw mm3, mm7
        psllw mm2, 5
        psubusw mm3, mm7
        psrlw mm3, 3
        por mm1, mm2
        psllw mm3, 0ah
        por mm1, mm0
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S]
        add ecx, 4
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L02A0
        mov dword ptr [_S+8h], edx
        mov edi, dword ptr [_S+4h]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov edx, dword ptr [_S+0Ch]
        mov eax, dword ptr [esp + 14h]
        shl eax, 3
        add eax, edi
        mov dword ptr [_S+4h], eax
        movq mm7, qword ptr [_pmemw7F00]
        ALIGN16 segstart
L0400:
        movd mm4, dword ptr [edx]
        pxor mm0, mm0
        xor eax, eax
        add edx, 4
        mov al, byte ptr [ebp]
        punpcklbw mm4, mm0
        movd mm2, dword ptr [eax*4 + _YUVTables+1800h]
        movd mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebp + 1]
        add ebp, 2
        psubusw mm4, qword ptr [_pmemw16]
        movd mm6, dword ptr [eax*4 + _YUVTables+1800h]
        punpckldq mm1, dword ptr [eax*4 + _YUVTables+1000h]
        mov al, byte ptr [ebx]
        psllw mm4, 2
        pmulhw mm4, qword ptr [_pmemwYscale]
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        movd mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm2, mm5
        mov al, byte ptr [ebx + 1]
        add ebx, 2
        movd mm5, dword ptr [eax*4 + _YUVTables+1400h]
        punpckldq mm3, dword ptr [eax*4 + _YUVTables+1C00h]
        paddw mm6, mm5
        mov al, byte ptr [ebp]
        punpckldq mm2, mm6
        psrlq mm1, 10h
        movd mm6, dword ptr [eax*4 + _YUVTables+1000h]
        psrlq mm2, 10h
        movd mm5, dword ptr [eax*4 + _YUVTables+1800h]
        psrlq mm3, 10h
        mov al, byte ptr [ebx]
        psllq mm6, 30h
        por mm1, mm6
        movd mm6, dword ptr [eax*4 + _YUVTables+1400h]
        paddw mm5, mm6
        movd mm6, dword ptr [eax*4 + _YUVTables+1C00h]
        psllq mm5, 30h
        psllq mm6, 30h
        por mm2, mm5
        por mm3, mm6
        paddw mm1, mm4
        mov eax, dword ptr [ecx]
        paddw mm2, mm4
        and eax, 80808080h
        paddsw mm1, mm7
        movd mm6, eax
        paddw mm3, mm4
        punpcklbw mm0, mm6
        psubusw mm1, mm7
        psrlw mm1, 3
        paddsw mm2, mm7
        psllw mm1, 0
        psubusw mm2, mm7
        psrlw mm2, 3
        paddsw mm3, mm7
        psllw mm2, 5
        psubusw mm3, mm7
        psrlw mm3, 3
        por mm1, mm2
        psllw mm3, 0ah
        por mm1, mm0
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S+4h]
        add ecx, 4
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L0400
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        mov dword ptr [_S+0Ch], edx
        mov dword ptr [_S+1Ch], ecx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUV_16a1_4x2_odd_MMX@4 ENDP

BINK5551 ENDS
        END
