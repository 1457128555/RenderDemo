#import "RenderEngineWrapper.h"
#import "RenderEngine.h"

#import "MBProgressHUD/MBProgressHUD.h"

@implementation RenderEngineWrapper

#pragma mark - MBProgressHUD 封装

// 显示加载HUD
+ (void)showLoadingHUDInView:(UIView *)view withText:(NSString *)text {
    if (!view) return;
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.label.text = text ?: @"";
}

// 隐藏HUD
+ (void)hideHUDInView:(UIView *)view {
    if (!view) return;
    [MBProgressHUD hideHUDForView:view animated:YES];
}

// 显示文本提示
+ (void)showTextHUDInView:(UIView *)view text:(NSString *)text delay:(NSTimeInterval)delay {
    if (!view) return;
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.label.text = text ?: @"";
    hud.offset = CGPointMake(0.f, MBProgressMaxOffset);
    [hud hideAnimated:YES afterDelay:delay > 0 ? delay : 2.0];
}

// 显示带进度的HUD
+ (MBProgressHUD *)showProgressHUDInView:(UIView *)view text:(NSString *)text {
    if (!view) return nil;
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.mode = MBProgressHUDModeDeterminate;
    hud.label.text = text ?: @"";
    return hud;
}

+ (void)initRenderEngine {

    NSString *assetPath = [[NSBundle mainBundle] pathForResource:@"Asset" ofType:nil];
    const char* cAssetPath = [assetPath UTF8String];
    initRenderEngine(cAssetPath);
}

+ (void)renderOneFrame {
    renderOneFrame();
}

+ (void)quitRenderEngine {
    quitRenderEngine();
}

// 带HUD的 onPlayBottom
+ (void)onPlayBottomInView:(UIView *)view {
    [self showLoadingHUDInView:view withText:@"正在处理..."];
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
        onPlayBottom();
        dispatch_async(dispatch_get_main_queue(), ^{
            [self hideHUDInView:view];
        });
    });
}

+ (void)onPlayBottom{
    onPlayBottom();
}

+ (void)setLutIntensity:(float)value {
    setLutIntensity(value);
}



@end
