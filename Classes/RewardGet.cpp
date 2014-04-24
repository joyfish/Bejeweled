//
//  RewardGet.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#include "RewardGet.h"

RewardGet* RewardGet::instance = NULL;

void RewardGet::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("RewardGet.json");
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

void RewardGet::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_close,0.4f);
    btn_close->addReleaseEvent(this, coco_releaseselector(RewardGet::onClose));
}

void RewardGet::initItems(CCArray* rewards){
    G::G_getRewards(rewards);
    UIWidget* bg = m_tips->getChildByName("bg");
    CCArray* _items = CCArray::create();
    CCObject* obj;
    int id = 0;
    
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/reward_des.plist");
    
    CCARRAY_FOREACH(rewards, obj){
        RewardInfo* info = (RewardInfo*)obj;
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
    
    _strings->release();
    
    G::G_orderUIWiddget(_items, ccp(-148, -150), 1, 0, -90);
    
    CCSize bgSize  =CCSizeMake(568,250+(_items->count()-1)*90);
    
    bg->setSize(bgSize);
    bg->setPosition(ccp(_pCenter.x, _pCenter.y+bgSize.height/2));
    m_autoCenter = false;
    
    _items->removeAllObjects();
    CC_SAFE_DELETE(_items);
}


void RewardGet::onClose(cocos2d::CCObject *sender){
    closeWindow();
}