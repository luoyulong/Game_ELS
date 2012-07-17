/*
 *  PlayLayerHead.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "PlayLayerHead.h"
#include "GlobalData.h"
#include "GameNetCenter.h"
#include "GameStatePlay.h"


PlayLayerHead::PlayLayerHead()
{
//    m_bIsChoosePkObj=false;
    //得到场景
    GEScene* pScenePlay = GEDirector::GetInstance()->getScene("StatePlay");
    //将本类的菜单层加入场景中
    pScenePlay->addChild(this,30);
    
    //创建6个头像按钮，依次加入层
    for (int i=0; i<6; i++) {
        m_pButtonHead[i] = GEButton::buttonFromImagesWithTarget("blankHead", 
                                                                NULL,
                                                                NULL,
                                                                this, 
                                                                menu_selector(PlayLayerHead::buttonHeadOnEvent));
        m_pButtonHead[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]);
        this->addButton(m_pButtonHead[i]);
    }
//    //选择PK对象时的背景按钮，用于取消选择。
//    m_pButtonChoosePkObjBack = GEButton::buttonFromImagesWithTarget("playerNormal", 
//                                                                    "playerSelected", 
//                                                                    "playerSelected", 
//                                                                    this, 
//                                                                    menu_selector(PlayLayerHead::buttonHeadOnEvent));
//    m_pButtonChoosePkObjBack->setPosition(480, 320);
//    m_pButtonChoosePkObjBack->setScale(30);
//    m_pButtonChoosePkObjBack->setColor(0.0, 0.0, 0.0, 0.2);
//    m_pButtonChoosePkObjBack->setIsVisible(false);
//    this->addButton(m_pButtonChoosePkObjBack);
    
    /*
     *  创建菜单层，包含2个按钮，一个显示玩家个人信息，另一个作为背景，点中时隐藏此层
     *  平时此层隐藏，玩家头像按钮被点中时显示
     *  此层是场景的最上层，第0层。
     */
    m_pMenuPlayerInfo = new GEMenu();
    m_pMenuPlayerInfo->setIsVisible(false);
    pScenePlay->addChild(m_pMenuPlayerInfo,0);
    
    //创建2个按钮，一个用于显示玩家详细信息，另一个作为背景。
    for (int i=0; i<2; i++) {
        m_pButtonPlayerInfo[i] = GEButton::buttonFromImagesWithTarget("playerNormal", 
                                                                      "playerSelected", 
                                                                      "playerSelected", 
                                                                      this, 
                                                                      menu_selector(PlayLayerHead::buttonPlayerInfoOnEvent));
        m_pMenuPlayerInfo->addButton(m_pButtonPlayerInfo[i],i);
    }
    m_pButtonPlayerInfo[1]->setScale(50);//放大充满整个背景
    
    //个人信息的动画效果
    m_pEasePlayerInfo = new GEEaseNumber();
    m_pEasePlayerInfo->setEaseType(circEaseOut);
    m_pEasePlayerInfo->setSingleCycleDuration(0.15);
    m_pEasePlayerInfo->setTargetAndCallBacks(this, 
                                             NULL, 
                                             schedule_selector(PlayLayerHead::easePlayerInfoCallback), 
                                             schedule_selector(PlayLayerHead::easePlayerInfoCallback));
    
    
    //玩家的头像、名字和剩余筹码
    for (int i=0; i<6; i++) {
//        m_pHeadImage[i]=new GEImage();
//        m_pHeadImage[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]);
//        this->addChild(m_pHeadImage[i]);
        
        m_pName[i] = new GEText();
        m_pName[i]->setArea(64, 16);
        m_pName[i]->setAlignment(textAlignmentCenter);
        m_pName[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]-65);
        this->addChild(m_pName[i]);
        
        m_pChipLeft[i]=new GEText();
        m_pChipLeft[i]->setArea(128, 32);
        m_pChipLeft[i]->setAlignment(textAlignmentCenter);
        m_pChipLeft[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]+70);
        this->addChild(m_pChipLeft[i]);
    }
    refreshPlayerInfo();
    
}

PlayLayerHead::~PlayLayerHead()
{}

//void PlayLayerHead::beginChoosePkObject(){m_bIsChoosePkObj=true; m_pButtonChoosePkObjBack->setIsVisible(true);}
//void PlayLayerHead::endChoosePkObject(){m_bIsChoosePkObj=false; m_pButtonChoosePkObjBack->setIsVisible(false);}

void PlayLayerHead::refreshPlayerInfo()
{
    char n[20];
    char chip[30];
    for (int i=0; i<6; i++) {
        if (g_seat_info[i].uid==0) {
//            m_pHeadImage[i]->deleteImage();
//            m_pHeadImage[i]->setImage("blankHead");
//            m_pHeadImage[i]->setColor(1.0, 1.0, 1.0, 0.5);
            m_pName[i]->setText("中文");
            m_pChipLeft[i]->setText("模拟器玩家金币");
            continue;
        }
        //名字的长度
        memset(n, 0, 20);
        sprintf(n, "%d",g_seat_info[i].uid);
        m_pName[i]->setText(n);
        memset(chip, 0, 30);
        sprintf(chip, "%d",g_seat_player_info[i].chip);
        m_pChipLeft[i]->setText(chip);
    }
}





//玩家头像被点击的回调
void PlayLayerHead::buttonHeadOnEvent(GEObject* pObj)
{
//    if (m_bIsChoosePkObj) {
//        int i;
//        for (i=0; i<6; i++) {
//            if (pObj==(GEObject*)m_pButtonHead[i]) {
//                m_iChosenPlayer = i;
//                break;
//            }
//        }
//        if (i<6) 
//            gameNetCenter::GetInstance()->pkOne(g_user.location[3], i+1);
//        GameStatePlay::GetInstance()->endChoosePkObject();
//    }
//    else {
        this->setIsTouchEnabled(false);
        m_pMenuPlayerInfo->setIsVisible(true);
    
        m_pButtonPlayerInfo[1]->setColor(0.0, 0.0, 0.0, 0.0); //背景由透明变黑色
        int i;
        for (i=0; i<6; i++) {
            if (pObj==(GEObject*)m_pButtonHead[i]) {
                m_iChosenPlayer = i;
                break;
            }
        }
        m_pButtonPlayerInfo[0]->setScale(1.0);
        m_pButtonPlayerInfo[0]->setPosition(g_seat_position[i][0], g_seat_position[i][1]);
        m_pEasePlayerInfo->reset();
        m_pEasePlayerInfo->resume();
//    }
}

//玩家个人信息被点击的回调
void PlayLayerHead::buttonPlayerInfoOnEvent(GEObject* pObj)
{
    if (pObj==(GEObject*)m_pButtonPlayerInfo[1]) { //取消
        this->setIsTouchEnabled(true);
        m_pMenuPlayerInfo->setIsVisible(false);
        m_pButtonPlayerInfo[1]->setColor(0.0, 0.0, 0.0, 0.0);
        m_pButtonPlayerInfo[0]->setScale(1.0);
    }
    if (pObj==(GEObject*)m_pButtonPlayerInfo[0]) {
        
    }
}

//用于个人信息展示时候的动画
void PlayLayerHead::easePlayerInfoCallback(float ratio)
{
    //printf("easePlayerInfoCallback!!\n");
    m_pButtonPlayerInfo[1]->setColor(0.0, 0.0, 0.0, 0.2*ratio);
    m_pButtonPlayerInfo[0]->setScale(0.5+2.0*ratio);
    m_pButtonPlayerInfo[0]->setPosition(g_seat_position[m_iChosenPlayer][0]+(480.0-g_seat_position[m_iChosenPlayer][0])*ratio,
                                        g_seat_position[m_iChosenPlayer][1]+(320.0-g_seat_position[m_iChosenPlayer][1])*ratio);
}


void PlayLayerHead::shiftSeat()
{
    for (int i=0; i<6; i++) {
        m_pButtonHead[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]);
        m_pName[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]-65);
        m_pChipLeft[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]+70);
        //m_pHeadImage[i]->setPosition(g_seat_position[i][0], g_seat_position[i][1]);
    }
}