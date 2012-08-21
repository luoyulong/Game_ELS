//
//  AnimationLayerPlayELS.h
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_AnimationLayerPlayELS_h
#define ThreeCard_AnimationLayerPlayELS_h

#define SNOW_COUNT 20
#include "GameScenePlayELS.h"
#include "GameEngine.h"
#include "GELayer.h"
#include "GESequenceFrames.h"
#include "CCRenderBox.h"
#include "ELSSaveData.h"
#include "ELSDefine.h"
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





class AnimationLayerPlayELS: public GELayer
{
public:
    AnimationLayerPlayELS();
    ~AnimationLayerPlayELS();
    void Background_Snow(CCRenderBox* mRender,int dir);
    void RendCountDown();
    
    void Render(CCRenderBox* mRender);
    //void onEnter();
    void New_ClearRow(int index);
    void Cancel_ClearRow(int);
    void Render_ClearRow(int);
    
    void New_fall(int index);
    void Cancel_fall(int index);//判断是否在直落，若是直落，则取消调用真正的取消直落函数
    void  RenderDrop(int);//方块的阴影
    
    void Update(float dt);                                  //主循环更新

    void New_UseItem(int,int,int,int,int);
    GESprite * Display_Item(int itemtype,float posx,float posy);
    //void Render_Item();
private:
    //void buttonCallback(GEObject* pObj);
    void Loadimages();
    void Setconfig();
    private:

    
    bool init;
    
    GETimer * fallTimer;
    CCImage * fallImg;
    GEImage * fallImage;
    
    GETimer * ClearRowTimer;
    CCImage * ClearRowImg1;
    CCImage * ClearRowImg2;
    
    GEImage * ClearRowImage1[4];
    GEImage * ClearRowImage2_1[4];
    GEImage * ClearRowImage2_2[4];
    
    
    int mCountDownTimeLeft;//倒计时4秒
    
    GESequenceFrames * m_pBackGround;
      
   
    CCImage *mSnow;
    
    

    CCAssetBox * assetbox;
    GETimer* m_pTimer;
public:float fallstat[4];
    float ClearRowstat[4];
    float ClearRow_displaylength;//消行动画的针数
    
    
    
        
    
};



#endif
