; codfh-match: eight bytes opening XGRPH's uninitialized tail (PLAN M7)
; The image's XGRPH read-only data ends at 0x3AA2BC and its first tail variable, the
; assembler's g_pErrorLog, lies at 0x3AA2C8: the eight bytes at 0x3AA2C0 are the rest of
; the vertex shader optimizer's Instruction::collections (0x3AA2B8, 16 bytes), whose first
; dwords lie in the stand-in piece at 0x3AA28F. The library member's definition is a
; reference in the M7 link (config/m7drop.txt, -NAME) resolved to xgrph_icoll here
; (config/m7alt.txt). Only the M7 link uses this object, its section named as the probe
; keys the tail's (XGRPH_RW$ADDR).

        .686p

PUBLIC _xgrph_icoll

xgrphfill SEGMENT DWORD PUBLIC USE32 ALIAS('XGRPH_RW$003AA2C0') 'DATA'
_xgrph_icoll EQU $ - 8
        dd 0, 0
xgrphfill ENDS

        END
