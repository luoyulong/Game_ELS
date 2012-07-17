//
//  GameStateWaiting.cpp
//  ThreeCard
//
//  Created by  on 12-6-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GameStateWaiting.h"
#include "MenuLayerNormalRoom.h"
#include "MenuLayerMatchRoom.h"
#include "FileConfigure.h"

GameStateWaiting *GameStateWaiting::m_Instance = 0;

GameStateWaiting *GameStateWaiting::GetInstance()
{
    if (m_Instance == 0)
	{
		m_Instance = new GameStateWaiting();
	}
	
	return m_Instance;
}

GameStateWaiting::GameStateWaiting()
{
    m_moveViewType = 0;
    
    GEScene *pScene = GEDirector::GetInstance()->createScene("GameStateWaiting");
    pScene->addChild(this);
    
    // new menu
    GEMenu *pMenu = new GEMenu();
    pScene->addChild(pMenu);
    
    //序列帧
    GESequenceFrames *tmpsf = new GESequenceFrames();
    GESprite *pLoadingImage = new GESprite();
    
    for (int i=0; i<12; i++) {
        char tmp[32];
        sprintf(tmp, "wait%d", i);
        tmpsf->addFrame(tmp);
    }
    pLoadingImage->setAnimationFrames(tmpsf);
    // button
    GEButton *m_pButton = GEButton::buttonFromImagesWithTarget("ChooseRoomButton1Normal",
                                                     "ChooseRoomButton1Selected",
                                                     NULL,
                                                     this,
                                                     menu_selector(GameStateWaiting::buttonCallback));
    m_pButton->setPosition(282,480);
    pMenu->addButton(m_pButton);
    pLoadingImage->setPosition(110, 480);
    pMenu->addChild(pLoadingImage);
    pLoadingImage->setFrameSpeed(0.05);
    pLoadingImage->resume();
}

GameStateWaiting::~GameStateWaiting()
{
}

void GameStateWaiting::SetWaitType(int moveViewType)
{
    m_moveViewType = moveViewType;
}

void GameStateWaiting::buttonCallback()
{
    printf("                --------- 等待页面 取消跳转 %d-----------\n", m_moveViewType);
    
    if (m_moveViewType == 1) {
        //返回到登录页面
        sprintf(g_config["login_type"], "&&^^_null");
        FileConfigure *fileConfigure = new FileConfigure();
        fileConfigure->WriteOption();
        free(fileConfigure);
        GEDirector::GetInstance()->setCurrentScene("StateLogIn");
    } else if (m_moveViewType == 2) {
        //返回到主菜单
        GEDirector::GetInstance()->setCurrentScene("StateMainMenu");
        gameNetCenter::GetInstance()->closeConn();
        g_roomId = 0;
    } else if (m_moveViewType == 3) {
        //返回到普通场
//        gameNetCenter::GetInstance()->closeConn();
        [[[MenuLayerNormalRoom sharedManager] view ] setHidden:NO];
//        gameNetCenter::GetInstance()->enterRoom(g_roomId);
        [[MenuLayerNormalRoom sharedManager] backToNormalRoom];
    } else if (m_moveViewType == 4) {
        //返回到比赛场
//        gameNetCenter::GetInstance()->closeConn();
        [[[MenuLayerMatchRoom sharedManager] view ] setHidden:NO];
//        gameNetCenter::GetInstance()->enterRoom(g_roomId);
        [[MenuLayerMatchRoom sharedManager] backToMatchRoom];
    }
    
}




















