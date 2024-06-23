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
