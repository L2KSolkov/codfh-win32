; codfh-match: Bink's 16-bit (565/555) YUV-to-RGB 4x2 block converters (the library's rgb16.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _RGBshift:DWORD
EXTERN _S:DWORD
EXTERN _YUVTables:DWORD
EXTERN _pmemw16:DWORD
EXTERN _pmemw7F00:DWORD
EXTERN _pmemwYscale:DWORD

BINK16 SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUV_16_4x2_even_MMX@4 @ 0x00351340
; // sp-match: _YUV_16_4x2_even_MMX@4 @ 0x00261340
_YUV_16_4x2_even_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, dword ptr [_S]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov edx, dword ptr [_S+8h]
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
        paddw mm2, mm4
        paddsw mm1, mm7
        paddw mm3, mm4
        psubusw mm1, mm7
        psrlw mm1, qword ptr [_RGBshift+18h]
        paddsw mm2, mm7
        psllw mm1, qword ptr [_RGBshift]
        psubusw mm2, mm7
        psrlw mm2, qword ptr [_RGBshift+20h]
        paddsw mm3, mm7
        psllw mm2, qword ptr [_RGBshift+8h]
        psubusw mm3, mm7
        psrlw mm3, qword ptr [_RGBshift+28h]
        por mm1, mm2
        psllw mm3, qword ptr [_RGBshift+10h]
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S]
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L0040
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
L0150:
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
        psrlw mm1, qword ptr [_RGBshift+18h]
        paddsw mm2, mm7
        psllw mm1, qword ptr [_RGBshift]
        psubusw mm2, mm7
        psrlw mm2, qword ptr [_RGBshift+20h]
        paddsw mm3, mm7
        psllw mm2, qword ptr [_RGBshift+8h]
        psubusw mm3, mm7
        psrlw mm3, qword ptr [_RGBshift+28h]
        por mm1, mm2
        psllw mm3, qword ptr [_RGBshift+10h]
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S+4h]
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L0150
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
        ALIGN16 segstart
_YUV_16_4x2_even_MMX@4 ENDP

; // match: _YUV_16_4x2_odd_MMX@4 @ 0x00351590
; // sp-match: _YUV_16_4x2_odd_MMX@4 @ 0x00261590
_YUV_16_4x2_odd_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, dword ptr [_S]
        mov ebp, dword ptr [_S+10h]
        mov ebx, dword ptr [_S+14h]
        mov edx, dword ptr [_S+8h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 3
        add eax, edi
        mov dword ptr [_S], eax
        movq mm7, qword ptr [_pmemw7F00]
        ALIGN16 segstart
L0290:
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
        psrlw mm1, qword ptr [_RGBshift+18h]
        paddsw mm2, mm7
        psllw mm1, qword ptr [_RGBshift]
        psubusw mm2, mm7
        psrlw mm2, qword ptr [_RGBshift+20h]
        paddsw mm3, mm7
        psllw mm2, qword ptr [_RGBshift+8h]
        psubusw mm3, mm7
        psrlw mm3, qword ptr [_RGBshift+28h]
        por mm1, mm2
        psllw mm3, qword ptr [_RGBshift+10h]
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S]
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L0290
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
L03F0:
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
        psrlw mm1, qword ptr [_RGBshift+18h]
        paddsw mm2, mm7
        psllw mm1, qword ptr [_RGBshift]
        psubusw mm2, mm7
        psrlw mm2, qword ptr [_RGBshift+20h]
        paddsw mm3, mm7
        psllw mm2, qword ptr [_RGBshift+8h]
        psubusw mm3, mm7
        psrlw mm3, qword ptr [_RGBshift+28h]
        por mm1, mm2
        psllw mm3, qword ptr [_RGBshift+10h]
        por mm1, mm3
        add edi, 8
        mov eax, dword ptr [_S+4h]
        movq qword ptr [edi - 8], mm1
        cmp edi, eax
        jb L03F0
        mov dword ptr [_S+10h], ebp
        mov dword ptr [_S+14h], ebx
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUV_16_4x2_odd_MMX@4 ENDP

BINK16 ENDS
        END
