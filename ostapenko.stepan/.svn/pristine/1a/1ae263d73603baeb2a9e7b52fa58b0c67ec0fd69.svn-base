#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char* new_label);
    ~Circle() override;

    void zoom(int factor) override;
    void print() const override;
    bool is_inside(int point_x, int point_y) const override;

protected:
	int radius;
	char* label;
};