//
//  HoleModeResult.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#include "HoleModeResult.h"

HoleModeResult* HoleModeResult::instance = NULL;

void HoleModeResult::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("HoleModeResult.json");
    HoleModeResultParam* param = (HoleModeResultParam*)data;
    int _score = 0;
    int _topScore = G::g_hole_max_score;
    m_star = 0;
    int _coin = 0;
    m_rewards = NULL;
    m_currentdepth = 0;
    if (param) {
        _score = param->hole_score;
        m_currentdepth = param ->depth;
    }
    m_totaldepth = G::g_hole_total_depth;
    
    for (int i=0; i< maxunlimitscorescount; i++) {
        if (_score<unlimitrewardscores[i]) {
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
            _coin += 1000;;
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
    UILabelAtlas* mScore = (UILabelAtlas*)m_tips->getChildByName("mScore");
    UILabelAtlas* mTopScore = (UILabelAtlas*)m_tips->getChildByName("mTopScore");
    UILabelAtlas* mCoin = (UILabelAtlas*)m_tips->getChildByName("mCoin");
    IntToString(_nScore, _score);
    IntToString(_nTopScore, _topScore);
    IntToString(_nCoin, _coin);
    mScore->setStringValue(_nScore);
    mTopScore->setStringValue(_nTopScore);
    mCoin->setStringValue(_nCoin);
    
    UIWidget* mScoreLabel = NULL;
    if (_score>_topScore) {
        mScoreLabel = m_tips->getChildByName("label_mScore_1");
        G::g_hole_max_score = _score;
    }else{
        mScoreLabel = m_tips->getChildByName("label_mScore_0");
    }
    if (mScoreLabel) {
        mScoreLabel->setVisible(true);
    }
    
    G::g_hole_total_depth = m_currentdepth+m_totaldepth;
    
    G::G_getReward(0,_coin);
    
    G::G_getRewards(m_rewards);
    
    HPersistence::S()->SaveToFile();
    CC_SAFE_DELETE(param);
}

void HoleModeResult::startAnim(){
        HCCWindow::startAnim();
    if (m_star>0&&m_star<=4) {
        for (int i=0; i<m_star; i++) {
            IntToStringFormat(_starName, "gift_%d", i);
            UIWidget* mStars = m_tips->getChildByName(_starName);
            mStars->setVisible(true);
            PopNodeQ(mStars, 0.6f+0.4f*i);
        }
    }
    UIWidget* mLight = m_tips->getChildByName("light");
    UIWidget* btn_home = m_tips->getChildByName("btn_home");
    UIWidget* btn_next = m_tips->getChildByName("btn_next");
    UIWidget* mTitle = m_tips->getChildByName("title_bg");
    
    mLight->setVisible(false);
    mLight->runAction(CCRepeatForever::create(CCRotateBy::create(6.0f, 360)));
    mLight->runAction(CCSequence::create(CCDelayTime::create(0.6f+0.4f*m_star),CCShow::create(),NULL));
    mTitle->runAction(CCSequence::create(CCDelayTime::create(0.6f+0.4f*m_star),CCRepeat::create(CCSequence::create(CCScaleTo::create(0.15f, 1.1f),CCScaleTo::create(0.3f, 1.0f),NULL),99),NULL));
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
    
    btn_home->addReleaseEvent(this, coco_releaseselector(HoleModeResult::onHome));
    btn_next->addReleaseEvent(this, coco_releaseselector(HoleModeResult::onRestart));
    
    UIWidget* mContainer = m_tips->getChildByName("Container");
    
    const int count = 8;
    
    UILabelAtlas* mNums[count];
    for (int i=0; i<count; i++) {
        IntToStringFormat(mName, "m_%d", i);
        mNums[i] = (UILabelAtlas*)mContainer->getChildByName(mName);
    }
    SetDepthNum(mNums, count, m_totaldepth)
//    {
//        int tmpNum = m_totaldepth;
//        
//        for (int i=0; i<count; i++) {
//            IntToString(n, tmpNum%10)
//            tmpNum/=10;
//            mNums[i]->setStringValue(n);
//        }
//    }
    ScrollDepthNum(mNums, count, m_totaldepth, m_totaldepth+m_currentdepth);
//    {
//        int pre = m_totaldepth;
//        int current = m_totaldepth+m_currentdepth;
//        for (int i=0; i<count; i++) {
//            if (current%10==pre%10) {
//                current/=10;
//                pre/=10;
//                continue;
//            }
//            IntToString(n, current%10);
//            current/=10;
//            pre/=10;
//            CCPoint pos = mNums[i]->getPosition();
//            UIWidget* parent = mNums[i]->getParent();
//            mNums[i]->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.3f, ccp(0, 50)),CCCallFuncND::create(this, callfuncND_selector(G::G_callbackRemoveUIWidget2),mNums[i]),NULL));
//            mNums[i] = UILabelAtlas::create();
//            mNums[i]->setProperty(n, "numbers/num3.png", 20, 28, "0");
//            mNums[i]->setPosition(ccp(pos.x,pos.y-50));
//            parent->addChild(mNums[i]);
//            mNums[i]->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.3f, ccp(0, 50)),NULL));
//        }
//    }
    

}

void HoleModeResult::onHome(cocos2d::CCObject *sender){
    //closeWindow();
    DoVoidEvent(m_homeListener, m_homeSelector);
    
}

void HoleModeResult::onRestart(cocos2d::CCObject *sender){
    closeWindow();
    DoVoidEvent(m_restartListener, m_restartSelector);
}