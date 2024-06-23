#pragma once
#include"Application.h"
#include<sstream>
void Application::help() const {
    std::cout << "Application help:\n";
    std::cout << "Commands- help, load<file>, change<sessionid>, close, sessioninfo, undo, save, saveas, collage<f1, f2, orientation, outf>, grayscale, monochrome, negative, rotate left, rotate right\n";
}

void Application::load(const String& s){
    sess.pushBack(Session());
    curr = sess.getSize()-1;
    std::cout << "Session with ID: " << sess[curr].getID() << " started\n";
    sess[curr].add(s);
}

void Application::change(int id){
    for(int i = 0; i < sess.getSize(); i++){
        if(sess[i].getID() == id){
            std::cout << "changing session to " << id << "\n"; 
            curr = i;
            return;
        }
    }
}

void Application::add(const String& s){
    sess[curr].add(s);
}

void Application::close(){
    if(curr == -1){
        std::cerr << "cannot close non-existend session\n";
    }
    sess.popAt(curr);
    curr = -1;
    std::cout << "Session Closed\n";
}

void Application::sessioninfo() const {
    if(curr!=-1){
        sess[curr].info();
    }else{
        std::cerr << "cannot display info of non-existend session\n";
    }
}

void Application::undo(){
    if(curr!=-1){
        sess[curr].undo();
    }else{
        std::cerr << "cannot display udno in non-existend session\n";
    }
}

void Application::save(){
    if(curr!=-1){
        sess[curr].save();
    }else{
        std::cerr << "cannot display save in non-existend session\n";
    }
}
void Application::saveas(const String& s){
    if(curr!=-1){
        sess[curr].saveas(s);
    }else{
        std::cerr << "cannot display save in non-existend session\n";
    }
}
void Application::collage(const String&  s1, const String& s2, bool isVertical, const String& s3){
    sess[curr].collage(s1, s2, isVertical, s3);
}
void Application::operate(const Operation& op){
    if(curr!=-1){
        sess[curr].operate(op);
    }else{
        std::cerr << "cannot display operate in non-existend session\n";
    }
}


bool Application::parse(const String& cmd) {
    std::istringstream iss(cmd.c_str());
    String command;
    iss >> command;

    if (command == "help") {
        help();
        return 1;
    }

    if (command == "switch") {
        int sessionId;
        iss >> sessionId;
        change(sessionId);
        return 1;
    }

    if (command == "close") {
        close();
        return 1;
    }


    if (command == "session") {
        sessioninfo();
        return 1;
    }

    if (command == "undo") {
        undo();
        return 1;
    }

    if (command == "quit") {
        std::cout << "exited!";
        return 0;
    }

    if (command == "save") {
        save();
        return 1;
    }

    if (command == "load") {
        String filename;
        iss >> filename;
        load(filename.c_str());
        return 1;
    }

    if (command == "add") {
        String filename;
        iss >> filename;
        add(filename);
        return 1;
    }

    if (command == "saveas") {
        String filename;
        iss >> filename;
        saveas(filename);
        return 1;
    }

    if (command == "grayscale") {
        operate(Operation::Grayscale);
        return 1;
    }

    if (command == "monochrome") {
        operate(Operation::Monochrome);
        return 1;
    }

    if (command == "negative") {
        operate(Operation::Negative);
        return 1;
    }

    if (command == "collage") {
        String orientation, file1, file2, file3;
        iss >> orientation >> file1 >> file2 >> file3;
        bool isVertical = (orientation == "vertical");
        collage(file1, file2, isVertical, file3);
        return 1;
    }


    if (command == "rotate") {
        String direction;
        iss >> direction;
        if (direction == "left") {
            operate(Operation::RotationL);
        } else if (direction == "right") {
            operate(Operation::RotationR);
        }
        return 1;
    }

    std::cerr << "invalid command\n";
    return 1;
}


void Application::run(){
    char buff[1024];
    while(std::cin){
        std::cin.getline(buff, 1024);
        if(!parse(buff)){
            break;
        }
    }
}