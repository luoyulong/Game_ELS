/*
 *  PlayLayerAboveHead.h
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _PLAY_LAYER_ABOVE_HEAD_H_
#define _PLAY_LAYER_ABOVE_HEAD_H_
#include "GameEngine.h"

class ClassMoveChip;

class PlayLayerAboveHead: public GELayer
{
public:
    PlayLayerAboveHead();
    ~PlayLayerAboveHead();
    
    
    //根据全局数据更新层内元素的状态
    void refresh();
    
    //改变庄家
    void changeBanker();
    //发牌
    void deal();
    // 下注操作，筹码由玩家头像移动到面前的桌子上。参数：下注数量。
    // 可能根据下注数量的不同，显示不同颜色的筹码
    void addChips(int chip);
    // 一圈下注结束后，将每个人面前的筹码移动到桌子中央的筹码池中
    void moveChipsToTable();
    //test
    void moveChipsFromPositionToPool(int position, int number);
    // 弃牌
    void giveUp(int seatId);
    // 看牌
    void seeCard(int seatId);
    //转化座位，需要更新内部图的位置
    void shiftSeat();
    
    //是否正在发牌
    bool isDealing();
    
    void onEnter();
    void onExit();
private:
    
    //移动庄家标识的回调
    void changeBankerCallBack(float ratio);
    //发牌缓动效果的回调
    void dealAnimationCallback(float ratio);
    //定时器回调，发下一张牌
    void dealNextComplete(float dt);
    //定时器回调，显示牌型
    void seeCardCallbackUpdate(float dt);
    void seeCardCallbackComplete(float dt);
    
private:
    GEImage     *m_pChip1, *m_pChip2, *m_pChip5, *m_pChip10, *m_pChip50, *m_pChip100, *m_pChip1K;
    ClassMoveChip   *m_pMovingChips[6];
    GEText      *m_pChipsInPool;
    
    //banker和发牌的效果
    GEImage       *m_pBanker, *m_pCardBack[18];
    GEEaseNumber  *m_pEaseChangeBanker;
    int           m_iBankerPreX;
    int           m_iBankerPreY;
    
    int           m_iCurrentDealCard;
    GETimer       *m_pTimerDealNext;//发牌时间定时器
    GEEaseNumber  *m_pEaseDealAnimation;//发牌动画
    
    //看牌
    bool          m_bIsSeeCardHidding;//复用定时器m_pSeeCardTimer，标记渐隐和渐显两个过程。
    GETimer       *m_pSeeCardTimer;
    int           m_i1stCard;
};





class ClassMoveChip : public SelectorProtocol
{
public:
    ClassMoveChip(GELayer* layer,int position);
    ~ClassMoveChip();
    void moveChips(int number);
    
private:
    void moveChipsUpdate(float ratio);
    void moveChipsComplete(float ratio);
    
private:
    int     m_iPosition;
    GELayer*  m_pLayer;
    bool    m_bIsMoving;
    GEEaseNumber *m_pEaseMoveChip;
    vector<GEImage*>  m_vAllMovingChips;
};
#endif