#include "keys.h"

keys::keys(std::uint16_t addr) : io_element::io_element(addr) {
}

void keys::set_data(std::uint8_t data) {
    io_element::set_data(data);    
}

std::uint8_t keys::get_data() {
    return io_element::get_data();
}
void input(std::uint8_t data)
{
    //keys::set_data(data);
   //this.set_data(data);
}
