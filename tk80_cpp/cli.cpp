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
    
    std::printf("Command-line Interactive TK-80 emulator\n"); 
    
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
        
        } else if(cmds[0]=="store") {
        
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
