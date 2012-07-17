//
//  gamelayer.h
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_gamelayer_h
#define ThreeCard_gamelayer_h
class gamelayer: public GELayer
{
public:
    GameScenePlayELS();
    ~GameScenePlayELS();
    void onEnter();
    
private:
    void buttonCallback(GEObject* pObj);
    
private:
    GEButton  *m_pButtons[MAIN_MENU_MAX_BUTTON];
    GEImage   *m_pBackGround;
    
    char      m_cNetRequest[NET_CONNECT_BUFFER];
};



#endif
