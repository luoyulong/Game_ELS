//
//  CommonLayerHelpScrollView.h
//  ThreeCard
//
//  Created by Chao Li on 12-6-6.
//  Copyright (c) 2012年 GameSnow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UITableLayer.h"
@interface CommonLayerHelpScrollView : UITableLayer<UIScrollViewDelegate>
{
    UIScrollView *helpScrollView;
    UIPageControl *helpPageControl;
    UILabel *pageNumber;
}

@property (retain, nonatomic) UIScrollView *helpScrollView;
@property (retain, nonatomic) UIPageControl *helpPageControl;

+ (CommonLayerHelpScrollView *) sharedManager;

- (void)changePage:(id)sender;
- (void)backButtonCallback;
- (void)switchAnimation:(UIView *)otherView;
@end
