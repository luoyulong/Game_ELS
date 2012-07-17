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
#import <mach/mach.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import "EAGLView.h"
#import "CCGameBox.h"
#import "GameApp.h"
#import "GlobalData.h"
#import "MainViewController.h"
#import "Texture2D.h"
#import "CCImage.h"
#import "warningMessageWrapper.h"
#import "SNSWrapper.h"
#import "GameCenterwrapper.h"
#import "SimpleAudioEngine.h"
#import "GameScenePlayELS.h"

#define USE_DEPTH_BUFFER 1

#define MAX_TOUCHES     11
static GETouch *s_pTouches[MAX_TOUCHES];

@interface EAGLView ()
@property (nonatomic, assign) NSTimer *animationTimer;
- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;
@end

@implementation EAGLView

@synthesize animationTimer;
@synthesize animationInterval;
@synthesize gameCenterManager;
@synthesize iapManager;
@synthesize touchesIntergerDict;
@synthesize indexBitsUsed;

// You must implement this
+ (Class)layerClass 
{
	return [CAEAGLLayer class];
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder 
{
    if ((self = [super initWithCoder:coder])) 
    {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        EAGLSharegroup* group = context.sharegroup;
        context_t = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1 sharegroup:group];
        if (!context || ![EAGLContext setCurrentContext:context]) 
        {
            [self release];
            return nil;
        }
        
        int w = 320, h = 480;
        float ver = [[[UIDevice currentDevice] systemVersion] floatValue];
        // You can't detect screen resolutions in pre 3.2 devices, but they are all 320x480
        if (ver >= 3.2f)
        {
            UIScreen* mainscr = [UIScreen mainScreen];
            w = mainscr.currentMode.size.width;
            h = mainscr.currentMode.size.height;
        }
        printf("w=%d, h=%d\n", w, h);
        // Retina display detected
        if ((w == 640 && h == 960) || (h==768)) 
        {
            printf("RETINA\n");
            self.contentScaleFactor = 2.0;
            CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
            eaglLayer.contentsScale=2;
        }
        
        gameApp=NULL;
        iapManager=[[IAPManager alloc] init];
        touchDispatcher=NULL;
        mDirector=NULL;
        mTimerManager=NULL;
        touchesIntergerDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 4, NULL, NULL);
        indexBitsUsed = 0x00000000;
        framesPerSec = 0;
        fpsTime = 0.0;
        globalClock=0;
        
    }
   
    return self;
}

- (void)report_memory
{
    struct task_basic_info info;
    mach_msg_type_number_t size = sizeof(info);
    kern_return_t kerr = task_info(mach_task_self(),
                                   TASK_BASIC_INFO,
                                   (task_info_t)&info,
                                   &size);
    if( kerr == KERN_SUCCESS ) {
        NSLog(@"Memory in use (in bytes): %u", info.resident_size);
    } else {
        NSLog(@"Error with task_info(): %s", mach_error_string(kerr));
    }
}

- (void)drawView 
{
    /*打印内存占用情况
    static int debug_memory=0;
    if (debug_memory++%100==0)
    {
        NSLog(@"..........");
        [self report_memory];
    }*/
    
	//计算两帧之间的时间dt...
	CFTimeInterval time = CFAbsoluteTimeGetCurrent();
	float dt = time - mOldTime;
	mOldTime = time;
	globalClock+=dt;
    
    
    
    
    if (mDirector) {
        if (mDirector->m_iLoadInBackground==1) {
            mDirector->m_iLoadInBackground=100;
            NSLog(@"begin loading in back.....................");
            [self performSelectorInBackground: @selector(loadingInBackground:) withObject: context_t];
        }
        if (mDirector->m_iLoadInBackground==1000) {
            //读取资源完成后生成其他的场景
           // new GameScenePlayELS();
            new GameStateLogIn();
            new GameStateMainMenu();
            GameStateWaiting::GetInstance();
            GameStatePlay::GetInstance();
            GameScenePlayELS::GetInstance();
            //其他场景建立完成后转场，进入登陆界面
            printf("\n\n 进入第一个场景.\n\n");
            printf(" **************** 登录类型 %s **************** \n", g_config["login_type"]);
           
                GEDirector::GetInstance()->setCurrentScene("GameScenePlayELS");
            printf("");
            
            mDirector->m_iLoadInBackground=0;
        }
    }
    
	framesPerSec++;
	fpsTime+=dt;
	if (fpsTime>=1.0) {
        mDirector->setFPS(framesPerSec/fpsTime);
		framesPerSec=0;
		fpsTime=0.0f;
	}
	
    if (mTimerManager) {
        mTimerManager->_GETimerManager_Update_GETimer_List(dt);
    }
    
	[EAGLContext setCurrentContext:context];
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    
	CCRenderBox *renderBox = CCRenderBox::GetInstance();
	
    
    //以下开始展示
    /*--------------------------------------------------*/
    renderBox->RenderBegin();
	if (mDirector)
    {
        mDirector->Render(dt);
    }
	renderBox->RenderEnd();
	
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context presentRenderbuffer:GL_RENDERBUFFER_OES];
    
    //如果不注释掉这行，UITableView拖动时会很卡
//	[[NSRunLoop currentRunLoop] runUntilDate: [NSDate distantPast]];
}


#pragma mark -
#pragma mark Actions in background

- (void)loadingInBackground:(EAGLContext *) main_context
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	[EAGLContext setCurrentContext:main_context];
	if (mDirector) {
        ((mDirector->m_pLoadResourceTarget)->*(mDirector->m_pfuncLoadInBackground))();
        mDirector->m_iLoadInBackground=1000;
	}
	[pool release];
	return;
}

- (void)layoutSubviews 
{
	if(gameApp==NULL)
	{
		[EAGLContext setCurrentContext:context];
		[self destroyFramebuffer];
		[self createFramebuffer];
		[self engineStart];
        
        //get engine singltons.
        mTimerManager = GETimerManager::GetInstance();
		touchDispatcher = GETouchDispatcher::GetInstance();
		mDirector = GEDirector::GetInstance();
		//mDirector->setDeviceOrientation(DeviceOrientationLandscapeLeft);
      //  mDirector->setDeviceOrientation(DeviceOrientationLandscapeLeft);
        mDirector->setShowFPS(true);
		//gameCenterManager = GEGameCenterManager::GetInstance();

		//script test,don't open now.
//        const char *vpath = GetPath("main.lua", NULL);
//        CLuaManager::GetInstance()->DoScriptFile(vpath); 
        
		gameApp = new GameApp();
        
		[self drawView];
	}
}

- (void)engineStart
{
    // init low level support
    CCGameBoxInit();
    
    [SimpleAudioEngine sharedEngine];
    
    // init game engine
    GETouchDispatcher::GetInstance();
    GETimerManager::GetInstance();
    GEDirector::GetInstance();
    //gameCenterManager = GEGameCenterManager::GetInstance();
    
    // init script engine
    CLuaManager::GetInstance();
    ObjectManager::GetInstance();
    GEScriptDisplay::GetInstance();   //used for script
    GEScriptUi::GetInstance();
    GEScriptTransition::GetInstance();
    GEScriptRuntime::GetInstance();
}

- (BOOL)createFramebuffer 
{
	glGenFramebuffersOES(1, &viewFramebuffer);
	glGenRenderbuffersOES(1, &viewRenderbuffer);
	
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
	[context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
	
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	
	if (USE_DEPTH_BUFFER) 
	{
		glGenRenderbuffersOES(1, &depthRenderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
		glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
	}
    
	if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) 
	{
		NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
		return NO;
	}
	
	return YES;
}

- (void)destroyFramebuffer 
{	
	glDeleteFramebuffersOES(1, &viewFramebuffer);
	viewFramebuffer = 0;
	glDeleteRenderbuffersOES(1, &viewRenderbuffer);
	viewRenderbuffer = 0;
	
	if(depthRenderbuffer) 
	{
		glDeleteRenderbuffersOES(1, &depthRenderbuffer);
		depthRenderbuffer = 0;
	}
}

- (void)startAnimation 
{
	self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:animationInterval 
                                                           target:self 
                                                         selector:@selector(drawView) 
                                                         userInfo:nil 
                                                          repeats:YES];
	mOldTime = CFAbsoluteTimeGetCurrent();
}

- (void)stopAnimation 
{
	self.animationTimer = nil;
}

- (void)setAnimationTimer:(NSTimer *)newTimer 
{
	[animationTimer invalidate];
	animationTimer = newTimer;
}

- (void)setAnimationInterval:(NSTimeInterval)interval 
{	
	animationInterval = interval;
	if (animationTimer) 
	{
		[self stopAnimation];
		[self startAnimation];
	}
}

-(void) removeUsedIndexBit:(int) index
{
	if (index < 0 || index >= MAX_TOUCHES) {
		return;
	}
    unsigned int temp = 1 << index;
    temp = ~temp;
    indexBitsUsed &= temp;
}

-(int) getUnUsedIndex
{
    int i;
    int temp = indexBitsUsed;
    
    for (i = 0; i < MAX_TOUCHES; i++) {
        if (! (temp & 0x00000001)) {
            indexBitsUsed |= (1 <<  i);
            return i;
        }
        temp >>= 1;
    }
    
    // all bits are used
    return -1;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event 
{
    	if (touchDispatcher) {
		GESet mSet;
		GETouch *pTouch;
		for (UITouch *touch in touches) {
			NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
			int unUsedIndex = 0;
			
			// it is a new touch
			if (! index) {
				unUsedIndex = [self getUnUsedIndex];
				
				// The touches is more than MAX_TOUCHES ?
				if (unUsedIndex == -1) {
					return;
				}
				
				pTouch = s_pTouches[unUsedIndex] = new GETouch();
				float x = 2.0*[touch locationInView: [touch view]].x;
				float y = 2.0*[touch locationInView: [touch view]].y;
				pTouch->SetTouchInfo(0, x, y, unUsedIndex);
				mSet.addObject(pTouch);
				CFDictionaryAddValue(touchesIntergerDict, touch, [NSNumber numberWithInt:unUsedIndex]);				
			}
		}
		
		if (mSet.count() == 0)
			return;
		touchDispatcher->touchesBegan(&mSet,NULL);
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event 
{
//	UITouch *touch = [touches anyObject];	
	if (touchDispatcher) {
		GESet mSet;
		for (UITouch *touch in touches) {
			NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
			if (! index) {
				// if the index doesn't exist, it is an error
				return;
			}
			
			GETouch *pTouch = s_pTouches[[index intValue]];
			if (! pTouch) {
				// if the pTouch is null, it is an error
				return;
			}
			
			float x = 2.0*[touch locationInView: [touch view]].x;
			float y = 2.0*[touch locationInView: [touch view]].y;
			pTouch->SetTouchInfo(0, x, y, pTouch->id());
			
			mSet.addObject(pTouch);
		}
		
		touchDispatcher->touchesMoved(&mSet, NULL);
	}
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	if (touchDispatcher) {
		GESet mSet;
		for (UITouch *touch in touches) {
            NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
            if (! index) {
                // if the index doesn't exist, it is an error
                return;
            }
			
			GETouch *pTouch = s_pTouches[[index intValue]];
			if (! pTouch) {
				// if the pTouch is null, it is an error
				return;
			}
			
			float x = 2.0*[touch locationInView: [touch view]].x;
			float y = 2.0*[touch locationInView: [touch view]].y;
			pTouch->SetTouchInfo(0, x, y, pTouch->id());
			
			mSet.addObject(pTouch);
			CFDictionaryRemoveValue(touchesIntergerDict, touch);
			pTouch->release();
			s_pTouches[[index intValue]] = NULL;
			[self removeUsedIndexBit:[index intValue]];
		}
		
		touchDispatcher->touchesEnded(&mSet,NULL);
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	GESet mSet;
	for (UITouch *touch in touches) {
		NSNumber *index = (NSNumber*)CFDictionaryGetValue(touchesIntergerDict, touch);
		if (! index) {
			// if the index doesn't exist, it is an error
			return;
		}
        
		GETouch *pTouch = s_pTouches[[index intValue]];
		if (! pTouch) {
			// if the pTouch is null, it is an error
			return;
		}
        
		float x = 2.0*[touch locationInView: [touch view]].x;
		float y = 2.0*[touch locationInView: [touch view]].y;
		pTouch->SetTouchInfo(0, x, y, pTouch->id());
		
		mSet.addObject(pTouch);
		CFDictionaryRemoveValue(touchesIntergerDict, touch);
		pTouch->release();
		s_pTouches[[index intValue]] = NULL;
		[self removeUsedIndexBit:[index intValue]];
	}
	
	touchDispatcher->touchesCancelled(&mSet, NULL);
}

- (void)dealloc 
{
	[self stopAnimation];	
	CFRelease(touchesIntergerDict);
	if ([EAGLContext currentContext] == context) 
	{
		[EAGLContext setCurrentContext:nil];
	}
	delete gameApp;
	CCGameBoxDestroy();
	[context release];
	[super dealloc];
}

/*
- (void)viewScreenshot:(UIView *)uiView
{
    UIGraphicsBeginImageContext(uiView.frame.size);
    [self.layer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *viewImage = UIGraphicsGetImageFromCurrentImageContext(); 
    UIGraphicsEndImageContext();
    Texture2D *tex = [[Texture2D alloc] initWithImage: viewImage];
    CCTexture *texture = new CCTexture([tex name], tex.contentSize.width, tex.contentSize.height, tex.pixelsWide, tex.pixelsHigh);
    CCImage viewccimg = CCImage(texture);
}*/

@end
