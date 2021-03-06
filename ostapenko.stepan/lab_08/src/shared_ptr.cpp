#include "matrix.hpp"
#include "shared_ptr.hpp"
#include <utility>

shared_ptr::shared_ptr(Matrix* obj): _storage(nullptr) {
	reset(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other): _storage(other._storage) {
	if (_storage != nullptr) {
		_storage->incr();
	}
}

shared_ptr::~shared_ptr() {
	reset();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	std::swap(_storage, other._storage);
	return *this;
}

Matrix* shared_ptr::ptr() const {
	if (_storage == nullptr) {
		return nullptr;
	}
	return _storage->getObject();
}

bool shared_ptr::isNull() const {
	return ptr() == nullptr;
}

void shared_ptr::reset(Matrix* obj) {
	if (_storage != nullptr) {
		_storage->decr();
		if (!_storage->getCounter()) {
			delete _storage;
		}
	}
	
	if (obj == nullptr) {
		_storage = nullptr;
	} else {
		_storage = new Storage(obj);
	}
}

Matrix* shared_ptr::operator->() const {
	return _storage->getObject();
}

Matrix& shared_ptr::operator*() const {
	return *(_storage->getObject());
}

// ==========================================================================

shared_ptr::Storage::Storage(Matrix* mtx): _data(mtx), _ref_count(1) {}

shared_ptr::Storage::~Storage() {
	delete _data;
}

void shared_ptr::Storage::incr() {
	_ref_count++;
}

void shared_ptr::Storage::decr() {
	_ref_count--;
}

int shared_ptr::Storage::getCounter() const {
	return _ref_count;
}

Matrix* shared_ptr::Storage::getObject() const {
	return _data;
}