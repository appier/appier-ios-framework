//
//  AIDConversionInfo.h
//  AiDealSdk
//
//  Created by Appier on 2020/3/26.
//  Copyright © 2020 Appier. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AIDConversionItem: NSObject
@property (nonatomic, copy) NSString *identifier;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *url;
@property (nonatomic, copy) NSNumber *price;
@property (nonatomic, copy) NSNumber *count;
@end

@interface AIDConversionInfo : NSObject
@property(nonatomic, copy) NSString *conversionId;
@property(nonatomic, copy) NSString *conversionName;
@property(nonatomic, strong) NSArray *couponCodes;   //Coupon codes are used in one purchase
@property(nonatomic, copy) NSNumber *totalItems;
@property(nonatomic, copy) NSNumber *totalPrice;
@property(nonatomic, strong) NSArray<AIDConversionItem *> *items;

+ (nullable NSDictionary *)convertInfoToDictionary:(AIDConversionInfo *)info;
@end

NS_ASSUME_NONNULL_END
