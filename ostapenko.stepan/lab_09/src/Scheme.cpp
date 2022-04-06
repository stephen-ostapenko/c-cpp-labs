#include "Scheme.hpp"
#include <utility>

Scheme::Scheme(int capacity):
	_sz(0), _cp(capacity), _figures(new Figure*[capacity]) {}

Scheme::~Scheme() {
	for (std::size_t i = 0; i < _sz; i++) {
		delete _figures[i];
	}
	delete[] _figures;
}

void Scheme::push_back_figure(Figure* fg) {
	_figures[_sz++] = fg;
}

std::size_t Scheme::find_figure_index_by_id(int id) {
	for (std::size_t i = 0; i < _sz; i++) {
		if (_figures[i]->get_id() == id) {
			return i;
		}
	}
	return _sz;
}

void Scheme::remove_figure(int id) {
	std::size_t index = find_figure_index_by_id(id);
	if (index == _sz) {
		return;
	}

	for (std::size_t i = index + 1; i < _sz; i++) {
		std::swap(_figures[i - 1], _figures[i]);
	}
	delete _figures[--_sz];
}

void Scheme::print_all_figures() {
	for (std::size_t i = 0; i < _sz; i++) {
		_figures[i]->print();
	}
}

void Scheme::zoom_figure(int id, int factor) {
	std::size_t index = find_figure_index_by_id(id);
	if (index == _sz) {
		return;
	}

	_figures[index]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
	for (std::size_t i = 0; i < _sz; i++) {
		if (_figures[i]->is_inside(x, y)) {
			return _figures[i];
		}
	}
	return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
	std::size_t index = find_figure_index_by_id(id);
	if (index == _sz) {
		return;
	}

	_figures[index]->move(new_x, new_y);
}