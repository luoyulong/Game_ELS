//
//  MenuLayerStore.h
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UITableLayer.h"
@interface MenuLayerStore : UITableLayer
{
    UIButton *chipStore;
    UIButton *iItems;
    UIButton *buyDetail;
    UIImageView *backgroundview;
    int chooseButton;
}
@property (retain)UIButton *chipStore;
@property (retain)UIButton *iItems;
@property (retain)UIButton *buyDetail;
@property int chooseButton;
+ (MenuLayerStore *)sharedManager;
- (void) chipStoreCallBack;
- (void) iItemsCallBack;
- (void) buyDetailCallBack;
- (void) reloadData;
@end
