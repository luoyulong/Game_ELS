//
//  CommonLayerClass.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "backtoroomwrapper.h"
#import "MenuLayerNormalRoom.h"
#import "MenuLayerMatchRoom.h"

void backToNormalRoom()
{
    [[MenuLayerNormalRoom sharedManager] backToNormalRoom];
}

void backToMatchRoom()
{
    [[MenuLayerMatchRoom sharedManager] backToMatchRoom];
}



