#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <fstream>
#include <string>
#include <cstdint> // for fixed-size integer types

#include "reader.hpp"

class FileReader final : public Reader {
public:
    FileReader(std::string path) : path(std::move(path)), file(this->path, std::ios::binary) {
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + this->path);
        }
    }

    ~FileReader() {
        close();
    }

    void close() {
        file.close();
    }

public:
    void readInt8(int8_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(int8_t));
    }

    void readUint8(uint8_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(uint8_t));
    }

    void readInt16(int16_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(int16_t));
    }

    void readUint16(uint16_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(uint16_t));
    }

    void readInt32(int32_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(int32_t));;
    }

    void readUint32(uint32_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(uint32_t));
    }

    void readInt64(int64_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(int64_t));
    }

    void readUint64(uint64_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(uint64_t));
    }

    void readLong(long& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(long));
    }

    void readUlong(unsigned long& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(unsigned long));
    }

    void readFloat(float& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(float));
    }

    void readDouble(double& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(double));
    }

    void readLongDouble(long double& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(long double));
    }

    void readString(std::string& data) override {
        auto size = readSize();
        data.resize(size);
        file.read(data.data(), size);
    }

    void readChar(char& data) override {
        file.read(&data, sizeof(char));
    }

    void readWChar(wchar_t& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(wchar_t));
    }

    void readBool(bool& data) override {
        file.read(reinterpret_cast<char*>(&data), sizeof(bool));
    }

private:
    FileSizeType readSize() {
        FileSizeType size;
        file.read(reinterpret_cast<char*>(&size), sizeof(FileSizeType));
        return size;
    }

private:
    std::string path;
    std::ifstream file;
};

#endif //FILE_READER_HPP