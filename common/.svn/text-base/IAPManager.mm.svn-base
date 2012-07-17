#import "IAPManager.h"

#import "CCGameBox.h"
#import "GameApp.h"
#import "GlobalData.h"

@implementation IAPManager

#define kInAppPurchase100CoinProductId  @"M100COIN"
#define kInAppPurchase500CoinProductId  @"M500COIN"
#define kInAppPurchase1000CoinProductId @"M1000COIN"
#define kInAppPurchase2500CoinProductId @"M2500COIN"
#define kInAppPurchaseFullMapProductId  @"MMAPS"
#define kProductCount	5

/*
 #define kInAppPurchase320CoinProductId      @"M320COIN"
 #define kInAppPurchase600CoinProductId      @"M600COIN"
 #define kInAppPurchase2000CoinProductId     @"M2000COIN"
 #define kInAppPurchase4600CoinProductId     @"M4600COIN"
 #define kInAppPurchase13000CoinProductId    @"M13000COIN"
 #define kInAppPurchase40000CoinProductId    @"M40000COIN"
 #define kInAppPurchase90000CoinProductId    @"M90000COIN"
 */

@synthesize mApp;

//获取商品信息...
- (void)requestProductDataWithId:(NSString *)productid
{
    NSSet *productIdentifiers = [NSSet setWithObject:productid ];
    productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
}

//获取全部商品信息
- (void)requestAllProductData
{
	NSSet *pid = [NSSet setWithObjects:kInAppPurchase100CoinProductId, kInAppPurchase500CoinProductId, kInAppPurchaseFullMapProductId, nil];
	productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:pid];
    productsRequest.delegate = self;
    [productsRequest start];
}

#pragma mark -
#pragma mark SKProductsRequestDelegate methods
//收到商品信息的处理，此处应该界面显示...
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray *products = response.products;
    if ([products count]==3)
    {
		for(SKProduct *pro in products)
		{
			NSLog(@"Product title: %@" , pro.localizedTitle);
			NSLog(@"Product description: %@" , pro.localizedDescription);
			NSLog(@"Product price: %@" , pro.price);
			NSLog(@"Product id: %@" , pro.productIdentifier);
			if ([pro.productIdentifier isEqualToString: kInAppPurchase100CoinProductId]) {
				m100coin = [pro retain];
			}
		}
        
		//购买商品...
		if ([self canMakePurchases]) {
			NSLog(@"can make purchases....");
			NSLog(@"start purchase............");
			SKPayment *payment = [SKPayment paymentWithProduct:m100coin];
			[[SKPaymentQueue defaultQueue] addPayment:payment];
		}
    }
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    
    [productsRequest release];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerProductsFetchedNotification object:self userInfo:nil];
}

#pragma -
#pragma Public methods
//
// call this method once on startup
//
- (void)loadStore
{
    // restarts any purchases if they were interrupted last time the app was open
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    // get the product description (defined in early sections)
    [self requestAllProductData];
}
//
// call this before making a purchase
//
- (BOOL)canMakePurchases
{
    return [SKPaymentQueue canMakePayments];
}
//
// kick off the upgrade transaction
//
- (void)purchaseProUpgrade
{
	NSLog(@"start purchase............");
    SKPayment *payment = [SKPayment paymentWithProductIdentifier:kInAppPurchase100CoinProductId];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}
//
//purchase a product
//
- (void)purchaseProduct
{
    /*
	if ([self canMakePurchases]) {
		NSString *productId=[NSString stringWithFormat:@""];
		if (mApp->score0store1==1) {//
			if (mApp->firstChoose==0) {//coins
				if (mApp->secondChoose==0) //100coins
					productId = [NSString stringWithFormat:@"M100COIN"];
				if (mApp->secondChoose==1) //500coins
					productId = [NSString stringWithFormat:@"M500COIN"];
				if (mApp->secondChoose==2) //1000coins
					productId = [NSString stringWithFormat:@"M1000COIN"];
				if (mApp->secondChoose==3) //2500coins
					productId = [NSString stringWithFormat:@"M2500COIN"];
				NSLog(@"can make purchases....");
				NSLog(@"start purchase............");
				SKPayment *payment = [SKPayment paymentWithProductIdentifier:productId];
				[[SKPaymentQueue defaultQueue] addPayment:payment];
			}
		}
	}
    */
}
#pragma -
#pragma Purchase helpers
//
// saves a record of the transaction by storing the receipt to disk
//
- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
    if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchase100CoinProductId])
    {
        // save the transaction receipt to disk
        [[NSUserDefaults standardUserDefaults] setValue:transaction.transactionReceipt forKey:@"proUpgradeTransactionReceipt" ];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}
//
// enable pro features
//
- (void)provideContent:(NSString *)productId
{
    if ([productId isEqualToString:kInAppPurchase100CoinProductId])
    {
        // enable the pro features
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"isProUpgradePurchased" ];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}
//
// removes the transaction from the queue and posts a notification with the transaction result
//
- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
    // remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:transaction, @"transaction" , nil];
    if (wasSuccessful)
    {
        // send out a notification that we’ve finished the transaction
        [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionSucceededNotification object:self userInfo:userInfo];
    }
    else
    {
        // send out a notification for the failed transaction
        [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionFailedNotification object:self userInfo:userInfo];
    }
}
//
// called when the transaction was successful
//
- (void)completeTransaction:(SKPaymentTransaction *)transaction
{	
	//发送给我们自己的服务器，验证后生效购买...
	//NSString *receiptStr = [[transaction transactionReceipt] encodeBase64ForData];
    //snprintf(g_receipt, 4096, "%s", [receiptStr cStringUsingEncoding:NSUTF8StringEncoding]);
	//mApp->BuyFromAppStore();
    [self recordTransaction:transaction];
    [self provideContent:transaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}
//
// called when a transaction has been restored and and successfully completed
//
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
	NSLog(@"restore transaction.......");
    [self recordTransaction:transaction.originalTransaction];
    [self provideContent:transaction.originalTransaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}
//
// called when a transaction has failed
//
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
	NSLog(@"failed transaction.......");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        // error!
		NSLog(@"ERROR..........%d-%@", transaction.error.code, transaction.error);
        [self finishTransaction:transaction wasSuccessful:NO];
    }
    else
    {
		NSLog(@"canceled..........");
        // this is fine, the user just cancelled, so don’t notify
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
}
#pragma mark -
#pragma mark SKPaymentTransactionObserver methods
//
// called when the transaction status is updated
//
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
	NSLog(@"update transaction.......");
    for (SKPaymentTransaction *transaction in transactions)
    {
		NSLog(@"**************************%@, %d", transaction, transaction.transactionState);
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
            default:
                break;
        }
    }
}

@end
