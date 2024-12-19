#import <Foundation/Foundation.h>
#import <UIKit/UITapGestureRecognizer.h>
#import "QGImageManager.h"

@class QGInApp;
@class AIQConfiguration;
@class AIQLocalStorage;

@protocol QGInAppDisplayManagerDelegate <NSObject>
- (void)inAppViewRemoved;
- (void)inWebViewPermanentClosed:(NSNumber *)nId;
- (void)renewInApp:(QGInApp *)inApp;

- (void)didFailToDisplayInAppWithNotificationId:(NSNumber *)notificationId eventName:(NSString *)eventName param:(NSDictionary *)param;
@end

@interface InAppTapGestureRecognizer : UITapGestureRecognizer
@property (nonatomic, strong) QGInApp *tappedInApp;
@end

@interface QGInAppDisplayManager : NSObject
@property (nonatomic, weak) id<QGInAppDisplayManagerDelegate> delegate;
@property (nonatomic, strong) UIWindow *overlayWindow;
- (instancetype)init __attribute__((unavailable));
- (instancetype)initWithImageManager:(QGImageManager *)imageManager config:(AIQConfiguration *)config storage:(AIQLocalStorage *)storage;
- (void)createInAppFor:(QGInApp *)qginApp eventName:(NSString *)eventName param:(NSDictionary *)param;
- (void)simplyRemoveAllInAppViews;
- (void)removeAllInAppViewsAndClearCurrentInApp;
- (void)prepareInAppPopupCreative:(QGInApp *)qgInApp;
- (void)setInAppCampaignVisible:(BOOL)isVisible;
@end
