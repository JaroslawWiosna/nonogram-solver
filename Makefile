# https://stackoverflow.com/a/13673907
CXXFLAGS=-O3 -std=c++17 -Wswitch -Wextra -Wpedantic -Werror
DEBUG_CXXFLAGS=$(CXXFLAGS) -ggdb -O0
LIBS=
PROG=nonogram-solver
DEBUG_PROG=$(PROG)_debug
OBJS= \
	  src/Nonogram.o \
	  src/main.o \
	  src/Line.o \
	  src/Clue.o

.PHONY: all
all: $(PROG) Makefile

# TODO: Does %.cpp capture src/%.cpp?
%.cpp: %.hpp

$(PROG): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LIBS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: debug
debug: Makefile
	$(CXX) $(DEBUG_CXXFLAGS) -o $(DEBUG_PROG) src/Nonogram.cpp src/main.cpp src/Line.cpp src/Clue.cpp $(LIBS)

.PHONY: run-debug
run-debug: debug
	/opt/rh/devtoolset-7/root/usr/bin/gdb --command=.gdbinit ./nonogram-solver_debug

.PHONY: run-debug-valgrind
run-debug-valgrind: debug
	/opt/rh/devtoolset-7/root/usr/bin/valgrind --leak-check=full ./nonogram-solver_debug

.PHONY: format
format: $(wildcard *.cpp) $(wildcard *.hpp) 
	/opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i src/*.cpp 
	/opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i src/*.hpp
	
.PHONY: clean
clean:
	rm -rf src/*.o
	rm -rf $(PROG)
	rm -rf $(DEBUG_PROG)
