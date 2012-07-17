//
//  wrapper.cpp
//  ThreeCard
//
//  Created by Chao Li on 12-6-4.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "AddonWrapper.h"
//MenuLayerAddon
#import "MenuLayerMsg.h"
#import "MenuLayerActs.h"
#import "MenuLayerFAQ.h"
#import "MenuLayerFriend.h"
#import "MenuLayerStore.h"
#import "MenuLayerFriend.h"

#pragma mark -
#pragma mark MenuLayer Addon
void menuLayerMsgShow()
{
    [[MenuLayerMsg sharedManager] getMessage:0];
    [[MenuLayerMsg sharedManager] viewMoveToTop :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerMsgHide()
{
    [[MenuLayerMsg sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}

void reloadMsgData()
{
    [[MenuLayerMsg sharedManager]reloadData];
}

void menuLayerFAQShow()
{
    [[MenuLayerFAQ sharedManager] viewMoveToTop :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerFAQHide()
{
    [[MenuLayerFAQ sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerActsShow()
{
    [[MenuLayerActs sharedManager] viewMoveToTop :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerActsHide()
{
    [[MenuLayerActs sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerFriendsShow()
{
    [[MenuLayerFriend sharedManager] getFriends];
    [[MenuLayerFriend sharedManager] viewMoveToTop :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerFriendsHide()
{
    [[MenuLayerFriend sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}

void reloadFriendData()
{
    [[MenuLayerFriend sharedManager] reloadData];
}
void menuLayerStoreShow()
{
    [MenuLayerStore sharedManager].chooseButton=1;
    [[MenuLayerStore sharedManager] reloadData];
    [[MenuLayerStore sharedManager] viewMoveToTop :SINGLE_LAYER_MOVE otherView:nil];
}

void menuLayerStoreHide()
{
    [[MenuLayerStore sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}