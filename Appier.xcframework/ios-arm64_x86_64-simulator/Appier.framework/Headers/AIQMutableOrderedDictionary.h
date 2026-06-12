//
//  AIQMutableOrderedDictionary.h
//  QGSdk
//
//  Created by Appier on 2021/4/8.
//  Copyright © 2021 QGraph. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AIQMutableOrderedDictionary : NSObject <NSCoding>
- (void)addObject:(id)obj forKey:(id)key;
- (void)insertObject:(id)obj forKey:(id)key atIndex:(NSUInteger)index;
- (nullable id)objectForKey:(id)key;
- (void)removeObjectForKey:(id)key;
- (NSArray *)allKeys;
- (NSInteger)count;
- (BOOL)isEqualToAIQOrderedDictionary:(AIQMutableOrderedDictionary *)dict;
@end

NS_ASSUME_NONNULL_END
