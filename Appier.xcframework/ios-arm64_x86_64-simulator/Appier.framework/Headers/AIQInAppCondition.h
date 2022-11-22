#ifndef AIQInAppCondition_h
#define AIQInAppCondition_h

typedef NS_ENUM(NSInteger, AIQInAppOperator){
    AIQ_INAPP_OPERATOR_UNEXPECTED = -1,
    AIQ_INAPP_OPERATOR_EQUAL,
    AIQ_INAPP_OPERATOR_NOT_EQUAL,
    AIQ_INAPP_OPERATOR_CONTAINED,
    AIQ_INAPP_OPERATOR_GREATER_THAN,
    AIQ_INAPP_OPERATOR_GREATER_THAN_OR_EQUAL,
    AIQ_INAPP_OPERATOR_LESS_THAN,
    AIQ_INAPP_OPERATOR_LESS_THAN_OR_EQUAL,
    AIQ_INAPP_OPERATOR_HAS_VALUE
};

@interface AIQInAppCondition : NSObject<NSCoding>
@property (nonatomic) NSString * parameter;
@property (nonatomic) AIQInAppOperator op;
@property (nonatomic) id value;
/**
 * Initializes a condition from a dictionary.
 * @param dictionary Dictionary to initialize from.
 */
- (instancetype)initFromDictionary:(NSDictionary *)dictionary;
@end

#endif /* AIQInAppCondition_h */
