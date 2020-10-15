//
//  AIDPageType.h
//
//  Created by Appier on 2020/2/11.
//  Copyright © 2020 Appier. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    AIDPageType_Undefined = 0,
    AIDPageType_Uninterested,
    AIDPageType_Top,
    AIDPageType_Category,
    AIDPageType_Search,
    AIDPageType_Item,
    AIDPageType_Cart,
    AIDPageType_CartForm,
    AIDPageType_Conversion,
    AIDPageType_MyPage,
    AIDPageType_Login,
    AIDPageType_RegistrationForm,
    AIDPageType_Registration
} AIDPageType;

NS_ASSUME_NONNULL_BEGIN
@interface AIDPageTypeHelper : NSObject
+ (NSDictionary *)preparePageWithType:(AIDPageType)page IsLogin:(BOOL)isLogin ItemPrice:(nullable NSNumber *)itemprice
                            CartPrice:(nullable NSNumber *)cartprice Parms:(nullable NSDictionary*)parms;
+ (NSString *)convertPageToString:(AIDPageType)page;
@end

NS_ASSUME_NONNULL_END

