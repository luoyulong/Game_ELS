//
//  SinaLogInWrapper.m
//  GameBox
//
//  Created by  on 12-4-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIDevice+IdentifierAddition.h"
#import "DeviceIDWrapper.h"
#import "NSString+MD5Addition.h"

const char *GetUniqueDeviceIdentifier()
{
    return [[[UIDevice currentDevice] uniqueDeviceIdentifier] UTF8String];
}

const char *GetDeviceType()
{
    return [[UIDevice currentDevice].model UTF8String];
}


