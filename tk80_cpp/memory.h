#include <iostream>
#include <fstream>
#include <cstdint>
#include <map>

//static const size_t RAM_SIZE = 0x10000;

class tk80_mem {
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);
        bool load(std::ifstream fis);
        tk80_mem();

    private:
        std::map<std::uint16_t, std::uint8_t> array;
};
