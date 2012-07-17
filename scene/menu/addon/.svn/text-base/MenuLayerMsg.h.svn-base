//
//  MenuLayerMsg.h
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UITableLayer.h"
#import "GELayer.h"
#import "GENet.h"

@interface MenuLayerMsg : UITableLayer<UITableViewDelegate, UITableViewDataSource>
{
    UIButton *personInfo;
    UIButton *systemInfo;
    UITableView *messageTableView;
}

@property (retain)UIButton *personInfo;
@property (retain)UIButton *systemInfo;
@property (retain)UITableView *messageTableView;
+ (MenuLayerMsg *) sharedManager;

-(void) personInfoCallBack;
-(void) systemInfoCallBack;
-(void) reloadData;
-(void) getMessage:(int)msgType;
@end
