//
//  CommonLayerHelpScrollView.m
//  ThreeCard
//
//  Created by Chao Li on 12-6-6.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import "CommonLayerHelpScrollView.h"
#import "CommonLayerHelpWrapper.h"
@implementation CommonLayerHelpScrollView

@synthesize helpScrollView;
@synthesize helpPageControl;
static CommonLayerHelpScrollView *commonLayerHelpScrollView = nil;

+(CommonLayerHelpScrollView *)sharedManager
{
    if (!commonLayerHelpScrollView) {
        commonLayerHelpScrollView = [[CommonLayerHelpScrollView alloc] init];
    }
    return commonLayerHelpScrollView;
}

- (void) initSelfView
{
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    //设置当前view的tag
    self.view.tag= 11;
    NSLog(@"CommonLayerHelpScrollVIew initSelfView\n");
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    
    [backButton setFrame:CGRectMake(7.0, 7.0, 42, 30)];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    
    //设置标题显示文字
    titleLable.font=[UIFont fontWithName:@".HelvetiaNeueUI" size:25];
    titleLable.backgroundColor = [UIColor clearColor];
    titleLable.textAlignment=UITextAlignmentLeft;
    titleLable.text=@"基本玩法";
    
    //导航栏
    UIImageView *titleBar=[[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, 480, 45)]autorelease];
    titleBar.image=[UIImage imageNamed:@"L2title@2x.png"];
    [[self view] addSubview:titleBar];
    
    //页面数
    pageNumber = [[UILabel alloc]initWithFrame:CGRectMake(450, 10, 30, 20)];
    pageNumber.backgroundColor = [UIColor clearColor];
    pageNumber.textColor=[UIColor whiteColor];
    pageNumber.font = [UIFont fontWithName:@".HelvetiaNeueUI" size:15];
    pageNumber.text=@"1/8";
    [[self view] addSubview:pageNumber];
    
    /*
    int pageCount=8;
    NSLog(@"CommonLayerHelpScrollView viewDidLoad\n");
    helpScrollView=[[UIScrollView alloc]initWithFrame:CGRectMake(10, 50, 460, 260)];
    helpScrollView.pagingEnabled = YES; 
    helpScrollView.backgroundColor = [UIColor blueColor]; 
    helpScrollView.showsVerticalScrollIndicator = NO; 
    helpScrollView.showsHorizontalScrollIndicator = NO; 
    helpScrollView.scrollEnabled=YES;
    helpScrollView.delegate = self; 
    
    helpScrollView.contentSize=CGSizeMake(460*pageCount, 260);
    
    [[self view] addSubview:helpScrollView];
    */
    
    [self createPages];
    
    //initSelfView 在 viewDidLoad 之后执行
    [[self view] addSubview:helpScrollView];
    [[self view] addSubview:helpPageControl];
}

- (void) viewDidLoad
{
    [super viewDidLoad];
    
    int pageCount=8;
    NSLog(@"CommonLayerHelpScrollView viewDidLoad\n");
    
    helpPageControl = [[UIPageControl alloc]initWithFrame:CGRectMake((480-200)/2, 300, 200, 20)];
    //helpPageControl.frame.origin=CGPointMake(480-100)/2, 300);
    helpPageControl.frame.size=[helpPageControl sizeForNumberOfPages:pageCount];
    //helpPageControl.backgroundColor = [UIColor redColor];
    helpPageControl.numberOfPages = pageCount;
    helpPageControl.currentPage = 0;
    helpPageControl.defersCurrentPageDisplay=YES;
    [helpPageControl addTarget:self action:@selector(changePage:) forControlEvents:UIControlEventValueChanged];
    
    helpScrollView=[[UIScrollView alloc]initWithFrame:CGRectMake(0, 50, 480, 280)];
    helpScrollView.pagingEnabled = YES; 
    //helpScrollView.backgroundColor = [UIColor blueColor]; 
    helpScrollView.showsVerticalScrollIndicator = NO; 
    helpScrollView.showsHorizontalScrollIndicator = NO; 
    helpScrollView.scrollEnabled=YES;
    helpScrollView.delegate = self; 
    helpScrollView.contentSize=CGSizeMake(480*pageCount, 280);
    
    [self createPages];
    
}

- (void) backButtonCallback
{
    commonLayerHelpScrollViewHide();
}

#pragma mark 视图加载
- (void)loadScrollViewWithPage:(UIView *)page 
{
    int pageCount = [[helpScrollView subviews] count];
    
    CGRect bounds = helpScrollView.bounds;
    bounds.origin.x = bounds.size.width * pageCount;
    bounds.origin.y = 0;
    //page.frame = bounds;
    [helpScrollView addSubview:page];
    
}

- (void)scrollViewDidScroll:(UIScrollView *)sender 
{
    CGFloat pageWidth = sender.frame.size.width;
    int page = floor((sender.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    helpPageControl.currentPage = page;
    
    switch (page) {
        case 0:
            titleLable.text=@"基本玩法";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        case 1:
            titleLable.text=@"游戏举例";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        case 2:
            titleLable.text=@"比牌规则";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];            
            break;
        case 3:
            titleLable.text=@"界面介绍";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        case 4:
            titleLable.text=@"奖池分配";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        case 5:
            titleLable.text=@"名词解释";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        case 6:
            titleLable.text=@"游戏流程";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        case 7:
            titleLable.text=@"比赛须知";
            pageNumber.text=[NSString stringWithFormat:@"%d/8",page + 1];
            break;
        default:
            break;
    }
}

- (void)createPages
{
    //CGRect pageRect = helpScrollView.frame;
    //CGRect pageRect = CGRectMake((460-384)/2, (280-192)/2, 384, 192);
    //create and add pages
    for (int i=0; i<8; i++) {
        CGRect pageRect = CGRectMake(i*480 + (460-384)/2, (280-192)/2, 384, 192);
        UIImageView *page = [[UIImageView alloc] initWithFrame:pageRect];
        page.image=[UIImage imageNamed:[NSString stringWithFormat:@"Help_%d", i+4]];
        
        //add to scrollview
        [self loadScrollViewWithPage:page];
        
        //clean up
        [page release];
    }
}

- (void)changePage:(id)sender
{
    int page = helpPageControl.currentPage;
    /*
    switch (page) {
        case 0:
            self->titleLable.text=@"基本玩法";
            break;
        case 1:
            self->titleLable.text=@"游戏举例";
            break;
        case 2:
            self->titleLable.text=@"比牌规则";
            break;
        case 3:
            self->titleLable.text=@"界面介绍";
            break;
        case 4:
            self->titleLable.text=@"奖池分配";
            break;
        case 5:
            self->titleLable.text=@"名词解释";
            break;
        case 6:
            self->titleLable.text=@"游戏流程";
            break;
        case 7:
            self->titleLable.text=@"比赛须知";
            break;
        default:
            break;
    }
    */
    // update the scroll view to the appropriate page
    CGRect frame = helpScrollView.frame;
    frame.origin.x = frame.size.width * page;
    frame.origin.y = 0;
    [helpScrollView scrollRectToVisible:frame animated:YES];
}

- (void)dealloc
{
    [helpScrollView release];
    [helpPageControl release];
    
    [super dealloc];
}

- (void)switchAnimation:(UIView *)otherView
{
    [UIView beginAnimations:@"animationID" context:nil];//开始一个动画块，第一个参数为动画块标识 
    
    [UIView setAnimationDuration:1.0f];//设置动画的持续时间  
    
    [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];  
    //设置动画块中的动画属性变化的曲线，此方法必须在beginAnimations方法和commitAnimations，默认即为UIViewAnimationCurveEaseInOut效果。
    
    [UIView setAnimationRepeatAutoreverses:NO];//设置是否自动反转当前的动画效果  
    
    [UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:self.view.superview cache:YES];
    //设置过渡的动画效果，此处第一个参数可使用上面5种动画效果  
    [self.view.superview sendSubviewToBack:self.view];
    [[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    [self.view.superview exchangeSubviewAtIndex:14 withSubviewAtIndex:13];//页面翻转  
    
    
    
    [UIView commitAnimations];//提交动画 
    NSLog(@"[self view].superview.subviews.count=%d\n",[self view].superview.subviews.count);
    NSLog(@"%d", [self.view.superview.subviews indexOfObject:self.view]);
    NSLog(@"%d", [self.view.superview.subviews indexOfObject:[self.view.superview viewWithTag:10]]);
    NSLog(@"%d", [self.view.superview.subviews indexOfObject:[self.view.superview viewWithTag:11]]);
    //NSLog(@"", [self.view.superview viewWithTag:11])
    /*
    //[[self view] addSubview:otherView];
    //CGContextRef context = UIGraphicsGetCurrentContext();
    // 准备动画
    CATransition *animation = [CATransition animation];
    //动画播放持续时间
    [animation setDuration:0.75];
    //动画速度,何时快、慢
    [animation setTimingFunction:[CAMediaTimingFunction
                                  functionWithName:kCAMediaTimingFunctionLinear]];
    [animation setType:kCATransitionPush];
    [animation setSubtype:kCATransitionFromLeft];
    [[self view].superview bringSubviewToFront:self.view];
    //[[self view].superview exchangeSubviewAtIndex:4 withSubviewAtIndex:2];
    [[self view].superview.layer addAnimation:animation forKey:nil];
    
    //NSLog(@"current view index=%d", [self view] );
    //[[self view]bringSubviewToFront:otherView];
    */
}
@end
