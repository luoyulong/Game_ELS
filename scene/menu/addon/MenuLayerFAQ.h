//
//  MenuLayerFAQ.h
//  GameBox
//
//  Created by Chao Li on 12-5-21.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

/* 还需要完成的工作： 
 * 1.设置输入字符限制(10<textNum<140)，输入字符过多或过少时会弹出提示窗口
 * 2.点击其他区域时隐藏键盘
 * 3.当弹出键盘时,画面自动上移
 * 已经完成1、2
 */
#import <Foundation/Foundation.h>
#import "UITableLayer.h"
@interface MenuLayerFAQ : UITableLayer<UITextFieldDelegate>
{    
    UIButton *feedBack;
    UIButton *FAQ;
    UIButton *sendOut;
    UITextField *m_textField;
    UITextView *m_help;
    UIAlertView *m_Tips;
}

@property (nonatomic,retain) UIButton *feedBack;
@property (nonatomic,retain)UIButton *FAQ;
@property (nonatomic,retain)UIButton *sendOut;
@property (nonatomic,retain)UITextField *m_textField;
@property (nonatomic,retain)UIAlertView *m_Tips;

-(IBAction)backgroundTap:(id)sender;
+ (MenuLayerFAQ *)sharedManager;
- (void) feedBackCallBack;
- (void) FAQCallBack;
- (void) sendOutCallBack;


@end
