#pragma once
#include <iostream>
// credit: angeld

class _bitset
{
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;
	const unsigned elementsInBucket = sizeof(uint8_t) * 8;

	void free();
	void copyFrom(const _bitset& other);

	unsigned getBucketIndex(unsigned num) const;
public:
	_bitset(unsigned n); // [0....n] (n + 1 �����)

	_bitset(const _bitset& other);
	_bitset& operator=(const _bitset& other);
	~_bitset();

	void add(unsigned num);
	void remove(unsigned num);
	bool contains(unsigned num) const; 
	void print() const;

};