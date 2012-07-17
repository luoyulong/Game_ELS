//
//  AddNoticeTableView.h.h
//  GameBox
//
//  Created by  on 12-5-7.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "RoomWrapper.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import "GETouchDispatcher.h"
#import "Texture2D.h"
#import "GEDirector.h"
#import "MenuLayerMatchRoom.h"
#import "MenuLayerNormalRoom.h"
#import "AppDelegate.h"
#import "UITableLayer.h"

#include "CCImage.h"
#include "GlobalData.h"

#pragma mark -
#pragma mark 普通桌子列表
void menuLayerNormalRoomShow()
{
    MenuLayerNormalRoom *normalRoom = [MenuLayerNormalRoom sharedManager];
    normalRoom->preSortFocusOn = -1;
    normalRoom->sortFocusOn = 0;
    [normalRoom setSortButtonTitle];
    [normalRoom reloadUserInfo];
    [normalRoom reloadTableViewData];
    [normalRoom startAWaitnet];
    [normalRoom setSlideBlockPosition:CGRectMake(7.0, 278.0, 116.5, 44.0) backgoundImageName:@"Roomlist_roomTypeSelected2.png"];
    
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [normalRoom viewMoveToLeft:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void menuLayerNormalRoomHidden()
{
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[MenuLayerNormalRoom sharedManager] viewMoveToRight:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void refreshMenuLayerNormalRoomTableView()
{
    [[MenuLayerNormalRoom sharedManager] refreshTableView];
}

#pragma mark -
#pragma mark 淘汰桌子列表
void menuLayerMatchRoomShow()
{
    MenuLayerMatchRoom *matchRoom = [MenuLayerMatchRoom sharedManager];
    matchRoom->preSortFocusOn = -1;
    matchRoom->sortFocusOn = 0;
    [matchRoom setSortButtonTitle];
    [matchRoom reloadUserInfo];
    [matchRoom reloadTableViewData];
    [matchRoom startAWaitnet];
    
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [matchRoom viewMoveToLeft:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void menuLayerMatchRoomHidden()
{
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[MenuLayerMatchRoom sharedManager] viewMoveToRight:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void refreshMenuLayerMatchRoomTableView()
{
    [[MenuLayerMatchRoom sharedManager] refreshTableView];
}