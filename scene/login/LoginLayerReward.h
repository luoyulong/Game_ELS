//
//  LoginLayerReward.h
//  GameBox
//
//  Created by Chao Li on 12-5-31.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

//连续登陆奖励
#import <Foundation/Foundation.h>
#import "UITableLayer.h"
@interface LoginLayerReward : UITableLayer
{
    UIImageView *background;
    UILabel *title;
    UIImageView *starLine;
    UILabel *numberOfGetCoin;
    UIView *rewardArea;
    UILabel *tips;
    UIButton *confirm;
    
    UIImageView *rotateCard;
    UIImageView *rotatePlus;
    UIImageView *rotateCoins;
    UILabel *rotateDayNum;

    NSTimer *m_Timer;
}

+ (LoginLayerReward *)sharedManager;
@property (retain)UIImageView *starLine;
@property (retain)UILabel *numberOfGetCoin;
@property (retain)UIView *rewardArea;
@property (retain)UILabel *tips;
@property (retain)UIButton *confirm;

//- (IBAction)confirmButton:(id)sender;
//- (id) initWithFrame:(CGRect)frame;
- (void)updateData;
- (void)confirmButtonCallBack;
- (void)turnFrontCallBack;
@end
