//
//  MenuLayerMsg.m
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "MenuLayerMsg.h"
#import "AddonWrapper.h"
#import "GlobalData.h"
#import "cJSON.h"
#import "SimpleAudioEngineWrapper.h"

class MsgNetWrapper: public GELayer
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
        
        if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring, "SS_MSG")==0) {
            cJSON *result, *msg;
            result =cJSON_GetObjectItem(read, "result");
            msg = cJSON_GetObjectItem(result, "msg");
            g_message.count=cJSON_GetArraySize(msg);
            for (int i=0; i<g_message.count; i++) {
                snprintf(g_message.date[i], 256, "%s", cJSON_GetArrayItem(cJSON_GetArrayItem(msg, i), 0)->valuestring);
                snprintf(g_message.message[i], 256, "%s", cJSON_GetArrayItem(cJSON_GetArrayItem(msg, i), 1)->valuestring);
            }
            reloadMsgData();
            /*
            if (g_message.type==0) {
                delete m_PersonalNet;
            }
            else {
                delete m_SystemNet;
            }
            */
        }
    }
    
    void sendShortMsg(const char *msg, GENet *m_Net)
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
    
    void getMessage(int msgType)
    {
        memset(m_cNetRequest, 0, NET_CONNECT_BUFFER);
        sprintf(m_cNetRequest, "{\"cmd\":\"RS_MSG\", \"params\":{\"gameId\":1,\"userId\":%d,\"type\":%d},\"cmdId\":1}\r\n",g_user.uid, msgType);
        if (msgType==0) {
            g_message.type=0;
            sendShortMsg(m_cNetRequest,m_PersonalNet);
        }
        else {
            g_message.type=1;
            sendShortMsg(m_cNetRequest,m_SystemNet);
        }
        
    }
    
public:
    static MsgNetWrapper* m_pSelf;
    char   m_cNetRequest[NET_CONNECT_BUFFER];
    GENet  *m_PersonalNet;
    GENet  *m_SystemNet;
};
MsgNetWrapper* MsgNetWrapper::m_pSelf=0;

@implementation MenuLayerMsg
@synthesize personInfo;
@synthesize systemInfo;
@synthesize messageTableView;
//@synthesize m_personalInfoTable;
static MenuLayerMsg *menuLayerMsg = nil;

+(MenuLayerMsg *)sharedManager
{
    if (!menuLayerMsg) {
        menuLayerMsg = [[MenuLayerMsg alloc] init];
    }
    return menuLayerMsg;
}

-(void)getMessage:(int)msgType
{
     MsgNetWrapper::m_pSelf->getMessage(msgType);
}

-(void)initSelfView
{
    //初始化网络对象...
    MsgNetWrapper::m_pSelf = new MsgNetWrapper();
    MsgNetWrapper::m_pSelf->m_PersonalNet = GENet::netWithTarget(MsgNetWrapper::m_pSelf, net_selector(MsgNetWrapper::netShortCallBack));
    MsgNetWrapper::m_pSelf->m_SystemNet = GENet::netWithTarget(MsgNetWrapper::m_pSelf, net_selector(MsgNetWrapper::netShortCallBack));
    
    [[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    //设置标题显示文字
    [titleLable setFrame:CGRectMake(backButton.frame.origin.x+backButton.frame.size.width+5, 10, 100, 25)];
    [titleLable setText:@"个人动态栏"];
    [titleLable setFont:[UIFont fontWithName:@".HelvetiaNeueUI" size:25]];
    titleLable.backgroundColor = [UIColor clearColor];
    
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];
    
    personInfo = [[UIButton alloc] initWithFrame:CGRectMake(310.0, 7.5, 90, 40)];
    systemInfo = [[UIButton alloc] initWithFrame:CGRectMake(390, 7.5, 90, 40)];
    
    [personInfo.layer setBackgroundColor:[UIColor blueColor].CGColor];
    [personInfo setTitle:@"个人消息" forState:UIControlStateNormal];
    personInfo.backgroundColor = [UIColor clearColor];
    [personInfo.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [personInfo addTarget:self action:@selector(personInfoCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [systemInfo.layer setBackgroundColor:[UIColor blueColor].CGColor];
    systemInfo.backgroundColor = [UIColor clearColor];
    [systemInfo setTitle:@"系统消息" forState:UIControlStateNormal];
    [systemInfo.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [systemInfo addTarget:self action:@selector(systemInfoCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    //创建滑动阴影控件 
    /* 图片的大小为180x104，蓝色区域大小为173x64 */
    
    [self setSlideBlockFrame:CGRectMake(personInfo.frame.origin.x-2, personInfo.frame.origin.y-10, 90, 52)];
    [slideBlock setImage:[UIImage imageNamed:@"Store_arrow.png"]];
    
    //添加两个Button到这个View
    [[self view] addSubview:personInfo];
    [[self view] addSubview:systemInfo];
    
    [self makeTableView:CGRectMake(10, 50, 460, 260) style:UITableViewStylePlain];
    uiTableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;
    UIImageView *uiTableViewBkg=[[[UIImageView alloc]initWithFrame:CGRectMake(uiTableView.frame.origin.x, uiTableView.frame.origin.y, uiTableView.frame.size.width, uiTableView.frame.size.height)]autorelease];;
    uiTableViewBkg.image=[UIImage imageNamed:@"L2white.png"];
    [uiTableView setBackgroundView:uiTableViewBkg];
    /*
    messageTableView = [[UITableView alloc]initWithFrame:CGRectMake(10, 50, 460, 230)];
    [[self view]addSubview:messageTableView];
    messageTableView.backgroundColor = [UIColor clearColor];
    [messageTableView setDelegate:self];
    [messageTableView setDataSource:self];
    messageTableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;
     */
}

-(void)personInfoCallBack
{
    //MsgNetWrapper::m_pSelf->getMessage(0);
    [self getMessage:0];
    [self slideBlockOfButton:CGRectMake(personInfo.frame.origin.x-2, personInfo.frame.origin.y-10, 90, 52)];
}

-(void)systemInfoCallBack
{
    //MsgNetWrapper::m_pSelf->getMessage(1);
    [self getMessage:1];
    [self slideBlockOfButton:CGRectMake(systemInfo.frame.origin.x-2, systemInfo.frame.origin.y-10, 90, 52)];
}

-(void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    menuLayerMsgHide();
}

//Cell的高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 45;
}

//Cell的数量
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSLog(@"\n MenuLayerMsg =====g_message.count=%d=====\n\n",g_message.count);
    return g_message.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"\n MenuLayerMsg =====indexPath.row=%d=====\n",indexPath.row);
    static NSString *SimpleTableIdentifier = @"MenuLayerMsg";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) { 
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    UIImageView *head=[[[UIImageView alloc]initWithFrame:CGRectMake(5, 15, 12, 12)]autorelease];
    [head setImage:[UIImage imageNamed:@"MainMenu_message.png"]];
    [cell.contentView addSubview:head];
    
    UILabel *date=[[[UILabel alloc]initWithFrame:CGRectMake(head.frame.origin.x+head.frame.size.width+5, head.frame.origin.y, 108,12+5)]autorelease];
    [date setText:[NSString stringWithFormat:@"%s",g_message.date[indexPath.row]]];
    date.backgroundColor=[UIColor clearColor];
    [cell.contentView addSubview:date];
    
    UILabel *message=[[[UILabel alloc] initWithFrame:CGRectMake(date.frame.origin.x+date.frame.size.width+10, head.frame.origin.y, 320, 12+5)]autorelease];
    [message setText:[NSString stringWithFormat:@"-%@", [NSString stringWithUTF8String:g_message.message[indexPath.row]]]];
    message.textColor=[UIColor orangeColor];
    message.backgroundColor=[UIColor clearColor];
    [cell.contentView addSubview:message];
    
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
