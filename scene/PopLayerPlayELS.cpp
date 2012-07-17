//
//  PopLayerPlayELS.cpp
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PopLayerPlayELS.h"
#include "GameLayerPlayELS.h"
#include "GEMenu.h"
PopLayerPlayELS::PopLayerPlayELS()
{
    GEScene* pScene = GEDirector::GetInstance()->getScene("GameScenePlayELS");
    pScene->addChild(this,20);
    mPause=new GEButton();
    mPause->setButtonColorOnPress(0, 0, 0, 50);
    mPause->setButtonImageNormal(mAssetCommon->GetImage("Bretry.png"));
    mPause->setPosition(80, 400);
    
    this->addChild(mPause);
    obstacles_set.insert(make_pair("PopLayerPlayELS_mPuase",obstacles(80, 400, 230,90)));
    
    
    
}
PopLayerPlayELS::~PopLayerPlayELS(){}




