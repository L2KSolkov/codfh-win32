; codfh-match: the zeros closing .rdata (PLAN M7)
; The image's .rdata ends with xgraphics' last funcinfo at 0x426D20, whose last four fields
; (zeros) lie past the section's raw end: the virtual size covers them (0x59A3C), imagebld's
; raw data stops at 0x426D2C. The placement link's stand-in piece holds the raw bytes only;
; these sixteen zero bytes, sorting after every keyed EH table, give the M7 link's .rdata its
; virtual size. Only the M7 link uses this object.

        .686p

rdatafill SEGMENT DWORD PUBLIC USE32 READONLY ALIAS('.xdata$xzzzzzzz') 'DATA'
        dd 0, 0, 0, 0
rdatafill ENDS

        END
