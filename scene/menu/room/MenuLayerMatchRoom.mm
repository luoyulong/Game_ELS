//
//  MenuLayerMatchRoom.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MenuLayerMatchRoom.h"
#import "RoomWrapper.h"
#import "gameNetCenter.h"
#import "AppDelegate.h"

@implementation MenuLayerMatchRoom

static MenuLayerMatchRoom *menuLayerMatchRoom = nil;

+ (MenuLayerMatchRoom *) sharedManager
{
    if(!menuLayerMatchRoom)
        menuLayerMatchRoom=[[MenuLayerMatchRoom alloc] init];
    return menuLayerMatchRoom;
}

- (void)initSelfRoom
{
    playingStateChoice = true;
    emptyRoomChoice = true;
    IDSortStyle = true;
    bonusSortStyle = true;
    stateSortStyle = true;
    feeSortStyle = true;
    
    // 设置比赛场
    [titleLable setFrame:CGRectMake(201.0, 5.0, 78, 25)];
    [titleLable setText:@"比赛场"];
    
    // 设置列表背景图
    [tableImageView setFrame:CGRectMake(7.0, 42, 466.0, 272)];
    [tableImageView setImage:[UIImage imageNamed:@"Roomlist_backgroundBox_sng.png"]];
    
    //tableView设置
    [self makeTableView:CGRectMake(7.0, 73, 466.0, 239) style:UITableViewStylePlain];
    [self makeActivityIndicatorView:CGRectMake(225.0, 178, 30.0, 30)];
    
    // 选择桌子状态
    playStateChoiceButton = [[UIButton alloc] init];
    [self makeButton:playStateChoiceButton rect:CGRectMake(330.0, 7.5, 52, 30)];
    [playStateChoiceButton setImage:[UIImage imageNamed:@"Roomlist_button.png"] forState:UIControlStateNormal];
    [playStateChoiceButton addTarget:self action:@selector(playStateChoiceButtonCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [self addLableView:&playStateChoiceButtonLable1 cgrect:CGRectMake(11.0, 3.5, 32, 10) fontSize:10.0 addToView:playStateChoiceButton];
    [playStateChoiceButtonLable1 setText:@"进行中"];
    [self addLableView:&playStateChoiceButtonLable2 cgrect:CGRectMake(12.5, 14.0, 26, 13) fontSize:13.0 addToView:playStateChoiceButton];
    [playStateChoiceButtonLable2 setText:@"显示"];
    
    // 空房间是否显示
    emptyRoomChoiceButton = [[UIButton alloc] init];
    [self makeButton:emptyRoomChoiceButton rect:CGRectMake(388.0, 7.5, 52, 30)];
    [emptyRoomChoiceButton setImage:[UIImage imageNamed:@"Roomlist_button.png"] forState:UIControlStateNormal];
    [emptyRoomChoiceButton addTarget:self action:@selector(emptyRoomChoiceButtonCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [self addLableView:&emptyRoomChoiceButtonLable1 cgrect:CGRectMake(11.0, 3.5, 32, 10) fontSize:10.0 addToView:emptyRoomChoiceButton];
    [emptyRoomChoiceButtonLable1 setText:@"空房间"];
    [self addLableView:&emptyRoomChoiceButtonLable2 cgrect:CGRectMake(12.5, 14.0, 26, 13) fontSize:13.0 addToView:emptyRoomChoiceButton];
    [emptyRoomChoiceButtonLable2 setText:@"显示"];
    
    // 房间"ID"排序按钮
    [self addSortButton:&IDSortButton frame:CGRectMake(7.0, 42.0, 66.0, 31.0) title:@"ID" callback:@selector(IDSortButtonCallback)];
    [self addUnchangedImageView:CGRectMake(73.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    [self addButtonTriangleView:&IDSortButtonTriangle cgrect:CGRectMake(57.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "一/二名奖金"排序按钮
    [self addSortButton:&bonusSortButton frame:CGRectMake(73.0, 42.0, 150, 31.0) title:@"一/二名奖金" callback:@selector(bonusSortButtonCallback)];
    [self addUnchangedImageView:CGRectMake(223.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    [self addButtonTriangleView:&bonusSortButtonTriangle cgrect:CGRectMake(200.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "状态"排序按钮
    [self addSortButton:&stateSortButton frame:CGRectMake(227.0, 42.0, 150, 31.0) title:@"状态" callback:@selector(stateSortButtonCallback)];
    [self addUnchangedImageView:CGRectMake(373.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    [self addButtonTriangleView:&stateSortButtonTriangle cgrect:CGRectMake(350.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "参赛费/服务费"排序按钮
    [self addSortButton:&feeSortButton frame:CGRectMake(373.0, 42.0, 100.0, 31.0) title:@"参赛费/服务费" callback:@selector(feeSortButtonCallback)];
    [self addButtonTriangleView:&feeSortButtonTriangle cgrect:CGRectMake(459.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
}

- (void)backButtonCallback
{
    if (ignoreBackbuttonClick) 
    {
        return;
    }
    
    playingStateChoice = true;
    emptyRoomChoice = true;
    IDSortStyle = true;
    bonusSortStyle = true;
    stateSortStyle = true;
    feeSortStyle = true;
    
    g_table_list.clear();
    table_list.clear();
    
    gameNetCenter::GetInstance()->closeConn();
    GEDirector::GetInstance()->gotoScene("StateMainMenu", MoveToRight, 0);
    menuLayerMatchRoomHidden();
}

- (void)playStateChoiceButtonCallBack
{
    playingStateChoice = !playingStateChoice;
    [self sortTableList];
}

- (void)emptyRoomChoiceButtonCallBack
{
    emptyRoomChoice = !emptyRoomChoice;
    [self sortTableList];
}

- (void)IDSortButtonCallback
{
    [self doSortTableList:0 sortStyle:&IDSortStyle];
}

- (void)bonusSortButtonCallback
{
    [self doSortTableList:1 sortStyle:&bonusSortStyle];
}

- (void)stateSortButtonCallback
{
    [self doSortTableList:2 sortStyle:&stateSortStyle];
}

- (void)feeSortButtonCallback
{
    [self doSortTableList:3 sortStyle:&feeSortStyle];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{

    static NSString *SimpleTableIdentifier = @"SimpleTableIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    
    [cell setBackgroundColor:[UIColor clearColor]];
    [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    
    UIImageView *cellBackgroundImageView = [[[UIImageView alloc] initWithFrame:CGRectMake(0.0, 0.0, 466.0, 41.0)] autorelease];
    [cellBackgroundImageView setImage:[UIImage imageNamed:@"Roomlist_cellNormal.png"]];
    [[cell contentView] addSubview:cellBackgroundImageView];
    
    //房间ID
    UILabel *roomIdLable;
    [self addLableView:&roomIdLable cgrect:CGRectMake(21, 0, 80, 41) fontSize:12.0 addToView:cell.contentView];
    [roomIdLable setText:[NSString stringWithFormat:@"%d", table_list[indexPath.row]->tid]];
    
    //状态
    UILabel *stateLable;
    [self addLableView:&stateLable cgrect:CGRectMake(240.0, 0, 32, 41) fontSize:10.0 addToView:cell.contentView];
    if (table_list[indexPath.row]->state == TABLE3CSTAT_IDLE)
    {  
        [stateLable setText:@"准备中"];
    }
    else if (table_list[indexPath.row]->state == TABLE3CSTAT_PLAYING)
    {
        [stateLable setText:@"进行中"];
    }
    
    [self addPlayers:indexPath.row frameOriginX:275.0 frameOriginY:15.0 addToCell:cell];
    
    return cell;
}

- (void)sortTableList
{
    table_list.clear();
    
    switch (sortFocusOn)
    {
        case 0:
            stable_sort(g_table_list.begin(), g_table_list.end(), (IDSortStyle?roomIdLessCmp:roomIdGreaterCmp));
            [self rotateButtonTriangleView:IDSortButtonTriangle angle:(IDSortStyle?3.14159:0)];
            break;
            
        case 1:
            [self rotateButtonTriangleView:bonusSortButtonTriangle angle:(bonusSortStyle?3.14159:0)];
            break;
            
        case 2:
            stable_sort(g_table_list.begin(), g_table_list.end(), (stateSortStyle?stateLessCmp:stateGreaterCmp));
            [self rotateButtonTriangleView:stateSortButtonTriangle angle:(stateSortStyle?3.14159:0)];
            break;
            
        case 3:
            [self rotateButtonTriangleView:feeSortButtonTriangle angle:(feeSortStyle?3.14159:0)];
            break;
    }
    
    [playStateChoiceButtonLable2 setText:(playingStateChoice?@"显示":@"隐藏")];
    [emptyRoomChoiceButtonLable2 setText:(emptyRoomChoice?@"显示":@"隐藏")];
    
    vector<TABLE_INFO *>::iterator iter;
    for(iter = g_table_list.begin(); iter != g_table_list.end(); iter++)
    {
        //选择进行中状态桌子是否显示 playingStateChoice=False,将进行中状态桌子过滤掉
        if (!playingStateChoice && (*iter)->state == TABLE3CSTAT_PLAYING)
        {
            continue;
        }
        //选择隐藏空房间 emptyRoomChoice=False,将空房间过滤掉
        if (!emptyRoomChoice && (*iter)->currentSeat == 0)
        {
            continue;
        }
        table_list.push_back(*iter);
    }
    
    [uiTableView reloadData];
}

- (void)backToMatchRoom
{
    ignoreBackbuttonClick = NO;
    
    table_list.clear();
    [uiTableView reloadData];
    [self startAWaitnet];
    gameNetCenter::GetInstance()->refreshRoom();
    
    [[menuLayerMatchRoom view] setFrame:CGRectMake(0.0, -480.0, 320.0, 480.0)];
    [[menuLayerMatchRoom view] setHidden:NO];
    
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    
    GETouchDispatcher::GetInstance()->setDispatchEvents(true);
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [[menuLayerMatchRoom view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    [[ad.viewController view] setFrame:CGRectMake(0.0, 480.0, 320.0, 480.0)];
    [UIView setAnimationDelegate:self];
//    [UIView setAnimationDidStopSelector:@selector(backToRoomCallback)];
    [UIView commitAnimations];
}

@end
