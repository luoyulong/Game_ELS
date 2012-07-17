//
//  CommonLayerHelpWrapper.m
//  ThreeCard
//
//  Created by Chao Li on 12-6-6.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#include "CommonLayerHelp.h"
#include "CommonLayerHelpScrollView.h"
#import "AppDelegate.h"

void commonLayerHelpShow()
{
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[CommonLayerHelp sharedManager] viewMoveToLeft:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void commonLayerHelpHide()
{
    iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[CommonLayerHelp sharedManager] viewMoveToRight:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void commonLayerHelpScrollViewShow(int page)
{
    //iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    [[CommonLayerHelpScrollView sharedManager].helpScrollView setContentOffset: CGPointMake(480*page, 0) animated:NO];
    
    //[[CommonLayerHelpScrollView sharedManager] switchAnimation:[ad.viewController view]];    
    /*
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.7];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:[CommonLayerHelp sharedManager].view cache:YES];
        
    [[CommonLayerHelp sharedManager].view setFrame:CGRectMake(0.0, -480.0, 320.0, 480.0)];
    [[CommonLayerHelpScrollView sharedManager].view setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    
    
    [UIView commitAnimations];
    */
    [[CommonLayerHelpScrollView sharedManager].view setFrame:CGRectMake(-320.0, 0.0, 320.0, 480.0)];
    [UIView beginAnimations:@"animationID" context:nil];//开始一个动画块，第一个参数为动画块标识 
    
    [UIView setAnimationDuration:1.0f];//设置动画的持续时间  
    
    [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];  
    //设置动画块中的动画属性变化的曲线，此方法必须在beginAnimations方法和commitAnimations，默认即为UIViewAnimationCurveEaseInOut效果。
    
    [UIView setAnimationRepeatAutoreverses:NO];//设置是否自动反转当前的动画效果  
    
    //[UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:[CommonLayerHelp sharedManager].view cache:YES];
    [UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:[CommonLayerHelpScrollView sharedManager].view cache:YES];
    //[self.view.superview sendSubviewToBack:self.view];
    //[[self view] setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    //[[CommonLayerHelp sharedManager].view setFrame:CGRectMake(0.0, -480.0, 320.0, 480.0)];
    [[CommonLayerHelpScrollView sharedManager].view setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    //[[CommonLayerHelp sharedManager].view.superview exchangeSubviewAtIndex:14 withSubviewAtIndex:13];//页面翻转 
    [UIView commitAnimations];//提交动画 

    //[[CommonLayerHelpScrollView sharedManager] viewMoveToLeft:ALL_LAYER_MOVE otherView:[ad.viewController view]];
}

void commonLayerHelpScrollViewHide()
{
    //iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    //[[CommonLayerHelpScrollView sharedManager] viewMoveToRight:ALL_LAYER_MOVE otherView:[ad.viewController view]];
    
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.4];
    [UIView setAnimationTransition:UIViewAnimationTransitionNone forView:[CommonLayerHelpScrollView sharedManager].view cache:YES];
    
    [[CommonLayerHelpScrollView sharedManager].view setFrame:CGRectMake(0.0, 480.0, 320.0, 480.0)];
    [[CommonLayerHelp sharedManager].view setFrame:CGRectMake(0.0, 0.0, 320.0, 480.0)];
    
    [UIView commitAnimations];

}