//
//  MenuLayerFAQ.m
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "MenuLayerFAQ.h"
#import "AddonWrapper.h"
#import "GameStateShortConnect.h"
#import "SimpleAudioEngineWrapper.h"

@implementation MenuLayerFAQ

@synthesize feedBack;
@synthesize sendOut;
@synthesize FAQ;
@synthesize m_textField;
@synthesize m_Tips;

static MenuLayerFAQ *menuLayerFAQ = nil;

+ (MenuLayerFAQ *)sharedManager
{
    if (!menuLayerFAQ) {
        menuLayerFAQ = [[MenuLayerFAQ alloc] init];
    }
    return menuLayerFAQ;
}
-(void)initSelfView
{
    [[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    
    [titleLable setFrame:CGRectMake(backButton.frame.origin.x+backButton.frame.size.width+5, 10, 100, 25)];
    [titleLable setText:@""];
    titleLable.backgroundColor = [UIColor clearColor];
    [titleLable setFont:[UIFont fontWithName:@".HelvetiaNeueUI" size:25]];
    titleLable.backgroundColor = [UIColor clearColor];
    
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];
    feedBack = [[UIButton alloc] initWithFrame:CGRectMake(310.0, 7.5, 90, 40)];
    FAQ = [[UIButton alloc] initWithFrame:CGRectMake(390, 7.5, 90, 40)];
    sendOut = [[UIButton alloc] initWithFrame:CGRectMake(480-10-50, 320-10-30, 50, 30)];    
    
    [feedBack.layer setBackgroundColor:[UIColor blueColor].CGColor];
    [feedBack.layer setCornerRadius:2.5];
    feedBack.backgroundColor = [UIColor clearColor];
    [feedBack setTitle:@"意见反馈" forState:UIControlStateNormal];
    [feedBack.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [feedBack addTarget:self action:@selector(feedBackCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [FAQ.layer setBackgroundColor:[UIColor blueColor].CGColor];
    [FAQ.layer setCornerRadius:2.5];
    FAQ.backgroundColor = [UIColor clearColor];
    [FAQ setTitle:@"常见问题" forState:UIControlStateNormal];
    [FAQ.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    //注册回调
    [FAQ addTarget:self action:@selector(FAQCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [sendOut.layer setBackgroundColor:[UIColor blueColor].CGColor];
    [sendOut.layer setCornerRadius:2.5];
    FAQ.backgroundColor = [UIColor clearColor];

    [sendOut setTitle:@"送出" forState:UIControlStateNormal];
    [sendOut.titleLabel setFont:[UIFont boldSystemFontOfSize:15]];
    [sendOut setBackgroundImage:[UIImage imageNamed:@"SendButton.png"] forState:UIControlStateNormal];
    sendOut.backgroundColor = [UIColor clearColor];
    //注册回调
    [sendOut addTarget:self action:@selector(sendOutCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    //创建滑动阴影控件
    [self setSlideBlockFrame:CGRectMake(feedBack.frame.origin.x-2, feedBack.frame.origin.y-10, 90, 52)];
    [slideBlock setImage:[UIImage imageNamed:@"Store_arrow.png"]];
    //添加两个Button到这个View
    [[self view] addSubview:feedBack];
    [[self view] addSubview:FAQ];
    [[self view] addSubview:sendOut];
    
    //创建和初始化文字输入框
    m_textField = [[UITextField alloc] initWithFrame:CGRectMake(10, 50, 460, 260)];
    [m_textField setBorderStyle:UITextBorderStyleRoundedRect];
    m_textField.placeholder = @"在此输入您的反馈，仅限140字以内";
    m_textField.clearsOnBeginEditing = YES;//设置为YES当用点触文本字段时，字段内容会被清除
    m_textField.clearButtonMode = UITextFieldViewModeWhileEditing;//在编辑文字时可以删除所有文字，方便用户全部重新输入
    m_textField.delegate = self;
    [[self view] addSubview:m_textField];
    
    m_help = [[UITextView alloc] initWithFrame:CGRectMake(10, 50, 460, 260)];
    m_help.backgroundColor = [UIColor clearColor];
    [m_help setText:@"\
     \n庄家：每副牌开始发牌的玩家，下注从庄家的下家开始。新开始的赛桌上随机指定庄家，以后每副牌的庄家为上副牌的赢家，庄家离桌后再次随机指定庄家。\
     \n底注：指游戏开始后每位玩家投入的初始注。\
     \n明注：看牌后的下注。\
     \n暗注：不看牌的下注。暗注的筹码相当于明注筹码的2倍。\
     \n单注封顶：每个玩家每次下注的上限。\
     \n手数封顶：每副牌每名玩家下注次数的上限（不包括底注），当达到手数封顶时，玩家将只可以与其他玩家比牌（比牌时仍要支付比牌费用）。\
     \n跟注：和上家加入同样的筹码。注：暗注相当于明注的2倍。\
     \n加注：加入比上家上手单注更多的筹码。加注后不能超过单注封顶。\
     \n锅底：每副牌玩家所有下注之和，每副牌最后的赢家独得其中所有筹码。\
     \n看牌：查看自己三张牌的花色和点数，不能分别看一张或两张。\
     \n弃牌：指玩家自动弃权,本副牌认输且不收回本副牌筹码。\
     \n比牌：拿自己的牌和其他玩家的牌比大小，同时要支付当前单注两倍的比牌费用，加入锅底。\
     \n喜金：当最后获胜牌型为豹子、顺金、235时，同桌的其它玩家还要额外支付胜者一些喜金，弃牌、\
     \n断线者也包括在内。若某玩家剩余费用不够支付喜金，则支付剩余所有筹码即可。"];
    m_help.editable = NO;
    [[self view] addSubview:m_help];
    m_help.hidden = YES;
    
    m_Tips = [[UIAlertView alloc] initWithFrame:CGRectMake(80, 60, 160, 100)];
    [m_Tips addButtonWithTitle:@"好滴"];
    m_Tips.delegate = self;
}

- (void)feedBackCallBack
{
    m_textField.hidden = NO;
    sendOut.hidden = NO;
    m_help.hidden = YES;
    [self slideBlockOfButton:CGRectMake(feedBack.frame.origin.x-2, feedBack.frame.origin.y-10, 90, 52)];
}

- (void)FAQCallBack
{
    m_textField.hidden = YES;
    sendOut.hidden = YES;
    m_help.hidden = NO;
    [self slideBlockOfButton:CGRectMake(FAQ.frame.origin.x-2, FAQ.frame.origin.y-10, 90, 52)];
}

- (void)sendOutCallBack
{
    NSLog(@"===sendOutCallBack===\nm_textField.text.length = %d\n", m_textField.text.length);
    if (m_textField.text.length < 10) {
        m_Tips.message = @"亲，字数有点少哦";
        [m_Tips show];
        m_Tips.hidden = NO;
    }
    else if (m_textField.text.length > 140) {
        m_Tips.message = @"太给力了，但是只能在140字以内哦";
        [m_Tips show];
        m_Tips.hidden = NO;
    }
    else {
        m_Tips.message = @"谢谢您的意见，我们会及时做出修改";
        [m_Tips show];
        m_Tips.hidden = NO;
        //向服务器发送请求
        GameStateShortConnect::GetInstance()->feedback([m_textField.text UTF8String]);
        CGRect rect = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height); 
        self.view.frame = rect;
        m_textField.frame = CGRectMake(10, 50, 460, 220);
        [UIView commitAnimations];
        [m_textField resignFirstResponder];
    }
}

- (void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    menuLayerFAQHide();
}


-(IBAction)backgroundTap:(id)sender
{
    // When the user presses return, take focus away from the text field so that the keyboard is dismissed. 
    NSTimeInterval animationDuration = 0.20f; 
    [UIView beginAnimations:@"ResizeForKeyboard" context:nil]; 
    [UIView setAnimationDuration:animationDuration]; 
    CGRect rect = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height); 
    self.view.frame = rect;
    [UIView commitAnimations];
    //重新设置m_textField 的大小
    m_textField.frame = CGRectMake(10, 50, 460, 220);
    [m_textField resignFirstResponder];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIControl *_back = [[UIControl alloc] initWithFrame:self.view.frame];
    _back.backgroundColor = [UIColor grayColor];
    self.view = _back;
    [_back release];
    [(UIControl *)self.view addTarget:self action:@selector(backgroundTap:) forControlEvents:UIControlEventTouchDown];
}


-(BOOL)textFieldShouldReturn:(UITextField *)textField
{ 
    // When the user presses return, take focus away from the text field so that the keyboard is dismissed. 
    NSTimeInterval animationDuration = 0.250f; 
    [UIView beginAnimations:@"ResizeForKeyboard" context:nil]; 
    [UIView setAnimationDuration:animationDuration]; 
    CGRect rect = CGRectMake(0.0f, 0.0f, self.view.frame.size.width, self.view.frame.size.height); 
    m_textField.frame = CGRectMake(10, 50, 460, 220);
    self.view.frame = rect;
    [UIView commitAnimations];
    [textField resignFirstResponder];
    return YES; 
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{ 
    CGRect frame = textField.frame;
    int offset = frame.origin.y + 32 - (self.view.frame.size.height - 216.0);//键盘高度216
    NSTimeInterval animationDuration = 0.25f; 
    [UIView beginAnimations:@"ResizeForKeyBoard" context:nil]; 
    [UIView setAnimationDuration:animationDuration];
    float width = self.view.frame.size.width; 
    float height = self.view.frame.size.height;
  
    CGRect rect = CGRectMake(-offset, 0.0f, width,height); 
    m_textField.frame = CGRectMake(10, 50+140, 460, 90);
    self.view.frame = rect; 
    [UIView commitAnimations]; 
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    m_Tips.hidden = YES;
}
@end
