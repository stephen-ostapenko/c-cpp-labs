#pragma once

class Figure {
public:
    Figure(int id, int x, int y);
    virtual ~Figure() = default;

    virtual void print() const = 0;
    virtual bool is_inside(int point_x, int point_y) const = 0;
    virtual void zoom(int factor) = 0;
    virtual void move(int new_x, int new_y) final;
    virtual int get_id() final;

protected:
    int id;
    int x;
    int y;
};