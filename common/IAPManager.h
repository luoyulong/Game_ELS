#import <StoreKit/StoreKit.h>
#import "NSData+Base64Additions.h"

#define kInAppPurchaseManagerProductsFetchedNotification @"kInAppPurchaseManagerProductsFetchedNotification"
#define kInAppPurchaseManagerTransactionFailedNotification @"kInAppPurchaseManagerTransactionFailedNotification"
#define kInAppPurchaseManagerTransactionSucceededNotification @"kInAppPurchaseManagerTransactionSucceededNotification"

class GameApp;

@interface IAPManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
{
    //SKProduct *m320coin, *m660coin, *m2000coin, *m4600coin, *m13000coin, *m40000coin, *m90000coin, *mmap;
    SKProduct *m100coin, *m500coin, *m1000coin, *m2500coin, *mmap;
    SKProductsRequest *productsRequest;
	GameApp *mApp;
}

@property (nonatomic, assign) GameApp *mApp;

// public methods
- (void)loadStore;
- (BOOL)canMakePurchases;
- (void)purchaseProUpgrade;
- (void)requestAllProductData;
- (void)purchaseProduct;

@end