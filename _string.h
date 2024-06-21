#pragma once
#include <iostream>
// credit: angeld55

class _string 
{
public:
    _string();
    _string(const char* data);

    _string(const _string& other);
    _string(_string&& other) noexcept;

    _string& operator=(const _string& other); 

    _string& operator=(_string&& other) noexcept;
    ~_string();

    size_t getCapacity() const;
    size_t getSize() const;

    const char* c_str() const;

    _string& operator+=(const _string& other);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const _string& obj);
    friend std::istream& operator>>(std::istream& is, _string& ref);
    friend _string operator+(const _string& lhs, const _string& rhs);

    _string substr(size_t begin, size_t howMany) const;

private:
    explicit _string(size_t stringLength);
    void resize(unsigned newAllocatedDataSize);

    void free();
    void copyFrom(const _string& other);

    void moveFrom(_string&& other);

    char* _data;
    size_t _size;
    size_t _allocatedDataSize;
};



bool operator==(const _string& lhs, const _string& rhs);
bool operator!=(const _string& lhs, const _string& rhs);
bool operator<(const _string& lhs, const _string& rhs);
bool operator<=(const _string& lhs, const _string& rhs);
bool operator>(const _string& lhs, const _string& rhs);
bool operator>=(const _string& lhs, const _string& rhs);