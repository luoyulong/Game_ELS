//
//  CommonLayerSet.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MenuLayerUserDetail.h"
#import "SimpleAudioEngineWrapper.h"

@implementation MenuLayerUserDetail
static MenuLayerUserDetail *menuLayerUserDetail = nil;

+ (MenuLayerUserDetail *) sharedManager
{
    if(!menuLayerUserDetail)
        menuLayerUserDetail=[[MenuLayerUserDetail alloc] init];
    return menuLayerUserDetail;
}

- (void)initSelfView
{
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    
    [titleLable setFrame:CGRectMake(180, 10, 200, 25)];
    [titleLable setText:@"修改个人信息"];
    [titleLable setBackgroundColor:[UIColor clearColor]];
    [titleLable setTextColor:[UIColor whiteColor]];
    [titleLable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:25]];
    
    
    [self makeTableView:CGRectMake(240, 60, 220, 230) style:UITableViewStylePlain];
    uiTableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;
    //[uiTableView setBackgroundColor:[UIColor clearColor]];
    uiTableView.scrollEnabled=YES;
    [uiTableView setBackgroundColor:[UIColor clearColor]];
    
    //任务中心UITableView的白背景
    UIImageView *uiTableViewBkg=[[[UIImageView alloc]initWithFrame:CGRectMake(10, 50, 460, 260)] autorelease];
    uiTableViewBkg.image=[UIImage imageNamed:@"L2white.png"];
    uiTableViewBkg.backgroundColor=[UIColor clearColor];
    //[uiTableView addSubview:uiTableViewBkg];       
    [[self view] addSubview:uiTableViewBkg];
    [[self view] addSubview:uiTableView];
}



- (void)backButtonCallback
{
    //NSLog(@"back button test");
    //menuLayerSetHiddenFigure();
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    [[MenuLayerUserDetail sharedManager] viewMoveToRight:SINGLE_LAYER_MOVE otherView:nil];
}

- (void)showPlayTableButtonCallBack
{
    
}

- (void)hiddenPlayTbleButtonCallBack
{
    
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];//选中后的反显颜色即刻消失
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    return 2;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{

	return 200;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *SimpleTableIdentifier = @"SimpleTableIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    if (indexPath.row==0) 
    {
        UILabel *nameLabel=[[[UILabel alloc] initWithFrame:CGRectMake(10, 10, 200, 200)]autorelease];    
        nameLabel.backgroundColor=[UIColor clearColor];
        nameLabel.numberOfLines=0;
        nameLabel.text=@"性别：\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t男\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t女\n\n资产：\t\t\t\t\t\t\t\t\t\t\t$588\n\n等级：\t\t\t\t\t\t\t\t\t\t\t平民\n\n道具：\n\n现居住地：\n";
        nameLabel.textAlignment=UITextAlignmentLeft;
        nameLabel.lineBreakMode = UILineBreakModeWordWrap;
        nameLabel.font=[UIFont fontWithName:@"Helvetica" size:12];
        [cell.contentView addSubview:nameLabel];
    }
    else 
    {
        UILabel *nameLabel=[[[UILabel alloc] initWithFrame:CGRectMake(10, -20, 200, 200)]autorelease];    
        nameLabel.backgroundColor=[UIColor clearColor];
        nameLabel.numberOfLines=0;
        nameLabel.text=@"胜率：\t\t\t\t\t\t\t\t\t\t\t%13\n\n最大手牌：\t\t\t\t\t\t\t\t\n\n已玩局数：\t\t\t\t22\n\n最高拥有：\t\t\t\t$88888\n\n最大赢取：\t\t\t\t8888\n";
        nameLabel.textAlignment=UITextAlignmentLeft;
        nameLabel.lineBreakMode = UILineBreakModeWordWrap;
        nameLabel.font=[UIFont fontWithName:@"Helvetica" size:12];
        [cell.contentView addSubview:nameLabel];

    }
    
    return cell;
}

@end
