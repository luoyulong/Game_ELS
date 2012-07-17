/*
 *  ELSTouchKey.h
 *  GameBox
 *
 *  Created by xing zip on 11-2-17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameLayerPlayELS.h"
#include <dirent.h>
#include <sys/types.h>
 


#define MAIN_TOUCH_Y 440
#define MAIN_TOUCH_X 290

#define ELS_TOUCH_STATE_COUNT 6
#define ITEM_LIMIT_NOTICE_STAGE  180
typedef enum _els_touch_state {
	ELSTOUCH_PLAY,
	ELSTOUCH_MENU,
	ELSTOUCH_OVER,
	ELSTOUCH_NETS,
	ELSTOUCH_NETR,
	ELSTOUCH_ITEM
} ELSTOUCHSTATE;

#define ELS_PLAY_KEY_COUNT 8
typedef enum _els_play_key {
    ELSKEY_PLAY_MENU,
	ELSKEY_PLAY_STORE,
    ELSKEY_PLAY_SAVE,
    ELSKEY_PLAY_DROP,
    ELSKEY_PLAY_DOWN,   
    ELSKEY_PLAY_LEFT,
    ELSKEY_PLAY_RIGHT,
    ELSKEY_PLAY_TURN
} ELSKEYPLAY;
const static int BUTTON_RECT_PLAY[ELS_PLAY_KEY_COUNT][4]=
{
	//{200,342,239,380},
	{  0,  0,100, 60},
	//{200,303,239,341},
	{101,  0,200, 60},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};
char g_key_play[ELS_PLAY_KEY_COUNT];

#define ELS_MENU_KEY_COUNT 4
typedef enum _els_menu_key {
    ELSKEY_MENU_RESUME,
    ELSKEY_MENU_BACK,
	ELSKEY_MENU_TUTORIAL,
	ELSKEY_MENU_MUTE
} ELSKEYMENU;
const static int BUTTON_RECT_MENU[ELS_MENU_KEY_COUNT][4]=
{
	{120,150,200,213},
	{120,215,200,274},
	{120,276,200,338},
	{120,340,200,400}
};
char g_key_menu[ELS_MENU_KEY_COUNT];

#define ELS_OVER_KEY_COUNT 3
typedef enum _els_over_key {
	ELSKEY_OVER_SAVE,
	ELSKEY_OVER_BACK,
	ELSKEY_OVER_AGAIN
} ELSKEYOVER;
const static int BUTTON_RECT_OVER[ELS_OVER_KEY_COUNT][4]=
{
	{50, 330,120,400},
	{125,330,195,400},
	{200,330,270,400}
};
char g_key_over[ELS_OVER_KEY_COUNT];

#define ELS_NETS_KEY_COUNT 4
typedef enum _els_nets_key {
	ELSKEY_NETS_LV1,
	ELSKEY_NETS_LV2,
	ELSKEY_NETS_LV3,
	ELSKEY_NETS_FRIEND
} ELSKEYNETS;
const static int BUTTON_RECT_NETS[ELS_NETS_KEY_COUNT][4]=
{
	{50,48, 435, 95},
	{50,108,435,155},
	{50,168,435,215},
	{50,228,435,275}
};
char g_key_nets[ELS_NETS_KEY_COUNT];

#define ELS_NETR_KEY_COUNT 3
typedef enum _els_netr_key {
	ELSKEY_NETR_READY,
	ELSKEY_NETR_REENTER,
	ELSKEY_NETR_BACK
} ELSKEYNETR;
const static int BUTTON_RECT_NETR[ELS_NETR_KEY_COUNT][4]=
{
	{65, 123, 160, 153},
	{65, 163, 160, 193},
	{65, 198, 160, 228}
};
char g_key_netr[ELS_NETR_KEY_COUNT];

#define ELS_ITEM_KEY_COUNT 10
const static int BUTTON_RECT_ITEM[ELS_ITEM_KEY_COUNT][4]=
{	
	{ 18, 445,  67, 480},
	{ 68, 445, 127, 480},
	{128, 445, 187, 480},
	{188, 445, 247, 480},
	{999, 999, 999, 999},//不显示
	{248, 445, 307, 480},
	
	{295, 170, 320, 230},
	{295, 231, 320, 290},
	{295, 291, 320, 350},
	{295, 351, 320, 410},
};
char g_key_item[ELS_ITEM_KEY_COUNT];

const static int g_key_count[ELS_TOUCH_STATE_COUNT]=
{ELS_PLAY_KEY_COUNT, ELS_MENU_KEY_COUNT, ELS_OVER_KEY_COUNT, 
    ELS_NETS_KEY_COUNT, ELS_NETR_KEY_COUNT, ELS_ITEM_KEY_COUNT};

const static void *g_key_point[ELS_TOUCH_STATE_COUNT]=
{BUTTON_RECT_PLAY, BUTTON_RECT_MENU, BUTTON_RECT_OVER, 
    BUTTON_RECT_NETS, BUTTON_RECT_NETR, BUTTON_RECT_ITEM};

void *g_key_map[ELS_TOUCH_STATE_COUNT]=
{g_key_play, g_key_menu, g_key_over, g_key_nets, g_key_netr, g_key_item};

typedef enum _els_key {
    ELSKEY_BACK,
    ELSKEY_RESTART,
    ELSKEY_PAUSE,
    ELSKEY_DOWN,
    ELSKEY_TURN1,
    ELSKEY_LEFT,
    ELSKEY_TURN,
    ELSKEY_DROP,
    ELSKEY_HOLD,
    ELSKEY_RIGHT,
    ELSKEY_HELP
} ELSKEY;

static float g_first_touch[2];   //纪录手指刚按下的点
static float g_last_touch[2];    //纪录上一次move事件的点,move不一定水平滑动
static float g_last_x;           //纪录上一次水平滑动的x坐标
static float g_last_y;           //纪录上一次水平滑动的y坐标
static bool  g_need_drop, g_need_hold;
static float g_end_touch[2];     //纪录手指离开时的点

static int   g_began_play, g_began_item;


void GameLayerPlayELS::touchesBegan(GESet *pTouches, GEEvent *pEvent)
{
    
    GETouch *touch=(GETouch *)pTouches->anyObject();
    float touch_x,touch_y;
    GEPoint p=touch->locationInView(0);
    touch_x=p.x;
    touch_y=p.y;
        
    
    if(mHelp)
		return;
	
	/*if (ELS_PAUSE) 
	{
		int k=touch_key(ELSTOUCH_MENU, touch_x, touch_y);
		printf("menu touch:%d\n", k);
		return;
	}*/
	
	if (mElsMode!=ELS_MODE_NET) 
	{
		if (mElsMode==ELS_MODE_REPLAY) {
			//replay over
			if(g_recact_index>=g_recact_count+1)
			{  
				if(touch_y<410 && touch_y>=320 && touch_x<160 && touch_x>60)
				{
					//mApp->mTransform=9;
					
					return;
				}
				if(touch_y<410 && touch_y>=320 && touch_x>160 && touch_x<300)
				{
					mTheme=mRepTheme;
					ResetELS();
					return;
				}
			}
		}
		if(mGS[0].game_over || mGS[1].game_over)
		{
			int k=touch_key(ELSTOUCH_OVER, touch_x, touch_y);
			printf("over touch:%d\n", k);
			return;
		}
	}
	/*else 
	{
		if (GetNetState()==NET_STATE_GAMEOVER) 
		{
			int k=touch_key(ELSTOUCH_OVER, touch_x, touch_y);
			printf("over touch:%d\n", k);
			return;
		}
		if (GetNetState()==NET_STATE_ERROR) {
			DisconnectGame(true);
		}
	}
	
	if(mElsMode == ELS_MODE_NET && (GetNetState()==NET_STATE_ENTERROOMOK || GetNetState()==NET_STATE_WAITREADY || GetNetState()==NET_STATE_READYOK)) {
		int k=touch_key(ELSTOUCH_NETR, touch_x, touch_y);
		printf("wait net ready touch:%d\n", k);
		return;
	}
	
	if(mElsMode == ELS_MODE_NET && GetNetState()==NET_STATE_INIT) {
		int k=touch_key(ELSTOUCH_NETS, touch_x, touch_y);
		printf("wait net select touch:%d\n", k);
		return;
	}
	if (mElsMode == ELS_MODE_NET && GetNetState()==NET_STATE_LOGINOK && isFriendRequest()) {
		char of[20][64];
		int ofcount=GetOnlineFriend(of);
		int k=touch_key_selfriend(ofcount, touch_x, touch_y);
		if (touch_y>=440) {
            mApp->backFromNet = 1;
			mApp->mTransform=9;
			
            
			mApp->isNewTable = 1;
			mApp->score0store1 = -1;
		}
		else
		{
			if (k>=0)
			{
				mApp->isNewTable = 1;
				mApp->score0store1 = -1;
				EnterFriendRoom(k);
			}
			else {
				if (touch_y<400) {
					printf("Refresh table...\n");
					
					mApp->isNewTable = 1;
					mApp->score0store1 = -1;
					InitNet();
					EnterRoom(0, true);
				}
			}
		}
	}
	*/
    
    
    //设置初始坐标
    g_first_touch[0] = touch_x;
    g_first_touch[1] = touch_y;
    g_last_touch[0]  = touch_x;
    g_last_touch[1]  = touch_y;
    g_last_x         = touch_x;
	g_last_y         = touch_y;
	g_need_drop      = false;
	g_need_hold		 = false;
	
	//主区域内准备检测手势,清空键盘状态表
    if(isMainArea(touch_x, touch_y))
	{
        printf("主控区域  \n\n");
        memset(g_key_play, 0, sizeof(g_key_play));
	}
	//虚拟键盘区检测某个虚拟键被按下
    else
    {  
		//防止touchbegan时就触发menu和store影响游戏操作...
        g_began_play=touch_key(ELSTOUCH_PLAY, touch_x, touch_y, false);
		g_began_item=touch_key(ELSTOUCH_ITEM, touch_x, touch_y);
		if (g_began_play==-1) {
			memset(g_key_play, 0, sizeof(g_key_play));
		}
    }
   
}

void GameLayerPlayELS::touchesEnded(GESet *pTouches, GEEvent *pEvent)
{ 
    GETouch *touch=(GETouch *)pTouches->anyObject();
    float touch_x,touch_y;
    GEPoint p=touch->locationInView(0);
    touch_x=p.x;
    touch_y=p.y;
    

    
    if(g_need_drop)
	{
		g_key_play[ELSKEY_PLAY_DROP]=KEY_PRESSED;
		g_need_drop=false;
	}
	if(g_need_hold)
	{
		g_key_play[ELSKEY_PLAY_SAVE]=KEY_PRESSED;
		g_need_hold=false;
	}
	
	//检测mItemTarget
	//每次Touch结束时检测模mItemTarget，如果此时mItemChoose！=0,则检测到目标后立即使用道具。
	if (mItemChoose != 0) {
		if (mElsMode == ELS_MODE_NET && mItemLimit[mItemChoose-1]<=0) {
			mShowItemLimitNoticeStageLeft=ITEM_LIMIT_NOTICE_STAGE;
			mItemChoose=0;
			mItemTarget=4;
			return;
		}
		if (mElsMode == ELS_MODE_SINGLE || mElsMode == ELS_MODE_AI || mElsMode == ELS_MODE_NET)
			if (touch_x > mainx && touch_x < mainx+188 && touch_y < MAIN_TOUCH_Y) 
				mItemTarget = 0;
		if (mElsMode == ELS_MODE_AI || mElsMode == ELS_MODE_NET)
			if (touch_x > 215 && touch_x < 280 && touch_y > 50 && touch_y < 170)
				mItemTarget = 1;
		
		if (mElsMode == ELS_MODE_NET) {
            if (touch_x > 215 && touch_x < 280 && touch_y > 190 && touch_y < 310)
                mItemTarget = 2;
            if (touch_x > 215 && touch_x < 280 && touch_y > 330 && touch_y < 450)
                mItemTarget = 3;
		}
		char tmp[7];
		if (mItemTarget>=0 && mItemTarget<4 && mItemChoose>0 && mItemChoose<=6) {//防守道具1-6可以给任何人使用
			if(mItemTarget==0)
			{
				//给自己使用道具，直接执行...
				sprintf(tmp, "I%d%d%02x", GetSeatIdByidx(0), GetSeatIdByidx(mItemTarget), mItemChoose);
				RecordAction(0, tmp);
				UseItem(0, mItemChoose, mItemTarget);
			}
			else {
				//给别人使用道具...
				sprintf(tmp, "Y%d%d%02x", GetSeatIdByidx(0), GetSeatIdByidx(mItemTarget), mItemChoose);
				RecordAction(0, tmp);
				if (mElsMode==ELS_MODE_NET && !isRobotGame()) {
					mItemTarget=4;
					mItemChoose=0;
					//如果是网络对战模式则不执行,而是等到回馈后再执行，保证时序...
				}else {
					UseItem(0, mItemChoose, mItemTarget);
				}
			}
            
		}
		if (mItemTarget >0 && mItemTarget<4 && mItemChoose>6 && mItemChoose<=10) {//攻击道具6-10只能给敌人使用，不能给自己使用，防止误操作。
			sprintf(tmp, "Y%d%d%02x", GetSeatIdByidx(0), GetSeatIdByidx(mItemTarget), mItemChoose);
			RecordAction(0, tmp);
			if (mElsMode==ELS_MODE_NET) {
				mItemTarget=4;
				mItemChoose=0;
				printf("use item online..\n\n");
				//如果是网络对战模式则不执行,而是等到回馈后再执行，保证时序...
			}else {
				UseItem(0, mItemChoose, mItemTarget);
			}
		}
	}
	
    //主区域检测旋转,模拟按了一下旋转键
    if(isMainArea(g_first_touch[0], g_first_touch[1]))
    {
        g_end_touch[0]=touch_x;
        g_end_touch[1]=touch_y;
		
        float dx = fabs(g_end_touch[0]-g_first_touch[0]);
        float dy = fabs(g_end_touch[1]-g_first_touch[1]);
		
        if(dx<=15 && dy<=15)
        {
			printf("ELS_PAUSE=%d\n", ELS_PAUSE);
            g_key_play[ELSKEY_PLAY_TURN]=KEY_PRESSED;
        }
        return;
    }
	
	//虚拟键盘区检测某个虚拟键被按下
	if (!isMainArea(touch_x, touch_y)) {
        int k1=touch_key(ELSTOUCH_PLAY, touch_x, touch_y, false);
		if (k1!=-1 && k1==g_began_play) 
			touch_key(ELSTOUCH_PLAY, touch_x, touch_y);
	}
    
    
    
}
void GameLayerPlayELS::touchesMoved(GESet *pTouches, GEEvent *pEvent)
{
    
    GETouch *touch=(GETouch *)pTouches->anyObject();
    float touch_x,touch_y;
    GEPoint p=touch->locationInView(0);
    touch_x=p.x;
    touch_y=p.y;
    
    
    if(!isMainArea(g_first_touch[0], g_first_touch[1]))
	{
		//如果移动进入了主区域，模拟一个touchesbegan
		if(isMainArea(touch_x, touch_y))
		{
			//设置初始坐标
			g_first_touch[0] = touch_x;
			g_first_touch[1] = touch_y;
			g_last_touch[0]  = touch_x;
			g_last_touch[1]  = touch_y;
			g_last_x         = touch_x;
			g_last_y         = touch_y;
			g_need_drop      = false;
			
			//主区域内准备检测手势,清空键盘状态表
			memset(g_key_play, 0, sizeof(g_key_play));
		}
        return;
	}
	/*
	if (mElsMode == ELS_MODE_NET && GetNetState()==NET_STATE_SELFOVER) 
	{
		return;
	}*/
	
    //处理手势
	float dx, dx_drag, dy, dy_drag;
	
    dx      = touch_x - g_last_touch[0];
    dx_drag = touch_x - g_last_x;
    dy      = touch_y - g_last_touch[1];
	dy_drag = touch_y - g_last_y;
    g_last_touch[0]=touch_x;
    g_last_touch[1]=touch_y;
	
    //拖动
    if(dy<=12)
    {
        //距离上次拖动,又拖动了16个像素以上,模拟按了一下右移键
        if(dx_drag>18)
        {
            g_key_play[ELSKEY_PLAY_RIGHT]=KEY_PRESSED;
            g_last_x = touch_x;
			g_need_drop=false;
			g_need_hold=false;
        }
        //左移键盘
        if(dx_drag<-18)
        {
            g_key_play[ELSKEY_PLAY_LEFT]=KEY_PRESSED;
            g_last_x = touch_x;
			g_need_drop=false;
			g_need_hold=false;
        } 
		if(dy_drag>18)
		{
			g_key_play[ELSKEY_PLAY_DOWN]=KEY_PRESSED;
			g_last_y = touch_y;
			g_need_drop=false;
			g_need_hold=false;
		}
    }
	//下扫直落
    if(dy>12)
    {
        if(dx<=18 && dx>=-18)
        {
			g_need_drop=true;
        }
        g_last_x = touch_x;
    }
	//上扫暂存
	if(dy<-12)
	{
		if(dx<=18 && dx>=-18)
        {
			g_need_hold=true;
        }
        g_last_x = touch_x;
	}

}


int GameLayerPlayELS::touch_key(int state, int x, int y, bool setkeymap)
{
	int kcount=g_key_count[state];
	int (*BUTTON_RECT)[][4];
	char *keymap;
	
	BUTTON_RECT = (int (*)[][4])g_key_point[state];
	keymap = (char *)g_key_map[state];
	
    for(int i=0;i<kcount;i++)
    {
        if(x>=(*BUTTON_RECT)[i][0] && y>=(*BUTTON_RECT)[i][1] &&
           x<=(*BUTTON_RECT)[i][2] && y<=(*BUTTON_RECT)[i][3])
		{
			if (state == ELSTOUCH_PLAY && mCountDownTimeLeft > 0.0) {
				printf("play state and countdown...\n");
				return -1;
			}
			if(setkeymap)
				keymap[i]=KEY_PRESSED;
            return i;
		}
    }
    return -1;
}

inline bool GameLayerPlayELS::isMainArea(float x, float y)
{
	
    for(map<string,obstacles>::iterator ai=obstacles_set.begin();ai!=obstacles_set.end();ai++)
    {
        if(x<ai->second.pos_x-ai->second.w/2)
            break;
        if(x>(ai->second.pos_x+ai->second.w/2))
            break;
        if(y<ai->second.pos_y-ai->second.h/2)
            break;
        if(y>(ai->second.pos_y+ai->second.h/2))
            break;
        return false;
    }
        
        
    return  true;
     if (y<=MAIN_TOUCH_Y && y>=0 && x<MAIN_TOUCH_X)
     {		
         return true;
     }
    
   
}




void GameLayerPlayELS::PlayItemTouchAction()
{
	//处理使用道具
	int n;
	for (int i=0; i<10; i++) {
		if (mElsMode==ELS_MODE_NET)
			n = g_item_num[i];
		else 
			n = mItemNum[i];
		
		if (TestKey(ELSTOUCH_ITEM, i)) {
			if (n>0) {
				if (mItemChoose==(i+1)) {//再次点击,取消操作
					mItemChoose=0;
				}
				else {
					mItemChoose=i+1;//选中道具
				}
			}
			else
				mItemChoose=0; //若点了一下数量为0的道具，则取消之前选中的道具
		}		
	}
}




bool GameLayerPlayELS::TestKey(int state, int k)
{	

	char *p;
	p = (char *)g_key_map[state];
    if(p[k])
    {
        //虚拟键盘或者拖动手势产生的键盘按下快速弹起事件
        if(p[k]==KEY_PRESSED)
        {
            p[k]=0;
            return true;
        }
    }
      return false;
}

char GameLayerPlayELS::GetTouchAct()
{
	/*if (mCountDownTimeLeft > 0.0)
		return 'N';
	*/
	char ret=0;
	
	if(TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_MENU))
	{
		if (ELS_PAUSE)
			return 'X';
		ELS_PAUSE=true;
		mPauseStage = MAX_PAUSE_STAGE;
		//mApp->TraceLog("PBM"); //Play_Button_Menu
	}
	
	if(TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_STORE))
	{
		//mApp->AddState(mApp->mGameStates[GAME_STATE_STORE]);
		//mApp->TraceLog("PBS"); //Play_Button_Store
	}
	
	//保存
	if(TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_SAVE)) {
		ret='S';
		//mApp->TraceLog("PGS"); //Play_Gesture_S
	}
	//旋转
	if(TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_TURN))
		ret='T';
	//直下
	if(TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_DROP)) {
		ret='W';
		//mApp->TraceLog("PGW"); //Play_Gesture_W
	}
	//右移
	if (TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_RIGHT))
		ret='R';
	//左移
	if(TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_LEFT))
		ret='L';
	//下移
	if (TestKey(ELSTOUCH_PLAY, ELSKEY_PLAY_DOWN))		
		ret='D';
    if (ret!=0) {
        //printf("act is -------- %c\n",ret);
    }
    
	return ret;
}


int GameLayerPlayELS::GetButtonRecItem(int itemIdx,int point)
{
	if (itemIdx>=0 && itemIdx<10 && point>=0 && point<4)
		return BUTTON_RECT_ITEM[itemIdx][point];
	return -1;
}
void GameLayerPlayELS::PlayTouchAction()
{	
	//if (mCountDownTimeLeft > 0.0) //倒计时还没有结束，不接受动作
	//	return;
	
	char ret;
	if ((ret=GetTouchAct())) {
		if(mElsMode!=ELS_MODE_REPLAY)
		{
			char ts[4];
			ts[0]=ret, ts[1]=0;
			if (mGS[0].grect_stage>180) {
				//当检测到直落指令后，在grect_stage没减小到180的时候，不允许其他指令
				printf("GRECT deny action!!!");
				return;
			}
			//RecordAction(0, ts);
			PlayActionBase(ts, 0);
		}
	}
}

void GameLayerPlayELS::ResetTouch()
{
	g_first_touch[0]=g_first_touch[1]=0;
	g_last_touch[0]=g_last_touch[1]=0;
	g_last_x=g_last_y=0;
	g_end_touch[0]=g_end_touch[1]=0;
	g_began_play=g_began_item=0;
	g_need_drop=false;
	g_need_hold=false;
	for (int i=0; i<ELS_TOUCH_STATE_COUNT; i++) {
		printf("RESET TOUCH:sizeof(keymap[%d])=%lu(%d)\n", i, sizeof(g_key_map[i]), g_key_count[i]);
		memset(g_key_map[i], 0, g_key_count[i]);
	}
}
