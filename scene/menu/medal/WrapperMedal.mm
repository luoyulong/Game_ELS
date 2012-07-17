//供GameStateMainMenu.cpp调用的c++接口

#import "WrapperMedal.h"
#import "MenuLayerMedal.h"

void menuLayerShowMedal()
{
    [[MenuLayerMedal sharedManager] sendGetMedal];
    [[MenuLayerMedal sharedManager] viewMoveToLeft:SINGLE_LAYER_MOVE otherView:nil];
}