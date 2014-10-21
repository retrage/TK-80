#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

static const int str_max = 128;

std::string clean_str(std::string str) {
    std::string tmp = str;
    int i;
    for(i=0; i<tmp.size(); i++) {
        if(tmp[i]=='\t')
            tmp.erase(i,1);
        if(tmp[i]==';')
            tmp.erase(i);
    }
    return tmp;
}

std::vector<std::string> parse(std::string str, char c) {
    std::stringstream ss(str);
    std::string tmp;
    std::vector<std::string> res;
    while(std::getline(ss, tmp, c)) {
        res.push_back(tmp);
    }
    return res;
}

uint8_t get_reg(std::string str) {
    switch(str) {
        case "M":
            return 0x06;
            break;
        case "B":
            return 0x00;
            break;
        case "C":
            return 0x01;
            break;
        case "D":
            return 0x02;
            break;
        case "E":
            return 0x03;
            break;
        case "H":
            return 0x04;
            break;
        case "L":
            return 0x05;
            break;
        case "A":
            return 0x07;
            break;
        case "SP":
            return 
        default:
            break;

    }
}

uint32_t assemble(std::vector<std::string> ops) {
    uint32_t tmp;
    uint8_t params[2];
    if(ops[1])
        params[0] = get_reg(ops[1]);
    else
        params[0] = 0x06;
    if(ops[2])
        params[1] = get_reg(ops[2]);
    else
        params[1] = 0x06;

    switch(ops[0]) {
        "MOV":
            tmp = 0x40 | (params[0] << 3) | params[1];
            break;
        "HLT":
            tmp = 0x76;
            break;
        "MVI":
            tmp = ((0x00 | (params[0] << 3)) << 8) | params[1];
            break;
        "INR":
            tmp = 0x34;
            break;
        "DCR":
            tmp = 0x35;
            break;
        "ADD":
            tmp = 0x80 | params[0];
            break;
        "ADC":
            tmp = 0x88 | params[0];
            break;
        "SUB":
            tmp = 0x90 | params[0];
            break;
        "SBB":
            tmp = 0x98 | params[0];
            break;
        "ANA":
            tmp = 0xa0 | params[0];
            break;
        "XRA":
            tmp = 0xa8 | params[0];
            break;
        "ORA":
            tmp = 0xb0 | params[0];
            break;
        "CMP":
            tmp = 0xb8 | params[0];
            break;
        "ADI":
            tmp = (0xc6 << 8) | params[0];
            break;
        "ACI":
            tmp = (0xce << 8) | params[0];
            break;
        "SUI":
            tmp = (0xd6 << 8) | params[0];
            break;
        "SBI":
            tmp = (0xde << 8) | params[0];
            break;
        "ANI":
            tmp = (0xe6 << 8) | params[0];
            break;
        "XRI":
            tmp = (0xee << 8) | params[0];
            break;
        "ORI":
            tmp = (0xf6 << 8) | params[0];
            break;
        "CPI":
            tmp = (0xfe << 8) | params[0];
            break;
        "RLC":
            tmp = 0x07;
            break;
        "RRC":
            tmp = 0x0f;
            break;
        "RAL":
            tmp = 0x17;
            break;
        "RAR":
            tmp = 0x1f;
            break;
        "DAA":
            tmp = 0x27;
            break;
        "CMA":
            tmp = 0x2f;
            break;
        "STC":
            tmp = 0x37;
            break;
        "CMC":
            tmp = 0x3f;
            break;
        "NOP:
            tmp = 0x00;
            break;
        "LXI"
            tmp = ((0x01 | (params[0] << 4)) << 16) | params[1];
            break;
        "DAD":
            tmp = 0x09 | (params[0] << 4);
            break;
        "STAX":
            tmp = 0x02 | (params[0] << 4);
            break;
        "LDAX":
            tmp = 0x0a | (params[0] << 4);
            break;
        "SHLD":
            tmp = (0x22 << 8) | params[0];
            break;
        "LHLD":
            tmp = (0x2a << 8) | params[0];
            break;
        "STA":
            tmp = (0x32 << 8) | params[0];
            break;
        "LDA":
            tmp = (0x3a << 8) | params[0];
            break;
        "INX":
            tmp = 0x03 | (params[0] << 4);
            break;
        "DCX":
            tmp = 0x0b | (params[0] << 4);
            break;
        "OUT":
            tmp = (0xd3 << 8) | params[0];
            break;
        "IN":
            tmp = (0xdb << 8) | params[0];
            break;
        "XTHL":
            tmp = 0xe3;
            break;
        "XCHG":
            tmp = 0xeb;
            break;
        "DI":
            tmp = 0xf3;
            break;
        "EI":
            tmp = 0xfb;
            break;
        "PUSH":
            tmp = 0xc5 | (params[0] << 4);
            break;
        "POP":
            tmp = 0xc1 | (params[0] << 4);
            break;
        "PCHL":
            tmp = 0xe9;
            break;
        "SPHL":
            tmp = 0xf9;
            break;
        "JMP":
            tmp = (0xc3 << 16) | (params[1] << 8) | params[0];
            break;
        "JNZ":
            tmp = (0xc2 << 16) | (params[1] << 8) | params[0];
            break;
        "JZ":
            tmp = (0xca << 16) | (params[1] << 8) | params[0];
            break;
        "JNC":
            tmp = (0xd2 << 16) | (params[1] << 8) | params[0];
            break;
        "JC":
            tmp = (0xda << 16) | (params[1] << 8) | params[0];
            break;
        "JPO":
            tmp = (0xe2 << 16) | (params[1] << 8) | params[0];
            break;
        "JPE":
            tmp = (0xea << 16) | (params[1] << 8) | params[0];
            break;
        "JP":
            tmp = (0xf2 << 16) | (params[1] << 8) | params[0];
            break;
        "JM":
            tmp = (0xfa << 16) | (params[1] << 8) | params[0];
            break;
        "CALL":
            tmp = (0xcd << 16) | (params[1] << 8) | params[0];
            break;
        "CNZ":
            tmp = (0xc4 << 16) | (params[1] << 8) | params[0];
            break;
        "CN":
            tmp = (0xcc << 16) | (params[1] << 8) | params[0];
            break;
        "CNC":
            tmp = (0xd4 << 16) | (params[1] << 8) | params[0];
            break;
        "CC":
            tmp = (0xdc << 16) | (params[1] << 8) | params[0];
            break;
        "CP0":
            tmp = (0xe4 << 16) | (params[1] << 8) | params[0];
            break;
        "CPE":
            tmp = (0xec << 16) | (params[1] << 8) | params[0];
            break;
        "CP":
            tmp = (0xf4 << 16) | (params[1] << 8) | params[0];
            break;
        "CM":
            tmp = (0xfc << 16) | (params[1] << 8) | params[0];
            break;
        "RET":
            tmp = 0xc9;
            break;
        "RNZ":
            tmp = 0xc0;
            break;
        "RZ":
            tmp = 0xc8;
            break;
        "RNC":
            tmp = 0xd0;
            break;
        "RC":
            tmp = 0xd8;
            break;
        "RPO":
            tmp = 0xe0;
            break;
        "RPE":
            tmp = 0xe8;
            break;
        "RP":
            tmp = 0xf0;
            break;
        "RM":
            tmp = 0xf8;
            break;
        "RST":
            tmp = 0xc7 | (params[0] << 3);
            break;
    }
}

int main(int argc, char *argv[]) {
    if(argc!=2) {
        std::cout << "No input file.\n";
        return 0;
    }

    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);
    
    std::string str;

    int i = 0;
    while(ifs.good()) {
        std::getline(ifs, s);

        }

        i++;
    }

    return 0;
}
