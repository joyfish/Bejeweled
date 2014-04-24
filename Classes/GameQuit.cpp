//
//  GameQuit.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#include "GameQuit.h"

void GameQuit::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameQuit.json");

    UIWidget* btn_quit = m_tips->getChildByName("label");
    btn_quit->setTouchEnable(true);
    btn_quit->addReleaseEvent(this, coco_releaseselector(GameQuit::onGameQuit));
    //setAnimType(WINDOW_ANIM_RIGHT);
}


void GameQuit::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_contiue  = m_tips->getChildByName("btn_continue");
    btn_contiue->setTouchEnable(true);
    btn_contiue->addReleaseEvent(this, coco_releaseselector(GameQuit::onCloseClicked));
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setTouchEnable(true);
    btn_close->addReleaseEvent(this, coco_releaseselector(GameQuit::onCloseClicked));
    PopNode(btn_close, 0.4f);
    PopNode(btn_contiue, 0.4f);
}

void GameQuit::onCloseClicked(CCObject* sender){
    closeWindow();
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
}

void GameQuit::onGameQuit(cocos2d::CCObject *sender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

GameQuit* GameQuit::instance = NULL;