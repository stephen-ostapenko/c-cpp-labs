#include "employees.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
	EmployeesArray arr;

	std::string c;
	while (std::cin >> c) {
		if (c == "exit") {
			break;
		} else if (c == "add") {
			arr.add(Employee::read_employee(std::cin));
		} else if (c == "list") {
			std::cout << arr;
		} else if (c == "save") {
			std::string file_name;
			std::cin >> file_name;
			std::ofstream out(file_name);
			out << arr;
		} else if (c == "load") {
			std::string file_name;
			std::cin >> file_name;
			std::ifstream in(file_name);
			in >> arr;
		} else {
			std::cout << "unknown command " << c << "\n";
		}

		std::cout.flush();
	}
}