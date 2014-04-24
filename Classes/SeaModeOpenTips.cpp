//
//  SeaModeOpenTips.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#include "SeaModeOpenTips.h"

SeaModeOpenTips* SeaModeOpenTips::instance = NULL;

void SeaModeOpenTips::init(void* data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("SeaModeOpenTips.json");
    UIWidget* btn_close = m_tips->getChildByName("btn_ok");
    if (btn_close) {
        btn_close->addReleaseEvent(this, coco_releaseselector(SeaModeOpenTips::onCloseClicked));
    }
}


void SeaModeOpenTips::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_ok");
    PopNode(btn_close,0.4f);
}

void SeaModeOpenTips::onCloseClicked(cocos2d::CCObject *sender){
    closeWindow();
}
