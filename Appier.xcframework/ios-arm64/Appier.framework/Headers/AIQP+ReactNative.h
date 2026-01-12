//
//  AIQP+ReactNative.h
//  QGSdk
//
//  Created by Shiv.Raj on 13/6/19.
//  Copyright © 2019 QGraph. All rights reserved.
//

#import <Appier/AIQP.h>

NS_ASSUME_NONNULL_BEGIN

@interface AIQP (ReactNative)

/*!
 @abstract
 Get the personalized value for React Native
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will always return an empty dictionary.
 No server requests will be made.
 
 @note
 For use in React Native AIQUA SDK only
 
 @result Empty dictionary
 @deprecated This API is deprecated and will be removed in a future version.
 */
+ (NSDictionary *)getConfigForReactNative DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Returns empty dictionary.");

/*!
 @abstract
 Set configuration key for React Native
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 This method has no effect.
 
 @param key the key (no longer used)
 @param type the type (no longer used)
 @param context the context (no longer used)
 @param value the value (no longer used)
 @deprecated This API is deprecated and will be removed in a future version.
 */
+ (void)setConfigKey:(NSString *)key withType:(NSString *)type withContext:(NSString *)context withDefaultValue:(NSString *)value DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Has no effect.");

@end

NS_ASSUME_NONNULL_END
