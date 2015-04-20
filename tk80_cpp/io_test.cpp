#include <cstdio>

#include "io.h"
#include "digs.h"

int main(int argc, char *argv[]) {
    //tk80_io io = new tk80_io::tk80_io();
    tk80_io io;

    io.write(0x0000, 0xff);
    std::printf("%4x, %2x\n", 0x0000, io.read(0x0000));

    io.write(0x83f8, 0x5c);
    std::printf("%4x, %2x\n", 0x83f8, io.read(0x83f8));
    
    std::string s = io.disp_digs();
    std::cout << s << std::endl;
/*
    char c;
    dig d = io.addr_table[0x38f8];
    c = d.get_dig();
    std::printf("%c\n", c);
*/
    return 0;
}
