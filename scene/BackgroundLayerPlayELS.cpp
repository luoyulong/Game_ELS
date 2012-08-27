//
//  BackgroundLayerPlayELS.cpp
//  ThreeCard
//
//  Created by tuyoo on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BackgroundLayerPlayELS.h"

BackgroundLayerPlayELS::BackgroundLayerPlayELS()
{
    init=false;
    
  
    GEScene* pScene = GEDirector::GetInstance()->getScene("GameScenePlayELS");
   
    pScene->addChild(this,45);
     mSnow=mAssetCommon->GetImage("newsnow.png");
    GEImage * m_pBackGround = new GEImage();
    m_pBackGround->setImage("playback.png");
    m_pBackGround->setPosition(320,480);   
  //  this->addChild(m_pBackGround);   
    
   
    
     Background_playboard(0, mainx, mainy, 1.0f);
    
}


void BackgroundLayerPlayELS::Background_playboard(int idx,float boxx,float boxy,float boxs)
{
    
    for (int i=0; i<4; i++) {
        Playboard[i]=new GEImage();
        if(!i)Playboard[i]->setImage("kuang.png");
        else Playboard[i]->setImage(mAssetCommon->GetImage("skuang.png"));
    }
    Playboard[0]->setPosition(mainx+237,mainy+471+Game_layer->get_adjy_bygrect(0));
    this->addChild(Playboard[0]);
    
    GEText * mBFont=new GEText();
    GEText * mLFont=new GEText();
    
    
    u8 tmode=(mElsMode==ELS_MODE_REPLAY)?mElsRepMode:mElsMode;
    /*if (tmode==ELS_MODE_NET) 
	{
		if (Game_layer->isRobotGame()) 
		{
			if(idx==1) mRender->SetColor(1, 0, 1, 0.8f);
			if(idx==2) mRender->SetColor(0.1f, 0.1f, 0.1f, 0.8f);
			if(idx==3) mRender->SetColor(0.1f, 0.1f, 0.1f, 0.8f);
		}
		else 
		{
			if (idx==1)
			{
				if(g_seats[Game_layer->GetSeatIdByidx(1)-1].userid!=0)
					mRender->SetColor(1, 0, 1, 0.8f);
				else 
					mRender->SetColor(0.1f, 0.1f, 0.1f, 1);
			}
			if (idx==2)
			{
				if(g_seats[Game_layer->GetSeatIdByidx(2)-1].userid!=0)
					mRender->SetColor(0, 1, 1, 0.8f);
				else 
					mRender->SetColor(0.1f, 0.1f, 0.1f, 1);
			}
			if (idx==3)
			{
				if(g_seats[Game_layer->GetSeatIdByidx(3)-1].userid!=0)
					mRender->SetColor(1, 1, 0, 0.8f);
				else 
					mRender->SetColor(0.1f, 0.1f, 0.1f, 1);
			}
		}
		
		//background
		CCImage *tmpnbk=idx?mNameSBk:mNameBk;
		int ax=idx?75:234, ay=idx?276:838;
		mRender->RenderImage(tmpnbk, boxx+ax, boxy+ay+Game_layer->get_adjy_bygrect(idx)*boxs);
		
		//name
		char tmpname[128];
		int  seatid=Game_layer->GetSeatIdByidx(idx);
		if (Game_layer->isRobotGame()&&idx==1) seatid=1;//机器人seatid肯定是1，idx肯定是1
		CCFont *tmpfont=idx?mBFont:mLFont;
		ax=idx?80:235, ay=idx?264:828;
		if(Game_layer->isRobotGame())
		{
			if (idx==0) {
				snprintf(tmpname, 128, "%s", g_seats[seatid-1].name);
				mRender->SetColor(1, 1, 1, 1);
				tmpfont->DrawCString(tmpname, boxx+ax, boxy+ay+Game_layer->get_adjy_bygrect(idx)*boxs+3);
			}
			else if (idx==1 && mRandomSeed!=0) {
				snprintf(tmpname, 128, "%s", g_robotname[mRandomSeed%235]);
				mRender->SetColor(1, 1, 1, 1);
				int adjtx=(strlen(tmpname)-6)*4;
				float tx=boxx+ax-32-adjtx;
				//printf("%d,%s,%d,%f\n",mRandomSeed%235,tmpname,adjtx,tx);
				tmpfont->DrawString(tmpname, tx, boxy+ay+Game_layer->get_adjy_bygrect(idx)*boxs+1);
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
                tmpfont->DrawCString(tmpname, boxx+ax, boxy+ay+Game_layer->get_adjy_bygrect(idx)*boxs+3);
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
		mRender->RenderImage(tmpnbk, boxx+ax, boxy+ay+Game_layer->get_adjy_bygrect(idx)*boxs);
		
		//name
		mRender->SetColor(1, 1, 1, 1);
		char tmpname[2][64]={"Fighting Offline", "Robot.AI"};
		CCFont *tmpfont=idx?mBFont:mLFont;
		ax=idx?40:168, ay=idx?264:828;
		tmpfont->DrawString(tmpname[idx], boxx+ax, boxy+ay+Game_layer->get_adjy_bygrect(idx)*boxs);
	}*/
	if (tmode==ELS_MODE_SINGLE) 
	{
		//only idx 0
		Namebk=new GEImage();
        Namebk->setImage(Game_layer->mNameBk);
        Namebk->setPosition(boxx+234, boxy+840+Game_layer->get_adjy_bygrect(idx));
        this->addChild(Namebk);
        
        mLFont->setText("Classic Mode");
        mLFont->setPosition(boxx+128, boxy+828+Game_layer->get_adjy_bygrect(idx)*boxs);
		//mLFont->DrawString("Classic Mode", boxx+128, boxy+828+Game_layer->get_adjy_bygrect(idx)*boxs);
		//冒险模式下倒数第二行的高光条
	/*	if (mBJIdx!=0) {
			//绘制倒数第二行的高光条
			//mRender->SetColor(1.0f,1.0f,1.0f,1.0f);
			mRender->EnableAddictiveDraw(true);
			//int nn=mStage%200;
			float alp=1;//=-1*pow((float)(mStage%300)/150.0-1, 2)+1.0;
			mRender->SetColor(1.0f, 1.0f, 1.0f, 0.5+0.5*alp);
			//mRender->RenderImage(m2ndhlight, 235, 741);
			mRender->EnableAddictiveDraw(false);
			//mRender->SetColor(1.0f,1.0f,1.0f,1.0f);
		}*/
	}
}
void BackgroundLayerPlayELS::Background_Snow(CCRenderBox* mRender,int dir)
{
    if (!init) {
		for (int i=0; i<SNOW_COUNT; i++) {
			gs_bm_snow[i].scale = rand()%100/100.0f;
			gs_bm_snow[i].alpha = rand()%100/100.0f;			
			gs_bm_snow[i].speed = (rand()%100/100.0f+0.5)*2;
			gs_bm_snow[i].arc_speed = rand()%5/100.0f;
			gs_bm_snow[i].angle = (rand()%100/100.0f+0.5)*3.1415926f/2.0f;
			gs_bm_snow[i].x     = (rand()%4)*160+80;
			gs_bm_snow[i].y     = rand()%100/100.0f*960.0f;
			gs_bm_snow[i].r     = rand()%100/100.0f;
			gs_bm_snow[i].g     = rand()%100/100.0f;
			gs_bm_snow[i].b     = rand()%100/100.0f;			
			gs_bm_snow[i].arc   = 0;
			gs_bm_snow[i].stage = 200;
			init=true;
		}
	}
    
    
    else {
		for (int i=0; i<SNOW_COUNT; i++) {
			bool reborn;
			
			if (dir) 
				reborn=(gs_bm_snow[i].x<0.0f || gs_bm_snow[i].y<0.0f);
			else 
				reborn=(gs_bm_snow[i].x>640.0f || gs_bm_snow[i].y>960.0f);
			
			if (reborn) {
				gs_bm_snow[i].scale = rand()%100/100.0f;
				gs_bm_snow[i].alpha = rand()%100/100.0f;			
				gs_bm_snow[i].speed = (rand()%100/100.0f+0.5)*2;
				gs_bm_snow[i].arc_speed = rand()%5/100.0f;
				gs_bm_snow[i].angle = (rand()%100/100.0f+0.5)*3.1415926f/2.0f;
				//gs_bm_snow[i].x     = rand()%100/100.0f*640.0f;
				gs_bm_snow[i].x     = (rand()%4)*160+80;
				gs_bm_snow[i].y     = dir?960.0f:0.0f;
				gs_bm_snow[i].r     = rand()%100/100.0f;
				gs_bm_snow[i].g     = rand()%100/100.0f;
				gs_bm_snow[i].b     = rand()%100/100.0f;
				gs_bm_snow[i].arc   = 0;
				gs_bm_snow[i].stage = 200;
			}
			else {
				float det=dir?-1:1;
				gs_bm_snow[i].x += gs_bm_snow[i].speed*cos(gs_bm_snow[i].angle)*det;
				gs_bm_snow[i].y += gs_bm_snow[i].speed*sin(gs_bm_snow[i].angle)*det;
				gs_bm_snow[i].arc += gs_bm_snow[i].arc_speed;
				gs_bm_snow[i].stage--;
			}
			//mRender->SetColor(gs_bm_snow[i].r, gs_bm_snow[i].g, gs_bm_snow[i].b, gs_bm_snow[i].alpha);
			mRender->SetColor(1, 1, 1, gs_bm_snow[i].alpha);
			mRender->EnableAddictiveDraw(true);
			mRender->RenderImage(mSnow, gs_bm_snow[i].x, gs_bm_snow[i].y, gs_bm_snow[i].arc, gs_bm_snow[i].scale, gs_bm_snow[i].scale);
			mRender->EnableAddictiveDraw(false);
		} 
	}
    
}

void BackgroundLayerPlayELS::Render(CCRenderBox* mRender)
{
    Background_Snow(mRender,0);
    
    
}


BackgroundLayerPlayELS::~BackgroundLayerPlayELS(){}