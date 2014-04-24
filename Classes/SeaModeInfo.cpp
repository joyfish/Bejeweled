//
//  SeaModeInfo.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#include "SeaModeInfo.h"

SeaModeInfo* SeaModeInfo::instance = NULL;

void SeaModeInfo::init(void* data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("SeaModeInfo.json");
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    if (btn_close) {
        btn_close->addReleaseEvent(this, coco_releaseselector(SeaModeInfo::onCloseClicked));
    }
}


void SeaModeInfo::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_close,0.4f);
}

void SeaModeInfo::onCloseClicked(cocos2d::CCObject *sender){
    closeWindow();
}