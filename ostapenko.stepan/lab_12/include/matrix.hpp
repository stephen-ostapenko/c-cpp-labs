#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <iosfwd>
#include <cstddef>
#include <stdexcept>

class MatrixException : public std::invalid_argument {
public:
	explicit MatrixException(const std::string_view &msg);
};

class Matrix {
public:
	Matrix();
	Matrix(std::size_t r, std::size_t c);
	Matrix(const Matrix &m);
	~Matrix();

	int get(std::size_t i, std::size_t j) const;

	void load(std::ifstream &in);
	static Matrix* load_matrix_from_file(const std::string &fname);
	void print(std::ostream &out) const;

	Matrix& operator=(Matrix m);
	Matrix& operator+=(const Matrix& m);
	Matrix& operator*=(const Matrix& m);

private:
	std::size_t _rows;
	std::size_t _cols;
	int **_ptr;
	int *_data;
};

#endif
