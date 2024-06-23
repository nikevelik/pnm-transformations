#pragma once
#include "../assets/_string.h"
#include <fstream>
#include <stdexcept>

class AbstractMap{
    public:
        AbstractMap() = default;
        AbstractMap(const _string& filename, bool isRaw, int g = 0);
        virtual void serialize() const;
        virtual void serialize(const _string& filename) const;
        virtual void serializeraw(const _string& filename) const = 0;
        virtual void serializeplain(const _string& filename) const = 0;
        virtual void deserialize(const _string& filename);
        virtual void grayscale() = 0;
        virtual void monochrome() = 0;
        virtual void negative() = 0;
        virtual void rotation90() = 0;
        virtual void rotation180() = 0;
        virtual void rotation270() = 0;
        // virtual AbstractMap* collagevertical() const = 0;
        // virtual AbstractMap* collagehorizontal() const = 0;
        virtual AbstractMap* clone() const = 0;

        void restore();
        const _string& getFilename() const;
        bool isGray() const;
        bool isMonochrome() const;
        // void restore();
        // void updatebackup();
    protected:
        // static void copyf(const _string& srcname, const _string& destname);
        virtual void deserializeplain(std::ifstream& infile) = 0;
        virtual void deserializeraw(std::ifstream& infile) = 0;
        virtual void deserializeheader(std::ifstream& infile) = 0;
        _string fn;
        int g = 0;
        bool raw = false; 
        bool mod = false;
};
