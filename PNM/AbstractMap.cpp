#pragma once
#include"AbstractMap.h"

AbstractMap::AbstractMap(const _string& filename, bool isRaw, int gray):fn(filename), raw(isRaw), g(gray) {}

void AbstractMap::deserialize(const _string& filename){
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

const _string& AbstractMap::getFilename() const{
    return fn;
}

// void AbstractMap::restore(){
//     copyf("~"+fn, fn);
//     deserialize(fn);
// }

// void AbstractMap::copyf(const _string& srcname, const _string& destname) {
//     std::ifstream src(srcname, std::ios::binary);
//     if (!src.is_open()) {
//         throw std::runtime_error("Error: unable to open source file in order to make backup");
//     }

//     std::ofstream dest(destname, std::ios::binary);
//     if (!dest.is_open()) {
//         throw std::runtime_error("Error: unable to open destination file in order to make backup");
//     }

//     dest << src.rdbuf();

//     if(!src.good() || !dest.good()){
//         throw std::runtime_error("Error: unable to make backup");
//     }

//     src.close();
//     dest.close();
// }

// void updatebackup(){
//     copyf(fn, "~"+fn);
// }