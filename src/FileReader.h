#pragma once

#include <cstdio>
#include <string>
#include <vector>

class FileReader {
public:
    static std::vector<uint8_t> Read(const std::string &);

};
