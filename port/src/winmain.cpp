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
static volatile LONG port_menu_mouse_button_down, port_menu_mouse_button_dirty;
static volatile LONG port_menu_cursor_visible;

/* Translate the visible cursor into the game's 640x480 menu canvas and report RenderWare
   mouse-move/button state changes for the SP front-end. */
static POINT port_menu_last_cursor;
static int port_menu_have_cursor;

extern "C" void port_menu_mouse_reset(void)
{
    InterlockedExchange(&port_menu_cursor_visible, 1);
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    port_menu_have_cursor = 0;
    InterlockedExchange(&port_menu_mouse_button_down, 0);
    InterlockedExchange(&port_menu_mouse_button_dirty, 0);
}

extern "C" void port_menu_mouse_hide(void)
{
    InterlockedExchange(&port_menu_cursor_visible, 0);
    SetCursor(NULL);
    InterlockedExchange(&port_menu_mouse_button_down, 0);
    InterlockedExchange(&port_menu_mouse_button_dirty, 0);
    port_menu_have_cursor = 0;
}

extern "C" int port_menu_mouse_poll(int *x, int *y, int *buttonState)
{
    if (!port_hwnd || GetForegroundWindow() != (HWND)port_hwnd)
    {
        port_menu_have_cursor = 0;
        InterlockedExchange(&port_menu_mouse_button_down, 0);
        InterlockedExchange(&port_menu_mouse_button_dirty, 0);
        return 0;
    }

    int input = 0;
    POINT cursor;
    if (GetCursorPos(&cursor) && ScreenToClient((HWND)port_hwnd, &cursor))
    {
        RECT client;
        GetClientRect((HWND)port_hwnd, &client);
        int width = client.right - client.left;
        int height = client.bottom - client.top;
        int left = 0, top = 0, drawWidth = width, drawHeight = height;
        if (!port_config.widescreen && width > 0 && height > 0)
        {
            if (width * 480 > height * 640)
            {
                drawWidth = height * 640 / 480;
                left = (width - drawWidth) / 2;
            }
            else
            {
                drawHeight = width * 480 / 640;
                top = (height - drawHeight) / 2;
            }
        }
        if (drawWidth > 0 && drawHeight > 0)
        {
            int frameX = (cursor.x - left) * 640 / drawWidth;
            int frameY = (cursor.y - top) * 480 / drawHeight;
            if (!port_menu_have_cursor || cursor.x != port_menu_last_cursor.x || cursor.y != port_menu_last_cursor.y)
                input |= PORT_MENU_MOUSE_MOVE;
            *x = frameX;
            *y = frameY;
            port_menu_last_cursor = cursor;
            port_menu_have_cursor = 1;
        }
    }
    if (InterlockedExchange(&port_menu_mouse_button_dirty, 0))
        input |= PORT_MENU_MOUSE_BUTTON;
    *buttonState = InterlockedCompareExchange(&port_menu_mouse_button_down, 0, 0) != 0;
    return input;
}

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

static LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
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
        InterlockedExchange(&port_menu_mouse_button_down, 1);
        InterlockedExchange(&port_menu_mouse_button_dirty, 1);
        break;
    case WM_LBUTTONUP:
        InterlockedExchange(&port_menu_mouse_button_down, 0);
        InterlockedExchange(&port_menu_mouse_button_dirty, 1);
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
    case WM_SETCURSOR:
        if (LOWORD(lp) == HTCLIENT && !InterlockedCompareExchange(&port_menu_cursor_visible, 0, 0))
        {
            SetCursor(NULL);
            return TRUE;
        }
        break;
    case WM_SYSKEYDOWN:
        /* Alt+Enter: windowed and fullscreen (a borderless window over the monitor) */
        if (wp == VK_RETURN && (lp & (1 << 29)) && !(lp & (1 << 30)))
        {
            set_fullscreen(hwnd, !fullscreen);
            return 0;
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
    if (!port_config.windowed)
        set_fullscreen(hwnd, 1);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    port_hwnd = hwnd;
    RAWINPUTDEVICE rid = {0x01, 0x02, 0, hwnd};    /* the mouse */
    RegisterRawInputDevices(&rid, 1, sizeof(rid));
}

extern "C" void port_cli_parse(const char *cmd);

int WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR cmd, int)
{
    port_crash_handler_install();
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
