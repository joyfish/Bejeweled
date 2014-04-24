//
//  MenuScene.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#include "MenuScene.h"

void MenuScene::onEnter(){
    HScene::onEnter();
    G::g_gamescene_type = GAMESCENE_MENU;
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
    G::G_playBackGroundMusic(RES_MUSIC_MENU_BG);
    UIWidget* menu = CCUIHELPER->createWidgetFromJsonFile("GameMenu.json");
    m_layer->addWidget(menu);
    menu->setPosition(CCPointZero);
    UIWidget* bg = menu->getChildByName("bg");
    bg->setPosition(_pCenter);
    UIWidget* btn_setting = menu->getChildByName("btn_setting");
    UIWidget* btn_play = menu->getChildByName("btn_play");
    UIWidget* btn_back = menu->getChildByName("btn_back");
    btn_setting->addReleaseEvent(this, coco_releaseselector(MenuScene::onSettingClicked));
    btn_play->addReleaseEvent(this, coco_releaseselector(MenuScene::onPlayClicked));
    btn_back->addReleaseEvent(this, coco_releaseselector(MenuScene::onBackClicked));
    btn_setting->setPosition(ccp(_pLeft+60, _pBottom+60));
    btn_back->setPosition(ccp(_pRight-60, _pBottom+60));
    UIWidget* l = btn_play->getChildByName("arrow_l");
    UIWidget* r = btn_play->getChildByName("arrow_r");
    l->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.4f, ccp(-20, 0)),CCMoveBy::create(0.3f, ccp(20, 0)),NULL)));
    r->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.4f, ccp(20, 0)),CCMoveBy::create(0.3f, ccp(-20, 0)),NULL)));
    
//    UIWidget* sprite_name = menu->getChildByName("name");
//    sprite_name->setPosition(ccp(0, _pTop/4));
//    sprite_name -> runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5f, 1.1f),CCScaleTo::create(0.2f, 0.8f),CCScaleTo::create(0.1f,1.0f), NULL)));

    UIWidget* light = bg->getChildByName("light");
    light->setOpacity(128);
    light->runAction(CCRepeatForever::create(CCRotateBy::create(5.0f, 360)));
}

void MenuScene::loadResource(){
    HScene::loadResource();
    if (!G::g_has_first_saved) {
       addTextureName("menu/bg.png");
    }
//
//    addTextureName("menu/title.png");
//    addTextureName("menu/blue_light.png");
//    addTextureName("menu/btn_start_up.png");
//    addTextureName("menu/btn_start_down.png");
//    addTextureName("menu/btn_exit_up.png");
//    addTextureName("menu/btn_exit_down.png");
//    addTextureName("menu/btn_set_up.png");
}

void MenuScene::ReleaseResource(){
    HScene::ReleaseResource();
    releaseTexture("menu/bg.png");
    releaseTexture("menu/title.png");
    releaseTexture("menu/blue_light.png");
    releaseTexture("menu/btn_start_up.png");
    releaseTexture("menu/btn_start_down.png");
    releaseTexture("menu/btn_exit.up.png");
    releaseTexture("menu/btn_exit_down.png");
    releaseTexture("menu/btn_set_up.png");
    releaseTexture("menu/btn_set_down.png");
}


void MenuScene::onStarMovedOver(cocos2d::CCNode *o){
    o->removeFromParentAndCleanup(true);
    
}


void MenuScene::onSettingClicked(CCObject* sender){
    Setting::show(m_layer);
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
}

void MenuScene::onBackClicked(CCObject* sender){
    GameQuit::show(m_layer);
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
}

void MenuScene::onPlayClicked(CCObject* sender){
     changeScene(M_SCENE_MAIN);
     G::G_playEffect(RES_MUSIC_MENU_START);
    //GameReady::show(m_layer,new GameReadyModeParam(MODE_TIME)); //游戏计时
    //GameLose::show(m_layer,new GameLoseParam(TARGET_SCORE));//游戏失败
    //GamePause::show(m_layer,new GamePauseParam(GAMEMODE_STAGE,3));//游戏暂停
    //GameWin::show(m_layer,new GameWinParam(3000));//游戏胜利
    //HoleModeShow::show(m_layer);
//    CCArray* rewards = CCArray::create();
//    for (int i=0; i<4; i++) {
//        rewards->addObject(new RewardInfo(3,2));
//    }
//    HoleModeResult::show(m_layer,new HoleModeResultParam(3000,G::g_hole_max_score,    3,200,rewards,G::g_hole_total_depth,20));//洞穴模式结算
    //ShopBuyed::show(m_layer,new RewardsParams(rewards));
//    RewardGet::show(m_layer,new RewardsParams(rewards));
//    HoleModeInfo::show(m_layer);//洞穴模式没有开启的时候界面
 //   HoleModeOpenTips::show(m_layer);//洞穴模式开启的提示界面
 //    ToolBuy::show(m_layer,new ToolBuyParam(2,5));
//    int* win_conditions = new int[MAX_WIN_CONDITIONS];
//    for (int i=0; i<MAX_WIN_CONDITIONS; i++) {
//        win_conditions[i] = 0;
//    }
//    win_conditions[0]=20;
//    win_conditions[1]=20;
//     //win_conditions[2]=20;
//    win_conditions[9] = 200;
//    int* lose_conditions = new int[MAX_LOSE_CONDITIONS];
//    lose_conditions[0] = 0;
//    lose_conditions[1] = 100;
 //     G::G_loadGameMap(GAMEMODE_STAGE, 20);
 //   GameStart::show(m_layer);
 //   changeScene(M_SCENE_GAME);
 //   Shop::show(m_layer);
 //   QuickBuy::show(m_layer,new QuickBuyParam(4));
    
}