//
//  CommonLayerClass.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MenuLayerMedal.h"
#import "GlobalData.h"
#import "dataDefine.h"
#import "ImageCache.h"
#import "SimpleAudioEngineWrapper.h"

class MedalNetWrapper: public GELayer
{
public:
    GENet *mNet;
    
    //获取medal列表
    void getMedals()
    {
        char msgbuf[1024];
        sprintf(msgbuf, "{\"cmd\":\"RS_MEDAL\", \"params\":{\"gameId\":1,\"userId\":%d},\"cmdId\":1}\r\n",g_user.uid);
        mNet->setMsg(msgbuf);
        mNet->reqConn(SERVERIP, SHORTPORT, NULL);
    }    
    //请求medal奖励
    void getMedalRewards(int medalid)
    {
        char msgbuf[1024];
        sprintf(msgbuf, "{\"cmd\":\"RS_MEDAL_REWARD\", \"params\":{\"gameId\":1,\"userId\":%d,\"medalId\":%d},\"cmdId\":1}\r\n",g_user.uid,medalid);
        mNet->setMsg(msgbuf);
        mNet->reqConn(SERVERIP, SHORTPORT, NULL);
    }
    //服务器返回信息处理函数
    void netShortCallBack(const char* msg)
    {    
        cJSON *read;
        read=cJSON_Parse(msg);
        printf("server back msg!!\n%s", cJSON_Print(read));
        if(read == 0)
        {
            printf("json format error!!\n");
            return;
        }
        if (cJSON_GetObjectItem(read, "cmd")==NULL) {
            printf("no cmd.\n");
            return;
        }
        //处理medal列表
        if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring, "SS_MEDAL")==0) {
            cJSON *result, *medals;
            result =cJSON_GetObjectItem(read, "result");
            medals = cJSON_GetObjectItem(result, "medal");
            g_rewardInfo.count=cJSON_GetArraySize(medals);
            for (int i=0; i<g_rewardInfo.count; i++) {
                g_rewardInfo.medalId[i]=cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 0)->valueint;
                snprintf(g_rewardInfo.picture_url[i], 256, "%s", cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 1)->valuestring);
                snprintf(g_rewardInfo.name[i], 256, "%s", cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 2)->valuestring);
                snprintf(g_rewardInfo.desc[i], 256, "%s", cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 3)->valuestring);
                
                g_rewardInfo.reward[i]=cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 4)->valueint;
                g_rewardInfo.finish[i]=cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 5)->valueint;
                g_rewardInfo.total[i]=cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 6)->valueint;
                g_rewardInfo.state[i]=cJSON_GetArrayItem(cJSON_GetArrayItem(medals, i), 7)->valueint;
                //g_rewardInfo.state[i]=0;//测试代码，为了测试点击领取奖励后的效果
            }
            [[MenuLayerMedal sharedManager] reloadData];
        }        
        //点击领取成就奖励
        if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring, "SS_MEDAL_REWARD")==0) {
            cJSON *error, *result, *rewards, *coins,*isMedalIds, *info;
            result =cJSON_GetObjectItem(read, "result");
            
            
            //测试代码
            if (!result)
            {
                
                error = cJSON_GetObjectItem(read, "error");
                if (error) 
                {
                    info=cJSON_GetObjectItem(error, "info");
                    if(info) 
                    {
                        printf("GET MEDAL REWARD error is %s\n", info->valuestring);
                    }
                }               
                if (g_isReward.isMedalId==11) 
                {
                     g_rewardInfo.state[10]=1;
                     //g_isReward.isMedalId=0;
                }
                if (g_isReward.isMedalId==1) 
               {
                    g_rewardInfo.state[0]=1;
                    //g_isReward.isMedalId=10;
               }
                
                [[MenuLayerMedal sharedManager] reloadData];                
                return;
            }

            
            rewards = cJSON_GetObjectItem(result, "reward");
            coins   =cJSON_GetObjectItem(result, "coin");
            isMedalIds=cJSON_GetObjectItem(result, "medalId");
            
            g_isReward.reward = rewards->valueint;    
            g_isReward.isMedalId=isMedalIds->valueint;
            g_isReward.coin=coins->valueint;
            g_user.coin=g_isReward.coin;
            
           
            //g_rewardInfo.state[g_isReward.isMedalId-1]=1;//确认返回SS_MEDAL后，将state设置为1
            [[MenuLayerMedal sharedManager] sendGetMedal];
           
            [[MenuLayerMedal sharedManager] viewWillAppear];
            [[MenuLayerMedal sharedManager] reloadData]; 
        } 
    }
    static MedalNetWrapper* m_pSelf;
};
MedalNetWrapper* MedalNetWrapper::m_pSelf=0;

@implementation MenuLayerMedal
static MenuLayerMedal *menuLayerMedal = nil;

+ (MenuLayerMedal *) sharedManager
{
    if(!menuLayerMedal)
        menuLayerMedal=[[MenuLayerMedal alloc] init];
    return menuLayerMedal;
}
//发送获取成就列表信息
- (void)sendGetMedal
{
    MedalNetWrapper::m_pSelf->getMedals();
}

- (void)initSelfView
{
    MedalNetWrapper::m_pSelf = new MedalNetWrapper();
    MedalNetWrapper::m_pSelf->mNet = GENet::netWithTarget(MedalNetWrapper::m_pSelf, net_selector(MedalNetWrapper::netShortCallBack));
    //任务中心初始化
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    //刷新按钮
    refreshButton=[[UIButton alloc] init];
    [refreshButton setFrame:CGRectMake(440, 10, 25, 25)];
    [refreshButton setBackgroundImage:[UIImage imageNamed:@"refresh.png"] forState:UIControlStateNormal];
    refreshButton.backgroundColor=[UIColor clearColor];
    [refreshButton addTarget:self action:@selector(refresh) forControlEvents:UIControlEventTouchUpInside];
    [[self view] addSubview:refreshButton];
    
    //任务中心背景图
    [backgroundView setImage:[UIImage imageNamed:@"L2back.jpg"]];    
    //后退按钮
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    //任务中心标题
    [titleLable setFrame:CGRectMake(180, 10, 200, 25)];
    [titleLable setText:@"任务中心"];
    [titleLable setBackgroundColor:[UIColor clearColor]];
    [titleLable setTextColor:[UIColor whiteColor]];
    [titleLable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:25]];  
    //任务中心UITableView
    [self makeTableView:CGRectMake(10, 50, 460, 260) style:UITableViewStylePlain];
    uiTableView.separatorStyle=UITableViewCellSeparatorStyleSingleLine;//cell是单行
    [uiTableView setBackgroundColor:[UIColor clearColor]];
    //任务中心UITableView的白背景
    UIImageView *uiTableViewBkg=[[[UIImageView alloc]initWithFrame:CGRectMake(uiTableView.frame.origin.x, uiTableView.frame.origin.y, uiTableView.frame.size.width, uiTableView.frame.size.height)] autorelease];
    uiTableViewBkg.image=[UIImage imageNamed:@"L2white.png"];
    [uiTableView setBackgroundView:uiTableViewBkg];   
}
//回退上一层界面
- (void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    [[MenuLayerMedal sharedManager] viewMoveToRight:SINGLE_LAYER_MOVE otherView:nil];
}

- (void)showPlayTableButtonCallBack
{
    
}

- (void)hiddenPlayTbleButtonCallBack
{
    
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];//选中后的反显颜色即刻消失
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    //NSLog(@"=====g_rewardInfo.count=%d=======", g_rewardInfo.count);
    return g_rewardInfo.count;    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView 
{
     return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 45;     
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    //NSLog(@"\n MenuLayerClass =====indexPath.row=%d=====\n",indexPath.row);
    static NSString *SimpleTableIdentifier = @"SimpleTableIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    //任务图标missionPic
    UIImageView *missionPic = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 45, 45)]autorelease];
    //[missionPic setImage:[UIImage imageNamed:@"vip_chip.png"]];
    missionPic.backgroundColor=[UIColor clearColor];
   
    //http://i0.sinaimg.cn/ent/402/2009/0701/U2398P28T402D1F12485DT20120525111419.jpg
    
    ImageCache *imgcache=[[[ImageCache alloc] init] autorelease];    
    [imgcache getImageByUrl:@"http://theocacao.com/images/content/000555-nanolife.png"
           defaultImageName:@"medalPic1.jpg" 
                  imageView:missionPic];
    [cell.contentView addSubview:missionPic];
    //[imgcache release];
    //http://theocacao.com/images/content/000555-nanolife.png
     

    
   
    
    //missionNameLabel:任务名称    
    UILabel *missionNameLabel=[[[UILabel alloc] initWithFrame:CGRectMake(missionPic.frame.origin.x+missionPic.frame.size.width+5, 0, 120, 15)]autorelease];    
    missionNameLabel.backgroundColor=[UIColor clearColor];
    missionNameLabel.text=[NSString stringWithUTF8String:g_rewardInfo.name[indexPath.row]];
    missionNameLabel.textAlignment=UITextAlignmentLeft;
    missionNameLabel.font=[UIFont fontWithName:@"Helvetica" size:12];
    [cell.contentView addSubview:missionNameLabel];
    //missionDescLabel:任务描述
    UILabel *missionDescLabel=[[[UILabel alloc]initWithFrame:CGRectMake(missionNameLabel.frame.origin.x, missionNameLabel.frame.origin.y+missionNameLabel.frame.size.height, 120, 25)]autorelease];
    missionDescLabel.backgroundColor=[UIColor clearColor];   
    missionDescLabel.text=[NSString stringWithUTF8String:g_rewardInfo.desc[indexPath.row]];
    missionDescLabel.textAlignment=UITextAlignmentLeft;
    missionDescLabel.font=[UIFont fontWithName:@"Helvetica" size:18];
    [cell.contentView addSubview:missionDescLabel];
    //奖励游戏币数量
    UILabel *price=[[[UILabel alloc]initWithFrame:CGRectMake(270, 0, 80, 45)]autorelease];
    price.backgroundColor=[UIColor clearColor];
    //price.text=[NSString stringWithUTF8String:g_coin_store.price[indexPath.row]];
    price.text=[NSString stringWithFormat:@"%d",(g_rewardInfo.reward[indexPath.row])];
    price.textAlignment=UITextAlignmentLeft;
    //price.textColor=[UIColor colorWithRed:244 green:164 blue:96 alpha:0.8];
    price.font=[UIFont fontWithName:@"Helvetica" size:14];
    [cell.contentView addSubview:price];
    
    //任务进行状态
    UILabel *missionFinish=[[[UILabel alloc] initWithFrame:CGRectMake(missionPic.frame.origin.x+missionPic.frame.size.width+350, 25, 120, 15)]autorelease]; //任务完成数   
    UILabel *missionTotal=[[[UILabel alloc]initWithFrame:CGRectMake(missionFinish.frame.origin.x+10, missionNameLabel.frame.origin.y+25, 120, 15)]autorelease];//任务总数
    if (g_rewardInfo.finish[indexPath.row]==g_rewardInfo.total[indexPath.row])
    {
        
    }
    else 
    {
        //任务完成数
        missionFinish.backgroundColor=[UIColor clearColor];
        missionFinish.font=[UIFont fontWithName:@"Helvetica" size:12];
        missionFinish.textAlignment=UITextAlignmentLeft;
        missionFinish.text=[NSString stringWithFormat:@"%d\\",g_rewardInfo.finish[indexPath.row]];
        //NSLog(@"2222222200000088888%@", [NSString stringWithUTF8String:g_rewardInfo.name[indexPath.row]]);
        [cell.contentView addSubview:missionFinish];        
        //任务总数
        missionTotal.backgroundColor=[UIColor clearColor];
        missionTotal.font=[UIFont fontWithName:@"Helvetica" size:12];        
        missionTotal.textAlignment=UITextAlignmentLeft;
        missionTotal.text=[NSString stringWithFormat:@"%d",g_rewardInfo.total[indexPath.row]];
        //NSLog(@"indexPath=%d, UUUUUUUU%@",indexPath.row, [NSString stringWithUTF8String:g_rewardInfo.name[1]]);
        [cell.contentView addSubview:missionTotal];

    }            
    //进行中Label
    if (g_rewardInfo.finish[indexPath.row]<g_rewardInfo.total[indexPath.row]) 
    {        
        UILabel *missionIng=[[[UILabel alloc]initWithFrame:CGRectMake(missionFinish.frame.origin.x-10, missionNameLabel.frame.origin.y+5, 120, 15)]autorelease];        
        missionIng.backgroundColor=[UIColor clearColor];        
        missionIng.text=@"进行中";
        missionIng.textAlignment=UITextAlignmentLeft;
        missionIng.font=[UIFont fontWithName:@"Helvetica" size:12];
        [cell.contentView addSubview:missionIng];        
    }
    //领取奖励按钮
    if( (g_rewardInfo.state[indexPath.row]==0)&&(g_rewardInfo.finish[indexPath.row]==g_rewardInfo.total[indexPath.row]) )
    {        
        medalIdState=indexPath.row;//服务器返回的成就Id 
        //NSLog(@"medalIdState=%d",indexPath.row);
        UIButton *getReward=[[[UIButton alloc]initWithFrame:CGRectMake(missionFinish.frame.origin.x-30, missionNameLabel.frame.origin.y+5, 80, 34)]autorelease];
        getReward.tag = g_rewardInfo.medalId[indexPath.row];
        [getReward setTitle:@"领取奖励" forState:UIControlStateNormal];
        [getReward setBackgroundImage:[UIImage imageNamed:@"SendButton.png"] forState:UIControlStateNormal];        
        [getReward addTarget:self action:@selector(isRewardBack:) forControlEvents:UIControlEventTouchUpInside];
        [cell.contentView addSubview:getReward];
    }
    //任务完成后点击领取奖励按钮，领取相应奖励，并出现“已完成”Label
   if(g_rewardInfo.state[indexPath.row]==1)
   {
       UILabel *completeLabel=[[[UILabel alloc] initWithFrame:CGRectMake(missionFinish.frame.origin.x-10, missionNameLabel.frame.origin.y+5, 80, 34)]autorelease];    
       completeLabel.text=@"已完成";
       completeLabel.backgroundColor=[UIColor clearColor];
       completeLabel.font=[UIFont fontWithName:@"Helvetica" size:12];
       completeLabel.textAlignment=UITextAlignmentLeft;
       [cell.contentView addSubview:completeLabel];
   }    
    return cell;
}
//发送领取奖励消息
-(void) isRewardBack:(id)sender
{
    UIButton *srcbtn = (UIButton *)sender;
    NSLog(@"button tag=%d", srcbtn.tag);
    MedalNetWrapper::m_pSelf->getMedalRewards(srcbtn.tag);
    //CFTimeInterval CFAbsoluteTimeGetCurrent();
    [[MenuLayerMedal sharedManager] viewWillAppear];
    
}
//重新读取数据，因为这时服务器返回了请求后的数据信息
//刷新数据，并在屏幕显示
-(void)reloadData
{
//    [[MenuLayerMedal sharedManager] sendGetMedal];
    [uiTableView reloadData];
}
-(void)refresh
{
    [[MenuLayerMedal sharedManager] sendGetMedal];
    [uiTableView reloadData];
}
//获取系统当前时间
-(NSString *)setTimeInt:(NSTimeInterval)timeSeconds setTimeFormat:(NSString *)timeFormatStr setTimeZome:(NSString *)timeZoneStr
{    
    NSString *date_string; 
    NSDate *time_str;
    
    if( timeSeconds>0){
        time_str =[NSDate dateWithTimeIntervalSince1970:timeSeconds];
    }else{
        time_str=[[[NSDate alloc] init] autorelease];
    }    
    
    if( timeFormatStr==nil){
        date_string =[NSString stringWithFormat:@"%d",(long)[time_str timeIntervalSince1970]];
    }else{
        NSDateFormatter *date_format_str =[[[NSDateFormatter alloc] init] autorelease];
        [date_format_str setDateFormat:timeFormatStr];
        if( timeZoneStr!=nil){
            [date_format_str setTimeZone:[NSTimeZone timeZoneWithName:timeZoneStr]];
        }
        date_string =[date_format_str stringFromDate:time_str];
    }
    return date_string;
}

/**
 
 *用法
 
 */

-(void)viewWillAppear
{     
    
    NSString *a =[self setTimeInt:1317914496 setTimeFormat:@"yy.MM.dd HH:mm:ss" setTimeZome:nil];
    
    NSString *b =[self setTimeInt:0 setTimeFormat:@"yy.MM.dd HH:mm:ss" setTimeZome:nil];
    
    NSString *c =[self setTimeInt:0 setTimeFormat:nil setTimeZome:nil];
    
    NSString *d =[self setTimeInt:0 setTimeFormat:@"yy.MM.dd HH:mm:ss" setTimeZome:@"GMT"];        
    
    NSLog(@"%@,,,%@,,,%@,,,%@",a,b,c,d);
    
}
@end