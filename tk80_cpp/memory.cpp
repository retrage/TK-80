//
//  memory.cpp
//  tk80
//

#include "memory.h"

uint8_t tk80_mem::read(uint16_t addr) {
    uint16_t data;
    if (addr>=RAM_BEGIN && addr<=RAM_END) {
        data = array[addr-RAM_BEGIN];
    } else {
        data = 0;
    }
    printf("r %4x: %2x\n", addr, data);
    return data;
}

void tk80_mem::write(uint16_t addr, uint8_t data) {
    if (addr>=RAM_BEGIN && addr<=RAM_END) {
        array[addr-RAM_BEGIN] = data;
        printf("w %4x: %2x\n", addr, data);
    }
}
bool tk80_mem::load(std::string fileName, uint16_t addr) {
    std::ifstream ifs;
    ifs.open(fileName, std::ifstream::in|std::ifstream::binary);
    if (!ifs) {
        printf("Could not open the file.\n");
        return false;
    }
    char c;
    int i = 0;
    while ((c=ifs.get())!=EOF) {
        write(addr+i, (uint8_t)c);
        i++;
    }
    ifs.close();
    return true;
}