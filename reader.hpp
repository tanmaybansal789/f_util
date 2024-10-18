#ifndef READER_HPP
#define READER_HPP

#include <fstream>
#include <string>
#include <cstdint> // for fixed-size integer types

class Reader;

template <typename T>
concept NonTrivialDeserialisable = (!std::is_trivial_v<T>) &&
    requires (Reader* reader)
    {
        { T::deserialise(reader) } -> std::same_as<T>;
    };

class Reader {
public:
    Reader() = default;

    template <typename T>
    void read(T& data) {
        if constexpr (NonTrivialDeserialisable<T>) {
            data = T::deserialise(this);
        } else {
            readImpl(data);
        }
    }

    void readImpl(int8_t& data) { readInt8(data); }
    void readImpl(uint8_t& data) { readUint8(data); }
    void readImpl(int16_t& data) { readInt16(data); }
    void readImpl(uint16_t& data) { readUint16(data); }
    void readImpl(int32_t& data) { readInt32(data); }
    void readImpl(uint32_t& data) { readUint32(data); }
    void readImpl(int64_t& data) { readInt64(data); }
    void readImpl(uint64_t& data) { readUint64(data); }
    void readImpl(long& data) { readLong(data); }
    void readImpl(unsigned long& data) { readUlong(data); }
    void readImpl(float& data) { readFloat(data); }
    void readImpl(double& data) { readDouble(data); }
    void readImpl(long double& data) { readLongDouble(data); }
    void readImpl(std::string& data) { readString(data); }
    void readImpl(char& data) { readChar(data); }
    void readImpl(wchar_t& data) { readWChar(data); }
    void readImpl(bool& data) { readBool(data); }

public:
    void readInt(int& data) {
        readInt32(data);
    }

    void readUint(unsigned int& data) {
        readUint32(data);
    }

    virtual void readInt8(int8_t& data) = 0;
    virtual void readUint8(uint8_t& data) = 0;
    virtual void readInt16(int16_t& data) = 0;
    virtual void readUint16(uint16_t& data) = 0;
    virtual void readInt32(int32_t& data) = 0;
    virtual void readUint32(uint32_t& data) = 0;
    virtual void readInt64(int64_t& data) = 0;
    virtual void readUint64(uint64_t& data) = 0;
    virtual void readLong(long& data) = 0;
    virtual void readUlong(unsigned long& data) = 0;
    virtual void readFloat(float& data) = 0;
    virtual void readDouble(double& data) = 0;
    virtual void readLongDouble(long double& data) = 0;
    virtual void readString(std::string& data) = 0;
    virtual void readChar(char& data) = 0;
    virtual void readWChar(wchar_t& data) = 0;
    virtual void readBool(bool& data) = 0;
};

#endif //READER_HPP