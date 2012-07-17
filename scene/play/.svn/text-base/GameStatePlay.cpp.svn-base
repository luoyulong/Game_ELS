/*
 *  GEStatePlay.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "GameStatePlay.h"
#include "GlobalData.h"

GameStatePlay* GameStatePlay::m_pSelf=0;
GameStatePlay* GameStatePlay::GetInstance()
{
    if (m_pSelf == 0) {
        m_pSelf = new GameStatePlay();
    }
    return m_pSelf;
}

GameStatePlay::GameStatePlay()
{
    //初始化全局的位置，从g_*_init_pos中拷贝
    for (int i=0; i<6; i++) {
        g_seat_position[i][0]=g_seat_init_position[i][0];
        g_seat_position[i][1]=g_seat_init_position[i][1];
        g_banker_position[i][0]=g_banker_init_position[i][0];
        g_banker_position[i][1]=g_banker_init_position[i][1];
        g_cards_position[i][0]=g_cards_init_position[i][0];
        g_cards_position[i][1]=g_cards_init_position[i][1];
    }
    
    GEScene *pScene=GEDirector::GetInstance()->createScene("StatePlay");
    pScene->addChild(this);
    
    m_pLayerAction = new PlayLayerAction(this);
    m_pLayerHead = new PlayLayerHead();
    m_pLayerAboveHead = new PlayLayerAboveHead();
    m_pLayerUnderHead = new PlayLayerUnderHead();
    pScene->addChild(m_pLayerUnderHead, 40);
    
    m_pEaseShiftSeat = new GEEaseNumber();
    m_pEaseShiftSeat->setEaseType(sineEaseInOut);
    m_pEaseShiftSeat->setSingleCycleDuration(0.3);
    m_pEaseShiftSeat->setTargetAndCallBacks(this, 
                                            schedule_selector(GameStatePlay::shiftSeatCallbackStart),
                                            schedule_selector(GameStatePlay::shiftSeatCallback),
                                            schedule_selector(GameStatePlay::shiftSeatCallback),
                                            NULL);
    
}

GameStatePlay::~GameStatePlay(){}

void GameStatePlay::preEnterScene()
{
    m_pLayerAboveHead->refresh();
    m_pLayerHead->refreshPlayerInfo();
}

void GameStatePlay::gameStart()
{
    g_noMoreGame=false;
    g_autoRechangeChip=false;
    g_followToEnd=false;
    refreshPlayerInfo();
    for (int i=0; i<6; i++) {
        if (g_seat_info[i].state==SEAT3CSTAT_PLAYING) {
            moveChipsFromPlayerToPool(i, 4*g_table_info.baseBet);
        }
    }
    m_pLayerAboveHead->changeBanker();
    m_pLayerUnderHead->endCountdown();
    m_pLayerAboveHead->deal();
}
void GameStatePlay::refreshButtonStatus() {m_pLayerAction->refreshButtonStatus();}
void GameStatePlay::moveChipsFromPlayerToPool(int player,int chipNumber)
{
    m_pLayerAboveHead->moveChipsFromPositionToPool(player, chipNumber);
}
void GameStatePlay::seeCard(int seatId){m_pLayerAboveHead->seeCard(seatId);}
void GameStatePlay::giveUp(int seatId) 
{
    
}
void GameStatePlay::refreshPlayerInfo() 
{
    m_pLayerAboveHead->refresh();
    m_pLayerHead->refreshPlayerInfo(); 
}

//下一家出牌时更新全局的数据
void GameStatePlay::next()
{
    m_pLayerAction->refreshButtonStatus();
    m_pLayerUnderHead->endCountdown();
    m_pLayerUnderHead->startCountdown(g_table_state.nowOp-1,g_table_info.opTime);
}

bool GameStatePlay::isDealing()
{
    return m_pLayerAboveHead->isDealing();
}

//开始及结束选择PK对象
void GameStatePlay::beginChoosePkObject()
{
    m_pLayerAboveHead->setColor(0.7, 0.7, 0.7, 1.0);
    m_pLayerAction->setColor(0.7, 0.7, 0.7, 1.0);
    m_pLayerAction->setIsTouchEnabled(false);
    //m_pLayerHead->beginChoosePkObject();
    m_pLayerHead->setIsTouchEnabled(false);
    
}
void GameStatePlay::endChoosePkObject()
{
    m_pLayerAboveHead->setColor(1.0, 1.0, 1.0, 1.0);
    m_pLayerAction->setColor(1.0, 1.0, 1.0, 1.0);
    m_pLayerAction->setIsTouchEnabled(true);
    //m_pLayerHead->endChoosePkObject();
    m_pLayerHead->setIsTouchEnabled(true);
}

//胜利
void GameStatePlay::win(int seatId)
{
    m_pLayerUnderHead->endCountdown();
    //胜利动画
    printf("\n============================\n");
    printf("WIN!!!\n");
    printf("============================\n");
}


//换座位的效果
void GameStatePlay::shiftSeat()
{
    m_pEaseShiftSeat->reset();
    m_pEaseShiftSeat->resume();
}
void GameStatePlay::shiftSeatCallbackStart(float ratio)
{
    for (int i=0; i<6; i++) {
        tmp_seat_position[i][0]=g_seat_position[i][0];
        tmp_seat_position[i][1]=g_seat_position[i][1];
        tmp_banker_position[i][0]=g_banker_position[i][0];
        tmp_banker_position[i][1]=g_banker_position[i][1];
        tmp_cards_position[i][0]=g_cards_position[i][0];
        tmp_cards_position[i][1]=g_cards_position[i][1];
        //printf("tmp seat:%d, banker:%d, cards:%d\n",tmp_seat_position[i][0],tmp_banker_position[i][0],tmp_cards_position[i][0]);
    }
    //printf("call back start over.\n");
}
void GameStatePlay::shiftSeatCallback(float ratio)
{
    //printf("in update callback.\n");
    
    int curPlayerSeat=0;
    for (int i=0; i<6; i++) {
        if (g_seat_info[i].uid == g_user.uid) {
            curPlayerSeat=i;
            //printf("current seat is:%d \tcurrent ease ratio is:%f\n",curPlayerSeat,ratio);
            break;
        }
    }
    int desPos;
    for (int i=0; i<6; i++) {
        desPos=(i+(6-curPlayerSeat))%6;
        g_seat_position[i][0]=tmp_seat_position[i][0]+ratio*(g_seat_init_position[desPos][0]-tmp_seat_position[i][0]);
        g_seat_position[i][1]=tmp_seat_position[i][1]+ratio*(g_seat_init_position[desPos][1]-tmp_seat_position[i][1]);
        g_banker_position[i][0]=tmp_banker_position[i][0]+ratio*(g_banker_init_position[desPos][0]-tmp_banker_position[i][0]);
        g_banker_position[i][1]=tmp_banker_position[i][1]+ratio*(g_banker_init_position[desPos][1]-tmp_banker_position[i][1]);
        g_cards_position[i][0]=tmp_cards_position[i][0]+ratio*(g_cards_init_position[desPos][0]-tmp_cards_position[i][0]);
        g_cards_position[i][1]=tmp_cards_position[i][1]+ratio*(g_cards_init_position[desPos][1]-tmp_cards_position[i][1]);
    }
    m_pLayerAboveHead->shiftSeat();
    m_pLayerHead->shiftSeat();
}
