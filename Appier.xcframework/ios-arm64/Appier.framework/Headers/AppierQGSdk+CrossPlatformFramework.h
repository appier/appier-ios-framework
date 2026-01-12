#import <Appier/QGSdk.h>

NS_ASSUME_NONNULL_BEGIN

@interface QGSdk (CrossPlatformFramework)
/**
 * Sets and persists initialization parameters.
 * @param appId App ID.
 * @param appGroup iOS App Group name.
 * @param devProfile YES to enable development mode.
 * @param type Type of the SDK for cross-platform framework. Use nil if not applicable.
 * @param version Vesrion of the SDK for the cross-platform framework. Use nil if not applicable.
 * @note This API is for internal use only.
 */
- (void)onStart:(NSString *)appId withAppGroup:(NSString *)appGroup setDevProfile:(BOOL)devProfile frameworkType:(NSString * _Nullable)type version:(NSString * _Nullable)version;
@end

NS_ASSUME_NONNULL_END
