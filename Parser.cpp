#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

std::vector<std::filesystem::path> OffsetParser::findHppFiles(const std::filesystem::path& directory) {
    std::vector<std::filesystem::path> result;
    if (!std::filesystem::exists(directory)) return result;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext == ".hpp" || ext == ".h") {
                result.push_back(entry.path());
            }
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

bool OffsetParser::parseFile(const std::filesystem::path& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return false;

    std::string line;
    std::vector<std::string> namespaceStack;
    std::string filename = filepath.filename().string();

    while (std::getline(file, line)) {
        std::smatch nsMatch;
        if (std::regex_search(line, nsMatch, namespacePattern)) {
            namespaceStack.push_back(nsMatch[1]);
        }

        if (line.find('}') != std::string::npos && !namespaceStack.empty()) {
            int opens = (int)std::count(line.begin(), line.end(), '{');
            int closes = (int)std::count(line.begin(), line.end(), '}');
            if (closes > opens) {
                namespaceStack.pop_back();
            }
        }

        std::smatch match;
        if (std::regex_search(line, match, constexprPattern)) {
            OffsetEntry entry;
            entry.name = match[1];
            entry.value = match[2];
            entry.sourceFile = filename;
            entry.context = extractContext(line, namespaceStack);
            entries.push_back(entry);
        }
    }
    return true;
}

std::string OffsetParser::extractContext(const std::string& line, const std::vector<std::string>& nsStack) {
    std::smatch match;
    if (std::regex_search(line, match, classCommentPattern)) {
        std::string ctx = match[1];
        ctx.erase(std::remove_if(ctx.begin(), ctx.end(),
            [](char c) { return c == '\r' || c == '\n'; }), ctx.end());
        while (!ctx.empty() && ctx.back() == ' ') ctx.pop_back();
        if (!ctx.empty()) return ctx;
    }

    for (auto it = nsStack.rbegin(); it != nsStack.rend(); ++it) {
        if (*it != "cs2_dumper" && *it != "offsets" && *it != "buttons" &&
            *it != "schemas" && *it != "client_dll") {
            return *it;
        }
    }

    if (!nsStack.empty()) return nsStack.back();
    return "global";
}

bool OffsetParser::generateMergedFile(const std::filesystem::path& outputPath,
    const std::vector<std::filesystem::path>& selectedFiles,
    const std::string& namespaceName) {
    std::ofstream out(outputPath);
    if (!out.is_open()) return false;

    out << "#pragma once\n";
    out << "#include <cstdint>\n\n";
    out << "namespace " << namespaceName << "\n{\n";

    std::map<std::string, std::vector<OffsetEntry>> byFile;
    for (const auto& e : entries) {
        bool selected = false;
        for (const auto& sf : selectedFiles) {
            if (e.sourceFile == sf.filename().string()) { selected = true; break; }
        }
        if (selected) byFile[e.sourceFile].push_back(e);
    }

    for (const auto& [file, group] : byFile) {
        if (group.empty()) continue;

        out << "\n    // ============================================\n";
        out << "    // Source: " << file << "\n";
        out << "    // ============================================\n";

        std::map<std::string, std::vector<OffsetEntry>> byContext;
        for (const auto& e : group) byContext[e.context].push_back(e);

        for (const auto& [ctx, ctxGroup] : byContext) {
            if (ctx != "global" && ctx != file) {
                out << "\n    // -> " << ctx << "\n";
            }
            for (const auto& e : ctxGroup) {
                out << "    constexpr std::ptrdiff_t " << e.name << " = " << e.value << ";\n";
            }
        }
    }

    out << "}\n";
    out.close();
    return true;
}