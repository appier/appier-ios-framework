#import <Foundation/Foundation.h>

NS_SWIFT_NAME(Page)
@interface AIDPage: NSObject
@end

// MARK: - Page Attributes

typedef NSString * AIDPageAttributeName NS_TYPED_ENUM NS_SWIFT_NAME(Page.AttributeName);

extern AIDPageAttributeName const AIDPageTypeAttributeName NS_SWIFT_NAME(pageType);
extern AIDPageAttributeName const AIDPageTypesAttributeName NS_SWIFT_NAME(pageTypes);
extern AIDPageAttributeName const AIDPageLoggedInAttributeName NS_SWIFT_NAME(loggedIn);
extern AIDPageAttributeName const AIDPageItemPriceAttributeName NS_SWIFT_NAME(itemPrice);
extern AIDPageAttributeName const AIDPageCartPriceAttributeName NS_SWIFT_NAME(cartPrice);

// MARK: - Page Types

typedef NSString * AIDPageType NS_TYPED_ENUM;

extern AIDPageType const AIDPageTypeUninterested;
extern AIDPageType const AIDPageTypeTop;
extern AIDPageType const AIDPageTypeCategory;
extern AIDPageType const AIDPageTypeSearch;
extern AIDPageType const AIDPageTypeItem;
extern AIDPageType const AIDPageTypeCart;
extern AIDPageType const AIDPageTypeCartForm;
extern AIDPageType const AIDPageTypeConversion;
extern AIDPageType const AIDPageTypeMyPage;
extern AIDPageType const AIDPageTypeLogin;
extern AIDPageType const AIDPageTypeRegistrationForm;
extern AIDPageType const AIDPageTypeRegistration;
