//
//  UITableLayer.m
//  GameBox
//
//  Created by  on 12-5-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NetErrorAlertView.h"

@implementation NetErrorAlertView
static NetErrorAlertView *netErrorAlertView = nil;
+ (NetErrorAlertView *) sharedManager
{
    if(!netErrorAlertView)
    {
        netErrorAlertView=[[NetErrorAlertView alloc] init];
    }
    return netErrorAlertView;
}

- (id)init
{
    uiAlertView = [[UIAlertView alloc] initWithTitle:nil
                                                   message:@"网络连接故障,请检查网络连接!"
                                                  delegate:self
                                         cancelButtonTitle:@"确定"
                                         otherButtonTitles:nil];
    
    return self;
}

- (void)willPresentAlertView:(UIAlertView *)alertView
{
    [alertView setFrame:CGRectMake(125, 80, 240, 160)];
    
    UIView *vtmp;
    for (vtmp in alertView.subviews) {
        if ([vtmp isKindOfClass:[UIButton class]]) {
            [vtmp setFrame:CGRectMake(80, 100, 80, 35)];
        } else if ([vtmp isKindOfClass:[UILabel class]]) {
            [vtmp setFrame:CGRectMake(0, 10, 240, 50)];
        } else if ([vtmp isKindOfClass:[UIControl class]]) {
            //在ios4.3.5中 重新设置确定按钮的frame (UIThreePartButton)
            [vtmp setFrame:CGRectMake(80, 100, 80, 35)];
        }
    }

}

- (bool)checkNetWork
{
    bool isNetWorkOk = [self connectedToNetwork];
    if (!isNetWorkOk) {
        [uiAlertView show];
    }
    
    return isNetWorkOk;
}

- (void)alertViewShow
{
    [uiAlertView show];
}

- (bool)connectedToNetwork
{
    // Create zero addy
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    // Recover reachability flags
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
    SCNetworkReachabilityFlags flags;
    
    bool didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    CFRelease(defaultRouteReachability);
    
    if (!didRetrieveFlags)
    {
        return NO;
    }
    
    bool isReachable = flags & kSCNetworkFlagsReachable;
    bool needsConnection = flags & kSCNetworkFlagsConnectionRequired;
    
    return (isReachable && !needsConnection) ? YES : NO;
}

@end
