#include "digs.h"

dig::dig(std::uint16_t addr) : io_element::io_element(addr) {
}

char dig::get_dig() {
    char res = '0';

    switch (this->get_data()) {
        case 0x5c:
            res = '0';
            break;
        case 0x06:
            res = '1';
            break;
        case 0x5b:
            res = '2';
            break;
        case 0x4f:
            res = '3';
            break;
        case 0x66:
            res = '4';
            break;
        case 0x6d:
            res = '5';
            break;
        case 0x7d:
            res = '6';
            break;
        case 0x27:
            res = '7';
            break;
        case 0x7f:
            res = '8';
            break;
        case 0x6f:
            res = '9';
            break;
        case 0x77:
            res = 'a';
            break;
        case 0x7c:
            res = 'b';
            break;
        case 0x39:
            res = 'c';
            break;
        case 0x5e:
            res = 'd';
            break;
        case 0x79:
            res = 'e';
            break;
        case 0x71:
            res = 'f';
            break;
        default:
            res = '!';
            break;
    }

    return res;
}

void dig::set_data(std::uint8_t data) {
    io_element::set_data(data);    
}

std::uint8_t dig::get_data() {
    return io_element::get_data();
}
