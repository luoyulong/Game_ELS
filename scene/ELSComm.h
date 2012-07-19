//
//  ELSComm.h
//  ThreeCard
//
//  Created by mini10 on 12-7-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_ELSComm_h
#define ThreeCard_ELSComm_h
#include "CCAssetBox.h"
#include <map>
#include "GELayer.h"
#include "ELSDefine.h"

#define sidex1		423.0f
#define sidey1		mainy+18.0f
#define sidex2		423.0f
#define sidey2		mainy+296.0f
#define sidex3		423.0f
#define sidey3		mainy+574.0f
#define sidesc		0.32f

#define blksize		36.0f
#define SNOW_COUNT	20	

#define blkadjx		74
#define blkadjy		108
#define nextx		mainx+210.0f
#define nexty		mainy+86.0f
#define savex		mainx+342.0f
#define savey		mainy+86.0f

#define BLK_CHANGE_TIME		10.0f

#define tablestra   0.65f
#define tablestrx	60
#define tablestry	170
#define Annimation_layer ((AnimationLayerPlayELS *)(Annimationlayer))


class obstacles
{
public:
    float pos_x;
    float pos_y;
    float h;
    float w;
    obstacles(float x,float y,float h,float w)
    {
        pos_x=x;
        pos_y=y;
        this->h=h;
        this->w=w;
    }
};

extern  CCAssetBox *mAssetCommon;
extern  map<string, obstacles> obstacles_set;
extern  GELayer * gamelayer;
extern  GELayer * Annimationlayer;
extern   GSTAT			mGS[4];
extern int mainx,mainy;


#endif
