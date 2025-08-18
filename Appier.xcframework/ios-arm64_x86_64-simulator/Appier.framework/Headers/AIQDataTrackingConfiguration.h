#ifndef AIQDataTrackingConfiguration_h
#define AIQDataTrackingConfiguration_h

NS_ASSUME_NONNULL_BEGIN
@protocol AIQDataTrackingConfigurationDelegate <NSObject>
- (void)updateUserDetailWhenDataTrackingConfigChanged;
@end

@interface AIQDataTrackingConfiguration: NSObject
@property (nonatomic, assign) BOOL isCollectIDFA;
@property (nonatomic, assign) BOOL isCollectLocation;
- (instancetype)initWithIsCollectIDFA:(BOOL)isCollectIDFA isCollectLocation:(BOOL)isCollectLocation;
- (BOOL)isSameConfigWith:(AIQDataTrackingConfiguration *)targetConfig;
@end

NS_ASSUME_NONNULL_END
#endif /* AIQDataTrackingConfiguration_h */
