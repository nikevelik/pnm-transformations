#include<iostream>
#include"assets/Bitset.cpp"
#include"assets/String.cpp"
#include"PNM/Pixel.cpp"
#include"PNM/Shade.cpp"
#include"Application/Session.cpp"
#include"Application/Application.cpp"
#include"PNM/AbstractMap.cpp"
#include"PNM/Bitmap.cpp"
using namespace std;


int main(){
    // Bitmap a("parsing/samples/a.pbm");
    // a.serializeplain("parsing/samples/b.pbm");
    // Bitmap b("parsing/samples/b.pbm");
    // b.rotation90();
    // a.rotation90();
    // b.serialize("parsing/samples/c.pbm");
    // a.serialize("parsing/samples/d.pbm");

    // Bitmap x("parsing/samples/x.pbm");
    // x.serializeraw("parsing/samples/y.pbm");


    // Bitmap y("parsing/samples/y.pbm");
    // y.serializeplain("parsing/samples/z.pbm");

    // Bitmap a("parsing/samples/a.pbm");
    // a.rotation180();
    // a.serialize("parsing/samples/b.pbm");
    Application app;
    app.run();
    return 0;
}