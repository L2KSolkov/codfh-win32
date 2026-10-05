; codfh-match: Bink's YUY2 converter for mono (grayscale) video (the library's yuy2m.obj,
; RAD's hand-written MMX, MASM 6.15; drafted by tools/asmgen.py). The
; blit state S, the YUV tables and the pmem* constants are yuv.obj's and
; yuv32.obj's.

        .586
        .mmx
        .model flat
        INCLUDE masm6.inc

EXTERN _S:DWORD
EXTERN _pmemb80:DWORD

BINKYUY2M SEGMENT PARA PUBLIC 'CODE'
segstart:

; // match: _YUY2_m_4x2_MMX@4 @ 0x003550A0
_YUY2_m_4x2_MMX@4 PROC PUBLIC
        push ebx
        push ebp
        push esi
        push edi
        movq mm2, qword ptr [_pmemb80]
        mov esi, dword ptr [_S]
        mov ecx, dword ptr [_S+8h]
        mov eax, dword ptr [esp + 14h]
        lea eax, [esi + eax*8]
        ALIGN16 segstart
__do_upper:
        movd mm1, dword ptr [ecx]
        punpcklbw mm1, mm2
        add esi, 8
        add ecx, 4
        cmp esi, eax
        movq qword ptr [esi - 8], mm1
        jb __do_upper
        mov dword ptr [_S], eax
        mov dword ptr [_S+8h], ecx
        mov edi, dword ptr [_S+4h]
        mov edx, dword ptr [_S+0Ch]
        mov eax, dword ptr [esp + 14h]
        lea eax, [edi + eax*8]
        ALIGN16 segstart
__do_lower:
        movd mm1, dword ptr [edx]
        punpcklbw mm1, mm2
        add edi, 8
        add edx, 4
        cmp edi, eax
        movq qword ptr [edi - 8], mm1
        jb __do_lower
        mov dword ptr [_S+4h], edi
        mov dword ptr [_S+0Ch], edx
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret 4
_YUY2_m_4x2_MMX@4 ENDP

BINKYUY2M ENDS
        END
