#include "config.hpp"
#include <fstream>
#include <Windows.h>
#include <ShlObj.h>

namespace Config {

    std::filesystem::path getConfigPath() {
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            std::filesystem::path configDir = std::filesystem::path(path) / "OffsetMergerGUI";
            std::filesystem::create_directories(configDir);
            return configDir / "config.ini";
        }
        return "config.ini";
    }

    static std::filesystem::path getSelectedFilesPath() {
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            std::filesystem::path configDir = std::filesystem::path(path) / "OffsetMergerGUI";
            std::filesystem::create_directories(configDir);
            return configDir / "selected.ini";
        }
        return "selected.ini";
    }

    static std::filesystem::path getOutputFilePath() {
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            std::filesystem::path configDir = std::filesystem::path(path) / "OffsetMergerGUI";
            std::filesystem::create_directories(configDir);
            return configDir / "outputfile.ini";
        }
        return "outputfile.ini";
    }

    bool loadLastPath(std::filesystem::path& outPath) {
        std::ifstream file(getConfigPath());
        if (!file.is_open()) return false;

        std::string line;
        if (std::getline(file, line)) {
            std::filesystem::path p(line);
            if (std::filesystem::exists(p)) {
                outPath = p;
                return true;
            }
        }
        return false;
    }

    bool saveLastPath(const std::filesystem::path& path) {
        std::ofstream file(getConfigPath());
        if (!file.is_open()) return false;
        file << path.string();
        return true;
    }

    bool saveSelectedFiles(const std::vector<std::string>& selectedNames) {
        std::ofstream file(getSelectedFilesPath());
        if (!file.is_open()) return false;
        for (const auto& name : selectedNames)
            file << name << "\n";
        return true;
    }

    bool loadSelectedFiles(std::vector<std::string>& outNames) {
        std::ifstream file(getSelectedFilesPath());
        if (!file.is_open()) return false;
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty())
                outNames.push_back(line);
        }
        return true;
    }

    bool saveOutputFile(const std::filesystem::path& path) {
        std::ofstream file(getOutputFilePath());
        if (!file.is_open()) return false;
        file << path.string();
        return true;
    }

    bool loadOutputFile(std::filesystem::path& outPath) {
        std::ifstream file(getOutputFilePath());
        if (!file.is_open()) return false;
        std::string line;
        if (std::getline(file, line) && !line.empty()) {
            outPath = line;
            return true;
        }
        return false;
    }

}