#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

static const int str_max = 128;

typedef enum {
    none,
    origin,
    opcode,
    label,
} optype;

typedef struct {
    optype type;
    std::uint32_t bin;
    int len; // 8bit = 1
} codeinfo;

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

std::uint16_t get_reg(std::string str) {
    std::uint16_t res;
    
    if(!str.compare("M"))
        res = 0x06;
    else if(!str.compare("B"))
        res = 0x00;
    else if(!str.compare("C"))
        res = 0x01;
    else if(!str.compare("D"))
        res = 0x02;
    else if(!str.compare("E"))
        res = 0x03;
    else if(!str.compare("H"))
        res = 0x04;
    else if(!str.compare("L"))
        res = 0x05;
    else if(!str.compare("A"))
        res = 0x07;
    else if(!str.compare("SP"))
        res = 0x06;
    else if(!str.compare("PSW"))
        res = 0x06;
    else if(str.length() == 1) {
        if(std::stoi(str,nullptr, 10) < 8)
            res = std::stoi(str,nullptr, 10);
    }
    // get absolute adress
    else if(str[str.length()-1] == 'H') {
        str = str.erase(str.length()-1, 1);
        int len = str.length();
        res = std::stoi(str.substr(0,2), nullptr, 16);
        if(len>2) {
            res = res << 8 | std::stoi(str.substr(2,2), nullptr, 16);
        }
    }

    return res;
}

codeinfo assemble(std::vector<std::string> ops) {
    std::uint32_t tmp = 0x00;
    std::uint16_t params[2];
    
    codeinfo res;

    if(ops.size() >= 2)
        params[0] = get_reg(ops[1]);
    else
        params[0] = 0x06;
    
    if(ops.size() >= 3)
        params[1] = get_reg(ops[2]);
    else
        params[1] = 0x06;

    if(!ops[0].compare("ORG")) {
        res.optype = origin;
        res.bin = params[0];
        res.len = 2;
        return res;
    }

    res.optype = opcode;

    if(!ops[0].compare("MOV")) {
        res.bin = 0x40 | (params[0] << 3) | params[1];      
        res.len = 1;
    }

    else if(!ops[0].compare("HLT")) {
        res.bin = 0x76;
        res.len = 1;
    }

    else if(!ops[0].compare("MVI")) {
        res.bin = ((0x06 | (params[0] << 3)) << 8) | params[1];
        res.len = 2;
    }

    else if(!ops[0].compare("INR")) {
        res.bin = 0x04 | (params[0] << 3);
        res.len = 1;
    }
            
    else if(!ops[0].compare("DCR"))
        tmp = 0x05 | (params[0] << 3);
            
    else if(!ops[0].compare("ADD"))
        tmp = 0x80 | params[0];
            
    else if(!ops[0].compare("ADC"))
        tmp = 0x88 | params[0];
            
    else if(!ops[0].compare("SUB"))
        tmp = 0x90 | params[0];
            
    else if(!ops[0].compare("SBB"))
        tmp = 0x98 | params[0];
            
    else if(!ops[0].compare("ANA"))
        tmp = 0xa0 | params[0];
            
    else if(!ops[0].compare("XRA"))
        tmp = 0xa8 | params[0];
            
    else if(!ops[0].compare("ORA"))
        tmp = 0xb0 | params[0];
            
    else if(!ops[0].compare("CMP"))
        tmp = 0xb8 | params[0];
            
    else if(!ops[0].compare("ADI"))
        tmp = (0xc6 << 8) | params[0];
            
    else if(!ops[0].compare("ACI"))
        tmp = (0xce << 8) | params[0];
            
    else if(!ops[0].compare("SUI"))
        tmp = (0xd6 << 8) | params[0];
            
    else if(!ops[0].compare("SBI"))
        tmp = (0xde << 8) | params[0];
            
    else if(!ops[0].compare("ANI"))
        tmp = (0xe6 << 8) | params[0];
            
    else if(!ops[0].compare("XRI"))
        tmp = (0xee << 8) | params[0];
            
    else if(!ops[0].compare("ORI"))
        tmp = (0xf6 << 8) | params[0];
            
    else if(!ops[0].compare("CPI"))
        tmp = (0xfe << 8) | params[0];
            
    else if(!ops[0].compare("RLC"))
        tmp = 0x07;
            
    else if(!ops[0].compare("RRC"))
        tmp = 0x0f;
            
    else if(!ops[0].compare("RAL"))
        tmp = 0x17;
            
    else if(!ops[0].compare("RAR"))
        tmp = 0x1f;
            
    else if(!ops[0].compare("DAA"))
        tmp = 0x27;
            
    else if(!ops[0].compare("CMA"))
        tmp = 0x2f;
            
    else if(!ops[0].compare("STC"))
        tmp = 0x37;
            
    else if(!ops[0].compare("CMC"))
        tmp = 0x3f;
            
    else if(!ops[0].compare("NOP"))
        tmp = 0x00;
            
    else if(!ops[0].compare("LXI"))
        tmp = ((0x01 | (params[0] << 4)) << 16) | params[1];
            
    else if(!ops[0].compare("DAD"))
        tmp = 0x09 | (params[0] << 4);
            
    else if(!ops[0].compare("STAX"))
        tmp = 0x02 | (params[0] << 4);
            
    else if(!ops[0].compare("LDAX"))
        tmp = 0x0a | (params[0] << 4);
            
    else if(!ops[0].compare("SHLD"))
        tmp = (0x22 << 16) | params[0];
            
    else if(!ops[0].compare("LHLD"))
        tmp = (0x2a << 16) | params[0];
            
    else if(!ops[0].compare("STA"))
        tmp = (0x32 << 16) | params[0];
            
    else if(!ops[0].compare("LDA"))
        tmp = (0x3a << 16) | params[0];
            
    else if(!ops[0].compare("INX"))
        tmp = 0x03 | (params[0] << 4);
            
    else if(!ops[0].compare("DCX"))
        tmp = 0x0b | (params[0] << 4);
            
    else if(!ops[0].compare("OUT"))
        tmp = (0xd3 << 8) | params[0];
            
    else if(!ops[0].compare("IN"))
        tmp = (0xdb << 8) | params[0];
            
    else if(!ops[0].compare("XTHL"))
        tmp = 0xe3;
            
    else if(!ops[0].compare("XCHG"))
        tmp = 0xeb;
            
    else if(!ops[0].compare("DI"))
        tmp = 0xf3;
            
    else if(!ops[0].compare("EI"))
        tmp = 0xfb;
            
    else if(!ops[0].compare("PUSH"))
        tmp = 0xc5 | (params[0] << 3);
            
    else if(!ops[0].compare("POP"))
        tmp = 0xc1 | (params[0] << 3);
            
    else if(!ops[0].compare("PCHL"))
        tmp = 0xe9;
            
    else if(!ops[0].compare("SPHL"))
        tmp = 0xf9;
            
    else if(!ops[0].compare("JMP"))
        tmp = (0xc3 << 16) | params[0];
            
    else if(!ops[0].compare("JNZ"))
        tmp = (0xc2 << 16) | params[0];
            
    else if(!ops[0].compare("JZ"))
        tmp = (0xca << 16) | params[0];
            
    else if(!ops[0].compare("JNC"))
        tmp = (0xd2 << 16) | params[0];
            
    else if(!ops[0].compare("JC"))
        tmp = (0xda << 16) | params[0];
            
    else if(!ops[0].compare("JPO"))
        tmp = (0xe2 << 16) | params[0];
            
    else if(!ops[0].compare("JPE"))
        tmp = (0xea << 16) | params[0];
            
    else if(!ops[0].compare("JP"))
        tmp = (0xf2 << 16) | params[0];
            
    else if(!ops[0].compare("JM"))
        tmp = (0xfa << 16) | params[0];
            
    else if(!ops[0].compare("CALL"))
        tmp = (0xcd << 16) | params[0];
            
    else if(!ops[0].compare("CNZ"))
        tmp = (0xc4 << 16) | params[0];
            
    else if(!ops[0].compare("CN"))
        tmp = (0xcc << 16) | params[0];
            
    else if(!ops[0].compare("CNC"))
        tmp = (0xd4 << 16) | params[0];
            
    else if(!ops[0].compare("CC"))
        tmp = (0xdc << 16) | params[0];
            
    else if(!ops[0].compare("CP0"))
        tmp = (0xe4 << 16) | params[0];
            
    else if(!ops[0].compare("CPE"))
        tmp = (0xec << 16) | params[0];
            
    else if(!ops[0].compare("CP"))
        tmp = (0xf4 << 16) | params[0];
            
    else if(!ops[0].compare("CM"))
        tmp = (0xfc << 16) | params[0];
            
    else if(!ops[0].compare("RET"))
        tmp = 0xc9;
            
    else if(!ops[0].compare("RNZ"))
        tmp = 0xc0;
            
    else if(!ops[0].compare("RZ"))
        tmp = 0xc8;
            
    else if(!ops[0].compare("RNC"))
        tmp = 0xd0;
            
    else if(!ops[0].compare("RC"))
        tmp = 0xd8;
            
    else if(!ops[0].compare("RPO"))
        tmp = 0xe0;
            
    else if(!ops[0].compare("RPE"))
        tmp = 0xe8;
            
    else if(!ops[0].compare("RP"))
        tmp = 0xf0;
            
    else if(!ops[0].compare("RM"))
        tmp = 0xf8;
            
    else if(!ops[0].compare("RST"))
        tmp = 0xc7 | (params[0] << 3);

    return res;
}

std::vector<codeinfo> code2vec(std::ifstream ifs) {

    std::vector<codeinfo> res;
    while(ifs.good()) {
        std::getline(ifs, str);
        if(str.size()) {
            codeinfo info = assemble(parse(str, ' '));
            res.push_back(info);
        }
    }
    
    return res;
}

std::map<auto, auto> vec2table(std::vector<codeinfo> vec) {
    
    std::map<std::string, std::uint16_t> label_table;
    std::uint16_t start_addr = 0x0000;
    
    if(vec.front().optype == origin) {
        start_addr = vec.front().bin;
        vec.erase(vec.begin());
    }
    
    std::uint16_t current_addr = start_addr;

    for(codeinfo info : vec) {
        if(info.optype==label) {
            std::pair<auto, auto> p = (info.l, current_addr);
            label_table.insert(p);
        } else if(info.optype==opcode) {
            current_addr += info.len;
        }
    }
    
    return label_table;
}

char[] vec2bin(std::vector<codeinfo> vec, std::map label_table) {

    int length = 0;
    for(codeinfo info : vec) {
        length += info.len;
        
    }
    if(vec.front().type==origin) {
        codeinfo end_addr = {origin, (vec.front().bin+length), 2};
        vec.insert(vec.begin()+1, end_addr);
    }

    
}

int main(int argc, char *argv[]) {

    if(argc!=2) {
        std::cout << "No input file." << std::endl;
        return 0;
    }
    
    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);
    
    std::vector<codeinfo> vec = code2vec(ifs);

    std::string str;

    while(ifs.good()) {
        std::getline(ifs, str);
        if(str.size()) {
            codeinfo res = assemble(parse(str, ' '));
            switch(res.optype) {
                case origin:
                    start_addr = res.bin;
                    break;
                case opcode:
                    program_len += res.len;

                case label:

            }
        }
    }


    std::cout << std::dec << get_reg(argv[1]) << std::endl;
    return 0;
}
