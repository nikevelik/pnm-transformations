#include "../assets/_string.h"
#include "../assets/Container.hpp"
#include "../assets/_vector.hpp"
#include "../assets/_pair.hpp"
#include "../assets/_queue.hpp"
#include "Operation.h"
#include "../PNM/AbstractMap.h"
class Session{
    public:
        void save();
        void saveas(const _string& filename);
        void info();
        void add(const _string& filename);
        void undo();
        void collage(const _string& i1, const _string& i2, bool isVertical, const _string& out);
        void operate(const Operation& op);
    private:
        Container<AbstractMap> img;
        _vector<_pair<_string, unsigned>> filenames;
        _queue<Operation> operations;
};

