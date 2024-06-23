#pragma once
#include"AbstractMap.h"
#include<fstream>
#include <stdexcept>

AbstractMap::AbstractMap(const String& filename, bool isRaw, int gray):fn(filename), raw(isRaw), g(gray) {}

void AbstractMap::deserialize(const String& filename){
    fn = filename;
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

void AbstractMap::serialize(const String& filename) const {
    switch(raw){
        case true:
            serializeraw(filename);
            break;
        case false: 
            serializeplain(filename);
            break;
    }
}


void AbstractMap::serialize() const {
    if(mod){
        serialize(fn);
    }
}

bool AbstractMap::isGray() const {
    return g>0;
}

bool AbstractMap::isMonochrome() const {
    return g==2;
}

const String& AbstractMap::getFilename() const{
    return fn;
}