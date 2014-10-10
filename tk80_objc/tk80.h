//
//  tk80.h
//  tk80
//

#import <Foundation/Foundation.h>
#import "cpu.h"
#import "memory.h"

@interface tk80 : NSObject
{
    cpu *upd8080a;
    memory *mem;
}
- (void)run;
- (void)monitor;
@end
