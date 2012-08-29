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
    
    GETimer * fallTimer[4];//4个游戏窗口 但目前只启用了主窗口一个
    CCImage * fallImg;
    GEImage * fallImage[4];//4个游戏窗口 但目前只启用了主窗口一个
    
    GETimer * ClearRowTimer[4];//4个游戏窗口
    CCImage * ClearRowImg1;
    CCImage * ClearRowImg2;
    
    GEImage * ClearRowImage1[4][4];//4个游戏窗口每个游戏窗口同时最多消除4行
    GEImage * ClearRowImage2_1[4][4];
    GEImage * ClearRowImage2_2[4][4];
    
    
    int mCountDownTimeLeft;//倒计时4秒
    
    GESequenceFrames * m_pBackGround;
      
   
    
    
    

    CCAssetBox * assetbox;
    GETimer* m_pTimer;
public:float fallstat[4];
    float ClearRowstat[4];
    float ClearRow_displaylength;//消行动画的针数
    
    
    
        
    
};



#endif
