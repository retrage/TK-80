#include <map>

#include "memory.h"
#include "digs.h"
#include "keys.h"

// io address
static const std::uint16_t dig_addr[8] = {
    0x83f8, 0x83f9, 0x83fa, 0x83fb, 0x83fc, 0x83fd, 0x83fe, 0x83ff
};

static const std::uint16_t key_addr = 0x83f3;

class tk80_io : public tk80_mem {
    public:
        std::map<std::uint16_t, dig> dig_table;
        keys a_keys;

        tk80_io();
        virtual void write(std::uint16_t addr, uint8_t data);
        virtual uint8_t read(std::uint16_t addr);

        std::string disp_digs();
        //void input_keys();
};
