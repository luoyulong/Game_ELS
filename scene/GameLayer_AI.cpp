/*
 *  ELSAI.h
 *  GameBox
 *
 *  Created by xing zip on 11-2-17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameLayerPlayELS.h"
//#define ELS_DEBUG 

#ifdef ELS_DEBUG
FILE  *g_fp;
#endif

//布局评分

inline int  GameLayerPlayELS::GetGridScore(int cx, int cy, int cf, int nf)
{
	int score=5000, i, xiagu[HENG], xiagu_count=0, xiagu_total=0;
	int hole_count=0, top_total=0;
	int cfsco[5] = {0, -350, -320, 8, 12};
	//int cfsco[5]		= {0, -250, -220, 8, 12};
	int cfsco_safe[5]	= {0, 200, 240, 360, 480};
	
	
	//计算总空
	for(i=0;i<HENG;i++)
	{
		hole_count+=mGS[1].col_hole[i];
		top_total+=mGS[1].col_top[i]*10;
		
		xiagu[i]=0;
		if(i==0)
		{
			if(mGS[1].col_top[1]>mGS[1].col_top[0])
				xiagu[i]=mGS[1].col_top[1]-mGS[1].col_top[0];
		}
		else if(i==HENG-1)
		{
			if(mGS[1].col_top[i-1]>mGS[1].col_top[i])
				xiagu[i]=mGS[1].col_top[i-1]-mGS[1].col_top[i];
		}
		else
		{
			if((mGS[1].col_top[i+1]>mGS[1].col_top[i]) && (mGS[1].col_top[i-1]>mGS[1].col_top[i]))
				xiagu[i]=min(mGS[1].col_top[i-1],mGS[1].col_top[i+1])-mGS[1].col_top[i];
		}
		if(xiagu[i]>2)
			xiagu_count++;
		xiagu_total+=xiagu[i];
	}
	
	//计算平均行高,计算行高方差
	int top_avg = top_total/HENG;
	int fangcha = 0;
	for(i=0;i<HENG;i++)
	{
		int t=mGS[1].col_top[i]*10-top_avg;
		fangcha+=(t*t);
	}
	
	fangcha=fangcha/10;
	
	//鼓励靠边...
	score += ((cx-5)*(cx-5)+(mGS[1].cur_x-5)*(mGS[1].cur_x-5))*5;
	
	//进攻模式不鼓励只消一两行，鼓励消掉两行以上
	if(mGS[1].safe_mode)
		score += cfsco_safe[cf]*20+cfsco_safe[nf]*20;
	else			
		score += cfsco[cf]*20+cfsco[nf]*20;
	
	//局面越低约均衡越好
	if(mGS[1].safe_mode)
		score -= top_avg*300;
	else 
		score -= top_avg*30;
	score -= fangcha*5;
	
	//空洞越少越好
	if(mGS[1].safe_mode)
		score -= hole_count*700;
	else
		score -= hole_count*750;
	
	//连击加分
	if(mGS[1].combo>2)
	{
		score += mGS[1].combo*100000;
		//printf("COMBO %d score=%d\n", mGS[1].combo, score);
	}
	else
		score += mGS[1].combo*2500;
	
	//峡谷越少越好，有一个大峡谷不怕，怕出现两个峡谷
	if(xiagu_count>=2)
		score-=500*xiagu_total;
    
#ifdef ELS_DEBUG
	if (g_fp==NULL) 
		g_fp=fopen("/Users/xingzip/Desktop/mmino/trunk/AIDebug/els.log", "w+");
	
	int m,n;
	//char tmps[32];
	for(m=0;m<ZONG;m++)
	{		
		/*for(n=0;n<HENG;n++)
         {
         if(mGS[1].grid[m][n+2])
         tmps[n]='0'+mGS[1].grid[m][n+2]%50;
         else
         tmps[n]='.';
         }
         tmps[n]=0;
         fprintf(g_fp, "%s\n", tmps);*/
		for(n=0;n<HENG;n++)
		{
			fprintf(g_fp, "%03d  ", mGS[1].grid[m][n+2]);
		}
		//tmps[n]=0;
		fprintf(g_fp, "\n");
	}
	fprintf(g_fp, "top=%d,atop=%d,fc=%d,xgc=%d,xgt=%d,b1x=%d,b2x=%d,b1f=%d,b2f=%d,  (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)|score=%d\n",
            
            mGS[1].top_line, 
            top_avg,
            fangcha,
            xiagu_count,
            xiagu_total,
            cx, mGS[1].cur_x, 
            cf, mGS[1].full_rows_count,
            
            mGS[1].col_top[0],mGS[1].col_top[1],mGS[1].col_top[2],mGS[1].col_top[3],
            mGS[1].col_top[4],mGS[1].col_top[5],mGS[1].col_top[6],mGS[1].col_top[7],
            mGS[1].col_top[8],mGS[1].col_top[9],
            
            mGS[1].col_hole[0],mGS[1].col_hole[1],mGS[1].col_hole[2],mGS[1].col_hole[3],
            mGS[1].col_hole[4],mGS[1].col_hole[5],mGS[1].col_hole[6],mGS[1].col_hole[7],
            mGS[1].col_hole[8],mGS[1].col_hole[9],
            
            xiagu[0],xiagu[1],xiagu[2],xiagu[3],xiagu[4],xiagu[5],xiagu[6],
            xiagu[7],xiagu[8],xiagu[9], score);
#endif
	
	return score;		
}

inline void GameLayerPlayELS::AI_F3(char *tActQueue, s8 cx, s8 cy, s8 cf, int *ms)
{
	int s, nf;
	GSTAT b;
	char bq[32];
	b=mGS[1];	
	sprintf(bq, "%s", tActQueue);
	//直接下落
	while(MoveBlk(DDOWN, 1, true)!=REACH_BOTTOM);
	strcat(tActQueue, "W");
	nf = mGS[1].full_rows_count;
	mGS[1].clear_stage=(SET_CLEAR_STAGE-REND_CLEAR_STAGE);
	ClearFullRows(1, true);
	s = GetGridScore(cx, cy, cf, nf);	
	if(s>*ms) 
	{
		sprintf(mActQueue, "%sN", tActQueue);
		*ms=s;
	}	
	mGS[1]=b;
	sprintf(tActQueue, "%s", bq);	
}

inline void GameLayerPlayELS::AI_F1(char *tActQueue, s8 cx, s8 cy, s8 cf, int *ms, 
								 void (GameLayerPlayELS::*fs)(char *, s8, s8, s8, int *))
{
	GSTAT b1,b2,b3;
	char  bq[32],bq1[32],bq2[32];
	int   s2,nz,n,x2;
	
	b1 = mGS[1];
	sprintf(bq, "%s", tActQueue);	
	int tmpz = block_zcount[mGS[1].cur_block];
	int tmpsave = tmpz<4?1:0;
	
	for(s2=0; s2<=tmpsave; s2++)
	{
		mGS[1] = b1;
		sprintf(tActQueue, "%s", bq);
		if(s2)
		{
			strcat(tActQueue, "S");
			SaveBlk(1, true);
		}
		b2 = mGS[1];
		sprintf(bq1, "%s", tActQueue);
		
		for(nz=0; nz<tmpz; nz++)
		{
			mGS[1] = b2;
			sprintf(tActQueue, "%s", bq1);
			//旋转
			for(n=0; n<nz; n++)
			{
				strcat(tActQueue, "T");
				MoveBlk(TURN, 1, true);
			}
			
			b3 = mGS[1];
			sprintf(bq2, "%s", tActQueue);
			
			for(x2=0;x2<3;x2++)
			{
				mGS[1] = b3;
				sprintf(tActQueue, "%s", bq2);
				//左移
				if(x2==1)					
					while(MoveBlk(LEFT, 1, true)!=REACH_BORDER)
					{
						strcat(tActQueue, "L");
						(this->*fs)(tActQueue, cx, cy, cf, ms);
					}
				//右移
				if(x2==2)					
					while(MoveBlk(RIGHT, 1, true)!=REACH_BORDER)
					{
						strcat(tActQueue, "R");
						(this->*fs)(tActQueue, cx, cy, cf, ms);
					}					
				if(x2==0)
					(this->*fs)(tActQueue, cx, cy, cf, ms);
			}					
		}
	}
}

inline void GameLayerPlayELS::AI_F2(char *tActQueue, s8 cxs, s8 cys, s8 cfs, int *ms) 
{
	s8 cx, cy, cf;
	GSTAT b0;
	char bq0[32];
	
	//保存现场
	b0=mGS[1];
	sprintf(bq0, "%s", tActQueue);
	
	//直接下落
	while(MoveBlk(DDOWN, 1, true)!=REACH_BOTTOM);
	strcat(tActQueue, "W");
	cf = mGS[1].full_rows_count;
	mGS[1].clear_stage=(SET_CLEAR_STAGE-REND_CLEAR_STAGE);
	ClearFullRows(1, true);
	cx = mGS[1].cur_x;	
	cy = mGS[1].cur_y;
	NextBlk(1, true);
	strcat(tActQueue, "N");
	
	GetGridScore(0, 0, 0, cf);
	AI_F1(tActQueue, cx, cy, cf, ms, &GameLayerPlayELS::AI_F3);	
	
	//恢复现场
	mGS[1]=b0;
	sprintf(tActQueue, "%s", bq0);
}

void GameLayerPlayELS::PlayAIAction(float dt)
{
	if (mCountDownTimeLeft > 0.0)
		return;
	//AI动作
	if(mAiTempo>AI_SPEED[mNanDu])
	{
		char aiact = GetAIAct();
		//printf("AIACT=%c\n", aiact);
		char ts[2];
		ts[0]=aiact, ts[1]=0;
		//RecordAction(1, ts);
		PlayActionBase(ts, 1);
		mAiTempo=0;
	}
	else {
		mAiTempo+=dt;
	}	
}

//如果自动运行动作序列为空则计算生成指令序列，否则返回动作指令	
char GameLayerPlayELS::GetAIAct()
{
	int   len = strlen(mActQueue);		
	char  tActQueue[32];
	static int maxScore = -3000000;
	GSTAT b;	
	
	//需要计算自动队列了
	if(len==0)
	{
		//保存现场
		b = mGS[1];
		tActQueue[0]=0;
		
		mGS[1].safe_mode = (mGS[1].top_line>mSafeTop);
		AI_F1(tActQueue, 0, 0, 0, &maxScore, &GameLayerPlayELS::AI_F2);
		//printf("MaxScore:%d(%s)\n", maxScore, mActQueue);
#ifdef ELS_DEBUG		
		fprintf(g_fp, "MaxScore:%d(%s)\n", maxScore, mActQueue);
#endif
		mGS[1]=b;
		maxScore = -3000000;	
	}
	
	//取走第一个动作码，返回
	char cret = mActQueue[0];
	sprintf(mActQueue, "%s", &mActQueue[1]);
	return cret;
}