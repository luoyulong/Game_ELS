/*
 *  GEStateLogIn.h
 *  Dice
 *
 *  Created by F.K. on 12-4-26.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _GAME_STATE_LOG_IN_H_
#define _GAME_STATE_LOG_IN_H_

#include "GENet.h"
#include "GameEngine.h"
#include "DeviceIDWrapper.h"
#include "PlayLayerUnderHead.h"
#include "FileConfigure.h"
#include "GameStateWaiting.h"

class GameStateLogIn: public GELayer
{
public:
    GameStateLogIn();
    ~GameStateLogIn();
    
private:
    void buttonCallback(GEObject* pObj);
    
    void testSubThread();
    
    void easeSNSBtShow();
    void easeSNSBtShowCallbackStart(float ratio);
    void easeSNSBtShowCallback(float ratio);
    
private:
    GENet *m_pShortNet;
    
    /* button
     * [0]:sina account
     * [1]:tourist
     * [2]:local play
     * [3]:help
     * [4]:set
     */
    GEButton* m_pButtons[9];
    GEImage*  m_pBackGround, *m_pIndexMeinv;
    PlayLayerUnderHead* m_pCountDown;
    GEEaseNumber *m_pEaseSNSBtShow;
};
#endif