//
//  SeaModeShow.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#include "SeaModeShow.h"

void SeaModeShow::init(void* data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("SeaModeShow.json");
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    if (btn_close) {
        btn_close->setTouchEnable(true);
        btn_close->addReleaseEvent(this, coco_releaseselector(SeaModeShow::onCloseClicked));
    }
    UIWidget* btn_start = m_tips->getChildByName("btn_start");
    btn_start->addReleaseEvent(this, coco_releaseselector(SeaModeShow::onGameStart));
    G::G_loadGameMap(GAMEMODE_SEA, 999);
}

void SeaModeShow::update(float dt){
    HIWindow::update(dt);
    //CCLOG("update %f",dt);
}

void SeaModeShow::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_start = m_tips->getChildByName("btn_start");
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_start,0.3f);
    PopNode(btn_close, 0.6f);
    
}

void SeaModeShow::onGameStart(cocos2d::CCObject *sender){
    if (!G::G_costBook(1)) {
        QuickBuy::show(m_layer,new QuickBuyParam(5));
        return;
    }
    HPersistence::S()->SaveToFile();
    //closeWindow();
    DoVoidEvent(m_gamestartListener, m_gameStartSelector);
    //addWindowClosedEvent(this, h_windowclosedselector(SeaModeShow::onWindowClosed));
    
}

void SeaModeShow::onCloseClicked(cocos2d::CCObject *sender){
    if (!m_closeListener||!m_closeSelector) {
        closeWindow();
    }
    DoVoidEvent(m_closeListener, m_closeSelector);
}

void SeaModeShow::onWindowClosed(){
    
}


SeaModeShow* SeaModeShow::instance = NULL;