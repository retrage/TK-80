#pragma once
#include "element.h"

class dig : public io_element {
    public:
        dig() {};
        dig(std::uint16_t addr);
        char get_dig();
        virtual void set_data(std::uint8_t data);
        virtual std::uint8_t get_data();
};
