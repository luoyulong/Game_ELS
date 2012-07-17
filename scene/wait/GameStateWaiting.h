//
//  GameStateWaiting.h
//  ThreeCard
//
//  Created by  on 12-6-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_GameStateWating_h
#define ThreeCard_GameStateWating_h

#include "GameEngine.h"
#include "GameNetCenter.h"

class GameStateWaiting: public GELayer
{
public:
    static GameStateWaiting *m_Instance;
    
private:
    //等待跳转视图类型标志
    //登录至主菜单页面: 1
    //快速登录至桌子: 2
    //普通场桌子列表至桌子: 3
    //比赛场桌子列表至桌子: 4
    int m_moveViewType;
    
public:
    GameStateWaiting();
    ~GameStateWaiting();
    
    static GameStateWaiting *GetInstance();
    
    void SetWaitType(int moveViewType);
    
    void buttonCallback();
    
};

#endif
