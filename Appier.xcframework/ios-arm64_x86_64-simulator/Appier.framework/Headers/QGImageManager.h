//
//  ImageManager.h
//  QGSdk
//
//  Created by Shiv
//  Copyright (c) 2019 APPIER INC. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UIImage;

@interface QGImageManager : NSObject

+ (instancetype)instance;
- (void)downloadImageForURL:(NSString *)urlString withIdentifier:(NSString *)identifier withCompletionHandler:(void(^)(BOOL))completionHandler;
- (BOOL)isAnimatedImageFile:(NSData *)data;
- (NSData *)getImageDataForURL:(NSString *)urlString withIdentifier:(NSString *)identifier;
- (UIImage *)getImageForURL:(NSString *)urlString withIdentifier:(NSString *)identifier;
- (BOOL)isImageAvailableForURL:(NSString *)urlString withIdentifier:(NSString *)identifier;
- (void)deleteImageForURL:(NSString *)urlString withIdentifier:(NSString *)identifier;
- (void)saveImageToFileManager:(NSData *)data forURL:(NSString *)url withIdentifier:(NSString *)identifier;
- (void)deleteLegacyImages;
@end
