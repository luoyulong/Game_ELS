/*
 *  gameNetCenter.h
 *  3Cards
 *
 *  Created by F.K. on 12-5-8.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#ifndef _GAME_NET_CENTER_H_
#define _GAME_NET_CENTER_H_
#include "GameEngine.h"
#define HEART_BEAT_SEND_TIME     3.0
#define HEART_BEAT_MAX_TIME      10.0
#define TIME_BERWEEN_2_GAME      2.0


class GameStatePlay;

class gameNetCenter : public SelectorProtocol
{
public:
    bool    m_bIsQuickStart, m_bQuickStartAutoSit;
    
public:
    gameNetCenter();
    ~gameNetCenter();
    static gameNetCenter* GetInstance();
    
    /*
     *  房间相关的操作
     */
    void quickStart(int roomId, int tableId, bool autosit=true);
    void enterRoom(int roomId);
    void refreshRoom(); 
    //void exitField();//离开某个场(普通场或淘汰场)返回到主菜单(MainMenu)时用。在普通场内部转换房间(1-4)不需要调用。
    
    /*
     *  桌子相关的操作
     */
    void enterTable(int tableId, const char* pwd);
    void getTableInfo();
    void sit(int seatId);
    void standUp();
    void leaveTable();
    void leaveRoom();
    
    /*
     *  玩牌相关的操作
     */
    void seeCard(int seatId);//1-6
    void betChip(int seatId, int chipNumber);
    void pkOne(int seatId, int pkSeat);
    void pkAll(int seatId);
    void giveUp(int seatId);
    /*
     *  外围功能
     */
    void coin2Chip(int coin, int seatId);
    void sendMsg(const char* msg, int serverPort=LONGPORT);
    void closeConn();
private:
    void netLongCallback(const char* msg);
    void heartBeatComplete(float dt);//计时结束发送下一个心跳
    void heartBeatMax(float dt);//计时结束，表示长时间没有收到服务器对心跳信号的回应，与服务器断开连接。
    void checkBeforeNewGame(float dt);
    
private:
    static gameNetCenter *m_sSelf;
    GameStatePlay   *m_pStatePlay;
    
    char    m_cNetBuffer[1024];
    GENet   *m_pNetLong;//游戏过程中的长连接。
    bool    m_bIsFirstConnect;
    GETimer *m_pHeartBeatTime;//前者是每次心跳的时间间隔，后者是服务器响应的最大时间间隔。
    int     m_iQuickStartRoomId, m_iQuickStartTableId;
    int     m_iCurrentPort;
    GETimer *m_pTimerBeforeNewGame;
    
public:
    bool    m_cancelLogin;
    bool    m_cancelEnterRoom;
    bool    m_cancelEnterTable;
    
};
#endif
