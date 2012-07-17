/*
 *  PlayLayerHead.h
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _PLAY_LAYER_HEAD_H_
#define _PLAY_LAYER_HEAD_H_
#include "GameEngine.h"

class PlayLayerHead: public GEMenu
{
public: 
    PlayLayerHead();
    ~PlayLayerHead();
    
    void confirmStandUp();
    
    //刷新玩家信息
    void refreshPlayerInfo();
    
    //转化座位，需要更新内部图的位置
    void shiftSeat();
    
    //玩家头像用于选择OK对象
    void beginChoosePkObject();
    void endChoosePkObject();

private:
    void buttonHeadOnEvent(GEObject* pObj); //点击玩家头像的回调
    void buttonPlayerInfoOnEvent(GEObject* pObj); //个人信息按钮的回调
    void easePlayerInfoCallback(float ratio); //个人信息动画
    
    
private:
    
    GEButton*   m_pButtonHead[6]; //头像
    GEMenu*     m_pMenuPlayerInfo;//显示玩家个人信息的菜单层
    GEButton*   m_pButtonPlayerInfo[2];//玩家详细信息，[0]按钮显示信息，[1]按钮作为背景，用于取消。
    GEEaseNumber*   m_pEasePlayerInfo;
    int         m_iChosenPlayer; //选中的玩家
    
    GEImage     *m_pHeadImage[6];//玩家头像
    GEText      *m_pName[6];     //玩家名字
    GEText      *m_pChipLeft[6]; //玩家剩余筹码
    
//    bool        m_bIsChoosePkObj;
//    GEButton    *m_pButtonChoosePkObjBack;//选择Pk对象时的背景按钮，用于取消选择Pk对象。
    
};
#endif