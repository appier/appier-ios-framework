#ifndef AsyncResult_h
#define AsyncResult_h

#import <Foundation/Foundation.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wquoted-include-in-framework-header"
#import "AppierError.h"
#pragma clang diagnostic pop

/**
 * Generic asynchronous result handler for API calls.
 *
 * This class provides open methods to handle various stages of API execution, including start, success, error, and completion.
 * It allows customization of behavior by providing an opportunity to override these methods in subclasses.
 *
 */
@interface AsyncResult<T> : NSObject

@property (nonatomic, strong, nullable) AsyncResult<T> *delegate;

/**
 * Callback method invoked when API execution is started.
 *
 * This method is called when the execution of the associated API is initiated.
 * It serves as a notification that the API process has started.
 */
- (void)onStarted;

/**
 * Callback method invoked when API execution is successful.
 *
 * This method is called when the execution of the associated API is successfully completed.
 *
 * @param result The result of the API execution, which may be of type T or nil depending on the API implementation.
 *   This parameter contains the outcome or data produced by the successful API execution.
 */
- (void)onSuccess:(nullable T)result;

/**
 * Callback method invoked when an error occurs during API execution.
 *
 * This method is called when an error occurs during the execution of the associated API.
 *
 * @param error An error object representing the error type or category.
 * @param errorMessage A string containing a descriptive message associated with the error.
 * @param exception An Exception object representing the actual error instance or exception thrown during API execution.
 *   This parameter may be nil if the error is not associated with a specific exception.
 */
- (void)onError:(AppierError)error errorMessage:(nullable NSString *)errorMessage exception:(nullable NSException *)exception;

/**
 * Callback method invoked when API execution is completed.
 *
 * This method is called when the execution of the associated API is fully completed, after onSuccess or onError.
 * It serves as a notification that the entire API process, including success or error handling, has concluded.
 */
- (void)onCompleted;

@end


#endif /* AsyncResult_h */
