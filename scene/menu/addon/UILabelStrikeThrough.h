//
//  UILabelStrikeThrough.h
//  GameBox
//
//  Created by Chao Li on 12-5-30.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//
/*
 *  用于在UILabel上画删除线
 */
#import <Foundation/Foundation.h>

@interface UILabelStrikeThrough : UILabel
{
    BOOL isWithStrikeThrough;
}

@property (nonatomic, assign) BOOL isWithStrikeThrough;
@end
