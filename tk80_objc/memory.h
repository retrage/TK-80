//
//  mem.h
//  tk80
//

#import <Foundation/Foundation.h>

@interface memory : NSObject
- (uint8_t)read:(uint16_t)addr;
- (void)write:(uint16_t)addr with:(uint8_t)data;
- (BOOL)load:(char *)fileName from:(uint16_t)addr;
@end
