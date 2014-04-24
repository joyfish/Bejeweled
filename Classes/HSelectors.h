//
//  HSelectors.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef Bejeweled_HSelectors_h
#define Bejeweled_HSelectors_h

#include "cocos2d.h"

USING_NS_CC;

enum M_SCENE{
    M_SCENE_LOGO,
    M_SCENE_MENU,
    M_SCENE_MAIN,
    M_SCENE_GAME,
    M_SCENE_GAME_TEST
};
//屏幕跳转事件
typedef void (CCObject::*SEL_SCENECHANGE)(M_SCENE scene,void* data);
#define h_scenechangeEvent(_SELECTOR) (SEL_SCENECHANGE)(&_SELECTOR)

//无参回调
typedef void (CCObject::*SEL_VOIDCALLBACK)();
#define h_voidcallback(_SELECTOR) (SEL_VOIDCALLBACK)(&_SELECTOR)

#endif
