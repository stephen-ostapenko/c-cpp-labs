#include "Circle.hpp"
#include <cstring>
#include <iostream>

Circle::Circle(int id, int x, int y, int radius, const char* new_label):
	Figure(id, x, y), radius(radius) {
	int label_length = strlen(new_label);
	label = new char[label_length + 1];
	strcpy(label, new_label);
}

Circle::~Circle() {
	delete[] label;
}

void Circle::zoom(int factor) {
	radius *= factor;
}

void Circle::print() const {
	std::cout << "Circle " << id
		<< ": x = " << x << " y = " << y
		<< " radius = " << radius << " label = " << label
		<< std::endl;
}

static int square(int t) {
	return t * t;
}

bool Circle::is_inside(int point_x, int point_y) const {
	return square(x - point_x) + square(y - point_y) <= square(radius);
}