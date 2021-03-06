/*
 *  saveData.cpp
 *  GameBox
 *
 *  Created by xing zip on 11-6-16.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "GlobalData.h"
#include <string>
#include <iostream>
#include <ext/hash_map>

using namespace std;


hash_map<const char *, char *>      g_config;           //配置信息
vector<TABLE_INFO*>                 g_table_list;       //桌子列表
USER_INFO                           g_user;             //玩家个人信息
REWARD_INFO                         g_rewardInfo;       //领取奖励信息
ISREWARD_INFO                       g_isReward;         //领取奖励数量
int                                 g_roomId;           //玩家选择进入的房间
//int                                 g_seatId;
TABLE_INFO                          g_table_info;       //玩家进入桌子的信息,只有一份,进入时从g_table_list中拷贝
TABLE_STATE                         g_table_state;      //玩家进入的桌子的状态
SEAT_INFO                           g_seat_info[6];     //6个座位的信息
USER_INFO                           g_seat_player_info[6];
vector<USER_INFO*>                  g_friend_list;      //玩家好友列表
MESSAGE_INFO                        g_message;          //个人或系统消息
bool                                g_feedback;         //反馈消息是否成功
COIN_STORE                          g_coin_store;       //金币商城

bool                                g_noMoreGame;
bool                                g_autoRechangeChip;
bool                                g_followToEnd;

int   g_seat_init_position[6][2] = 
{
    {320,460},
    {160,320},
    {320,180},
    {640,180},
    {800,320},
    {640,460},
};
int   g_banker_init_position[6][2]=
{
    {400,460},
    {240,320},
    {400,180},
    {560,180},
    {720,320},
    {560,460}
};
int   g_cards_init_position[6][2]=
{
    {400,460},
    {240,320},
    {400,180},
    {560,180},
    {720,320},
    {560,460}
};
int   g_seat_position[6][2];
int   g_banker_position[6][2];
int   g_cards_position[6][2];


int   tmp_seat_position[6][2];
int   tmp_banker_position[6][2];
int   tmp_cards_position[6][2];
