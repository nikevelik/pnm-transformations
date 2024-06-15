class Application{
public:
    void help() const;
    void load(MyString s);
    void change(int id);
    void close();
    void sessioninfo() const ;
    void undo();
    void save();
    void saveAs(MyString s);
    void collage(MyString s1, MyString s2, bool isVertical);
    void transformation(/**???*/); //! MOD HERE
private: 
    Vector<Session> sess;
    int curr = -1;
}

void Application::help() const {
    std::cout << "help information displayed"; //! MOD HERE
}

void Application::load(MyString s){
    sess.push(s);
}

void Application::change(int id){
    // find corresspondend session
    for(int i = 0; i < sess.getSize(); i++){
        if(sess[i].getID() == id){
            std::cout << "changing session to " << i; //!MOD HERE
            curr = i;
            return;
        }
    }
}

void Application::close(){
    if(curr == -1){
        std::cout << "cannot close unexistend session"; //!MOD HERE
    }
    std::cout << "Closing session " << curr; //!MOD HERE
    sess.splice(curr);
    curr = -1;
}

void Application::sessioninfo() const {
    sess[curr].info();
}

void Application::undo(){
    sess[curr].undo();
}

void Application::save(){
    sess[curr].save();
}
void Application::saveAs(MyString s){
    sess[curr].saveAs(s);
}
void Application::collage(MyString s1, MyString s2, bool isVertical){
    sess[curr].collage(s1, s2, isVertical);
}
void Application::transformation(/**???*/){//! MOD HERE
    sess[curr].transformation(/**???*/)
}