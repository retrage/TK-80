//
//  memory.h
//  tk80
//

#ifndef __tk80__memory__
#define __tk80__memory__

#include <iostream>
#include <fstream>

#endif /* defined(__tk80__memory__) */

#define RAM_BEGIN 0x0000
#define RAM_END 0xffff

class tk80_mem {
public:
    uint8_t array[RAM_END-RAM_BEGIN+1];
    
    uint8_t read(uint16_t addr);
    bool write(uint16_t addr, uint8_t data);
    bool load(std::string fileName, uint16_t addr);
};
