; codfh-match: four zero bytes in XPP's data (PLAN M7)
; The image's .XPP$Data holds xpp.obj's _XPP_XInitDevicesHasBeenCalled at 0x3C44B4 and
; typeinfo.obj's gamepad table at 0x3C44BC; the four zero bytes between them belong to a
; datum no code of the image refers to, whose object is not known. Only the M7 link uses
; this object, its section named as the probe keys the rows' (.XPP$Data$ADDR).

        .686p

xppfill SEGMENT DWORD PUBLIC USE32 ALIAS('.XPP$Data$003C44B8') 'DATA'
        dd 0
xppfill ENDS

        END
