#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

static const int str_max = 128;

class mnemonic {
public:
    std::vector<std::string> ops;
    int op_size;
    int at_line;
    bool need_label;
    mnemonic(std::string str, int at) {
        ops[0] = parse(str, ' ');
        at_line = at;
    }
    int asm();
}

int asm() {
    int tmp;
    switch(ops[0]) {
        case "MOV":
            op_size = 3;
            tmp = 0x10;
            break;
        case "JMP":
            op_size = 3;
            tmp = 0x20;
            need_label = true;
            break;
    }

    if(ops[1]) {
        tmp = tmp & key(equ);
    }

    if(ops[2]) {
        tmp = tmp & key(equ);
    }

    return tmp;
}

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

int translate(std::vector<std::string> tokens) {
    if(!tokens.size())
        return 0;
    std::cout << tokens[0] << std::endl;
    return 1;
}

int kind(std::string str) {
    std::string tmp = clean_str(str);
    if(tmp[-1]==':')
        return LABEL;
    else if(!parse(tmp).size)
        return NONE;
    else if(parse(tmp)[0]==EQU)
        return EQU;
    else
        return OP;
}

int main(int argc, char *argv[]) {
    if(argc!=2) {
        std::cout << "No input file.\n";
        return 0;
    }

    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);
    std::string s;

    //std::vector<std::string> op;

    std::set var;
    std::set label;

    int i = 0;
    while(ifs.good()) {
        std::getline(ifs, s);
        switch(kind(s)) {
            case LABEL:
                add_label(i, label(s));
                break;
            case EQU:
                add_label(i, equ(s));
                break;
            case OP:
                add_op(s);
                break;
        }

        //std::cout << op.size() << std::endl;
        i++;
    }

    for(auto op : ops) {
        if(op.need_label)
    }

    return 0;
}
