//
//  ItemLayerPlayELS.cpp
//  ThreeCard
//
//  Created by tuyoo on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ItemLayerPlayELS.h"
ItemLayerPlayELS::ItemLayerPlayELS()
{
    
    
    GEScene* pScene = GEDirector::GetInstance()->getScene("GameScenePlayELS");
    pScene->addChild(this,15);

    //init font
    
    mLFont=new CCFont(60.0f);
    
    
    mItemSelected=mAssetCommon->GetImage("itemselect.png");
    mTempItem = mAssetCommon->GetImage("tempitem.png");   
    mItemLimitNotice=mAssetCommon->GetImage("itemLimitNotice.png");
    mFace = mAssetCommon->GetImage("face.png");//道具笑脸
    mUnlock   = mAssetCommon->GetImage("unlock.png");
    DisplayItems();

}

void ItemLayerPlayELS::DisplayItems()
{
    for(int itemidx=0;itemidx<10;itemidx++)
    {
        ItemBLKBt[itemidx]=GEButton::buttonWithTarget(gamelayer, menu_selector(GameLayerPlayELS::PlayItemButton));
        ItemBLKBt[itemidx]->setButtonImages(Game_layer->mItemBLK[itemidx+1], NULL,NULL);//Game_layer->mItemBLK[itemidx+1], Game_layer->mItemBLK[itemidx+1]);
        
        ItemBLKBt[itemidx]->setColor(1, 1, 1, 1);
        int x=Game_layer->GetButtonRecItem(itemidx, 0)+Game_layer->GetButtonRecItem(itemidx, 2)-15;
        int y=Game_layer->GetButtonRecItem(itemidx, 1)+Game_layer->GetButtonRecItem(itemidx, 3)-2;
        ItemBLKBt[itemidx]->setPosition(x, y);
       
        this->addChild(ItemBLKBt[itemidx]); 
        
     
      //  if(GameSet->gamemode!=ELS_MODE_NET)
        //    mRender->RenderImage(mTempItem, 
          //                       Game_layer->GetButtonRecItem(itemidx, 0)+Game_layer->GetButtonRecItem(itemidx, 2)-15, 
            //                     Game_layer->GetButtonRecItem(itemidx, 1)+Game_layer->GetButtonRecItem(itemidx, 3)-2);

    }
    
    
}
void ItemLayerPlayELS::RenderItem()
{	
    //绘制刚获得的道具
    for(vector<ITEMMOVE>::iterator it=Game_layer->mItemFly.begin(); it!=Game_layer->mItemFly.end();)
    {
        int _itemtype	= it->itemtype;
        int _startx		= it->startx;
        int _starty     = it->starty;
        int _endx		= it->endx;
        int _endy		= it->endy;
        int _itemstage	= it->item_move_stage;
        if (it->display_handler==NULL) {
            it->display_handler=Annimation_layer->Display_Item(_itemtype, _startx, _starty);
        }
        GESprite * _display_handler= it->display_handler;
        
        if (_itemstage==0) {
            if (_itemtype<20) {//如果是得道具，那么在stage=0时得到这个道具，把道具数量+1
                if (GameSet->gamemode==ELS_MODE_NET)
                    g_item_num[_itemtype-1]++;
                else 
                    Game_layer->mItemNum[_itemtype-1]++;
            }
            //从vector中移除这个动作
            Annimation_layer->removeChild(_display_handler);
            it=Game_layer->mItemFly.erase(it);
            //判断是否是非网络模式下的第一个道具
            if (GameSet->gamemode!=ELS_MODE_NET && GameSet->gamemode!=ELS_MODE_REPLAY && isFirstItem==1 && g_options[9]>=0) { //不和hold的提示冲突
                if (g_options[8]>0) {
                    g_options[8]*=-1;//暂时标记为<0，以使GameStateReward识别显示道具相关的帮助
                     //暂停游戏，并增加reward-state
                    //ELS_PAUSE=true;
                    //edit by luoyulong
                   // GameState* rr=mApp->mGameStates[GAME_STATE_REWARD];
                    //rr->mArrowX = _endx;
                    //rr->mArrowY = _endy;
                    //mApp->AddState(mApp->mGameStates[GAME_STATE_REWARD]);
                }
                isFirstItem=0;
            }
        }
        else
            if(_itemstage > 0) //还没有移动完
            {
                float ralaph=_itemstage*1.0f/MAX_CLEAR_ITEM_STAGE;
                if (_itemtype<20&&it==Game_layer->mItemFly.begin()) 
                {//得到道具时在原道具位置显示"+500"字样
                    mRender->SetColor(1.0f, 1.0f, 1.0f, ralaph);
                    char reward_s[4];
                    int reward=Game_layer->mItemFly.size()*500;
                    sprintf(reward_s,"+%d",reward);
                    mLFont->DrawString(reward_s, _startx-10.0f, _starty-20);
                    
                }
                if (_itemtype>0 && _itemtype<20) //得到道具，显示对应的道具
                {  _display_handler->setPosition(_startx+(_endx-_startx)*(1.0-ralaph), _starty+(_endy-_starty)*(1.0-ralaph)+Game_layer->get_adjy_bygrect(0));
                }
                else if (_itemtype>=20) //使用道具时，显示星星，还要加粒子效果
                {
                    if (ralaph >= 0.3) {
                        float iux=_startx+(_endx-_startx)*(1.0-(ralaph-0.3)/0.7);
                        float iuy=_starty+(_endy-_starty)*(1.0-(ralaph-0.3)/0.7)+Game_layer->get_adjy_bygrect(0);
                        _display_handler->setPosition(iux, iuy);
                    }
                    else {
                       _display_handler->setPosition(_endx,_endy);
                    }
                }
                it->item_move_stage--;
                ++it;
                }
    }	

    mRender->SetColor(1, 1, 1, 1);
    //绘制选中的道具金黄色的底色
    if (mItemChoose!=0) {
        if ((GameSet->gamemode==ELS_MODE_NET && g_item_num[mItemChoose-1]>0)
            ||(GameSet->gamemode!=ELS_MODE_NET && Game_layer->mItemNum[mItemChoose-1]>0)) {
            mRender->SetColor(1, 1, 1, 1);
            mRender->EnableAddictiveDraw(true);
            mRender->RenderImage(mItemSelected, (Game_layer->GetButtonRecItem(mItemChoose-1, 0)+Game_layer->GetButtonRecItem(mItemChoose-1, 2)) -15, 
                                 (Game_layer->GetButtonRecItem(mItemChoose-1, 1)+Game_layer->GetButtonRecItem(mItemChoose-1, 3))-2);
            mRender->EnableAddictiveDraw(false);
        }
    }
    //绘制道具栏
    for (int itemidx=0; itemidx<10; itemidx++)
    {        //显示道具还剩多少数量
        //char itemnum[5];
        int  n;
        if (GameSet->gamemode==ELS_MODE_NET) //网络对战，数据取自ELSSaveData。
            n = g_item_num[itemidx];
        //else if (GameSet->gamemode==ELS_MODE_AI)//本地模式，则每局都是重新计算。
        else 
            n = Game_layer->mItemNum[itemidx];
        
        int ax,ay;
        if (itemidx<6)
        {
            ax=28,ay=4;
            mRender->SetColor(0.1f, 0.6f, 0.6f, 1);
        }
        else
        {
            ax=-10,ay=42;
            mRender->SetColor(1, 1, 1, 1);
        }
        Game_layer->drawnum(n, Game_layer->GetButtonRecItem(itemidx, 0)+Game_layer->GetButtonRecItem(itemidx, 2)+ax,
                Game_layer->GetButtonRecItem(itemidx, 1)+Game_layer->GetButtonRecItem(itemidx, 3)+ay, 0.0f, 0.85f, 0.85f);
        mRender->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        //如果网络状态下道具已达到使用限制，则显示禁止使用的图标
        if(GameSet->gamemode==ELS_MODE_NET && Game_layer->mItemLimit[itemidx]<=0)
            mRender->RenderImage(Game_layer->mCanNotUseItem, 
                                 Game_layer->GetButtonRecItem(itemidx, 0)+Game_layer->GetButtonRecItem(itemidx, 2)-5,
                                 Game_layer->GetButtonRecItem(itemidx, 1)+Game_layer->GetButtonRecItem(itemidx, 3));
    }
    //显示道具使用限制的提示
    if (GameSet->gamemode==ELS_MODE_NET && mShowItemLimitNoticeStageLeft>0) {
        mShowItemLimitNoticeStageLeft--;//不在Update里判断了
        mRender->RenderImage(mItemLimitNotice, 320, 900);
    }
    mRender->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    //绘制具有持续时间的道具，盾牌和遮挡
    for (int player=0; player<4; player++) {
        if (player==0) {//自己的道具
            //if (mGS[player].shield_remain_time>0) 
            //mRender->RenderImage(mShield, 300, 200);
            
            if (mGS[player].face_remain_time>0)
                mRender->RenderImage(mFace, 240, 450, 0, 1.3,1.3);
        }
        else {//其他人的道具
            if (mGS[player].face_remain_time>0)
                mRender->RenderImage(mFace, 495, 180+280*(player-1), 0, 0.3, 0.3);
        }
    }
    
    

    //绘制解锁新的试炼阵...
    static int lastunlock=0;
    if (mGS[0].unlock_stage==MAX_UNLOCK_STAGE) {
        lastunlock=1;
    }
    
    if (mGS[0].unlock_stage>0 && lastunlock!=0) {
        static float rx, ry, ra, rs;
        if (mGS[0].unlock_stage%5==0) {
            rx=rand()%10;
            ry=rand()%10;
            ra=rand()%10/100.0f;
            rs=rand()%50/100.0f;
        }
        //mParticleSystem2->Render(0, 0);
        mRender->SetColor(1, 1, 1, 1);
        mRender->RenderImage(mUnlock, 375.0f+rx, 145.0f+ry, ra, 0.5+rs, 0.5+rs);
        mGS[0].unlock_stage--;
        //printf("unlock=%d\n", mGS[0].unlock_stage);
        if (mGS[0].unlock_stage==0) 
        {
            Game_layer->mAdventureWin=true;
           // ProcessOver(0, false);
        }
    }
    else {
        lastunlock=0;
    }	
    
}

void ItemLayerPlayELS::Render(CCRenderBox* mRender)
{
    RenderItem();
    
}


ItemLayerPlayELS::~ItemLayerPlayELS()
{}
