; codfh-match: Bink's 16-bit mono (grayscale) converter, doubled width (the library's rgb16mx2.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD
EXTERN _pmemw16:DWORD
EXTERN _pmemw7F00m:DWORD
EXTERN _pmemwRGB:DWORD
EXTERN _pmemwYscalem:DWORD

BINK16MX SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUV_16mx2_8x2_MMX@4 @ 0x00355140
; // sp-match: _YUV_16mx2_8x2_MMX@4 @ 0x00265140
_YUV_16mx2_8x2_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        movq mm7, qword ptr [_pmemw7F00m]
        movq mm0, qword ptr [_pmemw16]
        movq mm2, qword ptr [_pmemwRGB]
        movq mm5, qword ptr [_pmemwYscalem]
        mov esi, dword ptr [_S]
        mov ecx, dword ptr [_S+8h]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, esi
        ALIGN16 segstart
__do_upper:
        movd mm3, dword ptr [ecx]
        pxor mm4, mm4
        movd mm6, dword ptr [ecx + 4]
        punpcklbw mm3, mm4
        psubusw mm3, mm0
        punpcklbw mm6, mm4
        psubusw mm6, mm0
        pmulhw mm3, mm5
        pmulhw mm6, mm5
        nop 
        add ecx, 8
        add esi, 20h
        paddsw mm3, mm7
        psubusw mm3, mm7
        paddsw mm6, mm7
        pmullw mm3, mm2
        psubusw mm6, mm7
        pmullw mm6, mm2
        movq mm1, mm3
        punpcklwd mm3, mm3
        punpckhwd mm1, mm1
        movq mm4, mm6
        movq qword ptr [esi - 20h], mm3
        punpcklwd mm6, mm6
        movq qword ptr [esi - 18h], mm1
        punpckhwd mm4, mm4
        movq qword ptr [esi - 10h], mm6
        movq qword ptr [esi - 8], mm4
        cmp esi, eax
        jb __do_upper
        mov dword ptr [_S], esi
        mov dword ptr [_S+8h], ecx
        mov edi, dword ptr [_S+4h]
        mov edx, dword ptr [_S+0Ch]
        mov eax, dword ptr [esp + 14h]
        shl eax, 4
        add eax, edi
        ALIGN16 segstart
__do_lower:
        movd mm3, dword ptr [edx]
        pxor mm4, mm4
        movd mm6, dword ptr [edx + 4]
        punpcklbw mm3, mm4
        psubusw mm3, mm0
        punpcklbw mm6, mm4
        psubusw mm6, mm0
        pmulhw mm3, mm5
        pmulhw mm6, mm5
        nop 
        add edx, 8
        add edi, 20h
        paddsw mm3, mm7
        psubusw mm3, mm7
        paddsw mm6, mm7
        pmullw mm3, mm2
        psubusw mm6, mm7
        pmullw mm6, mm2
        movq mm1, mm3
        punpcklwd mm3, mm3
        punpckhwd mm1, mm1
        movq mm4, mm6
        movq qword ptr [edi - 20h], mm3
        punpcklwd mm6, mm6
        movq qword ptr [edi - 18h], mm1
        punpckhwd mm4, mm4
        movq qword ptr [edi - 10h], mm6
        movq qword ptr [edi - 8], mm4
        cmp edi, eax
        jb __do_lower
        mov dword ptr [_S+4h], edi
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUV_16mx2_8x2_MMX@4 ENDP

BINK16MX ENDS
        END
