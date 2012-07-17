//
//  MenuLayerNormalRoom.h
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GameRoomLayer.h"
#import "GlobalData.h"

@interface MenuLayerNormalRoom : GameRoomLayer
{
    
@private
    //游戏速度选择
    // 普通:true 快速:false
    //bool betSpeedChoice;
    
    //房间满员状况选择
    bool fullRoomChoice;
    
    // 排序方式 true为正序
    bool IDSortStyle;
    bool betLimitSortStyle;
    bool betTimesSortStyle;
    bool chipsSortStyle;
    bool playersSortStyle;
    
    UIButton *fullRoomChoiceButton;
    UILabel *fullRoomButtonLable1;
    UILabel *fullRoomButtonLable2;
    
    //上部的排序按钮
    UIButton *roomIDNameButton;
    UIButton *betLimitOnceButton;
    UIButton *betTimesLimitButton;
    UIButton *chipsLimitButton;
    UIButton *playersCountButton;
    
    UIImageView *roomIDNameButtonTriangle;
    UIImageView *betLimitOnceButtonTriangle;
    UIImageView *betTimesLimitButtonTriangle;
    UIImageView *chipsLimitButtonTriangle;
    UIImageView *playersCountButtonTriangle;
    
    
    //下部导航条按钮
    //底部不同房间导航条实现
    CGFloat navigationImageX;
    CGFloat navigationImageY;
    CGFloat navigationImageWidth;
    CGFloat navigationImageHeight;
    
    UIButton *newUserFieldButton;
    UIButton *primaryFieldButton;
    UIButton *intermediateFieldButton;
    UIButton *advancedFieldButton;
    
    //
    UIImageView *navigationImageView;
    
}

+ (MenuLayerNormalRoom *) sharedManager;

- (void)fullRoomChoiceButtonCallback;
//- (void)speedTypeChoiceButtonCallback;
- (void)roomIDNameButtonCallback;
- (void)betLimitOnceButtonCallback;
- (void)betTimesLimitButtonCallback;
- (void)chipsLimitButtonCallback;
- (void)playersCountButtonCallback;
- (void)newUserFieldButtonCallback;
- (void)primaryFieldButtonCallback;
- (void)doFieldButtonCallback:(NSInteger) fieldId fieldButton:(UIButton *) fieldButton roomTypePng:(NSString *) roomTypeSelectedPng;
- (void)intermediateFieldButtonCallback;
- (void)advancedFieldButtonCallback;
- (void)backToNormalRoom;

@end
