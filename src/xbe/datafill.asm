; codfh-match: a .data dword of no known object (PLAN M7)
; 0x436D04 holds 1 between xbpipe.c's D3D8material (0x436CC0) and the world sector all-in-one
; node's cluster list (0x436D08). No code of the image refers to it, and neither the Xbox world
; pipeline files nor Godfather's 3.7 copies of them define such a variable; the placement link
; leaves it to its stand-in fill ('-' in config/splits.txt). Only the M7 link uses this object,
; its section keyed by the address as the probe keys .data rows.

        .686p

datafill SEGMENT DWORD PUBLIC USE32 ALIAS('.data$00436D04') 'DATA'
        dd 1
datafill ENDS

        END
