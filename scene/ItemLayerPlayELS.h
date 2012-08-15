//
//  ItemLayerPlayELS.h
//  ThreeCard
//
//  Created by tuyoo on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ThreeCard_ItemLayerPlayELS_h
#define ThreeCard_ItemLayerPlayELS_h
#include "ELSDefine.h"
#include "ELSComm.h"
#include "GameLayerPlayELS.h"
class ItemLayerPlayELS:public GELayer
{
public:
    ItemLayerPlayELS();
    ~ItemLayerPlayELS();
    
    
    
private:
    void DisplayItems();
    void RenderItem();
//    void Update(float dt);
   void Render(CCRenderBox* mRender);
private:
    GEText *mLFont;
    CCImage  *mItemSelected;
    CCImage  *mTempItem ;
    CCImage *mItemLimitNotice;
    CCImage *	mFace ;
    CCImage *	mUnlock ;
    GEImage *  ItemBLKImg[10];
    // GEButton *mPause;
        
};



#endif
