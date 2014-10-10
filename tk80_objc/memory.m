//
//  mem.m
//  tk80
//

#import "memory.h"

#define RAM_BEGIN 0x0000
#define RAM_END 0xffff

uint8_t array[RAM_END-RAM_BEGIN];

@implementation memory
- (uint8_t)read:(uint16_t)addr
{
    uint16_t data;
    if (addr>=RAM_BEGIN && addr<=RAM_END) {
        data = array[addr-RAM_BEGIN];
    } else {
        data = 0;
    }
    printf("r %4x: %2x\n", addr, data);
    return data;
}

- (void)write:(uint16_t)addr with:(uint8_t)data
{
    if (addr>=RAM_BEGIN && addr<=RAM_END) {
        array[addr-RAM_BEGIN] = data;
        printf("w %4x: %2x\n", addr, data);
    }
}

- (BOOL)load:(char *)fileName from:(uint16_t)addr;
{
    FILE *fp;
    if ((fp = fopen(fileName, "rb"))==NULL) {
        printf("no file.\n");
        return FALSE;
    }
    char c;
    int i = 0;
    while ((c=getc(fp))!=EOF) {
        [self write:addr+i with:(uint8_t)c];
        i++;
    }
    fclose(fp);
    return TRUE;
}
@end
