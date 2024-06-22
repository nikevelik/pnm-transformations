#pragma once
#include "../PNM/PNM.h"
#include "../../assets/_matrix.hpp"
#include "../../assets/Pixel.h"
#include <fstream>
#include <stdexcept>
class PPM : public PNM{
    public:
        void serializeraw(const _string& filename) const override;
        void serializeplain(const _string& filename) const override;
        void greyscale() override;
        void monochrome() override;
        void negative() override;
        void rotation90() override;
        void rotation180() override;
        void rotation270() override;
        // PNM* collagevertical() const override;
        // PNM* collagehorizontal() const override;
        // PNM* clone() const override;

        PPM(const _string& filename);
        PPM(unsigned width, unsigned height, unsigned maxvalue, bool isRaw);
        
    private:
        void deserializeplain(std::ifstream& infile) override;
        void deserializeraw(std::ifstream& infile) override;
        void deserializeheader(std::ifstream& infile) override;

        _matrix<Pixel> data;
};

PPM::PPM(unsigned width, unsigned height, unsigned maxvalue, bool isRaw) : data(width, height, maxvalue), PNM(isRaw){}

void PPM::deserializeheader(std::ifstream& infile){
    _string magic;
    infile >> magic;
    if (magic == "P3") {
        raw = false;
    }else if(magic == "P6"){
        raw = true;
    }else{
        throw std::runtime_error("Invalid magic number for PPM files");
    }
    unsigned w, h, mv;
    infile >> w >> h >> mv;
    if(!infile.good()){
        throw std::runtime_error("Invalid header values in file");
    }
    if(mv > MAX_ALLOWED){
        throw std::runtime_error("This application only supports maximum color values below 256");
    }
    data = _matrix<Pixel>(w, h, mv);
    char newline;
    infile.get(newline);
    if(!infile.good() || newline != '\n'){
        throw std::runtime_error("No separation between header and binary data. File is invalid");
    }
}

void PPM::deserializeplain(std::ifstream& infile) {
    data.populateFromPlain(infile);
}

void PPM::deserializeraw(std::ifstream& infile) {
    data.populateFromBinary(infile);    
}

PPM::PPM(const _string& filename){
    deserialize(filename);
}

void PPM::serializeplain(const _string& filename) const {
    std::ofstream outfile(filename.c_str());
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing");
    }

    outfile << "P3\n";
    outfile << data.width() << " " << data.height() << "\n";
    outfile << data.maxvalue() << "\n";
    
    data.populateToPlain(outfile);

    outfile.close();
}

void PPM::serializeraw(const _string& filename) const {
    std::ofstream outfile(filename.c_str(), std::ios::binary);
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }
    outfile << "P6\n";
    outfile << data.width() << " " << data.height() << "\n";
    outfile << data.maxvalue() << "\n";
    
    data.populateToBinary(outfile);
    
    outfile.close();
}
void PPM::rotation90(){
    data.rotation90();
}

void PPM::rotation270(){
    data.rotation270();
}

void PPM::rotation180(){
    data.rotation180();
}



void PPM::greyscale(){
    for(unsigned y = 0; y < data.height(); y++){
        for(unsigned x = 0; x < data.width(); x++){
            data[y][x].greyscale();
        }
    }
}

void PPM::monochrome(){
    for(unsigned y = 0; y < data.height(); y++){
        for(unsigned x = 0; x < data.width(); x++){
            data[y][x].monochrome(data.maxvalue());
        }
    }
}

void PPM::negative(){
    for(unsigned y = 0; y < data.height(); y++){
        for(unsigned x = 0; x < data.width(); x++){
            data[y][x].negative(data.maxvalue());
        }
    }
}