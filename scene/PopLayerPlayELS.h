//
//  PopLayerPlayELS.h
//  ThreeCard
//
//  Created by mini10 on 12-7-3.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_PopLayerPlayELS_h
#define ThreeCard_PopLayerPlayELS_h
#include "GELayer.h"
#include "GameScenePlayELS.h"
#include "GEButton.h"
class PopLayerPlayELS:public GELayer
{
public:
    PopLayerPlayELS();
    ~PopLayerPlayELS();
    //void onEnter();
private:
    GEButton *mPause;


};


#endif
