#pragma once
#include "../assets/_string.h"
#include "../assets/Container.hpp"
#include "../assets/_vector.hpp"
#include "../assets/_pair.hpp"
#include "Operation.h"
#include "../PNM/AbstractMap.h"
#include "../PNM/PNMFactory.h"
#include "../assets/fileformats.h"
class Session{
    public:
        Session();
        void save() noexcept;
        void saveas(const _string& filename) const noexcept;
        void info() const noexcept;
        void add(const _string& filename) noexcept;
        void undo() noexcept;
        void collage(const _string& i1, const _string& i2, bool isVertical, const _string& out) noexcept;
        void operate(const Operation& op) noexcept;
        unsigned getID() const noexcept;
    private:
        static void calc(const Operation& op, int& r, int& g, bool& n) noexcept;
        static void apply(AbstractMap* target, int r, int g, bool n) noexcept;
        unsigned id = 0;
        static unsigned lastId;
        Container<AbstractMap, PNMFactory> img;
        _vector<_pair<_string, unsigned>> files;
        _vector<Operation> operations;
};
