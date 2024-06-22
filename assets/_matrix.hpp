#include <utility>
template <class T>
class _matrix{
public:
    _matrix() = delete;
    _matrix(unsigned width, unsigned height, unsigned maxvalue);
    ~_matrix();

    _matrix(const _matrix<T>& o);
    _matrix(_matrix<T>&& o) noexcept;
    _matrix<T>& operator=(const _matrix<T>& o);
    _matrix<T>& operator=(_matrix<T>&& o) noexcept;

    unsigned width() const;
    unsigned height() const;
    unsigned maxvalue() const;

    const T* operator[](unsigned idx) const;
    T* operator[](unsigned idx);
private:
    T** data;
    unsigned w;
    unsigned h;
    unsigned mv;

    void destroy();
    void copy(const _matrix<T>& o);
    void move(_matrix<T>&& o);
};
template <class T>
void _matrix<T>::copy(const _matrix<T>& o){
    w = o.w;
    h = o.h;
    mv = o.mv;
    data = new T*[h];
    for(unsigned y = 0; y < h; y++){
        data[y] = new T[w];
        for(unsigned x = 0; x < w; x++){
            data[y][x] = o.data[y][x];   
        }
    }
}
template <class T>
void _matrix<T>::move(_matrix<T>&& o){
    w = o.w;
    o.w = 0;
    h = o.h;
    o.h = 0;
    mv = o.mv;
    o.mv = 0;
    data = o.data;
    o.data = nullptr;
}
template <class T>
void _matrix<T>::destroy(){
    for(unsigned y = 0; y<h; y++){
        delete[] data[y];
    }
    delete data;
}
template <class T>
_matrix<T>::_matrix(unsigned width, unsigned height, unsigned maxvalue){
    w = width;
    h = height;
    mv = maxvalue;
    data = new T*[h];
    for(unsigned y = 0; y < h; y++){
        data[y] = new T[w]{0};
    }
}
template <class T>
_matrix<T>::~_matrix(){
    destroy();
}
template <class T>
_matrix<T>::_matrix(const _matrix<T>& o){
    copy(o);
}
template <class T>
_matrix<T>::_matrix(_matrix<T>&& o) noexcept{
    move(std::move(o));
}
template <class T>
_matrix<T>& _matrix<T>::operator=(const _matrix<T>& o){
    if(this != &o){
        destroy();
        copy(o);
    }
    return *this;
}
template <class T>
_matrix<T>& _matrix<T>::operator=(_matrix<T>&& o) noexcept{
    if(this != &o){
        destroy();
        move(std::move(o));
    }
    return *this;
}
template <class T>
unsigned _matrix<T>::width() const{
    return w;
}
template <class T>
unsigned _matrix<T>::height() const{
    return h;
}
template <class T>
unsigned _matrix<T>::maxvalue() const{
    return mv;
}
template <class T>
const T* _matrix<T>::operator[](unsigned idx) const{
    return data[idx];
}
template <class T>
T* _matrix<T>::operator[](unsigned idx){
    return data[idx];
}
