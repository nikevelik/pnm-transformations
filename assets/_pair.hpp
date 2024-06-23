#pragma once
//credit: GeorgiTerziev02
template<typename T, typename D>
class _pair {
	T first;
	D second;

public:
	_pair() = default;
	_pair(const T& first, const D& second);
	_pair(T&& first, D&& second);
	_pair(const T& first, D&& second);
	_pair(T&& first, const D& second);

	T& getFirst();
	D& getSecond();
	const T& getFirst() const;
	const D& getSecond() const;

	void setFirst(const T& newValue);
	void setFirst(T&& newValue);
	void setSecond(const D& newValue);
	void setSecond(D&& newValue);
};

template<typename T, typename D>
_pair<T,D>::_pair(const T& first, const D& second) : first(first), second(second)
{}


template<typename T, typename D>
_pair<T,D>::_pair(T&& first, D&& second) : first(std::move(first)), second(std::move(second))
{}

template<typename T, typename D>
_pair<T,D>::_pair(const T& first, D&& second) : first(first), second(std::move(second))
{}

template<typename T, typename D>
_pair<T,D>::_pair(T&& first, const D& second) : first(std::move(first)), second(second)
{}

template<typename T, typename D>
T& _pair<T, D>::getFirst() {
	return first;
}

template<typename T, typename D>
D& _pair<T, D>::getSecond() {
	return second;
}

template<typename T, typename D>
const T& _pair<T, D>::getFirst() const {
    return first;
}

template<typename T, typename D>
const D& _pair<T, D>::getSecond() const {
	return second;
}

template<typename T, typename D>
void _pair<T, D>::setFirst(const T& newValue)   {
	first = newValue;
}

template<typename T, typename D>
void _pair<T, D>::setFirst(T&& newValue)   {
	first = std::move(newValue);
}

template<typename T, typename D>
void _pair<T, D>::setSecond(const D& newValue) {
	second = newValue;
}

template<typename T, typename D>
void _pair<T, D>::setSecond(D&& newValue) {
	second = std::move(newValue);
}