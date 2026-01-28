CXX = g++
CXXFLAGS += --std=c++23
CXXFLAGS += -Wall -Wextra -Wpedantic

day$(NUM).exe: day$(NUM).cpp aoc_utils.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

run: day$(NUM).exe
	./day$(NUM).exe

clean:
	rm -v *.exe

.PHONY: run clean
