//
//  MenuLayerMatchRoom.h
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GameRoomLayer.h"
#import "GlobalData.h"

@interface MenuLayerMatchRoom : GameRoomLayer
{
@private
    UIButton *playStateChoiceButton;
    UILabel *playStateChoiceButtonLable1;
    UILabel *playStateChoiceButtonLable2;
    
    UIButton *emptyRoomChoiceButton;
    UILabel *emptyRoomChoiceButtonLable1;
    UILabel *emptyRoomChoiceButtonLable2;
    
    //
    UIButton *IDSortButton;
    UIImageView *IDSortButtonTriangle;
    
    UIButton *bonusSortButton;
    UIImageView *bonusSortButtonTriangle;
    
    UIButton *stateSortButton;
    UIImageView *stateSortButtonTriangle;
    
    UIButton *feeSortButton;
    UIImageView *feeSortButtonTriangle;
    
    //游戏进行状态选择标志
    bool playingStateChoice;
    //房间满员状况选择标志
    bool emptyRoomChoice;
    
    // 排序方式 true为正序
    bool IDSortStyle;
    bool bonusSortStyle;
    bool stateSortStyle;
    bool feeSortStyle;
    
}

+ (MenuLayerMatchRoom *) sharedManager;

- (void)playStateChoiceButtonCallBack;
- (void)emptyRoomChoiceButtonCallBack;
- (void)IDSortButtonCallback;
- (void)bonusSortButtonCallback;
- (void)stateSortButtonCallback;
- (void)feeSortButtonCallback;
- (void)backToMatchRoom;

@end
