//------------------------------------------------------------------------
//
//	CCGameBox is a game development library for iPhone and iPod Touch.
//
//	Licensed under the BSD license, see LICENSE in root for details.
// 
//	Copyright (c) 2009 James Hui (a.k.a. Dr.Watson)
// 
//	For latest updates, please visit http://www.cocoachina.com
//
//------------------------------------------------------------------------

#import "AppDelegate.h"
#import "EAGLView.h"
#import "MenuLayerMatchRoom.h"
#import "MenuLayerNormalRoom.h"
#import "CommonLayerSet.h"
#import "CommonLayerSetAbout.h"
#import "MenuLayerUserDetail.h"
#import "MenuLayerMedal.h"
#import "MenuLayerLevelRule.h" 
//MenuLayerAddon
#import "MenuLayerMsg.h"
#import "MenuLayerFAQ.h"
#import "MenuLayerActs.h"
#import "MenuLayerFriend.h"
#import "MenuLayerStore.h"
//Continuous Login Reward
#import "LoginLayerReward.h"
//CommonLayerHelp
#import "CommonLayerHelp.h"
#import "CommonLayerHelpScrollView.h"
@implementation iDemoAppDelegate

@synthesize window;
@synthesize viewController;

- (void) startup 
{
}

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{
    [application setApplicationIconBadgeNumber:0];
    [application cancelAllLocalNotifications];
    
	NSLog(@"finish launching...");
    // 读取用户设置文件
    FileConfigure *m_filecfg=new FileConfigure();
    m_filecfg->ReadOption();
    free(m_filecfg);
    hash_map<const char *, char *>::iterator itr;
    for(itr=g_config.begin(); itr!=g_config.end(); itr++)
    {
        printf("%s: %s\t|\n", itr->first, itr->second);
    }
    
	[window addSubview:[viewController view]];
    
    menuLayerMatchRoom = [MenuLayerMatchRoom sharedManager];    
    [window addSubview:[menuLayerMatchRoom view]];
    
    menuLayerNormalRoom = [MenuLayerNormalRoom sharedManager];
    [window addSubview:[menuLayerNormalRoom view]];
    
    commonLayerSet     = [CommonLayerSet sharedManager];
    [window addSubview:[commonLayerSet view]];
    
    commonLayerSetAbout     = [CommonLayerSetAbout sharedManager];
    [window addSubview:[commonLayerSetAbout view]];
    
    menuLayerUserDetail   =[MenuLayerUserDetail sharedManager];
    [window addSubview:[menuLayerUserDetail view]];
    
    menuLayerMedal   =[MenuLayerMedal sharedManager];
    [window addSubview:[menuLayerMedal view]];
    
    menuLayerLevelRule   =[MenuLayerLevelRule sharedManager];
    [window addSubview:[menuLayerLevelRule view]];
    
    //MenuLayerAddon
    menuLayerMsg = [MenuLayerMsg sharedManager];
    [window addSubview:[menuLayerMsg view]];
    menuLayerActs = [MenuLayerActs sharedManager];
    [window addSubview:[menuLayerActs view]];
    
    menuLayerFAQ = [MenuLayerFAQ sharedManager];
    [window addSubview:[menuLayerFAQ view]];
    menuLayerStore = [MenuLayerStore sharedManager];
    [window addSubview:[menuLayerStore view]];
    menuLayerFriend = [MenuLayerFriend sharedManager];
    [window addSubview:[menuLayerFriend view]];
	
    //Continuous Login Reward
    longinLayerReward = [LoginLayerReward sharedManager];
    [window addSubview:[longinLayerReward view]];
    
    //CommonLayerHelp
    commonLayerHelp = [CommonLayerHelp sharedManager];
    [window addSubview:[commonLayerHelp view]];
    
    //CommonLayerHelpScrollView
    commonLayerHelpScrollView = [CommonLayerHelpScrollView sharedManager];
    [window addSubview:[commonLayerHelpScrollView view]];
   
    [window makeKeyAndVisible];
	//[self startup];
}

- (void)applicationWillResignActive:(UIApplication *)application 
{
	//glView.animationInterval = 1.0 / 5.0;
	//[OpenFeint applicationWillResignActive];
}


- (void)applicationDidBecomeActive:(UIApplication *)application 
{
	//glView.animationInterval = 1.0 / 60.0;
	//[OpenFeint applicationDidBecomeActive];
}

- (void)applicationWillTerminate:(UIApplication *)application {
	//[[NSUserDefaults standardUserDefaults] synchronize]; // Add for OpenFeint
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    sleep(2);
    NSLog(@"进入后台运行");
    
    UILocalNotification *notification=[[[UILocalNotification alloc] init] autorelease];
	if (notification!=nil) 
	{
        
		NSDate *now=[[[NSDate alloc] init] autorelease];
        notification.fireDate = [now dateByAddingTimeInterval:10];
		notification.timeZone=[NSTimeZone defaultTimeZone];
        
		notification.alertBody = [NSString stringWithFormat:NSLocalizedString(@"好久没玩扎金花",nil)];
        [notification setApplicationIconBadgeNumber:1];
        
		[[UIApplication sharedApplication]   scheduleLocalNotification:notification];
	}
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
//    [[NetErrorAlertView sharedManager] checkNetWork];
    

    
    NSLog(@"进入前台运行");
    [application setApplicationIconBadgeNumber:0];
    [application cancelAllLocalNotifications];
}

- (void)dealloc
{
	[window release];
	[viewController release];
    [menuLayerMatchRoom release];
    [menuLayerMsg release];
	[super dealloc];
}

@end
