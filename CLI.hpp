#include<iostream>
class CLI : Application{
public: 
    void run();
protected:
    bool parse(const char* cmd);
}
