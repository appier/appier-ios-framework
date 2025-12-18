#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>
#import <UserNotifications/UserNotifications.h>
#import "QGInbox.h"
#import "QGInApp.h"
#import "AIQInAppCondition.h"
#import "AIQMutableOrderedDictionary.h"
#import "AIQDataTrackingConfiguration.h"
#import "SwiftMediator.h"
//#import "AppierError.h"
//#import "AsyncResult.h"

@class AIQRecommendationRequest;
@class AIQRecommendationTagResponse;
@class AIQRecommendationProductResponse;
@protocol AIQEventLoggingProtocol;
@protocol AIQUserProfileLoggingProtocol;
@protocol AIQRecommendationLoggingProtocol;
@protocol AIQInAppRecommendationDataProviderProtocol;
@protocol AIQEventAttributionProtocol;
@protocol APRPushNotificationNotifierDelegate;

NS_ASSUME_NONNULL_BEGIN

/// This is the JavaScript to be injected into custom web view, in order to track custom events and attributes
extern NSString * _Nonnull QGWKWebViewUserScript;

@interface AiquaSDKImpl : NSObject <AIQEventLoggingProtocol, AIQUserProfileLoggingProtocol, AIQRecommendationLoggingProtocol, AIQInAppRecommendationDataProviderProtocol, AIQEventAttributionProtocol>

/*!
 @abstract
 Flush timer's interval.

 @discussion
 Setting a flush interval of 0 will turn off the flush timer.

 @note Default to 1 sec in Dev and 15 secs in Release
 */
@property (atomic) NSUInteger flushInterval;

/*!
 @abstract
 Data Tracking Configuration.

 @discussion
 Setting the data tracking configuration of the sdk.
 */
@property (nonatomic, strong, nonnull) AIQDataTrackingConfiguration *dataTrackingConfig;

/*!
 @abstract
 Use `[QGSdk getSharedInstance]` instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @discussion
 Initialises QGSdk and returns the shared instance of the sdk,
 to access all the methods of the sdk

 @result QGSdk instance
 */
+ (AiquaSDKImpl *) getSharedInstance;

/*!
 @method

 @abstract
 Register UNNotificationCategory for Carousel Action Buttons.

 @discussion
 Registers the UNNotificationCategory for custom notification(Carousel) with the action buttons.
 If there are no action buttons, this method can be used to directly register the carousel actions.
 If there are other action category to be registered, get the QGCAROUSEL category and
 register along with other categories. Use `getQGSliderPushActionCategoryWithNextButtonTitle` method.
 By default, sdk will register this with deault buttons.

 iOS 11 and below has Next button (to scroll item) and open app button (for deeplink).
 iOS 12 and above, user interaction is enabled, so only open app button is shown.

 @param next            optional next button title, default to '▶▶' (iOS 11 and below)
 @param openApp         optional open app button title, default to 'Open App'

 @code
 [QGSdk setCarouselNotificationCategoryWithNextButtonTitle:nil withOpenAppButtonTitle:nil];

 [QGSdk setCarouselNotificationCategoryWithNextButtonTitle:@"Next" withOpenAppButtonTitle:@"Check Out"];
 @endcode

 */
+ (void)setCarouselNotificationCategoryWithNextButtonTitle:(nullable NSString *)next withOpenAppButtonTitle:(nullable NSString *)openApp API_AVAILABLE(ios(10.0));

/*!
 @method

 @abstract
 Register UNNotificationCategory for Carousel Action Buttons.

 @discussion
 Registers the UNNotificationCategory for custom notification(Carousel) with the action buttons. If you have other notification action category, add along with this category. By default, sdk will register this with deault buttons.

 iOS 11 and below has Next button (to scroll item) and open app button (for deeplink).
 iOS 12 and above, user interaction is enabled, so only open app button is shown.

 @param next            optional next button title, default to '▶▶' (iOS 11 and below)
 @param openApp         optional open app button title, default to 'Open App'

 @code
 [QGSdk getQGSliderPushActionCategoryWithNextButtonTitle:nil withOpenAppButtonTitle:nil];

 [QGSdk getQGSliderPushActionCategoryWithNextButtonTitle:@"Next" withOpenAppButtonTitle:@"Check Out"];
 @endcode

 */
+ (UNNotificationCategory *)getQGSliderPushActionCategoryWithNextButtonTitle:(nullable NSString *)next withOpenAppButtonTitle:(nullable NSString *)openApp API_AVAILABLE(ios(10.0));

/*!
 @abstract
 Set the Associated Domains for Universal Links

 @discussion
 For Apps using universal links instead of URI scheme, they should pass the related domains. For all the notifications, sdk will route to continueUserActivity if domains are set else all the cliks would route to default browser Safari.

 @param domains         The Associated Universal Link Domains

 @code
 [[QGSdk getSharedInstance] setUniversalLinkDomains:@[@"first.domain.com", @"second.domain.com]];
 @endcode
 */
- (void)setUniversalLinkDomains:(NSArray <NSString *> *)domains;

/*! This method is not used currently */
- (void)onStop;

/*!
 @abstract
 Enable or disable data transmission to AIQUA servers

 @discussion
 This method controls whether the SDK should send data to AIQUA servers.
 When disabled, the following operations will be blocked:
 - Event logging (logEvent methods)
 - User profile updates (setUserId, setName, setEmail, etc.)
 - User detail logging
 - Analytics data transmission

 @param enable `YES` to enable data transmission (default behavior),
               `NO` to disable all data transmission to servers

 @note Local data operations and UI features (like InApp campaigns display)
       may still function when data transmission is disabled.
 */
- (void)enableSendData:(BOOL)enable;

/*!
 @abstract
 Get AIQUA App ID from storage
 */
- (nullable NSString *)getAppId;

- (BOOL)getShowPushPrompt DEPRECATED_MSG_ATTRIBUTE();

/*!
 @abstract
 Sends the APNS token to QGraph Server

 @discussion
 Set the Device Token received from APNS in the AppDelegate.
 This method is required to identify device for sending push notification.

 @note Implement this in @code application:didRegisterForRemoteNotificationsWithDeviceToken: @endcode to setToken
 */
- (void)setToken:(NSData *)tokenData;

/*!
 @abstract
 Sends the IDFA only when user's ads tracking status is ATTrackingManagerAuthorizationStatusAuthorized

 @discussion
 If Yes, IDFA will be send only when user's ads tracking status is ATTrackingManagerAuthorizationStatusAuthorized;
 No, send it in any status including invalid IDFA 0000
 */
- (void)setIDFAConsent:(BOOL)idfaConsent;

/*!
 @abstract
 Set Push Token from Firebase

 @discussion
 For App integrated with Firebase, use this method to set the push token generated by Firebase

 @param token   Push Token String

 @code
 // Use FIRMessagingDelegate
 // Firebase FCM subscribe to any topic
 - (void)messaging:(FIRMessaging *)messaging didReceiveRegistrationToken:(NSString *)fcmToken {
 // Note: This callback is fired at each app startup and whenever a new token is generated.
 [[QGSdk getSharedInstance] setFCMToken:fcmToken];
 }
 @endcode
 */
- (void)setFCMToken:(nullable NSString *)token;

/*!
 @abstract
 Set the unique user id for your users

 @discussion
 you can identify your user with user_id while creating segment on app.qgraph.io
 */
- (void)setUserId:(nullable NSString *)userId;

/*! @abstract Set the name of the user */
- (void)setName:(nullable NSString *)name;

/*! @abstract Set the first name of the user */
- (void)setFirstName:(nullable NSString *)name;

/*! @abstract Set the last name of the user */
- (void)setLastName:(nullable NSString *)name;

/*! @abstract Set the city of the user */
- (void)setCity:(nullable NSString *)city;

/*! @abstract Set the email id of the user */
- (void)setEmail:(nullable NSString *)email;

/*! @abstract Set the phone number of the user */
- (void)setPhoneNumber:(nullable NSString *)phoneNo;

/*! @abstract Set the day of DOB of the user */
- (void)setDayOfBirth:(nullable NSNumber *)day;

/*! @abstract Set the month of DOB of the user */
- (void)setMonthOfBirth:(nullable NSNumber *)month;

/*! @abstract Set the year of DOB of the user */
- (void)setYearOfBirth:(nullable NSNumber *)year;

/*!
 @abstract
 Set any custom key for your user

 @discussion
 Use this method to set any custom key for the user.
 Suppose you want to set rating of the user.

 @code setCustomKey:@"rating" withValue:3.5 @endcode
 */
- (void)setCustomKey:(NSString *)key withValue:(nullable id)value;

/*!
 @abstract
 Creates a new AIQUA userId and clean all local data related the previous userId

 @discussion
 Creates a new AIQUA userId, and clean local cache related to previous userId including
 Log Events, Push Notifications, InBox, InApp Campaigns and so on.
 Refer to documentation for some use cases when this method should be used.
 */
- (void)renewUserId:(void (^)(void))completionHandler DEPRECATED_MSG_ATTRIBUTE("Use renewAppierId:completionHandler: instead.");

/*!
 @abstract
 Creates a new AIQUA Appier ID and clean all local data related the previous Appier ID

 @discussion
 Creates a new AIQUA Appier ID, and clean local cache related to previous Appier ID including
 Log Events, Push Notifications, InBox, InApp Campaigns and so on.
 Refer to documentation for some use cases when this method should be used.
 */
- (void)renewAppierId:(nullable void (^)(void))completionHandler;

/*!
 @abstract
 Performs comprehensive cleanup and reset of the SDK state with optional Appier ID renewal.
 
 @discussion
 This method performs a complete reset of the AIQUA SDK internal state.

 This method is typically used during App ID switching scenarios where a complete
 state reset is required to ensure clean separation between different app contexts.
 
 @param shouldRenewAppierID If YES, generates a new Appier ID and saves it to storage.
                           If NO, preserves the current Appier ID.
 @param completionHandler  Called asynchronously when all cleanup operations complete.
                          The handler is executed on a background queue.
 
 @warning This operation is destructive and will permanently remove all cached data,
          logged events, and campaign information. Use with caution.
 */
- (void)cleanupAndResetStateWithAppierIDRenewal:(BOOL)shouldRenewAppierID completionHandler:(void (^)(void))completionHandler;



- (void)uploadUserDetailsAndGCMIdWithCompletionHandler:(nullable void (^)(void))completionHandler;

/*!
 @abstract
 Get AIQUA Appier ID from storage

 @discussion
 Get AIQUA Appier ID from storage
 */
- (NSString *)getAppierId;

/*!
 @abstract
 Sends any event in your app to the QGraph server

 @discussion
 This methods help you track any particular event.
 for example, viewing the products, playing a game or listening to a music

 eg: logEvent:@"product_viewed"

 @param name            name of the event
 */
- (void)logEvent:(NSString *)name;

/*!
 @abstract
 Track any event in your app with custom parameter

 @discussion
 Same as logEvent: but with some parameter in form of dictionary.
 You can pass custom parameter for the particular event.

 eg: for event: product_viewed, you want to track name of the product, brand, image url or any other details.

 @note use valid data types in dictionary

 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 */
- (void)logEvent:(NSString *)name withParameters:(nullable NSDictionary *)parameters;

/*!
 @abstract
 Track any event in your app with monetary value associated to it

 @discussion
 eg: for event: product_viewed, price of the product is Rs 50

 @note Use value in the form of NSNumber

 @param name            name of the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 */
- (void)logEvent:(NSString *)name withValueToSum:(nullable NSNumber *)valueToSum;

/*!
 @abstract
 Track any event in your app with monetary value associated to it along with its currency

 @discussion
 eg: for event: product_viewed, price of the product is 50 INR or 1 USD

 @note Use value in the form of NSNumber and 3 character currency code

 @param name            name of the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 @param vtsCurr         currency code of the value to sum
 */
- (void)logEvent:(NSString *)name withValueToSum:(nullable NSNumber *)valueToSum withValueToSumCurrency:(nullable NSString *)vtsCurr;

/*!
 @abstract
 Track any event in your app with custom parameters and monetary value associated to it

 @discussion
 Combination of logEvent:withParameter and logEvent:valueToSum

 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 */
- (void)logEvent:(NSString *)name withParameters:(nullable NSDictionary *)parameters withValueToSum:(nullable NSNumber *) valueToSum;

/*!
 @abstract
 Track any event in your app with custom parameters and monetary value associated to it along with its currency

 @discussion
 Combination of logEvent:withParameter and logEvent:withValueToSum:withValueToSumCurrency

 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 @param vtsCurr         currency code of the value to sum
 */
- (void)logEvent:(NSString *)name withParameters:(nullable NSDictionary *)parameters withValueToSum:(nullable NSNumber *) valueToSum withValueToSumCurrency:(nullable NSString *)vtsCurr;

/*!
 @abstract
 Convert the parameters into several events for tracking.

 @discussion
 Combination of logEvent:withParameter and logEvent:withValueToSum:withValueToSumCurrency:withConvertedEvent:withAttributeEnable

 @param name            name of the event
 @param parameters      dictionary of all the parameter for the event
 @param valueToSum      monetary value (NSNumber) associated to the event
 @param vtsCurr         currency code of the value to sum
 @param convertedEventName    name of multi-parameters event
 @param enabled         enabled / disabled sending attribution info

 @deprecated in version 7.18.0
 */
- (void)logEvent:(NSString *)name withParameters:(NSDictionary *)parameters withValueToSum:(nullable NSNumber *)valueToSum withValueToSumCurrency:(nullable NSString *)vtsCurr withConvertedEvent:(nullable NSString *)convertedEventName withAttributionEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("Use logEvent:withParameters:withValueToSum:withValueToSumCurrency: instead.");


/*!
 @abstract
 Clear summary explaining the method deletes logged events from memory queue by event name.

 @param eventName   Must be a non-empty string, all events with exact name match will be removed
 @param completion  Optional handler that receives the number of deleted events
 */
- (void)deleteLogEventWithName:(NSString *)eventName
                    completion:(nullable void(^)(NSInteger deletedCount))completion;

/*!
 @abstract
 Sets the Click Through Attribution Window for event attribution

 @discussion
 This method should be used to set the click through attribution window.
 Click through works for push notification (sent by QGraph) clicks and InApp Notification clicks.
 Default to 24 hrs (86400 secs).

 eg: for click attribution window to be 12 hrs, pass the value: 43200

 @note Setting Click Attribution Window as '0' is not supported. In case, you set '0', SDK will fallback to default window (86400 secs).

 @param seconds         click attribution window time in seconds
 */
- (void)setClickAttributionWindow:(NSInteger)seconds;

/*!
 @abstract
 Sets the View Through Attribution Window for event attribution

 @discussion
 This method should be used to set the View through attribution window.
 View through attribution works only for InApp notifications.
 Default to 1 hr (3600 secs).

 eg: for view through attribution window to be 2 hrs, pass the value: 7200

 @note Setting Attribution Window as '0' is not supported. In case, you set '0', SDK will fallback to default window (3600 secs).

 @param seconds         attribution window time in seconds
 */
- (void)setAttributionWindow:(NSInteger)seconds;

/*!
 @abstract
 Disables In-App campaigns

 @discussion
 This method allows to enable and disable InApp campaigns to be delivered to device
 By default it is enabled, set 'YES' to disable it
 Disabling it will prevent device to get any new InApp Campaigns

 @note Use @code disableInAppCampaigns:YES @endcode to Disable
 */
- (void)disableInAppCampaigns:(BOOL)disabled;

- (void)setInAppCampaignVisible:(BOOL)isVisible;
- (void)hideInAppCampaigns;

/*!
 @abstract
 Tracks application launch finish

 @discussion
 Add this method to your AppDelegate applicaiton:didFinishLaunchingWithOptions:
 */
- (void)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

/*!
 @abstract
 Captures the push notification sent by QGraph server

 @discussion
 Add to your AppDelegate application:didReceiveRemoteNotification:
 Implement this method if your app supports iOS 9
 pass all the push notifications received by the app
 This method also let the sdk track app_launched event due to click on the notification sent by QGraph
 */
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;

/*!
 @abstract
 Tells the app that a remote notification arrived that indicates there is data to be fetched.

 @discussion
 Add to your AppDelegate application:didReceiveRemoteNotification:fetchCompletionHandler:
 This method handles the silent push notifications sent by QGraph
 */
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))fetchCompletionHandler;

/*!
 @abstract
 Captures the push notification delivered in foreground.

 @discussion
 Add to your AppDelegate or class implementing your UNNotificationCenterDelegate methods.
 @code
 [[QGSdk getSharedInstance] userNotificationCenter:center willPresentNotification:notification];
 @endcode

 The delegate method can be used to show the notification alert in the foreground State.
 In your completion handler, pass your UNNotificationPresentationOptions.

 For eg:
 @code
 UNNotificationPresentationOptions option = UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionSound | UNNotificationPresentationOptionAlert;
 completionHandler(option);
 @endcode

 */
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification API_AVAILABLE(ios(10.0));

/*!
 @abstract
 Captures the push notification clicked event.

 @discussion
 Add to your AppDelegate or class implementing your UNNotificationCenterDelegate methods.

 The method will be called on the delegate when the user responded to the notification by opening the application or choosing a UNNotificationAction.

 @code
 [[QGSdk getSharedInstance] userNotificationCenter:center didReceiveNotificationResponse:response];
 @endcode
 */
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response API_AVAILABLE(ios(10.0));

/*!
 @abstract
 Uploads queued data to the QGraph server.

 @discussion
 By default, queued data is flushed to the QGraph servers every 15 seconds (the
 default for flushInterval). You only need to call this
 method manually if you want to force a flush at a particular moment.
 */
- (void)flush;

/*!
 @abstract
 Calls flush, then calls a handler when finished.

 @discussion
 When calling flush manually, it is sometimes important to verify
 that the flush has finished before further action is taken.
 The completion handler provides a success parameter indicating
 whether the flush operation completed successfully.

 @param handler A completion block that is called when the flush operation completes.
                The success parameter indicates whether the flush was successful (YES) or failed (NO).
 */
- (void)flushWithCompletion:(nullable void (^)(BOOL success))handler;

/**
 * Flushes the data queue with an option to guarantee execution.
 *
 * If guaranteed is YES and a flush is already in progress, the handler will be queued
 * and executed after the current flush completes.
 *
 * @param handler A completion block that is called when the flush operation completes.
 * @param guaranteed Whether to queue the flush if one is already in progress.
 */
- (void)flushWithCompletion:(nullable void (^)(BOOL success))handler guaranteed:(BOOL)guaranteed;

/*!
 @abstract
 This is a no-op API to keep backward compatibility without breaking any compiler.

 @deprecated in version 7.16.3
 */
- (void)getRecommendationForModelUserToProductWithCompletion:(void (^)(NSArray *response))completion DEPRECATED_MSG_ATTRIBUTE("Use getRecommendationWithScenarioId:withQueryParameters:withCompletion:  instead");

/*!
 @abstract
 This is a no-op API to keep backward compatibility without breaking any compiler.

 @deprecated in version 7.16.3
 */
- (void)getRecommendationForModelUserToProductWithCategory:(NSString * _Nullable)category withSubCategory:(NSString * _Nullable)subCategory
                                        withSubSubCategory:(NSString * _Nullable)subSubCategory
                                            withCompletion:(void (^)(NSArray *response))completion DEPRECATED_MSG_ATTRIBUTE("Use getRecommendationWithScenarioId:withQueryParameters:withCompletion:  instead");

/*!
 @abstract
 Returns recommendation data with 2.0 url for the user with scenario Id and query string

 @discussion
 This is a asynchronous function which returns an array of recommended objects with a scenario Id and an optional dictionary for query string that may contain filter.

 @param scenarioId ScenarioId

 @param queryStringDict Dictionary to make a query string

 @code
 [[QGSdk getSharedInstance] getRecommendationWithScenarioId:@"sid" withQueryParameters:@{@"pid":@"XXX-SKU"} withCompletion:^(NSArray * response) {
 if (response) {
 QGLog(@"totoal elements:%lu", (unsigned long)response.count);
 }
 }];
 @endcode

 Parse the response object and use it as required
 */
- (void)getRecommendationWithScenarioId:(NSString *)scenarioId
                    withQueryParameters:(NSDictionary * _Nullable)queryStringDict
                         withCompletion:(void (^)(NSArray * response))completion DEPRECATED_MSG_ATTRIBUTE("Use getRecommendationWithScenarioId:withQueryParameters:withCompletionHandler:  instead");

/*!
 @abstract
 Returns recommendation data with 2.0 url for the user with scenario Id and query string

 @discussion
 This is a asynchronous function which returns a dictonary of recommended objects with a scenario Id and an optional dictionary for query string that may contain filter.

 @param scenarioId ScenarioId

 @param queryStringDict Dictionary to make a query string

 @code
 [[QGSdk getSharedInstance] getRecommendationWithScenarioId:@"sid" withQueryParameters:@{@"pid":@"XXX-SKU"} withCompletionHandler:^(id _Nullable response) {
 if (response) {
 QGLog(@"You can parse response");
 }
 }];
 @endcode

 Parse the response object and use it as required
 */
- (void)getRecommendationWithScenarioId:(NSString *)scenarioId withQueryParameters:(NSDictionary * _Nullable)queryStringDict withCompletionHandler:(void (^)(id _Nullable response))completion;

/*!
 @abstract
 Returns recommendation data with 2.0 url for the user with scenario Id and query string

 @discussion
 This is an asynchronous function which returns a dictionary of recommended objects with a scenario Id and an optional dictionary for query string that may contain filter.

 @param scenarioId ScenarioId

 @param productId ProductId

 @param queryStringDict Dictionary to make a query string

 @code
 [[QGSdk getSharedInstance] getRecommendationWithScenarioId:@"sid" withProductId:@"XXX-SKU" withQueryParameters:@{@"param01":@"value"} withCompletionHandler:^(id _Nullable response) {
 if (response) {
 QGLog(@"You can parse response");
 }
 }];
 @endcode

 Parse the response object and use it as required
 */
- (void)getRecommendationWithScenarioId:(NSString *)scenarioId
                          withProductId:(NSString *)productId
                    withQueryParameters:(NSDictionary * _Nullable)queryStringDict
                  withCompletionHandler:(void (^)(id _Nullable response))completion;

/*!
 @abstract
 Returns recommendation tags based on the actual request type.

 @discussion
 This is an asynchronous function that returns a dictionary of recommended tag objects. To use it, select the appropriate request based on your scenario and initialize it using the corresponding builder.

 @param request ScenarioId

 @code
 AIQRecommendationPopularTagsRequestBuilder *builder = [AIQRecommendationPopularTagsRequestBuilder new];
 NSError *error = [NSError new];
 AIQRecommendationPopularTagsRequest *request = [[builder setScenarioId:@"sid"] buildWithError:&error];
 [[QGSdk getSharedInstance] getRecommendationTagsWithRequest:request withCompletionHandler:^(AIQRecommendationTagResponse _Nullable response) {
 if (response) {
 QGLog(@"You can parse response");
 }
 }];
 @endcode

 Parse the response object and use it as required
 */
- (void)getRecommendationTagsWithRequest:(AIQRecommendationRequest *)request
                   withCompletionHandler:(void (^)(AIQRecommendationTagResponse * _Nullable response))completion;

/*!
 @abstract
 Returns recommendation tags based on the actual request type.

 @discussion
 This is an asynchronous function that returns a dictionary of recommended product objects. To use it, select the appropriate request based on your scenario and initialize it using the corresponding builder.

 @param request ScenarioId

 @code
 AIQRecommendationTagToProductsRequestBuilder *builder = [AIQRecommendationTagToProductsRequestBuilder new];
 NSError *error = [NSError new];
 AIQRecommendationTagToProductsRequest *request = [[builder setScenarioId:@"sid"] buildWithError:&error];
 [[QGSdk getSharedInstance] getRecommendationProductsWithRequest:request withCompletionHandler:^(AIQRecommendationProductResponse _Nullable response) {
 if (response) {
 QGLog(@"You can parse response");
 }
 }];
 @endcode

 Parse the response object and use it as required
 */
- (void)getRecommendationProductsWithRequest:(AIQRecommendationRequest *)request
                       withCompletionHandler:(void (^)(AIQRecommendationProductResponse * _Nullable response))completion;

/*!
 @abstract
 Send a recommendation click event when users open one url or  have one recommendation-related action

 @discussion
 This is a regular log event with parameters. All three parameters are necessary

 @param scenarioId ScenarioId

 @param modelId ModelId

 @param productId ProductId

 @param recommendationId recId

 @code
 [[QGSdk getSharedInstance] logRecommendationClickedWithScenarioId:@"sid" withModelId:@"19023" withProductId:@"XXX-SKU" withRecommendationId:@"recId"];
 @endcode

 Parse the response object and use it as required
 */
- (void)logRecommendationClickedWithScenarioId:(NSString *)scenarioId
                                   withModelId:(NSString *)modelId
                                 withProductId:(NSString *)productId
                          withRecommendationId:(NSString *)recommendationId;

/*!
 @abstract
 Fetch the latest remote inboxMessages

 @discussion
 This is an asynchronous function to get the latest messages from servers. In the completionHandler,
 we could call getInboxesWithStatusRead:(BOOL)read statusUnread:(BOOL)unread statusDeleted:(BOOL)deleted to
 get the most recent messages if success is true. If success is false, we could still get the existingly local saved messages

 @code
 [[QGSdk getSharedInstance] fetchInboxMessages:^(BOOL success, NSError * _Nullable error) {
 if (success) {
 NSArray <QGInbox *> *inboxList = [[QGSdk getSharedInstance] getInboxesWithStatusRead:YES statusUnread:YES statusDeleted:YES];
 }
 }];
 @endcode
 */
- (void)fetchInboxMessages:(void (^)(BOOL success, NSError * _Nullable error))completionHandler;

/*!
 @abstract
 Returns inboxMessages from local storage.

 @discussion
 This is a synchronous function which immediately returns array of inbox objects

 @code
 Get messages with status Deleted, ex:
 NSArray <QGInbox *> *inboxList = [[QGSdk getSharedInstance] getInboxesWithStatusRead:NO read statusUnread:NO statusDeleted:YES];

 Get messages with status Read or Deleted, ex:
 NSArray <QGInbox *> *inboxList = [[QGSdk getSharedInstance] getInboxesWithStatusRead:YES statusUnread:NO statusDeleted:YES];
 @endcode
 */
- (NSArray<QGInbox *> *)getInboxesWithStatusRead:(BOOL)read statusUnread:(BOOL)unread statusDeleted:(BOOL)deleted;

/*!
 @abstract
 Update the limit of inboxMessage

 @discussion
 This will update the number of limit for storage of inbox message. Then check if current count of inbox
 message exceeds this new limit. If exceeds, older records in the existing inbox messages will be removed.

 @param limit             the limit to change (QGInboxLimitSmall, QGInboxLimitMedium, QGInboxLimitHigh, QGInboxLimitExtraHigh)

 @code
 Update the inbox limit to QGInboxLimitHigh, ex: [[QGSdk getSharedInstance] updateInboxRecordLimit:QGInboxLimitHigh];
 @endcode
 */
- (void)updateInboxRecordLimit:(NSInteger)limit;

/*!
 @abstract
 Get locally saved push notification data, which is a list of notification payload

 @discussion
 Whenever we received push notification, we save the payload in the local storage

 @code
 NSArray *payloadList = [[QGSdk getSharedInstance] fetchSavedPushNotifications];
 @endcode
 */
- (NSArray*)fetchSavedPushNotifications;

/*!
 @abstract
 Remove all local-saved push notification data

 @discussion
 Clean all local-saved push notification data if we don't need it

 @code
 [[QGSdk getSharedInstance] deleteSavedPushNotifications];
 @endcode
 */
- (void)deleteSavedPushNotifications;

/*!
 @abstract
 Remove one specific local-saved push notification

 @discussion
 We just need to remove one specific local-saved push notification

 @code
 [[QGSdk getSharedInstance] deleteNotificationAtIndex:index];
 @endcode
 */
- (void)deleteNotificationAtIndex:(NSUInteger)index;

/*!
 @abstract
 Enable or Disable Remote Push Notification Storage

 @discussion
 This method can be used to enable or disable storage of Remote
 Push Notification which are sent only from AIQUA Server.

 By default, it is @b DISABLED.

 @note QGNotificationSdk (Version 5.2.1 and above) i.e. Rich push @b MUST be integrated

 @code
 [[QGSdk getSharedInstance] enablePushNotificationStorage];
 @endcode
 */
- (void)enablePushNotificationStorage;

/*!
 @abstract
 Set the maxinum number of rows to save push notification

 @discussion
 This is the maximum number (Default to 20) of latest notifications received from AIQUA server will be stored by the sdk.
 If the limit you set is smaller than the existing limit, for example changing from 100 to 80, the older 20 notifications will be deleted.

 @code
 [[QGSdk getSharedInstance] setPushNotificationStorageLimit:100];
 @endcode
 */
- (void)setPushNotificationStorageLimit:(long)limit;

/*!
 @abstract
 Set whether the current AppID is active.

 @discussion
 This method is used to set whether this AppID is the currently active AppID. This is used to determine if the app should receive push notifications for this ID.

 @param isActive A boolean value indicating whether this AppID is active. `YES` if it is active, `NO` otherwise.
 */
- (void)setAIQActiveProfile:(BOOL)isActive;

/*!
 @abstract
 Check if the push notification is from Appier

 @discussion
 This is a helper function to check if the push notification is from Appier SDK.

 @code
 BOOL isAppierPush = [[QGSdk getSharedInstance] isAppierPush:@{@"example": @"example"}];
 @endcode
 */
- (BOOL)isAppierPush:(NSDictionary * _Nullable)userInfo;

/// By calling this method, the SDK will do the necessary URL handling with Appier-integrated
/// third-party services. eg. LINE data syncing
/// However, you don't have to call this method if you set the `AppierAppDelegateProxyEnabled`
/// flag to `YES` in your Info.plist.
/// @param url The URL resource to open.
- (void)handleOpenUrl:(NSURL *)url NS_SWIFT_NAME(handleOpenUrl(_:));

/// By calling this method, the SDK will do the necessary URL handling with Appier-integrated
/// third-party services. eg. LINE data syncing
/// However, you don't have to call this method if you set the `AppierAppDelegateProxyEnabled`
/// flag to `YES` in your Info.plist.
/// @param userActivity The activity object containing the data associated with the task the user was performing. Use the data to continue the user's activity in your iOS app.
- (void)handleUserActivity:(NSUserActivity *)userActivity NS_SWIFT_NAME(handleUserActivity(_:));

/// This is a handler of AIQUA-related WKWebView script message for the implementation of custom web view, to track custom events and attributes in such web view
- (void)handleScriptMessageOfWebView:(WKWebView *)webView userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message;
- (void)handleScriptMessageOfWebView:(WKWebView *)webView userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message processEventParameters:(BOOL)processEventParameters;
- (void)didReceiveAidealExternalCampaign:(NSDictionary *)campaign;
- (void)onStart:(NSString *)appId withAppGroup:(NSString * _Nullable)appGroup setDevProfile:(BOOL)devProfile frameworkType:(NSString * _Nullable)type frameworkVersion:(NSString * _Nullable)version;

/// Registers a push notification notifier delegate.
///
/// Use this method to register an object that conforms to the `AIQPushNotificationNotifierDelegate`.
/// The system will notify this notifier when relevant push notifications are received.
///
/// > Important: The system holds a **weak reference** to the `delegate`.
/// > You must store a **strong reference** elsewhere to keep it alive. If not retained,
/// > the `delegate` may be deallocated and will not receive notifications.
///
/// @param delegate The delegate object to register. This parameter can be `nil`
/// to clear any existing delegate.
- (void)setPushNotificationNotifierDelegate:(id <APRPushNotificationNotifierDelegate> _Nullable)delegate;

@end
NS_ASSUME_NONNULL_END
