//
//  GameReady.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-7.
//
//

#include "GameReady.h"

GameReady* GameReady::instance = NULL;

void GameReady::init(void *data){
    GameReadyModeParam* param = (GameReadyModeParam*)data;
    GAMEMODE_TYPE mode = MODE_TIME;
    if (param!=NULL) {
        mode = param->mode;
    }
    CC_SAFE_DELETE(param);
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameReady.json");
    Play(mode);
    }

void GameReady::update(float dt){
}

void GameReady::Play(GAMEMODE_TYPE mode){
    UIWidget* m_1 = m_tips->getChildByName("m_1");
    UIWidget* m_2 = m_tips->getChildByName("m_2");
    UIWidget* m_3 = m_tips->getChildByName("m_3");
    UIWidget* m_go = m_tips->getChildByName("m_go");
    m_1->setVisible(false);
    m_2->setVisible(false);
    m_3->setVisible(false);
    m_go->setVisible(false);
    m_1->setScale(5.0f);
    m_2->setScale(5.0f);
    m_3->setScale(5.0f);
    m_go->setScale(5.0f);
    switch (mode) {
        case MODE_TIME:
            m_1->runAction(CCSequence::create(CCDelayTime::create(1.6f),CCShow::create(),CCScaleTo::create(0.15f, 1.0f),CCDelayTime::create(0.35f),CCHide::create(),NULL));
            m_2->runAction(CCSequence::create(CCDelayTime::create(1.1f),CCShow::create(),CCScaleTo::create(0.15f, 1.0f),CCDelayTime::create(0.35f),CCHide::create(),NULL));
            m_3->runAction(CCSequence::create(CCDelayTime::create(0.6f),CCShow::create(),CCScaleTo::create(0.15f, 1.0f),CCDelayTime::create(0.35f),CCHide::create(),NULL));
            m_go->runAction(CCSequence::create(CCDelayTime::create(2.1f),CCShow::create(),CCScaleTo::create(0.15f, 1.0f),CCDelayTime::create(0.5f),CCCallFuncN::create(this,callfuncN_selector(GameReady::onWindowClose)), NULL));
            break;
        case MODE_STEP:
            m_go->runAction(CCSequence::create(CCDelayTime::create(0.6f),CCShow::create(),CCScaleTo::create(0.15f, 1.0f),CCDelayTime::create(0.5f),CCCallFuncN::create(this,callfuncN_selector(GameReady::onWindowClose)), NULL));
            break;
        default:
            break;
    }
}

void GameReady::onWindowClose(cocos2d::CCNode *sender){
    closeWindow();
}