/*
 * The platform layer's Xbox system services (docs/WIN32_PORT.md W1, W4): peripherals and
 * controllers (Windows XInput, and the keyboard as the first controller when no pad is in),
 * saves (a folder per save under u:\, the Xbox's layout kept), save signatures (HMAC-SHA1 with
 * a fixed local key), launch data (a file in the user directory), the console's settings (the
 * configuration), and physical memory.
 */
#include <xtl.h>
#include <bcrypt.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <stdlib.h>

#include "port.h"

#undef CreateFileA
#undef GetFileAttributesA
#undef CopyFileA

/*
 * Peripherals
 */

XPP_DEVICE_TYPE XDEVICE_TYPE_GAMEPAD_TABLE;
XPP_DEVICE_TYPE XDEVICE_TYPE_VOICE_MICROPHONE_TABLE;
XPP_DEVICE_TYPE XDEVICE_TYPE_VOICE_HEADPHONE_TABLE;

/* Windows XInput (its header's names clash with the Xbox's: declared here under our own). */
struct WinXInputGamepad
{
    WORD wButtons;
    BYTE bLeftTrigger, bRightTrigger;
    SHORT sThumbLX, sThumbLY, sThumbRX, sThumbRY;
};
struct WinXInputState
{
    DWORD dwPacketNumber;
    WinXInputGamepad Gamepad;
};
struct WinXInputVibration
{
    WORD wLeftMotorSpeed, wRightMotorSpeed;
};
typedef DWORD(WINAPI *XInputGetStateFn)(DWORD, WinXInputState *);
typedef DWORD(WINAPI *XInputSetStateFn)(DWORD, WinXInputVibration *);
static XInputGetStateFn win_get_state;
static XInputSetStateFn win_set_state;
static int xinput_loaded;

static void load_xinput(void)
{
    if (xinput_loaded)
        return;
    xinput_loaded = 1;
    static const char *const dlls[] = {"xinput1_4.dll", "xinput1_3.dll", "xinput9_1_0.dll"};
    for (int i = 0; i < 3; i++)
    {
        HMODULE m = LoadLibraryA(dlls[i]);
        if (m)
        {
            win_get_state = (XInputGetStateFn)GetProcAddress(m, "XInputGetState");
            win_set_state = (XInputSetStateFn)GetProcAddress(m, "XInputSetState");
            plog("controllers: %s", dlls[i]);
            return;
        }
    }
    plog("controllers: no XInput; keyboard only");
}

/* Windows' XInputGetState on a port with no controller is slow (it looks for the device each
   time), and the game asks every frame, and for the device changes as often: a port found empty
   is not asked again for a second. A connected pad is read every call. */
/* The overlay's switch for both input caches (this one and key_front/key_down's); off, every
   poll asks Windows as it comes (CODFH_INPUTCACHE=0 starts so). */
extern "C" int port_input_cache = -1;

static int input_cache_on(void)
{
    if (port_input_cache < 0)
    {
        char v[8];
        port_input_cache = GetEnvironmentVariableA("CODFH_INPUTCACHE", v, sizeof(v)) ? atoi(v) != 0 : 1;
    }
    return port_input_cache;
}

static int poll_pad(DWORD port, WinXInputState *s)
{
    static DWORD empty_since[4];
    static int empty[4];
    if (!win_get_state || port > 3)
        return 0;
    if (!input_cache_on())
        return win_get_state(port, s) == ERROR_SUCCESS;
    if (empty[port] && GetTickCount() - empty_since[port] < 1000)
        return 0;
    if (win_get_state(port, s) == ERROR_SUCCESS)
    {
        empty[port] = 0;
        return 1;
    }
    empty[port] = 1;
    empty_since[port] = GetTickCount();
    return 0;
}

static int pad_connected(DWORD port)
{
    WinXInputState s;
    return poll_pad(port, &s);
}

/* The ports with a controller: the XInput pads, and port 0 always (the keyboard). */
static DWORD gamepad_mask(void)
{
    load_xinput();
    DWORD mask = 1;
    for (DWORD p = 0; p < 4; p++)
        if (pad_connected(p))
            mask |= 1u << p;
    return mask;
}

static DWORD known_mask;

extern "C" VOID WINAPI XInitDevices(DWORD, PXDEVICE_PREALLOC_TYPE)
{
    load_xinput();
}

extern "C" DWORD WINAPI XGetDevices(PXPP_DEVICE_TYPE DeviceType)
{
    if (DeviceType != XDEVICE_TYPE_GAMEPAD)
        return 0;   /* no voice devices, no memory units */
    known_mask = gamepad_mask();
    return known_mask;
}

extern "C" BOOL WINAPI XGetDeviceChanges(PXPP_DEVICE_TYPE DeviceType, PDWORD pdwInsertions, PDWORD pdwRemovals)
{
    *pdwInsertions = *pdwRemovals = 0;
    if (DeviceType != XDEVICE_TYPE_GAMEPAD)
        return FALSE;
    DWORD now = gamepad_mask();
    *pdwInsertions = now & ~known_mask;
    *pdwRemovals = known_mask & ~now;
    known_mask = now;
    return *pdwInsertions || *pdwRemovals;
}

/* Handles: the port + 1. */
extern "C" HANDLE WINAPI XInputOpen(PXPP_DEVICE_TYPE DeviceType, DWORD dwPort, DWORD, PXINPUT_POLLING_PARAMETERS)
{
    if (DeviceType != XDEVICE_TYPE_GAMEPAD || dwPort > 3)
        return NULL;
    return (HANDLE)(ULONG_PTR)(dwPort + 1);
}

extern "C" VOID WINAPI XInputClose(HANDLE)
{
}

extern "C" DWORD WINAPI XInputGetCapabilities(HANDLE hDevice, PXINPUT_CAPABILITIES pCapabilities)
{
    if (!hDevice)
        return ERROR_DEVICE_NOT_CONNECTED;
    memset(pCapabilities, 0, sizeof(*pCapabilities));
    pCapabilities->SubType = 1;     /* a gamepad */
    pCapabilities->In.Gamepad.wButtons = 0xFF;
    memset(pCapabilities->In.Gamepad.bAnalogButtons, 0xFF, 8);
    pCapabilities->In.Gamepad.sThumbLX = pCapabilities->In.Gamepad.sThumbLY = (SHORT)0xFFC0;
    pCapabilities->In.Gamepad.sThumbRX = pCapabilities->In.Gamepad.sThumbRY = (SHORT)0xFFC0;
    pCapabilities->Out.Rumble.wLeftMotorSpeed = pCapabilities->Out.Rumble.wRightMotorSpeed = 0xFFFF;
    return ERROR_SUCCESS;
}

/* Xbox button bits and analog buttons (A B X Y black white left-trigger right-trigger). */
enum
{
    XB_DPAD_UP = 1, XB_DPAD_DOWN = 2, XB_DPAD_LEFT = 4, XB_DPAD_RIGHT = 8,
    XB_START = 0x10, XB_BACK = 0x20, XB_LTHUMB = 0x40, XB_RTHUMB = 0x80
};
enum { XB_A, XB_B, XB_X, XB_Y, XB_BLACK, XB_WHITE, XB_LTRIGGER, XB_RTRIGGER };

#ifdef CODFH_IMGUI
extern "C" int port_imgui_wants_mouse(void);
extern "C" int port_imgui_wants_keyboard(void);
#endif

/* The window in front and the keys' states, read at most every 4 ms: the game polls the pad
   several times a frame, and each poll asked Windows once a key (GetAsyncKeyState and
   GetForegroundWindow are calls into the kernel). */
extern "C" DWORD WINAPI xpal_GetTickCount(void);    /* (xpal_core.cpp: a millisecond tick) */

static int key_front(void)
{
    static DWORD at;
    static int front;
    DWORD now = xpal_GetTickCount();
    if (!input_cache_on())
        return port_hwnd && GetForegroundWindow() == (HWND)port_hwnd;
    if (!at || now - at >= 4)
    {
        at = now ? now : 1;
        front = port_hwnd && GetForegroundWindow() == (HWND)port_hwnd;
    }
    return front;
}

static int key_down(int vk)
{
    static DWORD at[256];
    static unsigned char down[256];
    DWORD now = xpal_GetTickCount();
    vk &= 0xFF;
    if (!input_cache_on())
        return (GetAsyncKeyState(vk) & 0x8000) ? 1 : 0;
    if (!at[vk] || now - at[vk] >= 4)
    {
        at[vk] = now ? now : 1;
        down[vk] = (GetAsyncKeyState(vk) & 0x8000) ? 1 : 0;
    }
    return down[vk];
}

static int key(int vk)
{
#ifdef CODFH_IMGUI
    /* (the overlay's: the mouse while it is shown, the keyboard while a field wants it) */
    if ((vk == VK_LBUTTON || vk == VK_RBUTTON || vk == VK_MBUTTON) ? port_imgui_wants_mouse() : port_imgui_wants_keyboard())
        return 0;
#endif
    return key_front() && key_down(vk);
}

/* The keyboard as a controller: WASD the left stick, the arrows the right, IJKL the d-pad;
   Space A, LeftCtrl B, R X, F Y, Q black, E white, the mouse buttons the triggers; Enter
   start, Escape back, Shift the left stick's click, C the right's. */
/*
 * Keyboard and mouse buttons as the pad, rebindable in codfh.ini's [keys] section: an action,
 * then up to four keys separated by commas (a letter or digit, F1-F12, SPACE ENTER ESCAPE TAB
 * BACKSPACE SHIFT CTRL ALT UP DOWN LEFT RIGHT, MOUSE1-3, or VK<number>). For example
 *     [keys]
 *     fire = MOUSE1, CTRL
 */
enum { BIND_KEYS = 4 };
struct Binding
{
    const char *action;
    const char *defaults;
    int kind;               /* 0 analog button (index), 1 digital button (mask), 2 stick (axis*2+sign) */
    int value;
    int keys[BIND_KEYS];
};
static Binding bindings[] = {
    {"forward", "W", 2, 1 * 2 + 1}, {"back", "S", 2, 1 * 2 + 0},
    {"left", "A", 2, 0 * 2 + 0}, {"right", "D", 2, 0 * 2 + 1},
    {"look_up", "UP", 2, 3 * 2 + 1}, {"look_down", "DOWN", 2, 3 * 2 + 0},
    {"look_left", "LEFT", 2, 2 * 2 + 0}, {"look_right", "RIGHT", 2, 2 * 2 + 1},
    {"dpad_up", "I", 1, XB_DPAD_UP}, {"dpad_down", "K", 1, XB_DPAD_DOWN},
    {"dpad_left", "J", 1, XB_DPAD_LEFT}, {"dpad_right", "L", 1, XB_DPAD_RIGHT},
    {"start", "ENTER", 1, XB_START}, {"back_button", "ESCAPE", 1, XB_BACK},
    {"left_stick", "SHIFT", 1, XB_LTHUMB}, {"right_stick", "C", 1, XB_RTHUMB},
    {"a", "SPACE", 0, XB_A}, {"b", "LCTRL, BACKSPACE", 0, XB_B},
    {"x", "R", 0, XB_X}, {"y", "F", 0, XB_Y},
    {"black", "Q", 0, XB_BLACK}, {"white", "E", 0, XB_WHITE},
    {"aim", "MOUSE2", 0, XB_LTRIGGER}, {"fire", "MOUSE1", 0, XB_RTRIGGER},
};
static int bindings_loaded;

static const struct { const char *name; int vk; } key_names[] = {
    {"SPACE", VK_SPACE}, {"ENTER", VK_RETURN}, {"RETURN", VK_RETURN}, {"ESCAPE", VK_ESCAPE}, {"ESC", VK_ESCAPE},
    {"TAB", VK_TAB}, {"BACKSPACE", VK_BACK}, {"SHIFT", VK_SHIFT}, {"LSHIFT", VK_LSHIFT}, {"RSHIFT", VK_RSHIFT},
    {"CTRL", VK_CONTROL}, {"LCTRL", VK_LCONTROL}, {"RCTRL", VK_RCONTROL}, {"ALT", VK_MENU},
    {"UP", VK_UP}, {"DOWN", VK_DOWN}, {"LEFT", VK_LEFT}, {"RIGHT", VK_RIGHT},
    {"MOUSE1", VK_LBUTTON}, {"MOUSE2", VK_RBUTTON}, {"MOUSE3", VK_MBUTTON},
};

static int key_code(const char *n)
{
    const size_t nNames = sizeof(key_names) / sizeof(key_names[0]);
    if (!n[0])
        return 0;
    if (!n[1] && ((n[0] >= 'A' && n[0] <= 'Z') || (n[0] >= '0' && n[0] <= '9')))
        return n[0];
    if (n[0] == 'F' && n[1] >= '1' && n[1] <= '9')
    {
        int f = atoi(n + 1);
        if (f >= 1 && f <= 12)
            return VK_F1 + f - 1;
    }
    if (!_strnicmp(n, "VK", 2) && n[2] >= '0' && n[2] <= '9')
        return atoi(n + 2);
    for (size_t i = 0; i < nNames; i++)
        if (!_stricmp(n, key_names[i].name))
            return key_names[i].vk;
    return 0;
}

static void parse_keys(Binding *b, const char *list)
{
    char buf[128];
    strncpy(buf, list, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = 0;
    int k = 0;
    memset(b->keys, 0, sizeof(b->keys));
    for (char *t = strtok(buf, ", "); t && k < BIND_KEYS; t = strtok(NULL, ", "))
    {
        for (char *c = t; *c; c++)
            *c = (char)toupper((unsigned char)*c);
        int vk = key_code(t);
        if (vk)
            b->keys[k++] = vk;
        else
            plog("input: [keys] %s: unknown key \"%s\"", b->action, t);
    }
}

static void load_bindings(void)
{
    bindings_loaded = 1;
    char ini[MAX_PATH];
    GetModuleFileNameA(NULL, ini, MAX_PATH);
    char *slash = strrchr(ini, '\\');
    strcpy(slash ? slash + 1 : ini, "codfh.ini");
    int changed = 0;
    for (size_t i = 0; i < sizeof(bindings) / sizeof(bindings[0]); i++)
    {
        char v[128];
        GetPrivateProfileStringA("keys", bindings[i].action, bindings[i].defaults, v, sizeof(v), ini);
        parse_keys(&bindings[i], v);
        changed += strcmp(v, bindings[i].defaults) != 0;
    }
    if (changed)
        plog("input: %d key bindings from codfh.ini", changed);
}

/*
 * The overlay's key binding editor (pd11_imgui.cpp, its Input section): the actions, their keys,
 * a change applied at once and written to codfh.ini's [keys] (a reset removes the line, so the
 * default holds again).
 */
static void bindings_ini(char *ini, size_t n)
{
    GetModuleFileNameA(NULL, ini, (DWORD)n);
    char *slash = strrchr(ini, '\\');
    strcpy(slash ? slash + 1 : ini, "codfh.ini");
}

/* A key's name as codfh.ini takes it: the first name in key_names, a letter or digit, F1-F12,
   else VK<number>. */
extern "C" void port_key_name(int vk, char *out, int n)
{
    if (n <= 0)
        return;
    out[0] = 0;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9'))
        _snprintf(out, n, "%c", vk);
    else if (vk >= VK_F1 && vk <= VK_F12)
        _snprintf(out, n, "F%d", vk - VK_F1 + 1);
    else
    {
        for (size_t i = 0; i < sizeof(key_names) / sizeof(key_names[0]); i++)
            if (key_names[i].vk == vk)
            {
                _snprintf(out, n, "%s", key_names[i].name);
                break;
            }
        if (!out[0])
            _snprintf(out, n, "VK%d", vk);
    }
    out[n - 1] = 0;
}

extern "C" int port_bind_count(void)
{
    if (!bindings_loaded)
        load_bindings();
    return (int)(sizeof(bindings) / sizeof(bindings[0]));
}

extern "C" const char *port_bind_action(int i)
{
    return i >= 0 && i < port_bind_count() ? bindings[i].action : "";
}

/* Its keys into keys[4]; how many. */
extern "C" int port_bind_keys(int i, int *keys)
{
    int n = 0;
    if (i < 0 || i >= port_bind_count())
        return 0;
    for (int k = 0; k < BIND_KEYS; k++)
    {
        keys[k] = bindings[i].keys[k];
        if (keys[k])
            n++;
    }
    return n;
}

/* Its keys set (up to four), and written to codfh.ini. */
extern "C" void port_bind_set(int i, const int *keys, int n)
{
    char ini[MAX_PATH], line[128] = "", name[16];
    if (i < 0 || i >= port_bind_count())
        return;
    memset(bindings[i].keys, 0, sizeof(bindings[i].keys));
    int k = 0;
    for (int j = 0; j < n && k < BIND_KEYS; j++)
        if (keys[j])
        {
            bindings[i].keys[k++] = keys[j];
            port_key_name(keys[j], name, sizeof(name));
            if (line[0])
                strcat(line, ", ");
            strcat(line, name);
        }
    bindings_ini(ini, sizeof(ini));
    /* (no keys: written as an empty value, so the action stays unbound rather than default) */
    WritePrivateProfileStringA("keys", bindings[i].action, line, ini);
    plog("input: %s = %s", bindings[i].action, line[0] ? line : "(none)");
}

/* Its default keys back, its line removed from codfh.ini. */
extern "C" void port_bind_reset(int i)
{
    char ini[MAX_PATH];
    if (i < 0 || i >= port_bind_count())
        return;
    parse_keys(&bindings[i], bindings[i].defaults);
    bindings_ini(ini, sizeof(ini));
    WritePrivateProfileStringA("keys", bindings[i].action, NULL, ini);
}

static void keyboard_state(XINPUT_GAMEPAD *g)
{
    if (!bindings_loaded)
        load_bindings();
    for (size_t i = 0; i < sizeof(bindings) / sizeof(bindings[0]); i++)
    {
        const Binding &b = bindings[i];
        int down = 0;
        for (int k = 0; k < BIND_KEYS && b.keys[k] && !down; k++)
            down = key(b.keys[k]);
        if (!down)
            continue;
        if (b.kind == 0)
            g->bAnalogButtons[b.value] = 255;
        else if (b.kind == 1)
            g->wButtons |= (WORD)b.value;
        else
        {
            SHORT v = (b.value & 1) ? 32767 : -32768;
            switch (b.value >> 1)
            {
            case 0: g->sThumbLX = v; break;
            case 1: g->sThumbLY = v; break;
            case 2: g->sThumbRX = v; break;
            default: g->sThumbRY = v; break;
            }
        }
    }
}

static DWORD packets[4];

extern volatile LONG port_mouse_dx, port_mouse_dy;

/* The mouse's movement as the right stick: counts per read scaled by the sensitivity, full
   deflection at about 25 counts a frame at 1.0 (codfh.ini [input] mouse_sensitivity). */
/*
 * Direct mouse look: the player's view code (unit_0FD730's sub_109AE0 and sub_10A330) takes the
 * mouse's movement in degrees, 0.1 a count at a sensitivity of 1 ([input] mouse_sensitivity).
 * While it does, the mouse no longer drives the right stick (mouse_state).
 */
static unsigned direct_look_frame;
static int script_count_fwd(void);

static int direct_look_ready(void)
{
    if (script_count_fwd() > 0)
        return 1;   /* (scripted input: in front or not) */
    if (!key_front())
        return 0;
#ifdef CODFH_IMGUI
    if (port_imgui_wants_mouse())
        return 0;
#endif
    return 1;
}

static float look_scale(void)
{
    return 0.1f * (port_config.mouseSensitivity > 0 ? port_config.mouseSensitivity : 1.0f);
}

/* (right turns the view right: the view's yaw grows to the left) */
extern "C" float port_mouse_yaw(void)
{
    direct_look_frame = port_frame;
    LONG dx = InterlockedExchange(&port_mouse_dx, 0);
    return direct_look_ready() ? -dx * look_scale() : 0.0f;
}

/* (the mouse forward looks up, as most PC games: the pitch grows downward) */
extern "C" float port_mouse_pitch(void)
{
    direct_look_frame = port_frame;
    LONG dy = InterlockedExchange(&port_mouse_dy, 0);
    return direct_look_ready() ? dy * look_scale() : 0.0f;
}

static void mouse_state(XINPUT_GAMEPAD *g)
{
    /* (the view takes the mouse directly while it asks for it) */
    if (direct_look_frame && port_frame - direct_look_frame <= 2)
        return;
    LONG dx = InterlockedExchange(&port_mouse_dx, 0), dy = InterlockedExchange(&port_mouse_dy, 0);
#ifdef CODFH_IMGUI
    if (port_imgui_wants_mouse())
        return;
#endif
    if (!key_front())
        return;
    float s = port_config.mouseSensitivity > 0 ? port_config.mouseSensitivity : 1.0f;
    float x = dx * s * 1300.0f, y = -dy * s * 1300.0f;
    if (x || y)
    {
        float nx = g->sThumbRX + x, ny = g->sThumbRY + y;
        g->sThumbRX = (SHORT)(nx > 32767 ? 32767 : nx < -32768 ? -32768 : nx);
        g->sThumbRY = (SHORT)(ny > 32767 ? 32767 : ny < -32768 ? -32768 : ny);
    }
}

/* The mouse's buttons in the menus (menumouse.cpp, winmain.cpp) as the pad's: a click A (on a
   setting's arrows the d-pad's left or right), the right button B, the wheel the d-pad's up and
   down; each held 60 ms so the menus read a press,
   the wheel's notches one at a time (held 60 ms, released 60 ms). */
extern "C" volatile LONG port_menu_mouse_clicks, port_menu_mouse_backs, port_menu_mouse_wheel;
extern "C" volatile LONG port_menu_mouse_lefts, port_menu_mouse_rights;
extern "C" int port_in_menus(void);

#ifdef CODFH_DRAW_TRIGGERS
extern "C" int port_freecam_input(XINPUT_GAMEPAD *pPad);
#endif

static void menu_mouse_state(XINPUT_GAMEPAD *g)
{
    static DWORD a_until, b_until, wheel_until, left_until, right_until;
    static int wheel_dir;
    static LONG wheel_pending;
    DWORD now = GetTickCount();
    if (!port_in_menus())
    {
        InterlockedExchange(&port_menu_mouse_clicks, 0);
        InterlockedExchange(&port_menu_mouse_backs, 0);
        InterlockedExchange(&port_menu_mouse_wheel, 0);
        InterlockedExchange(&port_menu_mouse_lefts, 0);
        InterlockedExchange(&port_menu_mouse_rights, 0);
        wheel_pending = 0;
        return;
    }
    if (InterlockedExchange(&port_menu_mouse_lefts, 0))
        left_until = now + 60;
    if (InterlockedExchange(&port_menu_mouse_rights, 0))
        right_until = now + 60;
    if ((LONG)(left_until - now) > 0)
        g->wButtons |= XB_DPAD_LEFT;
    if ((LONG)(right_until - now) > 0)
        g->wButtons |= XB_DPAD_RIGHT;
    if (InterlockedExchange(&port_menu_mouse_clicks, 0))
        a_until = now + 60;
    if (InterlockedExchange(&port_menu_mouse_backs, 0))
        b_until = now + 60;
    wheel_pending += InterlockedExchange(&port_menu_mouse_wheel, 0);
    if (wheel_pending && (LONG)(now - wheel_until) > 60)
    {
        wheel_dir = wheel_pending > 0 ? 1 : -1;
        wheel_pending -= wheel_dir;
        wheel_until = now + 60;
    }
    if ((LONG)(a_until - now) > 0)
        g->bAnalogButtons[XB_A] = 255;
    if ((LONG)(b_until - now) > 0)
        g->bAnalogButtons[XB_B] = 255;
    if ((LONG)(wheel_until - now) > 0)
        g->wButtons |= wheel_dir > 0 ? XB_DPAD_UP : XB_DPAD_DOWN;
}

/* CODFH_INPUT: "frame:button,frame:button,..." holds pad 0's button for 8 frames from that
   frame (A B X Y BLACK WHITE LT RT START BACK UP DOWN LEFT RIGHT; stick directions LUP LDOWN
   LLEFT LRIGHT), for driving the game without a person. */
struct ScriptedPress
{
    unsigned frame;
    char button[8];
};
static ScriptedPress script[256];
static int script_count = -1;
static int script_count_fwd(void)
{
    return script_count;
}

static void load_script(void)
{
    script_count = 0;
    char v[4096];
    if (!GetEnvironmentVariableA("CODFH_INPUT", v, sizeof(v)))
        return;
    for (char *tok = strtok(v, ","); tok && script_count < 256; tok = strtok(NULL, ","))
    {
        char *colon = strchr(tok, ':');
        if (!colon)
            continue;
        *colon = 0;
        script[script_count].frame = (unsigned)atoi(tok);
        strncpy(script[script_count].button, colon + 1, 7);
        script_count++;
    }
    plog("scripted input: %d presses", script_count);
}

static void scripted_state(XINPUT_GAMEPAD *g)
{
    if (script_count < 0)
        load_script();
    unsigned f = port_frame;
    for (int i = 0; i < script_count; i++)
    {
        if (f < script[i].frame || f >= script[i].frame + 8)
            continue;
        const char *b = script[i].button;
        static const char *const analog[8] = {"A", "B", "X", "Y", "BLACK", "WHITE", "LT", "RT"};
        for (int k = 0; k < 8; k++)
            if (!strcmp(b, analog[k]))
                g->bAnalogButtons[k] = 255;
        if (!strcmp(b, "START")) g->wButtons |= XB_START;
        if (!strcmp(b, "BACK")) g->wButtons |= XB_BACK;
        if (!strcmp(b, "UP")) g->wButtons |= XB_DPAD_UP;
        if (!strcmp(b, "DOWN")) g->wButtons |= XB_DPAD_DOWN;
        if (!strcmp(b, "LEFT")) g->wButtons |= XB_DPAD_LEFT;
        if (!strcmp(b, "RIGHT")) g->wButtons |= XB_DPAD_RIGHT;
        if (!strcmp(b, "LUP")) g->sThumbLY = 32767;
        if (!strcmp(b, "LDOWN")) g->sThumbLY = -32768;
        if (!strcmp(b, "LLEFT")) g->sThumbLX = -32768;
        if (!strcmp(b, "LRIGHT")) g->sThumbLX = 32767;
        /* (mouse movement, 20 counts a read: the direct look's test) */
        if (!strcmp(b, "MUP")) InterlockedExchangeAdd(&port_mouse_dy, -20);
        if (!strcmp(b, "MDOWN")) InterlockedExchangeAdd(&port_mouse_dy, 20);
        if (!strcmp(b, "MLEFT")) InterlockedExchangeAdd(&port_mouse_dx, -20);
        if (!strcmp(b, "MRIGHT")) InterlockedExchangeAdd(&port_mouse_dx, 20);
    }
}

extern "C" DWORD WINAPI XInputGetState(HANDLE hDevice, PXINPUT_STATE pState)
{
    DWORD port = (DWORD)(ULONG_PTR)hDevice - 1;
    if (port > 3)
        return ERROR_DEVICE_NOT_CONNECTED;
    XINPUT_STATE s;
    memset(&s, 0, sizeof(s));
    WinXInputState w;
#ifdef CODFH_DEDICATED
    int have = 0;       /* (the server reads no controllers) */
#else
    int have = poll_pad(port, &w);
#endif
    if (have)
    {
        XINPUT_GAMEPAD *g = &s.Gamepad;
        g->wButtons = w.Gamepad.wButtons & 0xFF;    /* d-pad, start, back, thumbs: the same bits */
        g->bAnalogButtons[XB_A] = (w.Gamepad.wButtons & 0x1000) ? 255 : 0;
        g->bAnalogButtons[XB_B] = (w.Gamepad.wButtons & 0x2000) ? 255 : 0;
        g->bAnalogButtons[XB_X] = (w.Gamepad.wButtons & 0x4000) ? 255 : 0;
        g->bAnalogButtons[XB_Y] = (w.Gamepad.wButtons & 0x8000) ? 255 : 0;
        g->bAnalogButtons[XB_BLACK] = (w.Gamepad.wButtons & 0x0200) ? 255 : 0;  /* right shoulder */
        g->bAnalogButtons[XB_WHITE] = (w.Gamepad.wButtons & 0x0100) ? 255 : 0;  /* left shoulder */
        g->bAnalogButtons[XB_LTRIGGER] = w.Gamepad.bLeftTrigger;
        g->bAnalogButtons[XB_RTRIGGER] = w.Gamepad.bRightTrigger;
        g->sThumbLX = w.Gamepad.sThumbLX;
        g->sThumbLY = w.Gamepad.sThumbLY;
        g->sThumbRX = w.Gamepad.sThumbRX;
        g->sThumbRY = w.Gamepad.sThumbRY;
    }
    else if (port != 0)
        return ERROR_DEVICE_NOT_CONNECTED;
    if (port == 0)
    {
#ifndef CODFH_DEDICATED
        keyboard_state(&s.Gamepad);
        mouse_state(&s.Gamepad);
        menu_mouse_state(&s.Gamepad);
#endif
        scripted_state(&s.Gamepad);
#ifdef CODFH_DRAW_TRIGGERS
        /* the debug tools' free camera (port/src/debug/trigdraw.cpp) takes the pad while it is on:
           the game gets a neutral one, but for start and back */
        if (port_freecam_input(&s.Gamepad))
        {
            WORD keep = s.Gamepad.wButtons & (XB_START | XB_BACK);
            memset(&s.Gamepad, 0, sizeof(s.Gamepad));
            s.Gamepad.wButtons = keep;
        }
#endif
    }
    if (memcmp(&s.Gamepad, &pState->Gamepad, sizeof(s.Gamepad)))
        packets[port]++;
    s.dwPacketNumber = packets[port];
    *pState = s;
    return ERROR_SUCCESS;
}

extern "C" DWORD WINAPI XInputSetState(HANDLE hDevice, PXINPUT_FEEDBACK pFeedback)
{
    DWORD port = (DWORD)(ULONG_PTR)hDevice - 1;
    if (port <= 3 && win_set_state)
    {
        WinXInputVibration v = {pFeedback->Rumble.wLeftMotorSpeed, pFeedback->Rumble.wRightMotorSpeed};
        win_set_state(port, &v);
    }
    pFeedback->Header.dwStatus = ERROR_SUCCESS;
    return ERROR_SUCCESS;
}

/*
 * Saves: u:\<8 hex digits>\ per save, its name in SaveMeta.xbx as on the Xbox.
 */

static DWORD name_hash(LPCWSTR name)
{
    DWORD h = 2166136261u;
    for (; *name; name++)
        h = (h ^ (DWORD)*name) * 16777619u;
    return h;
}

static void save_dir(LPCSTR root, LPCWSTR name, char *xboxDir, size_t n)
{
    _snprintf(xboxDir, n, "%c:\\%08lX\\", root && root[0] ? root[0] : 'u', name_hash(name));
}

static void write_meta(const char *dir, LPCWSTR name)
{
    char path[520];
    _snprintf(path, sizeof(path), "%sSaveMeta.xbx", dir);
    FILE *f = fopen(path, "wb");
    if (!f)
        return;
    WORD bom = 0xFEFF;
    fwrite(&bom, 2, 1, f);
    fwrite(L"Name=", 2, 5, f);
    fwrite(name, 2, wcslen(name), f);
    fwrite(L"\r\n", 2, 2, f);
    fclose(f);
}

static int read_meta(const char *dir, WCHAR *name, size_t n)
{
    char path[520];
    _snprintf(path, sizeof(path), "%sSaveMeta.xbx", dir);
    FILE *f = fopen(path, "rb");
    if (!f)
        return 0;
    WCHAR buf[512] = {0};
    size_t got = fread(buf, 2, 511, f);
    fclose(f);
    buf[got] = 0;
    WCHAR *p = wcsstr(buf, L"Name=");
    if (!p)
        return 0;
    p += 5;
    size_t i = 0;
    while (p[i] && p[i] != L'\r' && p[i] != L'\n' && i + 1 < n)
    {
        name[i] = p[i];
        i++;
    }
    name[i] = 0;
    return 1;
}

extern "C" DWORD WINAPI XCreateSaveGame(LPCSTR lpRootPathName, LPCWSTR lpSaveGameName, DWORD dwCreationDisposition,
                                        DWORD, LPSTR lpPathBuffer, UINT uSize)
{
    char xdir[64], dir[520];
    save_dir(lpRootPathName, lpSaveGameName, xdir, sizeof(xdir));
    port_map_path(xdir, dir);
    DWORD attr = GetFileAttributesA(dir);
    int exists = attr != INVALID_FILE_ATTRIBUTES;
    if (exists && dwCreationDisposition == CREATE_NEW)
        return ERROR_ALREADY_EXISTS;
    if (!exists && (dwCreationDisposition == OPEN_EXISTING))
        return ERROR_FILE_NOT_FOUND;
    if (!exists && !CreateDirectoryA(dir, NULL))
        return GetLastError();
    write_meta(dir, lpSaveGameName);
    if (lpPathBuffer && uSize)
    {
        strncpy(lpPathBuffer, xdir, uSize - 1);
        lpPathBuffer[uSize - 1] = 0;
    }
    return ERROR_SUCCESS;
}

static void delete_tree(const char *dir)
{
    char pat[520];
    _snprintf(pat, sizeof(pat), "%s*", dir);
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pat, &fd);
    if (h != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
                continue;
            char p[520];
            _snprintf(p, sizeof(p), "%s%s", dir, fd.cFileName);
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                strcat(p, "\\");
                delete_tree(p);
            }
            else
                DeleteFileA(p);
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
    RemoveDirectoryA(dir);
}

extern "C" DWORD WINAPI XDeleteSaveGame(LPCSTR lpRootPathName, LPCWSTR lpSaveGameName)
{
    char xdir[64], dir[520];
    save_dir(lpRootPathName, lpSaveGameName, xdir, sizeof(xdir));
    port_map_path(xdir, dir);
    if (GetFileAttributesA(dir) == INVALID_FILE_ATTRIBUTES)
        return ERROR_FILE_NOT_FOUND;
    delete_tree(dir);
    return ERROR_SUCCESS;
}

struct SaveFind
{
    HANDLE find;
    char root;
    char dir[520];
};

static BOOL next_save(SaveFind *s, PXGAME_FIND_DATA out, int first, WIN32_FIND_DATAA *fd)
{
    for (;;)
    {
        if (!first && !FindNextFileA(s->find, fd))
            return FALSE;
        first = 0;
        if (!(fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || fd->cFileName[0] == '.')
            continue;
        char d[520];
        _snprintf(d, sizeof(d), "%s%s\\", s->dir, fd->cFileName);
        WCHAR name[MAX_GAMENAME];
        if (!read_meta(d, name, MAX_GAMENAME))
            continue;
        memset(out, 0, sizeof(*out));
        out->wfd = *fd;
        _snprintf(out->szSaveGameDirectory, MAX_PATH, "%c:\\%s\\", s->root, fd->cFileName);
        wcsncpy(out->szSaveGameName, name, MAX_GAMENAME - 1);
        return TRUE;
    }
}

extern "C" HANDLE WINAPI XFindFirstSaveGame(LPCSTR lpRootPathName, PXGAME_FIND_DATA pFindGameData)
{
    SaveFind *s = (SaveFind *)calloc(1, sizeof(SaveFind));
    char xroot[4] = {lpRootPathName && lpRootPathName[0] ? lpRootPathName[0] : 'u', ':', '\\', 0};
    s->root = xroot[0];
    port_map_path(xroot, s->dir);
    char pat[520];
    _snprintf(pat, sizeof(pat), "%s*", s->dir);
    WIN32_FIND_DATAA fd;
    s->find = FindFirstFileA(pat, &fd);
    if (s->find == INVALID_HANDLE_VALUE || !next_save(s, pFindGameData, 1, &fd))
    {
        if (s->find != INVALID_HANDLE_VALUE)
            FindClose(s->find);
        free(s);
        SetLastError(ERROR_NO_MORE_FILES);
        return INVALID_HANDLE_VALUE;
    }
    return (HANDLE)s;
}

extern "C" BOOL WINAPI XFindNextSaveGame(HANDLE hFindGame, PXGAME_FIND_DATA pFindGameData)
{
    SaveFind *s = (SaveFind *)hFindGame;
    WIN32_FIND_DATAA fd;
    if (!s || !next_save(s, pFindGameData, 0, &fd))
    {
        SetLastError(ERROR_NO_MORE_FILES);
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL WINAPI XFindClose(HANDLE hFind)
{
    /* (the game closes only its save-game searches with it) */
    SaveFind *s = (SaveFind *)hFind;
    if (!s || hFind == INVALID_HANDLE_VALUE)
        return FALSE;
    if (s->find != INVALID_HANDLE_VALUE)
        FindClose(s->find);
    free(s);
    return TRUE;
}

/*
 * Save signatures: HMAC-SHA1 under a fixed key (saves are this machine's).
 */

static const BYTE sig_key[16] = {'C', 'O', 'D', 'F', 'H', '-', 'P', 'C', '-', 'S', 'A', 'V', 'E', 'K', 'E', 'Y'};

struct SigState
{
    BCRYPT_ALG_HANDLE alg;
    BCRYPT_HASH_HANDLE hash;
};

extern "C" HANDLE WINAPI XCalculateSignatureBegin(DWORD)
{
    SigState *s = (SigState *)calloc(1, sizeof(SigState));
    if (BCryptOpenAlgorithmProvider(&s->alg, BCRYPT_SHA1_ALGORITHM, NULL, BCRYPT_ALG_HANDLE_HMAC_FLAG) ||
        BCryptCreateHash(s->alg, &s->hash, NULL, 0, (PUCHAR)sig_key, sizeof(sig_key), 0))
    {
        free(s);
        return INVALID_HANDLE_VALUE;
    }
    return (HANDLE)s;
}

extern "C" DWORD WINAPI XCalculateSignatureUpdate(HANDLE hCalcSig, const BYTE *pbData, ULONG cbData)
{
    SigState *s = (SigState *)hCalcSig;
    BCryptHashData(s->hash, (PUCHAR)pbData, cbData, 0);
    return ERROR_SUCCESS;
}

extern "C" DWORD WINAPI XCalculateSignatureEnd(HANDLE hCalcSig, PVOID pSignature)
{
    SigState *s = (SigState *)hCalcSig;
    BCryptFinishHash(s->hash, (PUCHAR)pSignature, XCALCSIG_SIGNATURE_SIZE, 0);
    BCryptDestroyHash(s->hash);
    BCryptCloseAlgorithmProvider(s->alg, 0);
    free(s);
    return ERROR_SUCCESS;
}

/*
 * Launch data: the port "launches" itself by leaving launch.bin in the user directory.
 */

static void launch_file(char *path, size_t n)
{
    _snprintf(path, n, "%s\\launch.bin", port_config.userRoot);
}

extern "C" DWORD WINAPI XGetLaunchInfo(PDWORD pdwLaunchDataType, PLAUNCH_DATA pLaunchData)
{
    char path[520];
    launch_file(path, sizeof(path));
    FILE *f = fopen(path, "rb");
    memset(pLaunchData, 0, sizeof(*pLaunchData));
    if (f)
    {
        DWORD type = LDT_TITLE;
        fread(&type, 4, 1, f);
        fread(pLaunchData, 1, sizeof(*pLaunchData), f);
        fclose(f);
        DeleteFileA(path);
        *pdwLaunchDataType = type;
        plog("launch data: type %lu", type);
        return ERROR_SUCCESS;
    }
    /* none: a start as from the debugger */
    *pdwLaunchDataType = LDT_FROM_DEBUGGER_CMDLINE;
    return ERROR_SUCCESS;
}

extern "C" DWORD WINAPI XLaunchNewImageA(LPCSTR lpImagePath, PLAUNCH_DATA pLaunchData)
{
    plog("XLaunchNewImage(%s)", lpImagePath ? lpImagePath : "(dashboard)");
    if (!lpImagePath)
    {
        /* the dashboard (its memory screen when saves would not fit): PC saves have no limit */
        MessageBoxA((HWND)port_hwnd, "The game asked for the Xbox dashboard; there is none on PC.",
                    "Call of Duty: Finest Hour", MB_OK | MB_ICONINFORMATION);
    }
    else if (pLaunchData)
    {
        char path[520];
        launch_file(path, sizeof(path));
        FILE *f = fopen(path, "wb");
        if (f)
        {
            DWORD type = LDT_TITLE;
            fwrite(&type, 4, 1, f);
            fwrite(pLaunchData, 1, sizeof(*pLaunchData), f);
            fclose(f);
        }
    }
    /* (no other title to start on PC: the port exits, as the Xbox leaves the title) */
    ExitProcess(0);
    return ERROR_SUCCESS;
}

/*
 * The console's settings
 */

extern "C" DWORD WINAPI XGetVideoFlags(VOID)
{
    return port_config.widescreen ? XC_VIDEO_FLAGS_WIDESCREEN : 0;
}

extern "C" DWORD WINAPI XGetVideoStandard(VOID)
{
    return 1;   /* NTSC-M: 60 Hz */
}

extern "C" DWORD WINAPI XGetAudioFlags(VOID)
{
    return 0;   /* stereo */
}

/*
 * Physical memory: RenderWare keeps an address's low 31 bits and restores bit 31 (the Xbox's
 * contiguous mapping), so the memory comes from the top of the address space, where bit 31 is
 * set (the executable is large-address aware). Each allocation gets a page more: on the Xbox a
 * read past the end lands in the next memory, and some draws' declarations reach past their
 * stream's last vertex (a 20-byte stride under a 28-byte declaration read 8 bytes beyond it).
 */

extern "C" LPVOID WINAPI XPhysicalAlloc(SIZE_T dwSize, ULONG_PTR, ULONG_PTR ulAlignment, DWORD flProtect)
{
    (void)ulAlignment;      /* (allocations are 64 KB aligned) */
    (void)flProtect;
    void *p = VirtualAlloc(NULL, dwSize + 4096, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);
    if (p && !((ULONG_PTR)p & 0x80000000))
    {
        plog("XPhysicalAlloc: %lu bytes at %p, below 2 GB (the driver's addresses would break)",
             (unsigned long)dwSize, p);
        VirtualFree(p, 0, MEM_RELEASE);
        return NULL;
    }
    return p;
}

extern "C" VOID WINAPI XPhysicalFree(LPVOID lpAddress)
{
    VirtualFree(lpAddress, 0, MEM_RELEASE);
}
