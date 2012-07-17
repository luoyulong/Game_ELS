//
//  LoginWrapper.m
//  ThreeCard
//
//  Created by Chao Li on 12-6-4.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "LoginWrapper.h"
//Continuous Login Reward
#import "LoginLayerReward.h"

#pragma mark -
#pragma mark LoginLayerReward
void loginLayerRewardShow()
{
    [[LoginLayerReward sharedManager] viewMoveToTop :SINGLE_LAYER_MOVE otherView:nil];
}

void loginLayerRewardHide()
{
    [[LoginLayerReward sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}

void loginLayerRewardReloadData(){
    [[LoginLayerReward sharedManager] updateData];
}