CXX=g++
CXXFLAGS=-std=c++11 -Wall -I.

tk80_cli: tk80_cpu.o
	$(CXX) $(CXXFLAGS) -o tk80_cli tk80_mem.o tk80_cpu.o cli.cpp

tk80_cpu.o: tk80_mem.o
	$(CXX) $(CXXFLAGS) -o tk80_cpu.o -c cpu.cpp 
tk80_mem.o:
	$(CXX) $(CXXFLAGS) -o tk80_mem.o -c memory.cpp

.PHONY: clean
clean:
	rm -f tk80_mem.o tk80_cpu.o tk80_cli
