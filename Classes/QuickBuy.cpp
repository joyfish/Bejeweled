//
//  QuickBuy.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#include "QuickBuy.h"
#include "ShopBuyed.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HJNI.h"
#endif


QuickBuy* QuickBuy::instance = NULL;

void QuickBuy::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("QuickBuy.json");
    QuickBuyParam* param = (QuickBuyParam*)data;
    m_type = 0;
    if (param) {
        m_type = param->type;
    }
    CC_SAFE_DELETE(param);
    
    initQuickTip(m_tips,m_type);
    add_tips = NULL;
    if (m_type/2 == 1) {//精力值充值
        add_tips = CCUIHELPER->createWidgetFromJsonFile("QuickBuy.json");
        UIWidget* t = add_tips->getChildByName("tips");
        t->setVisible(false);
        UIWidget* btn_close = add_tips->getChildByName("btn_close");
        btn_close->removeFromParentAndCleanup(true);
        UIWidget* btn_buy = add_tips->getChildByName("btn_buy");
        btn_buy->setName("btn_buy_1");
        UIWidget* tips_bg = m_tips->getChildByName("bg");
        tips_bg->setPosition(ccp(_pCenter.x,_pCenter.y+120));
        m_autoCenter = false;
        tips_bg->addChild(add_tips);
        add_tips->setZOrder(-1);
        UIWidget* bg = add_tips->getChildByName("bg");
        bg->setName("bg_1");
        bg->setPosition(CCPointZero);
        UIPanel* _panel = (UIPanel*)add_tips;
        _panel->setBackGroundColorOpacity(0);
        initQuickTip(add_tips, 6);
    }
    setAnimType(WINDOW_ANIM_RIGHT);
}

void QuickBuy::initQuickTip(UIWidget* tips, int type){
    if (type<6) {
        UIImageView* title_tips = (UIImageView*)tips->getChildByName("tips");
        IntToStringFormat(_tipsPath, "shop/tips_%d.png", type);
        title_tips->setTexture(_tipsPath);

    }
    UIImageView* _icon = (UIImageView*)tips->getChildByName("Icon");
    UILabelBMFont* des = (UILabelBMFont*)_icon->getChildByName("label");
    IntToStringFormat(_iconPath, "icons/icon_reward_%d.png", quick_buy_type[type/2]);
    _icon->setTexture(_iconPath);
    CCDictionary* _string = CCDictionary::createWithContentsOfFile("data/quickBuy.plist");
    IntToStringFormat(_dKey, "quick_%d", type/2)
    CCString* _s_des = (CCString*)_string->objectForKey(_dKey);
    if (quick_buy_getCount[type/2]>0) {
        IntToStringFormat(_c_des, _s_des->getCString(), quick_buy_getCount[type/2]);
        des->setText(_c_des);
    }else{
        des->setText(_s_des->getCString());
    }
    UIWidget* btn_buy = tips->getChildByName("btn_buy");
    if (!btn_buy) {
        btn_buy = tips->getChildByName("btn_buy_1");
    }
    UILabelAtlas* mCost = (UILabelAtlas*)btn_buy->getChildByName("cost");
    IntToStringFormat(_cost, ":%d", G::quick_buy_prices[type/2]);
    mCost->setStringValue(_cost);
    btn_buy->setTag(type/2);
    _string->release();
}

void QuickBuy::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    UIWidget* btn_buy = m_tips->getChildByName("btn_buy");
    btn_buy->setTouchEnable(true);
    PopNode(btn_buy, 0.4f)
    PopNode(btn_close,0.8f);
    btn_buy->addReleaseEvent(this, coco_releaseselector(QuickBuy::onBuy));
    btn_close->addReleaseEvent(this, coco_releaseselector(QuickBuy::onClose));
    if (add_tips) {
        UIWidget* btn_buy = add_tips->getChildByName("btn_buy_1");
        add_tips->runAction(CCSequence::create(CCDelayTime::create(0.4f),CCMoveBy::create(0.2f, ccp(0, -180)),NULL));
        btn_buy->setTouchEnable(true);
        btn_buy->addReleaseEvent(this, coco_releaseselector(QuickBuy::onBuy));
        PopNode(btn_buy, 0.6f);
    }
}

void QuickBuy::endAnim(){
    HCCWindow::endAnim();
//    if (add_tips) {
//        add_tips->runAction(CCMoveTo::create(0.1f, CCPointZero));
//    }
}


void QuickBuy::onBuy(cocos2d::CCObject *sender){
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    UIWidget* u = (UIWidget*)sender;
    closeWindow();
    int id = u->getTag();
    if (quick_buy_type[id]==9&&G::g_maxPower==MAX_POWER) {
        NormalTips::show(m_layer,new NormalTipsParam(0));
        return;
    }else if(quick_buy_type[id] == 1 && G::G_getPower()>=G::g_maxPower){
        NormalTips::show(m_layer,new NormalTipsParam(1));
        return;
    }
    


    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    IntToStringFormat(_pay, "q%d", id);
    IntToStringFormat(_des, "qv%d", id);
    HJNI::Pay(_pay,_des);
//    char key[30];
//    sprintf(key,"fast%dButton",id+1);
//    HJNI::callumengs(key,"tool_use",NULL);
    switch (id) {
        case 0://金币29
            HJNI::callumeng("event16");
            break;
        case 1://体力满
            HJNI::callumeng("event9");
            break;
        case 2://挑战卷3
            HJNI::callumeng("event23");
            break;
        case 3://拓展卷
            HJNI::callumeng("event11");
            break;
        default:
            break;
    }

#else
     CCArray* rewards = CCArray::create();
    rewards->addObject(new RewardInfo(quick_buy_type[id],quick_buy_getCount[id]));
    ShopBuyed::show(m_layer,new RewardsParams(rewards));
#endif
    
    

    G::g_last_buytype = BUY_TYPE_QUICK;
    G::g_last_buyid = id;
}

void QuickBuy::onClose(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    if (G::g_gamescene_type == GAMESCENE_GAME) {
        Shop::show(m_layer);
    }
    closeWindow();
}