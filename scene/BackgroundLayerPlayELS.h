//
//  BackgroundLayerPlayELS.h
//  ThreeCard
//
//  Created by tuyoo on 12-8-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_BackgroundLayerPlayELS_h
#define ThreeCard_BackgroundLayerPlayELS_h
#include "ELSDefine.h"
#include "ELSComm.h"
#include "GEImage.h"
#include "GameLayerPlayELS.h"
typedef struct _bm_object {
	float x, y, scale, arc;
	float angle, speed;
	float scale_speed, arc_speed;
	float r, g, b;
	float alpha;
	int   stage;
} BMOBJ;
static BMOBJ gs_bm_snow[SNOW_COUNT];
class BackgroundLayerPlayELS:public GELayer
{
public:
    BackgroundLayerPlayELS();
    ~BackgroundLayerPlayELS();
   void Background_Snow(CCRenderBox* mRender,int dir);
    void Render(CCRenderBox* mRender);
    void Background_playboard(int idx,float boxx,float boxy,float boxs);
private:
    GEImage * Playboard[4];
    GEImage * Namebk;
    GEButton *mPause;
    CCImage *mSnow;
    bool init;
    
};

#endif
