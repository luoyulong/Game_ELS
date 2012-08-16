//
//  GameLayer_Item.cpp
//  ThreeCard
//
//  Created by tuyoo on 12-8-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
/*
 *  ELSItem.h
 *  GameBox
 *
 *  Created by xing zip on 11-2-27.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameLayerPlayELS.h"

//使用后消除最下面的n行
void GameLayerPlayELS::ItemSubNLines(int idx, int lines)
{
	int m, n;
	GSTAT *gp;
	
	gp = &mGS[idx];
	int fillcount=0;
	for(m=ZONG-lines;m<ZONG;m++)
	{
		int nullflag=1;
		for(n=0;n<HENG;n++)
		{
			if (gp->grid[m][n+2])
			{
				nullflag=0;
				break;
			}
		}
		if (!nullflag) {
			for(n=0;n<HENG;n++)
				gp->grid[m][n+2]=109;
			gp->fullrows[fillcount]=m;
			fillcount++;
		}
		printf("\n");
	}
	if(fillcount)
	{
		gp->full_rows_count=fillcount+100; //加上100，是为了让clearfullrows知道，这是道具造成的满行，不要加攻击，不要加道具
		Annimation_layer->New_ClearRow(0);
        
      //  gp->clear_stage=SET_CLEAR_STAGE;
	}
}

void GameLayerPlayELS::ItemPlusNLines(int idx,int lines)
{
	//Attack(idx,lines,0);
}


//使用后把所有空洞塌缩填满

void GameLayerPlayELS::ItemCompress(int idx)
{
	int m, n, fullflag;
	GSTAT *gp;
	
	gp = &mGS[idx];
	
	for (n=0; n<HENG; n++) {
		u8 col[ZONG];
		int cidx=0;
		memset(col, 0, ZONG);
		for (m=ZONG-1; m>=0; m--) {
			u8 blk=gp->grid[m][n+2];
			if(blk>100)
				col[cidx++]=blk;
		}
		for (m=ZONG-1; m>=0; m--) 
			gp->grid[m][n+2]=col[ZONG-m-1];
	}
	
	for (m=0; m<ZONG; m++)
	{
		fullflag=1;
		for (n=0; n<HENG; n++) {
			u8 blk=gp->grid[m][n+2];
			if (blk==0) {
				fullflag=0;
				break;
			}
		}
		if (fullflag) {
			gp->fullrows[gp->full_rows_count++]=m;
		}
	}
	
	if (gp->full_rows_count) {
		gp->full_rows_count+=100;
		gp->clear_stage=SET_CLEAR_STAGE;
	}
	
	printf("%d\n", gp->full_rows_count);
}

//使用后把中间的三行空出

void GameLayerPlayELS::ItemHammer(int idx)
{
	int m, n;
	GSTAT *gp;
	
	gp = &mGS[idx];
	
	for (n=0; n<HENG; n++) {
		u8 col[ZONG];
		memset(col, 0, ZONG);
		/*
         //压实其他列
         int cidx=0;
         if(n<4 || n>6)
         {
         for (m=ZONG-1; m>=0; m--) {
         u8 blk=gp->grid[m][n+2];
         if(blk>100)
         col[cidx++]=blk;
         }
         }
         */
		if (n>=4 && n<=6) {
			for (m=ZONG-1; m>=0; m--) 
				gp->grid[m][n+2]=col[ZONG-m-1];
		}
	}	
}
void GameLayerPlayELS::ItemShield(int idx)
{
	GSTAT *gp;
	gp = &mGS[idx];
	if (gp->shield_remain_time < 100)
		gp->shield_remain_time=100;
	
	printf("use item:Shield.\n");
}
void GameLayerPlayELS::ItemBlock(int idx)
{
	GSTAT *gp;
	gp = &mGS[idx];
	gp->face_remain_time=180;
	printf("use item:BlockFace.\n");
}
