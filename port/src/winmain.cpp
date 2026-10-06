/*
 * The port's entry point (docs/WIN32_PORT.md W0.3, section 6.1): the configuration, the window,
 * the timer resolution, then the game's own main (unit_19CD50.cpp), which the Xbox's
 * mainXapiStartup calls. Window messages are pumped from the device's Present (the bridge), once
 * a frame, the Xbox's frame boundary.
 */
#include <xtl.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>

#include "port.h"
#include "d3d/pdev.h"  /* (also the overlay's entry points) */

extern "C" void port_audio_shutdown(void);

int main();
extern "C" void port_crash_handler_install(void);

/* The mouse's movement since the controllers last read it (xpal_sys.cpp turns it into the right
   stick). */
volatile LONG port_mouse_dx, port_mouse_dy;

static void confine_cursor(HWND hwnd, int on)
{
    if (on)
    {
        RECT r;
        GetClientRect(hwnd, &r);
        MapWindowPoints(hwnd, NULL, (POINT *)&r, 2);
        ClipCursor(&r);
    }
    else
        ClipCursor(NULL);
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

/* The mouse in the menus (menumouse.cpp): the cursor's position, clicks, backs and the wheel. */
extern "C" volatile LONG port_menu_mouse_x, port_menu_mouse_y, port_menu_mouse_moved, port_menu_mouse_pressed;
extern "C" volatile LONG port_menu_mouse_clicks, port_menu_mouse_backs, port_menu_mouse_wheel;
extern "C" int port_in_menus(void);

static int menu_mouse(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (!port_in_menus())
        return 0;
    switch (msg)
    {
    case WM_MOUSEMOVE:
        InterlockedExchange(&port_menu_mouse_x, (SHORT)LOWORD(lp));
        InterlockedExchange(&port_menu_mouse_y, (SHORT)HIWORD(lp));
        InterlockedExchange(&port_menu_mouse_moved, 1);
        return 0;
    case WM_LBUTTONDOWN:
        /* (the click's own position first: the item under it takes the focus before A) */
        InterlockedExchange(&port_menu_mouse_x, (SHORT)LOWORD(lp));
        InterlockedExchange(&port_menu_mouse_y, (SHORT)HIWORD(lp));
        InterlockedExchange(&port_menu_mouse_moved, 1);
        InterlockedIncrement(&port_menu_mouse_pressed);
        return 1;   /* (no capture for mouse look in the menus) */
    case WM_RBUTTONDOWN:
        InterlockedIncrement(&port_menu_mouse_backs);
        return 1;
    case WM_MOUSEWHEEL:
        InterlockedExchangeAdd(&port_menu_mouse_wheel, (SHORT)HIWORD(wp) / WHEEL_DELTA);
        return 1;
    case WM_SETCURSOR:
        if (LOWORD(lp) == HTCLIENT)
        {
            /* an arrow over the menus, and the cursor free */
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            ClipCursor(NULL);
            return 2;
        }
        return 0;
    }
    return 0;
}

static LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    {
        int r = menu_mouse(hwnd, msg, wp, lp);
        if (r == 2)
            return TRUE;
        if (r == 1)
            return 0;
    }
#ifdef CODFH_IMGUI
    /* F1 shows and hides the overlay; while it is shown the cursor is free and ImGui has the
       window's messages first */
    if (msg == WM_KEYDOWN && wp == VK_F1 && !(lp & (1 << 30)))
    {
        port_imgui_toggle();
        confine_cursor(hwnd, 0);
        return 0;
    }
    if (port_imgui_wndproc(hwnd, msg, wp, lp))
        return TRUE;
    if (msg == WM_SETCURSOR && LOWORD(lp) == HTCLIENT && port_imgui_visible())
    {
        SetCursor(LoadCursor(NULL, IDC_ARROW));
        return TRUE;
    }
    if (msg == WM_LBUTTONDOWN && port_imgui_visible())
        return 0;   /* (the click is the overlay's: the cursor stays free) */
#endif
    switch (msg)
    {
    case WM_INPUT:
    {
        RAWINPUT ri;
        UINT size = sizeof(ri);
        if (GetRawInputData((HRAWINPUT)lp, RID_INPUT, &ri, &size, sizeof(RAWINPUTHEADER)) != (UINT)-1 &&
            ri.header.dwType == RIM_TYPEMOUSE && !(ri.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE))
        {
            InterlockedExchangeAdd(&port_mouse_dx, ri.data.mouse.lLastX);
            InterlockedExchangeAdd(&port_mouse_dy, ri.data.mouse.lLastY);
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
    RAWINPUTDEVICE rid = {0x01, 0x02, 0, hwnd};    /* the mouse */
    RegisterRawInputDevices(&rid, 1, sizeof(rid));
#endif
}

extern "C" void port_cli_parse(const char *cmd);

/* Run on the discrete GPU where a machine has two: NVIDIA's and AMD's drivers read these exports
   (Optimus, PowerXpress / switchable graphics). */
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 1;
extern "C" __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

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
    plog_to_console();
}
#else
/* The log window ([debug] console): the port's log, the game's debug prints and its printf
   output, in a console of its own. Its close button is off (closing a console ends its process). */
static void log_console(void)
{
    if (!port_config.console)
        return;
    /* (a console of its own, not one inherited from whatever started the game) */
    FreeConsole();
    if (!AllocConsole())
        return;
    SetConsoleTitleA("Call of Duty: Finest Hour log");
    HMENU menu = GetSystemMenu(GetConsoleWindow(), FALSE);
    if (menu)
        DeleteMenu(menu, SC_CLOSE, MF_BYCOMMAND);
    /* (no quick edit: a click in it would select text and stop every write to it, the game
       with them) */
    HANDLE in = CreateFileA("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                            OPEN_EXISTING, 0, NULL);
    if (in != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;
        GetConsoleMode(in, &mode);
        SetConsoleMode(in, (mode & ~ENABLE_QUICK_EDIT_MODE) | ENABLE_EXTENDED_FLAGS);
        CloseHandle(in);
    }
    FILE *f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "w", stderr);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    plog_to_console();
}
#endif

int WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR cmd, int)
{
    port_crash_handler_install();
#ifdef CODFH_DEDICATED
    server_console();
#endif
    port_config_load();
#ifndef CODFH_DEDICATED
    log_console();
#endif
    port_cli_parse(cmd);
    timeBeginPeriod(1);
    create_window(inst);
    port_pump_messages();
    plog("starting the game");
    int r = main();
    plog("main returned %d", r);
    return r;
}
