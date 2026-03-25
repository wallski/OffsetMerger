#include "gui.hpp"
#include "config.hpp"
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include <Windows.h>
#include <ShlObj.h>
#include <Commdlg.h>
#include "../ext/imgui/imgui_internal.h"

// ------------------------------------------------------------------ theme ---
void GUI::setDarkPurpleTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* c = style.Colors;

    // palette
    // bg0  #0B0812   bg1  #0F0B1A   bg2  #120E1F
    // bdr  #1E1530   acc0 #1A1030   acc1 #3A2070
    // acc2 #4A20A0   hi   #C4A8F0   txt  #C0A8E8
    // dim  #6B5A8A   dim2 #4A3870

    c[ImGuiCol_Text] = ImVec4(0.753f, 0.659f, 0.910f, 1.00f); // #C0A8E8
    c[ImGuiCol_TextDisabled] = ImVec4(0.290f, 0.220f, 0.439f, 1.00f); // #4A3870
    c[ImGuiCol_WindowBg] = ImVec4(0.043f, 0.031f, 0.071f, 1.00f); // #0B0812
    c[ImGuiCol_ChildBg] = ImVec4(0.059f, 0.043f, 0.102f, 1.00f); // #0F0B1A
    c[ImGuiCol_PopupBg] = ImVec4(0.071f, 0.051f, 0.118f, 1.00f); // #12_D1E
    c[ImGuiCol_Border] = ImVec4(0.118f, 0.082f, 0.188f, 1.00f); // #1E1530
    c[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    c[ImGuiCol_FrameBg] = ImVec4(0.071f, 0.051f, 0.122f, 1.00f); // #120E1F
    c[ImGuiCol_FrameBgHovered] = ImVec4(0.102f, 0.071f, 0.165f, 1.00f);
    c[ImGuiCol_FrameBgActive] = ImVec4(0.137f, 0.094f, 0.220f, 1.00f);
    c[ImGuiCol_TitleBg] = ImVec4(0.059f, 0.043f, 0.102f, 1.00f);
    c[ImGuiCol_TitleBgActive] = ImVec4(0.059f, 0.043f, 0.102f, 1.00f);
    c[ImGuiCol_TitleBgCollapsed] = ImVec4(0.043f, 0.031f, 0.071f, 1.00f);
    c[ImGuiCol_MenuBarBg] = ImVec4(0.059f, 0.043f, 0.102f, 1.00f);
    c[ImGuiCol_ScrollbarBg] = ImVec4(0.043f, 0.031f, 0.071f, 1.00f);
    c[ImGuiCol_ScrollbarGrab] = ImVec4(0.227f, 0.125f, 0.439f, 1.00f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.290f, 0.165f, 0.533f, 1.00f);
    c[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.353f, 0.188f, 0.659f, 1.00f);
    c[ImGuiCol_CheckMark] = ImVec4(0.769f, 0.659f, 0.941f, 1.00f); // #C4A8F0
    c[ImGuiCol_SliderGrab] = ImVec4(0.353f, 0.188f, 0.659f, 1.00f);
    c[ImGuiCol_SliderGrabActive] = ImVec4(0.451f, 0.251f, 0.800f, 1.00f);
    c[ImGuiCol_Button] = ImVec4(0.118f, 0.082f, 0.196f, 1.00f); // #1E1532
    c[ImGuiCol_ButtonHovered] = ImVec4(0.180f, 0.118f, 0.314f, 1.00f);
    c[ImGuiCol_ButtonActive] = ImVec4(0.227f, 0.145f, 0.400f, 1.00f);
    c[ImGuiCol_Header] = ImVec4(0.227f, 0.125f, 0.439f, 1.00f);
    c[ImGuiCol_HeaderHovered] = ImVec4(0.290f, 0.165f, 0.533f, 1.00f);
    c[ImGuiCol_HeaderActive] = ImVec4(0.353f, 0.188f, 0.659f, 1.00f);
    c[ImGuiCol_Separator] = ImVec4(0.118f, 0.082f, 0.188f, 1.00f);
    c[ImGuiCol_SeparatorHovered] = ImVec4(0.227f, 0.125f, 0.439f, 0.78f);
    c[ImGuiCol_SeparatorActive] = ImVec4(0.353f, 0.188f, 0.659f, 1.00f);
    c[ImGuiCol_ResizeGrip] = ImVec4(0.227f, 0.125f, 0.439f, 0.20f);
    c[ImGuiCol_ResizeGripHovered] = ImVec4(0.353f, 0.188f, 0.659f, 0.67f);
    c[ImGuiCol_ResizeGripActive] = ImVec4(0.451f, 0.251f, 0.800f, 0.95f);
    c[ImGuiCol_Tab] = ImVec4(0.071f, 0.051f, 0.122f, 1.00f);
    c[ImGuiCol_TabHovered] = ImVec4(0.290f, 0.165f, 0.533f, 1.00f);
    c[ImGuiCol_TabActive] = ImVec4(0.227f, 0.125f, 0.439f, 1.00f);
    c[ImGuiCol_TabUnfocused] = ImVec4(0.059f, 0.043f, 0.102f, 1.00f);
    c[ImGuiCol_TabUnfocusedActive] = ImVec4(0.165f, 0.094f, 0.314f, 1.00f);
    c[ImGuiCol_TextSelectedBg] = ImVec4(0.353f, 0.188f, 0.659f, 0.35f);

    // shape
    style.WindowRounding = 10.0f;
    style.ChildRounding = 7.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.PopupRounding = 8.0f;

    style.WindowPadding = ImVec2(20, 18);
    style.FramePadding = ImVec2(10, 7);
    style.ItemSpacing = ImVec2(10, 10);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.ScrollbarSize = 8.0f;
    style.GrabMinSize = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
}

// --------------------------------------------------------------- pickers ---
bool GUI::folderPicker(std::filesystem::path& outPath) {
    BROWSEINFOA bi = {};
    bi.lpszTitle = "Select folder containing .hpp files";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (!pidl) return false;
    char path[MAX_PATH];
    bool ok = SHGetPathFromIDListA(pidl, path);
    if (ok) outPath = path;
    IMalloc* m = nullptr;
    if (SUCCEEDED(SHGetMalloc(&m))) { m->Free(pidl); m->Release(); }
    return ok;
}

bool GUI::saveFilePicker(std::filesystem::path& outPath, const char* filter) {
    char filename[MAX_PATH] = "";
    if (!outPath.empty())
        strncpy_s(filename, outPath.string().c_str(), sizeof(filename) - 1);
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "h";
    if (GetSaveFileNameA(&ofn)) { outPath = filename; return true; }
    return false;
}

// ----------------------------------------------------------------- render ---
// accent colors used inline
static const ImVec4 kAccent = ImVec4(0.769f, 0.659f, 0.941f, 1.00f); // #C4A8F0  labels
static const ImVec4 kDim = ImVec4(0.420f, 0.353f, 0.549f, 1.00f); // #6B5A8A  hint text
static const ImVec4 kDimmer = ImVec4(0.290f, 0.220f, 0.400f, 1.00f); // #4A3870  very dim
static const ImVec4 kText = ImVec4(0.753f, 0.659f, 0.910f, 1.00f); // #C0A8E8  normal
static const ImVec4 kWarn = ImVec4(0.780f, 0.380f, 0.380f, 1.00f);
static const ImVec4 kOk = ImVec4(0.353f, 0.667f, 0.502f, 1.00f);

static void Label(const char* text) {
    ImGui::PushStyleColor(ImGuiCol_Text, kDimmer);
    ImGui::SetWindowFontScale(0.82f);
    ImGui::Text(text);
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleColor();
    ImGui::Spacing();
}

static void Gap() {
    ImGui::Spacing();
    ImGui::Spacing();
}

void GUI::render(AppState& state, std::function<void()> onGenerate) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("##root", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse);
        //ImGuiWindowFlags_NoBringToDisplayOnFocus

    // ---- header bar (custom title bar) ----
    {
        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImVec2 wpos = ImGui::GetWindowPos();
        float  barH = 38.0f;
        float  ww = io.DisplaySize.x;

        // bar background
        dl->AddRectFilled(
            wpos,
            ImVec2(wpos.x + ww, wpos.y + barH),
            IM_COL32(15, 11, 26, 255), 10.0f, ImDrawFlags_RoundCornersTop);
        // bottom edge line
        dl->AddLine(
            ImVec2(wpos.x, wpos.y + barH),
            ImVec2(wpos.x + ww, wpos.y + barH),
            IM_COL32(30, 21, 48, 255));

        // icon square
        dl->AddRectFilled(
            ImVec2(wpos.x + 14, wpos.y + 12),
            ImVec2(wpos.x + 26, wpos.y + 26),
            IM_COL32(58, 32, 112, 255), 3.0f);

        // title text  — rendered as ImGui text inside a dummy cursor-positioned region
        ImGui::SetCursorPos(ImVec2(34, 10));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.420f, 0.353f, 0.549f, 1.00f));
        ImGui::SetWindowFontScale(0.88f);
        ImGui::Text("OFFSET MERGER");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopStyleColor();

        // invisible drag region (whole bar except close btn)
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::InvisibleButton("##drag", ImVec2(ww - 48, barH));
        if (ImGui::IsItemActive()) {
            // drag-to-move the window
            POINT pt; GetCursorPos(&pt);
            static POINT last{};
            if (ImGui::IsItemActivated()) last = pt;
            HWND hw = (HWND)io.BackendPlatformUserData;
            if (hw) {
                RECT wr; GetWindowRect(hw, &wr);
                SetWindowPos(hw, nullptr,
                    wr.left + (pt.x - last.x),
                    wr.top + (pt.y - last.y),
                    0, 0, SWP_NOSIZE | SWP_NOZORDER);
            }
            last = pt;
        }

        // close button
        ImGui::SetCursorPos(ImVec2(ww - 38, 0));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.55f, 0.12f, 0.12f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.75f, 0.15f, 0.15f, 1.00f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.420f, 0.353f, 0.549f, 1.00f));
        if (ImGui::Button("x##close", ImVec2(38, barH)))
            PostQuitMessage(0);
        ImGui::PopStyleColor(4);

        // push content below title bar
        ImGui::SetCursorPos(ImVec2(0, barH + 4));
    }

    // ---- content area ----
    ImGui::SetCursorPos(ImVec2(20, 52));
    ImGui::BeginChild("##content", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);

    // SOURCE FOLDER
    Label("SOURCE FOLDER");
    {
        float bw = 80.0f;
        float sp = ImGui::GetStyle().ItemSpacing.x;
        float iw = ImGui::GetContentRegionAvail().x - bw - sp;

        char buf[512] = "";
        if (state.folderSelected)
            strncpy_s(buf, state.outputFolder.string().c_str(), sizeof(buf) - 1);

        ImGui::SetNextItemWidth(iw);
        ImGui::PushStyleColor(ImGuiCol_Text, kDim);
        ImGui::InputText("##fold", buf, sizeof(buf), ImGuiInputTextFlags_ReadOnly);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        if (ImGui::Button("Browse##f", ImVec2(bw, 0))) {
            std::filesystem::path p;
            if (folderPicker(p)) {
                state.outputFolder = p;
                state.folderSelected = true;
                std::vector<std::string> saved;
                Config::loadSelectedFiles(saved);
                state.files.clear();
                for (const auto& e : std::filesystem::directory_iterator(p)) {
                    if (!e.is_regular_file()) continue;
                    auto ext = e.path().extension().string();
                    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                    if (ext == ".hpp" || ext == ".h") {
                        SelectableFile sf;
                        sf.path = e.path();
                        std::string fn = e.path().filename().string();
                        sf.selected = std::find(saved.begin(), saved.end(), fn) != saved.end();
                        state.files.push_back(sf);
                    }
                }
                Config::saveLastPath(p);
            }
        }

        if (!state.folderSelected) {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Text, kWarn);
            ImGui::SetWindowFontScale(0.85f);
            ImGui::Text("  select a folder to get started");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::PopStyleColor();
        }
    }

    Gap();

    // FILES
    if (state.folderSelected) {
        if (!state.files.empty()) {
            char lbl[64];
            snprintf(lbl, sizeof(lbl), "FILES  (%zu)", state.files.size());
            Label(lbl);

            // file list card
            float listH = ImMin((float)state.files.size() * 34.0f + 2.0f, 180.0f);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.043f, 0.031f, 0.071f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.118f, 0.082f, 0.188f, 1.00f));
            ImGui::BeginChild("##files", ImVec2(0, listH), true);

            for (size_t i = 0; i < state.files.size(); i++) {
                bool prev = state.files[i].selected;

                // hover row highlight
                ImVec2 rmin = ImGui::GetCursorScreenPos();
                ImVec2 rmax = ImVec2(rmin.x + ImGui::GetContentRegionAvail().x,
                    rmin.y + 30.0f);
                if (ImGui::IsMouseHoveringRect(rmin, rmax))
                    ImGui::GetWindowDrawList()->AddRectFilled(
                        rmin, rmax, IM_COL32(58, 32, 112, 55), 4.0f);

                ImGui::PushStyleColor(ImGuiCol_Text,
                    state.files[i].selected ? kText : kDimmer);
                ImGui::Checkbox(
                    state.files[i].path.filename().string().c_str(),
                    &state.files[i].selected);
                ImGui::PopStyleColor();

                if (state.files[i].selected != prev) {
                    std::vector<std::string> sel;
                    for (const auto& f : state.files)
                        if (f.selected) sel.push_back(f.path.filename().string());
                    Config::saveSelectedFiles(sel);
                }
            }

            ImGui::EndChild();
            ImGui::PopStyleColor(2);

            // select all / none
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.071f, 0.051f, 0.122f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.118f, 0.082f, 0.188f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.180f, 0.118f, 0.314f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_Text, kDimmer);
            ImGui::SetWindowFontScale(0.85f);
            if (ImGui::Button("Select all", ImVec2(82, 0))) {
                for (auto& f : state.files) f.selected = true;
                std::vector<std::string> sel;
                for (const auto& f : state.files) sel.push_back(f.path.filename().string());
                Config::saveSelectedFiles(sel);
            }
            ImGui::SameLine();
            if (ImGui::Button("None", ImVec2(60, 0))) {
                for (auto& f : state.files) f.selected = false;
                Config::saveSelectedFiles({});
            }
            ImGui::SetWindowFontScale(1.0f);
            ImGui::PopStyleColor(4);
        }
        else {
            ImGui::PushStyleColor(ImGuiCol_Text, kWarn);
            ImGui::SetWindowFontScale(0.85f);
            ImGui::Text("  no .hpp / .h files found in that folder");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::PopStyleColor();
        }
    }

    Gap();

    // OUTPUT FILE
    Label("OUTPUT FILE");
    {
        float bw = 80.0f;
        float sp = ImGui::GetStyle().ItemSpacing.x;
        float iw = ImGui::GetContentRegionAvail().x - bw - sp;

        char buf[512] = "";
        if (!state.outputFilePath.empty())
            strncpy_s(buf, state.outputFilePath.string().c_str(), sizeof(buf) - 1);

        ImGui::SetNextItemWidth(iw);
        ImGui::PushStyleColor(ImGuiCol_Text, kDim);
        ImGui::InputText("##out", buf, sizeof(buf), ImGuiInputTextFlags_ReadOnly);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        if (ImGui::Button("Browse##o", ImVec2(bw, 0))) {
            std::filesystem::path p = state.outputFilePath;
            if (saveFilePicker(p)) {
                state.outputFilePath = p;
                Config::saveOutputFile(p);
            }
        }

        if (state.outputFilePath.empty()) {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Text, kWarn);
            ImGui::SetWindowFontScale(0.85f);
            ImGui::Text("  choose where to save the merged file");
            ImGui::SetWindowFontScale(1.0f);
            ImGui::PopStyleColor();
        }
    }

    Gap();

    // GENERATE BUTTON
    {
        bool hasSelection = false;
        for (const auto& f : state.files) if (f.selected) { hasSelection = true; break; }
        bool canGenerate = hasSelection && !state.outputFilePath.empty();

        float gw = ImGui::GetContentRegionAvail().x;

        if (canGenerate) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.290f, 0.125f, 0.627f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.353f, 0.157f, 0.745f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.227f, 0.094f, 0.510f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.910f, 0.847f, 1.000f, 1.00f));
            if (ImGui::Button("Generate##gen", ImVec2(gw, 42)))
                onGenerate();
            ImGui::PopStyleColor(4);
        }
        else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.059f, 0.043f, 0.102f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.059f, 0.043f, 0.102f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.059f, 0.043f, 0.102f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_Text, kDimmer);
            ImGui::Button("Generate##gen", ImVec2(gw, 42));
            ImGui::PopStyleColor(4);
        }
    }

    // STATUS
    if (state.showStatus && state.statusTimer > 0) {
        Gap();
        bool err = state.statusMessage.find("Error") != std::string::npos;
        ImGui::PushStyleColor(ImGuiCol_ChildBg, err
            ? ImVec4(0.180f, 0.047f, 0.047f, 1.00f)
            : ImVec4(0.039f, 0.137f, 0.078f, 1.00f));
        ImGui::BeginChild("##st", ImVec2(0, 34), false);
        ImGui::SetCursorPos(ImVec2(12, 8));
        ImGui::PushStyleColor(ImGuiCol_Text, err ? kWarn : kOk);
        ImGui::SetWindowFontScale(0.88f);
        ImGui::Text("%s", state.statusMessage.c_str());
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopStyleColor();
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }

    ImGui::EndChild();
    ImGui::End();
}

void GUI::init() {}
void GUI::shutdown() {}