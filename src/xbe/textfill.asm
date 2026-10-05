; codfh-match: the int3 padding closing .text (PLAN M7)
; The image's .text ends with __itoa at 0x2FF17C, and the link pads up to .text$x's first
; funclet (0x2FF180) with int3s. The M7 link lays the functions out with /ORDER, and link.exe
; leaves the padding after the /ORDER'ed block unwritten (zeros) wherever the unordered
; contributions begin; padding inside the block is int3, as everywhere in the image. This
; piece, listed in the order file right after __itoa, holds those four int3s. Only the M7
; link uses this object.

        .686p

PUBLIC _m7_textfill

textfill SEGMENT BYTE PUBLIC USE32 ALIAS('.text') 'CODE'
_m7_textfill:
        db 0CCh, 0CCh, 0CCh, 0CCh
textfill ENDS

        END
