#include "my_vector.hpp"
#include <algorithm>
#include <cstring>

MyVector::MyVector() {
  _sz = 0; _cp = 2;
  _data = new int[_cp];
}

MyVector::MyVector(std::size_t init_capacity) {
  _sz = 0; _cp = init_capacity;
  _data = new int[_cp];
}

MyVector::MyVector(const MyVector &init_vector) {
  _sz = init_vector._sz; _cp = init_vector._cp;
  _data = new int[_cp];
  std::memcpy(_data, init_vector._data, _sz * sizeof(int));
}

MyVector::~MyVector() {
  delete[] _data;
}

void MyVector::set(std::size_t index, int value) {
  _data[index] = value;
}

int MyVector::get(std::size_t index) {
  return _data[index];
}

std::size_t MyVector::size() {
  return _sz;
}

std::size_t MyVector::capacity() {
  return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
  if (new_capacity <= _cp) {
    return;
  }

  int *new_data = new int[new_capacity];
  std::memcpy(new_data, _data, _sz * sizeof(int));
  delete[] _data;

  _data = new_data;
  _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
  if (_cp < new_size) {
    reserve(std::max(_cp * 2, new_size));
  }

  if (new_size > _sz) {
    std::fill(_data + _sz, _data + new_size, 0);
  }
  _sz = new_size;
}

void MyVector::push_back(int value) {
  if (_cp == _sz) {
    reserve(_cp * 2);
  }
  _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
  push_back(value);
  for (std::size_t i = _sz - 1; i > index; i--) {
    std::swap(_data[i], _data[i - 1]);
  }
}

void MyVector::erase(std::size_t index) {
  for (std::size_t i = index; i + 1 < _sz; i++) {
    std::swap(_data[i], _data[i + 1]);
  }
  _sz--;
}

MyVector& MyVector::operator=(MyVector assign_from) {
  std::swap(_sz, assign_from._sz);
  std::swap(_cp, assign_from._cp);
  std::swap(_data, assign_from._data);
  return *this;
}