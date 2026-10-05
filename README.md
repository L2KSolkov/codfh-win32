# codfh-match

A matching decompilation of `Game_XboxMultiplayer.xbe` (Call of Duty: Finest Hour, Xbox
multiplayer, built 2004-10-29 with XDK 5849): source that, compiled with the original toolchain and
linked with the original Xbox libraries, rebuilds the XBE byte for byte.

- Plan: `docs/PLAN.md`
- Toolchain identity and proven flags: `docs/toolchain.md`
- The original image goes in `orig/` (not committed); `orig/Game_XboxMultiplayer.xbe.sha1` pins it.

```
python tools/build.py            the per-commit gate: compile, match, link, compare
python tools/build_probes.py     compile the toolchain probes and match them
python tools/flag_audit.py       show which probe each compiler flag is proven by
python tools/match.py OBJ NAME ADDRESS
python tools/export_symbols.py   refresh config/symbols.txt from the live IDA database
python tools/lib.py LIB [MEMBER OUT]  list or extract .lib members
```

Requires `C:\XDK` (XDK 5849, compiler in `xbox\bin\vc71`) and Python 3.
