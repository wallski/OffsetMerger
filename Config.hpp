#pragma once
#include <string>
#include <filesystem>
#include <vector>

namespace Config {
    bool loadLastPath(std::filesystem::path& outPath);
    bool saveLastPath(const std::filesystem::path& path);
    std::filesystem::path getConfigPath();

    // Save/load which filenames were checked
    bool saveSelectedFiles(const std::vector<std::string>& selectedNames);
    bool loadSelectedFiles(std::vector<std::string>& outNames);

    // Save/load the output .h file path
    bool saveOutputFile(const std::filesystem::path& path);
    bool loadOutputFile(std::filesystem::path& outPath);
}