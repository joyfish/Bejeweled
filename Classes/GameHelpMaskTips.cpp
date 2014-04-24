//
//  GameHelpMaskTips.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-15.
//
//

#include "GameHelpMaskTips.h"

void GameHelpMaskTips::init(void *data){
    GameHelpParam* param = (GameHelpParam*)data;
    int id = 0;
    int window_type = 0;
    if (param) {
        id = param->id;
        window_type = param->window_type;
    }
    IntToStringFormat(_tipsName, "GameHelp%d.json", id);
    m_tips = CCUIHELPER->createWidgetFromJsonFile(_tipsName);
    m_tips->setTouchEnable(false);
    CC_SAFE_DELETE(param);
    
    UIWidget* tips_bg = m_tips->getChildByName("bg");
    tips_bg->setPosition(ccp(_pCenter.x,_pCenter.y+360));
    m_autoCenter = false;
    if (window_type == 1) {
        tips_bg->setPosition(ccp(_pCenter.x, _pCenter.y));
        setAnimType(WINDOW_ANIM_RIGHT);
    }
}

void GameHelpMaskTips::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("BTN_OK");
    if (btn_close) {
        btn_close->setTouchEnable(true);
        btn_close->addReleaseEvent(this, coco_releaseselector(GameHelpMaskTips::onHelpMaskClosed));
        PopNode(btn_close, 0.4f);
    }
}

GameHelpMaskTips* GameHelpMaskTips::instance;