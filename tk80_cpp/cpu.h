#include <iostream>
#include <math.h>
#include <cstdint>

#include "memory.h"

class tk80_cpu {
public:
    tk80_mem mem;

    tk80_cpu(std::uint16_t pc_addr);
    void execute();

    uint16_t getpc();
    uint16_t getsp();
    uint8_t getreg(int index);
    
private:
    uint16_t pc;
    uint16_t sp;
    uint8_t reg[8];
    void setFlag(uint16_t data);

};
