//
//  UITableLayer.m
//  GameBox
//
//  Created by  on 12-5-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "UITableLayer.h"
#import "GETouchDispatcher.h"
#import "MainViewController.h"

@implementation UITableLayer

- (id)init
{
//    slideBlockButtonArray = [NSArray arrayWithObjects:nil];
    backgroundView = [[UIImageView alloc] initWithFrame:CGRectMake(0.0,0.0,480,320)];
    [[self view] addSubview:backgroundView];
    
    [[self view] setTransform:CGAffineTransformMakeRotation(3.14159/2)];
//	[[self view] setFrame:CGRectMake(-320.0, 0.0, 320, 480.0)];
    [[self view] setBackgroundColor:[UIColor clearColor]];
    
    titleLable = [[UILabel alloc] init];
    [titleLable setFrame:CGRectMake(60, 10, 100, 25)];
    [titleLable setBackgroundColor:[UIColor clearColor]];
    [titleLable setTextColor:[UIColor whiteColor]];
    [titleLable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:26]];
    
    backButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [backButton setFrame:CGRectMake(7.0, 7.0, 42, 30)];
    [backButton setBackgroundColor:[UIColor clearColor]];
    [backButton addTarget:self action:@selector(backButtonCallback) forControlEvents:UIControlEventTouchUpInside];
    
    [self initSelfView];
    
    [[self view] addSubview:titleLable];
    [[self view] addSubview:backButton];
    
    return self;
}

- (void)initSelfView
{
}

- (void)makeButton:(UIButton *)button rect:(CGRect)cgRect
{
    [button setFrame:cgRect];
    [button setBackgroundColor:[UIColor clearColor]];
//    [button.layer setBackgroundColor:[UIColor orangeColor].CGColor];
//    [button.layer setCornerRadius:3.0]; //设置矩形四个圆角半径
//    [button.layer setBorderWidth:0.0]; //边框宽度
//    [button setTitle:@"" forState:UIControlStateNormal];
//    [button.titleLabel setFont:[UIFont boldSystemFontOfSize:10]];
    [[self view] addSubview:button];
}

- (void)makeTableView:(CGRect)cgRect style:(UITableViewStyle)tableViewStyle
{
    
    uiTableView = [[UITableView alloc] initWithFrame:cgRect style:tableViewStyle];
	[uiTableView setFrame:cgRect];
    [uiTableView setBackgroundColor:[UIColor clearColor]];
    [uiTableView setScrollEnabled:YES];
	[[self view] addSubview:uiTableView];
    
	[uiTableView setDelegate:self];
	[uiTableView setDataSource:self];
    [uiTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
}

- (void)makeActivityIndicatorView:(CGRect)cgRect
{
    aWaitnet = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    [aWaitnet setBackgroundColor:[UIColor clearColor]];
	[aWaitnet setFrame:cgRect];
	[aWaitnet setHidden:NO];
	[aWaitnet setHidesWhenStopped:YES];
	[aWaitnet stopAnimating];
	[self.view addSubview:aWaitnet];
}

- (void)viewMoveToLeft:(NSInteger)moveType otherView:(UIView *)otview
{
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:[self view] cache:YES];
    

    if (moveType == SINGLE_LAYER_MOVE) {
        [[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    }
    else if (moveType == ALL_LAYER_MOVE) {
        [otview setFrame:CGRectMake(0.0, -480.0, 320.0, 480.0)];
        [[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    }
    
    [UIView setAnimationDelegate:self];
//    [UIView setAnimationDidStopSelector:@selector(viewMoveToLeftCallback)];
    [UIView commitAnimations];
}

//- (void)viewMoveToLeftCallback
//{
//}

- (void)viewMoveToRight:(NSInteger)moveType otherView:(UIView *)otview
{
    [otview setFrame:CGRectMake(0.0, -480.0, 320.0, 480.0)];
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:[self view] cache:YES];
    
    if (moveType == SINGLE_LAYER_MOVE) {
        [[self view] setFrame:CGRectMake(0.0, 480.0, 320.0, 480.0)];
    }
    else if (moveType == ALL_LAYER_MOVE) {
        [otview setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
        [[self view] setFrame:CGRectMake(0.0, 480.0, 320.0, 480.0)];
    }
    
    [UIView commitAnimations];
}

- (void)viewMoveToTop:(NSInteger)moveType otherView:(UIView *)otview
{
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:[self view] cache:YES];
    
    if (moveType == SINGLE_LAYER_MOVE) {
        [[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    }
    else if (moveType == ALL_LAYER_MOVE) {
        [otview setFrame:CGRectMake(0.0, 320.0, 320.0, 480.0)];
        [[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    }
    
    [UIView commitAnimations];
}

- (void)viewMoveToBottom:(NSInteger)moveType otherView:(UIView *)otview
{
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:[self view] cache:YES];
    
    if (moveType == SINGLE_LAYER_MOVE) {
        [[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    }
    else if (moveType == ALL_LAYER_MOVE) {
        [otview setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
        [[self view] setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    }
    
    [UIView commitAnimations];
}

- (void)backButtonCallback
{
}

- (void)switchAction
{
}

- (void)setSlideBlockFrame:(CGRect)cgrect
{
    slideBlock = [[UIImageView alloc] initWithFrame:cgrect];
    [slideBlock setBackgroundColor:[UIColor clearColor]];
    
    [[self view] addSubview:slideBlock];
}

- (void)setSlideBlockPosition:(CGRect)cgrect backgoundImageName:(NSString *)imageName
{
    [slideBlock setFrame:cgrect];
    [slideBlock setImage:[UIImage imageNamed:imageName]];
}

- (void)slideBlockOfButton:(CGRect)cgrect
{
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:slideBlock cache:YES];
    
    [slideBlock setFrame:cgrect];
    [UIView setAnimationDidStopSelector:@selector(setImageSlideBlock)];
    [UIView commitAnimations];
}

- (void)setImageSlideBlock:(NSString *)imageName
{
}

- (void)startAWaitnet
{
//    [aWaitnet setHidden:NO];
    [aWaitnet startAnimating];
}

- (void)stopAWaitnet
{
//    [aWaitnet stopAnimating];
}

- (void)addUnchangedImageView:(CGRect)cgRect imageName:(NSString *)imageName
{
    UIImageView *imageView = [[[UIImageView alloc] initWithFrame:cgRect] autorelease];
    [imageView setBackgroundColor:[UIColor clearColor]];
    [imageView setImage:[UIImage imageNamed:imageName]];
    /*
    CALayer *imageLayer=[imageView layer];
    [imageLayer setShadowOffset:CGSizeMake(4, 4)];  
    //[imageLayer setShadowRadius:theRadius];  
    [imageLayer setShadowOpacity:0.5];  
    [imageLayer setShadowColor:[UIColor redColor].CGColor]; 
//    theOffset(CGSize)为阴影偏移量,默认为(0, -3) 
//    theRadius(float)为阴影四角圆角半径,默认值为3 
//    theOpacity(float)为阴影透明度(取值为[0,1]) 
//    theColor(UIColor)为阴影颜色
     */
    [[self view] addSubview:imageView];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return nil;
}

@end
