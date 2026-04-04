#pragma once

#include <filesystem>
#include <algorithm>

class FileReader
{
private:
    std::vector<char> buffer;
    mutable size_t pos = 0;
    std::filesystem::path filePath;

public:
    FileReader(const std::filesystem::path &file, std::ios::openmode mode)
        : filePath(file) {
        if ((mode & std::ios::binary) == 0) {
            throw std::runtime_error("FileReader: Only binary mode is supported: " + filePath.string());
        }

        std::ifstream fileStream(filePath, mode);

        if (!fileStream.is_open()) {
            throw std::runtime_error("FileReader: Cannot open file for reading: " + filePath.string());
        }

        fileStream.seekg(0, std::ios::end);
        std::streamsize fileSize = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        buffer.resize(static_cast<size_t>(fileSize));

        if (!fileStream.read(buffer.data(), fileSize)) {
            throw std::runtime_error("FileReader: Failed to read full file: " + filePath.string());
        }

        fileStream.close();
    }

    ~FileReader() = default;

    template <class T>
    void readVariable(T *p, bool swapEndianness = false, std::size_t size = 0) const {
        if (!size) {
            size = sizeof(T);
        }

        if (pos + size > buffer.size()) {
            throw std::runtime_error("FileReader: Read beyond buffer size");
        }

        char *pChar = reinterpret_cast<char *>(p);
        std::copy(buffer.data() + pos, buffer.data() + pos + size, pChar);
        pos += size;

        if (swapEndianness) {
            std::reverse(pChar, pChar + size);
        }
    }

    void setPos(std::streampos new_pos) const {
        if (new_pos < 0 || static_cast<size_t>(new_pos) > buffer.size()) {
            throw std::out_of_range("FileReader: Seek position out of range");
        }
        pos = static_cast<size_t>(new_pos);
    }
};