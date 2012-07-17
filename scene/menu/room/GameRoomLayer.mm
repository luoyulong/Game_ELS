//
//  MenuLayerNormalRoom.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GameRoomLayer.h"
#import "gameNetCenter.h"
#import "AppDelegate.h"
#import "GlobalData.h"
#import "GameStateWaiting.h"

@implementation GameRoomLayer

- (void)initSelfView
{
    ignoreBackbuttonClick = NO;
    sortFocusOn = 0;
    preSortFocusOn = -1; //-1代表刚进入界面
    
    sortButtonArray = [[NSMutableArray alloc] initWithObjects:nil];
    buttonTriangleArray = [[NSMutableArray alloc] initWithObjects:nil];
    
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    
    //显示个人信息
    userInfoView = [[[UITableView alloc] initWithFrame:CGRectMake(56.0, 10.0, 150.0, 32.0)] autorelease];
    [userInfoView setBackgroundColor:[UIColor clearColor]];
    [[self view] addSubview:userInfoView];
    UIImageView *coinImageView = [[[UIImageView alloc] initWithFrame:CGRectMake(1.0, 15.0, 10.0, 10.0)] autorelease];
//    [coinImageView setImage:[UIImage imageNamed:@""]];
    [coinImageView setBackgroundColor:[UIColor redColor]];
    [userInfoView addSubview:coinImageView];
    [self addLableView:&nickLable cgrect:CGRectMake(0.0, 0.0, 200.0, 11.0) fontSize:11.0 addToView:userInfoView];
    [self addLableView:&coinLable cgrect:CGRectMake(12.0, 15.0, 66.0, 11.0) fontSize:11.0 addToView:userInfoView];
    
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    
    //刷新按钮
    refreshButton = [[UIButton alloc] init];
    [self makeButton:refreshButton rect:CGRectMake(450.0, 12.5, 16.0, 20.0)];
    [refreshButton setBackgroundImage:[UIImage imageNamed:@"refresh.png"] forState:UIControlStateNormal];
    [refreshButton addTarget:self action:@selector(refreshButtonCallback) forControlEvents:UIControlEventTouchUpInside];
    
    //tableView背景设置
//    tableImageView = [[UIImageView alloc] init:CGRectMake(7.0, 42, 466.0, 238)];
    tableImageView = [[[UIImageView alloc] init] autorelease];
    [tableImageView setBackgroundColor:[UIColor clearColor]];
//    [tableImageView setImage:[UIImage imageNamed:@"Roomlist_backgroundBox_game.png"]];
    [[self view] addSubview:tableImageView];
    
    [self initSelfRoom];
    
    [self setSortButtonTitle];
}

- (void)sortTableList
{
}

- (void)initSelfRoom
{
}

- (void)addSortButton:(UIButton **)button frame:(CGRect)cgrect title:(NSString *)buttonTitle callback:(SEL)funcallback
{
    *button = [[[UIButton alloc] init] autorelease];
    [self makeButton:*button rect:cgrect];
    [*button setTitle:buttonTitle forState:UIControlStateNormal];
    [(*button).titleLabel setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:11]];
    [*button addTarget:self action:funcallback forControlEvents:UIControlEventTouchUpInside];
    
    [sortButtonArray addObject:*button];
}


- (void)addNavigationButton:(UIButton **)button frame:(CGRect)cgrect title:(NSString *)buttonTitle callback:(SEL)funcallback;
{
    *button = [[[UIButton alloc] initWithFrame:cgrect] autorelease];
    [self makeButton:*button rect:cgrect];
    
    [*button setTitle:buttonTitle forState:UIControlStateNormal];
    [(*button).titleLabel setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:13]];
    [*button setBackgroundImage:[UIImage imageNamed:@"Roomlist_roomTypeSelectedHeight.png"] forState:UIControlStateHighlighted];
    [*button addTarget:self action:funcallback forControlEvents:UIControlEventTouchUpInside];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return table_list.size();
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 41;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    ignoreBackbuttonClick = YES;
//    NSLog(@"进入桌子请求: 桌号 %d  密码 %s", table_list[indexPath.row]->tid, table_list[indexPath.row]->pwd);
    gameNetCenter::GetInstance()->enterTable(table_list[indexPath.row]->tid, table_list[indexPath.row]->pwd);
    
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[ad.viewController view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    
    GEDirector::GetInstance()->setCurrentScene("GameStateWaiting");
    if (g_roomId >= 1 && g_roomId <= 4)
    {
        GameStateWaiting::GetInstance()->SetWaitType(3);
    } 
    else if (g_roomId == 5) {
        GameStateWaiting::GetInstance()->SetWaitType(4);
    }
    
    [[self view] setHidden:YES];
}

- (void)addLableView:(UILabel **)lable cgrect:(CGRect)cgrect fontSize:(NSInteger)fontSize addToView:(UIView *)uiView
{
    *lable = [[[UILabel alloc]initWithFrame:cgrect] autorelease];
    [*lable setTextColor:[UIColor whiteColor]];
    [*lable setBackgroundColor:[UIColor clearColor]];
    [*lable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:fontSize]];
    [uiView addSubview:*lable];
}

- (void)refreshTableView
{
    [self sortTableList];
    [aWaitnet stopAnimating];
}

- (void)reloadTableViewData
{
    [uiTableView reloadData];
}

- (void)reloadUserInfo
{
    ignoreBackbuttonClick = NO;
    
    [nickLable setText:[NSString stringWithUTF8String:g_user.name]];
    [coinLable setText:[NSString stringWithFormat:@"%d", g_user.coin]];
}

- (void)addButtonTriangleView:(UIImageView **)imageView cgrect:(CGRect)cgrect imageName:(NSString *)imageName
{
    *imageView = [[[UIImageView alloc] initWithFrame:cgrect] autorelease];
    [*imageView setHidden:YES];
    [*imageView setImage:[UIImage imageNamed:imageName]];
    [buttonTriangleArray addObject:*imageView];
    [[self view] addSubview:*imageView];
}

- (void)rotateButtonTriangleView:(UIImageView *)imageView angle:(CGFloat)angle
{
    CGAffineTransform transform = CGAffineTransformMakeRotation(angle);
    [imageView setTransform:transform];
}

- (void)doSortTableList:(NSInteger)_sortFocusOn sortStyle:(bool *)sortStyle
{
    preSortFocusOn = sortFocusOn;
    sortFocusOn = _sortFocusOn;
    
    [self setSortButtonTitle];
    
    if (preSortFocusOn == sortFocusOn)
    {
        *sortStyle = !(*sortStyle);
    }
    
    [self sortTableList];
}

- (void)setSortButtonTitle
{
    if (preSortFocusOn == -1)
    {
        UIButton *button;
        for (button in sortButtonArray) {
            [button setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
        }
        
        UIImageView *tringleImageView;
        for (tringleImageView in buttonTriangleArray) {
            [tringleImageView setHidden:YES];
        }
    }
    else {
        
        if (preSortFocusOn < [sortButtonArray count]) {
            [[sortButtonArray objectAtIndex:preSortFocusOn] setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
            [[buttonTriangleArray objectAtIndex:preSortFocusOn] setHidden:YES];
        }
        
        if (sortFocusOn < [sortButtonArray count]) {
            [[sortButtonArray objectAtIndex:sortFocusOn] setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [[buttonTriangleArray objectAtIndex:sortFocusOn] setHidden:NO];
        }
    }
}

- (void)addPlayers:(NSInteger)rowIndex frameOriginX:(CGFloat)originX frameOriginY:(CGFloat)originY addToCell:(UITableViewCell *)cell
{
    NSInteger currentSeatCount = table_list[rowIndex]->currentSeat;
    NSInteger playSeatCount = table_list[rowIndex]->playSeat;
    for (NSInteger i=0; i<6; i++) {
        UIImageView *currentSeatImage = [[UIImageView alloc] initWithFrame:CGRectMake(originX+12*i, originY, 10, 10)];
        
        if (i < playSeatCount) {
//            [currentSeatImage setImage:[UIImage imageNamed:@""]];
            [currentSeatImage setBackgroundColor:[UIColor redColor]];
        } else if (i >= playSeatCount && i < currentSeatCount) {
            [currentSeatImage setBackgroundColor:[UIColor orangeColor]];
        } else if (i >= currentSeatCount) {
//            [currentSeatImage setImage:[UIImage imageNamed:@""]];
            [currentSeatImage setBackgroundColor:[UIColor blueColor]];
        }
        
        [cell.contentView addSubview:currentSeatImage];
    }
}

- (void)refreshButtonCallback
{
    table_list.clear();
    [uiTableView reloadData];
    [self startAWaitnet];
    gameNetCenter::GetInstance()->refreshRoom();
}

//- (void)backToRoomCallback
//{
//    printf("取消的房间号 %d\n", g_roomId);
//    GEDirector::GetInstance()->gotoScene("GameStateWaiting", MoveShowInstant);
//    if (g_roomId >= 1 && g_roomId <= 4) {
//        GameStateWaiting::GetInstance()->SetWaitType(3);
//    } else if (g_roomId == 5) {
//        GameStateWaiting::GetInstance()->SetWaitType(4);
//    }
//}

//- (void)viewMoveToLeftCallback
//{
//    GEDirector::GetInstance()->gotoScene("GameStateWaiting", MoveShowInstant);
//    if (g_roomId >= 1 && g_roomId <= 4)
//    {
//        GameStateWaiting::GetInstance()->SetWaitType(3);
//    } 
//    else if (g_roomId == 5) {
//        GameStateWaiting::GetInstance()->SetWaitType(4);
//    }
//}

@end
