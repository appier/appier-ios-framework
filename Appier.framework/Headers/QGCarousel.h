//
//  QGCarousel.h
//
//  Version 1.8.3
//
//  Created by Nick Lockwood on 01/04/2011.
//  Copyright 2011 Charcoal Design
//
//  Distributed under the permissive zlib License
//  Get the latest version from here:
//
//  https://github.com/nicklockwood/QGCarousel
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wobjc-missing-property-synthesis"


#import <Availability.h>
#undef weak_delegate
#undef __weak_delegate
#if __has_feature(objc_arc) && __has_feature(objc_arc_weak) && \
(!(defined __MAC_OS_X_VERSION_MIN_REQUIRED) || \
__MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_8)
#define weak_delegate weak
#else
#define weak_delegate unsafe_unretained
#endif


#import <QuartzCore/QuartzCore.h>
#if defined USING_CHAMELEON || defined __IPHONE_OS_VERSION_MAX_ALLOWED
#define QGCarousel_IOS
#else
#define QGCarousel_MACOS
#endif


#ifdef QGCarousel_IOS
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
typedef NSView UIView;
#endif


typedef NS_ENUM(NSInteger, QGCarouselType)
{
    QGCarouselTypeLinear = 0,
    QGCarouselTypeRotary,
    QGCarouselTypeInvertedRotary,
    QGCarouselTypeCylinder,
    QGCarouselTypeInvertedCylinder,
    QGCarouselTypeWheel,
    QGCarouselTypeInvertedWheel,
    QGCarouselTypeCoverFlow,
    QGCarouselTypeCoverFlow2,
    QGCarouselTypeTimeMachine,
    QGCarouselTypeInvertedTimeMachine,
    QGCarouselTypeCustom
};


typedef NS_ENUM(NSInteger, QGCarouselOption)
{
    QGCarouselOptionWrap = 0,
    QGCarouselOptionShowBackfaces,
    QGCarouselOptionOffsetMultiplier,
    QGCarouselOptionVisibleItems,
    QGCarouselOptionCount,
    QGCarouselOptionArc,
    QGCarouselOptionAngle,
    QGCarouselOptionRadius,
    QGCarouselOptionTilt,
    QGCarouselOptionSpacing,
    QGCarouselOptionFadeMin,
    QGCarouselOptionFadeMax,
    QGCarouselOptionFadeRange,
    QGCarouselOptionFadeMinAlpha
};


NS_ASSUME_NONNULL_BEGIN

@protocol QGCarouselDataSource, QGCarouselDelegate;

@interface QGCarousel : UIView

@property (nonatomic, weak_delegate) IBOutlet __nullable id<QGCarouselDataSource> dataSource;
@property (nonatomic, weak_delegate) IBOutlet __nullable id<QGCarouselDelegate> delegate;
@property (nonatomic, assign) QGCarouselType type;
@property (nonatomic, assign) CGFloat perspective;
@property (nonatomic, assign) CGFloat decelerationRate;
@property (nonatomic, assign) CGFloat scrollSpeed;
@property (nonatomic, assign) CGFloat bounceDistance;
@property (nonatomic, assign, getter = isScrollEnabled) BOOL scrollEnabled;
@property (nonatomic, assign, getter = isPagingEnabled) BOOL pagingEnabled;
@property (nonatomic, assign, getter = isVertical) BOOL vertical;
@property (nonatomic, readonly, getter = isWrapEnabled) BOOL wrapEnabled;
@property (nonatomic, assign) BOOL bounces;
@property (nonatomic, assign) CGFloat scrollOffset;
@property (nonatomic, readonly) CGFloat offsetMultiplier;
@property (nonatomic, assign) CGSize contentOffset;
@property (nonatomic, assign) CGSize viewpointOffset;
@property (nonatomic, readonly) NSInteger numberOfItems;
@property (nonatomic, readonly) NSInteger numberOfPlaceholders;
@property (nonatomic, assign) NSInteger currentItemIndex;
@property (nonatomic, strong, readonly) UIView * __nullable currentItemView;
@property (nonatomic, strong, readonly) NSArray *indexesForVisibleItems;
@property (nonatomic, readonly) NSInteger numberOfVisibleItems;
@property (nonatomic, strong, readonly) NSArray *visibleItemViews;
@property (nonatomic, readonly) CGFloat itemWidth;
@property (nonatomic, strong, readonly) UIView *contentView;
@property (nonatomic, readonly) CGFloat toggle;
@property (nonatomic, assign) CGFloat autoscroll;
@property (nonatomic, assign) BOOL stopAtItemBoundary;
@property (nonatomic, assign) BOOL scrollToItemBoundary;
@property (nonatomic, assign) BOOL ignorePerpendicularSwipes;
@property (nonatomic, assign) BOOL centerItemWhenSelected;
@property (nonatomic, readonly, getter = isDragging) BOOL dragging;
@property (nonatomic, readonly, getter = isDecelerating) BOOL decelerating;
@property (nonatomic, readonly, getter = isScrolling) BOOL scrolling;

- (void)scrollByOffset:(CGFloat)offset duration:(NSTimeInterval)duration;
- (void)scrollToOffset:(CGFloat)offset duration:(NSTimeInterval)duration;
- (void)scrollByNumberOfItems:(NSInteger)itemCount duration:(NSTimeInterval)duration;
- (void)scrollToItemAtIndex:(NSInteger)index duration:(NSTimeInterval)duration;
- (void)scrollToItemAtIndex:(NSInteger)index animated:(BOOL)animated;

- (nullable UIView *)itemViewAtIndex:(NSInteger)index;
- (NSInteger)indexOfItemView:(UIView *)view;
- (NSInteger)indexOfItemViewOrSubview:(UIView *)view;
- (CGFloat)offsetForItemAtIndex:(NSInteger)index;
- (nullable UIView *)itemViewAtPoint:(CGPoint)point;

- (void)removeItemAtIndex:(NSInteger)index animated:(BOOL)animated;
- (void)insertItemAtIndex:(NSInteger)index animated:(BOOL)animated;
- (void)reloadItemAtIndex:(NSInteger)index animated:(BOOL)animated;

- (void)reloadData;

@end


@protocol QGCarouselDataSource <NSObject>

- (NSInteger)numberOfItemsInCarousel:(QGCarousel *)carousel;
- (UIView *)carousel:(QGCarousel *)carousel viewForItemAtIndex:(NSInteger)index reusingView:(nullable UIView *)view;

@optional

- (NSInteger)numberOfPlaceholdersInCarousel:(QGCarousel *)carousel;
- (UIView *)carousel:(QGCarousel *)carousel placeholderViewAtIndex:(NSInteger)index reusingView:(nullable UIView *)view;

@end


@protocol QGCarouselDelegate <NSObject>
@optional

- (void)carouselWillBeginScrollingAnimation:(QGCarousel *)carousel;
- (void)carouselDidEndScrollingAnimation:(QGCarousel *)carousel;
- (void)carouselDidScroll:(QGCarousel *)carousel;
- (void)carouselCurrentItemIndexDidChange:(QGCarousel *)carousel;
- (void)carouselWillBeginDragging:(QGCarousel *)carousel;
- (void)carouselDidEndDragging:(QGCarousel *)carousel willDecelerate:(BOOL)decelerate;
- (void)carouselWillBeginDecelerating:(QGCarousel *)carousel;
- (void)carouselDidEndDecelerating:(QGCarousel *)carousel;

- (BOOL)carousel:(QGCarousel *)carousel shouldSelectItemAtIndex:(NSInteger)index;
- (void)carousel:(QGCarousel *)carousel didSelectItemAtIndex:(NSInteger)index;

- (CGFloat)carouselItemWidth:(QGCarousel *)carousel;
- (CATransform3D)carousel:(QGCarousel *)carousel itemTransformForOffset:(CGFloat)offset baseTransform:(CATransform3D)transform;
- (CGFloat)carousel:(QGCarousel *)carousel valueForOption:(QGCarouselOption)option withDefault:(CGFloat)value;

@end

NS_ASSUME_NONNULL_END

#pragma clang diagnostic pop

