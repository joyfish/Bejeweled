//
//  GameLose.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#include "GameLose.h"
#include "QuickBuy.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HJNI.h"
#endif

GameLose* GameLose::instance= NULL;

void GameLose::init(void *data){
    G::G_playEffect(RES_MUSIC_GAMEOVER);
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameLoseResult.json");
    UIWidget* reason = NULL;
    if (G::g_game_win_conditions[WIN_CONDITION_SCORE]>0) {
        reason = m_tips->getChildByName("reason_2");
    }else{
        reason = m_tips->getChildByName("reason_1");
    }
    if (reason) {
        reason->setVisible(true);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    IntToStringFormat(_level, "level%d", G::g_game_stage+1);
    HJNI::umengfailLevel(_level);
#endif
}

void GameLose::startAnim(){
    HCCWindow::startAnim();
    UIWidget* title = m_tips->getChildByName("title_bg");
    UIWidget* btn_home = m_tips->getChildByName("btn_home");
    UIWidget* btn_restart = m_tips->getChildByName("btn_restart");
    UIWidget* btn_next = m_tips->getChildByName("btn_buy_next");
    title->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCRotateBy::create(0.15f, -5), NULL));
    PopNode(btn_home, 0.4f);
    PopNode(btn_restart,0.8f);
    PopNode(btn_next, 1.2f);
    btn_home->setTouchEnable(true);
    btn_restart->setTouchEnable(true);
    btn_home->addReleaseEvent(this, coco_releaseselector(GameLose::onHome));
    btn_restart->addReleaseEvent(this, coco_releaseselector(GameLose::onReTry));
    if (G::g_game_stage + 1>= MAX_STAGE) {
        btn_next->setVisible(false);
    }else{
        btn_next->setTouchEnable(true);
        btn_next->addReleaseEvent(this, coco_releaseselector(GameLose::onBuyNext));
    }
}

void GameLose::onHome(cocos2d::CCObject *sender){
    DoVoidEvent(m_homeListener, m_homeSelector)
    //closeWindow();
}

void GameLose::onReTry(cocos2d::CCObject *sender){
    DoVoidEvent(m_retryListener, m_retrySelector)
    closeWindow();
}

void GameLose::onBuyNext(cocos2d::CCObject *sender){
    if (G::G_costCoin(3000)) {
        int next_stage = G::g_game_stage+1;
        
        if (next_stage<MAX_STAGE&&next_stage>=0) {
            StageInfo* info = (StageInfo*)G::g_stageInfos->objectAtIndex(next_stage);
            info->isOpened = true;
            HPersistence::S()->SaveStage(next_stage);
            int needcloudId = (next_stage+1)/CLOUD_PADDING-1;
            if (needcloudId<0||G::g_cloud_isOpened[needcloudId]) {
                closeWindow();
                DoVoidEvent(m_nextStageListener, m_nextStageSelector)
                return;
            }
        }
        DoVoidEvent(m_homeListener, m_homeSelector)
    }else{
        QuickBuy::show(m_layer,new QuickBuyParam(0));
    }
}