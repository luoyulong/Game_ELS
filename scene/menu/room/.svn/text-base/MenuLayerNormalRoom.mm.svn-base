//
//  MenuLayerNormalRoom.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MenuLayerNormalRoom.h"
#import "RoomWrapper.h"
#import "gameNetCenter.h"
#import "AppDelegate.h"

@implementation MenuLayerNormalRoom
static MenuLayerNormalRoom *menuLayerNormalRoom = nil;

+ (MenuLayerNormalRoom *) sharedManager
{
    if(!menuLayerNormalRoom)
    {
        menuLayerNormalRoom=[[MenuLayerNormalRoom alloc] init];
    }
        return menuLayerNormalRoom;
}

- (void)initSelfRoom
{
    fullRoomChoice = true;
    IDSortStyle = true;
    betLimitSortStyle = true;
    betTimesSortStyle = true;
    chipsSortStyle = true;
    playersSortStyle = true;
    
    // 设置列表背景图
    [tableImageView setFrame:CGRectMake(7.0, 42, 466.0, 238)];
    [tableImageView setImage:[UIImage imageNamed:@"Roomlist_backgroundBox_game.png"]];
    
    // 视图名称
    [titleLable setFrame:CGRectMake(188.0, 5.0, 104, 25)];
    [titleLable setText:@"游戏大厅"];
    
    // 满房间显示是否显示设置
    fullRoomChoiceButton = [[UIButton alloc] init];
    [self makeButton:fullRoomChoiceButton rect:CGRectMake(388.0, 7.5, 52, 30)];
    [fullRoomChoiceButton setImage:[UIImage imageNamed:@"Roomlist_button.png"] forState:UIControlStateNormal];
    [fullRoomChoiceButton addTarget:self action:@selector(fullRoomChoiceButtonCallback) forControlEvents:UIControlEventTouchUpInside];
    [self addLableView:&fullRoomButtonLable1 cgrect:CGRectMake(11.0, 3.5, 32, 10) fontSize:10.0 addToView:fullRoomChoiceButton];
    [fullRoomButtonLable1 setText:@"满房间"];
    [self addLableView:&fullRoomButtonLable2 cgrect:CGRectMake(12.5, 14.0, 26, 13) fontSize:13.0 addToView:fullRoomChoiceButton];
    [fullRoomButtonLable2 setText:@"显示"];
    
    // "房间ID"排序按钮
    [self addSortButton:&roomIDNameButton frame:CGRectMake(7.0, 42.0, 94, 31) title:@"ID/房间名" callback:@selector(roomIDNameButtonCallback)];
    [self addButtonTriangleView:&roomIDNameButtonTriangle cgrect:CGRectMake(85.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "基数/单注封顶"排序按钮
    [self addSortButton:&betLimitOnceButton frame:CGRectMake(102.0, 42.0, 99, 31) title:@"基数/单注封顶" callback:@selector(betLimitOnceButtonCallback)];
    [self addButtonTriangleView:&betLimitOnceButtonTriangle cgrect:CGRectMake(190.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "可比/封顶手数"排序按钮
    [self addSortButton:&betTimesLimitButton frame:CGRectMake(202.0, 42.0, 99, 31) title:@"可比/封顶手数" callback:@selector(betTimesLimitButtonCallback)];
    [self addButtonTriangleView:&betTimesLimitButtonTriangle cgrect:CGRectMake(288.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "最小携带"排序按钮
    [self addSortButton:&chipsLimitButton frame:CGRectMake(302.0, 42.0, 70, 31) title:@"最小携带" callback:@selector(chipsLimitButtonCallback)];
    [self addButtonTriangleView:&chipsLimitButtonTriangle cgrect:CGRectMake(360.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    // "在玩人数"排序按钮
    [self addSortButton:&playersCountButton frame:CGRectMake(373.0, 42.0, 99, 31) title:@"在玩人数" callback:@selector(playersCountButtonCallback)];
    [self addButtonTriangleView:&playersCountButtonTriangle cgrect:CGRectMake(450.0, 54.5, 10, 6) imageName:@"Roomlist_triangleSelected.png"];
    
    [self setSortButtonTitle];
    
    // 排序按钮之间的分割线
    [self addUnchangedImageView:CGRectMake(101.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    [self addUnchangedImageView:CGRectMake(201.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    [self addUnchangedImageView:CGRectMake(301.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    [self addUnchangedImageView:CGRectMake(372.0, 47.5, 2, 20) imageName:@"Roomlist_cutoffLine1.png"];
    
    //tableView设置
    [self makeTableView:CGRectMake(7.0, 73, 466.0, 205) style:UITableViewStylePlain];
    [self makeActivityIndicatorView:CGRectMake(225.0, 160, 30.0, 30)];
    
    //底部不同房间导航条实现
    navigationImageX = 7.0;
    navigationImageY = 285.0;
    navigationImageWidth = 466;
    navigationImageHeight = 30;
    
    navigationImageView = [[UIImageView alloc] initWithFrame:CGRectMake(navigationImageX, navigationImageY, navigationImageWidth, navigationImageHeight)];
    [navigationImageView setImage:[UIImage imageNamed:@"Roomlist_navigation.png"]];
    [[self view] addSubview:navigationImageView];
    
    [self setSlideBlockFrame:CGRectMake(navigationImageX, navigationImageY-7, navigationImageWidth/4, 44)];
    [slideBlock setImage:[UIImage imageNamed:@"Roomlist_roomTypeSelected2.png"]];
    
    // "新手场"导航条按钮
    [self addNavigationButton:&newUserFieldButton frame:CGRectMake(navigationImageX, navigationImageY, navigationImageWidth/4, navigationImageHeight) title:@"新手场" callback:@selector(newUserFieldButtonCallback)];
    
    // "初级场"导航条按钮
    [self addNavigationButton:&primaryFieldButton frame:CGRectMake((navigationImageX+navigationImageWidth/4), navigationImageY, navigationImageWidth/4, navigationImageHeight) title:@"初级场" callback:@selector(primaryFieldButtonCallback)];
    
    // "中级场"导航条按钮
    [self addNavigationButton:&intermediateFieldButton frame:CGRectMake((navigationImageX+navigationImageWidth/2), navigationImageY, navigationImageWidth/4, navigationImageHeight) title:@"中级场" callback:@selector(intermediateFieldButtonCallback)];
    
    // "高级场"导航条按钮
    [self addNavigationButton:&advancedFieldButton frame:CGRectMake(navigationImageX+(navigationImageWidth/4)*3, navigationImageY, navigationImageWidth/4, navigationImageHeight) title:@"高级场" callback:@selector(advancedFieldButtonCallback)];
    
    // 导航条竖直分割线
    for (NSInteger i=1; i<=3; i++) {
        [self addUnchangedImageView:CGRectMake(navigationImageX+(navigationImageWidth/4)*i-1, navigationImageY+5, 2, 20) imageName:@"Roomlist_cutoffLine2.png"];
    }
}

- (void)backButtonCallback
{
    if (ignoreBackbuttonClick) 
    {
        return;
    }
    
    fullRoomChoice = true;
    IDSortStyle = true;
    betLimitSortStyle = true;
    betTimesSortStyle = true;
    chipsSortStyle = true;
    playersSortStyle = true;
    
    g_table_list.clear();
    table_list.clear();
    
    gameNetCenter::GetInstance()->closeConn();
    GEDirector::GetInstance()->gotoScene("StateMainMenu", MoveToRight, 0);
    menuLayerNormalRoomHidden();
}

- (void)fullRoomChoiceButtonCallback
{
    fullRoomChoice = !fullRoomChoice;
    [self sortTableList];
}

- (void)roomIDNameButtonCallback
{
    [self doSortTableList:0 sortStyle:&IDSortStyle];
}

- (void)betLimitOnceButtonCallback
{
    [self doSortTableList:1 sortStyle:&betLimitSortStyle];
}

- (void)betTimesLimitButtonCallback
{
    [self doSortTableList:2 sortStyle:&betTimesSortStyle];
}

- (void)chipsLimitButtonCallback
{
    [self doSortTableList:3 sortStyle:&chipsSortStyle];
}

- (void)playersCountButtonCallback
{
    [self doSortTableList:4 sortStyle:&playersSortStyle];
}

- (void)newUserFieldButtonCallback
{
    [self doFieldButtonCallback:1 fieldButton:newUserFieldButton roomTypePng:@"Roomlist_roomTypeSelected2.png"];
}

- (void)primaryFieldButtonCallback
{
    [self doFieldButtonCallback:2 fieldButton:primaryFieldButton roomTypePng:@"Roomlist_roomTypeSelected1.png"];
}

- (void)intermediateFieldButtonCallback
{
    [self doFieldButtonCallback:3 fieldButton:intermediateFieldButton roomTypePng:@"Roomlist_roomTypeSelected1.png"];
}

- (void)advancedFieldButtonCallback
{
    [self doFieldButtonCallback:4 fieldButton:advancedFieldButton roomTypePng:@"Roomlist_roomTypeSelected3.png"];
}

- (void)doFieldButtonCallback:(NSInteger) fieldId fieldButton:(UIButton *) fieldButton roomTypePng:(NSString *) roomTypeSelectedPng
{
    table_list.clear();
    [uiTableView reloadData];
    [self startAWaitnet];
    if(g_roomId==fieldId)
        gameNetCenter::GetInstance()->refreshRoom();
    else {
        gameNetCenter::GetInstance()->closeConn();
        gameNetCenter::GetInstance()->enterRoom(fieldId);
    }
    [self setImageSlideBlock:roomTypeSelectedPng];
    [self slideBlockOfButton:CGRectMake(fieldButton.frame.origin.x, fieldButton.frame.origin.y-7, fieldButton.frame.size.width, 44)];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
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
    
    // 房间ID
    UILabel *roomIdLable;
    [self addLableView:&roomIdLable cgrect:CGRectMake(14, 0, 80, 41) fontSize:12.0 addToView:cell.contentView];
    NSString *roomName = [NSString stringWithUTF8String: table_list[indexPath.row]->name];
    [roomIdLable setText:[NSString stringWithFormat:@"%d / %@", table_list[indexPath.row]->tid, roomName]];
    
    // 基数/单注封顶
    UILabel *betLimitLable;
    [self addLableView:&betLimitLable cgrect:CGRectMake(131, 0, 64, 41) fontSize:12.0 addToView:cell.contentView];
    [betLimitLable setText:[NSString stringWithFormat:@"%d / %d", table_list[indexPath.row]->baseBet, table_list[indexPath.row]->maxBet]];
    
    // 可比手数/封顶手数
    UILabel *betTimesLimitLable;
    [self addLableView:&betTimesLimitLable cgrect:CGRectMake(220, 0, 70, 41) fontSize:12.0 addToView:cell.contentView];
    [betTimesLimitLable setText:[NSString stringWithFormat:@"%d / %d", table_list[indexPath.row]->pkHand, table_list[indexPath.row]->maxHand]];
    
    // 最少携带筹码
    UILabel *carryLimitLable;
    [self addLableView:&carryLimitLable cgrect:CGRectMake(315, 0, 80, 41) fontSize:12.0 addToView:cell.contentView];
    [carryLimitLable setText:[NSString stringWithFormat:@"%d", table_list[indexPath.row]->minCoin]];
    
    // 在玩人数
    [self addPlayers:indexPath.row frameOriginX:379.0 frameOriginY:15.0 addToCell:cell];
    
    return cell;
}

- (void)setImageSlideBlock:(NSString *)imageName
{
    [slideBlock setImage:[UIImage imageNamed:imageName]];
}

- (void)sortTableList
{
    table_list.clear();
    
    switch (sortFocusOn)
    {
        case 0:
            stable_sort(g_table_list.begin(), g_table_list.end(), (IDSortStyle?roomIdLessCmp:roomIdGreaterCmp));
            [self rotateButtonTriangleView:roomIDNameButtonTriangle angle:(IDSortStyle?3.14159:0)];
            break;
            
        case 1:
            stable_sort(g_table_list.begin(), g_table_list.end(), (betLimitSortStyle?baseBetLessCmp:baseBetGreaterCmp));
            [self rotateButtonTriangleView:betLimitOnceButtonTriangle angle:(betLimitSortStyle?3.14159:0)];
            break;
            
        case 2:
            stable_sort(g_table_list.begin(), g_table_list.end(), (betTimesSortStyle?pkHandLessCmp:pkHandGreaterCmp));
            [self rotateButtonTriangleView:betTimesLimitButtonTriangle angle:(betTimesSortStyle?3.14159:0)];
            break;
            
        case 3:
            stable_sort(g_table_list.begin(), g_table_list.end(), (chipsSortStyle?minCoinLessCmp:minCoinGreaterCmp));
            [self rotateButtonTriangleView:chipsLimitButtonTriangle angle:(chipsSortStyle?3.14159:0)];
            break;
            
        case 4:
            stable_sort(g_table_list.begin(), g_table_list.end(), (chipsSortStyle?currentSeatLessCmp:currentSeatGreaterCmp));
            [self rotateButtonTriangleView:playersCountButtonTriangle angle:(playersSortStyle?3.14159:0)];
            break;
    }
    
    [fullRoomButtonLable2 setText:(fullRoomChoice?@"显示":@"隐藏")];
    
    vector<TABLE_INFO *>::iterator iter;
    for(iter = g_table_list.begin(); iter != g_table_list.end(); iter++)
    {
        //选择隐藏满员房间 fullRoomChoice=False,将满员房间过滤掉
        if (!fullRoomChoice && (*iter)->currentSeat >= 6)
        {
            continue;
        }
        table_list.push_back(*iter);
    }
    
    [uiTableView reloadData];
}

- (void)makeButtonTriangleView:(UIImageView **)imageView cgrect:(CGRect)cgrect imageName:(NSString *)imageName
{
    *imageView = [[[UIImageView alloc] initWithFrame:cgrect] autorelease];
    [*imageView setHidden:YES];
    [*imageView setImage:[UIImage imageNamed:imageName]];
    [[self view] addSubview:*imageView];
}

- (void)rotateButtonTriangleView:(UIImageView *)imageView angle:(CGFloat)angle
{
    CGAffineTransform transform = CGAffineTransformMakeRotation(angle);
    [imageView setTransform:transform];
}

- (void)backToNormalRoom
{
    ignoreBackbuttonClick = NO;
    
    table_list.clear();
    [uiTableView reloadData];
    [self startAWaitnet];
    
    gameNetCenter::GetInstance()->refreshRoom();
    
    [[self view] setFrame:CGRectMake(0.0, -480.0, 320.0, 480.0)];
    [[self view] setHidden:NO];
    
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    
    GETouchDispatcher::GetInstance()->setDispatchEvents(true);
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    [[ad.viewController view] setFrame:CGRectMake(0.0, 480.0, 320.0, 480.0)];
    [UIView setAnimationDelegate:self];
//    [UIView setAnimationDidStopSelector:@selector(backToRoomCallback)];
    [UIView commitAnimations];
}

@end
