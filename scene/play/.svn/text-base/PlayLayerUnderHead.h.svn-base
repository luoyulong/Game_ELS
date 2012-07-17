/*
 *  PlayLayerUnderHead.h
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _PLAY_LAYER_UNDER_HEAD_H_
#define _PLAY_LAYER_UNDER_HEAD_H_
#include "GameEngine.h"

#define COUNT_DOWN_WIDTH    150
#define COUNT_DOWN_HEIGHT   170
#define COUNT_DOWN_INNER_ROUNDREC_RADIUS    15  //内部圆角矩形 圆角的半径
#define COUNT_DOWN_OUTER_ROUNDREC_RADIUS    25 //外部圆角矩形 圆角的半径
#define COUNT_DOWN_MIDDLE_RADIUS            ((COUNT_DOWN_INNER_ROUNDREC_RADIUS+COUNT_DOWN_OUTER_ROUNDREC_RADIUS)/2.0)
#define COUNT_DOWN_BOLD     (COUNT_DOWN_OUTER_ROUNDREC_RADIUS-COUNT_DOWN_INNER_ROUNDREC_RADIUS)

#define START_COLOR_R       0.0
#define START_COLOR_G       1.0
#define START_COLOR_B       0.0
#define END_COLOR_R         1.0
#define END_COLOR_G         0.0
#define END_COLOR_B         0.0


class PlayLayerUnderHead: public GELayer
{
public:
    PlayLayerUnderHead();
    ~PlayLayerUnderHead();

    // 开始出牌倒计时。参数：倒计时时间
    void startCountdown(int player,float time);
    void pauseCountdown();
    void endCountdown();
    
    
private:
    void countDownUpdate(float dt);
    void countDownComplete(float dt);
    void renderCountDown(float ratio);
    
    
    
private:
    int      m_fCurrentPlayer;
    float    m_fTotoalTime;
    float    m_fUsedTime;
    GETimer* m_pTimer;
    
    GEDisplayRect*  m_pRect[5];
    GEDisplayEmptyCircle*  m_pCorner[4];
    GEDisplayCircle* m_pCircle[2];
    
    float    m_fBreakPoints[10];
    
    
};


#endif