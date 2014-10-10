//
//  cpu.h
//  tk80
//

#import <Foundation/Foundation.h>
#import <math.h>
#import "memory.h"

@interface cpu : NSObject
{
    uint16_t pc;
    uint16_t sp;
    
    memory *mem;
}
@property uint16_t pc;
@property uint16_t sp;
- (void)execute;
- (id)initWith:(memory* )memory;
@end
