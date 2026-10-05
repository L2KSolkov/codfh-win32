; codfh-match: the zeros closing BINKDATA (PLAN M7)
; The image's BINKDATA has a virtual size four bytes past its last placed datum (0xD560
; against 0xD55C): a zero dword at 0x538D7C no code of the image refers to. These four bytes,
; sorting after every keyed BINKDATA section, give the M7 link's BINKDATA its virtual size.
; Only the M7 link uses this object.

        .686p

binkdatafill SEGMENT DWORD PUBLIC USE32 ALIAS('BINKDATA$zzzzzzzz') 'DATA'
        dd 0
binkdatafill ENDS

        END
