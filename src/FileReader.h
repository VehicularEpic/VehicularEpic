#pragma once

#ifndef _FileReader
#define _FileReader

#include <napi.h>

#include <iostream>

class FileReader {
public:
    static void Init(const Napi::Object &global);

    static Napi::Buffer<uint8_t> Read(const std::string &filename);

private:
    static Napi::FunctionReference Reader;
};


#endif
