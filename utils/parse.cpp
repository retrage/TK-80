#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> parse(std::string str, char c) {
        std::stringstream ss(str);
        std::string tmp;
        std::vector<std::string> res;
        while(std::getline(ss, tmp, c)) {
            res.push_back(tmp);
        }   
        return res;
}

int main() {
    std::cout << parse("MOV R1", ' ')[0] << std::endl;
    std::cout << parse("MOV C,L", ',')[1] << std::endl;

    std::string s = "";
    if(s.size())
        std::cout << "s" << std::endl;

    return 0;
}
