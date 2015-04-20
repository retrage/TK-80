#include "element.h"

io_element::io_element(std::uint16_t addr) {
    this->addr = addr;
    this->data = 0x00;
}

std::uint16_t io_element::get_addr() {
    return this->addr;
}

void io_element::set_data(std::uint8_t data) {
    this->data = data;
}

std::uint8_t io_element::get_data() {
    return this->data;
}
