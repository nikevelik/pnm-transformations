#include <iostream>
#include <exception>
template <class T>
// credit: Angeld55
class _queue
{
	T* data;
	size_t capacity; 
	size_t size;

	size_t get;
	size_t put;

	void resize();

	void moveFrom(_queue<T>&& other);
	void copyFrom(const _queue<T>& other);
	void free();
public:
	_queue();

	_queue(const _queue<T>& other);
	_queue<T>& operator=(const _queue<T>& other);

	_queue(_queue<T>&& other);
	_queue<T>& operator=(_queue<T>&& other);

	void push(const T& obj);
	void push(T&& obj); 
	void pop();

	const T& peek() const;
	bool isEmpty() const;

	~_queue();

};

template <class T>
_queue<T>::_queue()
{
	capacity = 4;
	data = new T[capacity];
	size = 0;
	get = put = 0;
}

template <class T>
void _queue<T>::push(const T& obj)
{
	if (size == capacity)
		resize();

	data[put] = obj; //operator=
	(++put) %= capacity;
	size++;
}

template <class T>
void _queue<T>::push(T&& obj)
{
	if (size == capacity)
		resize();

	data[put] = std::move(obj); //move operator =
	(++put) %= capacity;
	size++;
}

template <class T>
bool _queue<T>::isEmpty() const
{
	return size == 0;
}


template <class T>
const T& _queue<T>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Empty queue!");

	return data[get];
}

template <class T>
void _queue<T>::pop()
{
	if (isEmpty())
		throw std::logic_error("Empty queue!");
	(++get) %= capacity;
	size--;
}

template <class T>
void _queue<T>::resize()
{
	T* resizedData = new T[capacity * 2];
	for (size_t i = 0; i < size; i++)
	{
		resizedData[i] = data[get];
		(++get) %= capacity;
	}
	capacity *= 2;
	delete[] data;
	data = resizedData;
	get = 0;
	put = size;
}


template <class T>
void _queue<T>::copyFrom(const _queue<T>& other)
{
	data = new T[other.capacity];
	for (int i = 0; i < other.capacity; i++)
		data[i] = other.data[i];

	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;

}

template <class T>
void _queue<T>::moveFrom(_queue<T>&& other)
{
	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;

	other.size = other.capacity = 0;
}

template <class T>
void _queue<T>::free()
{
	delete[] data;
}

template <class T>
_queue<T>::_queue(const _queue<T>& other)
{
	copyFrom(other);

}

template <class T>
_queue<T>& _queue<T>::operator=(const _queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
_queue<T>::_queue(_queue<T>&& other)
{
	moveFrom(std::move(other));
}

template <class T>
_queue<T>& _queue<T>::operator=(_queue<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


template <class T>
_queue<T>::~_queue()
{
	free();
}