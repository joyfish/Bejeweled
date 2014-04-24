//
//  HoleModeOpenTips.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#include "HoleModeOpenTips.h"
#include "HCSVParse.h"

HoleModeOpenTips* HoleModeOpenTips::instance = NULL;

void HoleModeOpenTips::init(void* data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("HoleModeOpenTips.json");
    UIWidget* wind = m_tips->getChildByName("wind");
    wind->runAction(CCRepeatForever::create(CCRotateBy::create(4.0f, -360)));
    UIWidget* btn_close = m_tips->getChildByName("btn_ok");
    if (btn_close) {
        btn_close->addReleaseEvent(this, coco_releaseselector(HoleModeOpenTips::onCloseClicked));
    }
    
//    UILabelBMFont* label = (UILabelBMFont*)m_tips->getChildByName("label");
//    
//    HCSVParse* csvFile = new HCSVParse();
//    csvFile->openFile("test.csv");
//    
//    label->setText(csvFile->getData(1, 1));
//    CCLOG("%s",csvFile->getData(1, 1));
//    label->setAnchorPoint(_nTopLeft);
//    label->setWidth(300);
//    delete csvFile;
}


void HoleModeOpenTips::startAnim(){
    HCCWindow::startAnim();
    UIWidget* wind = m_tips->getChildByName("wind");
    wind->runAction(CCSequence::create(CCHide::create(),CCDelayTime::create(0.3f),CCShow::create(), CCFadeIn::create(0.2f), NULL));
    UIWidget* btn_close = m_tips->getChildByName("btn_ok");
    PopNode(btn_close,0.4f);
}

void HoleModeOpenTips::onCloseClicked(cocos2d::CCObject *sender){
    closeWindow();
}