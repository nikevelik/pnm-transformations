#include<iostream>
#include<fstream>
#include "../_string.cpp"
using namespace std;

struct pixel {
    int r, g, b;
};

pixel** parsePlainPPM(_string filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        return nullptr;
    }
    _string magic;
    infile >> magic;
    if (magic != "P3") {
        std::cerr << "Error: Not a valid PPM ASCII file." << std::endl;
    }
    int width, height, maxColor;
    infile >> width >> height;
    infile >> maxColor;
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
        cerr << "Error: Could not open file " << filename << endl;
        return nullptr;
    }
    _string magic;
    infile >> magic;
    if (magic != "P6") {
        cerr << "Error: Not a valid PPM binary file." << endl;
        return nullptr;
    }
    int width, height, maxColor;
    infile >> width >> height;
    infile >> maxColor;
        
    char newline;
    infile.get(newline);
    
    pixel** res = new pixel*[width];
    
    for (int x = 0; x < width; ++x) {
        res[x] = new pixel[height];
        for (int y = 0; y < height; ++y) {
            infile.read(reinterpret_cast<char*>(&res[x][y].r), 1);
            infile.read(reinterpret_cast<char*>(&res[x][y].g), 1);
            infile.read(reinterpret_cast<char*>(&res[x][y].b), 1);
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

int main() {

    test1();
    
    return 0;
}
