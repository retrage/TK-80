#include "cpu.h"

#define FLAG reg[0x06]

#define SET_SUB reg[0x06]|0x01
#define SET_CY4 reg[0x06]|0x02
#define SET_P reg[0x06]|0x04
#define SET_S reg[0x06]|0x08
#define SET_C reg[0x06]|0x10
#define SET_Z reg[0x06]|0x20

#define RESET_SUB reg[0x06]&0xfe
#define RESET_CY4 reg[0x06]|0xfd
#define RESET_P reg[0x06]|0xfb
#define RESET_S reg[0x06]|0xf7
#define RESET_C reg[0x06]|0xf0
#define RESET_Z reg[0x06]|0xef

#define GET_SUB reg[0x06]&0x01
#define GET_CY4 reg[0x06]&0x02
#define GET_P reg[0x06]&0x04
#define GET_S reg[0x06]&0x08
#define GET_C reg[0x06]&0x10
#define GET_Z reg[0x06]&0x20

#define S_REG reg[opcode&0x07]
#define D_REG reg[(opcode&0x38)>>3]
#define M_REG (reg[0x04]<<4)+reg[0x05]

cpu::cpu() {
    pc = 0x8200;
}

void cpu::setFlag(uint16_t data) {
    if ((data&0x100)>>8) {
        FLAG=SET_C;
    } else {
        FLAG=RESET_C;
    }
    
    if ((data&0x80)>>7) {
        FLAG=SET_S;
    } else {
        FLAG=RESET_S;
    }
    
    if (!data) {
        FLAG=SET_Z;
    } else {
        FLAG=RESET_Z;
    }
    
    int i, sum;
    sum = 0;
    for (i=0; i<8; i++) {
        sum =sum + data&(int)pow(2.0, (double)i)>>(i-1);
    }
    
    if (sum%2) {
        FLAG=SET_P;
    } else {
        FLAG=RESET_P;
    }
}

void cpu::execute() {
    int i = 0;
    uint16_t tmp1, tmp2;
    uint32_t tmp3;
    uint8_t opcode = mem.read(pc);
    switch (opcode) {
            //mov r1, r2 01DDDSSS
        case 0x41:
        case 0x43:
        case 0x45:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4a:
        case 0x4b:
        case 0x4c:
        case 0x4d:
        case 0x4f:
        case 0x51:
        case 0x53:
        case 0x55:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5a:
        case 0x5b:
        case 0x5c:
        case 0x5d:
        case 0x5f:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0x6f:
        case 0x78:
        case 0x79:
        case 0x7a:
        case 0x7b:
        case 0x7c:
        case 0x7d: D_REG = S_REG; pc++; break;
            //MOV M, r 01110SSS
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x77: mem.write(M_REG, S_REG); pc++; break;
            //MOV r, M 01DDD110
        case 0x4e:
        case 0x56:
        case 0x5e:
        case 0x66:
        case 0x6e:
        case 0x7e: D_REG=mem.read(M_REG); pc++; break;
            //HLT
        case 0x76: printf("HLT\n"); pc++; break;
            //MVI r, B2
        case 0x06:
        case 0x0e:
        case 0x16:
        case 0x1e:
        case 0x26:
        case 0x2e:
        case 0x3e: D_REG=mem.read(pc+1); pc=pc+2; break;
            //MVI M, B2
        case 0x36: mem.write(M_REG, mem.read(pc+1)); pc=pc+2; break;
            //INR r (SUB=0)
        case 0x04:
        case 0x0c:
        case 0x14:
        case 0x1c:
        case 0x24:
        case 0x2c:
        case 0x3c:
            tmp1=D_REG+0x01;
            D_REG=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc++;
            break;
            //INR M
        case 0x34:
            tmp1=mem.read(M_REG)+0x01;
            mem.write(M_REG, tmp1&0x0f);
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc++;
            break;
            //DCR r
        case 0x05:
        case 0x0d:
        case 0x15:
        case 0x1d:
        case 0x25:
        case 0x2d:
        case 0x3d:
            tmp1=D_REG-0x01;
            D_REG=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //DCR M
        case 0x35:
            tmp1=mem.read(M_REG)-0x01;
            mem.write(M_REG, tmp1&0x0f);
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //ADD r
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
        case 0x87:
            tmp1=reg[0x07]+S_REG;
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc++;
            break;
            //ADD M
        case 0x86:
            tmp1=reg[0x07]+mem.read(M_REG);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc++;
            break;
            //ADC r
        case 0x88:
        case 0x89:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8f:
            tmp1=reg[0x07]+S_REG+(reg[0x07]&0x10>>4);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc++;
            break;
            //ADC M
        case 0x8e:
            tmp1=reg[0x07]+mem.read(M_REG)+(reg[0x07]&0x10>>4);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc++;
            break;
            //SUB r
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x97:
            tmp1=reg[0x07]-S_REG;
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //SUB M
        case 0x96:
            tmp1=reg[0x07]-mem.read(M_REG);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //SBB r
        case 0x98:
        case 0x99:
        case 0x9a:
        case 0x9b:
        case 0x9c:
        case 0x9d:
        case 0x9f:
            tmp1=reg[0x07]-S_REG-(reg[0x07]&0x10>>4);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //SBB M
        case 0x9e:
            tmp1=reg[0x07]-mem.read(M_REG)-(reg[0x07]&0x10>>4);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //ANA r
        case 0xa0:
        case 0xa1:
        case 0xa2:
        case 0xa3:
        case 0xa4:
        case 0xa5:
        case 0xa7:
            tmp1=reg[0x07]&S_REG;
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_C; //?
            pc++;
            break;
            //ANA M
        case 0xa6:
            tmp1=reg[0x07]&mem.read(M_REG);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_C; //?
            pc++;
            break;
            //XRA r
        case 0xa8:
        case 0xa9:
        case 0xaa:
        case 0xab:
        case 0xac:
        case 0xad:
        case 0xaf:
            tmp1=reg[0x07]^S_REG;
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_C;
            pc++;
            break;
            //XRA M
        case 0xae:
            tmp1=reg[0x07]^mem.read(M_REG);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_C;
            pc++;
            break;
            //ORA r
        case 0xb0:
        case 0xb1:
        case 0xb2:
        case 0xb3:
        case 0xb4:
        case 0xb5:
        case 0xb7:
            tmp1=reg[0x07]|S_REG;
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_C;
            pc++;
            break;
            //ORA M
        case 0xb6:
            tmp1=reg[0x07]|mem.read(M_REG);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_C;
            pc++;
            break;
            //CMP r
        case 0xb8:
        case 0xb9:
        case 0xba:
        case 0xbb:
        case 0xbc:
        case 0xbd:
        case 0xbf:
            tmp1=reg[0x07]-D_REG;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //CMP M
        case 0xbe:
            tmp1=reg[0x07]-mem.read(M_REG);
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc++;
            break;
            //ADI B2
        case 0xc6:
            tmp1=reg[0x07]+mem.read(pc+1);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc=pc+2;
            break;
            //ACI B2
        case 0xce:
            tmp1=reg[0x07]+mem.read(pc+1)+((FLAG&0x10)>>4);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=RESET_SUB;
            pc=pc+2;
            break;
            //SUI B2
        case 0xd6:
            tmp1=reg[0x07]-mem.read(pc+1);
            reg[0x07]=tmp1&0x0f;
            setFlag(tmp1);
            FLAG=SET_SUB;
            pc=pc+2;
            break;
            //SBI B2
        case 0xde:
            tmp1=reg[0x07]-mem.read(pc+1)-((FLAG&0x10)>>4);
            reg[0x07]=tmp1&0x0f;
            FLAG=SET_SUB;
            pc=pc+2;
            break;
            //ANI B2
        case 0xe6:
            tmp1=reg[0x07]&mem.read(pc+1);
            reg[0x07]=tmp1&0x0f;
            FLAG=RESET_C;
            pc=pc+2;
            break;
            //XRI B2
        case 0xee:
            tmp1=reg[0x07]^mem.read(pc+1);
            reg[0x07]=tmp1&0x0f;
            FLAG=RESET_C;
            pc=pc+2;
            break;
            //ORI B2
        case 0xf6:
            tmp1=reg[0x07]|mem.read(pc+1);
            reg[0x07]=tmp1&0x0f;
            FLAG=RESET_C;
            pc=pc+2;
            break;
            //CPI B2
        case 0xfe:
            tmp1=reg[0x07]-mem.read(pc+1);
            FLAG=SET_SUB;
            pc=pc+2;
            break;//?
            //RLC
        case 0x07:
            tmp1=reg[0x07]<<1;
            reg[0x07]=tmp1&0x0f;
            reg[0x07]=reg[0x07]|(tmp1>>8);
            FLAG=tmp1>>8 ? SET_C : RESET_C;
            pc++;
            break; //?
            //RRC
        case 0x0f:
            tmp1=(reg[0x07]>>1)&(reg[0x07]&0x01<<7);
            reg[0x07]=tmp1&0x0f;
            FLAG=(tmp1&0x80)>>7 ? SET_C : RESET_C;
            pc++;
            break;
            //RAL
        case 0x17:
            tmp1=(reg[0x07]<<1)|(GET_C);
            reg[0x07]=tmp1&0x0f;
            FLAG=(tmp1>>8)&0x01 ? SET_C : RESET_C;
            pc++;
            break;
            //RAR
        case 0x1f:
            tmp1=(reg[0x07]>>1)|(GET_C<<7);
            FLAG=reg[0x07]&0x01 ? SET_C : RESET_C;
            reg[0x07]=tmp1&0x0f;
            pc++;
            break;
            //DAA
        case 0x27:
            tmp1=reg[0x07]&0x0f;
            tmp2=(reg[0x07]&0xf0)>>4;
            if (GET_SUB) {
                reg[0x07] = GET_CY4 ? tmp1-0x06 : tmp1;
                reg[0x07] = GET_C ? ((tmp2-0x06)<<4)&0xf0 : (tmp2<<4)&0xf0;
            } else {
                if (tmp1>9 || GET_CY4) {
                    tmp1=tmp1+0x06;
                }
                if (tmp2>9 || GET_C) {
                    tmp2=tmp2+0x06;//?
                    FLAG=SET_C;
                }
            }
            reg[0x07]=tmp1+(tmp2<<4);
            setFlag(reg[0x07]);//?
            pc++;
            break;
            //CMA
        case 0x2f: reg[0x07]=~reg[0x07]; pc++; break;
            //STC
        case 0x37: FLAG = SET_C; pc++; break;
            //CMC
        case 0x3f: FLAG = GET_C ? RESET_C : SET_C; pc++; break;
            //NOP
        case 0x00: pc++; break;
            //LXI B, B2B3
        case 0x01: reg[0x01]=mem.read(pc+1); reg[0x00]=mem.read(pc+2); pc=pc+3; break;
            //LXI D, B2B3
        case 0x11: reg[0x03]=mem.read(pc+1); reg[0x02]=mem.read(pc+2); pc=pc+3; break;
            //LXI H, B2B3
        case 0x21: reg[0x05]=mem.read(pc+1); reg[0x04]=mem.read(pc+2); pc=pc+3; break;
            //LXI SP, B2B3
        case 0x31: reg[0x07]=mem.read(pc+1); reg[0x06]=mem.read(pc+2); pc=pc+3; break;
            //DAD B
        case 0x09:
            tmp3=(reg[0x04]<<8)+reg[0x05]+(reg[0x00]<<8)+reg[0x01];
            reg[0x04]=(tmp3&0xf0)>>8;
            reg[0x05]=tmp3&0x0f;
            setFlag(tmp3);
            FLAG=RESET_SUB;
            pc++;
            break;
            //DAD D
        case 0x19:
            tmp3=(reg[0x04]<<8)+reg[0x05]+(reg[0x02]<<8)+reg[0x03];
            reg[0x04]=(tmp3&0xf0)>>8;
            reg[0x05]=tmp3&0x0f;
            setFlag(tmp3);
            FLAG=RESET_SUB;
            pc++;
            break;
            //DAD H
        case 0x29:
            tmp3=(reg[0x04]<<8)+reg[0x05]+(reg[0x04]<<8)+reg[0x05];
            reg[0x04]=(tmp3&0xf0)>>8;
            reg[0x05]=tmp3&0x0f;
            setFlag(tmp3);
            FLAG=RESET_SUB;
            pc++;
            break;
            //DAD SP
        case 0x39:
            tmp3=(reg[0x04]<<8)+reg[0x05]+sp;
            reg[0x04]=(tmp3&0xf0)>>8;
            reg[0x05]=tmp3&0x0f;
            setFlag(tmp3);
            FLAG=RESET_SUB;
            pc++;
            break;
            //STAX B
        case 0x02: mem.write(((reg[0x00]<<8)+reg[0x01]), reg[0x07]); pc++; break;
            //STAX D
        case 0x12: mem.write(((reg[0x02]<<8)+reg[0x03]), reg[0x07]); pc++; break;
            //LDAX B
        case 0x0a: reg[0x07]=mem.read(((reg[0x00]<<8)+reg[0x01])); pc++; break;
            //LDAX D
        case 0x1a: reg[0x07]=mem.read(((reg[0x02]<<8)+reg[0x03])); pc++; break;
            //SHLD B3B2
        case 0x22: mem.write((mem.read(pc+2)<<8)+mem.read(pc+1), reg[0x05]); mem.write((mem.read(pc+2)<<8)+(mem.read(pc+1)+1), reg[0x05]); pc=pc+3; break;
            //LHLD B3B2
        case 0x2a: mem.write((mem.read(pc+2)<<8)+mem.read(pc+1), reg[0x05]); reg[0x04]=(mem.read(pc+2)<<8)+(mem.read(pc+1)+1); pc=pc+3; break;
            //STA B3B2
        case 0x32: mem.write((mem.read(pc+2)<<8)+mem.read(pc+1), reg[0x07]); pc=pc+3; break;
            //LDA B3B2
        case 0x3a: reg[0x07]=(mem.read(pc+2)<<8)+mem.read(pc+1); pc=pc+3; break;
            //INX B
        case 0x03: tmp1=(reg[0x00]<<8)+reg[0x01]+1; reg[0x00]=tmp1>>8; reg[0x01]=tmp1&0x0f; pc++; break;
            //INX D
        case 0x13: tmp1=(reg[0x02]<<8)+reg[0x03]+1; reg[0x02]=tmp1>>8; reg[0x03]=tmp1&0x0f; pc++; break;
            //INX H
        case 0x23: tmp1=(reg[0x04]<<8)+reg[0x05]+1; reg[0x04]=tmp1>>8; reg[0x05]=tmp1&0x0f; pc++; break;
            //INX SP
        case 0x33: sp++; pc++; break;
            //DCX B
        case 0x0b: tmp1=(reg[0x00]<<8)+reg[0x01]-1; reg[0x00]=tmp1>>8; reg[0x01]=tmp1&0x0f; pc++; break;
            //DCX D
        case 0x1b: tmp1=(reg[0x02]<<8)+reg[0x03]-1; reg[0x02]=tmp1>>8; reg[0x03]=tmp1&0x0f; pc++; break;
            //DCX H
        case 0x2b: tmp1=(reg[0x04]<<8)+reg[0x05]-1; reg[0x04]=tmp1>>8; reg[0x05]=tmp1&0x0f; pc++; break;
            //DCX SP
        case 0x3b: sp--; pc++; break;
            //OUT B2
        case 0xd3: printf("OUT\t%x\n", mem.read(i+1)); pc++; break;
            //IN B2
        case 0xdb: printf("IN\t%x\n", mem.read(i+1)); pc++; break;
            //HTHL
        case 0xe3: tmp1=mem.read(sp); mem.write(sp, reg[0x05]); reg[0x05]=tmp1; tmp2=mem.read(sp+1); mem.write(sp+1, reg[0x04]); reg[0x04]=tmp2; pc++; break;
            //XCHG
        case 0xeb: tmp1=reg[0x05]; reg[0x05]=reg[0x03]; reg[0x03]=tmp1; tmp2=reg[0x04]; reg[0x05]=reg[0x02]; reg[0x02]=tmp2; pc++; break;
            //DI
        case 0xf3: printf("DI\n"); pc++; break;
            //EI
        case 0xfb: printf("EI\n"); pc++; break;
            //PUSH B
        case 0xc5: mem.write(sp-1, reg[0x00]); mem.write(sp-2, reg[0x01]); sp=sp-2; pc++; break;
            //PUSH D
        case 0xd5: mem.write(sp-1, reg[0x02]); mem.write(sp-2, reg[0x03]); sp=sp-2; pc++; break;
            //PUSH H
        case 0xe5: mem.write(sp-1, reg[0x04]); mem.write(sp-2, reg[0x05]); sp=sp-2; pc++; break;
            //PUSH PSW
        case 0xf5: mem.write(sp-1, reg[0x07]); mem.write(sp-2, reg[0x06]); sp=sp-2; pc++; break; //?
            //POP B
        case 0xc1: reg[0x01]=mem.read(sp); reg[0x00]=mem.read(sp+1); sp=sp+2; pc++; break;
            //POP D
        case 0xd1: reg[0x03]=mem.read(sp); reg[0x02]=mem.read(sp+1); sp=sp+2; pc++; break;
            //POP H
        case 0xe1: reg[0x05]=mem.read(sp); reg[0x04]=mem.read(sp+1); sp=sp+2; pc++; break;
            //POP PSW
        case 0xf1: reg[0x06]=mem.read(sp); reg[0x07]=mem.read(sp+1); sp=sp+2; pc++; break; //?
            //PCHL
        case 0xe9: pc=(reg[0x04]<<8)+reg[0x05]; pc++; break; //?
            //SPHL
        case 0xf9: sp=(reg[0x04]<<8)+reg[0x05]; pc++; break;
            //JMP B3B2
        case 0xc3: pc=(mem.read(pc+2)<<8)+mem.read(pc+1); pc++; break;
            //pc=(mem.read(pc+1)<<8)+mem.read(pc+2); break;
            //JNZ B3B2
        case 0xc2: pc = !GET_Z ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JZ B3B2
        case 0xca: pc = GET_Z ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JNC B3B2
        case 0xd2: pc = !GET_C ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JC B3B2
        case 0xda: pc = GET_C ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JPO B3B2
        case 0xe2: pc = !GET_P ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JPE B3B2
        case 0xea: pc = GET_P ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JP B3B2
        case 0xf2: pc = !GET_S ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //JM B3B2
        case 0xfa: pc = GET_S ? (mem.read(pc+2)<<0x08)+mem.read(pc+1) : pc+3; break;
            //CALL B3B2
        case 0xcd:
            mem.write(sp-1, (pc&0xf0)>>0x08);
            mem.write(sp-2, pc&0x0f);
            sp=sp-2;
            pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            break;
            //CNZ B3B2
        case 0xc4:
            if (!GET_Z) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CN B3B2
        case 0xcc:
            if (GET_Z) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CNC B3B2
        case 0xd4:
            if (!GET_C) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CC B3B2
        case 0xdc:
            if (GET_C) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CP0 B3B2
        case 0xe4:
            if (!GET_P) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CPE B3B2
        case 0xec:
            if (GET_P) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CP B3B2
        case 0xf4:
            if (!GET_S) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //CM B3B2
        case 0xfc:
            if (GET_S) {
                mem.write(sp-1, pc>>0x08);
                mem.write(sp-2, pc&0x0f);
                sp=sp-2;
                pc=(mem.read(pc+2)<<0x08)+mem.read(pc+1);
            } else {
                pc=pc+3;
            }
            break;
            //RET
        case 0xc9: pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2; break;
            //RNZ
        case 0xc0:
            if (!GET_Z) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RZ
        case 0xc8:
            if (GET_Z) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RNC
        case 0xd0:
            if (!GET_C) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RC
        case 0xd8:
            if (GET_C) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RPO
        case 0xe0:
            if (!GET_P) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RPE
        case 0xe8:
            if (GET_P) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RP
        case 0xf0:
            if (!GET_S) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RM
        case 0xf8:
            if (GET_S) {
                pc=(mem.read(sp+1)<<8)+mem.read(sp); sp=sp+2;
            } else {
                pc++;
            }
            break;
            //RST
        case 0xc7:
        case 0xcf:
        case 0xd7:
        case 0xdf:
        case 0xe7:
        case 0xef:
        case 0xf7:
        case 0xff:
            mem.write(sp-1, pc>>8);
            mem.write(sp-2, pc&0x0f);
            sp=sp-2;
            pc=opcode&0x38<<3;
            break;
    }

}
