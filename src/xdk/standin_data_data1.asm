; codfh-match: XDK library data in .data1 (repacked)
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat

dseg0 SEGMENT BYTE PUBLIC ALIAS('.data1') 'DATA'
dseg0 ENDS


        END
