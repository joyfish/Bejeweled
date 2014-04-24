//
//  AchieveCompleted.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-16.
//
//

#include "AchieveCompleted.h"

void AchieveCompleted::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("AchieveCompleted.json");
    AchieveCompletedParam* param = (AchieveCompletedParam*)data;
    int id = 0;
    if (param) {
        id = param->id;
    }
    CC_SAFE_DELETE(param);
    ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(id);
    G::G_initAchievement_Item(info, m_tips);
    setAnimType(WINDOW_ANIM_RIGHT);
}


void AchieveCompleted::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setTouchEnable(true);
    btn_close->addReleaseEvent(this, coco_releaseselector(AchieveCompleted::onCloseClicked));
    PopNode(btn_close, 0.4f);
}

void AchieveCompleted::onCloseClicked(CCObject* sender){
    closeWindow();
}

AchieveCompleted* AchieveCompleted::instance;