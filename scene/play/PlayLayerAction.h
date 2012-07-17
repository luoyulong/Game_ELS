/*
 *  PlayLayerAction.h
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

/*  PlayLayerAction是一个GELayer层，定义了玩家可能的操作
 *  在玩家出牌时，按钮出现，玩家进行操作，
 *  然后将操作内容传到GameStatePlay进行网络发送。
 *  其他玩家进行操作时，Action层隐藏。
 */

#ifndef _PLAY_LAYER_ACTION_H_
#define _PLAY_LAYER_ACTION_H_
#include "GameEngine.h"
#define MAX_ACTION_BUTTON  15

class GameStatePlay;

class PlayLayerAction: public GEMenu
{
public:
    PlayLayerAction(GameStatePlay* pController);
    ~PlayLayerAction();
    void actionOnEvent(GEObject* pObj);
    //更新每个按钮的状态
    void refreshButtonStatus();
    
private:
    void setNoMoreGame(bool b);
    void setAutoRechangeChip(bool b);
    void setFollowToEnd(bool b);
    

    
private:
    GEMenu      *m_pMenuCompare, *m_pMenuStandConfirm;
    GEButton    *m_pButtons[MAX_ACTION_BUTTON];
    GEButton    *m_pButtonCompare[7];//比牌按钮，在比牌可选时出现。
    GEText      *m_pButtonName;
    GameStatePlay *m_pController;
};
#endif