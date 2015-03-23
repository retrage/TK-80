#include "cli.h"

tk80_cli::tk80_cli()
{
    this->current_addr = entry_addr;
    this->mode = step_t;
}

void tk80_cli::set_addr(std::uint16_t addr)
{
    this->current_addr = addr;    
}

void tk80_cli::set_mode(tk80_mode mode)
{
    this->mode = mode;
}

void tk80_cli::write_inc(std::uint8_t data)
{
    this->cpu.mem.write(this->current_addr, data);
    this->current_addr++;
}

std::uint8_t tk80_cli::read_inc()
{
    std::uint8_t data = this->cpu.mem.read(this->current_addr);
    this->current_addr++;
    return data;
}

std::uint8_t tk80_cli::read_dec()
{
    std::uint8_t data = this->cpu.mem.read(this->current_addr);
    this->current_addr--;
    return data;
}

void tk80_cli::run()
{
    this->cpu.setpc(this->current_addr);
    while (1) {
        this->ret();
        if (this->mode==step_t)
            break;
    }
}

void tk80_cli::ret()
{
    this->cpu.execute();
    if (this->mode==step_t) {
        this->current_addr = this->cpu.getpc();
        std::printf("(%4x %2x)\n", this->cpu.getpc(), this->cpu.getreg(7));
    }
}
void tk80_cli::reset()
{

}

bool tk80_cli::load_data(std::string path)
{
    std::ifstream ifs;
    ifs.open(path, std::ifstream::in|std::ifstream::binary);

    try {
        if (!ifs)
            throw path;
        
        char start_addr[2], end_addr[2];
        ifs.read(start_addr, 2);
        ifs.read(end_addr, 2);

        std::uint16_t addr = (start_addr[0] << 8) | start_addr[1];
        std::uint16_t e_addr = (end_addr[0] << 8) | end_addr[1];

        for(; addr<=e_addr; addr++) {
            try {
                char c;
                if((c=ifs.get())==EOF)
                    throw addr;
                
                this->cpu.mem.write(addr, c);
            } catch(std::uint16_t a) {
                std::cout << "Loading file was stopped at " << a << std::endl;
                break;
            }
        }

        ifs.close();
        return true;

    } catch (std::string ex_path) {
        std::cout << "could not open the file: " << ex_path << std::endl;
        return false;
    }

}

bool tk80_cli::store_data(std::string path, std::uint16_t start_addr, std::uint16_t end_addr)
{
    try {
        if (!(end_addr>start_addr))
            throw "end address must be bigger than start address.\n";

        try {
            std::ofstream ofs;
            ofs.open(path, std::ofstream::out|std::ofstream::binary);
            if(!ofs)
                throw path;

            ofs << (char)(start_addr >> 8);
            ofs << (char)(start_addr);
            ofs << (char)(end_addr >> 8);
            ofs << (char)(end_addr);
        
            std::uint8_t sum = 0x00;
            std::uint16_t addr;

            for (addr=start_addr; addr<=end_addr; addr++) {
                ofs <<  this->cpu.mem.read(addr);
                sum += this->cpu.mem.read(addr);
            }

            ofs << sum;

            // FIXME: delete LF code '0x0a'
            ofs.close();

        } catch(std::string ex_path) {
            std::cout << "could not open the file: " << ex_path << std::endl;
            return false;
        }
    
    } catch(std::string ex_str) {
        std::cout << ex_str << std::endl;
        return false;
    }

    return true;
}

//std::uint8_t print_reg();
std::uint8_t tk80_cli::print_mem(std::uint16_t addr)
{
    std::uint8_t data = this->cpu.mem.read(addr);
    return data;
}

std::vector<std::string> split(std::string str) {
    
    std::stringstream ss(str);
    std::string tmp;
    std::vector<std::string> res;

    while(getline(ss, tmp, ' ')) {
        if(!tmp.empty()) {
            res.push_back(tmp);
        }
    }

    return res;
}

int main(int argc, char *argv[]) {
    
    std::printf("Command-line TK-80 emulator\n"); 
    
    tk80_cli cli; 

    while(1) {
        std::string str;
        std::printf("(%4x) ", cli.current_addr);

        std::getline(std::cin, str);

        std::vector<std::string> cmds = split(str);

        if(cmds[0]=="set_addr" || cmds[0]=="s") {
            std::uint16_t addr = std::stoi(cmds[1], nullptr, 16);
            cli.set_addr(addr);

        } else if(cmds[0]=="set_mode") {
            if(cmds[1]=="auto") {
                cli.set_mode(auto_t);
                std::printf("mode: auto\n");
            } else if(cmds[1]=="step") {
                cli.set_mode(step_t);
                std::printf("mode: step\n");
            }
        } else if(cmds[0]=="write_inc" || cmds[0]=="w") {
            std::uint8_t data = std::stoi(cmds[1], nullptr, 16);
            cli.write_inc(data);
        
        } else if(cmds[0]=="read_inc" || cmds[0]=="ri") {
            std::uint8_t data = cli.read_inc();
            std::printf("(%4x %2x)\n", cli.current_addr-1, data);
                
        } else if(cmds[0]=="read_dec" || cmds[0]=="rd") {
            std::uint8_t data = cli.read_dec();
            std::printf("(%4x %2x)\n", cli.current_addr+1, data);

        } else if(cmds[0]=="run") {
            cli.run();
        } else if(cmds[0]=="ret") {
            cli.ret();
        } else if(cmds[0]=="reset") {
            cli.reset();
        } else if(cmds[0]=="load") {
            cli.load_data(cmds[1]);

        } else if(cmds[0]=="store") {
            std::uint16_t end_addr = std::stoi(cmds[1], nullptr, 16);
            std::string path = cmds.size() >= 3 ? cmds[2] : "data.bin";
            cli.store_data(path, cli.current_addr, end_addr);

        } else if(cmds[0]=="print_reg") {
            
        } else if(cmds[0]=="print_mem") {
            std::uint16_t addr = std::stoi(cmds[1], nullptr, 16);
            std::uint8_t data = cli.cpu.mem.read(addr);
            std::printf("(%4x %2x)\n", addr, data);
        
        } else if(cmds[0]=="quit" || cmds[0]=="q") {
            break;
        }
    }

    return 0;
}
