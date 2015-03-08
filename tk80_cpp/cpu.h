#include <iostream>
#include <math.h>

class cpu {
public:
    cpu();
    void execute();
    
private:
    uint16_t pc;
    uint16_t sp;
    uint8_t reg[8];
    void setFlag(uint16_t data);
};
