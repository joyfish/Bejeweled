//
//  SeaModeResult.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#include "SeaModeResult.h"

SeaModeResult* SeaModeResult::instance = NULL;

void SeaModeResult::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("SeaModeResult.json");
    SeaModeResultParam* param = (SeaModeResultParam*)data;
    m_star = 0;
    int _hurt = 0;
    int _max_blood = 0;
    int _coin = 0;
    m_rewards = NULL;
    m_currentdepth = 0;
    if (param) {
        _hurt = param->hurt;
        _max_blood = param ->max_blood;
    }
    
    if (_hurt == _max_blood) {
        G::G_Add_Achievement_Complete(31);
    }
    
    CCLOG("hurt %d,max %d",_hurt,_max_blood);
    for (int i=0; i< 4; i++) {
        if (_hurt<(i+1)*_max_blood/4) {
            break;
        }
        m_star++;
    }
    
    m_rewards= CCArray::create();

    switch (m_star) {
        case 4:
            m_rewards->addObject(new RewardInfo(t_getRandom(6)+2,1));
        case 3:
            m_rewards->addObject(new RewardInfo(t_getRandom(6)+2,1));
        case 2:
            _coin += 1000;
        case 1:
            _coin += 1000;
            break;
        default:
            break;
    }
    
    UIWidget* label_noReward = m_tips->getChildByName("label_noReward");
    if (m_rewards->count() == 0) {
        label_noReward->setVisible(true);
    }

    m_bar = (UILoadingBar*)m_tips->getChildByName("bar");
    m_bar_percent = _hurt*100/_max_blood;
    m_bar ->setPercent(m_bar_percent);
    
    
    UILabelAtlas* mCoin = (UILabelAtlas*)m_tips->getChildByName("mCoin");
    IntToString(_nCoin, _coin);
    mCoin->setStringValue(_nCoin);
    
    
    G::G_getReward(0,_coin);
    
    G::G_getRewards(m_rewards);
    
    HPersistence::S()->SaveToFile();
    CC_SAFE_DELETE(param);
}

void SeaModeResult::startAnim(){
    HCCWindow::startAnim();
    if (m_star>=0&&m_star<=4) {
        for (int i=0; i<4; i++) {
            IntToStringFormat(_starName, "gift_%d", i);
            UIWidget* mStars = m_tips->getChildByName(_starName);
            if (i>=m_star) {
                mStars->setVisible(false);
                continue;
            }else{
                mStars->setVisible(true);
            }
            
            PopNodeQ(mStars, 0.6f+0.4f*i);
        }
    }
    UIWidget* btn_home = m_tips->getChildByName("btn_home");
    UIWidget* btn_next = m_tips->getChildByName("btn_next");
    
    if (m_rewards) {
        for (unsigned int i=0; i<m_rewards->count()&&i<4; i++) {
            RewardInfo* info = (RewardInfo*)m_rewards->objectAtIndex(i);
            IntToStringFormat(_rName,"reward_%d",i+1);
            UIImageView* mReward = (UIImageView*)m_tips->getChildByName(_rName);
            IntToStringFormat(_iconName, "icons/icon_reward_%d.png",info->id);
            mReward->setTexture(_iconName);
            UILabelAtlas* num = (UILabelAtlas*)mReward->getChildByName("count");
            IntToStringFormat(_count, ":%d",info->count);
            num->setStringValue(_count);
            mReward->setVisible(true);
            PopNodeQ(mReward, 0.4f+0.4f*m_star);
        }
        m_rewards->removeAllObjects();
        CC_SAFE_DELETE(m_rewards);
    }
    
    PopNode(btn_home, 0.4f+0.4f*m_star);
    PopNode(btn_next, 0.8f+0.4f*m_star);
    
    btn_home->addReleaseEvent(this, coco_releaseselector(SeaModeResult::onHome));
    btn_next->addReleaseEvent(this, coco_releaseselector(SeaModeResult::onRestart));
}

void SeaModeResult::onHome(cocos2d::CCObject *sender){
    //closeWindow();
    DoVoidEvent(m_homeListener, m_homeSelector);
    
}

void SeaModeResult::onRestart(cocos2d::CCObject *sender){
    closeWindow();
    DoVoidEvent(m_restartListener, m_restartSelector);
}
