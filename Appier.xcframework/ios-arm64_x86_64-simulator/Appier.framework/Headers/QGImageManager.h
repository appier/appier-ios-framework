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
- (void)downloadImageForURL:(NSString *)urlString;
- (UIImage *)getImageForURL:(NSString *)urlString;
- (BOOL)isImageAvailableForURL:(NSString *)urlString;
- (void)deleteImageForURL:(NSString *)urlString;
- (void)saveImageToFileManager:(NSData *)data ForURL:(NSString *)url;
@end
