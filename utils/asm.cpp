#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

static const int str_max = 128;

typedef enum {
    NONE = 0,
    EQU = 1,
    LABEL = 2,
    OP = 3,
}asm_kind;

class mnemonic {
public:
    std::vector<std::string> ops;
    int op_size;
    int at_line;
    bool need_label;
    mnemonic(std::string str, int at);
    int assemble();
};

mnemonic::mnemonic(std::string, int at) {
    at_line = at;
}

mnemonic::assemble() {
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

asm_kind kind(std::string str) {
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
    
    std::string str;

    std::map<std::string, int> equs;
    std::map<std::string, int> labels;
    std::vector<mnemonic> ops;

    int i = 0;
    while(ifs.good()) {
        std::getline(ifs, s);

        switch(kind(clean_str(s))) {
            case LABEL:
                //labels.insert(std::pair<std::string,int>(s));
                break;
            case EQU:
                std::vector<std::string> tmp_p = parse(s);
                std::pair<std::stirng, int> tmp_equ(tmp_p[0],tmp_p[1]);
                equs.insert(tmp_equ);
                break;
            case OP:
                std::vector<std::string> tmp_p = parse(s); 
                break;
        }

        i++;
    }

    for(auto op : ops) {
        if(op.need_label)
    }

    return 0;
}
