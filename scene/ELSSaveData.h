/*
 *  ELSSaveData.h
 *  GameBox
 *
 *  Created by xing zip on 11-6-16.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

//分数数据
extern vector<HSCORE*>	g_mvHS;

extern char             g_receipt[4096];
extern int              g_buyitemid, g_buyitemcount, g_buyitemcoin;

//胜率数据
extern int				g_gamecount[2][4][2];

//勋章数据
extern int					g_xunzhang[5];
extern int				g_xunzhang4saverep[5];

//冒险模式相关数据
extern int				g_unlock_bmp;
extern char				g_bmp[MAX_BMP_COUNT][10][10];
extern int				g_bmp_time[MAX_BMP_COUNT];
extern int				g_score_bmp[MAX_BMP_COUNT];
extern int				g_star_bmp[MAX_BMP_COUNT];
extern int				g_have_buy_adventure;//是否已购买完整48个关卡,0/1.

//网络购买的道具的数量
extern int				g_item_num[10];
//剩余的金币
extern int				g_gold;

//回放相关的数据结构
extern vector<int>		g_mvRepFiles;
extern int				g_recact_count, g_recact_index;


extern FILE*			g_fprand, *g_fptrace;
extern ELSUSER			g_seats[4];
extern int              g_seatId;
extern int              g_robot;

extern int              g_tablecount;
extern unsigned         g_tablelist[4096][3];

extern int				g_options[10];  //0－bgm,1-sfx,2-mute,3-rotation,4-dropshadow,5-allmap,6-hardai,7-isFirstGame, 8-showItemHelpAgain, 9-showHoldHelpAgain.

#define		PRODUCT_100coin		0
#define		PRODUCT_500coin		1
#define		PRODUCT_1000coin	2
#define		PRODUCT_2500coin	3
#define		PRODUCT_MMAPS		4
#define		PRODUCT_HARDAI		5

#define		BUYSTATE_INIT		0
#define		BUYSTATE_PROCESSING	1
#define		BUYSTATE_OK			2
#define		BUYSTATE_FAIL		3

extern int				g_buyfrom_appstore[2]; //0:商品id   1:购买状态
extern int				g_reward;

//achievements
extern int				g_net_achieve;
extern char				g_robotname[240][32];

extern const char* achievementArray[54];
extern const char* achievementDescribeArray[54];
extern const char* achievementPreDescribeArray[54];
extern const char* achievementEarnedDescribeArray[54];
