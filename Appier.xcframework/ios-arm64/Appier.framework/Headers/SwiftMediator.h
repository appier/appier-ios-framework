@class AIQConfiguration;
@class AIQRemoteConfig;

@interface SwiftMediator: NSObject
+ (AIQConfiguration *_Nonnull)aiquaConfig;
+ (void)updateWithRemoteConfig:(AIQRemoteConfig *_Nonnull)remoteConfig;
- (UIWindow *_Nullable)getWindow;
- (void)setWindow:(UIWindow * _Nullable)window;
- (id)unarchiveObjectWithData:(NSData *)data;

@end
