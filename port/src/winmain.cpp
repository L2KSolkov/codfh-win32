/*
 * The port's entry point (docs/WIN32_PORT.md W0.3, section 6.1): the configuration, the window,
 * the timer resolution, then the game's own main (unit_19CD50.cpp), which the Xbox's
 * mainXapiStartup calls. Window messages are pumped from the device's Present (the bridge), once
 * a frame, the Xbox's frame boundary.
 */
#include <xtl.h>
#include <mmsystem.h>
#include <stdlib.h>

#include "port.h"
#include "d3d/pdev.h"

extern "C" void port_audio_shutdown(void);

int main();
extern "C" void port_crash_handler_install(void);

/* The mouse's movement since the controllers last read it (xpal_sys.cpp turns it into the right
   stick). */
volatile LONG port_mouse_dx, port_mouse_dy;
/* the wheel's notches since the controllers last read it (up positive) */
volatile LONG port_mouse_wheel;
/* the cursor is the game's (confined to the window after a click), and the mouse reports
   positions rather than movement (Remote Desktop's): look then comes from the cursor kept at the
   window's centre (port/src/xpal_sys.cpp) */
volatile LONG port_mouse_captured, port_mouse_absolute;

/* CODFH_INPUT_BACKGROUND=1: the keyboard and mouse read while another window is in front (for
   driving the game from a script when Windows will not give it the foreground). */
extern "C" int port_input_background(void)
{
    static int on = -1;
    if (on < 0)
    {
        char v[8];
        on = GetEnvironmentVariableA("CODFH_INPUT_BACKGROUND", v, sizeof(v)) ? 1 : 0;
    }
    return on;
}

static void confine_cursor(HWND hwnd, int on)
{
    if (on && !port_mouse_absolute)
    {
        RECT r;
        GetClientRect(hwnd, &r);
        MapWindowPoints(hwnd, NULL, (POINT *)&r, 2);
        ClipCursor(&r);
    }
    else
        ClipCursor(NULL);
    InterlockedExchange(&port_mouse_captured, on);
}

static int fullscreen;
static RECT windowed_rect;
static const DWORD windowed_style = WS_OVERLAPPEDWINDOW;

static void set_fullscreen(HWND hwnd, int on)
{
    if (on == fullscreen)
        return;
    if (on)
    {
        GetWindowRect(hwnd, &windowed_rect);
        MONITORINFO mi = {sizeof(mi)};
        GetMonitorInfoA(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST), &mi);
        SetWindowLongA(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left,
                     mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    }
    else
    {
        SetWindowLongA(hwnd, GWL_STYLE, windowed_style | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_NOTOPMOST, windowed_rect.left, windowed_rect.top, windowed_rect.right - windowed_rect.left,
                     windowed_rect.bottom - windowed_rect.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    }
    fullscreen = on;
    plog("display: %s", on ? "fullscreen" : "windowed");
}

/*
 * The keys and mouse buttons held, from the window's own messages (port/src/xpal_sys.cpp reads
 * them with GetAsyncKeyState as a fallback): Remote Desktop delivers its input as messages, which
 * the asynchronous key state does not always see.
 */
volatile unsigned char port_keys[256];

static void set_key(WPARAM vk, LPARAM lp, unsigned char down)
{
    if (vk >= 256)
        return;
    port_keys[vk] = down;
    /* (the left and right variants too, as GetAsyncKeyState gives them) */
    if (vk == VK_SHIFT)
    {
        UINT side = MapVirtualKeyA((UINT)(lp >> 16) & 0xFF, MAPVK_VSC_TO_VK_EX);
        if (side == VK_LSHIFT || side == VK_RSHIFT)
            port_keys[side] = down;
    }
    else if (vk == VK_CONTROL)
        port_keys[(lp & (1 << 24)) ? VK_RCONTROL : VK_LCONTROL] = down;
    else if (vk == VK_MENU)
        port_keys[(lp & (1 << 24)) ? VK_RMENU : VK_LMENU] = down;
}

static void track_input(UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_KEYDOWN: case WM_SYSKEYDOWN: set_key(wp, lp, 1); break;
    case WM_KEYUP: case WM_SYSKEYUP: set_key(wp, lp, 0); break;
    case WM_LBUTTONDOWN: port_keys[VK_LBUTTON] = 1; break;
    case WM_LBUTTONUP: port_keys[VK_LBUTTON] = 0; break;
    case WM_RBUTTONDOWN: port_keys[VK_RBUTTON] = 1; break;
    case WM_RBUTTONUP: port_keys[VK_RBUTTON] = 0; break;
    case WM_MBUTTONDOWN: port_keys[VK_MBUTTON] = 1; break;
    case WM_MBUTTONUP: port_keys[VK_MBUTTON] = 0; break;
    case WM_KILLFOCUS:
        /* (nothing stays held when the window loses the keyboard) */
        for (int i = 0; i < 256; i++)
            port_keys[i] = 0;
        break;
    }
}

static LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    track_input(msg, wp, lp);
    switch (msg)
    {
    case WM_INPUT:
    {
        RAWINPUT ri;
        UINT size = sizeof(ri);
        if (GetRawInputData((HRAWINPUT)lp, RID_INPUT, &ri, &size, sizeof(RAWINPUTHEADER)) != (UINT)-1 &&
            ri.header.dwType == RIM_TYPEMOUSE)
        {
            if (ri.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
            {
                /* (Remote Desktop and tablets: positions, not movement) */
                if (!port_mouse_absolute)
                {
                    plog("input: the mouse reports positions (Remote Desktop?): look from the cursor");
                    InterlockedExchange(&port_mouse_absolute, 1);
                }
            }
            else
            {
                /* (movement: a local mouse, or a Remote Desktop client in relative mouse mode) */
                if (port_mouse_absolute && (ri.data.mouse.lLastX || ri.data.mouse.lLastY))
                {
                    plog("input: the mouse reports movement: look from it");
                    InterlockedExchange(&port_mouse_absolute, 0);
                }
                InterlockedExchangeAdd(&port_mouse_dx, ri.data.mouse.lLastX);
                InterlockedExchangeAdd(&port_mouse_dy, ri.data.mouse.lLastY);
            }
            if (ri.data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
                InterlockedExchangeAdd(&port_mouse_wheel, (SHORT)ri.data.mouse.usButtonData / WHEEL_DELTA);
        }
        break;
    }
    case WM_LBUTTONDOWN:
        /* (the mouse is the game's once the player clicks into the window) */
        confine_cursor(hwnd, 1);
        break;
    case WM_ACTIVATE:
        if (LOWORD(wp) == WA_INACTIVE)
            confine_cursor(hwnd, 0);
        break;
    case WM_CLOSE:
        port_quit = 1;
        return 0;
    case WM_SIZE:
        pdev_window_resized();
        break;
    case WM_SYSKEYDOWN:
        /* Alt+Enter: windowed and fullscreen (a borderless window over the monitor) */
        if (wp == VK_RETURN && (lp & (1 << 29)) && !(lp & (1 << 30)))
        {
            set_fullscreen(hwnd, !fullscreen);
            return 0;
        }
        break;
    case WM_SETCURSOR:
        if (LOWORD(lp) == HTCLIENT)
        {
            SetCursor(NULL);
            return TRUE;
        }
        break;
    case WM_SYSCOMMAND:
        /* (no screen saver or menu-key pause while the game runs) */
        if ((wp & 0xFFF0) == SC_SCREENSAVE || (wp & 0xFFF0) == SC_MONITORPOWER || (wp & 0xFFF0) == SC_KEYMENU)
            return 0;
        break;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

extern "C" int port_pump_messages(void)
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    if (port_quit)
    {
        /* (the game has no shutdown path of its own: the Xbox never returns from a title; the
           port stops what runs beside the game, then exits) */
        plog("window closed: exiting");
        port_audio_shutdown();
        ClipCursor(NULL);
        ExitProcess(0);
    }
    return !port_quit;
}

static void create_window(HINSTANCE inst)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = wndproc;
    wc.hInstance = inst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "CODFH";
    RegisterClassA(&wc);

    DWORD style = windowed_style;
    RECT r = {0, 0, port_config.width, port_config.height};
    AdjustWindowRect(&r, style, FALSE);
    int w = r.right - r.left, h = r.bottom - r.top;
    int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
    HWND hwnd = CreateWindowA("CODFH", "Call of Duty: Finest Hour", style, x < 0 ? 0 : x, y < 0 ? 0 : y,
                              w, h, NULL, NULL, inst, NULL);
#ifndef CODFH_DEDICATED
    if (!port_config.windowed)
        set_fullscreen(hwnd, 1);
#endif
#ifdef CODFH_DEDICATED
    /* (the server's window is never shown: it only carries the messages) */
    port_hwnd = hwnd;
#else
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    port_hwnd = hwnd;
    RAWINPUTDEVICE rid = {0x01, 0x02, port_input_background() ? (DWORD)RIDEV_INPUTSINK : 0, hwnd};    /* the mouse */
    if (GetSystemMetrics(SM_REMOTESESSION))
    {
        plog("input: a Remote Desktop session: look from the cursor");
        port_mouse_absolute = 1;
    }
    RegisterRawInputDevices(&rid, 1, sizeof(rid));
#endif
}

extern "C" void port_cli_parse(const char *cmd);

#ifdef CODFH_DEDICATED
/* Ctrl+C or closing the console ends the server as closing the window ends the game. */
static BOOL WINAPI console_event(DWORD)
{
    port_quit = 1;
    return TRUE;
}

/* The console the server writes to: the one it was started from, else its own. */
static void server_console(void)
{
    if (!AttachConsole(ATTACH_PARENT_PROCESS))
        AllocConsole();
    SetConsoleTitleA("Call of Duty: Finest Hour dedicated server");
    SetConsoleCtrlHandler(console_event, TRUE);
}
#endif

int WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR cmd, int)
{
    port_crash_handler_install();
#ifdef CODFH_DEDICATED
    server_console();
#endif
    port_config_load();
    port_cli_parse(cmd);
    timeBeginPeriod(1);
    create_window(inst);
    port_pump_messages();
    plog("starting the game");
    int r = main();
    plog("main returned %d", r);
    return r;
}
