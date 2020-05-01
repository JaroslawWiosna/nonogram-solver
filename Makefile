# https://stackoverflow.com/a/13673907
CXXFLAGS=-O3 -std=c++17 -Wswitch -Wextra -Wpedantic -Werror
DEBUG_CXXFLAGS=$(CXXFLAGS) -ggdb -O0
LIBS=
PROG=nonogram-solver
DEBUG_PROG=$(PROG)_debug
OBJS= Nonogram.o main.o Line.o Clue.o

.PHONY: all
all: $(PROG) Makefile

Nonogram.cpp: Nonogram.hpp

%.cpp: %.hpp

$(PROG): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LIBS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: debug
debug: Makefile
	$(CXX) $(DEBUG_CXXFLAGS) -o $(DEBUG_PROG) Nonogram.cpp main.cpp Line.cpp Clue.cpp $(LIBS)

.PHONY: run-debug
run-debug: debug
	/opt/rh/devtoolset-7/root/usr/bin/gdb --command=.gdbinit ./nonogram-solver_debug

.PHONY: run-debug-valgrind
run-debug-valgrind: debug
	/opt/rh/devtoolset-7/root/usr/bin/valgrind --leak-check=full ./nonogram-solver_debug

.PHONY: format
format: $(wildcard *.cpp) $(wildcard *.hpp) 
	/opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i *.cpp 
	/opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i *.hpp
	
.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(PROG)
	rm -rf $(DEBUG_PROG)
