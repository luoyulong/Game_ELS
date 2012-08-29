//
//  GameLayerPlayELS.h
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_GameLayerPlayELS_h
#define ThreeCard_GameLayerPlayELS_h


#include "GameEngine.h"
#include "ELSDefine.h"
#include "ELSSaveData.h"
#include "CCAssetBox.h"
#include "CCGameBox.h"
#include "ELSComm.h"
#include "AnimationLayerPlayELS.h"


#define MAX_PAUSE_STAGE	10
//为了保证AB两人的方块序列完全一致，事先生成好500个方块序列，500块后轮回取块









 

class GameLayerPlayELS: public GELayer
{
   // public:static GameLayerPlayELS *m_Instance;
public:
    GameLayerPlayELS();
    //static GameLayerPlayELS *GetInstance();
    
    ~GameLayerPlayELS();
    //void onEnter();
    
private:
    //void buttonCallback(GEObject* pObj);
    void GenRandomBlockQueue(long seed);
    void ResetELS(); 
    void ResetImg();
    void ResetTouch();
    void ResetGstat(int idx);
    void WriteScore();

    
    
    
    /*--------moveblock-------*/
    
    void  PlayActionBase(char *act, int index);				//基本的处理动作码函数，供touch，replay file，net等多个动作源调用
    MSTAT MoveBlk(MDIR dir, int idx, bool ai);				//移动方块
    void  NextBlk(int idx, bool ai, bool issave=false);		//生成下一个方块
    void  SaveBlk(int idx, bool ai);						//保存当前块，调出上次保存的块
    void  UpdateColHoleTop(int idx, int xs, int xe);		//更新每列的高度和空洞
    int	  TestDDown(int idx);								//用于绘制方块将要落下的虚影
    void  Attack(int idx, int lines, int space_seed);		//攻击对方
	int   ClearFullRows(int idx, bool ai);					//清除填满的行
    void  FireAchievementMovie(int idx, int achid);
    void Update(float dt);                                  //主循环更新
    void UpdateELS(int i);                                  //检测攻击,应用道具，更新各种stage
    inline void UpdatePTSystem(float dt);                               //更新粒子系统
    void ProcessOver(int idx, bool ai);

    void PlayAutoDownAction(float dt);//update 方块的自动下落
    void DumpELS(int idx, const char *msg);    
    
    void UpdateLevel(int oldscore, GSTAT *gp, int idx);
    bool UseItem(int idx, int itemidx,int target);                  //使用道具
    void  ProcessClearRow(int idx, bool ai, bool isLocalClear);
   public:
    void FallWithUpdate(int ,char *);//int repreasent index of mGS
    void FallWithUpdate_0();// repreasent mGS 0 
    void FallWithUpdate_1();
    void FallWithUpdate_2();//
    void FallWithUpdate_3();//
    
    
    void ClearRowWithUpdate(int,char *);
    void ClearRowWithUpdate_0(int i);
    
    
    //==================TestAchievement================
    void  TestAchievement(int clear=0);
    void  AddNewAchieve(int achieve, float percent);
    
    
    
    //================Items=================
    void ItemSubNLines(int idx, int lines);
    void ItemPlusNLines(int idx, int lines);
    void ItemCompress(int idx);
    void ItemHammer(int idx);
    void ItemShield(int idx);
    void ItemBlock(int idx);
    
    
    /*--------ELS NET---------*/
    	bool  isRobotGame();
    int   GetSeatIdByidx(int idx);
    int   GetIdxBySeatId(int seatid);
    void SendMaxCombo(int combonum, int comboidx);
    void GetTableString(char *buf);
    
    //==============PlayTouch==========
   
    void touchesBegan(GESet *pTouches, GEEvent *pEvent);
    void touchesMoved(GESet *pTouches, GEEvent *pEvent);
    void touchesEnded(GESet *pTouches, GEEvent *pEvent);
    
    
    bool  isMainArea(float x, float y);
    void PlayTouchAction();
    void PlayItemTouchAction();
    void PlayItemButton(GEObject *);
    char GetTouchAct();//捕捉获取屏幕动作
    bool TestKey(int state, int k);//检测按键，如果某些键盘按下不松开,可以自动连发...
                                    //兼容拖动手势,手势也会产生键盘事件
    int   touch_key(int state, int x, int y, bool setkeymap=true);
    int GetButtonRecItem(int itemIdx,int point);
    
    
    //=========for save=============
    void SaveAction();
    void RecordAction(int idx, const char *act);
    
    
    
    
    //===================ELSRender.h=================
    void  Render(CCRenderBox* mRender);
    bool  RenderNetInit(float dt);
    void  RenderGameFrame();
    void  RenderHighLight();
    void  RenderReplay();
    void RenderItem();

    void  RenderNet();
    void  RenderScoreBoard(float dt);								//绘制得分榜
    void  RenderHelp();										//绘制帮助
    void  RendMainNextSave();								//绘制主区域
   

    void  RenderBM(int dir);
    void  RenderMain(int idx, float x, float y, float s,CCRenderBox* );
    void  RenderAddScore();
    void  RenderWinLose(float dt);
    void  RenderNextSave(CCRenderBox* mRender);
    void  RenderScore();
    void  drawnum(int num, float x, float y, float angle=0, float xs=1.0f, float ys=1.0f);
    
    
    
    //===================单机的AI相关函数 相关文件:GameLayer_AI.cpp=================
    int   GetGridScore(int cx, int cy, int cf, int nf);		//布局评分
    char  GetAIAct();										//如果自动运行动作序列为空则计算生成指令序列，否则返回动作指令
    void  PlayAIAction(float dt);							//定期取AI动作并执行
    void  AI_F3(char *a, s8 cx, s8 cy, s8 cf, int *ms);
    void  AI_F2(char *a, s8 cx, s8 cy, s8 cf, int *ms);
    void  AI_F1(char *a, s8 cx, s8 cy, s8 cf, int *ms, 
                void (GameLayerPlayELS::*fs)(char *, s8, s8, s8, int *));
    
    
     //==================background================
    float get_adjy_bygrect(int idx);
    void  rns(s8, float, float, float, int, int, float,CCRenderBox* );

public:  
    vector<ITEMMOVE> mItemFly;
    int				mItemNum[10];//记录每局【本地】游戏中得到的道具，对战中的数据取自ELSSaveData中的g_item_num[10].

public:
     GEImage   *m_pPlayBoard;
    CCImage	*mBgT, *mBgTK, *mBgSTK, *mBgNS[2], *mItemBLK[11], *mBLK[11], *mNO[10], //mItemBLK[0]存放星星，1-10存放10个道具
    *mMask, *mGrid, *mGua2, *mBottom, *mItemBox, *mBigNO[4], *mItemSelected, 
    *mAdvProBarB, *mAdvProBarF, *mAdvProBarHL, 
    *mDlgBack, *mMarkPause, *mMarkScore, *mButtonResume, *mButtonHome, *mButtonRetry, *mButtonOptions, *mButtonSound[2],//对话框相关素材
    *mArrow, *mItemBar, *mYingBLK[10], *mCanBLK[10], *mBgTKSmall, *mInfoNum[10], *mBigStar[2],//冒险模式结束时显示的星星,[0]是正常的,[1]是发光的。
    *mCombo, *mAttack, *mClear, *mPause, *mWin, *mLose, *mSP,  *mFighter,
    *mMsgFt[3], *mMsgLevel[4], *mDialogRep, *mDialogPause, *mXunZhang[5],
    *mItemMsg[5], *mUnlock, *mReplay, *mRepSImg, *mDropBar, *mNameBk, *mNameSBk, 
    *mClear1, *mClear2, *mXuanZhuan[5], *mTopLight, *mConnect, *mConnDot, 
    *mCountDownBoxGlass, *m2ndhlight,//冒险模式下的倒计时框和水面上的闪光,倒数第二行的高光条
    *mFace, *mShield[4], *mItemLimitNotice, *mCanNotUseItem,//道具笑脸和盾牌,道具使用限制的提示
    *mNRBready, *mNRBback, *mNRBchange, *mNRready, *mNRnaozhong, *mNetItemBox,
    *mOBnext, *mOBsave, *mOBagain, *mOBback, *mOBchange, *mOBunLockAll,*mAchDialog, *mNetErrorBg, *mNetErrorFace,
    *mWLback, *mWLwin, *mWLlose, *mWLover, *mWLPover, *mWLstar, *mWLpack, *mWLinfo, *mLevelUp, *mFriendUI, *mBackUI, *mTempItem;

    
    
    float			mManTempo, mAiTempo, mHeartTempo;
    u8	mBlockQueue[MAXBLKQUEUE];//方块序列，每局预生成好，保证AB序列完全相同
    u32				mStage;
    int				mRandomSeed;
  
    u8				mBJIdx;//public是因为要根据此数判断STORE初始化的设置
    
    
    
   
    int			mRepSaved, mPauseStage, mNetInitStage;//mPauseStage用于显示对话框时的效果,mNetInitStage用于显示刚进入房间
    char			mActQueue[32];//AI动作序列:T-旋转 W-直落 D-下落 L-左移 R-右移 N-下一块 S-保存当前块	
      int				mItemChoose;//选中了哪个道具，0未选中，1-10对应10个道具，使用道具时用于识别手势。
    int				mItemTarget;//道具的对象，0-3表示4个玩家，4表示没有使用对象，道具处于待发状态。
    //mItemChoose和mItemTarget组合来完成道具的选择和定位目标功能。
    
    int				mItemLimit[10];//每局游戏中每种道具的使用限制。使用时-1，每局开始时重置。
    
    int				mShowItemLimitNoticeStageLeft;//游戏中道具限制的提示，显示的剩余帧数。
    
    
    //GEImage   *m_pPlayBoard;
    bool			ELS_PAUSE;
    bool			mNeed_process_record, mHelp, mAdventureWin,isSelfItem;
    
    
    //检测Achievement用
    int				m4LineCleared;
    //是否此局游戏的第一个道具

    
    //当前局是否已显示过hold的帮助
    int				hasShowHoldHelp;
    char			mNetDrawStr[256];
    
    //时间相关
    float			timeused;//冒险模式下计时
    
    //网络时间
    float			timeForScoreBoard, timeForAScoreBoard, timeForWaitReady, timeForConnect;
    //timeForScoreBoard用于积分榜的动画显示
    //timeForWaitReady则是用于用于网络等待时间，两者均在ResetELS()中初始化；

    
    
    
    
    hgeParticleSystem *mParticleSystem, *mParticleSystem2;//粒子系统
   
    int mCountDownTimeLeft;//用于游戏开始前的倒计时
    
    
    
    
    
    static CCFont       *mFont;
	static CCFont       *mBFont;
	static CCFont       *mLFont;
    
    
    
    
    
    
    inline long int randomZ(int stage, const char* tag)
    {
        if (g_fprand==NULL) 
        {
            //const char *actlog=GetDocPath("act.log");
            //g_fprand=fopen(actlog, "w");
        }
        long int r=random();
        
        if (g_fprand) 
        {
            //fprintf(g_fprand, "%d %s %ld\n", stage, tag, r);
            //fflush(g_fprand);
        }
        
        return r;
    }
    
    


};



#endif
