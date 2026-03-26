
#include "gui.hpp"
#include "config.hpp"
#include "../ext/imgui/imgui.h"
#include <Windows.h>
#include <ShlObj.h>
#include <Commdlg.h>
#include <algorithm>

// ───────── THEME (keep your purple one if you want) ─────────
void GUI::setDarkPurpleTheme() {
    ImGuiStyle& s = ImGui::GetStyle();
    ImVec4* c = s.Colors;

    c[ImGuiCol_WindowBg] = { 0.05f, 0.03f, 0.08f, 1.f };
    c[ImGuiCol_ChildBg] = { 0.07f, 0.05f, 0.12f, 1.f };

    c[ImGuiCol_Text] = { 0.90f, 0.85f, 1.00f, 1.f };
    c[ImGuiCol_TextDisabled] = { 0.50f, 0.40f, 0.70f, 1.f };

    c[ImGuiCol_FrameBg] = { 0.10f, 0.06f, 0.18f, 1.f };
    c[ImGuiCol_FrameBgHovered] = { 0.15f, 0.10f, 0.28f, 1.f };

    c[ImGuiCol_Button] = { 0.45f, 0.20f, 0.90f, 1.f };
    c[ImGuiCol_ButtonHovered] = { 0.55f, 0.30f, 1.00f, 1.f };
    c[ImGuiCol_ButtonActive] = { 0.35f, 0.15f, 0.70f, 1.f };

    c[ImGuiCol_Header] = { 0.20f, 0.10f, 0.40f, 1.f };
    c[ImGuiCol_HeaderHovered] = { 0.40f, 0.20f, 0.80f, 1.f };
    c[ImGuiCol_HeaderActive] = { 0.30f, 0.15f, 0.60f, 1.f };

    c[ImGuiCol_CheckMark] = { 0.80f, 0.60f, 1.00f, 1.f };

    s.WindowRounding = 2.f;
    s.FrameRounding = 3.f;
    s.ChildRounding = 2.f;

    s.WindowPadding = { 12.f, 12.f };
    s.FramePadding = { 8.f, 6.f };
    s.ItemSpacing = { 8.f, 8.f };

    s.WindowBorderSize = 1.f;
    s.FrameBorderSize = 1.f;
}

// ───────── PICKERS ─────────
bool GUI::folderPicker(std::filesystem::path& outPath) {
    BROWSEINFOA bi = {};
    bi.lpszTitle = "Select folder";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (!pidl) return false;

    char path[MAX_PATH];
    if (SHGetPathFromIDListA(pidl, path)) {
        outPath = path;
        return true;
    }
    return false;
}

bool GUI::saveFilePicker(std::filesystem::path& outPath, const char* filter) {
    char filename[MAX_PATH] = "";
    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "h";

    if (GetSaveFileNameA(&ofn)) {
        outPath = filename;
        return true;
    }
    return false;
}

// ───────── RENDER ─────────
void GUI::render(AppState& state, std::function<void()> onGenerate) {
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowPos({ 0,0 });
    ImGui::SetNextWindowSize(io.DisplaySize);

    ImGui::Begin("##root", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove);

    float width = io.DisplaySize.x;

    // ───────── TITLEBAR ─────────
    float tb = 32.f;
    ImDrawList* dl = ImGui::GetWindowDrawList();

    dl->AddRectFilled({ 0,0 }, { width, tb }, IM_COL32(35, 25, 60, 255));
    dl->AddLine({ 0,tb }, { width,tb }, IM_COL32(90, 60, 150, 255));

    ImGui::SetCursorPos({ 0,0 });
    ImGui::InvisibleButton("drag", { width - 40.f, tb });

    if (ImGui::IsItemActive()) {
        POINT p; GetCursorPos(&p);
        static POINT last;
        if (ImGui::IsItemActivated()) last = p;

        HWND hwnd = FindWindowA("OffsetMerger", nullptr);
        RECT r; GetWindowRect(hwnd, &r);

        SetWindowPos(hwnd, nullptr,
            r.left + (p.x - last.x),
            r.top + (p.y - last.y),
            0, 0, SWP_NOSIZE | SWP_NOZORDER);

        last = p;
    }

    ImGui::SetCursorPos({ width - 40.f, 0 });
    if (ImGui::Button("X", { 40, tb }))
        PostQuitMessage(0);

    ImGui::SetCursorPosY(tb + 10);

    // ───────── TOP ROW (FIXED ALIGNMENT) ─────────
    float half = width * 0.5f;
    

 
    ImGui::Text("a2x's output Folder");
    ImGui::SameLine(half);
    ImGui::Text("Output File");

    char folderBuf[512] = "";
    if (state.folderSelected)
        strncpy_s(folderBuf, state.outputFolder.string().c_str(), sizeof(folderBuf) - 1);

    ImGui::SetNextItemWidth(half - 140);
    ImGui::InputText("##folder", folderBuf, sizeof(folderBuf), ImGuiInputTextFlags_ReadOnly);

    ImGui::SameLine();

    if (ImGui::Button("Browse##f")) {
        std::filesystem::path p;
        if (folderPicker(p)) {
            state.outputFolder = p;
            state.folderSelected = true;

            std::vector<std::string> saved;
            Config::loadSelectedFiles(saved);

            state.files.clear();
            for (auto& e : std::filesystem::directory_iterator(p)) {
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

    ImGui::SameLine(half);

    char outBuf[512] = "";
    if (!state.outputFilePath.empty())
        strncpy_s(outBuf, state.outputFilePath.string().c_str(), sizeof(outBuf) - 1);

    ImGui::SetNextItemWidth(half - 140);
    ImGui::InputText("##out", outBuf, sizeof(outBuf), ImGuiInputTextFlags_ReadOnly);

    ImGui::SameLine();

    if (ImGui::Button("Browse##o")) {
        std::filesystem::path p = state.outputFilePath;
        if (saveFilePicker(p)) {
            state.outputFilePath = p;
            Config::saveOutputFile(p);
        }
    }

    ImGui::Separator();

    // ───────── FILE TABLE ─────────
    if (state.folderSelected) {
        ImGui::Text("Files");

        if (ImGui::BeginTable("fileTable", 2,
            ImGuiTableFlags_Borders |
            ImGuiTableFlags_RowBg |
            ImGuiTableFlags_ScrollY,
            ImVec2(0, 300)))
        {
            ImGui::TableSetupColumn("Select", ImGuiTableColumnFlags_WidthFixed, 70.f);
            ImGui::TableSetupColumn("File Name");
            ImGui::TableHeadersRow();

            for (auto& f : state.files) {
                ImGui::TableNextRow();

                bool prev = f.selected;

                ImGui::TableSetColumnIndex(0);
                ImGui::Checkbox(("##" + f.path.string()).c_str(), &f.selected);

                ImGui::TableSetColumnIndex(1);
                ImGui::TextUnformatted(f.path.filename().string().c_str());

                if (prev != f.selected) {
                    std::vector<std::string> names;
                    for (auto& x : state.files)
                        if (x.selected)
                            names.push_back(x.path.filename().string());

                    Config::saveSelectedFiles(names);
                }
            }

            ImGui::EndTable();
        }

        if (ImGui::Button("Select All")) {
            for (auto& f : state.files) f.selected = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")) {
            for (auto& f : state.files) f.selected = false;
        }
    }

    ImGui::Separator();

    // ───────── GENERATE ─────────
    bool hasSel = false;
    for (auto& f : state.files)
        if (f.selected) hasSel = true;

    bool canGen = hasSel && !state.outputFilePath.empty();

    if (canGen)
        ImGui::PushStyleColor(ImGuiCol_Button, { 0.45f,0.25f,0.95f,1.f });

    if (ImGui::Button("Generate", ImVec2(-1, 32)) && canGen)
        onGenerate();

    if (canGen)
        ImGui::PopStyleColor();

    if (state.showStatus)
        ImGui::Text("%s", state.statusMessage.c_str());

    ImGui::End();
}

void GUI::init() {}
void GUI::shutdown() {}
