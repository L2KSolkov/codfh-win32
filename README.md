# Call of Duty: Finest Hour for Windows

A native Windows port of Call of Duty: Finest Hour (Xbox, 2004), built from the decompiled
source. It plays single player and multiplayer. It renders through Direct3D 11 and plays sound
through XAudio2. It takes input from the keyboard and mouse or an XInput controller. It runs from
the original disc's files, unchanged.

The full design and status are in [docs/WIN32_PORT.md](docs/WIN32_PORT.md).

## Requirements

- **Windows 10 or 11.**
- **Visual Studio** with the C++ desktop workload. The build expects MSVC 14.51.36231 and Windows
  SDK 10.0.26100.0, in Visual Studio 18 Enterprise's default location. Set these to build with
  another install:

  | Variable | Default |
  |---|---|
  | `CODFH_VS` | `C:\Program Files\Microsoft Visual Studio\18\Enterprise` |
  | `CODFH_MSVC` | `14.51.36231` |
  | `CODFH_WINSDK` | `C:\Program Files (x86)\Windows Kits\10` |
  | `CODFH_WINSDK_VER` | `10.0.26100.0` |

- **Python 3.**
- **Git.** It's only needed to stamp the build's revision into the log and the crash reports.
- **The game's files:** a copy of the Xbox disc's contents (`COD.PAK`, `SHELL`, `AUDIO`, `DATA`
  and the rest) in a folder of your own. They aren't part of this repository.

The Xbox Development Kit isn't needed. The port's own headers in `port/include` replace the XDK
headers, and nothing is linked from the XDK. Dear ImGui is included in `port/third_party/imgui`.

## Building

Run the build from the repository root:

```
python tools/portbuild.py --sp       single player:  build/port_sp/codfh.exe
python tools/portbuild.py            multiplayer:    build/port/codfh.exe
python tools/portbuild.py --dedicated  dedicated server: build/port/dedicated/codfh_server.exe
```

Each game build also builds `codfh_launcher.exe` beside `codfh.exe`. Single player's output folder
also gets `launch.bat`.

Builds are incremental. A unit is compiled again only when its source, a header it reads or its
compiler command changes. The link runs only when an object is newer than the executable. The
first build compiles every unit and takes a few minutes. Later ones take seconds.

Each output folder's `compile.log` holds the compiler output. Its `errors.md` summarizes any failed
units, and its `link.md` lists any unresolved symbols.

### Build options

| Option | Effect |
|---|---|
| `--sp` | Single player, in `build/port_sp`. Without it, multiplayer in `build/port`. |
| `--dedicated` | The dedicated server: no window, device, audio or local input. It hosts from the command line. |
| `--full` | Compile every unit, not only the changed ones. |
| `--only GLOB` | Compile only the units matching the pattern. Can be given more than once. |
| `--link` | Link after a partial `--only` compile. |
| `--jobs N` | Compile with N processes. The default is one per CPU. |
| `--launcher` | Build only the launcher. |
| `--no-imgui` | Leave out the overlay (F1). |
| `--no-debug-tools` | Leave out the debug tools: trigger and collision drawing, noclip and the overlay's Game debug tools window. |
| `--no-all-sections` | Leave out the option to load every section of a level at once. |
| `--no-sp-logs` | Single player: leave out the debug prints that multiplayer kept. |
| `--no-extra-logs` | Leave out the GameCube build's extra debug prints ([docs/extra-logs.md](docs/extra-logs.md)). |

## Running

Point the game at the folder with the disc's files. It looks for them in this order:

1. `[data] root` in `codfh.ini`, beside the executable.
2. The `CODFH_DATA` environment variable.
3. The executable's own folder.

```
set CODFH_DATA=D:\CODFH_DUMP
build\port_sp\codfh.exe
```

`codfh_launcher.exe` sets all of this from a window: the level, the difficulty, the renderer and the
logs. It checks the options before launching and shows tooltips for each one.

### Command line

| Flag | Effect |
|---|---|
| `-map <n\|name>` | Start a level straight away. Takes a number or part of a level's name. Single player uses the campaign's index. The log lists the levels. |
| `-difficulty easy\|medium\|hard` | Single player, with `-map`: the level's difficulty. 0, 1 and 2 also work. |
| `-checkpoint <n>`, `-cp <n>` | Single player, with `-map`: start at checkpoint n, counting from 1. 0 lists the level's checkpoints in the log. |
| `-cpvalue <v>` | Single player: the checkpoint register's value. |
| `-main-menu` / `-no-main-menu` | Single player: skip Press Start and pick the first saved profile, or don't. |
| `-gametype DM\|TDM\|CTF\|SD\|SUP` | Multiplayer, with `-map`: the game type. |
| `-name <name>` | Multiplayer: the name to host under. |
| `-movie <file>` | Play a movie from `SHELL\MOVIES` once the menus are up. |
| `-verbose` | Add the diagnostic lines to the log. |

### Configuration

`codfh.ini` beside the executable. Every key is optional.

| Section | Keys |
|---|---|
| `[video]` | `width`, `height`, `windowed`, `vsync`, `widescreen`, `fill` (stretch to the window, no black bars), `render_scale`, `max_fps`, `adapter` |
| `[input]` | `mouse_sensitivity` |
| `[keys]` | an action, then up to four keys, such as `fire = MOUSE1, CTRL`. The actions are in `port/src/xpal_sys.cpp`'s binding table. |
| `[game]` | `language`, `name` |
| `[data]` | `root` (the disc's files), `user` (saves and the title cache) |
| `[debug]` | `console` (the log in a console window: 1, or 0 for none) |

### Keys

- **F1:** show or hide the overlay. Its Renderer section has the fill and fullscreen switches.
- **F11 or Alt+Enter:** switch between windowed and fullscreen.

The log goes to `codfh.log` beside the executable. If the game crashes, it shows a dialog with the
stack trace, threads, memory and RenderWare state. It also writes a minidump and a zip of the
reports beside the executable.
