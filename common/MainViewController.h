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

#import <UIKit/UIKit.h>

@class EAGLView;

@interface MainViewController : UIViewController 
{
	IBOutlet EAGLView *glView;
}

@property (nonatomic, retain) EAGLView *glView;

+ (MainViewController *) getInstance;

@end
