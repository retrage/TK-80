#include "io.h"
#include "digs.h"

tk80_io::tk80_io() {

    for (int i=0; i<8; i++) {
        dig d = dig::dig(dig_addr[i]);
        std::pair<std::uint16_t, dig> dig_p (dig_addr[i], d);
        dig_table.insert(dig_p);
    }
}

void tk80_io::write(std::uint16_t addr, uint8_t data) {

    if (this->dig_table.find(addr)!=dig_table.end()) {
        this->dig_table[addr].set_data(data);
    }

    this->tk80_mem::write(addr, data);
}

std::uint8_t tk80_io::read(uint16_t addr) {

    std::uint8_t res;

    if (this->dig_table.find(addr)!=dig_table.end()) {
        res = this->dig_table[addr].get_data();
    } else {
        res = this->tk80_mem::read(addr);
    }

    return res;
}

std::string tk80_io::disp_digs() {
    std::string str = "";
    for (int i=0; i<8; i++) {
        dig d = this->dig_table[dig_addr[i]];
        str += d.get_dig();
    }

    return str;
}
