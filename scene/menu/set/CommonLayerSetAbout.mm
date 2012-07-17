//
//  CommonLayerSet.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CommonLayerSetAbout.h"

@implementation CommonLayerSetAbout
static CommonLayerSetAbout *commonLayerSetAbout = nil;

+ (CommonLayerSetAbout *) sharedManager
{
    if(!commonLayerSetAbout)
        commonLayerSetAbout=[[CommonLayerSetAbout alloc] init];
    return commonLayerSetAbout;
}

- (void)initSelfView
{
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    [backgroundView setImage:[UIImage imageNamed:@"Roomlist_BG.jpg"]];
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    
    //[self addUnchangedImageView:CGRectMake(5,40,470,275) imageName:@"二级页面_白背景.png"]; 
    
    [titleLable setFrame:CGRectMake(220, 10, 100, 25)];
    [titleLable setText:@"关于"];
    [titleLable setBackgroundColor:[UIColor clearColor]];
    [titleLable setTextColor:[UIColor whiteColor]];
    [titleLable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:25]];
    
    
    [self makeTableView:CGRectMake(30.0, 35.0, 450.0, 275) style:UITableViewStylePlain];
    //uiTableView.separatorColor=[UIColor clearColor];
    uiTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    [uiTableView setBackgroundColor:[UIColor clearColor]];
    
   
}



- (void)backButtonCallback
{
    //NSLog(@"About back button test");
    //menuLayerSetHiddenAbout();
    [[CommonLayerSetAbout sharedManager] viewMoveToRight:SINGLE_LAYER_MOVE otherView:nil];
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
    
    if (indexPath.section==0)
    {
        
        
        if (indexPath.row==0) 
        {
        
        UILabel *aboutLable = [[[UILabel alloc]initWithFrame:CGRectMake(0, 0, 420, 200)] autorelease];
        aboutLable.text =@"       北京时间5月29日消息，据雅虎体育报道，西部半决赛圣安东尼奥马刺与洛杉矶快船(微博)交战之时，有媒体曾爆料称马刺将为身处合同年的蒂姆-邓肯提供一份多年的续约合同。而在今天西部决赛首场比赛之后，邓肯也亲口确认了会继续留在马刺。";
        //aboutLable.textAlignment=UITextAlignmentLeft;
        aboutLable.backgroundColor = [UIColor clearColor];
        aboutLable.font =[UIFont systemFontOfSize:20];
        aboutLable.textColor=[UIColor whiteColor];
       
            
            
        aboutLable.lineBreakMode = UILineBreakModeWordWrap;
        aboutLable.numberOfLines = 0;
        [cell.contentView addSubview:aboutLable];
        
    //    UITextField *aboutText=[[[UITextField alloc] initWithFrame:CGRectMake(0, 0, 420, 300)] autorelease];
    //    aboutText.text =@"北京时间5月29日消息，据雅虎体育报道，西部半决赛圣安东尼奥马刺与洛杉矶快船(微博)交战之时";
    //    [cell.contentView addSubview:aboutText];
        }
        
    }
    return cell;
}

@end
