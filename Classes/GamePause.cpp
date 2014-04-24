//
//  GamePause.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#include "GamePause.h"

GamePause* GamePause::instance = NULL;

void GamePause::init(void* data){
    GAMEMODE mode = G::g_game_mode;
    int stage =  G::g_game_stage;
 
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GamePause.json");
    switch (mode) {
        case GAMEMODE_STAGE:
        {
            UILabelAtlas* level = (UILabelAtlas*)m_tips->getChildByName("mlevel");
            char l[10];
            sprintf(l, "%d",stage+1);
            level->setVisible(true);
            level->setStringValue(l);
        }
            break;
        case GAMEMODE_HOLE:
        {
            UIWidget* hole = m_tips->getChildByName("label_hole");
            hole->setVisible(true);
        }
            break;
        case GAMEMODE_SEA:
        {
            UIWidget* sea = m_tips->getChildByName("label_sea");
            sea->setVisible(true);
        }
            break;
        default:
            break;
    }
}

void GamePause::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_continue = m_tips->getChildByName("btn_continue");
    UIWidget* btn_restart = m_tips->getChildByName("btn_restart");
    UIWidget* btn_home = m_tips->getChildByName("btn_home");
    btn_continue->setTouchEnable(true);
    btn_restart->setTouchEnable(true);
    btn_home->setTouchEnable(true);
    PopNodeS(btn_continue, 0.4f);
    PopNodeS(btn_restart, 0.6f);
    PopNodeS(btn_home, 0.8f);
    btn_continue->addReleaseEvent(this, coco_releaseselector(GamePause::onContinue));
    btn_home->addReleaseEvent(this, coco_releaseselector(GamePause::onHome));
    btn_restart ->addReleaseEvent(this, coco_releaseselector(GamePause::onReStart));
}

void GamePause::onContinue(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    closeWindow();
}

void GamePause::onHome(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    //closeWindow();
    DoVoidEvent(m_homeListener, m_homeSelector)
}

void GamePause::onReStart(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    closeWindow();
    DoVoidEvent(m_retryListener, m_retrySelector)
}