#include<iostream>
#include<fstream>
#include <stdexcept>
#include "../_string.cpp"
#include "../_bitset.cpp"
using namespace std;

struct pixel {
    int r, g, b;
};

struct shade{
    int v;
};

pixel** parsePlainPPM(_string filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        throw std::runtime_error( "Error: Could not open file " );
        
    }
    _string magic;
    infile >> magic;
    if (magic != "P3") {
        throw std::runtime_error( "Error: Not a valid PPM ASCII file." );
    }
    int width, height, maxColor;
    infile >> width >> height;
    infile >> maxColor;
    if(width == 0 || height == 0 || maxColor == 0){
        throw std::runtime_error( "Error: Not a valid PGM ASCII file.");
    }

    pixel** res = new pixel*[width];
    
    for (int x = 0; x < width; x++) { 
        res[x] = new pixel[height];   
        for (int y = 0; y < 2; y++) {             
            infile >> res[x][y].r >> res[x][y].g >> res[x][y].b;
        }
    }
    infile.close();
    return res;
}

pixel** parseRawPPM(_string filename) {
    ifstream infile(filename.c_str(), ios::binary);
    if (!infile) {
        throw std::runtime_error( "Error: Could not open file " );
    }
    _string magic;
    infile >> magic;
    if (magic != "P6") {
        throw std::runtime_error( "Error: Not a valid PPM binary file." );
    }

    int width, height, maxColor;
    infile >> width >> height;
    infile >> maxColor;
    
    // validate!!

    char newline;
    infile.get(newline);
    
    pixel** res = new pixel*[width];
    
    for (int x = 0; x < width; ++x) {
        res[x] = new pixel[height];
        for (int y = 0; y < height; ++y) {
            //valdiare
            infile.read(reinterpret_cast<char*>(&res[x][y].r), 1); // 1??!??!
            infile.read(reinterpret_cast<char*>(&res[x][y].g), 1);
            infile.read(reinterpret_cast<char*>(&res[x][y].b), 1);
        }
    }
    
    infile.close();
    return res;
}

shade** parsePlainPGM(_string filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        throw std::runtime_error( "Error: Could not open file " );
        
    }
    
    _string magic;
    infile >> magic;
    if (magic != "P2") {
        throw std::runtime_error( "Error: Not a valid PGM ASCII file.");
        
    }
    
    int width, height, maxShade;
    infile >> width >> height >> maxShade;
    // validate widht, height, maxShade

    shade** res = new shade*[height];
    
    for (int y = 0; y < height; ++y) {
        res[y] = new shade[width];
        for (int x = 0; x < width; ++x) {
            infile >> res[y][x].v;
        }
    }
    
    infile.close();
    return res;
}

shade** parseRawPGM(_string filename) {
    ifstream infile(filename.c_str(), ios::binary);
    if (!infile) {
        throw std::runtime_error( "Error: Could not open file " );
    }
    
    _string magic;
    infile >> magic;
    if (magic != "P5") {
        throw std::runtime_error( "Error: Not a valid PGM binary file.");
    }
    
    int width, height, maxShade;
    infile >> width >> height >> maxShade;

    // validate widht, height, maxShade
    
    char newline;
    infile.get(newline);
    
    shade** res = new shade*[height];
    for (int y = 0; y < height; ++y) {
        res[y] = new shade[width];
        for (int x = 0; x < width; ++x) {
            infile.read(reinterpret_cast<char*>(&res[y][x].v), 1); // 1??? sizes!
        }
    }
    
    infile.close();
    return res;
}



void test1(){
    pixel** a = parseRawPPM("a.ppm");

    for (int x = 0; x < 640; x++) { 
        for (int y = 0; y < 427; y++) { 
            cout << a[x][y].r << ", ";
            cout << a[x][y].g << ", ";
            cout << a[x][y].b << "\n";
        }
    }

    
    for (int x = 0; x < 2; x++) { 
        delete[] a[x];
    }
    delete[] a;
}

void test2(){
    shade** a = parseRawPGM("a.pgm");
    for (int y = 0; y < 427; y++) { 
        for (int x = 0; x < 640; x++) { 
            cout << a[y][x].v << " ";
        }
        cout << endl;
    }

    
    for (int i = 0; i < 2; i++) { 
        delete[] a[i];
    }
    delete[] a;
}

int main() {

    test2();
    
    return 0;
}
