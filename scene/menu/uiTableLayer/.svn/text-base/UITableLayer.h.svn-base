//
//  UITableLayer.h
//  GameBox
//
//  Created by  on 12-5-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

enum type_move {
    SINGLE_LAYER_MOVE = 0, // 覆盖先前的视图
    ALL_LAYER_MOVE = 1 // 切换,同时滑动
    };

@interface UITableLayer : UIViewController <UITableViewDelegate, UITableViewDataSource>
{
@protected
    UIImageView *backgroundView;
    
    UIButton *backButton; //返回按钮
    
    UITableView *uiTableView;
    
    UIActivityIndicatorView *aWaitnet;
    
    UILabel *titleLable;
    
    UIImageView *slideBlock;
}

- (id)init;

- (void)initSelfView;

- (void)makeButton:(UIButton *)button rect:(CGRect)cgRect;

- (void)makeTableView:(CGRect)cgRect style:(UITableViewStyle)tableViewStyle;

- (void)makeActivityIndicatorView:(CGRect)cgRect;

- (void)viewMoveToLeft:(NSInteger)moveType otherView:(UIView *)otview;
//- (void)viewMoveToLeftCallback;

- (void)viewMoveToRight:(NSInteger)moveType otherView:(UIView *)otview;

//窗口向上滑动至顶部
- (void)viewMoveToTop:(NSInteger)moveType otherView:(UIView *)otview;

//窗口向下滑动至隐藏
- (void)viewMoveToBottom:(NSInteger)moveType otherView:(UIView *)otview;

//返回按钮回调方法
- (void)backButtonCallback;

- (void)slideBlockOfButton:(CGRect)cgrect;
- (void)setSlideBlockFrame:(CGRect)cgrect;
- (void)setSlideBlockPosition:(CGRect)cgrect backgoundImageName:(NSString *)imageName;
- (void)setImageSlideBlock:(NSString *)imageName;

- (void)startAWaitnet;
- (void)stopAWaitnet;

//增加一个不变的图片
- (void)addUnchangedImageView:(CGRect)cgRect imageName:(NSString *)imageName;

- (void)switchAction;

@end
