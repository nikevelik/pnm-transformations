#include<iostream>
#include"Application/Session.h"
#include"assets/_bitset.cpp"
#include"assets/_string.cpp"
#include"PNM/Pixel.cpp"
#include"PNM/Shade.cpp"
using namespace std;


int main(){
    Bitmap a("parsing/samples/a.pbm");
    a.serializeplain("parsing/samples/b.pbm");
    Bitmap b("parsing/samples/b.pbm");
    b.rotation90();
    a.rotation270();
    b.serialize("parsing/samples/c.pbm");
    a.serialize("parsing/samples/d.pbm");
    return 0;
}