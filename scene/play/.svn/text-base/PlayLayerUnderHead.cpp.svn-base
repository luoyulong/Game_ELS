/*
 *  PlayLayerUnderHead.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-4-27.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "PlayLayerUnderHead.h"
#include "GlobalData.h"


PlayLayerUnderHead::PlayLayerUnderHead()
{
    //m_fTotoalTime=0.0;
    m_fUsedTime = 0.0;
    m_pTimer = new GETimer();
    m_pTimer->setNotifyTarget(this);
    m_pTimer->setFuncOnTimerUpdate(schedule_selector(PlayLayerUnderHead::countDownUpdate));
    m_pTimer->setFuncOnTimerComplete(schedule_selector(PlayLayerUnderHead::countDownComplete));
    
    for (int i=0; i<5; i++) {
        if (i==4) {
            m_pRect[4] = new GEDisplayRect();
            m_pRect[4]->setColor(0.0, 0.0, 0.0, 0.0);
            this->addChild(m_pRect[4]);
            break;
        }
        m_pRect[i] = new GEDisplayRect();
        m_pCorner[i] = new GEDisplayEmptyCircle();
        m_pRect[i]->setColor(0.0, 0.0, 0.0, 0.0);
        m_pCorner[i]->setColor(0.0, 0.0, 0.0, 0.0);
        this->addChild(m_pRect[i]);
        this->addChild(m_pCorner[i]);
    }
    for (int i=0;i<2;i++) {
        m_pCircle[i] = new GEDisplayCircle();
        this->addChild(m_pCircle[i]);
    }
    
    //breakPoints
    float fTotalLength = 2.0*(COUNT_DOWN_WIDTH+COUNT_DOWN_HEIGHT)-8.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS+2.0*M_PI*COUNT_DOWN_MIDDLE_RADIUS;
    float fCornerLength = 0.5*M_PI*COUNT_DOWN_MIDDLE_RADIUS;
    m_fBreakPoints[0]=0.0;
    m_fBreakPoints[1]=((COUNT_DOWN_WIDTH-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS)/2.0)/fTotalLength;
    m_fBreakPoints[2]=fCornerLength/fTotalLength+m_fBreakPoints[1];
    m_fBreakPoints[3]=(COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS)/fTotalLength+m_fBreakPoints[2];
    m_fBreakPoints[4]=fCornerLength/fTotalLength+m_fBreakPoints[3];
    m_fBreakPoints[5]=(COUNT_DOWN_WIDTH-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS)/fTotalLength+m_fBreakPoints[4];
    m_fBreakPoints[6]=fCornerLength/fTotalLength+m_fBreakPoints[5];
    m_fBreakPoints[7]=(COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS)/fTotalLength+m_fBreakPoints[6];
    m_fBreakPoints[8]=fCornerLength/fTotalLength+m_fBreakPoints[7];
    m_fBreakPoints[9]=1.0;
    
}

PlayLayerUnderHead::~PlayLayerUnderHead()
{
    
}

#pragma mark -
#pragma mark public methods

void PlayLayerUnderHead::startCountdown(int player, float time)
{
    if (player<0 || player>=6) {
        return;
    }
    m_pRect[0]->fillRect(g_seat_position[player][0], 
                         g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD, 
                         COUNT_DOWN_WIDTH/2.0-COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_BOLD);
    
    m_pRect[1]->fillRect(g_seat_position[player][0]+(COUNT_DOWN_WIDTH/2.0), 
                         g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                         COUNT_DOWN_BOLD, COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS);
    
    m_pRect[2]->fillRect(g_seat_position[player][0]-(COUNT_DOWN_WIDTH/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                         g_seat_position[player][1]+(COUNT_DOWN_HEIGHT/2.0), 
                         COUNT_DOWN_WIDTH-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_BOLD);
    
    m_pRect[3]->fillRect(g_seat_position[player][0]-(COUNT_DOWN_WIDTH/2.0)-COUNT_DOWN_BOLD, 
                         g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                         COUNT_DOWN_BOLD, COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS);
    
    m_pRect[4]->fillRect(g_seat_position[player][0]-(COUNT_DOWN_WIDTH/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                         g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD, 
                         COUNT_DOWN_WIDTH/2.0-COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_BOLD);

    
    
    
    m_pCorner[0]->fillEmptyCircle(g_seat_position[player][0]+(COUNT_DOWN_WIDTH/2.0)-COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_OUTER_ROUNDREC_RADIUS,
                                  0,-90);
    
    m_pCorner[1]->fillEmptyCircle(g_seat_position[player][0]+(COUNT_DOWN_WIDTH/2.0)-COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  g_seat_position[player][1]+(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_OUTER_ROUNDREC_RADIUS,
                                  -90,-90);
    
    m_pCorner[2]->fillEmptyCircle(g_seat_position[player][0]-(COUNT_DOWN_WIDTH/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  g_seat_position[player][1]+(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_OUTER_ROUNDREC_RADIUS,
                                  180,-90);
    
    m_pCorner[3]->fillEmptyCircle(g_seat_position[player][0]-(COUNT_DOWN_WIDTH/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                  COUNT_DOWN_INNER_ROUNDREC_RADIUS, COUNT_DOWN_OUTER_ROUNDREC_RADIUS,
                                  90,-90);

    m_pCircle[0]->fillCircle(g_seat_position[player][0], 
                          g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD/2.0, 
                          COUNT_DOWN_BOLD/2.0);
    m_pCircle[0]->setScale(1.0);
    m_pCircle[1]->fillCircle(g_seat_position[player][0], 
                             g_seat_position[player][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD/2.0, 
                             COUNT_DOWN_BOLD/2.0);
    m_pCircle[1]->setScale(1.0);
    
    
    for (int i=0; i<5; i++) {
        m_pRect[i]->setIsVisible(true);
    }
    for (int i=0; i<4; i++) {
        m_pCorner[i]->setIsVisible(true);
    }
    m_pCircle[0]->setIsVisible(true);
    m_pCircle[1]->setIsVisible(true);
    
    m_fCurrentPlayer=player;
    //m_fTotoalTime=time;
    m_fUsedTime=0.0;
    m_pTimer->resetTimer();
    m_pTimer->setDuration(time);
    m_pTimer->resume();
    printf("start countdonw.\n");
}

void PlayLayerUnderHead::pauseCountdown()
{
    m_pTimer->pause();
}

void PlayLayerUnderHead::endCountdown()
{
    m_pTimer->resetTimer();
    for (int i=0; i<5; i++) {
        m_pRect[i]->setIsVisible(false);
    }
    for (int i=0; i<4; i++) {
        m_pCorner[i]->setIsVisible(false);
    }
    m_pCircle[0]->setIsVisible(false);
    m_pCircle[1]->setIsVisible(false);
}



#pragma mark -
#pragma mark private methods
void PlayLayerUnderHead::countDownUpdate(float dt)
{
    m_fUsedTime+=dt;
    //float ratio=(float)(m_fUsedTime/m_fTotoalTime);
    float ratio=(float)(m_fUsedTime/g_table_info.opTime);
    
    float colorR=START_COLOR_R+ratio*(END_COLOR_R-START_COLOR_R);
    float colorG=START_COLOR_G+ratio*(END_COLOR_G-START_COLOR_G);
    float colorB=START_COLOR_B+ratio*(END_COLOR_B-START_COLOR_B);
    
    for (int i=0; i<5; i++) {
        m_pRect[i]->setColor(colorR, colorG, colorB, 1.0);
    }
    for (int i=0; i<4; i++) {
        m_pCorner[i]->setColor(colorR, colorG, colorB, 1.0);
    }
    m_pCircle[0]->setColor(colorR, colorG, colorB, 1.0);
    m_pCircle[1]->setColor(colorR, colorG, colorB, 1.0);
    
    
    renderCountDown(ratio);
}

void PlayLayerUnderHead::countDownComplete(float dt)
{
    m_pRect[4]->setIsVisible(false);
    m_pCircle[0]->setIsVisible(false);
    m_pCircle[1]->setIsVisible(false);
    
}

void PlayLayerUnderHead::renderCountDown(float ratio)
{
    for (int i=0; i<=8; i++) {
        if (ratio>=m_fBreakPoints[i] && ratio<m_fBreakPoints[i+1]) {
            float r=(ratio-m_fBreakPoints[i])/(m_fBreakPoints[i+1]-m_fBreakPoints[i]);
            switch (i) {
                case 0:
                {
                    float w=ceil(r*(COUNT_DOWN_WIDTH-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS)/2.0);
                    m_pRect[0]->fillRect(g_seat_position[m_fCurrentPlayer][0]+w, 
                                         g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD, 
                                         COUNT_DOWN_WIDTH/2.0-COUNT_DOWN_INNER_ROUNDREC_RADIUS-w, COUNT_DOWN_BOLD);
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]+w, 
                                           g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD/2.0);
                    break;
                }
                case 1:
                {
                    m_pRect[0]->setIsVisible(false);
                    m_pCorner[0]->setSustainAngle(-90*(1.0-r));
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]+(COUNT_DOWN_WIDTH/2.0)-
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS+COUNT_DOWN_MIDDLE_RADIUS*sin(r*M_PI/2.0), 
                                           g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)+
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS-COUNT_DOWN_MIDDLE_RADIUS*cos(r*M_PI/2.0));
                    break;
                }   
                case 2:
                {
                    m_pCorner[0]->setIsVisible(false);
                    float h=ceil(r*(COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS));
                    m_pRect[1]->fillRect(g_seat_position[m_fCurrentPlayer][0]+(COUNT_DOWN_WIDTH/2.0), 
                                         g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS+h, 
                                         COUNT_DOWN_BOLD, COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS-h);
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]+(COUNT_DOWN_WIDTH/2.0)+COUNT_DOWN_BOLD/2.0, 
                                           g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)+
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS+h);
                    break;
                }
                    
                case 3:
                {
                    m_pRect[1]->setIsVisible(false);
                    m_pCorner[1]->setSustainAngle(-90*(1.0-r));
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]+(COUNT_DOWN_WIDTH/2.0)-
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS+COUNT_DOWN_MIDDLE_RADIUS*cos(r*M_PI/2.0), 
                                           g_seat_position[m_fCurrentPlayer][1]+(COUNT_DOWN_HEIGHT/2.0)-
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS+COUNT_DOWN_MIDDLE_RADIUS*sin(r*M_PI/2.0));
                    break;
                }
                    
                case 4:
                {
                    m_pCorner[1]->setIsVisible(false);
                    float w=ceil(r*(COUNT_DOWN_WIDTH-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS));
                    m_pRect[2]->fillRect(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)+
                                         COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                         g_seat_position[m_fCurrentPlayer][1]+(COUNT_DOWN_HEIGHT/2.0), 
                                         COUNT_DOWN_WIDTH-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS-w, COUNT_DOWN_BOLD);
                    
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]+(COUNT_DOWN_WIDTH/2.0)-
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS-w, 
                                           g_seat_position[m_fCurrentPlayer][1]+(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_BOLD/2.0);
                    break;
                }
                    
                case 5:
                {
                    m_pRect[2]->setIsVisible(false);
                    m_pCorner[2]->setSustainAngle(-90*(1.0-r));
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)+
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS-COUNT_DOWN_MIDDLE_RADIUS*sin(r*M_PI/2.0), 
                                           g_seat_position[m_fCurrentPlayer][1]+(COUNT_DOWN_HEIGHT/2.0)-
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS+COUNT_DOWN_MIDDLE_RADIUS*cos(r*M_PI/2.0));
                    break;
                }
                    
                case 6:
                {
                    m_pCorner[2]->setIsVisible(false);
                    float h=ceil(r*(COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS));
                    m_pRect[3]->fillRect(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)-COUNT_DOWN_BOLD, 
                                         g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)+COUNT_DOWN_INNER_ROUNDREC_RADIUS, 
                                         COUNT_DOWN_BOLD, COUNT_DOWN_HEIGHT-2.0*COUNT_DOWN_INNER_ROUNDREC_RADIUS-h);
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)-COUNT_DOWN_BOLD/2.0,
                                           g_seat_position[m_fCurrentPlayer][1]+(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_INNER_ROUNDREC_RADIUS-h);
                    break;
                }
                    
                case 7:
                {
                    m_pRect[3]->setIsVisible(false);
                    m_pCorner[3]->setSustainAngle(-90*(1.0-r));
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)+
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS-COUNT_DOWN_MIDDLE_RADIUS*cos(r*M_PI/2.0), 
                                           g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)+
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS-COUNT_DOWN_MIDDLE_RADIUS*sin(r*M_PI/2.0));
                    break;
                }
                    
                case 8:
                {
                    m_pCorner[3]->setIsVisible(false);
                    float w=ceil(r*(COUNT_DOWN_WIDTH/2.0-COUNT_DOWN_INNER_ROUNDREC_RADIUS));
                    m_pRect[4]->fillRect(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)+
                                         COUNT_DOWN_INNER_ROUNDREC_RADIUS+w, 
                                         g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD, 
                                         COUNT_DOWN_WIDTH/2.0-COUNT_DOWN_INNER_ROUNDREC_RADIUS-w, COUNT_DOWN_BOLD);
                    
                    m_pCircle[0]->setPosition(g_seat_position[m_fCurrentPlayer][0]-(COUNT_DOWN_WIDTH/2.0)+
                                           COUNT_DOWN_INNER_ROUNDREC_RADIUS+w, 
                                           g_seat_position[m_fCurrentPlayer][1]-(COUNT_DOWN_HEIGHT/2.0)-COUNT_DOWN_BOLD/2.0);
                    
                    break;
                }
                    
                    
                default:
                    break;
            }
        }
    }
}


