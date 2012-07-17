/*
 *  ELSSaveData.cpp
 *  GameBox
 *
 *  Created by xing zip on 11-6-16.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "ELSDefine.h"

//分数数据
vector<HSCORE*>		g_mvHS;

//胜率数据
int					g_gamecount[2][4][2];

//勋章数据
int					g_xunzhang[5];
int					g_xunzhang4saverep[5];

//冒险模式相关数据
int					g_unlock_bmp=1;
char				g_bmp[MAX_BMP_COUNT][10][10];
int					g_bmp_time[MAX_BMP_COUNT];
int					g_score_bmp[MAX_BMP_COUNT];
int					g_star_bmp[MAX_BMP_COUNT];
int					g_have_buy_adventure;

//网络购买的道具的数量
int					g_item_num[10];
//剩余金币
int					g_gold;

//回放相关的数据结构
vector<int>			g_mvRepFiles;
int					g_recact_count;
int					g_recact_index;

char                g_receipt[4096];
int                 g_buyitemid, g_buyitemcount, g_buyitemcoin;

FILE*				g_fprand, *g_fptrace;
ELSUSER				g_seats[4];
int                 g_seatId;
int                 g_robot;

//房间列表，第一个元素表示桌子id，第二个元素表示分类（菜鸟，普通，高手），第三个元素表示状态（F：满，I：空闲，R：准备好，P：正在玩)
//最多支持4096个房间
int                 g_tablecount;
unsigned            g_tablelist[4096][3];

int 				g_options[10];  //0－bgm,1-sfx,2-mute,3-rotation,4-dropshadow,5-allmap,6-hardai,7-isFirstGame, 8-showItemHelpAgain, 9-showHoldHelpAgain.

int					g_buyfrom_appstore[2]; //0:商品id   1:购买状态

int					g_reward;

//achievements
int					g_net_achieve=-1;

char				g_robotname[240][32];

const char* achievementArray[54] = {" ",
	"CLASSIC_LEVEL_3",		//1
	"CLASSIC_LEVEL_5",		//2
	"CLASSIC_LEVEL_9",		//3
	"CLASSIC_COMBO_3",		//4
	"CLASSIC_COMBO_5",		//5
	"CLASSIC_COMBO_10",		//6
	"CLASSIC_4LINE_2",		//7
	"CLASSIC_4LINE_3",		//8
	"CLASSIC_4LINE_4",		//9
	"CLASSIC_4LINE_5",		//10
	"ADVENTURE_ALL_STAGE",	//11
	"ADVENTURE_ALL_STAR",	//12
	"ADVENTURE_COMBO_3",	//13
	"ADVENTURE_COMBO_5",	//14
	"ADVENTURE_TIME_75",	//15
	"ADVENTURE_TIME_50",	//16
	"NET_LEVEL_1",			//17
	"NET_LEVEL_3",			//18
	"NET_LEVEL_6",			//19
	"NET_LEVEL_10",			//20
	"NET_LEVEL_15",			//21
	"NET_LEVEL_20",			//22
	"NET_WIN_1",			//23
	"NET_WIN_10",			//24
	"NET_WIN_50",			//25
	"NET_WIN_100",			//26
	"NET_WIN_500",			//27
	"NET_WIN_1000",			//28
	"NET_WIN_RATE_40",		//29
	"NET_WIN_RATE_50",		//30
	"NET_WIN_RATE_70",		//31
	"NET_WIN_RATE_90",		//32
	"NET_COMBO_3",			//33
	"NET_COMBO_5",			//34
	"NET_COMBO_10",			//35
	"NET_4LINE_2",			//36
	"NET_4LINE_3",			//37
	"NET_4LINE_4",			//38
	"NET_4LINE_5",			//39
	"AIHARD_COMBO_3",		//40
	"AIHARD_COMBO_5",		//41
	"AIHARD_COMBO_10",		//42
	"AIHARD_4LINE_2",		//43
	"AIHARD_4LINE_3",		//44
	"AIHARD_4LINE_4",		//45
	"AIHARD_4LINE_5",		//46
	"AINORMAL_COMBO_3",		//47
	"AINORMAL_COMBO_5",		//48
	"AINORMAL_COMBO_10",	//49
	"AINORMAL_4LINE_2",		//50
	"AINORMAL_4LINE_3",		//51
	"AINORMAL_4LINE_4",		//52
	"AINORMAL_4LINE_5"		//53
};

const char* achievementDescribeArray[54] = {" ",
	"Classic Level 6",			//1
	"Classic Level 12",			//2
	"Classic Level 20",			//3
	"Classic 3 Combos",			//4
	"Classic 5 Combos",			//5
	"Classic 10 Combos",		//6
	"Classic 2 Ultimate|Combos",//7
	"Classic 3 Ultimate|Combos",//8
	"Classic 4 Ultimate|Combos",//9
	"Classic 5 Ultimate|Combos",//10
	"Adventure Champion",		//11
	"All Star Champion",		//12
	"Adventure Master",			//13
	"Adventure Guru",			//14
	"Porsche speed",			//15
	"Lightening speed",			//16
	"Lieutenant",				//17
	"Captain",					//18
	"Major",					//19
	"Colonel",					//20
	"Brigadier General",		//21
	"General",					//22
	"1st Grade",				//23
	"Middle School|Graduate",	//24
	"High School|Graduate",		//25
	"Bachelor",					//26
	"Master",					//27
	"PhD",						//28
	"40Percenter",				//29
	"50Percenter",				//30
	"70Percenter",				//31
	"90Percenter",				//32
	"Online 3 Combos",			//33
	"Online 5 Combos",			//34
	"Online 10 Combos",			//35
	"Online 2 Ultimate|Combos",	//36
	"Online 3 Ultimate|Combos",	//37
	"Online 4 Ultimate|Combos",	//38
	"Online 5 Ultimate|Combos",	//39
	"Tough 3 Combos",			//40
	"Tough 5 Combos",			//41
	"Tough 10 Combos",			//42
	"Tough 2 Ultimate|Combos",	//43
	"Tough 3 Ultimate|Combos",	//44
	"Tough 4 Ultimate|Combos",	//45
	"Tough 5 Ultimate|Combos",	//46
	"3 Combos against|Robot",	//47
	"5 Combos against|Robot",	//48
	"10 Combos against|Robot",	//49
	"2 Ultimate Combos|against Robot", //50
	"3 Ultimate Combos|against Robot", //51
	"4 Ultimate Combos|against Robot", //52
	"5 Ultimate Combos|against Robot"	 //53
};

const char* achievementPreDescribeArray[54] = {" ",
	"Target for level 6 in classic mode.",//1
	"Target for level 12 in classic mode.",//2
	"Target for level 20 in classic mode.",//3
	"Make 3 combos to get this badge.",//4
	"Make 5 combos to get this badge.",//5
	"Make 10 combos to get this badge.",//6
	"Clear 4 lines twice in a row. ",//7
	"Clear 4 lines three times in a row. ",//8
	"Clear 4 lines four times in a row. ",//9
	"Clear 4 lines five times in a row. ",//10
	"Finish all the puzzles in adventure mode.",//11
	"Pass all the levels with 3 stars!",//12
	"Make 3 combos to earn this title!",//13
	"Make 5 combos to earn this title!",//14
	"Finish the level within 3 quarters of the given time.",//15
	"Finish the level within half of the given time.",//16
	"Target for level 1 in the online fighting mode.",//17
	"Target for level 3 in the online fighting mode.",//18
	"Target for level 6 in the online fighting mode.",//19
	"Target for level 10 in the online fighting mode.",//20
	"Target for level 15 in the online fighting mode.",//21
	"Target for level 20 in the online fighting mode.",//22
	"Win 1 online game to earn this title.",//23
	"Win 10 online game to earn this title.",//24
	"Win 50 online game to earn this title.",//25
	"Win 100 online game to earn this title.",//26
	"Win 500 online game to earn this title.",//27
	"Win 1000 online game to earn this title.",//28
	"Win 40% of the games to earn this title.",//29
	"Win 50% of the games to earn this title.",//30
	"Win 70% of the games to earn this title.",//31
	"Win 90% of the games to earn this title.",//32
	"Make 3 combos in online games to get this badge.",//33
	"Make 5 combos in online games to get this badge.",//34
	"Make 10 combos in online games to get this badge.",//35
	"Clear 4 lines twice in a row in online games.",//36
	"Clear 4 lines three times in a row in online games.",//37
	"Clear 4 lines four times in a row in online games.",//38
	"Clear 4 lines five times in a row in online games.",//39
	"Make 3 combos in games with the advanced robot",//40
	"Make 5 combos in games with the advanced robot",//41
	"Make 10 combos in games with the advanced robot",//42
	"Clear 4 lines twice in a row in games with the advanced robot.",//43
	"Clear 4 lines three times in a row in games with the advanced robot.",//44
	"Clear 4 lines four times in a row in games with the advanced robot.",//45
	"Clear 4 lines five times in a row in games with the advanced robot.",//46
	"Make 3 combos in games with the robot.",//47
	"Make 5 combos in games with the  robot",//48
	"Make 10 combos in games with the  robot",//49
	"Clear 4 lines twice in a row in games with the  robot.",//50
	"Clear 4 lines three times in a row in games with the  robot.",//51
	"Clear 4 lines four times in a row in games with the  robot.",//52
	"Clear 4 lines five times in a row in games with the robot."//53
};

const char* achievementEarnedDescribeArray[54] = {" ",
	"You have completed level 3 in the classic mode. Great job!",
	"You have completed level 5 in the classic mode. Keep it up!",
	"You have completed level 5 in the classic mode. You are a champion!",
	"Great job! You just made 3 combos!",
	"Great job! You just made 5 combos!",
	"Great job! You just made 10 combos!",
	"Cool! You just cleared 4 lines for twice in a row!",
	"Good job! You just cleared 4 lines for 3 times in a row!",
	"Awesome! You just cleared 4 lines for 4 times in a row!",
	"Amazing! You just cleared 4 lines for 5 times in a row!",
	"Awesome! You finished all the levels in the adventure mode! You are a genius!",
	"You are amazing! You finished all the levels in the adventure mode with 3 stars. Unbelievable!",
	"Good job! You just made 3 combos in the adventure mode! Keep it up!",
	"Great job! You just made 5 combos in the adventure mode! ",
	"You are fast! You just finish this level using less than 3 quarter of the given time!",
	"You finish the leve using less than half of the given time. Can you be even faster? ",
	"Good job, you are Lieuteant in this world!",
	"Good job, you are promoted Captain in this world!",
	"Good job, you are Major in this world!",
	"Good job, you are Colonel in this world!",
	"Good job, you are Brigadier General in this world!",
	"Good job, you are General now!",
	"Congratulations on winning your first game! Keep it up!",
	"Congratulations! You have won 10 games so far! Go go go!",
	"Congratulations! You have won 50 games so far! What an achievement!",
	"Congratulations! You have won 100 games so far! What a milestone!",
	"Congratulations! You have won 500 games so far! You are now a world class player!",
	"Congratulations! You have won 1000 games so far! Nobody can stop you now.",
	"Nice You won 40% of the games that you have played!",
	"Great Job! You won 50% of the games that you have played!",
	"Amazing You won 70% of the games that you have played!",
	"Awesome! You won 90% of the games that you have played!",
	"Great job! You just made 3 combos in the online game!",
	"Great job! You just made 5 combos in the online game!",
	"Great job! You just made 10 combos in the online game!",
	"Cool! You just cleared 4 lines for twice in a row!",
	"Good job! You just cleared 4 lines for 3 times in a row in an online game!",
	"Awesome! You just cleared 4 lines for 4 times in a row  in an online game!",
	"Amazing! You just cleared 4 lines for 5 times in a row in an online game!",
	"Great job! You just made 3 combos in the game with the advanced robot!",
	"Great job! You just made 5 combos in the game with the advanced robot!",
	"Great job! You just made 10 combos in the game with the advanced robot!",
	"Cool! You just cleared 4 lines for twice in a row!",
	"Good job! You just cleared 4 lines for 3 times in the game against the advanced robot!",
	"Awesome! You just cleared 4 lines for 4 timesin the game against the advanced robot!",
	"Amazing! You just cleared 4 lines for 5 times in the game against the advanced robot!",
	"Great job! You just made 3 combos in the game against the advanced robot!",
	"Great job! You just made 5 combos in the game against the advanced robot!",
	"Great job! You just made 10 combos in the game against the advanced robot!",
	"Cool! You just cleared 4 lines for twice in a row in the game against the robot!",
	"Good job! You just cleared 4 lines for 3 times in the game against the robot!",
	"Awesome! You just cleared 4 lines for 4 timesin the game against the robot!",
	"Amazing! You just cleared 4 lines for 5 times in the game against the  robot!"	
};