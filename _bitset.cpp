#include "_bitset.h"
// credit: angeld

_bitset::_bitset(unsigned N)
{
	bucketsCount = N / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	this->N = N;
}

void _bitset::free()
{
	delete[] buckets;//!!!
	bucketsCount = 0;
	buckets = nullptr;
}
void _bitset::copyFrom(const _bitset& other)
{
	buckets = new uint8_t[other.bucketsCount];
	for(size_t i = 0; i < other.bucketsCount; i++)
		buckets[i] = other.buckets[i];
	bucketsCount = other.bucketsCount;
	N = other.N;
}

_bitset::_bitset(const _bitset& other)
{
	copyFrom(other);
}
_bitset& _bitset::operator=(const _bitset& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
_bitset::~_bitset()
{
	free();
}

unsigned _bitset::getBucketIndex(unsigned num) const
{
	return num / elementsInBucket;
}

void _bitset::add(unsigned num)
{
	if (num > N)
		return;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex; 
	buckets[bucketIndex] |= mask;

}

void _bitset::remove(unsigned num)
{

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = ~(1 << bitIndex);
	buckets[bucketIndex] &= mask; 
}

bool _bitset::contains(unsigned num) const
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;

	return buckets[bucketIndex] & mask;
}

void _bitset::print() const
{
	std::cout << '{';
	for (int i = 0; i <= N; i++)
	{
		if (contains(i))
			std::cout << i << " ";
	}

	std::cout << '}' << std::endl;
}
