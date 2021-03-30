//
//  AIDManager.h
//
//  Created by Appier on 2020/2/4.
//  Copyright © 2020 Appier. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AIDPageType.h"
#import "AIDConversionInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface AIDManager : NSObject
+ (instancetype)instance;
/*!
@abstract
Initialize the Aideal SDK with valid API key.
 
@discussion
This MUST be called first before using any other functions in the Sdk.
 
@code
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    .
    .
    [[AIDManager instance] initWithApiKey:@"MyApiKey"];
    return YES;
}
@endcode
*/
- (void)initWithApiKey:(NSString *)key;

/*!
@abstract
Initialize the Tracking of the Page.

@discussion
This method is strongly suggested to be called in viewDidAppear.

@param vctl            Instance of current UIViewController visible to the user
@param pageType        One page type that is used to tell server which page you are staying at
@param scrollable      Instance of Scrollable View (subclass of UIScrollView) for tracking User behavior
@param isLogin         Boolean value that you can tell us if one user is logged-in
@param itemPrice       Price of product/item User is viewing, only for product details/item page
@param cartPrice       Total Price of the items in the Shopping Cart added by the User
 
 @code
 - (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    .
    .
    [[AIDManager instance] initPage:self PageType:AIDPageType_Top Scrollable:nil IsLogin:NO ItemPrice:nil CartPrice:nil];
 }
 @endcode
*/
- (void)initPage:(UIViewController *)vctl PageType:(AIDPageType)pageType Scrollable:(nullable UIScrollView *)scrollable IsLogin:(BOOL)isLogin ItemPrice:(nullable NSNumber *)itemPrice CartPrice:(nullable NSNumber *)cartPrice;

/*!
@abstract
De-Init the page for tracking.

@discussion
This is to stop tracking page once page disappears from the screen.
This MUST be called for every initTrackPage within the same view controller.
 
 @code
 - (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    .
    .
    .
    [[AIDManager instance] deinitPage];
 }
 @endcode
*/
- (void)deinitPage;

/*!
@abstract
Logging Conversion completed using AiDeal Coupon.

@discussion
Send the conversion data to server for AI analysis. Try to use this in one purchase only.

@param conversionInfo        the instance of AIDConversionInfo (AIDConversionInfo.h) which contain some necessary properties
 
@code

 - (void)methodToSendConversionInfo {
         
     AIDConversionInfo *conversionInfo = [[AIDConversionInfo alloc] init];
     conversionInfo.conversionId = @"98111";
     conversionInfo.conversionName = @"newconversion";
     conversionInfo.couponCodes = [NSArray arrayWithObjects:[NSNumber numberWithInt:20021], @"APPIER2020", nil];
     conversionInfo.totalItems = [NSNumber numberWithInteger:2];
     conversionInfo.totalPrice = [NSNumber numberWithInteger:1900];
         
     NSMutableArray *items = [NSMutableArray new];
     AIDConversionItem *item01 = [AIDConversionItem new];
     item01.identifier = @"12";
     item01.name = @"Hat";
     item01.url = @"https://www.google.com?product=223";
     item01.price = [NSNumber numberWithInteger:900];
     item01.count = [NSNumber numberWithInteger:1];
     [items addObject:item01];
         
     AIDConversionItem *item02 = [AIDConversionItem new];
     item02.identifier = @"2022";
     item02.name = @"Swatch";
     item02.url = @"https://www.swatch.com?product_id=223022";
     item02.price = [NSNumber numberWithInteger:1000];
     item02.count = [NSNumber numberWithInteger:1];
     [items addObject:item02];

     //Add all purchased items in the items
     conversionInfo.items = items;
         
     [[AIDManager instance] sendConversionInfo:conversionInfo];
 }
 @endcode
*/
- (void)sendConversionInfo:(AIDConversionInfo *)conversionInfo;
@end
NS_ASSUME_NONNULL_END

