//
//  tk80.m
//  tk80
//

#import "tk80.h"

@implementation tk80

- (instancetype)init
{
    self = [super init];
    if (self) {
        mem = [[memory alloc] init];
        upd8080a = [[cpu alloc] initWith:mem];
    }
    return self;
}

- (void)run
{
    int i;
    if([mem load:"basic_program" from:0x8200]) {
        upd8080a = [[cpu alloc] initWith:mem];
        upd8080a.pc = 0x8200;
    
        for (i=0; i<9; i++) {
            [upd8080a execute];
        }
    }
}

- (void)monitor
{
    char c;
    uint16_t data = 0x0000;
    uint16_t addr = 0x8000;
    //uint8_t operand = 0x00;
    while (c) {
        printf("%4x> ", addr);
        scanf("%c %hx", &c, &data);
        // 'h' = address set
        // 'j' = read increment
        // 'k' = read decrement
        // 'l' = write increment
        // 'r' = run
        switch (c) {
            case 'h':
                addr = data;
                break;
            case 'j':
                data = [mem read:addr];
                printf("%4x %4x\n", addr, data);
                addr++;
                break;
            case 'k':
                data = [mem read:addr];
                printf("%4x %4x\n", addr, data);
                addr--;
                break;
            case 'l':
                [mem write:addr with:data];
                addr++;
                break;
            case 'r':
                [upd8080a execute];
                break;
            default:
                break;
        }
    }
}
@end
