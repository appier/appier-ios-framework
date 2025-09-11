//
//  AIQP.h
//  QGSdk
//
//  Created by Ian.Lin on 2019/3/27.
//  Copyright © 2019 QGraph. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface AIQP : NSObject

/*!
 @discussion
 Restrict external init calls and allow to use singleton.
 */
- (instancetype)init __attribute__((unavailable("Please use `+ (AIQP *)getContextForViewController:(UIViewController *)controller;` instead")));

/*!
 @abstract
 Get the AIQP instance with namespace for the specific UIViewController.

 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will return a default instance that returns the default values provided.
 No server requests will be made, only default values will be returned.

 @param controller         UIViewController
 @deprecated This API is deprecated and will be removed in a future version.
 */
+ (AIQP *)getContextForViewController:(UIViewController *)controller DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default values will be used.");

/*!
 @abstract
 Get the AIQP instance with namespace for the specific UIViewController.

 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will return a default instance that returns the default values provided.
 No server requests will be made, only default values will be returned.

 @param controller         UIVewController
 @param enabled           YES/NO - Enable Use of Versioning (has no effect anymore)
 @deprecated This API is deprecated and will be removed in a future version.
 */
+ (AIQP *)getContextForViewController:(UIViewController *)controller withVersioning:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default values will be used.");

/*!
 @abstract
 Get the AIQP instance with namespace for the specific View or Screen.

 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will return a default instance that returns the default values provided.
 No server requests will be made.

 @param viewName         NonNull View / Screen Name
 @param enabled           YES/NO - Enable Use of Versioning (has no effect anymore)
 @deprecated This API is deprecated and will be removed in a future version.
 */
+ (AIQP *)getContextForView:(NSString * _Nonnull)viewName withVersioning:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default values will be used.");

/*!
 @abstract
 Get the personalized value for text.
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will always return the default value provided.
 No server requests will be made.
 
 @param key                 the key (no longer used)
 @param value               the default value to return
 
 @result                    the input default value
 @deprecated This API is deprecated and will be removed in a future version.
 */
- (NSString *)getTextForKey:(NSString *)key withDefaultValue:(NSString *)value DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default value will be returned.");

/*!
 @abstract
 Get the personalized value for color.
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will always return the default value provided.
 No server requests will be made.
 
 @param key                 the key (no longer used)
 @param value               the default hex color value to return
 
 @result                    the input default value
 @deprecated This API is deprecated and will be removed in a future version.
 */
- (NSString *)getColorForKey:(NSString *)key withDefaultValue:(NSString *)value DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default value will be returned.");


/*!
 @abstract
 Get UIColor from RGB hex String.
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 This method now always returns a transparent color (UIColor.clearColor).
 Please use UIColor extensions or other color utilities instead:
 - For Swift: UIColor(rgbHex:) from UIColor+Hex.swift
 - For Objective-C: UIColor category methods
 
 @param string              RGB hex string (ignored in deprecated version)
 
 @result                    Always returns transparent color (clearColor)
 @deprecated This API is deprecated and will be removed in a future version.
 */
- (UIColor *)getUIColorFromRGBHexString:(NSString *)string DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Always returns transparent color.");

/*!
 @abstract
 Get the personalized value for deeplink url string.
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will always return the default value provided.
 No server requests will be made.
 
 @param key                 the key (no longer used)
 @param value               the default URL string to return, e.g.,
                          @"http://your.default.domain/index.htm"
 
 @result                    the input default value
 @deprecated This API is deprecated and will be removed in a future version.
 */
- (NSString *)getDeepLinkForKey:(NSString *)key withDefaultValue:(NSString *)value DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default value will be returned.");

/*!
 @abstract
 Get the personalized value for image url string
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The method will always return the default value provided.
 No server requests will be made.
 
 @param key                 the key (no longer used)
 @param value               the default image URL string to return, e.g.,
                          @"http://your.default.domain/default.jpg"
 
 @result                    the input default value
 @deprecated This API is deprecated and will be removed in a future version.
 */
- (NSString *)getImageUrlForKey:(NSString *)key withDefaultValue:(NSString *)value DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Default value will be returned.");


/*!
 @abstract
 Set the disabled status of AIQP.
 
 @discussion
 DEPRECATED: This API is deprecated and will be removed in a future version.
 The API has no effect as AIQP is permanently disabled.
 
 @param status             YES/NO - has no effect as AIQP is permanently disabled
 @deprecated This API is deprecated and will be removed in a future version.
 */
+ (void)setDisabledStatus:(BOOL)status DEPRECATED_MSG_ATTRIBUTE("This API is deprecated and will be removed in a future version. Has no effect as AIQP is permanently disabled.");

@end
NS_ASSUME_NONNULL_END
