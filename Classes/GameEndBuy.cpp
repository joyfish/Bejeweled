//
//  GameEndBuy.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-20.
//
//

#include "GameEndBuy.h"
#include "QuickBuy.h"

void GameEndBuy::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameEndBuy.json");
    UIWidget* mCoin = m_tips->getChildByName("mCoin");
    UILabelBMFont* coin_num = (UILabelBMFont*)mCoin->getChildByName("num");
    IntToString(_coin, G::G_getCoin());
    coin_num->setText(_coin);
    UILabelBMFont* title = (UILabelBMFont*)m_tips->getChildByName("titile");
    UILabelBMFont* des = (UILabelBMFont*)m_tips->getChildByName("des");
    UILabelBMFont* price = (UILabelBMFont*)m_tips->getChildByName("price");
    UIImageView* icon = (UIImageView*)m_tips->getChildByName("icon");
    CCDictionary* _dic = CCDictionary::createWithContentsOfFile("data/normaltips.plist");
    
    if (G::g_game_lose_conditions[LOSE_CONDITION_TIME]>0) {
        CCString* _title_str = (CCString*)_dic->objectForKey("game_end_des_time");
        CCString* _des_str = (CCString*)_dic->objectForKey("game_end_tool_time");
        IntToString(_price, tool_prices[TOOL_TYPE_TIME]*15/10);
        icon->setTexture("tools/icon_0.png");
        title->setText(_title_str->getCString());
        des->setText(_des_str->getCString());
        price ->setText(_price);
    }else{
        CCString* _title_str = (CCString*)_dic->objectForKey("game_end_des_step");
        CCString* _des_str = (CCString*)_dic->objectForKey("game_end_tool_step");
        IntToString(_price, tool_prices[TOOL_TYPE_STEP]*15/10);
        icon->setTexture("tools/icon_1.png");
        title->setText(_title_str->getCString());
        des->setText(_des_str->getCString());
        price ->setText(_price);
    }
    _dic->release();
}

void GameEndBuy::update(float dt){
    UIWidget* mCoin = m_tips->getChildByName("mCoin");
    UILabelBMFont* coin_num = (UILabelBMFont*)mCoin->getChildByName("num");
    IntToString(_coin, G::G_getCoin());
    coin_num->setText(_coin);
}


void GameEndBuy::startAnim(){
	HCCWindow::startAnim();
	UIWidget* btn_close = m_tips->getChildByName("btn_close");
    UIWidget* btn_continue = m_tips->getChildByName("Btn_Continue");
    btn_close->setTouchEnable(true);
    btn_continue->setTouchEnable(true);
    PopNode(btn_continue, 0.4f);
    PopNode(btn_close,0.8f);
	btn_close->addReleaseEvent(this, coco_releaseselector(GameEndBuy::onCloseClicked));
    btn_continue->addReleaseEvent(this, coco_releaseselector(GameEndBuy::onContinue));
}

void GameEndBuy::onCloseClicked(CCObject* sender){
    DoVoidEvent(m_lose_listener, m_lose_selector);
    closeWindow();
}

void GameEndBuy::onContinue(cocos2d::CCObject *sender){
    int cost = 0;
    if (G::g_game_lose_conditions[LOSE_CONDITION_TIME]>0) {
        cost = tool_prices[TOOL_TYPE_TIME]*1.5f;
    }else{
        cost = tool_prices[TOOL_TYPE_STEP]*1.5f;
    }
    if (!G::G_costCoin(cost)) {
        QuickBuy::show(m_layer,new QuickBuyParam(0));
        return;
    }
    DoVoidEvent(m_continue_listener, m_continue_selector);
    closeWindow();
}

GameEndBuy* GameEndBuy::instance;