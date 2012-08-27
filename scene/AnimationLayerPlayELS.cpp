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
    ClearRow_displaylength=30;
    for (int i=0; i<4; i++) {
        fallstat[i]=-1;
        ClearRowstat[i]=0;
    }
    
    
    Loadimages();
    

 //   RendCountDown();//倒计时
   
}


void AnimationLayerPlayELS::New_fall(int index)
{
    
    fallTimer=new GETimer();
    fallTimer->setNotifyTarget(gamelayer);
    fallTimer->setDuration(0.25);//设置定时期时间
    fallTimer->setFuncOnTimerComplete(schedule_selector(GameLayerPlayELS::FallWithUpdate)); 
    fallTimer->resume();
    fallstat[index]=0;
     
}

void AnimationLayerPlayELS::RenderDrop(int idx)
{
	//not shades for other people.
	if (idx!=0)
		return;
	
	
	//当下扫动作发生后，绘制残影,小于0即非下扫动作
    if(fallstat[idx]<0) return;
    fallstat[idx]++;
    int l1x1=100, l1y1=100, l1x2=0, l1y2=0;
    if(mGS[idx].tdy&&idx==0)
	{
		int y=mGS[idx].tdy;
		int z=mGS[idx].cur_z;
        for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				int type=mGS[idx].cur_block;
				if(blkdat[type][z][i*4+j])
				{
					l1y2 = max(l1y2, y+i);//绘制时顺便求出高光条y2坐标
                }
			}
		}
	}
    
    for(int i=0;i<ZONG;i++)
        for (int j=0; j<HENG; j++)
            //计算渐变高光矩形条的坐标
            if(mGS[idx].grid[i][2+j]<100 && mGS[idx].grid[i][2+j]!=0)
            {
                l1x1 = min(l1x1, j);
                l1y1 = min(l1y1, i);
                l1x2 = max(l1x2, j);
            }

    if (l1y2==0) 
		return; //GAME OVER时，l1y2为0，此时不应绘制阴影
	
    
	int rw = (l1x2-l1x1+1)*blksize;
	int rh = (l1y2-l1y1+1)*blksize;
	int rx = mainx+l1x1*blksize-blksize/2+blkadjx+rw/2;
	int ry = mainy+100+l1y1*blksize+rh/2; 
    float alpha=(9-fallstat[idx])/9*0.5f;
    fallImage->setColor(1, 1, 1, alpha);
    fallImage->setPosition(rx, ry);
    fallImage->setScaleX(rw/84.0f);
    fallImage->setScaleY(rh/214.0f);
    
}


void AnimationLayerPlayELS::New_ClearRow(int idx)
{
    ClearRowTimer=new GETimer();
    ClearRowTimer->setNotifyTarget(gamelayer);//
    ClearRowTimer->setDuration(ClearRow_displaylength/60);//设置定时期时间
    ClearRowTimer->setFuncOnTimerComplete(general_selector(GameLayerPlayELS::ClearRowWithUpdate)); 
    char * argv= (char *)malloc(2*sizeof(char));
    argv[0]=idx;
    argv[1]=false;
    ClearRowTimer->setParameterOnTimerComplete(2,argv);
    ClearRowTimer->resume();
    ClearRowstat[idx]=ClearRow_displaylength;   
}


void AnimationLayerPlayELS::Render_ClearRow(int idx)
{
    int k;
    int cstage=0;
    //reset the clear image invisible
    for(k=0;k<4;k++)
    {   
        ClearRowImage1[k]->setColor(1, 1, 1,0);
        ClearRowImage2_1[k]->setColor(1, 1, 1,0);
        ClearRowImage2_2[k]->setColor(1, 1, 1,0);
    }
    k=-1;
    for(int i=0;i<ZONG;i++)
	{
		bool fflag0=false;
		
		if(ClearRowstat[idx]>0)
        {  
            //printf("idx is %d full row and clearrowstat is %f\n",idx,ClearRowstat[0]);
            for(int fm=0;fm<mGS[idx].full_rows_count%100;fm++)
				if(i==mGS[idx].fullrows[fm])
				{
					fflag0=true;
					break;
				}
        }
    
     if (!fflag0)
        {
            continue;
        }
        k++;
    float boxs=1.0;
    if(idx!=0) boxs=sidesc;
    int boxx=mainx;
    int boxy=mainy;
    //mRender->EnableAddictiveDraw(true);
        
    
        if(k==0)
        {
            cstage=ClearRow_displaylength-ClearRowstat[idx]--;//0-ClearRow_displaylength..
           // printf("cstage is %d \n",cstage);
        }
        else {
            //printf("k is %d\n",k);
        }
    float tx,ty, xs;
    ty=boxy+(blkadjy+i*blksize)*boxs;
    tx=boxx+(blkadjx-20)*boxs;
    xs=(20-cstage)*(1.0f/12.0f);
    if (cstage<8) {
        ClearRowImage1[k]->setColor(1, 1, 1, 0.75f);
        ClearRowImage1[k]->setPosition(tx+HENG/2*blksize*boxs,  ty);
        ClearRowImage1[k]->setScaleX(10.5f*boxs);
        ClearRowImage1[k]->setScaleY(boxs);
    }
    else {
        ClearRowImage2_1[k]->setColor(1, 1, 1, 0.75f);
        ClearRowImage2_1[k]->setPosition(tx+xs*2.5f*blksize*boxs, ty);
        ClearRowImage2_1[k]->setScaleX(xs*boxs);
        ClearRowImage2_1[k]->setScaleY(boxs);
        
        
        ClearRowImage2_2[k]->setColor(1, 1, 1, 0.75f);
        ClearRowImage2_2[k]->setPosition(tx+(HENG*blksize-xs*2.5f*blksize)*boxs, ty);
        ClearRowImage2_2[k]->setScaleX(xs*boxs);
        ClearRowImage2_2[k]->setScaleY(boxs);
        //2的角度要设置成3.1415926f
        }
    }
    //mRender->EnableAddictiveDraw(false);
}

   
void AnimationLayerPlayELS::Cancel_ClearRow(int idx)
{
    if(ClearRowstat[0]<=0) return;
    ClearRowTimer->cancelTimer();
    ClearRowstat[idx]=0;
}
void AnimationLayerPlayELS::Cancel_fall(int index)
{
    if(fallstat[index]<0) return;
    printf("really cancel \n");
    fallTimer->cancelTimer();
    fallstat[index]=-1;
}
void AnimationLayerPlayELS::New_UseItem(int _itemtype,int _startx,int _endx,int _starty,int _endy)
{
    {
        float ralaph=1;
        float bfsc=1.8f, bfa=0.6f, fa=0.9f, fsc=1.2f;
        if (ralaph >= 0.3) {
            float iux=_startx+(_endx-_startx)*(1.0-(ralaph-0.3)/0.7);
            float iuy=_starty+(_endy-_starty)*(1.0-(ralaph-0.3)/0.7)+Game_layer->get_adjy_bygrect(0);
            mRender->SetColor(1.0f, 1.0f, 1.0f, bfa);
            mRender->RenderImage(Game_layer->mItemBLK[0], iux, iuy, 3.1415926f*2-ralaph*5, bfsc, bfsc);
            mRender->SetColor(1.0f, 1.0f, 1.0f, fa);
            mRender->RenderImage(Game_layer->mItemBLK[0], iux, iuy, ralaph*5, fsc, fsc);
            mRender->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
            mRender->RenderImage(Game_layer->mItemBLK[_itemtype-20], iux, iuy);
        }
        else {
            mRender->SetColor(1.0f, 1.0f, 1.0f, cos(ralaph/0.3));
            mRender->SetColor(1.0f, 1.0f, 1.0f, bfa);
            mRender->RenderImage(Game_layer->mItemBLK[0], _endx, _endy, 3.1415926f*2-ralaph*5, bfsc, bfsc);
            //mRender->SetColor(1.0f, 1.0f, 1.0f, 1-ralaph);
            mRender->SetColor(1.0f, 1.0f, 1.0f, fa);
            mRender->RenderImage(Game_layer->mItemBLK[0], _endx, _endy, ralaph*5, fsc, fsc);
            mRender->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
            mRender->RenderImage(Game_layer->mItemBLK[_itemtype-20], _endx, _endy);
        }
        
    }
    
    
    
  
    
    
    
    
    
}  




void AnimationLayerPlayELS::Update(float dt)
{
   // int idx=0;
    RenderDrop(0);
    Render_ClearRow(0);
    
}


void AnimationLayerPlayELS::Loadimages()
{
    assetbox=new CCAssetBox();
    assetbox->LoadResource("Play1.xml");
    assetbox->LoadResource("Play2.xml");
    
    
    //下落条动画对象的添加，初始时不显示，故aphla设置为0
    fallImg=assetbox->GetImage("dropbar.png");
    fallImage=new GEImage();
    fallImage->setImage(fallImg);
    fallImage->setColor(1, 1, 1, 0);
    this->addChild(fallImage);
    
    
    
    //消行动画对象的添加
    ClearRowImg1= assetbox->GetImage("clear1.png");
    ClearRowImg2= assetbox->GetImage("clear2.png");
    
    for(int i=0;i<4;i++)
    {
    ClearRowImage1[i]=new GEImage();
    ClearRowImage1[i]->setImage(ClearRowImg1);
    ClearRowImage1[i]->setColor(1, 1, 1, 0);
    this->addChild(ClearRowImage1[i]);
    ClearRowImage2_1[i]=new GEImage();
    ClearRowImage2_1[i]->setImage(ClearRowImg2);
    ClearRowImage2_1[i]->setColor(1, 1, 1, 0);
    this->addChild(ClearRowImage2_1[i]);
    ClearRowImage2_2[i]=new GEImage();
    ClearRowImage2_2[i]->setImage(ClearRowImg2);
    ClearRowImage2_2[i]->setColor(1, 1, 1, 0);
    this->addChild(ClearRowImage2_2[i]);
    }
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
GESprite * AnimationLayerPlayELS::Display_Item(int itemtype, float posx, float posy)
{
    GESequenceFrames *countdownf = new GESequenceFrames();
    GESprite *display_handler = new GESprite();
    for (int i=0; i<4; i++) {
        char tmp[32];
        sprintf(tmp, "Gbig%d.png", i);
        if(itemtype>20&&(i%2))//使用道具的时候星星和item图标切换显示
        countdownf->addFrame(Game_layer->mItemBLK[0]);   
        
        countdownf->addFrame(Game_layer->mItemBLK[itemtype%20]);
    }
    display_handler->setAnimationFrames(countdownf);
    display_handler->setPosition(posx,posy);
    this->addChild(display_handler);
    display_handler->setFrameSpeed(0.05);
    display_handler->resume();
    return display_handler;
}
void AnimationLayerPlayELS::Render(CCRenderBox* mRender)
{
        
}
AnimationLayerPlayELS::~AnimationLayerPlayELS(){}


//绘制雪花或者气泡 dir=0,1


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





