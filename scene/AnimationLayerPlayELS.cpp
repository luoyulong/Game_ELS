//
//  AnimationLayerPlayELS.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "AnimationLayerPlayELS.h"
#include "GameLayerPlayELS.h"
#include "CCRenderBox.h"
AnimationLayerPlayELS::AnimationLayerPlayELS()
{
    Annimationlayer=this;
    GEScene* pScene = GEDirector::GetInstance()->getScene("GameScenePlayELS");
    pScene->addChild(this,30);
    init=false;
    for (int i=0; i<4; i++) {
        fallstat[i]=-1;
    }
    fallImage=new GEImage();
   
    Loadimages();
    

 //   RendCountDown();//倒计时
   
}


void AnimationLayerPlayELS::New_fall(int index)
{
    
    printf("new fall index %d \n",index);
    fallTimer=new GETimer();
    fallTimer->setNotifyTarget(gamelayer);
    fallTimer->setDuration(0.25);//设置定时期时间
    fallTimer->setFuncOnTimerComplete(schedule_selector(GameLayerPlayELS::FallWithUpdate)); 
    //fallTimer->setFuncOnTimerUpdate(schedule_selector(AnimationLayerPlayELS::rendFall));
    fallTimer->resume();
    
    fallImage->setImage(fallImg);
    this->addChild(fallImage);
    fallstat[index]=0;
    
    
     
}


void AnimationLayerPlayELS::RenderDrop(int idx, int l1x1, int l1y1, int l1x2, int l1y2)
{
	//not shades for other people.
	if (idx!=0)
		return;
	
	if (l1y2==0) 
		return; //GAME OVER时，l1y2为0，此时不应绘制阴影
	
	//当下扫动作发生后，绘制残影
	if (mGS[idx].grect_stage<=0 || mGS[idx].grect_stage<=180)
		return;
    
	int rw = (l1x2-l1x1+1)*blksize;
	int rh = (l1y2-l1y1+1)*blksize;
	int rx = mainx+l1x1*blksize-blksize/2+blkadjx+rw/2;
	int ry = mainy+100+l1y1*blksize+rh/2; 
	//float alpha=(mGS[idx].grect_stage-180)/6*0.05f;
    printf("pos:---%d,%d\n",rx,ry);
    fallImage->setPosition(rx, ry);
    fallImage->setScaleX(rw/84.0f);
    fallImage->setScaleY(rh/214.0f);
}








   
void AnimationLayerPlayELS::Cancel_fall(int index)
{
    if(fallstat[index]<0) return;
    printf("really cancel \n");
    fallTimer->cancelTimer();
    fallstat[index]=-1;
}

void AnimationLayerPlayELS::Update(float dt)
{
    int idx=0;
    int l1x1=100, l1y1=100, l1x2=0, l1y2=1;
    //rendFall(dt);
    
    
    
    if(fallstat[0]>=0)
    for(int i=0;i<ZONG;i++)
        for (int j=0; j<HENG; j++)
    //计算渐变高光矩形条的坐标
    if(mGS[idx].grid[i][2+j]<100 && mGS[idx].grid[i][2+j]!=0)
    {
            l1x1 = min(l1x1, j);
        l1y1 = min(l1y1, i);
        l1x2 = max(l1x2, j);
   }
    if(fallstat[0]>=0)
RenderDrop(0, l1x1, l1y1, l1x2, l1y2);
    
}






void AnimationLayerPlayELS::Loadimages()
{
    assetbox=new CCAssetBox();
    assetbox->LoadResource("Play1.xml");
    assetbox->LoadResource("Play2.xml");
    mSnow=assetbox->GetImage("newsnow.png");
    fallImg=assetbox->GetImage("dropbar.png");
  
}


void AnimationLayerPlayELS::Setconfig()
{
    if (true){//mElsMode==ELS_MODE_SINGLE && mBJIdx==0) {
        mainx=54, mainy=2;
    }
    else {
        mainx=0, mainy=2;
    }
}





void AnimationLayerPlayELS::Render(CCRenderBox* mRender)
{
        Background_Snow(mRender,0);
}
AnimationLayerPlayELS::~AnimationLayerPlayELS(){}


//绘制雪花或者气泡 dir=0,1
void AnimationLayerPlayELS::Background_Snow(CCRenderBox* mRender,int dir)
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

//绘制倒计时
void AnimationLayerPlayELS::RendCountDown()
{	
    GESequenceFrames *countdownf = new GESequenceFrames();
    GESprite *pLoadingImage = new GESprite();
    for (int i=0; i<4; i++) {
        char tmp[32];
        sprintf(tmp, "Gbig%d.png", i);
        countdownf->addFrame(tmp);
    }
    pLoadingImage->setAnimationFrames(countdownf);
    pLoadingImage->setPosition(320, 480);
    this->addChild(pLoadingImage);
    pLoadingImage->setFrameSpeed(1);
    pLoadingImage->resume();
    
}





