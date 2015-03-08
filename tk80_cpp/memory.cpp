#include "memory.h"

tk80_mem::tk80_mem() {
}

uint8_t tk80_mem::read(uint16_t addr) {

    uint16_t data;
    
    if(array.find(addr)!=array.end()) {
        data = array[addr];
#ifdef DEBUG
        printf("mem read at %4x: %2x\n", addr, data);
#endif
    } else {
        data = 0x00;
    }

    return data;
}

void tk80_mem::write(uint16_t addr, uint8_t data) {

    array[addr] = data;
#ifdef DEBUG
    printf("mem write at %4x: %2x\n", addr, data);
#endif

}
/*
bool tk80_mem::load(std::string fileName) {
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
*/

bool tk80_mem::load(std::ifstream ifs) {
    
    bool res;

    try {
        if (!ifs)
            throw "Could not open the file\n";
        
        char start_addr[2], end_addr[2];
        ifs.read(start_addr, 2);
        ifs.read(end_addr, 2);

        std::uint16_t addr = (start_addr[0] << 8) | start_addr[1];
        std::uint16_t e_addr = (end_addr[0] << 8) | end_addr[1];

        for(; addr<=e_addr; addr++) {
            try {
                char c;
                if((c=ifs.get())==EOF)
                    throw addr;
                
                write(addr, c);
            } catch(std::uint16_t a) {
                std::cout << "Loading file was stopped at " << a << std::endl;
                break;
            }
        }

        ifs.close();
        res = true;

    } catch (std::string ex_ifs) {
        std::cout << ex_ifs << std::endl;
        res = false;
    }

    return res;

}
