/*
 *  gameNetCenter.cpp
 *  3Cards
 *
 *  Created by F.K. on 12-5-8.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */

#include "gameNetCenter.h"
#include "cJSON.h"
#include "GlobalData.h"
#include "RoomWrapper.h"
#include "GameStatePlay.h"
#include "warningMessageWrapper.h"

gameNetCenter* gameNetCenter::m_sSelf = 0;
gameNetCenter* gameNetCenter::GetInstance()
{
    if (m_sSelf==0) {
        m_sSelf=new gameNetCenter();
    }
    return m_sSelf;
}

gameNetCenter::gameNetCenter()
{
    m_pStatePlay = GameStatePlay::GetInstance();
    
    m_pNetLong=NULL;
    g_table_list.reserve(200);
    
    m_bIsFirstConnect=true;
    m_pNetLong=GENet::netWithTarget(this, net_selector(gameNetCenter::netLongCallback));
    
    m_pHeartBeatTime=new GETimer();
    m_pHeartBeatTime->setDuration(HEART_BEAT_SEND_TIME);
    m_pHeartBeatTime->setNotifyTarget(this);
    m_pHeartBeatTime->setFuncOnTimerComplete(schedule_selector(gameNetCenter::heartBeatComplete));
    m_pHeartBeatTime->resetTimer();
    m_pHeartBeatTime->resume();
    
//    m_pHeartBeatMaxTime=new GETimer();
//    m_pHeartBeatMaxTime->setDuration(HEART_BEAT_MAX_TIME);
//    m_pHeartBeatMaxTime->setNotifyTarget(this);
//    m_pHeartBeatMaxTime->setFuncOnTimerComplete(schedule_selector(gameNetCenter::heartBeatMax));
    
    m_bIsQuickStart=false;
    //autoEnterTable=false;
    //autoEnterTableId=0;
    
    m_pTimerBeforeNewGame = new GETimer();
    m_pTimerBeforeNewGame->setDuration(TIME_BERWEEN_2_GAME);
    m_pTimerBeforeNewGame->setNotifyTarget(this);
    m_pTimerBeforeNewGame->setFuncOnTimerComplete(schedule_selector(gameNetCenter::checkBeforeNewGame));
    m_pTimerBeforeNewGame->resetTimer();
    
    
    m_cancelLogin = false;
    m_cancelEnterRoom = false;
    m_cancelEnterTable = false;
}

gameNetCenter::~gameNetCenter()
{
    delete m_pHeartBeatTime;
    //delete m_pHeartBeatMaxTime;
}

#pragma mark -
#pragma mark public methods
#pragma mark 
#pragma mark Room Options

void gameNetCenter::quickStart(int roomId, int tableId, bool autosit)
{
    m_iQuickStartRoomId = roomId;
    m_iQuickStartTableId= tableId;
    m_bIsQuickStart = true;
    m_bQuickStartAutoSit = autosit;
    enterRoom(roomId);
}

void gameNetCenter::enterRoom(int roomId)
{
    if (roomId<=0 || roomId>5) {
        printf("enterRoom:wrong room id. roomId=%d,which should 0 < roomId < 6.\n",roomId);
        return;
    }
    
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_ENTER_ROOM\", \"params\":{\"roomId\":%d, \"userId\":%d, \"pwd\":\"\", \"gameId\":1}, \"cmdId\":1}\r\n",roomId, g_user.uid);
    
    if (roomId==5) 
        sendMsg(m_cNetBuffer, 8003);
    else 
        sendMsg(m_cNetBuffer);
    
    //m_pHeartBeatTime->resetTimer();
    //m_pHeartBeatMaxTime->resetTimer();
}

/*void gameNetCenter::exitField()
{
    g_roomId=0;//从1开始,0表示当前不在任何房间
    m_pNetLong->closeSocket();
    m_pHeartBeatTime->resetTimer();
    m_pHeartBeatMaxTime->resetTimer();
}*/

void gameNetCenter::refreshRoom()
{
    if (g_roomId<=0 || g_roomId>5) {
        printf("refreshRoom:wrong room id. roomId=%d,which should 0 < roomId < 6.\n", g_roomId);
        return;
    }
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_ROOM_INFO\",\"params\":{\"roomId\":%d,\"userId\":%d, \"pwd\":\"\",\"gameId\":1}, \"cmdId\":1}\r\n",g_roomId, g_user.uid);
    if (g_roomId==5) 
        sendMsg(m_cNetBuffer, 8003);
    else 
        sendMsg(m_cNetBuffer);
}

#pragma mark -
#pragma mark Table Options

void gameNetCenter::enterTable(int tableId, const char* pwd)
{
    g_table_info.tid=tableId;
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_ENTER_TABLE\", \"params\":{\"roomId\":%d, \"userId\":%d, \"pwd\":\"%s\", \"gameId\":1, \"tableId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, pwd, tableId);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::getTableInfo()
{
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_TABLE_INFO\", \"params\":{\"roomId\":%d, \"userId\":%d, \"gameId\":1, \"tableId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::sit(int seatId)
{
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_SIT\", \"params\":{\"roomId\":%d, \"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid, seatId);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::standUp()
{
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_STANDUP\", \"params\":{\"roomId\":%d, \"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid,g_user.location[3]);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::leaveTable()
{
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_LEAVE_TABLE\", \"params\":{\"roomId\":%d, \"userId\":%d, \"tableId\":%d,\"gameId\":1}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::leaveRoom()
{
    sprintf(m_cNetBuffer, "{\"cmd\":\"RL_LEAVE_ROOM\", \"params\":{\"roomId\":%d, \"userId\":%d, \"gameId\":1}, \"cmdId\":1}\r\n",g_roomId, g_user.uid);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::seeCard(int seatId)
{
    sprintf(m_cNetBuffer,"{\"cmd\":\"RL_SEECARD\", \"params\":{\"roomId\":%d,\"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid, seatId);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::betChip(int seatId, int chipNumber)
{
    sprintf(m_cNetBuffer,"{\"cmd\":\"RL_BETCHIP\", \"params\":{\"roomId\":%d,\"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d, \"betchip\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid, seatId, chipNumber);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::pkOne(int seatId, int pkSeat)
{
    sprintf(m_cNetBuffer,"{\"cmd\":\"RL_PK\", \"params\":{\"roomId\":%d,\"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d, \"pkseat\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid, seatId, pkSeat);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::pkAll(int seatId)
{
    sprintf(m_cNetBuffer,"{\"cmd\":\"RL_PKALL\", \"params\":{\"roomId\":%d,\"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid, seatId);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::giveUp(int seatId)
{
    sprintf(m_cNetBuffer,"{\"cmd\":\"RL_GIVEUP\", \"params\":{\"roomId\":%d,\"userId\":%d, \"gameId\":1,\"tableId\":%d, \"seatId\":%d}, \"cmdId\":1}\r\n",g_roomId, g_user.uid, g_table_info.tid, seatId);
    sendMsg(m_cNetBuffer);
}

void gameNetCenter::coin2Chip(int coin, int seatId)
{
    sprintf(m_cNetBuffer,"{\"cmd\":\"RL_C2C\", \"params\":{\"userId\":%d, \"gameId\":1, \"roomId\":%d, \"tableId\":%d, \"seatId\":%d, \"coin\":%d}, \"cmdId\":1}\r\n", g_user.uid, g_roomId, g_table_info.tid, seatId, coin);
    sendMsg(m_cNetBuffer);
}

#pragma mark -
#pragma mark Game Options

//别处调用  直接传入完整的消息
void gameNetCenter::sendMsg(const char* msg, int serverPort)
{
    m_pNetLong->setMsg(msg);
    if (m_bIsFirstConnect) {
        m_bIsFirstConnect=false;
        m_pNetLong->reqConn(SERVERIP, serverPort, NULL);
        return;
    }
    m_pNetLong->netSend(msg);
    m_iCurrentPort = serverPort;
}

void gameNetCenter::closeConn()
{
    printf("CLOSE SOCKET\n");
    m_pNetLong->closeSocket();
    m_bIsFirstConnect=true;
}

#pragma mark -
#pragma mark private methods

void getTableState(cJSON *result)
{
    cJSON *stat;
    stat=cJSON_GetObjectItem(result, "stat");
    g_table_state.nowOp=cJSON_GetObjectItem(stat, "nowop")->valueint;
    g_table_state.currentHand=cJSON_GetObjectItem(stat, "curhand")->valueint;
    g_table_state.baozi=cJSON_GetObjectItem(stat, "baozi")->valueint;
    g_table_state.state=cJSON_GetObjectItem(stat, "state")->valueint;
    g_table_state.banker=cJSON_GetObjectItem(stat, "banker")->valueint;
    g_table_state.chipPool=cJSON_GetObjectItem(stat, "pool")->valueint;
    g_table_state.minBet=cJSON_GetObjectItem(stat, "minbet")->valueint;
}

void gameNetCenter::netLongCallback(const char* msg)
{
    cJSON *read, *error;
    char  *sback, *backcmd;
    
    read=cJSON_Parse(msg);
    
    //server back error json.
    if (read==NULL) {
        printf("server back(%s) error!\n", msg);
        return;
    }
    
    //debug server back json.
    sback = cJSON_Print(read);

    printf("server back:%s\n",sback);
    free(sback);
    
    //get server back cmd.
    if (cJSON_GetObjectItem(read, "cmd")==NULL) {
        cJSON_Delete(read);
        printf("server back error:no cmd.   \n");
        return;
    }
    else {
        backcmd = cJSON_GetObjectItem(read, "cmd")->valuestring;
    }
    
    //return error 
    if ((error=cJSON_GetObjectItem(read, "error"))!=0) {
        printf("server back error info:%s\n", cJSON_GetObjectItem(error, "info")->valuestring);
    }
    else {
        //处理进入房间
        if (strcmp(backcmd, "SL_ROOM_ENTER")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            cJSON *isEnterRoomOk;
            isEnterRoomOk=cJSON_GetObjectItem(result, "ok");
            if (isEnterRoomOk->valueint == 0) {
                printf("enter room fail.\n");
            }
            else {
                g_roomId = cJSON_GetObjectItem(result, "roomId")->valueint;
                refreshRoom();
            }
        }

        //离开房间
        if (strcmp(backcmd, "SL_ROOM_LEAVE")==0) {
            g_roomId= 0;
            closeConn();
        }
        
        //处理刷新房间
        if (strcmp(backcmd, "SL_ROOM_INFO")==0) {
            if (g_table_list.size()>0) {
                for (int i=0; i<g_table_list.size(); i++) {
                    free(g_table_list[i]);
                }
            }
            g_table_list.clear();
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            cJSON *tableList;
            tableList=cJSON_GetObjectItem(result, "tableList");
            int tableNum=cJSON_GetArraySize(tableList);
            if (tableNum>0) {
                for (int i=0; i<tableNum; i++) {
                    cJSON *oneTable=cJSON_GetArrayItem(tableList, i);
                    TABLE_INFO *table_info = (TABLE_INFO*)malloc(sizeof(TABLE_INFO));
                    //单个table信息具有25项
                    //0,table id
                    table_info->tid = cJSON_GetArrayItem(oneTable,0)->valueint; 
                    //1 table name
                    strcpy(table_info->name, cJSON_GetArrayItem(oneTable,1)->valuestring);     
                    //3 password
                    strcpy(table_info->pwd, cJSON_GetArrayItem(oneTable,3)->valuestring); 
                    //4 基数
                    table_info->baseBet = cJSON_GetArrayItem(oneTable,4)->valueint; 
                    //5 单注封顶
                    table_info->maxBet = cJSON_GetArrayItem(oneTable,5)->valueint; 
                    //6 手数封顶
                    table_info->maxHand = cJSON_GetArrayItem(oneTable,6)->valueint; 
                    //7 可比手数
                    table_info->pkHand = cJSON_GetArrayItem(oneTable,7)->valueint; 
                    //8 最少携带金币
                    table_info->minCoin = cJSON_GetArrayItem(oneTable,8)->valueint; 
                    //9 金币筹码兑换比例
                    table_info->coin2Chip = cJSON_GetArrayItem(oneTable,9)->valueint; 
                    //10 最大座位数
                    table_info->maxSeat = cJSON_GetArrayItem(oneTable,10)->valueint; 
                    //11 出牌时间
                    table_info->opTime = cJSON_GetArrayItem(oneTable,11)->valueint; 
                    //12 桌子状态
                    table_info->state = cJSON_GetArrayItem(oneTable,12)->valueint; 
                    int nowPlayers=0;
                    int playingPlayers=0;
                    for (int j=0; j<table_info->maxSeat; j++) {
                        //座位玩家id
                        if(cJSON_GetArrayItem(oneTable,13+2*j)->valueint !=0) {
                            nowPlayers++;
                        }
                        //座位状态,暂时不需要
                        int currentSeatState = cJSON_GetArrayItem(oneTable,14+2*j)->valueint;
                        if (currentSeatState == 10) {
                            playingPlayers += 1;
                        }
                    }
                    table_info->currentSeat=nowPlayers;
                    table_info->playSeat=playingPlayers;
                    
                    g_table_list.push_back(table_info);
                }
                if (m_bIsQuickStart) { //enter table and auto sit
                    printf("before auto enterTable.\n");
                    enterTable(m_iQuickStartTableId, NULL);
                }
                /*if (autoEnterTable) {   //enter table but not sit
                    autoEnterTable=FALSE;
                    enterTable(autoEnterTableId, NULL);
                }*/
            }
            if (g_roomId >= 1 && g_roomId <= 4) {
                refreshMenuLayerNormalRoomTableView();
            } else if (g_roomId == 5) {
                refreshMenuLayerMatchRoomTableView();
            }
        }
        
        //处理进入桌子。客户端发送这个消息，进入指定的桌子，进入成功后，首先进入旁观席
        //自己进入时没用，主要是正在玩着的时候，别人进来会收到此条广播。
        if (strcmp(backcmd, "SL_TABLE_ENTER")==0) {
            printf("..........table enter..........\n");
            //把房间静态信息从g_table_list拷贝到g_table_info中。
            int i;
            for (i=0; i<g_table_list.size(); i++) {
                if (g_table_list[i]->tid==g_table_info.tid) break;
            }
            if (i<g_table_list.size()) {
                memcpy(&g_table_info, g_table_list[i], sizeof(TABLE_INFO));
            }else {
                printf("\n***********\n\nERROR:Can not find table info in g_table_list.\n\n***********\n");
            }
            
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            if (cJSON_GetObjectItem(result, "userId")->valueint == g_user.uid) {
                getTableInfo();
                return;
            }
            USER_INFO *watchMan=(USER_INFO*)malloc(sizeof(USER_INFO));
            watchMan->uid=cJSON_GetObjectItem(result, "userId")->valueint;
            strcpy(watchMan->name, cJSON_GetObjectItem(result,"name")->valuestring);
            watchMan->experience=cJSON_GetObjectItem(result, "exp")->valueint;
            watchMan->coin=cJSON_GetObjectItem(result, "coin")->valueint;
            char *strStart = cJSON_GetObjectItem(result, "winrate")->valuestring;
            char *pos = strchr(cJSON_GetObjectItem(result, "winrate")->valuestring, ',');
            *pos='\0';
            watchMan->winrate[0]=atoi(strStart);
            watchMan->winrate[1]=atoi(pos+1);
            //将watchMan加入观察者列表中...
            
            //通知StatePlay,在界面上显示新加入者的消息....
        }
        
        //取得当前桌子的信息，只有在本地玩家加入游戏时调用一次，因此解析完成后进入StatePlay场景。
        if (strcmp(backcmd, "SL_TABLE_INFO")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            getTableState(result);
            char s[10];
            cJSON *seat, *card;
            for (int i=1; i<=6; i++) {
                memset(s, 0, 10);
                sprintf(s, "seat%d",i);
                seat=cJSON_GetObjectItem(result, s);
                g_seat_info[i-1].uid = cJSON_GetObjectItem(seat, "uid")->valueint;
                g_seat_info[i-1].state = cJSON_GetObjectItem(seat, "state")->valueint;
                g_seat_info[i-1].dark = cJSON_GetObjectItem(seat, "dark")->valueint;
                g_seat_info[i-1].cardScore = cJSON_GetObjectItem(seat, "score")->valueint;
                card=cJSON_GetObjectItem(seat, "card");
                if (cJSON_GetArraySize(card)>0) {
                    //                    strcpy(g_seat[i-1].card, card->valuestring);
                }else {
                    for (int m=0; m<3; m++) {
                        g_seat_info[i-1].cardColor[m]=0;
                        g_seat_info[i-1].cardNum[m]=0;
                    }
                }
                //如果此位置有人
                if (g_seat_info[i-1].uid>0) {
                    g_seat_player_info[i-1].chip=cJSON_GetObjectItem(seat, "chip")->valueint;
                    g_seat_player_info[i-1].coin=cJSON_GetObjectItem(seat, "coin")->valueint;
                    sprintf(g_seat_player_info[i-1].name, "%s",cJSON_GetObjectItem(seat, "name")->valuestring);
                }
            }
            m_pStatePlay->refreshButtonStatus();
            m_pStatePlay->refreshPlayerInfo();
            printf("======Before GoToSence=====\n");
            GEDirector::GetInstance()->setCurrentScene("StatePlay");
            //如果是快速开始，那么这时还处于StateConnect,取到信息后要准备转场。
            if (m_bIsQuickStart && m_bQuickStartAutoSit) {
                for (int i=0; i<6; i++) {
                    if (g_seat_info[i].uid==0) {
                        sit(i+1);
                        return;
                    }
                }
            }
            //自动坐下
            if (strcmp(g_config["autosit"], "1")==0) {
                for (int i=0; i<6; i++) {
                    if (g_seat_info[i].uid==0) {
                        printf("Autosit ok.\n");
                        sit(i+1);
                        break;
                    }
                }
            }
            return;
        }
        
        //处理坐下
        if (strcmp(backcmd, "SL_SIT")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            if (seatId<=0 || seatId>6) {
                return;
            }
            memset(&g_seat_info[seatId-1], 0, sizeof(SEAT_INFO));
            memset(&g_seat_player_info[seatId-1], 0, sizeof(USER_INFO));
            g_seat_info[seatId-1].uid = cJSON_GetObjectItem(result, "userId")->valueint;
            if (g_seat_info[seatId-1].uid==g_user.uid) {
                g_user.location[3]=seatId;
                printf("本地玩家坐下！！！！！\n");
            }
            g_seat_info[seatId-1].state=cJSON_GetObjectItem(result, "seatState")->valueint;
            sprintf(g_seat_player_info[seatId-1].name,"%s",cJSON_GetObjectItem(result, "userName")->valuestring);
            g_seat_player_info[seatId-1].coin=cJSON_GetObjectItem(result, "coin")->valueint;
            g_seat_player_info[seatId-1].chip=cJSON_GetObjectItem(result, "chip")->valueint;
            //从观察者列表中获取
            
            //通知StatePlay更新显示
            m_pStatePlay->refreshPlayerInfo();
            m_pStatePlay->shiftSeat();
        }
        
        //某人站起，但还处于观察状态
        if (strcmp(backcmd, "SL_STANDUP")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            if (g_seat_info[seatId-1].uid==g_user.uid) {
                g_user.location[3]=0;
            }
            memset(&g_seat_info[seatId-1], 0, sizeof(SEAT_INFO));
            memset(&g_seat_player_info[seatId-1], 0, sizeof(USER_INFO));
            
            //通知StatePlay更新显示
            m_pStatePlay->refreshPlayerInfo();
        }
        
        //兑换筹码
        if (strcmp(backcmd, "SL_C2C")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            //check
            int seatId=cJSON_GetObjectItem(result, "seatId")->valueint;
            if (g_seat_info[seatId-1].uid==cJSON_GetObjectItem(result, "userId")->valueint) {
                g_seat_player_info[seatId-1].chip=cJSON_GetObjectItem(result, "chip")->valueint;
                g_seat_player_info[seatId-1].coin=cJSON_GetObjectItem(result, "coin")->valueint;
                if (cJSON_GetObjectItem(result, "userId")->valueint==g_user.uid) {
                    g_user.chip=cJSON_GetObjectItem(result, "chip")->valueint;
                    g_user.coin=cJSON_GetObjectItem(result, "coin")->valueint;
                }
                m_pStatePlay->refreshPlayerInfo();
            }else {
                printf("\nERROR:in SL_C2C callback, g_seat_info[seatId-1]!=userId.\n\n");
            }
        }
        
        //游戏开始
        if (strcmp(backcmd, "SL_GAME_START")==0) {
            cJSON *result, *seatChip, *seats, *cards;//, *banker, *pool;
            result=cJSON_GetObjectItem(read, "result");
            seatChip=cJSON_GetObjectItem(result, "seatChip");
            seats=cJSON_GetObjectItem(result, "seats");
            getTableState(result);

            for (int i=0; i<6; i++) {
                g_seat_info[i].uid=cJSON_GetArrayItem(cJSON_GetArrayItem(seats, i), 0)->valueint;
                if (g_seat_info[i].uid==0) {
                    continue;
                }
                g_seat_player_info[i].chip=cJSON_GetArrayItem(seatChip, i)->valueint;
                g_seat_info[i].state=cJSON_GetArrayItem(cJSON_GetArrayItem(seats, i), 1)->valueint;
                cards=cJSON_GetArrayItem(cJSON_GetArrayItem(seats, i),2);
                for (int j=0; j<3; j++) {
                    g_seat_info[i].cardColor[j]=*(char*)cJSON_GetArrayItem(cJSON_GetArrayItem(cards,j),0)->valuestring;
                    g_seat_info[i].cardNum[j]=cJSON_GetArrayItem(cJSON_GetArrayItem(cards,j),0)->valueint;
                }
                g_seat_info[i].cardScore=cJSON_GetArrayItem(cJSON_GetArrayItem(seats,i), 3)->valueint;
                g_seat_info[i].dark=cJSON_GetArrayItem(cJSON_GetArrayItem(seats,i), 4)->valueint;
            }
            if (g_user.location[3]>0) {
                g_user.chip=g_seat_player_info[g_user.location[3]-1].chip;
            }
            //通知StatePlay开始游戏
            m_pStatePlay->gameStart();
        }
        
        //看牌操作
        if (strcmp(backcmd, "SL_SEE_CARD")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            if (seatId>0) {
                //服务器发回的数据，座位号由1开始，客户端是0-5，需要转换
                g_seat_info[seatId-1].dark = 0;
                m_pStatePlay->seeCard(seatId-1);
            }
        }
        
        //下一家操作
        if (strcmp(backcmd, "SL_NEXT")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            getTableState(result);
            if (g_table_state.nowOp>0) {
                //服务器座位号从1开始，本地是0-5，需要转化。
                if (!(m_pStatePlay->isDealing())) {
                    m_pStatePlay->next();
                }
            }
        }
        
        //下注操作
        if (strcmp(backcmd, "SL_BETCHIP")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            if (seatId>0) {
                int betChip= g_seat_player_info[seatId-1].chip - cJSON_GetObjectItem(result, "chip")->valueint;
                g_seat_player_info[seatId-1].chip = cJSON_GetObjectItem(result, "chip")->valueint;
                g_table_state.chipPool = cJSON_GetObjectItem(result, "pool")->valueint;
                //StatePlay下注
                m_pStatePlay->moveChipsFromPlayerToPool(seatId-1, betChip);
                m_pStatePlay->refreshPlayerInfo();
            }
        }
        
        //与单人PK操作，广播消息，所有玩家都会收到此消息
        if (strcmp(backcmd, "SL_PK")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            //int winseat = cJSON_GetObjectItem(result, "winseat")->valueint;//暂时不用
            int loseseat = cJSON_GetObjectItem(result, "loseseat")->valueint;
            g_seat_player_info[seatId-1].chip = cJSON_GetObjectItem(result, "chip")->valueint;
            g_seat_info[loseseat-1].state=SEAT3CSTAT_LOSE;
            g_table_state.chipPool = cJSON_GetObjectItem(result, "pool")->valueint;
            //更新数据
            m_pStatePlay->refreshPlayerInfo();
            //根据输赢座位号画图
        }
        
        //只剩两个最后玩家时胜者信息，广播消息，所有人都能收到 
        if (strcmp(backcmd, "SL_WIN")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            g_seat_player_info[seatId-1].chip=cJSON_GetObjectItem(result, "chip")->valueint;
            g_user.chip=g_seat_player_info[g_user.location[3]-1].chip;
            m_pStatePlay->refreshPlayerInfo();
            //根据胜利者ID和所得筹码更新显示信息
            m_pStatePlay->win(seatId-1);
            bool isAlreadyStandUp=false;
            //结束后站起
            if (g_noMoreGame && g_user.location[3]>=1 && g_user.location[3]<=6) {
                isAlreadyStandUp=true;
                standUp();
            }
            //自动兑换筹码
            if (!isAlreadyStandUp && g_autoRechangeChip && g_user.location[3]>=1 && g_user.location[3]<=6 
                && g_user.chip<= (0.8*g_table_info.minCoin*g_table_info.coin2Chip)) {
                printf("\n-------------------------\ncoin to chip!!!!!!!!!!!!!!!!!!\n-------------------------\n");
                coin2Chip((g_table_info.minCoin*g_table_info.coin2Chip-g_user.chip)/g_table_info.coin2Chip, g_user.location[3]);
            
            }
            m_pTimerBeforeNewGame->resume();
            g_table_state.state=TABLE3CSTAT_IDLE;
            g_table_state.chipPool=0;
            m_pStatePlay->refreshPlayerInfo();
        }
        
        //PK所有人
        if (strcmp(backcmd, "SL_PKALL")==0) {
            cJSON *result, *res;
            result=cJSON_GetObjectItem(read, "result");
            res=cJSON_GetObjectItem(result, "res");
            int pkNumber=cJSON_GetArraySize(res);
            for (int i=0; i<pkNumber; i++) {
                if (cJSON_GetArrayItem(cJSON_GetArrayItem(res, i), 1)->valueint == 0) {
                    printf("get a '0' in pkAll.\n");
                    g_seat_info[cJSON_GetArrayItem(cJSON_GetArrayItem(res, i), 0)->valueint-1].state=SEAT3CSTAT_LOSE;
                }
            }
            m_pStatePlay->refreshButtonStatus();
            m_pStatePlay->refreshPlayerInfo();
//            for (int i=0; i<cJSON_GetArraySize(res); i++) {
//                //依次顺序画输赢动画，从seatId+1开始画起
//            }
        }
        
        //弃牌
        if (strcmp(backcmd, "SL_GIVEUP")==0) {
            cJSON *result;
            result=cJSON_GetObjectItem(read, "result");
            int seatId = cJSON_GetObjectItem(result, "seatId")->valueint;
            int userId = cJSON_GetObjectItem(result, "userId")->valueint;
            if (seatId>0 && seatId<7) {
                if (g_seat_info[seatId-1].uid!=userId) {
                    printf("\n=============================\n");
                    printf("ERROR:<SL_GIVEUP>,g_seat_info[seatId-1].uid!=userId\n");
                    printf("=============================\n");
                }
                g_seat_info[seatId-1].state=SEAT3CSTAT_GIVEUP;
                for (int i=0; i<3; i++) {
                    g_seat_info[seatId-1].cardColor[i]='\0';
                    g_seat_info[seatId-1].cardNum[i]=0;
                }
                g_seat_info[seatId-1].cardScore=0;
                g_seat_info[seatId-1].dark=1;
            }
            //根据收到的座位号表现出弃牌。动画调用m_pStatePlay->giveUp()函数。
            m_pStatePlay->refreshPlayerInfo();
        }
    }
    cJSON_Delete(read);
}

void gameNetCenter::checkBeforeNewGame(float dt)
{
    if (g_user.location[3]>0 && g_seat_player_info[g_user.location[3]-1].chip<=0) {
        standUp();
    }
    m_pTimerBeforeNewGame->resetTimer();
}

void gameNetCenter::heartBeatComplete(float dt)
{
    if (!m_bIsFirstConnect) {
        //发送心跳信号
        //printf("send heartbeat...\n");
        sprintf(m_cNetBuffer, "{\"cmd\":\"RL_HB\", \"params\":{\"userId\":%d, \"gameId\":1}, \"cmdId\":1}\r\n", g_user.uid);
        sendMsg(m_cNetBuffer, m_iCurrentPort);
    }
    m_pHeartBeatTime->resetTimer();
    m_pHeartBeatTime->resume();
}

void gameNetCenter::heartBeatMax(float dt)
{
   //上时间没有收到服务器对心跳信号的反馈，断开连接，进行错误处理 
}