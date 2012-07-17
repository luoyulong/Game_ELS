/*
 *  GameStateMainMenu.h
 *  Dice
 *
 *  Created by F.K. on 12-4-24.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _GAME_STATE_MAIN_MENU_H_
#define _GAME_STATE_MAIN_MENU_H_
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