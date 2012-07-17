//
//  MenuLayerActs.m
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "MenuLayerActs.h"
#import "AddonWrapper.h"
#import "SimpleAudioEngineWrapper.h"

@implementation MenuLayerActs

@synthesize m_webView;

static MenuLayerActs *menuLayerActs = nil;

+(MenuLayerActs *)sharedManager
{
    if (!menuLayerActs) {
        menuLayerActs = [[MenuLayerActs alloc] init];
    }
    return menuLayerActs;
}

-(void)initSelfView
{
    [[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    //设置标题显示文字
    [titleLable setFrame:CGRectMake(backButton.frame.origin.x+backButton.frame.size.width+5, 10, 200, 25)];
    [titleLable setText:@"倾情回馈，买的多送得多"];
    [titleLable setFont:[UIFont fontWithName:@".HelvetiaNeueUI" size:10]];
    titleLable.backgroundColor = [UIColor clearColor];
    
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];
    
    m_webView = [[UIWebView alloc] initWithFrame:CGRectMake(10, 50, 460, 260)];
    m_webView.scalesPageToFit = YES;
    [[self view] addSubview:m_webView];
    NSURL *url = [[[NSURL alloc] initWithString:@"http://www.36kr.com"]autorelease];
    NSURLRequest *request = [[[NSURLRequest alloc] initWithURL:url] autorelease];
    [m_webView loadRequest:request];
}

-(void)backButtonCallback
{
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    menuLayerActsHide();
}
@end
