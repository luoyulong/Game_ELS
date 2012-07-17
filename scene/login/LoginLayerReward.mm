//
//  LoginLayerReward.m
//  GameBox
//
//  Created by Chao Li on 12-5-31.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "LoginLayerReward.h"
#import "GlobalData.h"
#import "GameStateShortConnect.h"
#import "QuartzCore/QuartzCore.h"

@implementation LoginLayerReward

@synthesize tips;
@synthesize confirm;
@synthesize rewardArea;
@synthesize numberOfGetCoin;
@synthesize starLine;

static LoginLayerReward *loginLayerReward=nil;
+ (LoginLayerReward *)sharedManager
{
    if (!loginLayerReward) {
        loginLayerReward=[[LoginLayerReward alloc] init];
    }
    
    return loginLayerReward;
}

- (void)initSelfView
{
    [[self view]setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    [self view].backgroundColor=[UIColor colorWithHue:0 saturation:0 brightness:0 alpha:0.6];
    
    //m_Timer=[NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(showAnimationCallBack) userInfo:nil repeats:YES];
    //[self view].layer.backgroundColor=[CGColor grayColor];
}

- (void)updateData{
    //实际红色区域大小为654x428
    background=[[[UIImageView alloc]initWithFrame:CGRectMake(60, 50, 688/2, 460/2)]autorelease];
    background.image=[UIImage imageNamed:@"getDailyChips_BG.png"];
    
    title=[[[UILabel alloc]initWithFrame:CGRectMake(background.frame.origin.x+17+5, background.frame.origin.y+18, 628/2-10, 30)]autorelease];
    title.text=@"连续登陆奖励";
    title.backgroundColor=[UIColor clearColor];
    title.textColor=[UIColor whiteColor];
    title.textAlignment=UITextAlignmentCenter;
    starLine=[[[UIImageView alloc]initWithFrame:CGRectMake(title.frame.origin.x+(654/2-428/2)/2, title.frame.origin.y+title.frame.size
                                                           .height+5, 428/2, 16/2)]autorelease];
    starLine.image=[UIImage imageNamed:@"getDailyChips_line.png"];
    
    numberOfGetCoin=[[[UILabel alloc]initWithFrame:CGRectMake(title.frame.origin.x, starLine.frame.origin.y+starLine.frame.size.height+5, 100, 15)]autorelease];
    numberOfGetCoin.text=[NSString stringWithFormat:@"今日领取%d金币", g_user.reward[g_user.nslogin-1]];
    numberOfGetCoin.adjustsFontSizeToFitWidth = YES;
    numberOfGetCoin.font=[UIFont fontWithName:@".HelvetiaNeueUI" size:2];
    numberOfGetCoin.backgroundColor=[UIColor clearColor];
    numberOfGetCoin.textAlignment=UITextAlignmentCenter;
    
    //rewardArea=[[[UIView alloc]initWithFrame:CGRectMake(0, 0, (688/2-2*5), 80)]autorelease];
    rewardArea=[[[UIView alloc]initWithFrame:CGRectMake(numberOfGetCoin.frame.origin.x, numberOfGetCoin.frame.origin.y+numberOfGetCoin.frame.size.height+5, (654/2-2*15), 80)]autorelease];
    //rewardArea.backgroundColor=[UIColor orangeColor];
    for (int i=1; i<7; i++) {
//        NSLog(@"####g_user_nslogin=%d####\n", g_user.nslogin);
        if (i < g_user.nslogin) {
            UIImageView *cardFront=[[[UIImageView alloc]initWithFrame:CGRectMake(0 + (i-1)*50,5,100/2, 120/2)]autorelease];
            cardFront.image=[UIImage imageNamed:@"getDailyChips_cardfront.png"];
            UIImageView *coins=[[UIImageView alloc]initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"getDailyChips_chips%d.png",i]]];
            coins.frame=CGRectMake((100/2-77/2)/2, (60-44)/2, 77/2, 88/2);
            
            NSLog(@"----coins.frame.size.width=%f, coins.frame.size.height=%f\n", coins.frame.size.width, coins.frame.size.height);
            NSLog(@"----coins.center.x=%f, coins.center.y=%f\n", coins.center.x, coins.center.y);
            
            [cardFront addSubview:coins];
            [rewardArea addSubview:cardFront];
        }
        else {
            UIImageView *cardBack=[[[UIImageView alloc]initWithFrame:CGRectMake(0 + (i-1)*50, 5, 100/2, 120/2)]autorelease];
            cardBack.image=[UIImage imageNamed:@"getDailyChips_cardback.png"];
            UILabel *dayNum=[[UILabel alloc]initWithFrame:CGRectMake(0, 0, cardBack.frame.size.width, cardBack.frame.size.height)];
            dayNum.numberOfLines=0;
            dayNum.text=[NSString stringWithFormat:@"%d\n天",i];
            dayNum.backgroundColor=[UIColor clearColor];
            dayNum.textAlignment=UITextAlignmentCenter;
            if (i==6) {
                UIImageView *plusMark=[[UIImageView alloc]initWithFrame:CGRectMake(30, 10, 28/2, 28/2)];
                plusMark.image=[UIImage imageNamed:@"getDailyChips_plusmark.png"];
                [cardBack addSubview:plusMark];
                if (g_user.nslogin==i) {
                    rotatePlus=plusMark;
                }
            }
            
            //添加翻转（拉伸）动画
            if (i==g_user.nslogin) {
                
                //记录翻转牌对象...
                rotateDayNum=dayNum;
                rotateCard=cardBack;
                
                UIImageView *coins=[[UIImageView alloc]initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"getDailyChips_chips%d.png",i]]];
                coins.frame=CGRectMake((100/2-77/2)/2, (60-44)/2, 77/2, 88/2);
                coins.hidden=YES;
                //旋转90度
                //CGAffineTransform at = CGAffineTransformMakeRotation(M_PI);
                //[coins setTransform:at];
                
                [cardBack addSubview:coins];
                rotateCoins=coins;
                
                
                //图像拉伸模拟的翻牌动画
                
                CAKeyframeAnimation* animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
                CATransform3D r[2] = {CATransform3DMakeScale(0.01,1,1), CATransform3DMakeScale(1,1,1)};
                
                animation.values = [NSArray arrayWithObjects:[NSValue valueWithCATransform3D:r[1]],[NSValue valueWithCATransform3D:r[0]], [NSValue valueWithCATransform3D:r[1]],nil];
                animation.repeatCount =1;
                animation.duration =1.5;
                animation.delegate=self;
                animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
                //animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
                [cardBack.layer addAnimation:animation forKey:nil];
                
                
                /*
                //绕Y轴旋转360度方法的翻牌效果
                CABasicAnimation *animation = [CABasicAnimation
                                               animationWithKeyPath: @"transform" ];
                CATransform3D tans3D = cardBack.layer.transform;
                //CATransform3D tans3D = self.view.layer.;
                tans3D = CATransform3DMakeRotation(M_PI, 0, 1, 0);
                
                animation.toValue = [NSValue valueWithCATransform3D:tans3D];
                animation.duration = 1.5;
                animation.cumulative = YES;
                animation.repeatCount = 1;
                animation.delegate=self;
                [cardBack.layer addAnimation:animation forKey:@"animation"];
                */
                //初始化定时器....
                m_Timer=[NSTimer timerWithTimeInterval:0.75 target:self selector:@selector(turnFrontCallBack) userInfo:nil repeats:YES];
                [[NSRunLoop mainRunLoop] addTimer:m_Timer forMode:NSDefaultRunLoopMode]; 
            }
            //旋转90度
            //CGAffineTransform at = CGAffineTransformMakeRotation(M_PI/2);
            //[dayNum setTransform:at];

            
            [cardBack addSubview:dayNum];
            [rewardArea addSubview:cardBack];
        }
        
        UILabel *rewardCoins = [[UILabel alloc]initWithFrame:CGRectMake(0 + (i-1)*50, rewardArea.frame.size.height-15, 100/2, 15)];
        rewardCoins.text=[NSString stringWithFormat:@"+%d", g_user.reward[i-1]];
        rewardCoins.textAlignment=UITextAlignmentCenter;
        rewardCoins.backgroundColor=[UIColor clearColor];
        rewardCoins.textColor=[UIColor orangeColor];
        rewardCoins.adjustsFontSizeToFitWidth = YES;
        [rewardArea addSubview:rewardCoins];
    }
    
    tips=[[[UILabel alloc]initWithFrame:CGRectMake(numberOfGetCoin.frame.origin.x, rewardArea.frame.origin.y+rewardArea.frame.size.height+5, rewardArea.frame.size.width, 15)]autorelease];
    tips.text=@"连续登陆可获得更多奖励，最高每天1200筹码奖励";
    tips.font=[UIFont fontWithName:@".HelvetiaNeueUI" size:2];
    tips.adjustsFontSizeToFitWidth = YES;
    tips.backgroundColor=[UIColor clearColor];
    tips.textAlignment=UITextAlignmentCenter;
    
    confirm=[[[UIButton alloc]initWithFrame:CGRectMake(200, tips.frame.origin.y+tips.frame.size.height+5, 184/2, 64/2)]autorelease];
    [confirm setBackgroundImage:[UIImage imageNamed:@"getDailyChips_btnOK.png"] forState:UIControlStateNormal];
    [confirm setTitle:@"确定" forState:UIControlStateNormal];
    [confirm addTarget:self action:@selector(confirmButtonCallBack) forControlEvents:UIControlEventTouchUpInside];
    
    [[self view] addSubview:background];
    [[self view] addSubview:title];
    [[self view] addSubview:starLine];
    [[self view] addSubview:numberOfGetCoin];
    [[self view] addSubview:rewardArea];
    [[self view] addSubview:tips];
    [[self view] addSubview:confirm];
}

- (void)confirmButtonCallBack{
    
    [[self view] removeFromSuperview];
    //[[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    //[[LoginLayerReward sharedManager] viewMoveToBottom :SINGLE_LAYER_MOVE otherView:nil];
}


- (void)animationDidStop:(CAAnimation *)theAnimation finished:(BOOL)flag 
{ 
    
    NSLog(@"***********cardFrontDidFinishedCallBack======\n");
    //添加
    /*
    UIImageView *coins=[[[UIImageView alloc]initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"getDailyChips_chips%d.png",g_user.nslogin]]]autorelease];
    coins.frame=CGRectMake((100/2-77/2)/2, (60-44)/2, 77/2, 88/2);
    [rotateCard addSubview:coins];
    */
    //显示对号标志
    UIImageView *okMark=[[[UIImageView alloc]initWithFrame:CGRectMake(rotateCard.frame.origin.x+rotateCard.frame.size.width-32/2, rotateCard.frame.origin.y-5, 32/2, 32/2)]autorelease];
    //UIImageView *okMark=[[[UIImageView alloc]initWithFrame:CGRectMake(20, 0, 32/2, 32/2)]autorelease];
    okMark.image=[UIImage imageNamed:@"getDailyChips_OKmark.png"];
    //[rotateCard addSubview:okMark];
    [rewardArea addSubview:okMark];
    CAKeyframeAnimation* animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
    CATransform3D r[2] = {CATransform3DMakeScale(1,1,1), CATransform3DMakeScale(1.2,1.2,1)};
    
    //animation.values = [NSArray arrayWithObjects:[NSValue valueWithCATransform3D:r[0]],[NSValue valueWithCATransform3D:r[1]],[NSValue valueWithCATransform3D:r[0]],nil];
    animation.values = [NSArray arrayWithObjects:[NSValue valueWithCATransform3D:r[0]],[NSValue valueWithCATransform3D:r[1]], [NSValue valueWithCATransform3D:r[0]], nil];
    animation.repeatCount =1;
    animation.duration =0.5;
    animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
    [okMark.layer addAnimation:animation forKey:nil];
    
    //m_RotateCard.hidden=YES;
    /*
    m_RotateCard.image=[UIImage imageNamed:@"getDailyChips_cardfront.png"];
    CAKeyframeAnimation* animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
    CATransform3D r[2] = {CATransform3DMakeScale(0.01,1,1), CATransform3DMakeScale(1,1,1)};
    
    //animation.values = [NSArray arrayWithObjects:[NSValue valueWithCATransform3D:r[0]],[NSValue valueWithCATransform3D:r[1]],[NSValue valueWithCATransform3D:r[0]],nil];
    animation.values = [NSArray arrayWithObjects:[NSValue valueWithCATransform3D:r[0]],[NSValue valueWithCATransform3D:r[1]], nil];
    animation.repeatCount =1;
    animation.duration =1.75;
    animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
    [m_RotateCard.layer addAnimation:animation forKey:nil];
    */
    /*
    NSLog(@"***********cardFrontDidFinishedCallBack======\n");
    background.image=[UIImage imageNamed:@"getDailyChips_cardfront.png"];
    CABasicAnimation *animation = [ CABasicAnimation
                                   animationWithKeyPath: @"transform" ];
    CATransform3D tans3D = background.layer.transform;
    //CATransform3D tans3D = self.view.layer.transform;
    tans3D = CATransform3DMakeRotation(3.1415/2, 0, 1, 0);//180度
    
    animation.toValue = [NSValue valueWithCATransform3D:tans3D];
    animation.duration = 2;
    animation.cumulative = YES;
    animation.repeatCount = 1;
    //animation.delegate=self;
    
    [background.layer addAnimation:animation forKey:@"animation"];
    */
}

- (void)turnFrontCallBack
{
    NSLog(@"=====turnFrontCallBack=====\n");
    rotateCard.image=[UIImage imageNamed:@"getDailyChips_cardfront.png"];
    /*
    for (UIView *view in rotateCard.subviews) {
        [view removeFromSuperview];
    }
    */
    
    [rotatePlus removeFromSuperview];
    [rotateDayNum removeFromSuperview];
    rotateCoins.hidden=NO;
    [m_Timer invalidate];
}

@end
