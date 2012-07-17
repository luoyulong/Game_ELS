//
//  MenuLayerStore.m
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "MenuLayerStore.h"
#import "AddonWrapper.h"
#import "GlobalData.h"
#import "UILabelStrikeThrough.h"
#import "SimpleAudioEngineWrapper.h"

@implementation MenuLayerStore
@synthesize iItems;
@synthesize chipStore;
@synthesize buyDetail;
@synthesize chooseButton;

static  MenuLayerStore *menuLayerStore = nil;

+(MenuLayerStore *)sharedManager
{
    if (!menuLayerStore) {
        menuLayerStore = [[MenuLayerStore alloc] init];
    }
    return menuLayerStore;
}

-(void)initSelfView
{
    [[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    //设置标题显示文字
    [titleLable setFrame:CGRectMake(backButton.frame.origin.x+backButton.frame.size.width+5, 10, 100, 25)];
    [titleLable setText:@"商城"];
    titleLable.textAlignment=UITextAlignmentLeft;
    [titleLable setFont:[UIFont fontWithName:@".HelvetiaNeueUI" size:25]];
    titleLable.backgroundColor = [UIColor clearColor];
    
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];
    //=======================================================================
    chipStore = [[UIButton alloc] initWithFrame:CGRectMake(230, 7.5, 90, 40)];    
    iItems = [[UIButton alloc] initWithFrame:CGRectMake(310.0, 7.5, 90, 40)];
    buyDetail = [[UIButton alloc] initWithFrame:CGRectMake(390, 7.5, 90, 40)];
    
    //=======================================================================
    [chipStore.layer setBackgroundColor:[UIColor blueColor].CGColor];
    chipStore.backgroundColor = [UIColor clearColor];

    [chipStore setTitle:@"筹码商城" forState:UIControlStateNormal];
    [chipStore.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [chipStore addTarget:self action:@selector(chipStoreCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    //=======================================================================    
    [iItems.layer setBackgroundColor:[UIColor blueColor].CGColor];
    iItems.backgroundColor = [UIColor clearColor];

    [iItems setTitle:@"我的道具" forState:UIControlStateNormal];
    [iItems.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [iItems addTarget:self action:@selector(iItemsCallBack) forControlEvents:UIControlEventTouchUpInside];
    //=======================================================================
    [buyDetail.layer setBackgroundColor:[UIColor blueColor].CGColor];
    buyDetail.backgroundColor = [UIColor clearColor];

    [buyDetail setTitle:@"购买明细" forState:UIControlStateNormal];
    [buyDetail.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [buyDetail addTarget:self action:@selector(buyDetailCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    //创建滑动阴影控件 
    /* 图片的大小为180x104，蓝色区域大小为173x64 */
    
    [self setSlideBlockFrame:CGRectMake(chipStore.frame.origin.x, 0, 180/2, 100/2)];
    [slideBlock setImage:[UIImage imageNamed:@"Store_arrow.png"]];
    
    
    backgroundview=[[[UIImageView alloc]initWithFrame:CGRectMake(10, 50, 460, 260)]autorelease];;
    backgroundview.image=[UIImage imageNamed:@"L2white.png"];
    [[self view] addSubview:backgroundview];
    
    [self makeTableView:CGRectMake(10, 50, 460, 260) style:UITableViewStylePlain];
    uiTableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;

    //[uiTableView setBackgroundView:backgroundview];
    //添加三个Button
    [[self view] addSubview:chipStore];
    [[self view] addSubview:iItems];
    [[self view] addSubview:buyDetail];
    
    strncpy(g_coin_store.original_coin[0], "300金币", 32);
    strncpy(g_coin_store.original_coin[1], "600金币", 32);
    strncpy(g_coin_store.original_coin[2], "1,800金币", 32);
    strncpy(g_coin_store.original_coin[3], "4,200金币", 32);
    strncpy(g_coin_store.original_coin[4], "9,000金币", 32);
    strncpy(g_coin_store.original_coin[5], "25,000金币", 32);
    strncpy(g_coin_store.original_coin[6], "70,000金币", 32);
    
    strncpy(g_coin_store.current_coin[0], "320金币", 32);
    strncpy(g_coin_store.current_coin[1], "660金币", 32);
    strncpy(g_coin_store.current_coin[2], "2,000金币", 32);
    strncpy(g_coin_store.current_coin[3], "4,600金币", 32);
    strncpy(g_coin_store.current_coin[4], "13,000金币", 32);
    strncpy(g_coin_store.current_coin[5], "40,000金币", 32);
    strncpy(g_coin_store.current_coin[6], "90,000金币", 32);
    
    strncpy(g_coin_store.price[0], "￥6.00", 16);
    strncpy(g_coin_store.price[1], "￥12.00", 16);
    strncpy(g_coin_store.price[2], "￥30.00", 16);
    strncpy(g_coin_store.price[3], "￥68.00", 16);
    strncpy(g_coin_store.price[4], "￥128.00", 16);
    strncpy(g_coin_store.price[5], "￥328.00", 16);
    strncpy(g_coin_store.price[6], "￥648.00", 16);
}

- (void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    menuLayerStoreHide();
}

-(void) chipStoreCallBack
{
    chooseButton=1;
    [self slideBlockOfButton:CGRectMake(chipStore.frame.origin.x, 0, 180/2, 104/2)];
    
    for (UIView *view in uiTableView.subviews) {
        [view  removeFromSuperview];
    }
    [self reloadData];
    NSLog(@"筹码商城\n");
}

- (void) iItemsCallBack
{
    chooseButton=2;
    [self slideBlockOfButton:CGRectMake(iItems.frame.origin.x, 0, 180/2, 104/2)];
    [self reloadData];
    for (UIView *view in uiTableView.subviews) {
        [view  removeFromSuperview];
    }
    
    if (g_user.items_count==0) {
        UILabel *message=[[[UILabel alloc] initWithFrame:CGRectMake(150, 100, 200, 30)]autorelease];
        message.text=@"没有相应的道具";
        message.textAlignment=UITextAlignmentCenter;
        message.backgroundColor=[UIColor clearColor];
        [uiTableView addSubview:message];
    }
    
    NSLog(@"我的道具\n");
}

- (void) buyDetailCallBack
{
    chooseButton=3;
    [self slideBlockOfButton:CGRectMake(buyDetail.frame.origin.x, 0, 180/2, 104/2)];
    [self reloadData];
    for (UIView *view in uiTableView.subviews) {
        [view  removeFromSuperview];
    }
    
    
    UILabel *message=[[[UILabel alloc] initWithFrame:CGRectMake(150, 100, 200, 30)]autorelease];
    message.backgroundColor=[UIColor clearColor];
    message.text=@"没有购买记录";
    message.textAlignment=UITextAlignmentCenter;
    [uiTableView addSubview:message];
    
    
    NSLog(@"购买明细\n");
}

//Cell的高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 45;
}

//Cell的数量
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    int countOfRow=0;
    if (chooseButton==1) {
         countOfRow=7;
    }
    else if (chooseButton==2) {
        countOfRow=g_user.items_count;
    }
    else if (chooseButton==3) {
        //暂时还不支持该功能
        countOfRow=0;
    }
    
    NSLog(@"chooseButton=%d, countOfRow=%d  g_user.items_count=%d\n", chooseButton, countOfRow, g_user.items_count);
    NSLog(@"Cell 数量\n");
    return countOfRow;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"\n MenuLayerStore =====indexPath.row=%d=====\n",indexPath.row);
    static NSString *SimpleTableIdentifier = @"MenuLayerStore";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) { 
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    if (chooseButton==1) {
        //金币图标
        UIImageView *coinPic = [[[UIImageView alloc] initWithFrame:CGRectMake(5, 0, 45, 45)]autorelease];
        [coinPic setImage:[UIImage imageNamed:@"vip_chip.png"]];
        coinPic.backgroundColor=[UIColor clearColor];
        [cell.contentView addSubview:coinPic];
        //原价现价
        UILabelStrikeThrough *originalPrice=[[[UILabelStrikeThrough alloc] initWithFrame:CGRectMake(coinPic.frame.origin.x+coinPic.frame.size.width+5, 0, 120, 15)]autorelease];
        originalPrice.isWithStrikeThrough=TRUE;
        
        UILabel *currentprice=[[[UILabel alloc]initWithFrame:CGRectMake(originalPrice.frame.origin.x, originalPrice.frame.origin.y+originalPrice.frame.size.height, 120, 25)]autorelease];
        originalPrice.backgroundColor=[UIColor clearColor];
        currentprice.backgroundColor=[UIColor clearColor];
        originalPrice.text=[NSString stringWithUTF8String:g_coin_store.original_coin[indexPath.row]];
        //NSLog(@"indexPath=%d, UUUUUUUU%@",indexPath.row, [NSString stringWithUTF8String:g_rewardInfo.name[indexPath.row]]);
        currentprice.text=[NSString stringWithUTF8String:g_coin_store.current_coin[indexPath.row]];
        originalPrice.textAlignment=UITextAlignmentLeft;
        currentprice.textAlignment=UITextAlignmentLeft;
        originalPrice.font=[UIFont fontWithName:@"Helvetica" size:12];
        currentprice.font=[UIFont fontWithName:@"Helvetica" size:18];

        [cell.contentView addSubview:originalPrice];
        [cell.contentView addSubview:currentprice];
        //价格
        UILabel *price=[[[UILabel alloc]initWithFrame:CGRectMake(270, 0, 80, 45)]autorelease];;
        price.backgroundColor=[UIColor clearColor];
        price.text=[NSString stringWithUTF8String:g_coin_store.price[indexPath.row]];
        price.textAlignment=UITextAlignmentLeft;
        //price.textColor=[UIColor colorWithRed:244 green:164 blue:96 alpha:0.8];
        price.font=[UIFont fontWithName:@"Helvetica" size:14];
        [cell.contentView addSubview:price];
        //购买
        UIButton *buy=[[[UIButton alloc]initWithFrame:CGRectMake(380, 5, 80, 34)]autorelease];
        [buy setTitle:@"购买" forState:UIControlStateNormal];
        [buy setBackgroundImage:[UIImage imageNamed:@"SendButton.png"] forState:UIControlStateNormal];
        [cell.contentView addSubview:buy];
    }
    else if (chooseButton==2) {
        //待确定
    }
    else if (chooseButton==3) {
        //待确定
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    //Not Implement
}

-(void)reloadData
{
    [uiTableView reloadData];
}

@end
