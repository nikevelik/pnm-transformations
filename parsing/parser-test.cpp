#include<iostream>
#include<fstream>
#include <stdexcept>
#include "../assets/_string.cpp"
#include "../assets/_bitset.cpp"

using namespace std;

struct pixel {
    int r, g, b;
};

struct shade{
    int v;
};

pixel** deserializePlainPPM(_string filename) {
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

pixel** deserializeRawPPM(_string filename) {
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

shade** deserializePlainPGM(_string filename) {
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

shade** deserializeRawPGM(_string filename) {
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

_bitset* deserializePlainPBM(_string filename, int &width, int &height) {
    ifstream infile(filename.c_str());
    if (!infile) {
        throw std::runtime_error("Error: Could not open file ");
    }
    
    _string magic;
    infile >> magic;
    if (magic != "P1") {
        throw std::runtime_error("Error: Not a valid PBM ASCII file.");
    }
    
    infile >> width >> height;
    // cout << width << " " << height;
    //validate!

    int rowSize = (width + 7) / 8;

    _bitset* res = new _bitset(rowSize*height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < rowSize; ++x) {
            for(int i = 7; i>=0; i--){
                bool pixel;
                infile >> pixel;
                if(pixel){
                    res->set((y * rowSize + x)*8 + i);
                }
            }
        }
    }
    
    infile.close();
    return res;
}

_bitset* deserializeRawPBM(_string filename, int &width, int &height) {
    ifstream infile(filename.c_str(), ios::binary);
    if (!infile) {
        throw("Error: Could not open file ");
    }
    
    _string magic;
    infile >> magic;
    if (magic != "P4") {
        throw("Error: Not a valid PBM binary file.");
    }
    
    infile >> width >> height;
    // validate!!!!

    char newline;
    infile.get(newline);
    
    int k = (width + 7) / 8;
    _bitset* res = new _bitset(height * k);
    
    infile.read(res->ptr(), height * k);
    
    infile.close();
    return res;
}




void test1(){
    pixel** a = deserializeRawPPM("a.ppm");
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
    shade** a = deserializeRawPGM("a.pgm");
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

void test3(){
    int width, height;
    _bitset* a = deserializePlainPBM("test.pbm", width, height);
    cout << "P1" << "\n" << width << " " << height << endl;
    int rowSize = (width + 7) / 8;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < rowSize; ++x) {
            for(int i = 7; i>=0; i--){
                cout << a->read((y * rowSize + x)*8 + i) << "";
            }
        }
        cout << "\n";
    }
}



void serializePlainPPM(const _string& filename, pixel** pixels, int width, int height, int maxColor) {
    std::ofstream outfile(filename.c_str());
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing");
    }

    // Write the PPM header
    outfile << "P3\n";
    outfile << width << " " << height << "\n";
    outfile << maxColor << "\n";

    // Write the pixel data
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            outfile << pixels[x][y].r << " " << pixels[x][y].g << " " << pixels[x][y].b << "\n";
        }
    }

    outfile.close();
}


void serializeRawPPM(const std::string& filename, pixel** image, int width, int height, int maxColor) {
    ofstream outfile(filename.c_str(), ios::binary);
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    // Write the magic number
    outfile << "P6\n";

    // Write the width, height, and maximum color value
    outfile << width << " " << height << "\n";
    outfile << maxColor << "\n";
    
    // Write the pixel data
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            outfile.write(reinterpret_cast<char*>(&image[x][y].r), 1);
            outfile.write(reinterpret_cast<char*>(&image[x][y].g), 1);
            outfile.write(reinterpret_cast<char*>(&image[x][y].b), 1);
        }
    }
    
    outfile.close();
}


void serializePlainPGM(_string filename, shade** data, int width, int height, int maxShade = 255) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }
    
    // Write magic number and header information
    outfile << "P2" << endl;
    outfile << width << " " << height << endl;
    outfile << maxShade << endl;
    
    // Write pixel data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            outfile << data[y][x].v << " ";
        }
        outfile << endl;
    }
    
    outfile.close();
}


void serializeRawPGM(_string filename, shade** data, int width, int height, int maxShade = 255) {
    ofstream outfile(filename.c_str(), ios::binary);
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }
    
    // Write the PGM header
    outfile << "P5\n";
    outfile << width << " " << height << "\n";
    outfile << maxShade << "\n";  // Assuming maxShade is always 255 for PGM P5 format
    
    // Write the pixel data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            outfile.write(reinterpret_cast<char*>(&data[y][x].v), 1);
        }
    }
    
    outfile.close();
}


void serializePlainPBM(const _string& filename, _bitset* bitmap, int width, int height) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    outfile << "P1" << endl;
    outfile << width << " " << height << endl;

    int rowSize = (width + 7) / 8;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < rowSize; ++x) {
            for(int i = 7; i >= 0; i--) {
                int index = (y * rowSize + x) * 8 + i;
                outfile << bitmap->read(index) << " ";
            }
        }
        outfile << endl;
    }

    outfile.close();
}

void serializeRawPBM(const _string& filename, _bitset* data, int width, int height) {
    ofstream outfile(filename.c_str(), ios::binary);
    if (!outfile) {
        throw("Error: Could not create file ");
    }

    // Write the magic number "P4"
    outfile << "P4\n";

    // Write width and height
    outfile << width << " " << height << "\n";

    // Calculate bytes per row (each byte represents 8 pixels)
    int k = (width + 7) / 8;

    outfile.write(data->ptr(), k*height);

    outfile.close();
}

int main() {

    int w, h;
    _bitset* a = deserializeRawPBM("samples/a.pbm", w, h);
    serializeRawPBM("samples/A.pbm", a, w, h);

    return 0;
}

