/*
 * The port's Dear ImGui overlay (CODFH_IMGUI; the dedicated server and `portbuild.py --no-imgui`
 * build without it): drawn over the finished frame in the window's buffer, after the gamma pass,
 * so captures (the game's 640x480 frame) never contain it. F1 shows and hides it. It reads the
 * renderer's per-frame statistics and sets its debugging switches (pdev.h), and the mouse
 * sensitivity; while it is shown it has the mouse, and the keyboard when a field wants it.
 */
#ifdef CODFH_IMGUI

#include <d3d11.h>
#include <stdio.h>
#include <string.h>

#include "../port.h"
#include "pdev.h"
#include "pd11.h"

#include "../../third_party/imgui/imgui.h"
#include "../../third_party/imgui/backends/imgui_impl_dx11.h"
#include "../../third_party/imgui/backends/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#ifdef CODFH_DRAW_TRIGGERS
/* the game's debug tools (port/src/debug/trigtools.cpp) */
extern "C" void port_debug_tools_window(void);
extern "C" int port_log_astar;   /* (xpal_core.cpp: the A* search logs) */
#endif

static int ready, visible, show_demo;
/* the real time between presents (not ImGui's smoothed rate): the last 240 frames */
enum { FRAMES = 240 };
static float frame_ms[FRAMES];
static int frame_at, frame_count;
static LARGE_INTEGER last_present;
static char device_name[64] = "?";

extern "C" void pdev_imgui_init(void *hwnd, const char *device)
{
    if (ready || !pd11_dev)
        return;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;      /* (no imgui.ini beside the game) */
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(pd11_dev, pd11_ctx);
    strncpy(device_name, device ? device : "?", sizeof(device_name) - 1);
    ready = 1;
    /* (CODFH_OVERLAY=1: shown from the start) */
    char v[8];
    visible = GetEnvironmentVariableA("CODFH_OVERLAY", v, sizeof(v)) ? 1 : 0;
    plog("overlay: Dear ImGui %s (F1 shows it)", IMGUI_VERSION);
}

extern "C" void pdev_imgui_shutdown(void)
{
    if (!ready)
        return;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    ready = 0;
}

extern "C" int port_imgui_visible(void)
{
    return ready && visible;
}

extern "C" void port_imgui_toggle(void)
{
    visible = !visible;
}

/* The window's messages, ImGui's first while it is shown; nonzero: ImGui took it. */
extern "C" int port_imgui_wndproc(void *hwnd, unsigned msg, ULONG_PTR wp, LONG_PTR lp)
{
    if (!ready || !visible)
        return 0;
    return ImGui_ImplWin32_WndProcHandler((HWND)hwnd, msg, (WPARAM)wp, (LPARAM)lp) != 0;
}

/* The game's input left out while the overlay has it. */
extern "C" int port_imgui_wants_mouse(void)
{
    return ready && visible;
}

extern "C" int port_imgui_wants_keyboard(void)
{
    return ready && visible && ImGui::GetIO().WantCaptureKeyboard;
}

/* A checkbox over an int switch. */
static void check(const char *label, int *v)
{
    bool b = *v != 0;
    if (ImGui::Checkbox(label, &b))
        *v = b ? 1 : 0;
}

/* The key binding editor (xpal_sys.cpp's bindings): each action's keys as buttons (a click
   removes one), "+" to take the next key or mouse button (a mouse button only away from the
   overlay, so its own buttons can be clicked), reset to the default. */
extern "C" void port_key_name(int vk, char *out, int n);
extern "C" int port_input_cache;   /* (xpal_sys.cpp: the input polling caches, -1 not read yet) */
extern "C" int port_bind_count(void);
extern "C" const char *port_bind_action(int i);
extern "C" int port_bind_keys(int i, int *keys);
extern "C" void port_bind_set(int i, const int *keys, int n);
extern "C" void port_bind_reset(int i);

static const char *bind_label(const char *action)
{
    static const struct { const char *action, *label; } labels[] = {
        {"forward", "move forward"}, {"back", "move back"}, {"left", "strafe left"}, {"right", "strafe right"},
        {"look_up", "look up"}, {"look_down", "look down"}, {"look_left", "look left"}, {"look_right", "look right"},
        {"dpad_up", "d-pad up"}, {"dpad_down", "d-pad down"}, {"dpad_left", "d-pad left"}, {"dpad_right", "d-pad right"},
        {"start", "start (pause)"}, {"back_button", "back"}, {"left_stick", "left stick click (sprint)"},
        {"right_stick", "right stick click"}, {"a", "A (jump, use)"}, {"b", "B (crouch)"}, {"x", "X (reload)"},
        {"y", "Y (switch weapon)"}, {"black", "Black"}, {"white", "White"}, {"aim", "left trigger (aim)"},
        {"fire", "right trigger (fire)"},
    };
    for (size_t i = 0; i < sizeof(labels) / sizeof(labels[0]); i++)
        if (!strcmp(labels[i].action, action))
            return labels[i].label;
    return action;
}

static void key_bindings(void)
{
    static int capturing = -1, released;
    int n = port_bind_count();
    if (capturing >= 0)
    {
        /* (every key up first, then the first one down) */
        int down = 0, any = 0;
        for (int vk = 1; vk < 255 && !down; vk++)
        {
            if (vk == VK_SHIFT || vk == VK_CONTROL || vk == VK_MENU)
                continue;   /* (their left and right keys are reported too) */
            if (!(GetAsyncKeyState(vk) & 0x8000))
                continue;
            any = 1;
            int mouse = vk == VK_LBUTTON || vk == VK_RBUTTON || vk == VK_MBUTTON;
            if (released && (!mouse || !ImGui::GetIO().WantCaptureMouse))
                down = vk;
        }
        if (!any)
            released = 1;
        if (down)
        {
            int keys[4], k = port_bind_keys(capturing, keys);
            int dup = 0;
            for (int j = 0; j < k; j++)
                dup |= keys[j] == down;
            if (!dup && k < 4)
            {
                keys[k++] = down;
                port_bind_set(capturing, keys, k);
            }
            capturing = -1;
        }
    }
    ImGui::TextDisabled("(click a key to remove it; + then press a key, or click a mouse button away from this "
                        "window; saved to codfh.ini's [keys])");
    if (capturing >= 0)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.3f, 1.0f), "press a key for \"%s\"...",
                           bind_label(port_bind_action(capturing)));
        ImGui::SameLine();
        if (ImGui::SmallButton("cancel"))
            capturing = -1;
    }
    if (ImGui::BeginTable("binds", 3, ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableSetupColumn("action", ImGuiTableColumnFlags_WidthFixed, 150.0f);
        ImGui::TableSetupColumn("keys");
        ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 40.0f);
        for (int i = 0; i < n; i++)
        {
            int keys[4], k = port_bind_keys(i, keys);
            char name[16];
            ImGui::PushID(i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(bind_label(port_bind_action(i)));
            ImGui::TableNextColumn();
            for (int j = 0; j < k; j++)
            {
                port_key_name(keys[j], name, sizeof(name));
                ImGui::PushID(j);
                if (ImGui::SmallButton(name))
                {
                    for (int m = j; m < k - 1; m++)
                        keys[m] = keys[m + 1];
                    port_bind_set(i, keys, k - 1);
                    ImGui::PopID();
                    break;
                }
                ImGui::PopID();
                ImGui::SameLine();
            }
            if (k < 4 && ImGui::SmallButton("+"))
            {
                capturing = i;
                released = 0;
            }
            if (!k && capturing != i)
            {
                ImGui::SameLine();
                ImGui::TextDisabled("(unbound)");
            }
            ImGui::TableNextColumn();
            if (ImGui::SmallButton("reset"))
                port_bind_reset(i);
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    if (ImGui::SmallButton("reset all keys"))
        for (int i = 0; i < n; i++)
            port_bind_reset(i);
}

static void port_window(int back_w, int back_h)
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 0), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("CODFH port (F1)"))
    {
        ImGui::End();
        return;
    }
    /* (every text wraps at the window's edge: the hints are long) */
    ImGui::PushTextWrapPos(0.0f);
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    /* the frame times: this one, the average, the worst and the 1% low over the last 240 */
    int n = frame_count < FRAMES ? frame_count : FRAMES;
    float cur = frame_ms[(frame_at + FRAMES - 1) % FRAMES], sum = 0, worst = 0;
    float sorted[FRAMES];
    for (int i = 0; i < n; i++)
    {
        sum += frame_ms[i];
        if (frame_ms[i] > worst)
            worst = frame_ms[i];
        sorted[i] = frame_ms[i];
    }
    float avg = n ? sum / n : 0;
    /* (the 1% low: the frame rate of the slowest 1% of frames) */
    float p99 = 0;
    if (n)
    {
        int k = n - 1 - n / 100;
        for (int i = 0; i <= k && i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (sorted[j] < sorted[i])
                {
                    float t = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = t;
                }
        p99 = sorted[k];
    }
    ImGui::Text("%.1f fps   %.2f ms   frame %u", cur > 0 ? 1000.0f / cur : 0.0f, cur, port_frame);
    ImGui::Text("average %.1f fps (%.2f ms), worst %.1f ms, 1%% low %.1f fps", avg > 0 ? 1000.0f / avg : 0.0f, avg, worst,
                p99 > 0 ? 1000.0f / p99 : 0.0f);
    char label[48];
    _snprintf(label, sizeof(label), "frame ms (0-50, last %d)", n);
    label[sizeof(label) - 1] = 0;
    ImVec2 at = ImGui::GetCursorScreenPos();
    ImVec2 size(ImGui::GetContentRegionAvail().x, 70);
    ImGui::PlotLines("##ms", frame_ms, FRAMES, frame_at, label, 0.0f, 50.0f, size);
    /* the 60 fps line (16.7 ms) */
    float y = at.y + size.y * (1.0f - 16.667f / 50.0f);
    ImGui::GetWindowDrawList()->AddLine(ImVec2(at.x, y), ImVec2(at.x + size.x, y), IM_COL32(90, 200, 90, 160));
    int rw, rh;
    pdev_render_size(&rw, &rh);
    ImGui::Text("Direct3D 11 on %s, drawn at %dx%d in %dx%d", device_name, rw, rh, back_w, back_h);

    if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen))
    {
        const PortRenderStats &s = port_render_stats;
        ImGui::Text("%u draws, %u vertices", s.draws, s.vertices);
        ImGui::Text("untextured %u, dropped %u", s.untextured, s.dropped);
        ImGui::Text("shaders %.2f  convert %.2f  state %.2f  device %.2f ms", s.shaderMs, s.convertMs, s.stateMs,
                    s.deviceMs);
        ImGui::Text("vertex cache: %u draws reused, %u converted, %u changing; %.1f MB", s.cacheHits,
                    s.cacheConverted, s.cacheUncached, s.cacheMB);
        {
            /* (xdraw.cpp's modes: the 3D draws only, in one colour) */
            static const char *const modes[] = {"off", "hidden lines", "over the shaded scene", "through walls"};
            if (port_render_debug.wireframe < 0 || port_render_debug.wireframe > 3)
                port_render_debug.wireframe = 1;
            ImGui::SetNextItemWidth(200.0f);
            ImGui::Combo("wireframe", &port_render_debug.wireframe, modes, 4);
        }
        check("no depth", &port_render_debug.nodepth);
        check("no culling", &port_render_debug.nocull);
        ImGui::SameLine();
        check("no fog", &port_render_debug.nofog);
        check("fullbright", &port_render_debug.fullbright);
        ImGui::SameLine();
        check("lighting only", &port_render_debug.lightingOnly);
        check("no alpha test", &port_render_debug.noAlphaTest);
        ImGui::SameLine();
        check("no blending", &port_render_debug.noBlend);
        check("point filtering", &port_render_debug.pointFilter);
        ImGui::SameLine();
        check("no gamma", &port_render_debug.noGamma);
        check("hide particles", &port_render_debug.hideParticles);
        ImGui::SameLine();
        check("hide 2D (HUD, menus)", &port_render_debug.hide2D);
        {
            /* (no black bars: the 4:3 frame stretched to the window; kept in codfh.ini's [video] fill) */
            bool fill = port_config.fill != 0;
            if (ImGui::Checkbox("fill the window (no black bars, stretched)", &fill))
                port_config_set_fill(fill);
            if (port_config.widescreen)
            {
                ImGui::SameLine();
                ImGui::TextDisabled("(widescreen fills it already)");
            }
        }
    }
    if (ImGui::CollapsingHeader("Input"))
    {
        ImGui::SliderFloat("mouse sensitivity", &port_config.mouseSensitivity, 0.1f, 5.0f, "%.2f");
        {
            /* (xpal_sys.cpp: the empty controller ports asked once a second, the keys and the window
               in front read once every 4 ms; -1 until the first poll reads CODFH_INPUTCACHE) */
            int on = port_input_cache != 0;
            check("input polling caches (empty pads once a second, keys every 4 ms)", &on);
            port_input_cache = on;
        }
        if (ImGui::TreeNode("key bindings"))
        {
            key_bindings();
            ImGui::TreePop();
        }
    }
    if (ImGui::CollapsingHeader("Logs"))
        check("A* search logs (scheduler, path finder)", &port_log_astar);
    check("ImGui demo", &show_demo);
    ImGui::PopTextWrapPos();
    ImGui::End();
}

/* The overlay's frame, into the window's buffer (bound by the caller). */
extern "C" void pdev_imgui_frame(int back_w, int back_h)
{
    if (!ready)
        return;
    LARGE_INTEGER now, freq;
    QueryPerformanceCounter(&now);
    QueryPerformanceFrequency(&freq);
    if (last_present.QuadPart)
    {
        frame_ms[frame_at] = (float)((now.QuadPart - last_present.QuadPart) * 1000.0 / freq.QuadPart);
        frame_at = (frame_at + 1) % FRAMES;
        frame_count++;
    }
    last_present = now;
    if (!visible)
        return;
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    port_window(back_w, back_h);
#ifdef CODFH_DRAW_TRIGGERS
    port_debug_tools_window();
#endif
    if (show_demo)
        {
            bool open = true;
            ImGui::ShowDemoWindow(&open);
            show_demo = open;
        }
    ImGui::Render();
    D3D11_VIEWPORT vp = {0, 0, (float)back_w, (float)back_h, 0, 1};
    pd11_ctx->RSSetViewports(1, &vp);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

#endif
