# The original image

`orig/Game_XboxMultiplayer.xbe`, SHA-1 `d3ec0b089647081fd733b1bf53c63136f1a95387`: the image as
signed.

## Section digests

Each XBE section header stores a SHA-1 digest of the section, computed by imagebld as
`SHA1(raw size as 4 little-endian bytes ‖ raw bytes)`. `tools/xbelink.py` recomputes all 34 and
fails the build unless every one verifies against the rebuilt bytes. For this image all 34 do, so
the gate checks the image against Microsoft's own signing record as well as against the file.

## The earlier, modified dump

Until 2026-09-24 the reference was a different dump (SHA-1
`17413a433d6706f3d86fdf1a3a4887b55a73fa9b`) whose `.text` failed its stored digest (stored
`71d7c01b9635cefd303b802ef855820b6fbb1e65`, computed `0dd31959c4c4dbfe736cf2597371553b7c2cdf34`).
Earlier searches for the modification (IDA `nop`s in game functions, XDK library code compared with
the installed libraries) found nothing. Comparing the two dumps settled it: they differ in exactly
16 bytes, at `sub_19A750`.

| | Bytes at `0x19A750` | Meaning |
|---|---|---|
| as signed | `55 8B EC 5D C3` + `CC` fill | an empty function: the game's debug print, compiled out for retail (754 callers) |
| modified dump | `8B 44 24 04 80 38 80 73 06 FF 25 AC D4 3C 00 C3` | jumps through the `DbgPrint` import (`0x3CD4AC`) when the format's first byte is below `0x80` |

So the modification re-enabled the debug output. The signed image replaced the modified one as the
reference; nothing already matched was affected (`sub_19A750` was still a binary unit). A copy of
the modified dump is kept, untracked, as `orig/Game_XboxMultiplayer.dbgprint-mod.xbe`.
