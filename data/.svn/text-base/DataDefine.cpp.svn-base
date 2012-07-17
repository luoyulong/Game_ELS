//
//  dataDefine.cpp
//  GameBox
//
//  Created by  on 12-5-15.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "dataDefine.h"

/* --------------------------- TABLE_INFO排序相关 strat --------------------------- */
//按照房间ID号排序
bool roomIdGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->tid > tableInfo2->tid;
}
bool roomIdLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->tid < tableInfo2->tid;
}
//按照最少投注数排序
bool baseBetGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->baseBet > tableInfo2->baseBet;
}
bool baseBetLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->baseBet < tableInfo2->baseBet;
}
//按照可比手数排序
bool pkHandGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->pkHand > tableInfo2->pkHand;
}
bool pkHandLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->pkHand < tableInfo2->pkHand;
}
//按照最小金币携带数排序
bool minCoinGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->minCoin > tableInfo2->minCoin;
}
bool minCoinLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->minCoin < tableInfo2->minCoin;
}
//按照当前状态排序
bool stateGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->state > tableInfo2->state;
}
bool stateLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->state < tableInfo2->state;
}
//按照当前人数排序
bool currentSeatGreaterCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->currentSeat > tableInfo2->currentSeat;
}
bool currentSeatLessCmp(const TABLE_INFO *tableInfo1, const TABLE_INFO *tableInfo2)
{
    return tableInfo1->currentSeat < tableInfo2->currentSeat;
}
/* --------------------------- TABLE_INFO排序相关  end --------------------------- */
