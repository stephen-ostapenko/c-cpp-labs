#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(int id, int x, int y, int width, int height):
	Figure(id, x, y), width(width), height(height) {}

void Rectangle::zoom(int factor) {
	width *= factor; height *= factor;
}

void Rectangle::print() const {
	std::cout << "Rectangle " << id
		<< ": x = " << x << " y = " << y
		<< " width = " << width << " height = " << height
		<< std::endl;
}

bool Rectangle::is_inside(int point_x, int point_y) const {
	return abs(x - point_x) * 2 <= width && abs(y - point_y) * 2 <= height;
}