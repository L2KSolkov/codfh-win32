// The debug tools' performance view (CODFH_DRAW_TRIGGERS): the game's own profiler sections
// (the begin and end marks the frame puts around each system, sub_16D7F0 and sub_16D850 in
// unit_16D220, named and coloured in its table dword_42A598, unit_184CF0), timed again with the
// high-resolution counter (the game's are GetTickCount's whole milliseconds), kept for the last
// 240 frames and drawn as a graph with a table under it (trigtools.cpp's Engine, Performance).

#ifdef CODFH_DRAW_TRIGGERS

#include <xtl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/debugmenu.h"
#include "../../third_party/imgui/imgui.h"

#define TRIGPERF_SECTIONS 49
#define TRIGPERF_FRAMES 240

static LARGE_INTEGER s_aStart[TRIGPERF_SECTIONS];
static RwInt32 s_anDepth[TRIGPERF_SECTIONS];
static double s_adNow[TRIGPERF_SECTIONS];                      // this frame's, so far (ms)
static float s_aafHistory[TRIGPERF_SECTIONS][TRIGPERF_FRAMES];  // the last frames' (ms)
static RwInt32 s_nAt, s_nFrames;
static double s_dTicksPerMs;
static RwBool s_abShown[TRIGPERF_SECTIONS];
static RwBool s_bShownSet, s_bPaused;
static RwReal s_fScaleMs = 20.0f;

static double TicksPerMs()
{
    if (s_dTicksPerMs == 0.0)
    {
        LARGE_INTEGER f;

        QueryPerformanceFrequency(&f);
        s_dTicksPerMs = f.QuadPart / 1000.0;
    }
    return s_dTicksPerMs;
}

// (from sub_16D7F0: a section begins; nested begins of one section count once)
void TrigPerfBegin(RwInt32 nSection)
{
    if (nSection < 0 || nSection >= TRIGPERF_SECTIONS)
        return;
    if (s_anDepth[nSection]++ == 0)
        QueryPerformanceCounter(&s_aStart[nSection]);
}

// (from sub_16D850: it ends)
void TrigPerfEnd(RwInt32 nSection)
{
    LARGE_INTEGER now;

    if (nSection < 0 || nSection >= TRIGPERF_SECTIONS || s_anDepth[nSection] <= 0)
        return;
    if (--s_anDepth[nSection] == 0)
    {
        QueryPerformanceCounter(&now);
        s_adNow[nSection] += (now.QuadPart - s_aStart[nSection].QuadPart) / TicksPerMs();
    }
}

// (from sub_16D740: the frame's end) This frame's into the history.
void TrigPerfFrame()
{
    RwInt32 i;

    if (!s_bPaused)
    {
        for (i = 0; i < TRIGPERF_SECTIONS; i++)
            s_aafHistory[i][s_nAt] = (float)s_adNow[i];
        s_nAt = (s_nAt + 1) % TRIGPERF_FRAMES;
        if (s_nFrames < TRIGPERF_FRAMES)
            s_nFrames++;
    }
    for (i = 0; i < TRIGPERF_SECTIONS; i++)
        s_adNow[i] = 0.0;
}

// A section's name from the game's table, its trailing spaces cut.
static void SectionName(RwInt32 i, RwChar *psz, RwInt32 n)
{
    RwInt32 k;

    strncpy(psz, dword_42A598[i].unk_04, n - 1);
    psz[n - 1] = 0;
    for (k = (RwInt32)strlen(psz); k > 0 && psz[k - 1] == ' '; k--)
        psz[k - 1] = 0;
}

// Its colour from the table (0xBBGGRR), brightened so dark ones read on the graph.
static ImU32 SectionColour(RwInt32 i)
{
    RwUInt32 c = (RwUInt32)dword_42A598[i].unk_3C;
    RwUInt32 r = c & 0xFF, g = (c >> 8) & 0xFF, b = (c >> 16) & 0xFF;

    if (r + g + b < 200)
    {
        r = r / 2 + 100;
        g = g / 2 + 100;
        b = b / 2 + 100;
    }
    return IM_COL32(r, g, b, 255);
}

static void Stats(RwInt32 i, float *pfLast, float *pfAvg, float *pfMax)
{
    RwInt32 k;
    float fSum = 0.0f, fMax = 0.0f;

    *pfLast = s_nFrames ? s_aafHistory[i][(s_nAt + TRIGPERF_FRAMES - 1) % TRIGPERF_FRAMES] : 0.0f;
    for (k = 0; k < s_nFrames; k++)
    {
        float f = s_aafHistory[i][k];

        fSum += f;
        if (f > fMax)
            fMax = f;
    }
    *pfAvg = s_nFrames ? fSum / s_nFrames : 0.0f;
    *pfMax = fMax;
}

// The Engine group's Performance tab.
void TabPerformance()
{
    RwInt32 i, k;
    RwChar szName[32];

    if (!s_bShownSet)
    {
        // (shown at first: the frame's totals and the logic's systems, the table's groups 0 and 1)
        for (i = 0; i < TRIGPERF_SECTIONS; i++)
            s_abShown[i] = dword_42A598[i].unk_00 == 1 || i == 0 || i == 1;
        s_bShownSet = TRUE;
    }
    {
        bool b = s_bPaused != 0;

        if (ImGui::Checkbox("pause", &b))
            s_bPaused = b;
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(200.0f);
    ImGui::SliderFloat("graph top (ms)", &s_fScaleMs, 1.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
    ImGui::TextDisabled("(the game's own profiler sections, timed with the high-resolution counter, the last %d "
                        "frames; tick a row to graph it)", TRIGPERF_FRAMES);

    // the graph: one line a shown section, the 16.7 and 33.3 ms marks
    {
        ImVec2 at = ImGui::GetCursorScreenPos();
        ImVec2 size(ImGui::GetContentRegionAvail().x, 180.0f);
        ImDrawList *pDraw = ImGui::GetWindowDrawList();
        float fMarks[2] = { 16.667f, 33.333f };

        pDraw->AddRectFilled(at, ImVec2(at.x + size.x, at.y + size.y), IM_COL32(20, 20, 24, 255));
        for (k = 0; k < 2; k++)
        {
            float y = at.y + size.y * (1.0f - fMarks[k] / s_fScaleMs);

            if (fMarks[k] < s_fScaleMs)
                pDraw->AddLine(ImVec2(at.x, y), ImVec2(at.x + size.x, y), IM_COL32(90, 200, 90, 90));
        }
        for (i = 0; i < TRIGPERF_SECTIONS && s_nFrames > 1; i++)
        {
            ImVec2 prev;
            ImU32 col = SectionColour(i);

            if (!s_abShown[i])
                continue;
            for (k = 0; k < s_nFrames; k++)
            {
                // (oldest on the left)
                RwInt32 idx = (s_nAt - s_nFrames + k + TRIGPERF_FRAMES) % TRIGPERF_FRAMES;
                float f = s_aafHistory[i][idx] / s_fScaleMs;
                ImVec2 p(at.x + size.x * k / (TRIGPERF_FRAMES - 1), at.y + size.y * (1.0f - (f > 1.0f ? 1.0f : f)));

                if (k)
                    pDraw->AddLine(prev, p, col, 1.5f);
                prev = p;
            }
        }
        ImGui::Dummy(size);
    }

    if (ImGui::BeginTable("perf", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 300.0f)))
    {
        static const RwChar *const s_apszGroup[8] = { "frame", "logic", "render", "atoms", "entities", "?",
                                                      "audio, loading", "?" };
        RwInt32 nGroup = -2;

        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("graph", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("section");
        ImGui::TableSetupColumn("ms");
        ImGui::TableSetupColumn("average");
        ImGui::TableSetupColumn("most");
        ImGui::TableHeadersRow();
        // (by the table's groups, in its order within each)
        for (k = 0; k < 8; k++)
        {
            for (i = 0; i < TRIGPERF_SECTIONS; i++)
            {
                float fLast, fAvg, fMax;
                bool b;

                if (dword_42A598[i].unk_00 != k)
                    continue;
                if (nGroup != k)
                {
                    nGroup = k;
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TableNextColumn();
                    ImGui::TextDisabled("%s", s_apszGroup[k]);
                }
                Stats(i, &fLast, &fAvg, &fMax);
                SectionName(i, szName, sizeof(szName));
                ImGui::PushID(i);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                b = s_abShown[i] != 0;
                if (ImGui::Checkbox("##shown", &b))
                    s_abShown[i] = b;
                ImGui::SameLine();
                ImGui::ColorButton("##c", ImGui::ColorConvertU32ToFloat4(SectionColour(i)), ImGuiColorEditFlags_NoTooltip,
                                   ImVec2(12.0f, 12.0f));
                ImGui::TableNextColumn();
                ImGui::TextUnformatted(szName);
                ImGui::TableNextColumn();
                if (fMax > 0.0f)
                    ImGui::Text("%.2f", fLast);
                else
                    ImGui::TextDisabled("-");
                ImGui::TableNextColumn();
                if (fMax > 0.0f)
                    ImGui::Text("%.2f", fAvg);
                else
                    ImGui::TextDisabled("not timed");
                ImGui::TableNextColumn();
                if (fMax > 0.0f)
                    ImGui::Text("%.2f", fMax);
                ImGui::PopID();
            }
        }
        ImGui::EndTable();
    }
}

#endif // CODFH_DRAW_TRIGGERS
