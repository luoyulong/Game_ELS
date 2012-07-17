/*
 *  saveData.h
 *  GameBox
 *
 *  Created by xing zip on 11-6-16.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "dataDefine.h"
#define NET_CONNECT_BUFFER    1024
using namespace std;

extern char                             g_server_ip[16];        //GameServer IP 
//短连接端口号
extern int                              g_long_connect[10];     //长连接端口号
extern vector<TABLE_INFO*>              g_table_list;           //桌子列表
extern hash_map<const char *, char *>   g_config;               //配置项，对应g_config.txt
extern USER_INFO                        g_user;                 //玩家个人信息
extern REWARD_INFO                      g_rewardInfo;           //领取奖励信息
extern ISREWARD_INFO                    g_isReward;             //领取奖励数量
extern int                              g_roomId;               //玩家选择进入的房间
extern TABLE_INFO                       g_table_info;           //玩家进入桌子的信息,只有一份,进入时从g_table_list中拷贝
extern TABLE_STATE                      g_table_state;          //玩家进入的桌子的状态,只有一份
extern SEAT_INFO                        g_seat_info[6];         //6个座位的信息
extern USER_INFO                        g_seat_player_info[6];
extern vector<USER_INFO*>               g_friend_list;          //玩家好友信息
extern MESSAGE_INFO                     g_message;              //个人或系统消息
extern bool                             g_feedback;             //反馈消息是否成功
extern COIN_STORE                       g_coin_store;           //金币商城

extern bool                             g_noMoreGame;
extern bool                             g_autoRechangeChip;
extern bool                             g_followToEnd;

//确定的五个座位的位置，这些值不会变
extern int   g_seat_init_position[6][2];
extern int   g_banker_init_position[6][2];
extern int   g_cards_init_position[6][2];

//游戏中座位的位置，当玩家点坐下时，他的座位会转到正下方，下面值会变
extern int   g_seat_position[6][2];
extern int   g_banker_position[6][2];
extern int   g_cards_position[6][2];

//用于座位旋转的临时变量
extern int    tmp_seat_position[6][2];
extern int    tmp_banker_position[6][2];
extern int    tmp_cards_position[6][2];
