/*
 *  PlayLayerAction.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "PlayLayerAction.h"
#include "GlobalData.h"
#include "gameNetCenter.h"
#include "GameStatePlay.h"
#include "backtoroomwrapper.h"
#include "GlobalData.h"

static int buttonPositions[MAX_ACTION_BUTTON][2] = 
{
    {  60,  60},      //0,BACK
    { 345,  60},      //1,help
    { 480,  60},      //2,face
    { 615,  60},      //3,talk
    
    { 200, 460},      //4,see card
    { 440, 460},      //5,drop card
    
    {  75, 600},      //6, 不参与下局
    { 210, 600},      //7, 自动补充筹码
    { 345, 600},      //8, 一直跟到底
    { 480, 600},      //9, 跟注
    { 615, 600},      //10,2倍
    { 750, 600},      //11,4倍
    { 885, 600},      //12,压满
    
    { 750,  60},      //13,PK
    { 885,  60}       //14,孤注一掷  
};

/*static char buttonName[MAX_ACTION_BUTTON][32] = 
{
    "返回",
    "帮助",
    "表情",
    "聊天",
    "看牌",
    "弃牌",
    "不参与下局",
    "自动补充筹码",
    "一直跟到底",
    "跟注",
    "2倍",
    "4倍",
    "压满",
    "PK",
    "孤注一掷"
};*/

PlayLayerAction::PlayLayerAction(GameStatePlay* pController)
{
    m_pController = pController;
    GEScene* pScene = GEDirector::GetInstance()->getScene("StatePlay");
    pScene->addChild(this,11);
    
    m_pMenuCompare = new GEMenu();
    pScene->addChild(m_pMenuCompare,10);
    m_pMenuStandConfirm = new GEMenu();
    pScene->addChild(m_pMenuStandConfirm,12);
    
    char buttonPicName[2][32];
    for (int i=0; i<MAX_ACTION_BUTTON; i++) {
        //m_pButtonName = new GEText();
        //m_pButtonName->setText(buttonName[i]);
        memset(buttonPicName, 0, 64);
        sprintf(buttonPicName[0], "action%dNormal",i);
        sprintf(buttonPicName[1], "action%dSelected",i);
        m_pButtons[i] = GEButton::buttonFromImagesWithTarget(buttonPicName[0], 
                                                             buttonPicName[1], 
                                                             buttonPicName[1], 
                                                             this, 
                                                             menu_selector(PlayLayerAction::actionOnEvent));
        m_pButtons[i]->setPosition(buttonPositions[i][0], buttonPositions[i][1]);
        //m_pButtons[i]->setButtonLable(buttonName[i]); setButtonLable没有实现
        this->addButton(m_pButtons[i]);
    }
    //比牌按钮
    for (int i=6; i>=0; i--) {
        m_pButtonCompare[i]=GEButton::buttonFromImagesWithTarget("action0Selected", 
                                                                 "action0Normal", 
                                                                 "action0Normal", 
                                                                 this, 
                                                                 menu_selector(PlayLayerAction::actionOnEvent));
        m_pButtonCompare[i]->setIsVisible(false);
        m_pMenuCompare->addButton(m_pButtonCompare[i]);
    }
    m_pButtonCompare[6]->setPosition(480, 320);
    m_pButtonCompare[6]->setColor(0.0, 0.0, 0.0, 0.4);
    m_pButtonCompare[6]->setScale(20);

}

PlayLayerAction::~PlayLayerAction()
{
}

#pragma mark -
#pragma mark Private Methods
void PlayLayerAction::setNoMoreGame(bool b)
{
    g_noMoreGame=b;
    if (b) {
        //m_pButtons[6]->setButtonImageNormal("");
    }else {
        //m_pButtons[6]->setButtonImageNormal("");
    }
}

void PlayLayerAction::setAutoRechangeChip(bool b)
{
    g_autoRechangeChip=b;
    if (b) {
        //m_pButtons[7]->setButtonImageNormal("");
    }else {
        //m_pButtons[7]->setButtonImageNormal("");
    }
}

void PlayLayerAction::setFollowToEnd(bool b)
{
    g_followToEnd=b;
    if (b) {
        //m_pButtons[8]->setButtonImageNormal("");
    }else {
        //m_pButtons[8]->setButtonImageNormal("");
    }
}

void PlayLayerAction::refreshButtonStatus()
{
    //先关闭所有按钮，再依次判断打开。
    for (int i=4; i<=14; i++) {
        m_pButtons[i]->setIsVisible(false);
    }
    if (m_pController->isDealing()) {
        printf("reurn at refreshbutton isdealing.************************\n\n\n");
        return;
    }
    int playerLeft=0;
    for (int i=0; i<6; i++) {
        if (g_seat_info[i].state==SEAT3CSTAT_PLAYING) {
            playerLeft++;
        }
    }
    //如果当前正在玩的不足两人
    if (playerLeft<=1) {
        printf("return at refreshbutton playerLeft<=1.*******************\n\n");
        return;
    }
    //本机玩家没有玩，则所有游戏按钮失效。
    if (g_user.location[3]>0 && g_seat_info[g_user.location[3]-1].state!=SEAT3CSTAT_PLAYING) {
        //printf("return at refreshbutton g_user.state!=PLAYING.location[3]:%d,userId:%d,state:%d\n*******************\n\n",g_user.location[3],g_user.uid,g_seat_info[g_user.location[3]-1].state);
        return;
    }
    //当前出牌玩家是本机用户
    if (g_seat_info[g_table_state.nowOp-1].uid==g_user.uid) {
        //看牌
        printf("now dark is:%d\n",g_seat_info[g_user.location[3]-1].dark);
        if (g_seat_info[g_user.location[3]-1].dark==1) {
            m_pButtons[4]->setIsVisible(true);
        }
        //弃牌
        m_pButtons[5]->setIsVisible(true);
        //按钮6、7、8是非本人出牌时的按钮，在此不做处理。
        //判断按钮9-14
        int betTime=(g_seat_info[g_user.location[3]-1].dark==1?1:2);//倍数
        //首先判断孤注一掷
        if (g_seat_player_info[g_user.location[3]-1].chip<(betTime*g_table_state.minBet)) {
            m_pButtons[14]->setIsVisible(true);
            if (g_followToEnd) {
                g_followToEnd=false;
                gameNetCenter::GetInstance()->pkAll(g_user.location[3]);
                return;
            }
        }else {
            if ((betTime*g_table_state.minBet)<=g_table_info.maxBet && g_seat_player_info[g_user.location[3]-1].chip>=(betTime*g_table_state.minBet)) {
                m_pButtons[9]->setIsVisible(true);
                if (g_followToEnd) {
                    gameNetCenter::GetInstance()->betChip(g_user.location[3],betTime*g_table_state.minBet);
                    return;
                }
            }
            if ((2*betTime*g_table_state.minBet)<=g_table_info.maxBet && g_seat_player_info[g_user.location[3]-1].chip>=(2*betTime*g_table_state.minBet)) {
                m_pButtons[10]->setIsVisible(true);
                if (g_followToEnd) {
                    gameNetCenter::GetInstance()->betChip(g_user.location[3],2*betTime*g_table_state.minBet);
                    return;
                }
            }
            if ((4*betTime*g_table_state.minBet)<=g_table_info.maxBet && g_seat_player_info[g_user.location[3]-1].chip>=(4*betTime*g_table_state.minBet)) {
                m_pButtons[11]->setIsVisible(true);
                if (g_followToEnd) {
                    gameNetCenter::GetInstance()->betChip(g_user.location[3],4*betTime*g_table_state.minBet);
                    return;
                }
            }
            //只剩两个人的时候，压满按钮可以使用
            if (playerLeft==2) {
                m_pButtons[12]->setIsVisible(true);
            }
            //可以比牌，当前手数大于可比手数
            if (g_table_state.currentHand>=g_table_info.pkHand && g_seat_player_info[g_user.location[3]-1].chip>=(2*betTime*g_table_state.minBet)) {
                m_pButtons[13]->setIsVisible(true);
            }
        }
    }else {
        //判断其他人出牌时按钮的状态
        m_pButtons[6]->setIsVisible(true);
        m_pButtons[7]->setIsVisible(true);
        m_pButtons[8]->setIsVisible(true);
    }
}

void PlayLayerAction::actionOnEvent(GEObject* pObj)
{
    int i;
    for (i=0; i<MAX_ACTION_BUTTON; i++) {
        if (pObj == (GEObject*)m_pButtons[i]) {
            break;
        }
    }
    switch (i) {
        case 0:
            //back
            if (gameNetCenter::GetInstance()->m_bIsQuickStart)
            {
                gameNetCenter::GetInstance()->leaveRoom();
                gameNetCenter::GetInstance()->m_bIsQuickStart = false;
                GEDirector::GetInstance()->gotoScene("StateMainMenu", MoveToRight, 0.3);
            }
            else if (!gameNetCenter::GetInstance()->m_bIsQuickStart)
            {
                gameNetCenter::GetInstance()->leaveTable();
                
                if (g_roomId <= 4)
                {
                    printf("回到普通场\n");
                    backToNormalRoom();
                }
                else if (g_roomId ==5 )
                {
                    printf("回到比赛场\n");
                    backToMatchRoom();
                }
            }
            break;
            
        case 1:
            //help
            
            break;
            
        case 2:
            //face
            
            break;
            
        case 3:
            //talk
            
            break;
            
        case 4:
            //看牌
            gameNetCenter::GetInstance()->seeCard(g_user.location[3]);
            
            break;
            
        case 5:
            //drop card
            gameNetCenter::GetInstance()->giveUp(g_user.location[3]);
            break;
            
        case 6:
            //不参与下局
            setNoMoreGame(!g_noMoreGame);
            break;
            
        case 7:
            //自动补充筹码
            setAutoRechangeChip(!g_autoRechangeChip);
            break;
            
        case 8:
            //一直跟到底
            setFollowToEnd(!g_followToEnd);
            break;
            
        case 9:
            //跟注
            printf("一倍跟注...\n");
            gameNetCenter::GetInstance()->betChip(g_user.location[3], (g_seat_info[g_table_state.nowOp].dark==1?1:2)*g_table_state.minBet);
            break;
        case 10:
            //2倍
            printf("二倍跟注...\n");
            gameNetCenter::GetInstance()->betChip(g_user.location[3], (g_seat_info[g_table_state.nowOp].dark==1?1:2)*2*g_table_state.minBet);
            break;
        case 11:
            //4倍
            printf("四倍跟注...\n");
            gameNetCenter::GetInstance()->betChip(g_user.location[3], (g_seat_info[g_table_state.nowOp].dark==1?1:2)*4*g_table_state.minBet);
            break;
        case 12:
            //压满
            printf("压满...\n");
            for (int i=0; i<6; i++) {
                if (g_seat_info[i].state==10 && g_seat_info[i].uid!=g_user.uid)  break;
            }
            
//            gameNetCenter::GetInstance()->betChip(g_user.location[3], 800);
            break;
        case 13:
            //与单个玩家PK...
            printf("与单个玩家PK...\n");
            GameStatePlay::GetInstance()->beginChoosePkObject();
            for (int i=0; i<6; i++) {
                if (g_seat_info[i].state==SEAT3CSTAT_PLAYING && g_seat_info[i].uid!=g_user.uid) {
                    m_pButtonCompare[i]->setPosition(g_seat_position[i][0]+40, g_seat_position[i][1]+60);
                    m_pButtonCompare[i]->setIsVisible(true);
                }
            }
            m_pButtonCompare[6]->setIsVisible(true);
            break;
        case 14:
            //孤注一掷
            printf("孤注一掷...\n");
            gameNetCenter::GetInstance()->pkAll(g_user.location[3]);
            break;
            
        default:
            break;
    }
    if (i==MAX_ACTION_BUTTON) {
        int j;
        for (j=0; j<7; j++) {
            if (pObj == (GEObject*)m_pButtonCompare[j]) {
                if (j<6) {
                    gameNetCenter::GetInstance()->pkOne(g_user.location[3], j+1);
                }
                GameStatePlay::GetInstance()->endChoosePkObject();
                for (int i=0; i<7; i++) {
                    m_pButtonCompare[i]->setIsVisible(false);
                }
            }
        }
    }
}


