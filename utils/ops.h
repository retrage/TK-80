#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

static const int str_max = 128;

typedef enum {
    none_t,
    origin_t,
    opcode_t,
    label_t,
} optype;

class opinfo {
    public:
        optype type;
        std::vector<std::uint8_t> bin;
        std::string label;

        opinfo(std::string str);
        
    private:
        std::vector<std::string> parse(std::string str, char c); 
        std::uint16_t get_reg(std::string str); 
        void assemble(std::vector<std::string> ops); 
};
