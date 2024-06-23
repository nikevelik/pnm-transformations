#pragma once
#include "../assets/String.h"

class AbstractMap{
    public:
        AbstractMap() = default;
        AbstractMap(const String& filename, bool isRaw, int g = 0);
        virtual void serialize() const;
        virtual void serialize(const String& filename) const;
        virtual void serializeraw(const String& filename) const = 0;
        virtual void serializeplain(const String& filename) const = 0;
        virtual void deserialize(const String& filename);
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
        const String& getFilename() const;
        bool isGray() const;
        bool isMonochrome() const;
    protected:
        virtual void deserializeplain(std::ifstream& infile) = 0;
        virtual void deserializeraw(std::ifstream& infile) = 0;
        virtual void deserializeheader(std::ifstream& infile) = 0;
        String fn;
        int g = 0;
        bool raw = false; 
        bool mod = false;
};
