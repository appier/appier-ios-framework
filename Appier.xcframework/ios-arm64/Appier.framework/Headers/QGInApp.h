//
//  QGInApp.h
//  QGSdk
//
//  Created by Shiv on 01/04/16.
//  Copyright © 2019 APPIER INC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QGImageManager.h"
#import "AIQInAppCondition.h"

typedef NS_ENUM(NSInteger, InAppType){
    InAppTypeUnknown = -1,
    InAppTypeControlGroup = 0,
    InAppTypeText = 1,
    InAppTypeImage = 2, // Deprecated
    InAppTypePopup = 3,
    InAppTypeInbox = 4, // The enum is not used in codebase, though inbox is still working
    InAppTypeWebView = 5,
    InAppTypeCreativeStudio = 6,
};

typedef NS_ENUM(NSInteger, InAppPersistency) {
    InAppPersistencyPersist = 0,
    InAppPersistencyKillWhenDeepLinkClicked = 1,
    InAppPersistencyNotPersist = 2
};

@class AIQInAppCondition;
@class AIQInAppAdditionalCondition;
@class AIQInAppBadgeSetting;

@interface WhenCond: NSObject<NSCoding>
@property (nonatomic) NSString *eventName;
@property (nonatomic) NSString *operators;
@property (nonatomic, retain) NSArray <AIQInAppCondition *> * conditions;
@end


@interface QGInApp: NSObject<NSCoding>
@property (nonatomic) NSNumber *notificationId;
@property (nonatomic) NSNumber *messageNo;
@property (nonatomic) InAppType type;
@property (nonatomic) NSString *icon;          //bubble button image
@property (nonatomic) NSString *gravity;       //top or bottom
@property (nonatomic) float margin;             //margin for bubble button
@property (nonatomic) NSString *deepLink;
@property (nonatomic) NSString *text;          //text for message view for type 1
@property (nonatomic) NSString *htmlCreative;
@property (nonatomic, retain) WhenCond *whenCond;
@property (nonatomic, retain) AIQInAppAdditionalCondition *preconditions;
@property (nonatomic) NSDictionary *fbCreative;
@property (nonatomic, retain) AIQInAppBadgeSetting *badge; // The setting for the badge button.
@property (nonatomic) long long startTime;
@property (nonatomic) long long endTime;
@property (nonatomic) NSInteger maxNumTimesToShow;
@property (nonatomic) NSInteger numShown;
@property (nonatomic, assign) BOOL neverShowAgain; //needed by InAppWebView
@property (nonatomic, assign) BOOL showOnce;
@property (nonatomic, assign) BOOL hasShown;
@property (nonatomic, assign) BOOL expanded;
@property (nonatomic, assign) BOOL sendReceipt;
@property (nonatomic, assign) BOOL killOnCollapse;
@property (nonatomic, assign) BOOL killOnDeepLinkClick;
@property (nonatomic, assign) BOOL badgeCloseButton;
@property (nonatomic, assign) BOOL creativeCloseButton;
@property (nonatomic) InAppPersistency persistency;
@property (nonatomic, assign) BOOL showOverlay;
@property (nonatomic) NSDictionary *creativeStudio;

//frequency cap
@property (nonatomic) NSInteger frequency;    //how many times
@property (nonatomic) NSInteger cycle;        //day
@property (nonatomic) NSInteger msgInterval; //minute
@property (nonatomic) NSMutableArray *displayHistory;
//delay display
@property (nonatomic, assign) NSInteger delayTime;

- (id)initWithDictionary:(NSDictionary *)campaign;

+ (BOOL)isValidInApp:(QGInApp *)qgInApp withDate:(NSDate *)now;
+ (BOOL)isValidFrequencyCapWithInApp:(QGInApp *)qgInApp withDate:(NSDate *)now;
+ (BOOL)isExpiredInApp:(QGInApp *)qgInApp;
+ (BOOL)isInvalidCreativeStudio:(QGInApp *)inApp;
- (void)downloadIconResourcesWithCompletionHandler:(void(^)(BOOL))completionHandler;
- (void)downloadImageResourcesWithCompletionHandler:(void(^)(BOOL))completionHandler;
- (NSString *)fbImageUrl;
@end
