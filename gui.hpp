#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <functional>

struct SelectableFile {
    std::filesystem::path path;
    bool selected;
};

struct AppState {
    std::filesystem::path outputFolder;
    std::vector<SelectableFile> files;
    char outputFilename[256] = "offsets.h";
    bool folderSelected = false;
    std::string statusMessage;
    float statusTimer = 0.0f;
    bool showStatus = false;

    // The chosen output .h file path (set via Browse in UI)
    std::filesystem::path outputFilePath;
};

namespace GUI {
    void init();
    void shutdown();
    void render(AppState& state, std::function<void()> onGenerate);
    void setDarkPurpleTheme();
    bool folderPicker(std::filesystem::path& outPath);
    bool saveFilePicker(std::filesystem::path& outPath, const char* filter = "Header Files (*.h)\0*.h\0All Files\0*.*\0");
}