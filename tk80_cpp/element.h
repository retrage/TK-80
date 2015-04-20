#pragma once
#include <cstdint>

class io_element {
    public:
        io_element() { this->addr = 0x0000; this->data = 0x00; };
        io_element(std::uint16_t addr);

        std::uint16_t get_addr();

        void set_data(std::uint8_t data);
        std::uint8_t get_data();
    
    private:
        std::uint16_t addr;
        std::uint8_t data;
};
