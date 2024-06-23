#pragma once
#include <iostream>
#include <fstream>
class _bitset{
	public: 
		_bitset() = default;
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
		const char* ptr() const ;
		// void flip(unsigned key);
		void flipbyte(unsigned idx);
		unsigned size() const;
	private:
		static const unsigned BITS_IN_BYTE = 8;
		unsigned n = 0;  
		char* data = nullptr;
		static unsigned byteof(unsigned key);
		static unsigned maskfor(unsigned key);
		void copy(const _bitset& o);
		void move(_bitset&& o);
		void destroy();
}; 