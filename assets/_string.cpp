#include "_string.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)
// credit: angeld55
static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

_string::_string() : _string("") {}

_string::_string(const char* data) 
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

_string::_string(size_t stringLength) 
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

_string::_string(const _string& other) 
{
    copyFrom(other);
}
_string::_string(_string&& other) noexcept
{
    moveFrom(std::move(other));
}


void _string::moveFrom(_string&& other)
{
    _data = other._data;
    other._data = nullptr;
    
    _size = other._size;
    other._size = 0;

    _allocatedDataSize = other._allocatedDataSize;
    other._allocatedDataSize = 0;
}


_string& _string::operator=(const _string& other) 
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

_string& _string::operator=(_string&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}


_string::~_string() 
{
    free();
}

size_t _string::getCapacity() const 
{
    return _allocatedDataSize - 1;
}

size_t _string::getSize() const 
{
    return _size;
}

const char* _string::c_str() const 
{
    return _data;
}

_string& _string::operator+=(const _string& other) 
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    // we need to use strncat instead of strcat, because strcat will not work for str += str 
    // (the terminating zero of str will be destroyed by the first char)
    std::strncat(_data, other._data, other.getSize()); 
    
    _size = getSize() + other.getSize();
    return *this;
}

char& _string::operator[](size_t index) 
{
    return _data[index]; // no security check!!
}

const char& _string::operator[](size_t index) const 
{
    return _data[index]; // no security check!!
}

std::ostream& operator<<(std::ostream& os, const _string& obj) 
{
    return os << obj._data;
}

std::istream& operator>>(std::istream& is, _string& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void _string::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, _data);
    delete[] _data;
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void _string::free() 
{
    delete[] _data;
}

void _string::copyFrom(const _string& other) 
{
    _allocatedDataSize = other._allocatedDataSize;
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, other._data);
    _size = other._size;
}

_string _string::substr(size_t begin, size_t howMany) const
{
    if (begin + howMany > getSize())
        throw std::length_error("Error, Substr out of range");


    _string res(howMany + 1);
    strncat(res._data, _data + begin, howMany);
    return res;
}


_string operator+(const _string& lhs, const _string& rhs) 
{
    _string result(lhs.getSize() + rhs.getSize());
    result += lhs; // no resize is needed
    result += rhs;
    return result;
}

bool operator==(const _string& lhs, const _string& rhs) 
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const _string& lhs, const _string& rhs) 
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const _string& lhs, const _string& rhs) 
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const _string& lhs, const _string& rhs) 
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const _string& lhs, const _string& rhs) 
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const _string& lhs, const _string& rhs) 
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}