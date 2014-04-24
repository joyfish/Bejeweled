//
//  GameStart.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#include "GameStart.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HJNI.h"
#endif
GameStart* GameStart::instance = NULL;

void GameStart::init(void *data){
    m_isClosed = false;
    m_open_time = 0;
    m_gamestartListener = NULL;
    m_gamestartSelector = NULL;
    m_closeListener = NULL;
    m_closeSelector = NULL;
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameStart.json");
    UILabelAtlas* num_stage = (UILabelAtlas*)m_tips->getChildByName("num_stage");
    UIWidget* left = m_tips->getChildByName("left");
    UIWidget* right = m_tips->getChildByName("right");
    IntToString(_stage, G::g_game_stage+1);
    num_stage->setStringValue(_stage);
    CCPoint num_pos = num_stage->getPosition();
    CCSize num_size = num_stage->getSize();
    left->setPosition(ccp(num_pos.x-num_size.width/2-50,num_pos.y));
    right->setPosition(ccp(num_pos.x+num_size.width/2+50,num_pos.y));
    
    if (G::g_game_win_conditions[WIN_CONDITION_SCORE]>0) {
        UIWidget* score_panel = m_tips->getChildByName("score");
        score_panel->setVisible(true);
        if (G::g_game_lose_conditions[LOSE_CONDITION_TIME]>0) {
            UIWidget* time = score_panel->getChildByName("time");
            time->setVisible(true);
        }else{
            UIWidget* step = score_panel->getChildByName("step");
            step->setVisible(true);
        }
        UILabelAtlas* _num_score = (UILabelAtlas*)score_panel->getChildByName("target_score");
        IntToString(_score, G::g_game_win_conditions[WIN_CONDITION_SCORE])
        _num_score->setStringValue(_score);
        _num_score->setVisible(true);
    }else{
        UIWidget* clear_panel = m_tips->getChildByName("clear");
        clear_panel->setVisible(true);
        if (G::g_game_lose_conditions[0]>0) {
            UIWidget* time = clear_panel->getChildByName("time");
            time->setVisible(true);
        }else{
            UIWidget* step = clear_panel->getChildByName("step");
            step->setVisible(true);
        }
        int condition_count = 0;
        for (int i=0; i<WIN_CONDITION_MAX&&condition_count<4; i++) {
            if (G::g_game_win_conditions[i]>0) {
                IntToStringFormat(_cName, "Icon%d", condition_count);
                UIImageView* _c = (UIImageView*)clear_panel->getChildByName(_cName);
                IntToStringFormat(_iconName, "icons/icon_gem_%d.png", i);
                _c->setTexture(_iconName);
                _c->setVisible(true);
                _c->setScale(1.2f);
                UILabelAtlas* _num_c = (UILabelAtlas*)_c->getChildByName("num");
                IntToString(_c_count, G::g_game_win_conditions[i]);
                _num_c->setStringValue(_c_count);
                _num_c->setPosition(ccp(0, -60));
                condition_count++;
            }
        }
        
        for (int i=0; i<condition_count; i++) {
            IntToStringFormat(_cName, "Icon%d", i);
            UIWidget* _c = clear_panel->getChildByName(_cName);
            CCPoint _c_pos = _c->getPosition();
            _c->setPosition(ccp(100-(condition_count-1)*90/2+i*90,_c_pos.y));
        }
    }
}

void GameStart::update(float dt){
    float pre = m_open_time;
    m_open_time+=dt;
    if (!m_isClosed&&m_open_time>2&&pre<=2) {
        m_isClosed = true;
        closeWindow();
    }
}

void GameStart::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
   // PopNode(btn_close, 0.4f);
    btn_close->setTouchEnable(false);
    btn_close->setVisible(false);
    UIWidget* panel = m_tips->getChildByName("Panel");
    panel->setTouchEnable(true);
    panel->addReleaseEvent(this, coco_releaseselector(GameStart::onCloseClick));
//    UIWidget* btn_start = m_tips->getChildByName("btn_OK");
//    
//    PopNode(btn_start, 0.4f);
//    
//    btn_start->addReleaseEvent(this, coco_releaseselector(GameStart::onStartGame));

}

void GameStart::onStartGame(cocos2d::CCObject *sender){
    G::G_checkPowerRecovery(this, h_voidcallback(HPersistence::SaveToFile));
    if (G::G_costPower(1)) {
        G::G_playEffect(RES_MUSIC_GAME_START);
        if (m_gamestartListener&&m_gamestartSelector) {
            (m_gamestartListener->*m_gamestartSelector)();
        }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        IntToStringFormat(_level, "level%d", G::g_game_stage+1);
        HJNI::umengstartLevel(_level);
#endif
        HPersistence::S()->SaveToFile();
    }else{
        QuickBuy::show(m_layer,new QuickBuyParam(2));
    }
}
