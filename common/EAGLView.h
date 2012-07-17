//------------------------------------------------------------------------
//
//	CCGameBox is a game development library for iPhone and iPod Touch.
//	Licensed under the BSD license, see LICENSE in root for details.
//	Copyright (c) 2009 James Hui (a.k.a. Dr.Watson)
//	For latest updates, please visit http://www.cocoachina.com
//
//------------------------------------------------------------------------

#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import "GameCenterManager.h"
#import "IAPManager.h"
#import "GameEngine.h"
#import "GameStateLogin.h"
#import "GameStateShortConnect.h"
#import "GameStateMainMenu.h"
#import "GameStatePlay.h"
#import "GameStateWaiting.h"

class GameApp;
class GETouchDispatcher;
class GEDirector;
class GameStateLogin;
class GameStateShortConnect;
class GameStateMainMenu;
class GameStatePlay;
class GameStateWaiting;

@interface EAGLView : UIView

{
	GameCenterManager* gameCenterManager;
	IAPManager*		   iapManager;
@private
    EAGLContext *context, *context_t;
	GLint backingWidth;
	GLint backingHeight;
    GLuint viewRenderbuffer, viewFramebuffer;
    GLuint depthRenderbuffer;
	
	NSTimer *animationTimer;
	NSTimeInterval animationInterval;
	CFTimeInterval mOldTime;
	
	GameApp *gameApp;
    
	GETouchDispatcher       *touchDispatcher;
	GEDirector              *mDirector;
	GETimerManager          *mTimerManager;
	CFMutableDictionaryRef  touchesIntergerDict;
	unsigned int            indexBitsUsed;
	int                     framesPerSec;
	float                   fpsTime;
    int globalClock;//全局时钟 至少能用1万小时
}

@property (nonatomic, retain) GameCenterManager *gameCenterManager;
@property (nonatomic, retain) IAPManager        *iapManager;
@property (nonatomic, assign) NSTimeInterval    animationInterval;

@property(readonly) CFMutableDictionaryRef touchesIntergerDict;
@property(readwrite) unsigned int indexBitsUsed;

- (void) startAnimation;
- (void) stopAnimation;
- (void) drawView;
- (void) engineStart;
@end



