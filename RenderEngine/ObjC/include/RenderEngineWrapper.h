#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface RenderEngineWrapper : NSObject

+ (void)initRenderEngine;
+ (void)renderOneFrame;
+ (void)quitRenderEngine;

+ (void)onPlayBottom;
+ (void)onPlayBottomInView:(UIView *)view;
+ (void)setLutIntensity:(float)value;
@end
