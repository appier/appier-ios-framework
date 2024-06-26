@class AIQConfiguration;
@class AIQRemoteConfig;

@interface SwiftMediator: NSObject
+ (AIQConfiguration *)aiquaConfig;
+ (void)updateWithRemoteConfig:(AIQRemoteConfig *)remoteConfig;
@end
