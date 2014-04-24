//
//  HoleModeShow.cpp
//  Bejeweled
//
//  Created by wilford on 13-12-31.
//
//

#include "HoleModeShow.h"

void HoleModeShow::init(void* data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("HoleModeShow.json");
    UIWidget* wind = m_tips->getChildByName("wind");
    wind->runAction(CCRepeatForever::create(CCRotateBy::create(4.0f, -360)));
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    if (btn_close) {
        btn_close->setTouchEnable(true);
        btn_close->addReleaseEvent(this, coco_releaseselector(HoleModeShow::onCloseClicked));
    }
    UIWidget* btn_start = m_tips->getChildByName("btn_start");
    btn_start->addReleaseEvent(this, coco_releaseselector(HoleModeShow::onGameStart));
    G::G_loadGameMap(GAMEMODE_HOLE, 999);
}

void HoleModeShow::update(float dt){
    HIWindow::update(dt);
    //CCLOG("update %f",dt);
}

void HoleModeShow::startAnim(){
    HCCWindow::startAnim();
    UIWidget* wind = m_tips->getChildByName("wind");
    wind->runAction(CCSequence::create(CCHide::create(),CCDelayTime::create(0.3f),CCShow::create(), CCFadeIn::create(0.2f), NULL));
    UIWidget* btn_start = m_tips->getChildByName("btn_start");
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_start,0.3f);
    PopNode(btn_close, 0.6f);
    
}

void HoleModeShow::onGameStart(cocos2d::CCObject *sender){
    if (!G::G_costBook(1)) {
        QuickBuy::show(m_layer,new QuickBuyParam(5));
        return;
    }
    HPersistence::S()->SaveToFile();
    //closeWindow();
     DoVoidEvent(m_gamestartListener, m_gameStartSelector);
    //addWindowClosedEvent(this, h_windowclosedselector(HoleModeShow::onWindowClosed));
    
}

void HoleModeShow::onCloseClicked(cocos2d::CCObject *sender){
    if (!m_closeListener||!m_closeSelector) {
        closeWindow();
    }
    DoVoidEvent(m_closeListener, m_closeSelector);
}

void HoleModeShow::onWindowClosed(){
   
}


HoleModeShow* HoleModeShow::instance = NULL;