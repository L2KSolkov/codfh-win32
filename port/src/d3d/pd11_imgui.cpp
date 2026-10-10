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
#endif
#ifdef CODFH_DRAW_TRIGGERS
/* the game's debug tools (port/src/debug/trigtools.cpp) */
extern "C" void port_debug_tools_window(void);
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

static void port_window(int back_w, int back_h)
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 0), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("CODFH port (F1)"))
    {
        ImGui::End();
        return;
    }
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
        check("wireframe", &port_render_debug.wireframe);
        ImGui::SameLine();
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
    }
    if (ImGui::CollapsingHeader("Input"))
        ImGui::SliderFloat("mouse sensitivity", &port_config.mouseSensitivity, 0.1f, 5.0f, "%.2f");
    check("ImGui demo", &show_demo);
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
