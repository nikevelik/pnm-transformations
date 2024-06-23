#pragma once
#include "AbstractMap.h"
#include "../assets/_string.h"
#include "GraphicMatrix.hpp"
#include <fstream>
#include <stdexcept>
#include "Shade.h"
#include "Pixel.h"

template<class T>
class Map : public AbstractMap{
    public:
        void serializeraw(const _string& filename) const override;
        void serializeplain(const _string& filename) const override;
        void grayscale() override;
        void monochrome() override;
        void negative() override;
        void rotation90() override;
        void rotation180() override;
        void rotation270() override;
        // AbstractMap* collagevertical() const override;
        // AbstractMap* collagehorizontal() const override;
        AbstractMap* clone() const override;

        Map(const _string& filename);
        Map(unsigned width, unsigned height, const _string& filename, bool isRaw, int gray, unsigned maxvalue = T::MAX_ALLOWED);
        
    private:
        void deserializeplain(std::ifstream& infile) override;
        void deserializeraw(std::ifstream& infile) override;
        void deserializeheader(std::ifstream& infile) override;

        GraphicMatrix<T> data;
};

template <class T>
Map<T>::Map(unsigned width, unsigned height, const _string& filename, bool isRaw, int gray, unsigned maxvalue) : data(width, height, maxvalue), AbstractMap(filename, isRaw, gray){
    mod = true;
}
template <class T>
void Map<T>::deserializeheader(std::ifstream& infile){
    _string magic;
    infile >> magic;
    if (magic == MagicValue<T>::plain()) {
        raw = false;
    }else if(magic == MagicValue<T>::raw()){
        raw = true;
    }else{
        throw std::runtime_error("Invalid magic number for Map files");
    }
    data = GraphicMatrix<T>(infile);
}
template <class T>
void Map<T>::deserializeplain(std::ifstream& infile) {
    data.deserializeplain(infile);
}
template <class T>
void Map<T>::deserializeraw(std::ifstream& infile) {
    data.deserializeraw(infile);    
}
template <class T>
Map<T>::Map(const _string& filename){
    // copyf(filename, "~"+filename);
    deserialize(filename);
}
template <class T>
void Map<T>::serializeplain(const _string& filename) const {
    data.serializeplain(filename);
}
template <class T>
void Map<T>::serializeraw(const _string& filename) const {
    data.serializeraw(filename);
}
template <class T>
void Map<T>::rotation90(){
    mod = true;
    data.rotation90();
}
template <class T>
void Map<T>::rotation270(){
    mod = true;
    data.rotation270();
}
template <class T>
void Map<T>::rotation180(){
    mod = true;
    data.rotation180();
}
template <class T>
void Map<T>::grayscale(){
    if(!isGray()){
        g = 1;
        mod = true;
        data.grayscale();
    }
}
template <class T>
void Map<T>::monochrome(){
    if(!isMonochrome()){
        g = 2;
        mod = true;
        data.monochrome();
    }
}
template <class T>
void Map<T>::negative(){
    mod = true;
    data.negative();
}

template <class T>
AbstractMap* Map<T>::clone() const {
    return new Map<T>(*this);
}


template <>
Map<Shade>::Map(const _string& filename){
    g = 1;
    // copyf(filename, "~"+filename);
    deserialize(filename);
}


using Pixmap = Map<Pixel>;
using Graymap = Map<Shade>;