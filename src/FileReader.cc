#include "FileReader.h"

std::vector<uint8_t> FileReader::Read(const std::string &File) {
    FILE *file;

    int error = fopen_s(&file, File.c_str(), "rb");

    if (error > 0) {
        if (error == ENOENT) {
            fprintf(stderr, "Error: %s not found\n", File.c_str());
        }

        throw std::exception("Error loading file");
    }

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    rewind(file);

    std::vector<uint8_t> buffer(size);

    size_t read = fread_s(&buffer[0], buffer.size(), 1, size, file);

    if (read != size) {
        throw std::exception("Bytes read differ from file size!");
    }

    fclose(file);

    return buffer;
}
