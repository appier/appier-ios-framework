@interface SwiftMediator: NSObject

- (UIWindow *_Nullable)getWindow;
- (void)setWindow:(UIWindow * _Nullable)window;
- (id)unarchiveObjectWithData:(NSData *)data;

@end
