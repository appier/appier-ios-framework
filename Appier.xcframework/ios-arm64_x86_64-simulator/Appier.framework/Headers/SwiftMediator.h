@class AIQConfiguration;
@class AIQRemoteConfig;

@interface SwiftMediator: NSObject
+ (AIQConfiguration *)aiquaConfig;
+ (void)updateWithRemoteConfig:(AIQRemoteConfig *)remoteConfig;
- (UIWindow *_Nullable)getWindow;
- (void)setWindow:(UIWindow * _Nullable)window;

@end
