//
//  MenuLayerNormalRoom.h
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "UITableLayer.h"
#import "GlobalData.h"

@interface GameRoomLayer : UITableLayer
{
@public
    //最后一次点击排序依据
    //房间ID:0 最小投注数:1 手数:2 最少携带筹码:3
    NSInteger sortFocusOn;
    NSInteger preSortFocusOn;
    
@protected
    bool ignoreBackbuttonClick;
    
    NSMutableArray *sortButtonArray;
    NSMutableArray *buttonTriangleArray;
    
    UIButton *refreshButton;
    
    UIImageView *tableImageView;
    
    //显示个人信息
    UITableView *userInfoView;
    UILabel *nickLable;
    UILabel *coinLable;
    
    //房间号
    NSInteger roomId;
    //桌子列表
    vector<TABLE_INFO*> table_list;
}

- (void)initSelfRoom;

- (void)addSortButton:(UIButton **)button frame:(CGRect)cgrect title:(NSString *)buttonTitle callback:(SEL)funcallback;

- (void)addNavigationButton:(UIButton **)button frame:(CGRect)cgrect title:(NSString *)buttonTitle callback:(SEL)funcallback;

- (void)addButtonTriangleView:(UIImageView **)imageView cgrect:(CGRect)cgrect imageName:(NSString *)imageName;

- (void)rotateButtonTriangleView:(UIImageView *)imageView angle:(CGFloat)angle;

- (void)doSortTableList:(NSInteger)_sortFocusOn sortStyle:(bool *)sortStyle;

- (void)setSortButtonTitle;

- (void)sortTableList;

- (void)addLableView:(UILabel **)lable cgrect:(CGRect)cgrect fontSize:(NSInteger)fontSize addToView:(UIView *)uiView;

- (void)refreshTableView;

- (void)reloadTableViewData;

- (void)reloadUserInfo;

- (void)addPlayers:(NSInteger)rowIndex frameOriginX:(CGFloat)originX frameOriginY:(CGFloat)originY addToCell:(UITableViewCell *)cell;

//- (void)backToRoomCallback;
- (void)refreshButtonCallback;
@end
