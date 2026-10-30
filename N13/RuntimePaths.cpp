#include "RuntimePaths.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <direct.h>
#elif defined(__APPLE__)
#include <filesystem>
#include <mach-o/dyld.h>
#else
#include <filesystem>
#endif

#if !defined(_WIN32)
namespace fs = std::filesystem;
#endif

namespace {
#if defined(_WIN32)
void enterExecutableDirectory(const char*) {
    std::vector<wchar_t> buffer(32768);
    const auto size = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
    if (!size || size >= buffer.size()) throw std::runtime_error("Cannot locate game executable");
    std::wstring path(buffer.data(), size);
    const auto separator = path.find_last_of(L"\\/");
    if (separator == std::wstring::npos || _wchdir(path.substr(0, separator + 1).c_str()) != 0)
        throw std::runtime_error("Cannot enter game directory");
}
bool resourceExists(const std::string& name) {
    const auto size = MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, nullptr, 0);
    if (!size) return false;
    std::vector<wchar_t> path(size);
    MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, path.data(), size);
    const auto attributes = GetFileAttributesW(path.data());
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}
#else
fs::path executablePath(const char* argument) {
#if defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::vector<char> buffer(size);
    if (_NSGetExecutablePath(buffer.data(), &size)) throw std::runtime_error("Cannot locate game executable");
    return fs::canonical(buffer.data());
#else
    std::error_code error;
    auto path = fs::read_symlink("/proc/self/exe", error);
    if (!error) return path;
    return fs::canonical(argument);
#endif
}
void enterExecutableDirectory(const char* argument) {
    fs::current_path(executablePath(argument).parent_path());
}
bool resourceExists(const std::string& name) { return fs::is_regular_file(fs::u8path(name)); }
#endif
}

bool initializeRuntime(const char* executableArgument) {
    try {
        enterExecutableDirectory(executableArgument);
        // Check the complete packaged asset list, including dynamically named cards.
        std::ifstream manifest("resources.manifest");
        if (!manifest) throw std::runtime_error("Missing resources.manifest. Extract the entire game folder first.");
        std::string name;
        while (std::getline(manifest, name)) {
            if (!name.empty() && name.back() == '\r') name.pop_back();
            if (!name.empty() && !resourceExists(name))
                throw std::runtime_error("Missing game resource: " + name);
        }
        std::cout << "Game resources OK\n";
        return true;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
#if defined(_WIN32)
        MessageBoxA(nullptr, error.what(), "N13 Poker - startup error", MB_OK | MB_ICONERROR);
#endif
        return false;
    }
}
