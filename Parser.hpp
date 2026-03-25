#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <regex>

struct OffsetEntry {
    std::string name;
    std::string value;
    std::string sourceFile;
    std::string context;
};

class OffsetParser {
public:
    bool parseFile(const std::filesystem::path& filepath);
    const std::vector<OffsetEntry>& getEntries() const { return entries; }
    void clear() { entries.clear(); }
    static std::vector<std::filesystem::path> findHppFiles(const std::filesystem::path& directory);
    bool generateMergedFile(const std::filesystem::path& outputPath,
        const std::vector<std::filesystem::path>& selectedFiles,
        const std::string& namespaceName = "Offsets");

private:
    std::vector<OffsetEntry> entries;
    std::regex constexprPattern{ R"(constexpr\s+std::ptrdiff_t\s+(\w+)\s*=\s*(0x[0-9A-Fa-f]+);)" };
    std::regex namespacePattern{ R"(namespace\s+(\w+))" };
    std::regex classCommentPattern{ R"(//\s*(?:->)?\s*([A-Za-z_][\w\s:]*))" };

    std::string extractContext(const std::string& line, const std::vector<std::string>& nsStack);
};