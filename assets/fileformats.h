#pragma once
#include "_string.h"
_string getFileType(const _string& filename) {
    for (int i = filename.getSize() - 1; i >= 0; --i) {
        if (filename[i] == '.') {
            return &filename[i+1];
            break;
        }
    }
    throw std::runtime_error("invalid filename passed");

}

bool isValidFileType(const _string& filename){
    try{
        _string format = getFileType(filename);
        return format=="ppm" || format =="pgm" || format == "pbm";
    }catch(...){
        return false;
    }
}