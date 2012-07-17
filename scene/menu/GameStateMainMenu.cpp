/*
 *  StateGameMainMenu.cpp
 *  Dice
 *
 *  Created by F.K. on 12-4-24.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "GameStateMainMenu.h"
#include "GlobalData.h"
#include "gameNetCenter.h"
#include "RoomWrapper.h"
#include "AddonWrapper.h"
#include "CommonLayerHelpWrapper.h"
#include "GameStateShortConnect.h"
#include "warningMessageWrapper.h"
//#include "MenuLayerMsg.h"
#include "WrapperMedal.h"
#include "WrapperLevelRule.h"
#include "WrapperSet.h"
#include "WrapperFigure.h"
#include "FileConfigure.h"
#include "GameStateWaiting.h"
#include "SimpleAudioEngineWrapper.h"

static int buttonLocation[MAIN_MENU_MAX_BUTTON][2] = {
    {720, 160}, //0快速开始
    {720, 260}, //1普通场
    {720, 360}, //2淘汰场
    {720, 510}, //3开始教学
    {650, 610}, //4帮助
    {790, 610}, //5设置
    {100, 560}, //6消息
    {200, 560}, //7活动
    {300, 560}, //8商城
    {400, 560}, //9好友
    {500, 560}, //10FAQ
    {100, 100}, //11头像
    {500, 80 }, //12登出
    {500, 140}  //13领取奖励
};












GameStateMainMenu::GameStateMainMenu()
{
    GEScene* pScene=GEDirector::GetInstance()->createScene("StateMainMenu");
    pScene->addChild(this);
    printf("StateMain is:%p\n",pScene);
    
    // backgrounds
    m_pBackGround = new GEImage();
    m_pBackGround->setImage("menu_back.png");
    m_pBackGround->setPosition(480, 320);
    this->addChild(m_pBackGround);    
    
    // new menu
    GEMenu* pMenu = new GEMenu();
    pScene->addChild(pMenu);
    
    // buttons
    char buttonPicName[MAIN_MENU_MAX_BUTTON*2][64]={
        "login_snsbtn.png", "login_snsbtn.png", 
        "login_snsbtn.png", "login_snsbtn.png", 
        "login_snsbtn.png", "login_snsbtn.png",         
        "login_singlebtn.png", "login_singlebtn.png", 
        "login_helpbtn.png", "login_helpbtn.png", 
        "login_setbtn.png", "login_setbtn.png",
        "menu_message.png", "menu_message.png",
        "menu_saleact.png", "menu_saleact.png",
        "menu_store.png", "menu_store.png",
        "menu_friend.png", "menu_friend.png",
        "menu_faq.png", "menu_faq.png",
        "menu_faq.png", "menu_faq.png",
        "menu_reward.png", "menu_reward.png",
        "menu_logout.png", "menu_logout.png"
    };
    for (int i=0; i<MAIN_MENU_MAX_BUTTON; i++) {
        //printf("n=%s, s=%s\n", buttonPicName[2*i+0], buttonPicName[2*i+1]);
        m_pButtons[i] = GEButton::buttonFromImagesWithTarget(buttonPicName[2*i+0], 
                                                             buttonPicName[2*i+1], 
                                                             NULL, 
                                                             this, 
                                                             menu_selector(GameStateMainMenu::buttonCallback));
        m_pButtons[i]->setPosition(buttonLocation[i][0], buttonLocation[i][1]);
        pMenu->addButton(m_pButtons[i]);
    }
}

GameStateMainMenu::~GameStateMainMenu()
{
}

void GameStateMainMenu::onEnter()
{
}

void GameStateMainMenu::buttonCallback(GEObject* pObj)
{
    FileConfigure *fileConfigure = NULL;
    for (int i=0; i<MAIN_MENU_MAX_BUTTON; i++) {
        if (pObj==m_pButtons[i]) {
            SimpleAudioPlayEffect("audio_btn_click.m4a");
            switch (i) {
                case 0:
                    //快速开始
                    GEDirector::GetInstance()->setCurrentScene("GameStateWaiting");
                    GameStateWaiting::GetInstance()->SetWaitType(2);
                    GameStateShortConnect::GetInstance()->quickStartReq(GetUniqueDeviceIdentifier());
                    break;
                    
                case 1:
                    //普通场
                    if (checkNetWork()) {
                        GameStateWaiting::GetInstance()->SetWaitType(3);
                        gameNetCenter::GetInstance()->enterRoom(1);//默认普通场 新手房间
                        menuLayerNormalRoomShow();
                    }
                    break;
                    
                case 2:
                    //比赛场
                    if (checkNetWork()) {
                        GameStateWaiting::GetInstance()->SetWaitType(4);
                        gameNetCenter::GetInstance()->enterRoom(5);
                        menuLayerMatchRoomShow();
                    }
                    break;
                    
                case 3:
                    //开始教学
                    menuLayerShowLevelRule();
                    break;
                    
                case 4:
                    //帮助
                    commonLayerHelpShow();
                    break;
                    
                case 5:
                    //设置
                    menuLayerShowSet();
                    break;
                    
                case 6:
                    //消息
                    menuLayerMsgShow();
                    break;
                    
                case 7:
                    //活动
                    menuLayerActsShow();
                    break;
                    
                case 8:
                    //商城
                    menuLayerStoreShow();
                    break;
                    
                case 9:
                    menuLayerFriendsShow();
                    //好友
                    break;
                    
                case 10:
                    //FAQ
                    menuLayerFAQShow();
                    break;
                    
                case 11:
                    //头像
                    menuLayerShowFigure();
                    break;
                    
                case 12:
                    //登出
                    if (strcmp(g_config["login_type"], "guest")==0) {
                        sprintf(g_config["login_type"], "&&^^_null");
                    }
                    else if (strcmp(g_config["login_type"], "gamecentert")==0) {
                        sprintf(g_config["login_type"], "&&^^_null");
                    }
                    else if (strcmp(g_config["login_type"], "sina")==0) {
                        sprintf(g_config["sina_uid"], "&&^^_null");
                        sprintf(g_config["sina_accesstoken"], "&&^^_null");
                    }
                    else if (strcmp(g_config["login_type"], "renren")==0) {
                        sprintf(g_config["renren_uid"], "&&^^_null");
                        sprintf(g_config["renren_sessionKey"], "&&^^_null");
                        sprintf(g_config["renren_accesstoken"], "&&^^_null");
                    }
                    else if (strcmp(g_config["login_type"], "qq")==0) {
                        sprintf(g_config["qq_openid"], "&&^^_null");
                        sprintf(g_config["qq_accesstoken"], "&&^^_null");
                    }
                    
                    
                    fileConfigure = new FileConfigure();
                    fileConfigure->WriteOption();
                    free(fileConfigure);
                    
                    GEDirector::GetInstance()->gotoScene("StateLogIn", MoveToRight, 0.3);
                    break;
                    
                case 13:
                    //领取奖励
                    //GameStateShortConnect::GetInstance()->rewards();
                    menuLayerShowMedal();
                    break;
                    
                default:
                    break;
            }
            return;
        }
    }
}

