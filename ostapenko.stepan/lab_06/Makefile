CXX=g++
CXXFLAGS=-Iinclude -std=c++17 -Wall -Wextra -pedantic

lab_06: src/main.cpp obj/my_vector.o include/*.hpp | obj
	$(CXX) $(CXXFLAGS) -o $@ $< obj/*

obj/%.o: src/%.cpp include/*.hpp | obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj:
	mkdir obj

.PHONY: clean
clean: | obj
	rm -rf lab_06 obj
