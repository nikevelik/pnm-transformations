#pragma once
#include<stdexcept>
#include"../assets/_string.h"
#include"AbstractMap.h"
#include"Map.hpp"
#include"Bitmap.h"

static _string getFileType(const _string& filename) {
    for (int i = filename.getSize() - 1; i >= 0; --i) {
        if (filename[i] == '.') {
            return &filename[i+1];
            break;
        }
    }
    throw std::runtime_error("invalid filename passed");

}

class PNMFactory{
    static AbstractMap* add(const char* str);
};

AbstractMap* PNMFactory::add(const char* str){
    _string format = getFileType(str);
    if(format == "ppm"){
        return new Pixmap(str);
    }
    if(format == "pgm"){
        return new Graymap(str);
    }
    if(format == "pbm"){
        return new Bitmap(str);
    }
    throw std::runtime_error("invalid filename passed");
}