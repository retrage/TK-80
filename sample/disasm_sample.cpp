//
//  main.cpp
//  tk80_cpp
//

#include <iostream>
#include "disasm.h"
//#include "cpu.h"
//#include "memory.h"

int main(int argc, const char * argv[]) {
    //cpu upd8080a;
    //tk80_mem mem;
    disasm disas;
    //mem.load("../bin/basic_program", 0x8200);
    disas.mem.load("../bin/basic_program", 0x8200);
    int i;
    /*for(i=0; i<10; i++) {
        
    }*/
    disas.showasm();
    //upd8080a.pc = 0x8200;
    /*
    int i;
    for (i=0; i<9; i++) {
        upd8080a.execute();
    }
    */
    return 0;
}
