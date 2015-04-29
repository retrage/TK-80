CXX=clang++
CXXFLAGS=-std=c++11 -Wall -I.
CXX_DEBUG_FLAGS=-g -O0

.PHONY: debug_cli
debug_cli: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug_cli: tk80_cli

.PHONY: debug_io_test
debug_io_test: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug_io_test: io_test

all: tk80_cli

io_test: tk80_io.o
	$(CXX) $(CXXFLAGS) -o io_test tk80_io.o tk80_keys.o tk80_digs.o tk80_io_element.o tk80_mem.o io_test.cpp

tk80_cli: tk80_cpu.o
	$(CXX) $(CXXFLAGS) -o tk80_cli tk80_mem.o tk80_cpu.o cli.cpp

tk80_cpu.o: tk80_mem.o
	$(CXX) $(CXXFLAGS) -o tk80_cpu.o -c cpu.cpp 

tk80_mem.o:
	$(CXX) $(CXXFLAGS) -o tk80_mem.o -c memory.cpp

tk80_io.o: tk80_mem.o tk80_digs.o tk80_keys.o
	$(CXX) $(CXXFLAGS) -o tk80_io.o -c io.cpp

tk80_keys.o: tk80_io_element.o
	$(CXX) $(CXXFLAGS) -o tk80_keys.o keys.cpp

tk80_digs.o: tk80_io_element.o
	$(CXX) $(CXXFLAGS) -o tk80_digs.o -c digs.cpp

tk80_io_element.o:
	$(CXX) $(CXXFLAGS) -o tk80_io_element.o -c element.cpp

.PHONY: clean
clean:
	rm -f tk80_mem.o tk80_cpu.o tk80_keys.o tk80_digs.o tk80_io_element.o tk80_io.o io_test tk80_cli
