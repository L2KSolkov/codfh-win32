; codfh-match: Bink's 16-bit mono (grayscale) converters (the library's rgb16m.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD
EXTERN _mono16:DWORD
EXTERN _pmemw16:DWORD
EXTERN _pmemw7F00m:DWORD
EXTERN _pmemwRGB:DWORD
EXTERN _pmemwYscalem:DWORD

BINK16M SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUV_16m_8x2_MMX@4 @ 0x003557E0
_YUV_16m_8x2_MMX@4 PROC PUBLIC
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
        shl eax, 3
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
        add esi, 10h
        paddsw mm3, mm7
        psubusw mm3, mm7
        paddsw mm6, mm7
        pmullw mm3, mm2
        psubusw mm6, mm7
        pmullw mm6, mm2
        movq qword ptr [esi - 10h], mm3
        movq qword ptr [esi - 8], mm6
        cmp esi, eax
        jb __do_upper
        mov dword ptr [_S], esi
        mov dword ptr [_S+8h], ecx
        mov edi, dword ptr [_S+4h]
        mov edx, dword ptr [_S+0Ch]
        mov eax, dword ptr [esp + 14h]
        shl eax, 3
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
        add edi, 10h
        paddsw mm3, mm7
        psubusw mm3, mm7
        paddsw mm6, mm7
        pmullw mm3, mm2
        psubusw mm6, mm7
        pmullw mm6, mm2
        movq qword ptr [edi - 10h], mm3
        movq qword ptr [edi - 8], mm6
        cmp edi, eax
        jb __do_lower
        mov dword ptr [_S+4h], edi
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
        ALIGN16 segstart
_YUV_16m_8x2_MMX@4 ENDP

; // match: _YUV_16m_4x2@4 @ 0x003558F0
_YUV_16m_4x2@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov esi, dword ptr [_S+8h]
        mov edi, dword ptr [_S]
        mov ebp, dword ptr [esp + 14h]
        xor eax, eax
        ALIGN16 segstart
__do_upper:
        mov al, byte ptr [esi]
        xor ecx, ecx
        mov cl, byte ptr [esi + 1]
        add edi, 8
        mov edx, dword ptr [_mono16 + eax*4]
        mov al, byte ptr [esi + 2]
        mov ebx, dword ptr [_mono16 + ecx*4]
        mov cl, byte ptr [esi + 3]
        shl ebx, 10h
        mov eax, dword ptr [_mono16 + eax*4]
        mov ecx, dword ptr [_mono16 + ecx*4]
        or ebx, edx
        shl ecx, 10h
        mov dword ptr [edi - 8], ebx
        or ecx, eax
        add esi, 4
        mov dword ptr [edi - 4], ecx
        xor eax, eax
        dec ebp
        jne __do_upper
        mov dword ptr [_S+8h], esi
        mov dword ptr [_S], edi
        mov esi, dword ptr [_S+0Ch]
        mov edi, dword ptr [_S+4h]
        mov ebp, dword ptr [esp + 14h]
        xor eax, eax
        ALIGN16 segstart
__do_lower:
        mov al, byte ptr [esi]
        xor ecx, ecx
        mov cl, byte ptr [esi + 1]
        add edi, 8
        mov edx, dword ptr [_mono16 + eax*4]
        mov al, byte ptr [esi + 2]
        mov ebx, dword ptr [_mono16 + ecx*4]
        mov cl, byte ptr [esi + 3]
        shl ebx, 10h
        mov eax, dword ptr [_mono16 + eax*4]
        mov ecx, dword ptr [_mono16 + ecx*4]
        or ebx, edx
        shl ecx, 10h
        mov dword ptr [edi - 8], ebx
        or ecx, eax
        add esi, 4
        mov dword ptr [edi - 4], ecx
        xor eax, eax
        dec ebp
        jne __do_lower
        mov dword ptr [_S+0Ch], esi
        mov dword ptr [_S+4h], edi
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUV_16m_4x2@4 ENDP

BINK16M ENDS
        END
