#pragma once
class Shade{
public:
    static unsigned MAX_ALLOWED;
    bool isCorrect(unsigned char maxvalue) const;
    // bool isGray() const; // I am always gray!!
    bool isMonochrome(unsigned char maxvalue) const;
    // void greyscale(); // I am always gray!!
    void monochrome(unsigned char maxvalue);
    void negative(unsigned char maxvalue);
    static void check(std::ifstream& ifs, int v);
    friend std::ifstream& operator>>(std::ifstream& ifs, Shade& obj);
    friend std::ofstream& operator<<(std::ofstream& ofs,const Shade& obj);

private:
    unsigned char v;
};