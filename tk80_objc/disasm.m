//
//  disasm.m
//  tk80
//

#import "disasm.h"

#define BASE_ADDR 0x8200

uint16_t pc;

char regnum(uint8_t num)
{
    char c;
    switch (num) {
        case 0x00:c='B'; break;
        case 0x01:c='C'; break;
        case 0x02:c='D'; break;
        case 0x03:c='E'; break;
        case 0x04:c='H'; break;
        case 0x05:c='L'; break;
        case 0x06:c='M'; break;
        case 0x07:c='A'; break;
        default:
            c='!'; break;
    }
    return c;
}

@implementation disasm

@synthesize mem;

- (id)init
{
    self = [super init];
    mem = [[memory alloc] init];
    return self;
}

- (void)disasm
{
    int i;
    uint8_t d;
    for (i=BASE_ADDR; i<BASE_ADDR+10; i++) {
        d = [mem read:i];
        printf("%x\t",i);
        switch (d) {
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
            case 0x7d: printf("MOV\t%c,%c\n", regnum((d&0x38)>>3),regnum(d&0x7)); break;
            //MOV M, r 01110SSS
            case 0x70:
            case 0x71:
            case 0x72:
            case 0x73:
            case 0x74:
            case 0x75:
            case 0x77: printf("MOV\tM,%c\n", regnum(d&0x7)); break;
            //MOV r, M 01DDD110
            case 0x4e:
            case 0x56:
            case 0x5e:
            case 0x66:
            case 0x6e:
            case 0x7e: printf("MOV\t%c,M\n", regnum((d&0x38)>>3)); break;
            //HLT
            case 0x76: printf("HLT\n"); break;
            //MVI r, B2
            case 0x06:
            case 0x0e:
            case 0x16:
            case 0x1e:
            case 0x26:
            case 0x2e:
            case 0x3e: printf("MVI\t%c,%x\n", regnum((d&0x38)>>3), [mem read:i+1]); i++; break;
            //MVI M, B2
            case 0x36: printf("MVI\tM,%x\n", [mem read:i+1]); i++; break;
            //INR r
            case 0x04:
            case 0x0c:
            case 0x14:
            case 0x1c:
            case 0x24:
            case 0x2c:
            case 0x3c: printf("INR\t%c\n", regnum((d&0x38)>>3)); break;
            //INR M
            case 0x34: printf("INR\tM\n"); break;
            //DCR r
            case 0x05:
            case 0x0d:
            case 0x15:
            case 0x1d:
            case 0x25:
            case 0x2d:
            case 0x3d: printf("DCR\t%c\n", regnum((d&0x38)>>3)); break;
            //DCR M
            case 0x35: printf("DCR\tM\n"); break;
            //ADD r
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
            case 0x87: printf("ADD\t%c\n", regnum(d&0x7)); break;
            //ADD M
            case 0x86: printf("ADD\tM\n"); break;
            //ADC r
            case 0x88:
            case 0x89:
            case 0x8a:
            case 0x8b:
            case 0x8c:
            case 0x8d:
            case 0x8f: printf("ADC\t%c\n", regnum(d&0x7)); break;
            //ADC M
            case 0x8e: printf("ADC\tM\n"); break;
            //SUB r
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
            case 0x95:
            case 0x97: printf("SUB\t%c\n", regnum(d&0x7)); break;
            //SUB M
            case 0x96: printf("SUB\tM\n"); break;
            //SBB r
            case 0x98:
            case 0x99:
            case 0x9a:
            case 0x9b:
            case 0x9c:
            case 0x9d:
            case 0x9f: printf("SBB\t%c\n", regnum(d&0x7)); break;
            //SBB M
            case 0x9e: printf("SBB\tM\n"); break;
            //ANA r
            case 0xa0:
            case 0xa1:
            case 0xa2:
            case 0xa3:
            case 0xa4:
            case 0xa5:
            case 0xa7: printf("ANA\t%c\n", regnum(d&0x7)); break;
            //ANA M
            case 0xa6: printf("ANA\tM\n"); break;
            //XRA r
            case 0xa8:
            case 0xa9:
            case 0xaa:
            case 0xab:
            case 0xac:
            case 0xad:
            case 0xaf: printf("XRA\t%c\n", regnum(d&0x7)); break;
            //XRA M
            case 0xae: printf("XRA\tM\n"); break;
            //ORA r
            case 0xb0:
            case 0xb1:
            case 0xb2:
            case 0xb3:
            case 0xb4:
            case 0xb5:
            case 0xb7: printf("ORA\t%c\n", regnum(d&0x7)); break;
            //ORA M
            case 0xb6: printf("ORA\tM\n"); break;
            //CMP r
            case 0xb8:
            case 0xb9:
            case 0xba:
            case 0xbb:
            case 0xbc:
            case 0xbd:
            case 0xbf: printf("CMP\t%c\n", regnum(d&0x7)); break;
            //CMP M
            case 0xbe: printf("CMP\tM\n"); break;
            //ADI B2
            case 0xc6: printf("ADI\t%x\n", [mem read:i+1]); i++; break;
            //ACI B2
            case 0xce: printf("ACI\t%x\n", [mem read:i+1]); i++; break;
            //SUI B2
            case 0xd6: printf("SUI\t%x\n", [mem read:i+1]); i++; break;
            //SBI B2
            case 0xde: printf("SBI\t%x\n", [mem read:i+1]); i++; break;
            //ANI B2
            case 0xe6: printf("ANI\t%x\n", [mem read:i+1]); i++; break;
            //XRI B2
            case 0xee: printf("XRI\t%x\n", [mem read:i+1]); i++; break;
            //ORI B2
            case 0xf6: printf("ORI\t%x\n", [mem read:i+1]); i++; break;
            //CPI B2
            case 0xfe: printf("CPI\t%x\n", [mem read:i+1]); i++; break;
            //RLC
            case 0x07: printf("RLC\n"); break;
            //RRC
            case 0x0f: printf("RRC\n"); break;
            //RAL
            case 0x17: printf("RAL\n"); break;
            //RAR
            case 0x1f: printf("RAR\n"); break;
            //DAA
            case 0x27: printf("DAA\n"); break;
            //CMA
            case 0x2f: printf("CMA\n"); break;
            //STC
            case 0x37: printf("STC\n"); break;
            //CMC
            case 0x3f: printf("CMC\n"); break;
            //NOP
            case 0x00: printf("NOP\n"); break;
            //LXI B, B2B3
            case 0x01: printf("LXI\tB,%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //LXI D, B2B3
            case 0x11: printf("LXI\tD,%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //LXI H, B2B3
            case 0x21: printf("LXI\tH,%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //LXI SP, B2B3
            case 0x31: printf("LXI\tSP,%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //DAD B
            case 0x09: printf("DAD\tB\n"); break;
            //DAD D
            case 0x19: printf("DAD\tD\n"); break;
            //DAD H
            case 0x29: printf("DAD\tH\n"); break;
            //DAD SP
            case 0x39: printf("DAD\tSP\n"); break;
            //STAX B
            case 0x02: printf("STAX\tB\n"); break;
            //STAX D
            case 0x12: printf("STAX\tD\n"); break;
            //LDAX B
            case 0x0a: printf("LDAX\tB\n"); break;
            //LDAX D
            case 0x1a: printf("LDAX\tD\n"); break;
            //SHLD B3B2
            case 0x22: printf("SHLD\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //LHLD B3B2
            case 0x2a: printf("LHLD\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //STA B3B2
            case 0x32: printf("STA\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //LDA B3B2
            case 0x3a: printf("LDA\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //INX B
            case 0x03: printf("INX\tB\n"); break;
            //INX D
            case 0x13: printf("INX\tD\n"); break;
            //INX H
            case 0x23: printf("INX\tH\n"); break;
            //INX SP
            case 0x33: printf("INX\tSP\n"); break;
            //DCX B
            case 0x0b: printf("DCX\tB\n"); break;
            //DCX D
            case 0x1b: printf("DCX\tD\n"); break;
            //DCX H
            case 0x2b: printf("DCX\tH\n"); break;
            //DCX SP
            case 0x3b: printf("DCX\tSP\n"); break;
            //OUT B2
            case 0xd3: printf("OUT\t%x\n", [mem read:i+1]); i++; break;
            //IN B2
            case 0xdb: printf("IN\t%x\n", [mem read:i+1]); i++; break;
            //HTHL
            case 0xe3: printf("HTHL\n"); break;
            //XCHG
            case 0xeb: printf("XCHG\n"); break;
            //DI
            case 0xf3: printf("DI\n"); break;
            //EI
            case 0xfb: printf("EI\n"); break;
            //PUSH B
            case 0xc5: printf("PUSH\tB\n"); break;
            //PUSH D
            case 0xd5: printf("PUSH\tD\n"); break;
            //PUSH H
            case 0xe5: printf("PUSH\tH\n"); break;
            //PUSH PSW
            case 0xf5: printf("PUSH\tPSW\n"); break;
            //POP B
            case 0xc1: printf("POP\tB\n"); break;
            //POP D
            case 0xd1: printf("POP\tD\n"); break;
            //POP H
            case 0xe1: printf("POP\tH\n"); break;
            //POP PSW
            case 0xf1: printf("POP\tPSW\n"); break;
            //PCHL
            case 0xe9: printf("PCHL\n"); break;
            //SPHL
            case 0xf9: printf("SPHL\n"); break;
            //JMP B3B2
            case 0xc3: printf("JMP\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JNZ B3B2
            case 0xc2: printf("JNZ\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JZ B3B2
            case 0xca: printf("JZ\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JNC B3B2
            case 0xd2: printf("JNC\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JC B3B2
            case 0xda: printf("JC\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JPO B3B2
            case 0xe2: printf("JPO\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JPE B3B2
            case 0xea: printf("JPE\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JP B3B2
            case 0xf2: printf("JP\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //JM B3B2
            case 0xfa: printf("JM\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CALL B3B2
            case 0xcd: printf("CALL\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CNZ B3B2
            case 0xc4: printf("CNZ\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CN B3B2
            case 0xcc: printf("CN\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CNC B3B2
            case 0xd4: printf("CNC\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CC B3B2
            case 0xdc: printf("CC\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CP0 B3B2
            case 0xe4: printf("CP0\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CPE B3B2
            case 0xec: printf("CPE\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CP B3B2
            case 0xf4: printf("CP\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //CM B3B2
            case 0xfc: printf("CM\t%x,%x\n", [mem read:i+1], [mem read:i+2]); i=i+2; break;
            //RET
            case 0xc9: printf("RET\n"); break;
            //RNZ
            case 0xc0: printf("RNZ\n"); break;
            //RZ
            case 0xc8: printf("RET\n"); break;
            //RNC
            case 0xd0: printf("RNC\n"); break;
            //RC
            case 0xd8: printf("RC\n"); break;
            //RPO
            case 0xe0: printf("RPO\n"); break;
            //RPE
            case 0xe8: printf("RPE\n"); break;
            //RP
            case 0xf0: printf("RP\n"); break;
            //RM
            case 0xf8: printf("RM\n"); break;
            //RST
            case 0xc7:
            case 0xcf:
            case 0xd7:
            case 0xdf:
            case 0xe7:
            case 0xef:
            case 0xf7:
            case 0xff: printf("RST\t%x\n",  regnum((d&0x38)>>3)); break;
        }
    }

    //pc = 0x8200;
/*
    int i;
    uint8_t d;
    while (i<10) {
        d = [mem read:pc];
 continue;
        
    }
    */
}
@end
