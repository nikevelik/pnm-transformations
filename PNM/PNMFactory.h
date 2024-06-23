#pragma once
#include<stdexcept>
#include"../assets/_string.h"
#include"AbstractMap.h"
#include"Map.hpp"
#include"Bitmap.h"
#include"../assets/fileformats.h"
class PNMFactory{
public:
    static AbstractMap* create(const char* str);
};

AbstractMap* PNMFactory::create(const char* str){
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