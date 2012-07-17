/*
 *  GEStatePlay.h
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _GAME_STATE_PLAY_H_
#define _GAME_STATE_PLAY_H_

/*
 *  StatePlay是玩牌的场景，负责
 *  1、生成1个PlayLayerAboveHead对象;
 *  2、生成1个PlayLayerHead对象;
 *  3、生成1个PlayLayerUnderHead对象;
 *  4、生成1个PlayLayerAction对象;(本机玩家可执行的操作，出牌，聊天，退出等)
 */

/*  
 *  PlayLayerHead、PlayLayerAboveHead以及PlayLayerUnderHead叠加组合，可以画出桌上玩家(6个)的所有行为动画，其中:
 *
 *  Head:
 *      2个Menu层，占据第0层和第30层。
 *      第0层显示玩家的个人信息，2个按钮。平时隐藏，只有点击了玩家头像才显示出来。
 *      第30层显示玩家头像。
 *
 *  AboveHead:
 *      暂定1个Layer层，占第20层.
 *      第20层显示一些玩家头像之上的动画效果，如下注，发牌，弃牌等。
 *      此层只是提供接口画相应的动画，被动接受StatePlayController的调用，然后根据调用参数或者全局数据画动画效果。
 *
 *  UnderHead:
 *      暂定1个Layer层，占第40层。
 *      第40层显示一些玩家头像之下的动画效果，如倒计时等。
 *      此层也是被动接受StatePlayController的调用，根据全局数据画动画效果。
 * 
 *  Action:
 *      暂定1个Menu层，1个Layer层和1个Menu，分别占第10，11，12层。
 *      第10层提供玩家的操作按钮，如聊天，帮助，退出，以及下注，弃牌等按钮。
 *      第11层显示某些表情等效果。
 *      第12层确认站起。平时隐藏，玩家准备站起时出现。
 *
 *  层与层之间预留9个空层，以备后续的添加
 */
#include "GameEngine.h"
#include "PlayLayerHead.h"
#include "PlayLayerAboveHead.h"
#include "PlayLayerUnderHead.h"
#include "PlayLayerAction.h"

class GameStatePlay: public GELayer
{
public:
    GameStatePlay();
    ~GameStatePlay();
    static GameStatePlay* GetInstance();
    
    //由于onEnter在转场效果结束之后才会被调用，而Play场景在进场之前就需要把所有元素初始化好，
    //所以用preEnterScene()函数来准备，在进场前被StateMainMenu调用
    void preEnterScene();
    
    //新游戏开始,换庄家，开始发牌，开始倒计时
    void gameStart();
    
    //将chipNumber数目的筹码从player面前移动到筹码池中
    void moveChipsFromPlayerToPool(int player,int chipNumber);

    //更新桌子玩家玩家信息，在有人坐下、站起时调用。
    //以及【筹码池状态】,在筹码移动结束后调用
    void refreshPlayerInfo();
    //更新按钮状态
    void refreshButtonStatus();
    
    
    //更新桌子的最小注，轮次以及倒计时动画等信息，在收到SL_NEXT后调用
    void next();
    bool isDealing();
    
    //开始及结束选择PK对象，在这期间，玩家头像保持有效，其他所有层按钮失效
    void beginChoosePkObject();
    void endChoosePkObject();

    
    //看牌
    void seeCard(int seatId);//0-5
    //弃牌
    void giveUp(int seatId);//0-5
    //胜利
    void win(int seatId);
    
    void shiftSeat();
    
    
private:
    //玩家坐下后，头像的转动效果。
    void shiftSeatCallbackStart(float ratio);
    void shiftSeatCallback(float ratio);
    
    
private:
    static GameStatePlay*  m_pSelf;
    PlayLayerAction*       m_pLayerAction;
    PlayLayerHead*         m_pLayerHead;
    PlayLayerAboveHead*    m_pLayerAboveHead;
    PlayLayerUnderHead*    m_pLayerUnderHead;//倒计时效果
    GEEaseNumber*          m_pEaseShiftSeat;
    
//public:
//    //在转动座位开始时保存转动前的位置，转动过程中依据tmp_*_pos和g_*_init_pos以及ratio改变每个座位的坐标
//    int    tmp_seat_position[6][2];
//    int    tmp_banker_position[6][2];
//    int    tmp_cards_position[6][2];

};
#endif