; codfh-match: Bink's 32-bit (8888) YUV-to-RGB 4x2 block converters (the library's rgb32.obj,
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

BINK32 SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUV_32_4x2_even_MMX@4 @ 0x0034EC80
_YUV_32_4x2_even_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, dword ptr [_S]
        mov edx, dword ptr [_S+8h]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, edi
        mov dword ptr [_S], eax
        movq mm7, qword ptr [_pmemw7F00]
L0031:
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
        paddw mm2, mm4
        paddsw mm1, mm7
        paddw mm3, mm4
        psubusw mm1, mm7
        paddsw mm2, mm7
        movq mm4, mm1
        psubusw mm2, mm7
        punpcklwd mm1, mm0
        movq mm5, mm2
        punpcklwd mm2, mm0
        paddsw mm3, mm7
        pslld mm2, 8
        psubusw mm3, mm7
        punpckhwd mm4, mm0
        movq mm6, mm3
        punpcklwd mm3, mm0
        pslld mm3, 10h
        por mm1, mm2
        por mm1, mm3
        punpckhwd mm5, mm0
        punpckhwd mm6, mm0
        pslld mm5, 8
        movq qword ptr [edi], mm1
        pslld mm6, 10h
        por mm4, mm5
        add edi, 10h
        por mm4, mm6
        mov eax, dword ptr [_S]
        movq qword ptr [edi - 8], mm4
        cmp edi, eax
        jb L0031
        mov dword ptr [_S+8h], edx
        mov edi, dword ptr [_S+4h]
        mov edx, dword ptr [_S+0Ch]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, edi
        mov dword ptr [_S+4h], eax
        movq mm7, qword ptr [_pmemw7F00]
L0147:
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
        paddw mm2, mm4
        paddsw mm1, mm7
        paddw mm3, mm4
        psubusw mm1, mm7
        paddsw mm2, mm7
        movq mm4, mm1
        psubusw mm2, mm7
        punpcklwd mm1, mm0
        movq mm5, mm2
        punpcklwd mm2, mm0
        paddsw mm3, mm7
        pslld mm2, 8
        psubusw mm3, mm7
        punpckhwd mm4, mm0
        movq mm6, mm3
        punpcklwd mm3, mm0
        pslld mm3, 10h
        por mm1, mm2
        por mm1, mm3
        punpckhwd mm5, mm0
        punpckhwd mm6, mm0
        pslld mm5, 8
        movq qword ptr [edi], mm1
        pslld mm6, 10h
        por mm4, mm5
        add edi, 10h
        por mm4, mm6
        mov eax, dword ptr [_S+4h]
        movq qword ptr [edi - 8], mm4
        cmp edi, eax
        jb L0147
        mov dword ptr [_S+0Ch], edx
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
        ALIGN16 segstart
_YUV_32_4x2_even_MMX@4 ENDP

; // match: _YUV_32_4x2_odd_MMX@4 @ 0x0034EED0
_YUV_32_4x2_odd_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, dword ptr [_S]
        mov edx, dword ptr [_S+8h]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, edi
        mov dword ptr [_S], eax
        movq mm7, qword ptr [_pmemw7F00]
L0281:
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
        paddw mm2, mm4
        paddsw mm1, mm7
        paddw mm3, mm4
        psubusw mm1, mm7
        paddsw mm2, mm7
        movq mm4, mm1
        psubusw mm2, mm7
        punpcklwd mm1, mm0
        movq mm5, mm2
        punpcklwd mm2, mm0
        paddsw mm3, mm7
        pslld mm2, 8
        psubusw mm3, mm7
        punpckhwd mm4, mm0
        movq mm6, mm3
        punpcklwd mm3, mm0
        pslld mm3, 10h
        por mm1, mm2
        por mm1, mm3
        punpckhwd mm5, mm0
        punpckhwd mm6, mm0
        pslld mm5, 8
        movq qword ptr [edi], mm1
        pslld mm6, 10h
        por mm4, mm5
        add edi, 10h
        por mm4, mm6
        mov eax, dword ptr [_S]
        movq qword ptr [edi - 8], mm4
        cmp edi, eax
        jb L0281
        mov dword ptr [_S+8h], edx
        mov edi, dword ptr [_S+4h]
        mov edx, dword ptr [_S+0Ch]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, edi
        mov dword ptr [_S+4h], eax
        movq mm7, qword ptr [_pmemw7F00]
L03E0:
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
        paddw mm2, mm4
        paddsw mm1, mm7
        paddw mm3, mm4
        psubusw mm1, mm7
        paddsw mm2, mm7
        movq mm4, mm1
        psubusw mm2, mm7
        punpcklwd mm1, mm0
        movq mm5, mm2
        punpcklwd mm2, mm0
        paddsw mm3, mm7
        pslld mm2, 8
        psubusw mm3, mm7
        punpckhwd mm4, mm0
        movq mm6, mm3
        punpcklwd mm3, mm0
        pslld mm3, 10h
        por mm1, mm2
        por mm1, mm3
        punpckhwd mm5, mm0
        punpckhwd mm6, mm0
        pslld mm5, 8
        movq qword ptr [edi], mm1
        pslld mm6, 10h
        por mm4, mm5
        add edi, 10h
        por mm4, mm6
        mov eax, dword ptr [_S+4h]
        movq qword ptr [edi - 8], mm4
        cmp edi, eax
        jb L03E0
        mov dword ptr [_S+0Ch], edx
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUV_32_4x2_odd_MMX@4 ENDP

BINK32 ENDS
        END
