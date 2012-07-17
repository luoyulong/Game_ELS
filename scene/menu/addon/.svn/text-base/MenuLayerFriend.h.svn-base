//
//  MenuLayerFriend.h
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UITableLayer.h"
@interface MenuLayerFriend : UITableLayer
{
    UIImageView *m_backGroundView;
    
    UITableView *friendList;
    UIView      *showDetail;    
    UIImageView *centerShadowLine;

    
    //朋友列表组件
    UIImageView *littleHead;
    UIImageView *sex;
    UILabel  *nickName;
    UIImageView *stateIndicator;
    UIImageView *centerArrow;
    UIImageView *rowBackground;

    //详细信息组件
    UIImageView *bigHead;
    UITextView  *personalInfo;
    UIButton    *location;
    UIButton    *deleteFriend;
    
    //其他组件
    UIAlertView *deleteFriendAlert;
    
    NSInteger indexSelected;
}

@property (nonatomic, retain)UIImageView *m_backGroundView;

@property (nonatomic, retain)UITableView *friendList;
@property (nonatomic, retain)UIView *showDetail;

@property (nonatomic, retain)UIImageView *centerShadowLine;
@property (nonatomic, retain)UIImageView *centerArrow;
//朋友列表组件
@property (nonatomic, retain)UIImageView *littleHead;
@property (nonatomic, retain)UIImageView *sex;
@property (nonatomic, retain)UILabel  *nickName;
@property (nonatomic, retain)UIImageView *stateIndicator;
@property (nonatomic, retain)UIImageView *rowBackground;
//详细信息组件
@property (nonatomic, retain)UIImageView *bigHead;
@property (nonatomic, retain)UITextView  *personalInfo;
@property (nonatomic, retain)UIButton *location;
@property (nonatomic, retain)UIButton *deleteFriend;
//其他组件
@property (nonatomic, retain)UIAlertView *deleteFriendAlert;
@property (assign)NSInteger indexSelected;

+ (MenuLayerFriend *)sharedManager;

- (void)locationCallBack;
- (void)deleteCallBack;
- (void)reloadData;
- (void)getFriends;
@end
