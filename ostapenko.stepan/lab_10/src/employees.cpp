#include "employees.h"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <cstring>

// ============================================================================

Employee::Employee(): _name(nullptr) {}

Employee::~Employee() {
	delete[] _name;
}

Employee* Employee::read_employee(std::istream &in) {
	int32_t type;
	in >> type;

	if (type == DEVELOPER_TYPE) {
		Developer *e = new Developer;
		in >> *e;
		return (Employee*)e;
	} else if (type == SALES_MANAGER_TYPE) {
		SalesManager *e = new SalesManager;
		in >> *e;
		return (Employee*)e;
	} else {
		return nullptr;
	}
}

Employee* Employee::read_employee_from_file(std::ifstream &in) {
	int32_t type;
	in.read((char*)(&type), sizeof(int32_t));

	if (type == DEVELOPER_TYPE) {
		Developer *e = new Developer;
		in >> *e;
		return (Employee*)e;
	} else if (type == SALES_MANAGER_TYPE) {
		SalesManager *e = new SalesManager;
		in >> *e;
		return (Employee*)e;
	} else {
		return nullptr;
	}
}

void Employee::print(std::ostream &out) const {
	out << "Name: " << _name << "\n";
	out << "Base Salary: " << _base_salary << "\n";
}

std::ostream& operator<<(std::ostream &out, const Employee &e) {
	e.print(out);
	return out;
}

void Employee::print_to_file(std::ofstream &out) const {
	std::size_t name_len = strlen(_name);
	out.write(_name, name_len + 1);
	out.write((char*)(&_base_salary), sizeof(int32_t));
}

std::ofstream& operator<<(std::ofstream &out, const Employee &e) {
	e.print_to_file(out);
	return out;
}

void Employee::set_name(std::string &name) {
	delete[] _name;
	_name = new char[name.size() + 1];
	std::strcpy(_name, name.c_str());
}

// ============================================================================

Developer::Developer() {}

int Developer::salary() const {
	int salary = _base_salary;
	if (_has_bonus) { salary += 1000; }
	return salary;
}

std::istream& operator>>(std::istream &in, Developer &d) {
	std::string tmp;
	in >> tmp >> d._base_salary >> d._has_bonus;
	d.set_name(tmp);
	return in;
}

std::ifstream& operator>>(std::ifstream &in, Developer &d) {
	std::string tmp;
	if (!std::getline(in, tmp, '\0')) {
		return in;
	}
	d.set_name(tmp);

	in.read((char*)(&d._base_salary), sizeof(int32_t));
	in.read((char*)(&d._has_bonus), sizeof(bool));
	return in;
}

void Developer::print(std::ostream &out) const {
	out << "Developer\n";
	Employee::print(out);
	out << "Has bonus: ";
	if (_has_bonus) {
		out << "+";
	} else {
		out << "-";
	}
	out << "\n";
}

void Developer::print_to_file(std::ofstream &out) const {
	int32_t type = DEVELOPER_TYPE;
	out.write((char*)(&type), sizeof(int32_t));
	Employee::print_to_file(out);
	out.write((char*)(&_has_bonus), sizeof(bool));
}

// ============================================================================

SalesManager::SalesManager() {}

int SalesManager::salary() const {
	return _base_salary + _sold_nm * _price * 0.01;
}

std::istream& operator>>(std::istream &in, SalesManager &m) {
	std::string tmp;
	in >> tmp >> m._base_salary >> m._sold_nm >> m._price;
	m.set_name(tmp);
	return in;
}

std::ifstream& operator>>(std::ifstream &in, SalesManager &m) {
	std::string tmp;
	if (!std::getline(in, tmp, '\0')) {
		return in;
	}
	m.set_name(tmp);

	in.read((char*)(&m._base_salary), sizeof(int32_t));
	in.read((char*)(&m._sold_nm), sizeof(int32_t));
	in.read((char*)(&m._price), sizeof(int32_t));
	return in;
}

void SalesManager::print(std::ostream &out) const {
	out << "Sales Manager\n";
	Employee::print(out);
	out << "Sold items: " << _sold_nm << "\n";
	out << "Item price: " << _price << "\n";
}

void SalesManager::print_to_file(std::ofstream &out) const {
	int32_t type = SALES_MANAGER_TYPE;
	out.write((char*)(&type), sizeof(int32_t));
	Employee::print_to_file(out);
	out.write((char*)(&_sold_nm), sizeof(int32_t));
	out.write((char*)(&_price), sizeof(int32_t));
}

// ============================================================================

EmployeesArray::EmployeesArray() {}

EmployeesArray::~EmployeesArray() {
	for (std::size_t i = 0; i < _employees.size(); i++) {
		delete _employees[i];
	}
}

void EmployeesArray::add(const Employee *e) {
	_employees.push_back(e);
}

int EmployeesArray::total_salary() const {
	int result = 0;
	for (std::size_t i = 0; i < _employees.size(); i++) {
		result += _employees[i]->salary();
	}
	return result;
}

void EmployeesArray::read_employees_from_file(std::ifstream &in) {
	std::size_t employees_number = 0;
	in.read((char*)(&employees_number), sizeof(int32_t));

	for (std::size_t i = 0; i < employees_number; i++) {
		add(Employee::read_employee_from_file(in));
	}
}

std::ifstream& operator>>(std::ifstream &in, EmployeesArray &arr) {
	arr.read_employees_from_file(in);
	return in;
}

void EmployeesArray::print(std::ostream &out) const {
	for (std::size_t i = 0; i < _employees.size(); i++) {
		out << i + 1 << ". " << *_employees[i];
	}
	out << "== Total salary: " << total_salary() << "\n\n";
}

std::ostream& operator<<(std::ostream &out, const EmployeesArray &arr) {
	arr.print(out);
	return out;
}

void EmployeesArray::print_to_file(std::ofstream &out) const {
	std::size_t employees_number = _employees.size();
	out.write((char*)(&employees_number), sizeof(int32_t));

	for (std::size_t i = 0; i < _employees.size(); i++) {
		out << *_employees[i];
	}
}

std::ofstream& operator<<(std::ofstream &out, const EmployeesArray &arr) {
	arr.print_to_file(out);
	return out;
}