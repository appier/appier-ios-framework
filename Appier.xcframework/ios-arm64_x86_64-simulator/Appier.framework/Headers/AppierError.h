#ifndef AppierError_h
#define AppierError_h

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AppierError) {
    Unknown = -1,
    AppIdNotSet = 1,
    ApplicationNotExist = 2,
    FetchRemoteConfigFailed = 3,
    InvalidEndpoint = 4,
    
    // HTTP Client Error
    BadRequest = 400,
    Unauthorized = 401,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    ProxyAuthenticationRequired = 407,
    RequestTimeout = 408,
    Conflict = 409,
    Gone = 410,
    LengthRequired = 411,
    PreconditionFailed = 412,
    PayloadTooLarge = 413,
    UriTooLong = 414,
    UnsupportedMediaType = 415,
    RangeNotSatisfiable = 416,
    ExpectationFailed = 417,
    Teapot = 418,
    MisdirectedRequest = 421,
    UnprocessableContent = 422,
    FailedDependency = 424,
    TooEarly = 425,
    UpgradeRequired = 426,
    PreconditionRequired = 428,
    TooManyRequests = 429,
    RequestHeaderFieldsTooLarge = 431,
    UnavailableForLegalReasons = 451,
    
    // HTTP Server Error
    InternalServerError = 500,
    NotImplemented = 501,
    BadGateway = 502,
    ServiceUnavailable = 503,
    GatewayTimeout = 504,
    HTTPVersionNotSupported = 505,
    VariantAlsoNegotiates = 506,
    InsufficientStorage = 507,
    LoopDetected = 508,
    NotExtended = 510,
    NetworkAuthenticationRequired = 511
};

@interface AppierErrorHelper : NSObject

+ (AppierError)fromErrorCode:(NSInteger)errorCode;
+ (NSString *)descriptionForError:(AppierError)error;

@end


#endif /* AppierError_h */
