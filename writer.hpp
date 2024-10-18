#ifndef WRITER_HPP
#define WRITER_HPP

#include <type_traits>
#include <string>
#include <cstdint> // for fixed-size integer types

class Writer;

template <typename T>
concept NonTrivialSerialisable = (!std::is_trivial_v<T>) &&
    requires (T t, Writer* writer)
    {
        { t.serialise(writer) } -> std::same_as<void>;
    };

class Writer {
public:
    Writer() = default;

    template <typename T>
    void write(T t) {
        if constexpr (NonTrivialSerialisable<T>) {
            t.serialise(this);
        } else {
            writeImpl(t);
        }
    }

private:
    void writeImpl(int8_t data) { writeInt8(data); }
    void writeImpl(uint8_t data) { writeUint8(data); }
    void writeImpl(int16_t data) { writeInt16(data); }
    void writeImpl(uint16_t data) { writeUint16(data); }
    void writeImpl(int32_t data) { writeInt32(data); }
    void writeImpl(uint32_t data) { writeUint32(data); }
    void writeImpl(int64_t data) { writeInt64(data); }
    void writeImpl(uint64_t data) { writeUint64(data); }
    void writeImpl(long data) { writeLong(data); }
    void writeImpl(unsigned long data) { writeUlong(data); }
    void writeImpl(float data) { writeFloat(data); }
    void writeImpl(double data) { writeDouble(data); }
    void writeImpl(long double data) { writeLongDouble(data); }
    void writeImpl(const std::string_view data) { writeString(data); }
    void writeImpl(char data) { writeChar(data); }
    void writeImpl(wchar_t data) { writeWChar(data); }
    void writeImpl(bool data) { writeBool(data); }

public:
    void writeInt(int data) {
        writeInt32(data);
    }

    void writeUint(unsigned int data) {
        writeUint32(data);
    }

    virtual void writeInt8(int8_t data) = 0;
    virtual void writeUint8(uint8_t data) = 0;
    virtual void writeInt16(int16_t data) = 0;
    virtual void writeUint16(uint16_t data) = 0;
    virtual void writeInt32(int32_t data) = 0;
    virtual void writeUint32(uint32_t data) = 0;
    virtual void writeInt64(int64_t data) = 0;
    virtual void writeUint64(uint64_t data) = 0;
    virtual void writeLong(long data) = 0;
    virtual void writeUlong(unsigned long data) = 0;
    virtual void writeFloat(float data) = 0;
    virtual void writeDouble(double data) = 0;
    virtual void writeLongDouble(long double data) = 0;
    virtual void writeString(std::string_view data) = 0;
    virtual void writeChar(char data) = 0;
    virtual void writeWChar(wchar_t data) = 0;
    virtual void writeBool(bool data) = 0;
};

#endif //WRITER_HPP