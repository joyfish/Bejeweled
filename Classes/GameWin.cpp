//
//  GameWin.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#include "GameWin.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HJNI.h"
#endif

GameWin* GameWin::instance = NULL;

void GameWin::init(void *data){
    G::G_playEffect(RES_MUSIC_SUCCESS);
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameWinResult.json");
    GameWinParam* param = (GameWinParam*)data;
    int stage_id = G::g_game_stage;
    m_star = 0;
    int reward_coin = 0;
    int score = 0;
    if (param) {
        score = param->score;
    }
    
//    for (int i=0; i<MAX_BAO; i++) {
//        if(baos_type[i]!=BAO_FROM_STAGE_OVER)
//            continue;
//        if (baos_level[i]!=stage_id+1) {
//            continue;
//        }
//        BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(i);
//        info->isGot = true;
//    }
    
    
	StageInfo* info_current = (StageInfo*)G::g_stageInfos->objectAtIndex(G::g_game_stage);
    if (!info_current->isPlayed) {
        info_current->isPlayed = true;
    }
	
	if(score>=G::g_game_star_score){
		m_star = 3;
	}else if(score>=G::g_game_star_score*2/3){
		m_star = 2;
	}else{
		m_star = 1;
	}
    
    G::G_Set_SingleRound_Achievement_Complete(23, m_star);
    if (info_current->stars<m_star) {
        info_current->stars = m_star;
        if (m_star == 3) {
            G::G_getReward(1, 1);
        }
    }
    info_current->isPlayed = true;
    
    reward_coin = stage_coin_rewards[m_star-1];
    CC_SAFE_DELETE(param);
    UILabelAtlas* mScore = (UILabelAtlas*)m_tips->getChildByName("mScore");
    UILabelAtlas* mCoin = (UILabelAtlas*)m_tips->getChildByName("mCoin");
    IntToString(_score, score);
    IntToString(_coin, reward_coin);
    mScore->setStringValue(_score);
    mCoin->setStringValue(_coin);
    
    int next_stage = stage_id+1;
    
    if (next_stage<MAX_STAGE&&next_stage>=0) {
        StageInfo* info = (StageInfo*)G::g_stageInfos->objectAtIndex(next_stage);
        info->isOpened = true;
        HPersistence::S()->SaveStage(next_stage);
    }
    
    G::G_getReward(0, reward_coin);
    HPersistence::S()->SaveStage(stage_id);
    HPersistence::S()->SaveToFile();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    IntToStringFormat(_level, "level%d", G::g_game_stage+1);
    HJNI::umengfinishLevel(_level);
    if (G::g_game_stage+1<=5) {
        char val[30];
        sprintf(val,"level%dSuc",G::g_game_stage+1);
        HJNI::callumengs(val,"tool_use",NULL);
    }
#endif
}

void GameWin::startAnim(){
    HCCWindow::startAnim();
    if (m_star>0&&m_star<=3) {
		/*const int _star = m_star;
		vector<UIWidget*> mStars;
        UIWidget* mStars[_star];*/
        for (int i=0; i<m_star; i++) {
            IntToStringFormat(_starName, "Star%d", i+1);
            UIWidget* mStar = m_tips->getChildByName(_starName);
            mStar->setVisible(true);
            PopNodeQ(mStar, 0.6f+0.4f*i);
        }
    }
    UIWidget* mLight = m_tips->getChildByName("light");
    UIWidget* btn_home = m_tips->getChildByName("btn_home");
    UIWidget* btn_restart = m_tips->getChildByName("btn_restart");
    UIWidget* btn_next = m_tips->getChildByName("btn_next");
    UIWidget* mTitle = m_tips->getChildByName("title_bg");
    
    mLight->setVisible(false);
    mLight->runAction(CCRepeatForever::create(CCRotateBy::create(6.0f, 360)));
    mLight->runAction(CCSequence::create(CCDelayTime::create(0.6f+0.4f*m_star),CCShow::create(),NULL));
    mTitle->runAction(CCSequence::create(CCDelayTime::create(0.6f+0.4f*m_star),CCRepeat::create(CCSequence::create(CCScaleTo::create(0.15f, 1.1f),CCScaleTo::create(0.3f, 1.0f),NULL),999),NULL));
    
    PopNode(btn_home, 0.4f+0.4f*m_star);
    PopNode(btn_restart, 0.8f+0.4f*m_star);
    PopNode(btn_next, 1.2f+0.4f*m_star);
    
    btn_home->addReleaseEvent(this, coco_releaseselector(GameWin::onHome));
    btn_restart->addReleaseEvent(this, coco_releaseselector(GameWin::onReStart));
    if (G::g_game_stage>=MAX_STAGE-1) {
        btn_next->setVisible(false);
    }
    btn_next->addReleaseEvent(this, coco_releaseselector(GameWin::onNext));
}

void GameWin::onHome(cocos2d::CCObject *sender){
    //closeWindow();
    DoVoidEvent(m_homeListener, m_homeSelector)
}

void GameWin::onReStart(cocos2d::CCObject *sender){
    closeWindow();
    DoVoidEvent(m_retryListener, m_retrySelector)
}

void GameWin::onNext(cocos2d::CCObject *sender){
    int next_stage = G::g_game_stage+1;
    
    if (next_stage<MAX_STAGE&&next_stage>=0) {
        int needcloudId = (next_stage+1)/CLOUD_PADDING-1;
        if (needcloudId<0||G::g_cloud_isOpened[needcloudId]) {
            closeWindow();
            DoVoidEvent(m_nextListener, m_nextSelector)
            return;
        }
    }
    DoVoidEvent(m_homeListener, m_homeSelector)
}