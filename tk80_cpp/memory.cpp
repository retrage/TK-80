//
//  memory.cpp
//  tk80
//

#include "memory.h"

uint8_t memory::read(uint16_t addr) {
    uint16_t data;
    if (addr>=RAM_BEGIN && addr<=RAM_END) {
        data = array[addr-RAM_BEGIN];
    } else {
        data = 0;
    }
    printf("r %4x: %2x\n", addr, data);
    return data;
}

void memory::write(uint16_t addr, uint8_t data) {
    if (addr>=RAM_BEGIN && addr<=RAM_END) {
        array[addr-RAM_BEGIN] = data;
        printf("w %4x: %2x\n", addr, data);
    }
}
bool memory::load(char *fileName, uint16_t addr) {
    FILE *fp;
    if ((fp = fopen(fileName, "rb"))==NULL) {
        printf("no file.\n");
        return false;
    }
    char c;
    int i = 0;
    while ((c=getc(fp))!=EOF) {
        write(addr+i, (uint8_t)c);
        i++;
    }
    fclose(fp);
    return true;
}