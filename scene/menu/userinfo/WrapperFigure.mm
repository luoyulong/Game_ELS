//供GameStateMainMenu.cpp调用的c++接口

#import "WrapperFigure.h"
#import "MenuLayerUserDetail.h"

void menuLayerShowFigure()
{
    [[MenuLayerUserDetail sharedManager] viewMoveToLeft:SINGLE_LAYER_MOVE otherView:nil];
}

