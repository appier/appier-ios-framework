//
//  QGNotificationServiceExtension.h
//  Appier
//
//  Created by chunta on 2020/7/3.
//  Copyright © 2020 chunta. All rights reserved.
//

#import <UserNotifications/UserNotifications.h>

NS_ASSUME_NONNULL_BEGIN

DEPRECATED_MSG_ATTRIBUTE("Notification extension support will be removed from AppierFramework in a future version. Please link to AppierExtensionFramework in your notification extensions.")
@interface QGNotificationService : UNNotificationServiceExtension

@end

NS_ASSUME_NONNULL_END
