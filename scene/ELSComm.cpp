//
//  ELSComm.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ELSComm.h"
CCAssetBox*  mAssetCommon;
map<string, obstacles> obstacles_set;
GELayer * gamelayer;
GELayer * Annimationlayer;
GSTAT			mGS[4];
int mainx,mainy;
u8 mElsMode, mElsRepMode, mSafeTop, mTurnMode, mTheme, mRepTheme, mNanDu;//stat data
CCRenderBox* mRender;
int				isFirstItem;
int				mItemChoose;//选中了哪个道具，0未选中，1-10对应10个道具，使用道具时用于识别手势。
int				mShowItemLimitNoticeStageLeft;//游戏中道具限制的提示，显示的剩余帧数。
GEButton * ItemBLKBt[10];