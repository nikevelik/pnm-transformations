#pragma once
#include<fstream>
#include <stdexcept>
class Pixel {
public:
    unsigned char r, g, b;
    bool isCorrect(unsigned char maxvalue) const {
        return r <= maxvalue && g <= maxvalue && b<=maxvalue;
    }
    bool isGray() const{
        return r==b && r==g;
    }
    bool isMonochrome(unsigned char maxvalue) const {
        return (r==0 && b==0 && g==0) || (r==maxvalue && b==maxvalue && g==maxvalue);
    }
    void greyscale(){
        if(!isGray()){
            int sum = r+b+g;
            r = b = g = sum/3;
        }
    }
    void monochrome(unsigned char maxvalue){
        if(!isMonochrome(maxvalue)){
            r = b = g = ((((0.5125*r + 0.8154*g + 0.3721*b)) >= maxvalue/2) ? maxvalue : 0);
        }
    }
    void negative(unsigned char maxvalue){
        r = maxvalue - r;
        g = maxvalue - g;
        b = maxvalue - b;
    }
};


int UCHAR_MAX = 255;

static void check(std::ifstream& ifs, int v){
    if(!ifs.good()){
        throw std::runtime_error("could not read pixel values from source.");
    }
    if(v > 255 || v < 0){
        throw std::runtime_error("Input value is not a pixel value");
    }
}

std::ifstream& operator>>(std::ifstream& ifs, pixel& obj){
    int v;
    ifs >> v;
    check(ifs, v);
    obj.r = v;

    ifs >> v;
    check(ifs, v);
    obj.g = v;

    ifs >> v;
    check(ifs, v);
    obj.b = v;
    
    return ifs;
}


std::ofstream& operator<<(std::ofstream& ofs,const pixel& obj){
    int v;
    v = obj.r;
    ofs << v << " ";


    v = obj.g;
    ofs << v << " ";


    v = obj.b;
    ofs << v << "\n";
    
    return ofs;
}
