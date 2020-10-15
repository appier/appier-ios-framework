//
//  AIQP+ReactNative.h
//  QGSdk
//
//  Created by Shiv.Raj on 13/6/19.
//  Copyright © 2019 QGraph. All rights reserved.
//

#import "AIQP.h"

NS_ASSUME_NONNULL_BEGIN

@interface AIQP (ReactNative)

/*!
 @abstract
 Get the personalized value for React Native
 
 @discussion
 This method is to be used for react native apps. Use above methods for native apps.
 It will return the personalized value for a key for a particular react component
 as context. Must pass default value and type.
 
 @note
 For use in React Native AIQUA SDK only
 */
+ (NSDictionary *)getConfigForReactNative;

+ (void)setConfigKey:(NSString *)key withType:(NSString *)type withContext:(NSString *)context withDefaultValue:(NSString *)value;

@end

NS_ASSUME_NONNULL_END
