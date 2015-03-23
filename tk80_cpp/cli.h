#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "cpu.h"

static const std::uint16_t entry_addr = 0x8200;

std::vector<std::string> split(std::string str);

typedef enum {
    auto_t,
    step_t,
} tk80_mode;

class tk80_cli {
    public:
        std::uint16_t current_addr;
        tk80_cpu cpu = tk80_cpu(current_addr);
        tk80_mode mode;

        tk80_cli();

        void set_mode(tk80_mode mode);

        void set_addr(std::uint16_t addr);
        void write_inc(std::uint8_t data);
        std::uint8_t read_inc();
        std::uint8_t read_dec();
        void run();
        void ret();
        void reset();

        bool load_data(std::string path);
        bool store_data(std::string path, std::uint16_t start_addr, std::uint16_t end_addr);

        //std::uint8_t print_reg();
        std::uint8_t print_mem(std::uint16_t addr);
};
