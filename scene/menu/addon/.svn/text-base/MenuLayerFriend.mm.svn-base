//
//  MenuLayerFriend.m
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "MenuLayerFriend.h"
#import "AddonWrapper.h"
#import "GlobalData.h"
#import "gameNetCenter.h"
#import "SimpleAudioEngineWrapper.h"

class FriendNetWrapper: public GELayer
{
public:
    void netShortCallBack(const char *msg) {
        cJSON *read;
        read=cJSON_Parse(msg);
        printf("server back msg!!\n%s", cJSON_Print(read));
        if(read == 0)
        {
            printf("json format error!!\n");
            return;
        }
        if (cJSON_GetObjectItem(read, "cmd")==NULL) {
            //信息错误
            printf("no cmd.\n");
            return;
        }
        
        //好友信息
        if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring, "SS_FRIENDS")==0) {
            if (g_friend_list.size()>0) {
                for (int i=0; i<g_friend_list.size(); i++) {
                    free(g_friend_list.at(i));
                }
            }
            g_friend_list.clear();
            
            cJSON *result, *friends;
            result = cJSON_GetObjectItem(read, "result");
            friends = cJSON_GetObjectItem(result, "friends");
            
            cJSON *c=friends->child;
            while (c) {
                USER_INFO *userInfo=(USER_INFO*)malloc(sizeof(USER_INFO));
                userInfo->uid = atoi(c->string);
                cJSON *friendlist=cJSON_GetObjectItem(friends, c->string);
                
                strcpy(userInfo->name, cJSON_GetArrayItem(friendlist, 0)->valuestring);
                snprintf(userInfo->picture_url, 256, "%s",cJSON_GetArrayItem(friendlist, 1)->valuestring);
                userInfo->coin=cJSON_GetArrayItem(friendlist, 2)->valueint;
                userInfo->level=cJSON_GetArrayItem(friendlist, 3)->valueint;
                
                //winrate[2]
                char *strStart = cJSON_GetArrayItem(friendlist, 4)->valuestring;
                char *pos = strchr(cJSON_GetArrayItem(friendlist, 4)->valuestring, ',');
                *pos='\0';
                userInfo->winrate[0]=atoi(strStart);
                userInfo->winrate[1]=atoi(pos+1);
                
                //location[4]
                strStart=cJSON_GetArrayItem(friendlist, 5)->valuestring;
                
                if (strcmp(strStart,"offline")==0) {//offline时location各项都置为0
                    for (int i=0; i<4; i++) {
                        userInfo->location[i]=0;
                    }
                }
                else {                              //不为offline时
                    for (int i=0; i<4; i++) {
                        pos=strchr(strStart, '.');
                        if (pos != NULL) {
                            *pos='\0';
                            userInfo->location[i]=atoi(strStart);
                            strStart=pos+1;
                        }
                        else{
                            userInfo->location[i]=atoi(strStart);
                        }
                    }
                }
                
                g_friend_list.push_back(userInfo);
                c=c->next;
            }
            reloadFriendData();
            printf("=============== g_friend_list size=%lu=================\n",g_friend_list.size());
        }
    }
    
    void sendShortMsg(const char *msg)
    {
        cJSON *read;
        read=cJSON_Parse(msg);
        if (read==0) {
            printf("sendMsg, json data format error!\n");
        }
        else {
            m_Net->setMsg(msg);
            m_Net->reqConn(SERVERIP, SHORTPORT, NULL);
        }
    }
    
    void getFriends()
    {
        memset(m_cNetRequest, 0, NET_CONNECT_BUFFER);
        sprintf(m_cNetRequest, "{\"cmd\":\"RS_FRIENDS\", \"params\":{ \"gameId\":1,\"userId\":%d},\"cmdId\":1}\r\n",g_user.uid);
        sendShortMsg(m_cNetRequest);
    }
    
public:
    static FriendNetWrapper* m_pSelf;
    char   m_cNetRequest[NET_CONNECT_BUFFER];
    GENet  *m_Net;
};
FriendNetWrapper* FriendNetWrapper::m_pSelf=0;

@implementation MenuLayerFriend

@synthesize m_backGroundView;
@synthesize friendList;
@synthesize showDetail;

@synthesize centerShadowLine;
@synthesize centerArrow;
//朋友列表组件
@synthesize littleHead;
@synthesize sex;
@synthesize nickName;
@synthesize stateIndicator;
@synthesize rowBackground;
//详细信息组件
@synthesize bigHead;
@synthesize personalInfo;
@synthesize location;
@synthesize deleteFriend;
@synthesize indexSelected;

@synthesize deleteFriendAlert;

static MenuLayerFriend *menuLayerFriend = nil;
+ (MenuLayerFriend *)sharedManager
{
    if (!menuLayerFriend) {
        menuLayerFriend = [[MenuLayerFriend alloc] init];
    }
    
    return menuLayerFriend;
}

- (void)getFriends{
    FriendNetWrapper::m_pSelf->getFriends();
}
- (void)initSelfView
{
    //初始化网络对象...
    FriendNetWrapper::m_pSelf = new FriendNetWrapper();
    FriendNetWrapper::m_pSelf->m_Net = GENet::netWithTarget(FriendNetWrapper::m_pSelf, net_selector(FriendNetWrapper::netShortCallBack));
    
    indexSelected = -1;
    [[self view] setFrame:CGRectMake(-320, 0, 320.0, 480.0)];
    //整个背景
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]]; 
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    //设置标题显示文字
    [titleLable setFrame:CGRectMake(202.5, 10, 100, 25)];
    [titleLable setText:@"我的好友"];
    titleLable.backgroundColor = [UIColor clearColor];
    [titleLable setFont:[UIFont fontWithName:@".HelvetiaNeueUI" size:25]];
    
    m_backGroundView = [[UIImageView alloc]initWithFrame:CGRectMake((480-924/2)/2, 50, 924/2, 532/2)];
    [m_backGroundView setImage:[UIImage imageNamed:@"FriendsCenter_back@2x.png"]];
    [[self view]addSubview:m_backGroundView];
    
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];
    
    //左侧表 24/2为FriendCenter_arrow右侧的灰色区域像素值
    [self makeTableView:CGRectMake(m_backGroundView.frame.origin.x, m_backGroundView.frame.origin.y, 492/2, 532/2) style:UITableViewStylePlain];
    //uiTableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;

    //[self makeTableView:CGRectMake((480-924/2)/2, 50, 490/2, 532/2) style:UITableViewStylePlain];
    [[self view] addSubview:uiTableView];
    //右侧个人信息
    showDetail = [[UIView alloc] initWithFrame:CGRectMake(uiTableView.frame.size.width, 50, 434/2-24/2, 532/2)];
    showDetail.backgroundColor = [UIColor clearColor];
    [[self view] addSubview:showDetail];
    
    centerShadowLine = [[UIImageView alloc]initWithFrame:CGRectMake(uiTableView.frame.origin.x+uiTableView.frame.size.width, uiTableView.frame.origin.y, 8, 532/2)];
    [centerShadowLine setImage:[UIImage imageNamed:@"FriendsCenter_shadow@2x.png"]];
    [[self view] addSubview:centerShadowLine];    
}

//Cell的高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 48;//对应center_arrow的高度
}

//Cell的数量
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    //NSLog(@"****************numberOfRows=%lu*******************\n",g_friend_list.size());
    //[uiTableView reloadData];
    return g_friend_list.size();
}

//选择某列时的动作
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

    indexSelected = indexPath.row;
    [uiTableView reloadData];
    NSLog(@"didSelectRowAtIndexPath indexPath.row = %d, indexSelected=%d", indexPath.row, indexSelected);
    for (UIView *view in showDetail.subviews) {
        [view removeFromSuperview];
    }
    
    bigHead = [[UIImageView alloc] initWithFrame:CGRectMake((showDetail.frame.size.width-80)/2, 20, 80, 80)];
    [bigHead setImage:[UIImage imageNamed:@"roboticon14_info.png"]];
    [showDetail addSubview:bigHead];
    
    //个人信息
    personalInfo = [[UITextView alloc] initWithFrame:CGRectMake(bigHead.frame.origin.x, bigHead.frame.origin.y + bigHead.frame.size.height +5, 80, 60)];
    
    float winrate;
    if (g_friend_list[indexPath.row]->winrate[0]+g_friend_list[indexPath.row]->winrate[1] == 0) {
        winrate = 0.0;
    }
    else {
        winrate = g_friend_list[indexPath.row]->winrate[0]/(g_friend_list[indexPath.row]->winrate[0]+g_friend_list[indexPath.row]->winrate[1]);
    }
    [personalInfo setText:[NSString stringWithFormat:@"金币: $%d\n等级: %d\n牌局数: %d\n胜率: %d\%\n", 
                           g_friend_list[indexPath.row]->coin, 
                           g_friend_list[indexPath.row]->level, 
                           g_friend_list[indexPath.row]->winrate[0]+g_friend_list[indexPath.row]->winrate[1], 
                           winrate*100]];
    
    //[personalInfo setText:@"筹码: $128\n等级:上等兵\n牌局数:1266\n胜率:23%\n"];
    personalInfo.editable = NO;
    personalInfo.backgroundColor=[UIColor clearColor];
    
     //位置信息
    location = [[UIButton alloc] initWithFrame:CGRectMake(personalInfo.frame.origin.x, personalInfo.frame.origin.y+personalInfo.frame.size.height +10, personalInfo.frame.size.width, 30)];
    
    NSString *messgae=nil;
    NSLog(@"location[0]=%d, location[1]=%d, location[2]=%d, location[3]=%d\n", g_friend_list[indexPath.row]->location[0], g_friend_list[indexPath.row]->location[1],g_friend_list[indexPath.row]->location[2],g_friend_list[indexPath.row]->location[3]);
    if (g_friend_list[indexPath.row]->location[0] == 0) {//offline
        messgae = @"离线";
    }
    else if (g_friend_list[indexPath.row]->location[1]==0) {//在大厅
        messgae = @"大厅";
    }
    else if (g_friend_list[indexPath.row]->location[1]==1) {
        messgae = [NSString stringWithFormat:@"新手场:%d",g_friend_list[indexPath.row]->location[2]];
    } 
    else if (g_friend_list[indexPath.row]->location[1]==2) {
        messgae = [NSString stringWithFormat:@"初级场:%d",g_friend_list[indexPath.row]->location[2]];
    }
    else if (g_friend_list[indexPath.row]->location[1]==3) {
        messgae = [NSString stringWithFormat:@"中级场:%d",g_friend_list[indexPath.row]->location[2]];
    }
    else if (g_friend_list[indexPath.row]->location[1]==4) {
        messgae = [NSString stringWithFormat:@"高级场:%d",g_friend_list[indexPath.row]->location[2]];
    }
    else if (g_friend_list[indexPath.row]->location[1]==5) {
        messgae = [NSString stringWithFormat:@"比赛场:%d",g_friend_list[indexPath.row]->location[2]];
    }
    
    [location setTitle:messgae forState:UIControlStateNormal];
    //[location setFont:[UIFont fontWithName:@"Courier" size:15]];
    [location setBackgroundImage:[UIImage imageNamed:@"FriendsCenter_btn1@2x.png"] forState:UIControlStateNormal];
    [location addTarget:self action:@selector(locationCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    //Test
    //[location setTitle:@"离线" forState:UIControlStateNormal];
    //[location addTarget:self action:@selector(locationCallBack) forControlEvents:UIControlEventTouchUpInside];

    //删除好友
    deleteFriend = [[[UIButton alloc] initWithFrame:CGRectMake(location.frame.origin.x, location.frame.origin.y+location.frame.size.height+10, location.frame.size.width, location.frame.size.height)] autorelease];
    [deleteFriend setTitle:@"删除好友" forState:UIControlStateNormal];
    [deleteFriend setBackgroundImage:[UIImage imageNamed:@"deleteFriend.png"] forState:UIControlStateNormal];
    [deleteFriend addTarget:self action:@selector(deleteCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [showDetail addSubview:bigHead];
    [showDetail addSubview:personalInfo];
    [showDetail addSubview:location];
    [showDetail addSubview:deleteFriend];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSLog(@"=======indecPath.row=%d, indexSelected=%d =========\n", indexPath.row, indexSelected);//indexPath.row 是从0开始
    static NSString *SimpleTableIdentifier = @"FriendListIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) { 
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;//被选中后的颜色
    //cell.selectedBackgroundView=[[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"FriendsCenter_CellBack_Backup.png"]]autorelease];
    
    
    if (indexSelected == indexPath.row) {
        cell.backgroundView=[[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"FriendsCenter_CellBack_Backup.png"]]autorelease];
        //cell.imageView.image=[UIImage imageNamed:@"FriendsCenter_CellBack_Backup.png"];
    }
    else {
        [cell.backgroundView removeFromSuperview];
        //cell.backgroundColor=[UIColor redColor];
        if (indexPath.row==0) {
            cell.backgroundView=[[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"settingroundbtn1@2x.png"]]autorelease];
        }
        else if (indexPath.row==g_friend_list.size()) {
            cell.backgroundView=[[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"settingroundbtn2@2x.png"]]autorelease];
        }
        else{
            cell.backgroundView=[[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"settingroundbtn3@2x.png"]]autorelease];
        }
    }
    
    if (g_friend_list.size()==0) {
        
        UILabel *noFriend = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, uiTableView.frame.size.width, uiTableView.frame.size.width)] autorelease];
        noFriend.text = @"暂时没有好友";
        noFriend.textAlignment=UITextAlignmentCenter;
        [uiTableView addSubview:noFriend];
        
        UIImageView *noFriendView = [[[UIImageView alloc] initWithFrame:CGRectMake((showDetail.frame.size.width-116)/2, (showDetail.frame.size.height-124)/2, 116, 124)]autorelease];
        [noFriendView setImage:[UIImage imageNamed:@"FriendsCenter_noFriends.png"]];
        [showDetail addSubview:noFriendView];
    }
    else 
    {
        //[noFriend removeFromSuperview];
        //[noFriendView removeFromSuperview];
        NSLog(@"====removeFromSuperView noFriend, noFriendView====\n");
        //小头像
        littleHead = [[[UIImageView alloc]initWithFrame:CGRectMake(0, (cell.frame.size.height-32)/2, 32, 32)] autorelease];
        [littleHead setImage:[UIImage imageNamed:@"roboticon14_info.png"]];
        [cell.contentView addSubview:littleHead];
        
        //性别
        sex = [[[UIImageView alloc]initWithFrame:CGRectMake(littleHead.frame.origin.x +littleHead.frame.size.width+5, (cell.frame.size.height-16)/2, 16, 16)] autorelease];
        /*
        //暂时没有性别信息
        if (g_friend_list[indexPath.row]->sex == 0) {
            [sex setImage:[UIImage imageNamed:@"male_big.png"]];
        }
        else {
            [sex setImage:[UIImage imageNamed:@"female_big.png"]];
        }
        */ 
        [sex setImage:[UIImage imageNamed:@"male_big.png"]];
        [cell.contentView addSubview:sex];
        
        //昵称
        nickName = [[[UILabel alloc]initWithFrame:CGRectMake(sex.frame.origin.x + sex.frame.size.width+5, 0, 120, 48)] autorelease];
        [nickName setText:[NSString stringWithFormat:@"%s", g_friend_list[indexPath.row]->name]];
        //[nickName setText:@"听雨观风闻雪"];
        nickName.font = [UIFont fontWithName:@".HelvetiaNeueUI" size:8];
        nickName.backgroundColor = [UIColor clearColor];
        [cell.contentView addSubview:nickName];
        
        //状态指示
        stateIndicator = [[UIImageView alloc] initWithFrame:CGRectMake(nickName.frame.origin.x + nickName.frame.size.width+5, 22, 4, 4)];
        if (g_friend_list.at(indexPath.row)->location[0]!=0) {
            [stateIndicator setImage:[UIImage imageNamed:@"FriendsCenter_point.png"]];
        }
        
        [cell.contentView addSubview:stateIndicator];
        
        //中间箭头
        //其中center_arrow的蓝色区域为44/2像素
        /*
        centerArrow = [[UIImageView alloc]initWithFrame:CGRectMake(cell.frame.origin.x+cell.frame.size.width-23, 1, 34, 48)];
        //centerArrow = [[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 34, 48)];
        [centerArrow setImage:[UIImage imageNamed:@"FriendsCenter_arrow.png"]];
        NSLog(@"centerArrow.x = %f, centerArrow.y = %f",centerArrow.frame.origin.x, centerArrow.frame.origin.y);
        if (indexSelected == indexPath.row) {
            [cell.contentView addSubview:centerArrow];
            NSLog(@"indexSelected == indexPath.row2\n");
        }
        */
    }
    
    NSLog(@"====Cell Render====\n ");
    return cell;
}
- (void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    menuLayerFriendsHide();
}

- (void)locationCallBack
{
    //gameNetCenter::GetInstance()->autoEnterTable=TRUE;
    //gameNetCenter::GetInstance()->autoEnterTableId=g_friend_list[indexSelected]->location[2];
    //gameNetCenter::GetInstance()->enterRoom(g_friend_list[indexSelected]->location[1]);
    gameNetCenter::GetInstance()->quickStart(g_friend_list[indexSelected]->location[1], 
                                             g_friend_list[indexSelected]->location[2], false);
    menuLayerFriendsHide();
}

- (void)deleteCallBack
{
    deleteFriendAlert = [[UIAlertView alloc] initWithTitle: nil message:@"确认删除好友？" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"确定", nil];
    [deleteFriendAlert show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == deleteFriendAlert.cancelButtonIndex) {
        deleteFriendAlert.hidden = NO;
    }
    else if (buttonIndex == deleteFriendAlert.firstOtherButtonIndex){
        deleteFriendAlert.hidden = YES;
        //向服务器发送删除好友消息
    }
}

- (void)reloadData
{
    [uiTableView reloadData];
}
@end
