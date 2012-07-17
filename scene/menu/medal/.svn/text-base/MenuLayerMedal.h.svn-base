//
//  CommonLayerClass.h
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UITableLayer.h"
#import "GameStateShortConnect.h"
#import "GENet.h"

@interface MenuLayerMedal : UITableLayer
{
@private    
    int medalIdState;
    UIButton *refreshButton;
}

+ (MenuLayerMedal *) sharedManager;

- (void)showPlayTableButtonCallBack;
- (void)hiddenPlayTbleButtonCallBack;
- (void)reloadData;
- (void)isRewardBack:(id)sender;
- (void)sendGetMedal;

-(void)viewWillAppear;
-(NSString *)setTimeInt:(NSTimeInterval)timeSeconds setTimeFormat:(NSString *)timeFormatStr setTimeZome:(NSString *)timeZoneStr;
@end
