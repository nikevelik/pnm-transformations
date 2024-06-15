#include<iostream>
class CLI : Application{
public: 
    void run();
protected:
    bool parse(const char* cmd);
}

void CLI::parse(const char* cmd){
    if(false){
        help();
        return 1;
    }

    if(false){
        load(filename);
        return 1;
    }

    if(false){
        change(sessionId);
        return 1;
    }

    if(false){
        close();
        return 1;
    }

    if(false){
        sessioninfo(); 
        return 1;  
    }

    if(false){
        undo();  
        return 1; 
    }

    if(false){
        add(filename);
        return 1;
    }

    if(false){
        save();   
        return 1;
    }

    if(false){
        saveAs(filename);   
        return 1; 
    }

    if(false){
        collage(file1, file2, isVertical); 
        return 1;  
    }

    if(false){
        transformation(/*????*/); //!MOD HERE
        return 1;
    }

    if(false){
        std::cout << "exit information displayed";
        return 0;
    }
}

void CMD::run(){
    while(true){
        // ...
        parse(cmd);
    }
}