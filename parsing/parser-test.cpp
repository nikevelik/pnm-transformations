#include<iostream>
#include<fstream>
#include "../_string.cpp"
using namespace std;

struct pixel {
    int r, g, b;
};

pixel** parseNoRawPPM(_string filename) {
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
    pixel** res = new pixel*[2];
    
    for (int x = 0; x < 2; x++) { 
        res[x] = new pixel[2];   
        for (int y = 0; y < 2; y++) {             
            infile >> res[x][y].r >> res[x][y].g >> res[x][y].b;
        }
    }
    infile.close();
    return res;
}


void test1(){
    pixel** a = parseNoRawPPM("test.ppm");

    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            cout << a[x][y].r << " ";
            cout << a[x][y].g << " ";
            cout << a[x][y].b << " ";
            cout << endl; 
        }
        cout << endl; 
    }

    
    for (int x = 0; x < 2; x++) { 
        delete[] a[x];
    }
    delete[] a;
}

int main() {
    test1();

    // std::ifstream infile("test.ppm"); 

    // if (!infile) {
    //     std::cerr << "Failed to open the file." << std::endl;
    //     return 1;
    // }

    // std::string line;
    // while (std::getline(infile, line)) {
    //     std::cout << line << std::endl;
    // }

    // infile.close();


    return 0;
}

