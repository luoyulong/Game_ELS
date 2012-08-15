//
//  GameScenePlayELS.h
//  ThreeCard
//
//  Created by mini10 on 12-7-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_GameScenePlayELS_h
#define ThreeCard_GameScenePlayELS_h

#include "GameEngine.h"
#include "DeviceIDWrapper.h"
#include "gameNetCenter.h"
#include "GameLayerPlayELS.h"
#include "AnimationLayerPlayELS.h"
#include "PopLayerPlayELS.h"
#include "ItemLayerPlayELS.h"
#define MAIN_MENU_MAX_BUTTON 14
#define NET_CONNECT_BUFFER    1024

class GameScenePlayELS: public GELayer
{
public:
    GameScenePlayELS();
    ~GameScenePlayELS();
    void onEnter();
   static  GameScenePlayELS* GetInstance();
    
private:
    void buttonCallback(GEObject* pObj);
    
private:
    static GameScenePlayELS * m_Instance; 
    GEButton  *m_pButtons[MAIN_MENU_MAX_BUTTON];
    GEImage   *m_pBackGround;
    
    char      m_cNetRequest[NET_CONNECT_BUFFER];
};


#endif
