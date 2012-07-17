/*
 *  GameStateLoading.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-6-1.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "GameStateLoading.h"
#include "GameStateLogIn.h"
#include "GameStateShortConnect.h"
#include "GameStateMainMenu.h"
#include "GameStatePlay.h"
#include "FileConfigure.h"
#include "SimpleAudioEngineWrapper.h"

GameStateLoading::GameStateLoading()
{
    GEDirector::GetInstance()->loadImageResource("c0.xml");
    GEDirector::GetInstance()->loadImageResource("c0b.xml");
    GEDirector::GetInstance()->setTargetAndSelectorInBackground(this, callfunc_selector(GameStateLoading::loadInSubThread));
    GEScene* pScene = GEDirector::GetInstance()->createScene("StateLoading");
    pScene->addChild(this);
    
    m_pBack = new GEImage();
    m_pBack->setImage("index_back.png");
    m_pBack->setPosition(480, 320);
    this->addChild(m_pBack);
    
    m_pMeinv = new GEImage();
    m_pMeinv->setImage("index_meinv.png");
    m_pMeinv->setPosition(480, 320);
    this->addChild(m_pMeinv);
    
    m_pText = new GEText();
    m_pText->setText("Loading...");
    m_pText->setAlignment(textAlignmentCenter);
    m_pText->setFontSize(14);
    m_pText->setPosition(920, 622);
    m_pText->setRGBAA(0.8f);
    this->addChild(m_pText);
}

GameStateLoading::~GameStateLoading(){}

void GameStateLoading::loadInSubThread()
{
    //在这里调用GEDirector的函数,读取图片等资源
    GEDirector::GetInstance()->loadImageResource("c1.xml");
    GEDirector::GetInstance()->loadImageResource("c2.xml");
    GEDirector::GetInstance()->loadImageResource("c3.xml");
     GEDirector::GetInstance()->loadImageResource("Play1.xml"); 
     GEDirector::GetInstance()->loadImageResource("Play2.xml"); 
     GEDirector::GetInstance()->loadImageResource("Play3.xml"); 
    GEDirector::GetInstance()->loadImageResource("Play4.xml");
     GEDirector::GetInstance()->loadImageResource("Play5.xml"); //加载声音资源
    SimpleAudioPreloadEffect("audio_btn_click.m4a");
    //sleep(1);
}





