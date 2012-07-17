/*
 *  PlayLayerAboveHead.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "PlayLayerAboveHead.h"
#include "GlobalData.h"
#include "GameStatePlay.h"

static int chipPool[2] = {480, 320};
static int chipValus[7] = {1,2,5,10,50,100,1000};

PlayLayerAboveHead::PlayLayerAboveHead()
{
    GEScene* pScene = GEDirector::GetInstance()->getScene("StatePlay");
    pScene->addChild(this,20);
    
    for (int i=0; i<6; i++) {
        m_pMovingChips[i] = new ClassMoveChip(this,i);
    }
    m_pChip1 = GEImage::imageFromImage("chip1");
    m_pChip2 = GEImage::imageFromImage("chip2");
    m_pChip5 = GEImage::imageFromImage("chip5");
    m_pChip10= GEImage::imageFromImage("chip10");
    m_pChip50= GEImage::imageFromImage("chip50");
    m_pChip100=GEImage::imageFromImage("chip100");
    m_pChip1K= GEImage::imageFromImage("chip1000");
    //Banker
    m_pBanker= GEImage::imageFromImage("bankerIcon");
    this->addChild(m_pBanker,1);
    m_pBanker->setIsVisible(false);
    m_pBanker->setPosition(480, 320);
    //显示筹码池筹码数量
    m_pChipsInPool = GEText::textWithText("0");
    this->addChild(m_pChipsInPool);
    m_pChipsInPool->setIsVisible(false);
    m_pChipsInPool->setPosition(480, 320);
    
    
    //移动庄家标识动画设置
    m_pEaseChangeBanker = new GEEaseNumber();
    m_pEaseChangeBanker->setSingleCycleDuration(1.0);
    m_pEaseChangeBanker->setEaseType(sineEaseInOut);
    m_pEaseChangeBanker->setTargetAndCallBacks(this, 
                                               NULL,
                                               schedule_selector(PlayLayerAboveHead::changeBankerCallBack),
                                               NULL);
    
    
    
    for (int i=0; i<18; i++) {
        m_pCardBack[i] = GEImage::imageFromImage("cardBack");
        m_pCardBack[i]->setIsVisible(false);
        this->addChild(m_pCardBack[i],0);
    }
    
    //发牌相关
    m_iCurrentDealCard=0;
    //定时发牌，完成发18张牌
    m_pTimerDealNext=new GETimer();
    m_pTimerDealNext->setDuration(0.30); //这个时间要比m_pEaseDealAnimation的时间至少多0.05秒，否则缓动效果会不到位
    m_pTimerDealNext->setNotifyTarget(this);
    m_pTimerDealNext->setFuncOnTimerComplete(schedule_selector(PlayLayerAboveHead::dealNextComplete));
    
    //发每一张牌动画效果
    m_pEaseDealAnimation = new GEEaseNumber();
    m_pEaseDealAnimation->setEaseType(sineEaseOut);
    m_pEaseDealAnimation->setSingleCycleDuration(0.25);
    m_pEaseDealAnimation->setTargetAndCallBacks(this, NULL,
                                                schedule_selector(PlayLayerAboveHead::dealAnimationCallback));
    
    //看牌动画效果
    m_bIsSeeCardHidding=true;
    m_pSeeCardTimer = new GETimer();
    m_pSeeCardTimer->setDuration(0.4);
    m_pSeeCardTimer->setNotifyTarget(this);
    m_pSeeCardTimer->setFuncOnTimerUpdate(schedule_selector(PlayLayerAboveHead::seeCardCallbackUpdate));
    m_pSeeCardTimer->setFuncOnTimerComplete(schedule_selector(PlayLayerAboveHead::seeCardCallbackComplete));
    
}
PlayLayerAboveHead::~PlayLayerAboveHead(){}

void PlayLayerAboveHead::refresh()
{
    if (g_table_state.state==TABLE3CSTAT_IDLE) {
        m_pChipsInPool->setIsVisible(false);
        for (int i=0; i<18; i++) {
            m_pCardBack[i]->setImage("cardBack");
            m_pCardBack[i]->setIsVisible(false);
            m_pCardBack[i]->setScaleX(1.0);
            m_pCardBack[i]->setRotation(0.0);
            m_pCardBack[i]->setPosition(480,320);
        }
    }
    else if (g_table_state.state==TABLE3CSTAT_PLAYING) {
        char n[16];
        memset(n, 0, 16);
        sprintf(n, "%d",g_table_state.chipPool);
        m_pChipsInPool->setText(n);
        m_pChipsInPool->setIsVisible(true);
        //处理没牌的、弃牌的、明牌的、暗牌的
        for (int i=0; i<6; i++) {
            if (g_seat_info[i].state==0 || g_seat_info[i].state==SEAT3CSTAT_GIVEUP || g_seat_info[i].state==SEAT3CSTAT_LOSE || g_seat_info[i].state==SEAT3CSTAT_WAIT) {
                //弃牌的
                int _1stCard=i-g_table_state.banker;
                if (i<g_table_state.banker) _1stCard+=6;
                for (int j=0; j<3; j++) {
                    m_pCardBack[_1stCard+j*6]->setIsVisible(false);
                }
            }
            //暂时关闭下面的语句。不同状态下应该显示不同的效果，暂时先做统一的效果。
//            else if (g_seat_info[i].state==SEAT3CSTAT_LOSE) {
//                //输的
//            }
//            else if (g_seat_info[i].state==SEAT3CSTAT_WAIT) {
//                //正在等待
//            }
        }
        //处理池中的筹码
    }
}

void PlayLayerAboveHead::onEnter()
{}

void PlayLayerAboveHead::onExit()
{
    m_pTimerDealNext->resetTimer();
    m_pEaseDealAnimation->reset();
}

#pragma mark -
#pragma mark Change Banker

void PlayLayerAboveHead::changeBanker()
{
    if (g_table_state.banker==0) {
        printf("\n======================\nWARNING:banker is 0.\n======================\n");
        m_pBanker->setIsVisible(false);
    }else {
        m_pBanker->setIsVisible(true);
        m_iBankerPreX=m_pBanker->getPosition().x;
        m_iBankerPreY=m_pBanker->getPosition().y;
        m_pEaseChangeBanker->reset();
        m_pEaseChangeBanker->resume();
    }
}
void PlayLayerAboveHead::changeBankerCallBack(float ratio)
{
    m_pBanker->setPosition(m_iBankerPreX+ratio*(g_banker_position[g_table_state.banker-1][0]-m_iBankerPreX), 
                           m_iBankerPreY+ratio*(g_banker_position[g_table_state.banker-1][1]-m_iBankerPreY));
    if (ratio>=1.0) {
        m_pBanker->setPosition(g_banker_position[g_table_state.banker-1][0],g_banker_position[g_table_state.banker-1][1]);
    }
}

#pragma mark -
#pragma mark Deal Cards

void PlayLayerAboveHead::deal()
{
    for (int i=0; i<18; i++) {
        m_pCardBack[i]->setImage("cardBack");
        m_pCardBack[i]->setIsVisible(false);
        m_pCardBack[i]->setScaleX(1.0);
        m_pCardBack[i]->setRotation(0.0);
        m_pCardBack[i]->setPosition(480,320);
    }
    m_iCurrentDealCard=-1;
    dealNextComplete(0);
}

bool PlayLayerAboveHead::isDealing()
{
    return (m_iCurrentDealCard==-1 || m_iCurrentDealCard>=17)?false:true;
}

//定时器回调，发下一张牌
void PlayLayerAboveHead::dealNextComplete(float dt)
{
    m_iCurrentDealCard++;
    if (m_iCurrentDealCard==18) {
        m_iCurrentDealCard=-1;
        return;
    }
    int tmp = m_iCurrentDealCard+g_table_state.banker;
    int cardPlayer=tmp<6?tmp:(tmp<12?(tmp-6):(tmp<18?(tmp-12):(tmp-18)));
    if (g_seat_info[cardPlayer].state!=10) {
        dealNextComplete(0);
        return;
    }
    m_pCardBack[m_iCurrentDealCard]->setIsVisible(true);
    //设置牌发出的位置
    m_pCardBack[m_iCurrentDealCard]->setPosition(480, 320);
    m_pTimerDealNext->resetTimer();
    m_pTimerDealNext->resume();
    m_pEaseDealAnimation->reset();
    m_pEaseDealAnimation->resume();
}
//发牌缓动效果的回调
void PlayLayerAboveHead::dealAnimationCallback(float ratio)
{
    int tmp = m_iCurrentDealCard+g_table_state.banker;
    int cardPlayer=tmp<6?tmp:(tmp<12?(tmp-6):(tmp<18?(tmp-12):(tmp-18)));
    int cardOrder=m_iCurrentDealCard/6;//当前是第几张手牌
    
    m_pCardBack[m_iCurrentDealCard]->setPosition(480+ratio*(g_cards_position[cardPlayer][0]-480)+(cardOrder-1)*15, //牌的错位
                                                 320+ratio*(g_cards_position[cardPlayer][1]-320));
    m_pCardBack[m_iCurrentDealCard]->setRotation(ratio*M_PI+(cardOrder-1)*(-3.1416/9.0));
    if (ratio>=1.0 && m_iCurrentDealCard==17) {
        GameStatePlay::GetInstance()->next();
    }
}

#pragma mark -
#pragma mark See Cards
//某玩家看牌
void PlayLayerAboveHead::seeCard(int seatId)
{
    m_i1stCard=(seatId>=g_table_state.banker?(seatId-g_table_state.banker):(seatId+6-g_table_state.banker));
    if (g_user.uid==g_seat_info[seatId].uid) {
        printf("see card id is:%d\n",seatId);
        m_bIsSeeCardHidding=true;
        m_pSeeCardTimer->resetTimer();
        m_pSeeCardTimer->resume();
    }
    else {
        //画seatId上的明牌图片效果
        for (int i=0; i<3; i++) 
            m_pCardBack[m_i1stCard+i*6]->setImage("brightCard");
    }
}
//某玩家弃牌
void PlayLayerAboveHead::giveUp(int seatId)
{
    
}

void PlayLayerAboveHead::seeCardCallbackUpdate(float dt)
{
    for (int i=0; i<3; i++) {
        if (m_bIsSeeCardHidding) {
            m_pCardBack[m_i1stCard+i*6]->setScaleX(1.0-m_pSeeCardTimer->m_fRatio);
        }
        else {
            m_pCardBack[m_i1stCard+i*6]->setScaleX(m_pSeeCardTimer->m_fRatio);
        }
    }
}

void PlayLayerAboveHead::seeCardCallbackComplete(float dt)
{
    if (m_bIsSeeCardHidding) {
        m_bIsSeeCardHidding=false;
        char cardColorNum[32];
        for (int i=0; i<3; i++) {
            sprintf(cardColorNum, "%c%d", g_seat_info[g_user.location[3]-1].cardColor[i],g_seat_info[g_user.location[3]-1].cardNum[i]);
            //m_pCardBack[m_i1stCard+i*6]->setImage(cardColorNum);
            m_pCardBack[m_i1stCard+i*6]->setImage("TestCard0");
            m_pCardBack[m_i1stCard+i*6]->setScaleX(0.0);
        }
        m_pSeeCardTimer->resetTimer();
        m_pSeeCardTimer->resume();
    }
}


#pragma mark -
#pragma mark Move Chips
void PlayLayerAboveHead::moveChipsFromPositionToPool(int position, int number)
{
    if (position<0 || position>5)
        return;
    m_pMovingChips[position]->moveChips(number);
    
}

#pragma mark -
#pragma mark Shift Cards and Banker Moving with Seat
//座位的移动的同时，座位旁边的牌也要跟随移动
void PlayLayerAboveHead::shiftSeat()
{
    if (m_iCurrentDealCard==0) {
        return;
    }
    int player,fstCard;
    for (int i=0; i<(m_iCurrentDealCard>=0?m_iCurrentDealCard:18); i++) {
        player=(g_table_state.banker+i%6);
        player=player>=6?(player-6):player;
        fstCard=i/6;
        m_pCardBack[i]->setPosition(g_cards_position[player][0]+(fstCard-1)*15, g_cards_position[player][1]);
    }
    int b=g_table_state.banker>0?(g_table_state.banker-1):0;
    m_pBanker->setPosition(g_banker_position[b][0], g_banker_position[b][1]);
    return;
}






#pragma mark -
#pragma mark ClassMoveChip

ClassMoveChip::ClassMoveChip(GELayer* layer,int position)
{
    m_pLayer = layer;
    m_iPosition = position;
    m_bIsMoving=false;
    m_vAllMovingChips.reserve(15);
    m_vAllMovingChips.clear();
    m_pEaseMoveChip = new GEEaseNumber;
    m_pEaseMoveChip->setEaseType(sineEaseInOut);
    m_pEaseMoveChip->setSingleCycleDuration(1.0);
    m_pEaseMoveChip->setTargetAndCallBacks(this, 
                                           NULL,
                                           schedule_selector(ClassMoveChip::moveChipsUpdate),
                                           schedule_selector(ClassMoveChip::moveChipsComplete),
                                           NULL);
    
}
ClassMoveChip::~ClassMoveChip()
{
    
}

void ClassMoveChip::moveChips(int number)
{
    if (m_bIsMoving) {
        moveChipsComplete(1.0);
    }
    m_bIsMoving=true;
    int everyChipNumber[7];
    for (int i=0; i<7; i++) {
        everyChipNumber[i] = (i<6)?((number%chipValus[i+1])/chipValus[i]):(number/chipValus[i]);
        int j=everyChipNumber[i];
        if (j>0) {
            for ( ; j>0; j--) {
                char chipPic[10];
                sprintf(chipPic, "chip%d",chipValus[i]);
                GEImage* pImage=GEImage::imageFromImage(chipPic);
                pImage->setPosition(g_seat_position[m_iPosition][0], g_seat_position[m_iPosition][1]);
                m_pLayer->addChild(pImage);
                m_vAllMovingChips.push_back(pImage);
            }
//            topChip[i]=j;//设置玩家所出的最大的一个筹码
        }
    }
    m_pEaseMoveChip->reset();
    m_pEaseMoveChip->resume();
    
}

void ClassMoveChip::moveChipsUpdate(float ratio)
{
    if (m_bIsMoving && m_vAllMovingChips.size()>0) {
        float r=m_pEaseMoveChip->m_fCurrentValue;
        for (int i=0; i<m_vAllMovingChips.size(); i++) {
            m_vAllMovingChips[i]->setPosition(g_seat_position[m_iPosition][0]+(chipPool[0]-g_seat_position[m_iPosition][0])*pow(r,i+1), 
                                              g_seat_position[m_iPosition][1]+(chipPool[1]-g_seat_position[m_iPosition][1])*pow(r,i+1));
        }
    }
}

void ClassMoveChip::moveChipsComplete(float ratio)
{
    if (m_bIsMoving && m_vAllMovingChips.size()>0) {
        for (int i=0; i<m_vAllMovingChips.size(); i++) {
            m_pLayer->removeChild(m_vAllMovingChips[i]);
            delete m_vAllMovingChips[i];
        }
        m_vAllMovingChips.clear();
        m_bIsMoving=false;
        m_pEaseMoveChip->reset();
    }
    GameStatePlay::GetInstance()->refreshPlayerInfo();
}

