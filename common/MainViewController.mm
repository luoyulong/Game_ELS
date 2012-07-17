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

#import "MainViewController.h"
#import "EAGLView.h"


@implementation MainViewController

@synthesize glView;


static MainViewController *sharedInstance;

+ (MainViewController *) getInstance 
{
	return sharedInstance;
}

/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad 
{
	sharedInstance = self;
	
	glView.animationInterval = 1.0 / 60.0;
	[glView startAnimation];
	
    [super viewDidLoad];
}



// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    //return (interfaceOrientation == UIInterfaceOrientationLandscapeRight);
    return NO ;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning]; // Releases the view if it doesn't have a superview
    // Release anything that's not essential, such as cached data
}


- (void)dealloc 
{
	[glView release];
    [super dealloc];
}


@end
