//
//  HoleModeInfo.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#include "HoleModeInfo.h"

HoleModeInfo* HoleModeInfo::instance = NULL;

void HoleModeInfo::init(void* data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("HoleModeInfo.json");
    UIWidget* wind = m_tips->getChildByName("wind");
    wind->runAction(CCRepeatForever::create(CCRotateBy::create(4.0f, -360)));
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    if (btn_close) {
        btn_close->addReleaseEvent(this, coco_releaseselector(HoleModeInfo::onCloseClicked));
    }
}


void HoleModeInfo::startAnim(){
    HCCWindow::startAnim();
    UIWidget* wind = m_tips->getChildByName("wind");
    wind->runAction(CCSequence::create(CCHide::create(),CCDelayTime::create(0.3f),CCShow::create(), CCFadeIn::create(0.2f), NULL));
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_close,0.4f);
}

void HoleModeInfo::onCloseClicked(cocos2d::CCObject *sender){
    closeWindow();
}
