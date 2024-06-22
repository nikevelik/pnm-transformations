#pragma once
#include "../../assets/_string.cpp"
#include <fstream>
class PNM{
    public:
        virtual void serialize(const _string& filename) const = 0;
        virtual void serializeraw(const _string& filename) const = 0;
        virtual void serializeplain(const _string& filename) const = 0;
        virtual void deserialize(const _string& filename) = 0;
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
        bool raw;
};

unsigned PNM::MAX_ALLOWED = 255;