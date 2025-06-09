#pragma once
#include <string>

struct FileException {
    std::string filename;
    bool bRead;
    FileException(const std::string& name, bool b) : filename(name), bRead(b) {}
};
