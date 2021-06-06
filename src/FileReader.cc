#include "FileReader.h"

Napi::FunctionReference FileReader::Reader;

void FileReader::Init(const Napi::Object &global) {
    Napi::Function function = global.Get("reader")
            .As<Napi::Function>();

    FileReader::Reader = Napi::Persistent(function);
}

Napi::Buffer<uint8_t> FileReader::Read(const std::string &filename) {
    Napi::Env env = FileReader::Reader.Env();

    return FileReader::Reader.Call({Napi::String::New(env, filename)})
            .As<Napi::Buffer<uint8_t>>();
}
