#pragma once
#include <utility>
#include <exception>
// credit: oop course

template<typename T>
class _vector {
private:
	static const short INITIAL_CAPACITY = 4;
	static const short RESIZE_COEF = 2; 

	T* data = nullptr;
	size_t size = 0;
	size_t capacity;
	
	void resize(size_t newCapacity);

	void assertIndex(size_t index) const;
	void upsizeIfNeeded();
	void downsizeIfNeeded();
public:

	_vector();
	_vector(size_t capacity);
	_vector(const _vector<T>& other);
	_vector(_vector<T>&& other);
	_vector<T>& operator=(const _vector<T>& other);
	_vector<T>& operator=(_vector<T>&& other);
	~_vector();

	size_t getSize() const;
	size_t getCapacity() const;

	
	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, size_t index);
	void pushAt(T&& element, size_t index);
	T popBack();
	T popAt(size_t index);

	bool empty() const;
	void clear();
	void shrinkToFit();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

private:
	void move(_vector<T>&& other);
	void copyFrom(const _vector<T>& other);
	void free();
};


template<typename T>
_vector<T>::_vector() : _vector(INITIAL_CAPACITY) { }


template<typename T>
_vector<T>::_vector(size_t capacity) : capacity(capacity) {
	data = new T[capacity];
}

template<typename T>
_vector<T>::_vector(const _vector<T>& other) {
	copyFrom(other);
}
template<typename T>
_vector<T>::_vector(_vector<T>&& other) {
	move(std::move(other));
}

template<typename T>
_vector<T>& _vector<T>::operator=(const _vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
_vector<T>& _vector<T>::operator=(_vector<T>&& other) {
	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}

template<typename T>
_vector<T>::~_vector() {
	free();
}

template<typename T>
void _vector<T>::assertIndex(size_t index) const {
	if (index >= size) {
		throw std::exception("Out of range");
	}
}

template<typename T>
void _vector<T>::upsizeIfNeeded() {
	if (size == capacity) {
		resize(capacity * RESIZE_COEF);
	}
}

template<typename T>
void _vector<T>::downsizeIfNeeded() {
	if (size * RESIZE_COEF * RESIZE_COEF <= capacity) {
		resize(capacity / RESIZE_COEF);
	}
}

template<typename T>
void _vector<T>::resize(size_t newCapacity) {
	capacity = newCapacity;
	T* temp = new T[capacity];

	
	if (size > newCapacity) {
		size = newCapacity;
	}

	for (size_t i = 0; i < size; i++) {
		temp[i] = std::move(data[i]);
	}

	delete[] data;
	data = temp;
}

template<typename T>
size_t _vector<T>::getSize() const {
	return size;
}

template<typename T>
size_t _vector<T>::getCapacity() const {
	return capacity;
}

template<typename T>
void _vector<T>::pushBack(const T& element) {
	upsizeIfNeeded();
	data[size++] = element;
}

template<typename T>
void _vector<T>::pushBack(T&& element) {
	upsizeIfNeeded();
	data[size++] = std::move(element);
}

template<typename T>
void _vector<T>::pushAt(const T& element, size_t index) {
	assertIndex(index);
	upsizeIfNeeded();

	for (size_t i = size; i > index; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[index] = element;
	size++;
}

template<typename T>
void _vector<T>::pushAt(T&& element, size_t index) {
	assertIndex(index);
	upsizeIfNeeded();

	for (size_t i = size; i > index; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[index] = std::move(element);
	size++;
}

template<typename T>
T _vector<T>::popBack() {
	if (empty()) {
		throw std::exception("_vector is empty");
	}
	
	
	
	return data[--size];
}

template<typename T>
T _vector<T>::popAt(size_t index) {
	assertIndex(index);
	
	downsizeIfNeeded();

	T temp = data[index];
	size--;
	for (size_t i = index; i < size; i++) {
		data[i] = std::move(data[i + 1]);
	}

	return temp;
}

template<typename T>
bool _vector<T>::empty() const {
	return size == 0;
}

template<typename T>
void _vector<T>::clear() {
	size = 0;
}

template<typename T>
void _vector<T>::shrinkToFit() {
	resize(size);
}

template<typename T>
T& _vector<T>::operator[](size_t index) {
	assertIndex(index);

	return data[index];
}

template<typename T>
const T& _vector<T>::operator[](size_t index) const {
	assertIndex(index);

	return data[index];
}

template<typename T>
void _vector<T>::move(_vector<T>&& other) {
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

template<typename T>
void _vector<T>::copyFrom(const _vector<T>& other) {
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (size_t i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
}

template<typename T>
void _vector<T>::free() {
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}