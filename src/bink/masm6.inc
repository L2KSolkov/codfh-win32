; codfh-match: MASM 6.15's code alignment fill, which RAD's assembler used
; and ml.exe 14 no longer emits (it pads with jmp/int3). ALIGN16 base pads
; the code to the next 16-byte boundary from the label base (the segment's
; first byte) with MASM 6's no-op instructions, longest first:
;   7: lea esp,[esp+00000000]   6: lea ebx,[ebx+00000000]   5: add eax,0
;   4: lea esp,[esp+00]         3: lea ecx,[ecx+00]         2: mov edi,edi
;   1: nop

MASM6FILL MACRO n
        IF n GE 7
        db 8Dh, 0A4h, 24h, 0, 0, 0, 0
        MASM6FILL %(n - 7)
        ELSEIF n EQ 6
        db 8Dh, 9Bh, 0, 0, 0, 0
        ELSEIF n EQ 5
        db 05h, 0, 0, 0, 0
        ELSEIF n EQ 4
        db 8Dh, 64h, 24h, 0
        ELSEIF n EQ 3
        db 8Dh, 49h, 0
        ELSEIF n EQ 2
        db 8Bh, 0FFh
        ELSEIF n EQ 1
        db 90h
        ENDIF
ENDM

ALIGN16 MACRO base
        MASM6FILL %((16 - (($ - base) AND 15)) AND 15)
ENDM
