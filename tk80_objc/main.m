//
//  main.m
//  tk80
//

#import <Foundation/Foundation.h>
#import "tk80.h"
#import "disasm.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
//        char c[10];
//        int i;
//        c[0] = 0x3c;
//        c[1] = 0xaa;
//        c[2] = 0x3e;
//        c[3] = 0xb0;
//        c[4] = 0x3e;
//        c[5] = 0xcc;
//        c[6] = 0xc3;
//        c[7] = 0x00;
//        c[8] = 0x82;
//        c[9] = 0x76;
//        
//        disasm *disamtest = [[disasm alloc] init];
//        for (i=0; i<10; i++) {
//            [disamtest.mem write:0x8200+i with:c[i]];
//        }
//        [disamtest disasm];
        /*memory *mem = [[memory alloc] init];
        for (i=0; i<10; i++) {
            [mem write:0x8200+i with:c[i]];
        }
        NSLog(@"%x\n",[mem read:0x8200]);*/
        
        tk80 *vm;
        vm = [[tk80 alloc] init];
        [vm monitor];
    }
    return 0;
}

