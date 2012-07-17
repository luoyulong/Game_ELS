//
//  warningMessageWrapper.m
//  GameBox
//
//  Created by  on 12-5-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "warningMessageWrapper.h"
#import "NetErrorAlertView.h"

bool checkNetWork()
{
    return [[NetErrorAlertView sharedManager] checkNetWork];
}

void netErrorAlertShow()
{
    [[NetErrorAlertView sharedManager] alertViewShow];
}

