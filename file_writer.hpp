#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

#include <fstream>
#include <cstddef>
#include <cstdint> // for fixed-size integer types

#include "writer.hpp"

using FileSizeType = uint32_t;

class FileWriter final : public Writer {
public:
    FileWriter(std::string path) : path(std::move(path)), file(this->path, std::ios::binary) {
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + this->path);
        }
    }

    ~FileWriter() {
        close();
    }

    void close() {
        file.flush();
        file.close();
    }

public:
    void writeInt8(int8_t data) override {
        // writeSize(sizeof(int8_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(int8_t));
    }

    void writeUint8(uint8_t data) override {
        // writeSize(sizeof(uint8_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(uint8_t));
    }

    void writeInt16(int16_t data) override {
        // writeSize(sizeof(int16_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(int16_t));
    }

    void writeUint16(uint16_t data) override {
        // writeSize(sizeof(uint16_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(uint16_t));
    }

    void writeInt32(int32_t data) override {
        // writeSize(sizeof(int32_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(int32_t));
    }

    void writeUint32(uint32_t data) override {
        // writeSize(sizeof(uint32_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(uint32_t));
    }

    void writeInt64(int64_t data) override {
        // writeSize(sizeof(int64_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(int64_t));
    }

    void writeUint64(uint64_t data) override {
        // writeSize(sizeof(uint64_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(uint64_t));
    }

    void writeLong(long data) override {
        // writeSize(sizeof(long));
        file.write(reinterpret_cast<const char*>(&data), sizeof(long));
    }

    void writeUlong(unsigned long data) override {
        // writeSize(sizeof(unsigned long));
        file.write(reinterpret_cast<const char*>(&data), sizeof(unsigned long));
    }

    void writeFloat(float data) override {
        // writeSize(sizeof(float));
        file.write(reinterpret_cast<const char*>(&data), sizeof(float));
    }

    void writeDouble(double data) override {
        // writeSize(sizeof(double));
        file.write(reinterpret_cast<const char*>(&data), sizeof(double));
    }

    void writeLongDouble(long double data) override {
        // writeSize(sizeof(long double));
        file.write(reinterpret_cast<const char*>(&data), sizeof(long double));
    }

    void writeString(const std::string_view data) override {
        writeSize(data.size());
        file.write(data.data(), data.size());
    }

    void writeChar(char data) override {
        // writeSize(sizeof(char));
        file.write(&data, sizeof(char));
    }

    void writeWChar(wchar_t data) override {
        // writeSize(sizeof(wchar_t));
        file.write(reinterpret_cast<const char*>(&data), sizeof(wchar_t));
    }

    void writeBool(bool data) override {
        // writeSize(sizeof(bool));
        file.write(reinterpret_cast<const char*>(&data), sizeof(bool));
    }

    void flush() {
        file.flush();
    }

private:
    void writeSize(FileSizeType size) {
        file.write(reinterpret_cast<const char*>(&size), sizeof(FileSizeType));
    }

private:
    std::string path;
    std::ofstream file;
};

#endif //FILE_WRITER_HPP