/*
 *  GEStateConnect.cpp
 *  Dice0
 *
 *  Created by F.K. on 12-4-26.
 *  Copyright 2012 __GameSnow_. All rights reserved.
 *
 */
#include "GameStateShortConnect.h"
#include "GlobalData.h"
#include "gameNetCenter.h"
#include "AddonWrapper.h"
#include "warningMessageWrapper.h"
#include "LoginWrapper.h"
GameStateShortConnect* GameStateShortConnect::m_pSelf=0;

GameStateShortConnect* GameStateShortConnect::GetInstance()
{
    if (m_pSelf==0) 
        m_pSelf = new GameStateShortConnect();
    return m_pSelf;
}

GameStateShortConnect::GameStateShortConnect()
{
    m_pShortNet = GENet::netWithTarget(this, net_selector(GameStateShortConnect::netShortCallBack));
}

GameStateShortConnect::~GameStateShortConnect()
{
    if (m_pShortNet) 
        delete m_pShortNet;
}

void GameStateShortConnect::sendMsg(const char *msg, GENet *p_Net)
{
    cJSON *read;
    read=cJSON_Parse(msg);
    if (read==0) {
        printf("sendMsg, json data format error!\n");
    }
    else {
        p_Net->setMsg(msg);
        p_Net->reqConn(SERVERIP, SHORTPORT, NULL);
    }
}

void GameStateShortConnect::quickStartReq(const char *deviceId)
{
    printf("Quick Start Command!\n");
    
    memset(m_cNetRequest, 0, NET_CONNECT_BUFFER);
    sprintf(m_cNetRequest, "{\"cmd\":\"RS_QUICK_START\",\"params\":{\"userId\":\"%s\",\"gameId\":1}, \"cmdId\":1}\r\n", deviceId);
    sendMsg(m_cNetRequest, m_pShortNet);
}

void GameStateShortConnect::logInFromSNS(const char* userType, const char* usrId, const char* nick_name, const char* picurl)
{
    printf("LogIn From %s!\n", userType);
    
    memset(m_cNetRequest, 0, NET_CONNECT_BUFFER);
    sprintf(m_cNetRequest, "{\"cmd\":\"RS_LOGIN\", \"params\":{ \"snsId\":\"%s:%s\",\"name\":\"%s\",\"picurl\":\"%s\",\"gameId\":1,\"friends\":[\"\", \"\"], \"version\":\"1.0\"},\"cmdId\":1}\r\n", userType, usrId, nick_name, picurl);
    
    sendMsg(m_cNetRequest, m_pShortNet);
}

void GameStateShortConnect::logInFromTourist(const char* usrId, const char* nick_name)
{
    printf("LogIn As a Toursit !\n");
    
    memset(m_cNetRequest, 0, NET_CONNECT_BUFFER);
    sprintf(m_cNetRequest, "{\"cmd\":\"RS_LOGIN\", \"params\":{ \"snsId\":\"%s\",\"picurl\":\"\",\"name\":\"%s\",\"gameId\":1,\"friends\":[\"\", \"\"], \"version\":\"1.0\"},\"cmdId\":1}\r\n", usrId, nick_name);
    sendMsg(m_cNetRequest, m_pShortNet);
}

void GameStateShortConnect::acts(){
    //待定
}

void GameStateShortConnect::store(){
    //None
}

void GameStateShortConnect::feedback(const char *msg){
    memset(m_cNetRequest, 0, NET_CONNECT_BUFFER);
    sprintf(m_cNetRequest, "{\"cmd\":\"RS_FEEDBACK\", \"params\":{ \"gameId\":1,\"userId\":%d, \"msg\":%s},\"cmdId\":1}\r\n",g_user.uid, msg);
    sendMsg(m_cNetRequest, m_pShortNet);
}

/*
 *  处理服务器返回的短连接消息消息
 */
void GameStateShortConnect::netShortCallBack(const char* msg)
{
    printf("msg=%s, msglen=%d\n", msg, (int)strlen(msg));
    cJSON *read;
    read=cJSON_Parse(msg);
    
    printf(" +++++++++++++++++ 短连接返回信息类型: %s  +++++++++++++++++\n", cJSON_GetObjectItem(read, "cmd")->valuestring);
    printf("server back msg!!\n%s", cJSON_Print(read));
    
    if(read == 0)
    {
        printf("json format error!!\n");
        return;
    }
    if (cJSON_GetObjectItem(read, "cmd")==NULL) {
        //信息错误
        printf("no cmd.\n");
        return;
    }
    if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring,"SS_LOGIN")==0) {
        printf("\n****************\nlog in ok.\n****************\n");
        
        cJSON *result, *udata, *gdata, *reward, *items;
        result=cJSON_GetObjectItem(read, "result");
        udata=cJSON_GetObjectItem(result, "udata");
        gdata=cJSON_GetObjectItem(result, "gdata");
        items=cJSON_GetObjectItem(result, "items");
        reward=cJSON_GetObjectItem(result, "reward");
        
        g_user.uid=atoi(cJSON_GetArrayItem(udata, 0)->valuestring);
        g_user.coin=cJSON_GetArrayItem(udata, 1)->valueint;
        snprintf(g_user.picture_url, 256, "%s", cJSON_GetArrayItem(udata, 2)->valuestring);
        snprintf(g_user.passwd, 256, "%s", cJSON_GetArrayItem(udata, 3)->valuestring);
        g_user.state = cJSON_GetArrayItem(udata, 4)->valueint;
        
        snprintf(g_user.lastlogin, 64, "%s", cJSON_GetArrayItem(gdata, 0)->valuestring);
        g_user.nslogin=cJSON_GetArrayItem(gdata, 1)->valueint;
        char *cardColorNum=cJSON_GetArrayItem(gdata, 2)->valuestring;
        printf("====%s====\n", cardColorNum);
        if (cardColorNum[0]=='\0') {
            for (int i=0; i<3; i++) {
                g_user.maxcard.color[i]='\0';
                g_user.maxcard.number[i]=0;
            }
        }
        else {
            for (int i=0; i<3; i++) {
                g_user.maxcard.color[i]=*cardColorNum;
                g_user.maxcard.number[i]=*(cardColorNum+1);
                cardColorNum=strchr(cardColorNum, ',');
            }
        }
 
        g_user.maxscore=cJSON_GetArrayItem(gdata, 3)->valueint;
        g_user.maxwinchip=cJSON_GetArrayItem(gdata, 4)->valueint;
        g_user.chip=cJSON_GetArrayItem(gdata, 5)->valueint;
        g_user.experience=cJSON_GetArrayItem(gdata, 6)->valuedouble;
        g_user.level=cJSON_GetArrayItem(gdata, 7)->valueint;

        char *strStart = cJSON_GetArrayItem(gdata, 8)->valuestring;
        char *pos = strchr(cJSON_GetArrayItem(gdata, 8)->valuestring, ',');
        *pos='\0';
        g_user.winrate[0]=atoi(strStart);  //cJSON_GetArrayItem(gdata, 3)->child->valueint;
        g_user.winrate[1]=atoi(pos+1);
        if (reward) {
            for (int i=0; i<6; i++) 
                g_user.reward[i]=cJSON_GetArrayItem(reward, i)->valueint;
        }
        else {
            for (int i=0; i<6; i++) 
                g_user.reward[i]=0;
        }
        
        //Deal with items data
        g_user.items_count=cJSON_GetArraySize(items);
        for (int i=0; i<g_user.items_count; i++) {
            g_user.items[i].itemid=cJSON_GetArrayItem(cJSON_GetArrayItem(items, i), 0)->valueint;
            g_user.items[i].senderid=cJSON_GetArrayItem(cJSON_GetArrayItem(items, i), 1)->valueint;
            g_user.items[i].starttime=cJSON_GetArrayItem(cJSON_GetArrayItem(items, i), 2)->valueint;
            g_user.items[i].count=cJSON_GetArrayItem(cJSON_GetArrayItem(items, i), 3)->valueint;
            g_user.items[i].state=cJSON_GetArrayItem(cJSON_GetArrayItem(items, i), 4)->valueint;
        }
        
        GEDirector::GetInstance()->setCurrentScene("StateMainMenu");
        
        //Test
        g_user.nslogin=2;
        g_user.reward[1]=100;
        
        if (g_user.nslogin>0 && g_user.reward[g_user.nslogin-1]!=0) {
            loginLayerRewardReloadData();
            loginLayerRewardShow();
        }
    }
    
    if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring,"SS_QUICK_START")==0) {
        printf("\n****************\n game quick start ok.\n****************\n");
        
        cJSON *result;
        result=cJSON_GetObjectItem(read, "result");
        
        char *pos;
        char *strStart=cJSON_GetObjectItem(result, "loc")->valuestring;
        
        for (int i=0; i<3; i++) {
            
            pos=strchr(strStart, '.');
            if (pos != NULL) {
                *pos='\0';
                g_user.location[i]=atoi(strStart);
                strStart=pos+1;
            }
            else{
                g_table_info.tid=atoi(strStart);
                g_user.location[i]=atoi(strStart);
            }
        }
        g_user.location[3]=0;
        gameNetCenter::GetInstance()->quickStart(g_user.location[1], g_user.location[2]);
    }

        
    if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring, "SS_STORE")) {
        //暂时没有该消息
    }
    
    if (strcmp(cJSON_GetObjectItem(read, "cmd")->valuestring, "SS_FEEDBACK")==0) {
        char *feedback;
        feedback=cJSON_GetObjectItem(cJSON_GetObjectItem(read, "result"), "ret")->valuestring;
        if (strcmp(feedback, "ok")==0) {
            g_feedback=TRUE;
        }
    }
    //m_pShortNet->closeSocket();
}






















