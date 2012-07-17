//
//  CommonLayerSetReward.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "menuLayerLevelRule.h"

@implementation MenuLayerLevelRule
static MenuLayerLevelRule *menuLayerLevelRule = nil;

+ (MenuLayerLevelRule *) sharedManager
{
    if(!menuLayerLevelRule)
        menuLayerLevelRule=[[MenuLayerLevelRule alloc] init];
    return menuLayerLevelRule;
}

- (void)initSelfView
{
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    
    [self addUnchangedImageView:CGRectMake(5,40,470,275) imageName:@"L2white.png"]; 
    
    [titleLable setFrame:CGRectMake(220, 10, 100, 25)];
    [titleLable setText:@"等级规则"];
    [titleLable setBackgroundColor:[UIColor clearColor]];
    [titleLable setTextColor:[UIColor whiteColor]];
    [titleLable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:25]];
    
    
    [self makeTableView:CGRectMake(20.0, 40.0, 450.0, 275) style:UITableViewStylePlain];
    //uiTableView.separatorColor=[UIColor clearColor];
    uiTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    [uiTableView setBackgroundColor:[UIColor clearColor]];
    
   
}



- (void)backButtonCallback
{
    //NSLog(@"About back button test");
    //menuLayerHiddenLevelRule();
    [[MenuLayerLevelRule sharedManager] viewMoveToRight:SINGLE_LAYER_MOVE otherView:nil];
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
     return 1;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 300;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *SimpleTableIdentifier = @"SimpleTableIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    
       return cell;
}

@end
