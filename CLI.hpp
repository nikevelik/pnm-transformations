#include<iostream>
class CLI{
public: 
    void run();
protected:
    void help();
    void load(MyString s);
    void change(MyString s);
    void close();
    void sessioninfo();
    void undo();
    void add(MyString s);
    void save();
    void saveAs(MyString s);
    void collage(MyString s1, MyString s2, bool isVertical);
    void transformation(/**???*/);
    void parse(const char* cmd);
}