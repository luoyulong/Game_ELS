#ifndef _DICE_DEFINE_H_
#define _DICE_DEFINE_H_

#include <ext/hash_map>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <algorithm>

using namespace __gnu_cxx;

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <unistd.h>

//定义桌子状态信息
#define TABLE3CSTAT_IDLE 10
#define TABLE3CSTAT_PLAYING 20
//定义每个座位状态信息
#define SEAT3CSTAT_PLAYING 10
#define SEAT3CSTAT_GIVEUP 20
#define SEAT3CSTAT_LOSE 30
#define SEAT3CSTAT_WAIT 40

//桌子信息，在tableList中 保存到一个链表中
typedef struct _table_info {
    int     tid;
    char    name[64];
    char    pwd[16];
    int     baseBet;    //基数
    int     maxBet;     //单注封顶
    int     maxHand;    //手数封顶
    int     pkHand;     //可比手数
    int     minCoin;    //最小金币携带数
    int     coin2Chip;  //金币筹码兑换比例
    int     currentSeat;//当前人数
    int     playSeat;   //正在玩的人数
    int     maxSeat;    //桌子最多人数
    int     opTime;     //超时时间
    int     state;      //桌子当前状态，在大厅里时用。
}TABLE_INFO;

//按照房间ID号排序
bool roomIdGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
bool roomIdLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
//按照最少投注数排序
bool baseBetGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
bool baseBetLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
//按照可比手数排序
bool pkHandGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
bool pkHandLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
//按照最小金币携带数排序
bool minCoinGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
bool minCoinLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
//按照当前状态排序
bool stateGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
bool stateLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
//按照当前人数排序
bool currentSeatGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);
bool currentSeatLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2);


//玩时的桌子数据，只有一份
typedef struct _table_state {
    short   state;          //桌子当前状态
    short   currentHand;    //当前手数
    short   banker;         //当前庄家
    short   baozi;          //场内是否有豹子
    int     chipPool;       //筹码池
    int     minBet;         //最小跟注数，开局时是baseBet，随玩家加注不断加大
    short   nowOp;          //当前操作玩家
} TABLE_STATE;

//座位信息
typedef struct _seat_info {
    int     uid;
    int     state;
    char    cardColor[3];   //牌型
    short   cardNum[3];     //牌的点数
    int     cardScore;      //牌大小点数
    int     dark;           //是否看牌
} SEAT_INFO;

typedef struct _card {
    char    color[3];
    int     number[3];
} CARD;

typedef struct _items {
    int itemid;
    int senderid;
    int starttime;
    int count;
    int state;
}ITEMS;

typedef struct _user_info {
    int     uid;                //用户ID
    char    name[64];           //昵称
    int     sex;                //性别 male=0,female=1
    int     coin;               //金币数量
    char    picture_url[256];   //头像连接
    char    passwd[256];        //账号密码
    int     state;              //用户状态 online=0 offline=1
    int     location[4];        //用户位置
                                //location[3]是座位位置，1-6，与服务器保持一致。
    
    char    lastlogin[64];      //上次登陆时间  
    int     nslogin;            //连续登陆天数
    CARD    maxcard;            //最大手牌
    int     maxscore;           //最大分值
    int     maxwinchip;         //最大赢取
    int     chip;               //筹码
    double  experience;         //经验值
    int     level;              //等级
    int     winrate[2];         //胜率
    int     items_count;        //道具数量
    ITEMS   items[10];          //道具 max=10
    int     reward[6];          //连续登陆奖励列表
}USER_INFO;

typedef struct _reward_info {
    //int     uid;                //用户ID
    char    name[20][256];           //昵称
    int     reward[20];             //奖励金币数量
    char    picture_url[20][256];   //picture连接url
    char    desc[20][256];          //任务描述账号密码
    int     state[20];              //state表示是否已经领取奖励，0表示未领取，1表示已经领取    
    
    int     total[20];              //总局数
    int     finish[20];             //完成数
    
    int     medalId[20];            //成就id
    int     count;              //返回的信息条数
}REWARD_INFO;

typedef struct _isreward_info {
    int     reward;             //奖励金币数量
    int     coin;               //coin  
    int     rewardsCount;       //返回的信息条数
    int     coinsCount;
    int     isMedalId;          //成就id
}ISREWARD_INFO;

typedef struct _message_info {
    int     type;               //信息类型 0为个人信息 1为系统信息 并且最多展示10条信息
    int     count;              //返回的信息条数
    char    date[40][256];      //信息的日期
    char    message[40][256];   //信息的内容
}MESSAGE_INFO;

typedef struct _coin_store{
    char    original_coin[7][32];
    char    current_coin[7][32];
    char    price[7][16];
}COIN_STORE;
#endif
