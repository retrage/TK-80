//
//  cpu.h
//  tk80
//

#ifndef __tk80__cpu__
#define __tk80__cpu__

#include <iostream>
#include <math.h>
#include "memory.h"

extern memory mem;

#endif /* defined(__tk80__cpu__) */

class cpu {
public:
//    memory mem;
    cpu();
    void execute();
    
private:
    uint16_t pc;
    uint16_t sp;
    uint8_t reg[8];
    void setFlag(uint16_t data);
};