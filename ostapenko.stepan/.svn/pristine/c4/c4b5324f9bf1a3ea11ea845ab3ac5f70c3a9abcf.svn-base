#include "my_vector.h"
#include <cstring>
#include <iosfwd>
#include <utility>

static std::size_t get_capacity(std::size_t n) {
	std::size_t ans = 1;
	while (ans < n) {
		ans <<= 1;
	}
	return ans;
}

template <typename T>
containers::my_vector<T>::my_vector(): _capacity(1), _size(0), _array((T*)(new char[sizeof(T)])) {}

template <typename T>
containers::my_vector<T>::my_vector(std::size_t n): _capacity(get_capacity(n)), _size(n) {
	_array = (T*)(new char[sizeof(T) * _capacity]);

	for (std::size_t i = 0; i < _size; i++) {
		new(&_array[i]) T();
	}
}

template <typename T>
containers::my_vector<T>::my_vector(const my_vector &other) {
	_capacity = other._capacity;
	_size = other._size;
	_array = (T*)(new char[sizeof(T) * _capacity]);
	for (std::size_t i = 0; i < _size; i++) {
		new(&_array[i]) T(other._array[i]);
	}
}

template <typename T>
containers::my_vector<T>::~my_vector() {
	for (std::size_t i = 0; i < _size; i++) {
		_array[i].~T();
	}
	delete[] (char*)_array;
}

template <typename T>
containers::my_vector<T>& containers::my_vector<T>::operator=(my_vector other) {
	std::swap(_capacity, other._capacity);
	std::swap(_size, other._size);
	std::swap(_array, other._array);
	return *this;
}

template <typename T>
std::size_t containers::my_vector<T>::size() const {
	return _size;
}

template <typename T>
std::size_t containers::my_vector<T>::capacity() const {
	return _capacity;
}

template <typename T>
bool containers::my_vector<T>::empty() const {
	return _size == 0;
}

template <typename T>
void containers::my_vector<T>::reserve(std::size_t n) {
	n = get_capacity(n);
	if (n <= _capacity) {
		return;
	}

	T *new_array = (T*)(new char[sizeof(T) * n]);
	for (std::size_t i = 0; i < _size; i++) {
		new(&new_array[i]) T(_array[i]);
		_array[i].~T();
	}
	delete[] (char*)_array;

	_array = new_array;
	_capacity = n;
}

template <typename T>
void containers::my_vector<T>::resize(std::size_t n) {
	if (n <= _size) {
		for (std::size_t i = n; i < _size; i++) {
			_array[i].~T();
		}
	} else {
		reserve(n);
		for (std::size_t i = _size; i < n; i++) {
			new(&_array[i]) T();
		}
	}
	_size = n;
}

template <typename T>
T& containers::my_vector<T>::operator[](std::size_t index) {
	return _array[index];
}

template <typename T>
T& containers::my_vector<T>::operator[](std::size_t index) const {
	return _array[index];
}

template <typename T>
void containers::my_vector<T>::push_back(const T &t) {
	if (_size == _capacity) {
		reserve(2 * _capacity);
	}
	new(&_array[_size]) T(t);
	_size++;
}

template <typename T>
void containers::my_vector<T>::pop_back() {
	_array[--_size].~T();
}

template <typename T>
void containers::my_vector<T>::clear() {
	for (std::size_t i = 0; i < _size; i++) {
		_array[i].~T();
	}
	_size = 0;
}

template <typename T>
void containers::my_vector<T>::print(std::ostream &out) const {
	if (empty()) {
		return;
	}

	for (std::size_t i = 0; i < _size - 1; i++) {
		out << _array[i] << " ";
	}
	out << _array[_size - 1];
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const containers::my_vector<T> &v) {
	v.print(out);
	return out;
}
