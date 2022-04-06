#include "matrix.hpp"
#include <cstring>
#include <algorithm>

Matrix::Matrix(std::size_t r, std::size_t c) {
	_rows = r; _cols = c;
	_data = new int[r * c];
	_ptr = new int*[r];

	std::fill(_data, _data + r * c, 0);
	for (std::size_t i = 0; i < r; i++) {
		_ptr[i] = _data + i * c;
	}
}

Matrix::Matrix(const Matrix &m) {
	_rows = m._rows; _cols = m._cols;
	_data = new int[_rows * _cols];
	_ptr = new int*[_rows];

	std::memcpy(_data, m._data, _rows * _cols * sizeof(int));
	for (std::size_t i = 0; i < _rows; i++) {
		_ptr[i] = _data + i * _cols;
	}
}

Matrix::~Matrix() {
	delete[] _data;
	delete[] _ptr;
}

std::size_t Matrix::get_rows() const {
	return _rows;
}

std::size_t Matrix::get_cols() const {
	return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
	_ptr[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
	return _ptr[i][j];
}

void Matrix::print(FILE* f) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols - 1; j++) {
			fprintf(f, "%d ", _ptr[i][j]);
		}
		fprintf(f, "%d\n", _ptr[i][_cols - 1]);
	}
}

Matrix& Matrix::operator=(Matrix m) {
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	std::swap(_data, m._data);
	std::swap(_ptr, m._ptr);

	return *this;
}

bool Matrix::operator==(const Matrix& m) const {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			if (_ptr[i][j] != m._ptr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& m) const {
	return !(operator==(m));
}

Matrix& Matrix::operator+=(const Matrix& m) {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_ptr[i][j] += m._ptr[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < _cols; j++) {
			_ptr[i][j] -= m._ptr[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	*this = *this * m;
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
	Matrix result(*this);
	result.operator+=(m);
	return result;
}

Matrix Matrix::operator-(const Matrix& m) const {
	Matrix result(*this);
	result.operator-=(m);
	return result;
}

Matrix Matrix::operator*(const Matrix& m) const {
	Matrix result(_rows, m._cols);
	for (std::size_t i = 0; i < _rows; i++) {
		for (std::size_t j = 0; j < m._cols; j++) {
			for (std::size_t k = 0; k < _cols; k++) {
				result._ptr[i][j] += _ptr[i][k] * m._ptr[k][j];
			}
		}
	}
	return result;
}