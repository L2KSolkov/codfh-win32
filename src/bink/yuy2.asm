; codfh-match: Bink's YUY2 blitter core (the library's yuy2.obj, RAD's
; hand-written MMX): interleaves two rows of Y with the shared U and V row
; into packed YUY2, using the row pointers in yuv.obj's S block.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

; yuv.obj's blit state: +0/+4 the two output rows, +8/+0xC the two Y rows,
; +0x10 the U row, +0x14 the V row
EXTERN _S:DWORD

BINKYUY2 SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUY2_8x2_MMX@4 @ 0x00354E50
_YUY2_8x2_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        mov edi, _S
        mov ebp, _S+10h
        mov ebx, _S+14h
        mov edx, _S+8
        mov ecx, [esp+14h]
        lea ecx, [edi+ecx*8-10h]
        ALIGN16 segstart
do_upper:
        movd mm1, dword ptr [ebp]
        movd mm2, dword ptr [ebx]
        movq mm6, qword ptr [edx]
        punpcklbw mm1, mm2
        movq mm7, mm6
        punpcklbw mm6, mm1
        add ebp, 4
        add ebx, 4
        movq qword ptr [edi], mm6
        punpckhbw mm7, mm1
        add edx, 8
        cmp edi, ecx
        movq qword ptr [edi+8], mm7
        lea edi, [edi+10h]
        jb do_upper
        mov _S, edi
        mov _S+8, edx
        mov edi, _S+4
        mov ebp, _S+10h
        mov ebx, _S+14h
        mov edx, _S+0Ch
        mov ecx, [esp+14h]
        lea ecx, [edi+ecx*8-10h]
        ALIGN16 segstart
do_lower:
        movd mm1, dword ptr [ebp]
        movd mm2, dword ptr [ebx]
        movq mm6, qword ptr [edx]
        punpcklbw mm1, mm2
        movq mm7, mm6
        punpcklbw mm6, mm1
        add ebp, 4
        add ebx, 4
        movq qword ptr [edi], mm6
        punpckhbw mm7, mm1
        add edx, 8
        cmp edi, ecx
        movq qword ptr [edi+8], mm7
        lea edi, [edi+10h]
        jb do_lower
        mov _S+4, edi
        mov _S+10h, ebp
        mov _S+14h, ebx
        mov _S+0Ch, edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUY2_8x2_MMX@4 ENDP

BINKYUY2 ENDS
        END
