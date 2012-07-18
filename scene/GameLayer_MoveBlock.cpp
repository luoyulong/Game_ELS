//
//  GameLayer_MoveBlock.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameLayerPlayELS.h"


#define blksize		36.0f

//出现宝石的几率,越大越不容易出现
static int GOLDENLUCK  =  50;
static int ItemLimit[10] = {5,5,5,5,5,5,5,5,5,5};
inline bool cmp_score(const HSCORE *a, const HSCORE *b)
{
	return a->score > b->score;
}


void GameLayerPlayELS::PlayAutoDownAction(float dt)
{
	if (mCountDownTimeLeft > 0.0)//倒计时还没有结束
		return;
	
	char ret=0;
	//自然下落...
#if ELS_AUTO
	u8 tmpmode=(mElsMode==ELS_MODE_REPLAY?mElsRepMode:mElsMode);
	float tdtime;
	if (tmpmode==ELS_MODE_NET) 
		tdtime=DOWN_TIME_NET[mGS[0].level];
	else 
		tdtime=DOWN_TIME[mGS[0].level];
	
    
    
    
	if(mManTempo>tdtime)
	{
		ret='D';
		mManTempo=0;
		char ts[4];
		ts[0]=ret,ts[1]=0;
        if (((AnimationLayerPlayELS *)Annimationlayer)->fallstat[0]>=0) {
            return;//当检测到直落指令后，在grect_stage没减小到180的时候，不允许其他指令
        }
		//RecordAction(0, ts);
		PlayActionBase(ts, 0);
	}
	else {
		mManTempo+=dt;
	}
#endif
}

void GameLayerPlayELS::DumpELS(int idx, const char *msg)
{
	if (g_fprand) {
		fprintf(g_fprand, "<%d.%d.%d> %s: top:%d", idx, mGS[idx].block_index, mStage, msg,  mGS[idx].top_line);
		fprintf(g_fprand, "(%d %d %d %d %d %d %d %d %d %d)", 
				mGS[idx].col_top[0],mGS[idx].col_top[1],mGS[idx].col_top[2],mGS[idx].col_top[3],
				mGS[idx].col_top[4],mGS[idx].col_top[5],mGS[idx].col_top[6],mGS[idx].col_top[7],
				mGS[idx].col_top[8],mGS[idx].col_top[9]);
		fprintf(g_fprand, " full_row_count=%d (%d %d %d %d)\n", mGS[idx].full_rows_count, 
				mGS[idx].fullrows[0],mGS[idx].fullrows[1],mGS[idx].fullrows[2],mGS[idx].fullrows[3]);
		
		fflush(g_fprand);
	}
}
void GameLayerPlayELS::UpdateLevel(int oldscore, GSTAT *gp, int idx)
{
	int oldlv=oldscore/350;
	int newlv=gp->score/350;
	//printf("UL:os=%d, ns=%d, ol=%d, nl=%d\n", oldscore, gp->score, oldlv, newlv);
	if (newlv>oldlv && gp->level<19) 
	{
		gp->level++;
		if (idx==0) 
			gp->levelup_stage=SET_LEVELUP_STAGE;
		if (g_options[1]) 
		{
			//printf("LEVEL UP WAV........\n");
			//mSND->PlaySound(mWavLevelup);
		}
	}
	return;
}

//消除满行,clear_stage是为了实现消行动态闪烁效果
int GameLayerPlayELS::ClearFullRows(int idx, bool ai)
{   
	int i, j, n, ret=0;
	GSTAT *gp;
	
	gp = &mGS[idx];
 
	if(gp->clear_stage==(SET_CLEAR_STAGE-REND_CLEAR_STAGE))
	{
		ret=1;
		bool isItemFullRows=false;
		if (gp->full_rows_count>100) {//道具造成的消行，不加分，不加攻击
			isItemFullRows=true;
		}
		if(gp->full_rows_count%100)
		{   
			//检测4行连消的情况
			if (idx==0)
				TestAchievement(mGS[0].full_rows_count%100);
			//清除满行
			DumpELS(idx, "CLEAR");
			for(n=0;n<gp->full_rows_count%100;n++)
			{
				for(i=gp->fullrows[n];i>=0;i--)
					for(j=0;j<HENG;j++) 
					{
						int tmpitemtype=gp->grid[i][j+2];
						if((tmpitemtype>150) && i==gp->fullrows[n])
						{
							tmpitemtype=tmpitemtype%150;
							gp->score+=5;
							UpdateLevel(gp->score-5, gp, idx);
							if (idx == 0) {
								//增加新ITEMMOVE到vector
								ITEMMOVE new_itemmove;
								new_itemmove.itemtype = tmpitemtype;
								new_itemmove.startx   =	mainx+10+(j+1)*blksize;//for retina
								new_itemmove.starty   = mainy+100+i*blksize;//for retina
								new_itemmove.endx	  = (GetButtonRecItem(tmpitemtype-1, 0)+GetButtonRecItem(tmpitemtype-1, 2))-5;
								new_itemmove.endy	  = (GetButtonRecItem(tmpitemtype-1, 1)+GetButtonRecItem(tmpitemtype-1, 3));
								new_itemmove.item_move_stage = 60;
								mItemFly.push_back(new_itemmove);
							}
						}
						if(i)
						{
							if(gp->grid[i-1][j+2]>100 || gp->grid[i-1][j+2]==0)
							{
								if(!(gp->grid[i][j+2]<10 && gp->grid[i][j+2]>0))
									gp->grid[i][j+2]=gp->grid[i-1][j+2];
							}
							else
								if(!(gp->grid[i][j+2]<10 && gp->grid[i][j+2]>0))
									gp->grid[i][j+2]=0;
						}
						else
						{
							if(!(gp->grid[i][j+2]<10 && gp->grid[i][j+2]>0))
								gp->grid[i][j+2]=0;
						}
					}
				gp->fullrows[n]=0;
			}
			UpdateColHoleTop(idx, 2, 11);
			if (!ai && !isItemFullRows) {
				gp->attack[0]=gp->full_rows_count-1;
				if(gp->combo>=3) gp->attack[0]++;
				gp->attack[1]=gp->block_index;
			}
			DumpELS(idx, "AFTER CLEAR");
		}
		gp->full_rows_count=0;
	} 
	//解锁下一个试炼阵法
	if (mElsMode==ELS_MODE_SINGLE && mBJIdx!=0) {
		//printf("unlock:bjidx=%d topline=%d unbmp=%d\n", mBJIdx, gp->top_line, g_unlock_bmp);
		if (gp->top_line<=2 && gp->unlock_stage==0) {
			gp->unlock_stage=MAX_UNLOCK_STAGE;
			WriteScore();
			if (g_options[5]==0 && g_unlock_bmp>=16) {
				//没有解锁就玩到16关
			}
			else if (g_unlock_bmp==mBJIdx && mBJIdx<=MAX_BMP_COUNT ) {//如果没有解锁，则不允许玩16关以后的关卡。
				g_unlock_bmp++;
			}
		}
	}
	return ret;
}





//主更新循环调用GameLayerPlayELS::Update
void GameLayerPlayELS::Update(float dt)
{
	mStage++;
	
	if (mPauseStage>0)
		mPauseStage--;
	
	/*if (mElsMode==ELS_MODE_NET) 
	{
        //发送心跳信号...
		DoSendHeartBeat(dt);
		
        //游戏如果是PLAYING或者GAMEOVER状态，进入代码段
		if (!PlayWaitNetAction()) 
		{
            if (mRandomSeed==0) {
                mRandomSeed=GetNetSeed();
                if (mRandomSeed) 
                {
                    GenRandomBlockQueue(mRandomSeed);
                    ResetGstat(0);
                    ResetGstat(1);
                    ResetGstat(2);
                    ResetGstat(3);
                    //mstage清零，防止网络replay文件回放时，前面一大段空白...
                    mStage=0;
                }
            }
            PlayMenuTouchAction();
            if(GetNetState()==NET_STATE_GAMEOVER) return;
            PlayAutoDownAction(dt);
            PlayTouchAction();
            PlayItemTouchAction();
            if (isRobotGame()) PlayAIAction(dt);
            PlayNetAction();
        }
	}
	*/
    if(mElsMode==ELS_MODE_SINGLE)
    {
        //PlayMenuTouchAction();  这里要替代为菜单层
        if(ELS_PAUSE) return;
        if(mGS[0].game_over || mGS[1].game_over) return;
        PlayAutoDownAction(dt);
		PlayTouchAction();
		PlayItemTouchAction();
    }
    /*
    if (mElsMode==ELS_MODE_AI) {
        PlayMenuTouchAction();
        if(ELS_PAUSE) return;
        if(mGS[0].game_over || mGS[1].game_over) return;
        PlayAutoDownAction(dt);
		PlayTouchAction();
		PlayItemTouchAction();
        PlayAIAction(dt);
    }*/
    /*
    if (mElsMode==ELS_MODE_REPLAY) {
        PlayMenuTouchAction();
        if(ELS_PAUSE) return;
        PlayReplayAction();
        if(mGS[0].game_over || mGS[1].game_over) return;
		PlayTouchAction();
    }
    */
    UpdatePTSystem(dt);
	UpdateELS(0);
	UpdateELS(1);
	UpdateELS(2);
	UpdateELS(3);
	
	//非网络模式下,第600帧判断是否需要显示hold的帮助
	/*if (mStage>600 && mElsMode!=ELS_MODE_NET && mElsMode!=ELS_MODE_REPLAY && hasShowHoldHelp==0 && g_options[8]>=0) { //不和hold的提示冲突
		if (g_options[9]>0) {
			g_options[9]*=-1;//暂时标记为-1，以使GameStateReward识别显示道具相关的帮助
			//暂停游戏，并增加reward-state
			//ELS_PAUSE=true;
			GameState* rr=mApp->mGameStates[GAME_STATE_REWARD];
			if (mElsMode==ELS_MODE_AI || (mElsMode==ELS_MODE_SINGLE && mBJIdx!=0)) {
				rr->mArrowX = 362;
				rr->mArrowY = 160;
			}
			else if(mElsMode==ELS_MODE_SINGLE && mBJIdx==0) {
				rr->mArrowX = 460;
				rr->mArrowY = 160;
			}
			mApp->AddState(mApp->mGameStates[GAME_STATE_REWARD]);
		}
		hasShowHoldHelp=1;
	}*/
}

inline void GameLayerPlayELS::UpdatePTSystem(float dt)
{
	//更新粒子系统
	float p2x, p2y, p2xto, p2yto, arc;
	arc=(mStage%30)*12.0f/180.0f*3.1415926f;
	p2yto=240.0f+100.0f*sin(arc);
	p2xto=300.0f+100.0f*cos(arc);
	
	mParticleSystem2->GetPosition(&p2x, &p2y);
    mParticleSystem2->MoveTo(p2x+(p2xto-p2x)*10*dt, p2y+(p2yto-p2y)*10*dt, false);
	mParticleSystem2->Update(dt);
}
/*
void GameLayerPlayELS::DoSendHeartBeat(float dt)
{
    if(mHeartTempo>HEARTBEAT_TIME)
    {
        mHeartTempo=0;
        SendHeartBeat();
    }
    else
        mHeartTempo+=dt;
}


 */
//检测攻击,应用道具，更新各种stage
inline void GameLayerPlayELS::UpdateELS(int i)
{
	if (mGS[i].game_over) return;
	if (!mGS[i].active) return;
	
	u8 tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
	/*
	if(mGS[i].attack[0]) //检测执行攻击
	{
		if(tmode==ELS_MODE_NET && !isRobotGame())
		{
			//当网络对战时，自己产生的攻击发送到server，由server广播给其他客户端执行
			//其他客户端收到加行命令后，执行加行并发送给server,server再广播给自己，这时候才真正执行加行.
			if(i==0)
			{
				char tmp[32];
				sprintf(tmp, "A%d%d", mGS[i].attack[0], mGS[i].attack[1]);
				//RecordAction(0, tmp);
				mGS[i].attack[0]=0;
			}
			else {
				//如果是其他窗口产生的attackcount，直接清零，什么也不做。
				mGS[i].attack[0]=0;
			}
            
		}
		else {
			for(int m=0;m<4;m++)
			{
				if(m!=i && !mGS[m].game_over)
				{
					Attack(m, mGS[i].attack[0], mGS[i].attack[1]);
					TestDDown(m);
				}
			}
			mGS[i].attack[0]=0;
		}
	}*/
	
	if (mGS[i].block_change_time>0) mGS[i].block_change_time--; //换下一个方块时next小方块的移动
	if (mGS[i].show_hold_time>0) mGS[i].show_hold_time--; //hold时高亮显示的时间
	if (mGS[i].face_remain_time>0) mGS[i].face_remain_time--; //face道具
	if (mGS[i].shield_remain_time>0) mGS[i].shield_remain_time--; //shield道具
	/*if (mGS[i].item_trigger>0 && mGS[i].full_rows_count==0) //执行应用道具
	{
		if (mGS[i].item_trigger==151) 
			ItemSubNLines(i, 1);
		if (mGS[i].item_trigger==152) 
			ItemSubNLines(i, 2);
		if (mGS[i].item_trigger==153) 
			ItemSubNLines(i, 4);
		if (mGS[i].item_trigger==154) 
			ItemHammer(i);
		if (mGS[i].item_trigger==155) {
			ItemShield(i);
			mGS[i].shield_remain_time = 100;
		}
		if (mGS[i].item_trigger==156) 
			ItemCompress(i);
		if (mGS[i].item_trigger==157) 
			ItemPlusNLines(i, 1);
		if (mGS[i].item_trigger==158) 
			ItemPlusNLines(i, 2);
		if (mGS[i].item_trigger==159) 
			ItemPlusNLines(i, 4);
		if (mGS[i].item_trigger==160) {
     ItemBlock(i);
		}
		
		mGS[i].item_trigger = 0;
		mItemChoose=0;//这两个参数也在UseItem()的最后重置了
		mItemTarget=4;//道具使用后，两个参数归为默认值。
		TestDDown(i);
	}*/
	
	if(mGS[i].grect_stage>0) mGS[i].grect_stage-=4; //更新下落残影stage
	if (mGS[i].clear_stage>0) mGS[i].clear_stage--; //更新消行stage
    
	if (mGS[i].cling_stage>0) mGS[i].cling_stage--;
	if (mGS[i].levelup_stage) mGS[i].levelup_stage--;
	
	//滑动时间，非直落而下落到底时，MoveBlk把ready_wending减一
	//触发每次Update减一，减到0时，真正REACH_BOTTOM，又重新置为WENDING
    //网络模式下，只更新自己的ready wending，其他的ready wending是靠消息设置的
	if (mElsMode!=ELS_MODE_NET || (mElsMode==ELS_MODE_NET&&i==0)) {
		if(mGS[i].ready_wending != WENDING)
			mGS[i].ready_wending--;
	}
    
	ClearFullRows(i, false); //消除填满的行
	if(mGS[i].grect_stage==180) //绘制完直落阴影(grect_stage从240减到180),执行真正的直落操作
	{
		while(MoveBlk(DDOWN, i, false)!=REACH_BOTTOM)
		{
			if(mGS[i].game_over)
				break;
		}
		NextBlk(i, false);
		TestDDown(i);
	}
}
void GameLayerPlayELS::FallWithUpdate(int i)
{
    printf("enter fallwithupdate and fallstat is %f\n",((AnimationLayerPlayELS *)Annimationlayer)->fallstat[0]);
    ((AnimationLayerPlayELS *)Annimationlayer)->fallstat[0]=-1;
    do{
        if(mGS[0].game_over)
        break;
    }while(MoveBlk(DDOWN, 0, false)!=REACH_BOTTOM);
    NextBlk(0, false);
    TestDDown(0);
    }




void GameLayerPlayELS::ResetImg()
{
	char tmp[16];
	
	mTheme=1;
	//snprintf(tmp, 16, "theme%d.xml", mTheme+1);
	//mAssetCommon->LoadResource(tmp);
	
	for(int i=0;i<10;i++)
	{
		//custom block
		sprintf(tmp, "fk_kuang.png", i);
		mYingBLK[i]=mAssetCommon->GetImage(tmp);
		
		sprintf(tmp, "fk%d.png", i+1);
		mBLK[i]=mAssetCommon->GetImage(tmp);
		
		sprintf(tmp, "n%d.png", i);
		mNO[i]=mAssetCommon->GetImage(tmp);
		
		sprintf(tmp, "infonum%d.png", i);
		mInfoNum[i]=mAssetCommon->GetImage(tmp);
	}
	mBLK[10]=mAssetCommon->GetImage("fk11.png");
	
	mFace = mAssetCommon->GetImage("face.png");//道具笑脸
	
	for (int i=0; i<11; i++) {
		sprintf(tmp, "item%d.png", i);
		mItemBLK[i]=mAssetCommon->GetImage(tmp);
	}
	
	for (int i=0; i<5; i++) {
		sprintf(tmp, "xuanzhuan%d.png", i+1);
		mXuanZhuan[i]=mAssetCommon->GetImage(tmp);
	}
	
	mBottom   = mAssetCommon->GetImage("Dbottom.png");
	mGrid     = mAssetCommon->GetImage("grid.png");
    mAdvProBarB = mAssetCommon->GetImage("advprobar_b.png");
	mAdvProBarF = mAssetCommon->GetImage("advprobar_f.png");
	mAdvProBarHL = mAssetCommon->GetImage("advprobar_hl.png");
	mGua2	  = mAssetCommon->GetImage("gua2.png");
	mItemBox  = mAssetCommon->GetImage("itembox.png");
	
	mBigNO[0] = mAssetCommon->GetImage("Gbig1.png");
	mBigNO[1] = mAssetCommon->GetImage("Gbig1.png");
	mBigNO[2] = mAssetCommon->GetImage("Gbig2.png");
	mBigNO[3] = mAssetCommon->GetImage("Gbig3.png");
	
	mClear1   = mAssetCommon->GetImage("clear1.png");
	mClear2   = mAssetCommon->GetImage("clear2.png");
	
	mBgT      = mAssetCommon->GetImage("playback.png");
	mBgTK     = mAssetCommon->GetImage("kuang.png");
	mBgTKSmall= mAssetCommon->GetImage("skuang.png");
	mBgNS[0]  = mAssetCommon->GetImage("nextsavebg.png");
	mBgNS[1]  = mAssetCommon->GetImage("nextsaveframe.png");
	mCombo    = mAssetCommon->GetImage("Tcombo.png");
	mAttack   = mAssetCommon->GetImage("Tattack.png");
	mClear    = mAssetCommon->GetImage("Tclear.png");
	mPause    = mAssetCommon->GetImage("pause.png");
	mWin      = mAssetCommon->GetImage("win.png");
	mLose     = mAssetCommon->GetImage("lose.png");
	mSP       = mAssetCommon->GetImage("help.png");
	mDropBar  = mAssetCommon->GetImage("dropbar.png");
	//
	mArrow    = mAssetCommon->GetImage("attackblk.png");
    mTopLight = mAssetCommon->GetImage("toplight.png");
	
	mConnect  = mAssetCommon->GetImage("connect.png");
	mConnDot  = mAssetCommon->GetImage("spot.png");
	
	mNameBk   = mAssetCommon->GetImage("namebk.png");
	mNameSBk  = mAssetCommon->GetImage("snamebk.png");
	
	mUnlock   = mAssetCommon->GetImage("unlock.png");
	
	mItemSelected = mAssetCommon->GetImage("itemselect.png");
	
	mNRBready = mAssetCommon->GetImage("nrbready.png");
	mNRBback  = mAssetCommon->GetImage("nrbback.png");
	mNRBchange= mAssetCommon->GetImage("nrbcroom.png");
	mNRready  = mAssetCommon->GetImage("nrready.png");
	mNRnaozhong=mAssetCommon->GetImage("nrnaozhong.png");
	
	mOBagain  = mAssetCommon->GetImage("overmenuplayagain.png");
	mOBnext   = mAssetCommon->GetImage("overmenunext.png");
	mOBsave   = mAssetCommon->GetImage("overmenusave.png");
	mOBback   = mAssetCommon->GetImage("overmenuback.png");
	mOBchange = mAssetCommon->GetImage("overmenuchangeroom.png");
	
	mWLback   = mAssetCommon->GetImage("wlback.png");
	mWLwin    = mAssetCommon->GetImage("wlwin.png");
	mWLover   = mAssetCommon->GetImage("wlover.png");
	mWLPover  = mAssetCommon->GetImage("wlpover.png");
	mWLlose   = mAssetCommon->GetImage("wllose.png");
	mWLstar   = mAssetCommon->GetImage("wlstar.png");
	mWLpack   = mAssetCommon->GetImage("wlpack.png");
	mWLinfo   = mAssetCommon->GetImage("wlinfo.png");
	
	mBigStar[0]=mAssetCommon->GetImage("bigstar.png");
	mBigStar[1]=mAssetCommon->GetImage("bigstaroutlight.png");
	
	mReplay   = mAssetCommon->GetImage("replayflag.png");
	mLevelUp  = mAssetCommon->GetImage("Tlevelup.png");
	mItemLimitNotice = mAssetCommon->GetImage("itemLimitNotice.png");
	mCanNotUseItem = mAssetCommon->GetImage("cannotuseitem.png");
	mNetItemBox = mAssetCommon->GetImage("netitembox.png");
	mNetErrorBg = mAssetCommon->GetImage("loadingbg.png");
	mNetErrorFace=mAssetCommon->GetImage("neterrorface.png");
	
	mFriendUI = mAssetCommon->GetImage("friendui.png");
	mBackUI   = mAssetCommon->GetImage("backgame.png");
	mTempItem = mAssetCommon->GetImage("tempitem.png");
	mAchDialog= mAssetCommon->GetImage("achdialog.png");
	
	mCountDownBoxGlass = mAssetCommon->GetImage("njindu.png");
	m2ndhlight = mAssetCommon->GetImage("2ndhlight.png");
	mDlgBack = mAssetCommon->GetImage("dlgback.png");
	
	mMarkPause	= mAssetCommon->GetImage("Lpausett.png");
	mMarkScore	= mAssetCommon->GetImage("Lscorestt.png");
	mButtonResume	= mAssetCommon->GetImage("Bresume.png");
	mButtonHome		= mAssetCommon->GetImage("Bhome.png");
	mButtonRetry	= mAssetCommon->GetImage("Bretry.png");
	mButtonOptions	= mAssetCommon->GetImage("Boptions.png");
	mButtonSound[0]	= mAssetCommon->GetImage("laba1.png");
	mButtonSound[1]	= mAssetCommon->GetImage("laba2.png");
}

void GameLayerPlayELS::ResetGstat(int idx)
{
	int i,j;
	
	memset(&mGS[idx], 0, sizeof(GSTAT));
    printf("idx %d reset end \n",idx);
    //设置初始grid
	for( i=0; i<ZONG+2; i++) //边框置为200，限制方块活动范围
		for( j=0; j<HENG+4; j++)
			mGS[idx].grid[i][j]=200;
	for( i=0; i<ZONG; i++) //冒险模式设置图形，其他模式清零
		for( j=0; j<HENG; j++)
			if (mBJIdx&&idx==0) {
				mGS[idx].grid[i][2+j]=(i>=(ZONG-10))?(100+g_bmp[mBJIdx][i-(ZONG-10)][j]):0;
				if(mGS[idx].grid[i][2+j]==100) mGS[idx].grid[i][2+j]=0;
			}
			else {
				mGS[idx].grid[i][2+j]=0;
			}
	
	//初始化各种变量
    if (mElsMode!=ELS_MODE_AI && idx==0) mGS[idx].level = mNanDu;
	mGS[idx].fullrows[0] = mGS[idx].fullrows[1] =
	mGS[idx].fullrows[2] = mGS[idx].fullrows[3] = -1;
	mGS[idx].shield_remain_time	= 0;
	mGS[idx].face_remain_time	= 0;
	mGS[idx].clear_stage=mGS[idx].itemuse_stage=mGS[idx].xunzhang_stage=mGS[idx].unlock_stage=0;
	mGS[idx].cur_block  = mBlockQueue[0];
	mGS[idx].next_block = mBlockQueue[1];
	mGS[idx].save_block = -1;
	mGS[idx].cur_x		= 5;
	mGS[idx].block_change_time = 0;
	mGS[idx].show_hold_time = 0;
	mGS[idx].game_over	= false;
	mGS[idx].ready_wending = WENDING;
	
    //计算初始col,hole,top
	UpdateColHoleTop(idx, 2, 11);
	
    //根据模式确定本窗口是否active
	mGS[idx].active=true;
	/*  comment by lyl
     if(mElsMode==ELS_MODE_REPLAY)
	{
		if (mElsRepMode==ELS_MODE_SINGLE) 
		{
			if (idx>0) mGS[idx].active=false;
		}
		else if (mElsRepMode==ELS_MODE_AI || (mElsRepMode==ELS_MODE_NET&&isRobotGame())) 
		{
			if (idx>1) mGS[idx].active=false;
		}
		else 
		{
            if(g_seats[GetSeatIdByidx(idx)-1].userid==0) mGS[idx].active=false;
		}
	}
	else 
	{
		if (mElsMode==ELS_MODE_SINGLE) 
		{
			if (idx>0) mGS[idx].active=false;
		}
		else if (mElsMode==ELS_MODE_AI || (mElsMode==ELS_MODE_NET&&isRobotGame())) 
		{
			if (idx>1) mGS[idx].active=false;
		}
		else 
		{
			if(g_seats[GetSeatIdByidx(idx)-1].userid==0) mGS[idx].active=false;
		}
    
	}*/
    
    mElsMode=ELS_MODE_SINGLE;
    if (idx>0) mGS[idx].active=false;

}

//生成随机块序列
void GameLayerPlayELS::GenRandomBlockQueue(long seed)
{
	srandom(seed);	
	printf("GEN BLK QUEUE\n");
	//生成500个块的序列
	for(int i=0; i<MAXBLKQUEUE; i++)
	{
		int tmpreplace = randomZ(mStage, "GBQ");
		int tmptype    = randomZ(mStage, "GBQ")%9;
		if (tmpreplace%3==0) 
		{
			if (tmptype==3 || tmptype==4) 
				tmptype=2;
		}
		mBlockQueue[i]=tmptype;
		printf("%d", mBlockQueue[i]);
	}
	printf("\n");
}	

//初始化游戏

void GameLayerPlayELS::ResetELS() 
{
	printf("%f, ENTER RESET...\n", CFAbsoluteTimeGetCurrent());
    
	/*if(mElsMode==ELS_MODE_REPLAY)
     {
     if (mNanDu==0)
     {
     char fn[64];
     sprintf(fn, "%d.rep", g_mvRepFiles[mTheme]);
     mRepTheme=mTheme;
     LoadAction(fn);
     GenRandomBlockQueue(mRandomSeed);
     }
     else 
     {
     LoadAction("demo.rep");
     GenRandomBlockQueue(mRandomSeed);
     }
     }
     else if(mElsMode==ELS_MODE_NET)
     {
     //等待服务器返回随机种子...
     mRandomSeed = 0;
     }
     else 
     {*/
    mRandomSeed = time(NULL);
    GenRandomBlockQueue(mRandomSeed);
    //	}
	
	//set goldenluck by mode...
	/*int emode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
     if (emode==ELS_MODE_NET) {
     GOLDENLUCK=50;
     }
     if(emode==ELS_MODE_AI) {//AI MODE 
     GOLDENLUCK=20;
     }
     if (emode==ELS_MODE_SINGLE) {
     if (mBJIdx==0) {//CLASSIC
     GOLDENLUCK=20;
     }`
     else {//ADVENTURE
     GOLDENLUCK=50;
     }
     }
     */
    
    
    
	srand(time(NULL));
    ResetImg();
    
	mSafeTop = 10;
	mStage=0;
	printf("mStage is:%d\n",mStage);
	
	
    
    mPauseStage = MAX_PAUSE_STAGE;
	mNetInitStage=0;
	mRepSaved=0;
    mActQueue[0] = 0;
	mItemFly.clear();
	mItemChoose=0;
	mItemTarget=4;
    
    
	
    for (int i=0; i<10; i++) {
		mItemNum[i]=0;
        mItemLimit[i]=ItemLimit[i];
	}
	mShowItemLimitNoticeStageLeft=0;
	
	ELS_PAUSE = false;
	mNeed_process_record=false;
    mManTempo=mAiTempo=mHeartTempo=10.0f;
    
    timeused = 0.0;
    
    timeForScoreBoard=TIMEFORSCOREBOARD;
    timeForAScoreBoard=TIMEFORASCOREBOARD;
	timeForWaitReady=20.0f;
    
    
    
	printf("mode=%d mstage=%d\n", mElsMode, mStage);
	m4LineCleared = 0;
	isFirstItem=1;
	hasShowHoldHelp=0;
	
	if(mElsMode==ELS_MODE_AI)
		g_gamecount[0][mNanDu][0]++;
	if(mElsMode==ELS_MODE_SINGLE)
		g_gamecount[1][mNanDu][0]++;
	if(mElsMode!=ELS_MODE_REPLAY)
		g_recact_count=0;
	mNetDrawStr[0]=0;
	
	ResetTouch();
	ResetGstat(0);
	ResetGstat(1);
	ResetGstat(2);
	ResetGstat(3);
	
	//把当前的勋章情况拷贝到g_xunzhang4saverep里，保存rep时，存下来
	//memcpy(g_xunzhang4saverep, g_xunzhang, sizeof(g_xunzhang));
	WriteScore();
	
	printf("\n\n\n\n\n\n %f, LEAVE RESET...mElsMode=%d\n\n\n\n\n", CFAbsoluteTimeGetCurrent(), mElsMode);
}

//使用道具时调用...
//当道具的位置固定时，UseItem函数有很大的变化。
//之前的函数中，itemidx表示使用道具栏中第几个位置的道具，1-10
//在item_trigger和grid[][]中，道具代码为151-160，但在vector中，道具代码为对应的位置，所以为1-10。
//g_item_value存储每个位置对应什么道具
//而修改之后每个位置是什么道具都是确定的，所以g_item_value参数没有什么用处了。
//target表示使用的对象，一般攻击道具需要指定使用的对象，防守道具只对自己使用。
bool GameLayerPlayELS::UseItem(int idx, int itemidx,int target)
{
	if (target==4)//target==4 没有目标
		return false;
	
	if(idx==0) { //如果道具的使用者是自己
		char t[6];
		sprintf(t, "PI%d%d", target, itemidx);
		//mApp->TraceLog(t);
		
		if (mElsMode==ELS_MODE_NET) {//对战状态下改变g_item_num[10]的值
			if (g_item_num[itemidx-1]>0) {
				g_item_num[itemidx-1]--;
				mItemLimit[itemidx-1]--;
			}
		}
		else {
			if (mItemNum[itemidx-1]>0) //其他状态(AI,CLASSIC)下改变mItemNum[10]的值
				mItemNum[itemidx-1]--;//道具数量-1
		}
	}
    
	//防守道具
	if (itemidx==1)	mGS[target].item_trigger=151;	//-1
	if (itemidx==2) mGS[target].item_trigger=152;	//-2
	if (itemidx==3) mGS[target].item_trigger=153;	//-4
	if (itemidx==4) mGS[target].item_trigger=154;	//锤子
	if (itemidx==5) mGS[target].item_trigger=155;	//盾
	if (itemidx==6) mGS[target].item_trigger=156;	//坍塌
	//进攻道具
	if (itemidx==7) mGS[target].item_trigger=157;	//+1
	if (itemidx==8) mGS[target].item_trigger=158;	//+2
	if (itemidx==9)	mGS[target].item_trigger=159;	//+4
	if (itemidx==10) mGS[target].item_trigger=160;	//遮挡
	if (itemidx>10)  mGS[target].item_trigger=161;
    
	mGS[idx].itemuse_stage=MAX_CLEAR_ITEM_STAGE;
    
	//新建ITEMMOVE结构存到vector中
	ITEMMOVE new_itemmove;
	new_itemmove.itemtype = 20+itemidx;//所有道具使用时，都是星星的效果，与得到道具时的效果不同，所以统一用20来代表。
	if (idx==0) {
		new_itemmove.startx =(float) GetButtonRecItem(itemidx-1, 0)+GetButtonRecItem(itemidx-1, 2);
		new_itemmove.starty =(float) GetButtonRecItem(itemidx-1, 1)+GetButtonRecItem(itemidx-1, 3);
	}
	else {
		new_itemmove.startx =(float)2*280;//2* for retina
		new_itemmove.starty =(float)2*120*idx;
	}
	if (target==0) {//道具对自己使用，那么终点是主屏幕中央，位置确定
		new_itemmove.endx = (float)6*blksize;
		new_itemmove.endy = (float)15*blksize;
	}else {//道具对其他玩家使用，终点由target确定
		new_itemmove.endx = (float)2*245;
		new_itemmove.endy = (float)2*140*(target-1)+220;//这是其他三个玩家的小屏幕中央
	}
	new_itemmove.item_move_stage = 60;
	mItemFly.push_back(new_itemmove);
    
	mItemChoose=0;
	mItemTarget = 4;
	return true;
}

//执行动作码的基础方法
void GameLayerPlayELS::PlayActionBase(char *act, int index)
{
	char aiact = act[0];
	char us[2], rs[2], is[3];
	int iid,uid,rid;
	char tmp[64];
	char aline[2],aseed[32];
	int ialine, iaseed;
	u8 tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
	
    
   ((AnimationLayerPlayELS *)Annimationlayer)->Cancel_fall(index);


	switch (aiact)
	{
		case 'A':
			if (mElsMode==ELS_MODE_REPLAY) break;
			aline[0]=act[1],aline[1]=0;
			sprintf(aseed, "%s", &act[2]);
			sscanf(aseed, "%d", &iaseed);
			ialine=atoi(aline);
			/*
            Attack(0, ialine, iaseed);
			*/
            
            sprintf(tmp, "K%d%d", ialine, iaseed);
			RecordAction(0, tmp);
			break;
		case 'K':
			//if (mElsMode==ELS_MODE_REPLAY) break;
			aline[0]=act[1],aline[1]=0;
			sprintf(aseed, "%s", &act[2]);
			sscanf(aseed, "%d", &iaseed);
			ialine=atoi(aline);
			//Attack(index, ialine, iaseed);
			break;
		case 'C':
			if (mElsMode==ELS_MODE_REPLAY && (index==0)) break;
			int f0,f1,f2,f3,co;
            sscanf(&act[1], "%d.%d.%d.%d.%d", &f0, &f1, &f2, &f3, &co);
			mGS[index].fullrows[0]=f0;
			mGS[index].fullrows[1]=f1;
            mGS[index].fullrows[2]=f2; 
			mGS[index].fullrows[3]=f3; 
			mGS[index].combo=co;
			mGS[index].full_rows_count=0;
            for (int f=0; f<4; f++) {
				if (mGS[index].fullrows[f]!=0) {
					mGS[index].full_rows_count++;
				}
            }
			ProcessClearRow(index, false, false);
            break;
		case 'Z':
			if (mElsMode==ELS_MODE_REPLAY) break;
			mGS[index].ready_wending=-1;
			if(MoveBlk(DOWN, index, false)==REACH_BOTTOM)
				NextBlk(index, false);
			TestDDown(index);
			break;
		case 'T':
			//到边时，如果旋转遇到碰撞，就尝试自动左右移动，看看能否不碰撞了
			if(MoveBlk(TURN, index, false)==NORMAL)
			{
				TestDDown(index);
				break;
			}
			else {
				//开始尝试左右移动再转...
				GSTAT tmpstat=mGS[index];
				MSTAT mret;
				//LT
				MoveBlk(LEFT, index, false);
				mret=MoveBlk(TURN, index, false);
				if (mret==NORMAL) {
					TestDDown(index);
					break;
				} 
				else {
					mGS[index]=tmpstat;
				}
				//LLT
				MoveBlk(LEFT, index, false);
				MoveBlk(LEFT, index, false);
				mret=MoveBlk(TURN, index, false);
				if (mret==NORMAL) {
					TestDDown(index);
					break;
				}
				else {
					mGS[index]=tmpstat;
				}
				//RT
				MoveBlk(RIGHT, index, false);
				mret=MoveBlk(TURN, index, false);
				if (mret==NORMAL) {
					TestDDown(index);
					break;
				}
				else {
					mGS[index]=tmpstat;
				}
				//RRT
				MoveBlk(RIGHT, index, false);
				MoveBlk(RIGHT, index, false);
				mret=MoveBlk(TURN, index, false);
				if (mret==NORMAL) {
					TestDDown(index);
					break;
				}
				else {
					mGS[index]=tmpstat;
				}
			}
			break;
		case 'W':
        {
            ((AnimationLayerPlayELS *)Annimationlayer)->New_fall(index);
            
            // luoyulong mGS[index].grect_stage = 240;
		}	
            break;
		case 'D':
			if(MoveBlk(DOWN, index, false)==REACH_BOTTOM)
				NextBlk(index, false);
			//TestDDown(index);
            break;
		case 'L':
			MoveBlk(LEFT, index, false);
			TestDDown(index);
			break;
		case 'R':
			MoveBlk(RIGHT, index, false);
			TestDDown(index);
			break;
		case 'S':
			SaveBlk(index,false);
			TestDDown(index);
			break;
		case 'N':
			break;
		case 'I':
			//其他人使用道具
			us[0]=act[1],us[1]=0;
			rs[0]=act[2],rs[1]=0;
			sprintf(is, "%s", &act[3]);
			sscanf(is, "%x", &iid);
			uid=atoi(us);
			rid=atoi(rs);
			UseItem(GetIdxBySeatId(uid), iid, GetIdxBySeatId(rid));
			printf("USEITEM:%d %d %d\n", GetIdxBySeatId(uid), iid, GetIdxBySeatId(rid));
			break;
		case 'Y':
			//对别人使用道具的消息，
			us[0]=act[1],us[1]=0;
			rs[0]=act[2],rs[1]=0;
			sprintf(is, "%s", &act[3]);
			sscanf(is, "%x", &iid);
			uid=atoi(us);
			rid=atoi(rs);
			tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
			if(GetIdxBySeatId(rid)==0 || tmode!=ELS_MODE_NET)
			{
				//如果接收者是自己，则发一个回馈消息I...
				//如果接收者不是自己，则忽略...
				UseItem(GetIdxBySeatId(uid), iid, GetIdxBySeatId(rid));
				printf("USEITEM:%d %d %d\n", GetIdxBySeatId(uid), iid, GetIdxBySeatId(rid));
				sprintf(tmp, "I%d%d%02x", uid, rid, iid);
				RecordAction(0, tmp);
			}
			break;
		default:
			break;	
	}
}











/*void GameLayerPlayELS::DumpELS(int idx, const char *msg)
{
	if (g_fprand) {
		fprintf(g_fprand, "<%d.%d.%d> %s: top:%d", idx, mGS[idx].block_index, mStage, msg,  mGS[idx].top_line);
		fprintf(g_fprand, "(%d %d %d %d %d %d %d %d %d %d)", 
				mGS[idx].col_top[0],mGS[idx].col_top[1],mGS[idx].col_top[2],mGS[idx].col_top[3],
				mGS[idx].col_top[4],mGS[idx].col_top[5],mGS[idx].col_top[6],mGS[idx].col_top[7],
				mGS[idx].col_top[8],mGS[idx].col_top[9]);
		fprintf(g_fprand, " full_row_count=%d (%d %d %d %d)\n", mGS[idx].full_rows_count, 
				mGS[idx].fullrows[0],mGS[idx].fullrows[1],mGS[idx].fullrows[2],mGS[idx].fullrows[3]);
		
		fflush(g_fprand);
	}
}*/

//下一块
void GameLayerPlayELS::NextBlk(int idx, bool ai, bool issave) 
{	
    //printf("get a new blcok\n");
	//DumpELS(idx, "NEXT");
	mGS[idx].block_index++;
	mGS[idx].cur_block  = mGS[idx].next_block;
	if (!issave)
		mGS[idx].block_change_time = 10;//标记next里面的方块的移动
	mGS[idx].cur_x=5, mGS[idx].cur_y=0, mGS[idx].cur_z=0;
	MoveBlk(SET, idx, ai);
    mGS[idx].next_block = mBlockQueue[(mGS[idx].block_index+1)%MAXBLKQUEUE];
    
    
    
}

//保存块,每次确认下落后才能再次保存(save_lock)
void GameLayerPlayELS::SaveBlk(int idx, bool ai)
{
	if(!mGS[idx].save_lock) {
		int tn=-1;
		mGS[idx].save_lock=1;
		MoveBlk(CLEAR, idx, ai);
		if(mGS[idx].save_block>=0)
		{
			tn=mGS[idx].next_block;
			mGS[idx].next_block=mGS[idx].save_block;
		}	
		mGS[idx].save_block=mGS[idx].cur_block;
		NextBlk(idx, ai, true);
		mGS[idx].block_index--;
		if(tn>=0)
			mGS[idx].next_block = tn;
	}
}

inline void GameLayerPlayELS::UpdateColHoleTop(int idx, int gxs, int gxe)
{
	GSTAT *gp;
	int m, n;
	
	gp = &mGS[idx];
	for(m=gxs;m<=gxe;m++)
	{
		gp->col_top[m-2]=0;
		gp->col_hole[m-2]=0;
		for(n=ZONG;n>0;n--)
		{
			if(gp->grid[ZONG-n][m]>100)
			{
				gp->col_top[m-2]=n;
				break;
			}
		}
		for(;n>0;n--)
		{
			if(gp->grid[ZONG-n][m]==0)
				//gp->col_hole[m-2]+=(gp->col_top[m-2]-n);
				//if((gp->col_top[m-2]-n)<=3)
				gp->col_hole[m-2]+=n;
		}
	}
	gp->top_line = 0;
	for(m=0; m<HENG; m++)
	{			
		if(gp->col_top[m]>gp->top_line)
			gp->top_line = gp->col_top[m];
	}
}

/*void GameLayerPlayELS::UpdateLevel(int oldscore, GSTAT *gp, int idx)
{
	int oldlv=oldscore/350;
	int newlv=gp->score/350;
	//printf("UL:os=%d, ns=%d, ol=%d, nl=%d\n", oldscore, gp->score, oldlv, newlv);
	if (newlv>oldlv && gp->level<19) 
	{
		gp->level++;
		if (idx==0) 
			gp->levelup_stage=SET_LEVELUP_STAGE;
		if (g_options[1]) 
		{
			//printf("LEVEL UP WAV........\n");
			mSND->PlaySound(mWavLevelup);
		}
	}
	return;
}*/
/*
 此函数根本没用到...
 int GameLayerPlayELS::CheckOver()
 {
 int ret=0;
 
 for (int i=0; i<4; i++) {
 if (mGS[i].game_over) {
 ret++;
 }
 }
 return ret;
 }
 */
/*
//攻击对方
void GameLayerPlayELS::Attack(int idx, int line, int spaceseed)
{
	if(line<=0)
		return;
	if (!mGS[idx].active) 
		return;
	if(idx==0) printf("SPACESEED=%d\n", spaceseed);
	srandom(spaceseed);
	int flowflag=0;
	
	u8 tgrid[ZONG+2][HENG+4];	
	memcpy(tgrid, mGS[idx].grid, GRIDSIZE);
	int i, j;
	
	for( i=0; i<ZONG-line; i++)
		for( j=0; j<HENG; j++)
		{
			tgrid[i][2+j]=mGS[idx].grid[i+line][2+j];	
			if(tgrid[i][2+j]<10 && tgrid[i][2+j]>0)
			{
				flowflag=1;
				tgrid[i][2+j]=0;
			}
		}
	for( i=0; i<line; i++) 
	{
		int r = randomZ(mStage, "ATT")%HENG;
		//printf("R=%d gl=%d\n", r, GOLDENLUCK);
		for(j=0; j<HENG; j++) 
		{
			if(r == j)
			{
				tgrid[ZONG-1-i][2+j]=0;
			}
			else
			{
				int yy=randomZ(mStage, "ATT");
				//printf("YY=%d gl=%d\n", yy, GOLDENLUCK);
				if(yy%GOLDENLUCK==0)//产生一个道具
				{	
					int itemOdd=(randomZ(mStage, "ATT")/10)%100;
					int emode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
					if (emode==ELS_MODE_NET)//网络模式下只产生-1，-2两种道具，机率分别为70%，30%
					{
						tgrid[ZONG-1-i][2+j]=110;
					}
					else if (emode==ELS_MODE_AI)//经典，电脑对战模式，入门中级大师三个级别，产生全部攻击防守道具
                    {
                        if (itemOdd>=0 && itemOdd<20)
                            tgrid[ZONG-1-i][2+j]=151;	//-1,20%
                        else if (itemOdd>=20 && itemOdd<32)
                            tgrid[ZONG-1-i][2+j]=152;	//-2,12%
                        else if (itemOdd>=32 && itemOdd<38)
                            tgrid[ZONG-1-i][2+j]=153;	//-4,6%
                        else if (itemOdd>=38 && itemOdd<44)
                            tgrid[ZONG-1-i][2+j]=154;	//锤子,6%
                        //else if (itemOdd>=44 && itemOdd<50)
                        //	tgrid[ZONG-1-i][2+j]=155;	//盾牌,6% //取消盾牌道具，任何时候都不产生
                        else if (itemOdd>=50 && itemOdd<56)
                            tgrid[ZONG-1-i][2+j]=156;	//坍塌,6%
                        else if (itemOdd>=56 && itemOdd<76)
                            tgrid[ZONG-1-i][2+j]=157;	//+1,20%
                        else if (itemOdd>=76 && itemOdd<88)
                            tgrid[ZONG-1-i][2+j]=158;	//+2,12%
                        else if (itemOdd>=88 && itemOdd<94)
                            tgrid[ZONG-1-i][2+j]=159;	//+4,6%
                        //							else if (itemOdd>=94 && itemOdd<100)
                        //								tgrid[ZONG-1-i][2+j]=160;	//遮挡,6%
                        else 
                            tgrid[ZONG-1-i][2+j]=110;
					}
				}
				else 
				{
					tgrid[ZONG-1-i][2+j]=110;
				}
			}
		}
	}
	memcpy(mGS[idx].grid, tgrid, GRIDSIZE);
	
	if (flowflag) {
		u8 x=mGS[idx].cur_x;
		u8 y=mGS[idx].cur_y;
		u8 z=mGS[idx].cur_z;
		u8 type=mGS[idx].cur_block;
		bool needUp=false;
		for(i=0; i<4; i++)
			for(j=0; j<4; j++)
				if(mGS[idx].grid[y+i][x+j]&&blkdat[type][z][i*4+j])
					needUp=true;
		if (needUp) {
			//printf("ATTACK NEED UP CURRENT BLOCK!\n");
			mGS[idx].cur_y-=line;
			y=mGS[idx].cur_y;
		}
		for(i=0; i<4; i++)
			for(j=0; j<4; j++)
				mGS[idx].grid[y+i][x+j]+=blkdat[type][z][i*4+j];
	}
	
	for( i=0;i<HENG;i++)
		mGS[idx].col_top[i]+=line;
	
	if (mGS[idx].full_rows_count!=0) 
	{
		for (int f=0; f<mGS[idx].full_rows_count; f++) 
			mGS[idx].fullrows[f]-=line;
		DumpELS(idx, "ATTACK add fullrows!!!");
	}
	//TODO:攻击影响col_hole
}
*/
//用于预先绘制下落到底部的虚影，用于更好的瞄准
int GameLayerPlayELS::TestDDown(int idx)
{
	s8 x, y;
	GSTAT tmp;
	
	tmp=mGS[idx];
	while(MoveBlk(DDOWN, idx, true)!=REACH_BOTTOM);
	x = mGS[idx].cur_x;
	y = mGS[idx].cur_y;	
	mGS[idx]=tmp;
	mGS[idx].tdx=x;
	mGS[idx].tdy=y;
	
	return 0;
}

void GameLayerPlayELS::ProcessClearRow(int idx, bool ai, bool isLocalClear)
{
	GSTAT *gp;
	
	gp = &mGS[idx];
	
	u16 ls[4]={10,30,50,100};
	//有行可消,连击加一
	if(gp->full_rows_count)
	{	
		
		
		if (gp->clear_stage>=(SET_CLEAR_STAGE-REND_CLEAR_STAGE) && !ai)
		{
			printf("CLEARING LINE DETECTED,STAGE=%d\n", gp->clear_stage);
			DumpELS(idx, "CLEARING");
			//遇到上次正在播放消行动画的满行，直接消掉，再处理...
			gp->clear_stage=(SET_CLEAR_STAGE-REND_CLEAR_STAGE);
			ClearFullRows(idx, ai);
		}
		gp->combo++;
		TestAchievement();
		gp->clear_stage=SET_CLEAR_STAGE;
		if(!ai)
		{
			gp->score+=ls[gp->full_rows_count-1];
			UpdateLevel(gp->score-ls[gp->full_rows_count-1], gp, idx);
			gp->lines+=gp->full_rows_count;
		}
		
		//输出3连以上连击
		if(gp->combo>2 && !ai) 
		{
			if(gp->combo>gp->max_combo)
			{
				gp->max_combo = gp->combo;
				if (mElsMode==ELS_MODE_NET) 
					SendMaxCombo(gp->combo, idx);
			}
			if(!ai)
			{
				gp->score+=(5*gp->combo);
				UpdateLevel(gp->score-(5*gp->combo), gp, idx);
			}
			
			
		}
		
		if(!ai)
		{
			//发送消行的网络命令...
			if (idx==0 && !isRobotGame() && mElsMode==ELS_MODE_NET && isLocalClear)
			{
				char tmp[64];
				if (gp->full_rows_count==1) sprintf(tmp, "C%d.0.0.0.%d", gp->fullrows[0], gp->combo);
				if (gp->full_rows_count==2) sprintf(tmp, "C%d.%d.0.0.%d", gp->fullrows[0], gp->fullrows[1], gp->combo);
				if (gp->full_rows_count==3) sprintf(tmp, "C%d.%d.%d.0.%d", gp->fullrows[0], gp->fullrows[1], gp->fullrows[2], gp->combo);
				if (gp->full_rows_count==4) sprintf(tmp, "C%d.%d.%d.%d.%d", gp->fullrows[0], gp->fullrows[1], gp->fullrows[2], gp->fullrows[3], gp->combo);
				RecordAction(idx, tmp);
			}
			
			//播放音效		
		/*	if (idx==0) 
				mSND->SetSoundVolume(100);
			else 
				mSND->SetSoundVolume(30);
			if (gp->full_rows_count==1)
			{
				//if (g_options[1]) mSND->PlaySound(mWavClear[2]);
			}
			else
			{
				if (g_options[1]) mSND->PlaySound(mWavPeeco);
			}
         */
		}
	}						
	else
	{
		gp->combo=0;
	}	
}

//操作方块,更新Grid
inline MSTAT GameLayerPlayELS::MoveBlk(MDIR dir, int idx, bool ai)
{
	//change the netstate to selfover.
	
	s8  type, cx, cy, cz, x=0, y=0, z=0;
	int i, j, m, n;
	bool fflag;
	
	GSTAT *gp;
	
	gp = &mGS[idx];
	
	//if (mElsMode == ELS_MODE_NET && mGS[idx].game_over) 
	//	SetNetStateSelfOver();
    
    
	char mtmp[16];
	sprintf(mtmp, "MOVE=%d", dir);
	if (ai==false && mElsMode==ELS_MODE_NET)
		//DumpELS(idx, mtmp);
	
	if(gp->game_over)
	{
		if(dir==LEFT || dir==RIGHT)
			return REACH_BORDER;
		else
			return REACH_BOTTOM;
	}
	
	type = gp->cur_block;
	cx=gp->cur_x, cy=gp->cur_y, cz=gp->cur_z;
	
	switch (dir)
	{
		case TURN:
			x=cx,y=cy,z=(cz+(mTurnMode?-1:1)+4)%4;
			/*if(!ai)
			{
				if (idx==0) 
					mSND->SetSoundVolume(100);
				else 
					mSND->SetSoundVolume(30);
				if (g_options[1]) mSND->PlaySound(mWavTurn);
			}*/
			gp->ready_wending=WENDING;
			break;
		case DOWN:
		case DDOWN:
			x=cx,y=cy+1,z=cz;
			break;
		case LEFT:
			x=cx-1,y=cy,z=cz;
			gp->ready_wending=WENDING;
			break;
		case RIGHT:
			x=cx+1,y=cy,z=cz;
			gp->ready_wending=WENDING;
			break;
		case SET:
			x=cx,y=cy,z=cz;
			break;
		case CLEAR:
			x=cx,y=cy,z=cz;
			break;
		default:
			
			break;
	}
	
	//不稳定块置0,100以上为已经下落稳定的块
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			if(gp->grid[cy+i][cx+j]<100)
				gp->grid[cy+i][cx+j]=0;
		}
	
	if(dir==CLEAR) 
		return NORMAL;	
	
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			//检测到了碰撞,可能是到底,到边,或者遇到了别的块,无法下落
			if(gp->grid[y+i][x+j] && blkdat[type][z][i*4+j])
			{	
				if (dir==DOWN || dir==DDOWN)
				{
					if(dir==DOWN)
					{
						if(gp->ready_wending>=0)
						{
							if(gp->ready_wending == WENDING)
								gp->ready_wending--;
							for( m=0; m<4; m++)
								for( n=0; n<4; n++)	
									if(blkdat[type][z][m*4+n])
										gp->grid[cy+m][cx+n] = blkdat[type][z][m*4+n];
							return READY_BOTTOM;
						}
						else
						{
							gp->ready_wending=WENDING;
							u8 tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
							//发送“粘住”消息...
							if (tmode==ELS_MODE_NET && idx==0)
							{
								printf("SEND Z MSG...\n");
							//	RecordAction(0, "Z");
							}
						}
					}
					
					//printf("ZHANZHU...\n");
					//加100,置为稳定块
					if (!ai) 
					{
						gp->cling_stage=MAX_CLING_STAGE;
						gp->cling_count=0;
						memset(gp->cling_blocks, 0, sizeof(gp->cling_blocks));
						gp->cling_ddown[0]=-1;
						gp->cling_ddown[1]=-1;
					}
					srandom(mRandomSeed+mGS[idx].block_index);
					
					u8 find_cling_ddown_x[4], find_cling_ddown_y;
					memset(find_cling_ddown_x, 0, 4);
					find_cling_ddown_y=0;
					
					for( m=0; m<4; m++)
						for( n=0; n<4; n++)	
							if(blkdat[type][z][m*4+n])
							{
								gp->grid[cy+m][cx+n] = 100+blkdat[type][z][m*4+n];
								if (!ai)
								{
									if(gp->grid[cy+m][cx+n]!=100)
									{
										//纪录下需要显示“粘住光晕”的块坐标及个数
										gp->cling_blocks[gp->cling_count][0]=cx+n-2;
										gp->cling_blocks[gp->cling_count][1]=cy+m;
										gp->cling_count++;
										
										//设置此两个辅助变量，以便计算直落两侧光晕的坐标位置
										find_cling_ddown_x[n]=1;
										find_cling_ddown_y=m;
										//printf("FCDY=%d\n", m);
										
										char ts[64];
										sprintf(ts, "MBK.%d.%d", idx, dir);
										//如果此位置产生道具，机率与GOLDENLUCK成反比。
										int randomResult=randomZ(mStage, ts);
										if (randomResult%GOLDENLUCK==0) {//此时randomResult已经是10的整数倍
											int itemOdd=(randomResult/10)%100;
											int emode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
											if (emode==ELS_MODE_NET)//网络模式下只产生-1，-2两种道具，机率分别为70%，30%
											{
											}
											if (emode==ELS_MODE_SINGLE && mBJIdx==0) //经典，ENDLESS模式下产生全部防守道具
											{
												if (itemOdd>=0 && itemOdd<20)
													gp->grid[cy+m][cx+n]=151;	//-1,40%
												else if (itemOdd>=20 && itemOdd<40)
													gp->grid[cy+m][cx+n]=152;	//-2,20%
												else if (itemOdd>=40 && itemOdd<60)
													gp->grid[cy+m][cx+n]=153;	//-4,10%
												else if (itemOdd>=60 && itemOdd<80)
													gp->grid[cy+m][cx+n]=154;	//锤子,10%
												//else if (itemOdd>=80 && itemOdd<90)
                                                //gp->grid[cy+m][cx+n]=155;	//盾牌,10%
												else if (itemOdd>=80 && itemOdd<100)
													gp->grid[cy+m][cx+n]=156;	//坍塌,10%
											}
											if (emode==ELS_MODE_AI)//经典，电脑对战模式，入门中级大师三个级别，产生全部攻击防守道具
											{
												if (itemOdd>=0 && itemOdd<20)
													gp->grid[cy+m][cx+n]=151;	//-1,20%
												else if (itemOdd>=20 && itemOdd<32)
													gp->grid[cy+m][cx+n]=152;	//-2,12%
												else if (itemOdd>=32 && itemOdd<38)
													gp->grid[cy+m][cx+n]=153;	//-4,6%
												else if (itemOdd>=38 && itemOdd<44)
													gp->grid[cy+m][cx+n]=154;	//锤子,6%
												//else if (itemOdd>=44 && itemOdd<50)
                                                //gp->grid[cy+m][cx+n]=155;	//盾牌,6%
												else if (itemOdd>=50 && itemOdd<56)
													gp->grid[cy+m][cx+n]=156;	//坍塌,6%
												else if (itemOdd>=56 && itemOdd<76)
													gp->grid[cy+m][cx+n]=157;	//+1,20%
												else if (itemOdd>=76 && itemOdd<88)
													gp->grid[cy+m][cx+n]=158;	//+2,12%
												else if (itemOdd>=88 && itemOdd<94)
													gp->grid[cy+m][cx+n]=159;	//+4,6%
												else if (itemOdd>=94 && itemOdd<100)
													gp->grid[cy+m][cx+n]=160;	//遮挡,6%
											}
											if (emode==ELS_MODE_SINGLE && mBJIdx!=0)//冒险模式，产生有限数量的防守道具
											{
												if (itemOdd>=0 && itemOdd<70) 
													gp->grid[cy+m][cx+n]=151;	//-1,70%
												else 
													gp->grid[cy+m][cx+n]=152;	//-2,30%
											}
										}
									}
								}
							}
					
					if (!ai)
					{
						//完成cling变量的计算,并输出检查...
						int fcd=0;
						for (int ci=0; ci<4; ci++) 
						{
							if (find_cling_ddown_x[ci]==1) {
								if (fcd==0) 
								{
									gp->cling_ddown[0]=(cx+ci)*2;
									fcd=1;
								}
								else 
									gp->cling_ddown[0]++;
							}
						}
						
						if (dir==DDOWN) {
							gp->cling_ddown[1]=find_cling_ddown_y+cy;
							gp->cling_ddown[0]-=4;
						}
						else {
							gp->cling_ddown[0]=-1;
							gp->cling_ddown[1]=-1;
						}
						gp->score+=1;
					//	UpdateLevel(gp->score-1, gp, idx);
					}
					
					UpdateColHoleTop(idx, 2, 11);
					u8 tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
                    if (tmode==ELS_MODE_NET && idx!=0 /*&& !isRobotGame()*/)
                    {    
                        gp->combo=0;
                    }    
                    else    
                    {
						//标注满行，检测满行信息 标记到fullrow里 同时标记full_rows_count
						i=0;
						for(m=0; m<4; m++)
						{
							fflag=true;
							for( n=0; n<HENG; n++)
								if(gp->grid[cy+m][n+2]<100 || gp->grid[cy+m][n+2]==200)
								{
									fflag=false;
									break;
								}
							if(fflag)						
								gp->fullrows[i++]=cy+m;
						}
						gp->full_rows_count = i;
					ProcessClearRow(idx, ai, true);
					}
					
					//进入了下一块处理,可以保存块了
					gp->save_lock=0;
					/*if(!ai)
					{
						if (idx==0) 
							mSND->SetSoundVolume(100);
						else 
							mSND->SetSoundVolume(30);
						if (g_options[1]) mSND->PlaySound(mWavDrop);
					}*/
                    //if(dir==6&&!ai)
					//printf("act is %d  and ai is %d reach bottom\n",dir,ai);
					return REACH_BOTTOM;
				}
				else if (dir==LEFT || dir==RIGHT)
				{
					for(i=0; i<4; i++)
						for(j=0; j<4; j++)
							gp->grid[cy+i][cx+j]+=blkdat[type][z][i*4+j];
					return REACH_BORDER;
				}
				else
				{
					if(dir==TURN)
					{
						for(i=0; i<4; i++)
							for(j=0; j<4; j++)
							{
								if(gp->grid[y+i][x+j]==0)
									gp->grid[y+i][x+j]+=blkdat[type][cz][i*4+j];
							}
						return REACH_BORDER;
					}
					
					//调用NextBlk会调用MoveBlk(SET),
					//此时方块刚出来就有碰撞表明Game Over了
					/*if(dir==SET) 
					{
						ProcessOver(idx, ai);
						mAdventureWin=false;
					}*/
					return NORMAL;
				}
			}	
		}
	
	//更新真正的Grid,置当前x,y,z,返回
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			gp->grid[y+i][x+j]+=blkdat[type][z][i*4+j];
	
	gp->cur_x=x, gp->cur_y=y, gp->cur_z=z;
	
	if (dir==LEFT || dir==RIGHT)
		/*if(!ai)
		{
			if (idx==0) 
				mSND->SetSoundVolume(100);
			else 
				mSND->SetSoundVolume(30);
			if (g_options[1]) mSND->PlaySound(mWavMove);
		}*/
	
	return NORMAL;
}

/*void GameLayerPlayELS::ProcessOver(int idx, bool ai)
{
	GSTAT *gp;
	gp = &mGS[idx];
	gp->game_over=true;
	
	gp->grect_stage=0;
	
	if (ai) 
		return;
	
	if (g_options[0]) mSND->SetMusicVolume(5);
	
	//网络对战模式，向服务器发送over消息...
	if (mElsMode==ELS_MODE_NET) {
		SendOver(idx);
	}
	
	//冒险模式...
	if(mElsMode==ELS_MODE_SINGLE && mBJIdx!=0)
	{
		if (mAdventureWin) {
			mGS[0].score+=10*(g_bmp_time[mBJIdx]-timeused);
			mGS[0].tmpstar=0;//此局所得的星星
			if (timeused<= g_bmp_time[mBJIdx]*0.7)
				mGS[0].tmpstar=3;
			else if(timeused<=g_bmp_time[mBJIdx]*0.85)
				mGS[0].tmpstar=2;
			else 
				mGS[0].tmpstar=1;
			if (mGS[0].tmpstar>g_star_bmp[mBJIdx-1]) {
				g_star_bmp[mBJIdx-1]=mGS[0].tmpstar;//如果所得星星比之前记录高，则更新。
				WriteScore();
			}
			
			if (g_options[1]) mSND->PlaySound(mWavWin);
			TestAchievement();
		}
		else {
			if (g_options[1]) mSND->PlaySound(mWavLose);
		}
        
	}
	
	//本地对战模式（AI模式）...
	if(idx==1 && mElsMode!=ELS_MODE_NET)
	{
		mGS[0].score+=1000*(mNanDu+1);
		if (g_options[1]) mSND->PlaySound(mWavWin);
		if(mElsMode == ELS_MODE_AI)
		{
			g_gamecount[0][mNanDu][1]++;
			float wincount, tcount, winrate;
			wincount=g_gamecount[0][mNanDu][1]*1.0f;
			tcount  =g_gamecount[0][mNanDu][0]*1.0f;
			winrate =wincount/tcount;
			if (mNanDu==1 && winrate>=0.3f && wincount>=5) 
				SetXunZhang(2);
			if (mNanDu==2 && winrate>=0.5f && wincount>=10) 
				SetXunZhang(1);
			if (mNanDu==3 && wincount>=30) 
				SetXunZhang(0);
		}
		if(mElsMode == ELS_MODE_SINGLE)
			g_gamecount[0][mNanDu][1]++;
		WriteScore();
	}
	else {
		if (g_options[1]) mSND->PlaySound(mWavLose);
	}
    
	
	//计算分数本地排行榜...
	if((mElsMode==ELS_MODE_SINGLE) || (mElsMode==ELS_MODE_AI))
	{
		vector<HSCORE*> *tmp;
		//if(mElsMode==ELS_MODE_SINGLE)
		tmp=&g_mvHS;
		size_t l;
		HSCORE *phs = new HSCORE;
		phs->score = mGS[0].score;
		phs->hang  = mGS[0].lines;
		phs->combo = mGS[0].max_combo;
		sprintf(phs->date, "%fs", timeused);
		phs->is_current = true;
		for(l=0; l<g_mvHS.size(); l++)
			g_mvHS[l]->is_current = false;
		tmp->push_back(phs);
		sort(tmp->begin(), tmp->end(), cmp_score);
		if(tmp->size()>=11)
		{
			SAFE_DELETE((*tmp)[10]);
			tmp->erase(tmp->end()-1);
		}
		mNeed_process_record = false;
		for(l=0; l<tmp->size(); l++)
		{
			if((*tmp)[l]->is_current)
			{
				mNeed_process_record = true;
				break;
			}
		}
		if(mNeed_process_record)
		{
			printf("need write score for new record\n");
			WriteScore();
		}
		if (mElsMode==ELS_MODE_SINGLE && mBJIdx==0)
			mApp->isNewScore=mGS[0].score*100;
	}
}
*/
//检测获得成就
void GameLayerPlayELS::TestAchievement(int clear)
{
	//return;
	//检测CLASSIC和ADVENTURE
	if (mElsMode==ELS_MODE_SINGLE) {
		if (mBJIdx==0) {//classic
			if (clear > 0) {//测试消4行
				printf("classic clear is :%d, m4LineCleared is:%d\n",clear,m4LineCleared);
				if (clear!=4)
					m4LineCleared=0;
				else 
					m4LineCleared++;
				
				if (m4LineCleared==2) 
					AddNewAchieve(7, 100.0);
				if (m4LineCleared==3) 
					AddNewAchieve(8, 100.0);
				if (m4LineCleared==4) 
					AddNewAchieve(9, 100.0);
				if (m4LineCleared==5) 
					AddNewAchieve(10, 100.0);
                
                
				//测试3,5,10连击
				if (mGS[0].combo==3) 
					AddNewAchieve(4, 100.0);
				if (mGS[0].combo==5) 
					AddNewAchieve(5, 100.0);
				if (mGS[0].combo==10)
					AddNewAchieve(6, 100.0);
				//测试速度等级
				if (mGS[0].level==3)
					AddNewAchieve(1, 100.0);
				if (mGS[0].level==5)
					AddNewAchieve(2, 100.0);
				if (mGS[0].level==9)
					AddNewAchieve(3, 100.0);
			}
		}
		if (mBJIdx>0) {//adventure
			if (mGS[0].game_over==true) {
				//检测所用时间
				if ((float)(timeused/g_bmp_time[mBJIdx])<=0.75) 
					AddNewAchieve(15, 100.0);
				if ((float)(timeused/g_bmp_time[mBJIdx])<=0.5) 
					AddNewAchieve(16, 100.0);
				//检测all stage
				if (g_unlock_bmp==48 && mAdventureWin)
					AddNewAchieve(11, 100.0);
				//检测all stars
				if (g_unlock_bmp==48 &&mAdventureWin) {
					int AllStar=0;
					for (int i=0; i<48; i++)
						AllStar+=g_star_bmp[i];
					float starRatio=(float)AllStar/(48.0*3);
					AddNewAchieve(12, starRatio);
				}
			}
			if (clear>0) {
				if (mGS[0].combo==3)
					AddNewAchieve(13, 100.0);
				if (mGS[0].combo==5)
					AddNewAchieve(14, 100.0);
			}
		}
	}//end SINGLE
	
	//检测NET
	if (mElsMode==ELS_MODE_NET) {
		//printf("\n\nwin id:%d count:%d\n\n",g_net_achieve,g_seats[g_net_achieve].wincount);
		if (clear > 0) {//测试消行
			if (clear!=4)
				m4LineCleared=0;
			else 
				m4LineCleared++;
			
			if (m4LineCleared==2) 
				AddNewAchieve(36, 100.0);
			if (m4LineCleared==3) 
				AddNewAchieve(37, 100.0);
			if (m4LineCleared==4)
				AddNewAchieve(38, 100.0);
			if (m4LineCleared==5)
				AddNewAchieve(39, 100.0);
            
			//检测连击
			if (mGS[0].combo==3) 
				AddNewAchieve(33, 100.0);
			if (mGS[0].combo==5) 
				AddNewAchieve(34, 100.0);
			if (mGS[0].combo==10)
				AddNewAchieve(35, 100.0);
		}
		//网络等级、胜利场次、胜率均由g_net_achieve标记判断，其值在ELSNET中HANDLE_WIN以后改变
		if (g_net_achieve!=-1) {//此时g_net_achieve为自己在此局游戏中的座位
			if (g_seats[g_net_achieve].level==1)
				AddNewAchieve(17, 100.0);
			if (g_seats[g_net_achieve].level==3)
				AddNewAchieve(18, 100.0);
			if (g_seats[g_net_achieve].level==6)
				AddNewAchieve(19, 100.0);
			if (g_seats[g_net_achieve].level==10)
				AddNewAchieve(20, 100.0);
			if (g_seats[g_net_achieve].level==15)
				AddNewAchieve(21, 100.0);
			if (g_seats[g_net_achieve].level==20)
				AddNewAchieve(22, 100.0);
			//胜利场次
			printf("\n\nwin count:%d\n\n",g_seats[g_net_achieve].wincount);
			AddNewAchieve(23, 100.0*(float)g_seats[g_net_achieve].wincount/1.0);
			AddNewAchieve(24, 100.0*(float)g_seats[g_net_achieve].wincount/10.0);
			AddNewAchieve(25, 100.0*(float)g_seats[g_net_achieve].wincount/50.0);
			AddNewAchieve(26, 100.0*(float)g_seats[g_net_achieve].wincount/100.0);
			AddNewAchieve(27, 100.0*(float)g_seats[g_net_achieve].wincount/500.0);
			AddNewAchieve(28, 100.0*(float)g_seats[g_net_achieve].wincount/1000.0);
			//胜率
			if (g_seats[g_net_achieve].totalcount>=50) {//胜率数据在玩50局以上时才有效
				if ((float)g_seats[g_net_achieve].wincount/g_seats[g_net_achieve].totalcount>=0.4)
					AddNewAchieve(29, 100.0);
				if ((float)g_seats[g_net_achieve].wincount/g_seats[g_net_achieve].totalcount>=0.5)
					AddNewAchieve(30, 100.0);
				if ((float)g_seats[g_net_achieve].wincount/g_seats[g_net_achieve].totalcount>=0.7)
					AddNewAchieve(31, 100.0);
				if ((float)g_seats[g_net_achieve].wincount/g_seats[g_net_achieve].totalcount>=0.9)
					AddNewAchieve(32, 100.0);
			}
			g_net_achieve=-1;
		}
	}//end NET
	
	//检测AI
	if (mElsMode==ELS_MODE_AI) {
		int achieveAdj;
		if (mNanDu==0)//easy
			achieveAdj=7;
		else if (mNanDu==2) //hard
			achieveAdj=0;
		if (clear>0) {
			//测试3,5,10连击
			if (mGS[0].combo==3) 
				AddNewAchieve(40+achieveAdj, 100.0);
			if (mGS[0].combo==5) 
				AddNewAchieve(41+achieveAdj, 100.0);
			if (mGS[0].combo==10)
				AddNewAchieve(42+achieveAdj, 100.0);
			
			//测试4连消
			if (clear!=4)
				m4LineCleared=0;
			else 
				m4LineCleared++;
			if (m4LineCleared==2) 
				AddNewAchieve(43+achieveAdj, 100.0);
			if (m4LineCleared==3) 
				AddNewAchieve(44+achieveAdj, 100.0);
			if (m4LineCleared==4) 
				AddNewAchieve(45+achieveAdj, 100.0);
			if (m4LineCleared==5) 
				AddNewAchieve(46+achieveAdj, 100.0);
		}
	}
}

void GameLayerPlayELS::AddNewAchieve(int achieve, float percent)
{
	if (percent>100.0) {
		percent=100.0;
	}
	printf("achieve id:%d, percent:%f\n",achieve,percent);
	/*if (mApp->mGameCenterAvailable!=3) //game centure unavailable.
		return;
	for (int i=0; i<20; i++) {
		if (mApp->mAchieveToSub[i]==0) {//找到第一个空白位置记录
			mApp->mAchieveToSub[i] = achieve;
			mApp->mAchievePercent[i] = percent;
			mApp->isNewAchieve = 1;
			return;
		}
	}*/
	return;
}


void GameLayerPlayELS::FireAchievementMovie(int idx, int achid)
{
	mGS[idx].xunzhang_stage=MAX_XUNZHANG_STAGE;
	mGS[idx].achv_list[mGS[idx].achv_count]=achid;
	mGS[idx].achv_count++;
}
