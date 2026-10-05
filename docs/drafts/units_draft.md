
## `src/recovered/unit_1B18E0.cpp`, message methods, `0x1B18E0`–`0x1B4690`

The network messages' own methods (game/netmsg.h):
- A point message's write and read (`type_3E0FB4`).
- The score messages' out-of-line constructors, destructors and ids (`type_3E1E3C`, `type_3E1FC4`).
- The full game state message, which writes and reads every manager part in turn (`type_3E105C`).
- The rules message (`type_3E1074`) and the kick message (`type_3E10BC`).

14 functions matched.

## `src/recovered/unit_1B79E0.cpp`, `unit_1BD6A0.cpp`, `unit_1C0830.cpp`, `unit_1C2F90.cpp`, more message methods

More writes and reads of message classes (`type_3E0F9C`, `type_3E111C`, `type_3E1134`, `type_3E10EC`,
`type_3E0FE4`, `type_3E0FFC`, `type_3E1014`). They use the stream's ranged whole numbers
(`sub_1F8B90`, `sub_1F8B30`). Several reads keep a compiled-out check as an empty `if` before a
field whose registers are one load on. 18 functions matched.

## `src/recovered/unit_1C5700.cpp`, message methods and the id maps, `0x1C5700`–`0x1C60A0`

The maps between the game's and the network's message ids (`sub_1C5800`, `sub_1C5860`). The writes
and reads of eight more message classes. The grenade throw's send (`sub_1C5CA0`), whose message's
implicit constructor is out of line (`0x1C5D40`) and whose session accessor keeps two unused
locals (`type_4F8058::get_2`, which the bomb sites' second send uses too). The sections' wait with
its compiled-out print (`sub_1C58C0`). 25 functions matched. `sub_1C5700` (std::string's `const
char *` constructor) and `sub_1C5740` are library or unplaced code, not yet done.

## `src/recovered/unit_1C60A0.cpp`, the voice chat, `0x1C60A0`–`0x1C7EE0`

The voice manager (game/voice.h, `type_3E3860`, 0x3160 bytes) receives the peers' voice data and
this machine's microphone data through two receiver levels. It keeps the latter in a 2500-byte ring
buffer and sends it every 100 milliseconds through its channel (`type_3E3870`, built by the session
module's `sub_1DE280`). The XHV engine's owner (`type_3E3884`, an `ITitleXHV`) creates the engine
and registers talkers with their XUIDs. It sets playback priorities from the mute masks, and sends
each player's headset, speaker and mute status as `type_3E0F54` messages. The XHV C entry points,
processing modes, `XGetDevices` and `IDirectSound_SetEffectData` are aliased to the library code.

Findings:
- The peer mask's `test`, `add` and `clear` are inlines. `add` and `clear` keep two compiled-out
  checks, since their registers are two loads on.
- Tests chained with `&&` whose registers jump between two inlines were written as nested `if`s,
  each with a check.
- The status message's fields are set through inline setters that take `bool`, which leaves the
  byte temporaries.
