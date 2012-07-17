//
//  GameLayer_Net.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameLayerPlayELS.h"


static RECACT g_netact[64];
static UInt8  __netbuf[2048];
static int    g_netact_count, g_netact_idx, g_netbuf_len, g_net_send, g_net_recv;

_netSates    g_net_state;

char g_short_conn[32] = "short connect";
char g_long_conn[32]  = "long connect";

CFSocketNativeHandle g_long_sock, g_short_sock;

bool g_onlyLogin, g_reqBuyCoin, g_reqBuyItem, g_reqStoreInfo;

//最多20个好友，4个元素分别存储roomid, tableid, table player count
char g_online_friends_name[20][64];
int  g_online_friends_info[20][3];
int  g_online_friends_count;

char g_userName[256];
char g_userSnsId[64];
char g_sfriends[512];
int  g_userId=12;
//int  g_roomId;
int  g_tableId;
int  netSeed;

CFSocketContext sCTX = { 0, g_short_conn, NULL, NULL, NULL };
CFSocketContext lCTX = { 0, g_long_conn, NULL, NULL, NULL };

CFSocketContext theContext;
CFReadStreamRef readStream; 
CFWriteStreamRef writeStream; 

int GameLayerPlayELS::GetIdxBySeatId(int seat)
{
	return (seat+4-g_seatId)%4;
}


int GameLayerPlayELS::GetSeatIdByidx(int idx)
{
	return (g_seatId-1+idx)%4+1;
}

bool GameLayerPlayELS::isRobotGame()
{
	if(g_robot)
		return true;
	return false;
}




void GameLayerPlayELS::GetTableString(char *buf)
{
	//sprintf(buf, "Room%d-%d", g_roomId, g_tableId);
    sprintf(buf, "Room%d-%d", 10, g_tableId);

	return;
}


void GameLayerPlayELS::SendMaxCombo(int combonum, int comboidx)
{
	char tmsg[256];
	int combo_userid=0;
	if (isRobotGame()) {
		combo_userid=g_seats[0].userid;
	}
	else {
		if(comboidx!=0)
			return;
		combo_userid=g_seats[GetSeatIdByidx(comboidx)-1].userid;
	}
    
	/*sprintf(tmsg, "{\"cmd\":\"MAX_COMBO\",\"gameName\":\"tetris\", \"params\":{\"roomId\": %d, \"tableId\": %d, \"userId\": %d, \"comboId\": %d, \"comboCount\": %d}, \"cmdId\":1}\r\n", 
			g_roomId, g_tableId, g_userId, combo_userid, combonum);
	netSend(tmsg);*/
}