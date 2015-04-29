#pragma once
#include "element.h"

/*
enum input_key std::uint8_t {
    key_0, key_1, key_2, key_3, key_4,
    key_5, key_6, key_7, key_8, key_9,
    key_a, key_b, key_c, key_d, key_e,
    key_f,
    key_run,
    key_ret,
    key_addr_set,
    key_read_decr,
    key_read_incr,
    key_write_incr,
    key_store_data,
    key_load_data
};
*/

class keys : public io_element {
    public:
        keys() {};
        keys(std::uint16_t addr);
        virtual void set_data(std::uint8_t data);
        virtual std::uint8_t get_data();

        void input(std::uint8_t data);
};
