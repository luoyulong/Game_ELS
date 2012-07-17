//
//  CommonLayerHelp.m
//  ThreeCard
//
//  Created by Chao Li on 12-6-6.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "CommonLayerHelp.h"
#import "CommonLayerHelpWrapper.h"
#import "CommonLayerHelpScrollView.h"
#import "SimpleAudioEngineWrapper.h"

@implementation CommonLayerHelp

static CommonLayerHelp *commonLayerHelp = nil;

+(CommonLayerHelp *)sharedManager
{
    if (!commonLayerHelp) {
        commonLayerHelp = [[CommonLayerHelp alloc] init];
    }
    return commonLayerHelp;
}

-(void) initSelfView
{
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    
    //设置标题显示文字
    [titleLable setFrame:CGRectMake(backButton.frame.origin.x+backButton.frame.size.width+5, 10, 100, 25)];
    [titleLable setText:@"帮助"];
    [titleLable setFont:[UIFont fontWithName:@".HelvetiaNeueUI" size:25]];
    
     titleLable.backgroundColor = [UIColor clearColor];
     titleLable.textAlignment=UITextAlignmentLeft;

    NSLog(@"CommonLayerHelp view.index=%d", [self.view.superview.subviews indexOfObject:self.view]);
    //设置当前view的tag
    self.view.tag= 10;
    
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];

    for (int i=0; i<8; i++) {
        UIButton *help=[[UIButton alloc]initWithFrame:CGRectMake(50+(i%2)*(176+30), 70+(i/2)*(42+20), 176, 42)];

        [help setBackgroundImage:[UIImage imageNamed:@"Help_Button01.png"] forState:UIControlStateNormal];
        [help setBackgroundImage:[UIImage imageNamed:@"Help_Button02.png"] forState:UIControlStateHighlighted];
        [help setTag:i];
        [help addTarget:self action:@selector(helpCallBack:) forControlEvents:UIControlEventTouchUpInside];
        
        switch (i) {
            case 0:
                [help setTitle:@"基本玩法" forState:UIControlStateNormal];
                break;
            case 1:
                [help setTitle:@"游戏举例" forState:UIControlStateNormal];
                break;
            case 2:
                [help setTitle:@"比牌规则" forState:UIControlStateNormal];
                break;
            case 3:
                [help setTitle:@"界面介绍" forState:UIControlStateNormal];
                break;
            case 4:
                [help setTitle:@"奖池分配" forState:UIControlStateNormal];
                break;
            case 5:
                [help setTitle:@"名词解释" forState:UIControlStateNormal];
                break;
            case 6:
                [help setTitle:@"游戏流程" forState:UIControlStateNormal];
                break;
            case 7:
                [help setTitle:@"比赛须知" forState:UIControlStateNormal];
                break;
            default:
                break;
        }
        
        [[self view] addSubview:help];
    }
}

-(void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    commonLayerHelpHide();
}

- (void)helpCallBack:(id)sender
{
    
    NSInteger i = [sender tag];
    NSLog(@"helpCallBack sender tag=%d", i);
    commonLayerHelpScrollViewShow(i);
    
    /*
    switch (i) {
        case 0:
            commonLayerHelpScrollViewShow(0);
            break;
        case 1:
            commonLayerHelpScrollViewShow(1);
            break;
        case 2:
            commonLayerHelpScrollViewShow(2);
            break;
        case 3:
            commonLayerHelpScrollViewShow(3);
            break;
        case 4:
            commonLayerHelpScrollViewShow(4);
            break;
        case 5:
            commonLayerHelpScrollViewShow(5);
            break;
        case 6:
            commonLayerHelpScrollViewShow(6);
            break;
        case 7:
            commonLayerHelpScrollViewShow(7);
            break;
        default:
            break;
    }
    */
}
@end
