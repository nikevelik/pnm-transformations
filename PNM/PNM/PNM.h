#pragma once
#include "../../assets/_string.cpp"
#include <fstream>
class PNM{
    public:
        PNM() = default;
        PNM(bool isRaw);
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
        // virtual PNM* collagevertical() const = 0;
        // virtual PNM* collagehorizontal() const = 0;
        // virtual PNM* clone() const = 0;
        static unsigned MAX_ALLOWED;
        
    protected:
        virtual void deserializeplain(std::ifstream& infile) = 0;
        virtual void deserializeraw(std::ifstream& infile) = 0;
        virtual void deserializeheader(std::ifstream& infile) = 0;
        bool raw = false;
};

unsigned PNM::MAX_ALLOWED = 255;

PNM::PNM(bool isRaw):raw(isRaw){}

void PNM::deserialize(const _string& filename){
    std::ifstream infile(filename.c_str(), std::ios::binary);
    if (!infile) {
        throw std::runtime_error("Error! Could not open file");   
    }
    deserializeheader(infile);
    switch(raw){
        case 1:
            deserializeraw(infile);
            break;
        case 0: 
            deserializeplain(infile);
            break;
    }
    infile.close();
}

void PNM::serialize(const _string& filename) const {
    switch(raw){
        case 1:
            serializeraw(filename);
            break;
        case 0: 
            serializeplain(filename);
            break;
    }
}