#pragma once
#include "../assets/_string.h"

template <class T>
struct MagicValue;


template <>
struct MagicValue<class Bit> {
    static const _string plain() { return "P1"; }
    static const _string raw() { return "P4"; }
};

template <>
struct MagicValue<class Shade> {
    static const _string plain() { return "P2"; }
    static const _string raw() { return "P5"; }
};

template <>
struct MagicValue<class Pixel> {    
    static const _string plain() { return "P3"; }
    static const _string raw() { return "P6"; }
};

