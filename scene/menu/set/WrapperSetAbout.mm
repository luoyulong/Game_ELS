//供GameStateMainMenu.cpp调用的c++接口

#import "WrapperSetAbout.h"
#import "CommonLayerSetAbout.h"

void menuLayerShowAbout()
{    
    [[CommonLayerSetAbout sharedManager] viewMoveToLeft:SINGLE_LAYER_MOVE otherView:nil];
}