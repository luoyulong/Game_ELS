//
//  CommonLayerSet.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GlobalData.h"
#import "CommonLayerSet.h"
#import "CommonLayerSetAbout.h"
#import "ImageCache.h"
#import "WrapperSetAbout.h"
#import "SimpleAudioEngineWrapper.h"

@implementation CommonLayerSet

static CommonLayerSet *commonLayerSet = nil;

+ (CommonLayerSet *) sharedManager
{
    if(!commonLayerSet)
        commonLayerSet=[[CommonLayerSet alloc] init];
    return commonLayerSet;
}

- (void)initSelfView
{
    NSLog(@"INIT COMMONLAYERSET .......................................");
    [[self view] setFrame:CGRectMake(0.0, 480.0, 320, 480.0)];
    
    
    //@"http://i0.sinaimg.cn/ent/402/2009/0701/U2398P28T402D1F12485DT20120525111419.jpg"
    /*ImageCache *imgcache=[[ImageCache alloc] init];
    [imgcache getImageByUrl:nil 
           defaultImageName:@"二级页面_底.jpg" 
                  imageView:backgroundView];
    [imgcache release];*/
    
    [backgroundView setImage:[UIImage imageNamed:@"L2back.jpg"]];
    
    //tableView
    [self makeTableView:CGRectMake(0.0, 40.0, 480.0, 280) style:UITableViewStyleGrouped];
    [uiTableView setBackgroundColor:[UIColor clearColor]];
    
    //layer title
    [self addUnchangedImageView:CGRectMake(0,0,480,50) imageName:@"L2title.png"];
    
    [titleLable setFrame:CGRectMake(220, 10, 100, 25)];
    [titleLable setText:@"设置"];
    [titleLable setBackgroundColor:[UIColor clearColor]];
    [titleLable setTextColor:[UIColor whiteColor]];
    [titleLable setFont:[UIFont fontWithName:@".Helvetica NeueUI" size:25]];
    [[self view] addSubview:titleLable];
    
    [backButton setBackgroundImage:[UIImage imageNamed:@"Roomlist_backBtn.png"] forState:UIControlStateNormal];
    [[self view] addSubview:backButton];    
    
    m_filecfg=new FileConfigure();
//    m_filecfg->ReadOption();
//  FileConfigure   filecfg=FileConfigure();
//  filecfg.ReadOption();
    
}



- (void)backButtonCallback
{
    //NSLog(@"value of %s is %s", "abc", g_config["abc"]);
    //NSLog(@"back button test*************");
    //menuLayerSetHidden();
    //iDemoAppDelegate *ad = (iDemoAppDelegate *)[[UIApplication sharedApplication] delegate];
    //[[CommonLayerSet sharedManager] viewMoveToRight:ALL_LAYER_MOVE otherView:[ad.viewController view]];
    SimpleAudioPlayEffect("audio_btn_click.m4a");
    [[CommonLayerSet sharedManager] viewMoveToRight:SINGLE_LAYER_MOVE otherView:nil];
}

- (void)showPlayTableButtonCallBack
{
    
}

- (void)hiddenPlayTbleButtonCallBack
{
    
}


- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section{
    if (section==0) {
        return @"声音与震动";
    } else {
        return @"通用";
    }
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    //NSLog(@"view f h i %d", section);
    UIView* myView = [[[UIView alloc] init] autorelease];

    //myView.backgroundColor = [UIColor redColor];
    UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(30, 15, 90, 24)];
    titleLabel.textColor=[UIColor whiteColor];
    titleLabel.backgroundColor = [UIColor clearColor];

    if (section==0) {
        
        titleLabel.text=@"声音与震动";
    } else {
        
        titleLabel.text=@"通用";
    }
    
    [myView addSubview:titleLabel];
    [titleLabel release];
    return myView;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 50.0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 1.0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    if (section==0) {
        return 2;
    }
    else return 3;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}




//设置cell背景图
- (void)g_soundmySwitch
{
    
    if (g_soundmySwitch.on==YES) {
        
        NSLog(@"0 section 0 cell is YES");  
        sprintf(g_config["sound"], "1");
        m_filecfg->WriteOption();
    }
    else {
        NSLog(@"0 section 0 cell is NO");        
        sprintf(g_config["sound"], "0");
        m_filecfg->WriteOption();
        
    }
   
}
- (void)g_shockmySwitch
{
    if (g_shockmySwitch.on==YES) {
        
        NSLog(@"0 section 1 cell is YES");        
        sprintf(g_config["shock"], "1");
        m_filecfg->WriteOption();
        
    }
    else {
        NSLog(@"0 section 1 cell is NO");        
        sprintf(g_config["shock"], "0");
        m_filecfg->WriteOption();
        
    }
   
}

- (void)g_automaticsitmySwitch
{
    if (g_automaticsitmySwitch.on==YES) {
        
        NSLog(@"1 section 0 cell is YES");        
        sprintf(g_config["autosit"], "1");
        m_filecfg->WriteOption();
        
    }
    else {
        NSLog(@"1 section 0 cell is NO");        
        sprintf(g_config["autosit"], "0");
        m_filecfg->WriteOption();
        
    }
   
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSLog(@"get common layer cell...............");
    static NSString *SimpleTableIdentifier = @"SimpleTableIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: SimpleTableIdentifier];
    for (UIView *view in cell.contentView.subviews) [view removeFromSuperview];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:SimpleTableIdentifier] autorelease];  
    }
    
    cell.selectionStyle = UITableViewCellSelectionStyleNone;    
    
    [uiTableView indexPathForCell:cell];
    if (indexPath.section==0) {
        
        if (indexPath.row==0) {
            //[cell.contentView setBackgroundColor:[UIColor redColor]];
            //[cell.contentView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"settingroundbtn1.png"]]];
            UIImageView *uiImageView=[[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 460, 46)] autorelease];
            [uiImageView setImage:[UIImage imageNamed:@"settingroundbtn1.png"]];
            [cell.contentView addSubview:uiImageView];
            
            UILabel *roomIdLable = [[[UILabel alloc]initWithFrame:CGRectMake(23, 10, 100, 24)] autorelease];
            roomIdLable.text =@"声音";
            roomIdLable.backgroundColor = [UIColor clearColor];
            [cell.contentView addSubview:roomIdLable];
            
            //1.UISwitch的初始化
            g_soundmySwitch = [[[ UISwitch alloc]initWithFrame:CGRectMake(360.0,10.0,0.0,0.0)] autorelease];  
            [cell.contentView addSubview:g_soundmySwitch];//添加到父视图          
            
                      
            if (strcmp(g_config["sound"], "1")==0) {
                //printf("is or not ");
                g_soundmySwitch.on = YES;
            }
            else {
                g_soundmySwitch.on = NO;
            }
            
            //3.UISwitch事件的响应
            [g_soundmySwitch addTarget:self action:@selector(g_soundmySwitch) forControlEvents:UIControlEventValueChanged];
            
             //NSLog(@"on or off is ％c", mySwitch);
                           
        }
        if (indexPath.row==1) {
            //[cell.contentView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"settingroundbtn2.png"]]];
            UIImageView *uiImageView=[[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 460, 46)] autorelease];
            [uiImageView setImage:[UIImage imageNamed:@"settingroundbtn2.png"]];
            [cell.contentView addSubview:uiImageView];
            
            UILabel *roomIdLable = [[[UILabel alloc]initWithFrame:CGRectMake(23, 10, 100, 24)] autorelease];
            roomIdLable.text =@"震动";
            roomIdLable.backgroundColor = [UIColor clearColor];
            [cell.contentView addSubview:roomIdLable];
            
            g_shockmySwitch = [[[ UISwitch alloc]initWithFrame:CGRectMake(360.0,10.0,0.0,0.0)] autorelease];  
            [cell.contentView addSubview:g_shockmySwitch];//添加到父视图  
        }
        //2.设置UISwitch的初始化状态
        //g_shockmySwitch.on = YES;//设置初始为ON的一边
        
        if (strcmp(g_config["shock"], "1")==0) {
            g_shockmySwitch.on =YES;
        }
        else {
            g_shockmySwitch.on =NO;
        }
        //3.UISwitch事件的响应
        [g_shockmySwitch addTarget:self action:@selector(g_shockmySwitch) forControlEvents:UIControlEventValueChanged];

    }
    
    

    
    if (indexPath.section==1) {
        
        if (indexPath.row==0) {
            //[cell.contentView setBackgroundColor:[UIColor clearColor]];
            //[cell.contentView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"settingroundbtn1.png"]]];
            
            
            UIImageView *uiImageView=[[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 460, 46)] autorelease];
            [uiImageView setImage:[UIImage imageNamed:@"settingroundbtn1.png"]];
            [cell.contentView addSubview:uiImageView];
            
            UILabel *roomIdLable = [[[UILabel alloc]initWithFrame:CGRectMake(23, 10, 200, 24)] autorelease];
            roomIdLable.text =@"进房间自动坐下";
            roomIdLable.backgroundColor = [UIColor clearColor];
            [cell.contentView addSubview:roomIdLable];
            
            g_automaticsitmySwitch = [[ UISwitch alloc]initWithFrame:CGRectMake(360.0,10.0,0.0,0.0)];  
            [cell.contentView addSubview:g_automaticsitmySwitch];//添加到父视图  
            
            //2.设置UISwitch的初始化状态
            //g_automaticsitmySwitch.on = YES;//设置初始为ON的一边
            
            if (strcmp(g_config["autosit"], "1")==0) {
                g_automaticsitmySwitch.on =YES;
            }
            else {
                g_automaticsitmySwitch.on =NO;
            }
            //3.UISwitch事件的响应
            [g_automaticsitmySwitch addTarget:self action:@selector(g_automaticsitmySwitch) forControlEvents:UIControlEventValueChanged];
        }
        if (indexPath.row==1) {
            //[cell.contentView setBackgroundColor:[UIColor clearColor]];
            //[cell.contentView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"settingroundbtn3.png"]]];
            
            UIImageView *uiImageView=[[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 460, 46)] autorelease];
            [uiImageView setImage:[UIImage imageNamed:@"settingroundbtn3.png"]];
            [cell.contentView addSubview:uiImageView];

            
            UILabel *roomIdLable = [[[UILabel alloc]initWithFrame:CGRectMake(23, 10, 100, 24)] autorelease];
            roomIdLable.text =@"清楚缓存";
            roomIdLable.backgroundColor = [UIColor clearColor];
            [cell.contentView addSubview:roomIdLable];
            
        }
        if (indexPath.row==2) {
            //[cell.contentView setBackgroundColor:[UIColor clearColor]];
            //[cell.contentView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"settingroundbtn2.png"]]];
            UIImageView *uiImageView=[[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 460, 46)] autorelease];
            [uiImageView setImage:[UIImage imageNamed:@"settingroundbtn2.png"]];
            [cell.contentView addSubview:uiImageView];

            
            UILabel *roomIdLable = [[[UILabel alloc]initWithFrame:CGRectMake(23, 10, 100, 24)] autorelease];
            roomIdLable.text =@"关于";
            roomIdLable.backgroundColor = [UIColor clearColor];
            [cell.contentView addSubview:roomIdLable];
            
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            
           
            
        }
       

    }

  
   
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath   
{  
    if (indexPath.section == 1 && indexPath.row==2)   
    {
        
        //NSLog(@"%d %d", indexPath.section, indexPath.row);
        //[[CommonLayerSetAbout sharedManager] viewMoveToLeft:SINGLE_LAYER_MOVE otherView:nil];
        [tableView deselectRowAtIndexPath:indexPath animated:YES];//选中后的反显颜色即刻消失
        menuLayerShowAbout();
    }
}

//- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
//{
//        [tableView deselectRowAtIndexPath:indexPath animated:YES];//选中后的反显颜色即刻消失
//}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 46;
}

@end
