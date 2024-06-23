#pragma once
#include "../assets/_string.h"
#include "AbstractMap.h"
#include "MagicValue.h"
#include <stdexcept>

class Bitmap : public AbstractMap{
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

        Bitmap(const _string& filename);
        Bitmap(unsigned width, unsigned height, const _string& filename, bool isRaw, int gray);
        
    private:
        void deserializeplain(std::ifstream& infile) override;
        void deserializeraw(std::ifstream& infile) override;
        void deserializeheader(std::ifstream& infile) override;
        unsigned w = 0;
        unsigned h = 0;
        _bitset data;
};

Bitmap::Bitmap(const _string& filename){
    g = 2;
    // copyf(filename, "~"+filename);
    deserialize(filename);
}

Bitmap::Bitmap(unsigned width, unsigned height, const _string& filename, bool isRaw, int gray) : w(width), h(height), data((width + 7) / 8 * height), AbstractMap(filename, isRaw, gray){
    mod = true;
}

void Bitmap::deserializeheader(std::ifstream& infile){
    _string magic;
    infile >> magic;
    if (magic == MagicValue<Bit>::plain()) {
        raw = false;
    }else if(magic == MagicValue<Bit>::raw()){
        raw = true;
    }else{
        throw std::runtime_error("Invalid magic number for Bitmap files");
    }
    infile >> w >> h;
    if(!infile.good()){
        throw std::runtime_error("Invalid header values in file");
    }
    data = _bitset(h*(w+7)/8);
    char newline;
    infile.get(newline);
    if(!infile.good() || newline != '\n'){
        throw std::runtime_error("No separation between header and binary data. File is invalid");
    }
}

void Bitmap::deserializeplain(std::ifstream& infile){
    unsigned rs = (w+7)/8;
    for (unsigned y = 0; y < h; ++y) {
        for (unsigned x = 0; x < rs; ++x) {
            for(int i = 7; i>=0; i--){
                bool pixel;
                infile >> pixel;
                if(pixel){
                    data.set((y * rs + x)*8 + i);
                }
            }
        }
    }
}

void Bitmap::deserializeraw(std::ifstream& infile){
    infile.read(data.ptr(), data.size());
}

void Bitmap::serializeraw(const _string& filename) const {
    std::ofstream outfile(filename.c_str(), std::ios::binary);
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    outfile << MagicValue<Bit>::raw() << "\n";

    outfile << w << " " << h << "\n";

    outfile.write(data.ptr(), data.size());

    outfile.close();
}

void Bitmap::serializeplain(const _string& filename) const {
    std::ofstream outfile(filename.c_str());
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    outfile << MagicValue<Bit>::plain() << "\n";
    outfile << w << " " << h << "\n";

    unsigned rs = (w + 7) / 8;
    for (unsigned y = 0; y < h; ++y) {
        for (unsigned x = 0; x < rs; ++x) {
            for(int i = 7; i >= 0; i--) {
                outfile << data.read((y * rs + x) * 8 + i) << " ";
            }
        }
        outfile << "\n";
    }

    outfile.close();
}

void Bitmap::grayscale() {
    return;
}
void Bitmap::monochrome() {
    return;
}
void Bitmap::negative() {
    mod = true;
    unsigned rs = (w+7)/8;
    for(unsigned y = 0; y < h; y++){
        for(unsigned x = 0; x < rs; x++){
            data.flipbyte(y*rs + x);
        }
    }
}
void Bitmap::rotation90() {
    mod = true;
}
void Bitmap::rotation180() {
    mod = true;
}
void Bitmap::rotation270() {
    mod = true;
}

AbstractMap* Bitmap::clone() const {
    return new Bitmap(*this);
}