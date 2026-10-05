; codfh-match: Bink's 32-bit mono (grayscale) converter (the library's rgb32m.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD
EXTERN _pmemw16:DWORD
EXTERN _pmemw7F00:DWORD
EXTERN _pmemwYscale:DWORD

; (its own .data, 16-byte aligned: the image has it at 0x004311A0, after the
; previous object's data padded to 16)
pdata SEGMENT PARA PUBLIC ALIAS('.data') 'DATA'
; RAD's dword 0x00010101 pair: spreads a gray byte into B, G and R
; // match: pmemd0111 @ 0x004311A0
pmemd0111 dd 000010101h, 000010101h
pdata ENDS

BINK32M SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUV_32m_8x2_MMX@4 @ 0x00356140
_YUV_32m_8x2_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        movq mm7, qword ptr [_pmemw7F00]
        movq mm0, qword ptr [_pmemw16]
        movq mm2, qword ptr [pmemd0111]
        movq mm5, qword ptr [_pmemwYscale]
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
        psllw mm3, 2
        pmulhw mm3, mm5
        psllw mm6, 2
        pmulhw mm6, mm5
        nop 
        add ecx, 8
        add esi, 20h
        paddsw mm3, mm7
        psubusw mm3, mm7
        paddsw mm6, mm7
        movq mm1, mm3
        punpcklwd mm3, mm3
        punpckhwd mm1, mm1
        pmullw mm3, mm2
        pmullw mm1, mm2
        psubusw mm6, mm7
        movq mm4, mm6
        punpcklwd mm6, mm6
        punpckhwd mm4, mm4
        pmullw mm6, mm2
        movq qword ptr [esi - 20h], mm3
        pmullw mm4, mm2
        movq qword ptr [esi - 18h], mm1
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
        psllw mm3, 2
        pmulhw mm3, mm5
        psllw mm6, 2
        pmulhw mm6, mm5
        nop 
        add edx, 8
        add edi, 20h
        paddsw mm3, mm7
        psubusw mm3, mm7
        paddsw mm6, mm7
        movq mm1, mm3
        punpcklwd mm3, mm3
        punpckhwd mm1, mm1
        pmullw mm3, mm2
        pmullw mm1, mm2
        psubusw mm6, mm7
        movq mm4, mm6
        punpcklwd mm6, mm6
        punpckhwd mm4, mm4
        pmullw mm6, mm2
        movq qword ptr [edi - 20h], mm3
        pmullw mm4, mm2
        movq qword ptr [edi - 18h], mm1
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
_YUV_32m_8x2_MMX@4 ENDP

BINK32M ENDS
        END
