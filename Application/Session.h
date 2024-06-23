#pragma once
#include "../assets/_string.h"
#include "../assets/Container.hpp"
#include "../assets/_vector.hpp"
#include "../assets/_pair.hpp"
// #include "../assets/_queue.hpp"
#include "Operation.h"
#include "../PNM/AbstractMap.h"
#include "../PNM/PNMFactory.h"
#include "../assets/fileformats.h"
class Session{
    public:
        Session();
        void save();
        void saveas(const _string& filename);
        void info();
        void add(const _string& filename);
        void undo();
        void collage(const _string& i1, const _string& i2, bool isVertical, const _string& out);
        void operate(const Operation& op);
    private:
        static void calc(const Operation& op, int& r, int& g, bool& n);
        static void apply(AbstractMap* target, int r, int g, bool n);
        unsigned id = 0;
        static unsigned lastId;
        Container<AbstractMap, PNMFactory> img;
        _vector<_pair<_string, unsigned>> files;
        _vector<Operation> operations;
};

void Session::calc(const Operation& op, int& r, int& g, bool& n){
    switch (op){
        case Operation::Grayscale:
            g = ((g == 2) ? 2 : 1);
            break;
        case Operation::Monochrome:
            g = 2;
            break;
        case Operation::Negative:
            n = !n;
            break;
        case Operation::RotationL:
            r = (r + 1)%4;
            break;
        case Operation::RotationR:
            r = (r + 3)%4;
            break;
    }
}

void Session::apply(AbstractMap* target, int r, int g, bool n){
    if(g == 2){
        target->monochrome();
    }else if(g == 1){
        target->grayscale();
    }
    if(r == 1){
        target->rotation90();
    }else if(r == 2){
        target->rotation180();
    }else if(r == 3){
        target->rotation270();
    }
    if(n){
        target->negative();
    }
}

unsigned Session::lastId = 0;
Session::Session(){
    id = lastId++;
}

void Session::info(){
    std::cout << "sessionID: " << id << "\nadded images: ";
    for(unsigned i = 0; i < files.getSize(); i++){
        std::cout << files[i].getFirst() << " ";
    }
    std::cout << "\nunsaved operations:";
    for(unsigned i = 0; i < operations.getSize(); i++){
        std::cout << operations[i] << " ";
    }
}

void Session::add(const _string& filename){
    if(isValidFileType(filename)){
        for(unsigned i = 0; i <files.getSize(); i++){
            if(files[i].getFirst() == filename){
                std::cout << "file is already in the session";
                return;
            }
        }
        for(unsigned i = 0; i <img.getSize(); i++){
            if(img[i]->getFilename() == filename){
                std::cout << "file is already in the session";
                return;
            }
        }
        files.pushBack(_pair<_string, unsigned>(filename, operations.getSize()));
    }else{
        std::cerr << "file name is not valid";
        return;
    }
}

void Session::undo(){
    if(operations.getSize()==0 && files.getSize() == 1 && img.getSize() == 0){
        std::cout << "nothing to undo\n";
        return; // session just started
    }
    if(files.getSize()>0 && files[files.getSize()-1].getSecond()==operations.getSize()){
        files.popBack();
        std::cout << "adding file undo\n";
    }else if(operations.getSize()>0){
        operations.popBack();
        std::cout << "last transformation undone\n";
    }else{
        std::cout << "nothing to undo\n";
    }
}

void Session::operate(const Operation& op){
    operations.pushBack(op);
    std::cout << "operation added to list\n";
}

void Session::save(){
    unsigned oldSize = img.getSize();
    for(int i = 0; i < files.getSize(); i++){
        img.add(files[i].getFirst().c_str());
    }
    int j = files.getSize()-1;
    int r = 0;
    int g = 0;
    bool n = 0;
    for(int i = operations.getSize()-1; i>=0; i--){
        calc(operations[i], r, g, n);
        if(r == 0 && g == 0 && n ==0){
            continue;
        }
        while(j>=0 && files[j].getSecond()>i){
            j--;
        }
        while(j>= 0 && files[j].getSecond()==i){
            apply(img[oldSize+j], r, g, n);
            img[oldSize+j]->serialize();
            j--;
        }
    }
    operations.clear();
    files.clear();
    for(int i = 0; i < oldSize; i++){
        apply(img[i], r, g, n);
        img[i]->serialize();
    }
    std::cout << "successfully saved!\n";
}

void Session::saveas(const _string& filename){
    int r = 0;
    int g = 0;
    bool n = 0;
    AbstractMap* res;
    try{
        res = PNMFactory::create(filename.c_str());
    }catch(std::exception& e){
        std::cerr << "Could not perform saveas. Err: \"" << e.what() <<"\"\n";
    }
    for(int i = operations.getSize()-1; i>=0; i--){
        calc(operations[i], r, g, n);
    }
    try{
        apply(res, r, g, n);
        res->serialize(filename);
    }catch(std::exception& e){
        std::cerr << "Could not perform saveas. Err: \"" << e.what() <<"\"\n";
    }
}