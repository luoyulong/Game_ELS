//
//  GameLayer_Render.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameLayerPlayELS.h"













void GameLayerPlayELS::Render(CCRenderBox* mRender)
{
    this->mRender=mRender;
	//if(RenderNetInit(dt)) return;			//绘制网络模式下各种等待状态的界面,如果其返回值为真，表示已经通过这个函数绘制了界面，则不需要后面的绘制工作了...
/*
	
    RenderAdventureStat(dt);				//绘制冒险模式的进度条
	RenderBM(0);							//背景动画
						//绘制主游戏框及副游戏框
	RenderScore();							//绘制分数，行数，级别
	
	RenderLevelUp(0);
	RenderItem();							//绘制道具
	RenderAttack();							//绘制攻击
	RenderCombo();							//绘制连击
	RenderPause();							//绘制暂停菜单
	RenderWinLose(dt);						//绘制输赢界面
	RenderAchieveMovie();

	
    
    
    RenderHighLight();						//绘制屏幕上方变幻彩灯...
	RenderReplay();							//绘制replay标识,仅在回放模式下生效...
	//printf("g_net_achieve is:%d\n",g_net_achieve);
	if (mElsMode==ELS_MODE_NET && g_net_achieve!=-1)
		TestAchievement();
*/
	RenderGameFrame();	
    RenderNextSave(mRender);						//绘制next和save块...
	//mRender->SetColor(1, 1, 1, 1);
	//mFont->DrawString(fuck, 30, 300);
   // mParticleSystem2->Render(0, 0);
}



inline void GameLayerPlayELS::RenderGameFrame()
{
	RenderMain(0, mainx, mainy, 1.0f,mRender);		
	u8 tmpmode=(mElsMode==ELS_MODE_REPLAY?mElsRepMode:mElsMode);
	
	if(tmpmode==ELS_MODE_SINGLE && mBJIdx==0)
	{
		//RenderClassicRightSide();
	}
	if (tmpmode==ELS_MODE_SINGLE && mBJIdx!=0) 
	{
		//RenderAdventureRightSide();
		
	}
	if (tmpmode==ELS_MODE_AI)
	{
		RenderMain(1, sidex1,   sidey1, sidesc,mRender);
		//RenderAiRightSide();
	}
	if (tmpmode==ELS_MODE_NET) 
	{
		RenderMain(1, sidex1,   sidey1, sidesc,mRender);
		RenderMain(2, sidex2,   sidey2,	sidesc,mRender);
		RenderMain(3, sidex3,   sidey3, sidesc,mRender);
		mRender->SetColor(1,1,1,tablestra);
		char tmp[256];
		GetTableString(tmp);
		mLFont->DrawString(tmp, tablestrx, tablestry);
	}
}






void GameLayerPlayELS::RenderNextSave(CCRenderBox* mRender)
{
    
    
 
	mRender->RenderImage(mBgNS[0], mainx+238-10, mainy+113+get_adjy_bygrect(0));
	int i, j;
	float moveAdj;
	moveAdj = sin((mGS[0].block_change_time/BLK_CHANGE_TIME)*1.57)*30;
	//绘制next和save块
	mRender->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{	
			//mRender->SetColor(1.0f, 1.0f, 1.0f, moveAlpha/2.0 +0.5f);
			//if (mGS[0].block_change_time<=(BLK_CHANGE_TIME/2.0))
			rns(mBlockQueue[(mGS[0].block_index+1)%MAXBLKQUEUE], 0.45f, nextx, nexty, i, j, moveAdj,mRender);
			rns(mBlockQueue[(mGS[0].block_index+2)%MAXBLKQUEUE], 0.25f, nextx-62, nexty+10,  i, j, moveAdj,mRender);
			if (moveAdj <= 20)
				rns(mBlockQueue[(mGS[0].block_index+3)%MAXBLKQUEUE], 0.25f, nextx-124, nexty+10, i, j, moveAdj,mRender);
			if(mGS[0].save_block>=0)
				rns(mGS[0].save_block, 0.45f, savex, savey, i, j, 0,mRender);
		}
	//绘制hold时高亮显示的东东
	//to be continued.
	mRender->RenderImage(mBgNS[1], mainx+237, mainy+113+get_adjy_bygrect(0));
}



void GameLayerPlayELS::RenderMain(int idx, float boxx, float boxy, float boxs,CCRenderBox* mRender)
{
	int l1x1=100, l1y1=100, l1x2=0;
	int i,j,bi;
	
	//网格...
	if(idx==0)
	{
		mRender->SetColor(0.5f, 0.5f, 0.5f, 0.8f);
	}
	//游戏框
	mRender->SetColor(1, 1, 1, 0.8f);
	/*if(idx==0)
		mRender->RenderImage(mBgTK, boxx+237, boxy+467+get_adjy_bygrect(idx));
	else 
		mRender->RenderImage(mBgTKSmall, boxx+77, boxy+173.0f+get_adjy_bygrect(idx)*boxs);
	*/
    
    
	//方块画在框的下面
	//画预估方块直落后的影子
  	if(mGS[idx].tdy && idx==0)// && g_options[4])
	{
		int x=mGS[idx].tdx;
		int y=mGS[idx].tdy;
		int z=mGS[idx].cur_z;
        mRender->SetColor(0.65f, 0.65f, 0.65f, 0.5f);
		for (i=0; i<4; i++) {
			for (j=0; j<4; j++) {
				int type=mGS[idx].cur_block;
				if(blkdat[type][z][i*4+j])
				{
                    
                    mRender->RenderImage(mBLK[blkdat[type][z][i*4+j]-1], 
										 boxx+(blkadjx+(x+j-2)*blksize)*boxs, boxy+(blkadjy+(y+i)*blksize)*boxs, 0, boxs, boxs);
				}
			}
		}
	}
	
	//画主区域方块及扫描光带...
	for(i=0;i<ZONG;i++)
	{
		bool fflag0=false;
		
		if(Annimation_layer->ClearRowstat[idx]>0)
			for(int fm=0;fm<mGS[idx].full_rows_count%100;fm++)
				if(i==mGS[idx].fullrows[fm])
				{
					fflag0=true;
					break;
				}
		for(j=0;j<HENG;j++)
		{
			int rex = boxx+(blkadjx+j*blksize)*boxs;
			int rey = boxy+(blkadjy+i*blksize)*boxs;
			
			bi=mGS[idx].grid[i][2+j]%100;
			
			//绘制小方块:正常，gameover灰块，道具
			
            mRender->SetColor(1.0f, 1.0f, 1.0f, fflag0?
							  ((Annimation_layer->ClearRowstat[idx])/(Annimation_layer->ClearRow_displaylength*0.8f))://满行淡出效果
							  1.0f);
			if(bi>0)
			{
				if(bi<50)
				{
                    assert(bi<12);
					if(!mGS[idx].game_over)
						mRender->RenderImage(mBLK[bi-1], rex, rey+get_adjy_bygrect(idx), 0, boxs, boxs);
					else
						mRender->RenderImage(mBLK[10], rex, rey+get_adjy_bygrect(idx), 0, boxs, boxs);
				}
				else
				{
					mRender->RenderImage(mItemBLK[bi-50], rex, rey+get_adjy_bygrect(idx), 0, boxs, boxs);
				}
			}
		}
		
			}
	
    
    
    
	
	//绘制粘住光晕及两侧烟尘...
	if(idx==0)
	{
		if (mGS[idx].cling_stage!=0)
		{
			mRender->EnableAddictiveDraw(true);
			for (int ci=0; ci<mGS[idx].cling_count; ci++)
			{
				int clingx = mGS[idx].cling_blocks[ci][0], clingy=mGS[idx].cling_blocks[ci][1];
				int cval   = mGS[idx].grid[clingy][clingx+2];
				int cidx   = mGS[idx].cling_stage/8%5;
				if(cval==0) continue;
				int rex = boxx+(blkadjx+clingx*blksize)*boxs;
				int rey = boxy+(blkadjy+clingy*blksize)*boxs;
				mRender->SetColor(1, 1, 1, (float)mGS[idx].cling_stage/MAX_CLING_STAGE);
				mRender->RenderImage(mXuanZhuan[cidx], rex, rey);
			}
			mRender->EnableAddictiveDraw(false);
		}
	}
	
	//绘制玩家名字...
	if (idx==0)
		mRender->SetColor(0.25f, 0.75f, 1, 0.95f);
	u8 tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
	if (tmode==ELS_MODE_NET) 
	{
		if (isRobotGame()) 
		{
			if(idx==1) mRender->SetColor(1, 0, 1, 0.8f);
			if(idx==2) mRender->SetColor(0.1f, 0.1f, 0.1f, 0.8f);
			if(idx==3) mRender->SetColor(0.1f, 0.1f, 0.1f, 0.8f);
		}
		else 
		{
			if (idx==1)
			{
				if(g_seats[GetSeatIdByidx(1)-1].userid!=0)
					mRender->SetColor(1, 0, 1, 0.8f);
				else 
					mRender->SetColor(0.1f, 0.1f, 0.1f, 1);
			}
			if (idx==2)
			{
				if(g_seats[GetSeatIdByidx(2)-1].userid!=0)
					mRender->SetColor(0, 1, 1, 0.8f);
				else 
					mRender->SetColor(0.1f, 0.1f, 0.1f, 1);
			}
			if (idx==3)
			{
				if(g_seats[GetSeatIdByidx(3)-1].userid!=0)
					mRender->SetColor(1, 1, 0, 0.8f);
				else 
					mRender->SetColor(0.1f, 0.1f, 0.1f, 1);
			}
		}
		
		//background
		CCImage *tmpnbk=idx?mNameSBk:mNameBk;
		int ax=idx?75:234, ay=idx?276:838;
		mRender->RenderImage(tmpnbk, boxx+ax, boxy+ay+get_adjy_bygrect(idx)*boxs);
		
		//name
		char tmpname[128];
		int  seatid=GetSeatIdByidx(idx);
		if (isRobotGame()&&idx==1) seatid=1;//机器人seatid肯定是1，idx肯定是1
		CCFont *tmpfont=idx?mBFont:mLFont;
		ax=idx?80:235, ay=idx?264:828;
		if(isRobotGame())
		{
			if (idx==0) {
				snprintf(tmpname, 128, "%s", g_seats[seatid-1].name);
				mRender->SetColor(1, 1, 1, 1);
				tmpfont->DrawCString(tmpname, boxx+ax, boxy+ay+get_adjy_bygrect(idx)*boxs+3);
			}
			else if (idx==1 && mRandomSeed!=0) {
				snprintf(tmpname, 128, "%s", g_robotname[mRandomSeed%235]);
				mRender->SetColor(1, 1, 1, 1);
				int adjtx=(strlen(tmpname)-6)*4;
				float tx=boxx+ax-32-adjtx;
				//printf("%d,%s,%d,%f\n",mRandomSeed%235,tmpname,adjtx,tx);
				tmpfont->DrawString(tmpname, tx, boxy+ay+get_adjy_bygrect(idx)*boxs+1);
			}
			else {
				snprintf(tmpname, 128, "%s", "no player");
				mRender->SetColor(1, 1, 1, 0.6f);
				mBFont->DrawString(tmpname, boxx+36, boxy+160);
			}
		}
		else 
		{
			if(g_seats[seatid-1].userid!=0)
			{
				snprintf(tmpname, 128, "%s", g_seats[seatid-1].name);
				mRender->SetColor(1, 1, 1, 1);
				//if (idx<=1 || !isRobotGame())
				//{
                //printf("idx=%d boxx=%f ax=%d adjnamex=%d x=%f\n", idx, boxx, ax, adjnamex, boxx+ax-adjnamex);
                tmpfont->DrawCString(tmpname, boxx+ax, boxy+ay+get_adjy_bygrect(idx)*boxs+3);
				//}
			}
			else {
				snprintf(tmpname, 128, "%s", "no player");
				mRender->SetColor(1, 1, 1, 0.6f);
				mBFont->DrawString(tmpname, boxx+36, boxy+160);
			}
		}
	}
	if (tmode==ELS_MODE_AI) 
	{
		//background
		CCImage *tmpnbk=idx?mNameSBk:mNameBk;
		int ax=idx?75:234, ay=idx?276:840;
		if(idx==1) mRender->SetColor(1, 0, 1, 0.8f);
		mRender->RenderImage(tmpnbk, boxx+ax, boxy+ay+get_adjy_bygrect(idx)*boxs);
		
		//name
		mRender->SetColor(1, 1, 1, 1);
		char tmpname[2][64]={"Fighting Offline", "Robot.AI"};
		CCFont *tmpfont=idx?mBFont:mLFont;
		ax=idx?40:168, ay=idx?264:828;
		tmpfont->DrawString(tmpname[idx], boxx+ax, boxy+ay+get_adjy_bygrect(idx)*boxs);
	}
	if (tmode==ELS_MODE_SINGLE) 
	{
		//only idx 0
		mRender->RenderImage(mNameBk, boxx+234, boxy+840+get_adjy_bygrect(idx));
		mRender->SetColor(1, 1, 1, 1);
		mLFont->DrawString("Classic Mode", boxx+168, boxy+828+get_adjy_bygrect(idx)*boxs);
		//冒险模式下倒数第二行的高光条
		if (mBJIdx!=0) {
			//绘制倒数第二行的高光条
			//mRender->SetColor(1.0f,1.0f,1.0f,1.0f);
			mRender->EnableAddictiveDraw(true);
			//int nn=mStage%200;
			float alp=-1*pow((float)(mStage%300)/150.0-1, 2)+1.0;
			mRender->SetColor(1.0f, 1.0f, 1.0f, 0.5+0.5*alp);
			mRender->RenderImage(m2ndhlight, 235, 741);
			mRender->EnableAddictiveDraw(false);
			//mRender->SetColor(1.0f,1.0f,1.0f,1.0f);
		}
	}
}







inline float GameLayerPlayELS::get_adjy_bygrect(int idx)
{
	if (ELS_PAUSE) 
		return 0;
	
	if(mGS[idx].game_over)
		return 0;
	
   // printf("clearrowstat is  %f",Annimation_layer->ClearRowstat[idx]);
	//int grect = mGS[idx].grect_stage;
	float adjy = 0;
	int grs    = Annimation_layer->fallstat[idx];//grect-200;
	int range  = (240-180)/2;
	int rdm    = 16;
	if (grs>0) 
	{
        printf("---grs is %d\n",grs);
		if (grs<=range) 
			adjy=blksize*(grs*1.0f/range)-rdm/2+rand()%rdm;
		else 
			adjy=blksize*(1.0f-(grs-range)*1.0f/range)-rdm/2+rand()%rdm;
		if (grs/6%2) {
			//printf("adjy set to 0..................%d\n", grs/6);
			adjy=0;
		}
	}
	
	return adjy;
}


inline void GameLayerPlayELS::rns(s8 bt, float sf, float adjx, float adjy, int i, int j, float moveAdj,CCRenderBox* mRender)
{
	float bc=blksize*sf;
	if(blkdat[bt][0][i*4+j]) 
		mRender->RenderImage(mBLK[blkdat[bt][0][i*4+j]-1], 
                             adjx+j*bc+blkadj[bt][0]*bc - moveAdj, 
                             adjy+i*bc+blkadj[bt][1]*bc, 0, sf, sf);
}


