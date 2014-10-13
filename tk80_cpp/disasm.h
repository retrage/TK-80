//
//  disasm.h
//  tk80
//

#ifndef __tk80__disasm__
#define __tk80__disasm__

#include <iostream>
#include "memory.h"

#endif /* defined(__tk80__disasm__) */

#define BASE_ADDR 0x8200

class disasm {
public:
    uint16_t pc;
    tk80_mem mem;
    
    void showasm();
    
private:
    char regnum(uint8_t num);
};
