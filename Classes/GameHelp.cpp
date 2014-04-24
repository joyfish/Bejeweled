//
//  GameHelp.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-15.
//
//

#include "GameHelp.h"

void GameHelp::init(void *data){
    GameHelpParam* param = (GameHelpParam*)data;
    int id = 0;
    if (param) {
        id = param->id;
    }
    
    IntToStringFormat(_tipsName, "Help%d.json", id);
    m_tips = CCUIHELPER->createWidgetFromJsonFile(_tipsName);
    CC_SAFE_DELETE(param);
}

void GameHelp::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("BTN_OK");
    PopNode(btn_close,0.4f);
    btn_close->addReleaseEvent(this, coco_releaseselector(GameHelp::onClose));
}


void GameHelp::onClose(cocos2d::CCObject *sender){
    closeWindow();
}
