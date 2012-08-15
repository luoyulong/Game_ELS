//
//  GameScenePlayELS.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameScenePlayELS.h"
#include "GlobalData.h"
#include "gameNetCenter.h"
#include "RoomWrapper.h"
#include "AddonWrapper.h"
#include "CommonLayerHelpWrapper.h"
#include "GameStateShortConnect.h"
#include "warningMessageWrapper.h"
//#include "MenuLayerMsg.h"
#include "WrapperMedal.h"
#include "WrapperLevelRule.h"
#include "WrapperSet.h"
#include "WrapperFigure.h"
#include "FileConfigure.h"
#include "GameStateWaiting.h"
#include "SimpleAudioEngineWrapper.h"


GameScenePlayELS* GameScenePlayELS::m_Instance=0;
GameScenePlayELS* GameScenePlayELS::GetInstance()
 {
 if (m_Instance == 0)
 {
 m_Instance = new GameScenePlayELS();
 }
 
 return m_Instance;
 }
 

GameScenePlayELS::GameScenePlayELS()
{
    
    GEScene* pScene=GEDirector::GetInstance()->createScene("GameScenePlayELS");
    pScene->addChild(this,50);
    printf("GameScenePlayELS is:%p\n",pScene);
    
    // backgrounds
    m_pBackGround = new GEImage();
    m_pBackGround->setImage("playback.png");
    m_pBackGround->setPosition(320,480);   
    this->addChild(m_pBackGround);    
    
    //new other layers
    new GameLayerPlayELS();
    new AnimationLayerPlayELS();
    new PopLayerPlayELS();
    new ItemLayerPlayELS();
    
    // new menu
    GEMenu* pMenu = new GEMenu();
    pScene->addChild(pMenu);
    
    
    
    //init common variable
   // mLFont=new GEText();
    //mLFont->setFontSize(20.0f);
    
    
}

GameScenePlayELS::~GameScenePlayELS()
{
}

void GameScenePlayELS::onEnter()
{
}

void GameScenePlayELS::buttonCallback(GEObject* pObj)
{
   

}

