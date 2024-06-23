#include<iostream>
#include"Application/Session.h"
#include"assets/_bitset.cpp"
#include"assets/_string.cpp"
#include"PNM/Pixel.cpp"
#include"PNM/Shade.cpp"
using namespace std;


// raw -> plain -> raw
int main(){
    // cout << _bitset::maskfor(0) << " " << _bitset::maskfor(7);
    Bitmap b("parsing/samples/a.pbm"); //deserialize plain
    b.rotation90();
    b.serialize("parsing/samples/b.pbm"); //serialize raw
    return 0;
}