/*
 *  ELSDefine.h
 *  GameBox
 *
 *  Created by xing zip on 11-2-17.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _ELS_DEFINE_H_
#define _ELS_DEFINE_H_

#include <ext/hash_map>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <algorithm>

using namespace __gnu_cxx;

#import  <CoreFoundation/CoreFoundation.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#import  <CoreFoundation/CFSocket.h> 
#include <sys/socket.h> 
#include <unistd.h>

typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef short		   s16;
typedef unsigned int   u32;

//是否自动下落的选项
#define ELS_AUTO	   1

//定义行数列数
#define HENG           10 
#define ZONG           20 
#define GRIDSIZE       (HENG+4)*(ZONG+2)*sizeof(u8)

//落到底后，达到稳定状态的延时
#define WENDING        25

//为了保证AB两人的方块序列完全一致，事先生成好500个方块序列，500块后轮回取块
#define MAXBLKQUEUE    500


//#define SET_CLEAR_STAGE			120
//#define REND_CLEAR_STAGE		20
//#define MAX_XUNZHANG_STAGE		120
//#define MAX_UNLOCK_STAGE		120
//#define MAX_CLING_STAGE			60

#define SET_CLEAR_STAGE		120
#define SET_LEVELUP_STAGE   120
#define REND_CLEAR_STAGE	20
#define MAX_XUNZHANG_STAGE	90
#define MAX_UNLOCK_STAGE	12
#define MAX_CLING_STAGE		60


#define MAX_ITEM				6
#define MAX_CLEAR_ITEM_STAGE	60

#define  KEY_PRESSED  100
#define  KEY_DOWN     1
#define  KEY_UP       0

#define  TIMEFORSCOREBOARD   2.0f
#define  TIMEFORASCOREBOARD  15.0f

//3种模式，WLAN尚未支持
typedef enum _els_mode {
	ELS_MODE_SINGLE,
	ELS_MODE_AI,
	ELS_MODE_NET,
	ELS_MODE_REPLAY
} EMODE;

//用于MoveBlk的参数
typedef enum _mdir {
	TURN  = 0,  //旋转
	DOWN  = 1,  //下落
	LEFT  = 2,  //左移
	RIGHT = 3,  //右移
	SET   = 4,  //不移动，仅填充Grid
	CLEAR = 5,  //不移动，在Grid中清除
	DDOWN = 6   //直落，不会留滑动时间
} MDIR;

//用于MoveBlk的返回值
typedef enum _mstat {
	NORMAL        = 0,  //移动正常
	READY_BOTTOM  = 1,  //到达最底
	REACH_BORDER  = 2,  //到达两边
	REACH_BOTTOM  = 3
} MSTAT;

//全局网格,关键变量，左.右.下.留边用于限制方块不越界
typedef struct _gstat {	
	u8      grid[ZONG+2][HENG+4], col_top[HENG], col_hole[HENG], grect_stage, shield_remain_time, face_remain_time,
			achv_count, achv_list[10];
	
			//col_top 每列总高块的高度， col_hole每列空洞的权重和，AI用。
			//shield_remain_time和face_remain_time分别是盾牌和遮挡效果的剩余时间
	s8      combo, max_combo,//当前连击数，最大连击数
			cur_block, next_block, save_block, block_change_time, show_hold_time,//换块时和hold时用于标记next里面几个块的微小移动
			cur_x, cur_y, cur_z, top_line,
			tdx, tdy,//记录将要落下虚影的坐标
			full_rows_count, fullrows[20],//纪录填满的行，最多20行(使用压缩机道具时，fullrows可能大于4行，正常情况下最多4个满行）
			cling_count, cling_blocks[5][2], cling_ddown[2];//纪录粘住块的个数，以及其x，y坐标, 粘住烟尘效果图片应该显示的坐标......
	
	u16     lines, level, block_index, item_trigger, xunzhang_trigger;
	unsigned int	score;
	u16     tmpstar;//冒险模式中暂存的每局所得的星星
	u16     attack[2];//只有当其他三方都没有消行动画时执行攻击，所以可能出现上次攻击未执行，本次攻击又产生的情况，最多留6个缓冲，记录０：行数，１：seed
	
	s16     ready_wending;
	s16		clear_stage, itemuse_stage, xunzhang_stage, unlock_stage, cling_stage, levelup_stage;
	
	bool    safe_mode, save_lock, game_over, active;
} GSTAT;

//此数据结构用于存放道具收集及使用时的起止位置等信息，均被用于vector itemFly中。
typedef struct	_itemmove {
	float startx;
	float starty;
	float endx;
	float endy;
	int   itemtype;
	int   item_move_stage;
}ITEMMOVE;

//分数相关的数据结构
typedef struct _hscore {
	char	playerName[20];
	int		score;
	int		hang;
	int		combo;
	bool    is_current;
	char    date[32];
} HSCORE;

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#define MAX_REP_COUNT 8
#define MAX_BMP_COUNT 49

typedef struct _st_rec {
	char idx; 
	char act[16]; 
	int  stage;
	int  blkindex;
} RECACT;


//不同级别对应的下落时间
const static float DOWN_TIME[20]={1.0, 0.95f, 0.9f, 0.85f, 0.8f, 0.75f, 0.7f, 0.65f, 0.6f, 0.55f,
									0.5f, 0.45f, 0.4f, 0.35f, 0.3f, 0.25f, 0.2f, 0.15f, 0.1f, 0.05f};

const static float DOWN_TIME_NET[20]={1.0f, 0.7f, 0.4f, 0.25f, 0.1f, 0.05f, 0.03f, 0.02f, 0.02f, 0.02f,
										0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f};

//三个AI难度
const static float AI_SPEED[4]={0.5f, 0.35f, 0.15f};

const static float HEARTBEAT_TIME=10.0f;

//调整方块缩略图位置
const static float blkadj[9][2]={{0,0.5},{0,0},{0,0},{0,0.5},{0,0.5},{-0.5,0.5},{0,0.5},{0,0.5},{0,0.5}};
//旋转态数
const s8 block_zcount[9] = {2, 2, 4, 4, 4, 2, 2, 4, 4};
//定义8种方块4种旋转的4*4点阵
const static u8 blkdat[9][4][16] = 
{
	{
		{
			0,0,0,0, 
			0,1,1,0, 
			0,0,0,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,1,0,0, 
			0,1,0,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,1,1,0, 
			0,0,0,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,1,0,0, 
			0,1,0,0, 
			0,0,0,0
		}
	},
	
	{
		{
			0,0,0,0, 
			0,0,2,0, 
			0,2,0,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,2,0,0, 
			0,0,2,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,0,2,0, 
			0,2,0,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,2,0,0, 
			0,0,2,0, 
			0,0,0,0
		}
	},
	
	{
		{
			0,0,0,0, 
			0,3,0,0, 
			0,3,3,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,0,3,0, 
			0,3,3,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,3,3,0, 
			0,0,3,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,3,3,0, 
			0,3,0,0, 
			0,0,0,0
		}
	},
	
	{
		{
			0,4,0,0, 
			0,0,4,0, 
			0,0,4,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,0,0,4, 
			0,4,4,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,4,0,0, 
			0,4,0,0, 
			0,0,4,0
		},
		{
			0,0,0,0, 
			0,4,4,0, 
			4,0,0,0, 
			0,0,0,0
		}
	},
	
	{
		{
			0,0,5,0, 
			0,5,0,0, 
			0,5,0,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,5,5,0, 
			0,0,0,5, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,0,5,0, 
			0,0,5,0, 
			0,5,0,0
		},
		{
			0,0,0,0, 
			5,0,0,0, 
			0,5,5,0, 
			0,0,0,0
		}
	},
	
	{
		{
			0,0,0,0, 
			0,6,6,6, 
			0,0,0,0, 
			0,0,0,0
		},
		{
			0,0,6,0, 
			0,0,6,0, 
			0,0,6,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,6,6,6, 
			0,0,0,0, 
			0,0,0,0
		},
		{
			0,0,6,0, 
			0,0,6,0, 
			0,0,6,0, 
			0,0,0,0
		}
	},
	
	{
		{
			0,0,0,0, 
			7,7,7,7, 
			0,0,0,0, 
			0,0,0,0
		},
		{
			0,0,7,0, 
			0,0,7,0, 
			0,0,7,0, 
			0,0,7,0
		},
		{
			0,0,0,0, 
			7,7,7,7, 
			0,0,0,0, 
			0,0,0,0
		},
		{
			0,0,7,0, 
			0,0,7,0, 
			0,0,7,0, 
			0,0,7,0
		}
	},
	
	{
		{
			0,8,0,0, 
			0,8,8,0, 
			0,8,8,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,8,8,8, 
			0,8,8,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,8,8,0, 
			0,8,8,0, 
			0,0,8,0
		},
		{
			0,0,0,0, 
			0,8,8,0, 
			8,8,8,0, 
			0,0,0,0
		}
	},

	{
		{
			0,0,9,0, 
			0,9,9,0, 
			0,9,9,0, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,9,9,0, 
			0,9,9,9, 
			0,0,0,0
		},
		{
			0,0,0,0, 
			0,9,9,0, 
			0,9,9,0, 
			0,9,0,0
		},
		{
			0,0,0,0, 
			9,9,9,0, 
			0,9,9,0, 
			0,0,0,0
		}
	},
};

enum _netSates
{
	NET_STATE_INIT,
	NET_STATE_WAITLOGIN,
	NET_STATE_LOGINOK,
	NET_STATE_WAITENTERROOM,
	NET_STATE_ENTERROOMOK,
	NET_STATE_WAITREADY,
	NET_STATE_READYOK,
	NET_STATE_PLAYING,
	NET_STATE_SELFOVER,
	NET_STATE_GAMEOVER,
	NET_STATE_ERROR
};

const char _netSatesStr[11][32]=
{
	"NET_STATE_INIT",
	"NET_STATE_WAITLOGIN",
	"NET_STATE_LOGINOK",
	"NET_STATE_WAITENTERROOM",
	"NET_STATE_ENTERROOMOK",
	"NET_STATE_WAITREADY",
	"NET_STATE_READYOK",
	"NET_STATE_PLAYING",
	"NET_STATE_SELFOVER",
	"NET_STATE_GAMEOVER",
	"NET_STATE_ERROR"
};


typedef struct _els_user {
	char name[128];
	int  userid;
	int  state;
	int  rank,level,wincount,totalcount,exp,stage_exp;
	int  isrobot;
} ELSUSER;

#endif