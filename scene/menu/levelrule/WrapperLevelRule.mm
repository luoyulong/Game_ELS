//供GameStateMainMenu.cpp调用的c++接口

#import "WrapperLevelRule.h"
#import "MenuLayerLevelRule.h"

void menuLayerShowLevelRule()
{
    [[MenuLayerLevelRule sharedManager] viewMoveToLeft:SINGLE_LAYER_MOVE otherView:nil];
}