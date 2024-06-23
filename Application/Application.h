#pragma once
#include "../assets/_vector.hpp"
#include "../assets/_string.h"
#include "Operation.h"
#include "Session.h"
#include<iostream>
#include<sstream>
class Application{
public:
    void help() const;
    void load(const _string& s);
    void change(int id);
    void close();
    void sessioninfo() const ;
    void undo();
    void save();
    void saveas(const _string& s);
    void collage(const _string&  s1, const _string& s2, bool isVertical, const _string& s3);
    void operate(const Operation& op);
    void run();
    void add(const _string& s);
private: 
    bool parse(const _string& cmd);
    _vector<Session> sess;
    int curr = -1;
};
