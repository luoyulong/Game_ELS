#include <stdio.h>

#include "CCGameBox.h"
#include "GameApp.h"

//3cards classes
#include "GameStateLoading.h"


GameApp::GameApp()
{
    //在子线程读取图片资源，资源没有读取完成时不能建立其他的State，因此其他State放在GameStateLoading的loadInSunThread函数中生成。
    m_pGameStateLoading = new GameStateLoading();
    GEDirector::GetInstance()->setCurrentScene("StateLoading");
}

GameApp::~GameApp()
{
}

