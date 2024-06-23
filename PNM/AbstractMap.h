#pragma once
#include "../assets/_string.h"
#include <fstream>
#include <stdexcept>
class AbstractMap{
    public:
        AbstractMap() = default;
        AbstractMap(bool isRaw);
        virtual void serialize(const _string& filename) const;
        virtual void serializeraw(const _string& filename) const = 0;
        virtual void serializeplain(const _string& filename) const = 0;
        virtual void deserialize(const _string& filename);
        virtual void greyscale() = 0;
        virtual void monochrome() = 0;
        virtual void negative() = 0;
        virtual void rotation90() = 0;
        virtual void rotation180() = 0;
        virtual void rotation270() = 0;
        // virtual AbstractMap* collagevertical() const = 0;
        // virtual AbstractMap* collagehorizontal() const = 0;
        // virtual AbstractMap* clone() const = 0;
    protected:
        virtual void deserializeplain(std::ifstream& infile) = 0;
        virtual void deserializeraw(std::ifstream& infile) = 0;
        virtual void deserializeheader(std::ifstream& infile) = 0;
        bool raw = false;
};

AbstractMap::AbstractMap(bool isRaw):raw(isRaw){}

void AbstractMap::deserialize(const _string& filename){
    std::ifstream infile(filename.c_str(), std::ios::binary);
    if (!infile) {
        throw std::runtime_error("Error! Could not open file");   
    }
    deserializeheader(infile);
    switch(raw){
        case true:
            deserializeraw(infile);
            break;
        case false: 
            deserializeplain(infile);
            break;
    }
}

void AbstractMap::serialize(const _string& filename) const {
    switch(raw){
        case true:
            serializeraw(filename);
            break;
        case false: 
            serializeplain(filename);
            break;
    }
}