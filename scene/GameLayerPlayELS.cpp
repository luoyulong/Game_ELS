//
//  GameLayerPlayELS.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameLayerPlayELS.h"
#include "GEScene.h"
#include "GEDirector.h"


CCFont*      GameLayerPlayELS::mFont;
CCFont*      GameLayerPlayELS::mBFont;
CCFont*      GameLayerPlayELS::mLFont;



GameLayerPlayELS::GameLayerPlayELS()
{
 
    gamelayer=this;
    GEScene* pScene = GEDirector::GetInstance()->getScene("GameScenePlayELS");
    pScene->addChild(this,40);
    m_pPlayBoard = new GEImage();
    m_pPlayBoard->setImage("kuang.png");
    m_pPlayBoard->setPosition(320,480);   
    //this->addChild(m_pPlayBoard);    
    mAssetCommon=new CCAssetBox();
    mAssetCommon->LoadResource("Loading.xml");
    mAssetCommon->LoadResource("Play1.xml");
    
    mSND = CCSoundBox::GetInstance();
    
    for (int i=3; i<=10; i++) {
        char tmp[32];
        sprintf(tmp, "combo%d.wav", i);
        mWavCombo[i-3]=mSND->LoadSound(tmp);
    }
    mWavClear[0] = mSND->LoadSound("clear1.wav");
    mWavClear[1] = mSND->LoadSound("clear2.wav");
    mWavClear[2] = mSND->LoadSound("clear3.wav");
    mWavClear[3] = mSND->LoadSound("clear4.wav");
    
    mWavDrop  = mSND->LoadSound("drop.wav");
    mWavMove  = mSND->LoadSound("move.wav");
    mWavTurn  = mSND->LoadSound("turn.wav");
    mWavWin   = mSND->LoadSound("win.wav");
    mWavLose  = mSND->LoadSound("lose.wav");
    mWavLevelup=mSND->LoadSound("levelup.wav");
    mWavPeeco = mSND->LoadSound("peeco.wav");
    
    g_options[1]=1;
    mBJIdx=1;
    mCountDownTimeLeft=0;
    mainx=54;
    mainy=2;
    
    CCImage *image = mAssetCommon->GetImage("particle8");
    mParticleSystem2 = new hgeParticleSystem("particle5.psi", image);
    mParticleSystem2->Fire();
    mParticleSystem2->MoveTo(0, 0, true);
    mFont   = new CCFont(28.0f);
    mBFont  = new CCFont(18.0f);
    mLFont  = new CCFont(30.0f);
    mNanDu=1;//难度关系到方块下落的速度
    ResetImg();
    ResetELS();
    
    
}
GameLayerPlayELS::~GameLayerPlayELS(){}







//写入分数文件
void GameLayerPlayELS::WriteScore()
{
	FILE *fp;
	
	const char *fn = "game.save";
	const char *path = GetDocPath(fn, NULL);
	
	if((fp=fopen(path,"rb+"))==NULL)
	{
		if((fp=fopen(path, "wb+"))==NULL)
			return;
	}
    
	printf("write score to %s...\n", path);
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%d\n", (int)g_mvHS.size());
	for(int i=0;i<g_mvHS.size();i++)
		fprintf(fp, "%d %d %d %s\n", 
				g_mvHS[i]->score,g_mvHS[i]->hang,
				g_mvHS[i]->combo,g_mvHS[i]->date);
	
	fprintf(fp, "%d %d %d %d %d\n", 
            g_xunzhang[0], g_xunzhang[1], g_xunzhang[2],
			g_xunzhang[3], g_xunzhang[4]);
	
	fprintf(fp, "%d\n", g_unlock_bmp);
	for (int i=0; i<MAX_BMP_COUNT; i++) {
		fprintf(fp, "%d ", g_star_bmp[i]);//g_star_bmp[i]只有在取得了比之前的记录更高的星星时才会变，所以这样赋值应该没问题
	}
	fclose(fp);
}




