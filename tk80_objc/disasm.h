//
//  disasm.h
//  tk80
//

#import <Foundation/Foundation.h>
#import "memory.h"

@interface disasm : NSObject
{
    memory *mem;
}
@property (nonatomic, strong)memory *mem;
- (void)disasm;

@end
