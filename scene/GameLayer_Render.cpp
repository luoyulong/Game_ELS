//
//  GameLayer_Render.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameLayerPlayELS.h"


void GameLayerPlayELS::drawnum(int num, float x, float y, float angle, float xs, float ys)
{
	char tmp[128];
	snprintf(tmp, 128, "%d", num);
	int lsc=strlen(tmp);
	int ssc=x+9-lsc*9;
	for (int i=0; i<lsc; i++) 
		mRender->RenderImage(mInfoNum[tmp[i]-'0'], ssc+i*18*xs, y, angle, xs, ys);
}









void GameLayerPlayELS::Render(CCRenderBox* Render)
{
    mRender=Render;
	//if(RenderNetInit(dt)) return;			//绘制网络模式下各种等待状态的界面,如果其返回值为真，表示已经通过这个函数绘制了界面，则不需要后面的绘制工作了...
/*
	
    RenderAdventureStat(dt);				//绘制冒险模式的进度条
	RenderBM(0);							//背景动画
						//绘制主游戏框及副游戏框
	RenderScore();							//绘制分数，行数，级别
	
	RenderLevelUp(0);
	
	RenderAttack();							//绘制攻击
	RenderCombo();							//绘制连击
	RenderPause();							//绘制暂停菜单
	RenderWinLose(dt);						//绘制输赢界面
	RenderAchieveMovie();

	
    
    
    RenderHighLight();						//绘制屏幕上方变幻彩灯...
	RenderReplay();							//绘制replay标识,仅在回放模式下生效...
	//printf("g_net_achieve is:%d\n",g_net_achieve);
	if (GameSet->gamemode==ELS_MODE_NET && g_net_achieve!=-1)
		TestAchievement();
*/
    //RenderItem();							//绘制道具
	RenderGameFrame();	
    RenderNextSave(mRender);						//绘制next和save块...
	//mRender->SetColor(1, 1, 1, 1);
	//mFont->DrawString(fuck, 30, 300);
   // mParticleSystem2->Render(0, 0);
    //void GameStatePlay::RenderItem(int idx, float mx, float my, float scale)
    //更改函数为RenderItem(int idx);
    //只Render自己的道具，其他人的道具只是记录但不显示
    
}












inline void GameLayerPlayELS::RenderGameFrame()
{
	RenderMain(0, mainx, mainy, 1.0f,mRender);		
	u8 tmpmode=(GameSet->gamemode==ELS_MODE_REPLAY?mElsRepMode:GameSet->gamemode);
	
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
    
//	int l1x1=100, l1y1=100, l1x2=0;
	int i,j,bi;
	
	//网格...
	if(idx==0)
	{
		mRender->SetColor(0.5f, 0.5f, 0.5f, 0.8f);
	}
	//游戏框
	mRender->SetColor(1, 1, 1, 0.8f);
	
    
    
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
	

}







inline float GameLayerPlayELS::get_adjy_bygrect(int idx)
{
	if (ELS_PAUSE) 
		return 0;
	
	if(mGS[idx].game_over)
		return 0;
	
	float adjy = 0;
	int grs    = Annimation_layer->fallstat[idx];//grect-200;
	int range  = (240-180)/2;
	int rdm    = 16;
	if (grs>0) 
	{
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


