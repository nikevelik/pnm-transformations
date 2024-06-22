// #pragma once
#include <iostream>
#include <fstream>
class _bitset{
	public: 
		_bitset() = delete;
		_bitset(unsigned size);
		~_bitset();
		_bitset(const _bitset& o);
		_bitset(_bitset&& o) noexcept;
		_bitset& operator=(const _bitset& o);
		_bitset& operator=(_bitset&& o) noexcept;
		void set(unsigned key);
		void clear(unsigned key);
		bool read(unsigned key) const;
		char* ptr();
		// const char operator[](unsigned idx) const;
		// char operator[](unsigned idx);
	private:
		static const unsigned BITS_IN_BYTE = 8;
		unsigned n = 0;  
		char* data;
		static unsigned byteof(unsigned key);
		static unsigned maskfor(unsigned key);
		void copy(const _bitset& o);
		void move(_bitset&& o);
		void destroy();
}; 

_bitset::_bitset(unsigned size){
	n = size;
	data = new char[n];
}

void _bitset::copy(const _bitset& o){
	n = o.n;
	data = new char[n];
	for(int i = 0; i < n; i++){
		data[i] = o.data[i];
	}
}

void _bitset::move(_bitset&& o){
	n = o.n;
	o.n = 0;
	data = o.data;
	o.data = nullptr;
}

void _bitset::destroy(){
	n = 0;
	delete[] data;
	data = nullptr;
}

_bitset::~_bitset(){
	destroy();
}

_bitset& _bitset::operator=(const _bitset& o){
	if(this != &o){
		destroy();
		copy(o);
	}
	return *this;
}

_bitset&  _bitset::operator=(_bitset&& o) noexcept {
	if(this != &o){
		destroy();
		move(std::move(o));
	}
	return *this;
}

_bitset::_bitset(const _bitset& o){
	copy(o);
}

_bitset::_bitset(_bitset&& o) noexcept {
	move(std::move(o));
}

unsigned _bitset::byteof(unsigned key){
    return key / BITS_IN_BYTE;
}

unsigned _bitset::maskfor(unsigned key){
    return 1 << (key % BITS_IN_BYTE);
}

void _bitset::set(unsigned key){
    data[byteof(key)] |= maskfor(key);
}

void _bitset::clear(unsigned key){
    data[byteof(key)] &= ~maskfor(key);
}

bool _bitset::read(unsigned key) const {
    return (bool) (maskfor(key) & data[byteof(key)]);
}

char* _bitset::ptr(){
	return data;
}