//
//  ShopBuyed.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#include "ShopBuyed.h"
#include "NormalTips.h"
#include "HJNI.h"

//ShopBuyed* ShopBuyed::instance = NULL;

void ShopBuyed::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("ShopBuyed.json");
    RewardsParams* param = (RewardsParams*)data;
    CCArray* rewards = NULL;
    if (param) {
        rewards = param->rewards;
    }
    if (rewards) {
        initItems(rewards);
    }
    CC_SAFE_DELETE(param);
    setAnimType(WINDOW_ANIM_RIGHT);

}

void ShopBuyed::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    //UIWidget* btn_buyagain = m_tips->getChildByName("btn_buy");
    //PopNode(btn_buyagain, 0.4f)
    PopNode(btn_close,0.4f);
    //btn_buyagain->addReleaseEvent(this, coco_releaseselector(ShopBuyed::onBuyAgain));
    btn_close->addReleaseEvent(this, coco_releaseselector(ShopBuyed::onClose));
    
}

void ShopBuyed::initItems(CCArray* rewards){
    
    G::G_getRewards(rewards);
    
    CCLOG("----22222----");
    UIWidget* bg = m_tips->getChildByName("bg");
    CCArray* _items = CCArray::create();
    CCObject* obj;
    int id = 0;
    
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/reward_des.plist");
    
    CCARRAY_FOREACH(rewards, obj){
        RewardInfo* info = (RewardInfo*)obj;
        if (info) {
            UIImageView* _icon = UIImageView::create();
            IntToStringFormat(_iconPath, "icons/icon_reward_%d.png", info->id);
            _icon->setTexture(_iconPath);
            UILabelBMFont* _des = UILabelBMFont::create();
            _des->setFntFile("font/font.fnt");
            _des->setColor(ccc3(110, 67, 50));
            _des->setScale(1.5f);
            _des->setPosition(ccp(60,0));
            _des->setAnchorPoint(_nLeft);
            if (info->count == 99) {
                CCString* _s_des = (CCString*)_strings->objectForKey("reward_max");
                _des->setText(_s_des->getCString());
            }else{
                IntToStringFormat(_dKey, "reward_%d", info->id);
                CCString* _s_des = (CCString*)_strings->objectForKey(_dKey);
                IntToStringFormat(_c_des, _s_des->getCString(), info->count);
                _des->setText(_c_des);
            }
            _icon->addChild(_des);
            bg->addChild(_icon);
            _items->addObject(_icon);
            id ++;
        }
    }
    
    _strings->release();
    
    G::G_orderUIWiddget(_items, ccp(-148, -150), 1, 0, -90);
    
    //CCSize bgSize  =CCSizeMake(568,330+(_items->count()-1)*90);
    CCSize bgSize  =CCSizeMake(568,250+(_items->count()-1)*90);
    
    UIWidget* btn_buyagain = bg->getChildByName("btn_buy");
    btn_buyagain->setVisible(false);
    float y =(_items->count()-1)*90;
    btn_buyagain->setTouchEnable(false);
    btn_buyagain ->setPosition(ccp(0,-265-y));
    
    
    bg->setSize(bgSize);
    bg->setPosition(ccp(_pCenter.x, _pCenter.y+bgSize.height/2));
    m_autoCenter = false;
    
    _items->removeAllObjects();
    CC_SAFE_DELETE(_items);
    
    HPersistence::S()->SaveToFile();
    
}

void ShopBuyed::onBuyAgain(cocos2d::CCObject *sender){
    CCArray* rewards = CCArray::create();
    int id = G::g_last_buyid;
    switch (G::g_last_buytype) {
        case BUY_TYPE_NORMAL:
            if (shop_item_type[id]==9&&G::g_maxPower==MAX_POWER) {
                NormalTips::show(m_layer,new NormalTipsParam(0));
                return;
            }else if(shop_item_type[id] == 1 && G::G_getPower()==G::g_maxPower){
                NormalTips::show(m_layer,new NormalTipsParam(1));
                return;
            }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        {
            IntToStringFormat(_pay, "k%d", id);
            IntToStringFormat(_des, "v%d", id);
            HJNI::Pay(_pay,_des);
            char key[30];
            sprintf(key,"shop%dButton",id+1);
            HJNI::callumengs(key,"tool_use",NULL);
        }
#else
            rewards->addObject(new RewardInfo(shop_item_type[id],shop_item_getCount[id]));
            ShopBuyed::show(m_layer,new RewardsParams(rewards));
#endif
            break;
        case BUY_TYPE_QUICK:
            if (quick_buy_type[id]==9&&G::g_maxPower==MAX_POWER) {
                NormalTips::show(m_layer,new NormalTipsParam(0));
                return;
            }
            else if(quick_buy_type[id] == 1 && G::G_getPower()==G::g_maxPower){
                NormalTips::show(m_layer,new NormalTipsParam(1));
                return;
            }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        {
            IntToStringFormat(_pay, "q%d", id);
            IntToStringFormat(_des, "qv%d", id);
            HJNI::Pay(_pay,_des);
            char key[30];
            sprintf(key,"fast%dButton",id+1);
            HJNI::callumengs(key,"tool_use",NULL);
        }
#else
            rewards->addObject(new RewardInfo(quick_buy_type[id],quick_buy_getCount[id]));
            ShopBuyed::show(m_layer,new RewardsParams(rewards));
#endif
            break;
        default:
            break;
    }

    HCCWindow::onClose();
}

void ShopBuyed::onClose(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    closeWindow();
}