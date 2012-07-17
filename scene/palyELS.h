//
//  palyELS.h
//  ThreeCard
//
//  Created by mini10 on 12-7-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_palyELS_h
#define ThreeCard_palyELS_h
#include "GameEngine.h"
#include "DeviceIDWrapper.h"
#include "gameNetCenter.h"

#define MAIN_MENU_MAX_BUTTON 14
#define NET_CONNECT_BUFFER    1024

class GameStateMainMenu: public GELayer
{
public:
    GameStateMainMenu();
    ~GameStateMainMenu();
    void onEnter();
    
private:
    void buttonCallback(GEObject* pObj);
    
private:
    GEButton  *m_pButtons[MAIN_MENU_MAX_BUTTON];
    GEImage   *m_pBackGround;
    
    char      m_cNetRequest[NET_CONNECT_BUFFER];
};












#endif
