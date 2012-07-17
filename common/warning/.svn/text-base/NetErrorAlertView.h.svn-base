//
//  UITableLayer.h
//  GameBox
//
//  Created by  on 12-5-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <netdb.h>
#import <SystemConfiguration/SCNetworkReachability.h>

@interface NetErrorAlertView : UIViewController <UIAlertViewDelegate>
{
    UIAlertView *uiAlertView;
}

- (id)init;
+ (NetErrorAlertView *) sharedManager;
- (bool)checkNetWork;
- (void)alertViewShow;
- (bool)connectedToNetwork;

@end
