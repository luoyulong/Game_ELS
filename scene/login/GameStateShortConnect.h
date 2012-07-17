/*
 *  GEStateConnect.h
 *  Dice
 *
 *  Created by F.K. on 12-4-26.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

/*  
 *  GameStateShortConnect用于在网络连接时 显示等待 以及 网络状态 等信息。
 */


#ifndef _GAME_STATE_CONNECT_H_
#define _GAME_STATE_CONNECT_H_
#define NET_CONNECT_BUFFER    1024
#include "GameEngine.h"
#include "dataDefine.h"
#include "cJSON.h"

class GameStateShortConnect : public SelectorProtocol
{
public:
    static GameStateShortConnect* GetInstance();
    
    GameStateShortConnect();
    ~GameStateShortConnect();
    
    //发送短连接消息
    void sendMsg(const char *msg, GENet *p_Net);
    
    //登陆相关
    void quickStartReq(const char *deviceId);
    void logInFromSNS(const char* userType, const char* usrId, const char* nick_name, const char* picurl);
    void logInFromTourist(const char* usrId, const char* nick_name);

    //外围信息
    //void message(int msgType);
    
    //领取奖励
    void rewards();
    //是否领取过奖励
    void isReward(int i);
    
    void acts();
    void store();
    //void friends();
    void feedback(const char *msg);
    
    void netShortCallBack(const char *msg);
private:
    static GameStateShortConnect* m_pSelf;
    GENet   *m_pShortNet;
    char    m_cNetRequest[NET_CONNECT_BUFFER];
    GEText  *m_pText;
    

};
#endif